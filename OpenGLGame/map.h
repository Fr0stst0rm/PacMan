
#ifndef _MAP_H
#define _MAP_H

#include "wall.h"
#include <stdio.h>

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
	
	void loadMap(char width,  char height, char * map);

	bool checkNextDir(int x, int y, Direction dir);

	void draw();

	void setPos(float x, float y, float z);


	float getZoom();

private:
	float size = 0.5f;
	float x, y, z;

	Wall * walls;

	char height = 0;
	char width = 0;

	char * map;

};

#endif // !_MAP_H

