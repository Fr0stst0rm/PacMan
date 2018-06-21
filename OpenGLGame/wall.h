
#ifndef WALL_H
#define WALL_H 

#include "object3d.h"
#include "defines.h"

class Wall : public Object3D
{
public:
	Wall();
	Wall(float size);
	~Wall();

protected:

	void createMesh();

private:
	void drawCube();

};

#endif // !WALL_H
