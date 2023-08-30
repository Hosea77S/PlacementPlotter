//==============================================================================//
//                                      qPlace                                  //
//                                                                              //
//               Written by Soheil Nazar Shahsavani and Massoud Pedram          //
//      SPORT Lab, University of Southern California, Los Angeles, CA 90089     //
//                           http://sportlab.usc.edu/                           //
//                     ColdFlux Project, http://coldflux.usc.edu                //
//                                                                              //
//  For licensing, please refer to the LICENSE file.                            //
//                                                                              //
// The development is supported in part by IARPA SuperTools program             // 
// via grant W911NF-17-1-0120.                                                  // 
//                                                                              // 
//==============================================================================//

#ifndef GRAPH_H
#define GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>

#include <iostream>
#include <fstream>
#include <sstream>


#ifndef COMMON__H
#include "common.h"
#endif

#include "DB.h"
#include "gridMapper.h"

//#include "Graph/graphParser.h"
#include "hMetis.h"
//#include "HMetis/hMetisParser.h"

#define UNIT_WEIGHT 1	
#define MIN_GP_WEIGHT 5
#define MAX_GP_WEIGHT 45
//#define INF_WEIGHT 10000
#define INF_WEIGHT 1000

#define WIDTH_NORM 10	
#define OPTION 1


#define debug 0

using namespace boost;

 /* define the graph type
	  listS: selects the STL list container to store 
			 the OutEdge list
	  vecS: selects the STL vector container to store 
			the vertices
	  directedS: selects directed edges
*/

/* struct VertexProperties{
	std::string name;
	std::string level;
	bool isPad;
};

struct EdgeProperties{
	float weight;
	std::string netName;
};


typedef boost::adjacency_list<  boost::listS, 
								boost::vecS, 
								boost::undirectedS,
								VertexProperties, 
								EdgeProperties > undirGraph; */


typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;

								
typedef boost::adjacency_list<  boost::listS, 
								boost::vecS, 
								boost::undirectedS, 
								boost::no_property,
								EdgeWeightProperty > undirGraph;							
								
typedef undirGraph::vertex_descriptor Vertex;
typedef undirGraph::edge_descriptor Edge;

class Graph 
{
	private:
		DB* _db;
		const Placement* _pl;
		undirGraph _gr;
		std::map<unsigned, std::vector<dbCell*>> level2Cell;
		
		void buildGraph();
		void buildLevel2CellMap();
		std::vector<int> findAdjdbCells (dbCell* );
		std::vector<unsigned> findAdjdbCells (unsigned idx );
		void write_to_file (const undirGraph &g, std::string outFileName, int l);
		undirGraph createLevelSubGraph(int level);
		void print_vertices (const undirGraph& g);
		void removeSingleVertices(undirGraph& g);
		void write_to_file_mine (const undirGraph &g, std::string outFileName, int l);
		void addWeightToNeighbors(undirGraph &g, int currLevel);
		void addEdgeWeight(float extraWeight, Vertex &u, Vertex& v, undirGraph& g );
		
		void print_edge_weights(undirGraph& g);
		undirGraph reduce_to_levelGraph(undirGraph& g, int currLevel);
		void is_dbCellID_valid(int id);
		void read_from_hMetis();
		int run_hMetis(int Nparts, std::string inFileName);
		std::map<int, int> read_from_hMetis(int Nparts, std::string filename);
		std::map<int, std::vector<int> > generate_SuperdbCells
								(const std::map<int, int> &cell_index_Map, const std::map<int, int> &cell_cluster_number);

		void contract_vertices(Vertex b, Vertex a, undirGraph& g);
		std::map<int, int> doRandomPartAssignment(int currLevel, int groupSize);
		void doPartitionBalancing
		(std::map<unsigned, std::vector<unsigned> >  &, 
		  int groupSize);
		
		int get_LevelDiff(int a, int b);
		std::vector<std::vector< int> >  find_levelOrderNeighbors(int rootID, int maxSearchLevel, undirGraph& g);
		void print_NeighborsVec(const std::vector< std::vector< int> >& );
		bool areConnected (int a, int b, undirGraph& g);
		std::vector <int > findParentNode(int baseNodeID, bool parent, undirGraph& g);
		std::pair<int, int> findMinMaxCoordinates(bool is_X_coordinate, int currLevel);
		void addWeightBasedOnPlacement(undirGraph& g, int currLevel);
		void addWeightBasedOnPlacementTodbCellsInSameRow(std::vector<dbCell*> &curRow);
		
		undirGraph reduce_to_RowGraph(std::vector<dbCell*> &cellRow);
		void placeSupdbCellsBasedOnCOM(std::map<int, std::vector<int> > &cur);
		
public:
  bool areConnected (int a, int b);
  std::map< unsigned, std::vector<unsigned>>  
    genLevelBasedSupCells(int groupSize);
  
  void print_name2dbCellMap();
  //void print_GraphStatus(undirGraph& g);
  int get_TotalEdges();
  
  int get_TotalVertices(undirGraph& g);
  //int get_TotalConnectedVertices(undirGraph& g);
  void print_clusteredGraph_status
    (const std::map< int, std::map<unsigned , std::vector<unsigned> > > &);
  void testGraph();
  
  std::map<int, std::map<int , std::vector<int>>> doSingleRowGraphClustering(std::vector<std::vector<dbCell*>>& cellRow);
  
  //Newly added funcs
  Graph(DB* , const Placement*);
  Graph(DB* , const Placement* , undirGraph& );
  
  std::map < unsigned, std::vector<unsigned> >
    genOptSuperCells (std::vector<unsigned>, int );

  std::map< unsigned, std::vector<unsigned>> 
    genAllOptSupCells ( BBox&, int, int);
	
  undirGraph getUndirGraph () const { return _gr ; }
  
  void addWeightBasedOnPlacement ( std::vector<unsigned> );
  float getWeightBasedOnPlacement
    (unsigned,unsigned,Dir,double,double);
	
  undirGraph reduceGraph(std::vector<unsigned> );
  void addEdgeWeight(float extraWeight, Vertex &u, Vertex& v);
  void setEdgeWeight ( float , Vertex &, Vertex&) ;		
  Vertex getVertex ( unsigned i)
  {
	  Vertex v = vertex ( i, _gr );
	  return v;
  }

  std::map<unsigned, std::vector<unsigned> > genSup2CellMap
   (const std::map<int, int> &, const std::map<int, int> &);
  
		
  ~Graph() {} ;
};



class hMetisParser {

private:
  const DB* _db;
  const undirGraph _graph;

public:

  hMetisParser ( const DB* db, const undirGraph& g ): 
	_db(db), _graph (g) {}
  
  std::map<int, int> write_to_hMetis
	(std::map<unsigned, std::vector<dbCell*>>&, 
		int , std::string );
		
  std::map<int, int> read_from_hMetis(int , std::string );    
  std::map<int, int> write_to_hMetis
	( std::vector<unsigned> , std::string );
  	
	
};

class graphParser
{
private:
  const DB* _db;
  const Graph* _graph;
  undirGraph _undirG;

public:
  graphParser ( const DB* db, const Graph* g ): 
	_db(db), _graph (g) {
		_undirG = (*_graph).getUndirGraph();
	}

  void write_to_file_mine (std::string , int currLevel = 0);
  void write_to_file (std::string , int level = 0, bool draw = false);
    
	
	
};







#endif 
