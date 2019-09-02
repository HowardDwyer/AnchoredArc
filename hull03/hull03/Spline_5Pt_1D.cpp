#include "stdafx.h"
#include "Spline_5Pt_1D.h"
#include "HullConst.h"

//====================================================================================
Spline_5Pt_1D::Spline_5Pt_1D()
{
	Reset();
} // Spline_5Pt_1D::Spline_5Pt_1D

//====================================================================================
Spline_5Pt_1D::Spline_5Pt_1D(
	const double aP0,  // value at t = 0
	const double aP1,  // value at t = 1
	const double aP2,  // value at t = 2
	const double aP3,  // value at t = 3
	const double aP4)  // value at t = 4
{
	ConstructCoefficients(aP0, aP1, aP2, aP3, aP4);
} // Spline_5Pt_1D::Spline_5Pt_1D

//====================================================================================
Spline_5Pt_1D::~Spline_5Pt_1D()
{
} // Spline_5Pt_1D::~Spline_5Pt_1D

//====================================================================================
void Spline_5Pt_1D::Reset()
{
	fIsDefined = false;
	fExtentsComputed = false;
	fMinValue = 0.0;
	fMaxValue = 0.0;
	for (int i = 0; i < 5; i++)
	{
		fCoeffA[i] = 0.0;
		fCoeffB[i] = 0.0;
		fCoeffC[i] = 0.0;
		fCoeffD[i] = 0.0;
	}
} // Spline_5Pt_1D::Reset

//====================================================================================
void Spline_5Pt_1D::ConstructCoefficients(
	const double aP0,  // value at t = 0
	const double aP1,  // value at t = 1
	const double aP2,  // value at t = 2
	const double aP3,  // value at t = 3
	const double aP4)  // value at t = 4
{
	fExtentsComputed = false;
	fMinValue = 0.0;
	fMaxValue = 0.0;

	// the A coefficients are simply the node values
	fCoeffA[0] = aP0;
	fCoeffA[1] = aP1;
	fCoeffA[2] = aP2;
	fCoeffA[3] = aP3;
	fCoeffA[4] = aP4;

	// we compute the C coefficients next, as the solution to a linear system
	// because the matrix is the same for all splines with 5 equally spaced nodes
	// we can compute the inverse matrix (once, by hand) and use it to solve the system

	// we compute the constants vector for the linear system
	double k[5];
	k[0] = 0.0;
	k[1] = 3.0 * (aP2 - 2.0 * aP1 + aP0);
	k[2] = 3.0 * (aP3 - 2.0 * aP2 + aP1);
	k[3] = 3.0 * (aP4 - 2.0 * aP3 + aP2);
	k[4] = 0.0;

	// we compute the c coefficients
	// we do this by a linear combination of the constant column, based on the inverse matrix
	// we compute a value for c[4] even though there is no poly segment #4
	// we will use this "pretend" c value in computing other coefficients
	fCoeffC[0] = 0.0;
	fCoeffC[1] = (-15.0 * k[0] + 15.0 * k[1] - 4.0 * k[2] + 1.0 * k[3] - 1.0 * k[4]) / 56.0;
	fCoeffC[2] = (4.0 * k[0] - 4.0 * k[1] + 16.0 * k[2] - 4.0 * k[3] + 4.0 * k[4]) / 56.0;
	fCoeffC[3] = (-1.0 * k[0] + 1.0 * k[1] - 4.0 * k[2] + 15.0 * k[3] - 15.0 * k[4]) / 56.0;
	fCoeffC[4] = 0.0;

	// compute the D coefficients
	fCoeffD[0] = (fCoeffC[1] - fCoeffC[0]) / 3.0;
	fCoeffD[1] = (fCoeffC[2] - fCoeffC[1]) / 3.0;
	fCoeffD[2] = (fCoeffC[3] - fCoeffC[2]) / 3.0;
	fCoeffD[3] = (fCoeffC[4] - fCoeffC[3]) / 3.0;
	fCoeffD[4] = 0.0;  // not used

	// compute the b coefficients
	fCoeffB[0] = aP1 - aP0 - (2.0 * fCoeffC[0] + fCoeffC[1]) / 3.0;
	fCoeffB[1] = aP2 - aP1 - (2.0 * fCoeffC[1] + fCoeffC[2]) / 3.0;
	fCoeffB[2] = aP3 - aP2 - (2.0 * fCoeffC[2] + fCoeffC[3]) / 3.0;
	fCoeffB[3] = aP4 - aP3 - (2.0 * fCoeffC[3] + fCoeffC[4]) / 3.0;
	fCoeffB[4] = 0.0;  //not used

	fIsDefined = true;
} // Spline_5Pt_1D::ConstructCoefficients

//====================================================================================
double Spline_5Pt_1D::P(const double aT)
{
	double returnValue = 0.0; // default value if spline is not defined
	double deltaT = 0.0;
	int segment = 0;
	if (fIsDefined)
	{
		if (aT<0.0)
		{
			// extrapolate before the first spline point 
			returnValue = fCoeffA[0] + fCoeffB[0] * aT;
		} // if T < 0
		else if (aT > 4.0)
		{
			// extrapolate after the last spline point
			returnValue = fCoeffA[4] + (fCoeffB[3] + 2.0*fCoeffC[3] + 3.0*fCoeffD[3]) * (aT - 4.0);
		} // if T > 4
		else
		{
			// 0 <= T <= 4
			if ((0.0 <= aT) && (aT < 1.0))
			{
				segment = 0;
				deltaT = aT - 0.0;
			}
			else if ((1.0 <= aT) && (aT < 2.0))
			{
				segment = 1;
				deltaT = aT - 1.0;
			}
			else if ((2.0 <= aT) && (aT < 3.0))
			{
				segment = 2;
				deltaT = aT - 2.0;
			}
			else if ((3.0 <= aT) && (aT < 4.0))
			{
				segment = 3;
				deltaT = aT - 3.0;
			}
			// evaluate the cubic poly using Horner's method.
			returnValue = ((fCoeffD[segment] * deltaT + fCoeffC[segment]) * deltaT 
				+ fCoeffB[segment]) * deltaT + fCoeffA[segment];
		}// if 0 <= T <= 4
	} // if the spline is defined
	return (returnValue);
} // Spline_5Pt_1D::P

//====================================================================================
// a simple step search is used to get approximate values for the minimum and maximum.
// TODO: Use the derivative to find local max/min.
void Spline_5Pt_1D::FindMinMax()
{
	if (!fIsDefined)
	{ 
		fExtentsComputed = false;
		fMinValue = 0.0;
		fMaxValue = 0.0;
	} // if the spline is not defined
	else
	{
		double dT = 4.0 / HullConst::NUMSEARCHSTEPS;
		fExtentsComputed = true;
		fMinValue = P(0.0);
		fMaxValue = fMinValue;
		for (int i = 1; i <= HullConst::NUMSEARCHSTEPS; i++)
		{
			double thisValue = P(dT * i);
			if (thisValue < fMinValue)
			{
				fMinValue = thisValue;
			}
			else if (thisValue > fMaxValue)
			{
				fMaxValue = thisValue;
			}
		} // loop through the search steps
	} // if the spline is defined
} // Spline_5Pt_1D::FindMinMax

//====================================================================================
double Spline_5Pt_1D::MinValue()
{
	if (!fExtentsComputed){ FindMinMax(); }
	return fMinValue;
} // Spline_5Pt_1D::MinValue

//====================================================================================
double Spline_5Pt_1D::MaxValue()
{
	if (!fExtentsComputed){ FindMinMax(); }
	return fMaxValue;
} // Spline_5Pt_1D::MaxValue

//====================================================================================
bool Spline_5Pt_1D::FindFirst(const double aTarget, double* aT)
{
	bool foundLowT = false;
	bool foundHighT = false;
	double lowValue, highValue, lowT, highT;
	//================================================================================
	double dT = 4.0 / HullConst::NUMSEARCHSTEPS;
	for (int i = 1; (i <= HullConst::NUMSEARCHSTEPS) && (!foundLowT) && (!foundHighT); i++)
	{
		double thisT = dT * i;
		double thisValue = P(thisT);
		
		if (abs(thisValue - aTarget) < HullConst::VERYSMALL())
		{
			*aT = thisT;
			return true;
		} // if this value is (approx) equal to the target
		else if (thisValue < aTarget)
		{
			if (foundLowT) 
			{   
				// we already have a lower bound.  see if this is better.
				if (lowValue < thisValue)
				{ 
					lowValue = thisValue; 
					lowT = thisT; 
				}
			}
			else
			{
				// this is our first lower bound.
				lowValue = thisValue;
				lowT = thisT;
				foundLowT = true;
			}
		} // if this value is less than the target
		else if (thisValue > aTarget)
		{
			if (foundHighT)
			{
				// we already have an upper bound.  see if this is better.
				if (highValue > thisValue)
				{
					highValue = thisValue;
					highT = thisT;
				}
			}
			else
			{
				// this is our first upper bound.
				highValue = thisValue;
				highT = thisT;
				foundHighT = true;
			}
		} // if this value is less than the target
	} // loop through the search steps
	//==============================================================================
	if (foundLowT && foundHighT)
	{
		int maxNumberOfBisections = 20;
		for (int i = 1; i <= maxNumberOfBisections; i++)
		{
			double thisT = (lowT + highT) * 0.5;
			double thisValue = P(thisT);
			if (abs(thisValue - aTarget) < HullConst::VERYSMALL())
			{
				*aT = thisT;
				return true;
			} // if this value is (approx) equal to the target
			else if (thisValue < aTarget)
			{
				lowT = thisT;
				lowValue = thisValue;
			} // if this value is less than the target
			else if (thisValue > aTarget)
			{
				highT = thisT;
				highValue = thisValue;
			} // if this value is less than the target
		} // loop through bisections to refine  the result

		// if we get here then still have not refined the value of T sufficiently to match
		// the target value closely enough.  Send back our best guess.
		if ((highValue-aTarget) < (aTarget-lowValue))
		{ 
			*aT = highT;
		}
		else
		{ 
			*aT = lowT;
		}
		return true;
	} // we have a bracket on the target
	return false;
} // Spline_5Pt_1D::FindFirst

//====================================================================================
//====================================================================================
//====================================================================================
//====================================================================================
//====================================================================================
//====================================================================================
//====================================================================================
