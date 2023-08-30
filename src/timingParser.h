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


#ifndef _TIMINGPARSER_H
#define _TIMINGPARSER_H

#include "common.h"

typedef std::tuple<std::string, std::string,  std::string> tuple3dStr;
typedef std::tuple<std::string, std::string,  std::string, std::string> tuple4dStr;


class timingParser 
{
private:
  std::string getHoldRegExPattern();    
  std::string getSlackRegExPattern();    


public:  
  timingParser(){}    
  std::vector< tuple3dStr >
    readHoldSlackFile (std::string fileName);  	
  std::vector< tuple4dStr >
    readSlackFile (std::string fileName);  	
	
	
};























#endif //_TIMINGPARSER_H