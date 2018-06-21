
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
#include "defines.h"

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

float lightx = 5.0f, lighty = 5.0f, lightz = 3.0f;
float lightAngle = 0.0f;

bool ende = false;

int zoom = -27;

Map * map;
ManPac * manPac;

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
		//manPac->offset += 0.01f;
		//manPac->setPos(1,1, map->getZoom());
		//cout << "Offset " << manPac->offset;
		break;
	case GLUT_KEY_DOWN:
		moveDown();
		//manPac->offset -= 0.01f;
		//manPac->setPos(1, 1, map->getZoom());
		//cout << "Offset " << manPac->offset;
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
		ende = true;
		
		break;
	case 'w':
		moveUp();
		break;
	case 's':
		moveDown();
		break;
	case 'a':
		moveLeft();
		break;
	case 'd':
		moveRight();
		break;
	case 'l':
		if (MODE_2D) {
			MODE_2D = false;
		}
		else {
			MODE_2D = true;
		}
		break;
	}
}

void endAnimation() {

	glPushMatrix();
	GLfloat mat_diffuse[] = { 1.0f,1.0f,0.0f }; //material (gelb)
	GLfloat mat_shininess[] = { 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -20.0f);
	glutSolidSphere(3.0f, 200, 160);
	glPopMatrix();

	glPushMatrix();
	GLfloat mat_diffuse2[] = { 1.0f,0.0f,0.0f }; //material (rot)
	GLfloat mat_shininess2[] = { 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse2);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(-1.25f, 1.25f, -17.5f);
	glutSolidSphere(0.5f, 200, 160);
	glPopMatrix();

	glPushMatrix();
	GLfloat mat_diffuse3[] = { 1.0f,0.0f,0.0f }; //material (rot)
	GLfloat mat_shininess3[] = { 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(1.25f, 1.25f, -17.5f);
	glutSolidSphere(0.5f, 200, 160);
	glPopMatrix();

	GLfloat light_position[] = { lightx, lighty, lightz, 0.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	glEnable(GL_LIGHTING); //light aktivieren
	glEnable(GL_LIGHT0); // licht nummer eins einschalten

	lightx = cos(lightAngle) * 5;
	lightz = sin(lightAngle) * 5;

	lightAngle += 0.05;

	if (lightAngle >= 18.0f) {
		std::cout << "Hello";
		glutDestroyWindow(window);
		exit(0);
	}

}

void display()
{
	if (!ende) { manPac->moveToNextPos(); }

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (ende) {
		endAnimation();
	}
	else {
		manPac->draw();
		map->draw();
	}

	

	glutSwapBuffers();
}

void init(int width, int height)
{
	if (!ende) {
		GLfloat mat_diffuse[] = { 1.0f,1.0f,0.0f }; //material (gelb)
		GLfloat mat_shininess[] = { 1.0f };
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		GLfloat light_position[] = { 10.0f, 10.0f, 0.1f, 0.0f };
		GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

		glEnable(GL_LIGHTING); //light aktivieren
		glEnable(GL_LIGHT0); // licht nummer eins einschalten
	}


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
	manPac->setZRotation(90);
	//glutPostRedisplay();
}

void moveDown() {
	manPac->moveToNextTile(SOUTH);
	manPac->setZRotation(-90);
	//glutPostRedisplay();
}

void moveLeft() {
	manPac->moveToNextTile(EAST);
	manPac->setZRotation(180);
	//glutPostRedisplay();
}

void moveRight() {
	manPac->moveToNextTile(WEST);
	manPac->setZRotation(0);
	//glutPostRedisplay();
}

