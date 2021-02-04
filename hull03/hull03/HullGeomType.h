#pragma once
#include "TransfMatrix3D.h"

class HullGeomType
{
protected:
	bool fIsVis;
	mutable double fMinX, fMaxX, fMinY, fMaxY, fMinZ, fMaxZ;
	mutable bool fIsBoundingBoxSet;
	
	virtual void SetBoundingBox() const = 0;

public:
	HullGeomType();
	HullGeomType(const HullGeomType & aSource);
	~HullGeomType();

	bool Visible() const
	{ 
		return fIsVis; 
	}

	void SetVisible(const bool aVis)
	{
		fIsVis = aVis; 
	}

	virtual void Draw() = 0;

	double MinX() const
	{ 
		if (!fIsBoundingBoxSet)
		{ 
			SetBoundingBox(); 
		} 
		return fMinX; 
	}

	double MaxX()  const
	{ 
		if (!fIsBoundingBoxSet)
		{ 
			SetBoundingBox(); 
		} 
		return fMaxX; 
	}

	double MinY()  const
	{ 
		if (!fIsBoundingBoxSet)
		{ 
			SetBoundingBox(); 
		} 
		return fMinY; 
	}

	double MaxY() const
	{ 
		if (!fIsBoundingBoxSet)
		{ 
			SetBoundingBox(); 
		}
		return fMaxY; 
	}

	double MinZ() const
	{ 
		if (!fIsBoundingBoxSet)
		{ 
			SetBoundingBox(); 
		}
		return fMinZ; 
	}
	
	double MaxZ() const
	{ 
		if (!fIsBoundingBoxSet)
		{
			SetBoundingBox(); 
		} 
		return fMaxZ; 
	}

	double Diagonal() const;

	virtual void TransformBy(const TransfMatrix3D &aM) = 0;

}; // class HullGeomType
