#include "stdafx.h"
#include "Point3D.h"

//===================================================================================
Point3D::Point3D()
{
	fIsVis = true;
	fIsBoundingBoxSet = false;
	fMinX = fMaxX = fMinY = fMaxY = fMinZ = fMaxZ = 0.0;
	SetToZero();
} // Point3D::Point3D

//===================================================================================
Point3D::Point3D(const double aX, const double aY, const double aZ)
{
	fIsVis = true;
	fIsBoundingBoxSet = false;
	fMinX = fMaxX = fMinY = fMaxY = fMinZ = fMaxZ = 0.0;
	fCoord[0] = aX;
	fCoord[1] = aY;
	fCoord[2] = aZ;
	SetBoundingBox();
} // Point3D::Point3D

//===================================================================================
Point3D::Point3D(Point3D &aSource): HullGeomType(aSource)
{
	fIsVis = true;
	fIsBoundingBoxSet = false;
	fMinX = fMaxX = fMinY = fMaxY = fMinZ = fMaxZ = 0.0;
	fCoord[0] = aSource.fCoord[0];
	fCoord[1] = aSource.fCoord[1];
	fCoord[2] = aSource.fCoord[2];
	SetBoundingBox();
} // Point3D::Point3D

//===================================================================================
Point3D::~Point3D()
{
}

//===================================================================================
void Point3D::SetToPoint(Point3D &aSource)
{
	fCoord[0] = aSource.fCoord[0];
	fCoord[1] = aSource.fCoord[1];
	fCoord[2] = aSource.fCoord[2];
	SetBoundingBox();
} // Point3D::SetToPoint

//===================================================================================
void Point3D::SetBoundingBox()
{
	fMinX = fMaxX = fCoord[0];
	fMinY = fMaxY = fCoord[1];
	fMinZ = fMaxZ = fCoord[2];
	fIsBoundingBoxSet = true;
}// Point3D::SetBoundingBox

//===================================================================================
void Point3D::TransformBy(TransfMatrix3D &aM)
{
	double temp[3];
	for (int i = 0; i < 3; i++){ temp[i] = fCoord[i]; }
	for (int i = 0; i < 3; i++)
	{ 
		fCoord[i] = aM.At(i,3);
		for (int k = 0; k < 3; k++)
		{
			fCoord[i] += aM.At(i, k) * temp[k];
		} // loop to compute the ot product
	}// loop through the coord in the point
	SetBoundingBox();
} // Point3D::TransformBy

//===================================================================================
