#pragma once

class HullGeomType
{
private:
	bool fIsVis;
	double fMinX, fMaxX, fMinY, fMaxY, fMinZ, fMaxZ;
	bool fBoundingBoxSet;
	
	virtual void SetBoundingBox() = 0;

public:
	HullGeomType();
	~HullGeomType();

	bool Visible(){ return fIsVis; }
	void SetVisible(const bool aVis){ fIsVis = aVis; }

	virtual void Draw() = 0;

	double MinX(){ if (!fBoundingBoxSet){ SetBoundingBox(); } return fMinX; }
	double MaxX(){ if (!fBoundingBoxSet){ SetBoundingBox(); } return fMaxX; }
	double MinY(){ if (!fBoundingBoxSet){ SetBoundingBox(); } return fMinY; }
	double MaxY(){ if (!fBoundingBoxSet){ SetBoundingBox(); } return fMaxY; }
	double MinZ(){ if (!fBoundingBoxSet){ SetBoundingBox(); } return fMinZ; }
	double MaxZ(){ if (!fBoundingBoxSet){ SetBoundingBox(); } return fMaxZ; }
}; // class HullGeomType
