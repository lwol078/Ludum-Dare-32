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
	moveFinished = false;
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
		moveFinished = true;
	}
	else
	{
		float xVel = (xDiff / dist)*trueVel;
		float yVel = (yDiff / dist)*trueVel;
		Move(x + xVel, y + yVel);
	}
	sprite->depth = (int)-y;
}

void Movable::SetTarget(float xx, float yy)
{
	xTarget = xx;
	yTarget = yy;
	if (xx == x && yy == y)
		moveFinished = true;
	else
		moveFinished = false;
}

void Movable::Move(float newX, float newY)
{
	x = newX;
	y = newY;
	SDL_Rect r = sprite->GetPosition();
	r.x = (int)newX;
	r.y = (int)newY;
	sprite->SetPosition(r);
}

std::pair<float, float> Movable::GetPosition()
{
	return std::pair<float, float>(x, y);
}

std::pair<float, float> Movable::GetTarget()
{
	return std::pair<float, float>(xTarget, yTarget);
}

bool Movable::MoveFinished()
{
	return moveFinished;
}