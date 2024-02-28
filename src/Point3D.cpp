#include "Point3D.h"

Point3D::Point3D()
{
    mX = 0.0;
    mY = 0.0;
    mZ = 0.0;
}
Point3D::Point3D(float inX, float inY, float inZ)
{
    mX = inX;
    mY = inY;
    mZ = inZ;
}
Point3D ::~Point3D()
{
}
float Point3D::x()
{
    return mX;
}
float Point3D::y()
{
    return mY;
}
float Point3D::z()
{
    return mZ;
}

void Point3D::setX(float x)
{
    mX = x;
}
void Point3D::setY(float y)
{
    mY = y;
}
void Point3D::setZ(float z)
{
    mZ = z;
}
//operator Overloading
bool Point3D::operator<(const Point3D& other) const
{
    if (mX < other.mX)
        return true;
    if (mX > other.mX)
        return false;

    if (mY < other.mY)
        return true;
    if (mY > other.mY)
        return false;

    return mZ < other.mZ;
}