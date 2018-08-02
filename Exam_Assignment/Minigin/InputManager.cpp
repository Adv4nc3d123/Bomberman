#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		for (auto &i : m_KeyMappings)
		{
			if (IsDown(i.first, e))
				i.second->Execute();
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}
	for (auto &i : m_ControllerMappings)
	{
		if (IsDown(i.first)) //check if controllerbutton is pressed
		{
			i.second->Execute(); //execute the command linked to that button
		}
	}


	return true;
}

bool dae::InputManager::IsDown(ControllerButton button) const //all controller button checks
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case ControllerButton::DpadDown:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case ControllerButton::DpadLeft:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case ControllerButton::DpadRight:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case ControllerButton::DpadUp:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case ControllerButton::LeftShoulder:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
	case ControllerButton::RightShoulder:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	case ControllerButton::LeftTrigger:
		return currentState.Gamepad.bLeftTrigger > 10; //255 means fully pressed and 0 is not pressed
	case ControllerButton::RightTrigger:
		return currentState.Gamepad.bRightTrigger > 10; //255 means fully pressed and 0 is not pressed
	case ControllerButton::Back:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
	case ControllerButton::Start:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_START;
	default:
		return false;
	}
}

bool dae::InputManager::IsDown(int key, const SDL_Event& e) const
{
	if (e.type == SDL_KEYDOWN)
		return e.key.keysym.sym == key;
	return false;
}

void dae::InputManager::SetCommand(ControllerButton button, Command* command)
{
	m_ControllerMappings[button] = std::unique_ptr<Command>(command);
}

void dae::InputManager::SetCommand(int key, Command* command)
{
	m_KeyMappings[key] = std::unique_ptr<Command>(command);
}