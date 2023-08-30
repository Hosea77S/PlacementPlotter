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


#include "confParser.h"
#include <iostream>
#include <fstream>
#include <boost/regex.hpp>

std::string confParser::getRegExPattern()
{

	std::string re="((?:[A-Za-z0-9_]+))";	// Variable Name 1
	re+="(\\s*)";	// White Space 1
	re+="(=)";	// Any Single Character 1
	re+="(\\s*)";	// White Space 2
	re+="(\")";	// Any Single Character 2
	re+="([+-]?\\d*\\.*\\d*)(?![-+0-9\\.])";	// Float 1
	re+="(\")";	// Any Single Character 3

	return re;	
}

void confParser::setVarVal
  (std::map< std::string, std::string >& vars, std::string varName,
   double& varVal)
{
  if (vars.find(varName) != vars.end() ){
    varVal =  (double) std::stof( vars.at(varName) );	  	
    //std::cout << "Setting var " << varName << " to value: " <<  varVal  << "\n";	  
  }
  return;
}


void confParser::setGlobalConst(std::string fileName)
{
  auto vars = parseConfigFile(fileName);

  setVarVal(vars, "SPL_HEIGHT"  , Constants::SPL_HEIGHT   );
  setVarVal(vars, "SPL_WIDTH"   , Constants::SPL_WIDTH    );
  setVarVal(vars, "PAD_WIDTH"   , Constants::PAD_WIDTH    );
  setVarVal(vars, "PAD_HEIGHT"  , Constants::PAD_HEIGHT   );
  setVarVal(vars, "PAD_OFFSET"  , Constants::PAD_OFFSET   );
  setVarVal(vars, "PITCH"       , Constants::PITCH        );
  setVarVal(vars, "SPL_DELAY"   , Constants::SPL_DELAY    );
  setVarVal(vars, "JTL_DELAY"   , Constants::JTL_DELAY    );
  setVarVal(vars, "JTL_WIDTH"   , Constants::JTL_WIDTH    );
  setVarVal(vars, "JTL_HEIGHT"  , Constants::JTL_HEIGHT   );
  setVarVal(vars, "SPEED_OF_PTL", Constants::SPEED_OF_PTL );  
  
  return;	
}


std::map< std::string, std::string >
 confParser::parseConfigFile
 (std::string fileName)
{
	std::map< std::string, std::string > vars;	

	std::ifstream fin(fileName);
	if (!fin.is_open())
		myAssert2(0, "(E) Error opening input file: ", fileName);

	std::string line;
	std::string pattern = getRegExPattern();  
	boost::regex rePattern(pattern, boost::regex::icase);

	while(getline(fin, line)) {
			if (line[0]=='#') continue;	  
			boost::smatch match;
			if(! boost::regex_search(line, match, rePattern)) continue;

			std::string varName =  match.str(1);
			std::string varVal  =  match.str(6);

			varName.erase(remove_if(varName.begin(), varName.end(), isspace), varName.end());
			varVal.erase(remove_if(varVal.begin(), varVal.end(), isspace), varVal.end());

			vars [ varName ] = varVal;
	}

  // std::cout << "\n\nParsed file: " << fileName << ":\n" << vars << "\n\n";

  return vars;  
}
