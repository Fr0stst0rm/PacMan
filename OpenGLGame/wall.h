
#ifndef WALL_H
#define WALL_H 

#include "object3d.h"

class Wall : public Object3D
{
public:
	Wall();
	Wall(double size);
	~Wall();

protected:

	void createMesh();

private:
	void drawCube();

	double size;
};

#endif // !WALL_H
