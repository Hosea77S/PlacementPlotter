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

#ifndef GLOBPLACEMENT_H
#define GLOBPLACEMENT_H

#include "qcMatrixGen.h"
#include "gridMapper.h"
#include "DB.h"
#include "qpSolver.h"
//#include "Solver/viennaSolver.h"
//#include "eigenCGSolver.h"
#include "padPl.h"
#include "subPlacement.h"
#include "mapping.h"
#include "Legalization.h"

#define MAX_GP_ITER 55
#define TARGET_UTIL 1.0
#define MAX_GP_IT_1 200


class globPlacement {

private:
   DB* _db;
   BBox _sourceBB;

  GridBin createUnitGBin(Placement* pl);   
   
public:
	globPlacement( DB* db):  _db(db){
	BBox bb = (*db)._rowDefs->getChipBbox();
	_sourceBB = BBox(Constants::PAD_HEIGHT*2, 
	Constants::PAD_HEIGHT*2, 
	bb.getWidth()+Constants::PAD_HEIGHT*2, 
	bb.getHeight()+Constants::PAD_HEIGHT*2); 
	
	/* // These lines shrink the placement bbox to have a density of 1.0 or more
	// Seems like degrades the results
	
	double density = (*db).calculateTotalCellArea() / _sourceBB.getArea();
	while ( ! greaterOrEqualDouble(density, TARGET_UTIL) ){
		_sourceBB = _sourceBB.ShrinkTo(0.95);
		density = (*db).calculateTotalCellArea() / _sourceBB.getArea();
	}	
	std::cout << "Initial Density: " << density << std::endl; */
	

	}
	globPlacement( DB* db, BBox bb):  _db(db), _sourceBB(bb){}
	
	
	Placement doLAL(Placement* pl, unsigned iteration);
	GridMapper createGridBins(Placement* , unsigned );	
	void doGlobalPlacement( int m = MAX_GP_ITER );
	void doNonLinearScaling
	(const GridMapper&, const GridBin& gb, const Placement* , Placement*, unsigned  );
	void legalizeBin(const GridBin& , Placement* anchorPl, Dir d);
	void addPsuedoNetWeights 
		(qcMatrixGen& ,  const Placement& , const Placement&, int ite, int maxIt);
		
	void shifToInitialLocations(Placement*);		
	
	BBox getBBox() const { return _sourceBB; }
	
	
	void minimizeMaxWL  ( unsigned maxIt = 100 );	
	bool minimizeMaxWLSub  ();	
};







#endif //GLOBPLACEMENT_H
