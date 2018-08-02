#include "MiniginPCH.h"
#include "Transform.h"

void dae::Transform::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void dae::Transform::SetAngle(const float angle)
{
	m_Angle = angle;
}
