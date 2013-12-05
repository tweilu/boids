#include "Boid.h"
#include "extra.h"

#define MAX_X 30
#define MIN_X -30
#define MAX_Y 30
#define MIN_Y -30
#define MAX_Z 30
#define MIN_Z -30

Boid::Boid(Vector3f position, Vector3f velocity)
{
    mPosition = position;
    mVelocity = velocity;
    oldX = 0.0;
    oldY = 0.0;
    oldZ = 1.0;
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

void Boid::draw()
{
    // draw based on position
    glPushMatrix();
    glTranslatef(mPosition.x(), mPosition.y(), mPosition.z());
    //orient based on velocity vector
    float magnitude = mVelocity.abs();
    if (magnitude > 0.0)
    {
        float xNorm = mVelocity.x() / magnitude;
        float yNorm = mVelocity.y() / magnitude;
        float zNorm = mVelocity.z() / magnitude;
        glRotatef(acos(oldX * xNorm + oldY * yNorm + oldZ * zNorm) * 57.2957795, oldY * zNorm - oldZ * yNorm, oldZ * xNorm - oldX * zNorm, oldX * yNorm - oldY * xNorm);
    }
    glutWireCone(0.25, 0.5, 50, 50);
    glPopMatrix();
}

void Boid::bound()
{
    float x = 0;
    float y = 0;
    float z = 0;

    float val = 0.03;

    if (mPosition.x() > MAX_X) {
        x -= val;
    }
    if (mPosition.x() < MIN_X) {
        x += val;
    }
    if (mPosition.y() > MAX_Y) {
        y -= val;
    }
    if (mPosition.y() < MIN_Y) {
        y += val;
    }
    if (mPosition.z() > MAX_Z) {
        z -= val;
    }
    if (mPosition.z() < MIN_Z) {
        z += val;
    }
    mVelocity += Vector3f(x,y,z);
}