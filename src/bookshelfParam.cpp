#include "bookshelfParam.h"


void bookshelfParam::readALLFiles(){
	
	
	for (unsigned int i=0; 
		i < _cmdlParser.bookshelfFileNames.size(); i++){
		BSFile cur = _cmdlParser.bookshelfFileNames[i];
		switch (cur._t){
			case(LEVELS):
				levelsFileName = std::string(cur);
				break;
			case (NETS):
				netsFileName = std::string(cur);
				break;
			case (NODES):
				nodesFileName = std::string(cur);
				break;
			case (PL):
				plFileName = std::string(cur);
				break;
			case (SCL):
				sclFileName = std::string(cur);
				break;
			case (WTS):
				wtsFileName = std::string(cur);
				break;
			default:
				myAssert2 (0, "Unknown input file: ", std::string(cur));
				break;
		}
			
	}
	
	if (levelsFileName.size() == 0)   myWarn(0, "ERROR: No levelsFile found.");
	if (netsFileName  .size() == 0) myAssert(0, "ERROR: No netsFile   found.");
	if (nodesFileName .size() == 0) myAssert(0, "ERROR: No nodesFile  found.");
	if (plFileName    .size() == 0) myAssert(0, "ERROR: No plFile     found.");
	if (sclFileName   .size() == 0) myAssert(0, "ERROR: No sclFile    found.");
	if (wtsFileName   .size() == 0) myAssert(0, "ERROR: No wtsFile    found.");


	allDesignFiles.push_back(levelsFileName);
	allDesignFiles.push_back(netsFileName);
	allDesignFiles.push_back(nodesFileName);
	allDesignFiles.push_back(plFileName);
	allDesignFiles.push_back(sclFileName);
	allDesignFiles.push_back(wtsFileName);
	
	std::cout << "allDesignFiles: " << allDesignFiles << std::endl;
	
	return;
}


bookshelfParam::bookshelfParam(int argc, const char *argv[]): _cmdlParser(argc, argv){
readALLFiles();
}


