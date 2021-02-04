#include "stdafx.h"
#include "TransfMatrix3D.h"
#include "FreeVector3D.h"
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
TransfMatrix3D::TransfMatrix3D(const TransfMatrix3D & aSource)
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
double TransfMatrix3D::At(const int aRow, const int aCol) const
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
	const double sinAngle = sin(aAngle);
	const double cosAngle = cos(aAngle);
	fM[0][0] = cosAngle;	fM[0][1] = -sinAngle;   fM[0][2] = 0.0;
	fM[1][0] = sinAngle;	fM[1][1] = cosAngle;	fM[1][2] = 0.0;
	fM[2][0] = 0.0;			fM[2][1] = 0.0;			fM[2][2] = 1.0;

} // TransfMatrix3D::SetToRotationMatrix_XY

//========================================================================================
// rotate around the X axis, from Y to Z
void TransfMatrix3D::SetToRotationMatrix_YZ(const double aAngle)
{
	SetToIdentity();
	const double sinAngle = sin(aAngle);
	const double cosAngle = cos(aAngle);
	fM[0][0] = cosAngle;	fM[0][1] = -sinAngle;   fM[0][2] = 0.0;
	fM[1][0] = sinAngle;	fM[1][1] = cosAngle;	fM[1][2] = 0.0;
	fM[2][0] = 0.0;			fM[2][1] = 0.0;			fM[2][2] = 1.0;
} // TransfMatrix3D::SetToRotationMatrix_XY

//========================================================================================
// rotate around the Y axis, from Z to X
void TransfMatrix3D::SetToRotationMatrix_ZX(const double aAngle)
{
	SetToIdentity();
	const double sinAngle = sin(aAngle);
	const double cosAngle = cos(aAngle);
	fM[0][0] = cosAngle;	fM[0][1] = 0.0;			fM[0][2] = sinAngle;
	fM[1][0] = 0.0;			fM[1][1] = 1.0;			fM[1][2] = 0.0;
	fM[2][0] = -sinAngle;	fM[2][1] = 0.0;			fM[2][2] = cosAngle;
} // TransfMatrix3D::SetToRotationMatrix_XY

//========================================================================================
void TransfMatrix3D::SetToRotateToVerticalUp(
	const double & p0X,
    const double & p0Y,
    const double & p0Z,
    const double & p1X,
    const double & p1Y,
    const double & p1Z)
{
	TransfMatrix3D mResult;
	mResult.SetToIdentity();
	if ((p0X != p1X) || (p0Y != p1Y) || (p0Z != p1Z) ){
		FreeVector3D zAxis(0.0, 0.0, 1.0);

		TransfMatrix3D m1, m1Inverse;
		m1.SetToTranslationMatrix(-p0X, -p0Y, -p0Z);
		m1Inverse.SetToTranslationMatrix(p0X, p0Y, p0Z);
		
		TransfMatrix3D m2;
		m2.SetToIdentity();

		FreeVector3D rotatedZAxis((p1X - p0X), (p1Y - p0Y), (p1Z - p0Z));
		const bool alreadyParallel = rotatedZAxis.IsParallelTo(zAxis);
		if (!alreadyParallel || (rotatedZAxis.Z() < 0.0)){
			rotatedZAxis.Normalize();
			FreeVector3D rotatedXAxis(1.0, 0.0, 0.0);
			if (!alreadyParallel){
				rotatedXAxis = rotatedZAxis.Cross(zAxis);
				rotatedXAxis.Normalize();
			}
			FreeVector3D rotatedYAxis = rotatedZAxis.Cross(rotatedXAxis);
			rotatedYAxis.Normalize();
			m2.fM[0][0] = rotatedXAxis.X();
			m2.fM[0][1] = rotatedXAxis.Y();
			m2.fM[0][2] = rotatedXAxis.Z();

			m2.fM[1][0] = rotatedYAxis.X();
			m2.fM[1][1] = rotatedYAxis.Y();
			m2.fM[1][2] = rotatedYAxis.Z();

			m2.fM[2][0] = rotatedZAxis.X();
			m2.fM[2][1] = rotatedZAxis.Y();
			m2.fM[2][2] = rotatedZAxis.Z();

			mResult = m1Inverse.MatrixMatrixMultiply(m2.MatrixMatrixMultiply(m1));
		} // if p1Prime is not already parallel to the Z axis
	} // if p0 and p1 are distinct
	CopyFrom(mResult);
} // TransfMatrix3D::SetToRotateToVerticalUp

//========================================================================================
TransfMatrix3D TransfMatrix3D::MatrixMatrixMultiply(const TransfMatrix3D aMatrix) const
{
	TransfMatrix3D result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.fM[i][j] = 0.0;
			for (int k = 0; k < 4; k++)
			{
				result.fM[i][j] += fM[i][k] * aMatrix.fM[k][j];
			} // loop to compute the dot product
		} // loop through cols of the result
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
			const double temp = fM[aRow1][j];
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
		const double scale = 1.0 / aDivisor;
		for (int j = 0; j < 4; j++)
		{
			fM[aRow1][j] *= scale;
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
TransfMatrix3D TransfMatrix3D::Invert() const
{
	TransfMatrix3D workingCopy(*this);
	TransfMatrix3D resultMatrix;
	bool ok = true;
	resultMatrix.SetToIdentity();

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
			resultMatrix.SwapRows(iCol, iPvt);
			workingCopy.SwapRows(iCol, iPvt);

			// divide the pivot row by the pivot element
			double value = workingCopy.fM[iCol][iCol];
			resultMatrix.DivideRowBy(iCol, value);
			workingCopy.DivideRowBy(iCol, value);

			// subtract a multiple of the pivot row from the other rows
			for (int iRow = 0; iRow < 4; iRow++)
			{
				if (iRow != iCol)
				{
					value = workingCopy.fM[iRow][iCol];
					resultMatrix.AddMultipleOfRow(iCol, -value, iRow);
					workingCopy.AddMultipleOfRow(iCol, -value, iRow);
				} // if this index iRow is not the pivot row
			} // loop through the rows
		} // if ok
	} // loop through the columns

	if (!ok){
		resultMatrix.SetToIdentity();
	}
	return resultMatrix;
} // TransfMatrix3D::Invert

//========================================================================================
//========================================================================================
//========================================================================================
//========================================================================================
//========================================================================================
//========================================================================================


