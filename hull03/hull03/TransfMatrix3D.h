#pragma once

class TransfMatrix3D
{
private:
	double fM[4][4];
	void SwapRows(const int aRow1, const int aRow2);
	void DivideRowBy(const int aRow1, const double aDivisor);
	void AddMultipleOfRow(
		const int aRow1,
		const double aMultiplier,
		const int aRow2);

public:
	TransfMatrix3D();
	TransfMatrix3D(const TransfMatrix3D & aSource);
	~TransfMatrix3D();

	double At(const int aRow, const int aCol) const;

	void SetToIdentity();
	void SetToTranslationMatrix(
		const double aDx,
		const double aDy,
		const double aDz);

	void SetToRotationMatrix_XY(const double aAngle);
	void SetToRotationMatrix_YZ(const double aAngle);
	void SetToRotationMatrix_ZX(const double aAngle);
	void SetToRotateToVerticalUp(
		const double & p0X, 
		const double & p0Y, 
		const double & p0Z, 
		const double & p1X, 
		const double & p1Y, 
		const double & p1Z);
	void CopyFrom(const TransfMatrix3D aSource);
	TransfMatrix3D Invert() const;

	TransfMatrix3D MatrixMatrixMultiply(const TransfMatrix3D aMatrix) const;

}; // class TransfMatrix3D

