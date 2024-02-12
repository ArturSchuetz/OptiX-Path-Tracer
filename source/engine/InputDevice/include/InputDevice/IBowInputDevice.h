#pragma once
#include "InputDevice/InputDevice_api.h"
#include "InputDevice/BowInputPredeclares.h"

#include "RenderDevice/Device/BowGraphicsWindow.h"

namespace bow {

	//! \brief InputDevice creates the real objects inside of the dll.
	//! maybe I have to change this interface to support exotic input 
	//! devices with a dll for one specific device like the Oculus Rift,
	//! but at this moment I don't support any.
	class IInputDevice
	{
	public:
		IInputDevice() {}
		virtual ~IInputDevice(void) {}
		virtual void VRelease() = 0;

		virtual MousePtr VCreateMouseObject(GraphicsWindowPtr window) = 0;
		virtual KeyboardPtr VCreateKeyboardObject(GraphicsWindowPtr window) = 0;
	};
}