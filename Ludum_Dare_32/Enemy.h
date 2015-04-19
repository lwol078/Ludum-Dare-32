#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Movable.h"

class Enemy : public Movable
{
public:
	Enemy();
	void DoLogic();
	static void UpdateGrid();
private:
	static int aiGrid[Level::MAX_ROOM_WIDTH][Level::MAX_ROOM_HEIGHT];
	void MoveTargetPlayer();
	void MoveTargetRandom();
};