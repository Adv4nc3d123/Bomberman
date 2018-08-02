#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include <typeinfo>
#include "GameObject.h"
#include <SDL.h>
#include "HitBoxComponent.h"
#include "Scene.h"


GameObject::GameObject()
{
	m_Transform.SetPosition(0, 0);
	m_Transform.SetAngle(0);
}


bool GameObject::OnOverlap(std::shared_ptr<GameObject> otherType)  //terrible and slow function TODO: fix if time left
{
	auto hitbox = GetComponent<HitBoxComponent>();
	auto goVec = m_Scene.lock()->GetObjects();
	for(const auto& go : goVec)
	{
		if(typeid(*go) == typeid(*otherType))
		{
			auto hitbox2 = go->GetComponent<HitBoxComponent>();
			if(hitbox->IsOverLapping(hitbox2))
			{
				return true;
			}
		}
	}
	return false;
}


GameObject::~GameObject() = default;

void GameObject::Update(const float deltaTime)
{
	for (auto component : m_ComponentVec)
	{
		component->Update(deltaTime);
	}
	for(auto child : m_ChildVec)
	{
		child->Update(deltaTime);
	}
}

void GameObject::Render() const
{
	for(auto component: m_ComponentVec)
	{
		component->Render();
	}
	for (auto child : m_ChildVec)
	{
		child->Render();
	}

}

void GameObject::AddComponent(const std::shared_ptr<Component>& pComponent)
{
	m_ComponentVec.push_back(pComponent);
	pComponent->m_GameObject = weak_from_this();
}

void GameObject::AddChild(const std::shared_ptr<GameObject>& pChild)
{
	m_ChildVec.push_back(pChild);
	pChild->m_Parent = weak_from_this();
}


void GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y);
}

void GameObject::SetAngle(const float angle)
{

	m_Transform.SetAngle(angle);
}

dae::Transform GameObject::GetTransform()
{
	if (this != nullptr)
		return m_Transform;
	else
	{
		throw std::runtime_error(std::string("getting transform of uninitialized gameObject") + SDL_GetError());
		//return dae::Transform();
	}
}

std::vector<std::shared_ptr<GameObject>> GameObject::GetChildren()
{
	return m_ChildVec;
}

std::shared_ptr<GameObject> GameObject::GetChild(int index)
{
	return m_ChildVec[index];
}



