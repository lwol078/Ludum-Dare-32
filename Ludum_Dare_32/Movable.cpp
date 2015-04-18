#include "Movable.h"

const float Movable::MIN_DISTANCE = 4.0f;
Level* Movable::pLevel = NULL;

Movable::Movable()
{
	x = 0;
	y = 0;
	velocity = 0;
	xTarget = x;
	yTarget = y;
	lock = false;
}

void Movable::Step(float timeStep)
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
	sprite->depth = -y;
}

void Movable::SetTarget(float x, float y)
{
	xTarget = x;
	yTarget = y;
}

void Movable::Move(float newX, float newY)
{
	x = newX;
	y = newY;
	SDL_Rect r = sprite->GetPosition();
	r.x = newX;
	r.y = newY;
	sprite->SetPosition(r);
}

void Movable::Lock(bool set)
{
	lock = set;
}