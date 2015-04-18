#pragma once
#include "Enemy.h"

class CrabEnemy : public Enemy
{
public:
	CrabEnemy();
	void Step(float timeStep) override;
};