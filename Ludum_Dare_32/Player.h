#pragma once
#include "Sprite.h"
#include "GraphicsEngine.h"

class Player
{
public:
	Player();
	void Move(float x, float y);
	void SetTarget(float x, float y);
	void Step(float TimeStep);
	void Lock(bool set);
	bool HandleEvent(SDL_Event& e);
private:
	float MIN_DISTANCE = 4.0f;
	Sprite* sprite;
	float x, y, velocity, xTarget, yTarget;
	bool lock;

};