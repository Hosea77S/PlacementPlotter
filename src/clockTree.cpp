#include "clockTree.h"


std::pair<double, double>
  clockTree::getLRDelay
   (int parentId, const std::vector<double>& delayTree) {
   myAssert3 ( parentId >= 0 && parentId < (int)_tree.size(),
	parentId, " is out of bound for clock tree: ", _tree.size() );
 	
   int leftIdx = _tree.at(parentId)->getLeft();
   int rightIdx = _tree.at(parentId)->getRight();
	
   double lD, rD;
   lD = ( leftIdx <= -1 || leftIdx >= (int)_tree.size() ) ?
	0.0 : delayTree.at(leftIdx);
	
   rD = ( rightIdx <= -1 || rightIdx >= (int)_tree.size() ) ?
	0.0 : delayTree.at(rightIdx);
	
  return {lD, rD};
}
int clockTree::getMaxHeight() {
  std::vector<int> heights;
  for (auto& i: _tree)
    heights.push_back( i->getHeight() );
  
  int maxH = *max_element( heights.begin(), heights.end() );
  return maxH;
}
int clockTree::getNeighbor(int id) {
  if (id < 0) return -1;
  myAssert3 (id < (int)_tree.size(),
	id, " is out of bound for clock tree: ", _tree.size() );
	
  int parent = _tree.at(id)->getParent();
  if (parent == -1) return -1;
  if ( _tree.at(parent)->getLeft() == id )
	return _tree.at(parent)->getRight();
  
  return _tree.at(parent)->getLeft();
}
const dbCell* clockTree::getLeftCell(int id) const {
  int leftId = _tree.at(id)->getLeft();
  if ( leftId == -1) return NULL;
  return _tree.at(leftId)->getCell();
  
}
const dbCell* clockTree::getRightCell(int id) const {
  int rightId = _tree.at(id)->getRight();
  if ( rightId == -1) return NULL;
  return _tree.at(rightId)->getCell();
}
const dbClkCell* clockTree::getLeftClkCell(int id) const {
  int leftId = _tree.at(id)->getLeft();
  if ( leftId == -1) return NULL;
  return _tree.at(leftId);
}
const dbClkCell* clockTree::getRightClkCell(int id) const {
  int rightId = _tree.at(id)->getRight();
  if ( rightId == -1) return NULL;
  return _tree.at(rightId);
}
//replaces the parent of node with minimum insertion delay //to increase the min clock tree delay and reduce the skew //returns true if it was successfull in improving the skew bool 
bool clockTree::minimizeSkew(bool minMaxDelay, double coef) {
  
  std::cout << "\n\nCalculating skew on internal tree nodes\n";
  auto delayTree = calcAllDelay(true);
  auto leafTree = calcLeafDelay(true);
  auto ct = _tree;
  std::sort(ct.begin(), ct.end(), CompareClkCellsByHeight());
  
  //auto maxH = getMaxHeight();
  auto maxElement = std::max_element(leafTree.begin(), leafTree.end());
  auto minElement = std::min_element(leafTree.begin(), leafTree.end());
  
  double maxDelay = *maxElement;
  double minDelay = *minElement;
  int maxDelayNode = std::distance( leafTree.begin(), maxElement );
  int minDelayNode = std::distance( leafTree.begin(), minElement );
  
  auto maxClkCell = _tree.at(maxDelayNode);
  auto maxParentClkCell = _tree.at(maxClkCell->getParent());
  
  auto minClkCell = (minMaxDelay) ?
					_tree.at(maxDelayNode):
					_tree.at(minDelayNode);
  auto minParentClkCell = _tree.at(minClkCell->getParent());
  
  
  std::cout << "\nMaxDelay Node: " << *_tree.at(maxDelayNode) << " l,r of parent = " << getLRDelay(maxParentClkCell->getId(), delayTree) << "\n";
  std::cout << "\nMinDelay Node: " << *_tree.at(minDelayNode) << " l,r of parent = " << getLRDelay(minParentClkCell->getId(), delayTree) << "\n";
  
  auto minParentCell = (minMaxDelay) ?
                           maxParentClkCell->myCell :
						     minParentClkCell->myCell;
							 
  auto minParent_parentClkCell = (minMaxDelay) ?
					_tree.at(maxParentClkCell->getParent()):
					_tree.at(minParentClkCell->getParent());
					
  auto minParent_parentCell = minParent_parentClkCell->myCell;
  double xP,xC,yP,yC,yPrimP,yPrimC;
  auto minPP = (*_pl)[minParent_parentCell->getIndex()];
  auto curPl = (*_pl)[ minParentCell->getIndex()];
  auto minC = (*_pl)[minClkCell->myCell->getIndex()];
  xP = minPP.x; yP = minPP.y;
  xC = minC.x ; yC = minC. y;
  yPrimP = abs ( curPl.y - yP );
  yPrimC = abs ( curPl.y - yC );
  auto COM = getMedian ( minPP, minC );
  Point sol1 = COM, sol2 = COM;
    
  double skew = (maxDelay - minDelay) * Constants::SPEED_OF_PTL * 1.0;
  if (minMaxDelay) skew *= -1.0;
  std::cout << "Node: " << *minParentCell
  << " loc = " << (*_pl)[ minParentCell->getIndex() ]
  << " parent, child Pl: " << minPP << "," << minC;
  
  //case 1: sol1 = COM + (s/2.0)
  sol1.x = COM.x + (( skew - yPrimC - yPrimP) /2.0);
  sol2.x = COM.x + (( yPrimC + yPrimP - skew) /2.0);
  bool sol1Valid = false, sol2Valid = false;
  std::cout << "\tsol1: " << sol1.x << "| sol2: " << sol2.x << "\n";
  
  if ( lessOrEqualDouble( xC, sol1.x ) &&
	   lessOrEqualDouble( xP, sol1.x ) ) // xC < x && x > xPP
  {// this is a valid solution
	//COM = sol1;
	sol1Valid = true;
  }
  if ( lessOrEqualDouble( sol2.x, xC ) &&
	   lessOrEqualDouble( sol2.x, xP ) ) // x < xL && x < xP
  {
	sol2Valid = true;
  } 
  if ( !sol1Valid && !sol2Valid )
  {
	std::cout << "\n\nNo solutions found to improve the skew, returning";
    return false;
  }
  
	
  double sol1Inc = 0.0, sol2Inc = 0.0;
  auto oldPl = (*_pl)[ minParentCell->getIndex() ];
  if (sol1Valid){
    (*_pl)[ minParentCell->getIndex() ].x = sol1.x;
	delayTree = calcAllDelay(true);
    sol1Inc = delayTree.at( minClkCell->getId() ) - minDelay;
	std::cout << "| sol1: " << sol1 <<
	  " | NewLocation: " << (*_pl)[ minParentCell->getIndex() ] <<
	  " , new l,r = " << getLRDelay(minParentClkCell->getId(), delayTree) << "|delayInc: " << sol1Inc << "\n";
	  //reversing the change
	  (*_pl)[ minParentCell->getIndex() ].x = oldPl.x;
  }	
  if (sol2Valid)
  {
    (*_pl)[ minParentCell->getIndex() ].x = sol2.x;
	delayTree = calcAllDelay(true);
    sol1Inc = delayTree.at( minClkCell->getId() ) - minDelay;
	std::cout << "| sol2: " << sol2 <<
	  " | NewLocation: " << (*_pl)[ minParentCell->getIndex() ] <<
	  " , new l,r = " << getLRDelay(minParentClkCell->getId(), delayTree) << "|delayInc: " << sol1Inc << "\n";
	  //reversing the change
	  (*_pl)[ minParentCell->getIndex() ].x = oldPl.x;
  }	  
  if ( lessOrEqualDouble(sol1Inc, 0.0) && lessOrEqualDouble(sol2Inc, 0.0) )
  {
	std::cout << "\n\nNo benefit from sol1 and sol2 to improve the skew, returning";
	return false;
  }
  (*_pl)[ minParentCell->getIndex() ].x =
	( greaterOrEqualDouble(sol1Inc, sol2Inc) ) ?
		sol1.x : sol2.x;
    
  COM = (*_pl)[ minParentCell->getIndex() ];
  delayTree = calcAllDelay(true);
  
  std::cout << "\n COM: " << COM <<
  " | NewLocation: " << (*_pl)[ minParentCell->getIndex() ] <<
  " , new l,r = " << getLRDelay(minParentClkCell->getId(), delayTree) << "\n";
  
  
  return true;
}
std::vector<double> clockTree::calcLeafDelay
  (bool useDbCell) {
  std::sort (_tree.begin(), _tree.end(), CompareClkCellsByID());
  std::vector<double> delayTree(_tree.size(), 0.0);
  calcDelay_sub (_rootId, delayTree, 0.0, useDbCell);
  
  std::vector<double> leafDelays;
  for (unsigned i=0; i < _tree.size(); i++)
    if (_tree.at(i)->isSinkNode() && _tree.at(i)->getParent() != -1)
      leafDelays.push_back( delayTree.at(i) );
  
  
  return leafDelays;
}
std::vector<double> clockTree::calcAllDelay
  (bool useDbCell) {
  std::sort (_tree.begin(), _tree.end(), CompareClkCellsByID());
  std::vector<double> delayTree(_tree.size(), 0.0);
  calcDelay_sub (_rootId, delayTree, 0.0, useDbCell);
  
  return delayTree;
}
double
 clockTree::calcDistFromChild
  (int id, Dir d, Child ch, bool useDbCell) {
  myAssert3( id >= 0 && id < (int)_tree.size(),
	id, " is out of bound for clock tree: ", _tree.size() );
 
  auto curClkCell = _tree.at(id);
  double delay;
  
  if (useDbCell) // works on dbCell instances
  {
	  if (!curClkCell->myCell) return 0.0;
	  auto childCell = (ch == _LEFT) ?
	    getLeftCell( id ) :
		  getRightCell(id) ;
		  		   
	  if (childCell){ //for the case of one output spl (hold budfs)

/*       std::cout << "Location of " << curClkCell->myCell->getName() << " : " << 	
           (*_pl)[curClkCell->myCell->getIndex()] << "\n";	  
      std::cout << "Location of " << childCell->getName() << " : " << 	
           (*_pl)[childCell->getIndex()] << "\n"; */	  
		  
		  
		delay = ( d == _XX) ?
		fabs((*_pl)[curClkCell->myCell->getIndex()].x - (*_pl)[childCell->getIndex()].x):
		fabs((*_pl)[curClkCell->myCell->getIndex()].y - (*_pl)[childCell->getIndex()].y) ;
		 
	  } else delay = 0.0;
	  
  } else // works on dbClkCell instances
  {
	  auto childCell = (ch == _LEFT) ?
		getLeftClkCell( id ) :
		 getRightClkCell(id);
	  if (childCell){ //for the case of one output spl (hold budfs)
		delay = (d == _XX) ?
		fabs ( curClkCell-> getOrigin().x - childCell->getOrigin().x ) :
		fabs ( curClkCell-> getOrigin().y - childCell->getOrigin().y );
	  
	  } else delay = 0.0;
  }	  
 
  return delay;
 
}
//returns a pair <leftCellDelay, rightCellDelay> std::pair<double,double>
std::pair<double,double> 
 clockTree::calcLeftRightDelay
  (int id, bool useDbCell) {
  myAssert3( id >= 0 && id < (int)_tree.size(),
	id, " is out of bound for clock tree: ", _tree.size() );
  
  double leftDelay, rightDelay;
  
/* auto curClkCell = _tree.at(id);
   if (useDbCell) // works on dbCell instances
  {
	  auto leftCell = getLeftCell( id );
	  if (leftCell){ //for the case of one output spl (hold budfs)
		leftDelay = abs((*_pl)[curClkCell->myCell->getIndex()].x - (*_pl)[leftCell->getIndex()].x);
		leftDelay += abs((*_pl)[curClkCell->myCell->getIndex()].y - (*_pl)[leftCell->getIndex()].y) ;
	  } else leftDelay = 0.0;
	  auto rightCell = getRightCell( id );
	  if (rightCell){
		rightDelay = abs((*_pl)[curClkCell->myCell->getIndex()].x - (*_pl)[rightCell->getIndex()].x);
		rightDelay += abs((*_pl)[curClkCell->myCell->getIndex()].y - (*_pl)[rightCell->getIndex()].y) ;
	  } else rightDelay = 0.0;
	  
  } else // works on dbClkCell instances
  {
	  auto leftCell = getLeftClkCell( id );
	  if (leftCell){ //for the case of one output spl (hold budfs)
		leftDelay = abs ( curClkCell-> getOrigin().x - leftCell->getOrigin().x );
		leftDelay += abs ( curClkCell-> getOrigin().y - leftCell->getOrigin().y );
	  
	  } else leftDelay = 0.0;
	  auto rightCell = getRightClkCell( id );
	  if (rightCell){
		rightDelay = abs ( curClkCell-> getOrigin().x - rightCell->getOrigin().x );
		rightDelay += abs ( curClkCell-> getOrigin().y - rightCell->getOrigin().y );
	  } else rightDelay = 0.0;
	  
  } */
  
  leftDelay = calcDistFromChild(id, _XX, _LEFT, useDbCell) +
	calcDistFromChild(id, _YY, _LEFT, useDbCell);
	
  rightDelay = calcDistFromChild(id, _XX, _RIGHT , useDbCell) +
	calcDistFromChild(id, _YY, _RIGHT, useDbCell);
  
  //technology dependent, 100um ~ 1ps
  leftDelay /=  Constants::SPEED_OF_PTL;
  rightDelay /= Constants::SPEED_OF_PTL;
  
  
  //std::cout << "\nNode: " << _tree.at(id) << " l,r delays: [" <<
  //leftDelay << "," << rightDelay << "]\n";
  
  return std::make_pair(leftDelay, rightDelay);
}
std::vector<double> clockTree::calcDelay
  (bool useDbCell) {
  std::sort (_tree.begin(), _tree.end(), CompareClkCellsByID());
  //std::cout << "\n\n\n\tClkTree: " << _tree << "\n\n\tRoot: " << _rootId << "\n\n";
  std::vector<double> delayTree(_tree.size(), 0.0);
  calcDelay_sub (_rootId, delayTree, 0.0, useDbCell);
  //for (unsigned i=0; i < delayTree.size(); i++)
    //std::cout << i << ": " << delayTree.at(i) << "\n";
  std::vector<double> leafDelays;
  for (unsigned i=0; i < _tree.size(); i++)
    if (_tree.at(i)->isSinkNode() && _tree.at(i)->getParent() != -1)
      leafDelays.push_back( delayTree.at(i) );
  
  //std::cout << "\nLeafDelays vec: \n" << leafDelays << "\n";
  std::cout << "\n\tSize of the leafDelays vec: " << leafDelays.size() << "\n";
  
/*   for (unsigned i=0; i < _tree.size(); i++)
	if (_tree.at(i)->getCell())
    std::cout << "Cell: " << _tree.at(i)->getCell()->getName() << " delay: " << delayTree.at(i) << "\n"; */	  
  
  double skew = calcSkew(leafDelays);
  std::cout << "\n\n\tClock Skew: " << skew << "\n\n";
  	
  return leafDelays;
}
double clockTree::calcSkew(const std::vector<double>& leafDelays) {
  double maxDelay = *std::max_element(leafDelays.begin(), leafDelays.end());
  double minDelay = *std::min_element(leafDelays.begin(), leafDelays.end());
  
  myAssert3 ( greaterOrEqualDouble( maxDelay, minDelay ),
  maxDelay, " maxLeaf dealy is not >= minleaf Delay: ", minDelay );
  
  std::cout << "\n\tMax-Min leafDelays: [" <<
	maxDelay << "," << minDelay << "]\n\n";
  
  double skew = maxDelay - minDelay;
  return skew;
}
void clockTree::calcDelay_sub
  (int id, std::vector<double>& delayTree, double curDelay, bool useDbCell) {
  if (id == -1) return;
  auto curClkCell = _tree.at(id);
  if ( curClkCell->getId() == -1 ) return ;
  //std::cout << "\nCurClkCell: " << *curClkCell << "\n";
  myAssert3 ( curClkCell->getId() == id,
  curClkCell->getId(), " is not equal to id: ", id);
   
  if (curClkCell->isSinkNode())
  {
    delayTree[curClkCell->getId()] = curDelay;
	  return ;
  }
  
  //no longer valid, maybe done only on clkCells
  //myAssert3 ( curClkCell->getCell(), " myCell for cell " ,
	//*curClkCell, " is null.");
  
  double leftDelay, rightDelay;
  
  auto delays = calcLeftRightDelay (curClkCell->getId(), useDbCell);
  leftDelay = delays.first;
  rightDelay = delays.second;
 
  
  //double skew = std::abs(
  calcDelay_sub(curClkCell->getLeft(), delayTree, curDelay+leftDelay+Constants::SPL_DELAY, useDbCell);
  calcDelay_sub(curClkCell->getRight(), delayTree, curDelay + rightDelay+Constants::SPL_DELAY, useDbCell);
   
  delayTree[curClkCell->getId()] = curDelay;
  
  return;
}
