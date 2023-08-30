#include "paramParser.h"


BSFile::BSFile(std::string name) {
	std::vector<std::string> strs;
	boost::split(strs, name, boost::is_any_of("."));
	for (unsigned int i=0; i < strs.size()-1; i++)
		_name += strs[i];
	
	if (strs.size() < 2) {
		myAssert (false, "File name doesn't have any extensions.");
	}
	std::string ext = strs.back();
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
	if (ext == "levels") _t = LEVELS;
	else if (ext == "nets") _t = NETS;
	else if (ext == "nodes") _t = NODES;
	else if (ext == "pl") _t = PL;
	else if (ext == "scl") _t = SCL;
	else if (ext == "wts") _t = WTS;
	else {
		ext = "OTHER";
		myAssert2 (false, "Unknown file name: ", name);
	}
}


paramParser::operator std::string() const{
	std::string out ;
  	out = "Input Parameters: " + AUXFilePath + " - " + 
	AUXFileName + " - " + std::to_string(groupSize) + " - " 
	+ std::to_string(algoType) + " - " + std::to_string(xSpace) + 
	" - " + std::to_string(ySpace) ; 
	return out;
}

std::ostream& operator<<(std::ostream& os, const paramParser& p){
	os << "Input Parameters: AUX-PATH: " << p.AUXFilePath << " - AUX: " << 
	p.AUXFileName << " - groupSize: " << p.groupSize << 
	" - algoType: " << p.algoType <<
	" - numGPIt: " << p.numGPIt <<
	" - doRDP: " << std::to_string(p.doRDP) <<
	" - doCTSBalance: " << std::to_string(p.balanceCTS) <<
	" - xSpace: " << std::to_string(p.xSpace) <<
	" - ySpace: " << std::to_string(p.ySpace) <<	
	" - useLP: " << std::to_string(p.useLP) <<	
	" - configFileName: " << p.configFileName << 
	" - lefFileName: " << p.lefFileName << 
	//" - lpTopType: " << std::to_string(p.lpTopType) <<	
	" - replc: " << std::to_string(p.replc) <<   // Add by XL, 04.15.2021, replc with hold buffers or not 
	" - incre: " << std::to_string(p.incre) <<   // Add by XL, 04.15.2021, generate intermediate placement solution for incremental placement 
	"\n"; 
	return os;
}


void paramParser::printHelp(){
    std::cout << "\n\nqPlace: Placement and Clock Tree Synthesis for Single Flux Quantum Logic Circuits\n\n";	
	std::cout << "\n\nInput format is as follows: (Path To Benchmark) (AUX File Name) [optional]\n\n" ;
	std::cout << "+--------------- Description ---------------+\n\n";
	std::cout << "\tPath To Benchmark: Absolute/Relative path to directory with the benchmark files\n";
	std::cout << "\tAUX File Name    : Name of the aux File Ex: Adder.aux\n";
	std::cout << "\t-nGP [int]       : Number of Global Placement Iterations. Default: 100, Max: 400\n";
	std::cout << "\t-CONF [string]       : Absolute/Relative path + Name of the configuration file\n";
	std::cout << "\t-LEF [string]        : Absolute/Relative path + Name of the lef file\n";
	std::cout << "\t-RDP             : Perform Routability Driven Detailed Placement(RDP). Default: off \n";
	std::cout << "\t-BAL             : Balance the clock tree by adding buffers and replacing the clock gates. Default: off\n";
	//std::cout << "\t-GS              : SFQ Group Size: Size of the cell groups. Must be integer. Default: 1\n";
	std::cout << "\t-X               : Extra X spacing between adjacent logic cells in a row. Must be integer. Default: 0\n";
	std::cout << "\t-Y               : Extra Y spacing between consecutive rows. Must be integer. Default: 0\n";
    //(SFQ Group Size) (Placement Algorithm)	
	//std::cout << "\t-ALG             : Cell grouping algorithm: Default: 1\n";
	//std::cout << "\t                   Options 1 : Level-based clustering\n";
	//std::cout << "\t                   2 : Partitioning-based clustering\n";
	//std::cout << "\t         3 : Pre  Placement Inter Row Clustering\n";
	std::cout << "\t-LP              : Linear Program Solver (CTS): Default: 0\n";
	std::cout << "\t                   Options 0 : no LP (Degrades quality of CTS in terms of max clock skew)\n";
	//std::cout << "\t                           1 : CPLEX (Generates the best result in terms of clock skew)\n";
	//std::cout << "\t                           2 : COIN-OR (Higher run-time w.r.t CPLEX)\n";
	//std::cout << "\t-TOP              : Clock Tree Topology Type: Default: 1\n";
	//std::cout << "\t                   Options 0 : Method of means and medians (optimizes the wirelength only)\n";
	//std::cout << "\t                           1 : CPLEX (PLACEMENT_AWARE)\n";
	//std::cout << "\t                           3 : CPLEX (HOLD_PL_AWARE)\n";
    std::cout<<"\t-fixHold           : Internally calls the qSTA tool and fixes hold time violations. (Default: false)\n";
	//std::cout << "\t-SSTA              : Fixes Hold violations based on ssta. (Default: false)\n";
    std::cout<<"\t-LAYOUT            : Generates layouts for netlist. Default: false\n";
    std::cout<<"\t                           -AR [aspect ratio] (Width/Height) (Default: 1.0)"<<std::endl;
    std::cout<<"\t                           -WS [whitespace %] (Default: 10)"<<std::endl;
	std::cout << "\t-REPLC             : Re-placement with hold buffers after hold time fixing. Default: off\n"; // Add by XL, 04.15.2021
	std::cout << "\t-INCRE            : generate intermediate placement solution for incremental placement. Default: off\n"; // Add by XL, 04.15.2021
	std::cout << "\n\n+-------------------------------------------+\n";
	std::cout << "\n\n\n";
	
	return;
}



paramParser::paramParser(int argc, const char *argv[]){
	
    BoolParam h ("h", argc, argv);
    BoolParam help ("help", argc, argv);
	
	if ( h.found() || help.found() ){
	  printHelp();
      exit(0);	  
	}
	
	
	if (argc < 3) {
		myWarn(false, "Wrong input format: Too few arguments.\nFor usage enter $ qPlace -h\n");
		printHelp();
		myAssert(false, "");
	}
		
	std::cout << "-Parsing Input Files ..\n\n";
	this->AUXFilePath = std::string(argv[1]);
	if (AUXFilePath.back() != '/') AUXFilePath += '/';
	this->AUXFileName = std::string(argv[2]);
	this->fullDesignPath = AUXFilePath + AUXFileName;
	if (AUXFileName.substr(AUXFileName.size()-4) == ".aux"){
		this->designName = AUXFileName.substr(0, AUXFileName.size()-4);
		//std::cout << "Design Name: " << designName << "\n";
	} else {
		myAssert2 (false, "Invalid AUX name: ", AUXFileName);
	}
	
	this->algoType = 1;
	this->groupSize = 1;
	this->balanceCTS = false;
	this->doRDP = false;
	this->numGPIt = 100;
	this->xSpace = 0;
	this->ySpace = 0;
    this->useLP = LPType::noLP;	
    this->genLayout = false;	
	this->aspectRatio = 1.0;
	this->whiteSpace = 10;
	this->fixHold = false;
	this->lpTopType = TopType::MMM_GREEDY;
    this->doSsta = false;	
    this->configFileName = "";
    this->lefFileName = "";
	this->replc = false; // Add by XL, 04.15.2021
	this->incre = false; // Add by XL, 04.15.2021

    BoolParam doRDPParam ("RDP", argc, argv);
    BoolParam balCTSParam("BAL", argc, argv);
    IntParam algoTypeParam("ALG", argc, argv);
    IntParam groupSizeParam("GS", argc, argv);
    IntParam numGPParam("nGP", argc, argv);
    IntParam xSpaceParam("X", argc, argv);
    IntParam ySpaceParam("Y", argc, argv);
    IntParam doLP ("LP", argc, argv);
    BoolParam layoutParam("layout", argc, argv);
    //StringParam saveAsParam("f", argc, argv);
    DoubleParam  ARParam("AR", argc, argv);
    DoubleParam  WSParam("WS", argc, argv);
    BoolParam fixHoldParam("fixHold", argc, argv);
    IntParam doLpTopParam ("TOP", argc, argv);
    BoolParam sstaParam("SSTA", argc, argv);
    StringParam configFileParam("CONF", argc, argv);
    StringParam lefFileParam("LEF", argc, argv);
	BoolParam replcParam("REPLC", argc, argv); // Add by XL, 04.15.2021
	BoolParam increParam("INCRE", argc, argv); // Add by XL, 04.15.2021
  


	
    if (balCTSParam.found()) balanceCTS = true;	
    if (doRDPParam.found()) doRDP = true;	
    if (algoTypeParam.found()) algoType = (int)algoTypeParam;	
    if (groupSizeParam.found()) groupSize = (int)groupSizeParam;	
    if (numGPParam.found())	numGPIt = (int)numGPParam;
    if (xSpaceParam.found())	xSpace = (int)xSpaceParam;
    if (ySpaceParam.found())	ySpace = (int)ySpaceParam;
    if (doLP.found()) useLP = (int)doLP;	
    if (fixHoldParam.found()) fixHold = true;	
    if (sstaParam.found()) doSsta = true;	
	if (doLpTopParam.found()) lpTopType = (int)doLpTopParam;
	if (replcParam.found()) replc = true; // Add by XL, 04.15.2021
	if (increParam.found()) incre = true; // Add by XL, 04.15.2021
	
	if (layoutParam.found())
	{
	  genLayout  = true;	
	  if(WSParam.found())
		whiteSpace = WSParam;
	  else
		whiteSpace = 10;

	  if(ARParam.found())
	  {
		aspectRatio = ARParam;
		std::cout<<"Setting Aspect Ratio to "<<aspectRatio<<std::endl;
	  }
	  else
	  {
		aspectRatio = 1;
		std::cout<<"Using default Aspect Ratio of "<<aspectRatio<<std::endl;
	  }		
	}
	
    if (configFileParam.found()) this->configFileName = configFileParam;
    if (lefFileParam.found()) this->lefFileName = lefFileParam;

	
    myAssert2( groupSize <= 10 && groupSize > 0, "groupSize is not 0 < GS <= 10: ", groupSize );	
    myAssert2( algoType <= 4 && algoType > 0, "algoType is not  0 < algoType <= 4: ", algoType );	
    myAssert2( numGPIt <= 400 && numGPIt > 0, "numGPIt is not 0 < numGPIt <= 400: ", numGPIt );	
    myAssert2( xSpace >= 0, "xSpace is not >= 0 : ", xSpace );	
    myAssert2( ySpace >= 0, "ySpace is not >= 0 : ", ySpace );	
    myAssert2( useLP >= LPType::noLP && useLP <= LPType::CBC, "useLP is invalid : ", doLP );	
    myAssert2( lpTopType == TopType::PLACEMENT_AWARE || lpTopType == TopType::HOLD_AWARE || lpTopType == TopType::HOLD_PL_AWARE || lpTopType == TopType::MMM_GREEDY, "lpTopType  is invalid : ", lpTopType);	
	
	
    	
	/*if (argc > 3) {
		try {
			this->groupSize = atoi(argv[3]);
		} catch (std::exception& e) {
			myWarn (false, e.what());
			printHelp();
			exit(-1);
		}
		myAssert2 (groupSize > 0, "Invalid groupSize arg: ", argv[3]);
		if (argc > 4){
			try {
				this->algoType = atoi(argv[4]);
			} catch (std::exception& e) {
				myWarn (false, e.what());
				printHelp();
				exit(-1);
			}
		} 
		myAssert2 (algoType > 0 && algoType < 4, "Invalid algoType arg: ", argv[4]);
	}*/
		
	params = {AUXFilePath, AUXFileName, std::to_string(groupSize), std::to_string(algoType), std::to_string(numGPIt), std::to_string(xSpace), std::to_string(ySpace) };
	
	std::cout << *this << std::endl;
	readAUXfile();

	
}

bool isComma (char c) { return c==','; }

void paramParser::readAUXfile(){
	
    std::cout << "Reading " << AUXFileName << std::endl;
	
	std::ifstream file (fullDesignPath);
	if (file.is_open()){
		std::string s;
		bool f = (bool) getline(file, s);
		if (!f)	myAssert (0, "No lines in the AUX file. Exit");			
		
		std::vector<std::string> strs;
		boost::split(strs, s, boost::is_any_of(" :"));		
		
		for (unsigned i=0; i < strs.size(); i++){
			boost::trim( strs[i] ); 
			boost::trim_if(strs[i], &isComma);
			boost::trim_right_if(strs[i], &isComma);
			if (strs[i].size() == 0) {
				strs.erase(strs.begin()+i);
				i--;
			}
		}

		
		if (strs.front() == "RowBasedPlacement")
			strs.erase(strs.begin());
		std::sort( strs.begin(), strs.end());
		for (unsigned int i=0; i < strs.size(); i++){
			bookshelfFileNames.push_back(BSFile(strs[i]));			
		}
	
	} else {
		myAssert2 (0, "Can't open AUX file. Exit", fullDesignPath);
	}
	
	
	return;	
}