#include "MiniginPCH.h"
#include "TurnDownCommand.h"
#include "Actor.h"

TurnDownCommand::TurnDownCommand(const std::shared_ptr<Actor>& actor)
	:Command(actor)
{

}

void TurnDownCommand::Execute()
{
	m_Actor->SetDirection(Direction::Down);
}
