#include "Cluster.h"



std::map <std::string, std::vector <dbCell*>> 
  Cluster::doClustering
  (int groupSize, 
   std::vector<std::vector<dbCell *> > &newRowVec, 
    int clsMethod )
{
	
	//maps each new Super Cell to the vector of cells it has clustered
	std::map <std::string, std::vector <dbCell*>> supC2CellMap;
	
	//maps each old cell to its new Super Cell
	std::map<std::string, dbCell*> cell2SupCellMap;
	
	// Forms a mapping of SuperCell to main chip cells
	//bool changeCellList = true;
	//if (clsMethod == _prePL)
	  //doPrePlClustering(groupSize, cell2SupCellMap, supC2CellMap);
	//else 
	  //this->clusterDesign(groupSize, supC2CellMap, cell2SupCellMap, newRowVec, changeCellList);
	
	//this->updateNetList_AfterClustering(cell2SupCellMap);
	
	
	
	std::cout << "\tSize of cell2SupCellMap is " <<  cell2SupCellMap.size() << std::endl;
	std::cout << "\tSize of clustered chip (cells + pads) " << (*_db).getNetlist().getNumCells() << std::endl;
	
	return supC2CellMap;
}


void Cluster::createNewDB 
  ( DB* clsDb, std::map<unsigned, std::vector<unsigned>>& sup2CellMap,
		std::vector<std::string> types  )
{
  
  std::map<unsigned, unsigned> cell2SupCellMap;
    
  std::vector<dbCell*> sups;
  for ( auto &i: sup2CellMap )
  {
    std::vector<dbCell*> c;
    for ( unsigned j=0; j < i.second.size() ; j++ ){
  	  c.push_back ( (*clsDb)._design._cellLib.at( i.second.at(j) ) );
		
   	  cell2SupCellMap [ i.second.at(j) ] = sups.size();
	}
    
    std::string name = "SupCell" + std::to_string ( i.first );
    std::string type = "SC";	
    if ( i.first < types.size() ) 	type = types.at(i.first);
    dbSuperCell cs ( name, i.first, Point (0,0), 1, c, type);
    sups.push_back ( cs.getCell() );
    
	//cout << cs << endl;
	//std::cout << *(sups.back()) << std::endl;
	//cout << (sups.back())->_nets << endl;
  }
  
  unsigned numTotalCells = (*clsDb).getNetlist().getNumCells();
  unsigned numPads = numTotalCells -
		(*clsDb).getNetlist().getNumCoreCells();
  
  myAssert2 ( numPads > 0, numPads, " is not > 0 " );
  
  //clears the cell list, only keeps pads  
  addPadsToCLSCellList ( clsDb ); 
  
  (*clsDb)._design._cellLib.insert ( 
	(*clsDb)._design.cellsBegin(), 
	  sups.begin(), sups.end() ) ;

  //adding pads to cell2SupCellMap 	
  for ( unsigned i= 0; 
  	i < numPads ;
  	i++)
  	  cell2SupCellMap [ numTotalCells - numPads + i ] = 
		sups.size() + i ;
	  
  std::cout << "cell2SupCellMap: " <<  cell2SupCellMap << std::endl;
  
  //adjusting index of the cells
  for (unsigned i=0; i < (*clsDb)._design._cellLib.size(); i++)
    (*clsDb)._design._cellLib.at( i )-> setIndex ( i );	  
  

   //clearing the cell vector of all nets, they belong to previous db
  for ( unsigned i=0; i < (*clsDb)._design._netLib.size(); i++)
	(*clsDb)._design._netLib.at ( i )-> _cells.clear ( );
   
   
  //changing _nameCellMap
  (*clsDb)._design._nameCellMap.clear();
  for (unsigned i=0; i < (*clsDb)._design._cellLib.size(); i++)
    (*clsDb)._design._nameCellMap 
		[ (*clsDb)._design._cellLib.at( i )->getName() ] = 
           (*clsDb)._design._cellLib.at( i );

  
	  
  /*for ( auto& i: sups )
  {
    (*clsDb)._design._netLib.insert ( (*clsDb)._design._netLib.end(),
		i->_nets.begin(), i->_nets.end() );  
		
	(*clsDb)._design._pinLib.insert ( (*clsDb)._design._pinLib.end(),
		i->_pins.begin(), i->_pins.end() );
  }*/
  
  (*clsDb)._design.postProcess ();

  std::cout << (*clsDb)._design._cellLib << std::endl;
  std::cout << "\n\n****************************\n\n";
  std::cout << (*clsDb)._design._pinLib << std::endl;
  std::cout << "\n\n****************************\n\n";
  std::cout << (*clsDb)._design._netLib << std::endl;
  
  (*clsDb).PrintBenchmarkStatus();
  
  //added 05.14.2019 
  (*clsDb)._spatial.locations = Placement ( (*clsDb)._design._cellLib.size() );
  
  //cout << sups << endl;
  
  //return clsDb;
     
}


//clears the cell list, only keeps pads
void Cluster::addPadsToCLSCellList
 ( DB* clsDb )
{	

	(*clsDb)._design._cellLib.erase
		( (*clsDb)._design.cellsBegin(), 
		(*clsDb)._design.cellsBegin() + (*clsDb)._design.getNumCoreCells() );
				
		
				
	return;
}


void Cluster::checkDBConsistency 
  ( const DB* newDb )
{
  std::cout << "Checking for consistency of cluster DB.. \n";
  //checking size of nets, should be same
  myAssert3 ( _db->getNetlist().getNumNets () == 
              newDb ->getNetlist().getNumNets (),
			  _db->getNetlist().getNumNets (),
			  " (orig) Incosistent num of Nets (new) ",
			  newDb ->getNetlist().getNumNets ()
			  );
			  
  //checking size of pins, should be same
  myAssert3 ( _db->getNetlist().getNumPins () == 
              newDb ->getNetlist().getNumPins (),
			  _db->getNetlist().getNumPins (),
			  " (orig) Incosistent num of Pins (new) ",
			  newDb ->getNetlist().getNumPins ()
			  );
			  
  //checking size of pads, should be same
  myAssert3 ( _db->getNetlist().getNumIOPads () == 
              newDb ->getNetlist().getNumIOPads (),
			  _db->getNetlist().getNumIOPads (),
			  " (orig) Incosistent num of I/O Pads (new) ",
			  newDb ->getNetlist().getNumIOPads ()
			  );

  //checking cell indices, should be consistent
  for ( unsigned i=0; i < (*newDb).getNetlist().getNumCells(); i++)
	  myAssert3 ( i == (*newDb).getNetlist().getCellByIdx (i).getIndex (), 
	  i , " not equal to index of cell: ",
	  (*newDb).getNetlist().getCellByIdx (i).getIndex ()
  );
  
  //checking index of cell instances of nets, 
  //should be within range
  for ( unsigned i=0; i < (*newDb).getNetlist().getNumNets();
        i++)
	for ( auto& j: (*newDb)._design._netLib.at(i)->_cells )
	  myAssert3 ( (*newDb).getNetlist().isCellIdValid( j->getIndex()    ),
        j->getIndex(), " Invalid cell Id for net #", i );
			  
  for ( unsigned i=0; 
        i < (*newDb).getNetlist().getNumPins();
        i++)
  {
	  myAssert3 ( (*newDb).getNetlist().isCellIdValid( (*newDb)._design._pinLib.at(i)->_cell->getIndex()    ),
        (*newDb)._design._pinLib.at(i)->_cell->getIndex(), " Invalid cell Id for pin #", i );
		
	  myAssert3 ( (*newDb).getNetlist().getNumNets() > (*newDb)._design._pinLib.at(i)->_net->getId(),
        (*newDb)._design._pinLib.at(i)->_net->getId(), " Invalid net Id for pin #", i );
	
  }
    
  std::cout << "Cluster DB is consistent with original DB \n";	
  return;  
}




//changes the original DB (member)
//Oh Oh !!!! changing type of all the cells but the first cell 
//in each supercell to CC, so they won't be counted as clkSink
//clsDb is the db with super cells
void Cluster::unClusterDesign 
  (const DB* clsDb, 
    const std::map < unsigned, std::vector<unsigned>>& sup2CellMap )
{
  Placement tempPl ( (*_db)._spatial.locations );
  //updating the pos of cells in the original db(member)
  for (auto &i: sup2CellMap)  
  {
	unsigned supIdx = i.first;
	auto cellVec = i.second;
	Point offset = (*clsDb)._spatial.locations[ supIdx ];

	for ( unsigned j=0; j < cellVec.size(); j++)
    {
	  if ( (*_db).getNetlist().getCellByIdx ( cellVec.at(j) ).isFixed() )
		  continue;
	  tempPl [ cellVec.at(j) ] = offset;
	  
	  offset.x += (*_db).getNetlist().getCellByIdx ( cellVec.at(j) ).getWidth();
	  
	  if ( j == 0 )
		(*_db)._design._cellLib.at( cellVec.at(j) )->_type = dbCellType("CORE","SC");
      else
		(*_db)._design._cellLib.at( cellVec.at(j) )->_type = dbCellType("CORE","CC");
		  
	  
	}		
	  
  }
	
  for (unsigned i=0; i < (*_db).getNetlist().getNumCoreCells();i++)
  (*_db)._spatial.locations[i] = tempPl[i];	  
	
}

