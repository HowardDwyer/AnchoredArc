#pragma once
#include "BoundVector3D.h"

class Plane3D
{
private:
	BoundVector3D fNormal;
public:
	Plane3D()
	{ 
		SetNormalToZero();
	}

	Plane3D(const BoundVector3D &aSource)
	{
		fNormal.SetToBoundVector(aSource);
	}

	Plane3D(const Plane3D &aSource)
	{
		fNormal.SetToBoundVector(aSource.fNormal);
	}

	Plane3D(const Point3D &aPointOnPlane, const FreeVector3D &aNormalVector);
	Plane3D(const Point3D &aPt1, const Point3D &aPt2, const Point3D &aPt3);
	~Plane3D();

	bool IsWellDefined() const;

	void SetNormalToZero()
	{
		fNormal.SetToZero();
	}

	void Normalize()
	{ 
		fNormal.Normalize(); 
	}

	Point3D PointOnPlane() const
	{ 
		return fNormal.StartPoint(); 
	}  
	
	FreeVector3D NormalDirVector() const
	{
		return fNormal.DirVector();
	}  

	BoundVector3D NormalVector() const
	{
		return fNormal;
	}  

	void SetUsingThreePts(const Point3D &aPt1, const Point3D &aPt2, const Point3D &aPt3);
	void SetUsingPtAndNormal(const Point3D &aPointOnPlane, const FreeVector3D &aNormalVector);

	bool PointIsOnPlane(const Point3D &aPt) const;
	bool PointIsExactlyOnPlane(const Point3D &aPt) const;
	bool PointIsAbovePlane(const Point3D &aPt) const;
	bool PointIsBelowPlane(const Point3D &aPt) const;
	void ProjectPointOntoPlane(Point3D* aPt) const;

	static bool PointsDefinePlane(const Point3D& p1, const Point3D& p2, const Point3D& p3);

}; // class Plane3D

