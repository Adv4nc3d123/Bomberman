#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "SDL.h"

SpriteComponent::SpriteComponent()
	: ImageComponent{}
	, m_Play(true)
	, m_Repeat(true)
	, m_Finished(false)
	, m_Anim("None")
	, m_FrameTime(0.0f)
{
	Initialize();
}

void SpriteComponent::Update(const float deltaTime)
{
	if (!m_Finished)
	{
		if (m_Play)
		{
			m_FrameTime += deltaTime;

			if (m_FrameTime > 0.1f)
			{
				m_FrameTime = 0.0f;
				if (m_Repeat)
					m_CurrentFrame = (m_CurrentFrame + 1) % m_Anims[m_Anim].size();
				else if (m_CurrentFrame + 1 < m_Anims[m_Anim].size())
					++m_CurrentFrame;
				else
					m_Finished = true;
				Clip(m_Anims[m_Anim][m_CurrentFrame]);
			}
		}
		else
		{
			Clip(m_Anims[m_Anim][m_CurrentFrame]);
			m_Finished = true;
		}
	}
}

void SpriteComponent::AddAnim(const std::string& name, std::vector<SDL_Rect>& animVec)
{
	m_Anims[name] = animVec;
}

void SpriteComponent::SetAnim(const std::string& name, int animFrame)
{
	if (name != m_Anim || animFrame != m_CurrentFrame)
	{
		m_FrameTime = 9999.0f; //just a big value, so when the update start after you change your animation it changes the frame
		m_Anim = name;
		m_CurrentFrame = animFrame;
		m_Finished = false;
	}
}

void SpriteComponent::SetRepeat(bool repeat)
{
	m_Finished = false;
	m_Repeat = repeat;
}

void SpriteComponent::SetPlay(bool play)
{
	m_Play = play;
	m_Finished = false;
}

bool SpriteComponent::IsFinished()
{
	return m_Finished;
}
