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



    glBegin(GL_LINES);
    glVertex3d(mPosition[0], mPosition[1], mPosition[2]);
    glVertex3d(mPosition[0] + mVelocity[0], mPosition[1] + mVelocity[1], mPosition[2] + mVelocity[2]);
    glVertex3d(mPosition[0], mPosition[1], mPosition[2]);
    glVertex3d(mPosition[0] - mVelocity[0], mPosition[1] - mVelocity[1], mPosition[2] - mVelocity[2]);
    Vector3f up = -Vector3f::cross(mVelocity, Vector3f::cross(mVelocity, Vector3f::UP) ).normalized();
    glVertex3d(mPosition[0], mPosition[1], mPosition[2]);
    glVertex3d(mPosition[0] + up[0], mPosition[1] + up[1], mPosition[2] + up[2]);
    glEnd();
}