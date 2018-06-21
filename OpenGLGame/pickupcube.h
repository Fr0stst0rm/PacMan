#pragma once

#ifndef _PICK_UP_CUBE_H
#define _PICK_UP_CUBE_H

#include "object3d.h"
#include "map.h"
#include "defines.h"

class PickupCube : public Object3D
{
public:
	PickupCube(int x, int y, Map * map);

protected:
	void createMesh();

private:
	Map * map;
};


#endif // !_PICK_UP_CUBE_H
