#include "MiniginPCH.h"
#include "ImageComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

ImageComponent::ImageComponent()
	: m_IsClipped(false)
	, m_Clip()
	, m_Texture(nullptr)
{
	Initialize();
	m_Clip.h = 0;
	m_Clip.w = 0;
	m_Clip.x = 0;
	m_Clip.y = 0;
}

void ImageComponent::Update(const float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void ImageComponent::Render()
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_Transform.GetPosition() + m_GameObject.lock()->GetTransform().GetPosition();
		glm::vec3 size;
		if (m_Transform.GetSize() == glm::vec3(1, 1, 1)) //if componentsize isnt set, use the actor size
			size = m_GameObject.lock()->GetTransform().GetSize();
		else
			size = m_Transform.GetSize();

		const auto angle = m_GameObject.lock()->GetTransform().GetAngle() + m_Transform.GetAngle();
		if (!m_IsClipped)
			dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, angle);
		else
			dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, (float)m_Clip.w * size.x, (float)m_Clip.h * size.y, m_Clip, angle);
	}
}

void ImageComponent::SetTexture(const std::string& fileName)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(fileName);
}

void ImageComponent::Clip(const SDL_Rect& rect)
{
	m_IsClipped = true;
	m_Clip = rect;
}
