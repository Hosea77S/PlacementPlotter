#ifndef DBCELL_H
#define DBCELL_H


#include "dbDefines.h"
#include "dbTypes.h"
#include "dbPin.h"
#include "dbSym.h"
#include "dbPoint.h"
#include "placement.h"


class dbCell {

public:
  MakeFriendsWithParsers;
  friend class dbNetlist;
  friend class DB;
  
  std::string      _name;
  unsigned         _index;    
  dbCellType 	   _type;
  
  double      _fallDelay;
  double      _riseDelay;
  
  double     _width;
  double     _height;
  
  Point            _origin;    
  
  unsigned         _inDegree;  
  unsigned         _outDegree; 
                             
  unsigned 		   _level;    
  
  ctainerPins 	   _pins;
  ctainerNets 	   _nets;	
  std::vector<ctainerPins> _setsOfJointPins;
      
  const Symmetry   _symmetry;
  
  dbCell(const dbCell& from): _type(from._type),
       _width(from._width),_height(from._height)
      { myAssert(0,"Can't copy-construct dbCell"); }
  void operator=(const dbCell&) const
      { myAssert(0,"Can't assign dbCell"); }
  
  dbCell(std::string name, std::string type, std::string sType, 
  			  unsigned index , double wth, double ht, Point orig, 
  			  unsigned level, const ctainerPins& pns, Symmetry sym);
			  
  dbCell(std::string name, std::string type, std::string sType,
               unsigned index , double wth, double ht);
			  
  ~dbCell(){};	

  unsigned getIndex()  const { return _index; }

  
  unsigned getNumPins()        const { return _pins.size(); }
  unsigned getNumNets() 		 const { return _nets.size(); }
  double   getHeight()         const { return _height;   }
  double   getWidth()          const { return _width;    }
  double   getArea()		   const { return _width*_height;}
  const ctainerNets getNets()	 const { return _nets; 		 }
  const ctainerPins getPins()	 const { return _pins; 		 }	
  std::string getName() const { return _name; }
  std::string getSymmetry() const { return _symmetry; }
  
  unsigned getLevel()        const { return _level; }
  const Point getOrigin()     const { return _origin;}
  
  bool isBlock()   const {return _type.isBlock();  }
  bool isCore()    const {return _type.isCore();   }
  bool isIO()      const {return _type.isIO();    }
  bool isUnknown() const {return _type.isUnknown(); }
  bool isFixed()   const {return !isCore(); }
  
  bool isPI()	  const {return _type.isPI();	   }
  bool isPO()	  const {return _type.isPO();      }
  bool isPIO()	  const {return _type.isPIO();	   }
  bool isPUnknown() const {return _type.isPUnknown();}
  
  bool isCC()           const {return _type.isCC();         }
  bool isSC()           const {return _type.isSC();         }
  bool isClkSink()      const {return _type.isSC();         }
  bool isCoreUNKNOWN()  const {return _type.isCoreUNKNOWN();  }
  bool isDisconnected() const { return (_nets.size()==0); }
  bool isClkSpl()		const ;
  

/* 	dbPin const *commonPin(const dbNet* net) const;
	bool commonPinIsCellInput(const dbNet*  net) const;
	bool commonPinIsCellOutput(const dbNet* net) const;
 */	

#if __GNUC__ < 5
// Fixes compilation issue with older gccs where std::vector<T>::erase()
// is not implemented for vector::const_iterators.
  itPin pinsBegin() { return _pins.begin(); }
  itPin pinsEnd()   { return _pins.end();   }
  itNet netsBegin() { return _nets.begin();}
  itNet netsEnd()   { return _nets.end();} 
#else

  itPin pinsBegin() const { return _pins.begin(); }
  itPin pinsEnd()   const { return _pins.end();   }
  itNet netsBegin() const { return _nets.begin();}
  itNet netsEnd()   const { return _nets.end();} 
#endif

  void setCoordinate(Point c) { 
    _origin.x = c.x; 
    _origin.y = c.y; 
    return;
  }	
  
  void setHeight (double h) { _height = h; }
  void setWidth  (double w) { _width  = w; }
  
  void setLevel(unsigned l) { _level = l; }
  void setName (std::string n) { _name = n; }
  void setIndex ( unsigned id ) { _index = id; }
  
  void induceNetsFromPins(std::vector<dbNet*> *Snets);
  void induceNetsFromPins();
  
  operator std::string() const;
  friend std::ostream& operator<<(std::ostream& os, const dbCell& cell);
  
  //TODO implement sort functions based on x and y direction
  
  Point getCenter (const Point& pl) const
  { return Point(pl.x + getWidth()/2, pl.y + getHeight()/2); }
	
  std::vector<int> getCommonNets(const std::vector<dbCell*>& );	
  	
};



class CompareCellIdsByX
{
   const Placement& _placement;
public:
   CompareCellIdsByX(const Placement& place)
      :_placement(place)
      {}

   bool operator()(unsigned id1, unsigned id2)
      { return _placement[id1].x < _placement[id2].x;}
};


class CompareCellIdsByY
{
   const Placement& _placement;
public:
   CompareCellIdsByY(const Placement& place)
      :_placement(place)
      {}

   bool operator()(unsigned id1, unsigned id2)
      { return _placement[id1].y < _placement[id2].y;}
};


class CompareCellsByType
{
   public:
    CompareCellsByType(){}
    
	bool operator() (dbCell* c1, dbCell* c2) const 
	{
		if ((c1->isCore() && c2->isCore()  ) ||
			(c1->isIO() && c2->isIO()      ) ||
			(c1->isBlock() && c2->isBlock())  )
			{
				return c1->getIndex() < c2->getIndex();
			}
		return c1->isIO() < c2->isIO();
	}
   
};

class CompareCellsByIndex
{
   public:
    CompareCellsByIndex(){}

    bool operator() ( dbCell* c1, dbCell* c2) const
    {
        return ( c1->getIndex() < c2->getIndex() );
    }
};

class CompareCellsByName
{
   public:
    CompareCellsByName(){}

    bool operator() ( dbCell const* c1, dbCell const* c2) const
    {
        int cmpResult = c1->_name.compare(c2->_name);
        if(cmpResult < 0) return true;
        else if (cmpResult > 0) return false;
        else  return false;
    }
};


class CompareCellsByPlace
{
   public:
    CompareCellsByPlace(){}

    bool operator() ( dbCell const* c1, dbCell const* c2) const
    {
		if (c1->_origin == c2->_origin) {
			return ( c1->getIndex() < c2->getIndex() );
		}
		return ( c1->_origin < c2->_origin );		
    }
};


class CompareCellsByX
{
public:
  CompareCellsByX(){}
  int operator()(dbCell const* c1, dbCell const* c2) const 
	{ 
		if (c1->_origin.x != c2->_origin.x)
			return c1->_origin.x < c2->_origin.x; 
		return c1->getIndex() < c2->getIndex();
	}
};
class CompareCellsByY
{
public:
  CompareCellsByY(){}
  int operator()(dbCell const* c1, dbCell const* c2) const 
	{	if (c1->_origin.y != c2->_origin.y) 	
			return c1->_origin.y < c2->_origin.y; 
		return c1->getIndex() < c2->getIndex();
		
	}
};

class CompareByLoc
{
public:
  CompareByLoc(){}
  int operator()(dbCell const* c1, dbCell const* c2) const 
	{ 
		if (c1->_origin.x != c2->_origin.x){
			return c1->_origin.x < c2->_origin.x;
		} else if (c1->_origin.y != c2->_origin.y){
			return c1->_origin.y < c2->_origin.y; 			
		}
		else {
			return c1->getIndex() < c2->getIndex();
		}
	}
};




class dbSuperCell
{
	
public:	
    std::string      _name;
    unsigned         _index;    
        
    double     		 _width;
    double     		 _height;
    
    Point            _origin;    
    
    unsigned         _inDegree;  
    unsigned         _outDegree; 
                               
	dbCell*  _myCell;
							   
	unsigned 		 _level; //if cells are with multiple levels, obsolete
							
    ctainerCells _cells;
    ctainerPins  _pins;
	ctainerNets  _nets;	


#if __GNUC__ < 5
// Fixes compilation issue with older gccs where std::vector<T>::erase()
// is not implemented for vector::const_iterators.
	itPin  pinsBegin()  { return _pins.begin(); }
	itPin  pinsEnd()    { return _pins.end();   }
	itCell cellsBegin() { return _cells.begin(); }
	itCell cellsEnd()   { return _cells.end();   }
	itNet  netsBegin()  { return _nets.begin();}
	itNet  netsEnd()    { return _nets.end();} 
#else
	itPin  pinsBegin()  const { return _pins.begin(); }
	itPin  pinsEnd()    const { return _pins.end();   }
	itCell cellsBegin() const { return _cells.begin(); }
	itCell cellsEnd()   const { return _cells.end();   }
	itNet  netsBegin()  const { return _nets.begin();}
	itNet  netsEnd()    const { return _nets.end();} 
#endif

  unsigned getNumPins()        const { return _pins.size(); }
  unsigned getNumNets() 	   const { return _nets.size(); }
  unsigned getNumCells() 	   const { return _cells.size(); }
  double   getHeight()         const { return _height;   }
  double   getWidth()          const { return _width;    }
  double   getArea()		   const { return _width*_height;}
	
	
	dbSuperCell(std::string name, unsigned index, Point orig, 
				unsigned level, const ctainerCells& cls, std::string type = "SC");
				
	~dbSuperCell();						
	dbCell* getCell() const ;
	friend std::ostream& operator<<(std::ostream& os, const dbSuperCell& );
	
	
};	
	


	
#endif //__DBCELL__H
