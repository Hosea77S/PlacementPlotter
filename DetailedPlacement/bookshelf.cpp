//Originally obtained from http://web.cs.ucla.edu/classes/cs258f/2003_spring/parser/src/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <math.h>
#include "bookshelf.h"
#include "readScl.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cassert>

// #define VERBOSE

using namespace std;


bool compare_cell_x(Cell* a, Cell* b) {
	return (a->x < b->x);
}
bool compare_cell_y(Cell* a, Cell* b) {
	return (a->y < b->y);
}


void bookshelfParser::insertPin2Net( Net *net, Cell *cell, char *io_type,
double px, double py)
{
    px *= unitScale;
    py *= unitScale;

    Pin * pin = new Pin;
    if (io_type[0] == 'O')
        pin->dir = PIN_OUT;
    else if (io_type[0] == 'I')
        pin->dir = PIN_IN;
    else if (io_type[0] == 'B')
        pin->dir = PIN_BI;
    else
    {
        cerr << "(E) : Invalid pin direction! " << endl;
        exit(0);
    }
    pin->x       = px;
    pin->y       = py;
    pin->netPtr  = net;
    pin->cellPtr = cell;
    cell->pinList.push_back(pin);
    net->pinList.push_back(pin);
    #ifdef VERBOSE
    cout << "Adding pin to " << cell->name << " on " << net->name << " "
        << px << " " << py << endl;
    #endif
}


bool operator< (const Cell &left, const Cell &right)
{
	return left.id < right.id;
}

void bookshelfParser::readFromNetsFile(const char *filename)
{
    Net  *net;
    ifstream fin;
    fin.open(filename);

    if (!fin)
    {
        cerr << "(E) Error opening input file: "
            << filename
            << endl;
        exit(-1);
    }

    cout << "Reading from file: " << filename << endl;

    int net_pad = 0;

    /*read title data*/
    string comment;
    getline(fin,comment);
    do
    {
        getline(fin,comment);
    }while((comment.c_str())[0]=='#');

    int tot_nets = 0;
    int tot_pins = 0;

    int  nid = 0;
    istringstream in1(comment);
    getline(in1, comment,':');
    if (!in1)
    {
        getline(fin, comment,':');
        fin >> tot_nets;
    }
    else
        in1>>tot_nets;

    getline(fin, comment,':');
    fin >> tot_pins;
	model->numOfPins = tot_pins;

	
    int i = -1;
    string blah, TMP;
    while(getline(fin,blah,':'))
    {
        vector<string > cellname_list;
        int nPin = 0;
        fin >> nPin;
        getline(fin,TMP,'\n');
        i++;
        getName("net",i);
        net = new Net(fullname);
		net->id = nid++;
        model->netList.push_back(net);


        for (int j = 0; j < nPin; j++)
        {
            double px = 0, py = 0;
            char   io_type[10];
            char   cellname[1000];

            fin    >> cellname >> io_type;

            string line;
            string comm;
            getline(fin, line);
            istringstream in(line);
            in >> comm;
            if (in)
                in >> px >> py;

            Cell * node = name2cell[cellname];
            insertPin2Net(net, node, io_type, px, py);
            if (node->pad == true )
                net_pad++;
        }
    }
    fin.close();
    //cout<<"total "<<net_pad<<" pads connect with nets"<<endl;
}


void bookshelfParser::readFromNodesFile(const char *filename)
{
    ifstream fin;
    fin.open(filename);
    if (!fin)
    {
        cerr << "(E) Error opening input file: "
            << filename
            << endl;
        exit(-1);
    }
    cout    << "Reading from file: "
        << filename
        <<endl;

    model = new Model;

    /*read preambles*/
    string   comment;
    getline( fin,comment );
    do
    {
        getline(fin, comment);
    }while((comment.c_str())[0]=='#');

    int tot_nodes = 0;
    int tot_pads  = 0;
    istringstream in1(comment);
    getline(in1, comment, ':');
    if(!in1)
    {
        getline(fin, comment,':');
        fin >> tot_nodes;
    }
    else
        in1 >> tot_nodes;
    getline(fin,comment, ':');
    fin >> tot_pads;
    int tot_cells = tot_nodes - tot_pads;
    string blah;
    int     nid = 0;
    while (getline(fin, blah))
    {
        istringstream in(blah);
        double  width, height;
        char    cellname[1000];
        string  tem;
        in >> cellname >> width >> height;
		if (!in)
		   continue;
        in >> tem;
        Cell * node     = new Cell;
        if (tem == "terminal" )           //a terminal
        {
            node->pad = true;
            node->wth = width * unitScale;
            node->hgt = height * unitScale;
        }
        else
        {
            node->pad = false;
            node->wth = width * unitScale;
            node->hgt = height * unitScale;
        }
		node->level = 0;
        node->id      = nid++;
        node->name    = string(cellname);
		node->isClSink = false;
        name2cell[node->name] = node;
        model->cellList.push_back( node );
        #ifdef VERBOSE
        cout << "Adding";
        if ( node->pad )
            cout << " pad ";
        else
            cout << " cell ";
        cout << node->name << " size " << node->hgt
            << " " << node->wth << endl;
        #endif
    }
    fin.close();
}


void bookshelfParser::readFromPlFile(const char *filename)
{
    char comment[256];
    ifstream fin;
    fin.open(filename);
    if(!fin)
    {
        cerr << "(E) Error opening input file: "
            << filename
            << endl;
        exit(-1);
    }

    cout << "Reading from file: " << filename << endl;

    fin.getline(comment, 256);
    while (fin.getline(comment, 256))
    {
        if (comment[0] == '#')
            continue;
        if (strlen(comment) == 0)
            continue;
        char cellName[80];
        char comm[10];
        string ort;
        double px = 0, py = 0;
        istringstream spec_in(comment);

        spec_in >> cellName >> px >> py >> comm >> ort;

        px *= unitScale;
        py *= unitScale;
        ORI o = B0;
        if (ort == "N")
            o = B0;
        else if (ort == "E")
            o = B90;
        else if ( ort == "S")
            o = B180;
        else if (ort == "W")
            o = B270;
        else if (ort == "FN")
            o = F180;
        else if (ort == "FE")
            o = F90;
        else if (ort== "FS")
            o = F0;
        else if (ort == "FW")
            o = F270;
        Cell * node = name2cell[string(cellName)];
        if (node == NULL)
        {
            cerr << "(E): inst/pad name "  << cellName
                << "  not in the library" << endl;
            continue;
        }
        node->x = px;
        node->y = py;
        #ifdef VERBOSE
        cout << "Placing cell/pad " << node->name << " at "
            << node->x  << " " << node->y << endl;
        #endif
    }
}

void bookshelfParser::readFromLevelsFile(const char *filename)
{
	char comment[256];
	ifstream fin;
	fin.open(filename);
	if (!fin)
	{
		cerr << "(E) Error opening input file: "
			<< filename 
			<< endl;
			exit(-1);
		return;
	}

	cout << "Reading from file: " << filename << endl;

	fin.getline(comment, 256);
	while (fin.getline(comment, 256))
	{
		if (comment[0] == '#')
			continue;
		if (strlen(comment) == 0)
			continue;
		char cellName[80];
		double currentLevel;
		istringstream spec_in(comment);

		spec_in >> cellName >> currentLevel;
		Cell * node = name2cell[string(cellName)];
		if (node == NULL)
		{
			cerr << "(E): inst/pad name " << cellName
				<< "  not in the library" << endl;
			continue;
		}
		if (currentLevel < 0) cerr << "(E) : currentLevel is a negative number : " << currentLevel << endl;
		node->level = currentLevel;

#ifdef VERBOSE
		cout << "Placing cell/pad " << node->name << " with level "
			<< currentLevel << endl;
#endif
	}
}

Model *  bookshelfParser::read(char**&argv, int&argc){
	if (argc == 5) {
		Model* chip = read(argv[1], argv[2]);
		//arg[3] is used for size of HL-tree groups
		chip->maxGPIter = atoi(argv[4]);
		return chip;
	}
	else {
		cerr << "Number of Global Placement iterations is not mentioned" << endl;
		return read(argv[1], argv[2]);	
	}
}

Model  * bookshelfParser::read(const char *pathName, const char *fileName)
{
    unitScale = 1;
	char * auxFileName = (char *) malloc(1 + strlen(pathName)+ strlen(fileName) );
    strcpy(auxFileName, pathName);
    strcat(auxFileName, fileName);
		
    extractDesignName(auxFileName);
	extractDesignPath(pathName);
	extractAUXFileName(fileName);

	cout << "Design Path : " << this->getDesignPath() << endl;
	cout << "Design Name : " << this->getAUXFileName() << endl;
	
    getFileName(auxFileName);

	char * nodesName = (char *) malloc(1 + strlen(pathName)+ strlen(nodesFileName) );
	strcpy(nodesName, pathName); strcat(nodesName, nodesFileName);
    readFromNodesFile(nodesName);
	
	char * netsName = (char *) malloc(1 + strlen(pathName)+ strlen(netsFileName) );
	strcpy(netsName, pathName); strcat(netsName, netsFileName);	
    readFromNetsFile(netsName);
	
	char * plName = (char *) malloc(1 + strlen(pathName)+ strlen(plFileName) );
	strcpy(plName, pathName); strcat(plName, plFileName);	
    readFromPlFile(plName);

	char * levelName = (char *) malloc(1 + strlen(pathName)+ strlen(levelsFileName) );
	strcpy(levelName, pathName); strcat(levelName, levelsFileName);		
	readFromLevelsFile(levelName);
	
	sclParser  rowParser;
    model->rowDef = rowParser.sclToStdCellRowDef(fileName, pathName);

	model->x_offset = model->rowDef->stdRows[0].lowerLeftX;
	model->y_offset = model->rowDef->stdRows[0].lowerLeftY;
	model->chip_width = model->rowDef->stdRows[0].width ;
	model->chip_height = model->rowDef->stdRows[0].height * (model->rowDef->stdRows.size()) ;

	int num_of_cells = model->cellList.size();

	model->maxIPiter = 7;
	model->IP_update_ratio = 1.0;
	model->gridSize = 200;
	model->gp_update_ratio = 1.0;
	model->maxCutLevel = 4;
	model->overfill_ratio = 1.0;
	model->maxBFSStage = 20;
	model->maxGPIter = 55;
/* 	model->x_offset = 500;
	model->y_offset = 600; */

    return(model);
}

int Model::numOfNonTerminalNodes(){
	int num_of_cells = this->cellList.size();
	int numOfNonTerminalNodes = 0;
	
	for (int i = 0; i < num_of_cells; i++)
		if (!this->cellList[i]->pad)
			numOfNonTerminalNodes++;
	return numOfNonTerminalNodes;
}


void     bookshelfParser::extractDesignPath(const char *designPathName){
    int len  = strlen(designPathName);
	int j;
    for (j = 0; j < len; j++)
        this->designPath[j] = designPathName[j];
    this->designPath[j] = '\0';
	
}


void     bookshelfParser::extractAUXFileName(const char *auxName){
    int len  = strlen(auxName);
	int j;
    for (j = 0; j < len; j++)
        this->auxFileName[j] = auxName[j];
    this->auxFileName[j] = '\0';
	
}


void   bookshelfParser::extractDesignName(const char *auxName)
{
    int len  = strlen(auxName);
    int head = 0;
    for (int i = len-1; i >= 0; i--)
    {
        if(auxName[i] == '.')
        {
            head = i;
            break;
        }
    }
    int j;
    for (j = 0; j < head; j++)
        designName[j] = auxName[j];
    designName[j] = '\0';
}


void   bookshelfParser::assignFileName(const char *fpName)
{
    char fileNameSuffix[1000];
    int len = strlen(fpName);
    int head = 0;
    for (int i = len-1; i >= 0; i--)
    {
        if(fpName[i] == '.')
        {
            head = i;
            break;
        }
    }

    int j = 0;
    for(int i=head+1; i<len; i++)
        fileNameSuffix[j++] = fpName[i];

    fileNameSuffix[j++]= '\0';

    if(strncmp(fileNameSuffix, "nodes", 5)==0)
        strcpy(nodesFileName,fpName);
    else if(strncmp(fileNameSuffix, "nets", 4)==0)
        strcpy(netsFileName,fpName);
	else if (strncmp(fileNameSuffix, "pl", 2) == 0)
		strcpy(plFileName, fpName);
	else if (strncmp(fileNameSuffix, "levels", 6) == 0)
		strcpy(levelsFileName, fpName);
}


void   bookshelfParser::getFileName(const char *auxFileName)
{
    char fpname[1000];
    netsFileName[0] = '\0';
    nodesFileName[0] = '\0';
    plFileName[0] = '\0';
	levelsFileName[0] = '\0';
    ifstream fin;
    fin.open(auxFileName);
    if (!fin)
    {
        cerr << "(E) Error opening input file: "<< auxFileName << endl;
        exit(-1);
    }
    while (fin >> fpname)
    {
        assignFileName(fpname);
    }
    fin.close();
    if( strlen(netsFileName) == 0 ||
        strlen(nodesFileName) == 0 ||
        strlen(plFileName) == 0 )
    {
        cerr << "(E) : aux file: " << auxFileName
            << " can not find *.nodes, *.nets and *.pl filename"
            << endl;
        exit(-1);
    }

	if (strlen(levelsFileName) == 0) {
		cerr << "(E) No .levels file found. Exiting " << endl ;
		exit(-1);
	}
}


void   bookshelfParser::getName(const char *name, int num)
{
    char buf[40];
    strcpy(fullname,name);
    sprintf(buf, "%d", num);
    strcat(fullname,buf);
}


void bookshelfParser::write( Model * chip, string filename)
{
	cout << "\n\nWriting the final placement to : " << filename << endl;
    model = chip;
	std::vector<char> writable(filename.begin(), filename.end());
	writable.push_back('\0');
	char    *outFile = &*writable.begin();
    write2PlFile(outFile);
//	write2NetsFile(outFile);
//	write2NodesFile(outFile);
/* 	write2SclFile(outFile);
	write2WtsFile(outFile);
 */
}

void bookshelfParser::write2SclFile(const char *filename){
	
	cout << "\tWriting to scl file: \t" << filename << ".scl" << endl;
	string desName = getDesignName();
	string command =  "cp " + desName + ".scl" + " " + filename + ".scl";
	cout << command << endl;
	return;
}


void bookshelfParser::write2WtsFile(const char *filename){
	cout << "\tWriting to wts file: \t" << filename << ".wts" << endl;
	string desName = getDesignName();
	string command =  "cp " + desName + ".wts" + " " + filename + ".wts";
	cout << command << endl;
	return;
	
}



void bookshelfParser::write2NodesFile(const char *filename)
{
	char   outFilename[1000];
	strcpy(outFilename, filename);
	//strcat(outFilename, "_JTLsAdded");
	strcat(outFilename, ".nodes");
	cout << "\tWriting to nodes file: \t" << outFilename << endl;
	ofstream fout;
	fout.open(outFilename);

	if (!fout)
	{
		cerr << "(E) Error opening output file: " << outFilename
			<< endl;
		exit(-1);
	}

	fout << "UCLA nodes 1.0\n";
	fout << "# Created\n";
	fout << "# Platform\n\n";
	fout << "NumNodes : " << model->cellList.size() << "\n";
	int numOfTerminals = 0;
	for (unsigned int i = 0; i < model->cellList.size(); i++)
		if (model->cellList[i]->pad)
			numOfTerminals++;

	fout << "NumTerminals : " << numOfTerminals << "\n";


	for (int i = 0; i < int(model->cellList.size()); i++)
	{
		Cell * node = model->cellList[i];
		fout << "\t" << node->name << "\t"
			<< node->wth << "\t"
			<< node->hgt ;
		if (node->pad)
			fout << " terminal";
		fout << endl;
	}
	fout.close();
}

void bookshelfParser::write2PlFile( const char *filename)
{
    char   outFilename[1000];
    strcpy(outFilename, filename);
    strcat(outFilename, ".pl");
    ofstream fout;
    fout.open(outFilename);
	cout << "\n\tWriting to pl file   : \t" << outFilename << endl;
	
    if (!fout)
    {
        cerr << "(E) Error opening output file: " << outFilename
            << endl;
        exit(-1);
    }

    fout << "UCLA pl 1.0\n";
    fout << "# Created\n";
    fout << "# Platform\n\n";
    fout << "# HPWL = " << model->HPWL() << "\n\n";

    for (int i = 0; i < int(model->cellList.size()); i++ )
    {
        Cell * node = model->cellList[i];
        fout << " " << node->name << " "
            << node->x << " "
            << node->y << " : ";
        if ( node->ori == B0 )
            fout << "N";
        else if ( node->ori == B90 )
            fout << "E";
        else if ( node->ori == B180)
            fout << "S";
        else if ( node->ori == B270 )
            fout << "W";
        else if (node->ori == F180)
            fout << "FN";
        else if (node->ori == F90)
            fout << "FE";
        else if (node->ori == F0)
            fout << "FS";
        else if (node->ori == F270)
            fout << "FW";
        else
        {
            cerr << "(E) : Invalid orientation !" << endl;
            exit(0);
        }
		if (node->pad)
			fout << " /FIXED";
        fout << endl;
    }
    fout.close();
}
void bookshelfParser::write2NetsFile(const char *filename)
{
	char   outFilename[1000];
	strcpy(outFilename, filename);
	//strcat(outFilename, "_clocksAdded");
	strcat(outFilename, ".nets");
	cout << "\tWriting to nets file : \t" << outFilename << endl;
	
	ofstream fout;
	fout.open(outFilename);

	if (!fout)
	{
		cerr << "(E) Error opening output file: " << outFilename
			<< endl;
		exit(-1);
	}

	
	fout << "UCLA nets 1.0 \n";
	fout << "# Created by Soheil Nazar Shahsavani \n";
	fout << "# Platform\n\n";


	fout << "NumNets : " << model->netList.size() << endl;
	fout << "NumPins : " << model->get_TotNumOfPins() << endl;
	fout << endl;

	for (int i = 0; i < int(model->netList.size()); i++)
	{
		Net*  net = model->netList[i];
		fout << "NetDegree : " << net->pinList.size() << " "
			<< net->name << endl;
		for (unsigned int j = 0; j < net->pinList.size(); j++) {
			std::cout.precision(5);
			string dir = " ";
			if (net->pinList[j]->dir == 1) dir = "I";
			else if (net->pinList[j]->dir == 2) dir = "O"; 
			else if (net->pinList[j]->dir == 3) dir = "B";
			else cerr << "Invalid direction for pin " << net->pinList[j]->cellPtr->name << endl;
			fout << "\t" << net->pinList[j]->cellPtr->name << "\t" <<
				dir << " : " << std::fixed << double(net->pinList[j]->x) << "\t" <<
				std::fixed << double(net->pinList[j]->y) << endl;
		}
	}

	fout.close();
}

Cell* Model::findGCLKCell() {
	for (unsigned int i = 0; i < this->cellList.size(); i++) {
		if (this->cellList[i]->name == "GCLK_Pad")
			return (this->cellList[i]);
	}
	return NULL;
}

double Model::minCellWidth() {
	double minWidth = 0.0; 
	for (unsigned int i = 0; i < cellList.size(); i++) {
		if (cellList[i]->pad) continue;
		if (minWidth == 0) minWidth = cellList[i]->wth;
		if (cellList[i]->wth < minWidth) minWidth = cellList[i]->wth;
	}

	return minWidth;
}


double Model::CalculateTotalCellArea(){
	double Area = 0.0;
	for (unsigned int i = 0; i < cellList.size(); i++) {
		Area += (cellList[i]->wth * cellList[i]->hgt);
	}
	return Area;
}

int Model::get_maxCellLevel(){
	int maxLevel = 0;
	for (unsigned int i = 0; i < cellList.size(); i++) {
		if (cellList[i]->level > maxLevel) 
			maxLevel = cellList[i]->level ;
	}
	return maxLevel;
}

int Model::get_TotNumOfPins(){
	int totPins = 0;
	
	for (int i=0; i < int(this->netList.size()); i++){
		totPins += int(this->netList[i]->pinList.size());
	}
	
	int totCellPins = 0;
	for (int i=0; i < int(this->cellList.size()); i++){
		totCellPins += int(this->cellList[i]->pinList.size());
	}
	//cout << "\ntotNetPins : " << totPins << " totCellPins : " << totCellPins << endl << endl;
	
	return totPins;
}


void Model::printNetList(){
	for (int i=0; i < int(this->netList.size()); i++){
		cout << "net " << i << " name " << this->netList[i]->name << " pinLits : " << endl;
		for (int j=0; j < int(this->netList[i]->pinList.size()); j++){
			cout << "\tpin " << j << " cellPtr: " << this->netList[i]->pinList[j]->cellPtr->name << endl;
		}
	}
	return ;
}

void Model::printCellList(){
	for (int i=0; i < int(this->cellList.size()); i++){
		cout << "Cell " << this->cellList[i]->name << " id : " << this->cellList[i]->id << 
				" pos (" << this->cellList[i]->x << "," << this->cellList[i]->y << ") w&h (" << 
				 this->cellList[i]->wth << "," << this->cellList[i]->hgt << ") has " << this->cellList[i]->pinList.size()
				 << " pins: " << endl;
		for (int j=0; j < int(this->cellList[i]->pinList.size()); j++){
			cout << "\tpin " << j << " dir " << this->cellList[i]->pinList[j]->dir << 
				" cellPtr " << this->cellList[i]->pinList[j]->cellPtr->name << 
			" id " << this->cellList[i]->pinList[j]->cellPtr->id << " net " << this->cellList[i]->pinList[j]->netPtr->name << endl; 
		}
	}
	
	return;
}

void bookshelfParser::updateName2CellMap(){
	name2cell.clear();
	for (int i=0; i < int(this->model->cellList.size()); i++)
		name2cell[this->model->cellList[i]->name] = this->model->cellList[i];
	return;
}

double Model::HPWL_x(){
	double sum = 0.0;
	for (int i = 0; i < int(this->netList.size()); i++) {
		int minX = int(chip_width + x_offset);
		int maxX = 0;
		for (int j = 0; j < int(this->netList[i]->pinList.size()); j++) {
			int centerX = netList[i]->pinList[j]->cellPtr->x + int(int(netList[i]->pinList[j]->cellPtr->wth) / 2); 
			if (centerX < minX) minX = centerX;
			if (centerX > maxX) maxX = centerX;
		}

		sum += int(abs(maxX - minX) );
	}
	return sum;
	
}
double Model::HPWL_y(){
	double sum = 0.0;
	for (int i = 0; i < int(this->netList.size()); i++) {
		int minY = int(chip_height + y_offset);
		int maxY = 0;
		for (int j = 0; j < int(this->netList[i]->pinList.size()); j++) {
			int centerY = netList[i]->pinList[j]->cellPtr->y + int(int(netList[i]->pinList[j]->cellPtr->hgt)/ 2);
			if (centerY < minY) minY = centerY;
			if (centerY > maxY) maxY = centerY;
		}

		sum += int(abs(maxY - minY));
	}
	return sum;
	
}
double Model::HPWL() {
	return (this->HPWL_x() + this->HPWL_y());
}


void bookshelfParser::PrintBenchmarkStatus(){
	
	cout << "\n\n" << endl;
	cout << "Total Nodes    : " << model->cellList.size() << endl;
	cout << "Movable Nodes  : " << model->numOfNonTerminalNodes() << "\t\t\t(" << 
		model->CalculateTotalCellArea() << ")" << endl;
	cout << "I/O Terminals  : " << model->cellList.size() - model->numOfNonTerminalNodes() << endl;
	cout << "Nets           : " << model->netList.size() << "\t\t\tPins           : " << model->numOfPins << endl;
	cout << "Rows           : " << model->rowDef->stdRows.size() << 
			"\t\t\t\tRow Height     : " << model->rowDef->stdRows[0].height << endl;
	cout << "Layout Area    : " << model->chip_width * model->chip_height << 
	"\t\t\t(X span:" << model->x_offset << "-" << model->x_offset + model->chip_width <<
	", Y span:" << model->y_offset << "-" << model->y_offset + model->chip_height <<
	"), Ratio: " << model->chip_height / model->chip_width << endl;
	cout << "Design Density : " << model->CalculateTotalCellArea() / (model->chip_width * model->chip_height) << endl;
	
	cout << "maxIPiter      : " << 	model->get_maxIPiter() << "\t\t\t\tmaxGPIter      : " << model->get_maxGPiter() << endl;
	cout << "IP update ratio: " << 	model->get_IP_update_ratio() << "\t\t\t\tGP update ratio: " <<  model->get_gp_update_ratio() << endl;
	cout << "Init grid Size : " <<  model->get_gridSize() << endl;
	cout << "Width          : " << model->chip_width << "\t\t\tHeight          : " << model->chip_height << endl;
	cout << "X offset       : " << model->x_offset   << "\t\t\tY offset        : " << model->y_offset <<  endl;
	cout << "Max Cell Level : " << model->get_maxCellLevel() << endl << endl; 	
	
/* 	cout << "maxCutLevel is : " << 		model->maxCutLevel << endl;
	cout << "overfill_ratio is : " << 	model->overfill_ratio << endl;
	cout << "maxBFSStage is : " << 		model->maxBFSStage << endl;
 */	
	
	
	cout << "\n\n" << endl;

	
}

