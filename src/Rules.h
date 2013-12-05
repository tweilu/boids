#ifndef RULES_H
#define RULES_H

#include "vecmath.h"
#include <vector>
#include <cstdlib>
#include "Boid.h"

#define MAX_X 30
#define MIN_X -30
#define MAX_Y 30
#define MIN_Y -30
#define MAX_Z 30
#define MIN_Z -30

struct Rules
{
	std::vector<Boid*> boids;
	int N;

	void init(int num_boids);

	Vector3f randPosVec3f();
	Vector3f randVelVec3f();

	// Boids try to fly towards the centre of mass of neighbouring boids.
	// returns position offset for given boid as a result of rule
	Vector3f center_of_mass(Boid* b);

	// Boids try to keep a small distance away from other objects (including other boids).
	// returns position offset for given boid as a result of rule
	Vector3f keep_distance(Boid* b);

	// Boids try to match velocity with near boids.
	// returns position offset for given boid as a result of rule
	Vector3f match_velocity(Boid* b);

	Vector3f avoid_predator(Boid* b);

	bool check_predator(Boid* b);

	void limit_velocity(Boid* b);

	void update_boids();

	bool scatter;

	bool predatorOn;

private:
	Vector3f mCenterOfMass;
	Vector3f mFlockHeading;
	Boid* predator;
	int secs;
};

#endif