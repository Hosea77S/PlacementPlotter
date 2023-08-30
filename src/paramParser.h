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


#ifndef PARAMPARSER_H
#define PARAMPARSER_H


#include <boost/algorithm/string.hpp>
#ifndef COMMON__H
#include "common.h"
#endif

#include <exception>
#include <fstream>


enum fileType 
	{ LEVELS= 1, NETS= 2, NODES= 3, PL=4, SCL=5, WTS=6, OTHER=7};

class BSFile {
public:
  std::string _name;
  fileType _t;
  BSFile(std::string name);
	
operator std::string() const{
	std::string out;
	out += _name + ".";
	if (_t == LEVELS) out += "levels";
	else if (_t == NETS) out += "nets";
	else if (_t == NODES) out += "nodes";
	else if (_t == PL) out += "pl";
	else if (_t == SCL) out += "scl";
	else if (_t == WTS) out += "wts";	
	return out;
}
//TODO fix this mess
friend std::ostream& operator<<(std::ostream& os, const BSFile& b){
	std::string t = b;
	os << t ;
	return os;
}
};
	
class paramParser {
	
	
public:
  std::vector<std::string> params;
  std::vector<BSFile> bookshelfFileNames;
  std::string AUXFileName;
  std::string AUXFilePath;
  std::string designName;
  std::string fullDesignPath;
  //std::string fullDesignName;  
  unsigned groupSize;
  unsigned algoType;
  bool balanceCTS;
  bool doRDP;  
  unsigned numGPIt;  
  int xSpace; 
  int ySpace;  
  unsigned useLP;  
  bool genLayout;  
  double aspectRatio;
  double whiteSpace;
  double layoutX;
  double layoutY;
  bool fixHold;
  unsigned lpTopType;
  bool doSsta;
  bool replc; // Add by XL, false: placement, true: re-placement with hold buffers after qHold
  bool incre; // Add by XL, false: normal placement solution, true: intermediate placement solution for incremental placement 
  
  std::string configFileName;
  std::string lefFileName;
  
  paramParser(int argc, const char *argv[]);		
  operator std::string() const;
  friend std::ostream& operator<<(std::ostream& os, const paramParser& p);

  void setDesignName (std::string n) 
    { 
	  designName = n; 
	  AUXFileName = n + ".aux";
	  fullDesignPath = AUXFilePath + AUXFileName;	  
	}

  
private:
  void printHelp();
  void readAUXfile();
  
};




#endif //PARAMPARSER_H
