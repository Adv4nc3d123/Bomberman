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
#include "Level.h"
#include "Tile.h"
#include "TurnDownCommand.h"
#include "TurnRightCommand.h"
#include "TurnUpCommand.h"
#include "BombCommand.h"


void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Bomberman - Bram Dewachter 2DAE01",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		720,
		624,
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

	//get window size
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(window, &width, &height);

	//FPS_Counter
	auto FPS_Counter = std::make_shared<::FPS_Counter>();
	FPS_Counter->Initialize();
	FPS_Counter->SetPosition(width - 50.0f, 0.0f);
	scene.Add(FPS_Counter);

	auto level = std::make_shared<Level>(15,13);
	level->LoadLevelFromFile("Level.txt");
	scene.Add(level);

	auto actor = std::make_shared<Actor>();
	actor->Initialize();
	actor->SetLevel(level);
	LoadCommands(actor);
	scene.Add(actor);

	level->AddPlayer(actor);

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
	input.SetHoldCommand(ControllerButton::DpadLeft, new TurnLeftCommand(actor));
	input.SetHoldCommand(ControllerButton::DpadDown, new TurnDownCommand(actor));
	input.SetHoldCommand(ControllerButton::DpadRight, new TurnRightCommand(actor));
	input.SetHoldCommand(ControllerButton::DpadUp, new TurnUpCommand(actor));

	//wasd commands
	input.SetHoldCommand(SDL_SCANCODE_A, new TurnLeftCommand(actor));
	input.SetHoldCommand(SDL_SCANCODE_S, new TurnDownCommand(actor));
	input.SetHoldCommand(SDL_SCANCODE_D, new TurnRightCommand(actor));
	input.SetHoldCommand(SDL_SCANCODE_W, new TurnUpCommand(actor));

	//arrow commands
	input.SetHoldCommand(SDL_SCANCODE_LEFT, new TurnLeftCommand(actor));
	input.SetHoldCommand(SDL_SCANCODE_DOWN, new TurnDownCommand(actor));
	input.SetHoldCommand(SDL_SCANCODE_RIGHT, new TurnRightCommand(actor));
	input.SetHoldCommand(SDL_SCANCODE_UP, new TurnUpCommand(actor));

	//***ACTIONS***
	input.SetCommand(ControllerButton::ButtonA, new BombCommand(actor));
	input.SetCommand(SDLK_SPACE, new BombCommand(actor));

}
