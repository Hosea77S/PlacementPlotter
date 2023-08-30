#include "detailedPl.h"



detailedPL::detailedPL(const DB* chip){
	_db = chip;
}

std::string detailedPL::doLegalization()
{
	return doDetailedPlacement (true, false);
}

std::string detailedPL::doDetailedPlacement (bool legal, bool dp)
{
	//./DP ../ASC/CMOS/ks32bit/ ks32bit_Sol.aux
	string designName = (*_db).getDesignName() ;
	string auxName = designName + "_placed.aux";
	string designPath = (*_db).getDesignPath();
	
	string pathToDP = "./DetailedPlacement/";
	
	//deleting the seed to make sure results are deterministic
	//string deleteSeedCmd = "rm " + pathToDP + "seeds.out";
	//cout << "Calling command " << deleteSeedCmd << endl<< endl<< endl; 
	//system (deleteSeedCmd.c_str());
	
	

	string command = pathToDP + "DP ";
	
	command += designPath + " " + auxName ; 
	
	if ( legal ) command += " -legalize ";
	if ( dp ) command += " -dp ";

	command += " > " + designPath + "DP.log" ;
	int status = system (command.c_str());
	std::cout << "Calling command " << command << "\n\n\n"; 

	std::cout << "\n\n\n\nStatus: " << status << "\n\n";
	
	string newDPPL =  designName;
	newDPPL = designPath + "/" + newDPPL +"_DP.pl"; 
	
	//cout << "Reading From Detailed Placement file: " << newDPPL << endl;
	
	
	if ( !( status == 0 || status == 256 ) )
		newDPPL = "";
	
	return newDPPL;
}



string detailedPL::doDetailedPlacement_FP()
{
	string designPath = (*_db).getDesignPath();
	string designName = (*_db).getDesignName() ;
	string auxName = designName + ".aux";
	string plName = designName + "_placed.pl";
	
	string command = "./HGraph/FastPlace3.0_Linux64_DP -legalize  -target_density 1.0 " +  designPath + " " + auxName + " " +  
						designPath + " " + plName + " > " + designPath + plName  + "_FP.log";
	system (command.c_str());
	std::cout << "Calling command " << command << "\n\n\n";

	
	string newDPPL = designName + "_FP_dp.pl";
	newDPPL = designPath + "/" + newDPPL;
	
	std::cout << "Reading From Detailed Placement file: " << newDPPL << std::endl;
	
	return newDPPL;
}

/*
void detailedPL::do_FAST_DP
  (string designPath, string designName)
{
	
	//removing .aux part from design name
	string plName = designName;
	plName.erase (plName.end()-4, plName.end());
	plName += "_placed.pl";
	string command = "./ASC/FastPlace3.0_Linux64_DP -legalize  " +  designPath + " " + designName + " " +  
						designPath + " " + plName + " > " + designPath  + "FP.log";
	system (command.c_str());
	cout << "Calling command " << command << endl<< endl<< endl;
	
	
	return;
}



string detailedPL::getNewFileName
  (string designPath, string designName)
{
	string path = designPath; string newDPPL =  designName;
	newDPPL = path + newDPPL; newDPPL.erase(newDPPL.end()-4, newDPPL.end());
	newDPPL = newDPPL + "_DP.pl";
	return newDPPL;
}

string detailedPL::FP_getNewFileName
  (string designPath, string designName)
{
	string path = designPath; string newDPPL =  designName;
	newDPPL = path + newDPPL; newDPPL.erase(newDPPL.end()-4, newDPPL.end());
	newDPPL = newDPPL + "_FP_dp.pl";
	return newDPPL;
}
*/
