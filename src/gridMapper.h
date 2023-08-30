//==============================================================================//
//                                      qPlace                                  //
//                                                                              //
//               Written by Soheil Nazar Shahsavani and Massoud Pedram          //
//      SPORT Lab, University of Southern California, Los Angeles, CA 90089     //
//                           http://sportlab.usc.edu/                           //
//                     ColdFlux Project, http://coldflux.usc.edu                //
//                                                                              //
//  For licensing, please refer to the LICENSE file.                            //
//                                                                              //
// The development is supported in part by IARPA SuperTools program             // 
// via grant W911NF-17-1-0120.                                                  // 
//                                                                              // 
//==============================================================================//


#ifndef GRIDMAPPER_H
#define GRIDMAPPER_H

#include "DB.h"

#include <queue>

#define THRESHOLD 0.1

class GridBin {
	
private:
	const DB* _db;
	BBox _bbox;
	unsigned _id;
	std::vector<int> _cellIndices;
	bool _touched;
	
public:
	GridBin (const DB* db, BBox bb, const Placement& pl, unsigned id): 
			_db(db), _bbox(bb), _id(id), _touched(false) {
		for (int i=0; i < pl.getSize(); i++){
			if ( _bbox.contains(pl[i]) ){
				_cellIndices.push_back(i);
			}
		}
	}

	GridBin (const DB* db, BBox bb, unsigned id): 
		_db(db), _bbox(bb), _id(id), _touched(false) {}

	GridBin(){}
	//GridBin getGridBin(){ return *(this); }
	
	void setTouched (bool f) {_touched = f;}
	bool isTouced () { return _touched; }
	unsigned getID(){return _id;}
	unsigned getID() const {return _id;}
	void setID(unsigned i) { 
	myAssert (i >= 0, " Invalid ID"); 
	_id = i; }

	void setBBox (const BBox& b) { _bbox = b; }
	void addCellIdx(unsigned idx) {
	    auto ptr = std::find(_cellIndices.begin(), _cellIndices.end(), idx);
	    if (ptr != _cellIndices.end()) return; //already present
		
		_cellIndices.push_back(idx);
		return;
	}
	
	bool removeCellIdx(unsigned idx){
		
	  auto ptr = std::find(_cellIndices.begin(), _cellIndices.end(), idx);
	  if (ptr == _cellIndices.end()) return false;
	  _cellIndices.erase(ptr);
	  if (_cellIndices.size() == 0)
        myWarn(0, "\n\nsize of the _cellIndices is 0 now.\n\n");		  
	  return true;
	}
	
	void addCellIdx(const std::vector<int>& idVec) {
		_cellIndices.insert(_cellIndices.end(), idVec.begin(), idVec.end() );
		return;
	}
	
	void clearCellIndices() { _cellIndices.clear(); }
	
	bool contains (const Point& pt) {
		return _bbox.contains(pt);
	}
	
	unsigned getCellCount() const {
		return _cellIndices.size();
	}
	
	BBox getBBox () const {
		return _bbox;
	}
	
	double getArea(){
		return _bbox.getArea() ;
	}
	
	std::vector<int> getCellIndices() const{
		return _cellIndices;
	}
	
	double getDensity() const {
		return (double) getCellArea()/_bbox.getArea();		
	}
	
	double getCellArea() const {
		double cellArea = 0.0;
		for (unsigned i=0; i < _cellIndices.size(); i++)
			cellArea += (*_db).getNetlist().getCellByIdx(_cellIndices[i]).getArea();		
		return cellArea;
	}
	
	double getCellAreaMedian(const Placement* pl, const Dir& d) const;
	std::pair <GridBin, GridBin> divideByCutLine (double, const Placement* , const Dir& ) const;
	double getCellCountMedian ( const Placement* pl, const Dir& d ) const;
	void legalizeBin(Placement* , Dir );
	
friend std::ostream&  operator<<(std::ostream& out, const GridBin& arg){
	out << "id: " << arg._id << " bbox: " << arg._bbox << " Total cells: " << arg.getCellCount() << " utility: " << arg.getDensity();
	return out;
}	
	
};


class CompareGridBinsByDensity
{
   public:
    CompareGridBinsByDensity(){}
    
	bool operator() (const GridBin& c1, const GridBin& c2) const 
	{
		//cout << "c1: " << c1.getDensity() << " c2: " << c2.getDensity() << "\n";
		return (greaterThanDouble( c1.getDensity(), c2.getDensity() ));
	}
	
};


class GridMapper {

private:
	const DB* _db;
	unsigned         _xSize, _ySize; 
    //std::vector<int> _pointIdcs;
	std::vector<GridBin> _gridBins;
	BBox _bbox;
	const Placement* _pl;


public:
	GridMapper(const DB* db, unsigned xs, unsigned ys, const BBox& bb, const Placement* pl);
	GridMapper(const DB* db, unsigned xs, unsigned ys, const BBox& bb, const Placement* pl, std::vector<GridBin>gb): _db(db), _xSize(xs), _ySize(ys), _gridBins(gb), _bbox(bb), _pl(pl){}

		//dummy
		GridMapper(){}		
		GridMapper(const DB* db, unsigned depth, const BBox& bb, const Placement* pl);  
		GridMapper
			(const DB* db, unsigned depth, const GridBin& parentGb, const Placement* pl );

		
void snapCellsToGrids();	
void snapCellsToGrids_bf();	
friend std::ostream&  operator<<(std::ostream& out, GridMapper& arg);

double getCellDensity(unsigned idx);
std::vector<GridBin> getGridBins () const { return _gridBins; }
GridBin combineGridBins (unsigned idx1, unsigned  idx2) const ;
GridBin combineGridBins (const GridBin& gbin1, const GridBin& gbin2) const ;

unsigned getTotalSize() const { return _xSize*_ySize; }
int getLeftGBin     ( unsigned idx ) const ;
int getRightGBin    ( unsigned idx ) const ;
int getTopGBin      ( unsigned idx ) const ;
int getBottomGBin   ( unsigned idx ) const ;

GridBin clusterBins ( const GridBin& gb, double targetUtil );
std::vector<GridBin> buildGBinsRecursively
	(unsigned depth, const GridBin& parentGb, const Placement* pl );	
};


/* void GridBin::legalizeBin
	(Placement* anchorPl, Dir d)
{
	GridMapper gm;
	
	if (d == _XX){
		int ySize = (int) ceil(_bbox.getHeight()/(*_db)._rowDefs->getRowHeight());
		//cout << "Creating " << ySize << " horizontal bins for legalizing\n";
		gm = GridMapper(_db, 1, ySize, _bbox, anchorPl);		
		gm.snapCellsToGrids();	
		//cout << gm << endl;
	} else {
		int xSize = (int) ceil (_bbox.getWidth() / (*_db).getAvgCellWidth());
		//cout << "Creating " << xSize << " vertical bins for legalizing\n";
		gm = GridMapper (_db, xSize, 1, _bbox, anchorPl);
		gm.snapCellsToGrids();	
		//cout << gm << endl;
	}	
	
	Legalizer lg (_db);
	auto gridBins = gm.getGridBins();	
	for (unsigned i=0; i < gridBins.size(); i++){
		//cout << i << " gBin: " << gridBins.at(i) << endl;
		lg . doInGridLegalization(gridBins.at(i), anchorPl, d); 
	}
	
	return;
} */



#endif //GRIDMAPPER_H