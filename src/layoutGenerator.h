#ifndef __LAYOUTGENERATOR_H
#define __LAYOUTGENERATOR_H

#include "common.h"
#include "DB.h"
#include "bookShelfParser.h"

class layoutGenerator
{

public:
  layoutGenerator(){}

  void  placeTerms(); //equally spaces the terminals around the edge of
   //the layout region.

   
   
  void generate  (DB* db, bookShelfParser& parser, 
				  double      aspectRatio = 1.0,
				  double      whiteSpace = 10,
	              double 		xStart = 1000.0, //4*Constants::PAD_OFFSET,
	              double		yStart = 1000.0, //4*Constants::PAD_OFFSET,
				  std::string outputFileName = "");		
};



#endif //__LAYOUTGENERATOR_H


