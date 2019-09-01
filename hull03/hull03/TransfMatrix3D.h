#pragma once
class TransfMatrix3D
{
private:
	double fM[4][4];

public:
	TransfMatrix3D();
	TransfMatrix3D(TransfMatrix3D & aSource);
	~TransfMatrix3D();

	void SetToIdentity();
	void SetToTranslationMatrix(const double aDx, const double aDy, const double aDz);
	void SetToRotationMatrix_XY(const double aAngle);
	void SetToRotationMatrix_YZ(const double aAngle);
	void SetToRotationMatrix_ZX(const double aAngle);

	TransfMatrix3D MatrixMatrixMultiply(const TransfMatrix3D aMatrix);
}; // class TransfMatrix3D

