#include "initPlacement.h"
#include "Bbox.h"
#include "placement.h"


void initPlacement::doInitialPl(){
	BBox bb = _db->_rowDefs->getChipBbox();
	//BBox sourceBB = BBox(0, 0, bb.getWidth(), bb.getHeight()); 
	BBox sourceBB = BBox(Constants::PAD_HEIGHT, Constants::PAD_HEIGHT, bb.getWidth()+Constants::PAD_HEIGHT, bb.getHeight()+Constants::PAD_HEIGHT);	
			
	Placement pl3(Placement::_TRandom, _db->getNetlist().getNumCells(), sourceBB);	

	//reorders the pads, LL corner is (50,50)
	//There's no need to change the initial bbox, since cg solver puts them inside chip area
	padPl pp(_db, &pl3);
	pp.reOrderPads(  );
 
 
	_db->_spatial.locations = pl3;
	std::cout << "Initial Random Placement:\n";
	std::cout << _db->evalHPWLcost() << std::endl;
	//std::cout << _db->_spatial.locations << "\n";
	
	qcMatrixGen b2b(const_cast<const DB*>(_db), &pl3);
	//ofstream ofsQX("qX.pla");
	//ofstream ofsCX("CX.pla");
	//ofstream ofsQY("qY.pla");
	//ofstream ofsCY("CY.pla");
	
	auto Qx = b2b.getQm(_XX);
	auto Cx = b2b.getCm(_XX);
	auto Qy = b2b.getQm(_YY);
	auto Cy = b2b.getCm(_YY);
	
	//ofsQX << Qx;
	//ofsCX << Cx;
	//ofsQY << Qy;
	//ofsCY << Cy;
	Legalizer lg (_db);
    Placement initPl ((*_db)._spatial.locations);	
	
	for (unsigned l=1; l < maxInitPlIterations; l++){
		std::cout << "Iteration" << l << " ..\n";
		qpSolver solver(_db->getNetlist().getNumCoreCells(), const_cast<Placement*> (&initPl));
		//eigenCGSolver solver((*_db).getNetlist().getNumCoreCells(), const_cast<Placement*> (&initPl));
		
		auto newX = solver.solve(Qx, Cx, Dir (_XX), true);
		auto newY = solver.solve(Qy, Cy, Dir (_YY), true);
		
		std::vector<Point> newPl;
		for (unsigned i=0; i  < newX.size(); i++){
			newPl.push_back(Point(newX[i], newY[i]));
		} 
		for (unsigned i=_db->getNetlist().getNumCoreCells(); 
						i < _db->getNetlist().getNumCells(); i++)
			newPl.push_back(pl3[i]);

		Placement afterSolvePl(newPl);
		_db->_spatial.locations = afterSolvePl;
		std::cout << "HPWL: x = " << std::setw(6) << _db->evalHPWLcostX();
		std::cout << " y = " << std::setw(6) << _db->evalHPWLcostY() ;
		std::cout << " Total = " << std::setw(6) << _db->evalHPWLcost() << "\n\n";
		
		lg . putCellsInBoundRelative(sourceBB);
	    //lg . putCellsInBound(sourceBB);
		
		if (l == maxInitPlIterations-1) continue;
		qcMatrixGen b2bF(const_cast<const DB*>(_db), &afterSolvePl);
		Qx = b2bF.getQm(_XX);
		Cx = b2bF.getCm(_XX);
		Qy = b2bF.getQm(_YY);
		Cy = b2bF.getCm(_YY);
		
		initPl = _db->_spatial.locations;
	}	
	
	//Legalizer lg (_db);
	//lg . putCellsInBound(sourceBB);
	
	//std::cout << _db->_spatial.locations << "\n";
	
	return;
}

