#include "stdafx.h"
#include "Spline_5Pt_3D.h"


//===========================================================================================
Spline_5Pt_3D::Spline_5Pt_3D()
{
} // Spline_5Pt_3D::Spline_5Pt_3D

//===========================================================================================
Spline_5Pt_3D::Spline_5Pt_3D(
		Point3D aP0, 
		Point3D aP1, 
		Point3D aP2,
		Point3D aP3, 
		Point3D aP4)
{
	ConstructCoefficients(aP0, aP1, aP2, aP3, aP4);
} // Spline_5Pt_3D::Spline_5Pt_3D


//===========================================================================================
Spline_5Pt_3D::~Spline_5Pt_3D()
{
} // Spline_5Pt_3D::~Spline_5Pt_3D

//===========================================================================================
void Spline_5Pt_3D::ConstructCoefficients(
	Point3D aP0,
	Point3D aP1,
	Point3D aP2,
	Point3D aP3,
	Point3D aP4)
{
	Spline_X.ConstructCoefficients(aP0.X(), aP1.X(), aP2.X(), aP3.X(), aP4.X());
	Spline_Y.ConstructCoefficients(aP0.Y(), aP1.Y(), aP2.Y(), aP3.Y(), aP4.Y());
	Spline_Z.ConstructCoefficients(aP0.Z(), aP1.Z(), aP2.Z(), aP3.Z(), aP4.Z());
} // Spline_5Pt_3D::ConstructCoefficients

//===========================================================================================
void Spline_5Pt_3D::Reset()
{
	Spline_X.Reset();
	Spline_Y.Reset();
	Spline_Z.Reset();
} // Spline_5Pt_3D::Reset

//===========================================================================================
Point3D Spline_5Pt_3D::P(const double aT)
{
	return Point3D(Spline_X.P(aT), Spline_Y.P(aT), Spline_Z.P(aT));
} // Spline_5Pt_3D::P

//===========================================================================================
bool Spline_5Pt_3D::Defined()
{
	return Spline_X.Defined() && Spline_Y.Defined() && Spline_Z.Defined();
} // Spline_5Pt_3D::Defined

//===========================================================================================
//===========================================================================================
//===========================================================================================
//===========================================================================================
//===========================================================================================
//===========================================================================================
