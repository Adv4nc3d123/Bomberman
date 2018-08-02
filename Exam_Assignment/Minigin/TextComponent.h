#pragma once
#include "Component.h"
#include "ImageComponent.h"
#include "Font.h"


//namespace dae
//{
//	class Font;
//}


class TextComponent final : public ImageComponent
{
public:
	TextComponent(const std::string& text, std::shared_ptr<dae::Font> font, const SDL_Color& color);
	//void Initialize();
	void Update(const float deltaTime) override;
	void SetText(const std::string& text);
	

private:
	SDL_Color m_Color;
	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<dae::Font> m_Font;
};
