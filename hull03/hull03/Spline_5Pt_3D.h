#pragma once
#include "Point3D.h"
#include "Spline_5Pt_1D.h"

class Spline_5Pt_3D
{
private:
	Spline_5Pt_1D Spline_X;
	Spline_5Pt_1D Spline_Y;
	Spline_5Pt_1D Spline_Z;

public:
	Spline_5Pt_3D();

	Spline_5Pt_3D(Point3D aP0, Point3D aP1, Point3D aP2, Point3D aP3, Point3D aP4);

	~Spline_5Pt_3D();

	double MinValue_X(){ return Spline_X.MinValue(); }
	double MaxValue_X(){ return Spline_X.MaxValue(); }
	double MinValue_Y(){ return Spline_Y.MinValue(); }
	double MaxValue_Y(){ return Spline_Y.MaxValue(); }
	double MinValue_Z(){ return Spline_Z.MinValue(); }
	double MaxValue_Z(){ return Spline_Z.MaxValue(); }

	void Reset();

	void ConstructCoefficients(Point3D aP0, Point3D aP1, Point3D aP2, Point3D aP3, Point3D aP4);

	Point3D P(const double aT);
	bool Defined();
	bool FindFirstX(const double aTarget, double* aT){ return Spline_X.FindFirst(aTarget, aT); }
	bool FindFirstY(const double aTarget, double* aT){ return Spline_Y.FindFirst(aTarget, aT); }
	bool FindFirstZ(const double aTarget, double* aT){ return Spline_Z.FindFirst(aTarget, aT); }

}; // class Spline_5Pt_3D

