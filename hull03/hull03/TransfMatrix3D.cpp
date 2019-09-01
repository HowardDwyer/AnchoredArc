#include "stdafx.h"
#include "TransfMatrix3D.h"
#include <cmath>

//========================================================================================
TransfMatrix3D::TransfMatrix3D()
{
	SetToIdentity();
} // TransfMatrix3D::TransfMatrix3D


//========================================================================================
TransfMatrix3D::~TransfMatrix3D()
{
} // TransfMatrix3D::~TransfMatrix3D

//========================================================================================
TransfMatrix3D::TransfMatrix3D(TransfMatrix3D & aSource)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fM[i][j] = aSource.fM[i][j];
		} // loop through cols
	} // loop through rows
} // TransfMatrix3D::TransfMatrix3D

//========================================================================================
void TransfMatrix3D::SetToIdentity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fM[i][j] = 0.0;
		} // loop through cols
		fM[i][i] = 1.0;
	} // loop through rows
} // TransfMatrix3D::SetToIdentity

//========================================================================================
void TransfMatrix3D::SetToTranslationMatrix(const double aDx, const double aDy, const double aDz)
{
	SetToIdentity();
	fM[0][3] = aDx;
	fM[1][3] = aDy;
	fM[2][3] = aDz;
} // TransfMatrix3D::SetToTranslationMatrix

//========================================================================================
// rotate around the Z axis, from X to Y
void TransfMatrix3D::SetToRotationMatrix_XY(const double aAngle)
{
	SetToIdentity();
	double sinAngle = sin(aAngle);
	double cosAngle = cos(aAngle);
	fM[0][0] = cosAngle;	fM[0][1] = -sinAngle;   fM[0][2] = 0.0;
	fM[1][0] = sinAngle;	fM[1][1] = cosAngle;	fM[1][2] = 0.0;
	fM[2][0] = 0.0;			fM[2][1] = 0.0;			fM[2][2] = 1.0;

} // TransfMatrix3D::SetToRotationMatrix_XY

//========================================================================================
// rotate around the X axis, from Y to Z
void TransfMatrix3D::SetToRotationMatrix_YZ(const double aAngle)
{
	SetToIdentity();
	double sinAngle = sin(aAngle);
	double cosAngle = cos(aAngle);
	fM[0][0] = cosAngle;	fM[0][1] = -sinAngle;   fM[0][2] = 0.0;
	fM[1][0] = sinAngle;	fM[1][1] = cosAngle;	fM[1][2] = 0.0;
	fM[2][0] = 0.0;			fM[2][1] = 0.0;			fM[2][2] = 1.0;
} // TransfMatrix3D::SetToRotationMatrix_XY

//========================================================================================
// rotate around the Y axis, from Z to X
void TransfMatrix3D::SetToRotationMatrix_ZX(const double aAngle)
{
	SetToIdentity();
	double sinAngle = sin(aAngle);
	double cosAngle = cos(aAngle);
	fM[0][0] = cosAngle;	fM[0][1] = 0.0;			fM[0][2] = sinAngle;
	fM[1][0] = 0.0;			fM[1][1] = 1.0;			fM[1][2] = 0.0;
	fM[2][0] = -sinAngle;	fM[2][1] = 0.0;			fM[2][2] = cosAngle;
} // TransfMatrix3D::SetToRotationMatrix_XY

//========================================================================================
TransfMatrix3D TransfMatrix3D::MatrixMatrixMultiply(const TransfMatrix3D aMatrix)
{
	TransfMatrix3D result;
	for (int i = 0; i < 4;i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.fM[i][j] = 0.0;
			for (int k = 0; k < 4; k++)
			{
				result.fM[i][j] += fM[i][k] * aMatrix.fM[k][j];
			} // loop to compute the dot product
		}// loop through cols of the result
	}  // loop through rows of the result
	return result;
} // TransfMatrix3D::MatrixMatrixMultiply

//========================================================================================
//========================================================================================
