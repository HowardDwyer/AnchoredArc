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
        public static FreeVector3D operator + (FreeVector3D A, FreeVector3D B)
        {
            FreeVector3D AplusB = new FreeVector3D();
            AplusB.X = A.X + B.X;
            AplusB.Y = A.Y + B.Y;
            AplusB.Z = A.Z + B.Z;
            return(AplusB);
        } // end operator +
        //========================================================================================================
        public static FreeVector3D operator - (FreeVector3D A, FreeVector3D B)
        {
            FreeVector3D AminusB = new FreeVector3D();
            AminusB.X = A.X - B.X;
            AminusB.Y = A.Y - B.Y;
            AminusB.Z = A.Z - B.Z;
            return (AminusB);
        } //end operator -
       //========================================================================================================
        public static double dot (FreeVector3D A, FreeVector3D B)
        {
            double dotProd = 0.0 ;
            dotProd += A.X * B.X;
            dotProd += A.Y * B.Y;
            dotProd += A.Z * B.Z;
            return (dotProd);
        } //end dot
        //========================================================================================================

    } // end class FreeVector3D

}
