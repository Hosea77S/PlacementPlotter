#include "hMetis.h"



hMetisPart::hMetisPart(std::string GraphFileName, int UBfactor, int Nruns, 
			int CType, int OType, int VCycle, int dbglvl){
				
	this->GraphFileName = GraphFileName;
	this->UBfactor = UBfactor ; 
	this->Nruns  = Nruns   ; 
	this->CType   = CType   ; 
	this->OType    = OType   ; 
	this->VCycle  = VCycle  ; 
	this->dbglvl  = dbglvl  ; 
			
}


hMetisPart::hMetisPart(std::string GraphFileName){
				
	this->GraphFileName = GraphFileName;
	this->UBfactor = 5; 
	this->Nruns  = 40   ; 
	this->CType   = 4   ; 
	this->OType    = 1   ; 
	this->VCycle  = 3  ; 
	this->dbglvl  = 8  ; 
			
}
	
int hMetisPart::do_khMetis(int Nparts){
	
	//GraphFileName includes complete path to graph file
	myAssert(Nparts > 0, "Nparts is not > 0");
	//Usage: ./hmetis/khmetis <GraphFile> <Nparts> <UBfactor> <Nruns> <Ctype> <OType> <VCycle> <dbglvl>
	std::string command = "./HMetis/hMetis/khmetis " + GraphFileName + " " + std::to_string(Nparts) + " " + std::to_string(UBfactor) + " " + 
						std::to_string(Nruns) + " " + std::to_string(CType) + " " + std::to_string(OType) + " " + 
							std::to_string(VCycle) + " " + std::to_string(dbglvl) + " " ;
	command = command + " > " +  GraphFileName + ".log" ;
	int returnStatus = system(command.c_str());
	std::cout << "\tCalling command " << command << std::endl;
	
	return returnStatus; 
}


hMetisAdvancedPart::hMetisAdvancedPart(std::string GraphFileName){
	this->GraphFileName = GraphFileName;
	ptype = "kway";
	ctype = "h1"; 
	rtype = "kpslow";
	otype = "cut";
	ufactor = 5;
	nruns = 40;
	nvcycles = 1;
	seed = 1464902610;
	dbglvl = 24;	
	
}
int hMetisAdvancedPart::do_advanced_khMetis(int Nparts){
	//GraphFileName includes complete path to graph file
	myAssert(Nparts > 0, "Nparts is not > 0");
	this->nvcycles = Nparts;
	//Usage: Usage: hmetis [options] <filename> <nparts> 
	std::string command = std::string("./HMetis/hMetis/hmetis2.0pre1 ") +  " -ptype=" + ptype + " -ctype=" + ctype + 
						" -rtype=" + rtype + " -otype=" + otype + " -ufactor=" + std::to_string(ufactor) + 
						" -nruns=" + std::to_string(nruns) + " -nvcycles=" + std::to_string(nvcycles) + 
						//" -seed=" + std::to_string(seed) + 
						" -dbglvl=" + std::to_string(dbglvl) + 
						" " + GraphFileName + " " + std::to_string(Nparts) ;
						
	command = command + " > " +  GraphFileName + "_" + std::to_string(Nparts) + ".log" ;
	int returnStatus = system(command.c_str());
	std::cout << "\tCalling command " << command << std:: endl;
	
		
	return returnStatus;
}



/* Usage: ./khmetis <GraphFile> <Nparts> <UBfactor> <Nruns> <Ctype> <OType> <VCycle> <dbglvl>
Where:
 GraphFile: name of the data file
 Nparts   : number of desired partitions
 UBfactor : balance between the partitions (e.g., 10 bounds the load-imbalance at 10% (max/average))
 Nruns    : Number of Iterations
 CType    : HFC(1), FC(2), GFC(3), HEDGE(4), EDGE(5)
 OType    : Cut(1), SOED(2)
 VCycle   : No(0), @End(1), ForMin(2), All(3)
 dbglvl   : debug level
 */	
 
 /*
 Usage: hmetis [options] <filename> <nparts>

 Required parameters
    filename    Stores the hypergraph to be partitioned.
    nparts      The number of partitions to split the hypergraph.

 Optional parameters
  -ptype=string
     Specifies the scheme to be used for computing the k-way partitioning.
     The possible values are:
        rb       - Recursive bisection [default]
        kway     - Direct k-way partitioning.

  -ctype=string                 (rb, kway)
     Specifies the scheme to be used for coarsening.
     The possible values are:
        fc1        - First-choice scheme
        gfc1       - Greedy first-choice scheme [default]
        fc2        - Alternate implementation of the fc scheme
        gfc2       - Alternate implementation of the gfc scheme
        h1         - Alternates between fc1 and gfc1 [default if nruns<20]
        h2         - Alternates between fc2 and gfc2
        h12        - Alternates between fc1, gfc1, fc2, gfc2 [default otherwise]
        edge1      - Edge-based coarsening
        gedge1     - Greedy edge-based coarsening
        edge2      - Alternate implementation of the edge scheme
        gedge2     - Alternate implementation of the gedge scheme

  -rtype=string                 (rb, kway)
     Specifies the scheme to be used for refinement.
     The possible values and the partitioning types where they apply are:
        fast        - Fast FM-based refinement (rb) [default]
        moderate    - Moderate FM-based refinement (rb)
        slow        - Slow FM-based refinement (rb)
        krandom     - Random k-way refinement (kway) [default for ptype=kway]
        kpfast      - Pairwise k-way FAST refinement (kway)
        kpmoderate  - Pairwise k-way MODERATE refinement (kway)
        kpslow      - Pairwise k-way SLOW refinement (kway)

  -otype=string                 (kway)
     Specifies the objective function to use for k-way partitioning.
     The possible values are:
        cut      - Minimize the cut [default]
        soed     - Minimize the sum-of-external-degrees

  -ufactor=float                (rb, kway)
     Specifies the unbalance factor. The meaning of this parameters depends
     on the partitioning scheme (ptype):
       For ptype=rb
         Specifies the maximum difference between each successive bisection.
         For instance, a value of 5 leads to a 45-55 split at each bisection.
       For ptype=kway
         Specifies the maximum load imbalance among all the partitions. For
         instance, a value of 5 produces partitions in which the weight of
         the largest partition over the average weight is bounded by 5%.

  -nruns=int                    (rb, kway)
     Specifies the number of different bisections to be computed
     at each level. The final bisection corresponds to the one that
     has the smallest cut

  -nvcycles=int                 (rb, kway)
     Specifies the number of solutions to be further refined using
     V-cycle refinement. If the supplied number is k, then the best
     k bisections are further refined using V-cycling. This number
     should be less or equal to that specified for -nruns. The default
     value is one.

  -cmaxnet=int                  (rb, kway)
     Specifies the size of the largest net to be considered during
     coarsening. Any nets larger than that are ignored when determing
     which cells to merge together. Default value for that is 50.

  -rmaxnet=int                  (rb, kway)
     Specifies the size of the largest net to be considered during
     refinement. Any nets larger than that are ignored during the
     multilevel partitioning phase, and are dealt once the partitioning
     has been computed. Default value for that is 50.

  -reconst                      (rb)
     Instructs hmetis to create partial nets within each partition
     representing the nets that were cut during the bisection.

  -kwayrefine                   (rb)
     Instructs hmetis to perform a final k-way refinement once the
     partitioning has been computed using recursive bisection

  -fixed=string                 (rb, kway)
     Instructs hmetis to read the file specified as the argument
     of this parameter for specifying the groups of cells to be
     placed in the same partition

  -seed=int                     (rb, kway)
     Selects the seed of the random number generator.

  -dbglvl=int                   (rb, kway)
     Selects the dbglvl. The value is obtained by adding the following
     codes:
        1       - Show coarsening progress
        2       - Show the initial cuts
        4       - Show the refinement progress
        8       - Show bisection statistics
       16       - Show bisection statistics
       32       - Print timing statistics
      128       - Show detailed bisection statistics
      256       - Show detailed info about cell moves

  -help
     Prints this message.
*/
