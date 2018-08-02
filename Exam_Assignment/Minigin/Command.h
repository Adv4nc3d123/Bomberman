#pragma once

class Actor;

class Command
{
public:
	explicit Command(const std::shared_ptr<Actor>& actor);
	virtual ~Command();
	virtual void Execute() = 0;
protected:
	std::shared_ptr<Actor> m_Actor;
};

