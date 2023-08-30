#ifndef _HMETIS_H_
#define _HMETIS_H_

#ifndef COMMON__H
#include "common.h"
#endif

class hMetisPart{
	 
	private: 
		std::string	GraphFileName;
		int UBfactor; 
		int Nruns   ; 
		int CType   ; 
		int OType   ; 
		int VCycle  ; 
		int dbglvl  ; 
	
	public:
	
		hMetisPart(std::string GraphFileName, int UBfactor, int Nruns, 
					int CType, int OType, int VCycle, int dbglvl);
					
		hMetisPart(std::string GraphFileName);
		
		int do_khMetis(int Nparts);
	
};

class hMetisAdvancedPart{
		
	private:
		std::string	GraphFileName;
		std::string ptype;
		std::string ctype;
		std::string	rtype;
		std::string otype;
		float ufactor;
		int nruns;
		int nvcycles;
		int seed;
		int dbglvl;
	public:
		hMetisAdvancedPart(std::string GraphFileName);
		int do_advanced_khMetis(int Nparts);

};

#endif