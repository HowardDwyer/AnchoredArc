#include "stdafx.h"
#include "BoundVector3D.h"

//======================================================================================
BoundVector3D::BoundVector3D() 
	: HullGeomType()
{
	SetToZero();
} // BoundVector3D::BoundVector3D

//======================================================================================
BoundVector3D::BoundVector3D(const Point3D &aBasePt, const FreeVector3D &aDirVector)
	: HullGeomType()
{
	fBasePt.SetToPoint(aBasePt);
	fDirVector.SetToVector(aDirVector);
} // BoundVector3D::BoundVector3D

//======================================================================================
BoundVector3D::BoundVector3D(const Point3D &aFromPt, const Point3D &aToPt)
	: HullGeomType()
{
	fBasePt.SetToPoint(aFromPt);
	fDirVector.SetX(aToPt.X() - aFromPt.X());
	fDirVector.SetY(aToPt.Y() - aFromPt.Y());
	fDirVector.SetZ(aToPt.Z() - aFromPt.Z());
} // BoundVector3D::BoundVector3D

//======================================================================================
BoundVector3D::BoundVector3D(const BoundVector3D &aSource)
	: HullGeomType(aSource)
{
	fBasePt.SetToPoint(aSource.fBasePt);
	fDirVector.SetToVector(aSource.fDirVector);
} // BoundVector3D::BoundVector3D

//======================================================================================
BoundVector3D::~BoundVector3D()
{
}// BoundVector3D::~BoundVector3D

//======================================================================================
void BoundVector3D::SetBoundingBox() const
{
	const double x1 = fBasePt.X(); 
	const double x2 = x1 + fDirVector.X();
	const double y1 = fBasePt.Y();
	const double y2 = y1 + fDirVector.Y();
	const double z1 = fBasePt.Z();
	const double z2 = z1 + fDirVector.Z();

	if (x1 > x2)
	{ 
		fMinX = x2; 
		fMaxX = x1; 
	}

	else 
	{ 
		fMinX = x1; 
		fMaxX = x2; 
	}

	if (y1 > y2)
	{ 
		fMinY = y2; 
		fMaxY = y1; 
	}
	else 
	{ 
		fMinY = y1; 
		fMaxY = y2; 
	}

	if (z1 > z2)
	{ 
		fMinZ = z2; 
		fMaxZ = z1; 
	}
	else 
	{ 
		fMinZ = z1; 
		fMaxZ = z2; 
	}
} // BoundVector3D::SetBoundingBox

//======================================================================================
//======================================================================================
//======================================================================================
