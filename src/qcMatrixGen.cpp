#include "qcMatrixGen.h"


void  qcMatrixGen::isQMconsistent( ){
	isQMconsistent(_XX);
	isQMconsistent(_YY);
}

void qcMatrixGen::isCMconsistent( ){
	isCMconsistent(_XX);
	isCMconsistent(_YY);
}


void qcMatrixGen::isQMconsistent( const Dir& d){
	auto Q = (d == _XX) ? _QmX : _QmY;
	int maxIdx = (*_db).getNetlist().getNumCoreCells();
	
	for (auto& i: Q){
		int idx1 = i.first.first;
		int idx2 = i.first.second;
		double val = i.second;
		myAssert3 ( idx1 >= 0 && idx1 < maxIdx && idx2 >= 0 && idx2 < maxIdx, i, "Invalid index in Q matrix: ", maxIdx );

		if (idx1 == idx2){
			//diagonal element, should be positive
			myAssert3 ( greaterOrEqualDouble ( val, 0.0), idx1 , " Diagonal element is not greaterOrEqual zero: " , val );
		} else {
			myAssert3 ( lessOrEqualDouble ( val, 0.0), idx1 , " non-Diagonal element is not lessOrEqual zero: " , val );
			auto rev = Q.find( std::make_pair ( idx2, idx1) );
			if (rev == Q.end()) 
				myAssert3 (0, idx1, "Inconsitent Q matrix, unsymmetry", idx2);
			
			myAssert3 ( equalDouble (rev->second, val), idx1, "Val is not equal in Q mat: " , idx2 );
		}
	}
	
	return;
}

void  qcMatrixGen::isCMconsistent( const Dir& d){
	auto C = (d == _XX) ? _CmX : _CmY;
	int maxIdx = (*_db).getNetlist().getNumCoreCells();

	for (auto& i: C){
		int idx1 = i.first;
		double val = i.second;
		myAssert3 ( idx1 >= 0 && idx1 < maxIdx , idx1, "Invalid index in C matrix: ", maxIdx );
		myAssert3 ( lessOrEqualDouble ( val, 0.0), idx1 , " value element on C matrix is not lessOrEqual zero: " , val );				
	}
	
	return;
}



std::map<INT_PAIR, double> qcMatrixGen::getQm(Dir d){
	if (d == _XX) return _QmX;
	else return _QmY;
}

std::map<int, double> qcMatrixGen::getCm(Dir d){
	if (d == _XX) return _CmX;
	else return _CmY;	
}


double qcMatrixGen::getDistance(double a, double b){
	if ( lessThanDouble ( fabs(a - b) , (double)minPosDist) )
		return (double)(minAssumDist);
	return fabs ( a - b ) ;
}

void   qcMatrixGen::generateQCMat(){
	generateQCMat(_XX);
	generateQCMat(_YY);
		
	return;
}	

void   qcMatrixGen::generateQCMat(Dir d){

	const dbNetlist& design = (*_db).getNetlist();
	unsigned netCnt = design.getNumNets();
	
	
/* 	itNet itN;
	for (itN = design.netsBegin(); 
				itN != design.netsEnd(); itN++)
 */	
	for (unsigned i=0; i < netCnt; i++)
	{
		const dbNet& curNet = design.getNetByIdx(i);
		//std::cout << "\n\n***********************\n\n";
		//std::cout << "Processing net: " << curNet.getName() << "\n";
		unsigned cellCnt = curNet.getNumCells();
		//curNet.sortCellsByIndex();
		if (cellCnt < 2) continue;
		if (cellCnt == 2) 
		for (unsigned i=0; i < cellCnt; i++)
			for (unsigned j=i+1; j < cellCnt; j++){
				
				const dbCell& c1 = curNet.getCellByIdx(i);
				const dbCell& c2 = curNet.getCellByIdx(j);
				unsigned idx1 = c1.getIndex();
				unsigned idx2 = c2.getIndex();
				//std::cout << "\tCell: " << c1 << "\t\tpos: " << (*_pl)[idx1] << "\n";
				//std::cout << "\tCell: " << c2 << "\t\tpos: " << (*_pl)[idx2] << "\n";
				
				double dist = 0.0;
				if (d == _XX)  
				dist = getDistance ( (*_pl)[idx1].x , (*_pl)[idx2].x );
				else  
				dist = getDistance ( (*_pl)[idx1].y , (*_pl)[idx2].y );
				
				//std::cout << "Dist: " << dist << "\n\n"; 
				
				//added by SOHEIL 
				dist = pow (dist, POW);
				
				myAssert ( (dist) > DBL_EPSILON, "dist between two cells is 0.0");
				
				if (c1.isFixed() || c2.isFixed()){
					handleFixMov(d, c1, c2, dist);
				} else {
					handleMovMov(d, c1, c2, dist);
				}
				
			}
		else //TODO handle more than 2 nets
		{
			myAssert (0, "Net Degree more than 2 is not handled.\n");
		}
	}
	
	
}	


void   
qcMatrixGen::handleMovMov
	( Dir& d, const dbCell& c1, const dbCell& c2, double dist )
{
	unsigned idx1 = c1.getIndex();
	unsigned idx2 = c2.getIndex();
	
	//myAssert3 (idx1 < idx2, idx1, " should be less than ", idx2);
	
	
	double recip = 1 / dist;
	INT_PAIR qIdx1_2 = std::make_pair(idx1, idx2);
	INT_PAIR qIdx2_1 = std::make_pair(idx2, idx1);
	INT_PAIR qIdx1 = std::make_pair (idx1, idx1);
	INT_PAIR qIdx2 = std::make_pair (idx2, idx2);
	
	addToQm (d, qIdx1, recip);
	addToQm (d, qIdx2, recip);
	addToQm (d, qIdx1_2, -1.0 * recip);
	addToQm (d, qIdx2_1, -1.0 * recip);	
	
	//std::cout << "Added " << recip << "to the qIdx: " <<  qIdx << std::endl;
	return ;
}

void 
qcMatrixGen::addToQm ( Dir& d, INT_PAIR qIdx, double weight ) {

	if (d == _XX) {
		if (_QmX.find(qIdx) == _QmX.end())
			_QmX [qIdx] = weight;
		else 
			_QmX [qIdx] += weight;
	} else {
		if (_QmY.find(qIdx) == _QmY.end())
			_QmY [qIdx] = weight;
		else 
			_QmY [qIdx] += weight;		
	}

	return;
}


void 
qcMatrixGen::addToCm ( Dir& d, unsigned cIdx, double weight ) 
{
	if (d == _XX) {
		if (_CmX.find(cIdx) == _CmX.end() )
			_CmX[cIdx] = weight;
		else 
			_CmX[cIdx] += weight;
		
	} else {
		if ( _CmY.find(cIdx) == _CmY.end() )
			_CmY[cIdx] = weight;
		else 
			_CmY[cIdx] += weight;		
	}
	
	return ;
}

void   
qcMatrixGen::handleFixMov
			( Dir& d, const dbCell& c1, const dbCell& c2, double dist ) 
{
	//if j is fixed, w is added to Qii, -w * xj is added to ci
	unsigned idx1 = c1.getIndex();
	unsigned idx2 = c2.getIndex();
	double recip = 1 / dist;
	if (c1.isFixed() && c2.isFixed()) return;
	if (c1.isFixed()) { //c1 is fixed
		INT_PAIR qIdx = std::make_pair(idx2, idx2);
		addToQm (d, qIdx, recip);
		double w = (d == _XX) ? -1.0*(*_pl)[idx1].x*recip :
								-1.0*(*_pl)[idx1].y*recip ;
		addToCm (d, idx2, w);
		
	} else { //c2 is fixed
		INT_PAIR qIdx = std::make_pair(idx1, idx1);
		addToQm (d, qIdx, recip);
		double w = (d == _XX) ? -1.0*(*_pl)[idx2].x*recip :
								-1.0*(*_pl)[idx2].y*recip ;
		
		addToCm (d, idx1, w);
		
	}
	
	return;
}
