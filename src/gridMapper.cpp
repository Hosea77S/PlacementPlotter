#include "gridMapper.h"


double GridBin::getCellCountMedian( const Placement* pl, const Dir& d) const
{
	auto cInd = _cellIndices;
	if (cInd.size() == 0)
		return (d == _XX) ? _bbox.getBottomLeft().x : _bbox.getBottomLeft().y;
	
	if (d == _XX)
	sort(cInd.begin(), cInd.end(), 
			CompareCellIdsByX( *pl ));
	else 
	sort(cInd.begin(), cInd.end(), 
			CompareCellIdsByY(  *pl ));
						
	int median = cInd.size() / 2;
	myAssert3 (median >= 0 && median < int(cInd.size()), median, " wrong median index: ", cInd.size());
	
	//auto center = (*_db).getNetlist().getCellByIdx( cInd.at(median) ).getCenter( (*pl)[ cInd.at(median) ] );
	auto center = (*pl)[ cInd.at(median) ];

	if (d == _XX) return center.x;
	return 	center.y;
}

double GridBin::getCellAreaMedian(const Placement* pl, const Dir& d) const
{
	Point centerP = _bbox.getGeomCenter();
	Point lowP = _bbox.getBottomLeft();
	Point highP = _bbox.getTopRight();
	double low, high, mid;
	if (d == _XX){		
		low = lowP.x;
		high = highP.x;
		mid = centerP.x;		
	} else {
		low = lowP.y;
		high = highP.y;
		mid = centerP.y;		
	}
	myAssert ( equalDouble ( mid, (low+high)/2), " mid is wrong" );

	int iter=0;
	while ( low < high && iter < 20){
		GridBin l;
		GridBin r;
		if (d == _XX){
			l = GridBin (_db, BBox(lowP.x, lowP.y, mid, highP.y ), 0 );
			r = GridBin (_db, BBox(mid, lowP.y, highP.x, highP.y), 1 );
		} else {
			l = GridBin (_db, BBox(lowP.x, lowP.y, highP.x, mid), 0);
			r = GridBin (_db, BBox(lowP.x, mid, highP.x, highP.y), 1);
		}
		for (unsigned i=0; i < _cellIndices.size(); i++)
			if ( l.contains( (*pl)[_cellIndices.at(i)] ) )
				l.addCellIdx(i);
			else if  ( r.contains( (*pl)[_cellIndices.at(i)] ) )
				r.addCellIdx (i);
			
		double lDensity = l.getCellArea() / l.getBBox().getArea();
		double rDensity = r.getCellArea() / r.getBBox().getArea();
		//cout << "\nl: " << l << " r: " << r << endl;
		//cout << "\nlDensity = " << lDensity << " rDensity: " << rDensity << endl;
		
		if ( lessOrEqualDouble (fabs(lDensity - rDensity), THRESHOLD) || 
				abs((int)(l.getCellCount() - r.getCellCount() ) < 2 ))
			return mid;
		else if ( lessThanDouble ( lDensity, rDensity) ){
			low = mid;
			mid = (low + high)/2;
		} else {
			high = mid;
			mid = (low + high)/2;
		}
		iter++;
	}

	if (d == _XX) return centerP.x;
	return centerP.y;	
}

std::pair <GridBin, GridBin> 
	GridBin::divideByCutLine (double mid, const Placement* pl, const Dir&d ) const
{
	Point lowP = _bbox.getBottomLeft();
	Point highP = _bbox.getTopRight();
	GridBin l;
	GridBin r;	
	if (d == _XX){
		l = GridBin (_db, BBox(lowP.x, lowP.y, mid, highP.y ), 0 );
		r = GridBin (_db, BBox(mid, lowP.y, highP.x, highP.y), 1 );
	} else {
		l = GridBin (_db, BBox(lowP.x, lowP.y, highP.x, mid), 0);
		r = GridBin (_db, BBox(lowP.x, mid, highP.x, highP.y), 1);
	}
	
	/* //changed this, because it produced cells not inside any of two bins
	int nOut = 0;
	for (unsigned i=0; i < _cellIndices.size(); i++)
		if ( l.contains( (*pl)[_cellIndices.at(i)] ) )
			l.addCellIdx(i);
		else if  ( r.contains( (*pl)[_cellIndices.at(i)] ) )
			r.addCellIdx (i);	
		else 
			nOut++;
		
	myWarn2 (nOut == 0, nOut, "Total cells out of both gridBins");	*/
	
	
	for (unsigned i=0; i < _cellIndices.size(); i++)
		if (d == _XX)
			if ( lessOrEqualDouble((*pl)[_cellIndices.at(i)].x, mid ))
				l.addCellIdx (_cellIndices.at(i));
			else 
				r.addCellIdx (_cellIndices.at(i));	
		else 
			if ( lessOrEqualDouble((*pl)[_cellIndices.at(i)].y, mid ))
				l.addCellIdx(_cellIndices.at(i));
			else 
				r.addCellIdx (_cellIndices.at(i));	
			
	
	return std::make_pair(l, r);
}



std::ostream&  operator<<(std::ostream& out, GridMapper& arg){
	out << "Total size of gridbins: " << arg._xSize << "*" << arg._ySize ;
 	out << " BBox: " << arg._bbox;
	/*out << " Stats: \n" ;
	for (unsigned i=0; i < arg._gridBins.size(); i++)
		out << arg._gridBins[i] << " \n";*/
	return out;
}


GridMapper::GridMapper
	(const DB* db, unsigned xs, unsigned ys, const BBox& bb, const Placement* pl)  
{
	_db = db;
	_xSize = xs;
	_ySize = ys;
	_bbox = bb;
	_pl = pl;
	
	myAssert(xs!=0 && ys!=0 , "Grid with dimension(s) zero");
		
	double xStep = bb.getWidth()*1.0 /_xSize;
	double yStep = bb.getHeight()*1.0/_ySize;
	//xStep = max (50*1.0, xStep);
	//yStep = max (120.0*1.0, yStep);
	
	
	myAssert3 ( fabs(xStep) > DBL_EPSILON && fabs(yStep) > DBL_EPSILON, " x(y) step is zero", xStep, yStep);
		
	double xOffset = _bbox.getBottomLeft().x;
	double yOffset = _bbox.getBottomLeft().y;
		
	int id = 0;	
	for (unsigned i=0; i < _xSize; i++){
		yOffset = _bbox.getBottomLeft().y;
		for (unsigned j=0; j < _ySize; j++){
			BBox curBB (xOffset, yOffset, xOffset+xStep, yOffset+yStep);
			_gridBins.push_back(GridBin(_db, curBB, id));
			yOffset += yStep;
			id++;
		}
		xOffset += xStep;
	}
	
	myAssert3 (_gridBins.size() == xs*ys, _gridBins.size(), "Total generated gridBins is not equal to xs*ys", xs*ys); 
		
		
	//cout << "All grid bins: " << _gridBins << endl;	
}


//This one starts with all the cells inside the parentGb, no matter they are 
//inside the bbox or not
GridMapper::GridMapper
	(const DB* db, unsigned depth, const GridBin& parentGb, const Placement* pl )
{
	_db = db;
	_bbox = parentGb.getBBox();
	_pl = pl;
	int t = (int) pow(2, depth);
	_ySize = (int) sqrt(t);
	_xSize = (int) t/_ySize;
	
	_gridBins = buildGBinsRecursively (depth, parentGb, pl) ;
	
}

std::vector<GridBin> GridMapper::buildGBinsRecursively
	(unsigned depth, const GridBin& parentGb, const Placement* pl )
{

	myAssert2 (depth >= 0, " invalid depth: " , depth);
	int d= 0;
	std::vector<GridBin> gBins = {parentGb};
	Placement tempPl (*pl);

	while ( d < (int)depth ){
		std::cout << "\n\nDepth: " << d << std::endl;
		auto tempBins = gBins;
		gBins.clear();
		Dir dir = (d % 2) ? _YY : _XX;		
		//Dir revDir = ( dir == _XX) ? _YY: _XX;
		for (unsigned i=0; i < tempBins.size(); i++){
			auto curBin = tempBins.at(i);
			//curBin. legalizeBin (&tempPl, revDir);
			
			std::cout << "curBin: " << curBin << std::endl;
			double mid = curBin.getCellCountMedian( &tempPl, dir);
			auto lrBins = curBin.divideByCutLine(mid, &tempPl, dir);
			GridMapper dummy ( _db, 2, 1, curBin.getBBox(), &tempPl);
			if (dir == _YY)
				dummy = GridMapper( _db, 1, 2, curBin.getBBox(), &tempPl);
			
			lrBins.first.setBBox( dummy. getGridBins().at(0).getBBox() );
			lrBins.second.setBBox( dummy. getGridBins().at(1).getBBox() );	
			std::cout << "dir: " << dir <<" median = " << mid << " resultant gBins: " << lrBins << std::endl;

			gBins.push_back (lrBins.first); 
			gBins.push_back (lrBins.second);
		}
		
		d ++;
	}

	for (unsigned i=0; i < gBins.size(); i++)
		gBins.at(i).setID(i);
	
	
	return gBins;
}


GridMapper::GridMapper
	(const DB* db, unsigned depth, const BBox& bb, const Placement* pl)
{
	_db = db;
	_bbox = bb;
	_pl = pl;
	
	int t = (int) pow(2, depth);
	_ySize = (int) sqrt(t);
	_xSize = (int) t/_ySize;
	
	myAssert2 (depth >= 0, " invalid depth: " , depth);
	
	GridBin baseBin (_db, bb, (*pl), 0);
	GridMapper gm (db, 1, 1, bb, pl);	
	baseBin. addCellIdx ( gm.getGridBins().at(0).getCellIndices() );
	
	_gridBins = buildGBinsRecursively (depth, baseBin, pl) ;

	
	/*for (int i=0; i < (*_pl).getSize(); i++){
		for (unsigned j=0; j < _gridBins.size(); j++){
			if ( _gridBins.at(j).contains( (*_pl)[i] ) ){
				_gridBins.at(j).addCellIdx (i);
				break;
			}
		
		}		
	}*/
	
}  


//skips fixed cells
void GridMapper::snapCellsToGrids() {
	
	//std::cout << "Original Box: " << _bbox << std::endl;
	double xStep = _bbox.getWidth()*1.0 /_xSize;
	double yStep = _bbox.getHeight()*1.0/_ySize;
	
	//xStep = max (50*1.0, xStep);
	//yStep = max (120.0*1.0, yStep);
	
	for (int i=0; i < (*_pl).getSize(); i++){
		if ((*_db).getNetlist().getCellByIdx(i).isFixed()){
			//std::cout << "Skipping from snapping cell (fixed)" << (*_db).getNetlist().getCellByIdx(i) << "\n";
			continue;
		} 
		Point curLoc = (*_db).getNetlist().getCellByIdx(i).getCenter((*_pl)[i]);
		
		if (! _bbox.contains(curLoc) ){
			
			if ( _bbox.contains( (*_pl)[i] ) ){
				curLoc = (*_pl)[i] ;
			} else {
			 //myWarn3 ( 0, i, " is out of original bbox ", curLoc);
			 //if it's not in the original bb
			 //just put it in the last idx
			//int xIdx = _xSize-1;
		    //int yIdx = _ySize-1;
		    //int idx = xIdx * _ySize + yIdx;
			//gridBins[idx].addCellIdx(i);
				continue;				
			}
			
		}
		
		int xIdx =  std::max(0, (int)floor(( curLoc.x - _bbox.getBottomLeft().x ) / xStep)) ;
		int yIdx =  std::max(0, (int)floor(( curLoc.y - _bbox.getBottomLeft().y) / yStep));
		
		xIdx = std::min (xIdx,(int) _xSize-1);
		yIdx = std::min (yIdx,(int) _ySize-1);
		//std::cout << "xIdx: " << xIdx << " yIdx: " << yIdx << std::endl;
		int idx = xIdx * _ySize + yIdx;
		myAssert3 ( idx < int(_gridBins.size()) && idx >= 0, idx , " genereated idx is out of bounds ", _gridBins.size() );
		
		myAssert3 (_gridBins[idx].contains( curLoc ), curLoc , " is snapped to this grid incorrectly ", _gridBins[idx].getBBox() );
		
		myAssert3 (int(_gridBins[idx].getID()) == idx , idx, " chosen id for gridbin is wrong", _gridBins[idx].getID()  );
		
		_gridBins[idx].addCellIdx(i);
		
	}
	
	return;
	
}

//Iterates over all gridbins and finds if a cell is contained within that gb's bbox
//added this to support non-uniform spacing between rows
void GridMapper::snapCellsToGrids_bf() {
	
	
	for (int i=0; i < (*_pl).getSize(); i++){
		if ((*_db).getNetlist().getCellByIdx(i).isFixed()){
			//std::cout << "Skipping from snapping cell (fixed)" << (*_db).getNetlist().getCellByIdx(i) << "\n";
			continue;
		} 
		Point curLoc = (*_db).getNetlist().getCellByIdx(i).getCenter((*_pl)[i]);
		
		if (! _bbox.contains(curLoc) ){
			
			if ( _bbox.contains( (*_pl)[i] ) ){
				curLoc = (*_pl)[i] ;
			} else {
			 myWarn3 ( 0, i, " is out of original bbox ", curLoc);
				continue;				
			}
			
		}
		bool foundCurCellsGB = false;
        for (unsigned bb=0; bb < _gridBins.size(); bb++)
		{
          if ( _gridBins.at(bb).contains( curLoc ) ){
           	_gridBins.at(bb).addCellIdx(i);
            foundCurCellsGB = true;			
            break;			  
		  }
		}			
		
		if (foundCurCellsGB == false)
		  myWarn3 ( 0, i, " <- cell was not snapped to any rows ", curLoc );		
	}
	
	return;
	
}



double GridMapper::getCellDensity(unsigned idx){
	myAssert (idx >=0 && idx < _gridBins.size(), " idx is out of bound of _gridBins");
		
	return  _gridBins[idx].getDensity();
	
}

GridBin GridMapper::combineGridBins (unsigned idx1, unsigned idx2) const 
{
	myAssert (idx1 >= 0 && idx1 < _gridBins.size() && idx2 >= 0 && idx2 < _gridBins.size(), "Index out of bound.");
	
	BBox bb1 = _gridBins[idx1].getBBox();
	BBox bb2 = _gridBins[idx2].getBBox();
	BBox bbf = bb1.expandToInclude ( bb2 );
	
	GridBin comb(_db, bbf, std::min(_gridBins[idx1].getID(), _gridBins[idx2].getID() )  );
	
	std::set<int> cellSet;
	auto cells1 = _gridBins[idx1].getCellIndices();
	cellSet.insert(cells1.begin(), cells1.end());
	auto cells2 = _gridBins[idx2].getCellIndices();
	cellSet.insert(cells2.begin(), cells2.end());
	
	std::vector<int> fC(cellSet.begin(), cellSet.end());
	comb.addCellIdx ( fC );
	
	
	return comb;
	
}

GridBin GridMapper::combineGridBins 
	(const GridBin& gbin1, const GridBin& gbin2) const 
{
	
	BBox bb1 = gbin1.getBBox();
	BBox bb2 = gbin1.getBBox();
	BBox bbf = bb1.expandToInclude ( bb2 );
	
	GridBin comb(_db, bbf, std::min(gbin1.getID(), gbin2.getID() )  );
	
	
	std::set<int> cellSet;
	auto cells1 = gbin1.getCellIndices();
	cellSet.insert(cells1.begin(), cells1.end());
	auto cells2 = gbin2.getCellIndices();
	cellSet.insert(cells2.begin(), cells2.end());

	std::vector<int> fC(cellSet.begin(), cellSet.end());
	comb.addCellIdx ( fC );
	
	
	return comb;
	
}


int GridMapper::getLeftGBin ( unsigned idx ) const 
{
	myAssert2 (idx >= 0 && idx < getTotalSize(), idx, " idx out of bound for gridbins");
	if ( idx < _ySize ) return -1;
	return idx - _ySize;
}

int GridMapper::getRightGBin    ( unsigned idx )  const
{
	myAssert2 (idx >= 0 && idx < getTotalSize(), idx, " idx out of bound for gridbins");
	if ( getTotalSize() - idx <= _ySize ) return -1;
	return idx + _ySize;	
}

int GridMapper::getTopGBin      ( unsigned idx )  const
{
	myAssert2 (idx >= 0 && idx < getTotalSize(), idx, " idx out of bound for gridbins");
	if (idx % _ySize == _ySize-1) return -1;
	return idx + 1;
}

int GridMapper::getBottomGBin   ( unsigned idx )  const
{
	myAssert2 (idx >= 0 && idx < getTotalSize(), idx, " idx out of bound for gridbins");
	if ( idx % _ySize  == 0 ) return -1;
	return idx - 1;	
}


GridBin GridMapper::clusterBins ( const GridBin& gb, double targetUtil ){
	
	GridBin finalGB = gb;
	double util = gb.getDensity();
	if ( lessOrEqualDouble (util, targetUtil) )
		return finalGB;
	
	std::vector<int> neighbors;
	std::queue<int> bfs;
	bfs.push(gb.getID());
	
	while ( !bfs.empty() || lessOrEqualDouble (util, targetUtil) ){
		int front = bfs.front();
		std::cout << "front is: " << front << std::endl;
		bfs.pop();
		if ( _gridBins.at(front).isTouced () )
			continue;
		else
			_gridBins.at(front).setTouched (true);
		int fId = _gridBins.at(front).getID();
		
		int lId = getLeftGBin(fId);
		if ( lId != -1 && !_gridBins.at(lId).isTouced() ) 
			bfs.push( lId );			
			
		int rId = getRightGBin(fId);
		if ( rId != -1 && !_gridBins.at(rId).isTouced() )  
			bfs.push( rId );

		int tId = getTopGBin (fId);
		if (tId != -1 && !_gridBins.at(tId).isTouced() )  
			bfs.push (tId);
		
		int bId = getBottomGBin (fId);
		if (bId != -1 && !_gridBins.at(bId).isTouced() ) 
			bfs.push (bId);
		
		finalGB = combineGridBins(finalGB, _gridBins.at(fId));
		util = finalGB.getDensity();
		std::cout << "finalGB: " << finalGB << std::endl;
		neighbors.push_back(fId);
	}
	
	return finalGB;
}

