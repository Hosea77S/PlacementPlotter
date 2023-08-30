#include "dbSpatial.h"



bool dbSpatial::isConsistent() const
{
    bool IamFine=true;
    if (locations.getSize()!= int (locationValid.size()))  //||
        //locations.getSize()!=orientations.size())
		IamFine=false;
    myWarn(IamFine,"Spatial section inconsistent : size mismatch\n");
    return IamFine;
}

//void dbSpatial::reorderCells(const Permutation& perm)
//{
   //locations.reorder(perm);  
   //reorderBitVector(locationValid,perm);  
   //reorderVector(orientations,perm);  
   //constraints.reorderSubPlWith(perm);
//}

bool dbSpatial::allCellsPlaced() const
{
  for(unsigned k=0;k<locationValid.size();k++) 
     if (!locationValid[k]) return false;
  return true;
}

