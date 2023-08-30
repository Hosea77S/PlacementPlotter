#include "DetailedPlacement.h"

void DetailedPlacement::RowIroning()
{
	cout << " ====== Launching row ironing ... " << endl;
	cout << *RIparams;
	cout <<"Initial Origin-to-Origin WL: "<<rbplace->evalHPWL(false)<<endl;
	cout <<"Initial Pin-to-Pin WL:       "<<rbplace->evalHPWL(true)<<endl;
	Timer RITimer;
	ironRows(*rbplace, *RIparams);
	rbplace->remOverlaps();
	RITimer.stop();
	cout << " Final Pin-to-Pin WL:       "<<rbplace->evalHPWL(true)<<endl;
	cout << "Saving " << "RI.pl" << endl;
    ///rbplace->savePlacement("RI.pl"); 
}

void DetailedPlacement::SimAnnealing()
{
	cout << " ====== Launching sim annealing ... " << endl;
	cout << *RIparams;
	cout <<"Initial Origin-to-Origin WL: "<<rbplace->evalHPWL(false)<<endl;
	cout <<"Initial Pin-to-Pin WL:       "<<rbplace->evalHPWL(true)<<endl; 
	Timer SATimer;  
	SimAnneal SA(*rbplace, true);
	rbplace->remOverlaps();
	SATimer.stop();
	cout << " Final Pin-to-Pin WL:       "<<rbplace->evalHPWL(true)<<endl;
	cout << "Saving " << "SA.pl" << endl;
    ///rbplace->savePlacement("SA.pl"); 
}

void DetailedPlacement::Update()
{
	int i, nodeId;
	const HGraphWDimensions & hgWDims = rbplace->getHGraph();
	const PlacementWOrient & placement = rbplace->getPlacement();
	for(i=0; i<cp->cellList.size(); i++)
	{
		nodeId = hgWDims.getNodeByName(cp->cellList[i]->name.c_str()).getIndex();
		cp->cellList[i]->x = placement[nodeId].x;
		cp->cellList[i]->y = placement[nodeId].y;
	}
}

void DetailedPlacement::removeOverLaps(){
	
	/*
      unsigned i = 0;
	  unsigned legalStrength = 5;
      do
      {
        rbplace.remOverlaps();
		i++;
      } while(i < legalStrength &&
              rbplace->calcOverlapInBBox(rbplace->getPlacement(), rbplace->getBBox(true), false) > 0.);
    rbplace->snapCellsInSites();
    rbplace->royjRemOverlaps(200.0); */
    rbplace->snapCellsInSites();
	rbplace->remOverlaps();
	cout << "\n\n*****************************************\n\n";
}

void DetailedPlacement::royjRemOverlaps(){
    rbplace->snapCellsInSites();
    rbplace->royjRemOverlaps(); 
	cout << "\n\n*****************************************\n\n";
}

DetailedPlacement::DetailedPlacement(Model *chip, int Passes)
{
	NumPasses = Passes;
	rbParam = new RBPlaceParams;
	RIparams = new RowIroningParameters;
	RIparams->numPasses = NumPasses;
	cp = chip;
	rbplace = new RBPlacement(chip);
}

DetailedPlacement::~DetailedPlacement()
{
	if(rbParam) delete rbParam;
	if(RIparams) delete RIparams;
	if(rbplace) delete rbplace;
}
