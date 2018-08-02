#pragma once
#include "Transform.h"

class GameObject;

class Component
{
public:
	Component();
	virtual void Render() = 0;
	virtual void Initialize();
	virtual void Update(const float deltaTime);
	virtual void SetPosition(const float x, const float y);
	virtual void SetAngle(const float angle);
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

protected:
	dae::Transform m_Transform;
	std::weak_ptr<GameObject> m_GameObject; //if shared circular dependancy with gameobject
private:
	friend class GameObject;


};
