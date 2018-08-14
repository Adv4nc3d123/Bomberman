#include "MiniginPCH.h"
#include "BombCommand.h"
#include "Actor.h"

BombCommand::BombCommand(const std::shared_ptr<Actor>& actor)
	:Command(actor)
{

}

void BombCommand::Execute()
{
	m_Actor->PlaceBomb();
}
