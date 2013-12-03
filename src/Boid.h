#ifndef CLOTHSYSTEM_H
#define CLOTHSYSTEM_H

#include "vecmath.h"
#include <vector>


class Boid
{
public:
	Boid(Vector3f position, Vector3f velocity);
	
	void draw();

	Vector3f getPosition();
	Vector3f getVelocity();

	void setPosition(Vector3f position);
	void setVelocity(Vector3f velocity);

private:
	Vector3f mPosition;
	Vector3f mVelocity;
};


#endif
