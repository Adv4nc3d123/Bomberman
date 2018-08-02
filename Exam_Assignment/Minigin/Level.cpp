#include "MiniginPCH.h"
#include "Level.h"
#include "Tile.h"
#include <SDL.h>
#include "HitBoxComponent.h"

Level::Level()
	: HorTiles(19)
	, Vertiles(22)
	, vectorSize(HorTiles * Vertiles)
{	
	Initialize();
}

void Level::Initialize()
{
	//--Tiles--
	//Create grid

	m_Tiles.resize(vectorSize);
	for (int i = 0; i < HorTiles * Vertiles; ++i)
	{
		auto tile = std::make_shared<Tile>(TileState::Dot, i);
		tile->Initialize();
		int size{ (int)tile->GetSize() };
		int x{ i  * size % int(HorTiles * size) };
		int y{ i * size / int(HorTiles * size) * size };
		tile->SetPosition((float)x, (float)y);
		m_Tiles[i] = tile;
		AddChild(tile);
	}

	//--Set the correct tiles--
	//Walls
	//upper wall
	for (int i{ 0 }; i < 18; ++i)
	{
		m_Tiles[i]->SetState(TileState::Wall);
	}
	//left wall
	for (int i{ HorTiles }; i < HorTiles * Vertiles; i += HorTiles)
	{
		m_Tiles[i]->SetState(TileState::Wall);
	}
	//right wall
	for (int i{ HorTiles - 1 }; i < HorTiles * Vertiles; i += HorTiles)
	{
		m_Tiles[i]->SetState(TileState::Wall);
	}
	//bottom wall
	for (int i{ HorTiles * (Vertiles - 1) + 1 }; i < HorTiles * Vertiles; ++i)
	{
		m_Tiles[i]->SetState(TileState::Wall);
	}


	m_Tiles[19 * 2 + 2]->SetState(TileState::Wall);
	m_Tiles[19 * 2 + 3]->SetState(TileState::Wall);
	m_Tiles[19 * 3 + 2]->SetState(TileState::Wall);
	m_Tiles[19 * 3 + 3]->SetState(TileState::Wall);

	m_Tiles[19 * 2 + 5]->SetState(TileState::Wall);
	m_Tiles[19 * 2 + 6]->SetState(TileState::Wall);
	m_Tiles[19 * 2 + 7]->SetState(TileState::Wall);
	m_Tiles[19 * 3 + 5]->SetState(TileState::Wall);
	m_Tiles[19 * 3 + 6]->SetState(TileState::Wall);
	m_Tiles[19 * 3 + 7]->SetState(TileState::Wall);

	m_Tiles[19 + 9]->SetState(TileState::Wall);
	m_Tiles[19 * 2 + 9]->SetState(TileState::Wall);
	m_Tiles[19 * 3 + 9]->SetState(TileState::Wall);

	m_Tiles[19 * 2 + 11]->SetState(TileState::Wall);
	m_Tiles[19 * 2 + 12]->SetState(TileState::Wall);
	m_Tiles[19 * 2 + 13]->SetState(TileState::Wall);
	m_Tiles[19 * 3 + 11]->SetState(TileState::Wall);
	m_Tiles[19 * 3 + 12]->SetState(TileState::Wall);
	m_Tiles[19 * 3 + 13]->SetState(TileState::Wall);

	m_Tiles[19 * 2 + 15]->SetState(TileState::Wall);
	m_Tiles[19 * 2 + 16]->SetState(TileState::Wall);
	m_Tiles[19 * 3 + 15]->SetState(TileState::Wall);
	m_Tiles[19 * 3 + 16]->SetState(TileState::Wall);

	m_Tiles[19 * 5 + 2]->SetState(TileState::Wall);
	m_Tiles[19 * 5 + 3]->SetState(TileState::Wall);

	m_Tiles[19 * 5 + 5]->SetState(TileState::Wall);
	m_Tiles[19 * 6 + 5]->SetState(TileState::Wall);
	m_Tiles[19 * 7 + 5]->SetState(TileState::Wall);
	m_Tiles[19 * 7 + 6]->SetState(TileState::Wall);
	m_Tiles[19 * 7 + 7]->SetState(TileState::Wall);
	m_Tiles[19 * 8 + 5]->SetState(TileState::Wall);
	m_Tiles[19 * 9 + 5]->SetState(TileState::Wall);

	m_Tiles[19 * 5 + 7]->SetState(TileState::Wall);
	m_Tiles[19 * 5 + 8]->SetState(TileState::Wall);
	m_Tiles[19 * 5 + 9]->SetState(TileState::Wall);
	m_Tiles[19 * 6 + 9]->SetState(TileState::Wall);
	m_Tiles[19 * 7 + 9]->SetState(TileState::Wall);
	m_Tiles[19 * 5 + 10]->SetState(TileState::Wall);
	m_Tiles[19 * 5 + 11]->SetState(TileState::Wall);

	m_Tiles[19 * 5 + 13]->SetState(TileState::Wall);
	m_Tiles[19 * 6 + 13]->SetState(TileState::Wall);
	m_Tiles[19 * 7 + 13]->SetState(TileState::Wall);
	m_Tiles[19 * 7 + 12]->SetState(TileState::Wall);
	m_Tiles[19 * 7 + 11]->SetState(TileState::Wall);
	m_Tiles[19 * 8 + 13]->SetState(TileState::Wall);
	m_Tiles[19 * 9 + 13]->SetState(TileState::Wall);

	m_Tiles[19 * 5 + 15]->SetState(TileState::Wall);
	m_Tiles[19 * 5 + 16]->SetState(TileState::Wall);

	m_Tiles[19 * 7 + 1]->SetState(TileState::Wall);
	m_Tiles[19 * 8 + 1]->SetState(TileState::Wall);
	m_Tiles[19 * 9 + 1]->SetState(TileState::Wall);
	m_Tiles[19 * 7 + 2]->SetState(TileState::Wall);
	m_Tiles[19 * 8 + 2]->SetState(TileState::Wall);
	m_Tiles[19 * 9 + 2]->SetState(TileState::Wall);
	m_Tiles[19 * 7 + 3]->SetState(TileState::Wall);
	m_Tiles[19 * 8 + 3]->SetState(TileState::Wall);
	m_Tiles[19 * 9 + 3]->SetState(TileState::Wall);

	m_Tiles[19 * 7 + 15]->SetState(TileState::Wall);
	m_Tiles[19 * 8 + 15]->SetState(TileState::Wall);
	m_Tiles[19 * 9 + 15]->SetState(TileState::Wall);
	m_Tiles[19 * 7 + 16]->SetState(TileState::Wall);
	m_Tiles[19 * 8 + 16]->SetState(TileState::Wall);
	m_Tiles[19 * 9 + 16]->SetState(TileState::Wall);
	m_Tiles[19 * 7 + 17]->SetState(TileState::Wall);
	m_Tiles[19 * 8 + 17]->SetState(TileState::Wall);
	m_Tiles[19 * 9 + 17]->SetState(TileState::Wall);

	m_Tiles[19 * 11 + 1]->SetState(TileState::Wall);
	m_Tiles[19 * 12 + 1]->SetState(TileState::Wall);
	m_Tiles[19 * 13 + 1]->SetState(TileState::Wall);
	m_Tiles[19 * 11 + 2]->SetState(TileState::Wall);
	m_Tiles[19 * 12 + 2]->SetState(TileState::Wall);
	m_Tiles[19 * 13 + 2]->SetState(TileState::Wall);
	m_Tiles[19 * 11 + 3]->SetState(TileState::Wall);
	m_Tiles[19 * 12 + 3]->SetState(TileState::Wall);
	m_Tiles[19 * 13 + 3]->SetState(TileState::Wall);

	m_Tiles[19 * 11 + 5]->SetState(TileState::Wall);
	m_Tiles[19 * 12 + 5]->SetState(TileState::Wall);
	m_Tiles[19 * 13 + 5]->SetState(TileState::Wall);

	m_Tiles[19 * 11 + 13]->SetState(TileState::Wall);
	m_Tiles[19 * 12 + 13]->SetState(TileState::Wall);
	m_Tiles[19 * 13 + 13]->SetState(TileState::Wall);

	m_Tiles[19 * 9 + 7]->SetState(TileState::Wall);
	m_Tiles[19 * 10 + 7]->SetState(TileState::Wall);
	m_Tiles[19 * 11 + 7]->SetState(TileState::Wall);
	m_Tiles[19 * 9 + 8]->SetState(TileState::Wall);
	m_Tiles[19 * 9 + 10]->SetState(TileState::Wall);
	m_Tiles[19 * 9 + 11]->SetState(TileState::Wall);
	m_Tiles[19 * 10 + 11]->SetState(TileState::Wall);
	m_Tiles[19 * 11 + 11]->SetState(TileState::Wall);
	m_Tiles[19 * 11 + 8]->SetState(TileState::Wall);
	m_Tiles[19 * 11 + 9]->SetState(TileState::Wall);
	m_Tiles[19 * 11 + 10]->SetState(TileState::Wall);

	m_Tiles[19 * 15 + 2]->SetState(TileState::Wall);
	m_Tiles[19 * 15 + 3]->SetState(TileState::Wall);
	m_Tiles[19 * 16 + 3]->SetState(TileState::Wall);
	m_Tiles[19 * 17 + 3]->SetState(TileState::Wall);

	m_Tiles[19 * 15 + 5]->SetState(TileState::Wall);
	m_Tiles[19 * 15 + 6]->SetState(TileState::Wall);
	m_Tiles[19 * 15 + 7]->SetState(TileState::Wall);

	m_Tiles[19 * 13 + 7]->SetState(TileState::Wall);
	m_Tiles[19 * 13 + 8]->SetState(TileState::Wall);
	m_Tiles[19 * 13 + 9]->SetState(TileState::Wall);
	m_Tiles[19 * 14 + 9]->SetState(TileState::Wall);
	m_Tiles[19 * 15 + 9]->SetState(TileState::Wall);
	m_Tiles[19 * 13 + 10]->SetState(TileState::Wall);
	m_Tiles[19 * 13 + 11]->SetState(TileState::Wall);

	m_Tiles[19 * 15 + 11]->SetState(TileState::Wall);
	m_Tiles[19 * 15 + 12]->SetState(TileState::Wall);
	m_Tiles[19 * 15 + 13]->SetState(TileState::Wall);

	m_Tiles[19 * 15 + 15]->SetState(TileState::Wall);
	m_Tiles[19 * 16 + 15]->SetState(TileState::Wall);
	m_Tiles[19 * 17 + 15]->SetState(TileState::Wall);
	m_Tiles[19 * 15 + 16]->SetState(TileState::Wall);

	m_Tiles[19 * 11 + 15]->SetState(TileState::Wall);
	m_Tiles[19 * 12 + 15]->SetState(TileState::Wall);
	m_Tiles[19 * 13 + 15]->SetState(TileState::Wall);
	m_Tiles[19 * 11 + 16]->SetState(TileState::Wall);
	m_Tiles[19 * 12 + 16]->SetState(TileState::Wall);
	m_Tiles[19 * 13 + 16]->SetState(TileState::Wall);
	m_Tiles[19 * 11 + 17]->SetState(TileState::Wall);
	m_Tiles[19 * 12 + 17]->SetState(TileState::Wall);
	m_Tiles[19 * 13 + 17]->SetState(TileState::Wall);

	m_Tiles[19 * 17 + 1]->SetState(TileState::Wall);

	m_Tiles[19 * 17 + 17]->SetState(TileState::Wall);

	m_Tiles[19 * 19 + 2]->SetState(TileState::Wall);
	m_Tiles[19 * 19 + 3]->SetState(TileState::Wall);
	m_Tiles[19 * 19 + 4]->SetState(TileState::Wall);
	m_Tiles[19 * 19 + 5]->SetState(TileState::Wall);
	m_Tiles[19 * 18 + 5]->SetState(TileState::Wall);
	m_Tiles[19 * 17 + 5]->SetState(TileState::Wall);
	m_Tiles[19 * 19 + 6]->SetState(TileState::Wall);
	m_Tiles[19 * 19 + 7]->SetState(TileState::Wall);

	m_Tiles[19 * 19 + 11]->SetState(TileState::Wall);
	m_Tiles[19 * 19 + 12]->SetState(TileState::Wall);
	m_Tiles[19 * 19 + 13]->SetState(TileState::Wall);
	m_Tiles[19 * 18 + 13]->SetState(TileState::Wall);
	m_Tiles[19 * 17 + 13]->SetState(TileState::Wall);
	m_Tiles[19 * 19 + 14]->SetState(TileState::Wall);
	m_Tiles[19 * 19 + 15]->SetState(TileState::Wall);
	m_Tiles[19 * 19 + 16]->SetState(TileState::Wall);

	m_Tiles[19 * 17 + 7]->SetState(TileState::Wall);
	m_Tiles[19 * 17 + 8]->SetState(TileState::Wall);
	m_Tiles[19 * 17 + 9]->SetState(TileState::Wall);
	m_Tiles[19 * 18 + 9]->SetState(TileState::Wall);
	m_Tiles[19 * 19 + 9]->SetState(TileState::Wall);
	m_Tiles[19 * 17 + 10]->SetState(TileState::Wall);
	m_Tiles[19 * 17 + 11]->SetState(TileState::Wall);

	m_Tiles[19 * 16 + 2]->SetState(TileState::Boost);
	m_Tiles[19 * 16 + 16]->SetState(TileState::Boost);


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
		//auto pos = tile->GetTransform().GetPosition();


		//if((actorPos.x > pos.x - halfwidth) && (actorPos.x < pos.x + halfwidth) && 
		//	(actorPos.y > pos.y - halfwidth) && (actorPos.y < pos.y + halfwidth))
		//{
		//	return tile->GetIndex();
		//}
	}
	throw std::runtime_error(std::string("Impossible actor location") + SDL_GetError());
}

std::vector<std::shared_ptr<Tile>> Level::GetTiles()
{
	return m_Tiles;
}

std::shared_ptr<Tile> Level::GetTile(int index)
{
	return m_Tiles[index];
}
