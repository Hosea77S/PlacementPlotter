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

#ifndef INITPLACEMENT_H
#define INITPLACEMENT_H

#include "qcMatrixGen.h"
#include "DB.h"
#include "qpSolver.h"
#include "padPl.h"
#include "Legalization.h"
//#include "eigenCGSolver.h"

#define maxInitPlIterations 8

class initPlacement{

private:
   DB* _db;


public:
	initPlacement( DB* db): 
		_db(db){}

	void doInitialPl();
	//void putCellsInBound(const BBox& bb);
	
};




#endif //INITPLACEMENT_H
