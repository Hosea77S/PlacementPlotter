/**************************************************************************
***    
*** Copyright (c) 1995-2000 Regents of the University of California,
***               Andrew E. Caldwell, Andrew B. Kahng and Igor L. Markov
*** Copyright (c) 2000-2002 Regents of the University of Michigan,
***               Saurabh N. Adya and Igor L. Markov
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





//created by Saurabh Adya, Dec 3 2000
#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <algorithm>
#include <list>
#include "sgi_hash_map.h"
#include "abkcommon.h"
#include "RBPlacement.h"

#ifdef _MSC_VER
#ifndef rint
#define rint(a) floor((a)+0.5)
#endif
#endif


//function to search a list
bool findInList(itRBPSubRow its, list<itRBPSubRow>& seenList)
{
  std::list<itRBPSubRow>::iterator listElem;
  bool foundInList = 0;
  for(listElem = seenList.begin();
      listElem != seenList.end();
      ++listElem)
    if(its == *listElem)
      {
	foundInList = 1;
	break;
      }
  return(foundInList);
}
//added by sadya to remove overlaps in each subrow
void RBPlacement::remOverlapsSR(void)
{
  if (_params.verb.forActions) cout << " Running overlap removal ..." << endl;
  double initHPWL=evalHPWL();
  if (_params.verb.forMajStats)
                   cout << "  HPWL before overlap remover is "<<initHPWL<<endl;
  Timer tm;

  itRBPCoreRow itc;
  itRBPSubRow its;

  unsigned initOverlaps = getNumOverlaps();

  //for each core row, for each subrow scan left to right if overlap found then take action
  for(itc=_coreRows.begin();itc!=_coreRows.end();++itc)
    {
      for(its=itc->subRowsBegin();its!=itc->subRowsEnd();++its)
	shuffleSR(its);
    }
  tm.stop();
  double HPWLafter=evalHPWL();
  double HPWLwPins=evalHPWL(true);
  unsigned finalOverlaps = getNumOverlaps();

  if (_params.verb.forMajStats) 
  {
    cout<<" Removing overlaps took " << tm << endl;
    cout<<"  Discovered " << initOverlaps << " overlaps "<<endl;
    cout<<"  Overlaps remaining: "<<finalOverlaps<<endl;
    cout<<"  HPWL after  overlap removal is "<<HPWLafter<<endl;
    cout<<"  HPWL w pins                 is "<<HPWLwPins<<endl;
    cout<<"  % change in HPWL is "<<(HPWLafter-initHPWL)*100/HPWLafter<<endl;
  }
}

//added by sadya to remove overlaps in each subrow
void RBPlacement::remOverlapsVert(void)
{
  if (_params.verb.forActions) 
    cout << " Running overlap removal with Vertical Moves..." << endl;
  double initHPWL=evalHPWL();
  if (_params.verb.forMajStats)
    cout << "  HPWL before overlap remover is "<<initHPWL<<endl;
  Timer tm;
  
  itRBPCoreRow itc;
  itRBPSubRow its;
  itRBPCellIds itn;
  itRBPCellIds itntemp;
  itRBPCoreRow itcNext;   //used to scan immediate next row
  itRBPSubRow itsNext;    //used to scan immediate next sub row 
  itRBPCellIds itnNext;   //used to scan immediate next sub row cells
  itRBPCellIds itnright;   //used to scan immediate next sub row cells
  itRBPCellIds itnNextLeft; //used to scan 
  itRBPCellIds itnNextRight; //used to scan 
  
  RBPSubRow tempSR;
  
  bool leftRight=false;   //false means move left else move right
  double WS=0;
  unsigned numOverlaps=0;
  unsigned totalOverlaps=0;
  double rowHeight=0;
  double xDiff=0;
  //for each core row, for each subrow scan left to right if overlap found then take action
  for(itc=_coreRows.begin();itc!=_coreRows.end();++itc)
    {
      rowHeight=itc->getHeight();
      for(its=itc->subRowsBegin();its!=itc->subRowsEnd();++its)
	{
	  for(itn=its->cellIdsBegin();itn!=its->cellIdsEnd();++itn)
	    {
	      //check for overlaps in the same row
	      xDiff=1;
	      if(itn!=its->cellIdsEnd()-1)
		{
		  itntemp=itn+1;
		  xDiff= _placement[*itn].x + 
		    _hgWDims->getNodeWidth(*itn)-_placement[*itntemp].x;
		  if(xDiff > 1e-10)
		    {
		      //overlap found, now deal with it
		      numOverlaps++;
		      totalOverlaps++;

		      itnright = itntemp;

		      //check for WS in upper rows
		      if(itc!=_coreRows.end()-1)
			{
			  itcNext = itc+1;
			  for(itsNext=itcNext->subRowsBegin();
			      itsNext!=itcNext->subRowsEnd();++itsNext)
			    {
			      for(itnNext=itsNext->cellIdsBegin();
				  itnNext!=itsNext->cellIdsEnd()-1;++itnNext)
				{
				  //check for WS in the upper adjacent  row
				  if((_placement[*itnNext].x <=
				      _placement[*itn].x) &&
				     (_placement[*(itnNext+1)].x >=
				      _placement[*itn].x))
				    break;   //closest cell found in upper
				             //row
				}
			      itnNextLeft = itnNext;
			      itnNextRight = itnNext;
			      
			      while(itnNextRight!=itsNext->cellIdsEnd()-1 ||
				    itnNextLeft!=itsNext->cellIdsBegin())
				{
				  if(leftRight==false && 
				     itnNextRight!=itsNext->cellIdsEnd()-1)
				    leftRight=true;
				  else if(leftRight==true && 
					  itnNextLeft!=itsNext->cellIdsBegin())
				    leftRight=false;
				  
				  if(leftRight == true)  //search right
				    {
				      itntemp=itnNextRight+1;
				      WS=_placement[*itntemp].x -
					_placement[*itnNextRight].x -
					_hgWDims->getNodeWidth(*itnNextRight);
				      if(WS > 0)   //white space found
					{
					  if(WS >=_hgWDims->getNodeWidth(*itn))
					    {
					      tempSR = *its;
					      tempSR.removeCell(*itn);
					      _placement[*itn].x = 
						_placement[*itnNextRight].x;
					      _placement[*itn].y = 
						itsNext->getYCoord();
					      tempSR = *itsNext;
					      tempSR.addCell(*itn);
					      --numOverlaps;
					      break;
					    }
					  else if
					    (WS>=
					     _hgWDims->getNodeWidth(*itnright))
					    {
					      tempSR = *its;
					      tempSR.removeCell(*itnright);
					      _placement[*itnright].x = 
						_placement[*itnNextRight].x;
					      _placement[*itnright].y = 
						itsNext->getYCoord();
					      tempSR = *itsNext;
					      tempSR.addCell(*itnright);
					      --numOverlaps;
					      break;
					    }
					  else
					    {
					      
					    }
					}
				      ++itnNextRight;
				    }
				  else //search left for WS
				    {
				      itntemp=itnNextLeft-1;
				      WS = _placement[*itnNextLeft].x -
					_placement[*itntemp].x -
					_hgWDims->getNodeWidth(*itntemp);
				      if(WS > 0)   //white space found
					{
					  if(WS >=_hgWDims->getNodeWidth(*itn))
					    {
					      tempSR = *its;
					      tempSR.removeCell(*itn);
					      _placement[*itn].x=
						_placement[*itntemp].x;
					      _placement[*itn].y=
						itsNext->getYCoord();
					      tempSR = *itsNext;
					      tempSR.addCell(*itn);
					      --numOverlaps;
					      break;
					    }
					  else if
					    (WS >= 
					     _hgWDims->getNodeWidth(*itnright))
					    {
					      tempSR = *its;
					      tempSR.removeCell(*itnright);
					      _placement[*itnright].x = 
						_placement[*itntemp].x;
					      _placement[*itnright].y=
						itsNext->getYCoord();
					      tempSR = *itsNext;
					      tempSR.addCell(*itnright);
					      --numOverlaps;
					      break;
					    }
					}
				      itnNextLeft--;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
  tm.stop();
  double HPWLafter=evalHPWL();
  double HPWLwPins=evalHPWL(true);
  if (_params.verb.forMajStats) 
    {
      cout<<" Removing overlaps took " << tm << endl;
      cout<<"  Discovered " << totalOverlaps << " overlaps "<<endl;
      cout<<"  Overlaps remaining: "<<numOverlaps<<endl;
      cout<<"  HPWL after  overlap removal is "<<HPWLafter<<endl;
      cout<<"  HPWL w pins                 is "<<HPWLwPins<<endl;
      cout<<"  % change in HPWL is "<<(HPWLafter-initHPWL)*100/HPWLafter<<endl;
    }
}

void RBPlacement::snapCellsInSites(void)
{
  itRBPCoreRow itc;
  itRBPSubRow its;
  itRBPCellIds itn;
  //itRBPCellIds itntemp;
  double siteSpacing;
  int index;
  
  for(itc=_coreRows.begin();itc!=_coreRows.end();++itc)
    {
      for(its=itc->subRowsBegin();its!=itc->subRowsEnd();++its)
	{
	  siteSpacing = its->getSpacing();
	  for(itn=its->cellIdsBegin();itn!=its->cellIdsEnd();++itn)
	    {
	      if(int(_placement[*itn].x)%int(siteSpacing) != 0 || 
		 _placement[*itn].x != int(_placement[*itn].x))
		{
		  //cout<<"cell not in site "<<endl;
		  index = *itn;
		  int newPosX = int(_placement[*itn].x) 
		    - int(_placement[*itn].x)%int(siteSpacing);

		  _placement[*itn].x = newPosX;
		}
	    }
	}
    }  
}


void RBPlacement::remOverlaps(void)
{
  if (_params.verb.forActions) cout << " Running overlap removal ..." << endl;
  double initHPWL=evalHPWL();
  if (_params.verb.forMajStats)
                   cout << "  HPWL before overlap remover is "<<initHPWL<<endl;
  Timer tm;

  itRBPCoreRow itc;
  itRBPCoreRow itcNext;   //used to scan immediate next row
  itRBPCoreRow itcCurr;   //used to scan immediate next row
  itRBPSubRow its;
  itRBPSubRow itsCurr;    //used to track current sub row in bfs
  itRBPCellIds itn;
  itRBPCellIds itntemp;
  itRBPCellIds itnToMove;
  itRBPSubRow itsNext;    //used to scan next sub row 
  double rowHeight=0;
  double nodeHeight=0;
  double xDiff=0;
  const unsigned threshold = 50;

  unsigned initOverlaps = getNumOverlaps();

  
  //for each core row, for each subrow scan left to right if overlap found then take action
  for(itc=_coreRows.begin();itc!=_coreRows.end();++itc)
    {
      rowHeight=itc->getHeight();
      for(its=itc->subRowsBegin();its!=itc->subRowsEnd();++its)
	{
	  shuffleSR(its);
	  for(itn=its->cellIdsBegin();itn!=its->cellIdsEnd();++itn)
	    {
	      nodeHeight=_hgWDims->getNodeHeight(*itn);
	      //check for overlaps in the same row
	      xDiff=1;
	      if(itn!=its->cellIdsEnd()-1)
		{
		  itntemp=itn+1;
		  xDiff= _placement[*itn].x + 
		    _hgWDims->getNodeWidth(*itn)-_placement[*itntemp].x;

		  if(xDiff > 1e-10)
		    {
		      //overlap found, now deal with it

		      double srOrigStart = its->getXStart();
		      double srOrigEnd = srOrigStart + its->getNumSites()*
			                               its->getSiteWidth();
		      list<itRBPSubRow> bfsList;
		      list<itRBPSubRow> seenList;
		      bfsList.push_back(its);
		      seenList.push_back(its);

		      //try to move the smallest node
		      if(_hgWDims->getNodeWidth(*itn) > 
			 _hgWDims->getNodeWidth(*(itn+1)))
			itnToMove = itn+1;
		      else
			itnToMove = itn;

		      unsigned cutoffCtr = 0;
		      while(cutoffCtr < threshold && !bfsList.empty())
			{
			  ++cutoffCtr;
			  itsCurr = *(bfsList.begin());
			  bfsList.pop_front();
			  itcCurr = static_cast<itRBPCoreRow>
				      (&itsCurr->getCoreRow());

			  double srStart = itsCurr->getXStart();
			  double srEnd = srStart + itsCurr->getNumSites()*
			                           itsCurr->getSiteWidth();

			  double srWidth = srEnd - srStart;
			  double cellWidths=0;
			  for(itntemp = itsCurr->cellIdsBegin(); 
			      itntemp != itsCurr->cellIdsEnd(); ++itntemp)
			    cellWidths += _hgWDims->getNodeWidth(*itntemp);

			  double widthToMove = 
			    _hgWDims->getNodeWidth(*itnToMove);

//cout<<" overlap x "<<_placement[*itn].x<<" YCoord: "<<itsCurr->getYCoord()<<" XCoords: "<<srStart<<"  "<<srEnd<<" list Size: "<<bfsList.size()<<" widthToMove "<<widthToMove<<" space "<<(srWidth-cellWidths)<<endl;
			  //found sr to move
			  if(widthToMove <= (srWidth-cellWidths)) 
			    {
//cout<<"found subrow "<<widthToMove<<"  "<<(srWidth-cellWidths)<<" "<<_hgWDims->getNodeByIdx(*itnToMove).getName()<<" "<<*itnToMove<<endl;
			      double xLocToMoveTo=0;

			      if(srEnd <= srOrigStart) //move left most cell
				{
				  double leftNodeWidth = 
				  _hgWDims->getNodeWidth(*its->cellIdsBegin());
				  if(leftNodeWidth <= widthToMove)
				    {
				      itnToMove = its->cellIdsBegin();
				      widthToMove = leftNodeWidth;
				    }
				  xLocToMoveTo = srEnd - widthToMove;
				}
			      else if(srStart >= srOrigEnd) //move right cell
				{
				  double rightNodeWidth = 
				  _hgWDims->getNodeWidth(*(its->cellIdsEnd()-1));
				  if(rightNodeWidth <= widthToMove)
				    {
				      itnToMove = its->cellIdsEnd()-1;
				      widthToMove = rightNodeWidth;
				    }
				  xLocToMoveTo = srStart;
				}
			      else//move the current cell
				{
				  if(srEnd <= _placement[*itnToMove].x)
				    xLocToMoveTo = srEnd - widthToMove;
				  else if(srStart >= _placement[*itnToMove].x)
				    xLocToMoveTo = srStart;
				  else
				    xLocToMoveTo = _placement[*itnToMove].x;
				}
		              unsigned indexToMove = *itnToMove;

		              RBPSubRow& tempSR1=const_cast<RBPSubRow&>(*its);
			      tempSR1.removeCell(indexToMove);
			      _placement[indexToMove].x = xLocToMoveTo;
			      _placement[indexToMove].y = itsCurr->getYCoord();
			      RBPSubRow& tempSR2 = 
				const_cast<RBPSubRow&>(*itsCurr);
			      tempSR2.addCell(indexToMove);
			      shuffleSR(itsCurr);
			      shuffleSR(its);
			      break;
			    }

			  //add new elements to bfsList
			  if(itsCurr != itcCurr->subRowsEnd()-1)
			    {
			      itsNext = itsCurr+1;
			      if(findInList(itsNext, seenList) == 0)
				{
				  bfsList.push_back(itsNext);
				  seenList.push_back(itsNext);
				}
			    }
			  if(itsCurr != itcCurr->subRowsBegin())
			    {
			      itsNext = itsCurr-1;
			      if(findInList(itsNext, seenList) == 0)
				{
				  bfsList.push_back(itsNext);
				  seenList.push_back(itsNext);
				}
			    }
			  if(itcCurr != _coreRows.end()-1)
			    {
			      itcNext = itcCurr+1;
			      for(itsNext = itcNext->subRowsBegin();
				  itsNext!=itcNext->subRowsEnd();++itsNext)
				{
				  double nextsrStart = itsNext->getXStart();
				  double nextsrEnd = nextsrStart + 
				    itsNext->getNumSites()*
				    itsNext->getSiteWidth();
				  
				  if((nextsrStart <= srStart && 
				      nextsrEnd >= srStart) || 
				     (nextsrStart >= srStart &&
				      nextsrEnd <= srEnd) ||
				     (nextsrStart <= srEnd &&
				      nextsrEnd >= srEnd)) //overlapping SR
				    {
				      if(findInList(itsNext, seenList) == 0)
					{
					  bfsList.push_back(itsNext);
					  seenList.push_back(itsNext);
					}
				    }
				}
			    }
			  if(itcCurr != _coreRows.begin())
			    {
			      itcNext = itcCurr-1;
			      for(itsNext = itcNext->subRowsBegin();
				  itsNext!=itcNext->subRowsEnd();++itsNext)
				{
				  double nextsrStart = itsNext->getXStart();
				  double nextsrEnd = nextsrStart + 
				    itsNext->getNumSites()*
				    itsNext->getSiteWidth();
				  
				  if((nextsrStart <= srStart && 
				      nextsrEnd >= srStart) || 
				     (nextsrStart >= srStart &&
				      nextsrEnd <= srEnd) ||
				     (nextsrStart <= srEnd &&
				      nextsrEnd >= srEnd)) //overlapping SR
				    {
				      if(findInList(itsNext, seenList) == 0)
					{
					  bfsList.push_back(itsNext);
					  seenList.push_back(itsNext);
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
  tm.stop();
  double HPWLafter=evalHPWL();
  double HPWLwPins=evalHPWL(true);
  unsigned finalOverlaps = getNumOverlaps();

  if (1/*_params.verb.forMajStats*/) 
  {
    cout<<" Removing overlaps took " << tm << endl;
    cout<<"  Discovered " << initOverlaps << " overlaps "<<endl;
    cout<<"  Overlaps remaining: "<<finalOverlaps<<endl;
    cout<<"  HPWL after  overlap removal is "<<HPWLafter<<endl;
    cout<<"  HPWL w pins                 is "<<HPWLwPins<<endl;
    cout<<"  % change in HPWL is "<<(HPWLafter-initHPWL)*100/HPWLafter<<endl;
  }
}

void RBPlacement::shuffleSR(itRBPSubRow its)
{
  itRBPCellIds itn;
  itRBPCellIds itntemp;
  itRBPCellIds itnleft;
  itRBPCellIds itnright;

  if(its->getNumCells() == 0)
    return;

  if(its->getNumCells() == 1)
    {
      itn = its->cellIdsBegin();
      if(_placement[*itn].x < its->getXStart())
        _placement[*itn].x = its->getXStart();
      else if(its->getXEnd() < 
	      (_placement[*itn].x + _hgWDims->getNodeWidth(*itn)))
       _placement[*itn].x = its->getXEnd()-_hgWDims->getNodeWidth(*itn);

      return;
    }

  //itRBPSubRow itsNext;    //used to scan immediate next sub row 
  //itRBPCellIds itnNext;   //used to scan immediate next sub row cells

  bool leftRight=false;   //false means move left else move right
  double WS=0;
  //double rowHeight=0;
  double nodeHeight=0;
  double xDiff=0;  
  double totalOverlap=0;
  double totalCellWidths=0;

  //snap all cells outside row to the row
  for(itn=its->cellIdsBegin();itn!=its->cellIdsEnd();++itn)
    {
      if(_placement[*itn].x < its->getXStart())
        _placement[*itn].x = its->getXStart();
      else if(its->getXEnd() < 
	      (_placement[*itn].x + _hgWDims->getNodeWidth(*itn)))
       _placement[*itn].x = its->getXEnd()-_hgWDims->getNodeWidth(*itn);

    }

  for(itn=its->cellIdsBegin();itn!=its->cellIdsEnd();++itn)
    {
      //check for overlaps in the same row
      xDiff=1;
      totalCellWidths += _hgWDims->getNodeWidth(*itn);
      itntemp=itn+1;
      if(itntemp != its->cellIdsEnd())
        {
          xDiff= _placement[*itn].x +
            _hgWDims->getNodeWidth(*itn)-_placement[*itntemp].x;

          if(xDiff > 1e-10)
            {
              //overlap found, now deal with it
	      totalOverlap += xDiff;
	    }
        }
    }

  if(totalOverlap <= 1e-10)
    return;

  double totalSiteWidths = its->getXEnd()-its->getXStart();
  itn = its->cellIdsBegin();
  double startWS = _placement[*itn].x - its->getXStart();
  itn = its->cellIdsEnd()-1;
  double endWS = its->getXEnd()-_placement[*itn].x-_hgWDims->getNodeWidth(*itn);
  double WSNeeded = totalCellWidths+startWS+endWS-totalSiteWidths;
  if(WSNeeded > 0)
    {
      itn = its->cellIdsBegin();
      if(WSNeeded <= startWS)
        {
   	  _placement[*itn].x = _placement[*itn].x - WSNeeded;
          WSNeeded = 0; 
        }  
      else if(startWS > 0)
       {
  	 _placement[*itn].x = _placement[*itn].x - startWS;
	 WSNeeded = WSNeeded - startWS;	 
       }
      if(_placement[*itn].x < its->getXStart())
        _placement[*itn].x = its->getXStart();

      itn = its->cellIdsEnd()-1;
      if(WSNeeded <= endWS)
        {
          _placement[*itn].x = _placement[*itn].x + WSNeeded;
          WSNeeded = 0;
        }
      else if(endWS > 0)
       {
         _placement[*itn].x = _placement[*itn].x + endWS;
         WSNeeded = WSNeeded - endWS;
       }
     if(its->getXEnd() < (_placement[*itn].x + _hgWDims->getNodeWidth(*itn)))
       _placement[*itn].x = its->getXEnd()-_hgWDims->getNodeWidth(*itn);
    }

  WS = 0;
  xDiff = 0;

  for(itn=its->cellIdsBegin();itn!=its->cellIdsEnd();++itn)
    {
      nodeHeight=_hgWDims->getNodeHeight(*itn);
      //check for overlaps in the same row
      xDiff=1;
      if(itn!=its->cellIdsEnd()-1)
	{
	  itntemp=itn+1;
	  xDiff= _placement[*itn].x + 
	    _hgWDims->getNodeWidth(*itn)-_placement[*itntemp].x;
	  
	  if(xDiff > 1e-10)
	    {
	      //overlap found, now deal with it
	      
	      itnleft=itn;
	      itnright=itn;
	      leftRight=false;
	      
	      while(xDiff>1e-10 && (itnleft!=(its->cellIdsBegin()) || 
				    itnright!=(its->cellIdsEnd()-2)))
		{
		  // chose the direction of search
		  if(leftRight==false && itnright!=its->cellIdsEnd()-2)
		    leftRight=true;
		  else if(leftRight==true && 
			  itnleft!=its->cellIdsBegin())
		    leftRight=false;
		  
		  if(leftRight==true)//search right for WS
		    {
		      ++itnright;
		      itntemp=itnright+1;
		      WS=_placement[*itntemp].x -
			_placement[*itnright].x -
			_hgWDims->getNodeWidth(*itnright);
		      if(WS > 0) //WS found
			{
			  if(WS > xDiff)
			    WS=xDiff;
			  xDiff-=WS;
			  for(itntemp=itn+1;itntemp!=itnright+1;
			      ++itntemp)
			    _placement[*itntemp].x+=WS;
			}
		    }
		  else //search left for WS
		    {
		      itntemp=itnleft;
		      --itnleft;
		      WS=_placement[*itntemp].x -
			_placement[*itnleft].x -
			_hgWDims->getNodeWidth(*itnleft);
		      if(WS > 0) //WS found
			{
			  if(WS > xDiff)
			    WS=xDiff;
			  xDiff-=WS;
			  for(itntemp=itn;itntemp!=itnleft;--itntemp)
			    {
			      _placement[*itntemp].x-=WS;
			    }
			}
		    }
		}
	    }
	}
    }

  //again snap all cells outside row to the row
  for(itn=its->cellIdsBegin();itn!=its->cellIdsEnd();++itn)
    {
      if(_placement[*itn].x < its->getXStart())
        _placement[*itn].x = its->getXStart();
      else if(its->getXEnd() < 
	      (_placement[*itn].x + _hgWDims->getNodeWidth(*itn)))
       _placement[*itn].x = its->getXEnd()-_hgWDims->getNodeWidth(*itn);
    }
}

unsigned RBPlacement::getNumOverlaps()
{
  unsigned overlaps = 0;
  itRBPCellIds itn;
  itRBPCellIds itntemp;
  itRBPCoreRow itc;
  itRBPSubRow its;

  double xDiff=0;
  for(itc=_coreRows.begin();itc!=_coreRows.end();++itc)
    {
      for(its=itc->subRowsBegin();its!=itc->subRowsEnd();++its)
	{
	  for(itn=its->cellIdsBegin();itn!=its->cellIdsEnd();++itn)
	    {
	      //check for overlaps in the same row
	      xDiff=1;
	      if(itn!=its->cellIdsEnd()-1)
		{
		  itntemp=itn+1;
		  xDiff= _placement[*itn].x + 
		    _hgWDims->getNodeWidth(*itn)-_placement[*itntemp].x;
		  
		  if(xDiff > 1e-10)
		    overlaps++;
		}
	    }
	}
    }
  return(overlaps);
}

bool RBPlacement::checkOutOfCoreCells(void)
{
  BBox layout = getBBox(false);
  bool consistent=true;
  double rowHeight=coreRowsBegin()->getHeight();

  for(unsigned i=0; i<getNumCells(); i++)
    {
      if(_isCoreCell[i] && !_isFixed[i])
	{
	  double cellWidth=0;
	  double cellHeight=0;
	  Orient nodeOrient = _placement.getOrient(i);
          if(nodeOrient == Orient("N") || nodeOrient == Orient("S") ||
             nodeOrient == Orient("FN") || nodeOrient == Orient("FS"))
            {
              cellWidth=_hgWDims->getNodeWidth(i);
              cellHeight=_hgWDims->getNodeHeight(i)*0.9;
            }
          else
            {
              cellWidth=_hgWDims->getNodeHeight(i);
              cellHeight=_hgWDims->getNodeWidth(i)*0.9;
            }

	  if(_placement[i].x < layout.xMin || 
	     (_placement[i].x + cellWidth) > layout.xMax ||
	     _placement[i].y < layout.yMin || 
	     (_placement[i].y + cellHeight) > layout.yMax)
	    {
	      consistent = false;
	      if(cellHeight > rowHeight)
		cout<<"Macro ";
	      else
		cout<<"Cell ";
	      cout<<_hgWDims->getNodeByIdx(i).getName()<<" ("
		  <<_placement[i].x<<" "<<_placement[i].y<<"->"
		  <<_placement[i].x+cellWidth<<" "<<_placement[i].y+cellHeight
		  <<")"<<" out of core "<<layout;
	    }
	}
    }
  return consistent;
}


double RBPlacement::calcOverlapGeneric(bool onlyMacros)
{
  const double P = 1.0;
  double overlap = 0;
  double rowHeight = coreRowsBegin()->getHeight();
  unsigned numNodes = getNumCells() - _hgWDims->getNumTerminals();
  unsigned numGridRows = unsigned(sqrt(numNodes/P));
  unsigned numGridCol = numGridRows;
  
  BBox layout = getBBox(false);
  double gridXSize = layout.getWidth()/numGridCol;
  double gridYSize = layout.getHeight()/numGridRows;

  vector< vector< vector<unsigned> > > grid(numGridRows);
  for(unsigned i=0; i<numGridRows; ++i)
    grid[i].resize(numGridCol);

  for(unsigned i=0; i<getNumCells(); i++)
    {
      if(_isCoreCell[i])
	{
	  if(onlyMacros)
	    {
	      //if(!_hgWDims->isNodeMacro(i))
	      if(_hgWDims->getNodeHeight(i) <= rowHeight)
		continue;
	    }

	  BBox cell;
          cell += _placement[i];
	  Orient nodeOrient = _placement.getOrient(i);
	  double cellWidth;
	  double cellHeight;
	  if(nodeOrient == Orient("N") || nodeOrient == Orient("S") ||
             nodeOrient == Orient("FN") || nodeOrient == Orient("FS"))
            {
              cellWidth=_hgWDims->getNodeWidth(i);
              cellHeight=_hgWDims->getNodeHeight(i);
            }
          else
            {
              cellWidth=_hgWDims->getNodeHeight(i);
              cellHeight=_hgWDims->getNodeWidth(i);
            }

          cell.add(_placement[i].x+cellWidth, _placement[i].y+cellHeight);
	  unsigned startGridCol = unsigned(floor((cell.xMin - layout.xMin)/gridXSize));
	  unsigned startGridRow = unsigned(floor((cell.yMin - layout.yMin)/gridYSize));
	  unsigned endGridCol = unsigned(ceil((cell.xMax - layout.xMin)/gridXSize));
          unsigned endGridRow = unsigned(ceil((cell.yMax - layout.yMin)/gridYSize));
	  if(startGridRow < 0)
	    startGridRow = 0;
	  if(startGridRow >= numGridRows)
	    startGridRow = numGridRows-1;
          if(endGridRow < 0)
            endGridRow = 0;
          if(endGridRow > numGridRows)
            endGridRow = numGridRows;
          if(startGridCol < 0)
            startGridCol = 0;
          if(startGridCol >= numGridCol)
            startGridCol = numGridCol-1;
          if(endGridCol < 0)
            endGridCol = 0;
          if(endGridCol > numGridCol)
            endGridCol = numGridCol;

	  for(unsigned rIdx = startGridRow; rIdx < endGridRow; ++rIdx)
	    for(unsigned cIdx = startGridCol; cIdx < endGridCol; ++cIdx)
	      grid[rIdx][cIdx].push_back(i);
	}
    }

  for(unsigned i=0; i<getNumCells(); i++)
    {
      if(_isCoreCell[i])
	{
	  if(onlyMacros)
	    {
	      //if(!_hgWDims->isNodeMacro(i))
	      if(_hgWDims->getNodeHeight(i) <= rowHeight)
		continue;
	    }

          BBox cell;
          cell += _placement[i];
	  Orient nodeOrient = _placement.getOrient(i);
	  double cellWidth;
	  double cellHeight;
	  if(nodeOrient == Orient("N") || nodeOrient == Orient("S") ||
             nodeOrient == Orient("FN") || nodeOrient == Orient("FS"))
            {
              cellWidth=_hgWDims->getNodeWidth(i);
              cellHeight=_hgWDims->getNodeHeight(i);
            }
          else
            {
              cellWidth=_hgWDims->getNodeHeight(i);
              cellHeight=_hgWDims->getNodeWidth(i);
            }

          cell.add(_placement[i].x+cellWidth, _placement[i].y+cellHeight);

          unsigned startGridCol = unsigned(floor((cell.xMin - layout.xMin)/gridXSize));
          unsigned startGridRow = unsigned(floor((cell.yMin - layout.yMin)/gridYSize));
          unsigned endGridCol = unsigned(ceil((cell.xMax - layout.xMin)/gridXSize));
          unsigned endGridRow = unsigned(ceil((cell.yMax - layout.yMin)/gridYSize));	  
          if(startGridRow < 0)
            startGridRow = 0;
          if(startGridRow >= numGridRows)
            startGridRow = numGridRows-1;
          if(endGridRow < 0)
            endGridRow = 0;
          if(endGridRow > numGridRows)
            endGridRow = numGridRows;
          if(startGridCol < 0)
            startGridCol = 0;
          if(startGridCol >= numGridCol)
            startGridCol = numGridCol-1;
          if(endGridCol < 0)
            endGridCol = 0;
          if(endGridCol > numGridCol)
            endGridCol = numGridCol;

	  vector<unsigned> seenNodes; 
	  for(unsigned rIdx = startGridRow; rIdx < endGridRow; ++rIdx)
	    {
	      for(unsigned cIdx = startGridCol; cIdx < endGridCol; ++cIdx)
		{
		  for(unsigned idx=0; idx<grid[rIdx][cIdx].size();++idx)
		    {
		      unsigned j=grid[rIdx][cIdx][idx];
		      if(i!=j)
			{
			  bool needThis=true;
			  for(unsigned k=0; k<seenNodes.size(); ++k)
			    {
			      if(j==seenNodes[k])
				{
				  needThis = false;
				  break;
				}
			    }
			  if(needThis)
			    {
			      seenNodes.push_back(j);
			      BBox cell2;
			      Orient nodeOrient2 = _placement.getOrient(j);
			      cell2 += _placement[j];
			      double cellWidth2;
			      double cellHeight2;
			      if(nodeOrient2 == Orient("N") || 
				 nodeOrient2 == Orient("S") ||
				 nodeOrient2 == Orient("FN") || 
				 nodeOrient2 == Orient("FS"))
				{
				  cellWidth2=_hgWDims->getNodeWidth(j);
				  cellHeight2=_hgWDims->getNodeHeight(j);
				}
			      else
				{
				  cellWidth2=_hgWDims->getNodeHeight(j);
				  cellHeight2=_hgWDims->getNodeWidth(j);
				}
			      
			      cell2.add(_placement[j].x+cellWidth2, 
					_placement[j].y+cellHeight2);

			      BBox intersection = cell.intersect(cell2);
			      overlap += intersection.getArea()/2.0;
			      
			      /*
			      if(intersection.getArea() > 0)
				{
				  cout<<_hgWDims->getNodeByIdx(i).getName()<<" "<<_hgWDims->getNodeByIdx(j).getName()<<" "<<intersection.getArea()<<endl;
				}
			      */
			    }
			}
		    }
		}
	    }
	}
    }
  double percentOverlap = 100.0*overlap/layout.getArea();
  if(!onlyMacros)
    cout<<"Total Overlap is "<<overlap<<" OR "<<percentOverlap<<" % of layout Area"<<endl;
  else
    cout<<"Total Macro Overlap is "<<overlap<<" OR "<<percentOverlap<<" % of layout Area"<<endl;

  /*
  overlap=0;
  for(unsigned i=0; i<getNumCells(); i++)
    {
      if(_isCoreCell[i])
	{
	  BBox cell1;
	  cell1 += _placement[i];
	  cell1.add(_placement[i].x+_hgWDims->getNodeWidth(i), 
		    _placement[i].y+_hgWDims->getNodeHeight(i));
	  for(unsigned j=0; j<getNumCells(); j++)
	    {
	      if(_isCoreCell[j] && i!=j)
		{
		  BBox cell2;
		  cell2 += _placement[j];
		  cell2.add(_placement[j].x+_hgWDims->getNodeWidth(j),
			    _placement[j].y+_hgWDims->getNodeHeight(j));
		  BBox intersection = cell1.intersect(cell2);
		  overlap += intersection.getArea()/2.0;
		}
	    }
	}
    }
  cout<<"Total Overlap is "<<overlap<<endl;
  */
  return(overlap);
}

// added by MRG to calculate total linear overlap 
double RBPlacement::calcOverlap()
{
  itRBPCoreRow itc;
  itRBPSubRow its;
  itRBPCellIds itn;
  itRBPCellIds itntemp;

  unsigned numOverlaps=0;
  unsigned totalOverlaps=0;
  double xDiff=0;
  double totalOverlapLength=0;

  //for each core row, for each subrow scan left to right if overlap found 
  //then take action
  for(itc=_coreRows.begin();itc!=_coreRows.end();++itc)
    {
      for(its=itc->subRowsBegin();its!=itc->subRowsEnd();++its)
	{
	  for(itn=its->cellIdsBegin();itn!=its->cellIdsEnd();++itn)
	    {
	      //check for overlaps in the same row
	      xDiff=1;
	      if(itn!=its->cellIdsEnd()-1)
		{
		  itntemp=itn+1;
		  if(_placement[*itntemp].x < 
		     _placement[*itn].x+_hgWDims->getNodeWidth(*itn))
		    {
		      //overlap found, now deal with it
		      numOverlaps++;
		      totalOverlaps++;
		      
		      xDiff= _placement[*itn].x + 
			_hgWDims->getNodeWidth(*itn)-_placement[*itntemp].x;
		      totalOverlapLength+=(xDiff*itc->getHeight());
		    }
		}
	    }
	}
    }
  return(totalOverlapLength);
}

// added by MRG to incrementally calculate total linear overlap
double RBPlacement::calcInstOverlap(vector<unsigned>& movables)
{
  double xDiff=0;
  double totalOverlapLength=0;
  itRBPCellIds itn;
  for(unsigned i=0;i<movables.size();i++)
    {
      abkassert(_isInSubRow[movables[i]], 
		"Requested cellCoord for cell not in a row");
      
      RBCellCoord& coord = _cellCoords[movables[i]];
      RBPSubRow& sr = _coreRows[coord.coreRowId][coord.subRowId];
      RBPCoreRow& cr = _coreRows[coord.coreRowId];
      double rowHeight = cr.getHeight();
      double myLeftEdge = _placement[movables[i]].x;
      double myRightEdge = _placement[movables[i]].x +
	_hgWDims->getNodeWidth(movables[i]);
      for(itn=sr.cellIdsBegin();itn!=sr.cellIdsEnd();++itn)
	{
	  double theirLeftEdge = _placement[*itn].x;
	  double theirRightEdge = _placement[*itn].x + 
	    _hgWDims->getNodeWidth(*itn);

	  // we're done when we've past the right of our cell
	  if (theirLeftEdge > myRightEdge)
	    break;
	  if (movables[i]==*itn)
	    continue;
	  
	  // i'm contained within another
	  if((myLeftEdge >= theirLeftEdge) && (myRightEdge <= theirRightEdge))
	    {
	      totalOverlapLength += 
		_hgWDims->getNodeWidth(movables[i])*rowHeight;
	    }
	  // another is contained within me	
	  else if((myLeftEdge <= theirLeftEdge) && 
		  (myRightEdge >= theirRightEdge))
	    {
	      totalOverlapLength += 
		_hgWDims->getNodeWidth(*itn)*rowHeight;
	    }
	  // left side overlap
	  else if((myLeftEdge > theirLeftEdge) && 
		  (myLeftEdge < theirRightEdge))
	    {
	      xDiff= theirRightEdge-myLeftEdge;
	      totalOverlapLength+=(xDiff*rowHeight);
	    }
	  // right side overlap
	  else if((myRightEdge > theirLeftEdge) && 
		  (myRightEdge < theirRightEdge))
	    {
	      xDiff= myRightEdge-theirLeftEdge;
	      totalOverlapLength+=(xDiff*rowHeight);
	    }
	}
    }
  return(totalOverlapLength);
}


bool RBPlacement::findClosestWS(Point& loc, Point& WSLoc, double width)
{
  RBRowPtrs rowPtrs = findBothRows(loc);
  RBPSubRow* its = const_cast<RBPSubRow*>(rowPtrs.second);
  if(rowPtrs.second == NULL) return false;

  itRBPCellIds itn;
  itRBPCellIds itntemp;
  itRBPCellIds itnleft;
  itRBPCellIds itnright;

  bool leftRight=false;   //false means move left else move right
  double WS=0;
  double xDiff=0;  

  itn=its->cellIdsBegin();
  if(itn == its->cellIdsEnd()) //no cells in subrow
    {
      return(true);
    }
  for(itn=its->cellIdsBegin();itn!=(its->cellIdsEnd()-1);++itn)
    {
      xDiff=1;
      itntemp=itn+1;
      if(_placement[*itn].x <= loc.x && _placement[*itntemp].x >= loc.x)
	break;
    }
  if(itn != (its->cellIdsEnd()-1))
    xDiff = _placement[*itntemp].x - 
      (_placement[*itn].x + _hgWDims->getNodeWidth(*itn));
  else 
    xDiff = its->getXEnd() - 
      (_placement[*itn].x + _hgWDims->getNodeWidth(*itn));

  if(xDiff >= width)
    {
      WSLoc.x = _placement[*itn].x + _hgWDims->getNodeWidth(*itn);
      return(true);
    }

  //closest node found, now try to find WS
      
  itnleft=itn;
  itnright=itn;
  leftRight=false;
      
  while((itnleft!=(its->cellIdsBegin()) || 
	 itnright!=(its->cellIdsEnd()-1)))
    {
      // chose the direction of search
      if(leftRight==false && itnright!=its->cellIdsEnd()-1)
	leftRight=true;
      else if(leftRight==true && itnleft!=its->cellIdsBegin())
	leftRight=false;
      
      if(leftRight==true)//search right for WS
	{
	  itntemp=itnright+1;
	  WS=_placement[*itntemp].x -
	    _placement[*itnright].x -
	    _hgWDims->getNodeWidth(*itnright);
	  if(WS >= width) //WS found
	    {
	      WSLoc.x = _placement[*itnright].x + 
		_hgWDims->getNodeWidth(*itnright);
	      return(true);
	    }
	  ++itnright;
	}
      else //search left for WS
	{
	  itntemp=itnleft-1;
	  WS=_placement[*itnleft].x -
	    _placement[*itntemp].x -
	    _hgWDims->getNodeWidth(*itntemp);
	  if(WS >= width) //WS found
	    {
	      WSLoc.x =  _placement[*itnleft].x - width;
	      return(true);
	    }
	  --itnleft;
	}
    }
  return(false);
}

double RBPlacement::CalcSwapCost(const unsigned &cell1, const Point &cell1NewPos,
                                 const bool skipLargeNets) const
{
  bool contains1, endearly;
  BBox temp, beforetemp, aftertemp, c1cur, c1new, pinOffset;
  double diff = 0.;
  itHGFNodeLocal c;
  itHGFEdgeLocal e;
  const Orient &cell1O = getOrient(cell1);
  unsigned netoffset = 0, offset = 0;
  const unsigned maxNetDegree = 32;

  const HGFNode& node1 = _hgWDims->getNodeByIdx(cell1);
  for(e = node1.edgesBegin(); e != node1.edgesEnd(); ++e, ++netoffset)
  {
     if((*e)->getDegree() > 1 && (!skipLargeNets || (*e)->getDegree() <= maxNetDegree))
     {
       const unsigned &n = (*e)->getIndex();
       endearly = false;
       c1cur = c1new = _hgWDims->edgesOnNodePinOffsetBBox(netoffset,cell1,cell1O);
       c1cur.TranslateBy(_placement[cell1]);
       c1new.TranslateBy(cell1NewPos);
       const HGFEdge& edge = _hgWDims->getEdgeByIdx(n);
       temp.clear();
       offset = 0;
       for(c = edge.nodesBegin(); c != edge.nodesEnd(); ++c, ++offset)
       {
          if((*c)->getIndex() != cell1) {
            pinOffset = _hgWDims->nodesOnEdgePinOffsetBBox(offset,n,getOrient((*c)->getIndex()));
            pinOffset.TranslateBy(_placement[(*c)->getIndex()]);
            temp.expandToInclude(pinOffset);
            contains1 = temp.contains(c1cur) && temp.contains(c1new);
            if(contains1) { endearly = true; break; }
          }
       }
       if(endearly) continue;
       beforetemp = aftertemp = temp;
       beforetemp.expandToInclude(c1cur);
       aftertemp.expandToInclude(c1new);
       diff += (*e)->getWeight()*(aftertemp.getHalfPerim()-beforetemp.getHalfPerim());
    }
  }

  return diff;
}

double RBPlacement::CalcSwapCost(const unsigned &cell1, const unsigned &cell2,
                                 const Point &cell1NewPos, const Point &cell2NewPos,
                                 const bool skipLargeNets) const
{
  vector<unsigned> thenets;
  hash_map<unsigned,unsigned,hash<unsigned>,equal_to<unsigned> > c1offsets, c2offsets;
  const unsigned maxNetDegree = 32;

  const HGFNode& node1 = _hgWDims->getNodeByIdx(cell1);
  unsigned offset = 0;
  for(itHGFEdgeLocal e = node1.edgesBegin(); e != node1.edgesEnd(); ++e, ++offset) {
     if((*e)->getDegree() > 1 && (!skipLargeNets || (*e)->getDegree() <= maxNetDegree)) {
       thenets.push_back((*e)->getIndex());
       c1offsets[(*e)->getIndex()] = offset;
     }
  }
  offset = 0;
  const HGFNode& node2 = _hgWDims->getNodeByIdx(cell2);
  for(itHGFEdgeLocal e = node2.edgesBegin(); e != node2.edgesEnd(); ++e, ++offset) {
     if((*e)->getDegree() > 1 && (!skipLargeNets || (*e)->getDegree() <= maxNetDegree)) {
       thenets.push_back((*e)->getIndex());
       c2offsets[(*e)->getIndex()] = offset;
     }
  }

  sort(thenets.begin(),thenets.end());
  thenets.erase(unique(thenets.begin(),thenets.end()),thenets.end());

  bool has1, has2, contains1, contains2, endearly;
  BBox temp, beforetemp, aftertemp;
  BBox c1cur, c1new, c2cur, c2new, pinOffset;
  double diff = 0.;
  itHGFNodeLocal c;
  const Orient &cell1O = getOrient(cell1);
  const Orient &cell2O = getOrient(cell2);

  for(vector<unsigned>::iterator n = thenets.begin(); n != thenets.end(); ++n) {
     has1 = has2 = endearly = false;
     if(c1offsets.find(*n) != c1offsets.end()) {
       has1 = true;
       c1cur = c1new = _hgWDims->edgesOnNodePinOffsetBBox(c1offsets[*n],cell1,cell1O);
       c1cur.TranslateBy(_placement[cell1]);
       c1new.TranslateBy(cell1NewPos);
     }
     if(c2offsets.find(*n) != c2offsets.end()) {
       has2 = true;
       c2cur = c2new = _hgWDims->edgesOnNodePinOffsetBBox(c2offsets[*n],cell2,cell2O);
       c2cur.TranslateBy(_placement[cell2]);
       c2new.TranslateBy(cell2NewPos);
     }
     const HGFEdge& edge = _hgWDims->getEdgeByIdx(*n);
     temp.clear();
     contains1 = !has1; contains2 = !has2;
     offset = 0;
     for(c = edge.nodesBegin(); c != edge.nodesEnd(); ++c, ++offset) {
        if((*c)->getIndex() != cell1 && (*c)->getIndex() != cell2) {
          pinOffset = _hgWDims->nodesOnEdgePinOffsetBBox(offset,*n,getOrient((*c)->getIndex()));
          pinOffset.TranslateBy(_placement[(*c)->getIndex()]);
          temp.expandToInclude(pinOffset);
          contains1 = contains1 || (temp.contains(c1cur) && temp.contains(c1new));
          contains2 = contains2 || (temp.contains(c2cur) && temp.contains(c2new));
          if(contains1 && contains2) { endearly = true; break; }
        }
     }
     if(endearly) continue;
     beforetemp = aftertemp = temp;
     if(has1) { beforetemp.expandToInclude(c1cur); aftertemp.expandToInclude(c1new); }
     if(has2) { beforetemp.expandToInclude(c2cur); aftertemp.expandToInclude(c2new); }
     diff += edge.getWeight()*(aftertemp.getHalfPerim()-beforetemp.getHalfPerim());
  }

  return diff;
}

double RBPlacement::CalcSwapCost(const unsigned &cell1, const unsigned &cell2, const unsigned &cell3,
                                 const Point &cell1NewPos, const Point &cell2NewPos,
                                 const Point &cell3NewPos, const bool skipLargeNets) const
{
  vector<unsigned> thenets;
  hash_map<unsigned,unsigned,hash<unsigned>,equal_to<unsigned> > c1offsets, c2offsets, c3offsets;
  const unsigned maxNetDegree = 32;

  const HGFNode& node1 = _hgWDims->getNodeByIdx(cell1);
  unsigned offset = 0;
  for(itHGFEdgeLocal e = node1.edgesBegin(); e != node1.edgesEnd(); ++e, ++offset) {
     if((*e)->getDegree() > 1 && (!skipLargeNets || (*e)->getDegree() <= maxNetDegree)) {
       thenets.push_back((*e)->getIndex());
       c1offsets[(*e)->getIndex()] = offset;
     }
  }
  offset = 0;
  const HGFNode& node2 = _hgWDims->getNodeByIdx(cell2);
  for(itHGFEdgeLocal e = node2.edgesBegin(); e != node2.edgesEnd(); ++e, ++offset) {
     if((*e)->getDegree() > 1 && (!skipLargeNets || (*e)->getDegree() <= maxNetDegree)) {
       thenets.push_back((*e)->getIndex());
       c2offsets[(*e)->getIndex()] = offset;
     }
  }
  offset = 0;
  const HGFNode& node3 = _hgWDims->getNodeByIdx(cell3);
  for(itHGFEdgeLocal e = node3.edgesBegin(); e != node3.edgesEnd(); ++e, ++offset) {
     if((*e)->getDegree() > 1 && (!skipLargeNets || (*e)->getDegree() <= maxNetDegree)) {
       thenets.push_back((*e)->getIndex());
       c3offsets[(*e)->getIndex()] = offset;
     }
  }

  sort(thenets.begin(),thenets.end());
  thenets.erase(unique(thenets.begin(),thenets.end()),thenets.end());

  bool has1, has2, has3, contains1, contains2, contains3, endearly;
  BBox temp, beforetemp, aftertemp;
  BBox c1cur, c1new, c2cur, c2new, c3cur, c3new, pinOffset;
  double diff = 0.;
  itHGFNodeLocal c;
  const Orient &cell1O = getOrient(cell1);
  const Orient &cell2O = getOrient(cell2);
  const Orient &cell3O = getOrient(cell3);

  for(vector<unsigned>::iterator n = thenets.begin(); n != thenets.end(); ++n) {
     has1 = has2 = has3 = endearly = false;
     if(c1offsets.find(*n) != c1offsets.end()) {
       has1 = true;
       c1cur = c1new = _hgWDims->edgesOnNodePinOffsetBBox(c1offsets[*n],cell1,cell1O);
       c1cur.TranslateBy(_placement[cell1]);
       c1new.TranslateBy(cell1NewPos);
     }
     if(c2offsets.find(*n) != c2offsets.end()) {
       has2 = true;
       c2cur = c2new = _hgWDims->edgesOnNodePinOffsetBBox(c2offsets[*n],cell2,cell2O);
       c2cur.TranslateBy(_placement[cell2]);
       c2new.TranslateBy(cell2NewPos);
     }
     if(c3offsets.find(*n) != c3offsets.end()) {
       has3 = true;
       c3cur = c3new = _hgWDims->edgesOnNodePinOffsetBBox(c3offsets[*n],cell3,cell3O);
       c3cur.TranslateBy(_placement[cell3]);
       c3new.TranslateBy(cell3NewPos);
     }
     const HGFEdge& edge = _hgWDims->getEdgeByIdx(*n);
     temp.clear();
     contains1 = !has1; contains2 = !has2; contains3 = !has3;
     offset = 0;
     for(c = edge.nodesBegin(); c != edge.nodesEnd(); ++c, ++offset) {
        if((*c)->getIndex() != cell1 && (*c)->getIndex() != cell2 && (*c)->getIndex() != cell3) {
          pinOffset = _hgWDims->nodesOnEdgePinOffsetBBox(offset,*n,getOrient((*c)->getIndex()));
          pinOffset.TranslateBy(_placement[(*c)->getIndex()]);
          temp.expandToInclude(pinOffset);
          contains1 = contains1 || (temp.contains(c1cur) && temp.contains(c1new));
          contains2 = contains2 || (temp.contains(c2cur) && temp.contains(c2new));
          contains3 = contains3 || (temp.contains(c3cur) && temp.contains(c3new));
          if(contains1 && contains2 && contains3) { endearly = true; break; }
        }
     }
     if(endearly) continue;
     beforetemp = aftertemp = temp;
     if(has1) { beforetemp.expandToInclude(c1cur); aftertemp.expandToInclude(c1new); }
     if(has2) { beforetemp.expandToInclude(c2cur); aftertemp.expandToInclude(c2new); }
     if(has3) { beforetemp.expandToInclude(c3cur); aftertemp.expandToInclude(c3new); }
     diff += edge.getWeight()*(aftertemp.getHalfPerim()-beforetemp.getHalfPerim());
  }

  return diff;
}

double RBPlacement::calcSwapCost(const unsigned &cell1, unsigned cell2, unsigned cell3,
                                 const Point &cell1NewPos, const Point &cell2NewPos,
                                 const Point &cell3NewPos, const bool skipLargeNets) const
{

  if(cell2 == UINT_MAX) return CalcSwapCost(cell1, cell1NewPos, skipLargeNets);
  else if(cell3 == UINT_MAX) return CalcSwapCost(cell1, cell2, cell1NewPos, cell2NewPos, skipLargeNets);
  else return CalcSwapCost(cell1, cell2, cell3, cell1NewPos, cell2NewPos, cell3NewPos, skipLargeNets);
}

double RBPlacement::calcSwapCost(const itRBPSubRow &sr1, unsigned sr1Cell, Point &sr1CellPos,
                                 const itRBPSubRow &sr2, unsigned sr2Cell, Point &sr2CellPos) const
{
  sr1CellPos.x = _placement[sr1Cell].x;
  sr1CellPos.y = sr2->getYCoord();
  if(sr1CellPos.x > (sr2->getXEnd()-_hgWDims->getNodeWidth(sr1Cell)))
    sr1CellPos.x = sr2->getXEnd()-_hgWDims->getNodeWidth(sr1Cell);
  if(sr1CellPos.x < sr2->getXStart())
    sr1CellPos.x = sr2->getXStart();

  if(sr2Cell != UINT_MAX) {
    sr2CellPos.x = _placement[sr2Cell].x;
    sr2CellPos.y = sr1->getYCoord();   
    if(sr2CellPos.x > (sr1->getXEnd()-_hgWDims->getNodeWidth(sr2Cell)))
      sr2CellPos.x = sr1->getXEnd()-_hgWDims->getNodeWidth(sr2Cell);
    if(sr2CellPos.x < sr1->getXStart())
      sr2CellPos.x = sr1->getXStart();
  }

  if(sr2Cell == UINT_MAX) return CalcSwapCost(sr1Cell,sr1CellPos,true);
  else return CalcSwapCost(sr1Cell,sr2Cell,sr1CellPos,sr2CellPos,true);
}

inline double rectPointDist(const Point &p1, const Point &p2)
{
  return fabs(p1.x - p2.x) + fabs(p1.y - p2.y);
}

double distToSR(const itRBPSubRow &its, const Point &pt)
{
  if(pt.x > its->getXEnd()) {
    return (pt.x-its->getXEnd())+fabs(pt.y-its->getYCoord());
  }
  else if(pt.x < its->getXStart()) {
    return (its->getXStart()-pt.x)+fabs(pt.y-its->getYCoord());
  }
  else {
    return fabs(pt.y-its->getYCoord());
  }
}

unsigned RBPlacement::findBestSwap(const vector<unsigned> &ordering,
                      const vector<pair<itRBPSubRow,double> > &haveSpace,
                      const itRBPSubRow &sourceRow, unsigned sourceCell, Point &newSourcePos,
                      unsigned &swapCell, Point &newSwapPos, double &bestImprovement, double &bestCost,
                      const double &distCutOff)
{
  const double lenNeeded = _hgWDims->getNodeWidth(sourceCell);
  double lenTarget, cost, improvement, dist;
  Point sourcePos, swapPos;
  unsigned bestSR = UINT_MAX;
  itRBPCellIds c;
  bestImprovement = -DBL_MAX;
  bestCost = DBL_MAX;

  // examine in the order of decreasing available space
  for(unsigned i = 0; i < ordering.size(); ++i)
  {
    const unsigned &rIdx = ordering[i];
    if(haveSpace[rIdx].second < 1.e-6) break; // since available space will only get smaller
    if(distCutOff != DBL_MAX)
    {
      dist = distToSR(haveSpace[rIdx].first,_placement[sourceCell]);
      if(dist > distCutOff) continue;
    }
    if(lenNeeded > haveSpace[rIdx].second) {
      if(haveSpace[rIdx].second < bestImprovement) break; // since available space will only get smaller
      lenTarget = lenNeeded - haveSpace[rIdx].second;
      if(lenTarget >= lenNeeded) continue;
      for(c = haveSpace[rIdx].first->cellIdsBegin(); c != haveSpace[rIdx].first->cellIdsEnd(); ++c) {
        const double &curLen = _hgWDims->getNodeWidth(*c);
        if(curLen < lenTarget || curLen >= lenNeeded) continue;
        improvement = lenNeeded - curLen;
        if(improvement < bestImprovement) continue;
        cost = calcSwapCost(sourceRow, sourceCell, sourcePos, haveSpace[rIdx].first, *c, swapPos);
        if(improvement == bestImprovement && cost >= bestCost) continue;
        bestImprovement = improvement;
        bestCost = cost;
        bestSR = rIdx;
        swapCell = *c;
        newSourcePos = sourcePos;
        newSwapPos = swapPos;
      }
    }
    else {
      improvement = lenNeeded;
      cost = calcSwapCost(sourceRow, sourceCell, sourcePos, haveSpace[rIdx].first, UINT_MAX, swapPos);
      if(improvement == bestImprovement && cost >= bestCost) continue;
      bestImprovement = improvement;
      bestCost = cost;
      bestSR = rIdx;
      swapCell = UINT_MAX;
      newSourcePos = sourcePos;
      newSwapPos = swapPos;
    }
  }
  return bestSR;
}

void RBPlacement::swapCells(RBPSubRow *sr1, unsigned sr1Cell, const Point &sr1CellPos,
                            RBPSubRow *sr2, unsigned sr2Cell, const Point &sr2CellPos)
{
//  sr1->removeCell(sr1Cell);
//  _placement[sr1Cell] = sr1CellPos;
//  sr2->addCell(sr1Cell);
  setLocation(sr1Cell,sr1CellPos);

  if(sr2Cell != UINT_MAX) {
//    sr2->removeCell(sr2Cell); 
//    _placement[sr2Cell] = sr2CellPos;
//    sr1->addCell(sr2Cell);
    setLocation(sr2Cell,sr2CellPos);
  }
}



void RBPlacement::royjRemOverlaps()
{
  //if (_params.verb.getForActions()) 
  cout << " Running overlap removal ..." << endl;

  Timer tm;

  double startWL = 0.;
  //if (_params.verb.getForMajStats()) {
      startWL = evalHPWL(true);
      cout << "  HPWL before overlap remover is " << startWL << endl;
  //}

  itRBPCoreRow itc;
  itRBPSubRow  its;

  //find any cells not in a row and put them in the closest one
  double dist, bestDist;
  Point newPos, bestNewPos;
  unsigned oormoves = 0;
  for(unsigned i=0; i<getNumCells(); i++)
  {
    if(_isCoreCell[i] && !_isFixed[i] && !_hgWDims->isNodeMacro(i))
    {
      if(_isInSubRow[i]) continue;
      
      bestDist = DBL_MAX;
      for(itc = _coreRows.begin(); itc != _coreRows.end(); ++itc)
      {
        for(its = itc->subRowsBegin(); its != itc->subRowsEnd(); ++its)
        {
          newPos.x = _placement[i].x;
          newPos.y = its->getYCoord();
          if(newPos.x > (its->getXEnd()-_hgWDims->getNodeWidth(i)))
            newPos.x = its->getXEnd()-_hgWDims->getNodeWidth(i);
          if(newPos.x < its->getXStart())
            newPos.x = its->getXStart();         

          dist = rectPointDist(_placement[i], newPos);
          if(dist >= bestDist) continue;
          bestDist = dist;
          bestNewPos = newPos;
        }
      }

      if(bestDist == DBL_MAX) continue; // this should not happen, but necessary for safety
      
      setLocation(i,bestNewPos);
      ++oormoves;
    }
  }

  //if (_params.verb.getForMajStats() > 1) {
      cout << "  Number of out of row moves " << oormoves << endl;
      cout << "  HPWL after moving cells to rows is " << evalHPWL(true) << endl;
  //}

  unsigned initOverlaps = 0, moves = 0;
  //if (_params.verb.getForMajStats()) 
	  initOverlaps = getNumOverlaps();

  //if (_params.verb.getForMajStats() > 1) {
      cout << "  Number of row overlaps " << initOverlaps << endl;
  //}

  vector<pair<itRBPSubRow,double> > haveSpace, needSpace;
  vector<pair<itRBPSubRow,double> >::iterator r;
  vector<unsigned> ordering(0);
  double totalCellLen, surplus;
  itRBPCellIds c;
  double sitewidth = (_coreRows.size() > 0) ? _coreRows[0].getSiteWidth() : 1.e-6;
  for(itc = _coreRows.begin(); itc != _coreRows.end(); ++itc)
  {
    for(its = itc->subRowsBegin(); its != itc->subRowsEnd(); ++its)
    {
      totalCellLen = 0.;
      for(c = its->cellIdsBegin(); c != its->cellIdsEnd(); ++c) {
        totalCellLen += _hgWDims->getNodeWidth(*c);
      }
      surplus = its->getLength() - totalCellLen;
      if(surplus >= 0.) {
        shuffleSR(its);
        if(surplus >= sitewidth) {
          haveSpace.push_back(pair<itRBPSubRow,double>(its,surplus));
          ordering.push_back(ordering.size());
        }
      }
      else if(surplus < -1.e-6)
        needSpace.push_back(pair<itRBPSubRow,double>(its,-surplus));
    }
  }

  resetPlacement();

  unsigned initoverfull = needSpace.size();
  unsigned curoverfull = initoverfull;

  //if (_params.verb.getForMajStats() > 1) {
      cout << "  Number of overfull rows " << needSpace.size() << endl;
      cout << "  Number of underfull rows " << haveSpace.size() << endl;
  //}

  sort(ordering.begin(),ordering.end(),OrderBySpace(haveSpace));

  vector< vector<cellMoveData> > themoves(needSpace.size());
  vector< unsigned > rowbestmove(needSpace.size());
  unsigned overallbestmove = UINT_MAX, rIdx, SR, swapCell;
  double cost, bestCost, rowBestCost, improvement, bestImprovement, rowBestImprovement;
  Point newSwapPos;
  const unsigned numNodes = getNumCells() - _hgWDims->getNumTerminals();
  double distCutOff = DBL_MAX;
  if(numNodes >= _params.overlapCells)
  {
    distCutOff = sqrt(static_cast<double>(_params.overlapCells)*getBBox(false).getArea()/static_cast<double>(2*numNodes));
  }
  
  // figure out all the possible moves, as well as the best per row and best overall
  bestImprovement = -DBL_MAX;
  bestCost = DBL_MAX;
  unsigned possibleswaps = 0;
  for(rIdx = 0, r = needSpace.begin(); r != needSpace.end(); ++rIdx, ++r) {
    rowBestImprovement = -DBL_MAX;
    rowBestCost = DBL_MAX;
    rowbestmove[rIdx] = UINT_MAX;
    for(c = r->first->cellIdsBegin(); c != r->first->cellIdsEnd(); ++c) {
      SR = findBestSwap(ordering, haveSpace, r->first, *c, newPos, swapCell, newSwapPos, improvement, cost, distCutOff);
      if(SR == UINT_MAX) continue;
      abkassert(SR < haveSpace.size(),"bad dest row");
      themoves[rIdx].push_back(cellMoveData(rIdx, *c, newPos,
                                            SR, swapCell, newSwapPos, improvement, cost));
      ++possibleswaps;
      if(improvement < rowBestImprovement) continue;
      if(improvement == rowBestImprovement && cost >= rowBestCost) continue;
      rowbestmove[rIdx] = themoves[rIdx].size()-1;
      rowBestImprovement = improvement;
      rowBestCost = cost;
    }
    //if(_params.verb.getForMajStats() > 3) {
      //cout << "Finished finding swaps for overfull row " << rIdx+1 << endl;
      //cout << possibleswaps << " possible swaps so far" << endl;
    //}
    if(rowbestmove[rIdx] == UINT_MAX) continue;
    if(themoves[rIdx][rowbestmove[rIdx]].WLcost > bestCost) continue;
    if(themoves[rIdx][rowbestmove[rIdx]].WLcost == bestCost && themoves[rIdx][rowbestmove[rIdx]].improvement <= bestImprovement) continue;
    overallbestmove = rIdx;
    bestImprovement = themoves[rIdx][rowbestmove[rIdx]].improvement;
    bestCost = themoves[rIdx][rowbestmove[rIdx]].WLcost;
  }

  //if (_params.verb.getForMajStats() > 1) {
      cout << "  Number of possible swaps " << possibleswaps << endl;
      tm.split();
      cout << "  Determining possible swaps took " << tm << endl;
      tm.resume();
  //}

  //maxMem->update("Standard cell overlap remover");

  cellMoveData bestmove;
  while(overallbestmove != UINT_MAX) {
    bestmove.sourceSRIdx  = themoves[overallbestmove][rowbestmove[overallbestmove]].sourceSRIdx;
    bestmove.sourceCell   = themoves[overallbestmove][rowbestmove[overallbestmove]].sourceCell;
    bestmove.sourceNewPos = themoves[overallbestmove][rowbestmove[overallbestmove]].sourceNewPos;
    bestmove.destSRIdx    = themoves[overallbestmove][rowbestmove[overallbestmove]].destSRIdx;
    bestmove.destCell     = themoves[overallbestmove][rowbestmove[overallbestmove]].destCell;
    bestmove.destNewPos   = themoves[overallbestmove][rowbestmove[overallbestmove]].destNewPos;
    bestmove.improvement  = themoves[overallbestmove][rowbestmove[overallbestmove]].improvement;
    bestmove.WLcost       = themoves[overallbestmove][rowbestmove[overallbestmove]].WLcost;

    // make the swap and record it
    swapCells(const_cast<RBPSubRow*>(&(*needSpace[bestmove.sourceSRIdx].first)), bestmove.sourceCell, bestmove.sourceNewPos,
              const_cast<RBPSubRow*>(&(*haveSpace[bestmove.destSRIdx].first)), bestmove.destCell, bestmove.destNewPos);
    ++moves;
    
    // update the amount of space everything has now
    needSpace[bestmove.sourceSRIdx].second -= _hgWDims->getNodeWidth(bestmove.sourceCell);
    haveSpace[bestmove.destSRIdx].second -= _hgWDims->getNodeWidth(bestmove.sourceCell);
    if(bestmove.destCell != UINT_MAX) {
      needSpace[bestmove.sourceSRIdx].second += _hgWDims->getNodeWidth(bestmove.destCell);
      haveSpace[bestmove.destSRIdx].second += _hgWDims->getNodeWidth(bestmove.destCell);
    }
    sort(ordering.begin(),ordering.end(),OrderBySpace(haveSpace));
    
    unsigned updates = 0;
    if(needSpace[bestmove.sourceSRIdx].second < 1.e-6) {
      --curoverfull;
      // if the row has space now, put it on the haveSpace list
      if(needSpace[bestmove.sourceSRIdx].second <= -sitewidth) {
        haveSpace.push_back(pair<itRBPSubRow,double>(needSpace[bestmove.sourceSRIdx].first,-needSpace[bestmove.sourceSRIdx].second));
        ordering.push_back(ordering.size());
        sort(ordering.begin(),ordering.end(),OrderBySpace(haveSpace));
      }
      // get rid of all the moves for this row since its fixed
      themoves[overallbestmove].clear();
      // shuffle this row for better HPWL estimates
      shuffleSR(needSpace[bestmove.sourceSRIdx].first);
    }
    else {
      // erase the move we just made
      themoves[overallbestmove].erase(themoves[overallbestmove].begin()+rowbestmove[overallbestmove]);
      // add a new possible move for the cell we just added to this row, if we can 
      if(bestmove.destCell != UINT_MAX) {
        ++updates;
        SR = findBestSwap(ordering, haveSpace, needSpace[bestmove.sourceSRIdx].first, bestmove.destCell, newPos, swapCell, newSwapPos, improvement, cost, distCutOff);
        if(SR != UINT_MAX) themoves[overallbestmove].push_back(cellMoveData(bestmove.sourceSRIdx, bestmove.destCell, newPos,
                                                                            SR, swapCell, newSwapPos, improvement, cost));
      }
    }
    // signify that this rows best move need to be updated
    rowbestmove[overallbestmove] = UINT_MAX;
    // pick up a new best move and update other moves that may not be valid
    overallbestmove = UINT_MAX;
    bestImprovement = -DBL_MAX;
    bestCost = DBL_MAX;    
    for(unsigned i = 0; i < themoves.size(); ++i) {
      // check all the moves and see if they should be updated
      bool madeachange = false;
      for(unsigned j = 0; j < themoves[i].size(); ++j) {
        if(themoves[i][j].destSRIdx == bestmove.destSRIdx) {
          // do a quick check first
          double space = haveSpace[bestmove.destSRIdx].second - _hgWDims->getNodeWidth(themoves[i][j].sourceCell);
          if(themoves[i][j].destCell != UINT_MAX)
            space += _hgWDims->getNodeWidth(themoves[i][j].destCell);
          if(space >= 0.) continue;
          // curses! we need to update
          madeachange = true; ++updates;
          SR = findBestSwap(ordering, haveSpace, needSpace[themoves[i][j].sourceSRIdx].first, themoves[i][j].sourceCell,
                            newPos, swapCell, newSwapPos, improvement, cost, distCutOff);
          if(SR == UINT_MAX) {
            themoves[i].erase(themoves[i].begin()+j);
            --j;
          }
          else {
            themoves[i][j].sourceNewPos = newPos;
            themoves[i][j].destSRIdx = SR;
            themoves[i][j].destCell = swapCell;
            themoves[i][j].destNewPos = newSwapPos;
            themoves[i][j].improvement = improvement;
            themoves[i][j].WLcost = cost;
          }
        }
      }

      if(madeachange || rowbestmove[i] == UINT_MAX) {
        rowBestImprovement = -DBL_MAX;
        rowBestCost = DBL_MAX;
        rowbestmove[i] = UINT_MAX;
        for(unsigned j = 0; j < themoves[i].size(); ++j) {
          if(themoves[i][j].improvement < rowBestImprovement) continue;
          if(themoves[i][j].improvement == rowBestImprovement && themoves[i][j].WLcost >= rowBestCost) continue;
          rowbestmove[i] = j;
          rowBestImprovement = improvement;
          rowBestCost = cost;
        }
      }

      if(rowbestmove[i] == UINT_MAX) continue;
      if(themoves[i][rowbestmove[i]].WLcost > bestCost) continue;
      if(themoves[i][rowbestmove[i]].WLcost == bestCost && themoves[i][rowbestmove[i]].improvement <= bestImprovement) continue;
      overallbestmove = i;
      bestImprovement = themoves[i][rowbestmove[i]].improvement;
      bestCost = themoves[i][rowbestmove[i]].WLcost;
    }
    //if(_params.verb.getForMajStats() > 3) {
    //  cout << "Just made move " << moves << endl;
    //  cout << "  Space still needed by source row: " <<  needSpace[bestmove.sourceSRIdx].second << endl;
    //  cout << "  Overfull rows left: " << curoverfull << endl;
    //  cout << "  Updates needed: " << updates << endl;
    //}
  }
  
  //if (_params.verb.getForMajStats() > 1)
     cout << "  HPWL after cell movement is " << evalHPWL(true) << endl;

  // remove the overlaps from all the subrows, since they should have room now
  for(itc = _coreRows.begin(); itc != _coreRows.end(); ++itc)
    for(its = itc->subRowsBegin(); its != itc->subRowsEnd(); ++its)
      shuffleSR(its);

  resetPlacement();

  double endWL = 0.;
  unsigned overfullrows = 0, finalOverlaps = 0;
  //if (_params.verb.getForMajStats()) {
    endWL = evalHPWL(true);
    finalOverlaps = getNumOverlaps();
    for(r = needSpace.begin(); r != needSpace.end(); ++r)
      if(r->second > 1.e-6) ++overfullrows;
  //}

  //if (_params.verb.getForMajStats() > 1)
     cout << "  HPWL after shuffling is " << endWL << endl;

  tm.stop();

  //if (_params.verb.getForMajStats())
  //{
    cout<<" Removing overlaps took " << tm << endl;
    if(oormoves > 0)
      cout<<"  Out of row moves performed: "<<oormoves<<endl;
    if(initOverlaps > 0 || finalOverlaps > 0)
    {
      cout<<"  Discovered " << initOverlaps << " overlaps "<<endl;
      cout<<"  Overlaps remaining: "<<finalOverlaps<<endl;
    }
    if(initoverfull > 0 || overfullrows > 0)
    {
      cout<<"  Discovered " << initoverfull << " overfull subrows "<<endl;
      cout<<"  Overfull subrows remaining: "<<overfullrows<<endl;
      cout<<"  Overfull subrow moves performed: "<<moves<<endl;
    }
    if(endWL != startWL)
    {
      cout<<"  HPWL after overlap removal is "<<endWL<<endl;
      double change = (startWL == 0) ? 0 : (endWL-startWL)/startWL;
      if(change < 0) cout<<"  % decrease in HPWL is "<<floor(-change*100000+0.5)/1000<<endl;
      else cout<<"  % increase in HPWL is "<<floor(change*100000+0.5)/1000<<endl;
    }
  //}
}