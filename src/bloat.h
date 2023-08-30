#ifndef BLOAT_H
#define BLOAT_H

#ifndef COMMON__H
#include "common.h"
#endif

#include "DB.h"
#include "placement.h"


class bloat 
{
private:
  DB* _db; //changes the placement for improving pad placement
  //Placement* _pl;
  BBox _oldBB;
  
public:
  //bloat(DB* db, Placement* pl): _db(db), _pl(pl) {}
  bloat(DB* db): _db(db) 
  { 
  _oldBB = (*db)._rowDefs->getChipBbox(); 
  }


  std::vector<double> expandSize(Dir, double);  
  void revertSizeExp ( const std::vector<double>&, double, Dir);
  
	
};



#endif //BLOAT_H