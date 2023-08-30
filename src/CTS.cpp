#include "CTS.h"
#include <cerrno>



std::vector<int> CTS::getClkSinkNodes()
{
	
	std::vector<int> clkSinkNodes;
	for ( auto cIt = (*_db).getNetlist().cellsBegin();
		 cIt != (*_db).getNetlist().cellsEnd(); 
		  cIt ++ )
    {
		myAssert2 ( 
		  ! ( (*cIt)->isClkSink() && !(*cIt)->isCore()), 
			*cIt, " is clk sink and not Core at same time!" );
		if ( (*cIt)->isClkSink() ){
			clkSinkNodes.push_back( (*cIt)->getIndex() );
		}
	}
	
	return clkSinkNodes;
}

bool CTS::isEnoughSpacingBetweenRows()
{
	/*
	Legalizer lg ( _db );
	Placement pl ( (*_db)._spatial.locations ); 
	auto rowVec = lg. snapCellsToRows ( &pl, _bbox );
	double rowHeight = (*_db)._rowDefs->getRowHeight();

	
	for (unsigned int i=0; i < rowVec.size() - 1; i++){
		if ( lessThanDouble ( fabs (
		 rowVec.at(i).getBBox().getBottomLeft().y - 
			rowVec.at(i+1).getBBox().getBottomLeft().y  ),
				 rowHeight + Constants::SPL_HEIGHT ) ) 
				 {
					std::cout <<  rowVec.at(i) << std::endl;
					std::cout <<  rowVec.at(i+1) << std::endl;
					
				 return false;
				 }
	} */
	
	double rowHeight = (*_db)._rowDefs->getRowHeight();
	double rowSpacing = _bbox.getHeight() / 
		(*_db)._rowDefs->getRowCnt();
	
	if ( greaterOrEqualDouble ( rowSpacing , 
			rowHeight + Constants::SPL_HEIGHT  ) )
		return true;
	
	myWarn3 ( 0, rowSpacing , " is less than rowHeight + Constants::SPL_HEIGHT", rowHeight + Constants::SPL_HEIGHT );
	return false;
}


//Gets 2 vectors, one containing all the merging segments, icluding the sink cells, one only containing sink cells indices
//Replaces the sink cells in the clkVec vector with the original clock cells, and deletes their designated cell(myCell)
void CTS::mergeClockSinksandSplitters
(std::vector<dbClkCell*> &clkVec, 
	const std::vector<int> &clkSinkNodes){
		
	std::cout << "\tMerging Clock Sinks and Splitters." << std::endl;
	int sinkSize = int(clkSinkNodes.size());
	for (int i=0; i < sinkSize; i++){
	  if ( !clkVec.at(i)->isSinkNode() )
		{
			myWarn2 (0, " Inconsistent data between clkVec and clkSinkNodes of index: Skipping " , i );
			continue;
		}
		
		//if (clkVec.at(i) == NULL) continue;
		//delete clkVec.at(i)->myCell;
		clkVec.at(i)->myCell = &(*_db).getNetlist().getCellByIdx ( clkSinkNodes.at(i));
	}
	
	//std::cout << clkVec << std::endl;
	return ;	
}

int findClosestIdx(double yLoc, std::vector<double>& rowYOffsets )
{
  int idx = 0;
  double dist = DBL_MAX;
  for (unsigned i=0; i < rowYOffsets.size(); i++)
  {
    if ( abs( yLoc - rowYOffsets.at(i) ) < dist ){ //if equi-distance put them in the lower index for now
      idx = i;
	  dist = abs( yLoc - rowYOffsets.at(i) );	
	}	  
  }	        
  return idx;	
}

//Populates the dbCell instance of dbClkCells, 
//Adds new dbCells to the cellList
//Legalizes the clock splitters
std::vector<GridBin>
 CTS::findSplitterLocations
  (const std::vector<dbClkCell*> &clkVec, unsigned useLP,
    const std::vector<double>& channelHeights)
{
	
	//TODO, fix ids, it duplicates sink nodes 
	std::cout << "\tAdding splitters to the cellList\n";
	double rowHeight = (*_db)._rowDefs->getRowHeight(); //e.g. 120, before adding space
	double rowWidth = (*_db)._rowDefs->getChipWidth();
	//int newRowHeight = rowHeight + Constants::SPL_HEIGHT ;
	double newRowHeight = _rowHeight ;	//160, after adding unifrom space
    std::cout << "rowHeight: " << rowHeight
	<< " newRowHeight: " << newRowHeight << "\n\n";	

	
	int numOfSplAdded = 0;
	int numOfRows = (*_db)._rowDefs->getRowCnt();
	//auto bb = (*_db)._rowDefs->getChipBbox();
	int numCells = (*_db).getNetlist().getNumCells();
	double yOffset2 = (_bbox.getBottomLeft().y) + rowHeight;
	double xOffset = (_bbox.getBottomLeft().x);

	std::vector<GridBin> gBins ( numOfRows, GridBin() );
	
    //TODO set the yOffset of gBins according to non-uniform spapcing	
    //TODO: check if the vanilla version has right yOffset2s, seems like yOffset2s should be incremented
	for (int i=0; i < numOfRows; i++){
		gBins.at(i) = GridBin ( _db, 
			BBox(xOffset, yOffset2, xOffset + rowWidth, yOffset2 + Constants::SPL_HEIGHT)  , i);
	}
	Placement pl( (*_db)._spatial.locations );

	assert(numOfRows > 0);
	std::vector<double> rowYOffsets (numOfRows, 0.0);
    int chSize = channelHeights.size();	
    if (chSize > 0) assert ( numOfRows == (int) chSize);	
    double rYO = (_bbox.getBottomLeft().y);	
	for (int i=0; i < numOfRows; i++)
	{
      rowYOffsets.at(i) = rYO;
      if ( chSize > 0 && i < chSize)	  
        rYO += rowHeight + channelHeights.at(i);	  
	  else 
        rYO += newRowHeight;		  
	}		

    //std::cout << "rowYOffsets: " << rowYOffsets << "\n\n";	
	
	for (unsigned i=0; i  < clkVec.size(); i++){
	    double yLoc = 0.0;
		int index = 0;
		
 		if (clkVec.at(i) == NULL) continue; 
		//Skipping the clock sinks
		if ( clkVec.at(i)->isSinkNode() ) continue; 
		
		double yOffset = (_bbox.getBottomLeft().y);
        if (channelHeights.size() == 0)	{ //uniform channel heights
		  	
		  
		  //int index = (int)( round( (clkVec.at(i)->getOrigin().y - yOffset) / newRowHeight) );
		  index = (int)( round( (clkVec.at(i)->getOrigin().y - yOffset) / newRowHeight) );
		  
		  double extraH = _rowHeight - (*_db)._rowDefs->getRowHeight() - Constants::SPL_HEIGHT;
		  //std::cout << "\n\nCTS: extraH is: " << extraH << "\n";
		  
		  if (useLP == LPType::noLP){
		    yLoc = (int)( index *  newRowHeight ) 
		  			+ yOffset + rowHeight;
            yLoc += ( (int)floor(extraH/(2*Constants::PITCH)) * Constants::PITCH); 					
		  } else
		  {
   		    yLoc = clkVec.at(i)->getOrigin().y;			
		  }
		} else {
          //TODO set index			
          //index = 0; 
          index = findClosestIdx (clkVec.at(i)->getOrigin().y, rowYOffsets );  
		  yLoc = rowYOffsets.at(index);
          //std::cout << "index: " << index << " for cell with origin: " << 
		   //clkVec.at(i)->getOrigin().y << "\n\n";	
		  
	  int spl_mult = (int) Constants::SPL_HEIGHT / Constants::PITCH;
		  //if channel height is 4*PITCH, then no extra shift is needed, otherwise
		  //deduct the 4*PITCH from spacing then shift by half the left spacing
          yLoc += rowHeight + round( ( (channelHeights.at(index) - spl_mult * (Constants::PITCH) )/ Constants::PITCH ) / 2.0) * Constants::PITCH ;
			
		}

        /*std::cout << "\t\tMapped " << clkVec.at(i)->getOrigin().y << " to idx: " << index << " and loc: " << yLoc << "\n";*/		
		
		/*
		//contract between pl and route, don't change
		//pins are added later in addNetToChip func
		//the reason is that exsiting cells (AND, OR, ..)
		//also need clk pins inserted
		Point p1(CLK_IN_PIN_POS, CLK_IN_PIN_POS);
		Point p2(CLK_OUT_PIN_1_POS, CLK_OUT_PIN_1_POS);
		Point p3(CLK_OUT_PIN_2_POS, CLK_OUT_PIN_2_POS); 
	  
		dbPin* pin1 = new dbPin("pin1", "INPUT", 0, p1);
		dbPin* pin2 = new dbPin("pin2", "OUTPUT", 1, p2);
		dbPin* pin3 = new dbPin("pin3", "OUTPUT", 2, p3);
		ctainerPins pVec = {pin1, pin2, pin3};*/
		ctainerPins pVec = {};
		
		Symmetry s1("Y");
		int id = numCells++ ;
	    std::string name = "SplitCLK_" + std::to_string(id);
		
		Point clkCellOrigin = clkVec.at(i)->getOrigin();
		dbCell* node = new dbCell (name, "CORE", "CC", 
				  id, Constants::SPL_WIDTH, Constants::SPL_HEIGHT, 
					Point ( clkCellOrigin.x, yLoc), 
					  0, pVec, s1);		
		
		pl.addToPlacement ( node->getOrigin() );
		
		(*_db)._design._nameCellMap[name] = node;		
		(*_db)._design._cellLib.push_back(node);
		
		/*std::cout << "Adding clkCell: " << *node << 
		" at place: " << pl[ node->getIndex() ] << "\n";*/
		
		clkVec.at(i)->setCell(const_cast<dbCell*> (node));
							
		if (index >= 0 && index < numOfRows)
			gBins.at(index).addCellIdx( node->getIndex() );
		
		numOfSplAdded ++;
	}
	
	
	myAssert3 ( pl.getSize() == (int)(*_db).getNetlist().getNumCells(), pl.getSize(), " pl size is diff from netlist size: ",  (*_db).getNetlist().getNumCells());

	//std::cout << clkVec << std::endl;
	
	(*_db)._spatial.locations = pl;
	
	std::cout << "HPWL before CLK splitter legalization is : " << 
	(*_db).evalWHPWLcost (pl)	<< std::endl;
	
	if (useLP == LPType::noLP)
	{
      Legalizer lg(_db);
	  for (int i=0; i < numOfRows; i++){
	   	//TODO change this to provide min spacing to the netlist
	    	//lg.doInGridLegalization(gBins.at(i), &pl, _XX);
	    	lg.legalizeCellsInPlace(gBins.at(i), &pl, Constants::PITCH, _XX);
	  }			
	}
	
	
	//doInGridLegalization(gb, pl, dir)
	//legal.legalizeCellsInPlace(rowVec, chip->minCellWidth());
	(*_db)._spatial.locations = pl; //to update the position of spls
	
	std::cout << "\tTotal number of " << numOfSplAdded << " splitters are added to the design to implement clock tree." << std::endl;
	return gBins;	
}

std::vector<int> CTS::getHeightVec
  (const std::vector<dbClkCell*> &clkVec, 
  const std::vector<int> &clkSinkNodes)
{
	int sinkSize = int(clkSinkNodes.size());
	int clkVecSize = clkVec.size();
	std::vector<int> sinkLevels(sinkSize, -1);
	//root of the tree has the id of clkVecSize-1
	findAllLevels(clkVecSize-1, clkVec, 0);
	for (int i=0; i < sinkSize; i++)
		sinkLevels[i] = clkVec[i]->getHeight();

    return sinkLevels;
	
}

void CTS::addBufferToClkTree
  (std::vector<dbClkCell*> &clkVec, int index)
{
      auto curSink = clkVec[index];	
      //std::cout << "\t" << *curSink << " has a height of " << h << ", maxHeight= " << maxL << "\n";		
	  //cur sink is transformed to left child of holdbuff
	  //holdbuff becomes the new parent of curSink
	  //old parent of curSink becomes new parent of holdbuff
      auto parent = clkVec.at(curSink->getParent());
      int idx = clkVec.size();
	  Point pos = curSink->getOrigin();
      if (lessThanDouble(parent->getOrigin().x , curSink->getOrigin().x))
		pos -= Point(1.0,0.0);
	  else
		pos += Point(1.0,0.0);
		  
	  //+ Point(1,1);	
					  
	  dbClkCell* holdBuffClkCell = new dbClkCell( idx,  
				curSink->getId(), -1, parent->getId(), 
				curSink->getHeight(),  
				pos,
				NULL);
				
      curSink->setParent(idx);
	  curSink->setHeight(curSink->getHeight()+1);
      if (parent->getLeft() == curSink->getId())
        parent->setLeft( idx );
      else if (parent->getRight() == curSink->getId())	
        parent->setRight( idx );
      else
        myAssert3(0, *curSink, " curSink is not left or right child of parent: ", *parent );		  
	  
      clkVec.push_back(holdBuffClkCell);	  	  
	
}

//finds nodes that have a level of maxLevel - 1 in an AVL tree
std::vector<unsigned> 
 CTS::getListOfImbalancedClkNodes
   (std::vector<dbClkCell*> &clkVec, 
     const std::vector<int> &clkSinkNodes, 
	 const std::vector<double>&leafDelays)
{

  auto sinkLevels = getHeightVec(clkVec, clkSinkNodes);	
  int maxL = *std::max_element(sinkLevels.begin(), sinkLevels.end());
  int minL = *std::min_element(sinkLevels.begin(), sinkLevels.end());

  //double maxDelay = *std::max_element(leafDelays.begin(), leafDelays.end());

//  std::cout << clkVec<< "\n";  
//  std::cout << "\nMax and Min levels: [" << maxL << "," << minL <<"]\n"; 
  int numHoldBufs = maxL - minL;
  myWarn2 (numHoldBufs <= 1,  
		" numHoldBufs is not < 1: ", numHoldBufs); 
    
  int sinkSize = clkSinkNodes.size();

  std::vector<unsigned> imbalancedNodeIdx;  
  for (int i=0; i < sinkSize; i++){
	int h = clkVec[i]->getHeight();
	if ( h == maxL - 1 ){
	  //if ( greaterOrEqualDouble ( (maxDelay - leafDelays.at(i)), Constants::SPL_DELAY  )  )
		imbalancedNodeIdx.push_back(i);	
	}
	  
  }
	
  return imbalancedNodeIdx;	
}

std::vector<unsigned>
  CTS::findDelayImbalancedNodes
    (const std::vector<double>& leafDelays)
{
	
  double maxDelay = *std::max_element(leafDelays.begin(), leafDelays.end());
  double minDelay = *std::min_element(leafDelays.begin(), leafDelays.end());
	
  if (lessThanDouble((maxDelay - minDelay), Constants::SPL_DELAY))
    return {}; //nothing can be done in this case, return empty	  
	
  std::vector<unsigned> imbIdx;	
  for (unsigned i=0; i < leafDelays.size(); i++)
  {
    auto curSinkDelay = leafDelays.at(i);	  
    if ( greaterOrEqualDouble(maxDelay - curSinkDelay, Constants::SPL_DELAY )  )
	{
	  imbIdx.push_back(i);	
	}		
	  
  }
	
  return imbIdx;		
}	
	


void CTS::addHoldBuffers
  (std::vector<dbClkCell*> &clkVec, 
    const std::vector<int> &clkSinkNodes, 
	 const std::vector<unsigned>& imbalancedNodeIdx)
{
    
  if (imbalancedNodeIdx.size() == 0) return;	
  auto clkRoot = clkVec.at(_rootId);
  auto clkSuperRoot = clkVec.at( _superRootId ); 

  int totalHoldBuffsAdded = 0;  
  
  for (unsigned i=0; i < imbalancedNodeIdx.size(); i++){
	addBufferToClkTree( clkVec, imbalancedNodeIdx.at(i) );  	  
	totalHoldBuffsAdded++;  	  
  }
  
  
  std::cout << "\n\t\tAdded total number of " << 
  totalHoldBuffsAdded << " hold splitters. The new size of clkVec is: "<< clkVec.size() << "\n";
  
  //std::cout << "\n\nnew clkVec: " << clkVec << "\n";
  
  clkVec.erase(clkVec.begin()+ clkRoot->getId() );
  //clkVec.erase(clkVec.begin()+ clkSuperRoot->getId() );
  std::cout << "\t\tAdding superRoot and root to clkVec, ";
  clkVec.push_back( clkRoot );
  //clkVec.insert(clkVec.begin() + clkVec.size()/2, clkSuperRoot );  
  
  //std::cout << "\n\nnew clkVec: " << clkVec << "\n";
  std::cout << "\t\tNew size of clk tree (#nodes) = " << clkVec.size() << "\n";
  //std::cout << "\n\nUpdating indices of the clkVec\n";
  
  std::map<int, int> oldTonew;
  oldTonew[-1] = -1;  
  //oldTonew[ clkSuperRoot->getId() ] = clkVec.size() / 2;
  //oldTonew[ clkRoot->getId() ] = clkVec.size() - 1;  
  for (unsigned i = 0; i < clkVec.size(); i++)
  {
    //if ( int(i) == clkSuperRoot->getId() )
      //continue;
  
	oldTonew[ clkVec.at(i)->getId() ] = i;	      	
  }	  
  
  //std::cout << "oldTonew: " << oldTonew << "\n\n";  
  
  for (unsigned i = 0; i < clkVec.size(); i++)
  {
    auto curClkCell = clkVec.at(i);
    curClkCell->setId    ( oldTonew[curClkCell->getId()    ] );
    curClkCell->setLeft  ( oldTonew[curClkCell->getLeft()  ] );
    curClkCell->setRight ( oldTonew[curClkCell->getRight() ] );
    curClkCell->setParent( oldTonew[curClkCell->getParent()] );	
  }    

  _rootId = clkVec.back()->getId();
  _superRootId = clkSuperRoot->getId();  
  
  //std::cout << "\n\nFinal clkVec: " << clkVec << "\n";
  std::cout << "\n\n\t\tFinished Adding Hold Buffers.\n\n";
  
        
  return;	
}

void CTS::fixDummyNodes
  (std::vector<dbClkCell*>& clkVec, 
    std::map<int,int>& new2oldMap)
{
  //reversing the indices of dbClkCells
  for (unsigned i=0; i < clkVec.size(); i++)
  {
    auto curClkCell = clkVec.at(i);	  
    clkVec.at( i )-> setId ( new2oldMap[ curClkCell->getId() ] );
    clkVec.at( i )-> setParent ( new2oldMap[ curClkCell->getParent() ] );
    clkVec.at( i )-> setLeft ( new2oldMap[ curClkCell->getLeft() ] );
    clkVec.at( i )-> setRight ( new2oldMap[ curClkCell->getRight() ] );		  
  }
  

	
	
  int numClkSinks = getClkSinkNodes().size();	
  std::set<int> idcsToBeRemoved;  
  
  std::sort( clkVec.begin(), clkVec.end(), CompareClkCellsByID() );
  //std::cout << "\n\nPostCTS(" << clkVec.size() << "): \n" << clkVec << "\n";
  
   //removing dummy nodes	
  for (int i=0; i < numClkSinks; i++)
  {
    auto curClkCell = clkVec.at(i);	
	auto curId = curClkCell->getId();
	myAssert3 ( (int)i == curId, i," is not == ", curId );
	if ( curClkCell->isSinkNode() ) continue;
	//found a dummy node
	idcsToBeRemoved.insert(curClkCell->getRight());
	auto leftId = curClkCell->getLeft();
	
	auto parent = clkVec.at( curClkCell->getParent() );
    auto parentId = parent->getId();
	
	//std::cout << "CurId: " << *curClkCell << " parent: " << *parent
	 //<< " left: " << *clkVec.at(leftId) << "\n";
	
	if ( clkVec.at(parentId)->getLeft() == curId )
      clkVec.at(parentId)->setLeft( leftId );
    else if ( clkVec.at(parentId)->getRight() == curId )  
      clkVec.at(parentId)->setRight(leftId);
    else
      myAssert3 (0, curId, " none of the parent children are curId: ", *clkVec.at(parentId) )		
  
	//should swap the ids of leaf and parent, change child of parentOfParent, delete right child of parent  
			
    
    curClkCell->setId ( leftId );
	curClkCell->setLeft ( curId );
    curClkCell->setRight(-1);	
	
	clkVec.at( leftId )->setId ( curId );
	clkVec.at( leftId )->setParent ( leftId );
      
	  
  }	   
  std::sort( clkVec.begin(), clkVec.end(), CompareClkCellsByID() );
    
  std::vector<dbClkCell*> newClkVec;  
  
  for (unsigned i=0; i < clkVec.size(); i++){
    auto node = 	  clkVec.at( i );
	if ( idcsToBeRemoved.find( node->getId() ) == idcsToBeRemoved.end()  )
		newClkVec.push_back( node );
  }
  
  for (auto&i: idcsToBeRemoved )
	delete clkVec.at(i);
  
  clkVec = newClkVec;

  std::sort( clkVec.begin(), clkVec.end(), CompareClkCellsByID() );
  //std::cout << "\n\nAfterDummy Removal(" << clkVec.size() << "): \n" << clkVec << "\n";  
  
  auto root = clkVec.at(numClkSinks*2-1);
  clkVec.erase( clkVec.begin()+ (numClkSinks*2)-1 );  
  clkVec.push_back(root);
  
  std::map<int,int> old2new;
  old2new[-1] = -1;  
  for (unsigned i=0; i < clkVec.size(); i++)
    old2new[ clkVec.at(i)->getId() ] = i;	  

  for (unsigned i=0; i < clkVec.size(); i++)
  {
    auto node = clkVec.at(i); 	  
	node->setId( old2new[node->getId()] );
	node->setParent( old2new[node->getParent()] );
	node->setLeft( old2new[node->getLeft()] );
	node->setRight( old2new[node->getRight()] );	  
  }  
  
  std::sort( clkVec.begin(), clkVec.end(), CompareClkCellsByID() );
  //std::cout << "\n\nAfterDummy Removal(" << clkVec.size() << "): \n" << clkVec << "\n";	
  
  _rootId = clkVec.back()->getId();
  _superRootId = clkVec.at(numClkSinks)->getId();	
  
  std::cout << "\n\nNew root: " << *clkVec.at(_rootId) <<
   " and super root: " << *clkVec.at(_superRootId) << "\n";
  
  return;  
}

void CTS::minimizeClkSkew
  (std::vector<dbClkCell*>& clkVec, 
    std::vector<GridBin>& clkCellGBins, 
	  bool insertHoldSpl, bool minMaxDelay,
	  double coef)
{
	
	auto rootNode = clkVec.at(_rootId);
	
	clockTree clt (rootNode->getId(), _db, clkVec);
	double oldSkew = clt.calcSkew(clt.calcDelay());
	
    double newSkew = oldSkew;	  
	if (insertHoldSpl){
      Placement beforBalance = ((*_db)._spatial.locations);			
      bool succ = true;		
	  //for (unsigned kk = 0; kk < 100; kk++)
	  //{
		std::cout.setstate(std::ios_base::failbit);		  
		while (succ){
		  succ = clt.minimizeSkew(minMaxDelay, coef);
		  //if (succ == false)
 		    //succ = clt.minimizeSkew(0.5);
		  //legalizeClkCells(clkCellGBins);
		  newSkew = clt.calcSkew(clt.calcDelay());				
		}
        std::cout.clear();		
	  //}				
		std::cout << "\n\n\t\tPre Legal: Improved Skew from " << oldSkew << " to " << newSkew << "(" << 
		100*((oldSkew - newSkew)/oldSkew) << "%)\n\n";
		
		legalizeClkCells(clkCellGBins);
		
		std::cout << "\n\n\t\tPost Legalization:\n"; 
		newSkew = clt.calcSkew(clt.calcDelay());	  
		
		double skewImpr = 100*((oldSkew - newSkew)/oldSkew);
		
		std::cout << "\n\n\t\tPost Legal: Changed Skew from " << oldSkew << " to " << newSkew << "(" << 
		skewImpr << "%)\n\n";
		
		if ( lessOrEqualDouble(skewImpr, 0.0 ) ){
		  std::cout <<"\n\nSkew is increased, rejecting changes\n";
		  ((*_db)._spatial.locations) = beforBalance;
		} else {
			std::cout <<"\n\n\tAccepting changes for skew minimization \n\n";
		}
		
	}
  return;
}

//updates locations of internal nodes in clkVec, by the locations
//obtained by MMM algorithm
void CTS::updateClkVecByMMMSol
 (std::vector<dbClkCell*> &clkVec, 
  const std::vector<dbClkCell> & mmmClockTop)
{
  for (unsigned i=0, j=0; i< clkVec.size() && j < mmmClockTop.size(); i++, j++){
    if ( clkVec.at(i)->getParent() == -1 ) {
  	j--;
  	continue;
    }		  
    myAssert3( clkVec.at(i)->getId() == mmmClockTop.at(j).getId() , *clkVec.at(i), " (clkVec) is not == mmmClockTop ", mmmClockTop.at(j) );
    if ( mmmClockTop.at(j).isSinkNode() || mmmClockTop.at(j).isHalfSinkNode() )
  	continue;
    clkVec.at(i)->setOrigin( mmmClockTop.at(j).getOrigin() )	;	  
  }
  //std::cout << "Current clock vec: " << clkVec << "\n";
} 	


//checks bin densities, adds to the chip width if density > 1
void CTS::adjustChipWidth(std::vector<GridBin>& clkCellGBins)
{
  double curWidth = _bbox.getTopRight().x - _bbox.getBottomLeft().x;		
  double maxWidth = curWidth;
  
  for (auto &i: clkCellGBins)
  {
    double density = i.getDensity();	  
    if ( greaterThanDouble( density, 1.0 ) )
      maxWidth = std::max( maxWidth, density * curWidth );		
  }

  if ( greaterThanDouble(maxWidth, curWidth) )  {
    maxWidth = round(maxWidth);
    printf("Increasing chip width to : %g", maxWidth);

	BBox finalBB ( _bbox.getBottomLeft().x,
			_bbox.getBottomLeft().y,
			_bbox.getBottomLeft().x + maxWidth,
			_bbox.getTopRight().y );
	
	(*_db)._rowDefs->setChipBBox  ( finalBB );
	
	std::cout << "\nCTS: New chip bbox: " << finalBB << "\n";
  }
	
	
	
}

void
 CTS::legalAndReSyn(double xSpace, std::vector<double> vSpacings)
{
  //std::cout << "In legalAndReSyn \n\n";
  //legalize rows, excluding clock splitters
  Legalizer ctsLg( _db );
  Placement curPl ( (*_db)._spatial.locations );
  int numRows =  (*_db)._rowDefs->getRowCnt(); 
  
  auto newRowHeights = vSpacings;
  double newHeight = 0.0;
  if ( int(vSpacings.size()) == numRows)  
  {
    for (int i=0; i < numRows; i++){
      newRowHeights.at(i) += (*_db)._rowDefs->getRowHeight();
      newHeight += newRowHeights.at(i);	   	  	  
    }
  }
  else
  {
    newHeight = numRows * _rowHeight;	  
  }	  
  
  //note: curBB should have the most updated bbox of the design, i.e., after placing the clock splitters, replacing the pads, and adjusting chip width & height
  BBox curBB ( _bbox.getBottomLeft().x,
				_bbox.getBottomLeft().y,
				 _bbox.getTopRight().x, 
				 _bbox.getBottomLeft().y + 
					newHeight);
					//numRows * _rowHeight);	
  
  std::cout << "CurBB after cts & legalization: " << curBB << "\n\n";
  auto rowVec = ctsLg . snapCellsToRows ( &curPl, curBB, newRowHeights ); 
  std::vector<GridBin>  clkCellGBins;
  for (auto& i: rowVec){
	GridBin curGb( _db, i.getBBox(), curPl, i.getIndex() );
	curGb.clearCellIndices();
    curGb.addCellIdx(i.getCellIndices());
    for (auto & j: curGb.getCellIndices()  )
      if ( (*_db).getNetlist().getCellByIdx( j ).isClkSpl() )
        curGb.removeCellIdx(j);		  
      		
    clkCellGBins.push_back( curGb );
  }
  
  //std::cout << "rowVec: " << rowVec << "\n";  
  //std::cout << "clkCellGBins: " << clkCellGBins << "\n";  
  
  for (unsigned jk=0; jk<clkCellGBins.size(); jk++){
	//std::cout << "Legalizing row: " << jk << "\n";
	ctsLg.legalizeCellsInPlace(clkCellGBins.at(jk), &curPl, xSpace, _XX);
  }
  
  (*_db)._spatial.locations = curPl;
  
  //report updated clock skew
  //clockTree cltPostHold (_rootId, _db, clkVec);
  //std::cout << "\n\n\tPre hold buffer insertion and Legalization: \n"; 
  //auto leafDelays = cltPostHold.calcDelay(false);
  
  
  //calling the cts engine with the update sink locations

  //doing lp or legalization incrementally  
	 
}

//TODO: add support for non-uniform channel heights to LP based CTS
//returns the clock skew
double 
 CTS::buildClockTree
  (bool fixTopology, bool preInsertHold, bool insertHoldSpl, unsigned useLP, unsigned topType, const std::vector<double>& channelHeights, bool replc)
{
  auto clkSinkNodes = getClkSinkNodes();
  std::string clockSinkFileName = _desPath + "/" + _desName + ".sinks" ;
  std::string clockMergeFileName = clockSinkFileName + ".clocks";
  int skewBound = 0;
  std::cout << "\tsize of clkSinkNodes is : " << clkSinkNodes.size() << std::endl;
  //for (int i=0; i < clkSinkNodes.size();i++)
  //	cerr << i << " cell: " << clkSinkNodes[i]->name << endl;
  bool enoughSp = isEnoughSpacingBetweenRows();
  myAssert ( enoughSp, "Not enough spacing between rows.");
  std::cout << "Row Spacing is enough.\n";	
  
  ctsParser cP (_desName, _desName);
  Placement sinkPl ( clkSinkNodes.size(), Point (0,0) );
  for (unsigned i=0; i < clkSinkNodes.size(); i++)
  {
    sinkPl[i] = (*_db)._spatial.locations[ clkSinkNodes.at(i)];
       //sinkPl[i].y += (*_db).getNetlist().getCellByIdx( clkSinkNodes.at(i) ).getHeight() / 2.0;		
  }
  
  std::string topFileName;
  std::map<int,int> new2oldMap;
     std::vector<dbClkCell> mmmClockTop;	
  Placement curPl((*_db)._spatial.locations);
  if (fixTopology)
  {
      /*Generating topology*/
      std::vector<dbClkCell> newSinks;									 
      MMM mmmTop(_db, &curPl, getClkSinkNodes());
      if (!preInsertHold)
	  if(replc) { // replacement
		topFileName = "../qHold/work/"+_desName+"/nextPlacement/"+_desName+"_topology_replc.top";
	  } else { // placement
        topFileName = mmmTop.buildTopology();		
	  }
         else
      {
  	  topFileName = mmmTop.buildTopology2(newSinks, new2oldMap);
        //to sort ascending 
        std::reverse(newSinks.begin(), newSinks.end());
        //std::cout << "\n\n\n\nNewsinks: " << newSinks << "\n";
        
        Placement sinkPlPost ( newSinks.size(), Point (0,0) );
           for (unsigned i=0; i < newSinks.size(); i++ )
             sinkPlPost[i] = newSinks.at(i).getOrigin();		  
        
        sinkPl = sinkPlPost;		  
      }
  	    
      //std::cout << "\n\n\tTapping Points: " << 
  	  //(mmmTop.getTappingPoints()) << "\n";
  	  
      
      mmmClockTop = mmmTop.getClockTopVec();
      std::sort(mmmClockTop.begin(), mmmClockTop.end(), CompareClkCellsByID() );
      if (mmmClockTop.front().getId() != 0)
        std::reverse(mmmClockTop.begin(), mmmClockTop.end());
      
      //std::cout << "Clock topology vec(MMM): " << mmmClockTop << "\n";
         //std::cout << "\n\nFinal sinkPl: " << sinkPl << "\n";
  } else 
   topFileName = "";	
  if(replc) {
	std::cout << "(replacement) topFileName: " << topFileName << std::endl;
  }
  
  cP.writeToSinksFile(&sinkPl,clockSinkFileName);
  //bool isClockTreeBalanced = false;
  std::vector<dbClkCell*> clkVec;  
  if (clkSinkNodes.size()<0) return 0;  
  if (clkSinkNodes.size()==1){ //should simply connect glck to the one cell and return
	int GCLK = (*_db).getNetlist().findGCLKCell();
	if (GCLK == -1) { 
	  myWarn( 0, " Error in RSFQ::routeClockNets : GCLK_Pad is not found; Skipping "); 
      return 0;	  
	}	  
    auto GCLKNet = (*_db)._design.addNetToChip(GCLK, clkSinkNodes.front(), "GCLK", 1, "CLOCK");	
	(*_db)._design.postProcess();
	return 0;
	
  } else {
    synthesizeClockTree(skewBound, clockSinkFileName, topFileName);
    clkVec = cP.readFromClocksFile(clockMergeFileName);
    //updateClkVecByMMMSol(clkVec, mmmClockTop);	  
  _rootId = clkVec.back()->getId();
  _superRootId = clkVec.at(clkVec.size()/2)->getId();	
  } 
  
  if (preInsertHold) fixDummyNodes(clkVec, new2oldMap);
  
  clockTree clt_pre (_rootId, _db, clkVec);
  std::cout << "\n\n\tPre hold buffer insertion and Legalization: \n"; 
  auto leafDelays = clt_pre.calcDelay(false);

	
  std::cout << "\tSize of clkVec is : " << clkVec.size() << std::endl;
  if (insertHoldSpl)
  {
    std::cout << "\n\tAdding hold buffers.\n";
       auto imbIdx = getListOfImbalancedClkNodes(clkVec, clkSinkNodes, leafDelays);  
    addHoldBuffers(clkVec, clkSinkNodes, imbIdx);	
    std::cout << "\n\n\tSize of the clkVec after adding hold buffers is : " << clkVec.size() << std::endl;
      clockTree clt_post_level (_rootId, _db, clkVec);	  
       clt_post_level.calcDelay(false);
    /*//uncomment to add more buffers to the nodes that have smaller delay than the largest phase delay value 
    auto dImbIdx = findDelayImbalancedNodes(leafDelays);
    addHoldBuffers(clkVec, clkSinkNodes, dImbIdx);	    	  
    std::cout << "\n\n\tSize of the clkVec after adding hold buffers to delay imbalaced nodes is : " << clkVec.size() << std::endl;*/
    
  }		
	
  // Add by XL: write updated balanced clkVec to topology.top	
  std::cout << "\n\t Start writing into fully balanced topology file \n"; 
  ctsParser cP2 (_desName, _desPath);
  topFileName = _desPath + "/" + _desName + "_topology_bal.top";
  // convert clkVec (pointer) to clkTopology (object)
  std::vector<dbClkCell> clkTopology; //std::vector<dbClkCell*> clkVec;
  for (std::vector<dbClkCell*>::iterator it = clkVec.begin() ; it != clkVec.end(); ++it) {
    clkTopology.push_back(*(*it));
  }
  cP2.write2TopologyFile(topFileName, clkTopology);   	
  std::cout << "\n\n\tFinished writing into fully balanced topology file: " << topFileName << " \n\n";
	//***********************************
	
  mergeClockSinksandSplitters(clkVec, clkSinkNodes);
  auto clkCellGBins = findSplitterLocations(clkVec, useLP, channelHeights);
  (*_db)._design.postProcess();
  //(*_db).PrintBenchmarkStatus();
  
  auto clockNetsVec = routeClockNets(clkVec);
  std::cout << "Clock nets are added to the netlist\n\n";
  (*_db)._design.postProcess();
  
  
  adjustChipWidth(clkCellGBins);
  
  //bool isClockTreeBalanced = checkIfClockTreeIsBalanced(clkVec, clkSinkNodes);
  checkIfClockTreeIsBalanced(clkVec, clkSinkNodes);
  
  
  //uncomment to print skew
  Placement finalSinkPl ( clkSinkNodes.size(), Point (0,0) );
  for (unsigned i=0; i < clkSinkNodes.size(); i++)
  	finalSinkPl[i] = (*_db)._spatial.locations[ clkSinkNodes.at(i)];
     //bool minMaxDelay = false;
  
  std::cout << "\n\nPre LP formulation: \n\n";
     clockTree clt_pre_LP (_rootId, _db, clkVec);	  
     clt_pre_LP.calcDelay(true);	   
  
  /*if (useLP != LPType::noLP) 
  {	
    std::vector<double> lambda, lambda2;	
	
	auto clkGBinsX = clkCellGBins;
    std::cout << "clkGBinsX: " << clkGBinsX << "\n";	  
	  LPInterface lp(_db);	
	  
	  auto clpPlacement = lp.doSkewMinCPLEXInY(
	    clkVec, clockNetsVec, _rootId, 
	     clkSinkNodes.size(), _rowHeight, clkGBinsX, fixTopology, lambda, useLP);

	  std::cout << "\n**************************************\n";
	  std::cout << "\n\n\nAfter solving ILP in Y dir\n\n";
	  clockTree clt_post_LP (_rootId, _db, clkVec);	  
	  //clt_post_LP.calcDelay(false);	   		
	  auto delayTree = clt_post_LP.calcDelay(true);	
      double maxDelay = * std::max_element(delayTree.begin(), delayTree.end());	  
      auto cplexYSkew = clt_post_LP  .calcSkew(delayTree);
	  Placement CPLEXYSolution((*_db)._spatial.locations);
	  (*_db)._spatial.locations = clpPlacement;
	  double clpYSkew = clt_post_LP.calcSkew(clt_post_LP.calcDelay());	  
	  
	  std::cout << "CPLEX skew: " << cplexYSkew << " clp skew: "
	  << clpYSkew << "\n\n";	  

	  if ( lessOrEqualDouble(cplexYSkew, clpYSkew ) ){
		(*_db)._spatial.locations = CPLEXYSolution ;
       	std::cout << "\n\nUsing CPLEX placement solution.\n";
        clkCellGBins = clkGBinsX;		
	  } else {
       	std::cout << "\n\nUsing CLP placement solution.\n";	  		  
	  }

	int numRows =  (*_db)._rowDefs->getRowCnt(); 
	std::cout<< "\nNum of rows: " << numRows << " rowHeight: " <<
	_rowHeight << " \n";
	Placement beforeLP_Pl ( (*_db)._spatial.locations ); 
	Legalizer lg(_db);
	BBox tempBB ( _bbox.getBottomLeft().x,
					_bbox.getBottomLeft().y,
					 _bbox.getTopRight().x, 
					 _bbox.getBottomLeft().y + 
						numRows * _rowHeight);	
	
	//lg.putCellsInBound(tempBB);
	//auto rowVec = lg. snapCellsToRows ( &beforeLP_Pl, tempBB, numRows );
    //std::cout << rowVec << "\n";	  
    std::cout << "After Y-LP, clkCellGBins: " << clkCellGBins << "\n";	  
     std::cout << "Size of rowVec: " << rowVec.size() << " size of clkCellGBins: " << clkCellGBins.size() << "\n\n";	  
    unsigned minNum = std::min(rowVec.size(), clkCellGBins.size());	
    for (unsigned i=0; i < minNum; i++ )
	{
      auto curGBin = clkCellGBins.at(i);		
	  curGBin.clearCellIndices();
      curGBin.addCellIdx( rowVec.at(i).getCellIndices() );	  
	}		
	
    std::cout << clkCellGBins << "\n";	   
	  
	double bestCPLEX = DBL_MAX, bestClp = DBL_MAX;
	for (int lpIt = 0; lpIt < 1; lpIt++){

	  
 	  //lp.doTimingAwareLegalization(clkVec, clockNetsVec, _rootId, 
	    // clkSinkNodes.size(), clkCellGBins, lambda); 
	  
	  clpPlacement = lp.doSkewMinCPLEX(clkVec, clockNetsVec, _rootId, 
	     clkSinkNodes.size(), clkCellGBins, fixTopology, lambda2, maxDelay, useLP);//, {{}}, lpIt+1);


	   //lp.doTimingAwareY(clkVec, clockNetsVec, _rootId, 
	     //clkSinkNodes.size(), clkCellGBins ); 
		 
	  delayTree = clt_post_LP.calcDelay(true);	
	  auto CPLEXskew = clt_post_LP.calcSkew(delayTree);
	  
 

  	  Placement CPLEXSolution((*_db)._spatial.locations);
	  (*_db)._spatial.locations = clpPlacement;
	  double clpSkew = clt_post_LP.calcSkew(clt_post_LP.calcDelay());	
	  
	  
	  bestCPLEX = std::min(CPLEXskew, bestCPLEX);
	  bestClp = std::min(clpSkew, bestClp);
	  
	  std::cout << "CPLEX skew: " << CPLEXskew << " clp skew: "
	  << clpSkew << "\n\n";

	  fout << "Iteration: " << lpIt << " CPLEX skew: " << CPLEXskew << " clp skew: " << clpSkew << "\n"; 	  
      //std::cout <<"\n\nDelayTree: " << delayTree << "\n";	  
	  
	  if ( lessOrEqualDouble(CPLEXskew, clpSkew ) ){
		(*_db)._spatial.locations = CPLEXSolution ;
       	std::cout << "\n\nUsing CPLEX placement solution.\n";	  
	  } else {
       	std::cout << "\n\nUsing CLP placement solution.\n";	  		  
	  } 
      	  
	  Placement tempPL((*_db)._spatial.locations);
	  Legalizer ctsLg(_db);
	  for (unsigned jk=0; jk<clkCellGBins.size(); jk++){
	  	ctsLg.legalizeCellsInPlace(clkCellGBins.at(jk), &tempPL, _XX);
		
      auto cellIndices = clkCellGBins.at(jk).getCellIndices();
      std::cout << "row: " << jk << " numCells: " << cellIndices.size() << "\n";		
      if (cellIndices.size() == 0) continue;
	  
	  std::sort(
		cellIndices.begin(), 
		cellIndices.end(), 			
	   CompareCellIdsByX( *const_cast<Placement*> (&tempPL) ));
	    for (unsigned i=0; i < cellIndices.size()-1; i++)
	    {		 
		  unsigned idx = cellIndices.at(i);
		  unsigned nextIdx = cellIndices.at(i+1);
		  double curXStart = (tempPL)[ idx ].x ;
		  double curXEnd = curXStart + (*_db).getNetlist().getCellByIdx( idx ).getWidth();	
		  double nextX = (tempPL) [ nextIdx  ] .x;
		  
	      myWarn3 (lessOrEqualDouble(curXEnd, nextX), 
		  curXEnd, " is not <= nextX, overlap: ", nextX);
		  	//(*pl) [nextIdx] .x = 	curXEnd + xMovement;   
	    }
	  }
	  (*_db)._spatial.locations = tempPL;
 	  
	  
	  std::cout << "\n\nFinal Skew: " <<  clt_post_LP.calcSkew(clt_post_LP.calcDelay(true)) << "\n";	
	  
 	  //if (insertHoldSpl){
      //  minimizeClkSkew(clkVec, clkCellGBins, insertHoldSpl);	
      //  //minimizeClkSkew(clkVec, clkCellGBins, insertHoldSpl, true);	
	  //} 
	} 
		
  }
	//doFinalPadPl();
	//write2File(clkVec, clockNetsVec, designName+"_clock");
*/	
  clockTree finalSkew (_rootId, _db, clkVec);	  
  auto delayTreeFinal = finalSkew.calcDelay(true);	
  auto finalSkewVal = finalSkew  .calcSkew(delayTreeFinal);
	
  return finalSkewVal;	
}

void CTS::legalizeClkCells
  (std::vector<GridBin>& gBins)
{
  Placement pl((*_db)._spatial.locations);	
  int numOfRows = (*_db)._rowDefs->getRowCnt();
  Legalizer lg(_db);
  for (int i=0; i < numOfRows; i++){
  	lg.legalizeCellsInPlace(gBins.at(i), &pl, 0.0, _XX);
  }
     (*_db)._spatial.locations = pl;
  return;
}



//Calls the binary file for BST
void CTS::synthesizeClockTree
  (int skewBound, 
   std::string clockSinkFileName, 
    std::string topFileName)
{
	//... execute binary file for clock tree synthesis tool
	std::string logFileName = clockSinkFileName;
	logFileName.erase(logFileName.end()-6, logFileName.end());
	logFileName += "CTS.log";
	std::string command = "./CTS/clockSyn/BSTsource1.2/bst -i " +  clockSinkFileName + " -B " + std::to_string(skewBound);
    if (topFileName.size())
	  command += " -G " + topFileName;
	else //if topology is not fixed, then consider delay
	  command += " -spD " + std::to_string(Constants::SPL_DELAY); 	//adds splitter delay
    command +=	" -D 0 "; //sets delay model to linear
	command += " > " + logFileName;
	
	int status = system (command.c_str());
	std::cout << "Calling command " << command << std::endl;
	
	std::cout << "status " << status << std::endl;
	if ( status < 0 )
	{ 
	   std::cout << "\n\nError:" << strerror(errno) << "\n\n";
	}
	myAssert ( status == 0, " CTS binary call failed.");
	//myWarn ( status == 0, " CTS binary call didn't return 0. CTS tool may have crashed.");
	
/* 	string newCommand = "clockSyn/BSTsource1.2/bst -i " +  clockSinkFileName + " -G " + clockSinkFileName + ".top_B" + to_string(skewBound) + " -B " + to_string(skewBound) + " > " +
					logFileName+"_final";
					
	system (newCommand.c_str());
	cout << "Calling command " << newCommand << std::endl;
 */	
	return ;
		
}


//Finds the type of splitter (location of in, out1, and out2 pins) 
// based on the connections to parent, left and right nodes
int CTS::findSplType
	(const std::vector<dbClkCell*> &clkVec, int cellIndex)
{
	//cerr << " cellIndex " << cellIndex << std::endl;
	if (cellIndex >= int(clkVec.size()) - 1) return -1;
	if (clkVec.at(cellIndex) == NULL) return -1;
	int parent = clkVec.at(cellIndex)->getParent();
	int leftC = clkVec.at(cellIndex)->getLeft();
	int rightC = clkVec.at(cellIndex)->getRight();
    if (parent == -1) return -1;	

	//cout << " cell : " << clkVec.at(cellIndex]->myCell->name << " loc : (" << clkVec.at(cellIndex]->myCell->x <<
	//	"," << clkVec.at(cellIndex]->myCell->y << "), " ;
	//cout << "parent : " << parent << " leftChild : " << leftC << " rightChild " << rightC << std::endl;		
	int parentLoc  =  (clkVec.at(parent) != NULL) ?
		findRespectivePosition(clkVec.at(parent)->myCell, clkVec.at(cellIndex)->myCell) : -1;
	//cout << " parent : " << clkVec.at(parent]->myCell->name << " loc : (" << clkVec.at(parent]->myCell->x <<
	//	"," << clkVec.at(parent]->myCell->y << "), " ;

	if (parentLoc == -1) {		
		std::cerr << " parent location is undefined. Cell : " <<  clkVec.at(cellIndex)->myCell->getName() <<
		" parent " << clkVec.at(parent)->myCell->getName() << std::endl;		
	}
	
	int leftChildLoc = LEFT;
    if (leftC != -1){
		
	  leftChildLoc  = (clkVec.at(leftC) != NULL) ?
	  	findRespectivePosition(clkVec.at(leftC)->myCell, clkVec.at(cellIndex)->myCell) : -1;
	  //cout << " leftC : " << clkVec.at(leftC]->myCell->name << " loc : (" << clkVec.at(leftC]->myCell->x <<
	  //	"," << clkVec.at(leftC]->myCell->y << "), " ;
	  	
	  if (leftChildLoc == -1) {		
	  	std::cerr <<  " leftChild location is undefined. Cell : " <<  clkVec.at(cellIndex)->myCell->getName() <<
	  	" leftChild " << 	clkVec.at(leftC)->myCell->getName() << std::endl;		
	  }	
	}	
	
	int rightChildLoc = LEFT;
    if (rightC != -1 )
	{
	   rightChildLoc  = (clkVec.at(rightC) != NULL) ?
	  	findRespectivePosition(clkVec.at(rightC)->myCell, clkVec.at(cellIndex)->myCell) : -1;
	  //cout << " rightC : " << clkVec.at(rightC]->myCell->name << " loc : (" << clkVec.at(rightC]->myCell->x <<
	  //	"," << clkVec.at(rightC]->myCell->y << "), " << std::endl;
      
	  if (rightChildLoc == -1){			
	  	std::cerr <<  " rightChild location is undefined. Cell : " <<  clkVec.at(cellIndex)->myCell->getName() <<
	  	" rightChild " << 	clkVec.at(rightC)->myCell->getName() << std::endl;		
	  }	
		
	}		

	return findSplitterTypeBasedOnLocation(parentLoc, leftChildLoc, rightChildLoc);

	//default
	//return SPLITCLK_0;
}


//Returns relative position of other Cell with respect to base Cell
int CTS::findRespectivePosition
	(const dbCell* other, const dbCell* base)
{	
	Point otherP = (*other).getOrigin();
	Point baseP = (*base).getOrigin();

	if ( lessThanDouble( otherP. y, baseP. y) ){
		if ( lessThanDouble( otherP. x, baseP. x) ) return LL;
		else if ( greaterThanDouble( otherP. x, baseP. x) ) return LR;
		else if ( equalDouble( otherP. x, baseP. x) ) return DOWN;
		else return LEFT;		
	}
		
	else if ( greaterThanDouble( otherP. y, baseP. y) ){
		if ( lessThanDouble( otherP. x, baseP. x) ) return UL;
		else if ( greaterThanDouble( otherP. x, baseP. x) ) return UR;
		else if ( equalDouble( otherP. x, baseP. x) ) return UP_UP;
		else return LEFT;
	}
	
	else if (  equalDouble ( otherP. y, baseP. y) ){
		if ( lessThanDouble( otherP. x, baseP. x) ) return LEFT;
		else if ( greaterThanDouble( otherP. x, baseP. x) ) return RIGHT;
		else if ( equalDouble( otherP. x, baseP. x) ) return LEFT;
		else return LEFT;		
	}

	return LEFT;	
}


std::vector<dbNet *> CTS::routeClockNets
	(std::vector<dbClkCell*> &clkVec)
{
    std::cout << "\n\n\tCreating clock nets and pins\n\n";	
	std::vector<dbNet *> clockNetlist;
	int numOfCLKNets =  0;
	for (int i = int(clkVec.size()) -1 ; i >= 0; i--){
		if (clkVec.at(i) == NULL) continue;
		//std::cout<< "i: " << i << " " << *clkVec.at(i) << std::endl;
		if (clkVec.at(i)->isSinkNode()) continue; //Certainly is a leaf node
		//it's the source of clk, should skip
		if (clkVec.at(i)->getParent() == -1) continue;

		//std::cout << "Processing node: " << i << std::endl;
		int splType = findSplType(clkVec, i);
		//std::cout << "SplType is : " << splType << "\n";
		if (splType == -1) splType = SPLITCLK_0;
		int pinTypeLeft = Constants::OUT_PIN_1;
		int pinTypeRight = Constants::OUT_PIN_2;
		//Determining the correct position for out1 and out2 pins
		if (clkVec.at(i)->getLeft() != -1 && clkVec.at(clkVec.at(i)->getLeft()) != NULL && 
			clkVec.at(i)->getRight() != -1 && clkVec.at(clkVec.at(i)->getRight()) != NULL)
			{
				
			auto rP = clkVec.at(clkVec.at(i)->getRight())->myCell->getOrigin();
			auto lP = clkVec.at(clkVec.at(i)->getLeft())->myCell->getOrigin();
			
			if (splType == SPLITCLK_0){

				if( greaterThanDouble (rP.y, lP.y) ){
					pinTypeLeft = Constants::OUT_PIN_2; 
					pinTypeRight = Constants::OUT_PIN_1;					
				}				
			} 
			if (splType == SPLITCLK_2){
				if( lessThanDouble(rP.y, lP.y) ){
					pinTypeLeft = Constants::OUT_PIN_2; 
					pinTypeRight = Constants::OUT_PIN_1;					
				}
			}			
			if (splType == SPLITCLK_4){
				if( lessThanDouble ( rP.x, lP.x) ){
					pinTypeLeft = Constants::OUT_PIN_2; 
					pinTypeRight = Constants::OUT_PIN_1;					
				}								
			}
			if (splType == SPLITCLK_6){
				if( greaterThanDouble( rP.x , lP.x) ){
					pinTypeLeft = Constants::OUT_PIN_2; 
					pinTypeRight = Constants::OUT_PIN_1;					
				}								
			}
		}
		if (pinTypeLeft == pinTypeRight) {
			std::cerr << " Both of left and right children are connected to same pin "<< std::endl;
			pinTypeLeft = Constants::OUT_PIN_1;
			pinTypeRight = Constants::OUT_PIN_2;
		}
		
		//std::cout << " pinTypeLeft is : " << pinTypeLeft << " and pinTypeRight is : " << pinTypeRight << std::endl;
		
				
		//Renaming SplitCLK cell
		unsigned idx = clkVec.at(i)->myCell->getIndex();
		std::string oldName =(*_db)._design._cellLib.at(idx)->getName(); 
        std::string newName = "SplitCLK_" + std::to_string(splType) +  "_" + std::to_string(i);		
		(*_db)._design._cellLib.at(idx)->setName (newName) ;
		
		//SplitCLK_id changes to  SplitCLK_0_id so map is updated
		(*_db)._design._nameCellMap[newName] = 
		  (*_db)._design._nameCellMap[oldName];
        auto it = (*_db)._design._nameCellMap.find(oldName);
		(*_db)._design._nameCellMap.erase(it);
		
		
		//std::cout << "New name of clk splitter is " << clkVec.at(i)->myCell->getName() << std::endl;
		//cout << "**************************************************************************" << std::endl;
		//std::cout << (*(clkVec[i])) << "\n";
		if (clkVec.at(i)->getLeft() != -1 && 
			clkVec.at(clkVec.at(i)->getLeft()) != NULL)
		{
			auto newNet = (*_db)._design.addNetToChip(
			clkVec.at(i)->myCell->getIndex(), 
			clkVec.at(clkVec.at(i)->getLeft())->myCell->getIndex(), 
			"clk" + std::to_string(numOfCLKNets), pinTypeLeft,
			"CLOCK");
			clockNetlist.push_back(newNet);
			numOfCLKNets++;
		} 

		if (clkVec.at(i)->getRight() != -1 && clkVec.at(clkVec.at(i)->getRight()) != NULL)
		{
			auto newNet = (*_db)._design.addNetToChip(
			clkVec.at(i)->myCell->getIndex(), 
			clkVec.at(clkVec.at(i)->getRight())->myCell->getIndex(),
			"clk" + std::to_string(numOfCLKNets), pinTypeRight,
			"CLOCK");	
			clockNetlist.push_back(newNet);
			numOfCLKNets++;
		}			
	}

	//std:: cout << "\n\nDone and done\n\n";
	//Routing from GCLK to the root of clock tree
	int GCLK = (*_db).getNetlist().findGCLKCell();
	if (GCLK == -1) { 
	myWarn( 0, " Error in RSFQ::routeClockNets : GCLK_Pad is not found; Skipping "); 
	}
	else { //adding a net from pin GCLK to the root of tree
			// true root of tree is the last index 
			//also, setting the myCell instance of dummy root of 
			//tree ( at index size/2 ) to GCLK pin
		//auto rootNode = clkVec.at( clkVec.size() / 2 );
		auto rootNode = clkVec.at( _superRootId );
		if ( rootNode == NULL ) {
			std::cerr << "Root of clock tree is NULL.\n";}
		else {
			myAssert2 ( rootNode->getParent() == -1, 
			 rootNode, " is not correct root Node.");


			//treating the super (dummy) root seperately
			if ( rootNode->isSinkNode() && rootNode->getParent() == -1){
				//correct (dummy) root
			  if ( clkVec.back()->getParent() == rootNode->getId())
			  {
				rootNode->myCell = &(*_db).getNetlist().getCellByIdx(GCLK);			
				std::cout << "GCLK cell: " << *(rootNode->myCell)
				 << "\n";

				auto curRootIdx = clkVec.back()->myCell->getIndex();
				auto GCLKNet = (*_db)._design.addNetToChip(GCLK, curRootIdx, "GCLK", 1, "CLOCK");
				numOfCLKNets++;
				clockNetlist.push_back(GCLKNet);			
			  }
			}
			 
		}
	}
	
	
	std::cout << "\tTotal Number of clockNets added is : " << numOfCLKNets << std::endl;
	std::cout << "\tSize of clockNets vector is : " << int(clockNetlist.size()) << std::endl;
	return clockNetlist;
} 

int CTS::findSplitterTypeBasedOnLocation
	(int par, int left, int right)
{	
	if (par == UL || par == UR) par = UP_UP;
	if (par == LL || par == LR) par = DOWN;
	
	if (left == UL || left == UR) left = UP_UP;
	if (left == LL || left == LR) left = DOWN;
	
	if (right == UL || right == UR) right = UP_UP;
	if (right == LL || right == LR) right = DOWN;

	if ((par == LEFT) && (left == LEFT) && (right == LEFT)) return SPLITCLK_2 ;
	if ((par == LEFT) && (left == LEFT) && (right == RIGHT)) return SPLITCLK_4 ;
	if ((par == LEFT) && (left == LEFT) && (right == UP_UP)) return SPLITCLK_4 ;
	if ((par == LEFT) && (left == LEFT) && (right == DOWN)) return SPLITCLK_4 ;
	if ((par == LEFT) && (left == RIGHT) && (right == LEFT)) return SPLITCLK_4 ;
	if ((par == LEFT) && (left == RIGHT) && (right == RIGHT)) return SPLITCLK_0 ;
	if ((par == LEFT) && (left == RIGHT) && (right == UP_UP)) return SPLITCLK_0 ;
	if ((par == LEFT) && (left == RIGHT) && (right == DOWN)) return SPLITCLK_0 ;
	if ((par == LEFT) && (left == UP_UP) && (right == LEFT)) return SPLITCLK_4 ;
	if ((par == LEFT) && (left == UP_UP) && (right == RIGHT)) return SPLITCLK_0 ;
	if ((par == LEFT) && (left == UP_UP) && (right == UP_UP)) return SPLITCLK_6 ;
	if ((par == LEFT) && (left == UP_UP) && (right == DOWN)) return SPLITCLK_0 ;
	if ((par == LEFT) && (left == DOWN) && (right == LEFT)) return SPLITCLK_4 ;
	if ((par == LEFT) && (left == DOWN) && (right == RIGHT)) return SPLITCLK_0 ;
	if ((par == LEFT) && (left == DOWN) && (right == UP_UP)) return SPLITCLK_0 ;
	if ((par == LEFT) && (left == DOWN) && (right == DOWN)) return SPLITCLK_4 ;
	if ((par == RIGHT) && (left == LEFT) && (right == LEFT)) return SPLITCLK_2 ;
	if ((par == RIGHT) && (left == LEFT) && (right == RIGHT)) return SPLITCLK_6 ;
	if ((par == RIGHT) && (left == LEFT) && (right == UP_UP)) return SPLITCLK_2 ;
	if ((par == RIGHT) && (left == LEFT) && (right == DOWN)) return SPLITCLK_2 ;
	if ((par == RIGHT) && (left == RIGHT) && (right == LEFT)) return SPLITCLK_6 ;
	if ((par == RIGHT) && (left == RIGHT) && (right == RIGHT)) return SPLITCLK_6 ;
	if ((par == RIGHT) && (left == RIGHT) && (right == UP_UP)) return SPLITCLK_6 ;
	if ((par == RIGHT) && (left == RIGHT) && (right == DOWN)) return SPLITCLK_6 ;
	if ((par == RIGHT) && (left == UP_UP) && (right == LEFT)) return SPLITCLK_6 ;
	if ((par == RIGHT) && (left == UP_UP) && (right == RIGHT)) return SPLITCLK_6 ;
	if ((par == RIGHT) && (left == UP_UP) && (right == UP_UP)) return SPLITCLK_6 ;
	if ((par == RIGHT) && (left == UP_UP) && (right == DOWN)) return SPLITCLK_2 ;
	if ((par == RIGHT) && (left == DOWN) && (right == LEFT)) return SPLITCLK_2 ;
	if ((par == RIGHT) && (left == DOWN) && (right == RIGHT)) return SPLITCLK_6 ;
	if ((par == RIGHT) && (left == DOWN) && (right == UP_UP)) return SPLITCLK_2 ;
	if ((par == RIGHT) && (left == DOWN) && (right == DOWN)) return SPLITCLK_4 ;
	if ((par == UP_UP) && (left == LEFT) && (right == LEFT)) return SPLITCLK_2 ;
	if ((par == UP_UP) && (left == LEFT) && (right == RIGHT)) return SPLITCLK_4 ;
	if ((par == UP_UP) && (left == LEFT) && (right == UP_UP)) return SPLITCLK_4 ;
	if ((par == UP_UP) && (left == LEFT) && (right == DOWN)) return SPLITCLK_4 ;
	if ((par == UP_UP) && (left == RIGHT) && (right == LEFT)) return SPLITCLK_4 ;
	if ((par == UP_UP) && (left == RIGHT) && (right == RIGHT)) return SPLITCLK_0 ;
	if ((par == UP_UP) && (left == RIGHT) && (right == UP_UP)) return SPLITCLK_0 ;
	if ((par == UP_UP) && (left == RIGHT) && (right == DOWN)) return SPLITCLK_4 ;
	if ((par == UP_UP) && (left == UP_UP) && (right == LEFT)) return SPLITCLK_4 ;
	if ((par == UP_UP) && (left == UP_UP) && (right == RIGHT)) return SPLITCLK_0 ;
	if ((par == UP_UP) && (left == UP_UP) && (right == UP_UP)) return SPLITCLK_0 ;
	if ((par == UP_UP) && (left == UP_UP) && (right == DOWN)) return SPLITCLK_4 ;
	if ((par == UP_UP) && (left == DOWN) && (right == LEFT)) return SPLITCLK_4 ;
	if ((par == UP_UP) && (left == DOWN) && (right == RIGHT)) return SPLITCLK_4 ;
	if ((par == UP_UP) && (left == DOWN) && (right == UP_UP)) return SPLITCLK_4 ;
	if ((par == UP_UP) && (left == DOWN) && (right == DOWN)) return SPLITCLK_4 ;
	if ((par == DOWN) && (left == LEFT) && (right == LEFT)) return SPLITCLK_2 ;
	if ((par == DOWN) && (left == LEFT) && (right == RIGHT)) return SPLITCLK_6 ;
	if ((par == DOWN) && (left == LEFT) && (right == UP_UP)) return SPLITCLK_6 ;
	if ((par == DOWN) && (left == LEFT) && (right == DOWN)) return SPLITCLK_2 ;
	if ((par == DOWN) && (left == RIGHT) && (right == LEFT)) return SPLITCLK_6 ;
	if ((par == DOWN) && (left == RIGHT) && (right == RIGHT)) return SPLITCLK_0 ;
	if ((par == DOWN) && (left == RIGHT) && (right == UP_UP)) return SPLITCLK_6 ;
	if ((par == DOWN) && (left == RIGHT) && (right == DOWN)) return SPLITCLK_6 ;
	if ((par == DOWN) && (left == UP_UP) && (right == LEFT)) return SPLITCLK_6 ;
	if ((par == DOWN) && (left == UP_UP) && (right == RIGHT)) return SPLITCLK_6 ;
	if ((par == DOWN) && (left == UP_UP) && (right == UP_UP)) return SPLITCLK_6 ;
	if ((par == DOWN) && (left == UP_UP) && (right == DOWN)) return SPLITCLK_6 ;
	if ((par == DOWN) && (left == DOWN) && (right == LEFT)) return SPLITCLK_2 ;
	if ((par == DOWN) && (left == DOWN) && (right == RIGHT)) return SPLITCLK_0 ;
	if ((par == DOWN) && (left == DOWN) && (right == UP_UP)) return SPLITCLK_0 ;
	if ((par == DOWN) && (left == DOWN) && (right == DOWN)) return SPLITCLK_0 ;
	
	//cerr << "Printing out deafult type" << std::endl;
	return SPLITCLK_0;
}


/* dbNet* CTS::addNetToChip
(unsigned sourceCell, unsigned sinkCell, 
	std::string newNetName, int outPinNum) 
{
	myWarn2 ( outPinNum == Constants::OUT_PIN_1 || outPinNum == Constants::OUT_PIN_2, " Wrong outPinNum: ", outPinNum);
	
	unsigned id = (*_db).getNetlist().getNumNets();
	
	const dbCell& src = (*_db).getNetlist().getCellByIdx(sourceCell);
	
	const dbCell& sink = (*_db).getNetlist().getCellByIdx(sinkCell);
	
	double pinPos = ( outPinNum == Constants::OUT_PIN_1 ) ? CLK_OUT_PIN_1_POS : CLK_OUT_PIN_2_POS;
	Point p2(pinPos, pinPos);
	dbPin* srcOutClkPin = new dbPin("pin"+std::to_string(outPinNum), "OUTPUT", outPinNum, p2);

	srcOutClkPin->setCell ( src );
	(*_db)._design._cellLib.at(sourceCell)->_pins.push_back(srcOutClkPin);
	myAssert2 ( srcOutClkPin->isDirOutput(), " srcOutClkPin is not PO:", (*srcOutClkPin));
	
	Point p1(CLK_IN_PIN_POS, CLK_IN_PIN_POS);  
	dbPin* sinkInClkPin = new dbPin("pin0", "INPUT", 0, p1);
	sinkInClkPin->setCell( sink ) ; 
	(*_db)._design._cellLib.at(sinkCell)->_pins.push_back(sinkInClkPin);	
	myAssert2 ( sinkInClkPin->isDirInput(), " sinkInClkPin is not PI:", (*sinkInClkPin));
	
	ctainerPins pins = {srcOutClkPin, sinkInClkPin} ;

	
	dbNetType nt("CLOCK");
	dbNet* newClockNet = new dbNet(newNetName, id, nt, pins);

	
	sinkInClkPin->setNet ( (*newClockNet) );
	srcOutClkPin->setNet ( (*newClockNet) );

	//std:: cout << "src pins: " << src.getPins() << "\n";
	//std:: cout << "sink pins: " << sink.getPins() << "\n";
	
	(*_db)._design._netLib.push_back(newClockNet);
	(*_db)._design._pinLib.push_back(srcOutClkPin);
	(*_db)._design._pinLib.push_back(sinkInClkPin);
	
	return newClockNet;
	
} */



void CTS::findAllLevels(int rootID, 
				const std::vector<dbClkCell*> &clkVec, int curLevel){
					
	myAssert3 ( rootID < int (clkVec.size()), rootID , 
	" is out of bounds for clkVec", clkVec.size());
	
	if (clkVec.at(rootID) != NULL)
		clkVec.at(rootID)->setHeight (curLevel+1) ;
	if (clkVec.at(rootID)->isSinkNode())
		return;
	
	if (clkVec.at(rootID)->getLeft() != -1)
	findAllLevels(clkVec.at(rootID)->getLeft(), clkVec, curLevel+1);

	if (clkVec.at(rootID)->getRight() != -1)
	findAllLevels(clkVec.at(rootID)->getRight(), clkVec, curLevel+1);	
	return;	
}


//Finds the level of each sink node in the binary tree
//returns true iff level difference between all leafs is only one
bool 
CTS::checkIfClockTreeIsBalanced
(const std::vector<dbClkCell*> &clkVec, 
	const std::vector<int> &clkSinkNodes)
{
	
	std::cout << "\tCheking to see if clock tree is balanced.\n" << std::endl;
    /*	
	int sinkSize = int(clkSinkNodes.size());
	int clkVecSize = clkVec.size();
	std::vector<int> sinkLevels(sinkSize, -1);
	//root of the tree has the id of clkVecSize-1
	findAllLevels(clkVecSize-1, clkVec, 0);
	for (int i=0; i < sinkSize; i++)
		sinkLevels[i] = clkVec[i]->getHeight();
    */
    auto sinkLevels = getHeightVec(clkVec, clkSinkNodes);
	
	//std::cout << clkVec << "\n";

			
 
	int maxL = *std::max_element(sinkLevels.begin(), sinkLevels.end());
	int minL = *std::min_element(sinkLevels.begin(), sinkLevels.end());
	
	//assert (maxL >= minL);
    myAssert3 (maxL >= minL, maxL, " maxHeight is smaller than minHeight ", minL );
	
	std::cout << "MaxL - MinL : " << maxL - minL << "\n\n\n\n\n" << std::endl;
	myWarn3 ( maxL - minL <= 1, maxL, " is larger than 1 + ", minL );
	
	if (maxL - minL > 1) return false;
	
	return true;
}


void CTS::doFinalPadPl()
{
	double  maxX = DBL_MIN ;
	BBox bb = (*_db)._rowDefs->getChipBbox();
	for (unsigned i=0; i < (*_db).getNetlist().getNumCells(); 
			i++ )
	{
		if ( (*_db).getNetlist().getCellByIdx(i).isFixed() ) continue;
		double x = (*_db)._spatial.locations[i].x + (*_db).getNetlist().getCellByIdx(i).getWidth();
		if ( greaterOrEqualDouble(x , bb.getTopRight().x ) )
			maxX = std::max (maxX, x) ;
	}
	
	//maxX -= bb.getBottomLeft().x;
	std::cout << "\tNew maxWidth is : " << maxX << std::endl;
	
	if ( greaterOrEqualDouble(maxX, _bbox.getTopRight().x) )
	{
		BBox finalBB ( _bbox.getBottomLeft().x,
				_bbox.getBottomLeft().y,
				maxX,
				_bbox.getTopRight().y );
		
		(*_db)._rowDefs->setChipBBox  ( finalBB );		
	}
	
	Placement fP( (*_db)._spatial.locations );
	padPl pp(_db, &fP );
	pp.reOrderPads( Point (-4*Constants::PAD_HEIGHT, -4*Constants::PAD_HEIGHT) );
	(*_db)._spatial.locations = fP;
	
	return;
}

