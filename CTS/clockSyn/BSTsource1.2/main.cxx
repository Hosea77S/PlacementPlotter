

/*
#**************************************************************************
#**   Please read README to see how to run this program
***   Created by Chung-Wen Albert Tsao  on May 2, 2000*
#**
#**
#**************************************************************************
*/

#include <cstdio>
#include <cfloat>
#include <cstring>
#include <cstdlib>
#include "bstdme.h"
#include "facility.h"

using namespace std;

/**********************************************************************/
/* Copyright (C) 1994-2000  by Andrew B. Kahng, C.-W. Albert Tsao    */
/**********************************************************************/
void tPrintTotalLength (
  const BST_DME &tree
) {
  double wire = tree.TotalLength () ;

  printf("=================================\n" );
  iShowTime () ;
  printf("\n" );
  printf("Total wirelength: %f\n", wire);
  printf("=================================\n" );
}

/****************************************************************************/
/*   parse arguments                                                        */
/****************************************************************************/
unsigned parse_argument( unsigned argc, char *argv[], 
  string &inputSinksFileName ,     
  string &inputTopologyFileName ,     
  string &inputObstructionFileName ,
  double  &skewBound ,
  double  &splDelay,  
  BST_DME::DelayModelType   &delayModel      
) {
unsigned nterms = 0 ;
  
  for (unsigned i=1;i<argc;i++) {
    if (strcmp("-i",argv[i]) == 0)  {
      i++;
      inputSinksFileName = argv[i] ;
    } else if (strcmp("-G",argv[i]) == 0)  {
      i++;
      inputTopologyFileName = argv[i] ;
	  cout << "Found topology file: " << inputTopologyFileName << endl;
    } else if (strcmp("-O",argv[i]) == 0)  { // not complete yet
      i++;
      inputObstructionFileName = argv[i] ;
    } else if (strcmp("-N",argv[i]) == 0)  { // to generate random testcase
      i++;
      sscanf(argv[i],"%d",&nterms);
    } else if (strcmp("-D",argv[i]) == 0)  { // for delay model
      i++;
      unsigned model ;
      sscanf(argv[i],"%d",& model );
      delayModel = (BST_DME::DelayModelType ) model ;
    } else if (strcmp("-B",argv[i]) == 0)  { // for skew bound
      i++;
      sscanf(argv[i],"%lf",& skewBound);
      if ( skewBound < 0) { 
         skewBound = DBL_MAX; 
      } 
    }
	else if ( strcmp ("-spD", argv[i]) == 0){ // splitter delay
		i++;
		sscanf ( argv[i],"%lf",&splDelay );
		if ( splDelay < DBL_EPSILON )
			splDelay = 0.0;
	}
	else {
      printf("Argument %d : %s incorrect\n",i, argv[i]);
      exit(0);
    }
  }

  return nterms ;
}


/*************************************************************************************/
/*                                                                                   */
/*************************************************************************************/
static
void bstsVersion () {
  const string lin = 
   "*******************************************************************************\n" ;
  const string msg = 
      lin   
    + "* Version BSTsource1.1 ,  05-11-2002                                          *\n"   
    + "* Copyright (C) 1994-2002  by Andrew B. Kahng, C.-W. Albert Tsao              *\n"   
    + "* usage: bst -i inputFileName -B number -spD splitterDelay                    *\n"   
    +  lin  
    ; 
  cout << msg << endl ;
}
/**********************************************************************/
/* Copyright (C) 1994-2000  by Andrew B. Kahng, C.-W. Albert Tsao    */
/**********************************************************************/
int 
main(int argc, char *argv[]) {

  bstsVersion () ;

string inputSinksFileName = "" ; // mandatory
string inputTopologyFileName = "" ;
string inputObstructionFileName = "" ;
double  skewBound = 0 ;
double  splDelay = 0.0;
BST_DME::DelayModelType delayModel = BST_DME::ELMOREMODEL;


     unsigned nterms = parse_argument (argc, argv, 
                      inputSinksFileName,
                      inputTopologyFileName, 
                      inputObstructionFileName,
                      skewBound,
					  splDelay,
                      delayModel
                      );


  if ( nterms ) { // generate testcase only 
    BST_GenTestcase::GenerateTestcase( nterms ) ;
  } else if ( inputSinksFileName.empty() ) { // mandatory 
     printf ("usage: bst -i inputFileName -B number\n" ) ;
     exit (0 ) ;
  } else {
    BST_DME tree (inputSinksFileName,
                inputTopologyFileName,
                inputObstructionFileName,
                skewBound,
				splDelay,
                delayModel ) ;
    tree.ConstructTree() ;
    tPrintTotalLength ( tree ) ;	
	cout << "Exiting \n\n\n\n\n\n" ;
  }


}
