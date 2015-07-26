using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace hull02
{
    //==============================================================================================================
    // this class is used as a container for constants used in hull analysis projects
    //==============================================================================================================
    static class hullConst
    {
        // parameters which shape the display
        public const int MINWINDOWWIDTH = 450;
        public const int MINWINDOWHEIGHT = 250;
        public const string PROJECTTITLE = "Boat Analysis v2.0";
        public const string AUTHOR = "H. Dwyer"; 
        public const int BUTTONWIDTH = 100;
        public const int BUTTONHEIGHT = 25;
        public const int LABELHEIGHT = 20;
        public const int MARGIN = 10;
        public const int GAP = 5;
        public const int RADIOBUTTONHEIGHT = 18;
        public const int RADIOBUTTONGAP = 2;
        public const int CHECKBOXHEIGHT = 18;
        public const int CHECKBOXGAP = 2;
        public const int BOTTOMPANELHEIGHT = 3 * BUTTONHEIGHT + 2 * MARGIN + 2 * GAP;
        public const int PANEL1TOP = 40;
        public const int PANEL1LEFT = 18;

        // parameters which define the boat object
        public const int MAXCHINES = 12;
        public const int NUMSECTIONS = 200;
        public const int NUMBULKHEADS = 3;
        public const double STATIONSPACING = 12.0;

        // parameters used in numerical procedures
        public const double VERYSMALL = 1.0e-5;   // used to compare real numbers to zero
        public const int NUMSEARCHSTEPS = 1000;   // used for initial bracketing in searches
        public const int NUMSUBINTERVALS = 250;   // used for num. integrations not involving sections

    }  // end of class hullConst 

}
