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


#ifndef LEGALIZER_H
#define	LEGALIZER_H

#ifndef COMMON__H
#include "common.h"
#endif

#include "DB.h"
#include "placement.h"
#include "gridMapper.h"
#include "padPl.h"


#define MINSPACE 1.0
#define NON_LIN_PERC 0.4

class Legalizer {
private:
	DB* _db;
	//Placement* _pl;
	
public:
	//Legalizer (DB* db, Placement* pl) : _db(db), _pl(pl) {}
	Legalizer (DB* db): _db(db) {}
	void doInGridLegalization (const GridBin&, Placement* pl, Dir d=_XX);
	void putCellsInBound(const BBox&);
	void putCellsInBoundRelative(const BBox&);
	std::vector<dbRow> snapCellsToRows(Placement*, const BBox& );
	std::vector<dbRow> snapCellsToRows(Placement*, const BBox&, double );
	void addVerticalSpace(Placement* , BBox&, double );	
	void groupAndShift(Placement*,BBox&,unsigned,double, double);
	
	void shiftCellsInRowVertically
	  (Placement*,dbRow&,double,double);
	void shiftCellsInRowHorizontally
 	  (Placement*, dbRow& curRow, double);
	  
	void addNonLinSpace
	  (Placement*,BBox&,double,double,double); 

	void doFinalPadPl();
	
	void legalizeCellsInPlace
	 (const GridBin&, Placement* pl, double xMovement = Constants::PITCH, Dir d = _XX);	
	 
	 
	void doLazyLeg (const GridBin&, Placement*, 
		double alHoriz = 1.0, double alVert = 1.0);
		
	void doLazyLegX (const GridBin&, Placement*, 
		double alHoriz = 1.0);
	void doLazyLegY (const GridBin&, Placement*, 
		double alHoriz = 1.0);
		
   void groupAndShift
  ( Placement* pl, BBox& bb, unsigned gSize, double horizSpace, std::vector<double>& vertSpace);
   void addVerticalSpace
	(Placement* pl, BBox& bb, std::vector<double>& sp);
	
  std::vector<dbRow>  snapCellsToRows
	(Placement* pl, const BBox& bb, const std::vector<double>& yHeights);

	
};

	

#endif //LEGALIZER_H