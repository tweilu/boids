#include "Boid.h"
#include "extra.h"

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