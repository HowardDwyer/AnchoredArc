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
	BoundVector3D(Point3D &aBasePt, FreeVector3D &aDirVector);
	BoundVector3D(Point3D &aFromPt, Point3D &aToPt);
	~BoundVector3D();

	Point3D BasePoint(){ return Point3D(fBasePt); }  // a copy, not a reference
	FreeVector3D DirVector(){ return FreeVector3D(fDirVector); } // a copy, not a reference

	void SetToZero(){ fBasePt.SetToZero(); fDirVector.SetToZero(); }
	void SetVector(FreeVector3D &aSourceVec){ fDirVector.SetToVector(aSourceVec); }
	void SetBase(Point3D &aSourcePt){ fBasePt.SetToPoint(aSourcePt); }
	void SetLength(const double aNewLength){ fDirVector.Setlength(aNewLength); }
	void TransformBy(TransfMatrix3D &aM){ fBasePt.TransformBy(aM); fDirVector.TransformBy(aM); }
	double Length(){ return fDirVector.Length(); }
	bool IsExactlyZero(){ return fDirVector.IsExactlyZero(); }
	bool IsApproxZero(){ return fDirVector.IsApproxZero(); }

}; // class BoundVector3D
