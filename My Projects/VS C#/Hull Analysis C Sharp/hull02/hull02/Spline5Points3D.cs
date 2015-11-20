using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace hull02
{
    //=============================================================================================
    // this class implements a 3D parametric cubic spline through 5 node points
    // the node points are equally spaced at t=0, t=1, t=2, t=3, t=4
    // the spline uses free (unclamped) end conditions for both ends
    //=============================================================================================
    class Spline5Points3D :HullGeom
    {
        // ======= fields =========================================================================
        public const int NUMNODEPOINTS= Spline5Points1D.NUMNODEPOINTS;
        private bool IsDefined = false;
        private Spline5Points1D SplineX = new Spline5Points1D();
        private Spline5Points1D SplineY = new Spline5Points1D();
        private Spline5Points1D SplineZ = new Spline5Points1D();
        //=========================================================================================
        public Spline5Points3D()  // default constructor
        {
            DEFAULTCOLOR = System.Drawing.Color.Black;
            IsDefined = false; 
            Visible = true;
            DisplayColor = DEFAULTCOLOR;
        }
        // ======= properties ======================================================================
        public double Length
        {
            // this property is read-only
            get
            {
                double returnValue = 0.0;
                if (IsDefined)
                {
                    double thisX, thisY, thisZ, dx, dy, dz, t;
                    double dt=4.0/( (double) hullConst.NUMSUBINTERVALS);
                    double prevX = this.X(0.0);
                    double prevY = this.Y(0.0);
                    double prevZ = this.Z(0.0);
                    for (int i=1;i<=hullConst.NUMSUBINTERVALS;i++) 
                    {
                        t=((double) i)*dt;
                        thisX=this.X(t); thisY=this.Y(t);thisZ=this.Z(t);
                        dx=thisX-prevX;dy=thisY=prevY;dz=thisZ-prevZ;
                        returnValue=returnValue+Math.Sqrt(dx*dx+dy*dy+dz*dz);
                        prevX=thisX;prevY=thisY;prevZ=thisZ;
                    }
                }
                return (returnValue);
            } // end get
        } // end Length
        // ======= methods =========================================================================
        public double X(double T)
        {
            double returnValue = 0.0;
            if (IsDefined) { returnValue = SplineX.Value(T);}
            return (returnValue);
        } // end X
        //==========================================================================================
        public double Y(double T)
        {
            double returnValue = 0.0;
            if (IsDefined) { returnValue = SplineY.Value(T); }
            return (returnValue);
        } // end Y
        //==========================================================================================
        public double Z(double T)
        {
            double returnValue = 0.0;
            if (IsDefined) { returnValue = SplineZ.Value(T); }
            return (returnValue);
        } // end Z
        //==========================================================================================
        public bool FindFirstX(double targetValue, double loT, double hiT, ref double targetT)
        {
            // find the first occurrence, if any, of the target value for parameter t values
            // restricted to the interval [loT , hiT]
            bool ok = IsDefined && SplineX.FindFirst(targetValue, loT, hiT,ref targetT);
            return (ok);
        } // end FindFirstX
        //==========================================================================================
        public bool FindFirstY(double targetValue, double loT, double hiT, ref double targetT)
        {
            // find the first occurrence, if any, of the target value for parameter t values
            // restricted to the interval [loT , hiT]
            bool ok = IsDefined && SplineY.FindFirst(targetValue, loT, hiT, ref targetT);
            return (ok);
        } // end FindFirstY
        //==========================================================================================
        public bool FindFirstZ(double targetValue, double loT, double hiT, ref double targetT)
        {
            // find the first occurrence, if any, of the target value for parameter t values
            // restricted to the interval [loT , hiT]
            bool ok = IsDefined && SplineZ.FindFirst(targetValue, loT, hiT, ref targetT);
            return (ok);
        } // end FindFirstZ
        //==========================================================================================
        public override void ScaleBy(double scaleFactor)
        {
            // we will not allow a scaling by zero
            if (IsDefined && HullUtil.NotNearZero(scaleFactor))
            {
                SplineX.ScaleBy(scaleFactor);
                SplineY.ScaleBy(scaleFactor);
                SplineZ.ScaleBy(scaleFactor);
            }
            return;
        } // end ScaleBy
        //========================================================================================================
        public override bool Extents(ref double minX, ref double maxX, ref double minY, ref double maxY,
            ref double minZ, ref double maxZ)
        {
            bool ok = IsDefined
                && SplineX.Extents(ref minX,ref maxX)
                && SplineY.Extents(ref minY,ref maxY)
                && SplineZ.Extents(ref minZ,ref maxZ);
            return (ok);
        } // end Extents
        //==========================================================================================
    }// end class Spline5Points3D
}
