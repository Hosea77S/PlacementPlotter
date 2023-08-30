#include "dbRowDef.h"


void dbRowDef::calculateChipDimensions(){
	int rowCnt = stdRows.size();
	this->xOffset = stdRows.front().lowerLeftX;
	this->yOffset = stdRows.front().lowerLeftY;
	
	double maxChipW = 0;
	double maxChipH = stdRows.front().height;
	for (int i=0; i < rowCnt; i++){
		maxChipW = std::max(maxChipW, stdRows[i].width);
		//sanity check
		if (maxChipH != stdRows[i].height){
			myAssert3 (0, "Invalid height for row: ", i, stdRows[i].height);
		}
	}
	this->chipWidth = maxChipW;
	this->chipHeight = maxChipH * rowCnt;
	this->chipXEnd = xOffset + chipWidth;
	this->chipYEnd = yOffset + chipHeight;
	this->rowHeight = maxChipH;
	this->chipArea = chipWidth * chipHeight;
	this->_layout = BBox(xOffset, yOffset, chipXEnd, chipYEnd);
	return;
}

void dbRowDef::setRowHeight(double h) { 
  auto prevHeight = rowHeight;
  rowHeight = h; 
  for (int i=0; i < stdRows.size(); i++) { 
    stdRows[i].height = h; 
    stdRows[i].lowerLeftY += i * (h - prevHeight);
  }
  calculateChipDimensions();
}

void dbRowDef::setRowWidth(double w) {
  auto prevWidth = stdRows.front().width;
  int m = ceil(w / prevWidth);
  //rowHeight = h;
  for (int i=0; i < stdRows.size(); i++) {
    stdRows[i].width = w;
    stdRows[i].site_width *= std::max(1, m);
  }
  calculateChipDimensions();
}




void dbRowDef::setChipBBox (const BBox& bb)
{
	
	std::cout << "\n\t\tChanging Chip BBox: " << bb << "\n";
	_layout = bb;
	xOffset = bb.getBottomLeft().x;
	yOffset = bb.getBottomLeft().y;
	chipWidth = abs( bb.getBottomLeft().x - bb.getTopRight().x );
	chipHeight= abs( bb.getBottomLeft().y - bb.getTopRight().y );
	chipXEnd  = bb.getTopRight().x;
	chipYEnd  = bb.getTopRight().y;
	//rowHeight = 1.0* chipHeight / (int) stdRows.size(); 
	chipArea = chipWidth * chipHeight;
}

