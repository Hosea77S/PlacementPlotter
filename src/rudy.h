#ifndef RUDY_H
#define RUDY_H


#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <vector>

#ifndef COMMON__H
#include "common.h"
#endif

#include "DB.h"
#include "placement.h"


class Rudy
{
private:
  const DB* _db;
  const Placement* _pl;
  BBox _bbox;
  
public:
  
  Rudy(const DB* db, const Placement* pl): _db(db), _pl(pl) { _bbox = ((*db)._rowDefs->getChipBbox()); }
  std::vector<double> calcRudy();  
	
};

#endif //RUDY_H