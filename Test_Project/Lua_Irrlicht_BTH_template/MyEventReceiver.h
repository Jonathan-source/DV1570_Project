#pragma once
#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;
class MyEventReceiver : public IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
			KeyIsDown[event.MouseInput.Event] = event.MouseInput.Event;


		return false;
	}

	// This is used to check whether a key is being held down
	bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	MyEventReceiver()
	{
		for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};