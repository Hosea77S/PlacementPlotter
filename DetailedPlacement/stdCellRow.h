#ifndef STDCELLROW_HH
#define STDCELLROW_HH
#include <iostream>
#include <vector>

enum rowType {HorizontalStdRow, VerticalStdRow};

struct SingleRow
{
    SingleRow( double x = 0, double y = 0, double w = 0,
        double h=0, rowType t = HorizontalStdRow):
		lowerLeftX(x), lowerLeftY(y), width(w), height(h), hvType(t)
        {}
    double  lowerLeftX;
    double  lowerLeftY;
    double  width;
    double  height;
    rowType hvType;
	double  site_width;
	double  site_spacing;
	unsigned  site_num;

    void    print(std::ostream &os = std::cout);
};

class StdCellRowDef
{
    public:
        StdCellRowDef()
        {
            shiftX = 0;
            shiftY = 0;
        }
        std::vector<SingleRow> stdRows;
        int     checkRowTypeConsistent();
        void    shiftCoor(double x, double y);
        double  getShiftX() {return shiftX;}
        double  getShiftY() {return shiftY;}
        void    print(std::ostream &os = std::cout);
        void    sortIncreOrder();
    private:
        double shiftX;
        double shiftY;
};
#endif
