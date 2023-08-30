#include "Graph.h"


typename graph_traits<undirGraph>::out_edge_iterator out_it, out_it_end;
typename graph_traits<undirGraph>::in_edge_iterator in_it, in_it_end;
typename graph_traits< undirGraph >::edge_iterator e_it, e_end;

typename graph_traits<undirGraph>::vertex_descriptor currVertex, nextVertex;
typedef property_map<undirGraph, vertex_index_t>::type VertexMap;
typename graph_traits<undirGraph>::vertex_iterator v_it, v_it_end, v_it_2, v_it_2_end, next_it;



int Graph::get_TotalEdges(){
	
	boost::graph_traits<undirGraph>::edges_size_type  
			totalEdgeCount = num_edges( _gr );
	return totalEdgeCount;	
}


int get_TotalEdges(const undirGraph& g){
	
	boost::graph_traits<undirGraph>::edges_size_type  
			totalEdgeCount = num_edges(g);
	return totalEdgeCount;	
}


int get_TotalConnectedVertices(undirGraph& g){
	int numNodes = 0;
	
	for (tie(v_it, v_it_end) = vertices(g); v_it != v_it_end; ++v_it){
		Vertex u = vertex(*v_it, g);
		tie(out_it, out_it_end) = out_edges(u, g);
		if (out_it != out_it_end)
			numNodes++;
	}

	return numNodes;
}

int get_TotalVertices(undirGraph& g){
	
	boost::graph_traits<undirGraph>::vertices_size_type 
			totalNodeCount = num_vertices(g);			
	return totalNodeCount;
	
}

void print_GraphStatus(undirGraph& g)
{	
	std::cout << "\n\nGraph Status" << std::endl;
	std::cout << "\tTotal Number of Vertices           : \t\t" << get_TotalVertices(g) << std::endl;
	std::cout << "\tTotal Number of Connected Vertices : \t\t" << get_TotalConnectedVertices(g) << std::endl;
	std::cout << "\tTotal Number of Edges              : \t\t" << get_TotalEdges(g)    << std::endl;
	std::cout << std::endl << std::endl;
	return;
}


Graph::Graph(DB* chip, const Placement* pl) {
	this->_db = chip;
	this->_pl = pl;
	this->buildGraph();
	this->buildLevel2CellMap();
}

Graph::Graph(DB* chip, const Placement* pl, undirGraph& gr):
 _db(chip), _pl (pl), _gr (gr) {
	 	this->buildLevel2CellMap();
 }
 

void Graph::buildLevel2CellMap(){
	level2Cell = (*_db).getNetlist().getLevel2CellMap();
	
	return;
}

void Graph::buildGraph(){
	undirGraph g(int((*_db).getNetlist().getNumCells() ));
/* 	typename property_map<undirGraph, edge_weight_t>::type 
		weight = get(edge_weight, g); */
		
	for (itNet itN = (*_db).getNetlist().netsBegin();
  		 itN != (*_db).getNetlist().netsEnd();
		 itN ++ )
	{
		
		for (unsigned i=0; i < (*itN)->getNumCells()-1; i++)
		{
			add_edge((*itN)->getCellByIdx(i).getIndex(), 
				(*itN)->getCellByIdx(i+1).getIndex(), EdgeWeightProperty(UNIT_WEIGHT), g);				
		}
	}
	
	this->_gr = g;
	//boost::print_graph(_gr);
	//this->print_vertices(gr);
	print_GraphStatus(_gr);
	
	return;
}




void graphParser::write_to_file_mine 
 (std::string outFileName, int currLevel)
{
	std::ofstream fout(outFileName);
	
	fout << "graph G {\n" ;
	
	for (tie(v_it, v_it_end) = vertices((_undirG)); v_it != v_it_end; ++v_it){
		Vertex u = vertex(*v_it, _undirG);
		tie(out_it, out_it_end) = out_edges(u, _undirG);
		if (out_it != out_it_end){
			std::string name = (*_db).getNetlist().getCellByIdx(*v_it).getName();
			
			int llevel = (*_db).getNetlist().getCellByIdx(*v_it).getLevel();
			name.erase(name.begin()+4, name.end());
			name = name + "_" + std::to_string(*v_it) + "_L" + std::to_string( llevel );
			
			if (llevel == currLevel)
				fout << *v_it <<  "[label="<< name << 
						" " << "color=blue" << "];" << std::endl;
			else
				fout << *v_it <<  "[label="<< name << "];" << std::endl;
			
		}
	}	

	
	for (tie(v_it, v_it_end) = vertices(_undirG); v_it != v_it_end; ++v_it){
		Vertex u = vertex(*v_it, _undirG);
		for (tie(out_it, out_it_end) = out_edges(u, _undirG); out_it != out_it_end; ++out_it){
			auto currSource = source ( *out_it, _undirG );
			auto currTarget = target ( *out_it, _undirG );
			std::pair<Edge, bool> ed = boost::edge(currSource, currTarget, _undirG);
			if (currSource < currTarget){
				float weight = get(edge_weight_t(), _undirG, ed.first);
				fout << currSource << "--" << currTarget << "[label=" <<  weight << "] ;" << std::endl;
			}
		}
	}

	fout << "}" << std::endl;
	

	return;

}



void graphParser::write_to_file 
  (std::string outFileName, int level, bool draw)
{
	
	//From http://stackoverflow.com/questions/7931164/graph-visualization-boost-graph
	std::ofstream fout(outFileName);
	//write_graphviz(fout, _undirG);
	write_to_file_mine(outFileName, level);
	
	//don't draw the png file, just leave the graph file
	if ( !draw ) return;
	
	std::string command = "dot -Tpng " + outFileName + " > " + outFileName + ".png";
	system(command.c_str());
	//cout << "\tCalling command " << command << endl;
	command = "rm -r " + outFileName;
	system(command.c_str());
	//cout << "\tCalling command " << command << endl<< endl<< endl;
	std::cout << "\tSaving " << outFileName << " image" << std::endl<< std::endl;
	
	return;
}


std::map<int, int> hMetisParser::read_from_hMetis
  (int Nparts, std::string filename)
{
	std::map<int, int> vertex_partition_mapping;

	char comment[1000];
	std::string hmetisResultFileName = filename + ".part." + std::to_string(Nparts);
	std::ifstream fin;
	fin.open(hmetisResultFileName);
	if (!fin)
	{
		std::cerr << "(E) Error opening input file: "
			<< hmetisResultFileName 
			<< std::endl;
			hmetisResultFileName = filename + ".part." + to_string(Nparts - 1);
			fin.open(hmetisResultFileName);
			
			myAssert2 ( !fin, "(E) Error opening input file: ", hmetisResultFileName );
	}

	std::cout << "\tReading from file: " << hmetisResultFileName << std::endl;

	int vertexID = 1;
	//fin.getline(comment, 256);
	while (fin.getline(comment, 1000))
	{
		if (comment[0] == '#')
			continue;
		if (strlen(comment) == 0)
			continue;
		int clusterNum;
		std::istringstream spec_in(comment);

		spec_in >> clusterNum ;
		myAssert2( clusterNum >= 0, clusterNum, 
			" clusterNum is not >= 0");
		vertex_partition_mapping[vertexID] = clusterNum;
		vertexID++;
	}

	return vertex_partition_mapping;
}


std::map<int, int> hMetisParser::write_to_hMetis
	(std::vector<unsigned> cells, std::string outFileName)
{
	
	std::cout << "\tWriting to hMetis input file: \t" << outFileName << std::endl;
	std::ofstream fout;
	fout.open(outFileName);

	if ( !fout )
	myAssert2 ( 0, "(E) Error opening output file: ", outFileName );
	
	//int numNodes = get_TotalConnectedVertices(g); //This will only add connected cells of this level, not all
	int numNodes = cells.size();
	int numEdges = get_TotalEdges(_graph);
	//Option : 
	//0 no edge Weight, no vertex Weight
	//1 edge Weight only
	//10 vertex Weight only
	//11 edge Weight and vertex Weight
	int option = OPTION; 
	
	fout << "%graph file, written by Soheil Nazar Shahsavani : " << std::endl;
	fout << numEdges << " " << numNodes << " " << option << std::endl;
	//fout << endl << endl;
	
	//maps cellIDs to vertices which are used as input to hMetis
	std::map<int, int> cell_vertex_map;
	int id=1; 
	
	
	//vertex numbers start from 1
	//only considers vertices that have at least a connection
	for (tie(v_it, v_it_end) = vertices(_graph); 
			v_it != v_it_end; ++v_it)
	{
		Vertex u = vertex(*v_it, _graph);
		tie(out_it, out_it_end) = out_edges(u, _graph);
		if (out_it != out_it_end){
			int cellID = *v_it;
			(*_db).getNetlist().isCellIdValid(cellID);
			cell_vertex_map[cellID] = id;
			id++;
		}
	}	
	
	
	//first writing all edges 
	for (tie(v_it, v_it_end) = vertices(_graph); 
			v_it != v_it_end; ++v_it)
	{
		Vertex u = vertex(*v_it, _graph);
		for (tie(out_it, out_it_end) = out_edges(u, _graph);
			 out_it != out_it_end; ++out_it)
		{
			auto currSource = source ( *out_it, _graph );
			auto currTarget = target ( *out_it, _graph );
			std::pair<Edge, bool> ed = boost::edge(currSource, currTarget, _graph);
			if (currSource < currTarget){
				float weight = get(edge_weight_t(), _graph, ed.first);
				fout << weight << " " << cell_vertex_map[currSource] << " " << cell_vertex_map[currTarget] << std::endl;
			}
		}
	}

	
	//Now writing vertex edges to outfile
	for (tie(v_it, v_it_end) = vertices(_graph); v_it != v_it_end; ++v_it){
		Vertex u = vertex(*v_it, _graph);
		tie(out_it, out_it_end) = out_edges(u, _graph);
		if (out_it != out_it_end){
			int cellID = *v_it;
			(*_db).getNetlist().isCellIdValid(cellID);
			int width = (*_db).getNetlist().getCellByIdx(cellID).getWidth() / (WIDTH_NORM);
			fout << width <<  " " << std::endl;			
		}
	}	
	

	int prevCount = id;
	//adding unconnected vertices to graph input file
	auto thisLevelCells = cells;
	for (int i=0; i < int (thisLevelCells.size()); i++){
		int cellID = (*_db).getNetlist().getCellByIdx(thisLevelCells.at(i)).getIndex();
		(*_db).getNetlist().isCellIdValid(cellID);
		auto it = cell_vertex_map.find(cellID);
		
		if (it != cell_vertex_map.end()) //this cell has already been written to graph file, skipping
			continue;
		
		std::cout << "\t\t\tUnconncted Cell is " << (*_db).getNetlist().getCellByIdx(cellID).getName() << std::endl;
		int width = (*_db).getNetlist().getCellByIdx(cellID).getWidth() / (WIDTH_NORM);
		fout << width <<  " " << std::endl;
		cell_vertex_map[cellID] = id;
		id++;
	}
	
	if (id - prevCount > 0)
	std::cout << "\t\t\ttotal # of " << (id - prevCount) << " unconnected cell(s) have been added to hMetis input file" << std::endl;
	
	fout.close();
	
	return cell_vertex_map;
}

std::map<int, int> 
 Graph::doRandomPartAssignment(int currLevel, int groupSize)
{
	std::map<int, int> vertex_partition_mapping;
	int part_index = 0;
	int v_index=1;
	int totalVertexCount = int (this->level2Cell.at(currLevel).size());
	int temp = 0;
	while(v_index <= totalVertexCount){
		if (temp < groupSize){
			//cerr << "assigning vertex " << v_index << " to part " << part_index << endl;
			vertex_partition_mapping[v_index] = part_index;
			std::cout << 
			temp++;
			v_index++;
		}
		else {
			temp = 0;
			part_index++;
		}
	}
	
	return vertex_partition_mapping;
}





//generates supercells, and returns a map of cells to supercells
//among the given cells to be clustered, finds the supercells
//in which none of the cells have direct connection to each other
// Trick is that sets the weight of direct connections to inf,
//then does partitioning
std::map < unsigned, std::vector<unsigned> >
  Graph::genOptSuperCells 
  (std::vector<unsigned> cellIndices, int gSize)
{
  
  //# of cells should be larger than gSize,
  //otherwise, may end up in a supercell with connections 
  //between their cells ( timing violation )
  myAssert3 ( int(cellIndices.size()) > gSize, 
			cellIndices.size(), " is not > ", gSize ); 
  
  //creating a duplicate graph to reduce and partition
  Graph g2 ( _db, _pl );
  
  g2.addWeightBasedOnPlacement ( cellIndices );      
  auto reducedGraph = g2.reduceGraph ( cellIndices );
  
  //reduced graph
  Graph red ( _db, _pl, reducedGraph);
  
  //if cells are connected and are of consecutive logic levels
  //second condition is to avoid putting neg weight on splitters
  for ( unsigned i=0; i < cellIndices.size(); i++)
  	for ( unsigned j=i+1; j < cellIndices.size(); j++)
  	  if ( areConnected ( cellIndices.at(i), cellIndices.at(j)  ) && 
		(abs ( (int)((*_db).getNetlist().getCellByIdx ( cellIndices.at(i)) .getLevel() - 
     	 (*_db).getNetlist().getCellByIdx (cellIndices.at(j)).getLevel()	)) == 1) )
  {
  	auto u = red.getVertex(cellIndices.at(i));
  	auto v = red.getVertex(cellIndices.at(j));
  	red.setEdgeWeight 
  	( -1.0 * INF_WEIGHT,  u, v);    	
  }

  graphParser gParser ( _db, &red );
  std::string fileName = (*_db).getDesignPath () + "/"
   + (*_db).getDesignName() + "_genOpt";
  //drawing the reduced graph after adding weights
  gParser. write_to_file ( fileName, 0, true );
    
  
  hMetisParser hmParser ( _db, red.getUndirGraph() );
  
  std::string hmetis_input = "./HMetis/hMetis/metis_in";
  std::map<int, int> cell_vertex_map = 
    hmParser.write_to_hMetis( cellIndices, hmetis_input );
	
  int Nparts = (int) (ceil(cellIndices.size() *1.0 / gSize )) ;
  std::map <int, int> vertex_partition_mapping;
  myWarn2 (Nparts > 0, Nparts, "Nparts is not > 0 ");

  if (Nparts > 1){
	int returnStatus = run_hMetis(Nparts, hmetis_input);
	if (returnStatus == 0)
		vertex_partition_mapping = 
			hmParser. read_from_hMetis(Nparts, hmetis_input);
	else {
		//vertex_partition_mapping = doRandomPartAssignment(currLevel, groupSize);
		myAssert2 (0, "\t\tError in calling hMetis cellList : " ,hmetis_input );
	}
  } 
  else {
  	//Nparts == 1, means all cells belong to same partiton, partition #(0)
  	for (unsigned lev=0; lev < cellIndices.size(); lev++)
  		vertex_partition_mapping[lev+1] = 0;
	
  }
  
  //cout << "cell_vertex_map: " << cell_vertex_map << endl;
  
  //cout << "vertex_partition_mapping: " << vertex_partition_mapping << endl;


  auto sup2CellMap = genSup2CellMap(cell_vertex_map, vertex_partition_mapping);

  //cout << "sup2CellMap: " << sup2CellMap << endl;
  
  //doPartitionBalancing(sup2CellMap, gSize);
  
  return sup2CellMap;	
}


//gets a map of supercells to vector of cells with actual cellIDs
//balances the partition to make sure superCells contain the same number of cells equal to groupSize
void Graph::doPartitionBalancing
  (std::map<unsigned, std::vector<unsigned> >  &superCell_map
    , int groupSize)
{
  int minPartSize = 100;
  int maxPartSize = 0;
  int level = 0; 
  
  for (auto it = superCell_map.begin(); it != superCell_map.end(); it++)
  {
    auto cellVec = it->second;
    if (cellVec.size() != 0 ) {
    	//this->chip->is_CellID_valid(cellVec[0]);
    	level = (*_db).getNetlist().getCellByIdx(cellVec.at(0)).getLevel();	
    }
    
    if ( minPartSize > int(cellVec.size())) minPartSize = int(cellVec.size());
    if ( maxPartSize < int(cellVec.size())) maxPartSize = int(cellVec.size());
  }
  int maxDiff = abs (maxPartSize - minPartSize);
  std::cout << "\tmax partition size difference is : " << maxDiff << std::endl;
  if (maxDiff == 0) return;
  
  int totalCellCount = int(this->level2Cell.at(level).size());
  //int totalFullPartitions = int(totalCellCount / groupSize);
  //int residueCellCount = int(totalCellCount % groupSize);
  
  std::vector<int > extraCells;
  for (auto it = superCell_map.begin(); it != superCell_map.end(); it++)
  {
  	auto cellVec = it->second;
  	if (int(cellVec.size()) == groupSize)
  		continue;
  	
  }
  
  
  return;
}


 
std::map< unsigned, std::vector<unsigned>> 
  Graph::genAllOptSupCells 
   ( BBox& bb, int cutSize, int gSize )
{
std::vector< 
	std::map< unsigned, std::vector<unsigned>>> allSup2CellMaps;
	
	std::map< unsigned, std::vector<unsigned>> finalMap;
	
	GridMapper gm(_db, cutSize, bb, _pl);	
	std::vector<GridBin> gBins = gm.getGridBins();
	
	for (unsigned i=0; i < gBins.size(); i++)
	{
	  auto vec = gBins.at(i).getCellIndices();
	  if ( (int)vec.size() <= gSize ){ //continue if cells sizes are less than a group, maybe there is a connection between these cells,can't risk it
		for ( auto v: vec )
		  allSup2CellMaps.push_back( {{0,{(unsigned) v}}} );
		  continue;
	  }
		
	  std::vector<unsigned> idx;
	  idx.insert ( idx.end(), vec.begin(), vec.end() );
	  
 	  allSup2CellMaps .push_back ( genOptSuperCells ( idx , gSize ) );
	}

	for (unsigned i=0; i < allSup2CellMaps.size(); i++)
	{
   	  auto cur = allSup2CellMaps.at(i);
	  for ( auto &j: cur)
		finalMap[ finalMap.size() ] = j.second; 
		
	}
	
	
   return finalMap;   
}



std::map < unsigned, std::vector<unsigned> >
Graph::genSup2CellMap
(const std::map<int, int> &cell_vertex_map, 
   const std::map<int, int> &vertex_partition_mapping)
{
	
	//returns a map, each item defines a supercell which points to a vector of cells
	std::map < unsigned, std::vector<unsigned> > supCell_cell_map;
	
	//map<int, int> cell_vertex_map : maps actual cellIDs to vertex numbers used as input to hMetis
	//e.g : if cellID[85] = 10, means that cell with actual ID of 85, has been mapped to vertex 0
	//vector<int> : maps the supercellID of each vertex, as output of hMetis, for ex vertex_partition_mapping[0] = 8
	//means that cell 0 (input to hMetis) is assigned to cluster(partition) #8

	std::map<int, int > vertex_cell_map;
	for (auto it = cell_vertex_map.begin(); it != cell_vertex_map.end(); it++)
		vertex_cell_map[it->second] = it->first;
	
	assert(int(cell_vertex_map.size()) == int(vertex_cell_map.size()));
	
	for (auto it = vertex_cell_map.begin(); it != vertex_cell_map.end(); it++){
		int vertexID = it->first;
		int cellID = it->second;
		(*_db).getNetlist().isCellIdValid (cellID);
		
		auto vertex_it = vertex_partition_mapping.find(vertexID);
		assert(vertex_it != vertex_partition_mapping.end());
		int superCellID = vertex_it->second;
		supCell_cell_map[superCellID].push_back(cellID);
	}
	
	for (auto it = supCell_cell_map.begin(); it != supCell_cell_map.end(); it++){
		if (debug) std::cout << "\tSuperCell " << it->first << " contains " <<  it->second.size() << " cells " << std::endl;
		for (int j=0; j < int(it->second.size()); j++){
			int cell_ID = it->second[j];
			auto cell_it = cell_vertex_map.find(cell_ID);
			assert (cell_it != cell_vertex_map.end());
			if (debug) std::cout << "\t\tcell : " << j << " vertex : " << cell_it->second << " with ID " << cell_ID << " name " << 
			(*_db).getNetlist().getCellByIdx(cell_ID).getName()
			<< std::endl;
		}
			if (debug) std::cout << "********************************" << std::endl;
	}
	

	return supCell_cell_map;
}



int Graph::run_hMetis(int Nparts, std::string inFileName){
	
/* 	//calls the old binary file
	hMetisPart khm(inFileName);
	khm.do_khMetis(Nparts);
	
 */	

    hMetisAdvancedPart khmAdv(inFileName);
	int returnStatus = khmAdv.do_advanced_khMetis(Nparts);
	
	if (returnStatus == 0) return 0;	
	myWarn2(0, "\tError in calling hMetis.2.0 trying hMetis 1.5.3 for ", inFileName );
	
	//trying with another binary for hMetis
	hMetisPart khm(inFileName);
	int ret2status = khm.do_khMetis(Nparts);
	if (ret2status == 256) return 0;
	return ret2status;
			
}



float Graph::getWeightBasedOnPlacement
  ( unsigned u, unsigned v, Dir dir,
	 double minDist, double maxDist )
{
	


			(*_db).getNetlist().isCellIdValid(u);
			(*_db).getNetlist().isCellIdValid(v);
	
			//if ((this->chip->cellList[u]->level == currLevel) && (this->chip->cellList[v]->level == currLevel)){
			int dist = ( dir == _XX) ? 
			  abs( (*_pl)[u].x - (*_pl)[v].x ) :
			  abs( (*_pl)[u].y - (*_pl)[v].y ) ;
			  
			
			float extraWeight = (int) ceil(
			  ( abs(dist - minDist)*
			    (MAX_GP_WEIGHT - MIN_GP_WEIGHT) ) /
				  abs(maxDist - minDist) ) + MIN_GP_WEIGHT;
				  
			
			extraWeight = (MAX_GP_WEIGHT - extraWeight);

				
			//}

	return extraWeight;
}


void Graph::addWeightBasedOnPlacement
  ( std::vector<unsigned> cells )
{
	
	//http://stackoverflow.com/questions/345187/math-mapping-numbers

	std::sort ( cells.begin(), cells.end(), 
						CompareCellIdsByX(*_pl));
	double maxDistX = abs( (*_pl)[ cells.front() ].x - (*_pl)[ cells.back() ].x );	

	std::sort ( cells.begin(), cells.end(), 
					CompareCellIdsByY(*_pl));
	double maxDistY = abs( (*_pl)[ cells.front() ].y - (*_pl)[ cells.back() ].y );		
	
	std::set< unsigned > cellSet ( cells.begin(), cells.end() );
	
	double minDistX = 1.0, minDistY = 1.0;

	for (tie(v_it, v_it_end) = vertices(_gr); v_it != v_it_end; ++v_it)
	{
	  auto u = vertex( *v_it, _gr );
	  
	  if ( cellSet.find(u) == cellSet.end() )
	  	continue;
	  
	  for (tie(v_it_2, v_it_2_end) = vertices(_gr); v_it_2 != v_it_2_end; ++v_it_2){
	  	
	    auto v = vertex( *v_it_2, _gr );
	    if (u == v) continue;
	    if (u < v) continue; //This makes sure edge between u and v is only weighted once, and not twice for (u,v) and (v,u)
	       
	  
	       
	    double extraWeight_x = 
	    	getWeightBasedOnPlacement(u,v,_XX,minDistX,maxDistX);
	    double extraWeight_y = 
	    	getWeightBasedOnPlacement(u,v,_YY,minDistY,maxDistY);
	    
	    float extraWeight = (int) ceil( 
	      sqrt( pow(extraWeight_x, 2) + 
	    		 pow(extraWeight_y, 2)) 
	    		 );
	    		
	    // if x is between A and B, Y = (X-A)/(B-A) * (D-C) + C would be between C and D
	    		
	    		
	    addEdgeWeight(extraWeight, u, v, _gr);
      
	  }
	} 
	
	return;
}


void Graph::addEdgeWeight
  (float extraWeight, Vertex &u, Vertex& v )
{
  addEdgeWeight ( extraWeight, u, v, _gr); 
}

void Graph::setEdgeWeight ( float w, Vertex &u, Vertex& v ) {
	std::pair<Edge, bool> ed = boost::edge(u, v, _gr);
	boost::put(boost::edge_weight_t(), _gr, ed.first, w);	
	return;
}

  
void Graph::addEdgeWeight
  (float extraWeight, Vertex &u, Vertex& v, undirGraph& g)
{

	//From http://stackoverflow.com/questions/24366642/how-do-i-change-the-edge-weight-in-a-graph-using-the-boost-graph-library
	std::pair<Edge, bool> ed = boost::edge(u, v, g);
	if (ed.second == false) {
		if (debug) std::cout << "edge between " << u << " & " << v << " does not exist" << std::endl;
		//add_edge(u, v, EdgeWeightProperty(UNIT_WEIGHT), g);
		add_edge(u, v, EdgeWeightProperty(extraWeight), g);
		return;
	}
	float weight = get(edge_weight_t(), g, ed.first);
	if (debug) std::cout << "old weight of edge " << "(" << u << "," << v << ")" << " is " << weight << std::endl;

	boost::put(boost::edge_weight_t(), g, ed.first, weight+extraWeight);
	
	weight = get(edge_weight_t(), g, ed.first);
	if (debug) std::cout << "new weight of edge " << "(" << u << "," << v << ")" << " is " << weight << std::endl;
	
	return;
}


undirGraph Graph::reduceGraph(std::vector<unsigned> cells)
{
		
	//building subgraph, only containing level i
	undirGraph lg( (*_db).getNetlist().getNumCells() );
	
	std::set<unsigned> cellSet ( cells.begin(), cells.end() );
	for(std::tie(e_it, e_end) = boost::edges(_gr); 
		e_it != e_end; 
			++e_it)
	{
		auto u = source ( *e_it, _gr );
		auto v = target ( *e_it, _gr );
		(*_db).getNetlist().isCellIdValid(u);
		(*_db).getNetlist().isCellIdValid(v);
		
		//if both u and v are in cells vec, add their edge
		if ( cellSet.find( u ) != cellSet.end() &&
			 cellSet.find(v) != cellSet.end() )
		 {
			std::pair<Edge, bool> ed = boost::edge(u, v, _gr);
			float weight = get(edge_weight_t(), _gr, ed.first);
			if (u < v)
				add_edge (u, v, EdgeWeightProperty(weight), lg);
			else if (v < u)
				add_edge (v, u, EdgeWeightProperty(weight), lg);				
		}
	}
	
	print_GraphStatus(lg);	
	return lg;	
	
}

bool Graph::areConnected (int a, int b){
	Vertex u = vertex(a, _gr);
	Vertex v = vertex(b, _gr);	
	std::pair<Edge, bool> ed = boost::edge(u, v, _gr);
	return (ed.second);
	
}


bool Graph::areConnected (int a, int b, undirGraph& g){
	Vertex u = vertex(a, g);
	Vertex v = vertex(b, g);	
	std::pair<Edge, bool> ed = boost::edge(u, v, g);
	return (ed.second);
}


//returns a vector containing the id of the adjacent cells, connected to baseCell
std::vector<unsigned> 
  Graph::findAdjdbCells(unsigned idx)
{
	
	std::vector<unsigned> adjCells;
	currVertex = vertex (idx, this->_gr);
	for (tie(out_it, out_it_end) = out_edges(currVertex, this->_gr); out_it != out_it_end; ++out_it){
		//cout << *out_it ;
		//auto currSource = source ( *out_it, this->gr );
		auto currTarget = target ( *out_it, this->_gr );
		adjCells.push_back(currTarget);
	}
	return adjCells;
}

undirGraph Graph::createLevelSubGraph(int level)
{
	
	int currLevel = level;
	myAssert3( currLevel >= 0 && 
	  currLevel < (int) level2Cell.size(), 
	   currLevel, " is invalid for level2Cell: ", 
	    level2Cell.size()); 
	
	//building subgraph, only containing level i, i-1, and i+1
	undirGraph levelGraph((*_db).getNetlist().getNumCells());
	auto cellVec = this->level2Cell.at(currLevel);
	
	for (unsigned i=0; i < cellVec.size(); i++)
	{
		
		currVertex = vertex (cellVec.at(i)->getIndex(), levelGraph);
		auto adjVec = findAdjdbCells(cellVec.at(i)->getIndex());
		for (unsigned j=0; j < adjVec.size(); j++)
		{
		  myAssert3 (adjVec.at(j) >= 0 && 
		   adjVec.at(j) < (*_db).getNetlist().getNumCells(), 
		    adjVec.at(j), "  adj cell has invalid idx: ", 
			(*_db).getNetlist().getNumCells() );
			
  		  nextVertex = vertex ((*_db).getNetlist().getCellByIdx(adjVec.at(j)).getIndex(), levelGraph);
			
			//checks if edge exists, http://programmingexamples.net/wiki/Boost/BGL/EdgeExists
			//Only adds an edge, if there is not an edge between two vertices
		  if (edge(currVertex, nextVertex, levelGraph).second == false)
			add_edge(currVertex, nextVertex, EdgeWeightProperty(UNIT_WEIGHT), levelGraph);
		}
	}
		
	//removeSingleVertices(levelGraph);
	//VertexMap vmap = get(vertex_index, levelGraph);
	
	return levelGraph;
}



//return a graph, only containing the edges between same level cells, cell level defined by currLevel
undirGraph 
 Graph::reduce_to_levelGraph
  (undirGraph& g, int currLevel)
{
	
	myAssert3( currLevel >= 0 && 
	  currLevel < (int) level2Cell.size(), 
	   currLevel, " is invalid for level2Cell: ", 
	    level2Cell.size()); 
			
	//building subgraph, only containing level i
	undirGraph lg((*_db).getNetlist().getNumCells());
	
	for(std::tie(e_it, e_end) = boost::edges(g); e_it != e_end; ++e_it){
	  auto u = source ( *e_it, g );
	  auto v = target ( *e_it, g );
	  (*_db).getNetlist().isCellIdValid(u);
	  (*_db).getNetlist().isCellIdValid(v);
	     
	  if (( (int) (*_db).getNetlist().getCellByIdx(u).getLevel() == currLevel) 
	   && ( (int)(*_db).getNetlist().getCellByIdx(v).getLevel() == currLevel))
	  {
	  	std::pair<Edge, bool> ed = boost::edge(u, v, g);
	  	float weight = get(edge_weight_t(), g, ed.first);
	  	if (u < v)
	  		add_edge (u, v, EdgeWeightProperty(weight), lg);
	  	else if (v < u)
	  		add_edge (v, u, EdgeWeightProperty(weight), lg);				
	  }
	}
	
	print_GraphStatus(lg);
	return lg;	
}

 
 
//generates a map of supercell to cell based on level-based partitioning
std::map< unsigned, std::vector<unsigned>>  
  Graph::genLevelBasedSupCells(int groupSize){
/* 	//http://stackoverflow.com/questions/8812466/using-c-boosts-graph-library
	// instantiate a undirGraph object with 8 vertices
	undirGraph g(8);
	
	// add some edges
	add_edge(0, 1, g);
	
	// represent graph in DOT format and send to cout 
	//write_graphviz(cout, gr);
	
	//print_graph(this->gr);
	//print_name2CellMap();
	//write_to_file(this->gr, "complete_graph");
	//Vertex s = *(vertices(this->gr).first);*/

	std::map<int,std::map<unsigned,std::vector<unsigned>>> level_supCell_cell_map;
	int totalNparts = 0;
	for (int i=1; i <= int((*_db).getMaxLevel()); i++){
		std::cout << "Level " << i << std::endl;
		int currLevel = i;
		auto levelGraph = createLevelSubGraph(currLevel);		
		if (debug) std::cout << "Level " << currLevel << " before adding edge weights " << std::endl; 
		if (debug) print_edge_weights(levelGraph);
		print_GraphStatus(levelGraph);
		std::string levelFileName = "./HMetis/hMetis/L"+ to_string(currLevel) + "_graph";
		if (debug) write_to_file(levelGraph, levelFileName+"_before", currLevel);
		//addWeightToNeighbors(levelGraph, currLevel);
		
        std::vector<unsigned> levelGraphCells;		
    	for (tie(v_it, v_it_end) = vertices(levelGraph); 
	         v_it != v_it_end; ++v_it)    			
        levelGraphCells.push_back( (unsigned) (*v_it) );                     			 
		
		addWeightBasedOnPlacement(levelGraphCells);
		if (debug) std::cout << "Level " << currLevel << " After adding edge weights " << std::endl; 
		if (debug) print_edge_weights(levelGraph);
		if (debug) write_to_file(levelGraph, levelFileName+"_after", currLevel);
		print_GraphStatus(levelGraph);

		
		auto reducedGraph = reduce_to_levelGraph(levelGraph, currLevel);
		std::cout << "Total # of cells of level " << currLevel << " is " << this->level2Cell[currLevel].size() << std::endl; 
		if (get_TotalConnectedVertices(reducedGraph) != int (this->level2Cell[currLevel].size()) )
			std::cout << "\tafter graph reduction, number of connceted cells(" << get_TotalConnectedVertices(reducedGraph) <<
				") is not equal to total number of cells(" << this->level2Cell[currLevel].size() << ") of level " <<
					currLevel << std::endl;
			
		if (debug) write_to_file(reducedGraph, levelFileName+"_reduced", currLevel);
		std::cout << "**********************************************" << std::endl << std::endl;
		
		std::string hmetis_input = "./HMetis/hMetis/L"+ to_string(currLevel) + "metis_in";
		
        hMetisParser hmParser ( _db, reducedGraph );
		
		std::vector<unsigned> currLevelCells;
        for (auto&i: level2Cell[currLevel])
          currLevelCells.push_back( i->getIndex() );			
		
		std::map<int, int> cell_vertex_map = 
		  hmParser.write_to_hMetis(currLevelCells, hmetis_input);
		int Nparts = (int(this->level2Cell[currLevel].size()) / groupSize ) ;
		int residue = (int(this->level2Cell[currLevel].size()) % groupSize );
		if (residue != 0) Nparts += 1;
		
		std::map <int, int> vertex_partition_mapping;
		if (Nparts == 0) std::cerr << "Nparts for level " << currLevel << " is 0" << std::endl;
		if (Nparts > 1){
			int returnStatus = run_hMetis(Nparts, hmetis_input);
			if (returnStatus == 0)
				vertex_partition_mapping = hmParser. read_from_hMetis(Nparts, hmetis_input);
			else {
				vertex_partition_mapping = doRandomPartAssignment(currLevel, groupSize);
				std::cerr << "\t\tError in calling hMetis for level " << currLevel << " cellList : " << hmetis_input
					<< " doing random partitioning " << std::endl;
			}
		}
		else {
			//Nparts == 1, means all cells belong to same partiton, partition #(0)
			for (int lev=0; lev < int(this->level2Cell[currLevel].size()); lev++){
				vertex_partition_mapping[lev+1] = 0;
			}
		}
		totalNparts += Nparts;
		
		if (debug){
			for (auto it = vertex_partition_mapping.begin(); it != vertex_partition_mapping.end(); it++)
				std::cout << "vertex : " << it->first << " cluster number : " << it->second << std::endl;			
		}
		

		
		auto thisLevelSupCells = genSup2CellMap(cell_vertex_map, vertex_partition_mapping);
		doPartitionBalancing(thisLevelSupCells, groupSize);
		
		
		level_supCell_cell_map[currLevel] = thisLevelSupCells;
	}
	
	std::cout << "\t\ttotalNparts : " << totalNparts << std::endl;
	//this->print_clusteredGraph_status(level_supCell_cell_map);

    std::map< unsigned, std::vector<unsigned>> outMap;
    for (auto &i: level_supCell_cell_map)	
	  for (auto &j: i.second){
		std::vector<unsigned> cur;
		for (auto&p: j.second)
          cur.push_back( (unsigned) p );			
	  
        outMap[outMap.size()] = cur;		   
	  }
	
    return outMap;	
}
