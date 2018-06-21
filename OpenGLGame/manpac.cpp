#include "manpac.h"

ManPac::ManPac(Map * map) : map(map)
{
}

void ManPac::moveToNextTile(Direction dir)
{
	
	if (map->checkNextDir(x,y,dir)) {
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

void ManPac::createMesh()
{
	glColor3f(1.0f,1.0f,0.0f);
	glutSolidSphere(1.0f, 5.0f, 5.0f);
}
