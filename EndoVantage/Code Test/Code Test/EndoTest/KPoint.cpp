//========================================================================================================
// KPoint.cpp: implementation for the CKPoint class.
//========================================================================================================
#include "Vector.h"
#include "KPoint.h"
#include <math.h>

CKPoint::CKPoint()
{
    m_dCoords[0]=m_dCoords[1]=m_dCoords[2]=0.0;
}
CKPoint::CKPoint(double x, double y, double z) 
{
    m_dCoords[0] = x; m_dCoords[1]=y; m_dCoords[2] = z; 
}

CKPoint::~CKPoint()
{

}
CKPoint CKPoint::operator =(CKPoint& other)
{
    m_dCoords[0] = other.m_dCoords[0];
    m_dCoords[1] = other.m_dCoords[1];
    m_dCoords[2] = other.m_dCoords[2];
    return *this;
}
CKPoint CKPoint::operator+(CVector& vtVector)
{
    CKPoint ptTemp = *this;
    ptTemp.m_dCoords[0] += vtVector.x;
    ptTemp.m_dCoords[1] += vtVector.y;
    ptTemp.m_dCoords[2] += vtVector.z;
    return ptTemp;
}
CKPoint CKPoint::operator-(CVector& vtVector)
{
    CKPoint ptTemp = *this;
    ptTemp.m_dCoords[0] -= vtVector.x;
    ptTemp.m_dCoords[1] -= vtVector.y;
    ptTemp.m_dCoords[2] -= vtVector.z;
    return ptTemp;
}
CVector CKPoint::operator-(CKPoint& other)
{
    CVector vt;
    vt.SetX( m_dCoords[0]- other.m_dCoords[0] );
    vt.SetY( m_dCoords[1]- other.m_dCoords[1] );
    vt.SetZ( m_dCoords[2]- other.m_dCoords[2] );
    return vt;	
}
double Distance(CKPoint pt1, CKPoint pt2 )
{
    double x1 = pt1.GetX();
    double x2 = pt2.GetX();
    double y1 = pt1.GetY();
    double y2 = pt2.GetY();
    double z1 = pt1.GetZ();
    double z2 = pt2.GetZ();

    return sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1));
}
double TriangleArea(CKPoint& pt1, CKPoint& pt2, CKPoint& pt3)
{
    CVector v1 = pt2-pt1;
    CVector v2 = pt3-pt1;
    CVector v3 = v1.Cross(v2);
    return (v3.Length())*0.5;
}
void CKPoint::RotatePoint(int iAxis,double dDeg)
{
    double dPi = asin(1.0)*2.0;
    double dRad = dDeg*dPi/180.0;
    double c = cos(dRad); 
    double s = sin(dRad);
    double x,y,z;
    switch (iAxis)
	{
	case 0:
	    y = c*m_dCoords[1]-s*m_dCoords[2];
	    z = s*m_dCoords[1]+c*m_dCoords[2];
	    m_dCoords[1] = y; m_dCoords[2] = z;
	    return;
	case 1:
	    x = c*m_dCoords[0]+s*m_dCoords[2];
	    z = -s*m_dCoords[0]+c*m_dCoords[2];
	    m_dCoords[0] = x; m_dCoords[2] = z;
	    return;
	case 2:
	    x = c*m_dCoords[0]-s*m_dCoords[1];
	    y = s*m_dCoords[0]+c*m_dCoords[1];
	    m_dCoords[0] = x; m_dCoords[1] = y;
	    return;
	default:
	    return;
	}
}
