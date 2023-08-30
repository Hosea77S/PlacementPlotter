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


#ifndef QPSOLVER_H
#define QPSOLVER_H


#include "compcol_double.h"	// Compressed column matrix header
#include "cg.h"
#include "icpre_double.h"   // Diagonal preconditioner
#include "iohb_double.h"    // Harwell-Boeing matrix I/O header
#include "diagpre_double.h"
#include "iotext_double.h"


#include <map>
#include <vector>
#include <iostream>

#include "placement.h"

//class CompCol_Mat_double;
//class MV_Vector_double;


//#define MAX_SOLVER_ITERATION 10000
//#define SOLVER_TOLERNCE  1.0e-10
#define MAX_SOLVER_ITERATION 1000
#define SOLVER_TOLERNCE  1.0e-9
//#define MAX_SOLVER_ITERATION 100000
//#define SOLVER_TOLERNCE  1.0e-10



class qpSolver
{
private:
  int _numOfNonTerminals;
  //int _numOfCells;
  const Placement* _pl;
  
   
  void generateQMatrix 
		(const std::map< INT_PAIR, double>&, CompCol_Mat_double* );
	
  void generateCMatrix 
		(const std::map<int, double> &, MV_Vector_double*  );  

  	std::vector<double> 
	solveCG( CompCol_Mat_double& Qx,
						 MV_Vector_double&   Cx, Dir d= _XX, bool acc = false ) ;  
public:


  //ctor - default 
  qpSolver(): _numOfNonTerminals(0){
	Placement pl(_numOfNonTerminals);
	_pl = &pl; 
  }
  qpSolver(int nT): _numOfNonTerminals(nT) {
	Placement pl(_numOfNonTerminals, Point(0.0, 0.0));
	_pl = &pl; 	  
  }
  qpSolver(int nT, const Placement* pl): 
  _numOfNonTerminals(nT), _pl(pl){}

	std::vector<double> 
	solve(const std::map<INT_PAIR, double>& Qx, 
		  const std::map<int, double> &Cx , 
		  Dir d= _XX, bool acc = false );

	std::vector<double> 
		solve( CompCol_Mat_double& Q, 
						 MV_Vector_double &C, Dir d= _XX );

	
};





#endif //QPSOLVER_H