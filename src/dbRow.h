#ifndef DBROW_H
#define DBROW_H

#include "dbPoint.h"
#include "dbCell.h"

class dbRow {
public:
  unsigned _index;
  BBox _bbox;
  std::vector<int> _rowCells;
  
  dbRow():
	_index(0), _bbox( BBox (0,0,1,1) ) {}
  dbRow(const std::vector<int>& c): 
	_index(0), _bbox( BBox (0,0,1,1) ), _rowCells(c){}
  dbRow( unsigned i, BBox bb, const std::vector<int>& c ): 
	_index(i),_bbox(bb),  _rowCells(c){}

  
	void addCell (unsigned c){
		_rowCells.push_back(c);
	}  
	
    unsigned operator[](unsigned idx) {
		myAssert (idx < _rowCells.size(), "Cell index out of bound");
		return _rowCells[idx];
	}
	
	BBox getBBox () const { return _bbox; }
	std::vector<int> getCellIndices() { return _rowCells; }
	void setBBox(const BBox& bb) { _bbox = bb; }
	unsigned getNumCells () const { return _rowCells.size(); }
	unsigned getIndex () const { return _index; }
  
friend std::ostream&  operator<<(std::ostream& out, const dbRow& r);
	
};




#endif //DBROW_H