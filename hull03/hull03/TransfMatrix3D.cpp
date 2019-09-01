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
double TransfMatrix3D::At(const int aRow, const int aCol)
{
	double result = 0.0;
	if ((0 <= aRow) && (aRow <= 3) && (0 <= aCol) && (aCol <= 3))
	{
		result = fM[aRow][aCol];
	}
	return result;
} // TransfMatrix3D::At

//========================================================================================
void TransfMatrix3D::CopyFrom(const TransfMatrix3D aSource)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fM[i][j] = aSource.fM[i][j];
		} // loop through cols
	} // loop through rows
} // TransfMatrix3D::CopyFrom(

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
void TransfMatrix3D::SwapRows(const int aRow1, const int aRow2)
{
	if ((0 <= aRow1) && (aRow1 <= 3) && (0 <= aRow2) && (aRow2 <= 3) && (aRow1 != aRow2))
	{
		for (int j = 0; j < 4; j++)
		{
			double temp = fM[aRow1][j];
			fM[aRow1][j] = fM[aRow2][j];
			fM[aRow2][j] = temp;
		} //loop through the columns
	} // if the inputs are valid
} // TransfMatrix3D::SwapRows

//========================================================================================
void TransfMatrix3D::DivideRowBy(const int aRow1, const double aDivisor)
{
	if ((0 <= aRow1) && (aRow1 <= 3) && (aDivisor != 0.0))
	{
		for (int j = 0; j < 4; j++)
		{
			fM[aRow1][j] /= aDivisor;
		} //loop through the columns
	} // if the inputs are valid
} // TransfMatrix3D::DivideRowBy

//========================================================================================
void TransfMatrix3D::AddMultipleOfRow(const int aRow1, const double aMultiplier, const int aRow2)
{
	if ((0 <= aRow1) && (aRow1 <= 3) && (0 <= aRow2) && (aRow2 <= 3))
	{
		for (int j = 0; j < 4; j++)
		{
			fM[aRow2][j] += fM[aRow1][j] * aMultiplier;
		} //loop through the columns
	} // if the inputs are valid
} // TransfMatrix3D::AddMultipleOfRow

//========================================================================================
bool TransfMatrix3D::Invert()
{
	TransfMatrix3D workingCopy(*this);
	TransfMatrix3D backupCopy(*this);
	bool ok = true;
	SetToIdentity();

	for (int iCol = 0; (iCol < 4) && ok; iCol++)
	{
		// find the pivot element in this column
		int iPvt = 0;
		double bestValue = abs(workingCopy.fM[0][iCol]);
		for (int iSearch = 1; iSearch < 4; iSearch++)
		{
			double thisValue = abs(workingCopy.fM[iSearch][iCol]);
			if (thisValue > bestValue)
			{
				iPvt = iSearch;
				bestValue = thisValue;
			} // if the magnitude of this entry is larger
		}// loop through the rows

		ok = (bestValue != 0.0);
		if (ok)
		{
			// swap the pivot row into position
			SwapRows(iCol, iPvt);
			workingCopy.SwapRows(iCol, iPvt);

			// divide the pivot row by the pivot element
			double value = workingCopy.fM[iCol][iCol];
			DivideRowBy(iCol, value);
			workingCopy.DivideRowBy(iCol, value);

			// subtract a multiple of the pivot row from the other rows
			for (int iRow = 0; iRow < 4;iRow++)
			{
				if (iRow != iCol)
				{
					value = workingCopy.fM[iRow][iCol];
					AddMultipleOfRow(iCol, -value, iRow);
					workingCopy.AddMultipleOfRow(iCol, -value, iRow);
				} // if this index iRow is not the pivot row
			} // loop through the rows
		} // if ok
	} // loop through the columns
	
	if (!ok)
	{
		CopyFrom(backupCopy);
	} // if something went wrong
	
	return ok;
} // TransfMatrix3D::Invert


//========================================================================================
//========================================================================================
//========================================================================================
//========================================================================================
//========================================================================================
//========================================================================================


