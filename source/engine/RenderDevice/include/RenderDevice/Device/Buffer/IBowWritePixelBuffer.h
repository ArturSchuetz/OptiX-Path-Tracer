#pragma once
#include <RenderDevice/RenderDevice_api.h>
#include <RenderDevice/BowRenderDevicePredeclares.h>

namespace bow {

	class IWritePixelBuffer
	{
	public:
		virtual void VCopyFromSystemMemory(void* bufferInSystemMemory, int lengthInBytes)
		{
			VCopyFromSystemMemory(bufferInSystemMemory, 0, lengthInBytes);
		}

		virtual void VCopyFromSystemMemory(void* bufferInSystemMemory, int destinationOffsetInBytes, int lengthInBytes) = 0;

		virtual std::shared_ptr<void> VCopyToSystemMemory()
		{
			return VCopyToSystemMemory(0, VGetSizeInBytes());
		}

		virtual std::shared_ptr<void> VCopyToSystemMemory(int offsetInBytes, int sizeInBytes) = 0;

		virtual int				VGetSizeInBytes() const = 0;
		virtual PixelBufferHint	VGetUsageHint() const = 0;
	};

}
