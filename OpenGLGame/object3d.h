#pragma once


#ifndef _OBJECT_3D_H
#define _OBJECT_3D_H

#include <Windows.h>
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>

#include <iostream>
#include <string>

#include "tga.h"

class Object3D
{
public:
	Object3D();
	virtual ~Object3D();

	void setTexture(std::string path);

	void setPos(int x, int y, int z);

	void draw();

	GLuint getTexture();

protected:

	virtual void createMesh() = 0;

private:

	GLuint texture;

	int x, y, z;

};

#endif // !_OBJECT_3D_H
