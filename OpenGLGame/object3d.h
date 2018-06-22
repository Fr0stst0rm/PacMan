#pragma once


#ifndef _OBJECT_3D_H
#define _OBJECT_3D_H

#include <Windows.h>
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <iostream>
#include <string>
#include <math.h>

#include "tga.h"

/* some math.h files don't define pi...*/
#ifndef M_PI
#define M_PI 3.141592653
#endif

#define RAD(x) (((x)*M_PI)/180.)

class Object3D
{
public:
	Object3D();
	virtual ~Object3D();

	void setTexture(std::string path);

	void setPos(float x, float y, float z);
	
	//Function called by the glut display loop
	void draw();

	GLuint getTexture();

	void setScale(float size);

	void setZRotation(float deg);

protected:

	float size = 1;

	// virtual function to override, to create the 3D mash
	virtual void createMesh() = 0;

private:

	float rotationZ = 0;

	GLuint texture;

	float x, y, z;

};

#endif // !_OBJECT_3D_H
