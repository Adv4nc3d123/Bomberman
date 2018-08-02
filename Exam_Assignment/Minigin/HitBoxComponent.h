#pragma once
#include "Component.h"

class HitBoxComponent : public Component
{
public:
	HitBoxComponent();
	std::pair<float,float> GetHitBox();
	void Render() override{};
	void SetWidth(float width);
	void SetHeight(float height);
	bool IsOverLapping(const std::shared_ptr<HitBoxComponent>& hitbox);
	bool IsInside(const std::shared_ptr<HitBoxComponent>& hitbox);
private:
	float m_Width;
	float m_Height;
};
