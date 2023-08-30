#ifndef _TIMINGANA_H
#define _TIMINGANA_H

#include "common.h"
#include "DB.h"
#include "timingParser.h"

class timingAna
{
private:
  DB* _db;  


std::vector< std::tuple <int, int, int, double> > 
 findHoldNets( std::vector< tuple4dStr >& hvp );
int calcNumHoldBuffs (double slack);
std::vector<dbCell*> createHoldBuffCells( int numHoldBuffs, Point pl, Point srcPl);
void addHoldBuffsToNetlist
 ( int netId, 
  std::vector<dbCell*>& holdBuffCells, int, int, int&);
void insertHoldBuffers
 ( std::vector< std::tuple <int, int, int, double> >& holdNets );   
dbCell* addNewJTLCell(Point pl, Point srcPl, int tCnt, int idx);
void createHoldBuffNets ( std::vector<dbCell*>& holdCells, int&);

int countNumHoldBuffs
 ( std::vector< std::tuple <int, int, int, double>  >& holdNets );


public:	
  timingAna(DB* db): _db(db){}
  bool fixHold(); //returns true if there are no hold violations in the input file
  bool fixHold(std::string); //returns true if there are no hold violations in the input file
	
};














#endif //_TIMINGANA_H