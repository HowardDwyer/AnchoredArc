#include "stdafx.h"
#include "Spline_5Pt_3D.h"


//===========================================================================================
Spline_5Pt_3D::Spline_5Pt_3D() 
	: HullGeomType()
{
} // Spline_5Pt_3D::Spline_5Pt_3D

//===========================================================================================
Spline_5Pt_3D::Spline_5Pt_3D(
		Point3D aP0, 
		Point3D aP1, 
		Point3D aP2,
		Point3D aP3, 
		Point3D aP4) 
	: HullGeomType()
{
	SetNodePoints(aP0, aP1, aP2, aP3, aP4);
} // Spline_5Pt_3D::Spline_5Pt_3D


//===========================================================================================
Spline_5Pt_3D::~Spline_5Pt_3D()
{
} // Spline_5Pt_3D::~Spline_5Pt_3D

//===========================================================================================
void Spline_5Pt_3D::SetNodePoints(
	Point3D aP0, 
	Point3D aP1, 
	Point3D aP2, 
	Point3D aP3, 
	Point3D aP4)
{
	fP0.SetToPoint(aP0);
	fP1.SetToPoint(aP1);
	fP2.SetToPoint(aP2);
	fP3.SetToPoint(aP3);
	fP4.SetToPoint(aP4);
	ConstructCoefficients();
} // Spline_5Pt_3D::SetNodePoints

//===========================================================================================
void Spline_5Pt_3D::ConstructCoefficients()
{
	fSpline_X.ConstructCoefficients(fP0.X(), fP1.X(), fP2.X(), fP3.X(), fP4.X());
	fSpline_Y.ConstructCoefficients(fP0.Y(), fP1.Y(), fP2.Y(), fP3.Y(), fP4.Y());
	fSpline_Z.ConstructCoefficients(fP0.Z(), fP1.Z(), fP2.Z(), fP3.Z(), fP4.Z());
	fIsBoundingBoxSet = false;
	fMinX = fMaxX = fMinY = fMaxY = fMinZ = fMaxZ = 0.0;
} // Spline_5Pt_3D::ConstructCoefficients

//===========================================================================================
void Spline_5Pt_3D::Reset()
{
	fSpline_X.Reset();
	fSpline_Y.Reset();
	fSpline_Z.Reset();
	fIsBoundingBoxSet = false;
	fMinX = fMaxX = fMinY = fMaxY = fMinZ = fMaxZ = 0.0;
} // Spline_5Pt_3D::Reset

//===========================================================================================
Point3D Spline_5Pt_3D::P(const double aT)
{
	return Point3D(fSpline_X.P(aT), fSpline_Y.P(aT), fSpline_Z.P(aT));
} // Spline_5Pt_3D::P

//===========================================================================================
bool Spline_5Pt_3D::Defined()
{
	return fSpline_X.Defined() && fSpline_Y.Defined() && fSpline_Z.Defined();
} // Spline_5Pt_3D::Defined

//===========================================================================================
void Spline_5Pt_3D::SetBoundingBox()
{
	fMinX = fSpline_X.MinValue();
	fMaxX = fSpline_X.MaxValue();
	fMinY = fSpline_Y.MinValue();
	fMaxY = fSpline_Y.MaxValue();
	fMinZ = fSpline_Z.MinValue();
	fMaxZ = fSpline_Z.MaxValue();
	fIsBoundingBoxSet = true;
}// Spline_5Pt_3D::SetBoundingBox

//===========================================================================================
void Spline_5Pt_3D::TransformBy(TransfMatrix3D &aM)
{
	fP0.TransformBy(aM);
	fP1.TransformBy(aM);
	fP2.TransformBy(aM);
	fP3.TransformBy(aM);
	fP4.TransformBy(aM);
	ConstructCoefficients();
} // Spline_5Pt_3D::TransformBy
//===========================================================================================
//===========================================================================================
//===========================================================================================
//===========================================================================================
