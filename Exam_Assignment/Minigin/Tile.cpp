#include "MiniginPCH.h"
#include "Tile.h"
#include "ImageComponent.h"
#include "HitBoxComponent.h"

Tile::Tile(TileState state, int index)
	: m_State(state)
	, m_Index(index)
	, m_Size(32.0f)

{
}

void Tile::Initialize()
{
	m_Textures[0] = "Boost.png";
	m_Textures[1] = "Open.png";
	m_Textures[2] = "Wall.png";
	m_Textures[3] = "Dot.png";
	std::string tex{};

	auto texture = std::make_shared<ImageComponent>();
	
	AddComponent(texture);
	SetTexture();

	auto hitbox = std::make_shared<HitBoxComponent>();
	hitbox->SetHeight(30.0f);
	hitbox->SetWidth(30.0f);
	AddComponent(hitbox);


}

void Tile::SetState(TileState state)
{
	m_State = state;
	SetTexture();
}

TileState Tile::GetState() const
{
	return m_State;
}

float Tile::GetSize()
{
	return m_Size;
}

int Tile::GetIndex() const
{
	return m_Index;
}


bool Tile::IsOverLapping(const std::shared_ptr<HitBoxComponent>& hitbox)
{
	if(GetComponent<HitBoxComponent>()->IsOverLapping(hitbox))
	{
		return true;
	}
	return false;
}


void Tile::SetTexture()
{
	switch (m_State)
	{
	case TileState::Boost:
		GetComponent<ImageComponent>()->SetTexture(m_Textures[0]);
		break;
	case TileState::Open:
		GetComponent<ImageComponent>()->SetTexture(m_Textures[1]);
		break;
	case TileState::Wall:
		GetComponent<ImageComponent>()->SetTexture(m_Textures[2]);
		break;
	case TileState::Dot:
		GetComponent<ImageComponent>()->SetTexture(m_Textures[3]);
		break;
	}

}
