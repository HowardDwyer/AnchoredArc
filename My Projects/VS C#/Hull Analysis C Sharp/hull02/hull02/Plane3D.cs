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
        double dotProd;
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
        public double DotProduct
        {
            get
            {
                return (dotProd);
            }

            set
            {
                dotProd = value;
            }
        } // end DotProduct
        // ======= methods =======================================================================================
        public Plane3D() // default constructor
        {
            SetNormal(0.0, 0.0, 0.0);
            DotProduct = 0.0;
        } // end default constructor
        //========================================================================================================
        public Plane3D(FreeVector3D newNormal, double newDotProduct) // constructor
        {
            SetNormal(newNormal);
            DotProduct = newDotProduct;
        } // end constructor
        //========================================================================================================
        public Plane3D(Plane3D existingPlane) // constructor
        {
            SetNormal(existingPlane.Normal);
            DotProduct = existingPlane.DotProduct;
        } // end constructor
        //========================================================================================================
        public void SetNormal(FreeVector3D newNormal)
        {
            SetNormal(newNormal.X, newNormal.Y, newNormal.Z);
            return;
        }
        //========================================================================================================
        public void SetNormal(double newX, double newY, double newZ)
        {
            normal.X = newX;
            normal.Y = newY;
            normal.Z = newZ;
            return;
        }
        //========================================================================================================
        public bool PointOnPlane(ref Point3D pt)
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
                            pt.X = DotProduct / Normal.X;
                            break;
                        case 2:
                            pt.Y = DotProduct / Normal.Y;
                            break;
                        case 3:
                            pt.Z = DotProduct / Normal.Z;
                            break;
                    }
                }
            }
            return (ok);
        } // end PointOnPlane
        //========================================================================================================
        public bool IsPointOnPlane(Point3D testPoint)
        {
            bool onPlane = false;
            if (IsDefined)
            {
                double thisDotProd = Normal.X * testPoint.X + Normal.Y * testPoint.Y
                    + Normal.Z * testPoint.Z;
                onPlane = HullUtil.NearEqual(thisDotProd, DotProduct);
            }
            return (onPlane);
        } // end IsPointOnPlane
        //========================================================================================================
        public double DistanceFromPlane(Point3D testPoint)
        {
            double distFromPlane = 0.0;
            if (IsDefined)
            {
                Point3D ptOnPlane = new Point3D();
                bool ok = PointOnPlane(ref ptOnPlane);
                if(ok)
                {
                    FreeVector3D v = new FreeVector3D();
                    v = testPoint - ptOnPlane;
                    double vDotN = FreeVector3D.Dot(v, Normal);
                    double lengthN = Normal.Length;
                    if(HullUtil.NotNearZero(lengthN))
                    {
                        distFromPlane = vDotN / lengthN;
                    }
                }
            }
            return (distFromPlane);
        } // end DistanceFromPlane
        //========================================================================================================
        public bool TransformBy(Matrix4Sq M)
        {
            bool ok = IsDefined;
            if(ok)
            {
                FreeVector3D newNormal = new FreeVector3D();
                newNormal = Normal;
                Point3D newPtOnPlane = new Point3D();
                if (ok) ok = PointOnPlane(ref newPtOnPlane);
                if (ok) ok = newNormal.TransformBy(M);
                if (ok) ok = newPtOnPlane.TransformBy(M);
                if(ok)
                {
                    double newDotProd = newNormal.X * newPtOnPlane.X + newNormal.Y * newPtOnPlane.Y 
                        + newNormal.Z * newPtOnPlane.Z;
                    SetNormal(newNormal);
                    DotProduct = newDotProd;
                }
            }
            return (ok);
        } // end TransformBy
        //========================================================================================================
    } // end Plane3D
}
