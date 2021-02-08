#include "stdafx.h" ;
#include "LeastSquaresArc.h"

//====================================================================================
//   Point
//====================================================================================
double Point::DistFrom(const Point& otherP)const
{
	return sqrt((X() - otherP.X())*(X() - otherP.X()) + (Y() - otherP.Y())*(Y() - otherP.Y()));
} // Point::DistFrom

//====================================================================================
double Point::Dot(const Point& otherP)const
{
	return (X() * otherP.X()) + (Y() * otherP.Y());
} // Point::Dot

//====================================================================================
bool Point::operator == (const Point& other)
{
	return NearlyEqual(X(), other.X()) && NearlyEqual(Y(), other.Y());
} // Point::operator ==

//====================================================================================
void Point::operator += (const Point& other)
{
	SetX(X() + other.X());
	SetY(Y() + other.Y());
} // Point::operator +=

//====================================================================================
void Point::operator -= (const Point& other)
{
	SetX(X() - other.X());
	SetY(Y() - other.Y());
} // Point::operator -=

//====================================================================================
void Point::operator *= (const double factor)
{
	SetX(X()*factor);
	SetY(Y()*factor);
} // Point::operator *= 

//====================================================================================
void Point::operator /= (const double divisor)
{
	SetX(X() / divisor);
	SetY(Y() / divisor);
} // Point::operator /=

//====================================================================================
Point Point::operator + (const Point& RHS)
{
	Point result(X() + RHS.X(), Y() + RHS.Y());
	return result;
} // Point::operator +

//====================================================================================
Point Point::operator - (const Point& RHS)
{
	Point result(X() - RHS.X(), Y() - RHS.Y());
	return result;
} // Point::operator -

//====================================================================================
//   SetOfPoints
//====================================================================================
SetOfPoints::SetOfPoints(const SetOfPoints& initSet)
{
	LoadList(initSet.fPointList);
} // SetOfPoints::SetOfPoints

//====================================================================================
void SetOfPoints::Append(const Point& newPoint)
{
	fPointList.push_back(newPoint);
} // SetOfPoints::Append

//====================================================================================
void SetOfPoints::LoadList(const std::vector<Point>& newList)
{
	fPointList = newList;
} // SetOfPoints::LoadList

//====================================================================================
//   Circle
//====================================================================================
bool Circle::IsPointOnCircle(const Point& P)const
{
	return NearlyEqual(DistFrom(P), 0.0);
} // Circle::IsPointOnCircle

//====================================================================================
double Circle::DistFrom(const Point& P)const
{
	return abs(Radius() - Center().DistFrom(P));
} // Circle::DistFrom

//====================================================================================
bool Circle::operator == (const Circle& other)
{
	return NearlyEqual(Radius(), other.Radius()) && (Center() == other.Center());
} // Circle::operator ==

//====================================================================================
//   Matrix3X3
//====================================================================================
void Matrix3X3::SetToIdentity()
{
	for (int iRow = 0; iRow < 3; iRow++)
	{
		for (int iColumn = 0; iColumn < 3; iColumn++)
		{
			fValues[iRow][iColumn] = 0.0;
		}
		fValues[iRow][iRow] = 1.0;
	}
} // atrix3X3::SetToIdentity

//====================================================================================
Matrix3X3 Matrix3X3::operator *(const Matrix3X3& RHS)const
{
	Matrix3X3 result;
	for (int iRow = 0; iRow < 3; iRow++)
	{
		for (int iColumn = 0; iColumn < 3; iColumn++)
		{
			double dot = 0.0;
			for (int j = 0; j < 3; j++)
			{
				dot += At(iRow, j)*RHS.At(j, iColumn);
			}
			result.Set(iRow, iColumn, dot);
		}
	}
	return result;
} // Matrix3X3::operator *

//====================================================================================
Point Matrix3X3::TransformPoint(const Point& P)const
{
	Point result;
	double dot = At(0, 0)*P.X() + At(0, 1)*P.Y() + At(0, 2);
	result.SetX(dot);
	dot = At(1, 0)*P.X() + At(1, 1)*P.Y() + At(1, 2);
	result.SetY(dot);
	return result;
} // Matrix3X3::TransformPoint

//====================================================================================
//   AnchoredArcProblem
//====================================================================================
void AnchoredArcProblem::SetProblem(const Point& A, const Point& B, const SetOfPoints& ptList)
{
	SetPointA(A);
	SetPointB(B);
	SetPointList(ptList);
} // AnchoredArcProblem::SetProblem

//====================================================================================
std::tuple<bool, Circle> AnchoredArcProblem::Solve()
{
	bool success = !PointsAreCollinear();
	Circle bestFit;
	if (success){
		BuildTransformMatrices();
		const std::tuple<double, double, double, double> sums = FormSums();
		const double sumX2Y = std::get<0>(sums);
		const double sumY3 = std::get<1>(sums);
		const double sumY = std::get<2>(sums);
		const double sumY2 = std::get<3>(sums);

		const double tValue = (sumX2Y+sumY3+sumY) / (2.0*sumY2);
		const Point transformedCircleCenter(0.0, tValue);
		const Point circleCenter = fInvT.TransformPoint(transformedCircleCenter);
		const double rA = A().DistFrom(circleCenter);
		const double rB = B().DistFrom(circleCenter);
		success = NearlyEqual(rA, rB);
		if (success){
			bestFit = Circle(circleCenter, rA);
		}
	}
	std::tuple<bool, Circle> result{ success, bestFit };
	return result;
} // AnchoredArcProblem::Solve

//====================================================================================
void AnchoredArcProblem::BuildTransformMatrices()
{
	Matrix3X3 T1, T2, T3, invT1, invT2, invT3;
	//------------------------------------------------------
	// translation matrices
	Point midPoint = fA + fB;
	midPoint *= 0.5;
	T1.SetToIdentity();
	T1.Set(0, 2, -midPoint.X());
	T1.Set(1, 2, -midPoint.Y());
	invT1.SetToIdentity();
	invT1.Set(0, 2, midPoint.X());
	invT1.Set(1, 2, midPoint.Y());
	//------------------------------------------------------
	// scaling matrices
	const Point aPrime = T1.TransformPoint(fA);
	const double reciprocalScale = sqrt(aPrime.X()*aPrime.X() + aPrime.Y()*aPrime.Y());
	const double scale = 1.0 / reciprocalScale;
	T2.SetToIdentity();
	T2.Set(0, 0, scale);
	T2.Set(1, 1, scale);
	invT2.SetToIdentity();
	invT2.Set(0, 0, reciprocalScale);
	invT2.Set(1, 1, reciprocalScale);
	//------------------------------------------------------
	// rotation matrices
	const Point aDoublePrime = T2.TransformPoint(aPrime);
	T3.SetToIdentity();
	T3.Set(0, 0, aDoublePrime.X());
	T3.Set(1, 1, aDoublePrime.X());
	T3.Set(0, 1, aDoublePrime.Y());
	T3.Set(1, 0, -aDoublePrime.Y());
	invT3.SetToIdentity();
	invT3.Set(0, 0, aDoublePrime.X());
	invT3.Set(1, 1, aDoublePrime.X());
	invT3.Set(0, 1, -aDoublePrime.Y());
	invT3.Set(1, 0, aDoublePrime.Y());
	//------------------------------------------------------
	fT = T3*T2*T1;
	fInvT = invT1*invT2*invT3;
} // AnchoredArcProblem::BuildTransformMatrices

//====================================================================================
std::tuple<double, double, double, double> AnchoredArcProblem::FormSums()const
{
	double sumX2Y = 0.0;
	double sumY3 = 0.0;
	double sumY = 0.0;
	double sumY2 = 0.0;
	const int numPoints = fPointsList.Size();
	for (int index = 0; index < numPoints;index++)
	{
		const Point transformedPoint = fT.TransformPoint(fPointsList.At(index));
		sumX2Y += transformedPoint.X()*transformedPoint.X()*transformedPoint.Y();
		sumY3 += transformedPoint.Y()*transformedPoint.Y()*transformedPoint.Y();
		sumY += transformedPoint.Y();
		sumY2 += transformedPoint.Y()*transformedPoint.Y();
	}
	std::tuple<double, double, double, double> result{ sumX2Y, sumY3, sumY, sumY2 };
	return result;
} // AnchoredArcProblem::FormSums

//====================================================================================
bool AnchoredArcProblem::PointsAreCollinear()const
{
	bool result = true;
	if ( !( A() == B() ) && (NumOfPoints()>0) ){
		const Point chordVec = B() - A();
		const double chordVecLength = sqrt(chordVec.X()*chordVec.X() + chordVec.Y()*chordVec.Y());
		Point unitChordVec = chordVec;
		unitChordVec /= chordVecLength;
		for (int index=0; result && (index < NumOfPoints()); index++)
		{
			const Point dirVec = P(index) - A();
			const double dirVecLength = sqrt(dirVec.X()*dirVec.X() + dirVec.Y()*dirVec.Y());
			const double projectedLength = abs(unitChordVec.Dot(dirVec));
			result = NearlyEqual(dirVecLength, projectedLength);
		}
	}
	return result;
} // AnchoredArcProblem::PointsAreCollinear

//====================================================================================
