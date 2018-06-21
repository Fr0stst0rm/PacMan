#include "manpac.h"

ManPac::ManPac(int x, int y, Map * map) : map(map)
{
	currentX = x;
	currentY = y;

	nextX = x;
	nextY = y;

	setPos(- (map->getWidth()/ 6.0f + (float)(x) * 1.5f), - (map->getHeight() / 7.0f + (float)(y) * 1.5f), map->getZoom());
}

void ManPac::moveToNextTile(Direction dir)
{

	if (map->checkNextDir(currentX, currentY, dir)) {
		if (!isMoving) {
			switch (dir) {
			case NORTH:
				nextX++;
				break;
			case EAST:
				nextY++;
				break;
			case SOUTH:
				nextX--;
				break;
			case WEST:
				nextY--;
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

void ManPac::moveToNextPos()
{
	if (isMoving) {
		if (abs(currentX) < abs(nextX)) {
			currentX += movementSpeed;
		}

		if (abs(currentY) < abs(nextY)) {
			currentY += movementSpeed;
		}

		if ((currentX == nextX) && (currentY == nextY)) {
			std::cout << "X:" << currentX << " Y:" << currentY;
			isMoving = false;
		}
	}
}
