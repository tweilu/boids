#include "Rules.h"
#include "extra.h"

using namespace std;

// Boids try to fly towards the centre of mass of neighbouring boids.
// returns position offset for given boid as a result of rule
Vector3f Rules::center_of_mass(Boid* b)
{
    Vector3f pc = -b->getPosition();
    for(unsigned i=0; i<N; i++)
    {
        pc = pc + boids.at(i)->getPosition();
    }
    pc = pc/(N-1);
    return (pc - b->getPosition())/100;
}

// Boids try to keep a small distance away from other objects (including other boids).
// returns position offset for given boid as a result of rule
Vector3f Rules::keep_distance(Boid* b)
{
    Vector3f c = Vector3f::ZERO;
    for(unsigned i=0; i<N; i++)
    {
        Vector3f disp = b->getPosition() - boids.at(i)->getPosition();
        if (disp.abs() < 5)
        {
            c = c - disp;
        }
    }
    return c;
}

// Boids try to match velocity with near boids.
// returns position offset for given boid as a result of rule
Vector3f Rules::match_velocity(Boid* b)
{
    Vector3f pv = -b->getVelocity();
    for(unsigned i=0; i<N; i++)
    {
        pv = pv + boids.at(i)->getVelocity();
    }
    pv = pv/(N-1);
    return (pv-b->getVelocity())/8;
}

Vector3f Rules::bound_position(Boid* b)
{
    float x, y, z;
    Vector3f pos = b->getPosition();
    float val = 2;

    if(pos.x() < MIN_X)
    {
        x = val;
    } else if(pos.x() > MAX_X)
    {
        x = -val;
    }

    if(pos.y() < MIN_Y)
    {
        y = val;
    } else if(pos.y() > MAX_Y)
    {
        y = -val;
    }

    if(pos.z() < MIN_Z)
    {
        z = val;
    } else if(pos.z() > MAX_Z)
    {
        z = -val;
    }
    return Vector3f(x,y,z);
}

void Rules::limit_velocity(Boid* b)
{
    int vlim = 10;
    Vector3f vel = b->getVelocity();
    float speed = vel.abs();
    if(speed > vlim)
    {
        b->setVelocity(vel/speed*vlim);
    }
}

// Applies all rules to all boids
void Rules::update_boids()
{
    Vector3f v1, v2, v3, v4;
    for(unsigned i=0; i<N; i++)
    {
        Boid* b = boids.at(i);
        v1 = center_of_mass(b);
        v2 = keep_distance(b);
        v3 = match_velocity(b);
        v4 = bound_position(b);

        Vector3f oldV = b->getVelocity();
        Vector3f oldP = b->getPosition();
        b->setVelocity(oldV + v1 + v2 + v3 + v4);
        limit_velocity(b);
        b->setPosition(oldP + b->getVelocity());
    }
}