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


#ifndef PADPL_H
#define PADPL_H

#ifndef COMMON__H
#include "common.h"
#endif

#include "DB.h"
#include "placement.h"

//changelog
//22.06.2018 changed pad spacing in y dir to be equal to rowHeight


class padPl {
private:
  DB* _db; //changes the placement for improving pad placement
  Placement* _pl;

  
public:
  padPl(DB* db, Placement* pl): _db(db), _pl(pl)
  {}
  
  void reOrderPads();
  void reOrderPads(Point base);
  bool improvePadPlacement ( unsigned maxItr = 100 ); 
  //void improvePadPlacement( Placement* pl, unsigned maxItr = 20 ) ;  
private:
void changePadlocation(int cellIdx, int x_loc, int y_loc);
bool findCellPadIdx(unsigned, int&, int&);	

bool improvePadPlacementSub( Placement* ); 


};




#endif //PADPL_H