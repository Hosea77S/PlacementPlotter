//==============================================================================//
//                                      qPlace                                  //
//                                                                              //
//               Written by Soheil Nazar Shahsavani and Massoud Pedram          //
//      SPORT Lab, University of Southern California, Los Angeles, CA 90089     //
//                           http://sportlab.usc.edu/                           //
//                     ColdFlux Project, http://coldflux.usc.edu                //
//                                                                              //
//  For licensing, please refer to the LICENSE file.                            //
//                                                                              //
// The development is supported in part by IARPA SuperTools program             // 
// via grant W911NF-17-1-0120.                                                  // 
//                                                                              // 
//==============================================================================//

#ifndef PLOTTER_H
#define PLOTTER_H

#include "DB.h"

#define PADDING	(0.4)


//1: red
//2: green
//3: blue
//4: purple
//5: light blue
//6: yellow
//7: black
//8: blue
//9: orange
//10: dark green
//12: brown


class Plotter {
private:
	const DB* _db;

public:
	Plotter ( const DB* db): _db(db) {}
	//void plot_area (std:: string );
	void plot_area_gnu ( std:: string, bool wCN = false, bool wL = false );
	std::string drawCell ( dbCell* , const Point& , bool writeCellNames = false, bool writeLevels = false );

	void 
	plotPlacementResult
	 ( std:: string filename, bool wCellN = false, bool wL = false);

	void plotBoxPLT
	  ( std::ofstream& stream, double x1, double y1, double x2, double y2 );

	
};



#endif //PLOTTER_H