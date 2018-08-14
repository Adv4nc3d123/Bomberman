#include "MiniginPCH.h"
#include "Actor.h"
#include "HitBoxComponent.h"
#include "ImageComponent.h"
#include "Level.h"
#include "SpriteComponent.h"
#include "Tile.h"

void Actor::Initialize()
{
	m_TextureHeight = 25.0f;
	m_Anim = "WalkLeft";
	m_Speed = 150;
	m_BombPower = 2;
	m_Index = 0;

	//SpriteSheet
	m_Sprite = "Sprites/Bomberman.png";
	//auto texture = std::make_shared<ImageComponent>();
	//texture->SetTexture(m_Sprite);
	//SetPosition(m_StartPos.x, m_StartPos.y);

	auto sprite = std::make_shared<SpriteComponent>();
	sprite->SetTexture(m_Sprite);
	SetPosition(m_StartPos.x, m_StartPos.y);
	sprite->SetPosition(0, -m_TextureHeight);
	AddComponent(sprite);
	sprite->SetPlay(true);
	sprite->SetRepeat(true);
	auto hitbox = std::make_shared<HitBoxComponent>();
	hitbox->SetWidth(16*3);
	hitbox->SetHeight(16*3);
	AddComponent(hitbox);


	InitializeAnims(); //call after adding spritecomponent to work

	m_Transform.SetSize(3.0f, 3.0f);


	sprite->SetAnim("WalkUp");
	//texture->Clip(clipRect);


}

void Actor::InitializeAnims()
{
	//for walking animations, push back the neutral frame twice
	auto sprite = GetComponent<SpriteComponent>();
	SDL_Rect clipRect;
	std::vector<SDL_Rect> animVector;

	clipRect.y = 44;
	clipRect.h = (int)m_TextureHeight;
	clipRect.x = 3;
	clipRect.w = 16;
	animVector.push_back(clipRect);

	clipRect.x = 19;
	animVector.push_back(clipRect);

	clipRect.x = 3;
	animVector.push_back(clipRect);

	clipRect.x = 36;
	animVector.push_back(clipRect);

	sprite->AddAnim("WalkLeft", animVector);
	//m_Anims["WalkLeft"] = animVector;
	animVector.clear();

	clipRect.y = 46;
	clipRect.x = 56;
	animVector.push_back(clipRect);

	clipRect.x = 72;
	animVector.push_back(clipRect);

	clipRect.x = 88;
	animVector.push_back(clipRect);

	clipRect.x = 72;
	animVector.push_back(clipRect);

	sprite->AddAnim("WalkDown", animVector);
	//m_Anims["WalkDown"] = animVector;
	animVector.clear();

	clipRect.y = 21;
	clipRect.x = 57;
	animVector.push_back(clipRect);

	clipRect.x = 73;
	animVector.push_back(clipRect);

	clipRect.x = 89;
	animVector.push_back(clipRect);

	clipRect.x = 73;
	animVector.push_back(clipRect);

	sprite->AddAnim("WalkUp", animVector);
	//m_Anims["WalkUp"] = animVector;
	animVector.clear();

	clipRect.y = 47;
	clipRect.x = 106;
	animVector.push_back(clipRect);

	clipRect.x = 122;
	animVector.push_back(clipRect);

	clipRect.x = 106;
	animVector.push_back(clipRect);

	clipRect.x = 138;
	animVector.push_back(clipRect);

	sprite->AddAnim("WalkRight", animVector);
	//m_Anims["WalkRight"] = animVector;
	animVector.clear();


	clipRect.y = 75;
	clipRect.x = 30;
	animVector.push_back(clipRect);

	clipRect.x = 49;
	animVector.push_back(clipRect);

	clipRect.x = 66;
	animVector.push_back(clipRect);

	clipRect.x = 83;
	animVector.push_back(clipRect);

	clipRect.x = 100;
	animVector.push_back(clipRect);

	clipRect.x = 118;
	animVector.push_back(clipRect);

	sprite->AddAnim("Die", animVector);
	//m_Anims["Die"] = animVector;
	animVector.clear();
	m_Transform.SetPosition(48, 48);
	//GetComponent<SpriteComponent>()->SetAnim("WalkLeft");

}

void Actor::Update(const float deltaTime)
{
	//HandleDirection();
	//ChangeDirection();








	if(m_HorSpeed == 0 && m_VerSpeed == 0)
		GetComponent<SpriteComponent>()->SetPlay(false);
	auto pos = m_Transform.GetPosition();
	auto xPos = float(pos.x + m_HorSpeed * deltaTime);
	auto yPos = float(pos.y + m_VerSpeed * deltaTime);
	SetPosition(xPos, yPos);
	HandleCollision(pos); //called after setting the position to snap back if in impossible boundaries

	//reset speed so you don't keep running when the button isn't pressed
	m_HorSpeed = 0.0f;
	m_VerSpeed = 0.0f;
}

void Actor::SetDirection(Direction direction)
{
	GetComponent<SpriteComponent>()->SetPlay(true);
	if (m_Direction != direction)
	{
		std::cout << "Changed Direction\n";
		m_Direction = direction;
		auto sprite = GetComponent<SpriteComponent>();
		switch (m_Direction)
		{
		case Direction::Up:
			sprite->SetAnim("WalkUp");
			break;
		case Direction::Down:
			sprite->SetAnim("WalkDown");
			break;
		case Direction::Left:
			sprite->SetAnim("WalkLeft");
			break;
		case Direction::Right:
			sprite->SetAnim("WalkRight");
			break;
		}

	}
	else
	{
		std::cout << "command used\n";
		switch (m_Direction)
		{
		case Direction::Up:
			m_HorSpeed = 0.0f;
			m_VerSpeed = -m_Speed;
			break;
		case Direction::Down:
			m_HorSpeed = 0.0f;
			m_VerSpeed = m_Speed;
			break;
		case Direction::Left:
			m_HorSpeed = -m_Speed;
			m_VerSpeed = 0.0f;
			break;
		case Direction::Right:
			m_HorSpeed = m_Speed;
			m_VerSpeed = 0.0f;
			break;
		}
	}

}

void Actor::HandleDirection()
{
	if(m_NewDirection != m_Direction)
	{
		switch(m_NewDirection)
		{
		case Direction::Down:

			break;
		case Direction::Left:

			break;
		case Direction::Right:

			break;
		case Direction::Up:

			break;

		}
	}
}

void Actor::HandleCollision(const glm::vec3& prevPos)
{
	UNREFERENCED_PARAMETER(prevPos);
	auto hitbox = GetComponent<HitBoxComponent>();
	auto indexPos = m_Level->GetActiveTileIndex(shared_from_this());
	auto onTile = m_Level->GetTile(indexPos);
	int nearIndex;
	std::shared_ptr<Tile> nearTile;
	float pushSpeed = 2.0f;
	switch (m_Direction)
	{
	case Direction::Right:
		nearIndex = m_Level->GetRightIndex(indexPos);
		nearTile = m_Level->GetTile(nearIndex);
		if((nearTile->GetState() == TileState::Wall || nearTile->GetState() == TileState::Breakable) && nearTile->IsOverLapping(GetComponent<HitBoxComponent>()))
		{
			SetPosition(onTile->GetTransform().GetPosition().x, m_Transform.GetPosition().y);
		}
			break;
	case Direction::Left:
		nearIndex = m_Level->GetLeftIndex(indexPos);
		nearTile = m_Level->GetTile(nearIndex);
		if ((nearTile->GetState() == TileState::Wall || nearTile->GetState() == TileState::Breakable) && nearTile->IsOverLapping(GetComponent<HitBoxComponent>()))
		{
			m_Transform.SetPosition(onTile->GetTransform().GetPosition().x, m_Transform.GetPosition().y);
		}
		break;
	case Direction::Up:
		nearIndex = m_Level->GetUpperIndex(indexPos);
		nearTile = m_Level->GetTile(nearIndex);
		if ((nearTile->GetState() == TileState::Wall || nearTile->GetState() == TileState::Breakable) && nearTile->IsOverLapping(GetComponent<HitBoxComponent>()))
		{
			m_Transform.SetPosition(m_Transform.GetPosition().x, onTile->GetTransform().GetPosition().y);
		}
		break;
	case Direction::Down:
		nearIndex = m_Level->GetBottomIndex(indexPos);
		nearTile = m_Level->GetTile(nearIndex);
		if ((nearTile->GetState() == TileState::Wall || nearTile->GetState() == TileState::Breakable) && nearTile->IsOverLapping(GetComponent<HitBoxComponent>()))
		{
			m_Transform.SetPosition(m_Transform.GetPosition().x, onTile->GetTransform().GetPosition().y);
		}
		break;

	}
	bool pushed = false;
	float range = 1.5f;
	nearIndex = m_Level->GetBottomIndex(indexPos);
	nearTile = m_Level->GetTile(nearIndex);
	if ((nearTile->GetState() == TileState::Wall || nearTile->GetState() == TileState::Breakable) && nearTile->IsOverLapping(GetComponent<HitBoxComponent>()))
	{
		pushed = true;
		SetPosition(m_Transform.GetPosition().x, m_Transform.GetPosition().y - pushSpeed);
		if ((m_Transform.GetPosition().y - onTile->GetTransform().GetPosition().y > -range) && (m_Transform.GetPosition().y - onTile->GetTransform().GetPosition().y < range))
			SetPosition(m_Transform.GetPosition().x, onTile->GetTransform().GetPosition().y);
	}
	nearIndex = m_Level->GetLeftIndex(indexPos);
	nearTile = m_Level->GetTile(nearIndex);
	if ((nearTile->GetState() == TileState::Wall || nearTile->GetState() == TileState::Breakable) && nearTile->IsOverLapping(GetComponent<HitBoxComponent>()))
	{
		pushed = true;
		SetPosition(m_Transform.GetPosition().x + pushSpeed, m_Transform.GetPosition().y);
		if ((m_Transform.GetPosition().x - onTile->GetTransform().GetPosition().x > -range) && (m_Transform.GetPosition().x - onTile->GetTransform().GetPosition().x < range))
			SetPosition(onTile->GetTransform().GetPosition().x, m_Transform.GetPosition().y);
	}
	nearIndex = m_Level->GetRightIndex(indexPos);
	nearTile = m_Level->GetTile(nearIndex);
	if ((nearTile->GetState() == TileState::Wall || nearTile->GetState() == TileState::Breakable) && nearTile->IsOverLapping(GetComponent<HitBoxComponent>()))
	{
		pushed = true;
		SetPosition(m_Transform.GetPosition().x - pushSpeed, m_Transform.GetPosition().y);
	}
	nearIndex = m_Level->GetUpperIndex(indexPos);
	nearTile = m_Level->GetTile(nearIndex);
	if ((nearTile->GetState() == TileState::Wall || nearTile->GetState() == TileState::Breakable) && nearTile->IsOverLapping(GetComponent<HitBoxComponent>()))
	{
		pushed = true;
		SetPosition(m_Transform.GetPosition().x, m_Transform.GetPosition().y + pushSpeed);
	}



	//std::cout << "X: " << m_Transform.GetPosition().x << '\t' << "Y: " << m_Transform.GetPosition().y << '\n';
}

void Actor::SetLevel(const std::shared_ptr<Level>& level)
{
	m_Level = level;
}

int Actor::GetBombPower()
{
	return m_BombPower;
}

void Actor::ChangeDirection()
{
	auto sprite = GetComponent<SpriteComponent>();
	//if (m_Direction != m_NewDirection)
	{
		m_Direction = m_NewDirection;
		switch (m_Direction)
		{
		case Direction::Up:
			sprite->SetAnim("WalkUp");
			m_HorSpeed = 0.0f;
			m_VerSpeed = -m_Speed;
			break;
		case Direction::Down:
			sprite->SetAnim("WalkDown");
			m_HorSpeed = 0.0f;
			m_VerSpeed = m_Speed;
			break;
		case Direction::Left:
			sprite->SetAnim("WalkLeft");
			m_HorSpeed = -m_Speed;
			m_VerSpeed = 0.0f;
			break;
		case Direction::Right:
			sprite->SetAnim("WalkRight");
			m_HorSpeed = m_Speed;
			m_VerSpeed = 0.0f;
			break;
		}
	}
}

void Actor::PlaceBomb()
{
	auto indexPos = m_Level->GetActiveTileIndex(shared_from_this());
	m_Level->PlaceBomb(indexPos, m_Index);
}

