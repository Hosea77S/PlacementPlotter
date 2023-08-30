#include "dbCell.h"



dbCell::dbCell(std::string name, 
			   std::string type, std::string sType,
               unsigned index , double wth, double ht, 
			   Point orig, unsigned level, 
			   const ctainerPins& pns, Symmetry sym)
            :_name(name), _index(index), _type(type, sType),  
            _fallDelay(-1.234567), _riseDelay(-1.234567),
             _width(wth), _height(ht),
            _origin(orig), _inDegree(0), _outDegree(0), _level(level), 
            _pins(pns), _symmetry(sym)
{
	//if ((type != "IO") && (level == 0))
		//myAssert( 0, "Gate is not IO but has level 0." ); 
	
    for(auto pItr = _pins.begin(); pItr != _pins.end(); pItr++)
    {
        if((*pItr)->isDirOutput() )
            _outDegree++;
        else if( (*pItr)->isDirInput() )
            _inDegree++;
        else if( (*pItr)->isDirBi() )
        {
            _inDegree++;
            _outDegree++;
        }
    }
	
}

dbCell::dbCell(std::string name, std::string type, std::string sType,
               unsigned index , double wth, double ht)
            :_name(name), _index(index), _type(type, sType),  
            _fallDelay(-1.234567), _riseDelay(-1.234567),
             _width(wth), _height(ht),
            _origin(), _inDegree(0), _outDegree(0), _level(0), 
            _symmetry(180){}

dbCell::operator std::string() const 
{
	std::string text;
	std::string origin = _origin;
	text = "dbCell_" + std::to_string(_index) + "_" + _name + ":" + origin ;
	return text;	
}

std::ostream& operator<<(std::ostream& os, const dbCell& cell)
{
    os<<" DBCell #"<<cell._index;

    std::string name = cell._name;
	os<<" ("<<name<<")"<<std::endl;

    os<<"Type: "<<std::string(cell._type)<<std::endl;
    os<<"height: "<<cell._height<<"  width: "<<cell._width<<std::endl;
    os<<"degree: "<<cell.getNumNets()<< std::endl;
	os<<"Num Of Pins: " << cell.getNumPins()<<std::endl;
	os<<"Level: "<<cell._level<<std::endl;
	os<<"Origin: " <<cell._origin<<std::endl;
  
    return os;  
}

bool dbCell::isClkSpl() const 
{
	std::string n = _name;
	std::transform(n.begin(), n.end(), n.begin(), ::tolower);
	if (n.find("splitclk") != std::string::npos)
		return true;
	return false;	
}


dbCell* dbSuperCell::getCell() const {
				  
	return _myCell;
}


std::ostream& operator<<(std::ostream& os, const dbSuperCell& cell)
{
    os<<" DBSuperCell #"<< cell._index;

    std::string name = cell._name;
	os<<" ("<<name<<")"<<std::endl;

    os<<"height: "<<cell._height<<"  width: "<<cell._width<<std::endl;
	os<<"Num Of Cells: "<<cell.getNumCells()<< std::endl;
    os<<"Num Of Nets: "<<cell.getNumNets()<< std::endl;
	os<<"Num Of Pins: " << cell.getNumPins()<<std::endl;
	os<<"Level: "<<cell._level<<std::endl;
	os<<"Origin: " <<cell._origin<<std::endl;
  
    return os;  
}



void dbCell::induceNetsFromPins(std::vector<dbNet*> *sNets)
{
        //create the vector of nets, from the vector of pins. to be called
        //by the post-processor.  removes the duplicate nets, and the
        //special nets.

    itPin        pinItr;
    const dbNet*      tmpNet; // changed by ILM
    itNet       sNetItr;

	//first, put all connected nets that are not special in _nets
    for(pinItr = _pins.begin(); pinItr != _pins.end(); pinItr++)
    {
        if(!(*pinItr)->isConnected() ) continue;

        tmpNet= &((*pinItr)->getNet() );

        for(sNetItr = sNets->begin(); sNetItr != sNets->end(); sNetItr++)
                if( (*sNetItr) == tmpNet ) break;

        if (sNetItr == sNets->end())//not a special net
                _nets.push_back(const_cast<dbNet*>(tmpNet));
    }
	//sort the net, by pointers.
    std::sort(_nets.begin(), _nets.end(), std::less<dbNet*>());

	//remove duplicates
    //itNet dupItr = std::unique(_nets.begin(), _nets.end());
    //_nets.erase(dupItr, _nets.end());
    //_nets.erase(const_cast<dbNet**> (dupItr),
      //          const_cast<dbNet**> (_nets.end()));
	  
	std::set<dbNet*> tempNets ( _nets.begin(), _nets.end());
	_nets.clear();
	_nets.insert (_nets.end(), tempNets.begin(), tempNets.end());
	  
}

void dbCell::induceNetsFromPins()
{

    itPin        pinItr;
    const dbNet*      tmpNet; 
    itNet       sNetItr;

    for(pinItr = _pins.begin(); pinItr != _pins.end(); pinItr++)
    {
        if(!(*pinItr)->isConnected() ) continue;

        tmpNet= &((*pinItr)->getNet() );
		_nets.push_back(const_cast<dbNet*>(tmpNet));
    }
	//sort the net, by pointers.
    std::sort(_nets.begin(), _nets.end(), std::less<dbNet*>());

	//remove duplicates
    //itNet dupItr = std::unique(_nets.begin(), _nets.end());
    //_nets.erase(dupItr, _nets.end());
    //_nets.erase(const_cast<dbNet**> (dupItr),
      //          const_cast<dbNet**> (_nets.end()));
	  
	std::set<dbNet*> tempNets ( _nets.begin(), _nets.end());
	_nets.clear();
	_nets.insert (_nets.end(), tempNets.begin(), tempNets.end());
	  
}



