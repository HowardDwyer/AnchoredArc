#include "stdafx.h"
#include "BoundVector3D.h"

//======================================================================================
BoundVector3D::BoundVector3D()
{
	SetToZero();
} // BoundVector3D::BoundVector3D

//======================================================================================
BoundVector3D::BoundVector3D(Point3D &aBasePt, FreeVector3D &aDirVector)
{
	fBasePt.SetToPoint(aBasePt);
	fDirVector.SetToVector(aDirVector);
} // BoundVector3D::BoundVector3D

//======================================================================================
BoundVector3D::BoundVector3D(Point3D &aFromPt, Point3D &aToPt)
{
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
//======================================================================================
//======================================================================================
//======================================================================================
