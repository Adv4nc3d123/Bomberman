#include "MiniginPCH.h"
#include "Transform.h"

dae::Transform::Transform()
	:m_Position(0,0,0)
	, m_Size(1,1,1)
	, m_Angle(0)
{
}

void dae::Transform::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}


void dae::Transform::SetSize(const float x, const float y)
{
	m_Size.x = x;
	m_Size.y = y;
}

void dae::Transform::SetAngle(const float angle)
{
	m_Angle = angle;
}

