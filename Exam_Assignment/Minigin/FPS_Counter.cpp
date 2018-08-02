#include "MiniginPCH.h"
#include "FPS_Counter.h"
#include <SDL.h>
#include "ResourceManager.h"
#include "TextComponent.h"


void FPS_Counter::Initialize()
{
	m_FpsTimer = 0.0f;
	m_FpsCount = 0 ;
	m_FPS = 0.0f;
	m_ShowFps = true;
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto tc = std::make_shared<TextComponent>("0", font, SDL_Color{ 255,255,255 });
	AddComponent(tc);
	SetPosition(50, 180);
	SetAngle(0);
}


void FPS_Counter::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);
	m_FpsTimer += deltaTime;
	++m_FpsCount;
	if (m_FpsTimer >= 1.0f)
	{
		m_FPS = (float)m_FpsCount;
		m_FpsCount = 0;
		m_FpsTimer -= 1.0f;
	}
	GetComponent<TextComponent>()->SetText(std::to_string((int)std::round(m_FPS)));
}

void FPS_Counter::Render() const
{
	if(m_ShowFps)
	{
		GameObject::Render();
	}
}

int FPS_Counter::GetFPS()
{
	return (int)m_FPS;
}

void FPS_Counter::EnableRender(bool showfps)
{
	m_ShowFps = showfps;
}
