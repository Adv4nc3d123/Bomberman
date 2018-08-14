#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <SDL.h>

class ImageComponent : public Component
{
public:
	ImageComponent();
	virtual void Update(const float deltaTime) override;
	virtual void Render();
	void SetTexture(const std::string& fileName);
	void Clip(const SDL_Rect& rect);
protected:
	std::shared_ptr<dae::Texture2D> m_Texture;
	SDL_Rect m_Clip;
	bool m_IsClipped;
};
