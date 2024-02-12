#pragma once
#include <RenderDevice/RenderDevice_api.h>
#include <RenderDevice/BowRenderDevicePredeclares.h>

namespace bow {

	enum class PixelBufferHint : char
	{
		Stream,
		Static,
		Dynamic
	};

}