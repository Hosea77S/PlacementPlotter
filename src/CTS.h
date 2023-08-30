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


#ifndef CTS_H
#define CTS_H

#ifndef COMMON__H
#include "common.h"
#endif

#include "Legalization.h"
#include "DB.h"
#include "ctsParser.h"
#include "padPl.h"
#include "MMM.h"
#include "clockTree.h"
//#include "clockTopology.h"
//#include "LPInterface.h"


#define LL 4
#define LR 5
#define UL 6
#define UR 7
#define LEFT 0
#define RIGHT 1
#define UP_UP 2
#define DOWN 3

#define SPLITCLK_0 0
#define SPLITCLK_2 2
#define SPLITCLK_4 4
#define SPLITCLK_6 6





//TODO delete all dbClkCells in desctructor

//added newRowHeight as a arg to cstr

class CTS {
private:
  DB* _db;
  BBox _bbox;
  std::string _desName;
  std::string _desPath;
  double _rowHeight;
  unsigned _superRootId;
  unsigned _rootId;
  //std::vector<GridBin> _gridBins;  //initially empty, until set by ::buildClockTree
  
public:
  CTS (DB* db, BBox bb, std::string n, std::string p) : 
	_db(db), _desName(n), _desPath(p) {
		
	_bbox = BBox ( bb.getBottomLeft().x,
					 bb.getBottomLeft().y, 
					 bb.getTopRight().x, 
					 bb.getBottomLeft().y + 
						(*db)._rowDefs->getRowCnt() * ( (*db)._rowDefs->getRowHeight() + Constants::SPL_HEIGHT ) );
	_rowHeight = (*db)._rowDefs->getRowHeight() + Constants::SPL_HEIGHT;
		
  }
  CTS (DB* db, BBox bb, std::string n, std::string p, double rH) : 
	_db(db), _desName(n), _desPath(p), _rowHeight (rH) {
		
	_bbox = BBox ( bb.getBottomLeft().x,
					 bb.getBottomLeft().y, 
					 bb.getTopRight().x, 
					 bb.getBottomLeft().y + 
						(*db)._rowDefs->getRowCnt() * ( (*db)._rowDefs->getRowHeight() + Constants::SPL_HEIGHT ) );
		
  }

  std::string getDesignName(){ return _desName; }
  std::string getDesignPath(){ return _desPath; }
	
  double buildClockTree(bool fixTopology = false, bool preInsertHold = false, bool insertHoldSpl = false, unsigned useLP=LPType::CPLEX, unsigned topType=TopType::MMM_GREEDY, const std::vector<double>& channelHeights = std::vector<double>(), bool replc = false);
  std::vector<int> getClkSinkNodes();
  bool isEnoughSpacingBetweenRows ();
  void mergeClockSinksandSplitters
	(std::vector<dbClkCell*> &,  const std::vector<int> &);
	
  std::vector<GridBin>
   findSplitterLocations
    (const std::vector<dbClkCell*> &clkVec, unsigned useLP=LPType::CPLEX, const std::vector<double>& channelHeights = std::vector<double>());	
  void synthesizeClockTree(int, std::string, std::string s="" );	
  int findSplitterTypeBasedOnLocation(int , int , int );
  int findRespectivePosition(const dbCell* , const dbCell* );
  int findSplType(const std::vector<dbClkCell*> &, int );
  dbNet* addNetToChip (unsigned, unsigned, std::string, int);
  std::vector<dbNet *> routeClockNets(std::vector<dbClkCell*> &);
	
  void findAllLevels(int , const std::vector<dbClkCell*> &, int);
  bool checkIfClockTreeIsBalanced
   (const std::vector<dbClkCell*> &, const std::vector<int> &);

  void doFinalPadPl();
  void addHoldBuffers(std::vector<dbClkCell*> &, 
    const std::vector<int> &, 
	const std::vector<unsigned>&);  
  void addBufferToClkTree
  (std::vector<dbClkCell*> &, int );	
  std::vector<unsigned> getListOfImbalancedClkNodes
	   (std::vector<dbClkCell*> &, 
		 const std::vector<int> &, 
		  const std::vector<double>&);
  std::vector<unsigned> findDelayImbalancedNodes
      (const std::vector<double>& );


  //added 05.14.2019 for hclc 
  void setRootId(int id) { _rootId = id; }	  
  int getRootId() { return _rootId; }	  
  void setSuperRootId(int id) { _superRootId = id; }	  
  int getSuperRootId() { return _superRootId; }	  
  double getRowHeight()  { return _rowHeight; }
  BBox getBBox()  { return _bbox; }
  
  std::vector<int> getHeightVec
	  (const std::vector<dbClkCell*> &, 
	  const std::vector<int> &);
	  
  void legalizeClkCells
	(std::vector<GridBin>& );
	
  void fixDummyNodes
  (std::vector<dbClkCell*>& , 
    std::map<int,int>& );

  //calls minimizeSkew func from clockTree class
  void minimizeClkSkew (std::vector<dbClkCell*>& , 
    std::vector<GridBin>& , 
	  bool insertHoldSpl, bool minMaxDelay = false, double coef = 1.0);

  void updateClkVecByMMMSol
 (std::vector<dbClkCell*> &clkVec, 
  const std::vector<dbClkCell> & mmmClockTop);
	
	
   void adjustChipWidth(std::vector<GridBin>& clkCellGBins);

  //05.14.2019, added by soheil for hclc handeling
  void postProcessNetlist(){(*_db)._design.postProcess();}

  void legalAndReSyn(double xSpace = 0.0, std::vector<double> vSpacings = std::vector<double>() );
  
};




#endif //CTS_H

