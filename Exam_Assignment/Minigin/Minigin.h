#pragma once
#include "InputManager.h"
#include <chrono>

struct SDL_Window;
class GameObject;

namespace dae
{

	class Minigin
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		void LoadCommands(const std::shared_ptr<Actor>& actor) const;
		std::chrono::high_resolution_clock::time_point m_T1;
	};
}