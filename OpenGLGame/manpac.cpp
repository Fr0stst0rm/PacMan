#include "manpac.h"

ManPac::ManPac(int x, int y, Map * map) : map(map)
{
	currentX = x;
	currentY = y;

	nextX = x;
	nextY = y;

	setPos(x,y,map->getZoom());
}

void ManPac::moveToNextTile(Direction dir)
{

	if (map->checkNextDir(currentX, currentY, dir)) {
		if (!isMoving) {
			switch (dir) {
			case NORTH:
				nextY++;
				break;
			case EAST:
				nextX++;
				break;
			case SOUTH:
				nextY--;
				break;
			case WEST:
				nextX--;
				break;
			}
			isMoving = true;
		}
	}
}

void ManPac::createMesh()
{
	glColor3f(1.0f, 1.0f, 0.0f);

	float zCoord = 1.0f;

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, zCoord); // center point
	int numberOfSegments = 100;
	GLfloat angle;

	if (mouthMover >= 0) {
		for (int i = 0; i <= numberOfSegments - mouthMover; i++) {

			angle = i * 2.0f * M_PI / numberOfSegments;
			glVertex2f(cos(angle) * manPacRadius, sin(angle) * manPacRadius);
		}

		if (mouthMover == 0) {
			mouthMover = -15;
		}
		else {
			mouthMover--;
		}

	}
	else {
		for (int i = 0; i <= numberOfSegments + mouthMover; i++) {

			angle = i * 2.0f * M_PI / numberOfSegments;
			glVertex2f(cos(angle) * manPacRadius, sin(angle) * manPacRadius);
		}

		if (mouthMover == -1) {
			mouthMover = 15;
		}
		else {
			mouthMover++;
		}
	}

	glEnd();
}

void ManPac::setPos(float x, float y, float z)
{
	Object3D::setPos(-(map->getWidth() / 2.0f) + (float)(x) * 1.0f + offset, -(map->getHeight() / 2.0f) + (float)(y) * 1.0f + offset, z);
}

void ManPac::moveToNextPos()
{
	if (isMoving) {
		if (abs(currentX) < abs(nextX)) {
			currentX += movementSpeed;
		}
		else {
			currentX = nextX;
		}

		if (abs(currentY) < abs(nextY)) {
			currentY += movementSpeed;
		}
		else {
			currentY = nextY;
		}

		setPos(currentX, currentY, map->getZoom());

		if ((currentX == nextX) && (currentY == nextY)) {
			std::cout << "X:" << currentX << " Y:" << currentY;
			isMoving = false;
		}
	}
}
