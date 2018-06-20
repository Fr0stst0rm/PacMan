
#ifndef WALL_H
#define WALL_H 

#include "object3d.h"

class Wall : public Object3D
{
public:
	Wall();
	Wall(float size);
	~Wall();

	void setScale(float size);

protected:

	void createMesh();

private:
	void drawCube();

	float size;
};

#endif // !WALL_H
