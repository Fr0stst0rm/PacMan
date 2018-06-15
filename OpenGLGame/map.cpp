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

void Map::loadMap(char * map)
{
	this->map = map;
}

