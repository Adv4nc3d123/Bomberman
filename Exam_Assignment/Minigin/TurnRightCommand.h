#pragma once
#include "Command.h"

class TurnRightCommand : public Command
{
public:
	TurnRightCommand(const std::shared_ptr<Actor>& actor);
	void Execute() override;

};
