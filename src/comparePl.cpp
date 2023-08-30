#include "comparePl.h"




double MaxMDiff ::operator()
(Placement& pl1,Placement& pl2)
   {  
	myAssert(pl1.getSize()==pl2.getSize(),
		   "Can\'t compare placements of different sizes");
	double dst,max=0.0;
	for(int i=0;i<pl1.getSize();i++)
	{
	   dst=mDist(pl1[i],pl2[i]);
	   if (dst>max) max=dst;
	}  
	return max;
   }    

 
double AvgMDiff::operator()
(Placement& pl1,Placement& pl2)
   {
	myAssert(pl1.getSize()==pl2.getSize(),
		   "Can\'t compare placements of different sizes");
	double sum=0.0;
	for(int i=0;i<pl1.getSize();i++)
	{
	   sum+=mDist(pl1[i],pl2[i]);
	}
	return sum/pl1.getSize();
   }

 
double AvgElongation::operator() 
(Placement& pl1,Placement& pl2)
   {  
	myAssert(pl1.getSize()==pl2.getSize(),
		   "Can\'t compare placements of different sizes");
	double sum=0.0;
	randomNumber randIdx(0,pl1.getSize());
	for(int i=0;i<5*pl1.getSize();i++)
	{
	   unsigned idxA=randIdx;
	   unsigned idxB=randIdx;
	   double dist1=mDist(pl1[idxA],pl1[idxB]);
	   double dist2=mDist(pl2[idxA],pl2[idxB]);
	   sum+=fabs(dist2-dist1);
	}
	return sum/(5*pl1.getSize());
   }

 
double MaxElongation::operator() 
(Placement& pl1,Placement& pl2)
   {  
	myAssert(pl1.getSize()==pl2.getSize(),
		   "Can\'t compare placements of different sizes");
	double max=0.0;
	randomNumber randIdx(0,pl1.getSize());
	for(int i=0;i<5*pl1.getSize();i++)
	{
	   unsigned idxA=randIdx;
	   unsigned idxB=randIdx;
	   double dist1=mDist(pl1[idxA],pl1[idxB]);
	   double dist2=mDist(pl2[idxA],pl2[idxB]);
	   if (max<fabs(dist2-dist1)) max=fabs(dist2-dist1);
	}
	return max;
   }

 
double AvgStretch:: operator() 
(Placement& pl1,Placement& pl2)
   {
	myAssert(pl1.getSize()==pl2.getSize(),
		   "Can\'t compare placements of different sizes");
	double sum=0.0;
	randomNumber randIdx(0,pl1.getSize());
	for(int i=0;i<5*pl1.getSize();i++)
	{
	   unsigned idxA=randIdx;
	   unsigned idxB=randIdx;
	   double dist1=mDist(pl1[idxA],pl1[idxB]);
	   double dist2=mDist(pl2[idxA],pl2[idxB]);
	   if (dist1>1e-15 && dist2>1e-15)
	   {
                double rat=dist2/dist1;
                if (rat>1)
		  sum+=rat;
                else 
                  sum+=1/rat;
	   }
	}
	return sum/(5*pl1.getSize());
   }

 
double MaxStretch:: operator() 
(Placement& pl1,Placement& pl2)
   {
	myAssert(pl1.getSize()==pl2.getSize(),
		   "Can\'t compare placements of different sizes");
	double max=0.0;
	randomNumber randIdx(0,pl1.getSize());
	for(int i=0;i<5*pl1.getSize();i++)
	{
	   unsigned idxA=randIdx;
	   unsigned idxB=randIdx;
	   double dist1=mDist(pl1[idxA],pl1[idxB]);
	   double dist2=mDist(pl2[idxA],pl2[idxB]);
	   if (dist1>1e-15 && dist2>1e-15)
	   {
                double rat=dist2/dist1;
                if (rat>1) rat=1/rat;
		if (max<rat) max=rat;
	   }
	}
	return max;
   }


