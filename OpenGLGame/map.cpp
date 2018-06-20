#include "map.h"

Map::Map(char height, char width) : height(height), width(width)
{
}

Map::~Map()
{
}

char Map::getHeight()
{
	return height;
}

char Map::getWidth()
{
	return width;
}

void Map::loadMap(char ** map)
{
	this->map = map;
}

bool Map::checkNextDir(int x, int y, Direction dir)
{
	int tempX = x;
	int tempY = y;

	switch (dir) {
	case NORTH:
		tempX++;
		break;
	case EAST:
		tempY++;
		break;
	case SOUTH:
		tempX--;
		break;
	case WEST:
		tempY--;
		break;
	}

	if ((tempX >= 0) && (tempX < width) && (tempY >= 0) && (tempY < height)) {
		if (map[tempX][tempY] == PATH) {
			return true;
		}
	}

	return false;
}

