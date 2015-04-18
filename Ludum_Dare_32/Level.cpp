#include "Level.h"
#include <stdio.h>
#include <cctype>
#include "GraphicsEngine.h"

Level Level::LoadLevel(std::string path)
{
	Level newLevel;
	newLevel.width = 0;
	newLevel.height = 0;
	int col = 0;
	int row = 0;
	FILE* file = fopen(path.c_str(),"r");
	while (1)
	{
		char c = getc(file);
		if (c == -1)
			break;
		if (isdigit(c))
		{
			newLevel.SetPosition(col,row,c - '0');
			newLevel.height = row+1;
			col++;
			if (col > newLevel.width)
				newLevel.width = col;
		}
		else switch (c)
		{
		case '\n': row++; col = 0; break;
		default: newLevel.SetPosition(col, row, 0); col++; break;
		}
	}
	for (col = 0; col < newLevel.width; col++)
	{
		for (int row = 0; row < newLevel.height; row++)
		{
			int current = newLevel.GetPosition(col, row);
			if (current < 0 || current > 9)
			{
				newLevel.SetPosition(col, row, 0);
			}
		}
	}
	fclose(file);
	return newLevel;
}

void Level::SetPosition(int col, int row, int value)
{
	grid[col][row] = value;
}

int Level::GetPosition(int col, int row)
{
	return grid[col][row];
}

void Level::GenerateWalls()
{
	int row = 0;
	int col = 0;
	for (col = 0; col < width; col++)
	{
		for (int row = 0; row < height; row++)
		{
			int current = grid[col][row];
			if (current == 1)
			{
				Sprite* spr = new Sprite(&GraphicsEngine::GetInstance());
				spr->SetTexture("wall tile.png");
				SDL_Rect r;
				r.x = 0;
				r.y = 0;
				r.w = GRID_WIDTH;
				r.h = GRID_HEIGHT;
				SDL_Rect r2 = r;
				bool left, right, above, below;
				left = grid[col - 1][row] == 1;
				right = grid[col + 1][row] == 1;
				above = grid[col][row - 1] == 1;
				below = grid[col][row + 1] == 1;/*
				if (!left)
				{
					r.w -= GRID_WIDTH / 8;
					r.x = GRID_WIDTH / 8;
				}
				if (!right)
					r.w -= GRID_WIDTH / 8;*/
				if (!above && !below)
				{
					r.y = GRID_WIDTH * 3 / 4;
				}
				else if (!below)
				{
					r.y = GRID_WIDTH;
				}
				spr->SetBounds(r);
				r2.x += col * 64;
				r2.y += row * 64;
				spr->SetPosition(r2);
				spr->depth = -r2.y;
				walls.push_back(spr);
			}
		}
	}
}