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


#ifndef QCMATRIXGEN_H
#define QCMATRIXGEN_H

#ifndef COMMON__H
#include "common.h"
#endif


#include "DB.h"
#include "placement.h"


/*


get netlist and placement info
get net model
a function that traverses each net in X and Y direction

a function that adds to the q matrix (moveable and moveable)
a function that adds to the c matrix (moveable and fixed   )

a function that checks consistency of q matrix
a function that checks consistency of c matrix

a function to mirror_Matrix
a function to calculate distance between cells



*/

#define minPosDist  25.0
#define minAssumDist 30.0
//#define minPosDist  0.000001
//#define minAssumDist 1.0
#define POW 1.0


class qcMatrixGen
{

public:	
	enum NetModel { _B2B, _STAR, _CLIQUE};

private:
   const DB* _db;
   const Placement* _pl;
   NetModel _nm;

   std::map< INT_PAIR, double > _QmX, _QmY;
   std::map< int, double> _CmX, _CmY;

public:
	qcMatrixGen(const DB* db, const Placement* pl): 
		_db(db), _pl(pl), _nm(_B2B) 
		{
			generateQCMat();
			isQMconsistent( );
			isCMconsistent( );			
		}

	std::map<INT_PAIR, double> getQm(Dir );
	std::map<int, double> getCm(Dir );

   double getDistance(double a, double b);
	   //utility to add weight to _QmX,_QmY
   void addToQm ( Dir& d, INT_PAIR qIdx, double weight );
   void addToCm ( Dir& d, unsigned cIdx, double weight );
   void   isQMconsistent( );
   void   isCMconsistent( );

	~qcMatrixGen() {}
private:
   void   generateQCMat();	
   void   generateQCMat( Dir );	
   void   mirrorQM( Dir& );
   
   void   handleMovMov( Dir&, const dbCell& , const dbCell&, double );
   void   handleFixMov( Dir&, const dbCell& , const dbCell&, double );

   //consistency check
   void   isQMconsistent( const Dir& );
   void   isCMconsistent( const Dir& );
   

};



#endif //QCMATRIXGEN_H