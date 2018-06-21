#pragma once

#ifndef _MAN_PAC_H
#define _MAN_PAC_H

#include "object3d.h"
#include "map.h"

class ManPac : public Object3D
{
public:
	ManPac(int x, int y, Map * map);

	void moveToNextTile(Direction dir);

	float movementSpeed = 0.05f;

	bool isMoving = false;

	void moveToNextPos();

	float offset = 0.45f;

	void setPos(float x, float y, float z);

	int score = 0;


protected:

	void createMesh();

private:

	int mouthMover = 15;

	GLfloat manPacRadius = 0.4f;

	Map * map;

	float nextX = 0;
	float nextY = 0;

	float currentX = 0;
	float currentY = 0;

	float oldX = 0;
	float oldY = 0;

	Direction currentDir = NORTH;

	void checkPortal();
	void handlePill();

};


#endif // !_MAN_PAC_H
