#pragma once
#include "Movable.h"

class Enemy : public Movable
{
public:
	Enemy();
	void DoLogic();
};