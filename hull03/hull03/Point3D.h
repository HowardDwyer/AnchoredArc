#pragma once
#include "HullGeomType.h"
class Point3D :	public HullGeomType
{
private:
	double fCoord[3];

protected:
	virtual void SetBoundingBox();
public:
	Point3D();
	Point3D(const double aX, const double aY, const double aZ);
	Point3D(const Point3D & aSource);
	~Point3D();

	virtual void Draw();
	double X(){ return fCoord[0]; }
	double Y(){ return fCoord[1]; }
	double Z(){ return fCoord[2]; }

	double SetX(const double aX){ fCoord[0] = aX; SetBoundingBox(); }
	double SetY(const double aY){ fCoord[1] = aY; SetBoundingBox(); }
	double SetZ(const double aZ){ fCoord[2] = aZ; SetBoundingBox(); }
}; // class Point3D

