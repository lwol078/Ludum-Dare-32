#include "Enemy.h"

Enemy::Enemy() : Movable()
{

}

void Enemy::DoLogic()
{
	int xx = GetPosition().first;
	int yy = GetPosition().second;
	SetTarget(xx - Level::GRID_WIDTH, yy);
}