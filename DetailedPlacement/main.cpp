#include "bookshelf.h"
#include "DetailedPlacement.h"
#include "Legalization.h"

std::pair <bool, bool> parseArgs ( int argc, char *argv[] )
{
  bool leg = false;
  bool dp = false;
  for (int i=0; i < argc; i++)
    if ( strcmp("-dp",argv[i]) == 0 )
	  dp = true;
    else if ( strcmp("-legalize",argv[i]) == 0 )
	  leg = true;
  
  return std::make_pair (leg, dp);
	
}

int main( int argc, char *argv[] )
{
	
    if (argc < 2)
    {
        cerr << "(E): Aux file missing" << endl;
        return -1;
    }

	cout << "-Parsing Input Files .." << endl << endl;

    bookshelfParser   parser;
	Model   *chip = parser.read(argv, argc);	
	DetailedPlacement DP(chip, 19);
	Legalizer legalch(chip);
	
	std::pair<bool,bool> leg_DP = parseArgs ( argc, argv );
	bool leg = leg_DP.first;
	bool dp = leg_DP.second;
	cout << "leg: " << leg << " dp: " << dp << "\n";
	
	
	if (leg && dp){
		DP.removeOverLaps();
		DP.royjRemOverlaps(); 
		//DP.SimAnnealing();
		DP.RowIroning();
		//DP.Update();
		DP.removeOverLaps();
		DP.royjRemOverlaps(); 		
		DP.Update();
		legalch.putCellsInBound();
		legalch.doLegalization();
		
	} else if (leg) {
		DP.removeOverLaps();
		DP.royjRemOverlaps(); 		
		DP.Update();
		legalch.putCellsInBound();
		legalch.doLegalization();		
	} else if ( dp )
	{
		//DP.SimAnnealing();
		DP.RowIroning();
		//DP.Update();
		DP.removeOverLaps();
		DP.royjRemOverlaps(); 		
		DP.Update();		
	} else {
		std::cout << "\n\nDidn't do anything. Didn't find command line options -legalize and -dp\n\n"; 
	}

	parser.PrintBenchmarkStatus();
	
	string fileName = parser.getDesignName();
	//removing placed from end of filename
	if ( fileName.size() > 7)
	{
	string temp = fileName.substr ( fileName.size() -7 );
	cout << "Temp: " << temp << endl;
	if (temp == "_placed")
		fileName.erase(fileName.end()-7, fileName.end());		
	}
	string outFileF = fileName + "_DP";
	parser.write(chip, outFileF);
	return 1;
}