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

#ifndef DETAILEDPL_H
#define DETAILEDPL_H

#ifndef COMMON__H
#include "common.h"
#endif

#include "DB.h"

using std::string;

class detailedPL { 

private:
  const DB* _db;
	
public:
  detailedPL(const DB* chip);
  
  string doDetailedPlacement_FP();  
  string doDetailedPlacement( bool legal = true, bool dp = true);
  std::string doLegalization();
  
  /*std::string getNewFileName(std::string designPath, std::string designName);
  std::string FP_getNewFileName(std::string designPath, std::string designName);  
  void do_FAST_DP(std::string designPath, std::string designName); */
  
};




#endif // DETAILEDPL_H