#include "dbNet.h"


dbNet::operator std::string() const{
	std::string text;
	text += "dbNet_" + std::to_string(_index) + "_" + _name;
	return text;
}



// =========================  IMPLEMENTATIONS ======================== //



bool CompareNetsByCellIndex:: operator()( dbNet* n1, dbNet* n2) const
{
    if(n1->getNumPins() == 0)
    {
        if(n2->getNumPins() == 0)
            return (n1->_index < n2->_index );
        else
            return false;   //'empty' nets always go last
    }

    if(n2->getNumPins() == 0) return true;
 
    itCell c1Itr, c2Itr;
 
    for(c1Itr = n1->_cells.begin(), c2Itr = n2->_cells.begin();
            (c1Itr != n1->_cells.end()) && (c2Itr != n2->_cells.end());
            c1Itr++, c2Itr++)
    {
        if( (*c1Itr)->_index < (*c2Itr)->_index ) return true;
        if( (*c1Itr)->_index > (*c2Itr)->_index ) return false;
    }       //if same..loop

    if( c1Itr == n1->_cells.end() && c2Itr == n2->_cells.end() )
             return(n1->_name.compare(n2->_name)<0 );//tie-breaker
 
    if( c1Itr == n1->_cells.end() ) return true;
        else return false;
}

bool CompareNetsByIndex:: operator()( dbNet* n1, dbNet* n2) const
{
	if (n1->getId() != n2->getId())
        return n1->getId() < n2->getId();
	return n1->getName() < n2->getName();
}

bool CompareNetsByIndex:: operator()( const dbNet* n1, const dbNet* n2) const
{
	if (n1->getId() != n2->getId())
        return n1->getId() < n2->getId();
	return n1->getName() < n2->getName();
	
}


bool CompareNetsByDegree:: operator()( dbNet* n1, dbNet* n2) const
{
    if(n1->getNumPins() > n2->getNumPins() )
	return true;

    else if(n2->getNumPins() > n1->getNumPins() )
	return false;

    else 
	return (n1->_index < n2->_index );
}
	
bool CompareNetsByName:: operator()( dbNet* n1, dbNet* n2) const
{
    int result = n1->_name.compare(n2->_name);

    if (result<0) return true;
    else if (result>0) return false;
    else return n1->_name.compare(n2->_name) <0 ;
}	



void dbNet::induceCellsFromPins()
{
        //to be called by the post-processor.  sets the vector of cell*s,
        //from the vector of pin*s, and sorts the cells..sources first.

    std::map<const dbCell*, int, std::less<const dbCell*> > sortCells;
    std::map<const dbCell*, int, std::less<const dbCell*> >::iterator  cellItr;
    const dbCell*  curCell;
    itPin     pinItr;
	

    for(auto const& pinItr : _pins)
    {
        curCell = &( (*pinItr).getCell() );
        if(sortCells.find(curCell) == sortCells.end() )
        {
            if( (*pinItr).isDirInput() )
                sortCells[curCell] = 0;

            else if( (*pinItr).isDirBi() )
                sortCells[curCell] = 1;

            else if( (*pinItr).isDirOutput() )
                sortCells[curCell] = 2;
	    else	//unknown
		sortCells[curCell] = 3;

        } else {
                //this cell has 2+ pins on the net.
	    if(sortCells[curCell] == 3)
	    {	//go with whatever this is:
		if( (*pinItr).isDirInput() )
                sortCells[curCell] = 0;
 
            	else if( (*pinItr).isDirBi() )
                    sortCells[curCell] = 1;
 
            	else if( (*pinItr).isDirOutput() )
                    sortCells[curCell] = 2; 
            	else        //unknown
                    sortCells[curCell] = 3;

	    }else if( (*pinItr).isDirInput() && (sortCells[curCell] == 2) )
                sortCells[curCell] = 1; //make it a type inout.

	    else if(((*pinItr).isDirOutput()) && (sortCells[curCell] == 0))
		sortCells[curCell] = 1;

            else if( (*pinItr).isDirBi() )
                sortCells[curCell] = 1;

            //otherwise, leave it as it is.
        }
    }

        //copy the map into the vector.  outputs, inouts, inputs, unknowns.
    _numOut = _numInOut = 0;
	
    for(cellItr = sortCells.begin(); cellItr != sortCells.end(); cellItr++)
        if( (*cellItr).second == 2 )
 	{
            _cells.push_back( (dbCell *)((*cellItr).first) );
	    _numOut++;
	}

    for(cellItr = sortCells.begin(); cellItr != sortCells.end(); cellItr++)
        if( (*cellItr).second == 1 )
	{
            _cells.push_back( (dbCell *)((*cellItr).first) );
	    _numInOut++;
	}

    for(cellItr = sortCells.begin(); cellItr != sortCells.end(); cellItr++)
        if( (*cellItr).second == 0 )
            _cells.push_back( (dbCell *)((*cellItr).first) );

    for(cellItr = sortCells.begin(); cellItr != sortCells.end(); cellItr++)
        if( (*cellItr).second == 3 )
            _cells.push_back( (dbCell *)((*cellItr).first) ); 

	//added by Soheil to remove duplicate cells from net vec
    std::set<dbCell*, CompareCellsByIndex> tempSet ( _cells.begin(), _cells.end() );
	_cells.clear();
	_cells.insert (_cells.end(), tempSet.begin(), tempSet.end());
	

	return;
}

void dbNet::removeDupPins()
{
    // it's possible to put the same pin on the net in
    // both the PINS section and the NETS section (e.g.
    // matsushita_blk1.  So here we remove dups.  001012 mro

    sort(_pins.begin(),_pins.end(),std::less<dbPin*>());
    std::vector<dbPin*>::iterator  dupItr = std::unique(_pins.begin(),_pins.end());
    _pins.erase(dupItr,_pins.end());
}


