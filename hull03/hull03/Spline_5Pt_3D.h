#pragma once
#include "HullGeomType.h"
#include "Point3D.h"
#include "Spline_5Pt_1D.h"
#include "TransfMatrix3D.h"

class Spline_5Pt_3D : public HullGeomType
{
private:
	Spline_5Pt_1D fSpline_X;
	Spline_5Pt_1D fSpline_Y;
	Spline_5Pt_1D fSpline_Z;
	Point3D fP0;
	Point3D fP1; 
	Point3D fP2; 
	Point3D fP3;
	Point3D fP4;
protected:
	virtual void SetBoundingBox();
public:
	Spline_5Pt_3D();

	Spline_5Pt_3D(
		Point3D aP0, 
		Point3D aP1, 
		Point3D aP2, 
		Point3D aP3, 
		Point3D aP4);

	~Spline_5Pt_3D();

	virtual void Draw(){ /* TODO*/ }
	virtual void TransformBy(TransfMatrix3D &aM);

	void Reset();
	
	void SetNodePoints(
		Point3D aP0, 
		Point3D aP1, 
		Point3D aP2, 
		Point3D aP3, 
		Point3D aP4);
	
	void ConstructCoefficients();

	Point3D P(const double aT);
	
	bool Defined();
	
	bool FindFirstX(const double aTarget, double* aT)
	{ 
		return fSpline_X.FindFirst(aTarget, aT); 
	}

	bool FindFirstY(const double aTarget, double* aT)
	{
		return fSpline_Y.FindFirst(aTarget, aT); 
	}

	bool FindFirstZ(const double aTarget, double* aT)
	{
		return fSpline_Z.FindFirst(aTarget, aT);
	}

}; // class Spline_5Pt_3D

