#pragma once
#include "TransfMatrix3D.h"
#include "Point3D.h"


class FreeVector3D
{
private:
	double fCoord[3];
	mutable double fLength;
	mutable bool fIsLengthComputed;
public:
	FreeVector3D();
	FreeVector3D(const double aX, const double aY, const double aZ);
	FreeVector3D(const Point3D &aFromPt, const Point3D &aToPt);

	FreeVector3D(const FreeVector3D &aSource);
	~FreeVector3D();

	bool Normalize();
	bool IsExactlyZero() const;
	bool IsApproxZero() const;
	void SetToZero();

	double X() const { return fCoord[0]; }
	double Y() const { return fCoord[1]; }
	double Z() const { return fCoord[2]; }

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

	void SetToVector(const FreeVector3D &aSource);
	
	double Length() const;
	
	void Setlength(const double aNewLength);
	
	void Scale(const double aScale);

	double Dot(const FreeVector3D &aV) const;
	
	FreeVector3D Cross(const FreeVector3D &aV) const;

	bool IsParallelTo(const FreeVector3D &aV) const;
	
	bool IsOrthogonalTo(const FreeVector3D &aV) const;

	void TransformBy(const TransfMatrix3D &aM);

	FreeVector3D operator + (const FreeVector3D &aV) const;
	FreeVector3D operator - (const FreeVector3D &aV) const;
	double operator * (const FreeVector3D &aV) const;
	void operator *= (const double aScale);
};

