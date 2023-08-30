#include "timingAna.h"

/* 
//finds id of the cells between two cells, src & des
bool 
  findPath(dbCell* src, dbCell* dest, std::vector<int>& path)
{
  if (src == dest) return;
  if (src->isFixed()) return;  
  for (auto itP = (*src).pinsBegin(); itP != (*src).pinsEnd(); itP++ )
  {
    if (( *itP )->isDirOutput())
	{
      for (auto itC = (*itP)->getNet().cellsBegin(); itC!=(*itP)->getNet().cellsEnd();
	  itC++)
	  {
        if (*itC)->getIndex() != (*src).getIndex()
		{
          if ( findPath (  ) )			
		}			
	  }	  
		
	}	  
  }	  
  
} */



//returns a vector of net ids 
std::vector< std::tuple <int, int, int, double> > 
  timingAna::findHoldNets( std::vector< tuple4dStr >& hvp )
{
  std::vector< std::tuple <int, int, int, double> > outVec;	
  for (auto &x: hvp)
  {
    std::string st1, st2, st3, st4;
    double slack;	
	std::tie (st1, st2, st3, st4) = x;	  
	slack = stof(st3);
	if ( greaterOrEqualDouble (slack, Constants::SLACK_UNCERTAINTY ) ) continue;
    auto cell1 = (*_db).getNetlist()._nameCellMap.at( st1 );
    auto cell2 = (*_db).getNetlist()._nameCellMap.at( st2 );
	int cellId1 = (*cell1).getIndex();
	int cellId2 = (*cell2).getIndex();
	
	auto cmnNets = (*cell1).getCommonNets({cell1, cell2});
    //myWarn3(cmnNets.size(), (*cell1).getIndex(), " size of the cmn nets of cells is 0, ", (*cell2).getIndex());	
    //reported net is a path, find the net input to 2nd cell and insert the hold buff there    	
	//assumption: cell1 has only one output, i.e., is not splitter
	//pins are 2-pin nets
	if ( cmnNets.size() == 0 ) continue;
/* 	if ( cmnNets.size() == 0 )
	{
	bool found = false;
	for (auto pIt = (*cell1).pinsBegin(); pIt != (*cell1).pinsEnd(); pIt++)
    {
      if ((*pIt)->isDirOutput())		
	  {
        cmnNets.push_back( (*pIt)->getNet().getId() );
        auto targetNet = (*pIt)->getNet().getId();		
		for (auto nIt = (*_db).getNetlist().getNetByIdx(targetNet).cellsBegin(); 
		 nIt != (*_db).getNetlist().getNetByIdx(targetNet).cellsEnd(); nIt++)
		{
		  if ( (int)(*nIt)->getIndex() != cellId1 ){
		    cellId2 = (*nIt)->getIndex();	  
			cell2 = (*_db).getNetlist()._nameCellMap.at((*nIt)->getName());
			found = true;
		    break ; 
		  }	
		}
		if (found) break;		
	  }		  
	}		
	} */
	
	
	std::cout << "Cell1: " << *cell1 << 
	  "\nCell2: " << *cell2 << "\n";	
   
    std::cout << "Common nets: " << (*_db).getNetlist().getNetByIdx( cmnNets.front() ) << "\n";
	
	myAssert2 (cmnNets.size() == 1, " More than one common nets exist: ", cmnNets ); 
	
	outVec.push_back ( std::make_tuple( cellId1, cellId2, cmnNets.front(), slack ) );
	
  }	  

  //std::cout << "Critial nets and Hold slacks: " << outVec << "\n";
  
  return outVec; //{ std::make_pair(1, -1) };	
}

int timingAna::calcNumHoldBuffs(double slack)
{
  //return (int) std::ceil( fabs (slack) / fabs ( Constants::JTL_DELAY ) );  
  return (int) std::ceil( fabs (slack) / fabs ( Constants::SPL_DELAY ) );  
}	

dbCell* 
  timingAna::addNewJTLCell(Point sinkPl, Point srcPl, int tCnt, int idx)  
{
	
  int numCells = (*_db).getNetlist().getNumCells();  
  Symmetry s1("Y");
  ctainerPins pVec = {};
  int id = numCells++ ;
  //std::string name = "JTL_HOLD_" + std::to_string(id);
  std::string name = "Split_HOLD_" + std::to_string(id);
  
  //double cellWidth = Constants::JTL_WIDTH;  
  double cellWidth = Constants::SPL_WIDTH;  
  //double cellHeight = (*_db)._rowDefs->getRowHeight();  
  //double cellHeight = Constants::JTL_HEIGHT;  
  double cellHeight = Constants::SPL_HEIGHT;  
  double xLoc = 
    ( lessOrEqualDouble ( srcPl.x, sinkPl.x)  ) ? 
	   sinkPl.x - cellWidth - ((tCnt - idx) * 0.5) : sinkPl.x + cellWidth + ((tCnt - idx) * 0.5);  
	   
  dbCell* node = new dbCell (name, "CORE", "CC", 
  		  id, cellWidth, cellHeight, 
  			Point( xLoc, sinkPl.y), 
  			  0, pVec, s1);		
			  
  int plSize = (*_db)._spatial.locations.getSize();			  
  myAssert3 ( plSize == numCells - 1,
			  plSize, " size of placement vec is not = numCells - 1", numCells - 1);			  
  (*_db)._spatial.locations.addToPlacement ( node->getOrigin() );
  (*_db)._design._nameCellMap[name] = node;		
  (*_db)._design._cellLib.push_back(node);
	
  return node;		
}  


//creates n hold buffers, connects cells 1...n, locates each cell in the cell place as the source cell
std::vector<dbCell*> 
 timingAna::createHoldBuffCells
   ( int numHoldBuffs, Point sinkPl, Point srcPl )
{
	
  if (numHoldBuffs <= 0)
  { 
    myWarn2 (0, "numHoldBuffs is: " , numHoldBuffs);
	return {};
  }	  

  std::vector<dbCell*> newCells;  

  for (int i=0; i < numHoldBuffs; i++)
    newCells.push_back( addNewJTLCell(sinkPl, srcPl, numHoldBuffs, i)	);
		  
  		
  myAssert3 ( (int) newCells.size() == numHoldBuffs  ,
				newCells.size(), " # of new cells is not = #HoldBuffs ", numHoldBuffs );

  std::cout << "NewCells: " << newCells << "\n";  
  
  return newCells;	
}


//reconnects the original critial net from the src cell to the first hold buffer,
// adds a net from the last hold to the sink cell
void timingAna::addHoldBuffsToNetlist
 ( int orgNetId, 
  std::vector<dbCell*>& holdBuffCells,
  int srcId, int sinkId, int& numNets )
{
  //remove the pin associated with sinkFF from orgNetId
  auto orgNet = (*_db)._design._netLib.at(orgNetId);
  dbPin* sinkFFInpPin = NULL;
  for (auto itPin = (*orgNet).pinsBegin(); 
			itPin != (*orgNet).pinsEnd(); itPin ++ )
  {
    if ( (int)(*itPin)->getCell().getIndex() ==  sinkId )
	{
      sinkFFInpPin = (*itPin);		
	  orgNet->_pins.erase(itPin);
      std::cout << "Found sinkFF pin & removed it: " << (*sinkFFInpPin) << "\n";		
      break;		
	}
		
  }		
  
  //removing sinkFF from list of orgNet cells 
  for (auto itC = (*orgNet).cellsBegin();
			itC != (*orgNet).cellsEnd(); itC++)
  {
	if ( (int)(*itC)->getIndex() == sinkId )
	{
      std::cout << "Found sinkFF cell in critical net & removed it: " << *(*itC) << "\n";		
      (*orgNet)._cells.erase(itC);
      break;	  	
	}
  }

  //removing orgNet from list of sinkFF nets  
  auto sinkCell = (*_db)._design._cellLib.at(sinkId);
  for (auto itN = (*sinkCell).netsBegin(); 
			itN != (*sinkCell).netsEnd(); 
			  itN++ )
  {
	if ( (*itN) == orgNet )
    {
      sinkCell->_nets.erase( itN );
      break;	  
		
	}		
  }    			  
  
  myAssert2 (sinkFFInpPin, (*orgNet)," sinkFF input pin not found! ");

     
  //sinkFFInpPin->setCell(NULL);
  //sinkFFInpPin->setNet (NULL);  

  myAssert3 ( (*orgNet).getNumCells() == 1, (*orgNet),
			 " orgNet doesn't have one cell: ", (*orgNet)._cells);  
  myAssert3 ( (*orgNet).getNumPins() == 1, (*orgNet),
			 " orgNet doesn't have one pin: ", (*orgNet)._pins);  
  //add the pin associated with the first holdBuff to orgNetId
  auto fstHoldBuff = holdBuffCells.front();
  auto lstHoldBuff = holdBuffCells.back();
  //Point p1(Constants::JTL_IN_PIN_POS, Constants::JTL_IN_PIN_POS);  
  Point p1(Constants::CELL_IN1_PIN_POS, Constants::CELL_IN1_PIN_POS);  
  dbPin* fhBuffInPin = new dbPin("pin0", "INPUT", 0, p1);
  fhBuffInPin->setCell( (*fstHoldBuff) ) ; 
  fhBuffInPin->setNet ( (*orgNet) );
  (*orgNet)._cells.push_back( fstHoldBuff );
  (*orgNet)._pins .push_back( fhBuffInPin );
  (*fstHoldBuff)._pins.push_back( fhBuffInPin );
  (*_db)._design._pinLib.push_back(fhBuffInPin);
  
  //add a net from last holdBuff to sinkFF   
  //auto outPinNum = Constants::OUT_PIN_1;
  auto outPinNum = Constants::OUT_PIN_2;
  //double pinPos = Constants::JTL_OUT_PIN_POS;
  double pinPos = Constants::CELL_OUT_PIN_POS;
  Point p2(pinPos, pinPos);
  dbPin* lstHoldBuffOutPin = new dbPin("pin"+std::to_string(outPinNum), "OUTPUT", outPinNum, p2);
  (*lstHoldBuffOutPin).setCell ( (*lstHoldBuff) ); 
  ctainerPins pins = { sinkFFInpPin, lstHoldBuffOutPin} ;
  dbNetType nt("SIGNAL");
  int id = numNets++;
  std::string newClkNetName = "net_JTL_" + std::to_string(id);
  dbNet* newClockNet = new dbNet(newClkNetName, id, nt, pins);
  sinkFFInpPin     ->setNet ( (*newClockNet) );
  lstHoldBuffOutPin->setNet ( (*newClockNet) );
  (*lstHoldBuff)._pins.push_back(lstHoldBuffOutPin);
  
  (*_db)._design._netLib.push_back(newClockNet);
  (*_db)._design._pinLib.push_back(lstHoldBuffOutPin);  
  	
  (*_db)._design.postProcess();
  std::cout << "Original Critial net after update: " << (*orgNet) << "\n";
  std::cout << "srcFF :" << (((*_db).getNetlist().getCellByIdx(srcId) )) << "\n";  
  std::cout << "first HoldBuff :" << (*fstHoldBuff) << "\n";  
  std::cout << "sinkFF :" << (*sinkCell) << "\n";  
  std::cout << "last HoldBuff :" << (*lstHoldBuff) << "\n";  
	
  std::cout << "new Net added :" << (*newClockNet) << "\n";  
	
}


//adds a net from each cell in the vector to the next cell
//if there are n cells, n-1 nets are added to the netlist
void timingAna::createHoldBuffNets
  ( std::vector<dbCell*>& holdCells, int& numNets)
{
  int n = holdCells.size();	
  std::vector<dbNet*> newNets;  
  //int numNets = (*_db).getNetlist().getNumNets();  
  for (int i=0; i < n-1; i++)
    newNets.push_back( 
	  (*_db)._design.addNetToChip ( holdCells.at(i)->getIndex()
	  , holdCells.at(i+1)->getIndex(), 
	   "net_JTL_"+std::to_string(numNets++), 
	     Constants::OUT_PIN_2, "SIGNAL", 
		 false, Constants::CELL_OUT_PIN_POS, Constants::JTL_IN_PIN_POS)
		 //false, Constants::JTL_OUT_PIN_POS, Constants::JTL_IN_PIN_POS)
	   );	  
  

  for (auto&i: newNets)
    myAssert3 ( i->getNumPins() == 2, 
			*i, "num of pins is not 2", i->getNumPins() );	  

  (*_db)._design.postProcess();				
  std::cout << "\nnewNets: " << newNets << "\n";  

  return;	
}  
  

int timingAna::countNumHoldBuffs
 ( std::vector< std::tuple <int, int, int, double>  >& holdNets )
{ 
  int numBuffs = 0;
  for (auto& h: holdNets)
  {
	int srcId, sinkId, netId; double slack;
	std::tie(srcId, sinkId, netId, slack) = h;
    int numHoldBuffs = calcNumHoldBuffs( - fabs(slack) - fabs( Constants::SLACK_UNCERTAINTY));
    numBuffs += numHoldBuffs;	
  }
  
  return numBuffs;  
}

void timingAna::insertHoldBuffers
 ( std::vector< std::tuple <int, int, int, double>  >& holdNets )
{ 
  int numNets = (*_db).getNetlist().getNumNets();
  for (auto& h: holdNets)
  {
	int srcId, sinkId, netId; double slack;
	std::tie(srcId, sinkId, netId, slack) = h;
	std::cout << "\n\n++++++++++++++++------------------\n\n";
    std::cout << "net,slack: " << netId << ","  << slack << "\n";	  
    int numHoldBuffs = calcNumHoldBuffs( - fabs(slack) - fabs( Constants::SLACK_UNCERTAINTY));
    std::cout << "number of required hold buffs: " << 
		numHoldBuffs << "\n";
	Point sinkPl = (*_db)._spatial.locations[sinkId];	
	Point srcPl = (*_db)._spatial.locations[srcId];	
    auto holdBuffCells = 
	   createHoldBuffCells( numHoldBuffs, sinkPl, srcPl);
    createHoldBuffNets( holdBuffCells, numNets );	  
	addHoldBuffsToNetlist( netId, holdBuffCells, srcId, sinkId, numNets );
	
  }
    	  
	
	
}

bool timingAna::fixHold()
{
  std::string inputFileName = (*_db).getDesignPath() + "/"+ (*_db).getDesignName() + "_hold.slack";	
  return fixHold(inputFileName);
}

bool timingAna::fixHold(std::string inputFileName)
{
  std::cout << "\n\n******************************\n\n";
  	
  
  //std::string inputFileName = (*_db).getDesignPath() + "/"+ (*_db).getDesignName() + "_hold.slack";	
 
  int numCells, numNets, numPins;
  numCells= (*_db).getNetlist().getNumCells();
  numNets = (*_db).getNetlist().getNumNets();
  numPins = (*_db).getNetlist().getNumPins();

  
  timingParser tp;
  //auto holdViolatingPaths = tp.readHoldSlackFile(inputFileName); 
  auto holdPaths = tp.readSlackFile(inputFileName); //this gets all the paths
/*   if ( holdPaths.size() == 0 ) {
	std::cout << "\n\n******************************\n\n";
	std::cout << "No hold violatios found.\n\n" ;  
    return true;
  }
  else
	std::cout << "\n\n******************************\n\n\tTotal # of hold time violations: " << holdPaths.size() << "\n\n" ; */
	  
  
  std::cout.setstate(std::ios_base::failbit);		
  auto holdNets = findHoldNets( holdPaths );
  //TODO: Double check for circuits with large no. of hold buffs needed
  insertHoldBuffers( holdNets );   
  std::cout.clear();		
  
  int numBuffs = countNumHoldBuffs  ( holdNets );   
  std::cout << "\n\nThe no. required hold buffs is: "<< numBuffs << "\n\n"  ;
    
  
  int numCellsPost, numNetsPost, numPinsPost;
  numCellsPost = (*_db).getNetlist().getNumCells();
  numNetsPost = (*_db).getNetlist().getNumNets();
  numPinsPost = (*_db).getNetlist().getNumPins();

  printf( "\tNumber of cells increased from %d to %d by %d (%2.4f%%)\n", numCells, numCellsPost, numCellsPost - numCells, 100*((double)(numCellsPost - numCells)/numCells));
  printf( "\tNumber of nets increased from %d to %d by %d (%2.4f%%)\n", numNets, numNetsPost, numNetsPost - numNets, 100*((double)(numNetsPost - numNets)/numNets));
  printf( "\tNumber of pins increased from %d to %d by %d (%2.4f%%)\n", numPins, numPinsPost, numPinsPost - numPins,100*((double)(numPinsPost - numPins)/numPins));
  
  std::cout << "\n\n******************************\n\n";
  return false;	
}
