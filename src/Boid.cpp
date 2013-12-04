#include "Boid.h"
#include <iostream>

using namespace std;

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

void Boid::draw(int i)
{
	// draw the boid based on position
	// cout << "drawing boid..." << endl;
	if (i != 1)
	{
		glPushMatrix();
		glTranslatef(mPosition[0],mPosition[1],mPosition[2]);
		glutSolidSphere(0.2f,20.0f,20.0f);
		glPopMatrix();
		glBegin(GL_LINES);
		glVertex3d(mPosition[0], mPosition[1], mPosition[2]);
		glVertex3d(mPosition[0] + mVelocity[0], mPosition[1] + mVelocity[1], mPosition[2] + mVelocity[2]);
		glEnd(); 
	}
}