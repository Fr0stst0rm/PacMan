
#include <Windows.h>
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "map.h"
#include "wall.h"
#include "level1.h"


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
float moveManPacX = 0.0f;

int animating = 1;

int zoom = -27;

Map * map;

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

	map->draw();
	
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
	map->loadMap(Level1::width, Level1::height, (char *) Level1::map);
	map->setPos(-Level1::width/2.0f + 0.5f, -Level1::height/2.0f+0.5f, zoom);

}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(15, timer, 1);
}

int main(int argc, char **argv)
{
	//hideConsole();

	if (PLAYTHEME) {
		PlaySound((LPCWSTR)"manpac.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
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

	delete map;
}