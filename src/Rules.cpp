#include "Rules.h"
#include "extra.h"

using namespace std;


// Boids try to fly towards the centre of mass of neighbouring boids.
// returns position offset for given boid as a result of rule
Vector3f Rules::center_of_mass(Boid* b)
{
    Vector3f pc = Vector3f::ZERO;
    float count = 0.0;
    for(int i=0; i<N; i++)
    {
        Boid* bi = boids[i];
        Vector3f disp = b->getPosition() - bi->getPosition();
        if(disp.abs() < 10 && disp.abs() > 0.0001)
        {
            count += 1.0;
            pc += bi->getPosition();
        }
    } 
    if (count > 0)
    {
        pc = pc/count;
        pc -= b->getPosition();
    }
    return pc;
}

// Boids try to keep a small distance away from other objects (including other boids).
// returns position offset for given boid as a result of rule
Vector3f Rules::keep_distance(Boid* b)
{
    Vector3f a = Vector3f::ZERO;
    float count = 0.0;
    for(int i=0; i < N; i++) {
        Vector3f disp = b->getPosition() - boids[i]->getPosition();
        if (disp.abs() < 10 && disp.abs() > 0.0001) {
            count += 1.0;
            a += disp;
        }
    }
    if (count > 0) {
        a = a/count;
    }
    return a;
}

// Boids try to match velocity with near boids.
// returns position offset for given boid as a result of rule
Vector3f Rules::match_velocity(Boid* b)
{
    Vector3f m = Vector3f::ZERO;
    float count = 0.0;
    for(int i=0; i < N; i++) {
        Boid* bi = boids[i];
        Vector3f disp = b->getPosition() - bi->getPosition();
        if (disp.abs() < 10 && disp.abs() > 0.0001) {
            count += 1.0;
            m += bi->getVelocity();
        }
    }
    if (count > 0) {
        m = m/(count);
        m -= b->getVelocity();
    }
    return m;
}

void Rules::limit_velocity(Boid* b)
{
    int vlim = 3;
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
    //mCenterOfMass = Vector3f::ZERO;
    //mFlockHeading = Vector3f::ZERO;
    /*for(unsigned i=0; i<N; i++)
    {
        Boid* b = boids.at(i);
        b->update(boids);
    }*/
    /*for (unsigned i=0; i<N; i++) {
        mCenterOfMass += boids[i]->getPosition();
        mFlockHeading += boids[i]->getVelocity();
    }*/

    for(unsigned i=0; i<N; i++)
    {
        Boid* b = boids.at(i);

        Vector3f oldV = b->getVelocity();
        Vector3f oldP = b->getPosition();
        b->setVelocity( 
                        oldV
                        + 0.5*center_of_mass(b)
                        + 0.5*keep_distance(b)
                        + 0.5*match_velocity(b)
                       );
        limit_velocity(b);
        b->bound();
        b->setPosition(oldP + b->getVelocity());
    }
}