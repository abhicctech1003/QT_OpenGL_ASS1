#include "Triangle.h"

using namespace std;

Triangle::Triangle()
{
}

Triangle ::~Triangle()
{
}

const int Triangle::v1() const
{
    return mV1;
}

const int Triangle::v2() const
{
    return mV2;
}

const int Triangle::v3() const
{
    return mV3;
}
const int Triangle::normalOfTriangle() const
{
    return mNormal;
}

Triangle::Triangle(int v1, int v2, int v3, int Normal)
{
    mV1 = v1;
    mV2 = v2;
    mV3 = v3;
    mNormal = Normal;
}