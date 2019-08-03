//========================================================================================================
// Vector.h: interface for the CVector class.
//========================================================================================================
#ifndef __VECTOR_HH
#define __VECTOR_HH

#include "KPoint.h"
class CVector  
{
 public:
    CVector();
    CVector(double x, double y, double z);
    virtual ~CVector();
    CVector& operator+(CVector& otherVector);
    CVector& operator-(CVector& otherVector);
    CVector& operator*(double dFactor);
    friend double DotProduct(CVector& vector1, CVector& vector2);
    friend CVector CrossProduct(CVector& vector1, CVector& vector2);
    double Dot(CVector& otherVector);
    CVector Cross(CVector& otherVector);
    void SetX(double dX) {x = dX;}
    void SetY(double dY) {y = dY;}
    void SetZ(double dZ) {z = dZ;}
    double GetX() { return x;}
    double GetY() { return y;}
    double GetZ() { return z; }
    double Length();
    void Normalize();
    // rotation about z-axis
    void Rotate(double dAngle);
    friend class CKPoint;
 private:
    double x,y,z;
};

#endif 
