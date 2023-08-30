#include "Legalization.h"
#include <cstdio>
//#include "Grid.h"
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

/**/

#define debug 0


Legalizer::Legalizer(Model* chip) {
	this->chip = chip;
	//this->putCellsInBound();
}

void Legalizer::addJTLCell(int index, double x, double y, double width, double height, int level){
	//cout << " Adding JTL at " << "(" << x << "," << y << ")" << endl;
	std::string name = "JTLCLK_" + std::to_string(index);
	Cell* jtl = new Cell();
	jtl->name = name;
	jtl->id = chip->cellList.size();
	jtl->hgt = height;
	jtl->wth = width;
	jtl->x = x;
	jtl->y = y;
	ORI o = B0;
	jtl->ori = o;
	jtl->level = level;
	jtl->pad = false;
	Pin* InClock = new Pin(); InClock->dir = PIN_IN;
	InClock->cellPtr = jtl;
	InClock->x = double(0.4); InClock->y = double(0.4);	
	jtl->pinList.push_back(InClock);
	Pin* OutClock = new Pin(); OutClock->dir = PIN_OUT;
	OutClock->cellPtr = jtl;
	OutClock->x = double(0.5); OutClock->y = double(0.5);
	jtl->pinList.push_back(OutClock);
	chip->cellList.push_back(jtl);
	
}


void Legalizer::doRSFQLegalization(int pitch, int sizeOfCluster, int verticalShiftAmount, int horizShiftAmount, 
									int padOffset, int JTL_height, bool addJTL) {
	//To debug, remove comments
	if (sizeOfCluster == 0) {cerr << " sizeOfCluster is 0 " << endl; return;}
	this->putCellsInBound();
	this->doLegalization();
	auto rowVec = this->findRowVec();
	double minCellWidth = this->chip->minCellWidth();
	minCellWidth = max(int(minCellWidth), horizShiftAmount);
	int maxChipWidth = this->chip->chip_width;
	double rowHeight = chip->rowDef->stdRows[0].height;
	int JTLcount = 0; 
	//int JTL_height = 40 ;

	
	for (unsigned int i = 0; i < rowVec.size(); i++) {
		int currentRowJTLs = 0; 
		if (debug) cout << "**********************************************************************************" << endl;
		if (debug) cout << "Row: " << i << " with " << rowVec[i].size() << " Cells" << endl;
		if (debug){
			for (unsigned int j = 0; j < rowVec[i].size(); j++)
				cout << " (" << rowVec[i][j]->name << ": " << rowVec[i][j]->x << ")";
			cout << endl;			
		}

		int numOfNonTerminalCellsInthisRow = 0;
		for(unsigned int p = 0; p < rowVec[i].size(); p++)
			if (!rowVec[i][p]->pad)
				numOfNonTerminalCellsInthisRow++;
			
		int numberOfClusters = ((numOfNonTerminalCellsInthisRow - (i % sizeOfCluster)) / sizeOfCluster);
		// If size of row is not a multiple of size of cluster, an extra cluster is formed in the the begining of the row
		numberOfClusters += (((numOfNonTerminalCellsInthisRow - (i % sizeOfCluster)) % sizeOfCluster) == 0) ? 0:1;
		numberOfClusters += ((i % sizeOfCluster) == 0) ? 0:1; 
		int maxcurrentRowJTLs = numberOfClusters - 1;
		if (debug) cout << " numOfNonTerminalCellsInthisRow : " << numOfNonTerminalCellsInthisRow <<
			" numberOfClusters: " << numberOfClusters << " maxcurrentRowJTLs : " << maxcurrentRowJTLs << endl;
		int x_offset = this->chip->x_offset;
		double rowWidth = 0;
		int n = 0;
		
		int firstIndex = 0; 
		int lastCellIndex = 0;
		if (int(rowVec[i].size()) >= sizeOfCluster) {
			while (firstIndex < int(i%sizeOfCluster)){
			//for (unsigned int k=0; k < (i%sizeOfCluster); k++){
				if (!rowVec[i][lastCellIndex]->pad){
					//cout << "Changing location of cell: " << rowVec[i][j]->name << " from (" << rowVec[i][j]->x << ", " << rowVec[i][j]->y << " ) to ";
					rowVec[i][lastCellIndex]->x = x_offset;
					rowVec[i][lastCellIndex]->y += (verticalShiftAmount * i );
					//cout << "(" << rowVec[i][j]->x << ", " << rowVec[i][j]->y << ")" << endl;
					x_offset += rowVec[i][lastCellIndex]->wth;
					firstIndex ++;
				} 
				lastCellIndex ++;
				
			}
			if (i%sizeOfCluster > 0){
				x_offset += minCellWidth;		
				if (addJTL) {
					JTLcount++;
					currentRowJTLs++;
					addJTLCell(JTLcount, x_offset - minCellWidth , (rowVec[i][lastCellIndex]->y + rowHeight - JTL_height), minCellWidth, JTL_height, rowVec[i][lastCellIndex-1]->level);	
				}

			}
		}
			
		if (debug) cout << " firstIndex : " << firstIndex << " LastIndex : " << lastCellIndex << endl;
		
		
		
		
		
		for (unsigned int j = lastCellIndex; j < rowVec[i].size(); j++) {
			if (rowVec[i][j]->pad) continue;
			if (!rowVec[i][j]->pad){
				//cout << "Changing location of cell: " << rowVec[i][j]->name << " from (" << rowVec[i][j]->x << ", " << rowVec[i][j]->y << " ) to ";
				rowVec[i][j]->x = x_offset;
				rowVec[i][j]->y += (verticalShiftAmount * i );
				//cout << "(" << rowVec[i][j]->x << ", " << rowVec[i][j]->y << ")" << endl;
				x_offset += rowVec[i][j]->wth;
			} 
			if (n < sizeOfCluster - 1) {
				if (!rowVec[i][j]->pad)
					n++;
			}
			else {
				n = 0; 
				if (addJTL == true) {
					if (currentRowJTLs >= maxcurrentRowJTLs) continue;
					JTLcount++;
					currentRowJTLs++;
					addJTLCell(JTLcount, x_offset, (rowVec[i][j]->y + rowHeight - JTL_height), minCellWidth, JTL_height, rowVec[i][j]->level);	
				}

				x_offset += minCellWidth;
			}
			rowWidth += rowVec[i][j]->wth;
			
		}
//		if (numberOfClusters * minCellWidth + rowWidth > maxChipWidth)
//			maxChipWidth = numberOfClusters * minCellWidth + rowWidth;

		if (x_offset - this->chip->x_offset > maxChipWidth)
			maxChipWidth = x_offset - this->chip->x_offset;


		if (debug){
			for (unsigned int j = 0; j < rowVec[i].size(); j++)
				cout << " (" << rowVec[i][j]->name << ": " << rowVec[i][j]->x << ")";
			cout << endl;
		}
		
		if (currentRowJTLs != maxcurrentRowJTLs && addJTL) cerr << "Row : " << i << " currentRowJTLs " << currentRowJTLs << " maxcurrentRowJTLs" << maxcurrentRowJTLs << endl;
		
	}
	if (maxChipWidth > this->chip->chip_width) {
		cout << " maxWidth violation." << " chip_width :  " << this->chip->chip_width << " maxChipWidth :  " << maxChipWidth << endl;
		maxChipWidth = ((int(maxChipWidth) / 10) + 1) * 10;
		for (unsigned int i = 0; i < rowVec.size(); i++){
			for (unsigned int j = 0; j < rowVec[i].size(); j++){
				if (!rowVec[i][j]->pad) continue;
				if (rowVec[i][j]->x > (this->chip->x_offset + this->chip->chip_width)){
					if (debug) cout << " Changing Cell : " << rowVec[i][j]->name << " 's X from " << rowVec[i][j]->x ;
					rowVec[i][j]->x = this->chip->x_offset + maxChipWidth + padOffset;
					if (debug) cout << " to : " << rowVec[i][j]->x << endl;					
				}
							
			}
			
		}
		chip->chip_width = maxChipWidth;
	}
	for (unsigned int i = 0; i < chip->cellList.size(); i++)
		if (chip->cellList[i]->x > this->chip->x_offset + maxChipWidth && chip->cellList[i]->pad != 1)
			cerr << " Cell " << chip->cellList[i]->name << " is out of x bound : " << chip->cellList[i]->x << endl;

	if (addJTL) cout << " Total number of " << JTLcount << " JTLclocks are added to design." << endl;
	return;
}




void Legalizer::putCellsInBound() {
	if (debug) cout << "************************ Legalizer :: PuttingCellsInChipBoundary ************************ \n";
	auto cellList = chip->cellList;
	for (unsigned int i = 0; i < cellList.size(); i++) {
		if (cellList[i]->pad) continue;

		Cell* currCell = cellList[i];
		if (currCell->x < chip->x_offset) {
			//cout << currCell->name << " : currCell->x < chip->x_offset " << currCell->x << " < " << chip->x_offset <<
			//	" , Setting x to be : " << chip->x_offset << endl;
			currCell->x = chip->x_offset;
		}
		if (currCell->x > chip->x_offset + chip->chip_width ||
			currCell->x + currCell->wth > chip->x_offset + chip->chip_width) {
			//cout << currCell->name << " : currCell->x > chip->x_offset + chip->chip_width " << currCell->x << " > " <<  chip->x_offset + chip->chip_width <<
			//	" , Setting x to be : " << chip->x_offset + chip->chip_width - currCell->wth << endl;
			currCell->x = chip->x_offset + chip->chip_width - currCell->wth;
		} 
		if (currCell->y < chip->y_offset) {
			//cout << currCell->name << " : currCell->y < chip->y_offset " << currCell->y << " < " << chip->y_offset <<
			//	" , Setting y to be : " << chip->y_offset << endl;
			currCell->y = chip->y_offset;
		}
		if (currCell->y > chip->y_offset + chip->chip_height ||
			currCell->y + currCell->hgt > chip->y_offset + chip->chip_height) {
			//cout << currCell->name << " : currCell->y > chip->y_offset + chip->chip_height " << currCell->y << " > " << chip->y_offset + chip->chip_height <<
			//	" , Setting y to be : " << chip->y_offset + chip->chip_height - currCell->hgt << endl;
			currCell->y = chip->y_offset + chip->chip_height - currCell->hgt;
		}
	}
}

vector< vector< Cell* >> Legalizer::findRowVec() {
	return (this->findRowVec(0));
	//vector<Cell* > ySortedCellList(this->chip->cellList);
	//sort(ySortedCellList.begin(), ySortedCellList.end(), compare_cell_y);
	//int numOfRows = chip->rowDef->stdRows.size();
	//double rowHeight = chip->rowDef->stdRows[0].height;
    //
	//vector< vector< Cell* >> rowVec(numOfRows);
	//double yPos = chip->rowDef->stdRows[0].height / 2;
    //
	////Putting the cells into the rows based on their CenterY coordinates
	//for (unsigned int i = 0; i < ySortedCellList.size(); i++) {
	//	double yCenterPos = ySortedCellList[i]->y - chip->y_offset + double(ySortedCellList[i]->hgt / 2);
	//	if (yCenterPos < 0) continue;
	//	int row_index = yCenterPos / rowHeight;
	//	if (row_index >= numOfRows || row_index < 0)
	//	{
	//		if (!ySortedCellList[i]->pad) {
	//			cerr << "Row index is outOfBound than total number of rows " << row_index << " " << numOfRows ;
	//			cerr << " Cell : " << ySortedCellList[i]->name << " is out of bound" << endl;
	//		}
	//	}
	//	else {
	//		//cout << "Cell : " << ySortedCellList[i]->name << " with coordinates: " << ySortedCellList[i]->x << " , " << ySortedCellList[i]->y << 
	//		//	" with height : " << ySortedCellList[i]->hgt << " is pushed to row: " << row_index << endl;
	//		rowVec[row_index].push_back(ySortedCellList[i]);
	//		//ySortedCellList[i]->y = row_index * rowHeight;
	//		//cout << " And it's new position is: " << ySortedCellList[i]->y << endl;
    //
	//	}
	//}
	//for (unsigned int i = 0; i < rowVec.size(); i++)
	//		sort(rowVec[i].begin(), rowVec[i].end(), compare_cell_x);
	//return rowVec;
}


vector< vector< Cell* >> Legalizer::findRowVec(int rowSpacing) {

	vector<Cell* > ySortedCellList(this->chip->cellList);
	sort(ySortedCellList.begin(), ySortedCellList.end(), compare_cell_y);
	int numOfRows = chip->rowDef->stdRows.size();
	double rowHeight = chip->rowDef->stdRows[0].height + rowSpacing;

	vector< vector< Cell* >> rowVec(numOfRows);

	//Putting the cells into the rows based on their CenterY coordinates
	for (unsigned int i = 0; i < ySortedCellList.size(); i++) {
		double yCenterPos = ySortedCellList[i]->y - chip->y_offset + double(ySortedCellList[i]->hgt / 2);
		if (yCenterPos < 0) continue;
		int row_index = yCenterPos / rowHeight;
		if (row_index >= numOfRows || row_index < 0)
		{
			if (!ySortedCellList[i]->pad) {
				cerr << "Row index is outOfBound than total number of rows " << row_index << " " << numOfRows ;
				cerr << " Cell : " << ySortedCellList[i]->name << " is out of bound" << endl;
			}
		}
		else {
			//cout << "Cell : " << ySortedCellList[i]->name << " with coordinates: " << ySortedCellList[i]->x << " , " << ySortedCellList[i]->y << 
			//	" with height : " << ySortedCellList[i]->hgt << " is pushed to row: " << row_index << endl;
			rowVec[row_index].push_back(ySortedCellList[i]);
			//ySortedCellList[i]->y = row_index * rowHeight;
			//cout << " And it's new position is: " << ySortedCellList[i]->y << endl;

		}
	}
	for (unsigned int i = 0; i < rowVec.size(); i++)
			sort(rowVec[i].begin(), rowVec[i].end(), compare_cell_x);
	return rowVec;
}






vector< vector< Cell* >> Legalizer::doLegalization() {
	
	cout << "************************ Legalization ************************\n";
	vector<Cell* > ySortedCellList (this->chip->cellList);
	sort(ySortedCellList.begin(), ySortedCellList.end(), compare_cell_y);

	int numOfRows = chip->rowDef->stdRows.size();
	double rowHeight = chip->rowDef->stdRows[0].height;

	vector< vector< Cell* >> rowVec(numOfRows);
	vector<double> totalCellWidthVec(numOfRows, 0.0);
	double yPos = chip->rowDef->stdRows[0].height / 2;
	
	//Putting the cells into the rows based on their CenterY coordinates
	for (unsigned int i = 0; i < ySortedCellList.size(); i++) {
		if (ySortedCellList[i]->pad ) continue;
		double yCenterPos = ySortedCellList[i]->y - chip->y_offset + double(ySortedCellList[i]->hgt/2);
		int row_index = yCenterPos / rowHeight;
		if (row_index > numOfRows || row_index < 0 ||
			ySortedCellList[i]->x < chip->x_offset || ySortedCellList[i]->x >(chip->chip_width + chip->x_offset))
		{
			if (!ySortedCellList[i]->pad) {
				cerr << "Row index is greater than total number of rows.\n";
				cerr << "Cell : " << ySortedCellList[i]->name << " is out of bound";
			}
		}
		else {
			//cout << "Cell : " << ySortedCellList[i]->name << " with coordinates: " << ySortedCellList[i]->x << " , " << ySortedCellList[i]->y << 
			//	" with height : " << ySortedCellList[i]->hgt << " is pushed to row: " << row_index << endl;
			rowVec[row_index].push_back(ySortedCellList[i]);
			totalCellWidthVec[row_index] +=  ySortedCellList[i]->wth;
			//ySortedCellList[i]->y = row_index * rowHeight;
			//cout << " And it's new position is: " << ySortedCellList[i]->y << endl;

		}
	}

	//for (unsigned int i = 0; i < rowVec.size(); i++){
	//	if (rowVec[i].size() == 0){
	//		if (debug) cout << "Row " << i << " is empty" << endl;			
	//	}
	//	else{
	//		if (debug) cout << "Row " << i << " is not empty" << endl;					
	//	} 
	//}
	
	double rowAvailableWidth = chip->chip_width;

	//Puts additional constraint on the maximum available width of each row, if greater than zero there's more space in each row for cell reordering
	double congestion = 20;
	
	bool isRowBalanceDone = false;
	while (!isRowBalanceDone) {

		for (unsigned int i = 0; i < rowVec.size(); i++) {
			if (totalCellWidthVec[i] > rowAvailableWidth) {
				while (totalCellWidthVec[i] > rowAvailableWidth - congestion) {
					//cout << "row # " << i << " is overfilled.\n";
					int offset = 0;
					int cellIndex = 0;
					int canFindNewRow = 
							findNewRow(rowVec, totalCellWidthVec, i, rowAvailableWidth - congestion, offset, cellIndex);
					if (canFindNewRow == -1) {
						cerr << "can't FindNewRow for congested row: " <<  i << " Skipping\n\n";
						break;
					}
					//cout << "Row #: " <<  i << " has " << rowVec[i].size() << " cells and its prospect cell is: " << rowVec[i][cellIndex]->name <<
					//	" with width: " << rowVec[i][cellIndex]->wth << " and total width is: " << totalCellWidthVec[i] << endl;
					//cout << "Row #: " << i+offset << " has " << rowVec[i + offset].size() << " cells and its front cell is: " << rowVec[i + offset][0]->name <<
					//	" and total width is: " << totalCellWidthVec[i + offset] << endl;

					//cout << "Moving Cell # " << cellIndex << " from overfilled row\n";
					moveCell(rowVec, totalCellWidthVec, i, offset, cellIndex);


					//cout << "Row #: " << i << " has " << rowVec[i].size() << " cells and its prospect cell is: " << rowVec[i][rowVec[i].size()-1]->name <<
					//	" with width: " << rowVec[i][cellIndex]->wth << " and total width is: " << totalCellWidthVec[i] << endl;
					//cout << "Row #: " << i + offset << " has " << rowVec[i + offset].size() << " cells and its front cell is: " << rowVec[i + offset][0]->name <<
					//	" and total width is: " << totalCellWidthVec[i + offset] << endl << endl;

				}
			}
		}
		isRowBalanceDone = true;
	}
	//for (unsigned int i = 0; i < totalCellWidthVec.size(); i++)
	//	cout << "Row # " << i << " total cell width: " << totalCellWidthVec[i] << endl;

	legalizeRows(rowVec, totalCellWidthVec, rowAvailableWidth, congestion);


	if (debug) cout << "Legalization is done.\n";
	

	return rowVec;
}


void Legalizer::legalizeRows(vector<vector< Cell* > > &rowVec, vector<double> &totalCellWidthVec, int rowAvailableWidth, int congestion) {
	vector<double> fixedCellsLocations;
	double rowHeight = chip->rowDef->stdRows[0].height;

	//Legalize cells inside every row
	for (unsigned int i = 0; i < rowVec.size(); i++) {
		if(rowVec[i].size() > 0){
			sort(rowVec[i].begin(), rowVec[i].end(), compare_cell_x);
	
			double minSpanningWidth;
			if (rowVec[i].size() > 0 )
				minSpanningWidth = int((rowAvailableWidth  - totalCellWidthVec[i])/(rowVec[i].size()));
			if (minSpanningWidth < 0)
				cerr << "minSpanningWidth is: " << minSpanningWidth << " setting it to 0 " << endl;
			else minSpanningWidth = 0;
			//cout << "Row # " << i << " total cell width: " << totalCellWidthVec[i] << " rowAvailableWidth: " << rowAvailableWidth <<
			//	" total number of cells: " << rowVec[i].size() <<
			//	  " congestion:  " << congestion << " minSpanningWidth is: " << minSpanningWidth << endl;
	
			rowVec[i][0]->x = chip->x_offset;
			rowVec[i][0]->y = i * rowHeight + chip->y_offset;
			for (int j = 1; j < int(rowVec[i].size()); j++) {
				//if (!rowVec[i][j]->pad && rowVec[i][j]->x > 0) {
					rowVec[i][j]->x = rowVec[i][j - 1]->x + rowVec[i][j - 1]->wth + minSpanningWidth;
					if (rowVec[i][j]->x < 0)
						cout << "Row # " << i << " with coordinate: " << rowVec[i][j]->x << endl;
					rowVec[i][j]->y = i * rowHeight + chip->y_offset;
				//}
			}			
		}
	}


	//Checking for out-of-bound cells;
	for (unsigned int i = 0; i < chip->cellList.size(); i++) {
		if (!chip->cellList[i]->pad) {
			if (chip->cellList[i]->x < chip->x_offset)	cerr << chip->cellList[i]->name << "is out of bound. x < x_offset" << endl;//chip->cellList[i]->x = chip->x_offset;
			if (chip->cellList[i]->x + chip->cellList[i]->wth > chip->chip_width + chip->x_offset)
				cerr << chip->cellList[i]->name << "is out of bound. x > chip_wdth" << endl;//chip->cellList[i]->x = chip->chip_width + chip->x_offset - chip->cellList[i]->wth;
			if (chip->cellList[i]->y < chip->y_offset)	cerr << chip->cellList[i]->name << "is out of bound. y < y_offset" << endl;//chip->cellList[i]->y = chip->y_offset;
			if (chip->cellList[i]->y + chip->cellList[i]->hgt > chip->y_offset + chip->chip_height)
				cerr << chip->cellList[i]->name << "is out of bound. y > chip_hght" << endl;//chip->cellList[i]->y = chip->chip_height + chip->y_offset - chip->cellList[i]->hgt;
			//cout << "Cell: " << this->chip->cellList[i]->id << " final position: (" << this->chip->cellList[i]->x << ", " << this->chip->cellList[i]->y << ") \n";

		}
	}



}

/* Legalizing W.R.T position of fixed cells
//double minSpanningWidth = (rowAvailableWidth + congestion - totalCellWidthVec[i])/rowVec;
for (unsigned int j = 0; j < rowVec[i].size(); j++) {
if (rowVec[i][j]->pad) {
fixedCellsLocations.push_back(j);
}
}
if (fixedCellsLocations.size() > 0) {
vector<double> sumOfWidth(fixedCellsLocations.size() + 1, 0.0);
for (unsigned int k = 0; k < fixedCellsLocations.size() + 1; k++) {
if (k == 0)
for (int s = 0; s < fixedCellsLocations[k]; s++)
sumOfWidth[k] += rowVec[i][s]->wth;
else
for (int s = fixedCellsLocations[k - 1]; s < fixedCellsLocations[k]; s++)
sumOfWidth[k] += rowVec[i][s]->wth;
}

for (unsigned int k = 0; k < fixedCellsLocations.size(); k++) {
for (int t = 0; t < sumOfWidth.size(); t++) {
if (t == 0) {
while (sumOfWidth[t] < rowVec[i][fixedCellsLocations[k]]->x - chip->x_offset) {
if (fixedCellsLocations[k] > 0) {
sumOfWidth[t] -= rowVec[i][fixedCellsLocations[k] - 1]->wth;
sumOfWidth[t + 1] += rowVec[i][fixedCellsLocations[k] - 1]->wth;
iter_swap(rowVec[i].begin() + fixedCellsLocations[k] - 1, rowVec[i].begin() + fixedCellsLocations[k]);
fixedCellsLocations[k]--;
if (fixedCellsLocations[k] == 0)
cerr << "Error in swaping cells t==0 case, exiting.\n";

}
}


}
// 0 < t < size()-1
else if (t < sumOfWidth.size() - 1) {
if (fixedCellsLocations[k] > 0) {
while (sumOfWidth[t] < rowVec[i][fixedCellsLocations[k]]->x - rowVec[i][fixedCellsLocations[k - 1]]->x) {
sumOfWidth[t] -= rowVec[i][fixedCellsLocations[k] - 1]->wth;
sumOfWidth[t + 1] += rowVec[i][fixedCellsLocations[k] - 1]->wth;
iter_swap(rowVec[i].begin() + fixedCellsLocations[k] - 1, rowVec[i].begin() + fixedCellsLocations[k]);
fixedCellsLocations[k]--;
if (fixedCellsLocations[k] == 0)
cerr << "Error in swaping cells t==0 case, exiting.\n";

}
}
}
}

}

}




*/

void Legalizer::moveCell(vector<vector< Cell* > > &rowVec, vector<double> &totalCellWidthVec, int overfilledRowNumber, const int& rowOffset, const int& cellIndex) {
	int destinationRow = overfilledRowNumber + rowOffset;
	if (destinationRow < 0 || destinationRow > int(rowVec.size()) - 1) {
		cerr << "Invalid destination row (moveCell). Exiting\n.";
		exit(1);
	}
	else if (cellIndex > int(rowVec[overfilledRowNumber].size())) {
		cerr << "Invalid cell index in source row (moveCell). Exiting\n.";
		exit(1);
	}

	else {
		//Subtracting the width of removed cell from source row
		totalCellWidthVec[overfilledRowNumber] -= rowVec[overfilledRowNumber][cellIndex]->wth;
		//Adding the width of new cell to destination row
		totalCellWidthVec[destinationRow] += rowVec[overfilledRowNumber][cellIndex]->wth;
		//Pushing new cell to the front of destination row
		rowVec[destinationRow].insert(rowVec[destinationRow].begin(), rowVec[overfilledRowNumber][cellIndex]);
		//poping the removed cell from source row
		rowVec[overfilledRowNumber].erase(rowVec[overfilledRowNumber].begin() + cellIndex );
	}

}



//Legalizes cells by checking if each 2 cell overlap, sorts overlapping cells, and shifts them to remove overlap
void Legalizer::legalizeCellsInPlace(vector<vector< Cell* > > &rowVec, int horizSpacing){
	for (int i=0; i < int(rowVec.size()); i++){
		sort(rowVec[i].begin(), rowVec[i].end(), compare_cell_x);
		for (int j=0; j < int(rowVec[i].size())-1; j++){
			if (rowVec[i][j]->x + rowVec[i][j]->wth > rowVec[i][j+1]->x){
				rowVec[i][j+1]->x = rowVec[i][j]->x + rowVec[i][j]->wth + horizSpacing;
				//cout << " Shifting cell " << rowVec[i][j+1]->name << " by " << 
				//		rowVec[i][j]->x + rowVec[i][j]->wth - rowVec[i][j+1]->x << "units.\n";
			} 
		}
	}
	
	return ;
}


int Legalizer::findNewRow(const vector<vector< Cell* > > &rowVec, const vector<double> &totalCellWidthVec, int overfilledRowNumber, int rowAvailableWidth,
	int& rowOffset, int& cellIndex) {
	int offset = 0;
	if (overfilledRowNumber < 0 || overfilledRowNumber > int(rowVec.size())) return -1;
	int prsopectCellIndex = rowVec.at(overfilledRowNumber).size() - 1;
	if (overfilledRowNumber == 0) {
	cout << "************************ Here ************************\n";
		int cellIndexDisplacement = 0;
		bool offsetIsFound = false;
		while (!offsetIsFound) {
			for (int i = 1; i < int(rowVec.size()); i++) {
				if ((prsopectCellIndex - cellIndexDisplacement) > int(rowVec.at(overfilledRowNumber).size()) || 
				(prsopectCellIndex - cellIndexDisplacement) < 0) {
					cerr << "prsopectCellIndex - cellIndexDisplacement : " << prsopectCellIndex - cellIndexDisplacement 
					<< " is invalid index for row " <<  overfilledRowNumber << endl;
					continue;
				}
				//make sure the prospect cell is moavble
				if (!rowVec.at(overfilledRowNumber).at(prsopectCellIndex - cellIndexDisplacement)->pad) {
					if (totalCellWidthVec.at(i) + rowVec.at(overfilledRowNumber).at(prsopectCellIndex - cellIndexDisplacement)->wth < rowAvailableWidth) {
						offset = i;
						rowOffset = offset;
						cellIndex = prsopectCellIndex - cellIndexDisplacement;
						return 0;
						//break;
					}
				}
				else {
					if (cellIndexDisplacement <= prsopectCellIndex)
						cellIndexDisplacement--;
					else {
						cerr << "Rows are overfilled, no prospect row could be found. Exiting (LEGALIZATION)(case row=0).\n";
						return -1;
					}
				}
			}
			//if all the rows are full to capacity
			if (offset == 0) {
				if(cellIndexDisplacement <= prsopectCellIndex)
					cellIndexDisplacement--;
				else {
					cerr << "Rows are overfilled, no prospect row could be found. Exiting (LEGALIZATION)(case row=0).\n";
					return -1;
				}

			}

		}
	}
	else if (overfilledRowNumber < int(rowVec.size()) - 1) {
		bool offsetIsFound = false;
		offset = 1;
		int cellIndexDisplacement = 0;
		while (!offsetIsFound) {
			//int maxPossibleOffset = max(overfilledRowNumber, rowVec.size() - 1 - overfilledRowNumber);
			//if ((prsopectCellIndex - cellIndexDisplacement) > int(rowVec[overfilledRowNumber].size()) || 
			//(prsopectCellIndex - cellIndexDisplacement) < 0) {
			//	cerr << "prsopectCellIndex - cellIndexDisplacement : " << prsopectCellIndex - cellIndexDisplacement 
			//	<< " is invalid index for row " <<  overfilledRowNumber << endl;
			//	break;
			//}
			
			//if ((offset + overfilledRowNumber) < 0 || (offset + overfilledRowNumber) > int(totalCellWidthVec.size())){
			//	cerr  << "offset + overfilledRowNumber : " << offset << " " << overfilledRowNumber << "is invalid for " <<
			//	"row totalCellWidthVec with size " << totalCellWidthVec.size() << endl; 
			//	//break;
			//}
			
			if (((offset + overfilledRowNumber) < int(rowVec.size()) - 1) && ((offset + overfilledRowNumber) >= 0 ) && 
				((prsopectCellIndex - cellIndexDisplacement) >= 0 && 
					((prsopectCellIndex - cellIndexDisplacement) < int(rowVec.at(overfilledRowNumber).size())))) {
				if (totalCellWidthVec.at(offset + overfilledRowNumber) + rowVec.at(overfilledRowNumber).at(prsopectCellIndex - cellIndexDisplacement)->wth < rowAvailableWidth) {
					rowOffset = offset;
					cellIndex = prsopectCellIndex - cellIndexDisplacement;
					return 0;
				}
			}
			
			//if ((overfilledRowNumber - offset) < 0 || (overfilledRowNumber - offset) > int(totalCellWidthVec.size())){
			//	cerr  << "overfilledRowNumber - offset : " << overfilledRowNumber << " " <<  offset << " is invalid for " <<
			//	"row totalCellWidthVec with size " << totalCellWidthVec.size() << endl; 
			//	//break;
			//}
			
			if (((overfilledRowNumber - offset) >= 0) && 
				((prsopectCellIndex - cellIndexDisplacement) >= 0 && 
					((prsopectCellIndex - cellIndexDisplacement) < int(rowVec.at(overfilledRowNumber).size())))) 
				{
				if (totalCellWidthVec.at(overfilledRowNumber - offset) + rowVec.at(overfilledRowNumber).at(prsopectCellIndex - cellIndexDisplacement)->wth < rowAvailableWidth) {
					rowOffset = -offset;
					cellIndex = prsopectCellIndex - cellIndexDisplacement;
					return 0;
				}
			}
			if(offset <  int(rowVec.size()) - 1)
				offset++;
			else {
				if (cellIndexDisplacement <= prsopectCellIndex) {
					offset = 1;
					cellIndexDisplacement++;
				}
				else {
					cerr << "Rows are overfilled, no prospect row could be found. Exiting (LEGALIZATION)(case row " << overfilledRowNumber << ").\n";
					return -1;
				}

			}

		}
	}
	//finding prospect row for balancing last row
	else {
		//cout << "In last row" << endl;
		bool offsetIsFound = false;
		offset = 0;
		int cellIndexDisplacement = 0;
		while (!offsetIsFound) {
			//Beacuse we are searching for a replacement of final row index starts from rowVec.size() - 2
			for (int i = 1; i <= int(rowVec.size()) - 1; i++) {
				if (totalCellWidthVec.at(rowVec.size() - 1 - i) + rowVec.at(overfilledRowNumber).at(prsopectCellIndex - cellIndexDisplacement)->wth < rowAvailableWidth) {
					offset = i;
					rowOffset = -offset;
					cellIndex = prsopectCellIndex - cellIndexDisplacement;
					return 0;
					//break;
				}
			}
			//if all the rows are full to capacity, meaning if offset is still 0
			if (offset == 0) {
				if (cellIndexDisplacement <= prsopectCellIndex)
					cellIndexDisplacement--;
				else {
					cerr << "Rows are overfilled, no prospect row could be found. Exiting (LEGALIZATION)(case row=0).\n";
					return -1;
				}
			}

		}

	}
	return -1;
}


void Legalizer::doVerticalLegal(bool DoAccurateLegalization, double alphaRatio){
	if (!DoAccurateLegalization){
		vector<Cell* > ySortedCellList (this->chip->cellList);
		sort(ySortedCellList.begin(), ySortedCellList.end(), compare_cell_y);

		int numOfRows = chip->rowDef->stdRows.size();
		double rowHeight = chip->rowDef->stdRows[0].height;

		//vector< vector< Cell* >> rowVec(numOfRows);
		int cellPerRow = int(chip->numOfNonTerminalNodes() / numOfRows) + 1;
		int index = 0;
		int height_offset = int(chip->y_offset * (1.0 / alphaRatio));
		for (int i=0; i < int(ySortedCellList.size()); i++){
			if (ySortedCellList[i]->pad) continue;
			if (index < cellPerRow){
				index ++ ;
			}
			else {
				index = 0;			
				height_offset += int(alphaRatio * rowHeight);
			}
			ySortedCellList[i]->y = height_offset;
		}
		//cout << "cellPerRow is : " << cellPerRow << endl;
		//for (int i=0; i < int(ySortedCellList.size()); i++){
		//	cout << "name " << ySortedCellList[i]->name << " y: " << ySortedCellList[i]->y << endl;
		//}	
		
	}
	return ;
}

void Legalizer::doLazyLegal(bool DoAccurateLegalization, double alphaRatio_vert, double alphaRatio_horiz){
	this->doVerticalLegal(DoAccurateLegalization, alphaRatio_vert);
	this->doHorizontalLegal(DoAccurateLegalization, alphaRatio_horiz);
	return;
}

void Legalizer::doHorizontalLegal(bool DoAccurateLegalization, double alphaRatio){
	if (!DoAccurateLegalization){
		auto rowVec = findRowVec();
		double rowHeight = chip->rowDef->stdRows[0].height;
		int avgCellWidth = int(chip->CalculateTotalCellArea() / rowHeight / chip->numOfNonTerminalNodes());
		for (int i=0; i < int(rowVec.size()); i++){
			if (rowVec[i].size() == 0) continue;
			int x_offset = int(chip->x_offset * (1.0 / alphaRatio));
			int xSpacing = max(0, int(int(chip->chip_width - (avgCellWidth * int(rowVec[i].size()))) / int(rowVec[i].size()))) + avgCellWidth;
			assert(xSpacing > 0);
			//cout << "Cellsper row : " << i << " is : " << rowVec[i].size() << " xSpacing : " << xSpacing << endl;
			for (int j=0; j < int (rowVec[i].size()); j++){
				if (rowVec[i][j]->pad) continue;
				rowVec[i][j]->x = x_offset;
				x_offset += int(alphaRatio * xSpacing) ;
			}
		}
		
	}
	return;
		
/* 		vector<Cell* > xSortedCellList (this->chip->cellList);
		sort(xSortedCellList.begin(), xSortedCellList.end(), compare_cell_x);

		int numOfRows = chip->rowDef->stdRows.size();
		double rowHeight = chip->rowDef->stdRows[0].height;
		//int cellPerRow = int(chip->numOfNonTerminalNodes() / numOfRows) + 1;
		int avgCellWidth = int(chip->CalculateTotalCellArea() / rowHeight / chip->numOfNonTerminalNodes());
		int cellPerRow = int(chip->chip_width / avgCellWidth);
		int xSpacing = avgCellWidth;
		cout << "numOfRows : " << numOfRows << " avgCellWidth : " << avgCellWidth << " cellPerRow : " << cellPerRow << endl;
		
		int index = 0;
		int width_offset = chip->x_offset * (1 / alphaRatio);
		for (int i=0; i < int(xSortedCellList.size()); i++){
			if (xSortedCellList[i]->pad) continue;
			if (index < cellPerRow){
				index ++ ;
			}
			else {
				index = 0;			
				width_offset += (alphaRatio * xSpacing) + xSortedCellList[i]->wth;
			}
			xSortedCellList[i]->x = width_offset;
		}	
	}
 return ;	
 */	
}

/*
void Legalizer::doUniformLegal(vector<Cell*> &cellVec, Grid* boundaryGrid, bool is_X_coor, bool startFromEndofBoundary){
	//cout << "Size of cellList : " << cellVec.size() << endl;
	if (cellVec.size() == 0) return;
	double left_offset = (is_X_coor) ? (boundaryGrid->grid->xl) : (boundaryGrid->grid->yl);
	double right_offset = (is_X_coor) ? (boundaryGrid->grid->xh) : (boundaryGrid->grid->yh);
	double spacing = (is_X_coor) ? (boundaryGrid->grid->_width / int(cellVec.size())) : 
								(boundaryGrid->grid->_height / int(cellVec.size())); 
	
	//uncomment if unsorted vec is passed
	if (is_X_coor) sort (cellVec.begin(), cellVec.end(), compare_cell_x);
	else sort (cellVec.begin(), cellVec.end(), compare_cell_y);
	
	if (!startFromEndofBoundary){
		for (int i = 0; i < int(cellVec.size()); i++){
			if (cellVec[i]->pad) continue;
			if (is_X_coor) cellVec[i]->x = left_offset;
			else cellVec[i]->y = left_offset;
			left_offset += spacing;		
		}
	} else {// sort from end of grid boundary 
		for (int i = int(cellVec.size()) - 1; i >=0; i--){
			if (cellVec[i]->pad) continue;
			if (is_X_coor) cellVec[i]->x = right_offset;
			else cellVec[i]->y = right_offset;
			right_offset -= spacing;		
		}		
	}
	
	
	return;
}

*/

/* 
#DATE2017
*/


/*a function to recive supercells, and insert a uniform space between them*/
void Legalizer::doSuperCellUniformSpacing(vector<vector<Cell*>> &rowVec, 
			map<int, map<int, int>>& row_cell_supCell_map, int horizSpacing){
	
	int offset;
	for (int i=0; i < int(rowVec.size()); i++){
		if (rowVec[i].size() == 0) continue;
		offset = chip->x_offset;
		for (int j=0; j < int(rowVec[i].size())-1; j++){
			if (rowVec[i][j]->level == 0) continue;
			
			int index = rowVec[i][j]->id;
			int next_index = rowVec[i][j+1]->id;
			
			rowVec[i][j]->x = offset;
			offset += rowVec[i][j]->wth;
			
			int supC1 = row_cell_supCell_map[i][index] ;
			int supC2 = row_cell_supCell_map[i][next_index];
			
			// if next cell belongs to another cell group, add space between groups
			if (supC1 != supC2){
				//cout << rowVec[i][j]->name << " is not same supCell " << rowVec[i][j+1]->name << endl;
				offset += horizSpacing;
				
			}
		}
		rowVec[i].back()->x = offset;
		
	}
	

	return;	
}






