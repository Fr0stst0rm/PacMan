
#include <Windows.h>
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "manpac.h"
#include "map.h"
#include "wall.h"
#include "level1.h"
#include "pickupcube.h"


#define PLAYTHEME false

void exitMain();
void hideConsole();

void moveUp();
void moveDown();
void moveLeft();
void moveRight();

using namespace std;

int window;
float moveManPacY = 0.0f;
float moveManPacX = 0.0f;

int zoom = -27;

Map * map;
ManPac * manPac;

// ###################################################
// DELETE TEST VARIABLES
PickupCube * testCube;
// ###################################################

void reportGLError(const char * msg)
{
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		errString = gluErrorString(errCode);
		fprintf(stderr, "OpenGL Error: %s %s\n", msg, errString);
	}
	return;
}

void resize(int width, int height)
{
	// prevent division by zero
	if (height == 0) { height = 1; }

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void specialKeyPressed(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		moveUp();
		break;
	case GLUT_KEY_DOWN:
		moveDown();
		break;
	case GLUT_KEY_LEFT:
		moveLeft();
		break;
	case GLUT_KEY_RIGHT:
		moveRight();
		break;
	}
}

void keyPressed(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutDestroyWindow(window);
		exit(0);
		break;
	case 'w':
		moveUp();
		break;
	case 's':
		moveDown();
		break;
	case 'd':
		moveLeft();
		break;
	case 'a':
		moveRight();
		break;
	}
}

void display()
{
	manPac->moveToNextPos();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	manPac->draw();
	map->draw();
	testCube->draw();

	glutSwapBuffers();
}

void init(int width, int height)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	resize(width, height);

	
	map = new Map();
	map->loadMap(Level1::width, Level1::height, (char *)Level1::map);
	map->setPos(-Level1::width / 2.0f + 0.5f, -Level1::height / 2.0f + 0.5f, zoom);

	manPac = new ManPac(1,1,map);
	//manPac->setPos(-(map->getWidth() / 6.0f + (float)(1) * 1.5f), -(map->getHeight() / 7.0f + (float)(1) * 1.5f), map->getZoom());

	// #########################################################
	// TEST VARIABLES, DELETE LATER ON
	testCube = new PickupCube(0, 0, map);
	//testCube->setScale(0.9f);
	// #########################################################
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(15, timer, 1);
}

int main(int argc, char **argv)
{
	//hideConsole();

	/*if (PLAYTHEME) {
		PlaySound((LPCSTR)"manpac.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}*/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("MacPan");
	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);
	glutKeyboardFunc(&keyPressed);
	glutSpecialFunc(&specialKeyPressed);
	init(640, 480);
	glutTimerFunc(15, timer, 1);
	//glutFullScreen();
	glutMainLoop();
	exitMain();
	return 0;
}

void hideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void exitMain() {
		delete map;
		delete manPac;
}

void moveUp() {
	manPac->moveToNextTile(NORTH);
	//glutPostRedisplay();
}

void moveDown() {
	manPac->moveToNextTile(SOUTH);
	//glutPostRedisplay();
}

void moveLeft() {
	manPac->moveToNextTile(EAST);
	//glutPostRedisplay();
}

void moveRight() {
	manPac->moveToNextTile(WEST);
	//glutPostRedisplay();
}