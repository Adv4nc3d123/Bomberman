#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : m_Name(name) {}

dae::Scene::~Scene() = default;


void dae::Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	object->m_Scene =  weak_from_this();
}

void dae::Scene::Update(const float deltaTime)
{
	for(auto gameObject : m_Objects)
	{
		gameObject->Update(deltaTime); //update this before the components because the components sometimes need calculations that happen inside here

		gameObject->UpDateMembers(deltaTime);	//2 different update functions, so if you override the update function, 
												//you don't have to call the parents class update function again to update components and children
	}
}

void dae::Scene::Render() const
{
	for (const auto gameObject : m_Objects)
	{
		gameObject->Render();
	}
}

std::vector<std::shared_ptr<GameObject>> dae::Scene::GetObjects() const
{
	return m_Objects;
}

