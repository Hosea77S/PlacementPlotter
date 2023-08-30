#include "bloat.h"

//changes the size of cells
std::vector<double> bloat::expandSize(Dir d, double extra)
{
  std::cout << "\n\n\tAdding extra value of " << 
  extra << " to " ;
  if ( d == _XX) std::cout << " width ";
  else std::cout << " height ";
  std::cout << " of all movable cells.\n";
  
  std::vector<double> prevSize ( (*_db).getNetlist().getNumCoreCells(),  0.0);
	
  for (unsigned i=0; i < (*_db).getNetlist().getNumCoreCells();  i++ )
  {
	if (d == _XX)
	{
	  double prev = (*_db)._design._cellLib.at(i)->getWidth();
	  prevSize [ i ] = prev ;
	  (*_db)._design._cellLib.at(i)->setWidth ( prev + extra );		
	}		
	else 
	{
	  double prev = (*_db)._design._cellLib.at(i)->getHeight();
	  prevSize [ i ] = prev ;
	  (*_db)._design._cellLib.at(i)->setHeight ( prev + extra );
		
	}  
	  
  }

   //now that cell sizes have changed, changing chip size
  if (d == _YY)
  {
	double newRowH = (*_db)._rowDefs->getRowHeight() + extra;
	(*_db)._rowDefs->setRowHeight( newRowH );
	
	(*_db)._rowDefs->setChipHeight (
		(*_db)._rowDefs->getRowCnt() * newRowH );
		
	(*_db)._rowDefs->setChipYEnd( (*_db)._rowDefs->getYOffset() +  (*_db)._rowDefs->getChipHeight() );	
	
	auto bb = (*_db)._rowDefs->getChipBbox();
	BBox newBB ( bb.getBottomLeft().x,
				 bb.getBottomLeft().y,
				 bb.getTopRight().x,
				 (*_db)._rowDefs->getChipYEnd());
				 
	(*_db)._rowDefs->setChipBBox (newBB);
  }
 else
  {
    int avgCellPerRow = (int)
	  ceil( (*_db).getNetlist().getNumCoreCells() /
		(*_db)._rowDefs->getRowCnt() ) ;
		
	double extraW = avgCellPerRow * extra;
    double newWidth = (*_db)._rowDefs->getChipWidth() + extraW;	
	
	(*_db)._rowDefs->setChipWidth ( newWidth );
		
	(*_db)._rowDefs->setChipXEnd( (*_db)._rowDefs->getXOffset() +  newWidth );	
	
	auto bb = (*_db)._rowDefs->getChipBbox();
	BBox newBB ( bb.getBottomLeft().x,
				  bb.getBottomLeft().y,
				  (*_db)._rowDefs->getChipXEnd(),
				   bb.getTopRight().y );	
	(*_db)._rowDefs->setChipBBox (newBB);		
  }
  
  
  
  
  
  return prevSize;	
}  

void bloat::revertSizeExp 
  ( const std::vector<double>& vec, double extra, Dir d)
{
  std::cout << "Reverting the cell size expansions;\n";	
  for (unsigned i=0; i < (*_db).getNetlist().getNumCoreCells();  i++ )
  {
	if (d == _XX)
	  (*_db)._design._cellLib.at(i)->_width = vec.at(i);
    else
	  (*_db)._design._cellLib.at(i)->_height = vec.at(i);
	
  }	
  

  if (d == _XX)
  {
	double w = _oldBB.getWidth();
	(*_db)._rowDefs->setChipWidth( w );
	(*_db)._rowDefs->setChipXEnd ( _oldBB.getTopRight().x  );
	(*_db)._rowDefs->setChipBBox ( _oldBB );
	
  }  
  else
  {
	double h = _oldBB.getHeight();
	double rh = (*_db)._rowDefs->getRowHeight( ) - extra;
	(*_db)._rowDefs->setChipHeight ( h );
	(*_db)._rowDefs->setChipYEnd ( _oldBB.getTopRight().y );
	(*_db)._rowDefs->setChipBBox ( _oldBB );
	(*_db)._rowDefs->setRowHeight ( rh );	
  }

  
  return;	
}


