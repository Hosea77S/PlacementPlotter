/**************************************************************************
***    
*** Copyright (c) 1995-2000 Regents of the University of California,
***               Andrew E. Caldwell, Andrew B. Kahng and Igor L. Markov
*** Copyright (c) 2000-2010 Regents of the University of Michigan,
***               Saurabh N. Adya, Jarrod A. Roy, David A. Papa and
***               Igor L. Markov
***
***  Contact author(s): abk@cs.ucsd.edu, imarkov@umich.edu
***  Original Affiliation:   UCLA, Computer Science Department,
***                          Los Angeles, CA 90095-1596 USA
***
***  Permission is hereby granted, free of charge, to any person obtaining 
***  a copy of this software and associated documentation files (the
***  "Software"), to deal in the Software without restriction, including
***  without limitation 
***  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
***  and/or sell copies of the Software, and to permit persons to whom the 
***  Software is furnished to do so, subject to the following conditions:
***
***  The above copyright notice and this permission notice shall be included
***  in all copies or substantial portions of the Software.
***
*** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
*** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
*** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
*** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
*** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
*** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
*** THE USE OR OTHER DEALINGS IN THE SOFTWARE.
***
***
***************************************************************************/


#ifndef _GRID_IN_PL_H_
#define _GRID_IN_PL_H_

#include <iostream>
#include "placement.h"
#include "myAssert.h"

//: Used when placement is in grid 
class GridInPlacement
{
	  //total number of cells in each dimension
      unsigned         _xSize, _ySize; 
      BBox             _bbox;
      std::vector<int> _pointIdcs;
   public: 
      GridInPlacement(unsigned xSize, unsigned ySize, const Placement& pl);
      unsigned operator()(unsigned i, unsigned j)  // (i,j) grid point
         {  myAssert(i<_xSize && j<_ySize," Index out of range ");
            return _pointIdcs[_xSize*j+i];
         }
      ~GridInPlacement() {}

      unsigned getSize() const             { return _xSize * _ySize; } 
      std::vector<int> getPointIdcs() const { return _pointIdcs; }
};



#endif
