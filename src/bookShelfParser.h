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


#ifndef BOOKSHELFPARSER_H
#define BOOKSHELFPARSER_H

#include "bookshelfParam.h"
#include "sclParser.h"
#include "myAssert.h"
#include "DB.h"
#include <iostream>
#include <fstream>
#include <exception>


//using namespace std;

class bookShelfParser {
	
	
public:
  
  DB* _db;
  bookshelfParam _auxParser;    //parser of the AUX file
								//contains name of the design files

  
  
  bookShelfParser(DB* db, const bookshelfParam& bsp): _db(db), _auxParser(bsp){
	(*_db).designName = _auxParser.getDesignName();
	(*_db).pathName = _auxParser.getDesignPath();
	(*_db).auxName = _auxParser.getAUXName   ();

	  readDesignFiles();
  };  
  
  
  //void printBenchmarkStatus();
  void writeBenchmark(std::string newFileName);
  void writeDesignFiles(bool wLev = false, bool wScl = false, bool precise = false, bool onlyClkNets = false);
  void setDesignName(std::string n)
   { _auxParser.setDesignName(n); }
  int  getGroupSize() { return _auxParser.getGroupSize(); } 

  //for reading legal solution
  void readPlFile();
  void readPlFile(std::string fullFileName);

  void writeToPlFile(std::string, bool precise = false);
  void writeSclFile(std::string fileName, dbRowDef dbRows);
  void writeSclFile();
  
private:  
  void readDesignFiles();  
  void readNodesFile();
  void readNetsFile();
  void readSclFile();
  void readWtsFile();
  void readLevelsFile();
  
  void writeToAUXFile(bool, bool);  
  void writeToNodesFile();
  void writeToNetsFile( bool onlyClkNets = false );
  void writeToPlFile( bool precise = false);
  void writeToLevelsFile();
  void writeToSCLFile();
  std::string determineCellType(std::string );

  	
};




#endif //BOOKSHELFPARSER_H