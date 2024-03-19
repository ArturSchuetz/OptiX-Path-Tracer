#pragma once
#include "CameraUtils/CameraUtils_api.h"

#include "CoreSystems/BowCoreSystems.h"
#include "InputDevice/BowInput.h"
#include "RenderDevice/BowRenderer.h"

namespace bow {

	class CAMERAUTILS_API Application
	{
	public:
		Application(void);
		virtual ~Application(void);

		void Run();


	protected:
		virtual std::string GetWindowTitle(void) { return "Application"; }
		virtual void OnInit() {}

		virtual void OnResized(int newWidth, int newHeight) {
			(void)newWidth;
			(void)newHeight;
		}

		virtual void OnUpdate(double deltaTime)
		{
			(void)deltaTime;
		}

		virtual void OnRender(void) {}
		virtual void OnRelease(void) {}

		unsigned int GetWidth() { return m_width; }
		unsigned int GetHeight() { return m_height; }
		void DisplayFramerate(double framerate);

		RenderDevicePtr		m_device;
		GraphicsWindowPtr	m_window;
		KeyboardPtr			m_keyboard;
		MousePtr			m_mouse;

	private:
		void Init(unsigned int width, unsigned int height);

		int				m_width;
		int				m_height;

		BasicTimer		m_timer;
		Texture2DPtr	m_colorTexture;
		Texture2DPtr	m_irTexture;
		Texture2DPtr	m_depthTexture;

		double			m_frametime;
	};
}
