#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "vecmath.h"
#include "Boid.h"

using namespace std;

// Globals here.
namespace
{
	vector<Boid*> boids;
	int N = boids.size();
}

// Boids try to fly towards the centre of mass of neighbouring boids.
// returns position offset for given boid as a result of rule
Vector3f rule1(Boid* b)
{
	Vector3f pc = -1*b->getPosition();
	for(unsigned i=0; i<N; i++)
	{
		pc = pc + boids.at(i)->getPosition();
	}
	pc = pc/(N-1);
	return (pc - b->getPosition())/100;
}

// Boids try to keep a small distance away from other objects (including other boids).
// returns position offset for given boid as a result of rule
Vector3f rule2(Boid* b)
{
	Vector3f c = Vector3f::ZERO;
	for(unsigned i=0; i<N; i++)
	{
		Vector3f disp = b->getPosition() - boids.at(i)->getPosition();
		if (disp.abs() < 100)
		{
			c = c - disp;
		}
	}
	return c;
}

// Boids try to match velocity with near boids.
// returns position offset for given boid as a result of rule
Vector3f rule3(Boid* b)
{
	Vector3f pv = -1*b->getVelocity();
	for(unsigned i=0; i<N; i++)
	{
		pv = pv + boids.at(i)->getVelocity();
	}
	pv = pv/(N-1);
	return (pv-b->getVelocity())/8;
}

// Applies all rules to all boids
void updateBoids()
{
	Vector3f v1;
	Vector3f v2;
	Vector3f v3;
	for(unsigned i=0; i<N; i++)
	{
		Boid* b = boids.at(i);
		v1 = rule1(b);
		v2 = rule2(b);
		v3 = rule3(b);

		Vector3f oldV = b->getVelocity();
		Vector3f oldP = b->getPosition();
		b->setVelocity(oldV + v1 + v2 + v3);
		b->setPosition(oldP + b->getVelocity());
	}
}

// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char* argv[] )
{
    cout << "Hello World";
}
