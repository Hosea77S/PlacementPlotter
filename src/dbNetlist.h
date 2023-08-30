#ifndef DBNETLIST_H
#define DBNETLIST_H

#include "dbDefines.h"
#include "dbTypes.h"
#include "dbPoint.h"
#include "dbIntPoint.h"
#include "dbSym.h"
#include "dbCell.h"
#include "dbNet.h"
#include "dbPin.h"
#include "dbClkCell.h"
#include "Bbox.h"
#include "dbRowDef.h"
#include "placement.h"


class CompareCellsByName;
class CompareCellsByIndex;
class CompareNetsByCellIndex;


class dbNetlist 
{
    friend class DB;
	friend class bookShelfParser;
	friend class CTS;
	friend class Cluster;
 	friend class bloat;
 	friend class levelPlacement;
 	friend class timingAna;
       
    //will all be populated by Parser/bookShelfParser
    ctainerCells	         _cellLib;
    ctainerPins		         _pinLib;
    ctainerNets		         _netLib;

	std::map<std::string, dbCell*> _nameCellMap;
   
    unsigned		  	  _numIOPads; 
    unsigned		  	  _numAllPads;
    unsigned              _numIOPins;
    unsigned              _numCoreCells;

    unsigned		  _numCCs;
    unsigned		  _numSCs;
    unsigned	      _numDummy1;	//no current use
    unsigned	 	  _numDummy2;	

    double		  	  _coreCellArea;
    

        // this is what you can't do  --
        // default copy-ctor and assignment are wrong

/*         dbNetlist(const dbNetlist&)
                 { myAssert(0,"Can't copy-construct dbNetlist"); }
        dbNetlist& operator=(const dbNetlist&)
                 { myAssert(0,"Can't assign dbNetlist"); return *this; }
 */    
    public:
	
		std::map<unsigned, std::vector<dbCell*> > _level2CellMap;
		std::map<unsigned, std::vector<dbCell*> > getLevel2CellMap() const
		{ return _level2CellMap; }
        
        dbNetlist(); // will be populated by parsers
        ~dbNetlist();
        
        
        bool isConsistent() const;
        
        unsigned getNumCells() 		 const {return _cellLib.size();}
        unsigned getNumPins()  		 const {return _pinLib.size();}    
        unsigned getNumNets()        const { return _netLib.size();   }
        unsigned getNumClkNets()        const;
        unsigned getNumClkPins()        const;

	unsigned getNumCCs()	const	{ return _numCCs; }
	unsigned getNumSCs()	const	{ return _numSCs; }
	unsigned getNumIOPads() const	{ return _numIOPads;}
	unsigned getNumAllPads() const 	{ return _numAllPads;}
	unsigned getNumIOPins()	const	{ return _numIOPins; }
	unsigned getNumCoreCells() const{ return _numCoreCells; }

#if __GNUC__ < 5
// Fixes compilation issue with older gccs where std::vector<T>::erase()
// is not implemented for vector::const_iterators.
        itCell cellsBegin() { return _cellLib.begin();}
        itCell cellsEnd()   { return _cellLib.end();  }

        itNet  netsBegin()  { return _netLib.begin(); }
        itNet  netsEnd()    { return _netLib.end();   }

	itPin  pinsBegin()  { return _pinLib.begin(); }
	itPin  pinsEnd()    { return _pinLib.end();   }
#else
        itCell cellsBegin() const { return _cellLib.begin();}
        itCell cellsEnd()   const { return _cellLib.end();  }

        itNet  netsBegin()  const { return _netLib.begin(); }
        itNet  netsEnd()    const { return _netLib.end();   }

	itPin  pinsBegin()  const { return _pinLib.begin(); }
	itPin  pinsEnd()	  const { return _pinLib.end();   }
#endif

	int findGCLKCell() const ;

        
        const dbCell& getCellByIdx(unsigned i) const;
        const dbNet&  getNetByIdx(unsigned i) const;
        const dbPin&  getPinByIdx(unsigned i) const;

	dbCell& getCellByIdxSurgery(unsigned i); //yusuketest

        
	bool isCellIdValid ( unsigned idx ) const {
		myAssert3 ( idx >=0 && idx < getNumCells(),
			idx , " out of bounds for _cellLib.", getNumCells());
		return true;
	}
		
	void postProcess();        

	double evalHalfPerimCost(dbNet *net, 
                        bool IONetsOnly=false) const;
	double evalHalfPerimCostX(dbNet *net, 
                        bool IONetsOnly=false) const;
	double evalHalfPerimCostY(dbNet *net, 
                        bool IONetsOnly=false) const;

						
 	double evalHalfPerimCostNoPins(dbNet *net, 
                        bool IONetsOnly=false) const;

	double evalHalfPerimCost(const Placement &pl, 
                unsigned threshold=0, bool IONetsOnly=false) const;
	double evalHalfPerimCostX(const Placement &pl, 
                unsigned threshold=0, bool IONetsOnly=false) const;
	double evalHalfPerimCostY(const Placement &pl, 
                unsigned threshold=0, bool IONetsOnly=false) const;
				
	double evalWHalfPerimCost(const Placement &pl, 
               unsigned threshold=0, bool IONetsOnly=false) const;
                // weighted
 	double evalHalfPerimCostNoPins(dbNet *net, const Placement &pl,
                        bool IONetsOnly=false) const;

				
						
	void printNetStats(std::ostream& out) const;
	void printNetStats() const  { printNetStats(std::cout); }

	double evalHalfPerimCost(dbNet *net, const Placement &pl,
			bool IONetsOnly=false) const;
			
	double evalHalfPerimCost(int netId, const Placement &pl,
				bool IONetsOnly) const;
			

	void sortCellsByType ();
	std::vector<unsigned> getPadIndices () const;
    dbNet* addNetToChip
    ( unsigned sourceCell, unsigned sinkCell, 
	  std::string newNetName, int outPinNum, std::string,
	  bool isCellClkSpl = true,
	  double srcCellPinPos = Constants::CELL_OUT_PIN_POS, 
	    double sinkCellPinPos =  Constants::CELL_IN1_PIN_POS);

	
private:
	double evalHalfPerimCost(unsigned threshold=0,
                                 bool IONetsOnly=false) const;
	double evalMSTCost      () const;

	double evalWHalfPerimCost( unsigned threshold=0,
							 bool IONetsOnly=false) const;
							 
	double evalHalfPerimCostX(dbNet *net, const Placement &pl,
			bool IONetsOnly=false) const;
	double evalHalfPerimCostY(dbNet *net, const Placement &pl,
			bool IONetsOnly=false) const;
							 
};

inline dbNetlist::dbNetlist():
_numIOPads(0),_numAllPads(0),_numIOPins(0),_numCoreCells(0)
{ 
//_rowDefs =  new dbRowDef;
}

inline const dbCell& dbNetlist::getCellByIdx(unsigned i) const
{    
    myAssert3(i < _cellLib.size(), i, " Cell number exceeds maximum ", _cellLib.size());
    return *(_cellLib[i]);
}

inline const dbNet& dbNetlist::getNetByIdx(unsigned i) const
{    
    myAssert(i < _netLib.size(),"Net number exceeds maximum");
    return *(_netLib[i]);
}


inline const dbPin& dbNetlist::getPinByIdx(unsigned i) const
{    
    myAssert(i < _pinLib.size(),"Pin number exceeds maximum");
    return *(_pinLib[i]);
}

inline dbCell& dbNetlist::getCellByIdxSurgery(unsigned i)  //yusuketest
{    
    myAssert3(i < _cellLib.size(), i, " Cell number exceeds maximum ", _cellLib.size());
    return *(_cellLib[i]);
}


#endif
