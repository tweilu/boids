#include "Rules.h"
#include "extra.h"

using namespace std;

void Rules::init(int num_boids)
{
    predatorOn = false;
    scatter = false;
    secs = 0;
    for(int i=0; i < num_boids; i++)
    {
        Vector3f p = randPosVec3f();
        Vector3f v = randVelVec3f();
        if (i==0)
        {
            boids.push_back(new Boid(p, v.normalized(), true)); // set first boid to predator
        }
        else
        {
            boids.push_back(new Boid(p, v.normalized(), false));
        }
    }
    N = boids.size();
    predator = boids[0]; // set first boid to predator
}

Vector3f Rules::randPosVec3f() {
    return Vector3f(rand() % (MAX_X * 2) - MAX_X, rand() % (MAX_Y * 2) - MAX_Y, rand() % (MAX_Z * 2) - MAX_Z);
}

Vector3f Rules::randVelVec3f() {
    return Vector3f(((float)rand() / RAND_MAX) - 0.5, ((float)rand() / RAND_MAX) - 0.5, ((float)rand() / RAND_MAX) - 0.5);
}

// Boids try to fly towards the centre of mass of neighbouring boids.
// returns position offset for given boid as a result of rule
Vector3f Rules::center_of_mass(Boid* b)
{
    Vector3f pc = Vector3f::ZERO;
    float count = 0.0;
    int compare;
    if (check_predator(b)) {
        compare = 30;
    } else {
        compare = 15;
    }
    for(int i=0; i<N; i++)
    {
        Boid* bi = boids[i];
        float disp = (b->getPosition() - bi->getPosition()).abs();
        if(disp < compare && disp > 0.0001)
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
        Boid* bi = boids[i];
        if (!check_predator(bi))
        {
            Vector3f disp = b->getPosition() - bi->getPosition();
            if (disp.abs() < 8 && disp.abs() > 0.0001) {
                count += 1.0;
                a += disp;
            }
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
        if (!check_predator(bi))
        {
            float disp = (b->getPosition() - bi->getPosition()).abs();
            if (disp < 10 && disp > 0.0001) {
                count += 1.0;
                m += bi->getVelocity();
            }
        }
    }
    if (count > 0) {
        m = m/(count);
        m -= b->getVelocity();
    }
    return m/10.0;
}

Vector3f Rules::avoid_predator(Boid* b)
{
    Vector3f disp = b->getPosition() - predator->getPosition();
    Vector3f p = Vector3f::ZERO;
    if (disp.abs() < 20) {
        p = disp;
    }
    return p;
}

bool Rules::check_predator(Boid* b)
{
    return predatorOn && b->isPredator();
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
    float wc = 0.4; // weight for center of mass
    float wk = 0.7; // weight for keep distance
    float wm = 0.5; // weight for match velocity
    float wa = 0.3; // weight for avoiding the predator

    for(unsigned i=0; i<N; i++)
    {
        Boid* b = boids.at(i);

        Vector3f oldV = b->getVelocity();
        Vector3f oldP = b->getPosition();
        Vector3f newV = Vector3f::ZERO;
        if(!b->isPredator()) // if it's not the predator
        {
            newV += wk*keep_distance(b);
            newV += wm*match_velocity(b);
            if(predatorOn) // if it's not the predator and the predator is ON
            {
                newV += wa*avoid_predator(b);
            }
            wc = 0.4;
        }  else { // if it is the predator
            if(predatorOn) // and it's ON
            {
               wc = 2.0;
            } else {
                newV += wk*keep_distance(b);
                newV += wm*match_velocity(b);
            }
        }

        if(scatter && secs < 5*N)
        {
            wc = -15*wc;
            secs += 1;
        } else
        {
            scatter = false;
            secs = 0;
        }


        newV += wc*center_of_mass(b);

        b->setVelocity( oldV + newV );

        limit_velocity(b);
        b->bound();
        b->setPosition(oldP + b->getVelocity());
    }
}