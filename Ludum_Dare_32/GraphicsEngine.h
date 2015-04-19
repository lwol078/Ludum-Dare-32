//Graphics engine for the game
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include "Sprite.h"

class GraphicsEngine
{
public:
	static GraphicsEngine* GetInstance();
	
	~GraphicsEngine();

	//Screen Limits
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	bool LoadMedia();

	void SetBackground(Sprite* spr);
	void AddSprite(Sprite* spr);
	void RemoveSprite(Sprite* spr);
	SDL_Texture* LoadTexture(std::string path);

	//Dont want these as singleton
	GraphicsEngine(GraphicsEngine const&) = delete;
	void operator=(GraphicsEngine const&) = delete;

	void Draw();
private:
	GraphicsEngine();
	static GraphicsEngine* ge;
	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;

	//The renderer
	SDL_Renderer* gRenderer = NULL;

	//Map of textures to draw
	std::map<std::string, SDL_Texture*> texMap;

	//Queue of sprites to draw
	std::priority_queue<Sprite*, std::vector<Sprite*>, LessThanByDepth> spriteQueue;
	Sprite* sprBack;

	//List of sprites
	std::vector<Sprite*> spriteList;
};