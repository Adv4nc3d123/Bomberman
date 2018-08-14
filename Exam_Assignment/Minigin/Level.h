#pragma once
#include "GameObject.h"
#include <deque>
class Tile;
class Actor;

class Level : public GameObject
{
public:
	Level(int horTiles, int verTiles);
	std::vector<std::shared_ptr<Tile>> GetTiles();
	std::shared_ptr<Tile> GetTile(int index);
	int GetActiveTileIndex(const std::shared_ptr<GameObject>& actor);
	virtual void Update(const float deltaTime) override;
	void PlaceBomb(int index, int actorIndex);
	void AddPlayer(const std::weak_ptr<Actor>& player);
	void LoadLevelFromFile(const std::string& file);
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
	std::deque<std::pair<int, std::pair<int, float> > > m_ExplosionTimers;
	std::vector<std::weak_ptr<Actor>> m_Players;
};
