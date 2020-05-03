#pragma once
#include "TransfMatrix3D.h"
#include "Point3D.h"


class FreeVector3D
{
private:
	double fCoord[3];
	double fLength;
	bool fIsLengthComputed;
public:
	FreeVector3D();
	FreeVector3D(const double aX, const double aY, const double aZ);
	FreeVector3D(Point3D &aFromPt, Point3D &aToPt);

	FreeVector3D(FreeVector3D &aSource);
	~FreeVector3D();

	bool Normalize();
	bool IsExactlyZero();
	bool IsApproxZero();
	void SetToZero();

	double X(){ return fCoord[0]; }
	double Y(){ return fCoord[1]; }
	double Z(){ return fCoord[2]; }

	void SetX(const double aX)
	{ 
		fCoord[0] = aX; 
		fIsLengthComputed = false; 
	}

	void SetY(const double aY)
	{ 
		fCoord[1] = aY; 
		fIsLengthComputed = false; 
	}

	void SetZ(const double aZ)
	{ 
		fCoord[2] = aZ; 
		fIsLengthComputed = false; 
	}

	void SetToVector(FreeVector3D &aSource);
	
	double Length();
	
	void Setlength(const double aNewLength);
	
	void Scale(const double aScale);

	double Dot(FreeVector3D &aV);
	
	FreeVector3D Cross(FreeVector3D &aV);

	bool IsParallelTo(FreeVector3D &aV);
	
	bool IsOrthogonalTo(FreeVector3D &aV);

	void TransformBy(TransfMatrix3D &aM);

	FreeVector3D operator + (FreeVector3D &aV);
	FreeVector3D operator - (FreeVector3D &aV);
	double operator * (FreeVector3D &aV);
	void operator *= (const double aScale);
};

