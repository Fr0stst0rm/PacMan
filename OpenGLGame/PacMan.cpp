#include "PacMan.h"

PacMan::PacMan(Map map) : map(map)
{
}

PacMan::~PacMan()
{
}

void PacMan::moveToNextTile(Direction dir)
{
	
	if (map.checkNextDir(x,y,dir)) {
		switch (dir) {
		case NORTH:
			x++;
			break;
		case EAST:
			y++;
			break;
		case SOUTH:
			x--;
			break;
		case WEST:
			y--;
			break;
		}


	}
}
