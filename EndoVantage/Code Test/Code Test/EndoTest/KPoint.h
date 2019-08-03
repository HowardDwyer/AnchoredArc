//========================================================================================================
// KPoint.h: interface for the CKPoint class.
//========================================================================================================
#ifndef __POINT_HH
#define __POINT_HH

class CVector;
class CKPoint  
{
 public:
    CKPoint();
    CKPoint(double x, double y, double z);
    virtual ~CKPoint();
    double GetX() { return m_dCoords[0]; }
    double GetY() { return m_dCoords[1]; }
    double GetZ() { return m_dCoords[2]; }
    void SetX(double dX) { m_dCoords[0] = dX; }
    void SetY(double dY) { m_dCoords[1] = dY; }
    void SetZ(double dZ) { m_dCoords[2] = dZ; }
    CKPoint operator=(CKPoint& other);
    CKPoint operator+(CVector& vtVector);
    CKPoint operator-(CVector& vtVector);
    friend class CVector;
    CVector operator-(CKPoint& other);

    // utilities
    friend double Distance(CKPoint pt1, CKPoint pt2);
    friend double TriangleArea(CKPoint& pt1,CKPoint& pt2,CKPoint& pt3);
    // rotation
    // int: 0, about x; 1, about y; 2, about z
    void RotatePoint(int,double);
 private:
    double m_dCoords[3];
};

#endif
