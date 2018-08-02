#include "MiniginPCH.h"
#include "TurnUpCommand.h"
#include "Actor.h"

TurnUpCommand::TurnUpCommand(const std::shared_ptr<Actor>& actor)
	:Command(actor)
{

}

void TurnUpCommand::Execute()
{
	m_Actor->SetDirection(Direction::Up);
}
