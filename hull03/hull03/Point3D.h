#pragma once
#include "HullGeomType.h"
#include "TransfMatrix3D.h"

class Point3D :	public HullGeomType
{
private:
	double fCoord[3];

protected:
	virtual void SetBoundingBox() const;
public:
	Point3D();
	Point3D(const double aX, const double aY, const double aZ);
	Point3D(const Point3D & aSource);
	~Point3D();

	virtual void Draw(){ /* TODO*/ }
	double X() const { return fCoord[0]; }
	double Y() const { return fCoord[1]; }
	double Z() const { return fCoord[2]; }

	void SetX(const double aX)
	{
		fCoord[0] = aX;
		SetBoundingBox(); 
	}

	void SetY(const double aY)
	{
		fCoord[1] = aY; 
		SetBoundingBox(); 
	}

	void SetZ(const double aZ)
	{
		fCoord[2] = aZ;
		SetBoundingBox();
	}
	
	void SetToZero()
	{
		fCoord[0] = fCoord[1] = fCoord[2] = 0.0; 
		SetBoundingBox(); 
	}
	
	void SetToPoint(const Point3D &aSource);
	virtual void TransformBy(const TransfMatrix3D &aM);

}; // class Point3D

