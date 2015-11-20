using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace hull02
{
    //=============================================================================================
    // this class implements a cubic spline through 5 node points
    // the node points are equally spaced at t=0, t=1, t=2, t=3, t=4
    // the spline uses free (unclamped) end conditions for both ends
    //=============================================================================================
    class Spline5Points1D
    {
        // ======= fields =========================================================================
        public const int NUMNODEPOINTS=5;
        private bool IsDefined = false;
        private double[] aCoeff = new double[NUMNODEPOINTS];
        private double[] bCoeff = new double[NUMNODEPOINTS];
        private double[] cCoeff = new double[NUMNODEPOINTS];
        private double[] dCoeff = new double[NUMNODEPOINTS];

        //=========================================================================================
        public Spline5Points1D()  // default constructor
        {
            IsDefined=false;
            for(int i=0;i<NUMNODEPOINTS;i++)
            {
                aCoeff[i] = 0.0;
                bCoeff[i] = 0.0;
                cCoeff[i] = 0.0;
                dCoeff[i] = 0.0;
            }
        } // end default constructor
        //=========================================================================================
        public Spline5Points1D(double p0, double p1, double p2, double p3, double p4)  // constructor
        {
            IsDefined = true;
            ConstructCoefficients(p0, p1, p2, p3, p4);
        } // end constructor

        // ======= properties ======================================================================
        // ======= methods =========================================================================
        public void ConstructCoefficients(double p0, double p1, double p2, double p3, double p4)
        {
            // the a coefficients are simply the node values
            aCoeff[0] = p0;
            aCoeff[1] = p1;
            aCoeff[2] = p2;
            aCoeff[3] = p3;
            aCoeff[4] = p4; 
            
            // we compute the c coefficents next, as the solution to a linear system
            // because the matrix is the same for all splines with 5 equally spaced nodes
            // we can compute the inverse matrix (once, by hand) and use it to solve the system
            
            // we compute the constants vector for the linear system
            double[] k=new double[NUMNODEPOINTS];
            k[0] = 0.0;
            k[1] = 3.0 * (p2 - 2.0 * p1 + p0);
            k[2] = 3.0 * (p3 - 2.0 * p2 + p1);
            k[3] = 3.0 * (p4 - 2.0 * p3 + p2);
            k[4] = 0.0;
            
            // we compute the c coefficients
            // we do this by a linear combination of the constant column, based on the inverse matrix
            // we compute a value for c[4] even though there is no poly segment #4
            // we will use this "pretend" c value in computing other coefficients
            cCoeff[0] = 0.0;
            cCoeff[1] = (-15.0 * k[0] + 15.0 * k[1] - 4.0 * k[2] + 1.0 * k[3] - 1.0 * k[4]) / 56.0;
            cCoeff[2] = (4.0 * k[0]-4.0 * k[1] + 16.0 * k[2] - 4.0 * k[3] + 4.0 * k[4]) / 56.0;
            cCoeff[3] = (-1.0 * k[0] + 1.0 * k[1] - 4.0 * k[2] + 15.0 * k[3] - 15.0 * k[4]) / 56.0;
            cCoeff[4] = 0.0;

            // compute the d coefficients
            dCoeff[0] = (cCoeff[1] - cCoeff[0]) / 3.0;
            dCoeff[1] = (cCoeff[2] - cCoeff[1]) / 3.0;
            dCoeff[2] = (cCoeff[3] - cCoeff[2]) / 3.0;
            dCoeff[3] = (cCoeff[4] - cCoeff[3]) / 3.0;
            dCoeff[4] = 0.0;  // not used

            // compute the b coefficients
            bCoeff[0] = p1 - p0 - (2.0 * cCoeff[0] + cCoeff[1]) / 3.0;
            bCoeff[1] = p2 - p1 - (2.0 * cCoeff[1] + cCoeff[2]) / 3.0;
            bCoeff[2] = p3 - p2 - (2.0 * cCoeff[2] + cCoeff[3]) / 3.0;
            bCoeff[3] = p4 - p3 - (2.0 * cCoeff[3] + cCoeff[4]) / 3.0;
            bCoeff[4] = 0.0;  //not used

            IsDefined = true;
            return;
        }  // end ConstructCoefficients
        //=========================================================================================
        public double Value(double T)
        {
            double returnValue = 0.0;
            double deltaT = 0.0;
            int segment = 0;
            if (IsDefined)
            {
                if(T<0.0)
                {
                    // extrapolate before the first spline point
                    returnValue = aCoeff[0] + bCoeff[0] * T;
                }
                else if((0.0<=T)&&(T<1.0))
                {
                    // segment 0
                    segment = 0;
                    deltaT = T - 0.0;
                    returnValue=( (dCoeff[segment]*deltaT+cCoeff[segment])*deltaT + bCoeff[segment]) * deltaT + aCoeff[segment];
                }
                else if ((1.0 <= T) && (T < 2.0))
                {
                    // segment 1
                    segment = 1;
                    deltaT = T - 1.0;
                    returnValue = ((dCoeff[segment] * deltaT + cCoeff[segment]) * deltaT + bCoeff[segment]) * deltaT + aCoeff[segment];
                }
                else if ((2.0 <= T) && (T < 3.0))
                {
                    // segment 2
                    segment = 2;
                    deltaT = T - 2.0;
                    returnValue = ((dCoeff[segment] * deltaT + cCoeff[segment]) * deltaT + bCoeff[segment]) * deltaT + aCoeff[segment];
                }
                else if ((3.0 <= T) && (T < 4.0))
                {
                    // segment 3
                    segment = 3;
                    deltaT = T - 3.0;
                    returnValue = ((dCoeff[segment] * deltaT + cCoeff[segment]) * deltaT + bCoeff[segment]) * deltaT + aCoeff[segment];
                }
                else
                {
                    // extrapolate after the last spline point
                    returnValue = aCoeff[4] + (bCoeff[3]+2.0*cCoeff[3]+3.0*dCoeff[3]) * (T-4.0);
                }
            }
            return (returnValue);
        } // end Value
        //=========================================================================================
        public bool FindFirst(double targetValue,double loT,double hiT,ref double targetT)
        {
            // find the first occurrence, if any, of the target value for parameter t values
            // restricted to the interval [loT , hiT]
            bool ok = IsDefined && (hiT > loT);
            targetT = 0.0;
            if (ok)
            {
                double deltaT=(hiT-loT)/((double) hullConst.NUMSEARCHSTEPS);
                bool foundLo = false;  // we have not found a spline value lower than the target
                bool foundHi = false;  // we have not found a spline value higher than the target
                bool bracket = foundLo && foundHi;  // we have a spline value higher, and one lower
                double testT = 0.0;
                double testValue = 0.0;
                double smallValueT = 0.0;
                double bigValueT = 0.0;
                
                // we step across the t interval until we find values on the spline which bracket
                // the target value
                for (int iStep = 0; (iStep <= hullConst.NUMSEARCHSTEPS) && (!bracket); iStep++)
                {
                    // compute the next T value
                    testT = loT + ((double)iStep) * deltaT;
                    // get the corresponding spline value
                    testValue = this.Value(testT);
                    // see if the test value is less than the target
                    if (testValue < targetValue)
                    {
                        // we have a T value which produces a spline value less than the target
                        foundLo = true;
                        smallValueT = testT;
                    }
                    else
                    {
                        // we have a T value which produces a spline value more than the target
                        foundHi = true;
                        bigValueT = testT;
                    }
                    // check to see if we have established a bracket
                    bracket = foundLo && foundHi;
                }// end for 

                if(bracket)
                {
                    // we have now found a T value for which the spline is too small
                    // and another for which the spline is too big
                    // we will employ a bisection search to refine this interval estimate
                    ok = HullUtil.NearEqual(testValue , targetValue);
                    if(ok) targetT=testT;
 
                    bool hopeless = false;
                    while (!ok && !hopeless) 
                    {
                        testT = (smallValueT+bigValueT)/2.0;
                        testValue=this.Value(testT);
                        ok = HullUtil.NearEqual(testValue , targetValue);
                        hopeless = HullUtil.NearEqual(smallValueT,bigValueT);
                        if(ok) 
                        {
                            targetT=testT;
                        } // if(ok) then
                        else
                        {
                            if(testValue<targetValue)
                            {
                                smallValueT=testT;
                            }
                            else
                            {
                                bigValueT=testT;
                            }
                        } // if(ok) else
                    }  // while (!ok && !hopeless)
                } // end if(bracket) then
                else
                {
                    // we failed to bracket the target value
                    ok=false;
                } // end if(bracket) else
            } // end if(ok)
            return (ok);
        } // end FindFirst
        //=========================================================================================
        public void ScaleBy(double scaleFactor)
        {
            // we will not allow a scaling by zero
            if (IsDefined && HullUtil.NotNearZero(scaleFactor))
            {
                double p0 = scaleFactor * aCoeff[0];
                double p1 = scaleFactor * aCoeff[1];
                double p2 = scaleFactor * aCoeff[2];
                double p3 = scaleFactor * aCoeff[3];
                double p4 = scaleFactor * aCoeff[4];
                ConstructCoefficients(p0, p1, p2, p3, p4);
            }
            return;
        } // end ScaleBy
        //=========================================================================================
        public bool Extents(ref double minVal, ref double maxVal)
        {
            bool ok = IsDefined;
            if (ok)
            {
                double testT,testVal;
                double dt=4.0/((double) hullConst.NUMSEARCHSTEPS);
                minVal = this.Value(0.0);
                maxVal = minVal;
                for (int i = 0; i <= hullConst.NUMSEARCHSTEPS;i++)
                {
                    testT=((double) i)*dt;
                    testVal = this.Value(testT);
                    minVal = Math.Min(minVal, testVal);
                    maxVal = Math.Max(maxVal, testVal);
                }
            }
            return (ok);
        }  // end Extents
        //=========================================================================================

    }// end class Spline5Points1D
    //=============================================================================================
}
