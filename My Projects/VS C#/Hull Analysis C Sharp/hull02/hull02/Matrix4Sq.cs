using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace hull02
{
    public class Matrix4Sq
    {
        // ======= fields =========================================================================================
        private double[,] coeffValue = new double[4, 4];
        // ======= methods ========================================================================================
        public Matrix4Sq()
        {
            SetToZero();
        } // end default constructor
        // ==================================================================================================
        private void SetZero()
        {
            for (int iRow = 0; iRow < 4;iRow++ )
                for (int iCol = 0; iCol < 4;iCol++ )
                    coeffValue[iRow, iCol] = 0.0;
            return;
        }  // end SetZero
        // ==================================================================================================
        public void SetToZero()
        {
            // the user cannot set the matrix to be non-allowable as a transformation matrix
            SetZero();
            coeffValue[3, 3] = 1.0;
            return;
        }  // end SetToZero
        // ==================================================================================================
        public void SetToIdentity()
        {
            this.SetZero();
            for (int i = 0; i < 4; i++)
                coeffValue[i, i] = 1.0;
            return;
        }  // end SetToIdentity
        // ==================================================================================================
        public bool SetCoeff(int iRow,int iCol, double newCoeff)
        {
            // this access routine does not allow the user to set values in the last row
            bool ok=(0<=iRow)&&(iRow<=2)&&(0<=iCol)&&(iCol<=3);
            if (ok) coeffValue[iRow, iCol] = newCoeff;
            return(ok);
        }  // end SetCoeff
        // ==================================================================================================
        public double GetCoeff(int iRow, int iCol)
        {
            double result = 0.0;
            bool ok = (0 <= iRow) && (iRow <=3) && (0 <= iCol) && (iCol <=3);
            if (ok) result=coeffValue[iRow, iCol];
            return (result);
        }  // end GetCoeff
        // ==================================================================================================
        public void SetToTranslate(double dx, double dy, double dz = 0.0)
        {
            SetToIdentity();
            SetCoeff(0, 3, dx);
            SetCoeff(1, 3, dy);
            SetCoeff(2, 3, dz);
            return;
        } // SetToTranslate
        // ==================================================================================================
        public void SetToRotateXY(double angleInDegrees)
        {
            SetToIdentity();
            double angleInRadians = angleInDegrees * Math.PI / 180.0;
            double cs = Math.Cos(angleInRadians);
            double sn = Math.Sin(angleInRadians);
            SetCoeff(0, 0, cs);
            SetCoeff(0, 1, -sn);
            SetCoeff(1, 0, sn);
            SetCoeff(1, 1, cs);
            return;
        } // SetToRotateXY
        // ==================================================================================================
        public void SetToRotateYZ(double angleInDegrees)
        {
            SetToIdentity();
            double angleInRadians = angleInDegrees * Math.PI / 180.0;
            double cs = Math.Cos(angleInRadians);
            double sn = Math.Sin(angleInRadians);
            SetCoeff(1, 1, cs);
            SetCoeff(1, 2, -sn);
            SetCoeff(2, 1, sn);
            SetCoeff(2, 2, cs);
            return;
        } // SetToRotateYZ
        // ==================================================================================================
        public void SetToRotateZX(double angleInDegrees)
        {
            SetToIdentity();
            double angleInRadians = angleInDegrees * Math.PI / 180.0;
            double cs = Math.Cos(angleInRadians);
            double sn = Math.Sin(angleInRadians);
            SetCoeff(0, 0, cs);
            SetCoeff(0, 2, sn);
            SetCoeff(2, 0, -sn);
            SetCoeff(2, 2, cs);
            return;
        } // SetToRotateZX
        // ======= static methods ===========================================================================
        public static void Multiply(Matrix4Sq M1, Matrix4Sq M2, ref Matrix4Sq M1XM2)
        {
            M1XM2.SetToZero();
            for (int iRow = 0; iRow <= 3; iRow++)
                for (int iCol = 0; iCol <= 3; iCol++)
                    for (int k = 0; k <= 3;k++ )
                        M1XM2.coeffValue[iRow, iCol] += M1.coeffValue[iRow, k] * M2.coeffValue[k, iCol];
            return;
        } // end Multiply
        // ==================================================================================================
        public static void Multiply(Matrix4Sq M, Point3D P, ref Point3D MXP)
        {
            MXP.X = M.GetCoeff(0, 0) * P.X + M.GetCoeff(0, 1) * P.Y + M.GetCoeff(0, 2) * P.Z + M.GetCoeff(0, 3);
            MXP.Y = M.GetCoeff(1, 0) * P.X + M.GetCoeff(1, 1) * P.Y + M.GetCoeff(1, 2) * P.Z + M.GetCoeff(1, 3);
            MXP.Z = M.GetCoeff(2, 0) * P.X + M.GetCoeff(2, 1) * P.Y + M.GetCoeff(2, 2) * P.Z + M.GetCoeff(2, 3);
            return;
        } // end Multiply
        // ==================================================================================================
        public static void Multiply(Matrix4Sq M, FreeVector3D V, ref FreeVector3D MXV)
        {
            MXV.X = M.GetCoeff(0, 0) * V.X + M.GetCoeff(0, 1) * V.Y + M.GetCoeff(0, 2) * V.Z;
            MXV.Y = M.GetCoeff(1, 0) * V.X + M.GetCoeff(1, 1) * V.Y + M.GetCoeff(1, 2) * V.Z;
            MXV.Z = M.GetCoeff(2, 0) * V.X + M.GetCoeff(2, 1) * V.Y + M.GetCoeff(2, 2) * V.Z;
            return;
        } // end Multiply
        // ======== operators ===============================================================================
        public static Matrix4Sq operator * (Matrix4Sq M1, Matrix4Sq M2)
        {
            Matrix4Sq M1XM2 = new Matrix4Sq();
            Multiply(M1, M2, ref M1XM2);
            return(M1XM2);
        } // end operator *
        // ==================================================================================================
        public static Point3D operator *(Matrix4Sq M, Point3D P)
        {
            Point3D MXP = new Point3D(P);
            Multiply(M, P, ref MXP);
            return (MXP);
        } // end operator *
        // ==================================================================================================
        public static FreeVector3D operator *(Matrix4Sq M, FreeVector3D V)
        {
            FreeVector3D MXV = new FreeVector3D();
            Multiply(M, V, ref MXV);
            return (MXV);
        } // end operator *
        // ==================================================================================================
    } // end Matrix4Sq
}
