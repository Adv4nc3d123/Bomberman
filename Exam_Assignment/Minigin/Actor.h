#pragma once
#include "GameObject.h"
#include <SDL.h>
#include <map>


enum class Direction
{
	Up,
	Down,
	Left,
	Right
};

class Level;

class Actor : public GameObject
{
public:
	Actor() = default;
	void Initialize();
	void InitializeAnims();
	void Update(const float deltaTime);
	void SetDirection(Direction direction);
	void HandleDirection();
	void SetLevel(const std::shared_ptr<Level>& level);
	int GetBombPower();
	void ChangeDirection();
	void PlaceBomb();
protected:
	Direction m_Direction;
	Direction m_NewDirection;
	void HandleCollision(const glm::vec3& prevPos);
	glm::vec3 m_StartPos;
	glm::vec3 m_TurnPos;
	std::map<std::string, std::vector<SDL_Rect>> m_Anims;
	std::string m_Sprite;
	std::string m_Anim;
	int m_CurrentFrame;
	float m_FrameTime;
	float m_TextureHeight;
	std::shared_ptr<Level> m_Level;
	float m_Speed;
	float m_HorSpeed;
	float m_VerSpeed;
	int m_BombPower;
	int m_Index;
};
