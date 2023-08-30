#ifndef BOOKSHELFPARAM_H
#define BOOKSHELFPARAM_H

#include "paramParser.h"



class bookshelfParam {
	
	
public:
  
  paramParser _cmdlParser;    //command line parser  
  bookshelfParam(int argc, const char *argv[]);  
  
  const std::string getDesignName() 
	{ return _cmdlParser.designName; }
  const std::string  getDesignPath() 
	{ return _cmdlParser.AUXFilePath; }
  const std::string  getAUXName() 
	{ return _cmdlParser.AUXFileName; }
  unsigned getGroupSize()
  { return _cmdlParser.groupSize; }
  unsigned getAlgType()
  { return _cmdlParser.algoType; }
  unsigned getNumGPIt()
  { return _cmdlParser.numGPIt; }  
  int getXSpace()
  { return _cmdlParser.xSpace; }  
  int getYSpace()
  { return _cmdlParser.ySpace; }  
  bool doRDP()
  { return _cmdlParser.doRDP; }
  bool doBalanceCTS()
  { return _cmdlParser.balanceCTS; }
  unsigned useLP()
  { return _cmdlParser.useLP; }
  bool genLayout()
  { return _cmdlParser.genLayout;}
  double getAR()
  { return _cmdlParser.aspectRatio;}
  double getWS()
  { return _cmdlParser.whiteSpace;}
  bool fixHoldVio()
  { return _cmdlParser.fixHold;}
  unsigned getTopType()
  { return _cmdlParser.lpTopType;}
  bool doSSTA()
  { return _cmdlParser.doSsta;}
  bool doReplc() // Add by XL, incremental placement, 04.15.2021
  { return _cmdlParser.replc; }
  bool doIncre() // Add by XL, incremental placement, 04.15.2021
  { return _cmdlParser.incre; }


  std::string getConfigFileName()
  { return _cmdlParser.configFileName;}

  std::string getLEFFileName()
  { return _cmdlParser.lefFileName;}
  
  
  void setDesignName (std::string n) { _cmdlParser.setDesignName(n); }
  
  std::string getLevelsFileName(){return levelsFileName;}
  std::string getNetsFileName  (){return netsFileName  ;}
  std::string getNodesFileName (){return nodesFileName ;}
  std::string getPlFileName    (){return plFileName    ;}
  std::string getSclFileName   (){return sclFileName   ;}
  std::string getWtsFileName   (){return wtsFileName   ;}
  std::vector<std::string> getAllDesignFiles(){return allDesignFiles;}

  friend std::ostream& operator<<(std::ostream& os, const bookshelfParam& p);  

private:  
  std::string levelsFileName;
  std::string netsFileName;
  std::string nodesFileName;
  std::string plFileName;
  std::string sclFileName;
  std::string wtsFileName;
  std::vector<std::string> allDesignFiles;
  
  void readALLFiles();
  	
};


inline std::ostream& operator<<
 (std::ostream& os, const bookshelfParam& p)
 {
   os << p._cmdlParser << "\n";
   return os;
 }




#endif //BOOKSHELFPARAM_H
