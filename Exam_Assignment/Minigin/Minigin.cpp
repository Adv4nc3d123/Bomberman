#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "FPS_Counter.h"
#include "TurnLeftCommand.h"
#include "Actor.h"
#include "TurnDownCommand.h"
#include "TurnRightCommand.h"
#include "TurnUpCommand.h"


void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		608,
		704,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("test");

}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();
	m_T1 = std::chrono::high_resolution_clock::now();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		bool doContinue = true;
		while (doContinue)
		{
			auto t2 = std::chrono::high_resolution_clock::now();
			auto timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - m_T1);
			float deltaTime = (float)timeSpan.count();

			//otherwise actor could jump to impossible locations after a breakpoint or huge timegap
			const float maxDelta{ 0.1f };
			deltaTime = min(deltaTime, maxDelta);
			m_T1 = t2;

			doContinue = input.ProcessInput();


			
			sceneManager.Update(deltaTime);;
			renderer.Render();

		}
	}

	Cleanup();
}

void dae::Minigin::LoadCommands(const std::shared_ptr<Actor>& actor) const
{
	//get input manager instance
	auto& input = InputManager::GetInstance();

	//***SETTING DIRECTION***
	//controllerbutton commands
	input.SetCommand(ControllerButton::DpadLeft, new TurnLeftCommand(actor));
	input.SetCommand(ControllerButton::DpadDown, new TurnDownCommand(actor));
	input.SetCommand(ControllerButton::DpadRight, new TurnRightCommand(actor));
	input.SetCommand(ControllerButton::DpadUp, new TurnUpCommand(actor));

	//wasd commands
	input.SetCommand(SDLK_a, new TurnLeftCommand(actor));
	input.SetCommand(SDLK_s, new TurnDownCommand(actor));
	input.SetCommand(SDLK_d, new TurnRightCommand(actor));
	input.SetCommand(SDLK_w, new TurnUpCommand(actor));

	//arrow commands
	input.SetCommand(SDLK_LEFT, new TurnLeftCommand(actor));
	input.SetCommand(SDLK_DOWN, new TurnDownCommand(actor));
	input.SetCommand(SDLK_RIGHT, new TurnRightCommand(actor));
	input.SetCommand(SDLK_UP, new TurnUpCommand(actor));

	//***ACTIONS***

}
