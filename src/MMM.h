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


#ifndef MMM_H
#define MMM_H

#ifndef COMMON__H
#include "common.h"
#endif

#include "DB.h"
#include "ctsParser.h"


typedef std::vector<dbClkCell> ClkVec;

class MMM
{
private:
  const DB* _db;  
  Placement _pl;
  std::vector<int> _clockSinks;	

  
  ClkVec _clkTop; //is only set by buildTopology
  
  std::vector<int> getClkSinks();
  void basicMMM(std::vector<int>&, ClkVec&, Dir d = _XX );
  void writeTopology(std::string, const ClkVec&);
  void drawClockTreeTop(std::string, const ClkVec&);
  void basicMMM_sub 
  (std::vector<int>&, ClkVec& clkTop, int&, int, int, Dir);
  Point getCOM(const std::vector<int>& );
  std::map<int,int> changeIds2(ClkVec& ); // for pre-cts-buffer-insertion
  void changeIds(ClkVec& );  
  bool isClockTreeBalanced(const ClkVec& );
  void updatePlacement(const ClkVec& );
  
public:
  MMM(const DB* db, const Placement* pl, 
    std::vector<int> cls): _db(db), _pl(*pl)
	{
		Placement tmpPl(cls.size(), Point(0,0));
		for (unsigned i=0; i < cls.size(); i++)
		  tmpPl[i] = (*pl)[ cls.at(i) ];
        _pl = tmpPl;
		
		
		std::vector<int> tmp(cls.size(),0);
        for (unsigned i=0; i < cls.size(); i++)
          tmp.at(i) = i;
       _clockSinks = tmp;
		
		
		//_clkTop = ClkVec temp;
		std::cout << "\n\tTotal # of clock sinks: " << _clockSinks.size() << "\n";
	}

  //std::string buildTopology(ClkVec&,std::map<int,int>& );
  std::string buildTopology();
  unsigned getNumClkSinks() { return _clockSinks.size(); }
  Placement getTappingPoints() const { return _pl; }
  void insertDummyNodes(ClkVec& );  
  
  ClkVec getClkSinksPostTop(ClkVec&);
  
  std::string buildTopology2
  (std::vector<dbClkCell>& , std::map<int,int>& );
  
  ClkVec getClockTopVec() {return _clkTop;}
  bool isClockTopSet() { return _clkTop.size() > 0; }
  
};


#endif //MMM_H