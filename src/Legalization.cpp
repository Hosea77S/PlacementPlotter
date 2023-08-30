#include "Legalization.h"



void Legalizer::doInGridLegalization 
	(const GridBin& gb, Placement* pl, Dir dir)
{
	auto cellIndices = gb.getCellIndices();
	if (cellIndices.size() == 0) return;
	
	//cout << "cellIndices size: " << cellIndices.size() << "\n";
	
	if (dir == _XX)	
		std::sort(cellIndices.begin(), cellIndices.end(), 
			CompareCellIdsByX( *const_cast<Placement*> (pl) ));
	else 
		std::sort(cellIndices.begin(), cellIndices.end(), 
			CompareCellIdsByY( *const_cast<Placement*> (pl) ));
	
	double totalCellArea = 0.0;
	for (unsigned i=0; i < cellIndices.size(); i++){
		if ((*_db).getNetlist().getCellByIdx(cellIndices.at(i)).isFixed()) 
			continue;
		if (dir == _XX)
		totalCellArea += (*_db).getNetlist().getCellByIdx(cellIndices[i]).getWidth();
		else 
		totalCellArea += (*_db).getNetlist().getCellByIdx(cellIndices[i]).getHeight();
	}
	//cout << "Total Cell Area " << dir << " : " << totalCellArea << std::endl;
	
	double spacing = (dir == _XX) ? 
		(gb.getBBox().getWidth()  - totalCellArea) / cellIndices.size() :
		(gb.getBBox().getHeight() - totalCellArea) / cellIndices.size();
			
	//spacing = std::max ( -30.0, spacing);
	//spacing = std::min (spacing, 10.0);
	//cout << "Spacing " << dir << " : " << spacing << std::endl;
	
	
	//double avgCellSize = (*_db).getAvgCellWidth();
	double avgCellSize = totalCellArea / cellIndices.size();
	//cout << "avgCellSize: " << avgCellSize << std::endl;
	double minSp = (dir == _XX) ? -30.0: -120.0;
	int m = 1;
	if ( lessThanDouble(spacing, minSp) ){
		//want to have a min spacing of MINSPACE between cells
		int numSamePlaceCells = (dir == _XX) ? 
			(gb.getBBox().getWidth()) / 
									(MINSPACE + avgCellSize):
			(gb.getBBox().getHeight()) / 
									(MINSPACE + avgCellSize);
		if (numSamePlaceCells == 0)
			numSamePlaceCells = 1;
		int n = cellIndices.size();
		//m is the num of cells that should be placed on top of each other, so that they will fit in the grid
		m = (int)  ceil( n*1.0 / numSamePlaceCells) ;
		std::cout << "m is: " << m << " n is: " << n << " numSamePlaceCells: " << numSamePlaceCells << std::endl;
		spacing = MINSPACE;
		myAssert2 (m > 0, "calculated m is wrong: " , m)
	}
	
	double offset = (dir == _XX) ?
				gb.getBBox().getBottomLeft().x :
				gb.getBBox().getBottomLeft().y ;
				
			
	
	for (unsigned i=0; i < cellIndices.size(); i+= m){		
		for (int j=0; j < m; j++){
			if ( i+j >= cellIndices.size()) continue;
			if ((*_db).getNetlist().getCellByIdx(cellIndices.at(i+j)).isFixed()){
				//offset += spacing + (*_db).getNetlist().getCellByIdx(cellIndices.at(i)).getWidth();
				continue;
			}
			
			if (dir == _XX)
				(*pl)[cellIndices.at(i+j)].x = offset;
			else
				(*pl)[cellIndices.at(i+j)].y = offset;

			offset += 0.1;
			//cout << (*_db).getNetlist().getCellByIdx(cellIndices.at(i+j)) << " located at: " << (*pl)[cellIndices.at(i+j)] << std::endl;
		}

		if (dir == _XX){
			//myAssert3 ( offset <= gb.getBBox().getTopRight().x && offset >= gb.getBBox().getBottomLeft().x , offset, " is out of bounds of bbox ", gb.getBBox());
			offset += spacing + (*_db).getNetlist().getCellByIdx(cellIndices.at(i)).getWidth();
		} else {
			//myAssert3 ( offset <= gb.getBBox().getTopRight().y && offset >= gb.getBBox().getBottomLeft().y , offset, " is out of bounds of bbox ", gb.getBBox());		
			//offset += spacing + (*_db).getNetlist().getCellByIdx(cellIndices.at(i)).getHeight();
			offset += spacing + (*_db)._rowDefs->getRowHeight();
		}
		
	}
	
	return;
}




void Legalizer::putCellsInBound(const BBox& bb)
{
	std::cout << "\tPutting cells in the bound: Fixed total # ";
	int totalOutOfBounds = 0;
	for (unsigned i=0; i < (*_db).getNetlist().getNumCoreCells(); i++){
		Point curPlace = (*_db)._spatial.locations[i] ;
		if (!bb.contains( curPlace) ){
			if (lessThanDouble(curPlace.x, bb.getBottomLeft().x))
				(*_db)._spatial.locations[i].x = bb.getBottomLeft().x;
			else if (greaterThanDouble(curPlace.x, bb.getTopRight().x))
				(*_db)._spatial.locations[i].x = 
						bb.getTopRight().x - (*_db).getNetlist().getCellByIdx(i).getWidth();
				
			if (lessThanDouble(curPlace.y, bb.getBottomLeft().y))
				(*_db)._spatial.locations[i].y = bb.getBottomLeft().y;
			else if ( greaterThanDouble(curPlace.y, bb.getTopRight().y) )
				(*_db)._spatial.locations[i].y = 
					bb.getTopRight().y - (*_db).getNetlist().getCellByIdx(i).getHeight();
					
		}
		
		if ((*_db)._spatial.locations[i] != curPlace)
			totalOutOfBounds++;
		
	}
	std::cout << totalOutOfBounds << " / " << (*_db).getNetlist().getNumCoreCells() << " out of bound cells\n";
	
	return;
}

void Legalizer::putCellsInBoundRelative(const BBox& bb)
{
	
	double minX = DBL_MAX; double maxX = DBL_MIN;
	double minY = DBL_MAX; double maxY = DBL_MIN;
	for (unsigned i=0; i < (*_db).getNetlist().getNumCoreCells(); i++){
		Point curPlace = (*_db)._spatial.locations[i] ;		
		minX = std::min (curPlace.x, minX);
		minY = std::min (curPlace.y, minY);
		maxX = std::max (curPlace.x, maxX);
		maxY = std::max (curPlace.y, maxY);
	}
	
	double hLeftShift = bb.getBottomLeft().x - minX;
	double vBottomShift = bb.getBottomLeft().y - minY;
	double hRightShift = bb.getTopRight().x - maxX;
	double vTopShift = bb.getTopRight().y - maxY;
	
	std::cout << "\thorizShift: (" << hLeftShift << ","<< hRightShift << ") vertShift: (" << vBottomShift << "," << vTopShift << ")\n" ;
	std::cout << "\tPutting cells in the bound Relative: Fixed total # ";
	int totalOutOfBounds = 0;
	
	for (unsigned i=0; i < (*_db).getNetlist().getNumCoreCells(); i++){
		Point curPlace = (*_db)._spatial.locations[i] ;
		if (!bb.contains( curPlace) ){
			if (lessThanDouble(curPlace.x, bb.getBottomLeft().x))
				(*_db)._spatial.locations[i].x += hLeftShift;
			else if (greaterThanDouble(curPlace.x, bb.getTopRight().x))
				(*_db)._spatial.locations[i].x += 
						hRightShift - (*_db).getNetlist().getCellByIdx(i).getWidth();
				
			if (lessThanDouble(curPlace.y, bb.getBottomLeft().y))
				(*_db)._spatial.locations[i].y += vBottomShift;
			else if ( greaterThanDouble(curPlace.y, bb.getTopRight().y) )
				(*_db)._spatial.locations[i].y += 
					vTopShift - (*_db).getNetlist().getCellByIdx(i).getHeight();
					
		}
		
		if ((*_db)._spatial.locations[i] != curPlace)
			totalOutOfBounds++;
		
	}
	std::cout << totalOutOfBounds << " / " << (*_db).getNetlist().getNumCoreCells() << " out of bound cells\n";
	
	return;
}


std::vector<dbRow>  Legalizer::snapCellsToRows
	(Placement* pl, const BBox& bb)
{
	double ySize = (int) ceil( 
		bb.getHeight()/
			(*_db)._rowDefs->getRowHeight()
			);
	return snapCellsToRows (pl, bb, ySize);
}

//skips from snapping pads
//ySize is the num of horizontal bins created
std::vector<dbRow>  Legalizer::snapCellsToRows
	(Placement* pl, const BBox& bb, double ySize)
{
	//BBox bb = (*_db)._rowDefs->getChipBbox();
	//double ySize = (int) ceil( 
	//	bb.getHeight()/
	//		(*_db)._rowDefs->getRowHeight()
	//		);
	
	std::cout << "\t\tCreating " << ySize << " horizontal bins for legalizing\n";
	GridMapper gm = GridMapper(_db, 1, ySize, bb, pl);		
	gm.snapCellsToGrids();	
	auto cIndices = gm.getGridBins();
	
	std::vector<dbRow> rows;
	unsigned totNodes = 0;
	for (unsigned i=0; i < cIndices.size(); i++){
		
		dbRow cur ( i, cIndices.at(i).getBBox(), cIndices.at(i).getCellIndices() );
		totNodes += cur.getCellIndices().size();
		
		rows.push_back(cur);
	}
	
	myWarn3 ( totNodes == (*_db).getNetlist().getNumCoreCells(),  (*_db).getNetlist().getNumCoreCells()-totNodes, 
	   " cells are not snapped to rows ",
 	    (*_db).getNetlist().getNumCoreCells()); 
	
	
	return rows;
}


//skips from snapping pads
//ySize is the num of horizontal bins created
std::vector<dbRow>  Legalizer::snapCellsToRows
	(Placement* pl, const BBox& bb, const std::vector<double>& yHeights)
{
	
    int ySize = yHeights.size();	
    int numRows =  (*_db)._rowDefs->getRowCnt(); 
    myAssert3 ( ySize == numRows, ySize, " <- ySize != numRows -> ", numRows )	;
	std::cout << "\t\tCreating " << ySize << " horizontal bins for legalizing\n";
	
    std::vector<GridBin> gb;	
	double yOffset = bb.getBottomLeft().y;
	double xOffset = bb.getBottomLeft().x;
    double xEnd = bb.getTopRight().x;    	
    for (int i=0; i < numRows; i++)
	{
        double yStep = 	yHeights.at(i);	
		BBox curBB (xOffset, yOffset, xEnd, yOffset+yStep );
		gb.push_back( GridBin(_db, curBB, i) );
		yOffset += yStep;		
	}		

	
	
	GridMapper gm = GridMapper(_db, 1, ySize, bb, pl, gb);		
	gm.snapCellsToGrids_bf();	
	auto cIndices = gm.getGridBins();
	
	
	std::vector<dbRow> rows;
	unsigned totNodes = 0;
	for (unsigned i=0; i < cIndices.size(); i++){
		
		dbRow cur ( i, cIndices.at(i).getBBox(), cIndices.at(i).getCellIndices() );
		totNodes += cur.getCellIndices().size();
		
		rows.push_back(cur);
	}

	std::cout << "GridMapper:: Non-uniform height rows: " <<
    rows << "\n\n";	

	
	myWarn3 ( totNodes == (*_db).getNetlist().getNumCoreCells(),  (*_db).getNetlist().getNumCoreCells()-totNodes, 
	   " cells are not snapped to rows ",
 	    (*_db).getNetlist().getNumCoreCells()); 
	
	
	return rows;
}

//adds vertical space between rows
//changes the chip bbox
void Legalizer::addVerticalSpace
	(Placement* pl, BBox& bb, double sp) 
{
	std::cout << "\n\tAdding vertical space of " << sp << "\n";
	myAssert2 ( greaterThanDouble (sp, 0.0), sp, " is not greater than 0.0" );
	auto rowVecs = snapCellsToRows (pl, bb);
	auto spacings = std::vector<double> (rowVecs.size(), sp);
    addVerticalSpace(pl, bb, spacings);	
}

//adds vertical space between rows
//changes the chip bbox
void Legalizer::addVerticalSpace
	(Placement* pl, BBox& bb, std::vector<double>& sp) 
{

	auto rowVecs = snapCellsToRows (pl, bb);
	

	//auto bb = (*_db)._rowDefs->getChipBbox();
	double yOffset = bb.getBottomLeft().y ;
	double rowHeight = (*_db)._rowDefs->getRowHeight();
	
	//skipping shifting first row, cuz we don't need it :)
	for (unsigned i=0; i < rowVecs.size(); i++){
  	  auto curRow = rowVecs.at(i);
	  shiftCellsInRowVertically ( pl, curRow, yOffset, rowHeight );
	  yOffset = yOffset + rowHeight + sp.at(i); 
		
	}
	
	//reseting chip bbox
	double finalY = yOffset;
	(*_db)._rowDefs->setChipBBox ( BBox( bb.getBottomLeft().x,
									bb.getBottomLeft().y,
									  bb.getTopRight().x,
									  finalY));
    std::cout << "New chip BBox: " << (*_db)._rowDefs->getChipBbox() << "\n";
									  
	return;
}

void Legalizer::groupAndShift
  ( Placement* pl, BBox& bb, 
  unsigned gSize, double horizSpace, double vertSpace)
{
	auto rowVecs = snapCellsToRows (pl, bb);
	auto spacings = std::vector<double> (rowVecs.size(), vertSpace);
    groupAndShift(pl, bb, gSize, horizSpace, spacings);	
}

// Groups the cells based on their initial location, and not based on level
void Legalizer::groupAndShift
  ( Placement* pl, BBox& bb, 
  unsigned gSize, double horizSpace, std::vector<double>& vertSpace)
{
	
  std::cout << "\n\tAdding horizontal space of " << horizSpace << " between cell groups of size"<< gSize <<"\n";
  auto rowVecs = snapCellsToRows (pl, bb);
  double maxX = 0;
  for (unsigned i=0; i < rowVecs.size(); i++){
  	auto curRow = rowVecs.at(i);
  	auto curCells = curRow.getCellIndices();
	std::sort(curCells.begin(), curCells.end(),
		CompareCellIdsByX( *const_cast<Placement*> (pl) ));
	
  	double x_offset = bb.getBottomLeft().x;
  	for (unsigned j=0; j < curCells.size(); j+= gSize)
  	{
  	  for (unsigned k=0; k < gSize; k++)
  	  {
		if (k+j >= curCells.size()) continue;  
		(*pl)[ curCells.at ( k + j ) ].x = x_offset;
		x_offset += (*_db).getNetlist().getCellByIdx ( curCells.at ( k + j ) ).getWidth();
  	  	
  	  }			
	  x_offset += horizSpace;
  	}
	
	maxX = std::max (maxX, x_offset);
  	
  }

  //changing chip bbox
  BBox finalBB ( bb.getBottomLeft().x,
		bb.getBottomLeft().y,
		maxX,
		bb.getTopRight().y );  
  (*_db)._rowDefs->setChipBBox ( finalBB );		
  
  std::cout << "\n\n\tAfter adding horizontal space: " << finalBB << "\n";
  
  //shifting cells vertically to make place for clk splitters  
  addVerticalSpace(pl, finalBB, vertSpace);
	
  return;
}

//added for improving routability 
//first adds linear space between all rows
//then adds extra space between rows in the middle of the chip
//which are heavily congested
void Legalizer::addNonLinSpace
	(Placement* pl, BBox& bb, 
	  double xSpace, double ySpace, double rowHeight) 
{  	
  std::cout << "\n\tAdding Non Linear vertical space of " << ySpace << " and horizontal space of " << xSpace << "\n";
  myAssert2 ( greaterThanDouble (ySpace, 0.0), ySpace, " is not greater than 0.0" );
  myAssert2 ( greaterThanDouble (xSpace, 0.0), xSpace, " is not greater than 0.0" );
  myAssert2 ( greaterThanDouble (rowHeight, 0.0), rowHeight, " is not greater than 0.0" );
  
  double numOfHBins = (int) ceil( 
		bb.getHeight()/
			rowHeight );
  
  auto rowVecs = snapCellsToRows (pl, bb, numOfHBins);
  unsigned numRows = rowVecs.size();
  
  int numRowsToChange = (int) ceil( NON_LIN_PERC * numRows );
  std::cout << "\n\tOnly changing " << numRowsToChange << " rows in the middle of chip area" << std::endl;	
  
  int stIdx = (int)((numRows / 2.0) - (numRowsToChange / 2.0));
  int endIdx = stIdx + numRowsToChange;
  
  std::cout << "\n\tChaning rows [" << stIdx << "," << endIdx << ")\n";
  
  myAssert3 ( stIdx >= 0 && stIdx < (int)numRows, stIdx, " is out of num of rows: ", numRows);
  myAssert3 ( endIdx >= 0 && endIdx < (int)numRows, endIdx, " is out of num of rows: ", numRows);
  myAssert3 ( endIdx > stIdx, endIdx, " is not > stIdx: ",stIdx);
  
  double yOffset;
  if (stIdx == 0)
    yOffset = bb.getBottomLeft().y ;
  else 
    yOffset = rowVecs.at(stIdx-1).getBBox().getBottomLeft().y + rowHeight + ySpace;
  
  //shifting cells between stIdx and endIdx by ySpace
  for (int i=stIdx; i < endIdx; i++){
    auto curRow = rowVecs.at(i);
    
	shiftCellsInRowVertically ( pl, curRow, yOffset, rowHeight + ySpace );
    yOffset = yOffset + rowHeight + ySpace; 
    //std::cout << "row " << i << " yOffset = " << yOffset << std::endl;
	
	shiftCellsInRowHorizontally (pl, curRow, xSpace);
	  	
  }
  
  //shifting up cells between endIdx and total row size by 
  // (endIdx - stIdx) * sp
  for (int i=endIdx; i < (int) numRows; i++){
    auto curRow = rowVecs.at(i); 
	if (curRow.getNumCells() == 0 ) continue;
	
	shiftCellsInRowVertically ( pl, curRow, yOffset, rowHeight );
    yOffset += rowHeight;   	
    //std::cout << "row " << i << " yOffset = " << yOffset << std::endl;	
  }
    
  
  //reseting chip bbox
  //double finalY = yOffset + 4*PAD_HEIGHT;
  //(*_db)._rowDefs->setChipBBox ( BBox( bb.getBottomLeft().x,
  //								bb.getBottomLeft().y,
  //								  bb.getTopRight().x,
  //								  finalY));
  //   std::cout << "New chip BBox: " << (*_db)._rowDefs->getChipBbox() << "\n";
  								  
  return;
  	
}	

void Legalizer::shiftCellsInRowHorizontally
	(Placement* pl, dbRow& curRow, double xSpace)
{
  unsigned numCells = curRow.getNumCells();
  if (numCells == 0) return;
  
  int numCellsToShift = (int) ceil( NON_LIN_PERC * numCells );
  int f = (int)((numCells / 2.0) - (numCellsToShift / 2.0));
  int l = f + numCellsToShift;
  std::cout << "\n\tChaning cells [" << f << "," << l << ")  horiz within row" << curRow.getIndex() << "\n";
  myAssert3 ( f >= 0 && f < (int)numCells, f, " is out of num of rows: ", numCells);
  myAssert3 ( l >= 0 && l < (int)numCells, l, " is out of num of rows: ", numCells);
  myAssert3 ( l > f, l, " is not > stIdx: ",f);
 
	
  auto curCells = curRow.getCellIndices();
  std::sort (curCells.begin(), curCells.end(), CompareCellIdsByX(*const_cast<Placement*> (pl)) );
  double xOffset = (*pl)[ curCells.at(f) ].x;
  for ( int j=f; j < l; j++ )
  {
    double prevXOffset = 	(*pl)[ curCells.at (j) ].x;
    (*pl)[ curCells.at (j) ].x = xOffset;
    //cout << j << " : " << xOffset << endl;
    xOffset += (*pl)[ curCells.at ( j + 1) ].x - prevXOffset + xSpace;
  }
  //xOffset += 2 * xSpace;
  
  for ( int j=l; j < (int) numCells-1; j++ )
  {
    double prevXOffset = 	(*pl)[ curCells.at (j) ].x;
    (*pl)[ curCells.at (j) ].x = xOffset;
    //cout << j << " : " << xOffset << endl;	  
    xOffset += (*pl)[ curCells.at ( j + 1) ].x - prevXOffset;		
  }	(*pl)[ curCells.back() ].x = xOffset + xSpace;

  return;  
}


void Legalizer::shiftCellsInRowVertically
	(Placement* pl, dbRow& curRow, double yOffset, double rowHeight)
{
  double originalRowHeight = (*_db)._rowDefs->getRowHeight();
  auto curCells = curRow.getCellIndices();
  curRow.setBBox ( BBox (
    curRow.getBBox().getBottomLeft().x, 
      yOffset, 
  	  curRow.getBBox().getTopRight().x,  
  	    yOffset + rowHeight ));
  
  for (unsigned j=0; j < curCells.size(); j++){
  	if ( (*_db).getNetlist().getCellByIdx( curCells.at(j)).isFixed())
  	 continue;
    	
    (*pl)[ curCells.at(j) ].y = yOffset;
	  
	if ( (*_db).getNetlist().getCellByIdx ( curCells.at(j) ).isClkSpl() )
      //(*pl)[ curCells.at(j) ].y = yOffset - (*_db).getNetlist().getCellByIdx ( curCells.at(j) ).getHeight() ;
      (*pl)[ curCells.at(j) ].y = yOffset + originalRowHeight;
		
		   
  	
  }

  return;	
}
	


void Legalizer::doFinalPadPl()
{
	double maxX = DBL_MIN ;
	double maxY = DBL_MIN;
	
	BBox bb = (*_db)._rowDefs->getChipBbox();
	for (unsigned i=0; i < (*_db).getNetlist().getNumCells(); 
			i++ )
	{
		if ( (*_db).getNetlist().getCellByIdx(i).isFixed() ) continue;
		double x = (*_db)._spatial.locations[i].x + 
			(*_db).getNetlist().getCellByIdx(i).getWidth();
		double y = (*_db)._spatial.locations[i].y + 
			(*_db).getNetlist().getCellByIdx(i).getHeight();
		
		if ( greaterOrEqualDouble(x , bb.getTopRight().x ) )
			maxX = std::max (maxX, x) ;
		if ( greaterOrEqualDouble(y , bb.getTopRight().y ) )
			maxY = std::max (maxY, y) ;
	}
	
	//maxX -= bb.getBottomLeft().x;
	
	if ( greaterOrEqualDouble(maxX, bb.getTopRight().x)
		 || greaterOrEqualDouble(maxY, bb.getTopRight().y) )
	{
	    std::cout << "\tNew maxX is : " << maxX << std::endl;
	    std::cout << "\tNew maxY is : " << maxY << std::endl;
		
		maxX = std::max ( maxX, bb.getTopRight().x);
		maxY = std::max ( maxY, bb.getTopRight().y);
		
		BBox finalBB ( bb.getBottomLeft().x,
				bb.getBottomLeft().y,
				maxX,
				maxY );
		
		(*_db)._rowDefs->setChipBBox  ( finalBB );		
	}
	
	Placement fP( (*_db)._spatial.locations );
	padPl pp(_db, &fP );
	pp.reOrderPads( Point (-4*Constants::PAD_HEIGHT, -4*Constants::PAD_HEIGHT) );
	(*_db)._spatial.locations = fP;
	
	return;
}

//Legalizes cells by checking if each 2 cell overlap, sorts overlapping cells, and shifts them to remove overlap
/* void Legalizer::legalizeCellsInPlace
  (const GridBin& gb, Placement* pl, double xMovement, Dir d)
{
  auto cellIndices = gb.getCellIndices();
  if (cellIndices.size() == 0) return;
  
  std::sort(
  	cellIndices.begin(), 
  	cellIndices.end(), 			
   CompareCellIdsByX( *const_cast<Placement*> (pl) ));
  
  for (unsigned i=1; i < cellIndices.size()-2; i++)
  {		 
    unsigned idx = cellIndices.at(i);
	unsigned prevIdx = cellIndices.at(i-1);
	
  	double curXStart = (*pl)[ idx ].x ;
	double curXEnd = curXStart + (*_db).getNetlist().getCellByIdx( idx ).getWidth();
  	double nextX = (*pl) [ cellIndices.at(i+1)  ] .x;
	double prevX = (*pl) [ prevIdx  ] .x + 
	  (*pl)[ prevIdx ].x + (*_db).getNetlist().getCellByIdx( prevIdx ).getWidth();
	
	if (greaterOrEqualDouble( curXStart, prevX ))
	{//doesn't have overlap with prev, check overlap with next
	  if ( lessOrEqualDouble(curXEnd, nextX) ) //no ovelap
		continue;
	  //otherwise, consider moving this cell to left, or next to right
	  unsigned nextNextIdx = cellIndices.at(i+2);
	  unsigned nextIdx = cellIndices.at(i+1);
	  double nextNextX = (*pl) [ nextNextIdx ] .x ;
	  double nextEndX = nextX + (*pl)[ nextIdx ].x + (*_db).getNetlist().getCellByIdx( nextIdx ).getWidth();
	  if ( greaterThanDouble(nextEndX, nextNextX) )
	  {//has overlap with next cell, shift curCell to left
		(*pl) [ idx  ] .x = prevX + xMovement;  
		continue;
	  }		  
	  
	  double overlap = nextX - curXEnd;
	  //next cell has room to move right
	  double sol1Cost = DBL_MAX, sol2Cost = DBL_MAX;
	  //one solution is to shift cell i+1 to right
	  sol1Cost = curXEnd + xMovement - (*pl) [ nextIdx  ].x;
	  
	  //another is to shift cell i to left
	  sol2Cost = curXStart - overlap - xMovement;
	  
	  if ( greaterOrEqualDouble(sol2Cost, sol1Cost) )
		(*pl) [ idx  ] .x = curXEnd + xMovement;
	  else 
		(*pl) [ idx  ] .x = curXStart - overlap - xMovement;
	  
	} else
	{ //has overlap with previous, can't do anything
	  (*pl) [ idx  ] .x = prevX	+ xMovement;
	  continue;
	}
		
  	//if ( lessOrEqualDouble(curX, nextX) )
  	//{
    //  //std::cout << "\t\tChaning loc of clkSpl " << cellIndices.at(i+1) << " from " << (*pl) [ cellIndices.at(i+1)  ] .x << " to " ;
	//  
	//  double sol1Cost = DBL_MAX, sol2Cost = DBL_MAX;
	//  //one solution is to shift cell i+1 to right
	//  sol1Cost = curX + xMovement - (*pl) [ cellIndices.at(i+1)  ].x;
	//  
	//  //another is to shift cell i to left
	//  sol2Cost = (*pl) [ cellIndices.at(i+1)  ].x - prevX - xMovement;
	//  
	//  if ( greaterOrEqualDouble(sol2Cost, sol1Cost) )
	//	(*pl) [ cellIndices.at(i+1)  ] .x = curX + xMovement;
	//  else 
	//	(*pl) [ cellIndices.at(i+1)  ] .x = prevX + xMovement;
	//	  
	//  //std::cout << curX + PITCH << " \n";
  	//} 
  }
  
  auto cellAfter = cellIndices;
  std::sort(
  	cellIndices.begin(), 
  	cellIndices.end(), 			
   CompareCellIdsByX( *const_cast<Placement*> (pl) ));

  for (unsigned i=0; i < cellAfter.size(); i++)
    myAssert3( cellAfter.at(i) == cellIndices.at(i),  
		cellAfter.at(i), 
		" not equal to before sort: ", 
		cellIndices.at(i));	  
	
	return ;
} */


//Legalizes cells by checking if each 2 cell overlap, sorts overlapping cells, and shifts them to remove overlap
void Legalizer::legalizeCellsInPlace
  (const GridBin& gb, Placement* pl, double xMovement, Dir d)
{
  auto cellIndices = gb.getCellIndices();
  if (cellIndices.size() == 0) return;
  
  std::sort(
  	cellIndices.begin(), 
  	cellIndices.end(), 			
   CompareCellIdsByX( *const_cast<Placement*> (pl) ));
   
  int cnt = 0; 
  for (unsigned i=0; i < cellIndices.size()-1; i++)
  {		 
    unsigned idx = cellIndices.at(i);
	unsigned nextIdx = cellIndices.at(i+1);
  	double curXStart = (*pl)[ idx ].x ;
	double curXEnd = curXStart + (*_db).getNetlist().getCellByIdx( idx ).getWidth();	
  	double nextX = (*pl) [ nextIdx  ] .x;
	
	if (i == 0 ) 
	{
	  if (greaterOrEqualDouble(curXEnd, nextX) )
	    (*pl) [nextIdx] .x = 	curXEnd + xMovement;
	  continue;
	}	
	
	unsigned prevIdx = cellIndices.at(i-1);
	double prevXEnd = (*pl) [ prevIdx  ] .x +
	 (*_db).getNetlist().getCellByIdx( prevIdx ).getWidth();



	 
  	if ( greaterOrEqualDouble(curXEnd, nextX) )
  	{
	  //double overlap = 	curXEnd - nextX;
      //std::cout << "\t\tChaning loc of cell " << nextIdx << " from " << (*pl) [ nextIdx  ] << " to " ; 
	  
/* 	  if (cnt % 2) //to toggle between moving gate to right or left, commented on 07.03.2019
	  {
		if ( greaterOrEqualDouble((curXStart - overlap - xMovement), prevXEnd) )  
		{ //can move cell i to left
		  cnt++;
		  (*pl) [idx] .x = curXStart - overlap - xMovement;
		  continue;
		}
	  } */
	  //or move next cell to right
  	  (*pl) [ nextIdx  ] .x = curXEnd + xMovement;
	  
	  //std::cout << (*pl) [ nextIdx  ] << " \n";
  	} 
  }
  
/*   auto cellAfter = cellIndices;
  std::sort(
  	cellIndices.begin(), 
  	cellIndices.end(), 			
   CompareCellIdsByX( *const_cast<Placement*> (pl) ));

  for (unsigned i=0; i < cellAfter.size(); i++)
    myAssert3( cellAfter.at(i) == cellIndices.at(i),  
		cellAfter.at(i), 
		" not equal to before sort: ", 
		cellIndices.at(i)); */	  
	
	return ;
}

void Legalizer::doLazyLegY 
  (const GridBin& gb, Placement* pl, double alphaRatio)
{
	auto cellIndices = gb.getCellIndices();
	std::sort(cellIndices.begin(), cellIndices.end(), 
		CompareCellIdsByY( *const_cast<Placement*> (pl) ));
		
	int numRows = (*_db)._rowDefs->getRowCnt();
    //double rowHeight = (int) ceil(
	//	(*_db)._rowDefs->getChipHeight() / numRows );	
	double rowHeight = (*_db)._rowDefs->getRowHeight();
	
	
	int cellPerRow = (int) (ceil (cellIndices.size() / numRows) );
	
	/*std::cout << "\n\n\tLazyLegY: cpr = " << cellPerRow << 
	" total cells = " << cellIndices.size() << 
	" rowHeight: " << rowHeight 
	<< " \n" ;*/
	double yOffset = gb.getBBox().getBottomLeft().y;
	int idx = 0;
	
	for (unsigned i=0; i < cellIndices.size(); i++)
	{
		unsigned curIdx = cellIndices.at(i);
		if ( (*_db).getNetlist().getCellByIdx( curIdx ).isFixed())
		   continue;
	   
		if (idx < cellPerRow){
			idx ++ ;
		}
		else {
			idx = 0;			
			yOffset += alphaRatio * rowHeight;
		}
		(*pl)[curIdx].y = yOffset;
	}

	return;	
}
	
void Legalizer::doLazyLegX 
  (const GridBin& gb, Placement* pl, double alphaRatio)
{
  double avgCellWidth = (*_db).getAvgCellWidth();
  int numRows = (*_db)._rowDefs->getRowCnt();  
  //double rowHeight = (int) ceil(
	//(*_db)._rowDefs->getChipHeight() / numRows );	
	
	
  auto bb = gb.getBBox();
  auto rowVecs = snapCellsToRows ( pl, bb, numRows );
  
  for (unsigned i=0; i < rowVecs.size(); i++){
  	auto curRow = rowVecs.at(i);

  	auto curCells = curRow.getCellIndices();
	if (curCells.size() == 0) continue;
	
	std::sort(curCells.begin(), curCells.end(), 
		CompareCellIdsByX( *const_cast<Placement*> (pl) ));
	
	
  	double xOffset = bb.getBottomLeft().x ;
	double xSpacing = (int) ceil((
		(*_db)._rowDefs->getChipWidth() -
		  (avgCellWidth * (int) curCells.size() )) 
		/ curCells.size());
		
	/*std::cout << "\n\t\tRow: " << i << " xSpacing = " << xSpacing
	<< " numCells: " << curCells.size() << "\n";*/

	
	xSpacing = std::max (xSpacing, 0.0) + avgCellWidth ;
	//xSpacing =  avgCellWidth ; //when utilization is low, this works better
	myAssert2 ( greaterThanDouble ( xSpacing, 0.0), xSpacing, " is not > 0.0 " );
	
	for (unsigned j=0; j < curCells.size(); j++)
	{
	  auto curIdx = curCells.at(j);
	  if ( (*_db).getNetlist().getCellByIdx( curIdx ).isFixed()) 
		continue;
	  (*pl)[curIdx]. x = xOffset;
	  xOffset += (alphaRatio * xSpacing) ;
	}
	
	
  }	
}  


void Legalizer::doLazyLeg
  (const GridBin& gb, Placement* pl, 
    double alHoriz, double alVert)
{
	doLazyLegY(gb, pl, alVert);
	doLazyLegX(gb, pl, alHoriz);
	return;
}




	
	
/**



void Legalizer::doHorizontalLegal(bool DoAccurateLegalization, double alphaRatio){
	if (!DoAccurateLegalization){
		auto rowVec = findRowVec();
		double rowHeight = chip->rowDef->stdRows[0].height;
		int avgCellWidth = int(chip->CalculateTotalCellArea() / rowHeight / chip->numOfNonTerminalNodes());
		for (int i=0; i < int(rowVec.size()); i++){
			if (rowVec[i].size() == 0) continue;
			int x_offset = int(chip->x_offset * (1.0 / alphaRatio));
			int xSpacing = max(0, int(int(chip->chip_width - (avgCellWidth * int(rowVec[i].size()))) / int(rowVec[i].size()))) + avgCellWidth;
			assert(xSpacing > 0);
			//cout << "Cellsper row : " << i << " is : " << rowVec[i].size() << " xSpacing : " << xSpacing << std::endl;
			for (int j=0; j < int (rowVec[i].size()); j++){
				if (rowVec[i][j]->pad) continue;
				rowVec[i][j]->x = x_offset;
				x_offset += int(alphaRatio * xSpacing) ;
			}
		}
		
	}
	return;
}	

void Legalizer::doVerticalLegal(bool DoAccurateLegalization, double alphaRatio){
	if (!DoAccurateLegalization){
		vector<Cell* > ySortedCellList (this->chip->cellList);
		sort(ySortedCellList.begin(), ySortedCellList.end(), compare_cell_y);

		int numOfRows = chip->rowDef->stdRows.size();
		double rowHeight = chip->rowDef->stdRows[0].height;

		//vector< vector< Cell* >> rowVec(numOfRows);
		int cellPerRow = int(chip->numOfNonTerminalNodes() / numOfRows) + 1;
		int index = 0;
		int height_offset = int(chip->y_offset * (1.0 / alphaRatio));
		for (int i=0; i < int(ySortedCellList.size()); i++){
			if (ySortedCellList[i]->pad) continue;
			if (index < cellPerRow){
				index ++ ;
			}
			else {
				index = 0;			
				height_offset += int(alphaRatio * rowHeight);
			}
			ySortedCellList[i]->y = height_offset;
		}
		//cout << "cellPerRow is : " << cellPerRow << std::endl;
		//for (int i=0; i < int(ySortedCellList.size()); i++){
		//	cout << "name " << ySortedCellList[i]->name << " y: " << ySortedCellList[i]->y << std::endl;
		//}	
		
	}
	return ;
}

void Legalizer::doLazyLegal(bool DoAccurateLegalization, double alphaRatio_vert, double alphaRatio_horiz){
	this->doVerticalLegal(DoAccurateLegalization, alphaRatio_vert);
	this->doHorizontalLegal(DoAccurateLegalization, alphaRatio_horiz);
	return;
}





**/	
	
