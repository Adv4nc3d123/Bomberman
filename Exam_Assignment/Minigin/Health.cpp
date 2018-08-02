#include "MiniginPCH.h"
#include "Health.h."
#include "TextComponent.h"
#include "ResourceManager.h"


void Health::Initialize()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto tc = std::make_shared<TextComponent>("Health: 3", font, SDL_Color{ 255,0,0 });
	AddComponent(tc);
	SetPosition(0, 0);
	SetAngle(0);
	m_Health = 3;
}

void Health::DecreaseHealth(int amount)
{
	m_Health -= amount;
	GetComponent<TextComponent>()->SetText("Health: " + std::to_string(m_Health));
}

void Health::ResetHealth()
{
	m_Health = 3;
	GetComponent<TextComponent>()->SetText("Health: " + std::to_string(m_Health));
}
