#ifndef ROUTINGDRIVENP_H
#define ROUTINGDRIVENP_H

#include "qcMatrixGen.h"
#include "gridMapper.h"
#include "DB.h"
#include "qpSolver.h"
#include "padPl.h"
#include "subPlacement.h"
#include "mapping.h"
#include "Legalization.h"
#include <algorithm>

bool compare_Allowance(double a, double b);
bool compareLogic(double a, double b);


bool compareSlack(const std::pair<int,double> &a, const std::pair<int,double> &b );

bool compareRowMax(const std::pair<int,double> &a, const std::pair<int,double> &b );


struct RScore
{
  public:
  double minX;
  double maxX;
  double hScore; 
  int columnId;
  double belowY;
  std::vector <unsigned> netList;

  RScore(double x_1 = 0, double x_2 = 0, double h =0, int id=0, double yPos=0 ): //Did refer dbRowdef.h #10
  minX(x_1), maxX(x_2), hScore(h), columnId(id), belowY(yPos)
  {}
  
};

bool compareScore(const RScore& a, const RScore& b);



class RDP {

private:
   DB* _db;
   BBox _sourceBB;
   const int phaseC = 1; //For Requested AQFP phase level constraint is 4 
   double xAggrMove = 0.6666666;
   double xModMove = 0.3333333;
   const int RowScore_num = (*_db)._rowDefs->getChipWidth()/50;   //50 is standard cell height

   const double swapHpwlAllowed = 0.1; //increase of 10 % allowed 
   int windowCur;
    const int windowInit =6;
public:
	RDP( DB* db):  _db(db){
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
	cout << "Initial Density: " << density << endl; */
	

	}
	BBox getBBox() const { return _sourceBB; }


	void minimizeMaxWLr  ( unsigned maxIt  );  //( unsigned maxIt = 1 );	
	bool minimizeMaxWLSubr  (unsigned netIdx, double cNetHpwl);
	bool moreThanPhase (std::vector <unsigned> &cellid) const;//, std::vector <int> &mcellid );

	std::vector<unsigned> connNetIds(unsigned &cellId, unsigned &cNetId);
	std::vector<unsigned> getAllNetIds(unsigned &cellId);
	std::vector<unsigned> getCellidsByNetid(unsigned &netId) const;

	double yAllowanceUpCalc(const unsigned &mCellid, const double &cPath, unsigned &netId);
	double yAllowanceDownCalc(const unsigned &mCellid, const double &cPath, unsigned &netId);

	bool MoveUpLogic( unsigned &moveCellid,  unsigned &cNetId, const double &cNetHPWL);
	bool MoveDownLogic( unsigned &moveCellid,  unsigned &cNetId, const double &cNetHPWL);

	double xAllowanceRightCalc(const unsigned &mCellid, const double &cPath,  unsigned &netId);
	double MoveRightCalc( unsigned &moveCellid,  unsigned &cNetId, const double &cNetHPWL, unsigned &MaxcCellid);

	double xAllowanceLeftCalc(const unsigned &mCellid, const double &cPath,  unsigned &netId);
	double MoveLeftCalc( unsigned &moveCellid,  unsigned &cNetId, const double &cNetHPWL, unsigned &MincCellid);

	void MoveCell(Placement& pl,unsigned cellId, double x, double y);

	bool moveExecuter();

//Items for Routing Vector

	std::vector <double> passToLeag;	

	std::vector < std::vector<RScore> > routeVect;

        std::vector < std::vector<RScore> > routeVectSwap;

	std::vector < std::tuple <int,unsigned, unsigned> > searchNetinRV (unsigned net_id);

	std::vector<RScore> aboveChip;

	std::vector<RScore> belowChip;

	std::vector<RScore> aboveChipSwap;

	std::vector<RScore> belowChipSwap;

	void routingVecGen ();
	std::vector < std::vector<RScore> > getRoutingVec () {return routeVect;}

	std::pair <int, unsigned> Filter1 (unsigned net_id); //oreder, netid

	void FilterAB (unsigned net_id);	

 	bool cellTopRow(double yPos); //are cells on top cell

	bool cellBotmRow(double yPos);

	void routeEstimate (unsigned maxIt);

        int getRowPos(double yPos);

	void printScore();

	double getMaxRowPos() const {return (*_db)._rowDefs->stdRows[ (*_db)._rowDefs->stdRows.size() - 1 ].lowerLeftY; }

        double getMinRowPos() const {return (*_db)._rowDefs->getYOffset(); } 

	double getCellX(unsigned cellId) const {return (*_db).getNetlist().getCellByIdx( cellId )._origin.x; }

	double getCellY(unsigned cellId) const {return (*_db).getNetlist().getCellByIdx( cellId )._origin.y; }

	int getRowNumDif(double y_high, double y_low) {return ( y_high - y_low ) / (*_db)._rowDefs->getRowHeight();}

	double thresSetter(double percent);

	void scoreAssign(int xFront, int xBack, int RVnum, unsigned net_id);

	void scoreAssignAboveBelow(int xFront, int xBack, bool above, unsigned net_id);

	void windowInitiate();

	bool swapEx(int rowRV);
      
	double getMaxRowScore(int rowRV);

	int getMaxColId(int rowRV);

	bool swapEx1(int rowRV, int colId );

	bool swapEx2(int rowRV, int colId, unsigned netId );

	bool swapRight( unsigned swapCan, int rowRV, int colId );

	bool swapLeft( unsigned swapCan, int rowRV, int colId );

	std::pair <bool, unsigned> searchCell(double xLeft, double yBotLeft); //return true and number if cells found.  if it is whitespace, then false. 

	bool swapAction (unsigned candAId, std::pair<bool, unsigned> candB, int rowRV, int colId ); //cand B true means cell existing,

	void alphaSwap( std::vector < std::vector<RScore> > &updatedRV, unsigned net_id,  std::vector < std::tuple <int,unsigned, unsigned> > netRV, int swapBCol, std::vector<RScore> &abChip, std::vector<RScore> &beChip);
	

	void betaSwap( std::vector < std::vector<RScore> > &updatedRV, unsigned net_id,  std::vector < std::tuple <int,unsigned, unsigned> > netRV, int swapBCol, std::vector<RScore> &abChip, std::vector<RScore> &beChip);


};








#endif //ROUTINGDRIVENP_H
