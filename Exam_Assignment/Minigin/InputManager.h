#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include <SDL.h>
#include <map>

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		DpadDown,
		DpadRight,
		DpadUp,
		DpadLeft,
		RightShoulder,
		LeftShoulder,
		Start,
		Back,
		RightTrigger,
		LeftTrigger
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsDown(ControllerButton button) const;
		bool IsDown(int key, const SDL_Event&e) const;
		void SetCommand(ControllerButton button, Command* command);
		void SetCommand(int key, Command* command); //pass the int from the enum with all keys
	private:
		XINPUT_STATE currentState{};
		std::map<ControllerButton, std::unique_ptr<Command>> m_ControllerMappings;
		std::map<int, std::unique_ptr<Command>> m_KeyMappings; //int because all keys are members of an enum

	};

}
