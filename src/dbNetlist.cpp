#include "DB.h"
#include "dbNetlist.h"
#include "Bbox.h"
#include "CTS.h"

int dbNetlist::findGCLKCell() const {
	auto c = _nameCellMap.find ( "GCLK_Pad" );
    if ( c == _nameCellMap.end())
	  return -1;
	
	return (*c).second->getIndex();
}




dbNetlist::~dbNetlist()
{
    unsigned k;
    for(k=0;k<_cellLib  .size();k++) delete  _cellLib [k];
    for(k=0;k<_pinLib   .size();k++) delete  _pinLib  [k];
    for(k=0;k<_netLib   .size();k++) delete  _netLib  [k];
}


void dbNetlist::postProcess()
{
	//remove nets with <= 1 pin.
	//first, sort them to put such nets at the end.
    itNet nItr;
    sort(_netLib.begin(), _netLib.end(), CompareNetsByDegree());

    for(nItr = _netLib.begin(); nItr != _netLib.end(); nItr++)
	if((*nItr)->getNumPins() <= 1)
	    break;

    if(nItr == _netLib.end())
	std::cout<<"  No degree 1 or 0 nets found"<<std::endl;
    else
	std::cout<<"  Removing degree 1 and 0 nets ... "<<std::endl;

    itNet tmpNItr;
    itPin  pItr;

	//update the pins's _net ptrs for the degree 1 nets
    for(tmpNItr = nItr; nItr != _netLib.end(); nItr++)
    {
	myAssert((*nItr)->getNumPins() <= 1, "Sorting By Degree Failed");

	if( (*nItr)->getNumPins() > 0 )
        {
		pItr = (*nItr)->pinsBegin();
		(*pItr)->_net = NULL;
	}

        delete (*nItr);  // we're going to remove this net from the vector
                         // in the following call to erase(), but we also
                         // need to make sure dbNet dtor be called.
    }
		
     _netLib.erase(tmpNItr, _netLib.end());
    //_netLib.erase(const_cast<dbNet**> (tmpNItr),
    //            const_cast<dbNet**> (_netLib.end()));
   
    //update net idxs after removing
	int i=0;
    for(itNet nItr = _netLib.begin(); nItr != _netLib.end(); nItr++)
	{
      (*nItr)->_index = i++;				
	}
	
	

   //for each cell, build its vector of nets.
    itCell cItr;
    for(cItr = cellsBegin(); cItr != cellsEnd(); cItr++)
        (*cItr)->induceNetsFromPins();

   //for each net, build its vector of cells.
    for(nItr = netsBegin(); nItr != netsEnd(); nItr++)
        (*nItr)->induceCellsFromPins();

  //populate dbNetlist's NUMs
    _numIOPads = _numCoreCells = _numAllPads = _numIOPins = 0;
    _numSCs = _numCCs = 0;
    _coreCellArea = 0.0;

    for(cItr = cellsBegin(); cItr != cellsEnd(); cItr++)
    {

        if ((*cItr)->isIO())
        {
            _numAllPads++;
            if(!(*cItr)->isPUnknown() )
	    {
                _numIOPads++;
		itPin lPItr;
		for(lPItr = (*cItr)->pinsBegin(); 
			lPItr != (*cItr)->pinsEnd(); lPItr++)
		{
		    if((*lPItr)->isConnected() ) 
	            	_numIOPins++;
		}
	    }
        }
        else if((*cItr)->isCore() )
        {
            _numCoreCells++;
            _coreCellArea += (*cItr)->getHeight() *
                             (*cItr)->getWidth();
            if((*cItr)->isSC() )
                _numSCs++;
            else if( (*cItr)->isCC() )
                _numCCs++;
        }
    }

   //populate dbNetlist::_pinLib


   if(_pinLib.size() == 0)
   {
	std::cout<<"  Populating _pinLib ..."<<std::endl;
 	ctainerPins	pinLibTemp;
   	itPin	mPItr;	
	itCell		mCItr;

   	for(mCItr = cellsBegin(); mCItr != cellsEnd(); mCItr++)
   	{
	    for(mPItr=(*mCItr)->pinsBegin();mPItr !=(*mCItr)->pinsEnd();mPItr++)
	    	pinLibTemp.push_back( (*mPItr) );
        }
	_pinLib = pinLibTemp;
   }  

  //populate dbNetlist::_pinLib

   if( _pinLib.size() == 0 )
   {
	std::cout<<"  Populating _pinLib ..."<<std::endl;
	ctainerPins	pinsTemp;

	for(cItr = cellsBegin(); cItr != cellsEnd(); cItr++)
	{
	    for(pItr = (*cItr)->pinsBegin(); pItr != (*cItr)->pinsEnd(); pItr++)
		pinsTemp.push_back( (*pItr) );
	}
	_pinLib = pinsTemp;
   }
   
   //sorting cells by cell type
   //std::sort ( _cellLib.begin(), 
//			   _cellLib.end(), 
//			   CompareCellsByType() );

	//populating _level2CellMap
	for(cItr = cellsBegin(); cItr != cellsEnd(); cItr++)
	{
		unsigned level = (*cItr)->getLevel();
		if ( _level2CellMap.find(level) != _level2CellMap.end() )
			_level2CellMap [ level ]. push_back ( *cItr );
		else {
			std::vector< dbCell* > t = { *cItr };
			_level2CellMap [ level ] = t ;
		}
	}	

}

void dbNetlist::sortCellsByType ()
{
   //sorting cells by cell type
   std::sort ( _cellLib.begin(), 
			   _cellLib.end(), 
			   CompareCellsByType() );	
			   
   
   for (unsigned i=0; i < _cellLib.size(); i++)
	 _cellLib.at(i)->_index = i;
   
   return;
}


std::vector<unsigned> dbNetlist::getPadIndices () const
{
	std::vector<unsigned> pads;
	for ( unsigned i=0; i < _cellLib.size(); i++)
		if ( _cellLib.at(i)-> isFixed() )
			pads.push_back (i);
	
	myAssert3 ( pads.size() == getNumAllPads(), pads.size(), " is not equal to pad cnt: ", getNumAllPads() );
	
	return pads;
}


double dbNetlist::evalHalfPerimCost(unsigned threshold, bool IONetsOnly) const
{
    itNet nItr;
    double totalPerim = 0.0;

    for(nItr = netsBegin(); nItr != netsEnd(); nItr++)
      if (!threshold || (*nItr)->getNumPins() < threshold)
	totalPerim += evalHalfPerimCost(*nItr, IONetsOnly);

    return totalPerim;
}


double dbNetlist::evalHalfPerimCost(dbNet *net, bool IONetsOnly) const
{
    BBox       netBox;
    itPin pItr;
    unsigned   cellId;
    Point      pinOffset;
    bool       IONet=false;


    for(pItr = net->pinsBegin(); pItr != net->pinsEnd(); pItr++)
    {
        if (IONetsOnly && (*pItr)->getCell().isIO()) IONet=true;

	cellId = (*pItr)->getCell().getIndex();
	pinOffset = (*pItr)->getCenter();

 
        myAssert(cellId < _cellLib.size(),"placement index out of range");
        netBox += (_cellLib[cellId ]->_origin + pinOffset);
    }

    if (!IONetsOnly || IONet) return netBox.getHalfPerim();
    else return 0;
} 


#define NumNetCostFactors 51

static double NetCostFactorTable[NumNetCostFactors]=
{
                0.0,
                1.000000, 1.000000, 1.000000, 1.082797, 1.153598,
                1.220592, 1.282322, 1.338501, 1.399094, 1.449260,
                1.497380, 1.545500, 1.593619, 1.641739, 1.689859,
                1.730376, 1.770893, 1.811410, 1.851927, 1.892444,
                1.928814, 1.965184, 2.001553, 2.037923, 2.074293,
                2.106117, 2.137941, 2.169766, 2.201590, 2.233414,
                2.264622, 2.295830, 2.327038, 2.358246, 2.389454,
                2.418676, 2.447898, 2.477119, 2.506341, 2.535563,
                2.560954, 2.586346, 2.611737, 2.637129, 2.662520,
                2.688684, 2.714848, 2.741013, 2.767177, 2.793341
};

static double getNetCostFactor(unsigned numPins)
{
   if (numPins<NumNetCostFactors) return NetCostFactorTable[numPins];
        else return NetCostFactorTable[NumNetCostFactors-1];
}


double 
dbNetlist::evalHalfPerimCostNoPins(dbNet *net, const Placement &pl, 
                                   bool IONetsOnly) const
{
    BBox       netBox;
    //itPinLocal pItr;
    unsigned   cellId;
//  Point      pinOffset;
    bool       IONet=false;
 
    for(auto pItr = net->pinsBegin(); pItr != net->pinsEnd(); pItr++)
    {
        cellId = (*pItr)->getCell().getIndex();
        netBox += pl[cellId];
        if (IONetsOnly && (*pItr)->getCell().isIO()) IONet = true;
    }

    if (!IONetsOnly || IONet) return netBox.getHalfPerim();
    else return 0;
}

double dbNetlist::evalWHalfPerimCost(const Placement &pl,
                unsigned threshold, bool IONetsOnly) const
{
    //itNetGlobal nItr;
    double totalPerim = 0.0;

    for(auto nItr = netsBegin(); nItr != netsEnd(); nItr++)
      if (!threshold || (*nItr)->getNumPins() < threshold)
	totalPerim += getNetCostFactor((*nItr)->getNumPins()) *
                      evalHalfPerimCost(*nItr, pl, IONetsOnly);

    return totalPerim;
}


double dbNetlist::evalWHalfPerimCost(unsigned threshold, bool IONetsOnly) const
{
    itNet nItr;
    double totalPerim = 0.0;

    for(nItr = netsBegin(); nItr != netsEnd(); nItr++)
      if (!threshold || (*nItr)->getNumPins() < threshold)
	totalPerim += getNetCostFactor((*nItr)->getNumPins()) *
                      evalHalfPerimCost(*nItr,  IONetsOnly);

    return totalPerim;
}


double dbNetlist::evalHalfPerimCost(const Placement &pl,
                unsigned threshold, bool IONetsOnly) const
{
    //itNetGlobal nItr;
    double totalPerim = 0.0;

    for(auto nItr = netsBegin(); nItr != netsEnd(); nItr++)
      if (!threshold || (*nItr)->getNumPins() < threshold)
	totalPerim += evalHalfPerimCost(*nItr, pl, 
                                         IONetsOnly);

    return totalPerim;
}


double dbNetlist::evalHalfPerimCostX(const Placement &pl,
                unsigned threshold, bool IONetsOnly) const
{
    //itNetGlobal nItr;
    double totalPerim = 0.0;

    for(auto nItr = netsBegin(); nItr != netsEnd(); nItr++)
      if (!threshold || (*nItr)->getNumPins() < threshold)
	totalPerim += evalHalfPerimCostX(*nItr, pl, 
                                         IONetsOnly);

    return totalPerim;
}


double dbNetlist::evalHalfPerimCostY(const Placement &pl,
                unsigned threshold, bool IONetsOnly) const
{
    //itNetGlobal nItr;
    double totalPerim = 0.0;

    for(auto nItr = netsBegin(); nItr != netsEnd(); nItr++)
      if (!threshold || (*nItr)->getNumPins() < threshold)
	totalPerim += evalHalfPerimCostY(*nItr, pl, 
                                         IONetsOnly);

    return totalPerim;
}



double 
dbNetlist::evalHalfPerimCostNoPins(dbNet *net,  
                                   bool IONetsOnly) const
{
    BBox       netBox;
    //itPin pItr;
    unsigned   cellId;
//  Point      pinOffset;
    bool       IONet=false;
 
    for(auto pItr = net->pinsBegin(); pItr != net->pinsEnd(); pItr++)
    {
        cellId = (*pItr)->getCell()._index;
        netBox += _cellLib[cellId]->_origin;
        if (IONetsOnly && (*pItr)->getCell().isIO()) IONet = true;
    }

    if (!IONetsOnly || IONet) return netBox.getHalfPerim();
    else return 0;
}

double dbNetlist::evalMSTCost() const
{
    itNet nItr;
    itPin  pItr;
    double totalPerim = 0.0;
//  Point cellCenter;
    Point pinOffset;

    for(nItr = netsBegin(); nItr != netsEnd(); nItr++)
    {
        unsigned netDegree=(*nItr)->getNumPins();
        myAssert(netDegree<3000," MST evaluator failed: netDegree > 3000\n");
                               // likely to overflow
	std::vector<Point> netPl(netDegree);
        unsigned pinCount=0;
	for(pItr = (*nItr)->pinsBegin(); pItr != (*nItr)->pinsEnd(); pItr++)
	{

		netPl[pinCount++]= _cellLib[ (*pItr)->getCell()._index ]->_origin;

	}	//end, for all pins
        double  netMSTCost =0; // = netPl.getMSTCost();
        myAssert(0," MST cost computation unavailable "); 
        myAssert(netMSTCost>=0.0,
           " MSTCost evaluator failed: overflow (net and scale too large)\n");
           // MST cost evaluator uses integers : they can easily overflow
	totalPerim += netMSTCost;

    }//end, for all nets

    return totalPerim;
}


double dbNetlist::evalHalfPerimCost(dbNet *net, const Placement &pl,
			bool IONetsOnly) const
{
    BBox       netBox;
    itPin pItr;
    int   cellId;
    Point      pinOffset;
    bool       IONet=false;


    for(itPin pItr = net->pinsBegin(); pItr != net->pinsEnd(); pItr++)
    {
        if (IONetsOnly && (*pItr)->getCell().isIO()) IONet=true;
	cellId = (*pItr)->getCell().getIndex();
	pinOffset = (*pItr)->getCenter();

        myAssert3(cellId < pl.getSize(),cellId, " placement index out of range: ", pl.getSize());
        netBox += (pl[cellId ] + pinOffset);
    }

    if (!IONetsOnly || IONet) return netBox.getHalfPerim();
    else return 0;
} 


double dbNetlist::evalHalfPerimCost(int netId, const Placement &pl,
			bool IONetsOnly) const
{//added by soheil
    BBox       netBox;
    itPin 	   pItr;
    int        cellId;
    Point      pinOffset;
    bool       IONet=false;

	myAssert3 ( netId >=0 && netId < (int) _netLib.size(), netId, " is out of bound for _netLib: ", _netLib.size() );
	auto net = _netLib.at ( netId );

    for(itPin pItr = net->pinsBegin(); pItr != net->pinsEnd(); pItr++)
    {
        if (IONetsOnly && (*pItr)->getCell().isIO()) IONet=true;
	cellId = (*pItr)->getCell().getIndex();
	pinOffset = (*pItr)->getCenter();

        myAssert3(cellId < pl.getSize(),cellId, " placement index out of range: ", pl.getSize());
        netBox += (pl[cellId ] + pinOffset);
    }

    if (!IONetsOnly || IONet) return netBox.getHalfPerim();
    else return 0;
} 


double dbNetlist::evalHalfPerimCostX(dbNet *net, const Placement &pl,
			bool IONetsOnly) const
{
    BBox       netBox;
    //itPinLocal pItr;
    int   cellId;
    Point      pinOffset;
    bool       IONet=false;


    for(auto pItr = net->pinsBegin(); pItr != net->pinsEnd(); pItr++)
    {
        if (IONetsOnly && (*pItr)->getCell().isIO()) IONet=true;

	cellId = (*pItr)->getCell().getIndex();
	pinOffset = (*pItr)->getCenter();

        myAssert3(cellId < pl.getSize(),cellId, " placement index out of range: ", pl.getSize());
        netBox += (pl[cellId ] + pinOffset);
    }

    if (!IONetsOnly || IONet) return netBox.getHalfPerimX();
    else return 0;
} 

double dbNetlist::evalHalfPerimCostY(dbNet *net, const Placement &pl,
			bool IONetsOnly) const
{
    BBox       netBox;
    //itPinLocal pItr;
    int   cellId;
    Point      pinOffset;
    bool       IONet=false;


    for(auto pItr = net->pinsBegin(); pItr != net->pinsEnd(); pItr++)
    {
        if (IONetsOnly && (*pItr)->getCell().isIO()) IONet=true;

	cellId = (*pItr)->getCell().getIndex();
	pinOffset = (*pItr)->getCenter();

        myAssert3(cellId < pl.getSize(),cellId, " placement index out of range: ", pl.getSize());
        netBox += (pl[cellId ] + pinOffset);
    }

    if (!IONetsOnly || IONet) return netBox.getHalfPerimY();
    else return 0;
} 


dbNet* dbNetlist::addNetToChip
( unsigned sourceCell, unsigned sinkCell, 
	std::string newNetName, int outPinNum, std::string netType,
	 bool isCellClkSpl,
	 double srcCellPinPos, double sinkCellPinPos) 
{
	myWarn2 ( outPinNum == Constants::OUT_PIN_1 || outPinNum == Constants::OUT_PIN_2, " Wrong outPinNum: ", outPinNum);
	/*for (unsigned int i = 0; i < chip->netList.size(); i++) {
		if (chip->netList[i]->name == newNetName) {
			Net* GCLKNet = chip->netList[i];
			for (unsigned int j = 0; j < GCLKNet->pinList.size(); j++) {
				if (GCLKNet->pinList[j]->dir == PIN_OUT) {
					//Pin* sourceOutClock = GCLKNet->pinList[j];
					Pin* sinkInClock = new Pin(); sinkInClock->dir = PIN_IN;
					sinkInClock->cellPtr = sinkCell; sinkInClock->netPtr = GCLKNet;
					sinkInClock->x = double(CLK_IN_PIN_POS);
					sinkInClock->y = double(CLK_IN_PIN_POS);
					sinkCell->pinList.push_back(sinkInClock);
					GCLKNet->pinList.push_back(sinkInClock);
					this->chip->numOfPins++;
					//cout << " Pushing a pin to GCLK: pin is inputClock of Cell: " << sinkCell->name << endl;
					return GCLKNet;
				}
			}
		}

	}*/
	
	unsigned id = this->getNumNets();
	
	const dbCell& src = this->getCellByIdx(sourceCell);
	
	const dbCell& sink = this->getCellByIdx(sinkCell);


	Point sinkInClkPinPos, srcOutClkPinPos;
	if (isCellClkSpl){
	 double pinPos = ( outPinNum == Constants::OUT_PIN_1 ) ? 		
		Constants::CLK_OUT_PIN_1_POS : 
		  Constants::CLK_OUT_PIN_2_POS;	
	 srcOutClkPinPos = Point (pinPos, pinPos);
	 sinkInClkPinPos = Point(Constants::CLK_IN_PIN_POS, Constants::CLK_IN_PIN_POS);  		
	} 
	else
	{
	  sinkInClkPinPos = Point(sinkCellPinPos, sinkCellPinPos);
	  srcOutClkPinPos = Point(srcCellPinPos, srcCellPinPos);
	}
	
	dbPin* srcOutClkPin = new dbPin("pin"+std::to_string(outPinNum), "OUTPUT", outPinNum, srcOutClkPinPos);

	srcOutClkPin->setCell ( src );
	this->_cellLib.at(sourceCell)->_pins.push_back(srcOutClkPin);
	myAssert2 ( srcOutClkPin->isDirOutput(), " srcOutClkPin is not PO:", (*srcOutClkPin));
	
	dbPin* sinkInClkPin = new dbPin("pin0", "INPUT", 0, sinkInClkPinPos);
	sinkInClkPin->setCell( sink ) ; 
	this->_cellLib.at(sinkCell)->_pins.push_back(sinkInClkPin);	
	myAssert2 ( sinkInClkPin->isDirInput(), " sinkInClkPin is not PI:", (*sinkInClkPin));
	
	ctainerPins pins = {srcOutClkPin, sinkInClkPin} ;

	
	dbNetType nt(netType);
	dbNet* newClockNet = new dbNet(newNetName, id, nt, pins);

	
	sinkInClkPin->setNet ( (*newClockNet) );
	srcOutClkPin->setNet ( (*newClockNet) );

	//std:: cout << "src pins: " << src.getPins() << "\n";
	//std:: cout << "sink pins: " << sink.getPins() << "\n";
	
	this->_netLib.push_back(newClockNet);
	this->_pinLib.push_back(srcOutClkPin);
	this->_pinLib.push_back(sinkInClkPin);
	
	return newClockNet;
	
}


unsigned dbNetlist::getNumClkNets() const
{
  unsigned numClkNets = 0;
  
  itNet nItr;
  for(nItr = netsBegin(); nItr != netsEnd(); nItr++) 
  {
	if ( (*nItr)->getType().isClock() ) 
	  numClkNets++;
  }	
  
  return numClkNets;
}

unsigned dbNetlist::getNumClkPins() const
{
  unsigned numClkPins = 0;
  
  itNet nItr;
  for(nItr = netsBegin(); nItr != netsEnd(); nItr++) 
  {
	if ( (*nItr)->getType().isClock() ) 
	  numClkPins += (*nItr)->getNumPins();
  }	
  
  return numClkPins;
}

