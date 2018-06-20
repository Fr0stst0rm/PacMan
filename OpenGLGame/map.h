
#ifndef _MAP_H
#define _MAP_H

#include "wall.h"

#define xyToIndex(x,y, maxX) ( (y * maxX) + x)

enum Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

enum MapTiles
{
	PATH = 0,
	WALL = 1
};

class Map
{
public:
	Map();
	~Map();

	char getHeight();
	char getWidth();
	
	void loadMap(char height, char width, char ** map);

	bool checkNextDir(int x, int y, Direction dir);

	void draw();

private:

	Wall * walls;

	char height = 0;
	char width = 0;

	char ** map;

};

#endif // !_MAP_H

