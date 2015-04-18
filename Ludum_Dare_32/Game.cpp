#include "Game.h"

void Game::GameLoop(float timeStep)
{
	switch (state)
	{
	case GameState::EnemyMoving: doEnemyMoving(timeStep); break;
	case GameState::PlayerMoving: doPlayerMoving(timeStep); break;
	case GameState::PlayerSelecting: doPlayerSelecting(timeStep); break;

	}
}

void Game::doEnemyMoving(float timeStep)
{
	bool finished = true;
	for (std::vector<Enemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); ++it)
	{
		(*it)->Step(timeStep);
		if (!(*it)->MoveFinished())
			finished = false;
	}
	if (finished)
		state = GameState::PlayerSelecting;
}

void Game::doPlayerMoving(float timeStep)
{
	bool finished = false;
	pPlayer->Step(timeStep);
	if (pPlayer->MoveFinished())
		finished = true;
	if (finished)
		state = GameState::EnemyMoving;
}

void Game::doPlayerSelecting(float timeStep)
{
	if (!pPlayer->MoveFinished())
		state = GameState::PlayerMoving;
}

Game::Game()
{
	pPlayer = NULL;
	pLevel = NULL;
}