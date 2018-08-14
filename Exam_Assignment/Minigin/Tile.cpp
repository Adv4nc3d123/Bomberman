#include "MiniginPCH.h"
#include "Tile.h"
#include "ImageComponent.h"
#include "HitBoxComponent.h"
#include "SDL.h"
#include "SpriteComponent.h"

Tile::Tile(TileState state, int index)
	: m_State(state)
	, m_Index(index)
	, m_Size(48.0f)
	, m_ExplosionState(ExplosionState::center)
{
}

void Tile::Initialize()
{

	auto sprite = std::make_shared<SpriteComponent>(); //TODO: try to make this more optimal so I don't need to remake the same huge spritecomponent for each tile
	sprite->SetTexture("Sprites/Tiles.png");
	AddComponent(sprite);
	//SetTexture();

	SDL_Rect clip;
	clip.w = 16;
	clip.h = 16;
	clip.x = 328;
	clip.y = 461;

	std::vector<SDL_Rect> animVec;
	animVec.push_back(clip);
	sprite->AddAnim("Open", animVec);
	animVec.clear();

	clip.x = 294;
	animVec.push_back(clip);
	sprite->AddAnim("Wall", animVec);
	animVec.clear();

	clip.x = 311;
	animVec.push_back(clip);
	sprite->AddAnim("Breakable", animVec);
	animVec.clear();

	clip.x = 277;
	clip.y = 563;
	animVec.push_back(clip);
	clip.x = 294;
	animVec.push_back(clip);
	clip.x = 311;
	animVec.push_back(clip);
	clip.x = 328;
	animVec.push_back(clip);
	clip.x = 345;
	animVec.push_back(clip);
	clip.x = 362;
	animVec.push_back(clip);
	sprite->AddAnim("Breaking", animVec);
	animVec.clear();



	clip.x = 379;
	clip.y = 563;
	animVec.push_back(clip);
	clip.x = 396;
	animVec.push_back(clip);
	clip.x = 413;
	animVec.push_back(clip);
	clip.x = 396;
	animVec.push_back(clip);
	sprite->AddAnim("Bomb", animVec);
	animVec.clear();

	clip.x = 277;
	clip.y = 495;
	animVec.push_back(clip);
	clip.x = 294;
	animVec.push_back(clip);
	clip.x = 311;
	animVec.push_back(clip);
	clip.x = 294;
	animVec.push_back(clip);
	sprite->AddAnim("SuperBomb", animVec);
	animVec.clear();

	clip.x = 345;
	clip.y = 512;
	animVec.push_back(clip);
	clip.x = 362;
	animVec.push_back(clip);
	clip.x = 379;
	animVec.push_back(clip);
	clip.x = 396;
	animVec.push_back(clip);
	clip.x = 345;
	clip.y = 529;
	animVec.push_back(clip);
	sprite->AddAnim("ExplodeCenter", animVec);
	animVec.clear();

	clip.x = 345;
	clip.y = 478;
	animVec.push_back(clip);
	clip.x = 328;
	animVec.push_back(clip);
	clip.x = 311;
	animVec.push_back(clip);
	clip.x = 294;
	animVec.push_back(clip);
	clip.x = 277;
	animVec.push_back(clip);
	sprite->AddAnim("ExplodeLeft", animVec);
	animVec.clear();

	clip.x = 294;
	clip.y = 512;
	animVec.push_back(clip);
	clip.y = 529;
	animVec.push_back(clip);
	clip.y = 546;
	animVec.push_back(clip);
	clip.x = 328;
	clip.y = 512;
	animVec.push_back(clip);
	clip.y = 529;
	animVec.push_back(clip);
	sprite->AddAnim("ExplodeRight", animVec);
	animVec.clear();

	clip.x = 396;
	clip.y = 478;
	animVec.push_back(clip);
	clip.y = 495;
	animVec.push_back(clip);
	clip.x = 379;
	animVec.push_back(clip);
	clip.x = 362;
	animVec.push_back(clip);
	clip.x = 345;
	animVec.push_back(clip);
	sprite->AddAnim("ExplodeUp", animVec);
	animVec.clear();

	clip.x = 362;
	clip.y = 546;
	animVec.push_back(clip);
	clip.x = 379;
	animVec.push_back(clip);
	clip.x = 396;
	animVec.push_back(clip);
	clip.x = 345;
	animVec.push_back(clip);
	clip.x = 328;
	clip.y = 495;
	animVec.push_back(clip);
	sprite->AddAnim("ExplodeDown", animVec);
	animVec.clear();

	clip.x = 277;
	clip.y = 512;
	animVec.push_back(clip);
	clip.y = 529;
	animVec.push_back(clip);
	clip.y = 546;
	animVec.push_back(clip);
	clip.x = 311;
	clip.y = 512;
	animVec.push_back(clip);
	clip.y = 529;
	animVec.push_back(clip);
	sprite->AddAnim("ExplodeHor", animVec);
	animVec.clear();

	clip.x = 362;
	clip.y = 529;
	animVec.push_back(clip);
	clip.x = 379;
	animVec.push_back(clip);
	clip.x = 396;
	animVec.push_back(clip);
	clip.x = 311;
	clip.y = 546;
	animVec.push_back(clip);
	clip.x = 328;
	animVec.push_back(clip);
	sprite->AddAnim("ExplodeVer", animVec);
	animVec.clear();

	clip.x = 277;
	clip.y = 580;
	animVec.push_back(clip);
	clip.x = 294;
	animVec.push_back(clip);
	clip.x = 311;
	animVec.push_back(clip);
	clip.x = 328;
	animVec.push_back(clip);
	clip.x = 345;
	animVec.push_back(clip);
	clip.x = 362;
	animVec.push_back(clip);
	clip.x = 379;
	animVec.push_back(clip);
	sprite->AddAnim("ExplodeItem", animVec);
	animVec.clear();

	clip.x = 933;
	clip.y = 448;
	animVec.push_back(clip);
	sprite->AddAnim("FireUp", animVec);
	animVec.clear();

	clip.x = 967;
	animVec.push_back(clip);
	sprite->AddAnim("BombUp", animVec);
	animVec.clear();

	clip.x = 984;
	animVec.push_back(clip);
	sprite->AddAnim("SkateUp", animVec);
	animVec.clear();

	clip.x = 967;
	clip.y = 465;
	animVec.push_back(clip);
	sprite->AddAnim("BoxingGloves", animVec);
	animVec.clear();

	clip.x = 933;
	clip.y = 499;
	animVec.push_back(clip);
	sprite->AddAnim("Death", animVec);
	animVec.clear();
	sprite->SetPlay(true);
	m_Transform.SetSize(3.0f, 3.0f);

	auto hitbox = std::make_shared<HitBoxComponent>();
	hitbox->SetHeight(16.0f*3);
	hitbox->SetWidth(16.0f*3);
	AddComponent(hitbox);

	UpdateState();
}

void Tile::Update(const float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void Tile::SetState(TileState state)
{
	m_State = state;
	UpdateState();
}

void Tile::SetExplosionState(ExplosionState state)
{
	m_ExplosionState = state;
	UpdateState();
}

void Tile::UpdateState() //putting updatestate inside update either makes the sprites not update becuase of setting anim all the time, or it wont override current explosions
{
	auto sprite = GetComponent<SpriteComponent>();
	switch (m_State) //exploding is a function in the level because tiles around the tile need to be known to set the texture
	{
	case TileState::Open:
		sprite->SetAnim("Open");
		sprite->SetRepeat(true);
		break;
	case TileState::Wall:
		sprite->SetAnim("Wall");
		break;
	case TileState::Breakable:
		sprite->SetAnim("Breakable");
		break;
	case TileState::Bomb:
		sprite->SetAnim("Bomb");
		sprite->SetRepeat(true);
		break;
	case TileState::SuperBomb:
		sprite->SetAnim("SuperBomb");
		break;
	case TileState::Explosion:
		sprite->SetRepeat(false);
		switch (m_ExplosionState)
		{
		case ExplosionState::center:
			sprite->SetAnim("ExplodeCenter");
			break;
		case ExplosionState::ver:
			sprite->SetAnim("ExplodeVer");
			break;
		case ExplosionState::hor:
			sprite->SetAnim("ExplodeHor");
			break;
		case ExplosionState::bottom:
			sprite->SetAnim("ExplodeDown");
			break;
		case ExplosionState::left:
			sprite->SetAnim("ExplodeLeft");
			break;
		case ExplosionState::right:
			sprite->SetAnim("ExplodeRight");
			break;
		case ExplosionState::top:
			sprite->SetAnim("ExplodeUp");
			break;
		}
		break;
	case TileState::Breaking:
		sprite->SetAnim("Breaking");
		sprite->SetRepeat(false);
		break;

	case TileState::Exit:

		break;

	}
	m_PrevTileState = m_State;

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

bool Tile::IsFinished()
{
	auto sprite = GetComponent<SpriteComponent>();
	return sprite->IsFinished();
}


void Tile::SetTexture()
{
	//switch (m_State)
	//{
	//case TileState::Boost:
	//	GetComponent<ImageComponent>()->SetTexture(m_Textures[0]);
	//	break;
	//case TileState::Open:
	//	GetComponent<ImageComponent>()->SetTexture(m_Textures[1]);
	//	break;
	//case TileState::Wall:
	//	GetComponent<ImageComponent>()->SetTexture(m_Textures[2]);
	//	break;
	//case TileState::Dot:
	//	GetComponent<ImageComponent>()->SetTexture(m_Textures[3]);
	//	break;
	//}

}
