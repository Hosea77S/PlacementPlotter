#include "MMM.h"


ClkVec MMM::getClkSinksPostTop
 (ClkVec& clkTop)
{
  ClkVec newSinks;
  for (auto& i: clkTop)
    if (i.isSinkNode())
      newSinks.push_back( i );		

  return newSinks;  
}


std::vector<int> MMM::getClkSinks()
{
  return _clockSinks;
}


//builds clk tree topology using MMM cts alg.
//writes the topology into output file
std::string MMM::buildTopology()
{
  ClkVec clkTopology;
  auto clkSinkIds = getClkSinks();
  unsigned numClkSinks = clkSinkIds.size();  
  int sizeOfTop = (2*numClkSinks) -1;
  
  basicMMM(clkSinkIds, clkTopology);
  changeIds(clkTopology);  
  //std::cout << "\n\n\tClk Tree: \n" << clkTopology << "\n";
  myAssert3 ( sizeOfTop == (int)clkTopology.size(),
			  sizeOfTop,
             " Invalid size of topology vector ", 
			   clkTopology.size());
  
  isClockTreeBalanced(clkTopology); 
  updatePlacement(clkTopology); //adds placement of tapping points  
  std::string topFileName = (*_db).getDesignPath() + "/" + (*_db).getDesignName() + "_topology.top";
  writeTopology(topFileName, clkTopology);
  std::string clockTopDotName = (*_db).getDesignPath() + "/" + (*_db).getDesignName() + "_topology.graph";
  drawClockTreeTop(clockTopDotName, clkTopology);

  _clkTop = clkTopology;
  
  return topFileName;	
}

// for pre-cts-buffer-insertion
//builds clk tree topology using MMM cts alg.
//writes the topology into output file
 std::string MMM::buildTopology2
  (std::vector<dbClkCell>& newSinks, std::map<int,int>& new2OldMap)
{
  ClkVec clkTopology;
  auto clkSinkIds = getClkSinks();
  //unsigned numClkSinks = clkSinkIds.size();  
  
  basicMMM(clkSinkIds, clkTopology);
  insertDummyNodes(clkTopology);  
  new2OldMap = changeIds2(clkTopology);  
  std::cout << "\n\n\tClk Tree: " << clkTopology.size() << "\n";
  
  //after adding dummy nodes, this doesn't hold anymore. disabled

  
  isClockTreeBalanced(clkTopology); 
  //updatePlacement(clkTopology); //adds placement of tapping points  
  std::string topFileName = (*_db).getDesignPath() + "/" + (*_db).getDesignName() + "_topology.top";
  writeTopology(topFileName, clkTopology);
  std::string clockTopDotName = (*_db).getDesignPath() + "/" + (*_db).getDesignName() + "_topology.graph";
  drawClockTreeTop(clockTopDotName, clkTopology);
  
  newSinks = getClkSinksPostTop(clkTopology);
  
  
  _clkTop = clkTopology;
  
  
  return topFileName;	
} 


//inserts dummy nodes for nodes with level= maxLevel - 1
//after this, all nodes should have the same level (height)
void MMM::insertDummyNodes(ClkVec& clkTop)
{
  std::vector<unsigned> heights;	
  for (auto& i: clkTop){
    //std:: cout << i << "\n";	  
	heights.push_back(i.getHeight());  
  }
  
  int maxH = *std::max_element(heights.begin(), heights.end());
  int maxId = clkTop.size()+1;
  
  for ( unsigned i=0; i < clkTop.size(); i++ )
  {
    auto curCell = clkTop.at(i);
	if (curCell.getHeight() == maxH - 1)
	{ 
      if (curCell.getId() < (int)getClkSinks().size())
	  { //found a leaf node with height = max - 1
        //std::cout << "CurCell: " << curCell << "\n";
        auto newPlace = (_pl)[curCell.getId()];//Point((_pl)[curCell.getId()].x - SPL_WIDTH, (_pl)[curCell.getId()].y);		
        dbClkCell dummy1(maxId++, -1, -1, curCell.getId(), maxH, Point(newPlace.x-0.9, newPlace.y), NULL);
        dbClkCell dummy2(maxId++, -1, -1, curCell.getId(), maxH, Point(newPlace.x, newPlace.y), NULL);
			
        //curCell.setLeft( dummy1.getId() );
        //curCell.setRight( dummy2.getId() );
		
		clkTop.push_back(dummy1);
		clkTop.push_back(dummy2);
		
	  }		
	}		
  }
  
/*   std::cout << "\n\n\n\t\tPost adding dummy cells: \n";    
  for (auto& i: clkTop){
    std:: cout << i << "\n";	  
  } */
  
  return;	
}  



void MMM::updatePlacement(const ClkVec& top)
{
  ClkVec tmp (top);
  std::sort (tmp.begin(), tmp.end(), CompareClkCellsByID());  
  unsigned n = getNumClkSinks();
  for (unsigned i=0; i < tmp.size(); i++)
  {
	auto curPos = tmp.at(i).getOrigin();
	if ( i < n )
	{ //these are sinks, placement should be same 
	  myAssert3 ( (_pl)[i] == curPos,
				  (_pl)[i], 
				   " is not consistent with tapping point: ",
				   curPos ) ;  
		
	}  
    //else if ( i == n ) //this is supernood, doesn't have placement
	//	continue;
	else //these are tapping poinst
	  (_pl).addToPlacement( curPos );
	  
  }
  
  myAssert3 ( (_pl).getSize() == (int)top.size(),
				(_pl).getSize(), " is diff from ",
				top.size());
  return;	
}

Point MMM::getCOM(const std::vector<int>& ids)
{
  unsigned n = ids.size();
  std::vector<Point> pts(n);
  for (unsigned i=0; i < n; i++)
    pts[i] = (_pl)[ ids.at(i) ];
  Placement pl(pts);
  return pl.getCenterOfGravity();	
}

void MMM::changeIds(ClkVec& clkTop)
{
  std::map <int, std::vector<int>> par2child;
   for (auto& i: clkTop)
  {
    if ( par2child.find(i.getParent()) != par2child.end() )
      par2child[i.getParent()].push_back(i.getId());
    else
      par2child[i.getParent()] = {i.getId()};		
  }

  for (auto& i: clkTop)
  {
	//only sink nodes don't have any children, continue
	if ( par2child.find( i.getId() ) == par2child.end() )
	{
      myAssert2 ( i.getId() < (int)getClkSinks().size(), 
               i, "doesn't have any children" );
      continue;		
	}
  
    auto children = par2child[i.getId()];
	//myAssert3 (children.size() == 2, i, " Doesn't have 2 children: ", children);
	std::sort(children.begin(), children.end());
	i.setLeft(children.at(0));
	if (children.size() > 1)
		i.setRight(children.at(1));  
  }  
  
  std::sort (clkTop.begin(), clkTop.end(), CompareClkCellsByHeight());  
  
  return;	
}
 

// for pre-cts-buffer-insertion
std::map<int,int> MMM::changeIds2(ClkVec& clkTop)
{
  std::map <int, std::vector<int>> par2child;
   for (auto& i: clkTop)
  {
    if ( par2child.find(i.getParent()) != par2child.end() )
      par2child[i.getParent()].push_back(i.getId());
    else
      par2child[i.getParent()] = {i.getId()};		
  }

  //std::cout << "\nPar2Child:\n" << par2child << "\n";
  for (auto& i: clkTop)
  {
	//only sink nodes don't have any children, continue
	//after adding dummy nodes, this doesn't work anymore, cause 
	//dummy nodes have id > number of sinks, disabled
 	if ( par2child.find( i.getId() ) == par2child.end() )
	{
      //myAssert2 ( i.getId() < (int)getClkSinks().size(), 
               //i, "doesn't have any children" );
      continue;		
	} 
	
  
    auto children = par2child[i.getId()];
	//myWarn3 (children.size() == 2, i, " Doesn't have 2 children: ", children);
	
	std::sort(children.begin(), children.end());
	i.setLeft(children.at(0));
	if (children.size() > 1)
		i.setRight(children.at(1));  
  }  
  
  std::sort (clkTop.begin(), clkTop.end() ,   	
				 CompareClkCellsByHeight_Id()); 

  //traversing in reverse order				   
  std::map <int,int> old2newIds;
  int clkTopSize = clkTop.size();  
  //old superRoot to new superRoot
  old2newIds[ getNumClkSinks() ] = (int)( clkTopSize / 2) + 1;
  old2newIds[-1] = -1;
  for ( int i=clkTopSize-1; i>=0; i-- )
  {
    //if ( i == (int)( clkTopSize / 2) + 1 ) continue;
    if ( i >= (int) (clkTopSize/2) )	
      old2newIds[ clkTop.at(i).getId() ] = clkTopSize - 1 - i;	
    else if ( i < (int) (clkTopSize/2) )
      old2newIds[ clkTop.at(i).getId() ] = clkTopSize - i;	
		
  }	  
  
  //std::cout << "Old2NewIds(" << old2newIds.size()  << "): " << old2newIds << "\n";
  
  for (int i=0; i < clkTopSize; i++)
  {
    auto cc = clkTop.at(i);
    clkTop.at(i).setId ( old2newIds[cc.getId()] );     	
    clkTop.at(i).setParent ( old2newIds[cc.getParent()] );     	
    clkTop.at(i).setLeft ( old2newIds[cc.getLeft()] );     	
    clkTop.at(i).setRight ( old2newIds[cc.getRight()] );     	
  }	  
  
  std::cout << "newClkTop(" << clkTop.size()  << ")\n: ";// << clkTop << "\n";
  
  std::map<int,int> new2OldMap;
  for (auto&i:old2newIds)
	new2OldMap[i.second] = i.first;
  
  return new2OldMap;	
}
 
void MMM::basicMMM 
 (std::vector<int>& sinkIds, ClkVec& clkTop, Dir d)
{
  int numClkSinks = sinkIds.size();
  if (numClkSinks < 1) return;
  int superRootId = ( numClkSinks * 2 ) - 1 ;
  
  int lastIdx = superRootId;
  basicMMM_sub(sinkIds, clkTop, lastIdx, numClkSinks, 0, d);
  	
}

void MMM::basicMMM_sub 
  (std::vector<int>& sinkIds, ClkVec& clkTop, 
    int& idx, int par, int h, Dir dir)
{
	
  int numClkSinks = sinkIds.size();
  if (numClkSinks < 1) return;
  if ( numClkSinks == 1 )
  {
	int id = sinkIds.front();  
	if (id < (_pl).getSize())
	{
      dbClkCell curCell(id, -1, -1, par, h, (_pl)[id], NULL);
      clkTop.push_back( curCell );
      return;			
	}
  }	   
  int myIdx = idx--;
  
  Point com = getCOM(sinkIds);  
  dbClkCell curCell(myIdx, -1, -1, par, h, com, NULL);
  clkTop.push_back( curCell );	  
	  
  int leftIdx = (int) numClkSinks/2;
  int rightIdx = leftIdx;

  if (dir == _XX)
    std::sort( sinkIds.begin(), sinkIds.end(), 
		CompareCellIdsByX( *const_cast<Placement*> (&_pl) ) );
  else
    std::sort( sinkIds.begin(), sinkIds.end(), 
		CompareCellIdsByY( *const_cast<Placement*> (&_pl) ) );
	  
  std::vector<int> leftIds, rightIds;
  leftIds.insert(leftIds.begin(), sinkIds.begin(), sinkIds.begin()+leftIdx);
  rightIds.insert(rightIds.begin(), sinkIds.begin()+rightIdx, sinkIds.end() );

  //std::cout << "ID: " << myIdx << "\nLeft: " << leftIds << "\nRight: " << rightIds << "\n";
  myAssert3( abs((int)(leftIds.size() - rightIds.size())) <= 1, 
   leftIds.size(), " diff is more than 1 ", rightIds.size());  

  Dir nextDir = (dir == _XX) ? _YY : _XX;   
  basicMMM_sub (leftIds,  clkTop, idx, myIdx, h+1, nextDir);
  basicMMM_sub (rightIds, clkTop, idx, myIdx, h+1, nextDir);

  return;  
}


void MMM::writeTopology(std::string fileName, const ClkVec& top)
{
  ctsParser cP ((*_db).getDesignName(), (*_db).getDesignPath());	
  cP.write2TopologyFile(fileName, top);   	
  std::cout << "\n\n\tFinished writing into topology file: " << fileName << " \n\n";
  return;	
}

void MMM::drawClockTreeTop(std::string fileName, const ClkVec& top)
{
  ctsParser cP ((*_db).getDesignName(), (*_db).getDesignPath());	
  cP.writeTopology2DotFile(fileName, top);   	
  std::cout << "\n\n\tFinished writing topology to dot file: " << fileName << " \n\n";
  return;	
}

bool MMM::isClockTreeBalanced(const ClkVec& clkTree)
{
  ClkVec tmp(clkTree);	 
  std::sort(tmp.begin(), tmp.end(), CompareClkCellsByID());
  unsigned n = getClkSinks().size();
  tmp.erase(tmp.begin()+n, tmp.end());
  //std::cout << "Tmp: " << tmp << "\n";
  
  auto maxH = *std::max_element(tmp.begin(), tmp.end(), CompareClkCellsByHeight());
  auto minH = *std::min_element(tmp.begin(), tmp.end(), CompareClkCellsByHeight());
  int maxHeight = maxH.getHeight();
  int minHeight = minH.getHeight();
 
  myAssert3 (maxHeight >= minHeight, maxHeight, " maxHeight is smaller than minHeight ", minHeight );
  std::cout << "MaxH - MinH : " << maxHeight - minHeight << "\n\n\n\n\n" << std::endl;
  myAssert3 ( maxHeight - minHeight <= 1, maxHeight, " is larger than 1 + ", minHeight );
  if (maxHeight - minHeight > 1) return false;
   
  return true;  
	
}

