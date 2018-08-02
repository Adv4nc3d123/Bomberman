#include "MiniginPCH.h"
#include "TurnRightCommand.h"
#include "Actor.h"

TurnRightCommand::TurnRightCommand(const std::shared_ptr<Actor>& actor)
	:Command(actor)
{

}

void TurnRightCommand::Execute()
{
	m_Actor->SetDirection(Direction::Right);
}
