using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace hull02
{
    public class Polygon3D: HullGeom
    {
        // ======= fields =========================================================================
        private List<Point3D> vertices = new List<Point3D>();
        // ======= properties ======================================================================
        public bool Empty
        {
            // this property is read-only
            get
            {
                return (vertices.Count > 0);
            } // end get
        } // end Empty
        //========================================================================================================
        public double Perimeter
        {
            // this property is read-only
            get
            {
                double returnValue = 0.0;
                if (Count>1)
                {
                    Point3D prevVertex = vertices[vertices.Count-1];
                    foreach(Point3D vertex in vertices)
                    {
                        returnValue += Point3D.DistanceBetween(prevVertex, vertex);
                        prevVertex = vertex;
                    }
                }
                return (returnValue);
            } // end get
        } // end Perimeter
        //========================================================================================================
        public int Count
        {
            // this property is read-only
            get
            {
                return(vertices.Count);
            } // end get
        } // end Count
        // ======= methods =========================================================================
        public Polygon3D()  // default constructor
        {
            DEFAULTCOLOR = System.Drawing.Color.Black;
            Visible = true;
            DisplayColor = DEFAULTCOLOR;
        } // end default constructor 
        //========================================================================================================
        public override bool TransformBy(Matrix4Sq M)
        {
            bool returnValue = true;
            if (!Empty)
                foreach (Point3D vertex in vertices)
                    returnValue = returnValue && vertex.TransformBy(M);
            return (returnValue);
        } // end TransformBy
        //=========================================================================================
        public bool PushFirst(Point3D newPoint)
        {
            // we use this routine to add a point at the beginning of the polyline.
            // this routine only checks that the new point is not already the first point.
            bool alreadyIncluded = IsFirstPoint(newPoint);
            if (!alreadyIncluded)
            {
                vertices.Insert(0, newPoint);
            }
            return (!alreadyIncluded);
        } // end PushFirst
        //=========================================================================================
        public bool PushLast(Point3D newPoint)
        {
            // we use this routine to add a point at the end of the polyline.
            // this routine only checks that the new point is not already the last point.
            bool alreadyIncluded = IsLastPoint(newPoint);
            if (!alreadyIncluded)
            {
                vertices.Add(newPoint);
            }
            return (!alreadyIncluded);
        } // end PushLast
        //=========================================================================================
        public bool Add(Point3D newPoint)
        {
            // we use this routine to add a point when we are not concerned with its order.
            // the routine does not allow a point to be added if it is coincident with any
            // existing point.
            // when we are concerned with order we use PushFirst or PushLast.
            bool alreadyIncluded = ContainsPoint(newPoint);
            if (!alreadyIncluded)
            {
                vertices.Add(newPoint);
            }
            return (!alreadyIncluded);
        } // end Add
        //=========================================================================================
        public bool ContainsPoint(Point3D testPoint)
        {
            bool foundIt = false;
            if (!Empty)
                foreach (Point3D vertex in vertices)
                {
                    foundIt = Point3D.AreCoincident(vertex, testPoint);
                    if (foundIt) break;
                }
            return (foundIt);
        } // end ContainsPoint
        //=========================================================================================
        public bool IsFirstPoint(Point3D testPoint)
        {
            bool foundIt = false;
            if (!Empty)
                foundIt = Point3D.AreCoincident(vertices[0], testPoint);
            return (foundIt);
        } // end IsFirstPoint
        //=========================================================================================
        public bool IsLastPoint(Point3D testPoint)
        {
            bool foundIt = false;
            if (!Empty)
                foundIt = Point3D.AreCoincident(vertices[vertices.Count-1], testPoint);
            return (foundIt);
        } // end IsLastPoint
        //=========================================================================================
        public override void ScaleBy(double scaleFactor)
        {
            // we will not allow a scaling by zero
            if (HullUtil.NotNearZero(scaleFactor))
            {
                if(!Empty)
                    foreach(Point3D vertex in vertices)
                    {
                        vertex.ScaleBy(scaleFactor);
                    }
            }
            return;
        } // end ScaleBy
        //========================================================================================================
        public override bool Extents(ref double minX, ref double maxX, ref double minY, ref double maxY,
            ref double minZ, ref double maxZ)
        {
            bool ok = !Empty;
            if (ok)
            {
                minX = vertices[0].X; maxX = minX;
                minY = vertices[0].Y; maxY = minY;
                minZ = vertices[0].Z; maxZ = minZ;
                foreach (Point3D vertex in vertices)
                {
                    minX = Math.Min(vertex.X, minX);
                    minY = Math.Min(vertex.Y, minY);
                    minZ = Math.Min(vertex.Z, minZ);
                    maxX = Math.Max(vertex.X, maxX);
                    maxY = Math.Max(vertex.Y, maxY);
                    maxZ = Math.Max(vertex.Z, maxZ);
                }
            }
            return (ok);
        } // end Extents
        //==========================================================================================
    } // end class Polygon3D
}
