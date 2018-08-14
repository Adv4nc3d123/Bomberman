#pragma once
#include "GameObject.h"
#include <map>

class HitBoxComponent;
struct SDL_Rect;

enum class TileState
{
	//normal states
	Open,
	Wall,
	Breakable,
	Bomb,
	SuperBomb,
	Exit,
	Explosion,
	Breaking,

	//pickups
	FireUp,
	BombUp,
	SkateUp,
	PierceBomb,
	BoxingGloves,
	Detonator,
	Death
};

enum class ExplosionState
{
	center,
	hor,
	ver,
	top,
	bottom,
	left,
	right
};

class Tile : public GameObject
{
public:
	Tile(TileState state, int index);
	void Initialize();
	virtual void Update(const float deltaTime) override;
	void SetState(TileState state);
	void SetExplosionState(ExplosionState state);
	TileState GetState() const;
	float GetSize();
	int GetIndex() const;
	bool IsOverLapping(const std::shared_ptr<HitBoxComponent>& hitbox);
	bool IsFinished();
private: 
	void UpdateState();
	void SetTexture();
	float m_Size;
	TileState m_State;
	int m_Index;
	TileState m_PrevTileState;
	ExplosionState m_ExplosionState;
	//std::map<std::string, std::vector<SDL_Rect>> m_Anims;

};
