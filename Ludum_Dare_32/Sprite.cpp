#include "Sprite.h"
#include "GraphicsEngine.h"

Sprite::Sprite(GraphicsEngine* pGE)
{
	pGE->AddSprite(this);
	this->pGE = pGE;
	bounds = SDL_Rect();
	bounds.x = 20;
	bounds.y = 30;
	bounds.h = 100;
	bounds.w = 200;
	position = SDL_Rect();
	position.x = 20;
	position.y = 30;
	position.h = 100;
	position.w = 200;
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