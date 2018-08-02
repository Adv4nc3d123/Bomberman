#include "MiniginPCH.h"
#include "Component.h"
#include "GameObject.h"

Component::Component()
{
	Initialize();
}

void Component::Initialize()
{
		m_Transform.SetPosition(0, 0);
		m_Transform.SetAngle(0);
}

void Component::Update(const float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void Component::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x,y);
	

}

void Component::SetAngle(const float angle)
{
	m_Transform.SetAngle(angle);
}

