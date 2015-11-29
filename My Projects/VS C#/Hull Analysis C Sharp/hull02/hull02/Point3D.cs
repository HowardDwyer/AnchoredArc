using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace hull02
{
    // ===========================================================================================================
    // This class represents a point in 3D space
    // This class is derived from the HullGeom class, a parent class for objects which will be
    // displayed on screen
    // ===========================================================================================================
    public class Point3D : HullGeom
    {
        // ======= fields =========================================================================================
        private double[] PtCoord = new double[3];
        // ======= properties =====================================================================================
        public double X
        {
            get
            {
                return (PtCoord[0]);
            }// end get
            set
            {
                PtCoord[0] = value;
            }// end set
        }// end X
        //========================================================================================================
        public double Y
        {
            get
            {
                return (PtCoord[1]);
            }// end get
            set
            {
                PtCoord[1] = value;
            }// end set
        }// end Y
        //========================================================================================================
        public double Z
        {
            get
            {
                return (PtCoord[2]);
            }// end get
            set
            {
                PtCoord[2] = value;
            }// end set
        }// end Z
        // ======= methods =======================================================================================
        public Point3D() // default constructor
        {
            DEFAULTCOLOR = System.Drawing.Color.Red;
            X = 0.0; Y = 0.0; Z = 0.0;
            Visible = true;
            DisplayColor = DEFAULTCOLOR;
        } // end default constructor
        //========================================================================================================
        public Point3D(Color initColor) // constructor
        {
            DEFAULTCOLOR = System.Drawing.Color.Red;
            X = 0.0; Y = 0.0; Z = 0.0;
            Visible = true;
            DisplayColor = initColor;
        } // end constructor
        //========================================================================================================
        public Point3D(bool initVis) // constructor
        {
            DEFAULTCOLOR = System.Drawing.Color.Red;
            X = 0.0; Y = 0.0; Z = 0.0;
            Visible = initVis;
            DisplayColor = DEFAULTCOLOR;
        } // end constructor
        //========================================================================================================
        public Point3D(Color initColor,bool initVis) // constructor
        {
            DEFAULTCOLOR = System.Drawing.Color.Red;
            X = 0.0; Y = 0.0; Z = 0.0;
            Visible = initVis;
            DisplayColor = initColor;
        } // end constructor
        //========================================================================================================
        public Point3D(double initX, double initY, double initZ) // constructor
        {
            DEFAULTCOLOR = System.Drawing.Color.Red;
            X = initX; Y = initY; Z = initZ;
            Visible = true;
            DisplayColor = DEFAULTCOLOR;
        } // end constructor
        //========================================================================================================
        public Point3D(double initX, double initY, double initZ, Color initColor) // constructor
        {
            DEFAULTCOLOR = System.Drawing.Color.Red;
            DisplayColor = initColor;
            Visible = true;
            X = initX; Y = initY; Z = initZ;
        } // end constructor
        //========================================================================================================
        public Point3D(double initX, double initY, double initZ, bool initVis) // constructor
        {
            DEFAULTCOLOR = System.Drawing.Color.Red;
            Visible = initVis;
            DisplayColor = DEFAULTCOLOR;
            X = initX; Y = initY; Z = initZ;
        } // end constructor
        //========================================================================================================
        public Point3D(double initX, double initY, double initZ, Color initColor, bool initVis) // constructor
        {
            DEFAULTCOLOR = System.Drawing.Color.Red;
            Visible = initVis;
            DisplayColor = initColor;
            X = initX; Y = initY; Z = initZ;
        } // end constructor
        //========================================================================================================
        public Point3D(Point3D existingPt3D) // constructor
        {
            DEFAULTCOLOR = System.Drawing.Color.Red;
            if (existingPt3D != null)
            {
                try
                {
                    DEFAULTCOLOR = existingPt3D.DEFAULTCOLOR;
                    this.X = existingPt3D.X; this.Y = existingPt3D.Y; this.Z = existingPt3D.Z;
                    this.Visible = existingPt3D.Visible;
                    this.DisplayColor = existingPt3D.DisplayColor;
                }
                catch
                {
                    X = 0.0; Y = 0.0; Z = 0.0;
                    Visible = true;
                    DisplayColor = DEFAULTCOLOR;
                }
            }
            else
            {
                X = 0.0; Y = 0.0; Z = 0.0;
                Visible = true;
                DisplayColor = DEFAULTCOLOR;
            }
        } // end constructor
        // ======================================================================================================
        public override void ScaleBy(double scaleFactor)
        {
            // we will not allow a scaling by zero
            if (HullUtil.NotNearZero(scaleFactor))
            {
                X = scaleFactor * X;
                Y = scaleFactor * Y;
                Z = scaleFactor * Z;
            }
            return;
        } // end ScaleBy
        //========================================================================================================
        public override bool Extents(ref double minX, ref double maxX, ref double minY, ref double maxY, 
            ref double minZ, ref double maxZ)
        {
            minX = this.X; maxX = this.X;
            minY = this.Y; maxY = this.Y;
            minZ = this.Z; maxZ = this.Z;
            return (true);
        } // end Extents
        //========================================================================================================
        public override bool TransformBy(Matrix4Sq M)
        {
            // a 3D point is rotated by the 4X4 transformation matrix and translated.
            double newX = M.GetCoeff(0, 0) * X + M.GetCoeff(0, 1) * Y + M.GetCoeff(0, 2) * Z 
                + M.GetCoeff(0, 3);
            double newY = M.GetCoeff(1, 0) * X + M.GetCoeff(1, 1) * Y + M.GetCoeff(1, 2) * Z 
                + M.GetCoeff(1, 3);
            double newZ = M.GetCoeff(2, 0) * X + M.GetCoeff(2, 1) * Y + M.GetCoeff(2, 2) * Z 
                + M.GetCoeff(2, 3);
            X = newX;
            Y = newY;
            Z = newZ;
            return (true);
        } // end TransformBy
        //========================================================================================================
        public static double DistanceBetween(Point3D A, Point3D B)
        {
            return ((A - B).Length);
        } //end DistanceBetween
        //========================================================================================================
        public static bool AreCoincident(Point3D A, Point3D B)
        {
            return (HullUtil.NearZero(DistanceBetween(A,B)));
        } //end AreCoincident
        //========================================================================================================
        public static bool AreDistinct(Point3D A, Point3D B)
        {
            return (!AreCoincident(A,B));
        } //end AreDistinct
        //========================================================================================================
        public bool Equals(Point3D B)
        {
            return (AreCoincident(this, B) && (this.DisplayColor == B.DisplayColor));
        } //end Equals
        //========= operators ===================================================================================
        public static FreeVector3D operator -(Point3D A, Point3D B)
        {
            FreeVector3D AminusB = new FreeVector3D();
            AminusB.X = A.X - B.X;
            AminusB.Y = A.Y - B.Y;
            AminusB.Z = A.Z - B.Z;
            return (AminusB);
        } //end operator -
        //========================================================================================================
        public static Point3D operator +(Point3D A, FreeVector3D B)
        {
            Point3D AplusB = new Point3D(A);
            AplusB.X = A.X + B.X;
            AplusB.Y = A.Y + B.Y;
            AplusB.Z = A.Z + B.Z;
            return (AplusB);
        } //end operator +
        //========================================================================================================
    } // end class Point3D

}
