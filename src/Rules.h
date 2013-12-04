#ifndef RULES_H
#define RULES_H

#include "vecmath.h"
#include <vector>
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

	// Boids try to fly towards the centre of mass of neighbouring boids.
	// returns position offset for given boid as a result of rule
	Vector3f center_of_mass(Boid* b);

	// Boids try to keep a small distance away from other objects (including other boids).
	// returns position offset for given boid as a result of rule
	Vector3f keep_distance(Boid* b);

	// Boids try to match velocity with near boids.
	// returns position offset for given boid as a result of rule
	Vector3f match_velocity(Boid* b);

	Vector3f bound_position(Boid* b);

	void limit_velocity(Boid* b);

	void update_boids();
};

#endif