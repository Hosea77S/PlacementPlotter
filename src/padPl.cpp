#include "padPl.h"


void padPl::reOrderPads(Point base)
{

	unsigned padCnt = (*_db).getNetlist().getNumAllPads();
	
	myAssert2 (padCnt > 0, padCnt, " padCnt is <= 0");
	
	std::cout << "\n\n******************************************\n";
	std::cout << "\n\t\t Reordering Pads\n\n";
	
	BBox layout = (*_db)._rowDefs->getChipBbox();
	BBox newLayout ( layout.getBottomLeft().x + base.x,
					 layout.getBottomLeft().y + base.y, 
	                 layout.getTopRight().x + base.x,
	                 layout.getTopRight().y + base.y
					 );
	layout = newLayout;				 
	std::cout << "Layout: " << layout << std::endl;

        double chipWidth, chipHeight, chipPerim;
        chipWidth = layout.getWidth();
        chipHeight = layout.getHeight();
        chipPerim = 2 * (chipWidth + chipHeight);

        int termsOnTop, termsOnBottom, termsOnLeft, termsOnRight;
	if ( equalDouble(Constants::PAD_WIDTH, Constants::PAD_HEIGHT) )
          termsOnTop = termsOnBottom = (int) ceil(padCnt * (chipWidth/chipPerim));
	else
          termsOnTop = termsOnBottom = (int) ceil(padCnt * (Constants::PAD_HEIGHT/Constants::PAD_WIDTH)* (chipWidth/chipPerim));
          //termsOnTop = termsOnBottom = (int) ceil(chipWidth/) /
			//(1.+Constants::PAD_HEIGHT-Constants::PAD_WIDTH) );
        //termsOnTop = termsOnBottom = (int) ceil(chipWidth/( Constants::PAD_WIDTH + (chipPerim/(padCnt+1))));
        int lrTerms = padCnt - termsOnTop - termsOnBottom;
        termsOnRight = (int) ceil(lrTerms/2.0);
        termsOnLeft = lrTerms - termsOnRight;

        int sumTerms = termsOnTop + termsOnBottom + termsOnLeft + termsOnRight;
        myAssert3(sumTerms == (int)padCnt, 
 		sumTerms, "\tMismatch between # terminals, #Total != padCnt\t", padCnt);

	std::cout << "No. Pads: " << padCnt << "\n";
	std::cout << " No. Pads on top: " << termsOnTop << "\n";
	std::cout << " No. Pads on right: " << termsOnRight << "\n";
	std::cout << " No. Pads on bottom: " << termsOnBottom << "\n";
	std::cout << " No. Pads on left: " << termsOnLeft << "\n";
	
	

	//int padPerSideCnt = (int) (padCnt /4) + 1;
	//int padPerSideCnt = (int) std::ceil(padCnt /4);
	//std::cout << "No. Pads: " << padCnt << 
	//			" No. Pads per Side: " << padPerSideCnt << "\n";

//	double rowHeight = (*_db)._rowDefs->getRowHeight();
//	int LL_x = layout.xMin;  
//int LL_y = layout.yMin;
//int UL_x = layout.xMin;  
//int UL_y = layout.yMax + Constants::PAD_OFFSET + Constants::PAD_HEIGHT; // So that splitters could fit in chip area
//int LR_y = layout.yMin - Constants::PAD_OFFSET - Constants::PAD_HEIGHT;
//int UR_x = layout.xMax + Constants::PAD_OFFSET + Constants::PAD_HEIGHT; // So that splitters could fit in chip area  
//int UR_y = layout.yMax;
//				
 	int LL_x = layout.getBottomLeft().x + Constants::PAD_HEIGHT;  
	int LL_y = layout.getBottomLeft().y + Constants::PAD_HEIGHT;
	int UL_x = layout.getBottomLeft().x + 3*Constants::PAD_HEIGHT;  
	int UL_y = layout.getBottomLeft().y + Constants::PAD_HEIGHT + layout.getHeight() + Constants::PAD_OFFSET + 3*Constants::PAD_HEIGHT;	
	int LR_y = layout.getBottomLeft().y + Constants::PAD_HEIGHT; 
	int UR_x = layout.getBottomLeft().x + Constants::PAD_HEIGHT+layout.getWidth() + Constants::PAD_OFFSET + 3*Constants::PAD_HEIGHT; 
	int UR_y = layout.getBottomLeft().y + 3*Constants::PAD_HEIGHT+layout.getHeight();
 
 
	int X_spacing; 
    if (termsOnTop == 0) X_spacing = 0;
    else {
	X_spacing = (int) 
			( layout.getWidth() - 
				( termsOnTop * Constants::PAD_WIDTH) )
					/ termsOnTop;		
	}	
					
  //added this to handle the case where X_spacing <= 0				
	if ( lessOrEqualDouble( (double)X_spacing , 0.0) && termsOnTop > 0  )
	{
	  X_spacing = std::max((int)Constants::PITCH, X_spacing);
	  layout = (*_db)._rowDefs->getChipBbox();
	  double newWidth = termsOnTop * (Constants::PAD_WIDTH + X_spacing);
	  myAssert3 (greaterThanDouble(newWidth, layout.getWidth()), newWidth, " newWidth should be greater than old width", layout.getWidth() );
	  
	  myWarn3 (0, layout.getWidth(), " X_spacing was < 0, changed chip width to ", newWidth );
	  (*_db)._rowDefs->setChipBBox ( BBox(
	  				 layout.getBottomLeft().x ,
	  				 layout.getBottomLeft().y , 
	                   layout.getBottomLeft().x + newWidth,
	                   layout.getTopRight().y ));
	  
	  
	  reOrderPads(base);
	  return;
	}
	//update: changed 	padPerSideCnt * 2 * Constants::PAD_HEIGHT to 
	//padPerSideCnt * Constants::PAD_HEIGHT			
    int Y_spacing;
	if (termsOnRight == 0) 	Y_spacing = 0;
    else{
	Y_spacing = (int) 
			(layout.getHeight() - 
				(termsOnRight * Constants::PAD_HEIGHT) - Constants::PAD_HEIGHT) /
					termsOnRight;		
	}	
	/*Y_spacing  = (Y_spacing < (int) rowHeight) ? 
					(Y_spacing) : 
					(int) (floor(Y_spacing/(rowHeight))) * rowHeight;*/

	if ( lessThanDouble( (double)Y_spacing , 0.0) )
	{
	  myWarn2 (0, " Y_spacing is < 0, consider modifying the aspect ratio ", Y_spacing );
	  Y_spacing = std::max(0, Y_spacing);
	  layout = (*_db)._rowDefs->getChipBbox();
      int maxTermsOnRight = floor (layout.getHeight()/ Constants::PAD_HEIGHT);
      std::cout << "Max terms fitting on right side of chip is: " << maxTermsOnRight << "\n";	  
      if (maxTermsOnRight < termsOnRight){
        int numAdditinalTermsOnTop = termsOnRight - maxTermsOnRight;
	    
	    double newWidth = (termsOnTop + numAdditinalTermsOnTop) * (Constants::PAD_WIDTH + X_spacing);
	    myAssert3 (greaterThanDouble(newWidth, layout.getWidth()), newWidth, " newWidth should be greater than old width", layout.getWidth() );
	    
	    myWarn3 (0, layout.getWidth(), " <-layout width, Y_spacing was < 0, changed chip width to ", newWidth );
	    (*_db)._rowDefs->setChipBBox ( BBox(
	    				 layout.getBottomLeft().x ,
	    				 layout.getBottomLeft().y , 
	                     layout.getBottomLeft().x + newWidth,
	                     layout.getTopRight().y ));
	    
	    
	    reOrderPads(base);
	    return;	  
	  }
	}


	std::cout << "X_spacing: " << X_spacing 
	<< " Y_spacing: " << Y_spacing  << std::endl;


	int x_offset = UL_x;
	auto padIndices = (*_db).getNetlist().getPadIndices();
	//unsigned padIdxOffset = (*_db).getNetlist().getNumCoreCells();
	unsigned lastIndex = 0;
	for (int j = 0; j < termsOnTop; j++) {
		if (lastIndex < padCnt)
			changePadlocation(padIndices.at(lastIndex), x_offset, UL_y); 
		x_offset = x_offset + Constants::PAD_WIDTH + X_spacing;
		lastIndex ++;
	}

	int y_offset = UR_y - 2*Constants::PAD_HEIGHT; 
	for (int j = 0; j < termsOnRight; j ++) {
		if (lastIndex < padCnt)
			changePadlocation(padIndices.at(lastIndex), UR_x, y_offset);
		y_offset = y_offset - Constants::PAD_HEIGHT - Y_spacing;
		lastIndex++;
	}

	x_offset = LL_x + Constants::PAD_WIDTH + Constants::PAD_OFFSET;
	for (int j = 0; j < termsOnBottom; j ++) {
		if (lastIndex < padCnt)
			changePadlocation(padIndices.at(lastIndex), x_offset, LR_y);
		x_offset = x_offset + Constants::PAD_WIDTH + X_spacing;
		lastIndex++;

	}

	//Since it is the left part of chip spacing is doubled
	y_offset = LL_y + (4*Constants::PAD_HEIGHT);
	for (int j = 0; j < termsOnLeft; j ++) {
		if (lastIndex < padCnt)
			changePadlocation(padIndices.at(lastIndex), LL_x, y_offset);
		y_offset = y_offset + Constants::PAD_HEIGHT + Y_spacing;
		lastIndex++;
	}

	std::cout << "\n\n******************************************\n\n";
	
}



void padPl::reOrderPads(){
	
	BBox layout = (*_db)._rowDefs->getChipBbox();
	Point o = layout.getBottomLeft();
	
	reOrderPads( Point ( -o.x , -o.y ) );
	return;
}

/*
void padPl::reOrderPads(){
	
	//reOrderPads( Point(0, 0) );
	//return;
	
	unsigned padCnt = (*_db).getNetlist().getNumAllPads();
	
	myAssert2 (padCnt > 0, padCnt, " padCnt is <= 0");
	
	BBox layout = (*_db)._rowDefs->getChipBbox();
	std::cout << "Layout: " << layout << std::endl;
		
	int padPerSideCnt = (int) (padCnt /4) + 1;
	std::cout << "No. Pads: " << padCnt << 
				" No. Pads per Side: " << padPerSideCnt << "\n";


// 	int LL_x = layout.xMin;  
//	int LL_y = layout.yMin;
//	int UL_x = layout.xMin;  
//	int UL_y = layout.yMax + Constants::PAD_OFFSET + Constants::PAD_HEIGHT; // So that splitters could fit in chip area
//	int LR_y = layout.yMin - Constants::PAD_OFFSET - Constants::PAD_HEIGHT;
//	int UR_x = layout.xMax + Constants::PAD_OFFSET + Constants::PAD_HEIGHT; // So that splitters could fit in chip area  
//	int UR_y = layout.yMax;
//				
 	int LL_x = Constants::PAD_HEIGHT;  
	int LL_y = Constants::PAD_HEIGHT;
	int UL_x = Constants::PAD_HEIGHT;  
	int UL_y = Constants::PAD_HEIGHT + layout.getHeight() + Constants::PAD_OFFSET + Constants::PAD_HEIGHT;	
	int LR_y = Constants::PAD_HEIGHT; 
	int UR_x = Constants::PAD_HEIGHT+layout.getWidth() + Constants::PAD_OFFSET + Constants::PAD_HEIGHT; 
	int UR_y = Constants::PAD_HEIGHT+layout.getHeight();
 
 
	int X_spacing = (int) 
			( layout.getWidth() - 
				(padPerSideCnt * Constants::PAD_WIDTH) )
					/ padPerSideCnt;
	//update: changed 	padPerSideCnt * 2 * Constants::PAD_HEIGHT to 
	//padPerSideCnt * Constants::PAD_HEIGHT			
	int Y_spacing = (int) 
			(layout.getHeight() - 
				(padPerSideCnt * Constants::PAD_HEIGHT) - Constants::PAD_HEIGHT) /
					padPerSideCnt;
	Y_spacing  = (Y_spacing < 2 * Constants::PAD_HEIGHT) ? (Y_spacing) : 
					(int) (Y_spacing/(2*Constants::PAD_HEIGHT)) * 2 * Constants::PAD_HEIGHT;

	std::cout << "X_spacing: " << X_spacing 
	<< " Y_spacing: " << Y_spacing  << std::endl;


	int x_offset = UL_x;
	auto padIndices = (*_db).getNetlist().getPadIndices();
	//unsigned padIdxOffset = (*_db).getNetlist().getNumCoreCells();
	unsigned lastIndex = 0;
	for (int j = 0; j < padPerSideCnt; j++) {
		if (lastIndex < padCnt)
			changePadlocation(padIndices.at(lastIndex), x_offset, UL_y); 
		x_offset = x_offset + Constants::PAD_WIDTH + X_spacing;
		lastIndex ++;
	}

	int y_offset = UR_y - 2*Constants::PAD_HEIGHT; 
	for (int j = 0; j < padPerSideCnt; j ++) {
		if (lastIndex < padCnt)
			changePadlocation(padIndices.at(lastIndex), UR_x, y_offset);
		y_offset = y_offset - Constants::PAD_HEIGHT - Y_spacing;
		lastIndex++;
	}

	x_offset = LL_x + Constants::PAD_WIDTH + Constants::PAD_OFFSET;
	for (int j = 0; j < padPerSideCnt; j ++) {
		if (lastIndex < padCnt)
			changePadlocation(padIndices.at(lastIndex), x_offset, LR_y);
		x_offset = x_offset + Constants::PAD_WIDTH + X_spacing;
		lastIndex++;

	}

	//Since it is the left part of chip spacing is doubled
	y_offset = LL_y + (4*Constants::PAD_HEIGHT);
	for (int j = 0; j < padPerSideCnt; j ++) {
		if (lastIndex < padCnt)
			changePadlocation(padIndices.at(lastIndex), LL_x, y_offset);
		y_offset = y_offset + Constants::PAD_HEIGHT + Y_spacing;
		lastIndex++;
	}

	
}
*/


void padPl::changePadlocation
	(int cellIdx, int x_loc, int y_loc){
	
	//std::cout << "Changing location of pad: " << cellIdx << " from (" << (*_pl)[cellIdx] << " ) to ";

	(*_pl)[cellIdx].x = x_loc;
	(*_pl)[cellIdx].y = y_loc;
	//std::cout << "(" << (*_pl)[cellIdx] << "\n";
	
}


bool padPl::improvePadPlacement 
  ( unsigned maxItr ) 
{
	
	auto cPath = findCriticalPath(_db,false);
	double initHpwl = cPath.second;
	
	std::cout << "\n\n****************************\n\n";
	std::cout << "\n\tOptimizing the placement of pads\n";
	Placement beforePadPl2 ( (*_pl) );
	bool succ = true;
	for (unsigned i=0; i < maxItr && succ; i++)
	{
	  if ( !succ ) break;
	  succ = improvePadPlacementSub ( &beforePadPl2 );
	  (*_db)._spatial.locations = beforePadPl2;			
	}  

   
	cPath = findCriticalPath(_db,false);
	double finalHpwl = cPath.second;
	double reduction = 100 * (abs(finalHpwl - initHpwl) / initHpwl);
     

	std::cout << "\n\t Cell reordering reduced the critical path from " << initHpwl << " to " << finalHpwl << "(" << reduction << "%)\n\n";
	
	std::cout << "\n\n***************************************************\n\n";
  	
	return succ;
}



//returns true if it can find them
//false otherwise
bool padPl::findCellPadIdx 
  ( unsigned netIdx, int& padIdx, int& cellIdx )
{
  const dbNet& topNet = (*_db).getNetlist().getNetByIdx(netIdx) ;
  
  //commented this out, cause only cell-pad connection
  //which is also clock signal is GCLK pad-cell connection
  //should also reorder GCLK pad
  /*if (topNet.getType().isClock() )
  {
	std::cout << "\n\n\t\tCritical path is a clk signal. Net: " <<  topNet <<  "\n";   
	return false;	  
  }*/
  
  for ( auto cItr = (topNet).cellsBegin();
		cItr != (topNet).cellsEnd();
		cItr ++ )
  {
	//this is a cell-pad connection, process it 
	if ( (*cItr)->isFixed() )
	  padIdx = (*cItr)->getIndex();
	else
      cellIdx = (*cItr)->getIndex();		
  }  
  if ( padIdx == -1 || cellIdx == -1 )
  {
	std::cout << "\n\n\t\tCritical path is not a cell-pad connection. Net:\n\t\t" <<  topNet <<  "\n";   
	return false;
  }	
  
  return true;	
}


//returns a boolean, indicating whether it's successfull 
//in reducing the hpwl or not
bool padPl::improvePadPlacementSub 
  ( Placement* pl ) 
{
  unsigned numPads = (*_db).getNetlist().getNumIOPads();
  auto padIndices = (*_db).getNetlist().getPadIndices();  
  myAssert3 ( padIndices.size() == numPads, numPads, 
			" is not equal to num of pads: ", padIndices.size());
			
  auto cPath = findCriticalPath(_db,false);
  unsigned netIdx = cPath.first;
  double cNetHpwl = cPath.second;

  int padIdx = -1;
  int cellIdx = -1;
  
  //if can't find cell & pad indices return
  bool f = findCellPadIdx ( netIdx, padIdx, cellIdx );
  if ( !f ) return false;
  
  //otherwise, start swapping pad with other pads and check 
  //if it improves HPWL  
  //saves the indices of candidate pads
  //The reason is that swapping with the best one may increase
  //hpwl of another net
  std::vector<unsigned> candidIdx;
  double candidPadDist = cNetHpwl;
  auto cellLoc = (*pl)[ cellIdx ];
  for ( unsigned i=0; i < numPads; i++)
  {
	unsigned curIdx = padIndices.at (i);
	//if ( curIdx == padIdx ) continue;
	double dist = mDist ( cellLoc, (*pl)[curIdx] );
	if ( lessThanDouble ( dist, candidPadDist ) )
	{
	  candidIdx.push_back ( curIdx );
	}
  }  
  
  if ( candidIdx.size() == 0)
  {
	myWarn (0, "Couldn't find any candidate pad to change place with worst case pad. Returning");
	return false;
  }

  //std::cout << " Total # of candidates are: " << candidIdx.size() << std::endl;
  
  //has candidates
  //swapping places
  for (unsigned i=0; i < candidIdx.size(); i++)
  {
    //find hwpl of the candidate pad
	unsigned candid = candidIdx.at(i);
    const dbCell& c = (*_db).getNetlist().getCellByIdx ( candid );
	
	unsigned numN = c.getNets().size();
	if ( numN == 0 ) continue;
    myAssert2 ( numN == 1, numN , " num of nets connected to a pad is != 1" );    
	
	unsigned nIdx = c.getNets().front()->getId();
    //double alternateHpwl = 
    //(*_db).getNetlist().evalHalfPerimCost ( nIdx, (*pl), false);
	
    std::swap ( (*pl) [ padIdx ], (*pl) [ candid ]);
	
    double newCPathHpwl = 
      (*_db).getNetlist().evalHalfPerimCost ( netIdx, (*pl), false);
	double newAlterHpwl = 
      (*_db).getNetlist().evalHalfPerimCost ( nIdx, (*pl), false);
	  
	  //critical hpwl is improved  
	  // and newAlterHpwl doesn't become new critical path
	  // though it may be more than alternateHpwl
	  if ( lessThanDouble ( newCPathHpwl, cNetHpwl) &&
 	        lessOrEqualDouble (newAlterHpwl, cNetHpwl) )
	  {
		std::cout << "\n\t\tPad reordering reduced critical path length from "<< cNetHpwl << " to " <<  newCPathHpwl;  
		return true;
	  }
	  //otherwise, reverse the change 
	  std::swap ( (*pl) [ padIdx ], (*pl) [ candid ]);
  }
  
  myWarn2 (0,  " Swapping didn't improve the critical net hpwl: ", cNetHpwl );
  
  
  
  return false;

}

