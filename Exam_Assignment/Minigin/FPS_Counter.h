#pragma once
#include "GameObject.h"

class FPS_Counter : public GameObject
{
public:
	void Initialize();
	void Update(const float deltaTime) override;
	void Render() const override;
	int GetFPS();
	void EnableRender(bool showfps);

private:
	float m_FpsTimer;
	int m_FpsCount;
	float m_FPS;
	bool m_ShowFps;
};
