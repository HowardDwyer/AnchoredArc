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
	double length = Length();
	if (length > 0.0)
	{
		fCoord[0] /= length;
		fCoord[1] /= length;
		fCoord[2] /= length;
		fLength = 1.0;
		fIsLengthComputed = true;
	}
	return (length > 0.0);
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
	return this->Dot(aV);
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
	double dot = 0.0;
	dot += this->fCoord[0] * aV.fCoord[0];
	dot += this->fCoord[1] * aV.fCoord[1];
	dot += this->fCoord[2] * aV.fCoord[2];
	return dot;
} // FreeVector3D::operator -

//==========================================================================================
FreeVector3D FreeVector3D::Cross(const FreeVector3D &aV)
{
	FreeVector3D crossProd;
	crossProd.fCoord[0] = this->fCoord[1] * aV.fCoord[2] - this->fCoord[2] * aV.fCoord[1];
	crossProd.fCoord[0] = -(this->fCoord[0] * aV.fCoord[2] - this->fCoord[2] * aV.fCoord[0]);
	crossProd.fCoord[0] = this->fCoord[0] * aV.fCoord[1] - this->fCoord[1] * aV.fCoord[0];
	crossProd.fIsLengthComputed = false;
	return crossProd;
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
	bool result = true;
	if (IsExactlyZero()){result = true;}
	else if (aV.IsExactlyZero()){result = true;}
	else
	{
		double dot = Dot(aV);
		double length_This = Length();
		double length_V = aV.Length();
		result = (abs(dot) >= length_This * length_V * HullConst::COSANGLETOL());
	} // neither of the vectors is zero
	return result;
} // FreeVector3D::IsParallelTo

//==========================================================================================
// Note: a zero vector is orthgonal to any other vector.
//==========================================================================================
bool FreeVector3D::IsOrthogonalTo(FreeVector3D aV)
{
	bool result = true;
	if (IsExactlyZero()){ result = true; }
	else if (aV.IsExactlyZero()){ result = true; }
	else
	{
		double dot = Dot(aV);
		double length_This = Length();
		double length_V = aV.Length();
		result = (abs(dot) <= length_This * length_V * HullConst::SINANGLETOL());
	} // neither of the vectors is zero
	return result;
} // FreeVector3D::IsOrthogonalTo

//==========================================================================================
void FreeVector3D::TransformBy(TransfMatrix3D aM)
{
	double temp[3];
	for (int i = 0; i < 3; i++){ temp[i] = fCoord[i]; }
	for (int i = 0; i < 3; i++)
	{
		fCoord[i] = 0.0; // free vectors are not translated.
		for (int k = 0; k < 3; k++)
		{
			fCoord[i] += aM.At(i, k) * temp[k];
		} // loop to compute the ot product
	}// loop through the coord in the point
} // FreeVector3D::TransformBy

//==========================================================================================
//==========================================================================================
