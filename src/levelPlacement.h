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

#ifndef LEVELPLACEMENT_H
#define LEVELPLACEMENT_H

#include "DB.h"
#include "padPl.h"
#include "globPlacement.h"
#include "Legalization.h"
#include "plotter.h"

class levelPlacement
{
private:
  DB* _db;	
  std::map<unsigned, std::vector<dbCell*>> _level2CellMap;
  BBox _sourceBB;
  unsigned _numGPIt;


public:
  levelPlacement(DB* db, unsigned n): _db(db) {
 	_level2CellMap = (*_db).getNetlist().getLevel2CellMap();
	_sourceBB = (*_db)._rowDefs->getChipBbox();
	_numGPIt = n;
  }	
  
  levelPlacement(DB* db): _db(db) {
 	_level2CellMap = (*_db).getNetlist().getLevel2CellMap();
	_sourceBB = (*_db)._rowDefs->getChipBbox();
	_numGPIt = 400;
  }	

  void doPlaceCells( int ac, const char* av[], bool changeLoc = true);
  void doPlaceCellsByLevel(unsigned level);
  void reduceDB(DB&, unsigned level, bool changeLoc = true);
  void checkLevel(unsigned level);
  Point getTotalWandH(unsigned level);
  
  
	
};




#endif //LEVELPLACEMENT_H