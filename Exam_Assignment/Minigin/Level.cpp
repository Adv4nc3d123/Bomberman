#include "MiniginPCH.h"
#include "Level.h"
#include "Tile.h"
#include <SDL.h>
#include "HitBoxComponent.h"
#include <fstream>
#include "ResourceManager.h"
#include "Actor.h"

Level::Level(int horTiles, int verTiles)
	: HorTiles(horTiles)
	, Vertiles(verTiles)
	, vectorSize(HorTiles * Vertiles)
{	
	m_Tiles.resize(vectorSize);
	//Initialize();
}

void Level::Initialize()
{
	//--Tiles--
	//Create grid

	m_Tiles.resize(vectorSize);
	for (int i = 0; i < HorTiles * Vertiles; ++i)
	{
		auto tile = std::make_shared<Tile>(TileState::Open, i);
		tile->Initialize();
		int size{ (int)tile->GetSize() };
		int x{ i  * size % int(HorTiles * size) };
		int y{ i * size / int(HorTiles * size) * size };
		tile->SetPosition((float)x, (float)y);
		m_Tiles[i] = tile;
		AddChild(tile);
	}

	////--Set the correct tiles--
	////Walls
	////upper wall
	//for (int i{ 0 }; i < 18; ++i)
	//{
	//	m_Tiles[i]->SetState(TileState::Wall);
	//}
	////left wall
	//for (int i{ HorTiles }; i < HorTiles * Vertiles; i += HorTiles)
	//{
	//	m_Tiles[i]->SetState(TileState::Wall);
	//}
	////right wall
	//for (int i{ HorTiles - 1 }; i < HorTiles * Vertiles; i += HorTiles)
	//{
	//	m_Tiles[i]->SetState(TileState::Wall);
	//}
	////bottom wall
	//for (int i{ HorTiles * (Vertiles - 1) + 1 }; i < HorTiles * Vertiles; ++i)
	//{
	//	m_Tiles[i]->SetState(TileState::Wall);
	//}


}

int Level::GetRowNumber(int index)
{
	return index / HorTiles;
}

int Level::GetColumnNumber(int index)
{
	return index % HorTiles;
}

//Tile at index 0 will always be a wall, so this is passed along as index whenever there is no neighbour in that way

int Level::GetUpperIndex(int index)
{
	auto result = index - HorTiles;
	if (result > 0 && result < HorTiles*Vertiles - 1)
		return result;
	else
		return 0;
}

int Level::GetLeftIndex(int index)
{
	auto result = index - 1;
	if (result > 0 && result < HorTiles*Vertiles - 1)
		return result;
	else
		return 0;
}

int Level::GetRightIndex(int index)
{
	auto result = index + 1;
	if (result > 0 && result < HorTiles*Vertiles - 1)
		return result;
	else
		return 0;
}

int Level::GetBottomIndex(int index)
{
	auto result = index + HorTiles;
	if (result > 0 && result < HorTiles*Vertiles - 1)
		return result;
	else
		return 0;
}


int Level::GetActiveTileIndex(const std::shared_ptr<GameObject>& actor)
{
	//auto halfwidth = (m_Tiles[0]->GetSize()+0.1f) /2.0f;



	for(const auto& tile: m_Tiles)
	{
		if(actor->GetComponent<HitBoxComponent>()->IsInside(tile->GetComponent<HitBoxComponent>()))
		{
			return tile->GetIndex();
		}
	}
	//throw std::runtime_error(std::string("Impossible actor location") + SDL_GetError());
	return 0;
}

void Level::Update(const float deltaTime)
{
	int popped = 0;

	for (auto &i : m_ExplosionTimers)
	{
		int& tileIndex = i.first;
		int& actorIndex = i.second.first;
		float& time = i.second.second;
		time -= deltaTime;
		if (time <= 0.0f)
		{
			++popped;
			GetTile(tileIndex)->SetState(TileState::Explosion);
			GetTile(tileIndex)->SetExplosionState(ExplosionState::center);

			auto radius = m_Players[actorIndex].lock()->GetBombPower();

			auto startIndex = tileIndex;
			for (int j = 0; j < radius; j++)
			{
				auto index = GetUpperIndex(startIndex);
				auto tile = GetTile(index);
				if (tile->GetState() == TileState::Open || tile->GetState() == TileState::Explosion)
				{
					tile->SetState(TileState::Explosion);
					if (j < radius - 1)
						tile->SetExplosionState(ExplosionState::ver);
					else
						tile->SetExplosionState(ExplosionState::top);
				}
				else if (tile->GetState() == TileState::Breakable)
				{
					tile->SetState(TileState::Breaking);
					break;
				}
				else
					break;
				startIndex = index;
			}
			startIndex = tileIndex;
			for (int j = 0; j < radius; j++)
			{
				auto index = GetRightIndex(startIndex);
				auto tile = GetTile(index);
				if (tile->GetState() == TileState::Open || tile->GetState() == TileState::Explosion)
				{
					tile->SetState(TileState::Explosion);
					if (j < radius - 1)
						tile->SetExplosionState(ExplosionState::hor);
					else
						tile->SetExplosionState(ExplosionState::right);
				}
				else if (tile->GetState() == TileState::Breakable)
				{
					tile->SetState(TileState::Breaking);
					break;
				}
				else
					break;
				startIndex = index;
			}
			startIndex = tileIndex;
			for (int j = 0; j < radius; j++)
			{
				auto index = GetLeftIndex(startIndex);
				auto tile = GetTile(index);
				if (tile->GetState() == TileState::Open || tile->GetState() == TileState::Explosion)
				{
					tile->SetState(TileState::Explosion);
					if (j < radius - 1)
						tile->SetExplosionState(ExplosionState::hor);
					else
						tile->SetExplosionState(ExplosionState::left);
				}
				else if (tile->GetState() == TileState::Breakable)
				{
					tile->SetState(TileState::Breaking);
					break;
				}
				else
					break;
				startIndex = index;
			}
			startIndex = tileIndex;
			for (int j = 0; j < radius; j++)
			{
				auto index = GetBottomIndex(startIndex);
				auto tile = GetTile(index);
				if (tile->GetState() == TileState::Open || tile->GetState() == TileState::Explosion)
				{
					tile->SetState(TileState::Explosion);
					if (j < radius - 1)
						tile->SetExplosionState(ExplosionState::ver);
					else
						tile->SetExplosionState(ExplosionState::bottom);
				}
				else if (tile->GetState() == TileState::Breakable)
				{
					tile->SetState(TileState::Breaking);
					break;
				}
				else
					break;
				startIndex = index;
			}


		}
	}
	for (int i{ 0 }; i < popped; ++i)
		m_ExplosionTimers.pop_back();

	for(auto &i : m_Tiles)
	{
		if (i->GetState() == TileState::Explosion || i->GetState() == TileState::Breaking)
			if (i->IsFinished())
				i->SetState(TileState::Open);
	}
}

void Level::PlaceBomb(int index, int actorIndex)
{
	if (GetTile(index)->GetState() != TileState::Bomb)
	{
		m_ExplosionTimers.push_front(std::pair<int, std::pair<int, float> >(index, std::pair<int, float>(actorIndex, 2.0f)));
		GetTile(index)->SetState(TileState::Bomb);
	}
}

void Level::AddPlayer(const std::weak_ptr<Actor>& player)
{
	m_Players.push_back(player);
}

void Level::LoadLevelFromFile(const std::string& file)
{
	auto is = dae::ResourceManager::GetInstance().LoadTextFile(file);
	if (is.fail())
		std::cout << "File didnt open\n";
	int i = 0;
	char c;
	bool DoNothing = false;
	while(is.get(c))
	{
		DoNothing = false;
		std::shared_ptr<Tile> tile;
		switch(c)
		{
		case 'W':
			tile = std::make_shared<Tile>(TileState::Wall, i);
			break;
		case 'O':
			tile = std::make_shared<Tile>(TileState::Open, i);
			break;
		case 'B':
			tile = std::make_shared<Tile>(TileState::Breakable, i);
			break;
		default:
			DoNothing = true;
			--i;
			break;
		}
		if (!DoNothing)
		{
			tile->Initialize();
			int size{ (int)tile->GetSize() };
			int x{ i  * size % int(HorTiles * size) };
			int y{ i * size / int(HorTiles * size) * size };
			tile->SetPosition((float)x, (float)y);
			m_Tiles[i] = tile;
			AddChild(tile);
		}
		++i;
	}
	is.close();
}

std::vector<std::shared_ptr<Tile>> Level::GetTiles()
{
	return m_Tiles;
}

std::shared_ptr<Tile> Level::GetTile(int index)
{
	return m_Tiles[index];
}
