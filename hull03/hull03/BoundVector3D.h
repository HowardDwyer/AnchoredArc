#pragma once
#include "HullGeomType.h"
#include "Point3D.h"
#include "FreeVector3D.h"
#include "TransfMatrix3D.h"

class BoundVector3D : public HullGeomType
{
private:
	Point3D fBasePt;
	FreeVector3D fDirVector;

public:
	BoundVector3D();
	BoundVector3D(const Point3D &aBasePt, const FreeVector3D &aDirVector);
	BoundVector3D(const Point3D &aFromPt, const Point3D &aToPt);
	BoundVector3D(const BoundVector3D &aSource);
	~BoundVector3D();

	Point3D BasePoint() const { return Point3D(fBasePt); }  // a copy, not a reference
	FreeVector3D DirVector() const { return FreeVector3D(fDirVector); } // a copy, not a reference

	virtual void SetBoundingBox() const;
	virtual void Draw(){ /* TODO*/ }

	void Normalize()
	{ 
		fDirVector.Normalize(); 
	}

	void SetToZero()
	{
		fBasePt.SetToZero(); 
		fDirVector.SetToZero(); 
	}

	void SetVector(const FreeVector3D &aSourceVec)
	{ 
		fDirVector.SetToVector(aSourceVec); 
	}

	void SetToBoundVector(const BoundVector3D &aSource)
	{ 
		fBasePt.SetToPoint(aSource.fBasePt); 
		fDirVector.SetToVector(aSource.fDirVector); 
	}

	void SetBase(const Point3D &aSourcePt)
	{ 
		fBasePt.SetToPoint(aSourcePt); 
	}

	void SetLength(const double aNewLength)
	{ 
		fDirVector.Setlength(aNewLength); 
	}

	void TransformBy(const TransfMatrix3D &aM)
	{ 
		fBasePt.TransformBy(aM); 
		fDirVector.TransformBy(aM); 
	}

	double Length() const
	{ 
		return fDirVector.Length(); 
	}
	
	bool IsExactlyZero() const
	{ 
		return fDirVector.IsExactlyZero(); 
	}
	
	bool IsApproxZero() const
	{ 
		return fDirVector.IsApproxZero(); 
	}


}; // class BoundVector3D
