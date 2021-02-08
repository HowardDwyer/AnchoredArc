//========================================================================================================
// Vector.cpp: implementation for the CVector class.
//========================================================================================================
#include "Vector.h"
#include <math.h>

CVector::CVector()
{
    x = y = z = 0.0;
}
CVector::CVector(double dX, double dY, double dZ) : x(dX), y(dY), z(dZ)
{
}

CVector::~CVector()
{

}
double DotProduct(CVector& vector1, CVector& vector2)
{
    return vector1.x*vector2.x
	+vector1.y*vector2.y
	+vector1.z*vector2.z;
}
CVector CrossProduct(CVector& vector1, CVector& vector2)
{
    CVector result;
    result.x = vector1.y*vector2.z-vector2.y*vector1.z;
    result.y = -(vector1.x*vector2.z-vector1.z*vector2.x);
    result.z = vector1.x*vector2.y-vector1.y*vector2.x;
    return result;
}
void CVector::Normalize()
{
    double dLength = Length();
    if ( dLength > 0.0 )
	{
	    x /= dLength;
	    y /= dLength;
	    z /= dLength;
	}
}
CVector& CVector::operator+(CVector& otherVector)
{
    x+=otherVector.x;
    y+=otherVector.y;
    z+=otherVector.z;
    return *this;
}
CVector& CVector::operator-(CVector& otherVector)
{
    x-=otherVector.x;
    y-=otherVector.y;
    z-=otherVector.z;
    return *this;
}
CVector& CVector::operator*(double dFactor)
{
    x*=dFactor;
    y*=dFactor;
    z*=dFactor;
    return *this;
}
double CVector::Length()
{
    return sqrt( x*x+y*y+z*z);
}
double CVector::Dot(CVector& otherVector)
{
    return x*otherVector.x
	+y*otherVector.y
	+z*otherVector.z;
}

CVector CVector::Cross(CVector& otherVector)
{
    CVector result;
    result.x = y*otherVector.z - z*otherVector.y;
    result.y = -x*otherVector.z + z*otherVector.x;
    result.z = x*otherVector.y - y*otherVector.x;
    return result;
}
// rotation about z-axis
void CVector::Rotate(double dAngle)
{
    double dSin = sin(dAngle);
    double dCos = cos(dAngle);

    double dNewX = dCos*x - dSin*y;
    double dNewY = dSin*x + dCos*y;
    x = dNewX; y = dNewY;
}
