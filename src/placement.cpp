#include "placement.h"


 double operator-
  (const Placement& arg1, const Placement& arg2);
 // returns the Linf distance between placements
 // which you can compare then to epsilon     



/* ============================ IMPLEMENTATION ========================== */



/* inline void Placement::reorder(const Permutation& pm)
{
  myAssert(pm.getSize()==getSize(),
          "Can't reorder placement: wrong size of permutation\n");
  Point * newPoints = new Point[getSize()];
  unsigned k;
  for(k=0;k<getSize();k++) newPoints[pm[k]]=_points[k];
  for(k=0;k<getSize();k++) _points[k]=newPoints[k];
  delete[] newPoints;
}


inline void Placement::reorderBack(const Permutation& pm)
{
  myAssert(pm.getSize()==getSize(),
          "Can't reorder placement: wrong size of permutation\n");
  Point * newPoints = new Point[getSize()];
  unsigned k;
  for(k=0;k<getSize();k++) newPoints[k]=_points[pm[k]];
  for(k=0;k<getSize();k++) _points[k]=newPoints[k];
  delete[] newPoints;
}
 */

/* ============================ IMPLEMENTATION ========================== */
 
 Placement::Placement(unsigned n, Point pt)
{
  myAssert(n>0,"Empty placement");
  _points=std::vector<Point>(n, pt);
}

Point Placement::getCenterOfGravity() const 
{ 
  Point cog(0,0); 
  int nPts = getSize();
  for (int i=0; i<nPts; i++) 
  {
     cog.x+=_points[i].x;
     cog.y+=_points[i].y;
  }
  cog.x/=nPts;
  cog.y/=nPts;
  return cog;
}


Point Placement::getCenterOfGravity(const std::vector<double> &weights) const 
{ 
  Point cog(0,0); 
  int nPts = getSize();
  for (int i=0; i<nPts; i++) 
  {
     cog.x+=weights[i]*_points[i].x;
     cog.y+=weights[i]*_points[i].y;
  }
  cog.x/=nPts;
  cog.y/=nPts;
  return cog;
}


double Placement::getPolygonArea() const 
{ 
  double area=0.0;
  int nPts = getSize();
  for (int i=0; i<nPts-1; i++) 
     area+=_points[i].x * _points[i+1].y - _points[i+1].x * _points[i].y;
  area+=_points[nPts-1].x * _points[0].y - _points[0].x * _points[nPts-1].y;
  return 0.5*area;
}


bool Placement::isInsidePolygon(const Point& p) const 
{ 
  unsigned counter = 0;
  int i;
  double xinters;
  int nPts = getSize();
  Point  p1,p2;
  std::vector<Point> polygon (_points);

  p1 = polygon[0];
  for (i=0;i<nPts;i++) 
      {
    p2 = polygon[i % nPts];
    if ((p.y > std::min(p1.y,p2.y)) &&
       (p.y <= std::max(p1.y,p2.y))&&
        (p.x <= std::max(p1.x,p2.x)) &&
        (p1.y != p2.y) )
        {
            xinters = (p.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
            if (p1.x == p2.x || p.x <= xinters)
              counter++;
          }
    p1 = p2;
  }

  if (counter % 2 == 0) return(false); // outisde
  else                  return(true);  // inside
}

/* Placement::Placement(const Mapping& pullBackMap, const Placement& from):
nPts(pullBackMap.getSourceSize())
//pullback
{
  if (nPts==0) { points=NULL; return; }
  points=new Point[nPts];
  for (unsigned k=0;k<nPts;k++) points[k]=from[pullBackMap[k]];
} */

Placement::Placement(Placement::Examples ex, long int size, BBox bb)
{
   long long int  i,j, nXFixed, nYFixed = 0, nXandYFixed = 0, num=0;
   long long int nPts = 0; //#SOHEIL ADDED to support big benchmarks
   

   // setting sizes;
   switch (ex)
   {
      case _Random :
	  
                           nPts=size;
                           if (size/10>20) nYFixed=20;
                           else nYFixed=size/10;
                           nXandYFixed=nXFixed=nYFixed;
                           break;
      case _Grid1: 
                           if (size==0) size=5; 
                           nPts=size*size+4*size;
                           nXandYFixed=nXFixed=nYFixed=4*size;
                           break;
      case _Grid2: 
                           if (size==0) size=5;
                           nPts=size*size;
                           nXandYFixed=0;
                           break;
	  case _TRandom:
                           nPts=size;
						   nYFixed = nXandYFixed ;
                           break;
	  
   }

   //std::cout << "nPts: " << nPts << std::endl;
 switch (ex)
 {
  case _Random:
   {
      RandomPoint pt(bb);
      _points= std::vector<Point>(nPts);
      for(i=0;i<size;i++)
         _points.at(i)=pt;
      for(i=0;i<nYFixed/4;i++)
         _points.at(i).x=0;
      for(i=nYFixed/4;i<nYFixed/2;i++)
         _points.at(i).y=1;
      for(i=nYFixed/2;i<3*nYFixed/4;i++)
         _points.at(i).x=1;
      for(i=3*nYFixed/4;i<nYFixed;i++)
         _points.at(i).y=0;
      return;
   }
  case _Grid1:
   {
      _points=std::vector<Point>(nPts);;
      long double xGridStep=(bb.xMax-bb.xMin)/(size+1);
      long double yGridStep=(bb.yMax-bb.yMin)/(size+1);
      for(i=0;i<size;i++) _points.at(num++)=Point(bb.xMin,bb.yMin+yGridStep*(1+i));
      for(i=0;i<size;i++) _points.at(num++)=Point(bb.xMax,bb.yMin+yGridStep*(1+i));
      for(i=0;i<size;i++) _points.at(num++)=Point(bb.xMin+xGridStep*(1+i),bb.yMin);
      for(i=0;i<size;i++) _points.at(num++)=Point(bb.xMin+xGridStep*(1+i),bb.yMax);
      for(i=0;i<size;i++)
        for(j=0;j<size;j++)
           _points.at(num++)=Point(bb.xMin+xGridStep*(1+i),bb.yMin+yGridStep*(1+j));
      return;
   }
  case _Grid2:
   {
      _points=std::vector<Point>(nPts);;
      long double xGridStep=(bb.xMax-bb.xMin)/(size-1);
      long double yGridStep=(bb.yMax-bb.yMin)/(size-1);
      for(i=0;i<size;i++)
        for(j=0;j<size;j++)
          _points.at(num++)=Point(bb.xMin+xGridStep*i,bb.yMin+yGridStep*j);
      return;
   }
  case _TRandom:
  {
      _points= std::vector<Point>(nPts);
      for(i=0;i<size;i++)
         _points.at(i)=RandomPoint(bb, i, i+1);
      return;
	  
  }
	//TODO search for Linear congruential generator 
	//https://www.cmpe.boun.edu.tr/~cemgil/Courses/cmpe548/mc-lecture02.pdf
   
  default : myAssert(0,"Unknown placement example");
}
}


/* Placement::Placement(istream& in)
{
  int lineNo=1;
  char word1[100], word2[100], word3[100];
  in >> eathash(lineNo) >> word1 >> word2 >> word3 ;
  myAssert(strcasecmp(word1,"Total")==0,
           "Placement files should start with \'Total points :\'\n");
  myAssert(strcasecmp(word2,"points")==0,
           "Placements files should start with \'Total points :\'\n");
  myAssert(strcasecmp(word3,":")==0,
           "Placements files should start with \'Total points :\'\n");
  in >> my_isnumber(lineNo) >> nPts >> skiptoeol;

  myAssert(nPts>0,"Empty placement"); 
  _points=new Point[nPts];
  for (unsigned i=0; i<nPts; i++)
       in >> eathash(lineNo) >> _points[i] >> skiptoeol;
} */

Placement&  
Placement::operator=(const Placement& from)
{  // this can be sped up with strcpy()
   if (from._points==_points) return *this;
   int nPts=from.getSize();
   _points= std::vector<Point>(nPts);
   for(int i=0;i<getSize();i++)
          _points[i]=from[i];
   return *this;
}


/*  double operator-
  (const Placement& arg1, const Placement& arg2)
 // returns the Linf distance between placements
  // which you can compare then to epsilon     
{
   myAssert(arg1.getSize()==arg2.getSize()," Comparing placements of different size");
   double dst,max=0;
   for (int i=0; i < arg1.getSize(); i++)
   { 
     dst=mDist(arg1[i],arg2[i]);
     if (max < dst) max=dst;
   }
   return max;
} */


void Placement::flipXY()
{
   for(int i=getSize(); i!=0; )
   {
      i--;
      std::swap(_points[i].x,_points[i].y);
   }
}

