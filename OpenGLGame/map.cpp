#include "map.h"

Map::Map() : x(0), y(0), z(0)
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

void Map::loadMap(char width, char height, char * map)
{
	this->height = height;
	this->width = width;

	int wallCount = 0;

	walls = new Wall[width*height];
	pickupCubes = new PickupCube[width*height];

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (map[xyToIndex(x, y, width)] == WALL) {
				walls[xyToIndex(x, y, width)] = Wall();
				walls[xyToIndex(x, y, width)].setPos(x + this->x, (height - 1) - (y + this->y), this->z);
				walls[xyToIndex(x, y, width)].setTexture("wall.tga");
			}
			else {
				walls[xyToIndex(x, y, width)] = NULL;
			}

			if (map[xyToIndex(x, y, width)] == PILL) {
				pickupCubes[xyToIndex(x, y, width)] = PickupCube();
				pickupCubes[xyToIndex(x, y, width)].setPos(x + this->x, (height - 1) - (y + this->y), this->z);
				pickupCubes[xyToIndex(x, y, width)].setTexture("wall.tga");
			}
			else {
				pickupCubes[xyToIndex(x, y, width)] = NULL;
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
		tempY++;
		break;
	case EAST:
		tempX--;
		break;
	case SOUTH:
		tempY--;
		break;
	case WEST:
		tempX++;
		break;
	}

	if ((tempX >= 0) && (tempX < width) && (tempY >= 0) && (tempY < height)) {
		//std::cout << "X: " << tempX << " Y: " << tempY << " => " << (int)(map[xyToIndex(tempX, (height - 1) - tempY, width)]);
		if (map[xyToIndex(tempX, (height - 1) - tempY, width)] == PATH) {
			return true;
		}
	}

	return false;
}

void Map::draw()
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (map[xyToIndex(x, y, width)] == WALL) {
				walls[xyToIndex(x, y, width)].setScale(size);
				walls[xyToIndex(x, y, width)].setPos(x + this->x, (height - 1) - (y + this->y), this->z);
				walls[xyToIndex(x, y, width)].draw();
			}
		}
	}
}

void Map::setPos(float x, float y, float z)
{
	this->x = x;
	this->y = -y;
	this->z = z;
}

float Map::getZoom()
{
	return z;
}

