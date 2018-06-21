#pragma once

#ifndef _PICK_UP_CUBE_H
#define _PICK_UP_CUBE_H

#include "object3d.h"
#include "defines.h"

class PickupCube : public Object3D
{
public:
	PickupCube();
	~PickupCube();

protected:
	void createMesh();

private:

};


#endif // !_PICK_UP_CUBE_H
