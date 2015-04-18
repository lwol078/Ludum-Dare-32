//Main Game loop of game

#include "GraphicsEngine.h"
#include "Sprite.h"
#include <stdio.h>
#include <string>

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

bool init();
GraphicsEngine* ge;


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

		//Event handler
		SDL_Event e;

		Sprite* spr = new Sprite(ge);
		spr->SetSurface("loaded.png");
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
			}

			ge->Draw();
		}
	}

	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	ge = new GraphicsEngine();
	if (ge == NULL)
	{
		printf("Failed to initialise Graphics Engine");
		success = false;
	}
	return success;
}