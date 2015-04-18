#include "Player.h"

Player::Player()
{
	x = 0;
	y = 0;
	velocity = 64.0f;
	xTarget = 0;
	yTarget = 0;
	sprite = new Sprite(&GraphicsEngine::GetInstance());
	sprite->SetTexture("player.png");
	SDL_Rect r = SDL_Rect();
	r.x = (int)x;
	r.y = (int)y;
	r.w = 64;
	r.h = 64;
	sprite->SetBounds(r);
	sprite->SetPosition(r);
}

void Player::Step(float timeStep)
{
	float trueVel = velocity*(timeStep);
	float xDiff = xTarget - x;
	float yDiff = yTarget - y;
	float dist = sqrt(xDiff*xDiff + yDiff*yDiff);
	if (dist < MIN_DISTANCE)
	{
		Move(xTarget, yTarget);
		Lock(false);
	}
	else
	{
		float xVel = (xDiff / dist)*trueVel;
		float yVel = (yDiff / dist)*trueVel;
		Move(x + xVel, y + yVel);
	}
}

void Player::Move(float newX, float newY)
{
	x = newX;
	y = newY;
	SDL_Rect r = sprite->GetPosition();
	r.x = newX;
	r.y = newY;
	sprite->SetPosition(r);
}

void Player::Lock(bool set)
{
	lock = set;
}

bool Player::HandleEvent(SDL_Event& e)
{
	bool consume = false;
	if (!lock && e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the target
		Lock(true);
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: yTarget = y - 64; xTarget = x; break;
		case SDLK_DOWN: yTarget = y + 64; xTarget = x; break;
		case SDLK_LEFT: xTarget = x - 64; yTarget = y; break;
		case SDLK_RIGHT: xTarget = x + 64; yTarget = y; break;
		default: Lock(false);
		}
	}
	return consume;
}

void Player::SetTarget(float x, float y)
{
	xTarget = x;
	yTarget = y;
}