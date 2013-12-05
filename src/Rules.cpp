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
        float disp = (b->getPosition() - bi->getPosition()).abs();
        if(disp < 15 && disp > 0.0001)
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
    return pc/10.0;
}

// Boids try to keep a small distance away from other objects (including other boids).
// returns position offset for given boid as a result of rule
Vector3f Rules::keep_distance(Boid* b)
{
    Vector3f a = Vector3f::ZERO;
    float count = 0.0;
    for(int i=0; i < N; i++) {
        Vector3f disp = b->getPosition() - boids[i]->getPosition();
        if (disp.abs() < 8 && disp.abs() > 0.0001) {
            count += 1.0;
            a += disp;
        }
    }
    if (count > 0) {
        a = a/count;
    }
    return a/10.0;
}

// Boids try to match velocity with near boids.
// returns position offset for given boid as a result of rule
Vector3f Rules::match_velocity(Boid* b)
{
    Vector3f m = Vector3f::ZERO;
    float count = 0.0;
    for(int i=0; i < N; i++) {
        Boid* bi = boids[i];
        float disp = (b->getPosition() - bi->getPosition()).abs();
        if (disp < 10 && disp > 0.0001) {
            count += 1.0;
            m += bi->getVelocity();
        }
    }
    if (count > 0) {
        m = m/(count);
        m -= b->getVelocity();
    }
    return m/10.0;
}

void Rules::limit_velocity(Boid* b)
{
    int vlim = 1;
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
    /*for (unsigned i=0; i<N; i++) {
        mCenterOfMass += boids[i]->getPosition();
        mFlockHeading += boids[i]->getVelocity();
    }*/

    float wc = 0.4;
    float wk = 0.7;
    float wm = 0.5;

    if(scatter && secs < 5)
    {
        wc = -10*wc;
        secs += 1;
    } else
    {
        scatter = false;
        secs = 0;
    }

    for(unsigned i=0; i<N; i++)
    {
        Boid* b = boids.at(i);

        Vector3f oldV = b->getVelocity();
        Vector3f oldP = b->getPosition();
        b->setVelocity( 
                        oldV
                        + wc*center_of_mass(b)
                        + wk*keep_distance(b)
                        + wm*match_velocity(b)
                       );
        limit_velocity(b);
        b->bound();
        b->setPosition(oldP + b->getVelocity());
    }
}