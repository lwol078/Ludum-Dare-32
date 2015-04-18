#pragma once
#include "Movable.h"

class Player : public Movable
{
public:
	Player();
	bool HandleEvent(SDL_Event& e);
};