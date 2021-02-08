using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace hull02
{
    // ===========================================================================================================
    // This class represents a free vector in 3D space
    // ===========================================================================================================
    public class FreeVector3D 
    {
        // ======= fields =========================================================================================
        private double[] VecCoord = new double[3];
        // ======= properties =====================================================================================
        public double X
        {
            get
            {
                return (VecCoord[0]);
            }// end get
            set
            {
                VecCoord[0] = value;
            }// end set
        }// end X
        //========================================================================================================
        public double Y
        {
            get
            {
                return (VecCoord[1]);
            }// end get
            set
            {
                VecCoord[1] = value;
            }// end set
        }// end Y
        //========================================================================================================
        public double Z
        {
            get
            {
                return (VecCoord[2]);
            }// end get
            set
            {
                VecCoord[2] = value;
            }// end set
        }// end Z
        //========================================================================================================
        public double Length
        {
            // this property is read-only
            get
            {
                return (Math.Sqrt(X * X + Y * Y + Z * Z));
            }
        } //end Length
        //========================================================================================================
        public bool IsZero
        {
            // this property is read-only
            get
            {
                return (HullUtil.NearZero(Length));
            }
        } //end IsZero
        // ======= methods =======================================================================================
        public FreeVector3D() // default constructor
        {
            X = 0.0; Y = 0.0; Z = 0.0;
        } // end default constructor
        //========================================================================================================
        public FreeVector3D(double initX, double initY, double initZ) // constructor
        {
            X = initX; Y = initY; Z = initZ;
        } // end constructor
        //========================================================================================================
        public FreeVector3D(FreeVector3D existingVector3D) // constructor
        {
            if (existingVector3D != null)
            {
                try
                {
                    X = existingVector3D.X;
                    Y = existingVector3D.Y;
                    Z = existingVector3D.Z;
                }
                catch
                {
                    X = 0.0; Y = 0.0; Z = 0.0;
                }
            }
            else
            {
                X = 0.0; Y = 0.0; Z = 0.0;
            }
        } // end constructor
        //========================================================================================================
        public static double Dot(FreeVector3D A, FreeVector3D B)
        {
            double dotProd = 0.0;
            dotProd += A.X * B.X;
            dotProd += A.Y * B.Y;
            dotProd += A.Z * B.Z;
            return (dotProd);
        } //end Dot
        //========================================================================================================
        public static bool AreOrthogonal(FreeVector3D A, FreeVector3D B)
        {
            FreeVector3D A2 = new FreeVector3D(A);
            FreeVector3D B2 = new FreeVector3D(B);
            A2.Normalize(); B2.Normalize();
            return (HullUtil.NearZero(Dot(A2, B2)));
        } //end AreOrthogonal
        //========================================================================================================
        public static bool AreParallel(FreeVector3D A, FreeVector3D B)
        {
            FreeVector3D A2 = new FreeVector3D(A);
            FreeVector3D B2 = new FreeVector3D(B);
            bool nonZeroVectors = A2.Normalize() && B2.Normalize();
            return (nonZeroVectors && HullUtil.NearEqual(1.0 , Math.Abs(Dot(A2, B2))));
        } //end AreParallel
        //========================================================================================================
        public bool Normalize()
        {
            bool ok = !IsZero;
            if(ok)
            {
                double magnitude = Length;
                X = X / magnitude;
                Y = Y / magnitude;
                Z = Z / magnitude;
            }
            return (ok);
        } //end Normalize
        //========================================================================================================
        public bool TransformBy(Matrix4Sq M)
        {
            // a free vector is rotated by the 4X4 transformation matrix but there is no
            // translation.
            double newX = M.GetCoeff(0, 0) * X + M.GetCoeff(0, 1) * Y + M.GetCoeff(0, 2) * Z;
            double newY = M.GetCoeff(1, 0) * X + M.GetCoeff(1, 1) * Y + M.GetCoeff(1, 2) * Z;
            double newZ = M.GetCoeff(2, 0) * X + M.GetCoeff(2, 1) * Y + M.GetCoeff(2, 2) * Z;
            X = newX;
            Y = newY;
            Z = newZ;
            return (true);
        } // end TransformBy
        //========================================================================================================
        public static FreeVector3D cross(FreeVector3D A, FreeVector3D B)
        {
            FreeVector3D aCrossB = new FreeVector3D();
            aCrossB.X = A.Y * B.Z - A.Z * B.Y;
            aCrossB.Y = -A.X * B.Z + A.Z * B.X;
            aCrossB.Z = A.X * B.Y - A.Y * B.X;
            return (aCrossB);
        } //end cross
        //======== operators ======================================================================================
        public static FreeVector3D operator +(FreeVector3D A, FreeVector3D B)
        {
            FreeVector3D AplusB = new FreeVector3D();
            AplusB.X = A.X + B.X;
            AplusB.Y = A.Y + B.Y;
            AplusB.Z = A.Z + B.Z;
            return (AplusB);
        } // end operator +
        //========================================================================================================
        public static FreeVector3D operator /(double s, FreeVector3D A)
        {
            FreeVector3D aDivS = new FreeVector3D();
            if (HullUtil.NotNearZero(s))
            {
                aDivS.X = A.X / s;
                aDivS.Y = A.Y / s;
                aDivS.Z = A.Z / s;
            }
            return (aDivS);
        } // end operator /
        //========================================================================================================
        public static FreeVector3D operator *(double s, FreeVector3D A)
        {
            FreeVector3D sA = new FreeVector3D();
            sA.X = s * A.X;
            sA.Y = s * A.Y;
            sA.Z = s * A.Z;
            return (sA);
        } // end operator *
        //========================================================================================================
        public static FreeVector3D operator *(FreeVector3D A, double s)
        { return (s * A); } // end operator *
        //========================================================================================================
        public static FreeVector3D operator -(FreeVector3D A, FreeVector3D B)
        {
            FreeVector3D AminusB = new FreeVector3D();
            AminusB.X = A.X - B.X;
            AminusB.Y = A.Y - B.Y;
            AminusB.Z = A.Z - B.Z;
            return (AminusB);
        } //end operator -


    } // end class FreeVector3D

}
