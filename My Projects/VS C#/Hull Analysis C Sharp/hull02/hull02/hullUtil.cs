    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    // =======================================================================================
    namespace hull02
    {
        static class HullUtil
        {
            //==============================================================================================================
            // this class is used as a container for utility methods used in hull analysis projects
            //==============================================================================================================
            public static bool NearZero(double x)
            {
                bool ok = (Math.Abs(x) <= hullConst.VERYSMALL);
                return (ok);
            } // end NearZero
            //==========================================================================================================
            public static bool NotNearZero(double x)
            {
                return (!NearZero(x));
            } // end NotNearZero
            //==========================================================================================================
            public static bool NearEqual(double x, double y)
            {
                return (NearZero(x - y));
            } // end NearEqual
            //==========================================================================================================
            public static bool NotNearEqual(double x, double y)
            {
                return (!NearZero(x - y));
            } // end NotNearEqual
            //==========================================================================================================
        } // end of class HullUtil
    }

