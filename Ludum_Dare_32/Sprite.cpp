#include "Sprite.h"
#include "GraphicsEngine.h"

Sprite::Sprite(GraphicsEngine* pGE)
{
	pGE->AddSprite(this);
	this->pGE = pGE;
	bounds = SDL_Rect();
	bounds.x = 0;
	bounds.y = 0;
	bounds.h = 0;
	bounds.w = 0;
	position = SDL_Rect();
	position.x = 0;
	position.y = 0;
	position.h = 0;
	position.w = 0;
}

Sprite::~Sprite()
{
	pGE->RemoveSprite(this);
}

bool Sprite::SetTexture(std::string path)
{
	pTexture = pGE->LoadTexture(path);
	if (pTexture != NULL)
		return true;
	return false;
}

SDL_Texture* Sprite::GetTexture()
{
	return pTexture;
}

SDL_Rect Sprite::GetBounds()
{
	return bounds;
}

void Sprite::SetBounds(SDL_Rect rect)
{
	bounds = rect;
}

SDL_Rect Sprite::GetPosition()
{
	return position;
}

void Sprite::SetPosition(SDL_Rect rect)
{
	position = rect;
}