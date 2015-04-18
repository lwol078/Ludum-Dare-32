#pragma once
#include "Sprite.h"
#include "GraphicsEngine.h"

class Player
{
public:
	Player();
	void Move(float x, float y);
	void Step();
private:
	Sprite* sprite;
	float x, y, xVel,yVel;

};