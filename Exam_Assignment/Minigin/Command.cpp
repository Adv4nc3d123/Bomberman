#include "MiniginPCH.h"
#include "Command.h"
#include "Actor.h"

Command::Command(const std::shared_ptr<Actor>& actor)
	:m_Actor(actor)
{}

Command::~Command()
{}
