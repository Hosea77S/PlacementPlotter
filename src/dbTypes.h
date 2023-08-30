/**************************************************************************
***    
*** Copyright (c) 1995-2000 Regents of the University of California,
***               Andrew E. Caldwell, Andrew B. Kahng and Igor L. Markov
*** Copyright (c) 2000-2010 Regents of the University of Michigan,
***               Saurabh N. Adya, Jarrod A. Roy, David A. Papa and
***               Igor L. Markov
***
***  Contact author(s): abk@cs.ucsd.edu, imarkov@umich.edu
***  Original Affiliation:   UCLA, Computer Science Department,
***                          Los Angeles, CA 90095-1596 USA
***
***  Permission is hereby granted, free of charge, to any person obtaining 
***  a copy of this software and associated documentation files (the
***  "Software"), to deal in the Software without restriction, including
***  without limitation 
***  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
***  and/or sell copies of the Software, and to permit persons to whom the 
***  Software is furnished to do so, subject to the following conditions:
***
***  The above copyright notice and this permission notice shall be included
***  in all copies or substantial portions of the Software.
***
*** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
*** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
*** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
*** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
*** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
*** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
*** THE USE OR OTHER DEALINGS IN THE SOFTWARE.
***
***
***************************************************************************/

/*************************************************************************
** Modified by Soheil Nazar Shahsavani (nazarsha@usc.edu)
**************************************************************************/

#ifndef DBTYPES_H
#define DBTYPES_H

#include "dbDefines.h"
#ifndef COMMON__H
#include "common.h"
#endif

//#include "dbCell.h"
//#include "dbPin.h"
//#include "dbNet.h"

#ifndef DBCELL_H
class dbCell;
class dbSuperCell;
class CompareCellsByName;
#endif

#ifndef DBNET_H
class dbNet;
#endif

#ifndef DBPIN_H
class dbPin;
#endif

class dbCell;
class dbNet;
class dbPin;


//=======================================================================//
//									dbPinType							 //
//=======================================================================//

class dbPinType{
	
  enum DIR
  {
	INPUT = 1,
	OUTPUT = 2,
	BIDIR = 3,
	UNKNOWN = 4
  };

private:
  unsigned int _dir;
  
public:
  dbPinType () { _dir = UNKNOWN; }
  dbPinType (std::string dir);
  dbPinType(DIR dir): _dir(dir) {}  

  bool isDirInput() { return _dir == INPUT; }  
  bool isDirOutput() { return _dir == OUTPUT; }  
  bool isDirBi() { return _dir == BIDIR; }  
  bool isDirUnknown() { return _dir == UNKNOWN; }

  
  bool operator==(dbPinType mpt) const
  {
    return (_dir == mpt._dir);
  }

  bool operator!=(dbPinType mpt) const
  {
    return (_dir != mpt._dir);
  }
  
operator std::string() const;
friend std::ostream& operator<<(std::ostream& os, const dbPinType& p);
  
};



//=======================================================================//
//									dbNetType							 //
//=======================================================================//

class dbNetType {

public:
  enum NetType 
  { 
	SIGNAL=0, 
	POWER=1, 
	GROUND=2, 
	CLOCK=3, 
	UNKNOWN=4
  };
	
private:
  std::string _text;
  unsigned int _type : 4;  


public:
  dbNetType() { _type = UNKNOWN; _text = "UNKNOWN"; } 
  dbNetType(std::string t);
  dbNetType(NetType nt): _type(nt) {}

  bool isSignal() { return _type == SIGNAL; }
  bool isPower() { return _type == POWER; }
  bool isGround() { return _type == GROUND; }
  bool isClock() { return _type == CLOCK; }
  bool isUnknown() { return _type == UNKNOWN; }

  bool operator==(dbNetType nt)
  {
    return _type == nt._type;
  }
  bool operator!=(dbNetType nt)
  {
    return _type != nt._type;
  }
  
  operator std::string() const;
  
	
};


//=======================================================================//
//									dbCellType							 //
//=======================================================================//
class dbCellType {

  enum MacroType 
  { 
	IO =1, 
	BLOCK=2, 
	CORE=3,
	MacroUNKNOWN=4
  };
  enum IOType    
  { 
	PI=0, 
	PO=1,
	PIO=2, 
	IOUNKNOWN=3 
  };
  
  enum CoreType  
  { 
	SC=0, 
	CC=1, 
	COREUNKNOWN=2 
  };

private:  
  std::string _text;
  unsigned int _mType : 3;
  unsigned int _subType: 2;  

public:
  dbCellType(): _mType(MacroUNKNOWN), _subType(IOUNKNOWN) {}
  dbCellType(MacroType m, int s):
      _mType(m), _subType(s) {}  
  dbCellType(std::string , std::string);

  bool isIO() const { return _mType == IO; }
  bool isCore() const { return _mType == CORE; }
  bool isBlock() const { return _mType == BLOCK; }
  bool isUnknown() const { return _mType == MacroUNKNOWN; }

  bool isPI()       const
  {
    myAssert(_mType == IO, "isPI is invalid for non-Pad cells");
    return _subType == PI;
  }
  bool isPO()       const
  {
    myAssert(_mType == IO, "isPO is invalid for non-Pad cells");
    return _subType == PO;
  }
  bool isPIO()      const
  {
    myAssert(_mType == IO, "isPIO is invalid for non-Pad cells");
    return _subType == PIO;
  }
  bool isPUnknown() const
  {
    myAssert(_mType == IO, "isPUnknown is invalid for non-Pad cells");
    return _subType == IOUNKNOWN;
  }

 bool isCC()          const
  {
    myAssert(_mType == CORE, "isCC is invlaid for non-Core cells");
    return _subType == CC;
  }
  bool isSC()          const
  {
    //myAssert2(_mType == CORE, "isSC is invalid for non-Core cells ", _mType);
    return _subType == SC;
  }
  bool isCoreUNKNOWN()   const
  {
    myAssert(_mType == CORE, "isCoreOther is invalid for non-Core cells");
    return _subType == COREUNKNOWN;
  }
  
  bool operator==(dbCellType ct) const;
  bool operator!=(dbCellType ct) const;
  operator std::string() const;

  
};

inline std::ostream& operator<<(std::ostream& os, const dbPinType& p){
	std::string ss = p;
	os << ss ;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const dbNetType& n){
	std::string ss = n;
	os << ss;
	return os;
}


inline bool dbCellType::operator==(dbCellType ct) const
{
  if (_mType != ct._mType) return false;
  if (_mType != IO && _mType != CORE) return true;
  if (_subType == ct._subType) return true;
  return false;
}

inline bool dbCellType::operator!=(dbCellType ct) const
{
  if (_mType != ct._mType) return true;
  if (_mType != IO && _mType != CORE) return false;
  if (_subType == ct._subType) return false;
  return true;
}

inline std::ostream& operator<<(std::ostream& os, const dbCellType& c){
	std::string ss = c;
	os << ss;
	return os;
}


typedef std::vector<dbPin*>		                  ctainerPins;
typedef std::vector<dbNet*>                       ctainerNets;
typedef std::vector<dbCell*>                      ctainerCells;
//typedef std::vector<dbRow*>                       ctainerRowsGlobal;

#if __GNUC__ < 5
// Fixes compilation issue with older gccs where std::vector<T>::erase()
// is not implemented for vector::const_iterators.
typedef ctainerPins::iterator         itPin;
typedef ctainerNets::iterator         itNet;
typedef ctainerCells::iterator        itCell;
#else
typedef ctainerPins::const_iterator         itPin;
typedef ctainerNets::const_iterator         itNet;
typedef ctainerCells::const_iterator        itCell;
#endif

#endif // DBTYPES_H
