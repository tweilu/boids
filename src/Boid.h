#ifndef BOID_H
#define BOID_H

#ifdef __APPLE__
# include <GLUT/glut.h>
#else
# include <GL/glut.h>
#endif

#include "vecmath.h"
#include <vector>


class Boid
{
public:
	Boid(Vector3f position, Vector3f velocity);
	
	void draw(int i);

	Vector3f getPosition();
	Vector3f getVelocity();

	void setPosition(Vector3f position);
	void setVelocity(Vector3f velocity);

private:
	Vector3f mPosition;
	Vector3f mVelocity;
};


#endif
