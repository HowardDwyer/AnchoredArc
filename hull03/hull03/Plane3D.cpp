#include "stdafx.h"
#include "Plane3D.h"
#include "FreeVector3D.h"
#include "HullConst.h"
#include <cmath>

//===============================================================================
Plane3D::Plane3D(const Point3D &aPointOnPlane, const FreeVector3D &aNormalVector)
{
	SetUsingPtAndNormal(aPointOnPlane, aNormalVector);
} // Plane3D::Plane3D

//===============================================================================
void Plane3D::SetUsingPtAndNormal(const Point3D &aPointOnPlane, const FreeVector3D &aNormalVector)
{
	fNormal.SetBase(aPointOnPlane);
	fNormal.SetVector(aNormalVector);
} // Plane3D::SetUsingPtAndNormal

//===============================================================================
Plane3D::Plane3D(
	const Point3D &aPt1,
	const Point3D &aPt2,
	const Point3D &aPt3)
{
	SetUsingThreePts(aPt1, aPt2, aPt3);
} // Plane3D::Plane3D

//===============================================================================
void Plane3D::SetUsingThreePts(
	const Point3D &aPt1,
	const Point3D &aPt2,
	const Point3D &aPt3)
{
	const FreeVector3D edge12(aPt1, aPt2);
	const FreeVector3D edge13(aPt1, aPt3);
	fNormal.SetBase(aPt1);
	fNormal.SetVector(edge12.Cross(edge13));
} // Plane3D::SetUsingThreePts

//===============================================================================
Plane3D::~Plane3D()
{
} // Plane3D::~Plane3D

//===============================================================================
bool Plane3D::IsWellDefined() const
{
	return !fNormal.IsApproxZero();
} // Plane3D::IsWellDefined

//===============================================================================
bool Plane3D::PointIsOnPlane(const Point3D &aPt) const
{
	BoundVector3D unitNormal = fNormal;
	unitNormal.Normalize();
	const FreeVector3D tempVector(unitNormal.StartPoint(), aPt);
	const double dotProd = tempVector.Dot(unitNormal.DirVector());
	return ( abs(dotProd) <=  HullConst::VERYSMALL() );
} // bool Plane3D::PointIsOnPlane

//===============================================================================
bool Plane3D::PointIsExactlyOnPlane(const Point3D &aPt) const
{
	BoundVector3D unitNormal = fNormal;
	unitNormal.Normalize();
	const FreeVector3D tempVector(unitNormal.StartPoint(), aPt);
	const double dotProd = tempVector.Dot(unitNormal.DirVector());
	return (dotProd == 0.0);
} // Plane3D::PointIsExactlyOnPlane

//===============================================================================
bool Plane3D::PointIsAbovePlane(const Point3D &aPt) const
{
	BoundVector3D unitNormal = fNormal;
	unitNormal.Normalize();
	const FreeVector3D tempVector(unitNormal.StartPoint(), aPt);
	const double dotProd = tempVector.Dot(unitNormal.DirVector());
	return (dotProd > 0.0);
} // Plane3D::PointIsAbovePlane

//===============================================================================
bool Plane3D::PointIsBelowPlane(const Point3D &aPt) const
{
	BoundVector3D unitNormal = fNormal;
	unitNormal.Normalize();
	const FreeVector3D tempVector(unitNormal.StartPoint(), aPt);
	const double dotProd = tempVector.Dot(unitNormal.DirVector());
	return (dotProd < 0.0);
} // Plane3D::PointIsBelowPlane

//===============================================================================
void Plane3D::ProjectPointOntoPlane(Point3D* aPt) const
{
	BoundVector3D unitNormal = fNormal;
	unitNormal.Normalize();
	const FreeVector3D tempVector(unitNormal.StartPoint(), *aPt);
	FreeVector3D normalVector = unitNormal.DirVector();
	const double distFromPlane = normalVector.Dot(tempVector);
	normalVector.Scale(distFromPlane);
	const FreeVector3D dispFromBasePt = tempVector - normalVector;
	aPt->SetX(aPt->X() - dispFromBasePt.X());
	aPt->SetY(aPt->Y() - dispFromBasePt.Y());
	aPt->SetZ(aPt->Z() - dispFromBasePt.Z());
} // Plane3D::ProjectPointOntoPlane

bool Plane3D::PointsDefinePlane(const Point3D& p1, const Point3D& p2, const Point3D& p3)
{
	bool result = true;
	if ((p1 == p2)||(p1 == p3)||(p2 == p3)){
		result = false;
	} // if the points are not distinct
	else {
		const Plane3D tempPlane(p1, p2, p3);
		result = tempPlane.IsWellDefined();
	} // if the points are distinct
	return result;
} // Plane3D::DefinePlane
