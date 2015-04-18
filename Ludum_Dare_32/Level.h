#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <string>
#include <vector>
#include "Sprite.h"

class Level
{
public:
	static const int MAX_ROOM_WIDTH = 100;
	static const int MAX_ROOM_HEIGHT = 100;
	static const int GRID_WIDTH = 64;
	static const int GRID_HEIGHT = 64;
	static Level LoadLevel(std::string path);
	void GenerateWalls();
	
	void SetPosition(int row, int col, int value);
	int GetPosition(int row, int col);
	int width, height;
private:
	int grid[MAX_ROOM_WIDTH][MAX_ROOM_HEIGHT];
	std::vector<Sprite*> walls;
};