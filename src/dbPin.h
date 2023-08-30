#ifndef DBPIN_H
#define DBPIN_H
/* 
#include "dbCell.h"
#include "dbTypes.h"
//#include "dbNet.h"
 */

#include <string> 
#include "dbDefines.h"
#include "dbTypes.h"
#include "dbCell.h"
#include "dbPoint.h"
 

 
class dbPin
{

  friend class dbNetlist;
	
public:

  std::string     _name;
  dbPinType       _type;
  unsigned        _index;
  const dbCell    * _cell;  // cell and net ptrs can't be references
  const dbNet     * _net;   // because they are set after pin is
  const Point     _center;

  double _riseDelay;
  double _fallDelay;
  double _riseResist;
  double _fallResist;
  double _inputCap;

  dbPin(const std::string name, const std::string dir, unsigned ind, Point center)
      :_name(name), _type(dir), _index(ind), _cell(NULL),
      _net(NULL), _center(center) { }

  ~dbPin(){};
  
  const dbCell& getCell() const
  {
    myAssert(_cell != NULL, "Null cell* in pin");
    return *_cell;
  }
  const dbNet& getNet()  const
  {
    myAssert(_net != NULL, "Null net* in pin");
    return *_net;
  }


operator std::string() const;
friend std::ostream& operator<<(std::ostream& os, const dbPin& pin);

  void setCell(dbCell const& cell) { _cell = &cell; }
  void setNet (dbNet  const&  net) { _net  = &net; }
  bool isConnected() const { return _net != NULL; }  
  bool isDirOutput()         { return  _type.isDirOutput(); }
  bool isDirInput()          { return  _type.isDirInput(); }
  bool isDirBi()             { return  _type.isDirBi(); }
  bool isDirUnknown()        { return  _type.isDirUnknown(); }

  Point           getCenter()  const { return _center;}
  dbPinType getDir () const { return _type; }
  std::string getName()    const { return _name;  }
  unsigned getIndex () const { return _index; }
  
};




class ComparePinsByDirAndName
{
  //output, inout, then input
public:
  ComparePinsByDirAndName(){}

  bool operator() ( dbPin* p1, dbPin* p2) const;
};

class ComparePinsByName
{
  //output, inout, then input
public:
  ComparePinsByName(){}

  bool operator() ( dbPin* p1, dbPin* p2) const {
    int strCmpResult;
    strCmpResult = p1->_name.compare(p2->_name);
    if(strCmpResult < 0)      return true;
    else if(strCmpResult > 0) return false;
    else return p1 < p2;	  
  }
};






#endif //__DBPIN__H