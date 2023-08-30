#include "rudy.h"
#include <exception>
namespace bnu = boost::numeric::ublas;

using std::vector;
using std::max;
using std::min;

vector<double> Rudy::calcRudy()
{
	

  double mMaxX, mMaxY, mMinY, mMinX;
  mMaxX = _bbox.getTopRight().x;
  mMaxY = _bbox.getTopRight().y;
  mMinX = _bbox.getBottomLeft().x;
  mMinY = _bbox.getBottomLeft().y;  
  
  
  myAssert2( greaterOrEqualDouble(mMinY, 0.0 ), mMinY , " mMinY is not >0 " );  
  myAssert2( greaterOrEqualDouble(mMaxY, 0.0 ), mMaxY , " mMaxY is not >0 " );  
  myAssert2( greaterOrEqualDouble(mMinX, 0.0 ), mMinX , " mMinX is not >0 " );  
  myAssert2( greaterOrEqualDouble(mMaxX, 0.0 ), mMaxX , " mMaxX is not >0 " );  
  myAssert3( greaterOrEqualDouble(mMaxX, mMinX), mMaxX , " mMaxX is not > mMinX ", mMinX );  
  myAssert3( greaterOrEqualDouble(mMaxY, mMinY), mMaxY , " mMaxY is not > mMinY ", mMinY );  
  
  static bnu::matrix<double> D (static_cast<int>(abs(mMaxY)+abs(mMinY) + 1), static_cast<int>(abs(mMaxX)+abs(mMinX) + 1), 0.0);
  //static bnu::matrix<double> D_route_sup (static_cast<int>(abs(mMaxY)+abs(mMinY) + 1), static_cast<int>(abs(mMaxX)+abs(mMinX) + 1), 1.0);

  D.clear();


  for (auto itNet = (*_db).getNetlist().netsBegin(); 
            itNet != (*_db).getNetlist().netsEnd(); ++itNet) {
    double xVal, yVal, hpwl = 0.0;
    double minXW = mMaxX, minYW = mMaxY, maxXW = mMinX, maxYW = mMinY;
    double rudy = 0.0;
    for (auto itCellList =  (*itNet) -> cellsBegin(); 
	          itCellList != (*itNet) -> cellsEnd(); ++itCellList) {
      //int orient = nodeId[itCellList->idx].orientation;
 
      xVal = (*_pl)[(*itCellList)->getIndex()].x;
      yVal = (*_pl)[(*itCellList)->getIndex()].y;

/*       // compute pin position from orientation & offsets
      if(orient == 0) { // 0
        xVal = xVal + itCellList->x_offset;
        yVal = yVal + itCellList->y_offset;
      } else if(orient == 2) { // 90
        xVal = xVal + itCellList->y_offset;
        yVal = yVal - itCellList->x_offset;
      } else if(orient == 4) { // 180
        xVal = xVal - itCellList->x_offset;
        yVal = yVal - itCellList->y_offset;
      } else if(orient == 6) { // 270
        xVal = xVal - itCellList->y_offset;
        yVal = yVal + itCellList->x_offset;
      } else {
        double rad = (orient*45.0*PI/180.0);
        xVal = itCellList->y_offset*sin(rad) + itCellList->x_offset*cos(rad) + xVal;
        yVal = itCellList->y_offset*cos(rad) - itCellList->x_offset*sin(rad) + yVal;
      } */

      if (xVal < minXW)
        minXW = xVal;
      if (xVal > maxXW)
        maxXW = xVal;
      if (yVal < minYW)
        minYW = yVal;
      if (yVal > maxYW)
        maxYW = yVal;
      // set read_net
      /*
      for (unsigned i = xVal-5; i < xVal+5; ++ i) {
          for (unsigned j = yVal-5; j < yVal+5; ++ j) {
            D (i,j) += 5;
          }
      }*/
    }
    minXW = max(minXW, mMinX);
    minYW = max(minYW, mMinY);
    maxXW = min(maxXW, mMaxX);
    maxYW = min(maxYW, mMaxY);
    // now have boundary of net
    hpwl = (abs((maxXW - minXW)) + abs((maxYW - minYW)));
    //rudy = hpwl / (max((maxXW - minXW)*(maxYW - minYW), 1.0)); // rudy density
    rudy = 1.0;
    // set read_net

    auto yVec = {max(minYW,0.0), maxYW};	
    //auto xVec = {max(minXW,0.0), maxXW};	
/*     for (unsigned i = max(minYW,0.0); i < maxYW; ++ i) {
        for (unsigned j = max(minXW,0.0); j < maxXW; ++ j) {
          D (i,j) += rudy;
        }
    } */
	
    //only incrementing src and dest rows and cols 
    for (auto&i: yVec) {
        for (unsigned j = max(minXW,0.0); j < maxXW; ++ j) {
          D (i,j) += rudy;
        }
    }
	
 
  }
  
  unsigned s1 = D.size1();  
  unsigned s2 = D.size2();  
  
  int avgCellW = ceil((*_db).getAvgCellWidth()/2);
  
/*   double r = 0.0;
  for (unsigned i = 0; i < s1; ++ i) {
      for (unsigned j = 0; j < s2; ++ j) {
        D(i,j) = exp((D(i,j) - D_route_sup(i,j))/D_route_sup(i,j));
        r += D(i,j);
      }
  } */

  unsigned numRows=(*_db)._rowDefs->getRowCnt();  
  unsigned yStep = ceil( (abs(mMaxY) - abs(mMinY) )  / numRows );    
  unsigned xStep = avgCellW;    
  unsigned numXTiles = ceil( (abs(mMaxX) - abs(mMinX) ) / xStep);
  
  vector<vector<double>> out ( numRows, vector<double> (numXTiles, 0.0) ) ;	
  unsigned yOffset = max(mMinY-1,0.);  
  unsigned xOffset = max(mMinX-1,0.);  
  std::cout << "BBox: " << _bbox << "\n";
  std::cout << "s1: " << s1 << " s2: " << s2 << "\n";
  std::cout << "numRows: " << numRows << " yStep: " << yStep << "\n";
  std::cout << "numXTiles: " << numXTiles << " xStep: " << xStep << "\n";
  
  for (unsigned k = 0; k < numRows; k++) {
    for (unsigned i=0; i < yStep; i++){
      if ( yOffset >= s1 ) break;
      xOffset = (int) max(0.0, mMinX);  	  
      for (unsigned p=0; p < numXTiles; p++)
	  {		  
        for (unsigned j = 0; j < xStep; j++) {
          if ( xOffset >= s2 ) break;  
          try {
            out.at(k).at(p) += D( yOffset, xOffset );			
		  }
		  catch (std::exception& e)
	      { 
		    std::cout << "\n\nFailed to access index " << yOffset << ", "<< xOffset <<"\n\n"; 
          }
          xOffset++;		  
        }
	  }
		
      yOffset++;	  
	}      	  
  }
  

  vector<double> res(numRows, 1.0);
  for (unsigned i=0; i < numRows; i++)
  {
    if (out.at(i).size() > 0)	  
      res.at(i) = *max_element( out.at(i).begin(), out.at(i).end() );	  
/*     for (unsigned j=0; j < numXTiles; j++)
    {
      res.at(i) += out.at(i).at(j);		
    } */
  }	  

  std::cout << "\n\nFinished Rudy\n\n"; 
  
  return res;	
}
