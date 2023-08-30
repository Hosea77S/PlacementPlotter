#include <iostream>
#include "bookShelfParser.h" 
#include "DB.h"
#include "plotter.h"
#include "confParser.h"

using namespace std;

void parseConfigFile(string confFileName)
{

  //auto confFileName = p.getConfigFileName();
  cout << "\n\nInput Config file: " << confFileName << "\n";
  if ( !checkFileExists(confFileName) ){
    myWarn3(0, "Can't find or open config file: ", confFileName, " Using default values.");
  }
  else {
	confParser cp;
	printf("Before: PITCH: %f, SPL_W:%f, SPL_H:%f, PAD_W:%f, PAD_H:%f, SPL_D:%f\n", Constants::PITCH,
		Constants::SPL_WIDTH, Constants::SPL_HEIGHT, Constants::PAD_WIDTH, Constants::PAD_HEIGHT,
		Constants::SPL_DELAY);

	//auto out = cp.parseConfigFile(confFileName);
	//for (auto& i: out)
	//	cout << i.first << ":==" << i.second << "\n";
	cp.setGlobalConst(confFileName);

	printf("After: PITCH: %f, SPL_W:%f, SPL_H:%f, PAD_W:%f, PAD_H:%f, SPL_D:%f\n", Constants::PITCH,
		Constants::SPL_WIDTH, Constants::SPL_HEIGHT, Constants::PAD_WIDTH, Constants::PAD_HEIGHT,
		Constants::SPL_DELAY);

  }
}


void placement_plotter(int argc, const char* argv[])
{
	cout << "Hello Phetla" << endl;
	
	// line 421
	bookshelfParam p (argc, argv);
	// line 427
	DB::Parameters dbParams;
	DB db(dbParams);
	bookShelfParser parser(&db, p); // strange obj
	string path = db.getDesignPath();

	// line 437
	if (p.getConfigFileName().size()){
	  parseConfigFile(p.getConfigFileName());
	}

	// line 849
	Plotter plot ( &db );
	// line 902
	plot.plotPlacementResult ( db.getDesignPath() + db.getDesignName() + "_final", true, false);
	
	return;
}

int main(int argc, const char* argv[])
{
	placement_plotter(argc, argv);
    return 0;
}