#pragma once

//=============================================================================================
// this class implements a cubic spline through 5 node points
// the node points are equally spaced at t=0, t=1, t=2, t=3, t=4
// the spline uses free (unclamped) end conditions for both ends
//=============================================================================================

class Spline_5Pt_1D
{
private:
	bool fIsDefined;
	mutable bool fExtentsComputed;
	mutable double fMinValue;
	mutable double fMaxValue;

	double fCoeffA[5];
	double fCoeffB[5];
	double fCoeffC[5];
	double fCoeffD[5];

	void FindMinMax() const;
public:
	Spline_5Pt_1D();
	
	Spline_5Pt_1D(
		const double aP0, 
		const double aP1, 
		const double aP2,
		const double aP3, 
		const double aP4);

	~Spline_5Pt_1D();

	void Reset();
	
	void ConstructCoefficients(
		const double aP0, 
		const double aP1, 
		const double aP2,
		const double aP3, 
		const double aP4);

	double P(const double aT) const;

	double MinValue() const;
	double MaxValue() const;
	bool FindFirst(const double aTarget, double* aT) const;

	bool Defined() const
	{ 
		return fIsDefined; 
	}

	bool ExtentsComputed() const
	{
		return fExtentsComputed; 
	}

}; // class Spline_5Pt_1D

