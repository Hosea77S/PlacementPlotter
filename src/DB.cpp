#include "DB.h"
//#include "dbNetlist.h"

DB::~DB() {}

DB::Parameters::Parameters(): fixPlacedPads(true)
{}



DB::DB(Parameters params):_params(params)
{
	//postProcessor();
}


double DB::evalHPWLcost(unsigned threshold, bool IONetsOnly) const
{
    return 
     _design.evalHalfPerimCost(_spatial.locations, threshold, IONetsOnly);
}

double DB::evalHPWLcostX(unsigned threshold, bool IONetsOnly) const
{
    return 
     _design.evalHalfPerimCostX(_spatial.locations, threshold, IONetsOnly);
}

double DB::evalHPWLcostY(unsigned threshold, bool IONetsOnly) const
{
    return 
     _design.evalHalfPerimCostY(_spatial.locations, threshold, IONetsOnly);
}

double DB::evalWHPWLcost(unsigned threshold, bool IONetsOnly) const
{
    return 
    _design.evalWHalfPerimCost(_spatial.locations, threshold, IONetsOnly);
}


/* const DB& operator>>(const DB& db,Placement& pl)
{  
  pl = db.spatial.locations;
  return db;
}

const DB& operator>>(const DB& db, vector<Orient>& ori)
{ 
  ori = db.spatial.orientations; 
  return db;
}

DB& operator<<(DB& db, const Placement& pl)
{ 
  db.spatial.locations=pl; 
  std::fill(db.spatial.locationValid.begin(),db.spatial.locationValid.end(),true);
  return db;
}

DB& operator<<(DB& db, const vector<Orient>& ori)
{ 
  db.spatial.orientations=ori; 
  return db;
}
 */
 
 

void DB::PrintBenchmarkStatus(std::ostream& os){
	
	auto rowDefs = this->_rowDefs;
	
	os << "\n\n" << std::endl;
	os << "Total Nodes    : " << this->_design._cellLib.size() << std::endl;
	os << "Movable Nodes  : " << this->_design.getNumCoreCells() << "\t\t\t("; 
	os <<  this->calculateTotalCellArea() << ")" << std::endl;
	os << "#SC Nodes  : " << _design.getNumSCs()	<<
	"\t\t\t#CC Nodes: " << _design.getNumCCs() << std::endl;
	os << "I/O Terminals  : " << this->_design.getNumAllPads() << std::endl;
	os << "Nets           : " << this->_design.getNumNets() ;
	os << "\t\t\tPins           : " << this->_design._pinLib.size() << std::endl;
	os << "Rows           : " << rowDefs->getRowCnt();
	os << "\t\t\t\tRow Height     : " << rowDefs->getRowHeight()<< std::endl;
	os << "Layout Area    : " << rowDefs->getChipArea() ; 
	os << "\t\t\t(X span:" << rowDefs->getXOffset() << "-" << rowDefs->getChipXEnd(); 
	os <<", Y span:" << rowDefs->getYOffset() << "-" << rowDefs->getChipYEnd(); 
	os << "), Aspect Ratio (width/height): " << rowDefs->getChipWidth() / rowDefs->getChipHeight()  << std::endl;
	os << "Design Density : " << this->calculateTotalCellArea() / rowDefs->getChipArea() << std::endl;
	
/* 	os << "maxIPiter      : " << 	this->get_maxIPiter() << "\t\t\t\tmaxGPIter      : " << this->get_maxGPiter() << std::endl;
	os << "IP update ratio: " << 	this->get_IP_update_ratio() << "\t\t\t\tGP update ratio: " <<  this->get_gp_update_ratio() << std::endl;
	os << "Init grid Size : " <<  this->get_gridSize() << std::endl;
 */	
	os << "Width          : " << rowDefs->getChipWidth(); 
	os << "\t\t\tHeight          : " << rowDefs->getChipHeight() << std::endl;
	os << "X offset       : " << rowDefs->getXOffset()   << "\t\t\tY offset        : " << rowDefs->getYOffset() <<  std::endl;
	os << "Max Cell Level : " << this->getMaxLevel() << std::endl << std::endl; 	
	
/* 	os << "maxCutLevel is : " << 		this->maxCutLevel << std::endl;
	os << "overfill_ratio is : " << 	this->overfill_ratio << std::endl;
	os << "maxBFSStage is : " << 		this->maxBFSStage << std::endl;
 */	
	
	
	os << "\n\n" << std::endl;

	
}

double DB::getAvgCellWidth () const {
	return calculateTotalCellArea() / 
			_rowDefs->getRowHeight() / 
			getNetlist().getNumCoreCells() ;	
}


double  DB::calculateTotalCellArea() const {
	double totalArea = 0.0;
	for (auto &i: _design._cellLib){
		totalArea += (i->_width * i->_height);
	}
	
	return totalArea;
}

double  DB::getTotalCoreCellWidth() const {
	double totalArea = 0.0;
	for (auto &i: _design._cellLib){
        if (i->isCore())		
		totalArea += (i->_width);
	}	
	return totalArea;
}

double  DB::getTotalCoreCellHeight() const {
	double totalArea = 0.0;
	for (auto &i: _design._cellLib){
        if (i->isCore())				
		totalArea += (i->_height);
	}	
	return totalArea;
}



int  DB::getMaxLevel(){
	int maxLevel = 0;
	for (auto &i: _design._cellLib){
		int curL = i->getLevel();
		maxLevel = std::max(curL, maxLevel);
	}
	
	return maxLevel;
	
}



double DB::evalHPWLcost(Placement& pl, unsigned threshold, bool IONetsOnly) const
{
     return  _design.evalHalfPerimCost(pl,
                              threshold, 
							  IONetsOnly);
}

double DB::evalWHPWLcost(Placement& pl, unsigned threshold, bool IONetsOnly) const
{
    return _design.evalWHalfPerimCost(pl,
                              threshold, 
							  IONetsOnly);
}


class CompareNetsByHPWL    //comp. class for sorting the netlist's nets
{
	
const DB* _db;	
const Placement* _placement;
public:
   CompareNetsByHPWL(const DB* db, const Placement* pl)
      :_db(db), _placement(pl)
      {}
	
  bool operator()( int n1, int n2 ) const
    { 
	
	//std:: cout << "Comparing Nets " << n1 << " with " << n2 << "\n"; 
	
	//added this to fix a wierd bug that generated n1 value
	//out of _netLib size 	
	if ( n1 < 0 || n1 >= (int)(*_db).getNetlist().getNumNets() )
	{
		myWarn3 ( 0, n1, " out of bound of nets ", 
			(*_db).getNetlist().getNumNets());
		return false;
	}
		
	if ( n2 < 0 || n2 >= (int)(*_db).getNetlist().getNumNets() ) 
	{
		myWarn3 ( 0, n2, " out of bound of nets ", 
			(*_db).getNetlist().getNumNets());

		return false;
	}
	
	if ( equalDouble(
			(*_db).getNetlist().evalHalfPerimCost(n1, (*_placement), false), 
			(*_db).getNetlist().evalHalfPerimCost(n2, (*_placement), false)) )
		return ( n1 < n2);	
			
	return  greaterOrEqualDouble(
			(*_db).getNetlist().evalHalfPerimCost(n1, (*_placement), false), 
			(*_db).getNetlist().evalHalfPerimCost(n2, (*_placement), false));
	}  
};




std::pair<int, double> findCriticalPath
 (const DB* db, bool print, std::ostream&os )
{
	Placement finalPl ( (*db)._spatial.locations);
	std::vector<int> netIdcs;
	//the following does not work if we delete the single pin nets, as indices
	//will not be continuos anymore, e.g., 0,1,2,5,6,...
	//for (auto itN = _design.netsBegin(); 
	//		itN != _design.netsEnd();
	//		itN++)
	//	netIdcs.push_back( (*itN) );
	
    //std::cout << "\n\nNets           : " << _design.getNumNets() ;
	
	for (unsigned i=0; 
			i < (*db).getNetlist().getNumNets(); i++)					
		netIdcs.push_back( (int) i );
				
	
	
	if (netIdcs.size() == 0) return std::make_pair (-1, 0.0);
	std::sort( netIdcs.begin(), netIdcs.end(), 
	  CompareNetsByHPWL(db, &finalPl) );
	
	double hpwl = (*db).getNetlist().evalHalfPerimCost( netIdcs.front(), finalPl, false );
	
	int vSize = std::min(5, (int)netIdcs.size());
	
	if (!print)
	  return std::make_pair (netIdcs.front(), hpwl); 
		
	os << "\n\nTop " << vSize << " longest wires: \n";
	for ( int i=0; i < vSize; i++ )
		os << "Net #" << netIdcs.at(i) <<
			" name: " << (*db).getNetlist().getNetByIdx( netIdcs.at(i) ) .getName()
			<< " type: " <<
			std::string((*db).getNetlist().getNetByIdx( netIdcs.at(i) ) .getType() )
		<< " HPWL = " << 
			(*db).getNetlist().evalHalfPerimCost( netIdcs.at(i), finalPl, false ) << "\n";

	return std::make_pair (netIdcs.front(), hpwl); 
}


std::vector < std::pair<int, double> >   DB::acquireSameHPWLLNet()
{
	Placement finalPl ( _spatial.locations);
	std::vector<int> netIdcs;
	
	std::cout << "Function DB::acquireSameHPWLLNet() is Called\n";

	std::vector < std::pair<int, double> > sameNet;
	
	for (unsigned i=0; i < _design.getNumNets(); i++) netIdcs.push_back( (int) i );
				
	
	
	if (netIdcs.size() == 0) 
	{ 
	sameNet.push_back( std::make_pair(-1, 0.0) );
	return sameNet;
	}

	std::sort( netIdcs.begin(), netIdcs.end(), 
	  CompareNetsByHPWL(const_cast<const DB*>(this), &finalPl) );   //sort with the HPWL
	
	double hpwl = _design.evalHalfPerimCost( netIdcs.front(), finalPl, false );
	

        std::cout << "Worst Netid "<< netIdcs.front() << " HPWL= " << hpwl <<"\n";

	sameNet.push_back( std::make_pair(netIdcs.front(), hpwl) );  //putting the worst HPWL



	double cad_HPWL=0;
	 
		
	//std::cout << "\n\nTop " << vSize << " longest wires: \n"; 
	for ( unsigned i=1; i < netIdcs.size()-1 ; i++ ){ //i=1 because starting from the 2nd net


	  cad_HPWL= _design.evalHalfPerimCost( netIdcs.at(i), finalPl, false );
	  std::cout << "Next Worst Netid "<< netIdcs.at(i) << " HPWL= " << cad_HPWL <<"\n";

	  if( (int)hpwl == (int)cad_HPWL ){
	   sameNet.push_back( std::make_pair (netIdcs.at(i), cad_HPWL) );
		std:: cout << "Net #" << netIdcs.at(i) <<" type: " << std::string( _design.getNetByIdx( netIdcs.at(i) ) .getType() ) << " HPWL = " << 
		cad_HPWL << "HAS the SAME HPWL with " << netIdcs.front() << "\n";
	  }
	  else break;
	}


	std::cout << "The number of Same HPWL of the NET= " << sameNet.size() <<"\n\n";	
	return sameNet; 
}




void DB::printAllNetHPWL() //yusuke
{
	Placement finalPl ( _spatial.locations);
	std::vector<int> netIdcs;

	
	for (unsigned i=0; 
			i < _design.getNumNets(); i++)					
		netIdcs.push_back( (int) i );
				
	
	
	if (netIdcs.size() == 0) return;

	std::sort( netIdcs.begin(), netIdcs.end(), 
	  CompareNetsByHPWL(const_cast<const DB*>(this), &finalPl) );
	
	
	
	
	
	
		
	std::cout << "\n\nTop " << netIdcs.size() << " longest wires: \n"; //Placement finalPl ( _spatial.locations);
	for ( unsigned i=0; i < netIdcs.size(); i++ ){//yusuketest
		std:: cout  << "Net " << netIdcs.at(i) << " = " <<
			_design.evalHalfPerimCost( netIdcs.at(i), finalPl, false ) << "\n";

	}
	return;

}




unsigned DB::findCellIdxByName( std::string name ) const
{
  for (auto cIt = getNetlist().cellsBegin();
		   cIt != getNetlist().cellsEnd();
		   cIt++)
   {
	 auto orgName = (*cIt)->getName();
     if ( orgName.find(name) != std::string::npos ) 
	   return (*cIt)->getIndex();	 
   }
   
   myWarn2 (0, "no cell found with subname: ", name);   
   return -1;	
}
