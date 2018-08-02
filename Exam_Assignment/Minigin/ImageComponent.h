#pragma once
#include "Component.h"
#include "Texture2D.h"

class ImageComponent : public Component
{
public:
	ImageComponent();
	virtual void Update(const float deltaTime) override;
	virtual void Render();
	void SetTexture(const std::string& fileName);
protected:
	std::shared_ptr<dae::Texture2D> m_Texture;
};
