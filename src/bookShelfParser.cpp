#include "bookShelfParser.h"

void bookShelfParser::writeDesignFiles
 (bool wLev, bool wScl, bool precise, bool onlyClkNets )
{
	writeToAUXFile(wLev, wScl);
	writeToNodesFile();
	writeToNetsFile(onlyClkNets);
	writeToPlFile( precise );
	if (wLev) writeToLevelsFile();
/* 	if (!wScl) 
		writeToSCLFile();//this just duplicates the original scl file
	else  */
		writeSclFile();     //this writes into the layoutGenerated .scl file	

	
	return;
}

  void writeBenchmark(std::string newFileName);



void bookShelfParser::writeToAUXFile(bool wLev, bool wScl)
{
	std::string fileName = _auxParser.getDesignPath() + _auxParser.getDesignName() + "_placed.aux";
	std::cout << "\tWriting to aux file: \t" << fileName << std::endl;
	std::ofstream fout;
	fout.open(fileName);
	if (!fout)
	{
		myAssert2 (0, "(E) Error opening output file: " , fileName);
	}

	std::string desName = _auxParser.getDesignName() ;
	std::string desName_placed = desName + "_placed";
	fout << "RowBasedPlacement :  ";
	//fout << desName_placed << ".nodes  ";
	//fout << desName_placed << ".nets  ";
	fout << desName_placed << ".nodes  ";
	fout << desName_placed << ".nets  ";
	fout << desName << ".wts  ";
	fout << desName_placed << ".pl  ";
	//if (!wScl) fout << desName << ".scl  ";
	//else fout << desName_placed << ".scl  ";
	fout << desName_placed << ".scl  ";
	
	if (!wLev) fout << desName << ".levels  ";
	else fout << desName_placed << ".levels  ";
	fout << std::endl;
	fout.close();
	
	return;
}
	
	
void bookShelfParser::writeToSCLFile()
{
  std::string outFilename = _auxParser.getDesignPath() + _auxParser.getDesignName() + "_placed.scl"; ;
  std::string cmd = "cp " + _auxParser.getDesignPath() + _auxParser.getDesignName().substr(0, _auxParser.getDesignName().size()-4) + ".scl " + outFilename;
  std::cout << "calling cmd : " << cmd << std::endl;
  system(cmd.c_str());
  std::cout << "\n\tWriting to scl file   : \t" << outFilename << "\n"; 
	
}	

void bookShelfParser::writeToLevelsFile()
{

    std::string outFilename = _auxParser.getDesignPath() + _auxParser.getDesignName() + "_placed.levels"; ;
    std::ofstream fout;
    fout.open(outFilename);
	std::cout << "\n\tWriting to levels file   : \t" << outFilename << "\n";
	
    if (!fout)
    {
		myAssert2 (0, "(E) Error opening output file: " , outFilename);
    }


	fout << "UCLA nodes 1.0\n";
	fout << "# Created by Soheil Nazar Shahsavani (nazarsha@usc.edu) \n";
	//fout << "# Platform\n\n";
	//fout << "NumNodes : " << (*_db).getNetlist().getNumCells() << "\n";
	
	//fout << "NumTerminals : " << (*_db).getNetlist().getNumAllPads() << "\n";


	for ( auto itC = (*_db).getNetlist().cellsBegin();
	       itC !=  (*_db).getNetlist().cellsEnd();
		    itC ++ )
	{
		fout << "\t" << (*itC)->getName() << "\t"
			<< (*itC)->getLevel() ;
		fout << std::endl;
	}
	fout.close();
	
}
	
	

void bookShelfParser::writeToNodesFile()
{

    std::string outFilename = _auxParser.getDesignPath() + _auxParser.getDesignName() + "_placed.nodes"; ;
    std::ofstream fout;
    fout.open(outFilename);
	std::cout << "\n\tWriting to nodes file   : \t" << outFilename << "\n";
	
    if (!fout)
    {
		myAssert2 (0, "(E) Error opening output file: " , outFilename);
    }


	fout << "UCLA nodes 1.0\n";
	fout << "# Created by Soheil Nazar Shahsavani (nazarsha@usc.edu) \n";
	fout << "# Platform\n\n";
	fout << "NumNodes : " << (*_db).getNetlist().getNumCells() << "\n";
	
	fout << "NumTerminals : " << (*_db).getNetlist().getNumAllPads() << "\n";


	for ( auto itC = (*_db).getNetlist().cellsBegin();
	       itC !=  (*_db).getNetlist().cellsEnd();
		    itC ++ )
	{
		fout << "\t" << (*itC)->getName() << "\t"
			<< (*itC)->getWidth() << "\t"
			<< (*itC)->getHeight() ;
		if ((*itC)->isFixed())
			fout << " terminal";
		fout << std::endl;
	}
	fout.close();
	
}


void bookShelfParser::writeToNetsFile(bool onlyClkNets)
{
    std::string outFilename = _auxParser.getDesignPath() + _auxParser.getDesignName() + "_placed.nets"; ;
    std::ofstream fout;
    fout.open(outFilename);
	std::cout << "\n\tWriting to nets file   : \t" << outFilename << "\n";
	
    if (!fout)
    {
		myAssert2 (0, "(E) Error opening output file: " , outFilename);
    }
		
	fout << "UCLA nets 1.0 \n";
	fout << "# Created by Soheil Nazar Shahsavani (nazarsha@usc.edu) \n";
	fout << "# Platform\n\n";

    unsigned numNets = (onlyClkNets) ? 
	    (*_db).getNetlist().getNumClkNets() : 
		     (*_db).getNetlist().getNumNets();
    unsigned numPins = (onlyClkNets) ? 
	                    (*_db).getNetlist().getNumClkPins() : 
			             (*_db).getNetlist().getNumPins() ;

	fout << "NumNets : " << numNets << std::endl;
	fout << "NumPins : " << numPins << std::endl;
	fout << std::endl;

	for (auto itN = (*_db).getNetlist().netsBegin(); 
			itN  != (*_db).getNetlist().netsEnd();
			itN++)
	{
		dbNet*  net = (*itN);
		if (onlyClkNets)
          if ( ! (*net).getType().isClock() )	continue;
	  
		fout << "NetDegree : " << (*net).getNumPins() << 
		  " " << (*net).getName() << std::endl;
		for (auto itP = (*net).pinsBegin(); 
				itP != (*net).pinsEnd();
				itP ++) 
		{
			std::cout.precision(5);
			std::string dir = " ";
			if ( (*itP)->isDirInput() ) dir = "I";
			else if ((*itP)->isDirOutput() ) dir = "O"; 
			else dir = "B";

			fout << "\t" << (*itP)->getCell().getName() << "\t" << dir << " : " << 
			std::fixed << (*itP)->getCenter().x << "\t" <<
				std::fixed << (*itP)->getCenter().y << std::endl;
		}
	}

	fout.close();	
	
	
}
void bookShelfParser::writeToPlFile( bool precise )
{

    std::string outFilename = _auxParser.getDesignPath() + _auxParser.getDesignName() + "_placed.pl";
	writeToPlFile(outFilename, precise);
	
}

void bookShelfParser::writeToPlFile
  (std::string outFilename, bool precise)
{

    std::ofstream fout;
    fout.open(outFilename);
	std::cout << "\n\tWriting to pl file   : \t" << outFilename << "\n\n";
	
    if (!fout)
    {
		myAssert2 (0, "(E) Error opening output file: " , outFilename);
    }

    fout << "UCLA pl 1.0\n";
    fout << "# Created by Soheil Nazar Shahsavani (nazarsha@usc.edu)\n";
    fout << "# Platform\n\n";
    fout << "# HPWL : x =  " << std::setw(6) << _db->evalHPWLcostX();
	fout << " y = " << std::setw(6) << _db->evalHPWLcostY() ;
	fout << " Total = " << std::setw(6) << _db->evalHPWLcost() << "\n\n";
	
    for (unsigned i = 0; i < (*_db).getNetlist().getNumCells(); i++ )
    {
        //auto node = (*_db).getNetlist().getCellByIdx(i);
		
        fout << " " << (*_db).getNetlist().getCellByIdx(i).getName() << " ";
		if (precise) fout << std::setprecision(std::numeric_limits<double>::digits10 + 1) ;
		
        fout << (*_db)._spatial.locations[i].x << " "
            << (*_db)._spatial.locations[i].y << " : ";
		//fout << (*_db).getNetlist().getCellByIdx(i).getSymmetry();
		fout << "N";
		if ((*_db).getNetlist().getCellByIdx(i).isFixed())
			fout << " /FIXED";
        fout << std::endl;		
    }
    fout.close();

	
}



void bookShelfParser::readDesignFiles(){
Timer tm; tm.Start();
	
	readNodesFile();
	readNetsFile();
	readSclFile();
	readWtsFile();
	readPlFile();
	readLevelsFile();
	(*_db)._design.postProcess();
	
	(*_db).PrintBenchmarkStatus();
/* 	std::cout << *(*_db)._design._pinLib.front() << "\n:" << *(*_db)._design._pinLib.front()->_cell << std::std::endl;

	auto fCell = (*_db)._design._cellLib.front();
	std::cout << *fCell << 
	"\n:" << (*fCell)._pins << 
	"\n:" << (*fCell)._nets <<  std::endl;
 */
std::cout << "TotalParseTime: " << tm.getFinalTime() << std::endl;
	
	return;
}

std::string bookShelfParser::determineCellType(std::string name){
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	if (name.find("spl") != std::string::npos || name.find("zero") != std::string::npos)
		return "CC";
	else if (name.find("jtl") != std::string::npos) // added for REPLC 
		return "CC";
	else return "SC";		
}


std::vector<std::string> chunkOnDelimeter(std::string s, std::vector<std::string> delims){
	
	std::string delim;
	for (unsigned int i=0; i < delims.size()-1;i++){
		delim += delims[i]+",";		
	} delim += delims.back();
	
	std::vector<std::string> chunks;
	boost::split(chunks, s, boost::is_any_of(delim));
	for (unsigned int i=0; i < chunks.size(); i++)
		if (chunks[i].size() == 0){
			chunks.erase(chunks.begin()+i);
			i--;
		}
	for (unsigned int i=0; i < chunks.size(); i++)
		boost::trim( chunks[i] );		
	return chunks;
}

std::vector<std::string> chunkOnDelimeter(std::string s, std::string delim){
		
	std::vector<std::string> chunks;
	boost::split(chunks, s, boost::is_any_of(delim));
	for (unsigned int i=0; i < chunks.size(); i++)
		if (chunks[i].size() == 0){
			chunks.erase(chunks.begin()+i);
			i--;
		}
	for (unsigned int i=0; i < chunks.size(); i++)
		boost::trim( chunks[i] );		
	return chunks;
}


void bookShelfParser::readLevelsFile(){
	std::string fileName = _auxParser.getDesignPath() + _auxParser.getLevelsFileName();
	std::cout << "Reading LEVELS file: " << fileName << "\n";
	
    std::ifstream fin;
    fin.open(fileName);
    if (!fin)
        myAssert2(0, "(E) Error opening input file: ", fileName);
	

    /*read preambles*/
    std::string   comment;
    getline( fin,comment );
    do
    {
        getline(fin, comment);
    } while((comment.c_str())[0]=='#');

	std::string s;
	bool f = (bool) getline(fin, s);
	std::vector<std::string> chunks;
		
	int index = 0;
	//reading levels
	while (f) {
		
		chunks = chunkOnDelimeter(s, "\t, ,    ");
		if (chunks.size() != 2) 
			myAssert3(0, "Invalid line in levels file: ", s, chunks.size());
		
		std::string name = chunks[0];
		int l = 0;
		try{ l = stoi(chunks[1]); }
		catch (std::exception& e) {
			myAssert3 (0, "Invalid value for level:", name, chunks[1]);
		}
		 
						
		if ((*_db)._design._nameCellMap.find(name) == (*_db)._design._nameCellMap.end()){
			;
			//myWarn2 (0, "Cell name in .levels is not present in .nodes", name);
		} else {
			(*_db)._design._nameCellMap[name]->_level = l;
		}   
		
		index++;
		f = (bool) getline(fin, s);
	}
	
	//for (auto& i: _db._design._cellLib){
	//	if (i->getLevel() == 0 && i->_type.isIO() == false){
	//		myAssert2 (0, "A non-IO cell has a level of 0: ", i->getName());
	//	}
	//}
	
	//cout << _db._design._cellLib << std::endl;
	
	return ;
	
}
void bookShelfParser::readNetsFile(){
	std::string fileName = _auxParser.getDesignPath() +  _auxParser.getNetsFileName();
	std::cout << "Reading NETS file: " << fileName  << "\n";


    std::ifstream fin;
    fin.open(fileName);
    if (!fin)
        myAssert2(0, "(E) Error opening input file: ", fileName);
	


    std::string   comment;
    getline( fin,comment );
    do
    {
        getline(fin, comment);
    } while((comment.c_str())[0]=='#');

	std::string s;
	bool f = (bool) getline(fin, s);
	std::vector<std::string> chunks;

	int numNets = 0;
	int numPins = 0;
	
	//reading numNets line
	if (!f || s.size() == 0) myAssert(0, "ERROR, numNets is not specified.");
	chunks = chunkOnDelimeter(s, ":");
	try { numNets = stoi(chunks.back()); }
	catch (std::exception& e) {
		myAssert3(0, "ERROR: numNets should be integer: ", e.what(), chunks.back()); }
	
	//reading numPins line
	f = (bool) getline(fin, s);
	if (!f || s.size() == 0) myAssert(0, "ERROR, numPins is not specified.");
	chunks = chunkOnDelimeter(s, ":");	
	try { numPins = stoi(chunks.back()); }
	catch (std::exception& e) {
		myAssert3(0, "ERROR: numPins should be integer: ", e.what(), chunks.back()); }

	
	int index = 0;
	f = (bool) getline(fin, s);	
	//reading rest of the file 
	while (f) {
		chunks = chunkOnDelimeter(s, ":");
		if (chunks.size() == 0) {
			//empty line skip;
			f = (bool) getline(fin, s);
			continue;
		}
		if (chunks.size() != 2) 
			myAssert3(0, "Invalid line in nets file: ", s, chunks.size());
		myAssert3 (chunks.front() == "NetDegree", "NetDegree word is not included in .nets file:", chunks.front(),"-");
		s = chunks.back();

		chunks = chunkOnDelimeter(s, "\t, ,    ");
		
		int netDeg = 0;
		try { netDeg = stoi(chunks[0]); }
		catch (std::exception& e) {
			myAssert3 (0, "Invalid net degree value: ", chunks[0], e.what());
		}
		
		std::string netName = chunks[1];		 
		ctainerPins pinVec;
		
		for (int i=0; i < netDeg; i++){
			try { f = (bool) getline(fin, s); }
			catch (std::exception& e) {
				myAssert2 (0, "Not enough lines in .nets file", e.what());
			}
			
			chunks = chunkOnDelimeter(s, ":");
			if (chunks.size() != 2)
				myAssert2 (0, "Invalid pin line def: ", s);
			std::string f = chunks[0];
			std::string l = chunks[1];
			
			chunks = chunkOnDelimeter(f, "\t, ,    ");			
			if (chunks.size() != 2)
				myAssert2 (0, "Invalid pin cell name and IO type: ", f);
			
			std::string cellName = chunks[0];
			std::string IOType = chunks[1] == "I" ? "INPUT":"OUTPUT";

			if ((*_db)._design._nameCellMap.find(cellName) == (*_db)._design._nameCellMap.end()){
				myAssert2 (0, "cell Name in .nets file not found in .nodes", cellName);
			}
			
			//reading pin dimensions
			chunks = chunkOnDelimeter(l, "\t, ,    ");			
			if (chunks.size() != 2)
				myAssert2 (0, "Invalid pin cell name and IO type: ", f);
			
			double x = stod(chunks[0]);
			double y = stod(chunks[1]);
			Point p1(x, y);
			
			int pinIndex = (*_db)._design._nameCellMap[cellName]->_pins.size();
			dbPin* pin1 = new dbPin("pin"+std::to_string(i), IOType, pinIndex, p1);
			pinVec.push_back(pin1);
			
			dbCell* curCell = (*_db)._design._nameCellMap[cellName];
			curCell->_pins.push_back(pin1);
			
			pin1->setCell(*curCell);
			
		}
		
		dbNetType netType1("SIGNAL");

		dbNet* net1 = new dbNet(netName, index, netType1, pinVec);
		(*_db)._design._netLib.push_back(net1);
		
		//setting each pins _net to cur Net
		for (auto &i: pinVec){
			i->setNet(*net1);
		}
		
		index++;
		f = (bool) getline(fin, s);
	}

	//sanity check
	myAssert3(numNets == int((*_db)._design._netLib.size()), "Inconsisten No. of Nets: ", numNets, (*_db)._design._netLib.size());
	int cntPins = 0;
	for (int i=0; i < numNets; i++){
		cntPins += (*_db)._design._netLib[i]->_pins.size();
	}
	myAssert3(numPins == cntPins, "Inconsisten No. of Terminal: ", numPins, cntPins);


	//cout << (*_db)._design._netLib << std::endl;
/* 	for (auto &i: (*_db)._design._netLib){
		cout << *i << std::endl;
		cout << i->_pins << std::endl;
	}
 */	
	return;
}


void bookShelfParser::readNodesFile(){
	std::string fileName = _auxParser.getDesignPath() + _auxParser.getNodesFileName();
	std::cout << "Reading NODES file: " << fileName << "\n";
	
	
    std::ifstream fin;
    fin.open(fileName);
    if (!fin)
        myAssert2(0, "(E) Error opening input file: ", fileName);
	

    /*read preambles*/
    std::string   comment;
    getline( fin,comment );
    do
    {
        getline(fin, comment);
    } while((comment.c_str())[0]=='#');

	std::string s;
	bool f = (bool) getline(fin, s);
	std::vector<std::string> chunks;

	int numNodes = 0;
	int numTerminals = 0;
	
	//reading numNodes line
	if (!f || s.size() == 0) myAssert(0, "ERROR, NumNodes is not specified.");
	
	chunks = chunkOnDelimeter(s, ":");		
	try { numNodes = stoi(chunks.back()); }
	catch (std::exception& e) {
		myAssert3(0, "ERROR: NumNodes should be integer: ", e.what(), chunks.back()); }
	
	//reading numTerminals line
	f = (bool) getline(fin, s);
	if (!f || s.size() == 0) myAssert(0, "ERROR, NumTerminals is not specified.");
	chunks = chunkOnDelimeter(s, ":");		
	try { numTerminals = stoi(chunks.back()); }
	catch (std::exception& e) {
		myAssert3(0, "ERROR: NumTerminals should be integer: ", e.what(), chunks.back()); }

	
	int index = 0;
	f = (bool) getline(fin, s);	
	//reading rest of the file 
	while (f) {
		chunks = chunkOnDelimeter(s, "\t, ,    ");		
		if (chunks.size() < 3 || chunks.size() > 4) 
			myAssert3(0, "Invalid line in nodes file: ", s, chunks.size());
		
		std::string name = chunks[0];
		int w = stoi(chunks[1]);
		int h = stoi(chunks[2]);
		
		std::string type;
		std::string subType;
		if (chunks.size() == 4){
			std::string last = chunks.back();
			std::transform(last.begin(), last.end(), last.begin(), ::tolower);
			type = "IO";
			if (last == "terminal")  subType = "PIO";
			else {
				myWarn2(0, "WARN: Invalid string in nodes file: ", last);
				subType = "";
			}
		} else { //it is core type
			type = "CORE";
			subType = determineCellType(name);			
		}
		
		
		dbCell* cur = new dbCell(name, type, subType, index, w, h);
		(*_db)._design._nameCellMap[name] = cur;
		
		(*_db)._design._cellLib.push_back(cur);
		
		index++;
		f = (bool) getline(fin, s);
	}
	
	myAssert3(numNodes == int((*_db)._design._cellLib.size()), "Inconsisten No. of Cells: ", numNodes, (*_db)._design._cellLib.size());
	int cntTerminals = 0;
	for (int i=0; i < numNodes; i++){
		if ((*_db)._design._cellLib[i]->_type.isIO())
			cntTerminals++;
	}
	myAssert3(numTerminals == cntTerminals, "Inconsisten No. of Terminal: ", numTerminals, cntTerminals);
	
	//sorting cells in the design by type to make sure Terminals
	//are at the end of netlist
	sort ((*_db)._design._cellLib.begin () , 
			(*_db)._design._cellLib.end () ,
			CompareCellsByType());
	
	//cout << "MyCells: " << (*_db)._design._cellLib << std::endl;	
	
	return;
	
}


void bookShelfParser::readSclFile(){
	std::string fileName = _auxParser.getDesignPath() +  _auxParser.getSclFileName();
	std::cout << "Reading SCL file: " << fileName << "\n";
	
	sclParser  rowParser;
    (*_db)._rowDefs = rowParser.sclToStdCellRowDef(fileName);
	(*_db)._rowDefs->calculateChipDimensions();
	
	//std::cout << "RowDefs:\n" << *(*_db)._design._rowDefs  << std::endl;
	
	return;
}


void bookShelfParser::writeSclFile(std::string fileName, dbRowDef dbRows)
{
	std::cout << "\tWriting to scl file: " << fileName << "\n";
	
	sclParser  rowParser;
	rowParser.writeSclFile(fileName, dbRows);
	
	//std::cout << "RowDefs:\n" << *(*_db)._design._rowDefs  << std::endl;
	
	return;
}

//just writes out the db version of _rowDefs
void bookShelfParser::writeSclFile()
{
	std::string fileName = _auxParser.getDesignPath() + _auxParser.getDesignName() + "_placed.scl";
	
	this->writeSclFile(fileName, (*(*_db)._rowDefs));
	
	return;
}

void bookShelfParser::readPlFile(std::string fileName)
{
	
	std::cout << "Reading PL file: " << fileName << "\n";
	

    std::ifstream fin;
    fin.open(fileName);
    if (!fin)
        myAssert2(0, "(E) Error opening input file: ", fileName);
	

    /*read preambles*/
    std::string   comment;
    getline( fin,comment );
    do
    {
        getline(fin, comment);
    } while((comment.c_str())[0]=='#');

	std::string s;
	bool f = (bool) getline(fin, s);
	std::vector<std::string> chunks;
	
	int index = 0;
	//reading rest of the file 
	while (f) {
		chunks = chunkOnDelimeter(s, ":");		
		//myWarn2(int(chunks.size()) == 2, "No orientation in .pl file: ", s);
		if (int(chunks.size()) != 2) {
			myWarn2 (0, "Can't read this line: ", s);
			f = (bool) getline(fin, s);
			continue;
		}
		
		std::string ori = chunks.back();
		std::string p = chunks.front();
		chunks = chunkOnDelimeter(p, "\t, ,    ");		
		
		if (chunks.size() != 3) {
			myWarn3(0, "Invalid line in pl file: ", p, chunks.size());
			f = (bool) getline(fin, s);
			continue;			
		} 
		
		std::string name = chunks[0];
		int x = stoi(chunks[1]);
		int y = stoi(chunks[2]);
				
		
		if ((*_db)._design._nameCellMap.find(name) == (*_db)._design._nameCellMap.end()){
			myAssert2 (0, "Cell name in .pl is not found in .nodes: ", name);
		} else{
			(*_db)._design._nameCellMap[name]->_origin = Point(x, y);
		} 
		
		
		index++;
		f = (bool) getline(fin, s);
	}
	myAssert3 (index == int((*_db)._design._nameCellMap.size()), "Position of some cells in the .nodes are not specified in .pl: ", index, (*_db)._design._nameCellMap.size());
		
	
	std::vector<Point> plVec;
	for ( auto itC = (*_db).getNetlist().cellsBegin();
			itC !=  (*_db).getNetlist().cellsEnd();
			itC ++ )
			plVec.push_back ( (*itC)->getOrigin() );

	myAssert3 ( plVec.size() == ((*_db)._design._nameCellMap.size()), plVec.size(), "Total placement points is not equal to total number of nodes.", (*_db)._design._nameCellMap.size() );
			
	Placement pl (plVec);
	(*_db)._spatial.locations = pl;
	
	//std::cout << (*_db)._design._cellLib << std::endl;
	
	return;
	
	
}


void bookShelfParser::readPlFile(){
	std::string fileName = _auxParser.getDesignPath() + _auxParser.getPlFileName();
	
	readPlFile (fileName);
	return;
}

//TODO implement this
void bookShelfParser::readWtsFile(){
	std::string fileName = _auxParser.getDesignPath() + _auxParser.getWtsFileName();
	std::cout << "Reading WTS file: " << fileName << "\n";
}
