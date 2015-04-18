#include "Player.h"

Player::Player()
{
	x = 0;
	y = 0;
	xVel = 0;
	yVel = 0;
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

void Player::Step()
{
	xVel = 0;
	yVel = 0;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		yVel = -1;
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		yVel = 1;
	}
	else if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		xVel = -1;
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		xVel = 1;
	}

	Move(x + xVel, y + yVel);
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