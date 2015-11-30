using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace hull02
{
    public class Plane3D
    {
        // ======= fields =========================================================================================
        FreeVector3D normal = new FreeVector3D();
        double pDotN;
        // ======= properties =====================================================================================
        public bool IsDefined
        {
            // this property is read-only
            get
            {
                return (HullUtil.NotNearZero(normal.Length));
            }
        } // end IsDefined
        //========================================================================================================
        public FreeVector3D Normal
        {
            // this property is read-only
            get
            {
                return (normal);
            }
        } // end Normal
        //========================================================================================================
        public double PDotN
        {
            get
            {
                return (pDotN);
            }

            set
            {
                pDotN = value;
            }
        } // end PDotN
        // ======= methods =======================================================================================
        public Plane3D() // default constructor
        {
            SetNormal(0.0, 0.0, 0.0);
            PDotN = 0.0;
        } // end default constructor
        //========================================================================================================
        public Plane3D(FreeVector3D newNormal, double newDotProduct) // constructor
        {
            SetNormal(newNormal);
            PDotN = newDotProduct;
        } // end constructor
        //========================================================================================================
        public Plane3D(Plane3D existingPlane) // constructor
        {
            SetNormal(existingPlane.Normal);
            PDotN = existingPlane.PDotN;
        } // end constructor
        //========================================================================================================
        public void SetNormal(FreeVector3D newNormal)
        {
            SetNormal(newNormal.X, newNormal.Y, newNormal.Z);
            return;
        } // end SetNormal
        //========================================================================================================
        public void SetNormal(double newX, double newY, double newZ)
        {
            normal.X = newX;
            normal.Y = newY;
            normal.Z = newZ;
            return;
        } // end SetNormal
        //========================================================================================================
        public bool GetPointOnPlane(ref Point3D pt)
        {
            // returns a piercing point for one of the principal axes, choosing the one closest
            // to the origin.
            bool ok = IsDefined;
            pt.X = 0.0; pt.Y = 0.0; pt.Z = 0.0;
            if (ok)
            {
                int largestComponent = 1;
                double maxMagnitude = Math.Abs(Normal.X);
                if (Math.Abs(Normal.Y) > maxMagnitude)
                {
                    maxMagnitude = Math.Abs(Normal.Y);
                    largestComponent = 2;
                }
                if (Math.Abs(Normal.Z) > maxMagnitude)
                {
                    maxMagnitude = Math.Abs(Normal.Z);
                    largestComponent = 3;
                }
                ok = HullUtil.NotNearZero(maxMagnitude);
                if (ok)
                {
                    switch (largestComponent)
                    {
                        case 1:
                            pt.X = PDotN / Normal.X;
                            break;
                        case 2:
                            pt.Y = PDotN / Normal.Y;
                            break;
                        case 3:
                            pt.Z = PDotN / Normal.Z;
                            break;
                    }
                }
            }
            return (ok);
        } // end GetPointOnPlane
        //========================================================================================================
        public bool IsPointOnPlane(Point3D testPoint)
        {
            bool onPlane = false;
            if (IsDefined)
            {
                double thisDotProd = Normal.X * testPoint.X + Normal.Y * testPoint.Y
                    + Normal.Z * testPoint.Z;
                onPlane = HullUtil.NearEqual(thisDotProd, PDotN);
            }
            return (onPlane);
        } // end IsPointOnPlane
        //========================================================================================================
        public bool IsPointAbovePlane(Point3D testPoint)
        {
            bool abovePlane = false;
            if (IsDefined)
            {
                double thisDotProd = Normal.X * testPoint.X + Normal.Y * testPoint.Y
                    + Normal.Z * testPoint.Z;
                abovePlane = HullUtil.NotNearEqual(thisDotProd, PDotN) && (thisDotProd > 0.0);
            }
            return (abovePlane);
        } // end IsPointAbovePlane
        //========================================================================================================
        public bool IsPointBelowPlane(Point3D testPoint)
        {
            bool belowPlane = false;
            if (IsDefined)
            {
                double thisDotProd = Normal.X * testPoint.X + Normal.Y * testPoint.Y
                    + Normal.Z * testPoint.Z;
                belowPlane = HullUtil.NotNearEqual(thisDotProd, PDotN) && (thisDotProd < 0.0);
            }
            return (belowPlane);
        } // end IsPointBelowPlane
        //========================================================================================================
        public double DistanceFromPlane(Point3D testPoint)
        {
            double distFromPlane = 0.0;
            if (IsDefined)
            {
                double thisDotProd = Normal.X * testPoint.X + Normal.Y * testPoint.Y
                    + Normal.Z * testPoint.Z;
                double normalLength = Normal.Length;
                if (HullUtil.NotNearZero(normalLength))
                {
                    distFromPlane = (thisDotProd - PDotN) / normalLength;
                }
            }
            return (distFromPlane);
        } // end DistanceFromPlane
        //========================================================================================================
        public bool PiercingPoint(Point3D A, Point3D B, ref Point3D PPt)
        {
            bool gotOne = false; ;
            if (IsDefined)
            {
                FreeVector3D AB = new FreeVector3D();
                AB = B - A;
                double ABDotN = FreeVector3D.Dot(AB, Normal);
                if(HullUtil.NotNearZero(ABDotN))
                {
                    double ADotN = A.X * Normal.X + A.Y * Normal.Y + A.Z * Normal.Z;
                    double t = (pDotN - ADotN) / ABDotN;
                    if((0.0 <= t) && (t <= 1.0))
                    {
                        gotOne = true;
                        PPt = A + t * AB;
                    }
                }
            }
            return (gotOne);
        } // end PiercingPoint
        //========================================================================================================
        public bool TransformBy(Matrix4Sq M)
        {
            bool ok = IsDefined;
            if(ok)
            {
                FreeVector3D newNormal = new FreeVector3D();
                newNormal = Normal;
                Point3D newPtOnPlane = new Point3D();
                if (ok) ok = GetPointOnPlane(ref newPtOnPlane);
                if (ok) ok = newNormal.TransformBy(M);
                if (ok) ok = newPtOnPlane.TransformBy(M);
                if(ok)
                {
                    double newDotProd = newNormal.X * newPtOnPlane.X + newNormal.Y * newPtOnPlane.Y 
                        + newNormal.Z * newPtOnPlane.Z;
                    SetNormal(newNormal);
                    PDotN = newDotProd;
                }
            }
            return (ok);
        } // end TransformBy
        //========================================================================================================
    } // end Plane3D
}
