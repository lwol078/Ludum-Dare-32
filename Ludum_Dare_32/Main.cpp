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
		Game* game = Game::GetInstance();
		Level l = Level::LoadLevel("Level1.txt");
		Sprite* back = new Sprite(GraphicsEngine::GetInstance());
		back->SetTexture("floor_tile.png");
		SDL_Rect r;
		r.x = 0;
		r.y = 0;
		r.w = 64;
		r.h = 64;
		back->SetBounds(r);
		r.w = 16;
		r.h = 16;
		back->SetPosition(r);
		GraphicsEngine::GetInstance()->SetBackground(back);
		l.GenerateWalls();
		Player p;
		game->pPlayer = &p;
		CrabEnemy mrKrabs;
		game->listEnemy.push_back(&mrKrabs);
		Movable::pLevel = &l;
		game->pLevel = &l;

		Timer stepTimer;
		stepTimer.start();
		//Event handler
		SDL_Event e;

		
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
			game->GameLoop(timeStep);
			//p.Step(timeStep);
			//mrKrabs.Step(timeStep);
			stepTimer.start();

			GraphicsEngine::GetInstance()->Draw();
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