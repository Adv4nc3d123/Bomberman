#pragma once
#include "Command.h"

class TurnLeftCommand : public Command
{
public:
	TurnLeftCommand(const std::shared_ptr<Actor>& actor);
	void Execute() override;
};
