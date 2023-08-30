#include "dbRow.h"

std::ostream&  operator<<(std::ostream& out, const dbRow& r){
	out << "Row: " << r._index << " BBox: " << r._bbox ;
	out << " Num of cells: " << r._rowCells.size() << "\n";
	return out;
}

