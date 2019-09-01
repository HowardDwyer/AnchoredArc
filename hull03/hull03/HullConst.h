#pragma once
#include <string>

using namespace std;
	//================== HULL CONST ============================================================
	class HullConst
	{
	public:
		// parameters which shape the display
		const int MINWINDOWWIDTH = 450;
		const int MINWINDOWHEIGHT = 250;
		const string PROJECTTITLE = "Stability Analysis v3.0";
		const string AUTHOR = "H. Dwyer";
		const int BUTTONWIDTH = 100;
		const int BUTTONHEIGHT = 25;
		const int LABELHEIGHT = 20;
		const int MARGIN = 10;
		const int GAP = 5;
		const int RADIOBUTTONHEIGHT = 18;
		const int RADIOBUTTONGAP = 2;
		const int CHECKBOXHEIGHT = 18;
		const int CHECKBOXGAP = 2;
		const int BOTTOMPANELHEIGHT = 3 * BUTTONHEIGHT + 2 * MARGIN + 2 * GAP;
		const int PANEL1TOP = 40;
		const int PANEL1LEFT = 18;

		// parameters which define the boat object
		const int MAXCHINES = 12;
		const int NUMSECTIONS = 200;
		const int NUMBULKHEADS = 3;
		const double STATIONSPACING = 12.0;

		// parameters used in numerical procedures
		const double VERYSMALL = 1.0e-5;   // used to compare real numbers to zero
		const int NUMSEARCHSTEPS = 1000;   // used for initial bracketing in searches
		const int NUMSUBINTERVALS = 250;   // used for num. integrations not involving sections

		//=========================================================================================
		HullConst();
		~HullConst();
	}; // class HullConst
