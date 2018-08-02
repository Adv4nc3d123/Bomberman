#include "MiniginPCH.h"
#include "HitBoxComponent.h"
#include "GameObject.h"

HitBoxComponent::HitBoxComponent()
	: m_Width(1.0f)
	, m_Height(1.0f)
{
	Initialize();
}


std::pair<float, float> HitBoxComponent::GetHitBox()
{
	return { m_Width, m_Height };
}

void HitBoxComponent::SetWidth(float width)
{
	m_Width = width;
}

void HitBoxComponent::SetHeight(float height)
{
	m_Height = height;
}

bool HitBoxComponent::IsOverLapping(const std::shared_ptr<HitBoxComponent>& hitbox)
{
	auto actorPos = m_GameObject.lock()->GetTransform().GetPosition() + m_Transform.GetPosition();
	auto pos = hitbox->m_GameObject.lock()->GetTransform().GetPosition() + m_Transform.GetPosition();

	auto totalWidth = (m_Width / 2.0f + hitbox->m_Width / 2.0);
	auto totalHeight = (m_Height / 2.0f + hitbox->m_Height / 2.0);


	if ((actorPos.x > pos.x - totalWidth && (actorPos.x < pos.x + totalWidth)) &&
		(actorPos.y > pos.y - totalHeight) && (actorPos.y < pos.y + totalHeight))
	{
		return true;
	}
	return false;
}

bool HitBoxComponent::IsInside(const std::shared_ptr<HitBoxComponent>& hitbox)
{
	auto halfwidth = (m_Width +2.0f) / 2.0f; //has to be a tiny bit bigger than the actual hitbox, otherwise when perfectly in between 2 tiles its not in any tile
	auto halfHeight = (m_Height +2.0f) / 2.0f;
	
	auto actorPos = m_GameObject.lock()->GetTransform().GetPosition() + m_Transform.GetPosition();
	auto pos = hitbox->m_GameObject.lock()->GetTransform().GetPosition() + m_Transform.GetPosition();

	if ((actorPos.x >= pos.x - halfwidth) && (actorPos.x <= pos.x + halfwidth) &&
		(actorPos.y >= pos.y - halfHeight) && (actorPos.y <= pos.y + halfHeight))
	{
		return true;
	}
	return false;

}
