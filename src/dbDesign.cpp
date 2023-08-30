#include "dbDesign.h"

//Definiton in dbPin.h
bool ComparePinsByDirAndName::operator() ( dbPin* p1, dbPin* p2) const
{
    if(p1->isDirOutput())
    {
        if(p2->isDirOutput())
        {
            int strCmpResult =  p1->_name.compare(
                                  p2->_name);
            if(strCmpResult < 0)      return true;
            else if(strCmpResult > 0) return false;
            else
                {
                CompareCellsByName cc;
                return cc(&(p1->getCell()),&(p2->getCell()));
                }
        } else
            return true;
    } else if(p2->isDirOutput() )
        return false;
 
    if(p1->isDirBi())
    {
        if(p2->isDirBi())
        {
            int strCmpResult = p1->_name.compare(
                                  p2->_name);
            if(strCmpResult < 0)      return true;
            else if(strCmpResult > 0) return false;
            else
                {
                CompareCellsByName cc;
                return cc(&(p1->getCell()),&(p2->getCell()));
                }
        } else
            return true;
    } else if(p2->isDirBi() )
        return false;

    if(p1->isDirInput() )
    {
        if(p2->isDirInput() )
        {
            int strCmpResult = p1->_name.compare(
                                  p2->_name);
            if(strCmpResult < 0)      return true;
            else if(strCmpResult > 0) return false;
            else
                {
                CompareCellsByName cc;
                return cc(&(p1->getCell()),&(p2->getCell()));
                }
        } else
            return true;
    } else if(p2->isDirInput() )
        return false;
 
    int strCmpResult = p1->_name.compare(
                          p2->_name);
    if(strCmpResult < 0)      return true;
    else if(strCmpResult > 0) return false;
    else
        {
        CompareCellsByName cc;
        return cc(&(p1->getCell()),&(p2->getCell()));
        }
}



std::ostream& operator<<(std::ostream& os, const dbPin& pin)
{
    os<<" dbPin #"<<pin._index;

    std::string name = pin._name;
	os<<" ("<<name<<")"<< "  ";

    os<<"Type: "<<pin._type<< "  ";
    os<<"Center: "<<pin._center << "  ";
    if (pin._cell != NULL) os<<"Cell: "<<pin.getCell()._name<< "  ";	
    if (pin._net != NULL) os<<"Net: "<<pin.getNet()._name<< "  ";
  
    return os;  
}

//should only be called by a new db (other than original one)
dbSuperCell::dbSuperCell(std::string name, unsigned index, 
	Point orig, unsigned level, const ctainerCells& cls, std::string type)
{
	_name = name;
	_index = index;
	_origin = orig;
	_width = 0;
	_height = 0;
	_level = level;
	_cells = cls;
	
	for (auto const &c: cls){
		_width += c->_width;
		_height = std::max(_height, c->_height);
		auto nn = c->getNets();
		auto pp = c->getPins();
		std::set<dbNet*> tempNet(nn.begin(), nn.end());
		std::set<dbPin*> tempPin(pp.begin(), pp.end());			
		_nets.insert(_nets.end(), tempNet.begin(), tempNet.end());
		_pins.insert(_pins.end(), tempPin.begin(), tempPin.end());		
		
	}
	
	
	/*
	std::map <const dbPin*, int, std::less<const dbPin*> > pin2pinMap ;
	std::vector<dbPin* > cellPins;
	
	for (auto const &c: cls){
		auto pp = c->getPins();
		std::set<dbPin*> tempPin(pp.begin(), pp.end());					
		for ( auto itP = tempPin.begin();
				itP != tempPin.end(); 
				itP ++)
		{
			dbPin* nPin = new dbPin( (*itP)->getName(),
								(*itP)->getDir (),
								 (*itP)->getIndex(),
								  (*itP)->getCenter() );
			//nPin->setCell ( *_myCell );
			pin2pinMap[*itP] =  cellPins.size();
			
			cellPins.push_back ( nPin );
			
		}
		
		
	} */

	Symmetry s1("Y");
	_myCell = new dbCell(_name, "CORE", type, _index, 
				  _width, _height, _origin, 
				  _level, _pins, s1);
				  
	_myCell->_nets = _nets;	
	_myCell->_pins = _pins;
	for (auto &i: _pins)
		i->setCell ( *_myCell );
	
	
	//Following flow has problem, 
	//it only considers the pins that are connected to the cells
	//and not pins from other cells connected to nets corresponding the cell
	//comment out for now
	//will assume there are no self connection in SuperCells
	/*
	
	Symmetry s1("Y");
	_myCell = new dbCell(_name, "CORE", "CC", _index, 
				  _width, _height, _origin, 
				  _level, cellPins, s1);
				  
	for ( auto itP = _myCell->pinsBegin();
			itP != _myCell->pinsEnd();
			itP++)
		(*itP)->setCell ( *_myCell );
	
	for (auto const &c: cls){
		auto nn = c->getNets();
		std::set<dbNet*> tempNet(nn.begin(), nn.end());
	
		for ( auto itN = tempNet.begin();
				itN != tempNet.end();
				itN ++ )
		{
			ctainerPins tP;
			for ( auto itP = (*itN)->pinsBegin();
					itP != (*itN)->pinsEnd();
					 itP ++ )
			{
			  if(pin2pinMap.find ( (*itP) ) != pin2pinMap.end() )
				tP.push_back ( _pins.at ( pin2pinMap[ (*itP) ] ) );
			}
			
			dbNet* nNet = new dbNet 
				( (*itN)->getName(),
					(*itN)->getId(),
					 (*itN)->getType(),
					  tP );
			
			nNet->induceCellsFromPins();
			(*_myCell)._nets.push_back (nNet);
		}
	}
	
 */
		for (auto const& p: _pins)
		if (p->isDirInput())
			_inDegree++;
		else if (p->isDirOutput())
			_outDegree++;
		else if (p->isDirBi()){
			_inDegree++;
			_outDegree++;
		}	
	for (auto const& p: (*_myCell)._pins)
		if (p->isDirInput())
			(*_myCell)._inDegree++;
		else if (p->isDirOutput())
			(*_myCell)._outDegree++;
		else if (p->isDirBi()){
			(*_myCell)._inDegree++;
			(*_myCell)._outDegree++;
		}
		
	//TODO change corresponding cell of nets and pins to this

	//std::cout << "_myCell: " << *_myCell << std::endl;
	
	//std::cout << _pins << std::endl;
				  
}

ctainerNets getCommonNets
 (const std::vector<const dbCell*> & cells)
{
  unsigned n = cells.size();
  myWarn2 ( n >= 2, " too few cells: ", cells.size());
  auto n0 = cells.at(0)->getNets();
  std::sort(n0.begin(), n0.end(), CompareNetsByIndex());
  
  if (n == 1) return n0;
  ctainerNets commonNets(n0.begin(), n0.end());
	  
  for (unsigned i=1; i < cells.size(); i++)
  {
	auto n1 = cells.at(i)->getNets();
	
	std::sort(n1.begin(), n1.end(), CompareNetsByIndex());
	std::sort(commonNets.begin(), commonNets.end(), CompareNetsByIndex());
	
	//https://stackoverflow.com/questions/19483663/vector-intersection-in-c
	std::set_intersection(n1.begin(),n1.end(),commonNets.begin(),commonNets.end(),back_inserter(commonNets));
  }
  return commonNets;	
}	

 
dbSuperCell::~dbSuperCell(){
	//unsigned k;
	//for(k=0;k<_pins   .size();k++) delete  _pins  [k];
	//for(k=0;k<_nets   .size();k++) delete  _nets  [k];
	//delete _myCell;
};						
 

 
std::vector<int> 
  dbCell::getCommonNets(const std::vector<dbCell*>& cellVec )
{
  //if (cellVec.size() == 0) return {}; 
  if (cellVec.size() != 2) 
	myAssert2 (0, "Total number of cells is not 2", cellVec.size() ); 
  
  std::vector< std::vector<int> > netIdVecs;
  for (int j=0; j <2; j++)
  {
	auto fCell = cellVec.at(j);  
	std::vector<int> curIds;
	for ( itNet it = (*fCell).netsBegin(); 
	it != (*fCell).netsEnd(); it++ )
	{
	  curIds.push_back( (*it)->getId() );		
	}
	
	netIdVecs.push_back( curIds );
  }
  
  for (auto &i: netIdVecs)
    std::sort ( i.begin(), i.end() );	  

  std::vector<int> outVec;
  std::set_intersection  ( netIdVecs.front().begin(),  
     netIdVecs.front().end(), 
	 netIdVecs.back().begin(),
	 netIdVecs.back().end(), 
	 std::back_inserter(outVec));
	 
	 
	 
  return outVec;  	
  
} 
