#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game
{
public:
	static Game* GetInstance();
	
	enum GameState { PlayerMoving, EnemyMoving, PlayerSelecting, EnemySelecting };
	Player* pPlayer;
	Level* pLevel;
	std::vector<Enemy*> listEnemy;
	void GameLoop(float timeStep);

	//Dont want these as singleton
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
private:
	Game();
	//instance
	static Game* game;

	GameState state;
	void doEnemySelecting(float timeStep);
	void doEnemyMoving(float timeStep);
	void doPlayerSelecting(float timeStep);
	void doPlayerMoving(float timeStep);
};