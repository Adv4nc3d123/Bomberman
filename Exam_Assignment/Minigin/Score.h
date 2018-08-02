#pragma once
#include "GameObject.h"

class Score : public GameObject
{
public:
	void Initialize();
	void IncreaseScore(int amount);
	void ResetScore();
private:
	int m_Score;
};
