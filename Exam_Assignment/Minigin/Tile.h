#pragma once
#include "GameObject.h"

class HitBoxComponent;

enum class TileState
{
	Open,
	Wall,
	Dot,
	Boost
};

class Tile : public GameObject
{
public:
	Tile(TileState state, int index);
	void Initialize();
	void SetState(TileState state);
	TileState GetState() const;
	float GetSize();
	int GetIndex() const;
	bool IsOverLapping(const std::shared_ptr<HitBoxComponent>& hitbox);
private:
	void SetTexture();
	float m_Size;
	TileState m_State;
	int m_Index;
	std::string m_Textures[4];
};
