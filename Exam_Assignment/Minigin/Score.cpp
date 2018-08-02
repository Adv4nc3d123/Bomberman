#include "MiniginPCH.h"
#include "Score.h"
#include "TextComponent.h"
#include "ResourceManager.h"


void Score::Initialize()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto tc = std::make_shared<TextComponent>("0", font, SDL_Color{ 255,0,0 });
	AddComponent(tc);
	SetPosition(0, 0);
	SetAngle(0);
}

void Score::IncreaseScore(int amount)
{
	m_Score += amount;
	GetComponent<TextComponent>()->SetText("Score: " + std::to_string(m_Score));
}

void Score::ResetScore()
{
	m_Score = 0;
	GetComponent<TextComponent>()->SetText("Score: " + std::to_string(m_Score));
}
