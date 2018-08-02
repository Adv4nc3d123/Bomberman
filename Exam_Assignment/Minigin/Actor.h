#pragma once
#include "GameObject.h"

enum class Direction
{
	Up,
	Down,
	Left,
	Right
};

class Actor : public GameObject
{
public:
	Actor() = default;
	void Update(const float deltaTime) override;
	void SetDirection(Direction direction);




protected:
	Direction m_Direction;
	Direction m_NewDirection;
	void HandleCollision();
	void UpdateSprites();
	glm::vec3 m_StartPos;
	glm::vec3 m_TurnPos;


};
