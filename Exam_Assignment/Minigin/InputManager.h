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
		void SetCommand(int key, Command* command); //pass the int from the enum with all keys
		void SetCommand(ControllerButton button, Command* command);
		//if you hold these buttons the cmd will repeat
		void SetHoldCommand(ControllerButton button, Command* command);
		void SetHoldCommand(int key, Command* command);
	private:
		XINPUT_STATE currentState{};
		std::map<ControllerButton, std::unique_ptr<Command>> m_ControllerMappings;
		std::map<int, std::unique_ptr<Command>> m_KeyMappings; //int because all keys are members of an enum
		std::map<ControllerButton, std::unique_ptr<Command>> m_HoldControllerMappings;
		std::map<int, std::unique_ptr<Command>> m_HoldKeyMappings;

		std::map<ControllerButton, bool> m_PrevButtonState;
		std::map<ControllerButton, bool> m_ButtonState;
	};

}
