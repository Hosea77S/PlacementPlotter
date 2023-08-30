#include "dbPoint.h"




Point::operator std::string() const
{
  std::string text;	
  text += "(" + std::to_string(x) + "," + std::to_string(y) + ")";
  return text;
} 



Point getMedian ( const Point& a, const Point& b)
{
  Point temp; 
  temp.x = (double) ( (a.x + b.x) / 2.0); 
  temp.y = (double) ( (a.y + b.y) / 2.0);  
  
  return temp;
}
