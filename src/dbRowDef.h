#ifndef DBROWDEF_H
#define DBROWDEF_H


#include "myAssert.h"
#include "Bbox.h"

enum rowType {HorizontalStdRow, VerticalStdRow};

struct SingleRow
{
	public:
    double  lowerLeftX;
    double  lowerLeftY;
    double  width;
    double  height;
    rowType hvType;
	double  site_width;
	double  site_spacing;
	unsigned  site_num;

    SingleRow( double x = 0, double y = 0, double w = 0,
        double h=0, rowType t = HorizontalStdRow):
		lowerLeftX(x), lowerLeftY(y), width(w), height(h), hvType(t)
        {}

friend std::ostream& operator<<(std::ostream& os, const SingleRow& s){
	os << "LL: (" << s.lowerLeftX << "," << s.lowerLeftY << ") ";
	os << "Dim: (" << s.width << "," << s.height << ") ";
	os << "site_width: " << s.site_width << "-site_spacing: " << 
	s.site_spacing << "-site_num: " << s.site_num << std::endl;
	return os ;
}	
	
	
};

class dbRowDef
{
public:
	dbRowDef()
	{
		xOffset    = 0;
		yOffset    = 0;
		chipWidth  = 0;
		chipHeight = 0;
		chipXEnd   = 0;
		chipYEnd   = 0;
		rowHeight  = 0;
		chipArea   = 0;
	}   
	std::vector<SingleRow> stdRows;
	//int     checkRowTypeConsistent();
	//void    shiftCoor(double x, double y);
	//double  getShiftX() {return shiftX;}
	//double  getShiftY() {return shiftY;}
	//void    sortIncreOrder();
	void calculateChipDimensions();
	double getXOffset() {return xOffset;}
	double getYOffset() {return yOffset;}
	
	double getChipWidth() {return chipWidth;}
	void   setChipWidth(double w) { chipWidth = w; }
	
	double getChipHeight() {return chipHeight;}
	void   setChipHeight(double h) { chipHeight = h; }
	
	int    getRowCnt() { return stdRows.size();}
	double getRowHeight() { return rowHeight;}
	void   setRowHeight (double);
        void   setRowWidth (double);

	
	double getChipXEnd() { return chipXEnd; }
	void  setChipXEnd(double x) { chipXEnd = x; }
	
	double getChipYEnd() { return chipYEnd; }
	void  setChipYEnd(double y) { chipYEnd = y; }
	
	double getChipArea() { return chipArea; }
	void setChipArea() { chipArea = chipWidth * chipHeight; }
	
	BBox   getChipBbox() { return _layout;  }	
	void   setChipBBox(const BBox& bb);

	
friend std::ostream& operator<<(std::ostream& os, const dbRowDef& s)
{
	os << "dbRowDef: total rows: " << s.stdRows.size() << std::endl;
	os << "offsets: (" << s.xOffset << "," << s.yOffset << ")" ;
	os << " Dim: (" << s.chipWidth << "," << s.chipHeight << ")" ;
	os << " EndCoor: (" << s.chipXEnd << "," << s.chipYEnd  << ")\n";
	for (unsigned int i=0; i < s.stdRows.size(); i++){
		os << "row: " << i << " " << s.stdRows[i] ;
	}
	return os;
}	

private:
	double xOffset;
	double yOffset;
	double chipWidth;
	double chipHeight;
	double chipXEnd;
	double chipYEnd;
	double rowHeight;
	double chipArea;
	BBox   _layout;

};



#endif // DBROWDEF_H

