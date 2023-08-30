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



#include "layoutGenerator.h"
#include "plotter.h"
#include "Legalization.h"

using std::ifstream;
using std::cout;
using std::endl;
using std::vector;

#ifdef _MSC_VER
#ifndef rint
#define rint(a) floor((a)+0.5)
#endif
#endif

/* bool nocase_compare (char c1, char c2)
{
    return toupper(c1) == toupper(c2);
}

void layoutGenerator::placeTerms(DB* db)
//place the terminals around the edge of the layout region.
{
    unsigned k,numNodes=db->getDesign().getNumNodes();
    Placement _placement(numNodes);	
    for(k=0; k < numNodes; k++) 
	  _placement[k] = Point(0,0);

    unsigned numRows=(*_db)._rowDefs->getRowCnt();
    myAssert(numRows," Zero core rows");
    unsigned numTerms = (*_db).getNetlist().getNumIOPads();
    if (numRows==1)
    {
        Orient  nOri("N");
		bool onLeft = true;
        for(k=0; k!=numTerms; k++)
        {
			std::string fotl = "Fixed__on__the__left";
			std::string fotr = "Fixed__on__the__right";
           if (getHGraph().getNodeNames()[k].size() == fotl.size() && equal(getHGraph().getNodeNames()[k].begin(),getHGraph().getNodeNames()[k].end(), fotl.begin(),nocase_compare) )
           {
              _placement[k]=Point(-1.0,0.0);
              _placement.setOrient(k, nOri);
           }
           else
           if (getHGraph().getNodeNames()[k].size() == fotl.size() && equal(getHGraph().getNodeNames()[k].begin(),getHGraph().getNodeNames()[k].end(), fotr.begin(), nocase_compare) )
           {
              _placement[k]=Point(numNodes-numTerms,0);
              _placement.setOrient(k, nOri);
           }
	       else
	       {
	         myWarn3(0,"In linear placement terms need to be fixed on left or right\n");
	         if(onLeft == true)
	           _placement[k]=Point(-1.0,0.0);
	         else
	           _placement[k]=Point(numNodes-numTerms,0);
	         _placement.setOrient(k, nOri);
	         onLeft = !onLeft;
	       }
        }
        return;
    }

	//first, find the BBox of the layout region.
    BBox layoutBBox;
    for(itRBPCoreRow cr = coreRowsBegin(); cr != coreRowsEnd(); cr++)
    {
	Point crOrigin(cr->subRowsBegin()->getXStart(), cr->getYCoord());
	Point crTopLeft(cr->_subRows.back().getXEnd(), 
			cr->getYCoord()+cr->getHeight());
	layoutBBox += crOrigin;
	layoutBBox += crTopLeft;
    }

    if(_params.verb.getForMajStats() > 4)
	cout<<"Layout BBox is: "<<layoutBBox<<endl;

    double layoutWidth = layoutBBox.getWidth();
    double layoutHeight= layoutBBox.getHeight();
    double layoutPerim = 2*layoutWidth + 2*layoutHeight;

    unsigned termsOnTop, termsOnBottom, termsOnLeft, termsOnRight;

    termsOnTop = termsOnBottom = 
	static_cast<unsigned>(rint(numTerms*(layoutWidth/layoutPerim)));

    termsOnLeft = numTerms - (termsOnTop+termsOnBottom);
    termsOnRight = static_cast<unsigned>(ceil(termsOnLeft/2.0));
    termsOnLeft -= termsOnRight;

    abkfatal(termsOnTop+termsOnBottom+termsOnLeft+termsOnRight == numTerms,
	"Mismatch in number of terminals.\n total != sum on each side");

    cout<<"Terminals: "<<numTerms<<endl;
    cout<<"  Top:     "<<termsOnTop<<endl;
    cout<<"  Bottom:  "<<termsOnBottom<<endl;
    cout<<"  Left:    "<<termsOnLeft<<endl;
    cout<<"  Right:   "<<termsOnRight<<endl;

	//note: uses the assumption that terminals are numbered
	//consecutively from 0
 
    Point    nextLoc;
    double   delta;
    double   crHeight   = coreRowsBegin()->getHeight(); 
	//assumes that all terminals have the same height & width
    double   termHeight = _hgWDims->getNodeHeight(0);
    double   termWidth  = _hgWDims->getNodeWidth(0);
    unsigned t;

    nextLoc = Point(floor(layoutBBox.xMin),ceil(layoutBBox.yMax + 2*crHeight));
    delta   = layoutWidth / termsOnTop;

    Orient  fsOri("FS");
    for(t = 0; t < termsOnTop; t++)
    {
        _placement.setOrient(t, fsOri);
	_placement[t] = nextLoc;
	_placement[t].x = rint(nextLoc.x);
	if(t && _placement[t].x < _placement[t-1].x+termWidth)
	{
	    _placement[t].x++;	//can't be off by more than one
	    nextLoc.x++;
	}

	nextLoc.x     += delta;
    }

    nextLoc = Point(floor(layoutBBox.xMin),
			floor(layoutBBox.yMin - 2*crHeight - termHeight));
    delta   = layoutWidth / termsOnBottom;
    Orient  nOri("N");
    for(;t < termsOnTop+termsOnBottom; t++)
    {
        _placement.setOrient(t, nOri);
	_placement[t] = nextLoc;
	_placement[t].x = rint(nextLoc.x);
	if(t!= termsOnTop && _placement[t].x < _placement[t-1].x+termWidth)
	{
	    _placement[t].x++;	//can't be off by more than one
	    nextLoc.x++;
	}

	nextLoc.x     += delta;
    }

    nextLoc = Point(floor(layoutBBox.xMin-2*crHeight-termWidth),
			floor(layoutBBox.yMin));
    delta   = layoutHeight / termsOnLeft;
    Orient  eOri("E");
    for(;t < termsOnTop+termsOnBottom+termsOnLeft; t++)
    {
        _placement.setOrient(t, eOri);
	_placement[t] = nextLoc;
	_placement[t].y = rint(nextLoc.y);
	if(_placement[t].y < _placement[t-1].y+termHeight)
	{
	    _placement[t].y++;	//can't be off by more than one
	    nextLoc.y++;
	}

	nextLoc.y     += delta;
    }

    nextLoc = Point(ceil(layoutBBox.xMax+2*crHeight),floor(layoutBBox.yMin));
    delta   = layoutHeight / termsOnRight;
    Orient  fwOri("FW");
    for(;t < termsOnTop+termsOnBottom+termsOnLeft+termsOnRight; t++)
    {
        _placement.setOrient(t, fwOri);
	_placement[t] = nextLoc;
	_placement[t].y = rint(nextLoc.y);
	if(_placement[t].y < _placement[t-1].y+termHeight)
	{
	    _placement[t].y++;	//can't be off by more than one
	    nextLoc.y++;
	}

	nextLoc.y     += delta;
    }
} */


void layoutGenerator::generate  
(DB* db, bookShelfParser& parser, 
	double      aspectRatio,
	double      whiteSpace,
	double 		xStart,
	double		yStart,
	std::string outFileName)
{
    if (aspectRatio!=0.0)
    myAssert(aspectRatio >= 0.1 && aspectRatio <= 10,
	"AspectRatio should be between 0.0 or 1/10th and 10");
    myAssert(whiteSpace >= 0 && whiteSpace <= 100,
	"Whitespace should be a percentage, between 0 and 100%");
		

    unsigned numCoreCells = (*db).getNetlist().getNumCoreCells();

/*     _placement  = PlacementWOrient(_hgWDims->getNumNodes());
    _isCoreCell = bit_vector(_hgWDims->getNumNodes(), true);
    _isInSubRow = bit_vector(_hgWDims->getNumNodes(), true);
    _isFixed    = bit_vector(_hgWDims->getNumNodes(), false);
    _storElt    = bit_vector(_hgWDims->getNumNodes(), false);
    _cellCoords = vector<RBCellCoord>(_hgWDims->getNumNodes()); 

    unsigned t;
    for(t=0; t!=_hgWDims->getNumTerminals(); t++)
    {
        _isFixed[t]=true;
        _isCoreCell[t]=false;
    }*/

	cout<<"Loaded netlist only from auxFile"<<endl;
	cout<<" Netlist contains:"<<endl;
        cout<<"    "<<(*db).getNetlist().getNumAllPads()<<" terminals"<<endl;
	cout<<"    "<<numCoreCells<<" core cells"<<endl;

    double padHeight = Constants::PAD_HEIGHT;
    double padWidth  = Constants::PAD_WIDTH;
	//checking to see if the widths & heights are consistent, if not overwrite with input file vals
	//check that the netlist meets the dimension requirments
    for (auto cIt = (*db).getNetlist().cellsBegin(); 
	         cIt != (*db).getNetlist().cellsEnd(); 
			 cIt++)
	 {
        if ( (*cIt)->isIO() )
		{
          padWidth = (*cIt)->getWidth();
          padHeight = (*cIt)->getHeight();			
		  break;
		}
	 }			 
	 
	double coreHeight = (*db)._rowDefs->getRowHeight();

    for (auto cIt = (*db).getNetlist().cellsBegin(); 
	         cIt != (*db).getNetlist().cellsEnd(); 
			 cIt++)
	 {
        if ( (*cIt)->isIO() )
		{
          if (padWidth != (*cIt)->getWidth() || padHeight != (*cIt)->getHeight())			
		  cout<<"Pad node ("<<(*cIt)->getName()
			<<") is not the same size as other pads: (" << (*cIt)->getWidth() <<
 			"," << (*cIt)->getHeight() << ")" <<endl;	   
		}		
	 }			 
	


    //double totalWidth = (*db).getTotalCoreCellWidth();
    double totalWidth = 0.0;
    double coreCellArea = 0;
    for (auto cIt = (*db).getNetlist().cellsBegin(); 
	         cIt != (*db).getNetlist().cellsEnd(); 
			 cIt++)
    {
      if ( (*cIt)->isCore() )
      {
        double height = (*cIt)->getHeight();
        if(height != coreHeight)
        {
          cout<<"Core node "<<(*cIt)->getName()
        	<<") is not the same height as other core nodes"<<endl;
        }
        double width = (*cIt)->getWidth();
        totalWidth += width;
        coreCellArea += width*height;
      	
      }
    }
	
 
   	//compute the layout dimensions

    bool areaOK=(coreCellArea != 0.);
    myAssert(areaOK, "No core cells to be placed. Exiting.. ");
    double targetLayoutArea  = coreCellArea /(1.0-(whiteSpace/100.0));
    unsigned numCoreRows = 1;
    if (aspectRatio>0.0)
             numCoreRows=static_cast<unsigned>(rint(
                              sqrt(targetLayoutArea/aspectRatio)/coreHeight));

    numCoreRows = std::max(numCoreRows, (unsigned)3); //due to the height of pads and rows, at least one pad should fit on the side
    double layoutHeight  = numCoreRows * coreHeight;
    double layoutWidth   = rint(targetLayoutArea/layoutHeight);
    layoutWidth = std::max ( 2 * Constants::PAD_WIDTH, layoutWidth);
    double actualLayoutArea = layoutWidth * layoutHeight;
	//layoutWidth must be integer as the sites wll have width 1
	cout<<"All nodes meet dimension requirments"<<endl;
	cout<<"Core cell height(==site height) is "<<coreHeight<<endl;
	cout<<"Total core cell width is "<<totalWidth<<" giving an"
		<<" ave width of "<<totalWidth/numCoreCells<<endl<<endl;
	cout<<"Target Dimensions:"<<endl;
	cout<<"  Area:   "<<targetLayoutArea<<endl;
	cout<<"  WS%:    "<<whiteSpace<<endl;
	cout<<"  AR:     "<<aspectRatio<<endl<<endl;
	//cout<<"Actual Dimensions:"<<endl;
    cout<<"  Width:  "<<layoutWidth<<endl;
	cout<<"  Height: "<<layoutHeight<<"("<<numCoreRows<<" rows)"<<endl;
	cout<<"  Area:   "<<actualLayoutArea<<endl;
	cout<<"  WS%:    "<<100*(actualLayoutArea-coreCellArea)
					/actualLayoutArea<<endl;
	cout<<"  AR:     "<<layoutWidth/layoutHeight<<endl<<endl;

	//construct the coreRows
    Point    origin(xStart,yStart);
    //Orient   rowOrients[2] = {"N", "FS"};
    //RBPSite  crSite(coreHeight, 1.0, Symmetry("Y"));
    //double   spacing = 1.0;


    dbRowDef* newScl = new dbRowDef;	

    for(unsigned rowId = 0; rowId < numCoreRows; rowId++)
    {
	  SingleRow sr (origin.x, origin.y, layoutWidth, coreHeight);		
	  sr.site_width = 50.0;
	  sr.site_spacing = 50.0;
	  sr.site_num = (int) ceil( layoutWidth/(sr.site_width));
      newScl->stdRows.push_back( sr ) ;
      origin.y += coreHeight;
    }
	
	newScl->calculateChipDimensions();
	if ( outFileName.size() == 0)
       outFileName = (*db).getDesignName() + "_AR_" + std::to_string(aspectRatio) + 
    "_WS_" + std::to_string(whiteSpace) ;
	outFileName = (*db).getDesignPath() + outFileName;
	parser.writeSclFile(outFileName+".scl", *newScl);

    //_hgWDims->expandStdCellWidthToFitSiteWidth(_coreRows[0].getSpacing());
    //_hgWDims->setNodeWeightsToAreas(_coreRows[0].getSpacing(),_coreRows[0].getHeight());

	cout<<"Done constructing layout region"<<endl;

	
	//modifing the _rowDefs obj of db
	delete (*db)._rowDefs;
	(*db)._rowDefs = newScl;

	//layout construction is done...add in terminal locations
    //if (aspectRatio>0.0) 
    //placeTerms();
    //backUpCoreRows();
    //initBBox();
	
	Legalizer lg(db);
	lg.doFinalPadPl();	
	

	Plotter plot(db);
	plot.plotPlacementResult ( outFileName, false, false);
	
	
	BBox sourceBB = (*db)._rowDefs->getChipBbox();
	std::cout << "Final BBox: " << sourceBB << "\n";
	
	

}

	
