//Main Game loop of game
#include "GraphicsEngine.h"
#include "Sprite.h"
#include "Player.h"
#include "Timer.h"
#include "Level.h"
#include "CrabEnemy.h"
#include "Game.h"
#include <stdio.h>
#include <string>

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

bool init();


int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Main loop flag
		bool quit = false;
		Game game;
		Level l = Level::LoadLevel("Level1.txt");
		l.GenerateWalls();
		game.pLevel = &l;
		Timer stepTimer;
		stepTimer.start();
		//Event handler
		SDL_Event e;

		SDL_Rect r = SDL_Rect();

		Player p;
		game.pPlayer = &p;
		CrabEnemy mrKrabs;
		game.listEnemy.push_back(&mrKrabs);
		Movable::pLevel = &l;

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else
				{
					p.HandleEvent(e);
				}
			}
			//Logic
			float timeStep = stepTimer.getTicks() / 1000.f;
			game.GameLoop(timeStep);
			//p.Step(timeStep);
			//mrKrabs.Step(timeStep);
			stepTimer.start();

			GraphicsEngine::GetInstance().Draw();
		}
	}

	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	return success;
}