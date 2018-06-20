#include "map.h"

Map::Map()
{
}

Map::~Map()
{
	delete walls;
}

char Map::getHeight()
{
	return height;
}

char Map::getWidth()
{
	return width;
}

void Map::loadMap(char height, char width, char ** map)
{
	this->height = height;
	this->width = width;

	int wallCount = 0;

	walls = new Wall[width*height];

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (map[x][y] == WALL) {
				walls[xyToIndex(x, y, width)] = Wall();
			}
			else {
				walls[xyToIndex(x, y, width)] = NULL;
			}
		}
	}

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

void Map::draw()
{
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (map[x][y] == WALL) {
				walls[xyToIndex(x, y, width)].draw();
			}
		}
	}
}

