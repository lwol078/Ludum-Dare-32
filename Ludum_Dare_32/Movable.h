#pragma once
#include "Sprite.h"
#include "Level.h"

class Movable
{
public:
	static const float MIN_DISTANCE;
	static Level* pLevel;
	
	Movable();
	void Move(float x, float y);
	virtual void Step(float timeStep);
	void SetTarget(float x, float y);
	void Lock(bool set);

protected:
	float x, y, velocity, xTarget, yTarget;
	bool lock;
	Sprite* sprite;
};