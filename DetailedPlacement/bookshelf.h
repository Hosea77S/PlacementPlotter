//Originally obtained from http://web.cs.ucla.edu/classes/cs258f/2003_spring/parser/src/
#ifndef BF_PARSER__H
#define BF_PARSER__H

#include <cstdio>
#include <fstream>
#include <list>
#include <set>
#include <utility>
#include <map>
#include <vector>
#include <string>
#include "stdCellRow.h"
#include <cmath>

using namespace std;



class Pin;
class Cell;
class Net;
class Model;

// direction of pin, may not be used 
// PIN_IN :    input pin
// PIN_OUT:    output pin
// PIN_BI :    bi-directional pin

enum DIR
{
    PIN_IN = 1, PIN_OUT = 2, PIN_BI = 3
};

// orientation w.r.t the center of the instance:
// BO:            - normal
// B90:           - clockwise rotate 90' from normal
// B180 :         - clockwise rotate 180' from normal
// B270:          - clockwise rotate 270' from normal
// F0:            - flip back along x-direction
// F90            - clockwise rotate 90' from flip-back
// F180           - clockwise rotate 180' from flip-back
// F270:          - clockwise rotate 270'

enum ORI
{
    B0 = 0, B90 = 1, B180 = 2, B270 = 3,
    F0 = 4, F90 = 5, F180 = 6, F270 = 7
};



struct Place {
	double x ;
	double y ;
};




// px, py:  - coordiate w.r.t LL corner of owner cell
// cellPtr: - pointer to the owner cell
// netPtr:  - pointer to the owener net

class Pin
{
    public:
        double  x, y;
        Cell    *cellPtr;
        Net     *netPtr;
        DIR     dir;
    public:
        void    setNetPtr( Net * net )
        {
            netPtr = net;
        }
        void setCellPtr( Cell *cell )
        {
            cellPtr = cell;
        }
};

// id  : cell index
// wth : width of this cell
// hgt : height of this cell
// x   : x coordinate of the cell's left-bottom corner
// y   : y  coordinate of the cell's left-bottom corner
// pad : flag indicating whether this cell a pad
// net : array of nets incident to this cell

class Cell
{
    public:

        int           id;
		int			level;
        string        name;
        double        wth, hgt;
        double        x, y;
        bool          pad;
		bool 		  isClSink;
        std::vector<Pin *> pinList;
        ORI           ori;
		friend bool operator< (const Cell &left, const Cell &right);
    public:

        Cell()
        {
            ori = B0;
            x   = 0;
            y   = 0;
            pad = false;
            wth = 0;
            hgt = 0;
			level = 0;
			isClSink = false;
			id = -1;
			name = "dummy";
        }
		
		Cell(const Cell &cell) {
			/* TestBench
			Cell* newCell = new Cell(*chip->cellList[56]);
			cout << "New Cell: name " << newCell->name << " id: " << newCell->id << " Coordinates: ( " << newCell->x << " , " << newCell->y << " ) PinList Size: "
			<< newCell->pinList.size() << endl;
			delete newCell;
			cout << "New Cell: name " << chip->cellList[5]->name << " id: " << chip->cellList[5]->id << " Coordinates: ( " << chip->cellList[5]->x << " , " << chip->cellList[5]->y << " ) PinList Size: "
				<< chip->cellList[5]->pinList.size() << endl;
			*/
			id = cell.id;
			level = cell.level;
			name = cell.name;
			wth = cell.wth; hgt = cell.hgt;
			x = cell.x; y  = cell.y;
			pad = cell.pad;
			isClSink = cell.isClSink;
			ori = cell.ori;
			for (unsigned int i = 0; i < cell.pinList.size(); i++) {
				pinList.push_back(cell.pinList[i]);
			}
		}

        ~Cell()
        {
            for (unsigned int i = 0; i < pinList.size(); i++ )
                delete pinList[i];
        }

        void setCoor(double cx, double cy)
        {
            x = cx;
            y = cy;
        }
};

// id   : net index
// tot  : total # of cell in this net
// cell : array of cells in this net

class Net
{
    public:
        int  id, tot;
        string   name;
        std::vector<Pin *> pinList;
        Net(char * netName)
	{
	    name = string(netName);
        }
		Net(string netName) {
			name = netName;
		}
		
};


class clkCell {
	public : 
	clkCell(int key, int left, int right, int parent, Cell* Cell) : id(key), left(left), right(right), parent(parent), height(0), myCell(Cell) {}
	clkCell(int key) : id(key), left(-1), right(-1), parent(-1), height(0), myCell(NULL) {}	
	clkCell() : id(-1), left(-1), right(-1), parent(-1), height(0), myCell(NULL){}
		int id;
		int left ;
		int right;
		int parent;
		int height;
		Cell* myCell;
		
	bool isSinkNode(){
		if (!this->myCell) return false;
		return (this->left == -1 && this->right == -1);
	}
	
	bool isHalfSinkNode(){		
		if (!this->myCell) return false;
		return (this->left == -1 && this->right != -1) || 
			   (this->left != -1 && this->right == -1);
	}
	

	
friend std::ostream& operator<<(std::ostream& os, const clkCell& c){
	os << "index: " << c.id << " par: " << c.parent << " left: " << c.left
		<< " right: " << c.right << " height: " << c.height;
	return os;
}		

};

class CompareClkCellsByHeight
{
public:
   CompareClkCellsByHeight(){}
   bool operator() ( clkCell* p1, clkCell* p2) const {
	   if (p1->height == p2->height){
	       if (p1->isSinkNode() && p2->isSinkNode())
		       return p1->id < p2->id;
		   else return p1->left + p1->right > p2->left + p2->right ;
	   }
		
	 return p1->height < p2->height;   
   }
	
};

class CompareClkCellsByID
{
public:
   CompareClkCellsByID(){}
   bool operator() ( clkCell* p1, clkCell* p2) const {
	   return p1->id < p2->id;
   }
	
};


class Model
{
	friend class bookshelfParser;
	private:
		int maxIPiter;
		double IP_update_ratio;
		int gridSize;
		double gp_update_ratio;
		int maxCutLevel;
		double overfill_ratio;
		int maxBFSStage;
		int maxGPIter;
	
    public:
        std::vector<Cell *>    cellList;
        std::vector<Net *>     netList;
        StdCellRowDef          *rowDef;
		double x_offset;
		double y_offset;
		double chip_width;
		double chip_height;
		int numOfNonTerminalNodes();
		int numOfPins;

		int get_maxIPiter(){return this->maxIPiter;}
		double get_IP_update_ratio(){return this->IP_update_ratio;}
		int get_gridSize() {return this->gridSize;}
		double get_gp_update_ratio(){return this->gp_update_ratio;}
		int get_maxCutLevel(){return this->maxCutLevel ;}
		double get_overfill_ratio(){return this->overfill_ratio ;}
		int get_maxBFSStage(){return this->maxBFSStage ;}
		int get_maxGPiter(){return this->maxGPIter ;}
		
		Cell* findGCLKCell();
		double minCellWidth();
		double CalculateTotalCellArea();
		int get_maxCellLevel();
		void printNetList();
		void printCellList();
		int get_TotNumOfPins();	
		vector<Cell*> findNeighborCells(Cell* me, bool sameLevel);
		vector<vector<Cell* > > get_LevelBasedCellList();	
		void is_CellID_valid(int id);

		double CalculateCenterOfMass(const vector<Cell*> &);
		
    public:
		double HPWL_x();
		double HPWL_y();
		double HPWL();
  
        Model()
        {
            rowDef = NULL;
        }

        ~Model()
        {
            for (int i = 0; i < int(cellList.size()); i++ )
                delete cellList[i];
            for (int i = 0; i < int(netList.size()); i++ )
                delete netList[i];
            if (rowDef != NULL )
                delete rowDef;
        }
        

};

class    bookshelfParser
{
    public:
        Model *  read(const char *pathName, const char *fileName);
		Model *  read(char**&, int&);
		void     write(Model * chip, string filename);
		char* 	 getDesignName() { return (designName); }
		char*	 getLevelsFileName() { return (levelsFileName); }
		void 	 PrintBenchmarkStatus();
		char* 	 getDesignPath() {return (designPath);}
		char*	 getAUXFileName() {return (auxFileName);}
        void     readFromPlFile(const char *filename);
        std::map<string, Cell *>  name2cell;
		void 	 updateName2CellMap();

    private:
        Model    *model;

        char     netsFileName[1000];
        char     nodesFileName[1000];
        char     plFileName[1000];
		char	 levelsFileName[1000];
        char     designName[1000];
        char     designPath[1000];
		char	 auxFileName[1000];
		
        int      unitScale;
        char     fullname[1000];
        void     getFileName(const char *name);
        void     assignFileName(const char *name);
        void     readFromNodesFile(const char *filename);
        void     readFromNetsFile(const char *filename);
		void     readFromLevelsFile(const char *filename);
        void     getName(const char *name, int num);
        void     write2NodesFile(const char *filename);
        void     write2NetsFile(const char *filename);
        void     write2PlFile(const char *filename);
		void 	 write2SclFile(const char *filename);
		void 	 write2WtsFile(const char *filename);
		void 	 write2AUXfile(string fileName);
		
        void     insertPin2Net(Net *net, Cell *cell, char *io_type,
                               double px, double py);
        int      sweep();
        void     extractDesignName(const char *auxFileName);
        void     extractDesignPath(const char *designPathName);
		void	 extractAUXFileName(const char *auxName);

};

bool compare_cell_x(Cell* a, Cell* b);
bool compare_cell_y(Cell* a, Cell* b);


#endif
