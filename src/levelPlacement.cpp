#include "levelPlacement.h"
#include "bookShelfParser.h"


void levelPlacement::checkLevel(unsigned level)
{
  myAssert3 ( level >= 0 && (int)level <= (*_db).getMaxLevel(),
   level, " level is out of index for ", (*_db).getMaxLevel() );  
  return;	
}

//returns total width and height of the cells in a level
Point levelPlacement::getTotalWandH(unsigned level)
{
  checkLevel(level); 
  auto curLevel = _level2CellMap.at(level);
  double w = 0.0, h = 0.0;
  for (auto& i: curLevel)
  {
	w += i->getWidth();
    h += i->getHeight();	
  }
  
  return Point(w,h);
}



//creates a db only containing cells of level <= input level,
//cells with < level, are fixed, cells of level are movable, returns this new db
void levelPlacement::reduceDB(DB& levelDB, unsigned level, bool changeLoc)
{

  
  
  //auto design = levelDB.getNetlistForSurgery();
  std::vector<unsigned> cells;  
  for(auto cItr = levelDB.getNetlist().cellsBegin(); 
     cItr != levelDB.getNetlist().cellsEnd(); cItr++)
  {
	if ( (*cItr)->getLevel() != level &&  (*cItr)->getLevel() != 0) {
	  cells.push_back( (*cItr)->getIndex() );
      levelDB._design._cellLib.at( cells.back() )->_type = dbCellType("IO","PIO");	  
	}
    //newCells.push_back( (*cItr) );
    //for (auto nItr = (*cItr)->netsBegin(); 
	//  nItr != (*cItr)->netsEnd(); nItr++)
    //  newNets.push_back ( (*nItr) );
    //for (auto pItr = (*cItr)->pinsBegin(); 
	//  pItr != (*cItr)->pinsEnd();  pItr ++ ) 	  
    //  newPins.push_back( (*pItr) );	  
  }
    
  //levelDB._design._cellLib = newCells;
  //for (unsigned i=0; i < levelDB._design._cellLib.size(); i++)
  //  levelDB._design._cellLib.at(i)->setIndex(i);
  //levelDB._design._netLib.clear();
  //levelDB._design._pinLib.clear();
  //
  //levelDB._design._netLib = newNets;
  //levelDB._design._pinLib = newPins;  
   
    
  
  //std::cout << newCells << "\n";
  //std::cout << newPins << "\n";
  //std::cout << newNets << "\n";
  
  
  if (changeLoc)
  {
    for (unsigned i=0; i < cells.size(); i++){
	  auto curL = levelDB.getNetlist().getCellByIdx( cells.at(i) ).getLevel();
      if ( curL > level && curL != 0)	  
      levelDB._spatial.locations[ cells.at(i) ] = 
         Point( _sourceBB.getTopRight().x, ((_sourceBB.getTopRight().y + _sourceBB.getBottomLeft().y) /2.0));
	     
      /*else if (curL != 0)
      levelDB._spatial.locations[ cells.at(i) ] = (*_db)._spatial.locations [ cells.at(i) ]; */
	  	
    }
	  
  }
  
  //levelDB._spatial.locations = Placement( levelDB.getNetlist().getNumCells() );
  
  levelDB._design.postProcess();
  std::cout << "\n\nDB for cells with level < " << level << "\n";
  levelDB.PrintBenchmarkStatus();
  std::cout << "Total number of Fixed cells: " << cells.size() << "\n";

  
  return ;	
}


void levelPlacement::doPlaceCells
  (int ac, const char* av[], bool chLoc)
{
  auto offsetPoint = _sourceBB.getBottomLeft();	
  unsigned maxLevel =  (unsigned)(*_db).getMaxLevel(); 
  for (unsigned level=1; level <= maxLevel; level++)   	
  {
	checkLevel(level);
	DB::Parameters dbParams;
	DB rdb(dbParams);
	
	bookshelfParam p_cls (ac, av);
	bookShelfParser parser(&rdb, p_cls);
	std::string newDesName = rdb.getDesignName() + "_lls";  
	rdb.setDesignName(newDesName);	  
    parser.setDesignName(newDesName);
    rdb._spatial.locations = (*_db)._spatial.locations;	
	
    auto curArea = getTotalWandH(level);
    reduceDB(rdb, level, chLoc);	  
    /* BBox rBB = BBox( offsetPoint.x, offsetPoint.y, 
					 offsetPoint.x + curArea.x , offsetPoint.y + curArea.y ); */    	

	//pause();
    parser.writeDesignFiles(true, true, false, false);		
	std::string ComplxCmd = "./HGraph/ComPLx.exe -f " + rdb.getDesignPath() +  rdb.getDesignName() + "_placed.aux" + " -fast > " + rdb.getDesignPath() + "ll_cmplx.log";
	std::cout << "calling cmd : " << ComplxCmd << std::endl;	
	system(ComplxCmd.c_str());

	std::string postGPFileName = rdb.getDesignName() + "_placed-ComPLx.pl";
	parser.readPlFile ( postGPFileName );

	std::string legalCmd = "./HGraph/PlaceUtil-Lnx64.exe -f " + rdb.getDesignPath() + "/"+ rdb. getDesignName() + "_placed.aux -legal"
	 + " -savePl " + rdb.getDesignPath()  + "/" + rdb. getDesignName() + "-ComPLx_ll_legal.pl";
	std::cout << "calling cmd : " << legalCmd << std::endl;
	system(legalCmd.c_str());
	
	std::string legalPl = rdb.getDesignPath() + "/"+ parser._auxParser. getDesignName() + "-ComPLx_ll_legal.pl";
	parser.readPlFile(legalPl);
/* 	detailedPL lp(&rdb);
	std::string legalPl = lp.doLegalization();		
	parser.readPlFile(legalPl); */
	
	
    (*_db)._spatial.locations = rdb._spatial.locations;	
	
/* 	Placement pl3 ( (*_db)._spatial.locations );
	Legalizer lg ( _db );
	lg.putCellsInBoundRelative(_sourceBB);
	lg.groupAndShift (&pl3, _sourceBB, 1, 0.01, 0.01); */
	
    //globPlacement gPL(&rdb, rBB);
    //gPL.doGlobalPlacement( _numGPIt ); 	
	
    offsetPoint += curArea + Point(100, 100) ;	  

	Plotter(&rdb).plot_area_gnu ( rdb.getDesignPath() + rdb.getDesignName() + "_"+ std::to_string(level) + "_GP", false, true ) ;
	
  }

 
}
