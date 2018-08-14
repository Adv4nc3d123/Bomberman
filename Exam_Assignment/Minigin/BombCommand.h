#pragma once
#include "Command.h"

class BombCommand : public Command
{
public:
public:
	BombCommand(const std::shared_ptr<Actor>& actor);
	void Execute() override;

};
