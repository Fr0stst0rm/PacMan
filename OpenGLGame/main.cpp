
#include <Windows.h>
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "manpac.h"
#include "map.h"
#include "wall.h"
#include "level1.h"
#include "level2.h"
#include "pickupcube.h"
#include "defines.h"

#define PLAYTHEME true

void endAnimation();
void endingGame();
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

bool level2 = false;
bool ende = false;

int zoom = -27;

Map * map = NULL;
ManPac * manPac = NULL;

int const win_width = 1280;
int const win_height = 720;

void resize(int width, int height)
{
	// prevent division by zero
	if (height == 0) { height = 1; }

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / (float)height, 0.1f, 500.0f);
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
		if (ende) {
			exitMain();
		}
		
		endingGame();

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

			zoom = -27;

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f, (float)win_width / (float)win_height, 0.1f, 500.0f);
			glMatrixMode(GL_MODELVIEW);
			map->setPos(-Level1::width / 2.0f + 0.5f, -Level1::height / 2.0f + 0.5f, zoom);
			manPac->resetPos();
		}
		else {
			MODE_2D = true;

			zoom = -250;

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(5.0f, (float)win_width / (float)win_height, 0.1f, 500.0f);
			glMatrixMode(GL_MODELVIEW);

			map->setPos(-Level1::width / 2.0f + 0.5f, -Level1::height / 2.0f + 0.5f, zoom);
			manPac->resetPos();
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

	//eyes
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

	//licht
	GLfloat light_position[] = { lightx, lighty, lightz, 0.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	glEnable(GL_LIGHTING); //light aktivieren
	glEnable(GL_LIGHT0); // licht nummer eins einschalten

	//lichtberechnungen
	lightx = cos(lightAngle) * 5;
	lightz = sin(lightAngle) * 5;

	lightAngle += 0.05;

	if (lightAngle >= 18.0f) {
		glutDestroyWindow(window);
		exitMain();
	}

}

void display()
{
	if (map->finished() && !level2){
		level2 = true;
		map->loadMap(Level2::width, Level2::height, (char *)Level2::map);
	}
	else if (map->finished() && level2 && !ende) {
		endingGame();
	}

	if (!ende) { manPac->moveToNextPos(); }

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (ende) {
		endAnimation();
	}
	else {
		map->draw();
		manPac->draw();
		
	}


	//gluOrtho2D(0.0, win_width, 0.0, win_height);
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glColor3f(1.0f, 0.0f, 0.0f);//needs to be called before RasterPos
	//glRasterPos2i(10, 10);
	//std::string s = "Some text";
	//void * font = GLUT_BITMAP_9_BY_15;

	//for (std::string::iterator i = s.begin(); i != s.end(); ++i)
	//{
	//	char c = *i;
	//	//this does nothing, color is fixed for Bitmaps when calling glRasterPos
	//	//glColor3f(1.0, 0.0, 1.0); 
	//	glutBitmapCharacter(font, c);
	//}
	//glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();

	glutSwapBuffers();
}

void init(int width, int height)
{

	if (!ende) {
		//GLfloat mat_diffuse[] = { 1.0f,1.0f,0.0f }; //material (gelb)
		//GLfloat mat_shininess[] = { 1.0f };
		//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse);
		//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		//GLfloat light_position[] = { 10.0f, 10.0f, 0.1f, 0.0f };
		//GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };
		//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

		//glEnable(GL_LIGHTING); //light aktivieren
		//glEnable(GL_LIGHT0); // licht nummer eins einschalten

	}


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	resize(width, height);

	map = new Map();
	map->loadMap(Level1::width, Level1::height, (char *)Level1::map);

	//Set map to center of screen
	map->setPos(-Level1::width / 2.0f + 0.5f, -Level1::height / 2.0f + 0.5f, zoom);

	manPac = new ManPac(9,9,map);
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
		PlaySound(TEXT("manpac.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("MacPan");
	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);
	glutKeyboardFunc(&keyPressed);
	glutSpecialFunc(&specialKeyPressed);
	init(win_height, win_width);
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
		exit(0);
}

void moveUp() {
	manPac->moveToNextTile(NORTH);
	manPac->setZRotation(90);
}

void moveDown() {
	manPac->moveToNextTile(SOUTH);
	manPac->setZRotation(-90);
}

void moveLeft() {
	manPac->moveToNextTile(EAST);
	manPac->setZRotation(180);
}

void moveRight() {
	manPac->moveToNextTile(WEST);
	manPac->setZRotation(0);
}

void endingGame() {
	PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
	ende = true;

	MODE_2D = false;

	zoom = -27;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)win_width / (float)win_height, 0.1f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	map->setPos(-Level1::width / 2.0f + 0.5f, -Level1::height / 2.0f + 0.5f, zoom);
	manPac->resetPos();
}
