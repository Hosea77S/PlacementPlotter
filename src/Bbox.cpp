#include "Bbox.h"


/* ============================ IMPLEMENTATION ========================== */

std::ostream&  operator<<(std::ostream& out, const BBox& arg){
  if (arg.isEmpty()) out  << "Empty BBox: ";
  out     << arg.xMin << "  " << arg.yMin <<
    "   " << arg.xMax << "  " << arg.yMax;
  return out;
	
}

std::istream&  operator>>(std::istream& in, BBox& arg);


void SmartBBox::computeAux()
{  
  myAssert(!isEmpty(),"Can\'t have empty SmartBBox");
  _xleft=center.x-xMin;
  _xright=xMax-center.x;
  _yup=yMax-center.y;
  _ydown=center.y-yMin;
  _phi1=atan2(-_xleft,-_ydown);
  _phi3=atan2(-_xleft,_yup);
  _phi5=atan2(_xright,_yup);
  _phi7=atan2(_xright,-_ydown);
  _area1=0.5*_ydown*_xleft;
  _area2=_area1+0.5*_ydown*_xleft;
  _area3=_area2+0.5*_yup*_xleft;
  _area4=_area3+0.5*_yup*_xleft;
  _area5=_area4+0.5*_yup*_xright;
  _area6=_area5+0.5*_yup*_xright;
  _area7=_area6+0.5*_ydown*_xright;
  _totalArea=_area7+0.5*_ydown*_xright;
}


Point& SmartBBox::coerce(Point& pt)
{ 
  myAssert(!isEmpty(),"Can\'t coerce to an empty SmartBBox");
  if (contains(pt)) return pt;
  double dx=pt.x-center.x;
  double dy=pt.y-center.y;
  double dist=sqrt(pow(dx,2)+pow(dy,2));
  double segLen=segLength(atan2(dx,dy));
  double tau=segLen/dist;
  pt.x=center.x+tau*dx; 
  pt.y=center.y+tau*dy;
  return pt;
}


double SmartBBox::segLength(double phi)
{
  if (phi<_phi1) return -_ydown/cos(phi);
  if (phi<_phi3) return -_xleft/sin(phi);
  if (phi<_phi5) return  _yup/cos(phi);
  if (phi<_phi7) return  _xright/sin(phi);
      return -_ydown/cos(phi);
}

