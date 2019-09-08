#include "stdafx.h"
#include "BoundVector3D.h"

//======================================================================================
BoundVector3D::BoundVector3D()
{
	fIsVis = true;
	fIsBoundingBoxSet = false;
	fMinX = fMaxX = fMinY = fMaxY = fMinZ = fMaxZ = 0.0;
	SetToZero();
} // BoundVector3D::BoundVector3D

//======================================================================================
BoundVector3D::BoundVector3D(Point3D &aBasePt, FreeVector3D &aDirVector)
{
	fIsVis = true;
	fIsBoundingBoxSet = false;
	fMinX = fMaxX = fMinY = fMaxY = fMinZ = fMaxZ = 0.0;
	fBasePt.SetToPoint(aBasePt);
	fDirVector.SetToVector(aDirVector);
} // BoundVector3D::BoundVector3D

//======================================================================================
BoundVector3D::BoundVector3D(Point3D &aFromPt, Point3D &aToPt)
{
	fIsVis = true;
	fIsBoundingBoxSet = false;
	fMinX = fMaxX = fMinY = fMaxY = fMinZ = fMaxZ = 0.0;
	fBasePt.SetToPoint(aFromPt);
	fDirVector.SetX(aToPt.X() - aFromPt.X());
	fDirVector.SetY(aToPt.Y() - aFromPt.Y());
	fDirVector.SetZ(aToPt.Z() - aFromPt.Z());
} // BoundVector3D::BoundVector3D

//======================================================================================
BoundVector3D::~BoundVector3D()
{
}// BoundVector3D::~BoundVector3D

//======================================================================================
void BoundVector3D::SetBoundingBox()
{
	double x1, x2, y1, y2, z1, z2;
	x1 = fBasePt.X(); x2 = x1 + fDirVector.X();
	y1 = fBasePt.Y(); y2 = y1 + fDirVector.Y();
	z1 = fBasePt.Z(); z2 = z1 + fDirVector.Z();

	if (x1 > x2){ fMinX = x2; fMaxX = x1; }
	else { fMinX = x1; fMaxX = x2; }

	if (y1 > y2){ fMinY = y2; fMaxY = y1; }
	else { fMinY = y1; fMaxY = y2; }

	if (z1 > z2){ fMinZ = z2; fMaxZ = z1; }
	else { fMinZ = z1; fMaxZ = z2; }
} // BoundVector3D::SetBoundingBox

//======================================================================================
//======================================================================================
//======================================================================================
