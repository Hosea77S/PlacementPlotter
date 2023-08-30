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









//! author="Igor Markov, July 15, 1997"
//! CHANGES="plGeom.h 971113 mro unified unseeded, seeded ctors in RandomPoint 971205 ilm added BBox::ShrinkTo(double percent=0.9) with percent>0; percent > 1.0 will expand the BBox"

// 971113 mro unified unseeded, seeded ctors in RandomPoint
// 971205 ilm added BBox::ShrinkTo(double percent=0.9)
//             with percent>0; percent > 1.0 will expand the BBox

#ifndef PLGEOM_H
#define PLGEOM_H


#include "dbPoint.h"
#include "Bbox.h"

//: Generates a point randomly
class RandomPoint
{
   double _xGen;
   double _yGen;
   BBox _bb;
public:
   RandomPoint(const BBox& bb, unsigned xSeed=UINT_MAX, unsigned ySeed=UINT_MAX){
	   
	srand(xSeed);
	_xGen = ( rand() % int (bb.xMax - bb.xMin) ) + bb.xMin;
	                   
	srand(ySeed);      
	_yGen = ( rand() % int (bb.yMax - bb.yMin) ) + bb.yMin;	   
   }
   
    RandomPoint(BBox& bb, unsigned seed = time(NULL) ){
	   
	srand(seed);
	 
	_xGen = ( rand()% int (bb.xMax - bb.xMin) ) + bb.xMin;
	_yGen = ( rand()% int (bb.yMax - bb.yMin) ) + bb.yMin;	   
   }
   

   
   
/*    RandomPoint(BBox& bb){
	   
	long seed = 1464902610;
	srand(seed);
	_bb = bb;
	 
	_xGen = ( rand()% int (bb.xMax) ) + bb.xMin;
	_yGen = ( rand()% int (bb.yMax) ) + bb.yMin;	   
   }
 */   
   operator Point()    { return Point(_xGen,_yGen); }
   
/* 	Point getRand(){
		//srand(time(NULL));
		unsigned xGen = ( rand()% int (_bb.xMax) ) + _bb.xMin;
		unsigned yGen = ( rand()% int (_bb.yMax) ) + _bb.yMin;	   
		return Point(xGen, yGen);
	}
 */   
   
   
};

#endif //PLGEOM_H
