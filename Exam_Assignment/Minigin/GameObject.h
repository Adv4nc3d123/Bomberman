#pragma once
#include <memory>
#include "Transform.h"

class Component;
class TextComponent;
namespace dae
{
	class Scene;
}

class GameObject : public std::enable_shared_from_this<GameObject> //needed to pass this pointer to smart pointers
{

public:
	void UpDateMembers(const float deltaTime);
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	void AddComponent(const std::shared_ptr<Component>& pComponent);
	void AddChild(const std::shared_ptr<GameObject>& pChild);
	void SetPosition(float x, float y);
	void SetAngle(const float angle);
	dae::Transform GetTransform();
	std::vector<std::shared_ptr<GameObject>> GetChildren();
	std::shared_ptr<GameObject> GetChild(int index);
	template<class T>std::shared_ptr<T> GetComponent() ;
	GameObject();
	virtual ~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;
protected:
	dae::Transform m_Transform;
	std::vector<std::shared_ptr<Component>> m_ComponentVec;
	std::vector<std::shared_ptr<GameObject>> m_ChildVec;
	std::weak_ptr<GameObject> m_Parent;
	std::weak_ptr<dae::Scene> m_Scene; //if shared circular dependancy with scene
	bool OnOverlap(std::shared_ptr<GameObject> otherType);

private:

	friend class dae::Scene;
};

template <class T> inline
std::shared_ptr<T> GameObject::GetComponent()
{
	const type_info& typeInfo = typeid(T); 
	for (const auto& component : m_ComponentVec) 
	{
		if (typeid(*component) == typeInfo)
		{
			return std::static_pointer_cast<T>(component);
		}
	}
	return nullptr;
}
