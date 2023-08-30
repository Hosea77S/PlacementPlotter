#pragma once
#ifndef LEGALIZER_H
#define	LEGALIZER_H

#include "bookshelf.h"

//class Grid;

class Legalizer {

private:
	Model* chip;
	int findNewRow(const std::vector<std::vector< Cell* > > &rowVec, const std::vector<double> &totalCellWidthVec,
	int overfilledRowNumber, int rowAvailableWidth, int& rowOffset, int& cellIndex);
	void moveCell(std::vector<std::vector< Cell* > > & rowVec, std::vector<double> & totalCellWidthVec, int overfilledRowNumber, const int& rowOffset, const int& cellIndex);

	void doVerticalLegal(bool DoAccurateLegalization, double alphaRatio);
	void doHorizontalLegal(bool DoAccurateLegalization, double alphaRatio);

	
public:
	Legalizer(Model* chip);
	std::vector< std::vector< Cell* > > doLegalization();
	std::vector< std::vector< Cell* > > findRowVec();
	std::vector< std::vector< Cell* > > findRowVec(int rowSpacing); 
	void putCellsInBound();
	void doRSFQLegalization(int pitch, int sizeOfCluster, int verticalShiftAmount, 
							int horizShiftAmount, int padOffset, int JTL_height, bool addJTL);
	void addJTLCell(int index, double x, double y, double width, double height, int level);
	void legalizeRows(std::vector<std::vector< Cell* > > &rowVec, std::vector<double> &totalCellWidthVec, int rowAvailableWidth, int congestion);
	void legalizeCellsInPlace(std::vector<std::vector< Cell* > > &rowVec, int horizSpacing);
	//void doUniformLegal(std::vector<Cell*> &cellVec, Grid* boundaryGrid, bool is_X_coor, bool);
	void doLazyLegal(bool DoAccurateLegalization,  double alphaRatio_vert, double alphaRatio_horiz);

	/*#DATE2017, a function to recive supercells, and insert a uniform space between them*/
	void doSuperCellUniformSpacing(std::vector<std::vector<Cell*> > &rowVec, 
			map<int, map<int, int> >& row_cell_supCell_map, int horizSpacing);
	
	
};


#endif // !LEGALIZER_H
