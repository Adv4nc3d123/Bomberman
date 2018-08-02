#pragma once
#include "GameObject.h"

class Tile;

class Level : public GameObject
{
public:
	Level();
	std::vector<std::shared_ptr<Tile>> GetTiles();
	std::shared_ptr<Tile> GetTile(int index);
	int GetActiveTileIndex(const std::shared_ptr<GameObject>& actor);
	int GetUpperIndex(int index);
	int GetLeftIndex(int index);
	int GetRightIndex(int index);
	int GetBottomIndex(int index);
private:
	void Initialize();
	const int HorTiles;
	const int Vertiles;
	const int vectorSize;
	std::vector<std::shared_ptr<Tile>> m_Tiles; //makes code more clear by not having to get child every time
	int GetRowNumber(int index);
	int GetColumnNumber(int index);
};
