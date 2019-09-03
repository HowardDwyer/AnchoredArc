#pragma once
#include "BoundVector3D.h"

class Plane3D
{
private:
	BoundVector3D fNormal;
public:
	Plane3D(){ fNormal.SetToZero(); };
	Plane3D(BoundVector3D &aSource){ fNormal.SetToBoundVector(aSource); }
	Plane3D(Point3D &aPointOnPlane, FreeVector3D &aNormalVector);
	Plane3D(Point3D &aPt1, Point3D &aPt2, Point3D &aPt3 );
	~Plane3D();

	bool IsWellDefined();
	void Normalize(){ fNormal.Normalize(); }

	Point3D PointOnPlane(){ return fNormal.BasePoint(); }  // a copy, not a reference
	FreeVector3D NormalDirVector(){ return fNormal.DirVector(); }  // a copy, not a reference

	void SetUsingThreePts(Point3D &aPt1, Point3D &aPt2, Point3D &aPt3);
	void SetUsingPtAndNormal(Point3D &aPointOnPlane, FreeVector3D &aNormalVector);

	bool PointIsOnPlane(Point3D &aPt);
	bool PointIsExactlyOnPlane(Point3D &aPt);
	bool PointIsAbovePlane(Point3D &aPt);
	bool PointIsBelowPlane(Point3D &aPt);
	void ProjectPointOntoPlane(Point3D* aPt);
}; // class Plane3D

