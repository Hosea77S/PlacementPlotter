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

#ifndef CTSPARSER_H
#define CTSPARSER_H

#include "common.h"
#include "DB.h"
#include <iostream>
#include <fstream>
#include <sstream>

class ctsParser {
	
public:
  std::string _desName;
  std::string _desPath;
  
 
  ctsParser(std::string n, std::string p): 
	_desName(n), _desPath(p)
  {}  
  
  
  void writeToSinksFile (const Placement* , std::string );
  std::vector<dbClkCell*> readFromClocksFile(std::string );
  void parseClocksFile(std::string , std::vector<dbClkCell*>& );
  void write2TopologyFile (std::string, const std::vector<dbClkCell>&);
  void writeTopology2DotFile (std::string, const std::vector<dbClkCell>&);
	
private:  
  	
};



#endif //CTSPARSER_H