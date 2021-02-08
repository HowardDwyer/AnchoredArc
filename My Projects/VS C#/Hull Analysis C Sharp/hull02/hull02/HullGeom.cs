using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace hull02
{
    //==============================================================================================================
    // this class is used as parent for classes defining geometry objects in hull analysis projects
    //==============================================================================================================
    abstract public class HullGeom
    {
        // ======= fields =========================================================================================
        private bool isVis = true;
        protected Color DEFAULTCOLOR = System.Drawing.Color.White;
        private Color dispColor = System.Drawing.Color.White;
        // ======= properties =====================================================================================
        public bool Visible
        {
            get
            {
                return (isVis);
            } // end get
            set
            {
                isVis=value;  
            } // end set   
        } // end Visible
        //========================================================================================================
        public Color DisplayColor
        {
            get
            {
                return (dispColor);
            } // end get
            set
            {
                dispColor = value;
            } // end set   
        } // end DisplayColor
        // ======= methods =======================================================================================
        public HullGeom() // default constructor
        {
            Visible = true;
            DisplayColor = DEFAULTCOLOR;
        } // end default constructor
        //========================================================================================================
        public HullGeom(Color initColor) // constructor
        {
            Visible = true;
            DisplayColor = initColor;
        } // end constructor
        //========================================================================================================
        public HullGeom(bool initVis) // constructor
        {
            Visible = initVis;
            DisplayColor = DEFAULTCOLOR;
        } // end constructor
        //========================================================================================================
        public HullGeom(Color initColor, bool initVis) // constructor
        {
            DisplayColor = initColor;
            Visible = initVis;
        } // end constructor
        //========================================================================================================
        public virtual bool Draw()
        {
            return (true);
        } // end Draw
        //========================================================================================================
        public virtual bool TransformBy(Matrix4Sq M)
        {
            return (true);
        } // end TransformBy
        //========================================================================================================
        public virtual void ScaleBy(double scaleFactor)
        {
            return;
        } // end ScaleBy
        //========================================================================================================
        public virtual bool Extents(ref double minX, ref double maxX, ref double minY, ref double maxY, 
            ref double minZ, ref double maxZ)
        {
            return (false);
        } // end Extents
    } // end class HullGeom
}
