#include "Enemy.h"
#include "Game.h"
#include <queue>
#include <tuple>

int Enemy::aiGrid[Level::MAX_ROOM_WIDTH][Level::MAX_ROOM_HEIGHT];

Enemy::Enemy() : Movable()
{

}

void Enemy::MoveTargetPlayer()
{
	int xx = (int)GetPosition().first/Level::GRID_WIDTH;
	int yy = (int)GetPosition().second / Level::GRID_HEIGHT;
	UpdateGrid();
	//here, up, down, left, right -> get minimum
	int destinations[5];
	destinations[0] = aiGrid[xx][yy];
	if (yy == 0)
		destinations[1] = INT_MAX;
	else
		destinations[1] = aiGrid[xx][yy - 1];
	if (yy == Level::MAX_ROOM_HEIGHT-1)
		destinations[2] = INT_MAX;
	else
		destinations[2] = aiGrid[xx][yy + 1];
	if (xx == 0)
		destinations[3] = INT_MAX;
	else
		destinations[3] = aiGrid[xx-1][yy];
	if (xx == Level::MAX_ROOM_WIDTH - 1)
		destinations[4] = INT_MAX;
	else
		destinations[4] = aiGrid[xx+1][yy];

	int min = 0;
	for (int i = 1; i < 5; i++)
	{
		if (destinations[i] < destinations[min] && destinations[i] != 1)
			min = i;
	}
	int tX, tY;
	switch (min)
	{
	case 0: tX = xx; tY = yy; break;
	case 1: tX = xx; tY = yy-1; break;
	case 2: tX = xx; tY = yy+1; break;
	case 3: tX = xx-1; tY = yy; break;
	case 4: tX = xx+1; tY = yy; break;
	}
	SetTarget(tX * Level::GRID_WIDTH, tY * Level::GRID_HEIGHT);
}

void Enemy::UpdateGrid()
{
	Level* pLevel = Game::GetInstance()->pLevel;
	Player* pPlayer = Game::GetInstance()->pPlayer;
	if (pLevel != NULL && pPlayer != NULL)
	{
		//Set to level map (1s walls, 0s free)
		for (int row = 0; row < Level::MAX_ROOM_HEIGHT; row++)
		{
			for (int col = 0; col < Level::MAX_ROOM_WIDTH; col++)
			{
				aiGrid[col][row] = pLevel->GetPosition(col,row);
			}
		}
		std::queue<std::tuple<int, int, int>> queue;
		int px = (int)pPlayer->GetPosition().first/64;
		int py = (int)pPlayer->GetPosition().second/64;

		//Add players position as (0+1=1) -> player is a wall in this ai
		queue.push(std::tuple<int,int,int>(px,py,0));
		while (!queue.empty())
		{
			int xx = std::get<0>(queue.front());
			int yy = std::get<1>(queue.front());
			int val = std::get<2>(queue.front());
			queue.pop();
			if (aiGrid[xx][yy] == 0)
			{
				aiGrid[xx][yy] = val + 1;
				//Add surrounding 4 squares to queue
				if (xx - 1 >= 0)
					queue.push(std::tuple<int, int, int>(xx - 1, yy, val + 1));
				if (xx + 1 < Level::MAX_ROOM_WIDTH)
				queue.push(std::tuple<int, int, int>(xx + 1, yy, val + 1));
				if (yy - 1 >= 0)
				queue.push(std::tuple<int, int, int>(xx, yy - 1, val + 1));
				if (yy + 1 < Level::MAX_ROOM_HEIGHT)
				queue.push(std::tuple<int, int, int>(xx, yy + 1, val + 1));
			}
		}
		FILE* file = fopen("enemyAI.txt", "w");
		for (int row = 0; row < Level::MAX_ROOM_HEIGHT; row++)
		{
			for (int col = 0; col < Level::MAX_ROOM_WIDTH; col++)
			{
				fprintf(file, "%3i", aiGrid[col][row]);
			}
			fprintf(file, "\n");
		}
		fclose(file);
	}
}

void Enemy::DoLogic()
{
	int random = rand() % 100;
	if (random < 70)
		MoveTargetPlayer();
	else
		MoveTargetRandom();
}

void Enemy::MoveTargetRandom()
{
	int xx = (int)GetPosition().first / Level::GRID_WIDTH;
	int yy = (int)GetPosition().second / Level::GRID_HEIGHT;
	//here, up, down, left, right -> get minimum
	int destinations[5];
	destinations[0] = aiGrid[xx][yy];
	if (yy == 0)
		destinations[1] = 1;
	else
		destinations[1] = aiGrid[xx][yy - 1];
	if (yy == Level::MAX_ROOM_HEIGHT - 1)
		destinations[2] = 1;
	else
		destinations[2] = aiGrid[xx][yy + 1];
	if (xx == 0)
		destinations[3] = 1;
	else
		destinations[3] = aiGrid[xx - 1][yy];
	if (xx == Level::MAX_ROOM_WIDTH - 1)
		destinations[4] = 1;
	else
		destinations[4] = aiGrid[xx + 1][yy];

	int min = 0;
	//Set self square to random
	destinations[0] = rand() % 100;
	for (int i = 1; i < 5; i++)
	{
		//if not a wall
		if (destinations[i] != 1)
		{
			//set destination to random
			destinations[i] = rand() % 100;
			if (destinations[i] < destinations[min])
				min = i;
		}
	}
	int tX, tY;
	switch (min)
	{
	case 0: tX = xx; tY = yy; break;
	case 1: tX = xx; tY = yy - 1; break;
	case 2: tX = xx; tY = yy + 1; break;
	case 3: tX = xx - 1; tY = yy; break;
	case 4: tX = xx + 1; tY = yy; break;
	}
	SetTarget(tX * Level::GRID_WIDTH, tY * Level::GRID_HEIGHT);
}