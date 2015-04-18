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
	std::pair<float, float> GetTarget();
	std::pair<float, float> GetPosition();
	bool MoveFinished();
protected:
	float velocity;
	bool moveFinished;
	Sprite* sprite;
private:
	float x, y, xTarget, yTarget;
};