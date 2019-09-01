#include "stdafx.h"
#include "HullGeomType.h"
#include <cmath>

//==============================================================================
HullGeomType::HullGeomType()
{
	fIsVis = true;
	fIsBoundingBoxSet =false;
	fMinX = fMaxX = fMinY = fMaxY = fMinZ = fMaxZ = 0.0;
} // HullGeomType::HullGeomType

//==============================================================================
HullGeomType::HullGeomType(const HullGeomType & aSource)
{
	fIsVis = aSource.fIsVis;
	fIsBoundingBoxSet = aSource.fIsBoundingBoxSet;
	fMinX = aSource.fMinX;
	fMaxX = aSource.fMaxX;
	fMinY = aSource.fMinY;
	fMaxY = aSource.fMaxY;
	fMinZ = aSource.fMinZ;
	fMaxZ = aSource.fMaxZ;
} // HullGeomType::HullGeomType


//==============================================================================
HullGeomType::~HullGeomType()
{
}

//==============================================================================
double HullGeomType::Diagonal()
{
	double dx = MaxX() - MinX();
	double dy = MaxY() - MinY();
	double dz = MaxZ() - MinZ();
	return sqrt(dx*dx + dy*dy + dz*dz);
} // double HullGeomType::Diagonal
