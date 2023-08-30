#include "subPlacement.h"


/* ============================ IMPLEMENTATION ========================== */

inline SubPlacement::SubPlacement
( Placement& rpl, const Subset& mp): 
_realPl(rpl), _inj(mp) 
{ 
     myAssert( int (_inj.getDestSize())<=_realPl.getSize(),
    "Can\'t construct Sub Placement: mapping and placement inconsistent\n");
}

inline BBox SubPlacement::getBBox() const 
{ 
  BBox box; 
  for (unsigned i=0; i<getSize(); i++) box+=points(i);  
  return box;
}

/* // uses smallPl to set locations in the _realPl member; returns _realPl
inline const Placement&  SubPlacement::
pushForward(const Placement& smallPl)
{
   for(unsigned i=0;i<getSize();i++)
      points(i)=smallPl[i];
   return _realPl;
}

// uses smallPl to set x locations in the _realPl member; returns _realPl
inline const Placement&  SubPlacement::
pushForwardX(const Placement& smallPl)
{
   for(unsigned i=0;i<getSize();i++)
      points(i).x=smallPl[i].x;
   return _realPl;
}

// uses smallPl to set y locations in the _realPl member; returns _realPl
inline const Placement&  SubPlacement::
pushForwardY(const Placement& smallPl)
{
   for(unsigned i=0;i<getSize();i++)
      points(i).y=smallPl[i].y;
   return _realPl;
}
 */
// empties smallPl and creates a new one, possibly of different size
// returns smallPl
inline Placement&  SubPlacement::
pullBack(Placement& smallPl)
{
   int nPts=getSize();
   smallPl._points= std::vector<Point> (nPts);
   for(unsigned i=0;i<getSize();i++)
      smallPl._points[i]=points(i);
   return smallPl;
}

// reorder the pints of _inj
inline void SubPlacement::reorder(const Permutation& pm)
{
  myAssert(pm.getSize()==getDestSize(),
            "Can't reorder a subplacement: wrong permutation size");
  for(unsigned k=0;k<getSize();k++) _inj[k]=pm[_inj[k]];
}


Point SubPlacement::getCenterOfGravity() const 
{ 
  Point cog(0,0); 
  for (unsigned i=0; i<getSize(); i++) 
  {
     cog.x+=points(i).x;
     cog.y+=points(i).y;
  }
  cog.x/=getSize();
  cog.y/=getSize();
  return cog;
}


Point SubPlacement::getCenterOfGravity(double * weights) const 
{ 
  Point cog(0,0); 
  for (unsigned i=0; i<getSize(); i++) 
  {
     cog.x+=weights[i]*points(i).x;
     cog.y+=weights[i]*points(i).y;
  }
  cog.x/=getSize();
  cog.y/=getSize();
  return cog;
}


double SubPlacement::getPolygonArea() const 
{ 
  double area=0.0;
  for (unsigned i=0; i<getSize()-1; i++) 
     area+=points(i).x * points(i+1).y - points(i+1).x * points(i).y;
  area+=points(getSize()-1).x * points(0).y - points(0).x*points(getSize()-1).y;
  return 0.5*area;
}


bool SubPlacement::isInsidePolygon(const Point& p) const 
{ 
  unsigned counter = 0;
  unsigned i;
  double xinters;
  Point  p1,p2;

  p1 = points(0);
  for (i=0;i<getSize();i++) {
    p2 = points(i % getSize());
    if (p.y > std::min(p1.y,p2.y)) {
      if (p.y <= std::max(p1.y,p2.y)) {
        if (p.x <= std::max(p1.x,p2.x)) {
          if (p1.y != p2.y) {
            xinters = (p.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
            if (p1.x == p2.x || p.x <= xinters)
              counter++;
          }
        }
      }
    }
    p1 = p2;
  }

  if (counter % 2 == 0)
    return(false); // outisde
  else
    return(true); // inside
}


std::ostream& operator<<(std::ostream& out, const SubPlacement& arg)
{
   out << " Total points in sub placement : " << arg.getSize() 
       << std::endl; 
   for (unsigned i=0; i<arg.getSize(); i++) out << arg.points(i) << std::endl ;
   return out;
}

/* 
double operator- (const SubPlacement& arg1, 
const SubPlacement& arg2)
 //returns the Linf distance between placements
 //   which you can compare then to epsilon     
{
   myAssert(arg1.getSize()==arg2.getSize()," Comparing placements of different size");
   double dst,max=0;
   for (unsigned i=0; i < arg1.getSize(); i++)
   { 
     dst=mDist(arg1[i],arg2[i]);
     if (max < dst) max=dst;
   }
   return max;
} */

