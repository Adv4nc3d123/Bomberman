#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"

TextComponent::TextComponent(const std::string& text, std::shared_ptr<dae::Font> font, const SDL_Color& color)
	: ImageComponent{}
	, m_NeedsUpdate{ true }
	, m_Text{ text }
	, m_Font{ font }
	, m_Color{color}
{
	Initialize();
}
//void TextComponent::Initialize()
//{
//	m_Transform.SetPosition(0, 0);
//	m_Transform.SetAngle(0);
//}
//
void TextComponent::Update(const float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if(m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if(surf == nullptr)
		{
			std::stringstream ss; 
			ss << "Render Text failed: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if(texture == nullptr)
		{
			std::stringstream ss;
			ss << "Create text texture from surface failed: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<dae::Texture2D>(texture);
	}
}
//
//
void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}
//
