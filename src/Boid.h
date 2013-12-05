#ifndef BOID_H
#define BOID_H

#include "vecmath.h"
#include <vector>

class Boid
{
public:
	Boid(Vector3f position, Vector3f velocity, bool predator);
	
	void draw();
	void bound();

	Vector3f getPosition();
	Vector3f getVelocity();
	bool isPredator();

	void setPosition(Vector3f position);
	void setVelocity(Vector3f velocity);

private:
	Vector3f mPosition;
	Vector3f mVelocity;
	float oldX, oldY, oldZ;
	bool mPredator;
};


#endif
