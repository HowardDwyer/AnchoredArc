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
    public class Spline5Points3D :HullGeom
    {
        // ======= fields =========================================================================
        public const int NUMNODEPOINTS= Spline5Points1D.NUMNODEPOINTS;
        private Spline5Points1D SplineX = new Spline5Points1D();
        private Spline5Points1D SplineY = new Spline5Points1D();
        private Spline5Points1D SplineZ = new Spline5Points1D();
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
        //=========================================================================================
        public bool IsDefined
        {
            get
            {
                return (SplineX.IsDefined && SplineY.IsDefined && SplineZ.IsDefined);
            } // end get
        } // end IsDefined
        // ======= methods =========================================================================
        public Spline5Points3D()  // default constructor
        {
            DEFAULTCOLOR = System.Drawing.Color.Black;
            Visible = true;
            DisplayColor = DEFAULTCOLOR;
        } // end default constructor
        //=========================================================================================
        public Spline5Points3D(Point3D pt0, Point3D pt1, Point3D pt2, Point3D pt3, Point3D pt4)  // constructor
        {
            DEFAULTCOLOR = System.Drawing.Color.Black;
            Visible = true;
            DisplayColor = DEFAULTCOLOR;
            SetNodes(pt0,pt1,pt2,pt3,pt4);
        } // end constructor
        //=========================================================================================
        public void SetNodes(Point3D pt0, Point3D pt1, Point3D pt2, Point3D pt3, Point3D pt4)
        {
            SplineX = new Spline5Points1D(pt0.X, pt1.X, pt2.X, pt3.X, pt4.X);
            SplineY = new Spline5Points1D(pt0.Y, pt1.Y, pt2.Y, pt3.Y, pt4.Y);
            SplineZ = new Spline5Points1D(pt0.Z, pt1.Z, pt2.Z, pt3.Z, pt4.Z);
            return;
        } // end SetNodes
        //=========================================================================================
        public void GetNodes(ref Point3D pt0, ref  Point3D pt1, ref Point3D pt2, ref Point3D pt3,
            ref Point3D pt4)
        {
            pt0 = Point(0.0);
            pt1 = Point(1.0);
            pt2 = Point(2.0);
            pt3 = Point(3.0);
            pt4 = Point(4.0);
            return;
        } // end GetNodes
        //=========================================================================================
        public Point3D Point(double T)
        {
            Point3D returnValue = new Point3D(0.0,0.0,0.0);
            if (IsDefined) 
            { 
                returnValue = new Point3D(SplineX.Value(T),SplineY.Value(T),SplineZ.Value(T)); 
            }
            return (returnValue);
        } // end Point
        //==========================================================================================
        public double X(double T)
        {
            double returnValue = 0.0;
            if (IsDefined) { returnValue = SplineX.Value(T); }
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
        public override bool TransformBy(Matrix4Sq M)
        {
            bool returnValue = true;
            Point3D pt0 = new Point3D();
            Point3D pt1 = new Point3D();
            Point3D pt2 = new Point3D();
            Point3D pt3 = new Point3D();
            Point3D pt4 = new Point3D();
            GetNodes(ref pt0, ref pt1, ref pt2, ref pt3, ref pt4);
            returnValue = pt0.TransformBy(M) && returnValue;
            returnValue = pt1.TransformBy(M) && returnValue;
            returnValue = pt2.TransformBy(M) && returnValue;
            returnValue = pt3.TransformBy(M) && returnValue;
            returnValue = pt4.TransformBy(M) && returnValue;
            SetNodes(pt0, pt1, pt2, pt3, pt4);
            return (returnValue);
        } // end TransformBy
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
