
#include <Windows.h>
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "map.h"
#include "wall.h"
#include <iostream>

#define PLAYTHEME false

void glutLeaveMainLoop();
void hideConsole();

using namespace std;

/* some math.h files don't define pi...*/
#ifndef M_PI
#define M_PI 3.141592653
#endif

#define RAD(x) (((x)*M_PI)/180.)

int window;
float moveManPacY = 0.0f;
float moveManPacX = 2.0f;

int animating = 1;

Wall * wall1;
Wall * wall2;
Wall * wall3;

Map* map;

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
			moveManPacY += 0.1f;
			glutPostRedisplay();
			break;

		case GLUT_KEY_DOWN:
			moveManPacY -= 0.1f;
			glutPostRedisplay();
			break;

		case GLUT_KEY_LEFT:
			moveManPacX -= 0.1f;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			moveManPacX += 0.1f;
	}
}

void keyPressed(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutDestroyWindow(window);
		exit(0);
		break;
	case 'a':
		animating = animating ? 0 : 1;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	wall1->setPos(moveManPacX, moveManPacY, -10);
	wall1->draw();

	wall2->setPos(0, 0, -10);
	wall2->draw();

	wall3->setPos(2, 0, -10);
	wall3->draw();

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

	/*map = new Map();
	map->loadMap();*/

	

	// ####################################################################
	// TEST VARIABLES -- DELETE LATER ON
	// ####################################################################
	wall1 = new Wall(1.1f);
	wall1->setTexture("crate.tga");

	wall2 = new Wall(1.2);
	wall2->setTexture("cheese.tga");

	wall3 = new Wall(1.3);
	wall3->setTexture("wall.tga");

}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(15, timer, 1);
}

int main(int argc, char **argv)
{
	hideConsole();

	if (PLAYTHEME) {
		PlaySound("manpac.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}

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
	glutLeaveMainLoop();
	return 0;
}

void hideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void glutLeaveMainLoop() {
	cout << "Freeing memory";

	delete wall1;
	delete wall2;
	delete wall3;
}