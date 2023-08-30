#ifndef DB_H
#define DB_H

#include <boost/algorithm/string.hpp>
#ifndef COMMON__H
#include "common.h"
#endif

#include "dbTypes.h"
#include "dbDesign.h"
#include "dbSpatial.h"
#include <vector>
#include <fstream>

class dbNetlist;

class DB
{
	
	friend class bookShelfParser;
	friend class CTS;	
	friend class Cluster;
	friend class bloat;
	friend class levelPlacement;
	friend class timingAna;
	
public:

    class Parameters
    {
      public:
          bool  fixPlacedPads;

      Parameters();
    };

private:
     
    Parameters _params;
	//will be set by the bookshelParser class
    std::string auxName; // w/o path 
    std::string pathName;
    std::vector<std::string> allFileNamesInAUX; // w/o path
    std::string designName; // w/o path 
    dbNetlist   _design;


	
    void  postProcessor(const std::string  LGCFileName=NULL);
                           //always called after parsing in every DB
                           //constructor, before consistency check
              
    
 public:   
 
		dbSpatial _spatial;	
		dbRowDef* _rowDefs;
 
 
        DB(Parameters params=Parameters());
       ~DB();
        bool  isConsistent() const;
        const std::string getAuxName() const { return auxName;  }
        const std::string getDesignPath() const { return pathName; }
        const std::string getDesignName() const { return designName; }
		void setDesignName(std::string n){ designName = n; }
		
        bool hasDesignName() const { return (designName.size())>0; }
        const std::vector<std::string >& getFileNames() const 
			{ return allFileNamesInAUX; }
        
        const dbNetlist& getNetlist() const { return _design;  }
        dbNetlist& getNetlistForSurgery() { return _design;  }

        double evalHPWLcost(unsigned threshold=0, bool IONetsOnly=false) const;
        double evalHPWLcostX(unsigned threshold=0, bool IONetsOnly=false) const;
        double evalHPWLcostY(unsigned threshold=0, bool IONetsOnly=false) const;
        // Half-Perimeter wirelength cost estimate (0 -- no thresholding)
        double evalWHPWLcost(unsigned threshold=0, bool IONetsOnly=false) const;
        // same, but net costs are weighted

        double evalHPWLcost(Placement& pl, unsigned threshold=0, bool IONetsOnly=false) const;
        // Half-Perimeter wirelength cost estimate (0 -- no thresholding)
        double evalWHPWLcost(Placement& pl, unsigned threshold=0, bool IONetsOnly=false) const;
        // same, but net costs are weighted
		
		
        void printNetStats(std::ostream& out) const  
			{ _design.printNetStats(out); }
        void printNetStats() const  { printNetStats(std::cout); }

        //Point locatePin(const dbPin& pin, const Placement& placement,
        //                const std::vector<Orient>& orientations) const;
        // These two methods are for calculating the actual location
        // of a given pin in the layout

	//void setPlaceAndOrient(const PlacementWOrient& plWOri);
        void PrintBenchmarkStatus(std::ostream&os = std::cout);
		double calculateTotalCellArea() const;
		int getMaxLevel();
		double getAvgCellWidth () const;
		
        std::vector < std::pair<int, double> >  acquireSameHPWLLNet();  //yusukeadd
        void printAllNetHPWL(); //yusuke
		
        unsigned findCellIdxByName( std::string name ) const;
        double  getTotalCoreCellWidth() const;
        double  getTotalCoreCellHeight() const;
		
};

std::pair<int, double> findCriticalPath
 (const DB* db, bool print = true, std::ostream&os = std::cout);


#endif //DB_H
