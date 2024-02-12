#include "CameraUtils/BowApplication.h"

#include "CoreSystems/BowLogger.h"

#include <iostream>

const std::string g_vertexColorShader = R"(#version 130

in vec3 in_Position;
in vec2 in_TexCoord;

out vec2 var_TextureCoord;

void main(void)
{
    gl_Position = vec4(in_Position, 1.0);
    var_TextureCoord = in_TexCoord;
}
)";

const std::string g_fragmentColorShader = R"(#version 130
precision highp float; // needed only for version 1.30

in vec2 var_TextureCoord;
uniform sampler2D inputTexture;

out vec4 out_Color;

void main(void)
{
    out_Color = vec4( texture(inputTexture, vec2(var_TextureCoord.x, 1.0 - var_TextureCoord.y)).rgb, 1.0);
}
)";


const std::string g_vertexGreyscaleShader = R"(#version 130

in vec3 in_Position;
in vec2 in_TexCoord;

out vec2 var_TextureCoord;

void main(void)
{
    gl_Position = vec4(in_Position, 1.0);
    var_TextureCoord = in_TexCoord;
}
)";

const std::string g_fragmentGreyscaleShader = R"(#version 130
precision highp float; // needed only for version 1.30

in vec2 var_TextureCoord;
uniform sampler2D inputTexture;

out vec3 out_Color;

void main(void)
{
    out_Color = texture(inputTexture, vec2(var_TextureCoord.x, 1.0 - var_TextureCoord.y)).rrr;
}
)";


namespace bow
{
	Application::Application(void) : m_width(800), m_height(600), m_frametime(0.0)
	{

	}


	Application::~Application(void)
	{

	}


	void Application::Init(unsigned int width, unsigned int height)
	{
		// Creating Render Device
		m_device = bow::RenderDeviceManager::GetInstance().GetOrCreateDevice(bow::RenderDeviceAPI::OpenGL3x);
		if (m_device == nullptr)
		{
			std::cout << "Could not create device!" << std::endl;
			return;
		}

		// Creating Window
		m_window = m_device->VCreateWindow(width, height, GetWindowTitle(), bow::WindowType::Windowed);
		if (m_window == nullptr)
		{
			std::cout << "Could not create window!" << std::endl;
			return;
		}

		///////////////////////////////////////////////////////////////////
		// Input

		m_keyboard = bow::InputDeviceManager::GetInstance().CreateKeyboardObject(m_window);
		if (m_keyboard == nullptr)
		{
			return;
		}

		m_mouse = bow::InputDeviceManager::GetInstance().CreateMouseObject(m_window);
		if (m_mouse == nullptr)
		{
			return;
		}
	}

	void Application::Run()
	{
		Init(m_width, m_height);

		auto contextOGL = m_window->VGetContext();

		///////////////////////////////////////////////////////////////////
		// compile shader

		bow::ShaderProgramPtr colorShaderProgram = m_device->VCreateShaderProgram(g_vertexColorShader, g_fragmentColorShader);
		bow::ShaderProgramPtr greyscaleShaderProgram = m_device->VCreateShaderProgram(g_vertexGreyscaleShader, g_fragmentGreyscaleShader);

		///////////////////////////////////////////////////////////////////
		// Vertex Array

		///////////////////////////////////////////////////////////////////
		// Define Triangle by Hand

		bow::MeshAttribute mesh;

		// Add Positions
		bow::VertexAttributeFloatVec3 *positionsAttribute = new bow::VertexAttributeFloatVec3("in_Position", 3);
		positionsAttribute->Values[0] = bow::Vector3<float>(-1.0f, -1.0f, 0.0f);
		positionsAttribute->Values[1] = bow::Vector3<float>(3.0f, -1.0f, 0.0f);
		positionsAttribute->Values[2] = bow::Vector3<float>(-1.0f, 3.0f, 0.0f);

		mesh.AddAttribute(bow::VertexAttributePtr(positionsAttribute));

		// Add TextureCoordinates
		bow::VertexAttributeFloatVec2 *texCoordAttribute = new bow::VertexAttributeFloatVec2("in_TexCoord", 3);
		texCoordAttribute->Values[0] = bow::Vector2<float>(0.0f, 0.0f);
		texCoordAttribute->Values[1] = bow::Vector2<float>(2.0f, 0.0f);
		texCoordAttribute->Values[2] = bow::Vector2<float>(0.0f, 2.0f);

		mesh.AddAttribute(bow::VertexAttributePtr(texCoordAttribute));

		bow::VertexArrayPtr vertexArray = contextOGL->VCreateVertexArray(mesh, colorShaderProgram->VGetVertexAttributes(), bow::BufferHint::StaticDraw);

		///////////////////////////////////////////////////////////////////
		// RenderState

		bow::RenderState renderState;
		renderState.faceCulling.Enabled = false;
		renderState.depthTest.Enabled = false;
		renderState.rasterizationMode = bow::RasterizationMode::Fill;

		// Change ClearColor
		bow::ClearState clearState;
		clearState.color = bow::ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f);

		///////////////////////////////////////////////////////////////////
		// Prepare render Texture

		m_colorTexture = m_device->VCreateTexture2D(bow::Texture2DDescription(m_width, m_height, bow::TextureFormat::RedGreenBlue8, false));
		bow::TextureSamplerPtr imageSampler = m_device->VCreateTexture2DSampler(bow::TextureMinificationFilter::Nearest, bow::TextureMagnificationFilter::Nearest, bow::TextureWrap::Clamp, bow::TextureWrap::Clamp);

		OnInit();

		bow::BasicTimer timer;
		while (!m_window->VShouldClose())
		{
			if (m_width != m_window->VGetWidth() || m_height != m_window->VGetHeight())
			{
				m_width = m_window->VGetWidth();
				m_height = m_window->VGetHeight();

				OnResized(m_width, m_height);
			}

			timer.Update();

			m_keyboard->VUpdate();
			m_mouse->VUpdate();

			OnUpdate(timer.GetDelta());

			OnRender();

			int TexID = 0;
			contextOGL->VSetTexture(TexID, m_colorTexture);
			contextOGL->VSetTextureSampler(TexID, imageSampler);

			// Clear Backbuffer to our ClearState
			contextOGL->VClear(clearState);
			contextOGL->VSetViewport(bow::Viewport(0, 0, m_width, m_height));

			colorShaderProgram->VSetUniform("inputTexture", TexID);
			contextOGL->VDraw(bow::PrimitiveType::Triangles, vertexArray, colorShaderProgram, renderState);

			contextOGL->GUI_NewFrame();

			contextOGL->GUI_Begin("fps");
			contextOGL->GUI_Text("fps: %7.2f", 1000.0 / m_frametime);
			contextOGL->GUI_Text("frametime: %7.2f ms", m_frametime);
			contextOGL->GUI_End();

			contextOGL->GUI_Render();

			contextOGL->VSwapBuffers(true);

			m_window->VPollWindowEvents();
		}

		OnRelease();
	}

	void Application::DisplayFramerate(double frametime)
	{
		m_frametime = frametime;
	}
}
