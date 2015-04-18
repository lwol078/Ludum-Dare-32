#include "Sprite.h"
#include "GraphicsEngine.h"

Sprite::Sprite(GraphicsEngine* pGE)
{
	pGE->AddSprite(this);
	this->pGE = pGE;
}

Sprite::~Sprite()
{
	pGE->RemoveSprite(this);
}

bool Sprite::SetSurface(std::string path)
{
	pSurface = pGE->LoadSurface(path);
	if (pSurface != NULL)
		return true;
	return false;
}

SDL_Surface* Sprite::GetSurface()
{
	return pSurface;
}