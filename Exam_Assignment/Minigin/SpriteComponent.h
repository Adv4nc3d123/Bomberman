#pragma once
#include "Component.h"
#include "ImageComponent.h"
#include <map>

class SpriteComponent final : public ImageComponent
{
public:
	SpriteComponent();
	void Update(const float deltaTime) override;
	void AddAnim(const std::string& name, std::vector<SDL_Rect>& animVec);
	void SetAnim(const std::string&name, int animFrame = 0);
	void SetRepeat(bool repeat);
	void SetPlay(bool play);
	bool IsFinished();

private:
	std::map<std::string, std::vector<SDL_Rect>> m_Anims;
	bool m_Repeat;
	bool m_Finished;
	bool m_Play;
	int m_CurrentFrame;
	float m_FrameTime;
	std::string m_Anim;
};
