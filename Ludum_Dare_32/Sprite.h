#pragma once
#include <SDL.h>
#include <string>

class GraphicsEngine;
class Sprite
{
public:
	Sprite(GraphicsEngine* pGE);
	~Sprite();
	bool SetTexture(std::string path);
	SDL_Texture* GetTexture();
	SDL_Rect GetBounds();
	SDL_Rect GetPosition();
	void SetBounds(SDL_Rect rect);
	void SetPosition(SDL_Rect rect);
	int depth = 0;
private:
	GraphicsEngine* pGE;
	SDL_Texture* pTexture;

	//bounds in texture
	SDL_Rect bounds;
	//position and size
	SDL_Rect position;
};

struct LessThanByDepth
{
	bool operator()(const Sprite* lhs, const Sprite* rhs) const
	{
		return lhs->depth < rhs->depth;
	}
};