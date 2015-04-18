#pragma once
#include "Sprite.h"

class Enemy
{
public:
	void Move(float x, float y);
	void SetTarget(float x, float y);
private:
	float x, y;

};