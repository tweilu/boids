#ifndef RULES_H
#define RULES_H

#include "vecmath.h"
#include <vector>
#include "Boid.h"

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

	void update_boids();
};

#endif