#include "abkcommon.h"
#include "abkversion.h"
#include "DB.h"
#include "RBPlaceFromDB.h"
#include "hgWDimsFromDB.h"
#include "rowIroning.h"
#include "greedyOrientOpt.h"
#include "bookshelf.h"
#include "simAnneal.h"

class DetailedPlacement
{
	private:
		RBPlaceParams *rbParam;
		RowIroningParameters *RIparams;
		RBPlacement *rbplace;
		Model *cp;
		int NumPasses;
	protected:
		
	public:
		void RowIroning();
		void SimAnnealing();
		void Update();
		void removeOverLaps();
		void royjRemOverlaps();
		DetailedPlacement(Model *chip, int Passes);		
		~DetailedPlacement();
};
