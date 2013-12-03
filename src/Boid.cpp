#include "Boid.h"

Boid::Boid(Vector3f position, Vector3f velocity)
{
	mPosition = position;
	mVelocity = velocity;
}

Vector3f Boid::getPosition()
{
	return mPosition;
}
Vector3f Boid::getVelocity()
{
	return mVelocity;
}

void Boid::setPosition(Vector3f position)
{
	mPosition = position;
}
void Boid::setVelocity(Vector3f velocity)
{
	mVelocity = velocity;
}

void draw()
{
	// draw the boid based on position
}