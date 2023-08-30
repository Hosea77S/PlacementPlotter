#include "gridInPl.h"
#include "placement.h"

GridInPlacement
::GridInPlacement(unsigned xSize, unsigned ySize, const Placement& pl)
:_xSize(xSize),_ySize(ySize), _bbox(pl.getBBox()), 
_pointIdcs(std::vector<int>(xSize*ySize, 0))
{
   myAssert(xSize!=0 && ySize!=0 , "Grid with dimension(s) zero");
   std::vector<int> allPoints (pl.getSize(), 0);
   for(int i=0; i!=pl.getSize(); i++) allPoints[i]=i;
   std::sort(allPoints.begin(),allPoints.end(),CompareX(pl));
   double xStepSize=(pl.getSize()*1.0)/xSize;
   unsigned curPtIdx=0;
   for(unsigned i=0; i!=xSize; i++)
   {
     unsigned beginXIdx=static_cast<unsigned>(ceil(xStepSize*i));
     unsigned endXIdx  =static_cast<unsigned>(ceil(xStepSize*(i+1)));
     std::sort(allPoints.begin()+beginXIdx,allPoints.begin()+endXIdx,CompareY(pl));
     double yStepSize=(endXIdx-beginXIdx)/(ySize*1.0);
     for(unsigned j=0; j!=ySize; j++) 
     {
        unsigned  offset=static_cast<unsigned>(ceil(yStepSize*(j+0.5)));
        _pointIdcs[curPtIdx++]=allPoints[beginXIdx+offset];
     }
   }
}
