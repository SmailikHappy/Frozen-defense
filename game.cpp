#include "game.h"
#include <cstdio> //printf

Tmpl8::Surface* screen_;

namespace Tmpl8
{
	// Initialize the application
	void Game::Init()
	{
		screen_ = screen;				// pass screen (Surface) to globalvariables file, it is needed to access the screen globally
		presentScene = Scenes::menu;
		timeKoef = 1.0f;

		GenerateAmbience();
	}
	
	// Close down application
	void Game::Shutdown()
	{}

	// f() that Updates every tick
	void Game::Tick(float deltaTime)
	{
		deltaTime *= timeKoef;

		CheckMouseHover();

		if (presentScene == Scenes::playzone) UpdateGameState(deltaTime);

		UpdateScreen(deltaTime);
	}
};