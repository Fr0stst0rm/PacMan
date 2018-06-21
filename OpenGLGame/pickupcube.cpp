#include "pickupcube.h"

PickupCube::PickupCube(int x, int y, Map * map) : map(map)
{
	setPos(- (map->getWidth()/ 6.0f + (float)(x) * 1.5f), - (map->getHeight() / 7.0f + (float)(y) * 1.5f), map->getZoom());
}

void PickupCube::createMesh()
{
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);

	if (MODE_2D) {
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.1f, -0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.0f);
		glVertex3f(0.1f, -0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.1f);
		glVertex3f(0.1f, 0.1f, -0.1f);
		glTexCoord2f(0.0f, 0.1f);
		glVertex3f(-0.1f, 0.1f, -0.1f);
	}
	else {
		// front face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.1f, -0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.0f);
		glVertex3f(0.1f, -0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.1f);
		glVertex3f(0.1f, 0.1f, -0.1f);
		glTexCoord2f(0.0f, 0.1f);
		glVertex3f(-0.1f, 0.1f, -0.1f);

		//// top face
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.1f, 0.1f, -0.3f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.1f, 0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.0f);
		glVertex3f(0.1f, 0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.1f);
		glVertex3f(0.1f, 0.1f, -0.3f);

		//// bottom face
		glTexCoord2f(0.1f, 0.1f);
		glVertex3f(-0.1f, -0.1f, -0.3f);
		glTexCoord2f(0.0f, 0.1f);
		glVertex3f(0.1f, -0.1f, -0.3f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.1f, -0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.0f);
		glVertex3f(-0.1f, -0.1f, -0.1f);

		//// right face
		glTexCoord2f(0.1f, 0.0f);
		glVertex3f(0.1f, -0.1f, -0.3f);
		glTexCoord2f(0.1f, 0.1f);
		glVertex3f(0.1f, 0.1f, -0.3f);
		glTexCoord2f(0.0f, 0.1f);
		glVertex3f(0.1f, 0.1f, -0.1f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.1f, -0.1f, -0.1f);

		//// left face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.1f, -0.1f, -0.3f);
		glTexCoord2f(0.1f, 0.0f);
		glVertex3f(-0.1f, -0.1f, -0.1f);
		glTexCoord2f(0.1f, 0.1f);
		glVertex3f(-0.1f, 0.1f, -0.1f);
		glTexCoord2f(0.0f, 0.1f);
		glVertex3f(-0.1f, 0.1f, -0.3f);
	}

	glEnd();
}


