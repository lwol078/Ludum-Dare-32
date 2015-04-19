#include "CrabEnemy.h"
#include "GraphicsEngine.h"

CrabEnemy::CrabEnemy() : Enemy()
{
	velocity = 64.0f;
	sprite = new Sprite(GraphicsEngine::GetInstance());
	sprite->SetTexture("player.png");
	SDL_Rect r = SDL_Rect();
	r.x = 0;
	r.y = 0;
	r.w = 64;
	r.h = 64;
	sprite->SetBounds(r);
	r.x = (int)GetPosition().first;
	r.y = (int)GetPosition().second;
	sprite->SetPosition(r);
	Move(64 * 4, 64 * 5);
}

void CrabEnemy::Step(float timeStep)
{
	Movable::Step(timeStep);
}