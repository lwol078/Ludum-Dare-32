#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game
{
public:
	Game();
	enum GameState { PlayerMoving, EnemyMoving, PlayerSelecting };
	Player* pPlayer;
	Level* pLevel;
	std::vector<Enemy*> listEnemy;
	void GameLoop(float timeStep);
private:
	GameState state;
	void doEnemyMoving(float timeStep);
	void doPlayerSelecting(float timeStep);
	void doPlayerMoving(float timeStep);
};