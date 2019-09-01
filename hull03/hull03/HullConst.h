#pragma once
#include <string>

using namespace std;
	//================== HULL CONST ============================================================
	class HullConst
	{
	public:
		// parameters which shape the display
		static const int MINWINDOWWIDTH = 450;
		static const int MINWINDOWHEIGHT = 250;
		static string PROJECTTITLE(){ return "Stability Analysis v3.0"; }
		static string AUTHOR(){ return "H. Dwyer"; }
		static const int BUTTONWIDTH = 100;
		static const int BUTTONHEIGHT = 25;
		static const int LABELHEIGHT = 20;
		static const int MARGIN = 10;
		static const int GAP = 5;
		static const int RADIOBUTTONHEIGHT = 18;
		static const int RADIOBUTTONGAP = 2;
		static const int CHECKBOXHEIGHT = 18;
		static const int CHECKBOXGAP = 2;
		static const int BOTTOMPANELHEIGHT = 3 * BUTTONHEIGHT + 2 * MARGIN + 2 * GAP;
		static const int PANEL1TOP = 40;
		static const int PANEL1LEFT = 18;

		// parameters which define the boat object
		static const int MAXCHINES = 12;
		static const int NUMSECTIONS = 200;
		static const int NUMBULKHEADS = 3;
		static double STATIONSPACING(){ return 12.0; }

		// parameters used in numerical procedures
		static double VERYSMALL(){ return 1.0e-5; }   // used to compare real numbers to zero
		static double ANGLETOL(){ return 0.01; }      // used to compare angles to zero
		static double SINANGLETOL(){ return 0.01; }
		static double COSANGLETOL(){ return 0.9999; }
		static const int NUMSEARCHSTEPS = 1000;   // used for initial bracketing in searches
		static const int NUMSUBINTERVALS = 250;   // used for num. integrations not involving sections

		//=========================================================================================
		HullConst();
		~HullConst();
	}; // class HullConst
