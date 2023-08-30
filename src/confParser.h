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

#ifndef _CONFPARSER_H
#define _CONFPARSER_H

#include "common.h"




class confParser
{
private:
  std::string getRegExPattern();
void setVarVal
  (std::map< std::string, std::string >& vars, std::string varName,
   double& varVal);
  
public:
  confParser(){};
  std::map< std::string, std::string >
     parseConfigFile(std::string fileName);
	 
  void setGlobalConst( std::string fileName );
  	 
	
};


#endif //_CONFPARSER_H