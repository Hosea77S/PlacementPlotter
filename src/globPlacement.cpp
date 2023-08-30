#include "globPlacement.h"



void globPlacement::doGlobalPlacement(int maxIt)
{
	//determines the accuracy of cg solver
	bool acc = (maxIt <= MAX_GP_IT_1) ? false : true;		
	
	std::cout << "\n\n***************************************************\n\n";
	std::cout << "+-------------    Global Placement    ------------------+\n";
	Placement initPl ((*_db)._spatial.locations);
	Placement anchorPl(initPl);
	Placement bestPl(initPl);
	double bestLegalHPWL = DBL_MAX;
	
	for (int i=0; i < maxIt; i++){
		qcMatrixGen b2b(const_cast<const DB*>(_db), &initPl);	
		std::cout << "\n\nIteration" << i << " ..\n";
		
		anchorPl = doLAL(&initPl, i);
		std::cout << "\n\nBefore NLS P2P HPWL    = " << 
			(*_db).evalHPWLcost(initPl) << std::endl; 
		std::cout << "After LAL-NLS P2P HPWL = " << 
			(*_db).evalHPWLcost(anchorPl) << std::endl;
			
		//this saves the best legal solution	
		if ( lessThanDouble((*_db).evalHPWLcost(anchorPl), bestLegalHPWL) )
		{
			bestPl = anchorPl;
			bestLegalHPWL = (*_db).evalHPWLcost(anchorPl);
		}
		
		//if (i == maxIt-1){
		//	_db->_spatial.locations = anchorPl;
		//	//std::cout << anchorPl << std::endl;
		//	continue;
		//}
		
		addPsuedoNetWeights(b2b, initPl, anchorPl, i, maxIt);
		
		//solve cg with updated q, c matrices
		auto Qx = b2b.getQm(_XX); auto Cx = b2b.getCm(_XX);
		auto Qy = b2b.getQm(_YY); auto Cy = b2b.getCm(_YY);
		
		Placement tempPL(initPl);
		qpSolver solver((*_db).getNetlist().getNumCoreCells(), const_cast<Placement*> (&tempPL));
		//viennaSolver solver((*_db).getNetlist().getNumCoreCells());
		//eigenCGSolver solver((*_db).getNetlist().getNumCoreCells(), const_cast<Placement*> (&tempPL));
		auto newX = solver.solve(Qx, Cx, Dir (_XX), acc);
		auto newY = solver.solve(Qy, Cy, Dir (_YY), acc);
		
		std::vector<Point> newPl;
		for (unsigned i=0; i  < newX.size(); i++){
			newPl.push_back(Point(newX[i], newY[i]));
		} //adding position of pads to solution
		for (unsigned i=_db->getNetlist().getNumCoreCells(); 
						i < _db->getNetlist().getNumCells(); i++)
			newPl.push_back(initPl[i]);

		Placement afterSolvePl(newPl);
		_db->_spatial.locations = afterSolvePl;
		//std::cout << _db->_spatial.locations << "\n";		
		std::cout << "After GP P2P HPWL : x = " << std::setw(6) << _db->evalHPWLcostX();
		std::cout << " y = " << std::setw(6) << _db->evalHPWLcostY() ;
		std::cout << " Total = " << std::setw(6) << _db->evalHPWLcost() << "\n\n";
		
		
		Legalizer lg (_db);		
		lg . putCellsInBoundRelative(_sourceBB);
		//lg . putCellsInBound(_sourceBB);

		initPl = _db->_spatial.locations;
	}
	
	
	/*double finalHPWL = _db->evalHPWLcost();
	if ( lessThanDouble(bestLegalHPWL, finalHPWL) ){
		std::cout << "\n\nHPWL for best solution (" << 
		bestLegalHPWL <<
		") is better than HWPL for final solution: (" <<
		finalHPWL << 
		 ").\nUsing best solution.\n\n";
		_db->_spatial.locations = bestPl;
		
	}*/
	//anchorPl is the final location of all cells
	//shifToInitialLocations(&anchorPl);
	shifToInitialLocations(&_db->_spatial.locations);
	
	
	
	std::cout << "\n\n***************************************************\n\n";
	std::cout << "Finished Global Placement\n";
	std::cout << "After " << maxIt <<" iterations of GBL P2P HPWL : x = " << std::setw(6) << _db->evalHPWLcostX();
	std::cout << " y = " << std::setw(6) << _db->evalHPWLcostY() ;
	std::cout << " Total = " << std::setw(6) << _db->evalHPWLcost() << "\n\n";
	
	
	
	return;	
}


void globPlacement::shifToInitialLocations(Placement* pl)
{
	//shifts all the cells to the initial bbox, defined by .scl file
	unsigned n = (*_db).getNetlist().getNumCells();
	/*
	std::vector<int> cellIndices ( n, 0);
	myAssert ( n > 0 && ((int)n == (*pl).getSize()), " Pl size is 0");
	for (unsigned i=0; i < n; i++)
		cellIndices.at(i) = i;
	
	std::sort(cellIndices.begin(), cellIndices.end(), 
			CompareCellIdsByY( *const_cast<Placement*> (pl) ));
	std::sort(cellIndices.begin(), cellIndices.end(), 
			CompareCellIdsByX( *const_cast<Placement*> (pl) ));
	
	std::cout << (*pl) << std::endl;
	std::cout << (*_db)._spatial.locations << std::endl;
	std::cout << cellIndices << std::endl; */
	 
	BBox originalBb = (*_db)._rowDefs->getChipBbox();
	Point minP = Point(Constants::PAD_HEIGHT, Constants::PAD_HEIGHT);
	std::cout << " min point is: " << minP << std::endl;
	Point shift = originalBb.getBottomLeft() - minP - Point(Constants::PAD_HEIGHT,Constants::PAD_HEIGHT);
	std::cout << " shift point is: " << shift << std::endl;
	
	for (unsigned i=0; i < n; i++){
		//(*_db)._spatial.locations[i] += shift;
		(*pl)[i] += shift;
	}
	
	return;	
}

//Performs Look Ahead Legalization, returns a semi-legal solution given the initial placement
Placement globPlacement::doLAL(Placement* pl, unsigned iteration)
{
	
	int maxGBins = 100;
	auto gMapping = createGridBins(pl, iteration);
	std::vector<GridBin> gBins = gMapping.getGridBins();
	//for (unsigned i=0; i < gBins.size(); i++)
	//	std::cout << " density: " << gBins[i].getDensity() << std::endl;
	
	//sorting grid bins in decsending order based on grid bin density 
	std::sort (gBins.begin(), gBins.end(), CompareGridBinsByDensity());
	//std::cout << "After sorting by density: \n";
	//for (unsigned i=0; i < gBins.size(); i++)
	//	std::cout << " density: " << gBins[i].getDensity() << std::endl;
	
	maxGBins = std::min (maxGBins, int(gBins.size()));
	//Placement anchorPl ((*_db).getNetlist().getNumCells(), Point(0,0));
	Placement anchorPl (*pl);
	
	/*if (maxGBins == 0) return anchorPl;
	GridBin topBin = maxGBins[0];
	double density = topBin.getDensity();
	if ( lessOrEqualDouble ( density, TARGET_UTIL ) ){
		//std::cout << "LAL loop : " << i << std::endl; 		
		//std::cout << "\tMax Bin Utilization = " << density << std::endl;
		//std::cout << "\tBin Clustering :  Num Bins for Spreading : 1\n";
		doNonLinearScaling(gMapping, gBins.at(i), pl, &anchorPl);		
	}
	else {
		GridBin tBin =  clusterBins ( gMapping, topBin );
		doNonLinearScaling(gMapping, tBin, pl, &anchorPl);				
	}*/
	
	for (int i=0; i < maxGBins; i++) {
		if (gBins.at(i).getCellCount() == 0) continue;
		std::cout << "LAL loop : " << i << std::endl;
		std::cout << "\tMax Bin Utilization = " << gBins.at(i).getDensity() << std::endl;
		doNonLinearScaling(gMapping, gBins.at(i), pl, &anchorPl, iteration);
		//add to net weights based on anchor places
		//solve cg again
	}
	
	std::cout << "\n*************************************\n";
	
	//std::cout << "After nonLinear Scaling: " << (*_db).evalHPWLcost(anchorPl) << std::endl;
	return anchorPl;
}


GridBin globPlacement::createUnitGBin(Placement* pl)
{
  auto initBB = _sourceBB;
  Point centerOfChip;
  centerOfChip = getMedian(_sourceBB.getBottomLeft(), _sourceBB.getTopRight());
  //std::cout << "Center of chip:\t"<< centerOfChip << "\n";  
  double w, h;
  double minW = 0.0, minH = 0.0;
  double maxW, maxH ;
  w = _sourceBB.getTopRight().x - centerOfChip.x;
  h = _sourceBB.getTopRight().y - centerOfChip.y;
  maxW = w;
  maxH = h;

  myAssert( greaterThanDouble(w, 0.0), "negative width" );
  myAssert( greaterThanDouble(h, 0.0), "negative width" );
  double density = DBL_MAX;
  double foundGBin = false;
  BBox curBB ( centerOfChip.x - w, centerOfChip.y-h, 
				centerOfChip.x + w, centerOfChip.y + h );	  
  GridBin curGb (_db, curBB, *pl, 0);					
  int iteration = 0;  
  while (!foundGBin)
  {
    if (iteration > 100) exit(0);	  
    auto curDensity = curGb.getDensity();	
    //std::cout << "\nIteration: "  << iteration << "\tWidth: " << w << "\tHeight: " << h << "\tDensity: " << curDensity << "\n";	  
    //printf ("\nmaxW:%f, minW:%f, maxH:%f, minH:%f\n", maxW, minW, maxH, minH);
    if ( (lessThanDouble (curDensity, 1.05) && greaterOrEqualDouble (curDensity, 1.0) )
		|| ( greaterOrEqualDouble(minW, maxW) || greaterOrEqualDouble(minH, maxH) ))
	{
      foundGBin = true;		
      break;	  
	}
	
    w = (minW+maxW)/2.;		
    h = (minH+maxH)/2.;		
    if ( lessThanDouble (curDensity, 1.0) ) //density is low, should reduce bbox
	{      		
	  maxW = w;
	  maxH = h;
	}
	else { //density > 1.0 should enlarge bbox
	  minW = w;
	  minH = h;		
	}
	
    curBB = BBox( centerOfChip.x - w, centerOfChip.y-h, 
				   centerOfChip.x + w, centerOfChip.y + h );	  
    curGb = GridBin(_db, curBB, *pl, 0);						
	
    iteration++;	
  }  
   
  std::cout << "Final GBin: " << curGb << "\n";
  return curGb;  	
}




GridMapper globPlacement::createGridBins
		(Placement* pl, unsigned iteration)
{
	
	auto unitBin = createUnitGBin(pl);

	//unsigned numGrids = (iteration < 20) ? 1: ( iteration < 40) ? 2 : 3;//(int)(( iteration - 30) / 10) + 1;
	//unsigned numGrids = 1;
	//unsigned numGrids =  2 + iteration;
	//unsigned numGrids = (iteration/25) + 1 ;
	//if ( numGrids >3 ) numGrids = 3;
	//unsigned numGrids = (iteration < 20) ? 0: ( iteration < 40) ? 2 : 4;
	//unsigned numGrids = (iteration/25);
	unsigned numGrids = 0;
	//unsigned numGrids = 2;
	
	//GridMapper gm(_db, numGrids, numGrids, _sourceBB, pl);	
	//gm.snapCellsToGrids();
	
	//GridMapper gm(_db, numGrids, unitBin.getBBox(), pl);	
	//if (iteration > 25)   
	GridMapper gm = GridMapper(_db, numGrids, _sourceBB, pl);	
	std::cout << gm << std::endl;
	
	//TODO, check new GridMapper cstr for numGrids = 1,2, 3, 4
	
	return gm;
}

void globPlacement::doNonLinearScaling
	(const GridMapper& gm, const GridBin& gb, 
	  const Placement* originalPl, Placement* anchorPl,
	  unsigned iteration)
{
	std::cout << "\tBin Clustering ID(" << gb.getID() << ") numCells(" << gb.getCellCount() <<") Num Bins for Spreading : 4" << std::endl;	
	
	//for (unsigned k=0; k < 4; k++)
	//  if (k%2 == 0)
	//    legalizeBin(gb,  anchorPl, _XX);
    //  else 		  
	//	legalizeBin(gb , anchorPl, _YY);


	legalizeBin(gb , anchorPl, _YY);
	return;
	int cutDepth = ((int)(iteration/25) + 1) ;
	GridMapper quadBins (_db, cutDepth, gb, anchorPl);
	auto gBins = quadBins.getGridBins();
	
	
	/*
	legalizeBin(gb,  anchorPl, _XX);	
	double xm = gb.getCellCountMedian( anchorPl, _XX);
	auto lrBins = gb.divideByCutLine(xm, anchorPl, _XX);
	GridMapper dummy ( _db, 2, 1, gb.getBBox(), anchorPl);
	lrBins.first.setBBox( dummy. getGridBins().at(0).getBBox() );
	lrBins.second.setBBox( dummy. getGridBins().at(1).getBBox() );	
	std::cout << "x median = " << xm << " resultant gBins: " << lrBins << std::endl;	
	std::vector<GridBin> initBins = {lrBins.first, lrBins.second};
	std::vector<GridBin> gBins;
	for (unsigned i=0; i < initBins.size(); i++){		
		// legalize vertically
		legalizeBin(initBins.at(i), anchorPl, _YY);
		if (initBins.at(i).getCellCount() == 0) continue;
		double ym = initBins.at(i).getCellCountMedian( anchorPl, _YY);
		auto tbBins = initBins.at(i).divideByCutLine(ym, anchorPl, _YY);
		GridMapper dummyY ( _db, 1, 2, gb.getBBox(), anchorPl);
		tbBins.first.setBBox( dummyY. getGridBins().at(0).getBBox() );
		tbBins.second.setBBox( dummyY. getGridBins().at(1).getBBox() );	
		std::cout << i << " y median = " << ym << " resultant gBins: " << tbBins << std::endl;	
		gBins.push_back(tbBins.first);
		gBins.push_back(tbBins.second);		
	} */
	
	
	//myAssert ( gBins.size() == 4, " Didn't generate 4 gBins.");
	
	for (unsigned i=0; i < gBins.size(); i++){
		auto cellIndices = gBins.at(i).getCellIndices();
		
		//sort cells by their placement by X and by Y
		//std::sort(cellIndices.begin(), cellIndices.end(), 
				//CompareCellIdsByX( *const_cast<Placement*> (originalPl) ));
		

		auto horizGBin = gBins.at(i);

		for (unsigned k=0; k < 4; k++)
		  if (k%2 == 0)
			legalizeBin(horizGBin, anchorPl, _XX);
		  else 		  
			legalizeBin(horizGBin, anchorPl, _YY);
		
		// legalize horizontally
		//legalizeBin(horizGBin, anchorPl, _XX);
		
		//std::sort(cellIndices.begin(), cellIndices.end(), 
				//CompareCellIdsByY( *const_cast<Placement*> (originalPl) ));

		//auto vertBin = gBins.at(i);
		
		// legalize vertically
		//legalizeBin (vertBin, anchorPl, _YY);
		
		//std::sort(cellIndices.begin(), cellIndices.end(), 
		//		CompareCellIdsByX( *const_cast<Placement*> (originalPl) ));
		//legalizeBin(horizGBin, anchorPl, _XX);
	
	}
	
	
}

void globPlacement::legalizeBin
	(const GridBin& gb, Placement* anchorPl, Dir d)
{
	Legalizer lg3 (_db);
	lg3.doLazyLeg ( gb, anchorPl );
	return;
	
	//std::cout << " Legalization in bins in dir: " << d << "\n";
	//std::cout << "HorizGBin: " << gb << std::endl;
	//std::cout << "Total cells in gb: " << gb.getCellIndices().size() << "\n";
	
	//creating bins for legalizing inside bins
	//GridMapper gm (_db, 1, 1, gb.getBBox(), anchorPl);
	GridMapper gm;
	
	if (d == _XX){
		int ySize = (int) ceil(gb.getBBox().getHeight()/(*_db)._rowDefs->getRowHeight());
		//std::cout << "\t\tCreating " << ySize << " horizontal bins for legalizing\n";
		gm = GridMapper(_db, 1, ySize, gb.getBBox(), anchorPl);		
		gm.snapCellsToGrids();	
		//std::cout << gm << std::endl;
	} else {
		int xSize = (int) ceil (gb.getBBox().getWidth() / (*_db).getAvgCellWidth());
		//std::cout << "\t\tCreating " << xSize << " vertical bins for legalizing\n";
		gm = GridMapper (_db, xSize, 1, gb.getBBox(), anchorPl);
		gm.snapCellsToGrids();	
		//std::cout << gm << std::endl;
	}
	
	
	Legalizer lg (_db);
	auto gridBins = gm.getGridBins();
	
	unsigned total = 0;
	for ( unsigned i=0; i < gridBins.size();i++)
		total += gridBins.at(i).getCellIndices().size();
	
	//myWarn3 ( total == gb.getCellIndices().size(), total,
	//		" is not equal to ", gb.getCellIndices().size());
	
	for (unsigned i=0; i < gridBins.size(); i++){
		//std::cout << i << " gBin: " << gridBins.at(i) << std::endl;
		lg . doInGridLegalization(gridBins.at(i), anchorPl, d); 
	}
	
}


void globPlacement::addPsuedoNetWeights 
	(qcMatrixGen& b2b, const Placement& pl, const Placement& anchorPl, int iteration, int maxIt)
{
	myAssert ( pl.getSize() == anchorPl.getSize(), " Inconsistent size between pl and anchorPl");
	

	//best result, run for 400 iterations
	//double alpha = 1e-2 * (1 + iteration/3);
	
	//best result for < 200 iterations
	//double alpha = 1e-2 * (1 + iteration);
	
	double alpha = ( maxIt<= MAX_GP_IT_1) ?
					1e-2 * (1 + iteration) :
					1e-2 * (1 + iteration/3);
					
	/*std::cout << "\n\nt maxIt= " << maxIt << " alpha: " <<
	alpha << " iter= " << iteration << "\n\n";*/
	
	//double alpha = 1.0 + (0.01 * (1 + iteration));
	//double alpha  = 0.5;

	
	for (int i = 0 ; i < pl.getSize(); i++){
		if ( (*_db).getNetlist().getCellByIdx(i).isFixed() ) continue;
		if ( pl[i] == anchorPl[i] ) continue;

		//std::cout << "Id: " << i << " initPl: " << pl[i] << " anchorPl: " << anchorPl[i] << std::endl;
		
		double distX = b2b.getDistance (pl[i].x, anchorPl[i].x);
		double recipX = 1 / distX;
		double distY = b2b.getDistance (pl[i].y, anchorPl[i].y);
		double recipY = 1 / distY;		
		Dir dx = _XX;
		Dir dy = _YY;
		
		//std::cout << "recipX: " << recipX << " recipY: " << recipY;
		//recip * fixedAnchorPosition
		
		
		INT_PAIR qIdx = std::make_pair(i, i);
		b2b.addToQm ( dx, qIdx, alpha*recipX );
		b2b.addToQm ( dy, qIdx, alpha*recipY );
		
		double wX = alpha * (-1.0*anchorPl[i].x) * recipX;
		double wY = alpha * (-1.0*anchorPl[i].y) * recipY;
		
		b2b.addToCm ( dx, i, wX );
		b2b.addToCm ( dy, i, wY );
		
	}
	
	//check consistency
    b2b.isQMconsistent( );
    b2b.isCMconsistent( );	
	
	return;
}


//tries to minimze the max WL
void globPlacement::minimizeMaxWL 
	( unsigned maxIt )
{
	
  std::cout << "\n\n***************************************************\n\n";
  std::cout << "\n\tOptimizing the placement of movable cells\n";
	
  auto cPath = findCriticalPath(_db, false);
  double initHpwl = cPath.second;
	
  bool succ = true;
  for (unsigned i=0; i < maxIt; i++)
  {
    succ = minimizeMaxWLSub ();	
	if ( !succ ) break;
  }

  cPath = findCriticalPath(_db,false);
  double finalHpwl = cPath.second;
  
  double reduction = 100 * (abs(finalHpwl - initHpwl) / initHpwl);
  

  
  std::cout << "\n\t Cell reordering reduced the unlegalized critical path from " << initHpwl << " to " << finalHpwl << "(" << reduction << "%)\n\n";
  
  std::cout << "\n\n***************************************************\n\n";
  
  return;
}
	
	
bool globPlacement::minimizeMaxWLSub()	
{
			
  auto cPath = findCriticalPath(_db, false);
  unsigned netIdx = cPath.first;
  double cNetHpwl = cPath.second;
  
  const dbNet& topNet = (*_db).getNetlist().getNetByIdx(netIdx) ;
  if ( topNet.getType().isClock() )
  {
	myWarn2 (0, "\n\n\t\tCritical path is a clk signal. Net:", topNet );  
	return false;
  }
  
  if ( topNet.getNumCells() > 2)
  {
	myWarn2 (0, "\n\n\nTotal cells connected to critical net is >2: ", topNet.getNumCells() );
	return false;
  }	  

  const dbCell& fCell = ( topNet ).getCellByIdx (0);
  const dbCell& sCell = ( topNet ).getCellByIdx (1);
    
  Placement pl ( (*_db)._spatial.locations );
/*   if (fCell.isFixed()){
    myWarn2 (0, fCell.getIndex(), " is a fixed cell, cant' move.")	;  	  
	padPl pp3(_db, &pl);
	bool succ = pp3. improvePadPlacement ();
    (*_db)._spatial.locations [ sCell.getIndex() ] = (pl)[ sCell.getIndex() ];	
	return succ;
  } 
  else if (sCell.isFixed()){	  
    myWarn2 (0, sCell.getIndex(), " is a fixed cell, cant' move.")	 ; 	  
	padPl pp3(_db, &pl);
	bool succ = pp3. improvePadPlacement ();
    (*_db)._spatial.locations [ fCell.getIndex() ] = (pl)[ fCell.getIndex() ];
	return succ;
  } */
  
  
  std::vector< std::pair<unsigned, double> > connNets;
  for (unsigned j=0; j < 1; j++)
  {
	const dbCell& tCell = ( j == 0) ? 
			( topNet ).getCellByIdx (0) : 
			( topNet ).getCellByIdx (1)	;
   
    for ( auto nIt = tCell.netsBegin(); 
  		nIt != tCell.netsEnd();
  		nIt ++ )
    {
  	unsigned idx = (*nIt)->getId();
  	if (idx == netIdx) continue;
  	double hpwl = (*_db).getNetlist().evalHalfPerimCost 
  	                               ( idx, (pl), false);
  	
      connNets.push_back ( {idx, hpwl} );
    }	
  }  
  //std::cout << "\n\t\tTotal # of connected nets: " << connNets.size() << "\n";

  //placing cells in the median point of curr loc and median of cell locs  

  
  //temp placement vals  
  Point tf = (pl)[ fCell.getIndex() ];
  Point ts = (pl)[ sCell.getIndex() ];

  Point med = getMedian( tf, ts);
  
  Point med_f = getMedian ( tf, med );
  Point med_s = getMedian ( ts, med );
  
  (pl)[ fCell.getIndex() ] = med_f;
  (pl)[ sCell.getIndex() ] = med_s;
  
  //std::cout << "\n\tCell reordering changed 1: " << tf << 
  //" to " << med_f << " and 2: " << ts << " to " << med_s << "\n";

  
  
  for ( unsigned i=0; i < connNets.size(); i++ )
  {
	auto p = connNets.at (i);
	unsigned idx = p.first;
	double newHpwl = (*_db).getNetlist().evalHalfPerimCost 
	                               ( idx, (pl), false);
	
	//if by reordering one of the nets becomes critical net return
	if ( greaterThanDouble ( newHpwl, cNetHpwl ) )
	{
	  //reversing the placement reordering
	  (pl)[ fCell.getIndex() ] = tf;
	  (pl)[ sCell.getIndex() ] = ts; 
	  myWarn2 ( 0, "\tReordering introduces a new critical path. hpwl: ", newHpwl );
	  return false;	
	}
    	  
  }
  
  //if no new critical paths are introduced, accept move
  (*_db)._spatial.locations [ fCell.getIndex() ] = (pl)[ fCell.getIndex() ];
  (*_db)._spatial.locations [ sCell.getIndex() ] = (pl)[ sCell.getIndex() ];

  std::cout << "\n\tCell reordering reduced critical path hpwl from "
  << cNetHpwl << " to " << (*_db).getNetlist().evalHalfPerimCost ( netIdx, (pl), false) << "\n";
  
  auto newCPath = findCriticalPath(_db,false);
  
  std::cout << "\tNew critical net has HPWL: " << newCPath.second << "\n\n";  
  
  return true;
}


