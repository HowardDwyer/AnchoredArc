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
FreeVector3D::FreeVector3D(const double aX, const double aY, const double aZ)
{
	fCoord[0] = aX;
	fCoord[1] = aY;
	fCoord[2] = aZ;
	fLength = 0.0;
	fIsLengthComputed = false;
} // FreeVector3D::FreeVector3D

//==========================================================================================
FreeVector3D::FreeVector3D(const FreeVector3D & aSource)
{
	fCoord[0] = aSource.fCoord[0];
	fCoord[1] = aSource.fCoord[1];
	fCoord[2] = aSource.fCoord[2];
	fLength = aSource.fLength;
	fIsLengthComputed = aSource.fIsLengthComputed;
} // FreeVector3D::FreeVector3D

//==========================================================================================
FreeVector3D::~FreeVector3D(){}

//==========================================================================================
double FreeVector3D::Length()
{
	if (!fIsLengthComputed)
	{
		fLength = sqrt(fCoord[0] * fCoord[0] + fCoord[1] * fCoord[1] + fCoord[2] * fCoord[2]);
		fIsLengthComputed = true;
	}
	return fLength;
} // FreeVector3D::Length

//==========================================================================================
bool FreeVector3D::Normalize()
{
	double lLength = Length();
	if (lLength > 0.0)
	{
		fCoord[0] /= lLength;
		fCoord[1] /= lLength;
		fCoord[2] /= lLength;
		fLength = 1.0;
		fIsLengthComputed = true;
	}
	return (lLength > 0.0);
} // FreeVector3D::Normalize

//==========================================================================================
FreeVector3D FreeVector3D::operator + (const FreeVector3D &aV)
{
	FreeVector3D lThisPlusV;
	lThisPlusV.fCoord[0] = this->fCoord[0] + aV.fCoord[0];
	lThisPlusV.fCoord[1] = this->fCoord[1] + aV.fCoord[1];
	lThisPlusV.fCoord[2] = this->fCoord[2] + aV.fCoord[2];
	lThisPlusV.fIsLengthComputed = false;
	return lThisPlusV;
} // FreeVector3D::operator +

//==========================================================================================
FreeVector3D FreeVector3D::operator - (const FreeVector3D &aV)
{
	FreeVector3D lThisPlusV;
	lThisPlusV.fCoord[0] = this->fCoord[0] + aV.fCoord[0];
	lThisPlusV.fCoord[1] = this->fCoord[1] + aV.fCoord[1];
	lThisPlusV.fCoord[2] = this->fCoord[2] + aV.fCoord[2];
	lThisPlusV.fIsLengthComputed = false;
	return lThisPlusV;
} // FreeVector3D::operator +

//==========================================================================================
double FreeVector3D::operator * (const FreeVector3D &aV)
{
	double lDot = 0.0;
	lDot += this->fCoord[0] * aV.fCoord[0];
	lDot += this->fCoord[1] * aV.fCoord[1];
	lDot += this->fCoord[2] * aV.fCoord[2];
	return lDot;
} // FreeVector3D::operator -

//==========================================================================================
void FreeVector3D::operator *= (const double aScale)
{
	this->fCoord[0] *= aScale;
	this->fCoord[1] *= aScale;
	this->fCoord[2] *= aScale;
	this->fLength *= abs(aScale);
} // FreeVector3D::operator *=

//==========================================================================================
double FreeVector3D::Dot(const FreeVector3D &aV)
{
	double lDot = 0.0;
	lDot += this->fCoord[0] * aV.fCoord[0];
	lDot += this->fCoord[1] * aV.fCoord[1];
	lDot += this->fCoord[2] * aV.fCoord[2];
	return lDot;
} // FreeVector3D::operator -

//==========================================================================================
FreeVector3D FreeVector3D::Cross(const FreeVector3D &aV)
{
	FreeVector3D lCrossProd;
	lCrossProd.fCoord[0] = this->fCoord[1] * aV.fCoord[2] - this->fCoord[2] * aV.fCoord[1];
	lCrossProd.fCoord[0] = -(this->fCoord[0] * aV.fCoord[2] - this->fCoord[2] * aV.fCoord[0]);
	lCrossProd.fCoord[0] = this->fCoord[0] * aV.fCoord[1] - this->fCoord[1] * aV.fCoord[0];
	lCrossProd.fIsLengthComputed = false;
	return lCrossProd;
} // FreeVector3D::Cross

//==========================================================================================
bool FreeVector3D::IsExactlyZero()
{
	return ((fCoord[0] == 0.0) && (fCoord[1] == 0.0) && (fCoord[2] == 0.0));
} // FreeVector3D::IsExactlyZero

//==========================================================================================
bool FreeVector3D::IsApproxZero()
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
bool FreeVector3D::IsParallelTo(FreeVector3D aV)
{
	bool lResult = true;
	if (IsExactlyZero()){lResult = true;}
	else if (aV.IsExactlyZero()){lResult = true;}
	else
	{
		double lDot = Dot(aV);
		double lLength_This = Length();
		double lLength_V = aV.Length();
		lResult = (abs(lDot) >= lLength_This * lLength_V * HullConst::COSANGLETOL());
	} // neither of the vectors is zero
	return lResult;
} // FreeVector3D::IsParallelTo

//==========================================================================================
// Note: a zero vector is orthgonal to any other vector.
//==========================================================================================
bool FreeVector3D::IsOrthogonalTo(FreeVector3D aV)
{
	bool lResult = true;
	if (IsExactlyZero()){ lResult = true; }
	else if (aV.IsExactlyZero()){ lResult = true; }
	else
	{
		double lDot = Dot(aV);
		double lLength_This = Length();
		double lLength_V = aV.Length();
		lResult = (abs(lDot) <= lLength_This * lLength_V * HullConst::SINANGLETOL());
	} // neither of the vectors is zero
	return lResult;
} // FreeVector3D::IsOrthogonalTo

//==========================================================================================
//==========================================================================================
//==========================================================================================
