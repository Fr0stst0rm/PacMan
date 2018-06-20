#pragma once

#ifndef PAC_MAN_H
#define PAC_MAN_H

#include "map.h"

class PacMan
{
public:
	PacMan(Map map);
	~PacMan();

	void moveToNextTile(Direction dir);

private:

	Map map;

	float x = 0;
	float y = 0;

	Direction currentDir = NORTH;

};


#endif // !PAC_MAN_H
