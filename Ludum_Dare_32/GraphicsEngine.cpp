#include "GraphicsEngine.h"
#include "Sprite.h"
#include <stdio.h>

GraphicsEngine::GraphicsEngine()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}
}

GraphicsEngine::~GraphicsEngine()
{
	//Free loaded image
	SDL_FreeSurface(gPNGSurface);
	gPNGSurface = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void GraphicsEngine::Draw()
{
	for (std::vector<Sprite*>::iterator it = spriteList.begin(); it != spriteList.end(); ++it)
		spriteQueue.push(*it);

	while (!spriteQueue.empty())
	{
		Sprite* spr = spriteQueue.top();
		spriteQueue.pop();
		//Apply the PNG image
		SDL_BlitSurface(spr->GetSurface(), NULL, gScreenSurface, NULL);
	}

	//Update the surface
	SDL_UpdateWindowSurface(gWindow);
}

SDL_Surface* GraphicsEngine::LoadSurface(std::string path)
{
	//If already in map return surface
	if (surfaceMap.find(path) != surfaceMap.end())
		return surfaceMap.find(path)->second;

	//Otherwise load surface

	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	surfaceMap.insert(std::pair<std::string,SDL_Surface*>(path, optimizedSurface));
	return optimizedSurface;
}

bool GraphicsEngine::LoadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	gPNGSurface = LoadSurface("loaded.png");
	if (gPNGSurface == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}

	return success;
}

void GraphicsEngine::AddSprite(Sprite* spr)
{
	std::vector<Sprite*>::iterator found = std::find(spriteList.begin(), spriteList.end(), spr);
	if (found == spriteList.end())
		spriteList.push_back(spr);
}

void GraphicsEngine::RemoveSprite(Sprite* spr)
{
	spriteList.erase(std::remove(spriteList.begin(), spriteList.end(), spr), spriteList.end());
}
