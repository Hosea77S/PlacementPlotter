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

#ifndef CLOCKTREE_H
#define CLOCKTREE_H

//#define SPEED_OF_PTL 100.0

#ifndef COMMON__H
#include "common.h"
#endif

#include "DB.h"


class clockTree
{
public:
  int _rootId;
  DB* _db; 
  Placement* _pl;
  std::vector<dbClkCell*> _tree;

  //clockTree(): _rootId(-1), _db(NULL){}
  clockTree(int id, DB* db, std::vector<dbClkCell*> v):
  _rootId(id), _db(db), _pl(&((*db)._spatial.locations)), _tree(v) {}
  clockTree(int id, DB* db, Placement* pl, std::vector<dbClkCell*> v):
  _rootId(id), _db(db), _pl(pl), _tree(v) {}
  
  std::vector<double> calcDelay (bool cell = true);
  void calcDelay_sub (int,std::vector<double>&, double, bool cell = true);  
  const dbCell* getLeftCell (int)  const;
  const dbCell* getRightCell(int) const;
  const dbClkCell* getLeftClkCell (int)  const;
  const dbClkCell* getRightClkCell(int) const;
  double calcSkew(const std::vector<double>&);
  std::vector<double> calcAllDelay(bool );
  std::vector<double> calcLeafDelay(bool );

  int getNeighbor(int id);
  bool minimizeSkew(bool minMaxDelay = false, double coef = 1.0);  
  std::pair<double,double> calcLeftRightDelay(int, bool useDbCell = true);
  double calcDistFromChild 
   (int id, Dir d = _XX, Child ch = _LEFT, bool useDbCell = true);
  
  int getMaxHeight ();	
  std::pair<double, double> getLRDelay (int, const std::vector<double>& );
  
};





#endif //CLOCKTREE_H
