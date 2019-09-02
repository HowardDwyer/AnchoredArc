#pragma once
#include "TransfMatrix3D.h"

class HullGeomType
{
protected:
	bool fIsVis;
	double fMinX, fMaxX, fMinY, fMaxY, fMinZ, fMaxZ;
	bool fIsBoundingBoxSet;
	
	virtual void SetBoundingBox() = 0;

public:
	HullGeomType();
	HullGeomType(const HullGeomType & aSource);
	~HullGeomType();

	bool Visible(){ return fIsVis; }
	void SetVisible(const bool aVis){ fIsVis = aVis; }

	virtual void Draw() = 0;

	double MinX(){ if (!fIsBoundingBoxSet){ SetBoundingBox(); } return fMinX; }
	double MaxX(){ if (!fIsBoundingBoxSet){ SetBoundingBox(); } return fMaxX; }
	double MinY(){ if (!fIsBoundingBoxSet){ SetBoundingBox(); } return fMinY; }
	double MaxY(){ if (!fIsBoundingBoxSet){ SetBoundingBox(); } return fMaxY; }
	double MinZ(){ if (!fIsBoundingBoxSet){ SetBoundingBox(); } return fMinZ; }
	double MaxZ(){ if (!fIsBoundingBoxSet){ SetBoundingBox(); } return fMaxZ; }

	double Diagonal();

	virtual void TransformBy(TransfMatrix3D &aM) = 0;

}; // class HullGeomType
