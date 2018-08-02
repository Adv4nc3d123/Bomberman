#pragma once
#include "GameObject.h"

class Health : public GameObject
{
public:
	void Initialize();
	void DecreaseHealth(int amount);
	void ResetHealth();
private:
	int m_Health;

};
