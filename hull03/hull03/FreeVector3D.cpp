#include "stdafx.h"
#include "FreeVector3D.h"
#include "HullConst.h"

#include <cmath>

//==========================================================================================
FreeVector3D::FreeVector3D()
{
	SetToZero();
} // FreeVector3D::FreeVector3D()

//==========================================================================================
FreeVector3D::FreeVector3D(
	const double aX, 
	const double aY, 
	const double aZ)
{
	fCoord[0] = aX;
	fCoord[1] = aY;
	fCoord[2] = aZ;
	fLength = 0.0;
	fIsLengthComputed = false;
} // FreeVector3D::FreeVector3D

//==========================================================================================
FreeVector3D::FreeVector3D(const Point3D &aFromPt,const Point3D &aToPt)
{
	fCoord[0] = (aToPt.X() - aFromPt.X());
	fCoord[1] = (aToPt.Y() - aFromPt.Y());
	fCoord[2] = (aToPt.Z() - aFromPt.Z());
	fLength = 0.0;
	fIsLengthComputed = false;
}

//==========================================================================================
FreeVector3D::FreeVector3D(const FreeVector3D &aSource)
{
	SetToVector(aSource);
} // FreeVector3D::FreeVector3D

//==========================================================================================
FreeVector3D::~FreeVector3D(){}

//==========================================================================================
double FreeVector3D::Length() const
{
	if (!fIsLengthComputed)
	{
		fLength = sqrt(fCoord[0] * fCoord[0] + fCoord[1] * fCoord[1] + fCoord[2] * fCoord[2]);
		fIsLengthComputed = true;
	}
	return fLength;
} // FreeVector3D::Length

//==========================================================================================
void FreeVector3D::Scale(const double aScale)
{
	fCoord[0] *= aScale;
	fCoord[1] *= aScale;
	fCoord[2] *= aScale;
	fLength *= abs(aScale);
}

//==========================================================================================
void FreeVector3D::Setlength(const double aNewLength)
{
	const double length = Length();
	if (length > 0.0)
	{
		const double factor = aNewLength / length;
		Scale(factor);
	} // if this is not a zero vector
} // FreeVector3D::Setlength

//==========================================================================================
void FreeVector3D::SetToVector(const FreeVector3D &aSource)
{
	fCoord[0] = aSource.fCoord[0];
	fCoord[1] = aSource.fCoord[1];
	fCoord[2] = aSource.fCoord[2];
	fLength = aSource.fLength;
	fIsLengthComputed = aSource.fIsLengthComputed;
} // FreeVector3D::SetToVector

//==========================================================================================
bool FreeVector3D::Normalize()
{
	const double length = Length();
	if ((length > 0.0) && (length != 1.0))
	{
		const double scale = 1.0 / length;
		Scale(scale);
		fLength = 1.0;
		fIsLengthComputed = true;
	}
	return (length > 0.0);
} // FreeVector3D::Normalize

//==========================================================================================
FreeVector3D FreeVector3D::operator + (const FreeVector3D &aV) const
{
	FreeVector3D thisPlusV;
	thisPlusV.fCoord[0] = fCoord[0] + aV.fCoord[0];
	thisPlusV.fCoord[1] = fCoord[1] + aV.fCoord[1];
	thisPlusV.fCoord[2] = fCoord[2] + aV.fCoord[2];
	thisPlusV.fIsLengthComputed = false;
	return thisPlusV;
} // FreeVector3D::operator +

//==========================================================================================
FreeVector3D FreeVector3D::operator - (const FreeVector3D &aV) const
{
	FreeVector3D thisPlusV;
	thisPlusV.fCoord[0] = fCoord[0] + aV.fCoord[0];
	thisPlusV.fCoord[1] = fCoord[1] + aV.fCoord[1];
	thisPlusV.fCoord[2] = fCoord[2] + aV.fCoord[2];
	thisPlusV.fIsLengthComputed = false;
	return thisPlusV;
} // FreeVector3D::operator +

//==========================================================================================
double FreeVector3D::operator * (const FreeVector3D &aV) const
{
	return Dot(aV);
} // FreeVector3D::operator -

//==========================================================================================
void FreeVector3D::operator *= (const double aScale)
{
	Scale(aScale);
} // FreeVector3D::operator *=

//==========================================================================================
double FreeVector3D::Dot(const FreeVector3D &aV) const
{
	double dot = 0.0;
	dot += fCoord[0] * aV.fCoord[0];
	dot += fCoord[1] * aV.fCoord[1];
	dot += fCoord[2] * aV.fCoord[2];
	return dot;
} // FreeVector3D::operator -

//==========================================================================================
FreeVector3D FreeVector3D::Cross(const FreeVector3D &aV) const
{
	FreeVector3D crossProd;
	crossProd.fCoord[0] = fCoord[1] * aV.fCoord[2] - fCoord[2] * aV.fCoord[1];
	crossProd.fCoord[0] = -(fCoord[0] * aV.fCoord[2] - fCoord[2] * aV.fCoord[0]);
	crossProd.fCoord[0] = fCoord[0] * aV.fCoord[1] - fCoord[1] * aV.fCoord[0];
	crossProd.fIsLengthComputed = false;
	return crossProd;
} // FreeVector3D::Cross

//==========================================================================================
bool FreeVector3D::IsExactlyZero() const
{
	return ((fCoord[0] == 0.0) && (fCoord[1] == 0.0) && (fCoord[2] == 0.0));
} // FreeVector3D::IsExactlyZero

//==========================================================================================
bool FreeVector3D::IsApproxZero() const
{
	return ((abs(fCoord[0]) <= HullConst::VERYSMALL()) 
		&& (abs(fCoord[1]) <= HullConst::VERYSMALL()) 
		&& (abs(fCoord[2]) <= HullConst::VERYSMALL()));
} // FreeVector3D::IsApproxZero

//==========================================================================================
void FreeVector3D::SetToZero()
{
	fCoord[0] = fCoord[1] = fCoord[2] = 0.0;
	fLength = 0.0;
	fIsLengthComputed = true;
} // FreeVector3D::SetToZero

//==========================================================================================
// Note: a zero vector is parallel to any other vector.
//==========================================================================================
bool FreeVector3D::IsParallelTo(const FreeVector3D &aV) const
{
	bool result = true;
	if (IsExactlyZero()){result = true;}
	else if (aV.IsExactlyZero()){result = true;}
	else
	{
		const double dot = Dot(aV);
		const double length_This = Length();
		const double length_V = aV.Length();
		result = (abs(dot) >= length_This * length_V * HullConst::COSANGLETOL());
	} // neither of the vectors is zero
	return result;
} // FreeVector3D::IsParallelTo

//==========================================================================================
// Note: a zero vector is orthgonal to any other vector.
//==========================================================================================
bool FreeVector3D::IsOrthogonalTo(const FreeVector3D &aV) const
{
	bool result = true;
	if (IsExactlyZero()){ result = true; }
	else if (aV.IsExactlyZero()){ result = true; }
	else
	{
		const double dot = Dot(aV);
		const double length_This = Length();
		const double length_V = aV.Length();
		result = (abs(dot) <= length_This * length_V * HullConst::SINANGLETOL());
	} // neither of the vectors is zero
	return result;
} // FreeVector3D::IsOrthogonalTo

//==========================================================================================
void FreeVector3D::TransformBy(const TransfMatrix3D &aM)
{
	double temp[3];
	for (int i = 0; i < 3; i++)
	{
		temp[i] = fCoord[i]; 
	}

	for (int i = 0; i < 3; i++)
	{
		fCoord[i] = 0.0; // free vectors are not translated.
		for (int k = 0; k < 3; k++)
		{
			fCoord[i] += aM.At(i, k) * temp[k];
		} // loop to compute the ot product
	}// loop through the coord in the point
	fLength = 0.0;
	fIsLengthComputed = false;
} // FreeVector3D::TransformBy

//==========================================================================================
//==========================================================================================
