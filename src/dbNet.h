#ifndef DBNET__H
#define DBNET__H

#include "myAssert.h"
#include "dbTypes.h"
#include "dbCell.h"
#include "dbPin.h"


class dbNet
{
  friend class dbNetlist;
  friend class DB;

public:

  std::string      	_name;
  unsigned   		_index;
  const dbNetType  	_type;        // regular, timing, clock
  
  ctainerCells  	_cells;       // source cell(s) come<s> first
  ctainerPins   	_pins;
  
  unsigned		_numOut;
  unsigned		_numInOut;
  unsigned      _numIn;

  bool          _hasLogicalPin;
  double        _weight;      //weight of the net.

private:

  dbNet(const dbNet& from):_type(from._type)
  {
    myAssert(0,"Can't copy-construct dbNet");
  }
  void operator=(const dbNet&)
  {
    myAssert(0,"Can't assign dbNet");
  }
  
public:
  dbNet(std::string name, unsigned idx, dbNetType type,
        const ctainerPins& pins):
      _name(name), _index(idx),_type(type),_pins(pins), _numOut(0), _numInOut(0), _numIn(0), _hasLogicalPin(false), _weight(1) {}
	   
  ~dbNet(){};


  unsigned  getNumCells() const { return _cells.size(); }
  unsigned  getNumPins()  const { return _pins.size() ; }
  unsigned  getDegree()   const { return _cells.size(); }
  unsigned  getNumOut()   const { return _numOut; }
  unsigned  getNumInOut() const { return _numInOut; }
  unsigned  getNumIn()	const {
  return _cells.size() - (_numOut + _numInOut); }
  unsigned   hasLogicalPin() const { return _hasLogicalPin; }
  std::string getName()    const { return _name;}
  unsigned getId() const { return _index; }
  
#if __GNUC__ < 5
// Fixes compilation issue with older gccs where std::vector<T>::erase()
// is not implemented for vector::const_iterators.
	itPin pinsBegin()  { return _pins.begin();  }
	itPin pinsEnd()    { return _pins.end();    }

	itCell cellsBegin() { return _cells.begin(); }
	itCell cellsEnd()   { return _cells.end();   }
#else
	itPin pinsBegin()  const { return _pins.begin();  }
	itPin pinsEnd()    const { return _pins.end();    }

	itCell cellsBegin() const { return _cells.begin(); }
	itCell cellsEnd()   const { return _cells.end();   }
#endif
  
  dbNetType getType () const { return _type; }
  
  
  void addPin ( dbPin* p ) { _pins.push_back(p); }
  
  const dbCell&  getCellByIdx(unsigned i) const
  {
    myAssert(i < _cells.size(),"Cell index out of range");
    return *(_cells[i]);
  }

  const dbPin&  getPinByIdx(unsigned i) const
  {
    myAssert(i < _pins.size(),"Pin index out of range");
    return *(_pins[i]);
  }

  const dbPin *commonPin(const dbCell* cell) const;
  bool   commonPinIsCellInput (const dbCell* cell) const;
  bool   commonPinIsCellOutput(const dbCell* cell) const;

  double getInputCap(const dbCell* cell) const;
  double getDriverResist(const dbCell* cell) const;

operator std::string() const;
friend std::ostream& operator<<(std::ostream& os, const dbNet& net);

  
//private:
  void induceCellsFromPins();
  void sortCellsByIndex();
  //void sortCellsByDir();
  void removeDupPins();
  

};




class CompareNetsByCellIndex    //comp. class for sorting the netlist's nets
{
public:
  CompareNetsByCellIndex(){}

  bool operator()( dbNet* n1, dbNet* n2) const;
};
class CompareNetsByIndex    
{
public:
  CompareNetsByIndex(){}

  bool operator()( dbNet* n1, dbNet* n2) const;
  bool operator()( const dbNet* n1, const dbNet* n2) const;
};

class CompareNetsByDegree
{
public:
  CompareNetsByDegree(){}

  bool operator()( dbNet* n1, dbNet* n2) const;
};

class CompareNetsByName
{
public:
  CompareNetsByName(){}

  bool operator()( dbNet* n1, dbNet* n2) const;
};

class CompareNetsByDirection
{
  const dbCell& _cell;
public:
  CompareNetsByDirection(const dbCell& cell)
      : _cell(cell)
  {}
  bool operator()( dbNet* n1, dbNet* n2) const;
};


inline std::ostream& operator<<(std::ostream& os, const dbNet& net){
	
    os<<" dbNet #"<< net._index;

    std::string name = net._name;
	os<<" ("<<name<<")"<<std::endl;

    os<<"Type: "<<std::string(net._type)<<std::endl;
    os<<"degree: "<<net.getDegree()<<std::endl;
	os<<"#In: " << net.getNumIn() << " #Out: " << net.getNumOut() << std::endl;
	for (unsigned i=0; i < net._cells.size(); i++)
		os << net._cells.at(i)->getIndex() << " ";
	
	
	return os;
}

 inline void dbNet::sortCellsByIndex()
{
  std::sort(_cells.begin(), _cells.end(), CompareCellsByIndex());
}


#endif //DBNET__H
