#include "stdafx.h"
#include "Plane3D.h"
#include "HullConst.h"
#include <cmath>

//===============================================================================
Plane3D::Plane3D(Point3D &aPointOnPlane, FreeVector3D &aNormalVector)
{
	SetUsingPtAndNormal(aPointOnPlane, aNormalVector);
} // Plane3D::Plane3D

//===============================================================================
void Plane3D::SetUsingPtAndNormal(Point3D &aPointOnPlane, FreeVector3D &aNormalVector)
{
	fNormal.SetBase(aPointOnPlane);
	fNormal.SetVector(aNormalVector);
} // Plane3D::SetUsingPtAndNormal

//===============================================================================
Plane3D::Plane3D(Point3D &aPt1, Point3D &aPt2, Point3D &aPt3)
{
	SetUsingThreePts(aPt1, aPt2, aPt3);
} // Plane3D::Plane3D

//===============================================================================
void Plane3D::SetUsingThreePts(Point3D &aPt1, Point3D &aPt2, Point3D &aPt3)
{
	FreeVector3D edge12(aPt1, aPt2);
	FreeVector3D edge13(aPt1, aPt3);
	fNormal.SetBase(aPt1);
	fNormal.SetVector(edge12.Cross(edge13));
} // Plane3D::SetUsingThreePts

//===============================================================================
Plane3D::~Plane3D()
{
} // Plane3D::~Plane3D

//===============================================================================
bool Plane3D::IsWellDefined()
{
	return !fNormal.IsApproxZero();
} // Plane3D::IsWellDefined

//===============================================================================
bool Plane3D::PointIsOnPlane(Point3D &aPt)
{
	Normalize();
	FreeVector3D tempVector(fNormal.BasePoint(), aPt);
	double dotProd = tempVector.Dot(fNormal.DirVector());
	return ( abs(dotProd) <=  HullConst::VERYSMALL() );
} // bool Plane3D::PointIsOnPlane

//===============================================================================
bool Plane3D::PointIsExactlyOnPlane(Point3D &aPt)
{
	Normalize();
	FreeVector3D tempVector(fNormal.BasePoint(), aPt);
	double dotProd = tempVector.Dot(fNormal.DirVector());
	return (dotProd == 0.0);
} // Plane3D::PointIsExactlyOnPlane

//===============================================================================
bool Plane3D::PointIsAbovePlane(Point3D &aPt)
{
	Normalize();
	FreeVector3D tempVector(fNormal.BasePoint(), aPt);
	double dotProd = tempVector.Dot(fNormal.DirVector());
	return (dotProd > 0.0);
} // Plane3D::PointIsAbovePlane

//===============================================================================
bool Plane3D::PointIsBelowPlane(Point3D &aPt)
{
	Normalize();
	FreeVector3D tempVector(fNormal.BasePoint(), aPt);
	double dotProd = tempVector.Dot(fNormal.DirVector());
	return (dotProd < 0.0);
} // Plane3D::PointIsBelowPlane

//===============================================================================
void Plane3D::ProjectPointOntoPlane(Point3D* aPt)
{
	Normalize();
	FreeVector3D tempVector(fNormal.BasePoint(), *aPt);
	FreeVector3D normalVector = fNormal.DirVector();
	double distFromPlane = normalVector.Dot(tempVector);
	normalVector.Scale(distFromPlane);
	FreeVector3D dispFromBasePt = tempVector - normalVector;
	aPt->SetX(aPt->X() - dispFromBasePt.X());
	aPt->SetY(aPt->Y() - dispFromBasePt.Y());
	aPt->SetZ(aPt->Z() - dispFromBasePt.Z());
} // Plane3D::ProjectPointOntoPlane

