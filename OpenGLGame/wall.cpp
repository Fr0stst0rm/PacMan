#include "wall.h"

Wall::Wall() : size(1)
{
}

Wall::Wall(float size) : size(size)
{
}

Wall::~Wall()
{
}

void Wall::setScale(float size)
{
	this->size = size;
}

void Wall::createMesh() {
	
	glScalef(size, size, size);
	drawCube();
}


void Wall::drawCube()
{
	glBegin(GL_QUADS);
	// front face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	// back face
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(-1.0f, -1.0f, -1.0f);
	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-1.0f, 1.0f, -1.0f);
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(1.0f, 1.0f, -1.0f);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(1.0f, -1.0f, -1.0f);
	//// top face
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(-1.0f, 1.0f, -1.0f);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-1.0f, 1.0f, 1.0f);
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(1.0f, 1.0f, 1.0f);
	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(1.0f, 1.0f, -1.0f);
	//// bottom face
	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-1.0f, -1.0f, -1.0f);
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(1.0f, -1.0f, -1.0f);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(1.0f, -1.0f, 1.0f);
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(-1.0f, -1.0f, 1.0f);
	//// right face
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(1.0f, -1.0f, -1.0f);
	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(1.0f, 1.0f, -1.0f);
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(1.0f, 1.0f, 1.0f);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(1.0f, -1.0f, 1.0f);
	//// left face
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-1.0f, -1.0f, -1.0f);
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(-1.0f, -1.0f, 1.0f);
	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-1.0f, 1.0f, 1.0f);
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(-1.0f, 1.0f, -1.0f);

	glEnd();
}