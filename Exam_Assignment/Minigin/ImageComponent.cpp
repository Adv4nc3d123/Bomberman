#include "MiniginPCH.h"
#include "ImageComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

ImageComponent::ImageComponent()
{
	Initialize();
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
		const auto angle = m_GameObject.lock()->GetTransform().GetAngle() + m_Transform.GetAngle();
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, angle);
	}
}

void ImageComponent::SetTexture(const std::string& fileName)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(fileName);
}
