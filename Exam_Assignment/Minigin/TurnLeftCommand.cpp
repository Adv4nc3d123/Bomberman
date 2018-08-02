#include "MiniginPCH.h"
#include "TurnLeftCommand.h"
#include "Actor.h"


TurnLeftCommand::TurnLeftCommand(const std::shared_ptr<Actor>& actor)
	:Command(actor)
{
}

void TurnLeftCommand::Execute()
{
	m_Actor->SetDirection(Direction::Left);
}
