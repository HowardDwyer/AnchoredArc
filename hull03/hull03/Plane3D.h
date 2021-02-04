#pragma once
#include "BoundVector3D.h"

class Plane3D
{
private:
	BoundVector3D fNormal;
public:
	Plane3D()
	{ 
		fNormal.SetToZero(); 
	}

	Plane3D(const BoundVector3D &aSource)
	{ 
		fNormal.SetToBoundVector(aSource); 
	}

	Plane3D(const Point3D &aPointOnPlane, const FreeVector3D &aNormalVector);
	Plane3D(const Point3D &aPt1, const Point3D &aPt2, const Point3D &aPt3);
	~Plane3D();

	bool IsWellDefined() const;

	void Normalize()
	{ 
		fNormal.Normalize(); 
	}

	Point3D PointOnPlane() const
	{ 
		return fNormal.BasePoint(); 
	}  // a copy, not a reference
	
	FreeVector3D NormalDirVector() const
	{
		return fNormal.DirVector(); 
	}  // a copy, not a reference

	void SetUsingThreePts(const Point3D &aPt1, const Point3D &aPt2, const Point3D &aPt3);
	void SetUsingPtAndNormal(const Point3D &aPointOnPlane, const FreeVector3D &aNormalVector);

	bool PointIsOnPlane(const Point3D &aPt) const;
	bool PointIsExactlyOnPlane(const Point3D &aPt) const;
	bool PointIsAbovePlane(const Point3D &aPt) const;
	bool PointIsBelowPlane(const Point3D &aPt) const;
	void ProjectPointOntoPlane(Point3D* aPt) const;
}; // class Plane3D

