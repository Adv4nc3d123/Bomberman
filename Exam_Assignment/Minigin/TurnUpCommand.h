#pragma once
#include "Command.h"

class TurnUpCommand : public Command
{
public:
	TurnUpCommand(const std::shared_ptr<Actor>& actor);
	void Execute() override;

};
