#pragma once
#include "Command.h"

class TurnDownCommand : public Command
{
public:
	TurnDownCommand(const std::shared_ptr<Actor>& actor);
	void Execute() override;

};
