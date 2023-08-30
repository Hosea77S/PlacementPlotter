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


#ifndef DBINTPOINT__H
#define DBINTPOINT__H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cfloat>

class IntPoint;


//: Point with integer coordinates
class IntPoint
{
public:
  int x;   
  int y;   

  IntPoint() {};  
  IntPoint(int xx, int yy) : x(xx),y(yy) {};
  IntPoint operator-(IntPoint arg) const
  {
    return IntPoint(x-arg.x,y-arg.y);
  }
  IntPoint& operator-=(IntPoint arg)
  {
    x-=arg.x,y-=arg.y;
    return *this;
  }

  IntPoint  operator+(const IntPoint arg) const
  {
    return IntPoint(x+arg.x,y+arg.y);
  }
  IntPoint& operator+=(IntPoint arg)
  {
    x+=arg.x,y+=arg.y;
    return *this;
  }

  bool   operator==(const IntPoint arg) const
  {
    return x==arg.x && y==arg.y;
  }
  bool   operator!=(const IntPoint arg) const
  {
    return x!=arg.x || y!=arg.y;
  }
  bool   operator<(const  IntPoint arg) const
  {
    if (x<arg.x) return true;
    if (x>arg.x) return false;
    if (y<arg.y) return true;
    return false;
  }

  IntPoint& moveBy(const IntPoint& arg)
  {
    x+=arg.x, y+=arg.y;
    return *this;
  }
  IntPoint& scaleBy(int xsc, int ysc)
  {
    x*=xsc, y*=ysc;
    return *this;
  }

  friend std::ostream&  operator<<(std::ostream& out, const IntPoint& arg);
};

inline double mDist(const IntPoint arg1,const IntPoint arg2)
{
  return abs(arg1.x-arg2.x)+abs(arg1.y-arg2.y);
}

inline std::ostream&  operator<<(std::ostream& out, const IntPoint& arg)
{
  out << "(" << std::setw(6) << arg.x << "," << std::setw(6) << arg.y << ")";
  return out;
}


#endif //__DBINTPOINT__H
