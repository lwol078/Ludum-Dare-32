#include "GraphicsEngine.h"
#include "Sprite.h"
#include "Game.h"
#include <stdio.h>

GraphicsEngine* GraphicsEngine::ge = NULL;

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
			if (gRenderer == NULL)
				printf("Renderer could not be created");
			SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0xFF);

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
			//Create Renderer
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			
			
		}
	}
	sprBack = NULL;
}

GraphicsEngine::~GraphicsEngine()
{
	//Free loaded surfaces
	for (std::map<std::string, SDL_Texture*>::iterator it = texMap.begin(); it != texMap.end(); ++it)
	{
		SDL_DestroyTexture(it->second);
		it->second = NULL;
	}
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Destroy Renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void GraphicsEngine::Draw()
{
	//Clear Screen
	SDL_SetRenderDrawColor(gRenderer, 0, 100, 100, 0xFF);
	SDL_RenderClear(gRenderer);

	Game* game = Game::GetInstance();
	if (sprBack != NULL && game->pLevel != NULL)
	{
		SDL_Rect rPos = sprBack->GetPosition();
		float ratioX = Level::GRID_WIDTH / rPos.w;
		float ratioY = Level::GRID_HEIGHT / rPos.h;
		for (int row = 0; row < Game::GetInstance()->pLevel->height*ratioY; row++)
		{
			for (int col = 0; col < Game::GetInstance()->pLevel->width*ratioX; col++)
			{
				SDL_Rect r = sprBack->GetPosition();
				r.x = col*rPos.w;
				r.y = row*rPos.h;
				sprBack->SetPosition(r);
				SDL_RenderCopy(gRenderer, sprBack->GetTexture(), &sprBack->GetBounds(), &sprBack->GetPosition());
			}
		}
	}

	for (std::vector<Sprite*>::iterator it = spriteList.begin(); it != spriteList.end(); ++it)
		spriteQueue.push(*it);

	while (!spriteQueue.empty())
	{
		Sprite* spr = spriteQueue.top();
		spriteQueue.pop();
		//Render texture to screen
		SDL_RenderCopy(gRenderer, spr->GetTexture(), &spr->GetBounds(), &spr->GetPosition());
	}

	//Update screen
	SDL_RenderPresent(gRenderer);
}

SDL_Texture* GraphicsEngine::LoadTexture(std::string path)
{
	//If already in map return surface
	if (texMap.find(path) != texMap.end())
		return texMap.find(path)->second;

	//Otherwise load surface

	//The final optimized image
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	texMap.insert(std::pair<std::string,SDL_Texture*>(path, newTexture));
	return newTexture;
}

bool GraphicsEngine::LoadMedia()
{
	return true;
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

GraphicsEngine* GraphicsEngine::GetInstance()
{
	if (ge == NULL)
		ge = new GraphicsEngine();
	return ge;
}

void GraphicsEngine::SetBackground(Sprite* spr)
{
	sprBack = spr;
}