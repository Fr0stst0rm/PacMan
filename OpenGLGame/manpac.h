#pragma once

#ifndef _MAN_PAC_H
#define _MAN_PAC_H

#include "object3d.h"
#include "map.h"

class ManPac : public Object3D
{
public:
	ManPac(Map * map);

	void moveToNextTile(Direction dir);

protected:

	void createMesh();

private:

	Map * map;

	float x = 0;
	float y = 0;

	Direction currentDir = NORTH;

};


#endif // !_MAN_PAC_H
