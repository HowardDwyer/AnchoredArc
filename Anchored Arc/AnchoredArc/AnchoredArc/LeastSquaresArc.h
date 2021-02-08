#pragma once

#include "stdafx.h" 
#include <vector>
#include <tuple>
#include <algorithm>

//====================================================================================
// Utilities
//====================================================================================
const double kRelTol = 1.0e-5;

inline bool NearlyEqual(const double a, const double b)
{
	const double maxValue = max(abs(a), abs(b));
	return (abs(a - b) < kRelTol*maxValue);
} // NearlyEqual

//====================================================================================
// Classes
//====================================================================================
class Point{
public:
	Point(){ SetX(0.0); SetY(0.0); }
	Point(const double initX, const double initY){ SetX(initX); SetY(initY); }
	Point(const Point& source){ Set(source); }
	
	double X()const{ return fX; }
	double Y()const{ return fY; }
	void SetX(const double value){ fX = value; }
	void SetY(const double value){ fY = value; }
	void Set(const Point& value){ SetX(value.X()); SetY(value.Y()); }
	double DistFrom(const Point& otherP)const;
	double Dot(const Point& otherP)const;
	bool operator == (const Point& other);
	void operator += (const Point& other);
	void operator -= (const Point& other);
	void operator *= (const double factor);
	void operator /= (const double divisor);
	Point operator + (const Point& RHS);
	Point operator - (const Point& RHS);

private:
	double fX = 0;
	double fY = 0;
}; // class Point

//====================================================================================
class SetOfPoints{
public:
	SetOfPoints();
	SetOfPoints(const std::vector<Point>& initList){ LoadList(initList); }
	SetOfPoints(const SetOfPoints& initSet);

	Point At(const int index)const{ return fPointList.at(index); }
	int Size()const{ return fPointList.size(); }
	bool Empty()const { return fPointList.empty(); }
	void Clear() { fPointList.clear(); }
	void Append(const Point& newPoint);
	void LoadList(const std::vector<Point>& newList);

private:
	std::vector<Point> fPointList;
}; // class SetOfPoints

//====================================================================================
class Circle{
public:
	Circle(){ SetRadius(0.0); SetCenterX(0.0); SetCenterY(0.0); }
	Circle(const Point& C, const double R){ SetRadius(R); SetCenter(C); }
	Circle(const Circle& source){ SetRadius(source.Radius()); SetCenter(source.Center()); }

	double Radius()const { return fRadius; }
	double CenterX()const { return fCenter.X(); }
	double CenterY()const { return fCenter.Y(); }
	Point Center()const { return fCenter; }
	void SetRadius(const double value) { fRadius = abs(value); }
	void SetCenterX(const double value) { fCenter.SetX(value); }
	void SetCenterY(const double value) { fCenter.SetY(value); }
	void SetCenter(const Point& value) { fCenter.Set(value); }
	double DistFrom(const Point& P)const;
	bool IsPointOnCircle(const Point& P)const;
	bool operator == (const Circle& other);

private:
	double fRadius = 0.0;
	Point fCenter;
}; // class Circle

//====================================================================================
class Matrix3X3{
public:
	Matrix3X3(){};
	void SetToIdentity();

	double At(const int iRow, const int iColumn)const { return fValues[iRow][iColumn]; }
	void Set(const int iRow, const int iColumn, const double value) { fValues[iRow][iColumn] = value; }

	Matrix3X3 operator *(const Matrix3X3& RHS)const;
	Point TransformPoint(const Point& P)const;

private:
	double fValues[3][3];
}; // class Matrix3X3

//====================================================================================
class AnchoredArcProblem{
public:
	AnchoredArcProblem();
	AnchoredArcProblem(const Point& A, const Point& B, const SetOfPoints& ptList)
	{ SetProblem(A, B, ptList);	}

	void SetProblem(const Point& A, const Point& B, const SetOfPoints& ptList);
	void SetPointA(const Point& value){ fA = value; }
	void SetPointB(const Point& value){ fB = value; }
	void AppendToPointList(const Point& value){ fPointsList.Append(value); }
	void SetPointList(const SetOfPoints& value){ fPointsList = value; }

	Point A()const { return fA; }
	Point B()const { return fB; }
	Point P(const int index)const { return fPointsList.At(index); }
	int NumOfPoints()const{ return fPointsList.Size(); }
	std::tuple<bool, Circle> Solve();

private:
	void BuildTransformMatrices();
	std::tuple<double, double, double, double> FormSums()const; // [sumX2Y, sumY3, sumY, sumY2]
	bool PointsAreCollinear()const;

	Point fA;
	Point fB;
	SetOfPoints fPointsList;
	Matrix3X3 fT;
	Matrix3X3 fInvT;
};  // class AnchoredArcProblem

//====================================================================================
