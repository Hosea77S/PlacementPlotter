#ifndef CLUSTER_H
#define CLUSTER_H

#ifndef COMMON__H
#include "common.h"
#endif

#include "DB.h"


class Cluster {
private:
	DB* _db;
	
public:

    enum clsMethod 
		{ _prePL, _InRow, _postPl_sameLeve, _postPl_adv};

	//~Cluster();
	//Cell* generateSuperCell(string name, int id,  vector<Cell*> &cells, bool changeNetlList);
	Cluster(DB* d): _db(d) {};
	
	void clusterDesign
	(int, std::map<std::string, std::vector <dbCell*>> &, 
	  std::map<std::string, dbCell*> &,
	  std::vector<std::vector<dbCell*>> &newRowVec, 
	  bool changeCellList);
	  
	  
	void unCluster(std::map<std::string, dbCell*> OldCellMap,
	std::map<dbCell*, std::vector<dbCell*>> &NewCellMap);
	
	void updateNetList_AfterClustering
		(std::map<std::string, dbCell*> &cell2SupCellMap);
		
	std::map <std::string, std::vector <dbCell*>> doClustering
	  (int , std::vector<std::vector<dbCell*>> &, 
	   int );
	  
	void TransformNetsToMultiPinNets();
	void doUnClustering(std::map<std::string, dbCell*> &OldCellMap, 
	std::map <std::string, std::vector <dbCell*>> &newCellMap);
	
	void doPrePlClustering(int groupSize, std::map <std::string, dbCell*> &, std::map <std::string, std::vector <dbCell*>>& );
	std::vector<dbCell*> generate_SuperCellList
	  (const std::map<int, std::map<int, std::vector<int> > > &level_supC_cell_map,
	  std::vector<dbCell*> &, std::map<std::string, dbCell*>& , 
	  std::map <std::string, std::vector <dbCell*>>& );

	void addPadsToCLSCellList 
	  ( DB* );											
  void createNewDB 
    (DB* , std::map<unsigned, std::vector<unsigned>>& , 
	  std::vector<std::string> types);
	
  void checkDBConsistency ( const DB* );	
  void unClusterDesign 
    (const DB* , 
     const std::map < unsigned, std::vector<unsigned>>& );

  
};





#endif 