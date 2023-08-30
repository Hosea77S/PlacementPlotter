#include "routerDriven.h"
#include "dbPoint.h"

double RDP::getMaxRowScore(int rowRV){

  auto scoreSort = routeVect[rowRV]; 

  std::sort ( scoreSort.begin(), scoreSort.end(), compareScore ); //front is the higest

  return scoreSort[0].hScore;
}




int RDP::getMaxColId(int rowRV){

  auto scoreSort = routeVect[rowRV]; 

  std::sort ( scoreSort.begin(), scoreSort.end(), compareScore ); //front is the higest

  return scoreSort[0].columnId;
}



bool RDP::swapEx(int rowRV){ //if  this returns false that means the given rowRv cannt be optimized anymore

  std::cout <<"**swapEx is invoked\n";

  auto scoreSortRow = routeVect[rowRV]; //to sort RV row score

  std::sort ( scoreSortRow.begin(), scoreSortRow.end(), compareScore ); //front is the higest score



  std::vector <int> maxScoreIdList;

  for (unsigned i=0; i < scoreSortRow.size(); i++ ){      //collecting the column id that has the max score
    if(scoreSortRow[0].hScore == scoreSortRow[i].hScore){
      maxScoreIdList.push_back( scoreSortRow[i].columnId );
    } 
    else break;
  }


  std::cout<<"Number of column that has the same MAX in row " << rowRV <<"= " << maxScoreIdList.size() <<"\n"; 

  bool suc=false;

  for(unsigned i=0; i < maxScoreIdList.size(); i++ ){ //yusukeopti
        std::cout <<"Attempt of swapEx1 " << i+1 << "/" << maxScoreIdList.size() <<"\n";
	suc= swapEx1(rowRV, maxScoreIdList[i] );   //sending RV row num and col# to optimize the target slot

	if( suc == true){
	  
	  break;
	}
   }
  std::cout <<"SwapEx suc= " << suc<<"\n";
  if (suc==false) return false;

  else return true;
      


}

bool RDP::swapEx1(int rowRV, int colId ){

  std::cout <<"**Function Swap1 is invoked\n"; 
  std::cout <<"Looking into RVrow = " << rowRV << ", colID= " <<colId << "\n";
  auto RVslot = routeVect[rowRV][colId];

  bool suc =false;

  for(unsigned i=0; i < RVslot.netList.size(); i++){
    std::cout<<"Attempt of NET optim =" << i+1 << "/" <<RVslot.netList.size() <<"\n";
    std::cout<<"one of cells in net_id=  " << RVslot.netList[i] << " is consider to be swapped\n";
    suc = swapEx2(rowRV, colId, RVslot.netList[i] );  //return true if 
    
    if(suc == true ){
	std::cout <<"**Function Swap1 is END: returnning suc=1\n";
	return suc;
    }

  }
std::cout <<"**Function Swap1 is END: returning suc=0\n";    
return false;

}


std::pair <bool, unsigned> RDP::searchCell( double xLeft, double yBotLeft ){ //ignores the random pad location. We assume it as whitespace.

  std::cout << "**Function SearchCell is invoked\n"; 
  
  unsigned x_colPos;
  int xVal;

  double x_inc =   (*_db)._rowDefs->getChipWidth()  / RowScore_num;
  double x_begining = (*_db)._rowDefs->getXOffset();  

 

  for(unsigned i=0; i < (*_db).getNetlist().getNumCells(); i++){
    if(xLeft == getCellX(i) ){
      if(yBotLeft == getCellY(i) ){
      std::cout << "Cell Id=" << i << " has " << xLeft << ", " << yBotLeft <<"\n";
      return std::make_pair(true, i);  //true returns cell id 
      }
    }
  }
  std::cout << "Could not find cell that has " << xLeft << ", " << yBotLeft <<"\n";
  std::cout << "Meaning that this is whitespace " << xLeft << ", " << yBotLeft <<"\n";
  xVal= ( xLeft - x_begining ) / x_inc;
  if(xVal < 0) x_colPos=0;
  else if(xVal >  (RowScore_num-1) ) x_colPos=RowScore_num-1;
  else  x_colPos=xVal;
  return std::make_pair(false, x_colPos);  //false means that it is whitespace in terms of x-col pos is returned
}





bool RDP::swapRight( unsigned swapCan, int rowRV, int colId ){
  std::cout <<"\n**Function swapRight is invoked\n";
  std::cout <<"Cand A is at RV row = " << rowRV << " column= " <<colId <<"\n";
  auto targetRV = routeVect[rowRV][colId];

  std::pair <bool, unsigned> swapCanB;

  bool suc=false;

  for(int i = colId+1; i < RowScore_num; i++  ){ //B cell selection maybe I can assert window here
    std::cout << "Swap B column = " << i <<"\n";
    swapCanB = searchCell( routeVect[rowRV][i].minX, getCellY(swapCan)   );  //true is cellid.  false is column id.

    if ( (swapCanB.first == true) && ( (*_db).getNetlist().getCellByIdx( swapCanB.second ).isFixed() ) ){
    std::cout <<"Swap B is fixed cell\n";
    continue;
    }

   suc=swapAction( swapCan, swapCanB, rowRV, colId);

   if (suc== true){
  std::cout <<"**Function swapRight is END\n";
 return true;
  }

   std::cout <<"No swap with swap B happened\n";
 
  }
  
 std::cout <<"**Function swapRight is END\n";
  return false;
    
   
}


bool RDP::swapLeft( unsigned swapCan, int rowRV, int colId ){
  std::cout <<"\n**Function swapLeft is invoked\n";
  std::cout <<"Cand A is at RV row = " << rowRV << " column= " <<colId <<"\n";
  auto targetRV = routeVect[rowRV][colId];

  std::pair <bool, unsigned> swapCanB;

  bool suc=false;

  for(int i = colId-1; i >= 0; i--  ){ //maybe I can assert window here
    std::cout << "Swap B column = " << i <<"\n";
    swapCanB = searchCell( routeVect[rowRV][i].minX, getCellY(swapCan)   );  //true is cellid.  false is column id.

    if ( (swapCanB.first == true) && ( (*_db).getNetlist().getCellByIdx( swapCanB.second ).isFixed() ) ){
         std::cout <<"Swap B is fixed cell\n";
         continue;
    }

   suc=swapAction( swapCan, swapCanB, rowRV, colId);

   if (suc== true){
  std::cout <<"Function swapLeft is END\n";
 return true;
  }

   std::cout <<"No swap with swap B happened\n";
 
  }
    std::cout <<"**Function swapLeft is END\n";
  return false;
    
   
}










bool RDP::swapAction (unsigned candAId, std::pair<bool, unsigned> candB, int rowRV, int colId ){ //onlywhite space or movable cell is passed


  std::cout << "**Function swapAction is invoked\n";

  auto UpdateRV = routeVect;
  auto UpdateAbRV = aboveChip;
  auto UpdateBeRV = belowChip;
 
  double x_inc =   (*_db)._rowDefs->getChipWidth()  / RowScore_num;
  double x_begining = (*_db)._rowDefs->getXOffset();  

  unsigned candABeforeColId= ( getCellX(candAId) - x_begining ) / x_inc;  //candA original colunm id
  

  unsigned candBBeforeColId;   //cand B original colunm id //if false meaning empty just give col position then you can get xpos
//  double candBBeforePos;

  std::vector <unsigned> netBIdList;

  std::vector < std::vector < std::tuple <int,unsigned, unsigned> > > RVaffListA; //1st vector->net 2nd vector ->net RV info

  std::vector < std::vector < std::tuple <int,unsigned, unsigned> > > RVaffListB;



  std::vector <unsigned> netAIdList = getAllNetIds(candAId); //all net in the candA cell

  std::cout<<"!!Search RVaffListA Begin\n";
  for(unsigned i=0; i < netAIdList.size(); i++){  

  RVaffListA.push_back( std::vector < std::tuple <int,unsigned, unsigned> > () );
  
  RVaffListA[i]= searchNetinRV( netAIdList[i] );  //net id corresponding to net information




  }
  std::cout<<"!!Search RVaffListA End\n";
  

  std::cout<<"!!Search RVaffListB Begin\n";
  if(candB.first == true){//can B is movable and has cell id

   netBIdList = getAllNetIds(candB.second); //all net in the candB cell

   for(unsigned i=0; i < netBIdList.size(); i++){

     RVaffListB.push_back( std::vector < std::tuple <int,unsigned, unsigned> > () );  //type; row; column;  get<0,1,2> type middle=0, bottom=1, top=2
  
     RVaffListB[i]= searchNetinRV( netBIdList[i] );

   }

   candBBeforeColId= ( getCellX(candB.second) - x_begining ) / x_inc;
//   candBBeforePos= getCellX(candB.second);
  }
  
  else{ //can B is white space with col id

  candBBeforeColId = candB.second;  //whitespace so already colid //no worry of affec list
//  candBBeforePos = routeVect[0][ candBBeforeColId ].minX;
  }
  std::cout<<"!!Search RVaffListB End\n"; 




  //do temp swap then see if swap wont violate RV optimization

  for(unsigned i=0; RVaffListA.size() > i ; i++ ){ //Number of net

  if(RVaffListA[i].size()==0) continue;
  //if(RVaffListA[i][0].third == candABeforeColId ){ //case alpha

   if(std::get<2>(RVaffListA[i][0]) == candABeforeColId ){ //case alpha

    std::cout<<"In this case, cell, before Swap, should be at the left of the net\n"; 

    alphaSwap( UpdateRV, netAIdList[i], RVaffListA[i], candBBeforeColId, UpdateAbRV, UpdateBeRV ); //Updated RV, net id, RV net vec, swap B col id, 
   }

   else if( std::get<2>(RVaffListA[i][ RVaffListA[i].size()-1 ]) == candABeforeColId  ){ //case beta
   
    std::cout<<"In this case, cell, before Swap, should be at the right of the net\n"; 

    betaSwap( UpdateRV, netAIdList[i], RVaffListA[i], candBBeforeColId, UpdateAbRV, UpdateBeRV ); //Updated RV, net id, RV net vec, swap B col id, 
   }
  }


//now i need to modify swap cell B
  if(candB.first == false){ //means that whitespace

    std::cout << "CandB is whitespace. We do not have to calculate RV affect\n";
  }

  else{ //swap B is movable
//    std::cout<<"Calculating for Cand B\n";
//    std::cout<<"RVaffListB.size()= " << RVaffListB.size() <<"\n";
//    std::cout <<"total net num...netBIdList.size()= " << netBIdList.size() <<"\n";
//    std::cout <<"candBBeforeColId = " << candBBeforeColId <<"\n";
     for(unsigned i=0; RVaffListB.size() > i ; i++ ){ //Number of net
//     std::cout << "i= " << i <<"\n";
//     std::cout << "min col x pos = " << routeVect[0][0].minX <<"\n";
//     std::cout << "net num.....netBIdList[ " << i <<"]= " << netBIdList[i] <<"\n";
//     std::cout << "RVaffListB[i].size() = " << RVaffListB[i].size() <<"\n";
     getCellidsByNetid(netBIdList[i]);
//     std::cout << "std::get<2>(RVaffListB[i][0]) = "<< std::get<2>(RVaffListB[i][0]) <<"\n";
//     std::cout <<"std::get<2>(RVaffListB[i][ RVaffListB[i].size()-1 ]) = " << std::get<2>(RVaffListB[i][ RVaffListB[i].size()-1 ]) <<"\n";

  //alphaSwap( UpdateRV, netAIdList[i], RVaffListA[i], candBBeforeColId, UpdateAbRV, UpdateBeRV );
  //if(RVaffListA[i][0].third == candABeforeColId ){ //case alpha
       if(RVaffListB[i].size()==0) continue;

       if(std::get<2>(RVaffListB[i][0]) == candBBeforeColId ){ //case alpha

        std::cout<<"In this case, cell, before Swap, should be at the left of the net\n"; 

        alphaSwap( UpdateRV, netBIdList[i], RVaffListB[i], candABeforeColId, UpdateAbRV, UpdateBeRV ); //Updated RV, net id, RV net vec, swap B col id, 
//        std::cout <<"aft alph\n";
//        std::cout <<"candBBeforeColId= " << candBBeforeColId <<"\n";
//        std::cout << "RVaffListB[1].size()= " << RVaffListB[1].size() << "\n";
//        std::cout << "std::get<2>(RVaffListB[i][ RVaffListB[i].size()-1 ])= " << std::get<2>(RVaffListB[i][ RVaffListB[1].size()-1 ]) <<"\n";
       }
       
       else if( std::get<2>(RVaffListB[i][ RVaffListB[i].size()-1 ]) == candBBeforeColId  ){ //case beta
   
        std::cout<<"In this case, cell, before Swap, should be at the right of the net\n"; 
//        printScore();
        betaSwap( UpdateRV, netBIdList[i], RVaffListB[i], candABeforeColId, UpdateAbRV, UpdateBeRV ); //Updated RV, net id, RV net vec, swap B col id, 
//	routeVect = UpdateRV; //yusuke now test update
//        std::cout<<"Before and after\n";
//	printScore();
       }
     }
  }


//  std::cout <<"check f\n";

//then comapre updated and routeVect if better keep going if not return false

  auto tempUpdated = UpdateRV;
  auto scoreSort = routeVect;
//  bool suc; 
  int tempSamen=0;
  int scoreSamen=0;

  std::vector <bool> checkOptim; //purpose of this is to only allow optimized swap //yusuketest

  bool maxGone=false;

  std::cout<< "Gain check Begins!\n";  
  for (unsigned i=0; i < scoreSort.size(); i++ ){ //first filter if max score reduced
   std::cout << "AT RV row num = " << i <<"\n";
  
    std::sort ( scoreSort[i].begin(), scoreSort[i].end(), compareScore ); //sorting with score LOW being the higest

    std::sort ( tempUpdated[i].begin(), tempUpdated[i].end(), compareScore ); //sorting with score LOW being the higest

    if ( tempUpdated[i][0].hScore < scoreSort[i][0].hScore  ) maxGone=true;

    else if ( tempUpdated[i][0].hScore > scoreSort[i][0].hScore  ){

      std::cout << "Aft Max swap RV scr = " <<tempUpdated[i][0].hScore <<" :Bf Max swap RV scr = " <<scoreSort[i][0].hScore<<"\n";   
      std::cout << "#########Swapped RV exceeds the current worst RV score Then Exit#####\n";
      return false;
    }
  }

  //filter 2 begins
  if(maxGone == false){//a
    std::cout<< "Because no max reduction: check if the num of MAX RV score has increased\n"; 
    for (unsigned i=0; i < scoreSort.size(); i++ ){ //b


    
     if ( tempUpdated[i][0].hScore == scoreSort[i][0].hScore ){ //if the number of max (same) increases then flag //c



        for(unsigned j=1; j < tempUpdated[i].size(); j++){
	  if(tempUpdated[i][j].hScore == tempUpdated[i][0].hScore ) tempSamen= tempSamen + 1;
	
	  else break;
         }

        for(unsigned j=1; j < scoreSort[i].size(); j++){
	  if(scoreSort[i][j].hScore == tempUpdated[i][0].hScore ) scoreSamen= scoreSamen + 1;
	
	  else break;
        }
     }//c

    }//b
	 
     if (tempSamen >= scoreSamen ){
         std::cout <<"aft MAX scr num = "<<tempSamen<<" :bef MAX scr num = "<< scoreSamen<<"\n";
	 std::cout<< "#######The same max score has increased or same, Exit#####\n";
	 return false;
     }

  }//a


  std::cout <<"Routing Vector Constraint Passed\n"; //comeback
  
//swap the coordinate 
  auto cPath = findCriticalPath(_db,false);

  double cNetHpwl = cPath.second;
  
//  const dbNet& topNet = (*_db).getNetlist().getNetByIdx(netIdx) ;
  
  std::vector< std::pair<unsigned, double> > connNets;  	  


  unsigned bCellId;
  Point temB;

//  const dbCell& sCell = ( topNet ).getCellByIdx (1);

  Placement pl ( (*_db)._spatial.locations );
  


  const dbCell& aCell = (*_db).getNetlist().getCellByIdx (candAId);

  for ( auto nIt = aCell.netsBegin(); 
  		nIt != aCell.netsEnd();
  		nIt ++ )
    {
  	unsigned idx = (*nIt)->getId();
  	double hpwl = (*_db).getNetlist().evalHalfPerimCost 
  	                               ( idx, (pl), false);
  	
        connNets.push_back ( {idx, hpwl} );
    }	

  Point af = (pl)[ aCell.getIndex() ]; //pointA point 
  

    const dbCell& bCell = (*_db).getNetlist().getCellByIdx (candB.second);
    bCellId = bCell.getIndex();


  if(candB.first == true){  //if cand b is cell
//    const dbCell& bCell = (*_db).getNetlist().getCellByIdx (candB.second);
//    bCellId = bCell.getIndex();
    
    for ( auto nIt = bCell.netsBegin(); 
  		nIt != bCell.netsEnd();
  		nIt ++ )
      {
  	unsigned idx = (*nIt)->getId();
  	double hpwl = (*_db).getNetlist().evalHalfPerimCost 
  	                               ( idx, (pl), false);
  	
        connNets.push_back ( {idx, hpwl} );
      }	

    Point bf = (pl)[ bCell.getIndex() ]; //pointB declaired
    temB = bf;
    (pl)[ aCell.getIndex() ] = bf;
    (pl)[ bCell.getIndex() ] = af;
  }
  


  else{ //whitespace
    Point bf (routeVect[0][candB.first].minX, af.y); //pointB declaired

    (pl)[ aCell.getIndex() ] = bf;
  }



  
  for ( unsigned i=0; i < connNets.size(); i++ )
  {
	auto p = connNets.at (i);
	unsigned idx = p.first;
	double newHpwl = (*_db).getNetlist().evalHalfPerimCost 
	                               ( idx, (pl), false);
	
	//if by reordering one of the nets becomes critical net return
	if ( greaterThanDouble ( newHpwl, cNetHpwl ) )
	{
	  //reversing the placement reordering
	  if(candB.first == false) (pl)[ aCell.getIndex() ] = af; //whitespace

	  else{
    	    (pl)[ aCell.getIndex() ] = af;
   	    (pl)[ bCellId ] = temB;  /////////////////////
	  }
	  myWarn2 ( 0, "\tReordering introduces a new critical path. hpwl: ", newHpwl );
	  return false;	
	}
    	  
  }
  
  if(candB.first == true){ //cell swap validate
  (*_db)._spatial.locations [ aCell.getIndex() ] = (pl)[ aCell.getIndex() ];
  (*_db)._spatial.locations [ bCellId ] = (pl)[ bCellId ];
//  (*_db)._spatial.locations [ bCellId ] = (pl)[ bCellId ];
  }

  else{ //relocation validate whitespace
  (*_db)._spatial.locations [ aCell.getIndex() ] = (pl)[ aCell.getIndex() ];
  }

 
  auto newCPath = findCriticalPath(_db, false);
  
  std::cout << "\tNew critical net has HPWL: " << newCPath.second << "\n\n";  
  
 


//comapre if good then change coordinate and update route vect

  printScore();
  routeVect=UpdateRV;
  aboveChip = UpdateAbRV;
  belowChip = UpdateBeRV;
  std::cout<<"SWAP COMPLETE\n";
  printScore();
   

//return true

  return true;


 
} 

//asdfg




void RDP::alphaSwap( std::vector < std::vector<RScore> > &updatedRV, unsigned net_id,  std::vector < std::tuple <int,unsigned, unsigned> > netRV, int swapBCol, std::vector<RScore> &abChip, std::vector<RScore> &beChip){

  unsigned RvrowId = std::get<1>(netRV[0]); //getting row position
  std::cout <<"\n**Function alphaSwap is inoked\n";
  std::cout << "net " << net_id << " is in RV row = " << RvrowId <<"\n";
  std::cout << "Cell at the net left end is at " << std::get<2>(netRV[0]) << " and Right end is " << std::get<2>(netRV[ netRV.size()-1 ]) <<"\n";
  unsigned erase_netListId;
  int netRV_colId = std::get<2>(netRV[0]);
  int netRV_colId_Max = std::get<2>(netRV[ netRV.size()-1 ]);
  //alpha case 1 
//  if( swapBCol < std::get<2>(netRV[0]) ){
  if( swapBCol < netRV_colId ){
    std::cout<< "alpha case 1 invoked\n";
    for(int i = (std::get<2>(netRV[0]) - 1);  i >= swapBCol ; i--  ){
        
	if(std::get<0>(netRV[0]) == 0){
//	  std::cout <<"check a\n";
	  updatedRV[RvrowId][i].netList.push_back(net_id);
	  updatedRV[RvrowId][i].hScore = updatedRV[RvrowId][i].hScore + 1;
//	  std::cout <<"check a end\n";
	}
	else if (std::get<0>(netRV[0]) == 1){
//	  std::cout <<"check b\n";
	  beChip[i].netList.push_back(net_id);
	  beChip[i].hScore = beChip[i].hScore + 1;
//	  std::cout <<"check b end\n";
	}
	else if (std::get<0>(netRV[0]) == 2){
//	  std::cout <<"check c\n";
	  abChip[i].netList.push_back(net_id);
	  abChip[i].hScore = abChip[i].hScore + 1;
//	  std::cout <<"check c end\n";
	}
    }
    std::cout<<"\n";
  }


  //alpha case 2 
//  else if( (swapBCol > std::get<2>(netRV[0])) && (swapBCol < std::get<2>(netRV[ netRV.size()-1 ]) ) ){//g
  else if( (swapBCol > netRV_colId) && (swapBCol < netRV_colId_Max ) ){//g
    std::cout<< "alpha case 2 invoked\n";
    for(int i= std::get<2>(netRV[0]); i < swapBCol; i++  ){ //x

      if(std::get<0>(netRV[0]) == 0){ //k
        for(unsigned e=0; e < updatedRV[RvrowId][i].netList.size(); e++ ){ //y
	 if( updatedRV[RvrowId][i].netList[e] == net_id ){//L
	   erase_netListId = e;	  
	   updatedRV[RvrowId][i].netList.erase( updatedRV[RvrowId][i].netList.begin() + erase_netListId );

	   updatedRV[RvrowId][i].hScore = updatedRV[RvrowId][i].hScore - 1;
	  break;
	  } //L
	} //y
      }//k

      else if(std::get<0>(netRV[0]) == 1){//a
	for(unsigned e=0; e < beChip[i].netList.size(); e++ ){ //b
	  if( beChip[i].netList[e] == net_id ){//q
	      erase_netListId = e;
	      beChip[i].netList.erase( beChip[i].netList.begin() + erase_netListId );

	      beChip[i].hScore = beChip[i].hScore - 1;
	      break;
	  }//q
	}//b
      }//a



	else if(std::get<0>(netRV[0]) == 2){ //s
	  for(unsigned e=0; e < abChip[i].netList.size(); e++ ){ //d
	    if( abChip[i].netList[e] == net_id ){ //f
	      erase_netListId = e;
	      abChip[i].netList.erase( abChip[i].netList.begin() + erase_netListId );

	      abChip[i].hScore = abChip[i].hScore - 1;
	      break;
	    }//f
	  }//d
	}//s	         
    } //x

  }//g




  //alphac case 3 
//  else if( swapBCol > std::get<2>(netRV[ netRV.size()-1 ]) ){//Q
  else if( swapBCol > netRV_colId_Max ){//Q
    std::cout<< "alpha case 3 invoked\n";
//    std::cout<< "netRV.size()= " << netRV.size() <<"\n";
//    std::cout << "std::get<2>(netRV[0])=" << std::get<2>(netRV[0]) <<"\n";
    for(unsigned i= std::get<2>(netRV[0]); i < std::get<2>(netRV[ netRV.size()-1 ]); i++  ){ //x

//    std::cout <<"i= " <<i <<"\n";
//    std::cout <<"std::get<0>(netRV[0])= " <<std::get<0>(netRV[0]) <<"\n";
      if(std::get<0>(netRV[0]) == 0){ //k
        for(unsigned e=0; e < updatedRV[RvrowId][i].netList.size(); e++ ){ //y
	 if( updatedRV[RvrowId][i].netList[e] == net_id ){//L
	   erase_netListId = e;	  
	   updatedRV[RvrowId][i].netList.erase( updatedRV[RvrowId][i].netList.begin() + erase_netListId );

	   updatedRV[RvrowId][i].hScore = updatedRV[RvrowId][i].hScore - 1;
	  break;
	  } //L
	} //y
      }//k

      else if(std::get<0>(netRV[0]) == 1){//a
	for(unsigned e=0; e < beChip[i].netList.size(); e++ ){ //b
	  if( beChip[i].netList[e] == net_id ){//q
	      erase_netListId = e;
	      beChip[i].netList.erase( beChip[i].netList.begin() + erase_netListId );

	      beChip[i].hScore = beChip[i].hScore - 1;
	      break;
	  }//q
	}//b
      }//a



	else if(std::get<0>(netRV[0]) == 2){ //s
	  for(unsigned e=0; e < abChip[i].netList.size(); e++ ){ //d
	    if( abChip[i].netList[e] == net_id ){ //f
              erase_netListId = e;
	      abChip[i].netList.erase( abChip[i].netList.begin() + erase_netListId );

	      abChip[i].hScore = abChip[i].hScore - 1;
	      break;
	    }//f
	  }//d
	}//s
    } //x   
 

    for(int i=std::get<2>(netRV[ netRV.size()-1 ])+1; i <= swapBCol; i++ ){//A

	if(std::get<0>(netRV[0]) == 0){
	  updatedRV[RvrowId][i].netList.push_back(net_id);
	  updatedRV[RvrowId][i].hScore = updatedRV[RvrowId][i].hScore + 1;
	}
	else if (std::get<0>(netRV[0]) == 1){
	  beChip[i].netList.push_back(net_id);
	  beChip[i].hScore = beChip[i].hScore + 1;
	}
	else if (std::get<0>(netRV[0]) == 2){
	  abChip[i].netList.push_back(net_id);
	  abChip[i].hScore = abChip[i].hScore + 1;
	}
    }//A
  std::cout<<"\n";
  }//Q
       

 std::cout <<"***Function alphaSwap END\n\n";

//  std::cout << "EXPat01 = " << updated[0][0].hScore << "\n";
//  updated[0][0].hScore=updated[0][0].hScore+1;



  return ;
}
//std::vector < std::tuple <int,unsigned, unsigned> > RDP::searchNetinRV (unsigned net_id)
  


void RDP::betaSwap( std::vector < std::vector<RScore> > &updatedRV, unsigned net_id,  std::vector < std::tuple <int,unsigned, unsigned> > netRV, int swapBCol, std::vector<RScore> &abChip, std::vector<RScore> &beChip){

  std::cout <<"\n";
  std::cout <<"**Function betaSwap is invoked\n";

  unsigned erase_netListId;
  unsigned RvrowId = std::get<1>(netRV[0]); //getting row position

  std::cout << "net " << net_id << " is in RV row = " << RvrowId <<"\n";
  std::cout << "Cell at the net left end is at " << std::get<2>(netRV[0]) << " and Right end is " << std::get<2>(netRV[ netRV.size()-1 ]) <<"\n";


  std::cout <<"Rownum= " <<RvrowId << "\n";
  std::cout << "Type 0=middle, 1=btom, 2=top; Type = " << std::get<0>(netRV[0]) <<"\n";
  std::cout << "swapBcol= " << swapBCol <<"\n";
  std::cout <<"swapAcol= " << std::get<2>(netRV[ netRV.size()-1 ]) <<"\n";
  int netRV_colId = std::get<2>(netRV[0]);
  int netRV_colId_Max = std::get<2>(netRV[ netRV.size()-1 ]);
//  if( swapBCol == std::get<2>(netRV[ netRV.size()-1 ]) ) std::cout << "swap Affected pos is the same; thus no effect\n";
  if( swapBCol == netRV_colId_Max ) std::cout << "swap Affected pos is the same; thus no effect\n";

  //beta case 1 
//  else if( swapBCol > std::get<2>(netRV[ netRV.size()-1 ]) ){
  else if( swapBCol > netRV_colId_Max ){
    std::cout<< "beta case 1 invoked\n";
    std::cout << "std::get<2>(netRV[ netRV.size()-1 ]) + 1 = " << std::get<2>(netRV[ netRV.size()-1 ]) + 1 << " \n";
    for(int i = std::get<2>(netRV[ netRV.size()-1 ]) + 1;  i <= swapBCol ; i++  ){
	if(std::get<0>(netRV[0]) == 0){
	  updatedRV[RvrowId][i].netList.push_back(net_id);
          std::cout<<"updatedRV[RvrowId][" << i <<"].hScore= " << updatedRV[RvrowId][i].hScore <<"\n";
	  updatedRV[RvrowId][i].hScore = updatedRV[RvrowId][i].hScore + 1;
          std::cout<<"AftupdatedRV[RvrowId][" << i <<"].hScore= " << updatedRV[RvrowId][i].hScore <<"\n";
	}
	else if (std::get<0>(netRV[0]) == 1){
	  beChip[i].netList.push_back(net_id);
	  beChip[i].hScore = beChip[i].hScore + 1;
	}
	else if (std::get<0>(netRV[0]) == 2){
	  abChip[i].netList.push_back(net_id);
	  abChip[i].hScore = abChip[i].hScore + 1;
	}
    }
  }


  //beta case 2 
  else if( (swapBCol >= netRV_colId) && (swapBCol < netRV_colId_Max ) ){//g
//  else if( (swapBCol >= std::get<2>(netRV[0])) && (swapBCol < std::get<2>(netRV[ netRV.size()-1 ]) ) ){//g
    std::cout<< "beta case 2 invoked\n";
    for(int i= std::get<2>(netRV[ netRV.size()-1 ]); i > swapBCol; i--  ){ //x

      if(std::get<0>(netRV[0]) == 0){ //k
        for(unsigned e=0; e < updatedRV[RvrowId][i].netList.size(); e++ ){ //y
	 if( updatedRV[RvrowId][i].netList[e] == net_id ){//L
	   erase_netListId = e;	  
	   updatedRV[RvrowId][i].netList.erase( updatedRV[RvrowId][i].netList.begin() + erase_netListId );

	   updatedRV[RvrowId][i].hScore = updatedRV[RvrowId][i].hScore - 1;
	  break;
	  } //L
	} //y
      
      }//k

      else if(std::get<0>(netRV[0]) == 1){//a
	for(unsigned e=0; e < beChip[i].netList.size(); e++ ){ //b
	  if( beChip[i].netList[e] == net_id ){//q
	      erase_netListId = e;
	      beChip[i].netList.erase( beChip[i].netList.begin() + erase_netListId );

	      beChip[i].hScore = beChip[i].hScore - 1;
	      break;
	  }//q
	}//b
      
      }//a



	else if(std::get<0>(netRV[0]) == 2){ //s
	  for(unsigned e=0; e < abChip[i].netList.size(); e++ ){ //d
	    if( abChip[i].netList[e] == net_id ){ //f
              erase_netListId = e;
	      abChip[i].netList.erase( abChip[i].netList.begin() + erase_netListId );

	      abChip[i].hScore = abChip[i].hScore - 1;
	      break;
	    }//f
	  }//d
	}//s	         
    } //x
  std::cout<<"\n";
  }//g




  //alphac case 3 
//  else if( swapBCol < std::get<2>(netRV[ 0 ]) ){//Q
  else if( swapBCol < netRV_colId ){//Q
    std::cout<< "beta case 3 invoked\n";
//    std::cout<< "netRV.size()= " << netRV.size() <<"\n";
 //   std::cout << "std::get<2>(netRV[0])=" << std::get<2>(netRV[0]) <<"\n";
 //   std::cout << "std::get<0>(netRV[0])=" << std::get<0>(netRV[0]) <<"\n";
    for(unsigned i= std::get<2>(netRV[ netRV.size()-1 ]); i > std::get<2>(netRV[ 0 ]); i--  ){ //x
//    std::cout << "i= "<< i <<"\n";

      if(std::get<0>(netRV[0]) == 0){ //k
        for(unsigned e=0; e < updatedRV[RvrowId][i].netList.size(); e++ ){ //y
	 if( updatedRV[RvrowId][i].netList[e] == net_id ){//L
	   erase_netListId = e;	  
	   updatedRV[RvrowId][i].netList.erase( updatedRV[RvrowId][i].netList.begin() + erase_netListId );

	   updatedRV[RvrowId][i].hScore = updatedRV[RvrowId][i].hScore - 1;
   //        std::cout <<"note\n";
	  break;
	  } //L
	} //y
      }//k

      else if(std::get<0>(netRV[0]) == 1){//a
	for(unsigned e=0; e < beChip[i].netList.size(); e++ ){ //b
	  if( beChip[i].netList[e] == net_id ){//q
	      erase_netListId = e;
	      beChip[i].netList.erase( beChip[i].netList.begin() + erase_netListId );

	      beChip[i].hScore = beChip[i].hScore - 1;
	      break;
	  }//q
	}//b
      }//a



	else if(std::get<0>(netRV[0]) == 2){ //s
	  for(unsigned e=0; e < abChip[i].netList.size(); e++ ){ //d
	    if( abChip[i].netList[e] == net_id ){ //f
              erase_netListId = e;
	      abChip[i].netList.erase( abChip[i].netList.begin() + erase_netListId );

	      abChip[i].hScore = abChip[i].hScore - 1;
	      break;
	    }//f
	  }//d
	}//s
    } //x   
 
   
    for(int i=std::get<2>(netRV[ 0 ])-1; i >= swapBCol; i-- ){//A
//        std::cout <<"swapBCol= " << swapBCol << "\n";
//	std::cout<<"i= " << i <<"\n";
	if(std::get<0>(netRV[0]) == 0){
	  updatedRV[RvrowId][i].netList.push_back(net_id);
	  updatedRV[RvrowId][i].hScore = updatedRV[RvrowId][i].hScore + 1;
	}
	else if (std::get<0>(netRV[0]) == 1){
	  beChip[i].netList.push_back(net_id);
	  beChip[i].hScore = beChip[i].hScore + 1;
	}
	else if (std::get<0>(netRV[0]) == 2){
	  abChip[i].netList.push_back(net_id);
	  abChip[i].hScore = abChip[i].hScore + 1;
	}
    }//A
  std::cout<<"\n";
  }//Q
       


  std::cout << "***Function betaSwap is END\n";
//  std::cout << "EXPat01 = " << updated[0][0].hScore << "\n";
//  updated[0][0].hScore=updated[0][0].hScore+1;
  return ;
}





bool RDP::swapEx2(int rowRV, int colId, unsigned netId ){ //it is given target net_id and target slot to reduce the score

  std::cout << "\n**Function swapEx2 is invoked.\n";
  auto cellList = getCellidsByNetid(netId);  //cell Ids

  std::vector < unsigned > swapCand;    //bool 0 means lowwest 1 means highest in X

  Placement pl ( (*_db)._spatial.locations );
  
  
  std::sort( cellList.begin(), cellList.end(), CompareCellIdsByX( pl ) );   //xshort->xlarge cell id of the critical cells

 
  for(unsigned i=0; i < cellList.size(); i++){
    if( (*_db).getNetlist().getCellByIdx( cellList[i] ).isFixed() == false ) //only select movable cell
    swapCand.push_back( cellList[i] );
  }




  bool suc=false;

  for(unsigned i=0; swapCand.size() > i; i++ ){

    if( getCellX( cellList[0] ) == getCellX( cellList[ cellList.size()-1 ] )  ){ //two cells on the same x-axis then no swap occurs
    std::cout << "two cells on the same X then no reason to swap\n";
    break;  //two cells on the same X then no reason to swap
    }

    else if(cellList[0] == swapCand[i]){  //means that swap cad is equal or less than critical location left end of the net
    std::cout <<"Selected cell "<< swapCand[i] <<" will consider to be swapped by right cell\n";
    suc=swapRight( swapCand[i], rowRV, colId ); //swap with right of critcal location

      if(suc==true){
	 std::cout <<"Right Swap is Successful!\n";
	 break;
      }
    }

    else if(cellList[ cellList.size()-1 ] == swapCand[i]){  //means that swap cad is equal or less than critical location right end of the net
    std::cout <<"Selected cell " << swapCand[i] << " will consider to be swapped by left cell\n";
    suc=swapLeft( swapCand[i], rowRV, colId );//swap with left of critical location
      if(suc==true){
	 std::cout <<"Left Swap is Successful!\n";
	 break;
      }
    }
 
  }
     

    
   std::cout << "\n**Function swapEx2 is END: returning suc= " << suc <<"\n";

  return suc;
}





void RDP::windowInitiate(){
  windowCur= windowInit;
  return;
}



std::vector < std::tuple <int,unsigned, unsigned> > RDP::searchNetinRV (unsigned net_id){ //middle=0, bottom=1, top=2 
  											//first=type second=row third=column
  std::cout << "**Function searchNetinRV is invoked\n";

  std::vector < std::tuple <int,unsigned, unsigned> > netLocation;

  for(unsigned i=0; i < routeVect.size() ; i++){
    
    for(unsigned j=0; j < routeVect[i].size(); j++){
      
      for(unsigned k=0; k < routeVect[i][j].netList.size(); k++){
	if( net_id==routeVect[i][j].netList[k] ){
//	  std::cout <<"Net " <<net_id << " is found in RV[" << i<<"]["<<j<<"]\n";
//	  std::cout <<"RV Row = " << i <<" Column = " << j <<"\n";
	  netLocation.push_back( std::make_tuple(0,i,j) );
	}
      }
    }
  }
  
  for(unsigned i=0; i < belowChip.size(); i++ ){

    for(unsigned j=0; j < belowChip[i].netList.size(); j++){
      if( net_id == belowChip[i].netList[j]){
//	  std::cout <<"Net " <<net_id << " is found in belowChip[" << i<<"] (colunm)\n";
  //      std::cout<<"belowChip Vec column= " <<i <<"\n";
        netLocation.push_back( std::make_tuple(1,0,i) );
      }
    }
  }

  for(unsigned i=0; i < aboveChip.size(); i++ ){

    for(unsigned j=0; j < aboveChip[i].netList.size(); j++){
      if( net_id == aboveChip[i].netList[j]){
//	  std::cout <<"Net " <<net_id << " is found in aboveChip[" << i<<"] (colunm)\n";
  //      std::cout<<"aboveChip Vec column= " <<i <<"\n";
        netLocation.push_back( std::make_tuple(2,0,i) );
      }
    }
  }
 
 if(netLocation.size() == 0){
 std::cout << "ERROR!!!!!!!Net " <<net_id << " is not found in RV,aboveChip, or belowChip\n";
 }
  return netLocation;
}





void RDP::scoreAssign(int xFront, int xBack, int RVnum, unsigned net_id){


  std::cout << "**Function 'scoreAssign' is Invoked**" << "\n";


  if (xBack > (RowScore_num - 1) ) {  
//	std::cout << "In X direction, X.Back is beyond the Chip; thus X.Back is adjusted to the right end of chip" << "\n";
	xBack = RowScore_num - 1;  //meaning pad is beyond x postion
  }



  if (xFront < 0){
//	std::cout << "In X direction, X.Front is beyond the Chip; thus X.Front is adjusted to the left end of chip" << "\n";
	xFront = 0;  //meaning pad is beyond x postion
  }



  while ( (xFront == xBack) || (xFront < xBack) ){
 
//    std::cout<< "Matrix Position[" <<  RVnum << "]" << "[" << xFront <<"]\n";
    routeVect[ RVnum ][xFront].hScore = routeVect[ RVnum ][xFront].hScore + 1;  
    routeVect[ RVnum ][xFront].netList.push_back(net_id);  
    xFront = xFront + 1;
  }
  std::cout << "**Function 'scoreAssign' is End**" << "\n";
  return;
}


void RDP::scoreAssignAboveBelow(int xFront, int xBack, bool above, unsigned net_id){


  std::cout << "\n**Function 'scoreAssignAboveBelow' is Invoked**" << "\n";
  std::cout << "Net " << net_id << " will be added to X= " << above << " (x=0 Below) (x=1 Above) \n";
  


  if (xBack > (RowScore_num - 1) ) {  
	std::cout << "In X direction, X.Back is beyond the Chip; thus X.Back is adjusted to the right end of chip" << "\n";
	xBack = RowScore_num - 1;  //meaning pad is beyond x postion
  }



  if (xFront < 0){
	std::cout << "In X direction, X.Front is beyond the Chip; thus X.Front is adjusted to the left end of chip" << "\n";
	xFront = 0;  //meaning pad is beyond x postion
  }



  while ( (xFront == xBack) || (xFront < xBack) ){
 
    if(above==true){

    aboveChip[xFront].hScore = aboveChip[xFront].hScore + 1;  
    aboveChip[xFront].netList.push_back(net_id); 
    std::cout <<"In aboveChip[" << xFront << "], net= " << net_id << " is recorded\n";  
    }

    else{ 
    belowChip[xFront].hScore = belowChip[xFront].hScore + 1;  
    belowChip[xFront].netList.push_back(net_id);
    std::cout <<"In belowChip[" << xFront << "], net= " << net_id << " is recorded\n";
    }
    xFront = xFront + 1;
  }
  std::cout << "\n**Function 'scoreAssignAboveBelow' is END\n";
  return;
}









double RDP::thresSetter(double percent){

  auto cPath = findCriticalPath(_db,false);    //capturing the pair of critical net id and HPWL
  std::cout << "Critical HPWL Before rationized = " << cPath.second <<"\n";
  double cHPWL = cPath.second * percent;
  std::cout << "Critical HPWL After rationized = " << cHPWL <<"\n";
  return cHPWL;

}






void RDP::printScore(){  
/*
Purpose: To print the scores of each routing vector row
*/

  std::cout << "Row "<<  "x     |  ";
   	  for(unsigned j=0; j < routeVect[0].size() ; j++){

	    std::cout << "|"  <<   j;
	  } 

  std::cout << "|\n\n\n";



  std::cout << "Above" << "     |  ";

  for(unsigned j=0; j < aboveChip.size() ; j++){

    std::cout << "|"  <<   aboveChip[j].hScore;
  }

  std::cout << "|\n\n";	






  for(int i= routeVect.size() - 1; i > -1 ; i--){     //I need to test to see the values
	  std::cout << "Row "<< i << "     |  ";
  	  for(unsigned j=0; j < routeVect[i].size() ; j++){

	    std::cout << "|"  <<   routeVect[i][j].hScore;
	  }
	  std::cout << "|\n";	
   }

  std::cout << "\n";

  std::cout << "Below" << "     |  ";

  for(unsigned j=0; j < belowChip.size() ; j++){

    std::cout << "|"  <<   belowChip[j].hScore;
  }

  std::cout << "|\n\n";	


  return;
}









int RDP::getRowPos(double yPos){    
/*
Purpose: From the argument of Cell's y-axis position, return the row number
*/
return ( ( yPos - (*_db)._rowDefs->getYOffset() ) / (*_db)._rowDefs->getRowHeight() );
}






bool RDP::cellTopRow(double yPos){   
/*

Purpose: From the argument of Cell"s y-axis position, return 1 if it is located at the top.

*/
  
  if (yPos ==  getMaxRowPos()   ) return true;

  else return false;

}


 

bool RDP::cellBotmRow(double yPos){
/*
Purpose: From the argument of Cell's y-axis position, return 1 if it is located at the bottom.
*/


  if (yPos == (*_db)._rowDefs->stdRows[ 0 ].lowerLeftY ) return true;

  else return false;

}


void RDP::routeEstimate (unsigned maxIt){


  std::cout << "\n\n*****************Route Estimation**********************************\n\n";
  std::cout << "\n\tInitializing routablility estimation\n";

  	std::cout.setstate(std::ios_base::failbit);  //cancel cout begin

  std::pair<int, unsigned> passFilter1;

  std::vector <unsigned> filter2Net;  //this filter has nets in which cells on the same row
  std::vector <unsigned> filter3Net;  //this filter has nets jumping rows


  for (unsigned i=0; i<((*_db).getNetlist().getNumNets() ) ; i++){

    std::cout<<"-----------------Iteration " << i << "\n";
    passFilter1 = Filter1 ( i );

    if (passFilter1.first == 2){
	std::cout << "  Net " << i << " Added to Filter 2\n";
	filter2Net.push_back(i);
      

	}

    if (passFilter1.first == 3){
	std::cout << "  Net " << i << " Added to Filter 3\n";
	filter3Net.push_back(i);
	}

//  printScore();
//  std::cout<<"filter2Net.size()= " <<filter2Net.size()<<"\n";
//  std::cout<<"filter3Net.size()= " <<filter3Net.size()<<"\n";
  }//return;


  
  std::cout << "Filter 2 has " << filter2Net.size() << " nets total\n";   //assumes that 2 cells are int the row
  for(unsigned i=0; i < filter2Net.size(); i++ ){
	std::cout << "Filter 2 Cand NET ID " << filter2Net[i] << " \n";
	FilterAB ( filter2Net[i] );
      // if(filter2Net[i]==785) {std::cout<<"ASDFGH\n"; return;} //yusuketest

	

  }
//std::cout.setstate(std::ios_base::failbit);//cancel begin
//  printScore();

  std::cout << "Filter 3 has " << filter3Net.size() << " nets total\n"; 

  for(unsigned i=0; i < filter3Net.size(); i++ ){
	std::cout << "Filter 3 Cand NET ID " << filter3Net[i] << " \n";
	FilterAB ( filter3Net[i] );
//	printScore();
  }


 // printScore();

  std::cout << "\n\tStarting the swap to reduce the routing vector\n";









  windowInitiate();  //it does not have any impact to the current code for future optim item


std::cout.clear();  //cancel print end

    std::cout<< "BEFORE SWAP\n";
  printScore();


std::cout.setstate(std::ios_base::failbit);  //cancel cout begin







//exit(0);

//return;
 
//  std::cout <<"temp test find me\n";
//  Filter1(28);//test yusuke

  std::pair <bool, int> RVsuc[routeVect.size()];

  for(unsigned x=0; x < routeVect.size(); x++){
  RVsuc[x].first=true;
  RVsuc[x].second=x;
  }



if(maxIt != 0){	

  //int itrNum=30;
  int itrNum=maxIt;

  for(int i=0; i < itrNum; i++ ){

    for(unsigned x=0; x < routeVect.size(); x++){
      if(RVsuc[x].first==true){
        RVsuc[x].first=swapEx(RVsuc[x].second); //it returns false then it locks the optimization 
      }
    }
    //std::cout << "i= " << i <<"\n";
  }

//std::cout.clear();  //cancel print end

  for(unsigned x=0; x < routeVect.size(); x++){
  std::cout <<"0 is done= "<<RVsuc[x].first <<" row = " << RVsuc[x].second <<"\n" ;
  
  }


//rnd2

  for(unsigned x=0; x < routeVect.size(); x++){
  RVsuc[x].first=true;
  }

  for(int i=0; i < itrNum; i++ ){

    for(unsigned x=0; x < routeVect.size(); x++){
      if(RVsuc[x].first==true){
        RVsuc[x].first=swapEx(RVsuc[x].second); //it returns false then it locks the optimization 
      }
    }
    //std::cout << "i= " << i <<"\n";
  }

//rnd2


  for(unsigned x=0; x < routeVect.size(); x++){
  std::cout <<"0 is done= "<<RVsuc[x].first <<" row = " << RVsuc[x].second <<"\n" ;
  
  }

}

std::cout.clear();  //cancel print end

  std::cout<< "AFTER SWAP\n";
  printScore();// return;


  std::cout << "Adding to the passlegVECT\n";

  auto scoreSortRow = routeVect; //to sort RV row score

//  std::sort ( scoreSortRow.begin(), scoreSortRow.end(), compareScore ); //front is the higest score

  for(unsigned i=0; i < routeVect.size(); i++){

	  std::sort ( scoreSortRow[i].begin(), scoreSortRow[i].end(), compareScore ); //front is the higest score
	  passToLeag.push_back( scoreSortRow[i][0].hScore );

  }

  auto scoreSortTop = aboveChip;

   std::sort ( scoreSortTop.begin(), scoreSortTop.end(), compareScore ); //front is the higest score

  passToLeag.push_back( scoreSortTop[0].hScore );
return;
}


/*
	std::cout << "RowHeight=" << (*_db)._rowDefs->getRowHeight() << "\n";
	std::cout << "Rowsize=" << (*_db)._rowDefs->stdRows.size() << "\n"; 
	std::cout << "(*_db).stdRows[0]Xpos" << (*_db)._rowDefs->stdRows[0].lowerLeftX << "\n";
	std::cout << "getXoffset" << (*_db)._rowDefs->getXOffset() << "\n";
	std::cout << "getYoffset" << (*_db)._rowDefs->getYOffset() << "\n";
	std::cout << "phaseC = " << phaseC << "\n";
	std::cout << "(*_db).stdRows[0]=" << (*_db)._rowDefs->stdRows[0].lowerLeftY << "\n";
	std::cout << "(*_db).stdRows[1]=" << (*_db)._rowDefs->stdRows[1].lowerLeftY << "\n";
	std::cout << "(*_db).stdRows[2]=" << (*_db)._rowDefs->stdRows[2].lowerLeftY << "\n";
	std::cout << "(*_db).stdRows[3]=" << (*_db)._rowDefs->stdRows[3].lowerLeftY << "\n";
	std::cout << "(*_db).stdRows[4]=" << (*_db)._rowDefs->stdRows[4].lowerLeftY << "\n";
	std::cout << "(*_db).stdRows[5]=" << (*_db)._rowDefs->stdRows[5].lowerLeftY << "\n";
	std::cout << "Allthe info of stdrow[5]" << (*_db)._rowDefs->stdRows[5] << "\n";
	std::cout << "Allthe info of stdrow[4]" << (*_db)._rowDefs->stdRows[4] << "\n";
*/


void RDP::FilterAB (unsigned net_id) {


  auto cellList = getCellidsByNetid(net_id);  //cell Ids in net_id

  int rowNum;  // row difference in net

  std::vector <int> rowsItr;  //saves which routing vector to add score

  std::vector <double> xList;  

  std::vector <double> yList;

  int x_inc =   (*_db)._rowDefs->getChipWidth()  / RowScore_num;



  int xStartPos;
  int xEndPos;

  int rowPos;

  //std::pair <bool, unsigned> output;
  

  

  for(unsigned i=0; i < cellList.size(); i++){ //current

//  std::cout << "getCellX(cellList[i])=" << getCellX(cellList[i]) << "\n";
//  std::cout << "Cell x=" << (*_db).getNetlist().getCellByIdx( cellList[i] )._origin.x <<"\n";
   xList.push_back( getCellX(cellList[i]) );
   yList.push_back( getCellY(cellList[i]) );
  }

  std::sort(xList.begin(), xList.end(), compareLogic  );  //x-coordinate low -> High
  std::sort(yList.begin(), yList.end(), compareLogic  ); //y-coordinate low -> High

//  std::cout<<"yListback()=" << yList.back() <<"\n";

//  x_MaxMin = xList.back() - xList.front();   //X coordinate Difference

  xStartPos = ( xList.front() - (*_db)._rowDefs->getXOffset() ) / x_inc;  //x position of starting in array
  xEndPos = ( xList.back() - (*_db)._rowDefs->getXOffset() ) / x_inc;     //x position of ending in array
 


  rowNum = getRowNumDif(yList.back(), yList.front() );  //
  std::cout <<"Rowdifference is= " << rowNum <<"\n";

  std::vector <int> rowList;

  rowPos = getRowPos( yList.front() );  //row position is the lowesr row

  std::cout << "ROW Pos= "<< rowPos <<"\n";
  
  for(int i=0; (rowNum+1)>i; i++ ){  //Store the row numbers from ylow to yhigh
	rowList.push_back( rowPos );
	rowPos++;
  }


std::vector < std::pair<int, double> > RowScoreList;  //first row# second max score
auto scoreSort = routeVect; //now

for(unsigned n=0; n < scoreSort.size(); n++ ){
  std::sort ( scoreSort[n ].begin(), scoreSort[n].end(), compareScore );
  RowScoreList.push_back(   std::make_pair( n , scoreSort[n ][0].hScore )   );
}

  std::vector <std::pair <int, double> > priSel;   //int is order and double is total score
							//int 1 is to add top RV and int 2 is add below RV

  double totalScoreA=0;
  double totalScoreB=0; 
  

  if( rowList.size()==1 ){     //row list has row number from low to high
//  std::cout << "two cells are in the same row\n"; 
//  std::cout <<"rowList[0]= " <<rowList[0] <<"\n";

  if(( rowList.size()==1) && (rowList[0]==0) ) return;

//getting max position of 2 routing vector
  std::sort ( scoreSort[rowList[0] ].begin(), scoreSort[rowList[0] ].end(), compareScore ); //compare score of specified row   
  
  std::sort ( scoreSort[rowList[0] - 1].begin(), scoreSort[rowList[0] - 1].end(), compareScore ); //compare score of specified row - 1

  std::cout <<"xStartPos=" <<xStartPos <<"\n";

  std::cout<<"xEndPos= " <<xEndPos <<"\n";

  std::cout <<"scoreSort[rowList[0]][0].columnId= " <<scoreSort[rowList[0]][0].columnId <<"\n";

  std::cout <<"scoreSort[rowList[0]-1][0].columnId= " <<scoreSort[rowList[0]-1][0].columnId<<"\n";

//continue collecting id of sorted row of max score then check if it overlaps with desired candidates

//Begin Filter A

  if ( ( (xStartPos < scoreSort[rowList[0]][0].columnId) && (xEndPos < scoreSort[rowList[0]][0].columnId) ) || ( (xStartPos > scoreSort[rowList[0]][0].columnId) && (xEndPos > scoreSort[rowList[0]][0].columnId) )  ){
	//std::cout <<"Since no MAX in Upper routing vector, scores are added \n";
	//scoreAssign(xStartPos, xEndPos, rowList.front(), net_id);
        std::cout<<"A\n";
	for(int x=xStartPos; x <= xEndPos; x++ ){
	totalScoreA= totalScoreA + routeVect[ rowList[0] ][x].hScore;
	}

	priSel.push_back( std::make_pair(1, totalScoreA ));


  }

  if ( ((xStartPos < scoreSort[rowList[0]-1][0].columnId) && (xEndPos < scoreSort[rowList[0]-1][0].columnId)) || ((xStartPos > scoreSort[rowList[0]-1][0].columnId) && (xEndPos > scoreSort[rowList[0]-1][0].columnId)) ){
	//std::cout <<"Since no MAX in Lower routing vector, scores are added \n";
	//scoreAssign(xStartPos, xEndPos, rowList.front()-1, net_id);
	std::cout<<"B\n";
	for(int x=xStartPos; x <= xEndPos; x++ ){
	totalScoreB= totalScoreB +routeVect[ rowList[0]-1 ][x].hScore;
	}

	priSel.push_back( std::make_pair(2, totalScoreB ));
  }

//  std::cout<<"priSel.size()= "<<priSel.size() <<"\n";

  if( priSel.size() ==1 ){ //x

    if(priSel[0].first == 1){

      std::cout <<"Since no MAX in Upper routing vector, scores are added to upper \n";
      scoreAssign(xStartPos, xEndPos, rowList.front(), net_id);
    }


    else {
    	std::cout <<"Since no MAX in Lower routing vector, scores are added to lower \n";
	scoreAssign(xStartPos, xEndPos, rowList.front()-1, net_id);
    }
  }//x


  




  else if( priSel.size() ==2 ){  //means that it can be added to top or bottom

        std::cout <<"SHOWtScoreA= " << totalScoreA << " tScoreB= " << totalScoreB << "\n";

      if (totalScoreA < totalScoreB){  //case below is bigger, then add to above

      std::cout <<"tScoreA= " << totalScoreA << "tScoreB= " << totalScoreB << "\n";

      std::cout <<"Since no MAX in Upper routing vector, scores are added \n";

      scoreAssign(xStartPos, xEndPos, rowList.front(), net_id);

      }


      else if(totalScoreA > totalScoreB){ //opposite

      std::cout <<"tScoreA= " << totalScoreA << "tScoreB= " << totalScoreB << "\n";

      std::cout <<"Since no MAX in Lower routing vector, scores are added \n";

      scoreAssign(xStartPos, xEndPos, rowList.front()-1, net_id);

      }

    
      else if( (totalScoreA >= 0) && (totalScoreA == totalScoreB) ){  //if two are equal and larger than 0
      std::cout<<"equal and larger than 0\n";
        if ( scoreSort[rowList[0]][0].hScore > scoreSort[rowList[0]-1][0].hScore){ 
         std::cout << "below has lower max RV score so added to below\n";
         scoreAssign(xStartPos, xEndPos, rowList.front()-1, net_id);
        }

        else if ( scoreSort[rowList[0]][0].hScore < scoreSort[rowList[0]-1][0].hScore){ 
         std::cout << "above has lower max RV score so added to below\n";
         scoreAssign(xStartPos, xEndPos, rowList.front(), net_id);
        } 
       
     
        else {   

          int arb= rand() % 2; //generate 0 and 1 randomly

          std::cout <<"tScoreA= " << totalScoreA << "tScoreB= " << totalScoreB << "\n";

          std::cout <<"Since no MAX in Lower and Upper routing vector, scores are Randomly added \n";

          if (arb==1) scoreAssign(xStartPos, xEndPos, rowList.front(), net_id);

          else scoreAssign(xStartPos, xEndPos, rowList.front()-1, net_id);
        }
       }

     //ASDFGH

  } 

 
   
  else{  //priselect=0
  std::cout << "if both socre A & B equal to 0 total A= " << totalScoreA << " total B= " << totalScoreB << "\n";
 
    if ( scoreSort[rowList[0]][0].hScore > scoreSort[rowList[0]-1][0].hScore){ 
     std::cout << "below has lower max RV score so added to below\n";
     scoreAssign(xStartPos, xEndPos, rowList.front()-1, net_id);
    }

    else if ( scoreSort[rowList[0]][0].hScore < scoreSort[rowList[0]-1][0].hScore){ 
     std::cout << "above has lower max RV score so added to below\n";
     scoreAssign(xStartPos, xEndPos, rowList.front(), net_id);
    }
  
    else{//b

     int arb= rand() % 2; //generate 0 and 1 randomly

     std::cout <<" Randomly added ";

     if (arb==1){ 
	std::cout << "to the top RV\n" ;
	scoreAssign(xStartPos, xEndPos, rowList.front(), net_id);}

     else {
         std::cout << "to the below RV\n" ;
	 scoreAssign(xStartPos, xEndPos, rowList.front()-1, net_id);}
     }//b
  }//priselect=0
}

  

// End Filter A


//Begin Filter B for not cells overlapping in the same row case

  else {  //this else means that rowList is more than 1

  std::cout << "rowList size should be larger than 1 " << rowList.size() <<"\n"; //row list is the list of cell row

  double temp; //temporary high
  int tempId; //temporarly high c Id
//  double dif;
  std::vector < std::pair<int, double> > rowSlack;  //row list has the position

  std::vector < std::pair<int, double> > fairList;

 /*/orginal begin 
  for(int i=0; i < rowList.size()-1; i++ ){  //because row list num and rv num

       // if (rowList[i] == scoreSort.size() ) continue;
	std::sort ( scoreSort[rowList[i] ].begin(), scoreSort[rowList[i] ].end(), compareScore ); //compare score of specified row 
	temp = scoreSort[ rowList[i] ][0].hScore; //highest score
	dif=0;
	for (int j=0; j < scoreSort[ rowList[i] ].size(); j++ ){
	  if (scoreSort[ rowList[i] ][0].hScore > scoreSort[ rowList[i] ][j].hScore){
		dif = scoreSort[ rowList[i] ][0].hScore - scoreSort[ rowList[i] ][j].hScore;
		rowSlack.push_back( std::make_pair( rowList[i] ,dif ) );
		break;
	  }
	std::cout << "slack comparing with " << rowList[i] << "th are still the same\n";
	}

	if(dif==0) rowSlack.push_back( std::make_pair( rowList[i] ,dif ) );  //meaning that all the RV has the same score
	

  }

  std::sort (rowSlack.begin(), rowSlack.end(), compareSlack);  //sort the slack being the first array the low slack // dif low to high
  std::cout<< rowSlack[0].first <<" th position of dif slack value "<< rowSlack[0].second <<"\n";
  done=false;
  std::sort (RowScoreList.begin(), RowScoreList.end(), compareRowMax); //low to high score  //has row num and score low to high

  for(int k=0;k<RowScoreList.size(); k++ ){
	for(int g=0; g<rowSlack.size(); g++){
	  if( (rowSlack[g].first==RowScoreList[k].first) && (rowSlack[0].second == rowSlack[g].second )  ){
	    scoreAssign(xStartPos, xEndPos, rowSlack[g].first, net_id);
            done=true;
	    break;
	    }
	}
  if(done==true)  break;
  }
	
    

  if(done==false) scoreAssign(xStartPos, xEndPos, rowSlack[0].first, net_id);
  
  }
  *///original end

  bool done=false;       //switch on is prefered
  bool distriSwitch =1;  //switch ON = the value tends to be distributed in row //add score if it is not overlapping with max score in row
			// switch off= the value tends to be distributed in column  //add score  to smallest max row score

  double tempTotal=0;

  for(unsigned i=0; i < rowList.size()-1; i++ ){

    std::sort ( scoreSort[rowList[i] ].begin(), scoreSort[rowList[i] ].end(), compareScore ); //compare score of specified row 
    temp = scoreSort[ rowList[i] ][0].hScore; //highest score
    tempId= scoreSort[ rowList[i] ][0].columnId; //highest score c-id


   if(distriSwitch == 1){
     if( ((xStartPos < tempId) && (xEndPos < tempId)) || ((xStartPos > tempId) && (xEndPos > tempId))  ){

	std::cout << "Since in this RV " << rowList[i] <<" none max score is found. Thus add to the RV "<< rowList[i] <<"\n";
	//scoreAssign(xStartPos, xEndPos, rowList[i], net_id);
	done=true;
	tempTotal=0;

	for(int j=xStartPos; j <= xEndPos; j++ ){
	  tempTotal = tempTotal + routeVect[ rowList[i] ][j].hScore;
	}
	fairList.push_back( std::make_pair( rowList[i] ,tempTotal ) );
	//break;
       } 



     else{

       std::cout << "Violating max thus RV=" << rowList[i] << " is added to rowSlack vec\n";
	
  
       rowSlack.push_back( std::make_pair( rowList[i] ,temp ) );

     }
   }



   else { //only add to MIN max hscore row
    std::cout << "Violating max thus RV=" << rowList[i] << " is added to rowSlack vec\n";
	
  
    rowSlack.push_back( std::make_pair( rowList[i] ,temp ) );
   }
  } //end of for loop

 

  if(done == true){



    if(fairList.size() > 0){
  
      std::sort (fairList.begin(), fairList.end(), compareRowMax); //low to high score  //has row num and score low to high

      scoreAssign(xStartPos, xEndPos, fairList[0].first, net_id);
    }


    else if (fairList.size() == 0){

    std::sort (rowSlack.begin(), rowSlack.end(), compareRowMax); //low to high score  //has row num and score low to high


    scoreAssign(xStartPos, xEndPos, rowSlack[0].first, net_id);

    }
  }
      

  if(done == false){

    std::sort (rowSlack.begin(), rowSlack.end(), compareRowMax); //low to high score  //has row num and score low to high


    scoreAssign(xStartPos, xEndPos, rowSlack[0].first, net_id);

  }

  

}



return;

}









std::pair<int, unsigned> RDP::Filter1 (unsigned net_id){

  std::cout <<"**Function Filter 1 is invoked\n";
  std::cout <<"in Filter 1 Operated net = " << net_id <<"\n";

  auto cellList = getCellidsByNetid(net_id);  //cell Ids in net_id

  int rowNum;  // row difference in net

  std::vector <int> rowsItr;  //saves which routing vector to add score

  std::vector <double> xList;  

  std::vector <double> yList;

  int x_inc =   (*_db)._rowDefs->getChipWidth()  / RowScore_num;



  int xStartPos;
  int xEndPos;



  

  

  for(unsigned i=0; i < cellList.size(); i++){

//  std::cout << "getCellX(cellList[i])=" << getCellX(cellList[i]) << "\n";
//  std::cout << "Cell x=" << (*_db).getNetlist().getCellByIdx( cellList[i] )._origin.x <<"\n";
   xList.push_back( getCellX(cellList[i]) );
   yList.push_back( getCellY(cellList[i]) );
  }

  std::sort(xList.begin(), xList.end(), compareLogic  );  //x-coordinate low -> High

  std::sort(yList.begin(), yList.end(), compareLogic  ); //y-coordinate low -> High

  std::cout<<"yListback()=" << yList.back() <<"\n";

//  x_MaxMin = xList.back() - xList.front();   //X coordinate Difference

  xStartPos = ( xList.front() - (*_db)._rowDefs->getXOffset() ) / x_inc;  //x position of starting in array
  

  xEndPos = ( xList.back() - (*_db)._rowDefs->getXOffset() ) / x_inc;     //x position of ending in array
 


  rowNum = getRowNumDif(yList.back(), yList.front() );
  std::cout <<"Rowdifference is= " << rowNum <<"\n";

  if ( yList.back() > getMaxRowPos() ) {
  std::cout << "Pad above the chip then add to abovePlacement" << "\n";
  scoreAssignAboveBelow(xStartPos, xEndPos, true, net_id);
  return std::make_pair(0, 0);
  

  }

  else if ( yList.front() < (*_db)._rowDefs->getYOffset() ) {
  std::cout << "Pad below the chip then add to belowPlacement" << "\n";
  scoreAssignAboveBelow(xStartPos, xEndPos, false, net_id);
  return std::make_pair(0, 0);

  }


  else{  //current




  if (rowNum < 1){ //meaning 2 positions of y-axis are the same
	std::cout << "2 positions of y-axis are the same\n";

         if( cellTopRow( yList.front() ) ){

	  std::cout << "2 cells are at the top, Thus add to abovePlacement  " << "\n";
          scoreAssignAboveBelow(xStartPos, xEndPos, true, net_id);
	  return std::make_pair(0, 0);
         }

         else if ( cellBotmRow( yList.front() ) ){  //n

	  std::cout << "2 cells are at the bottom, Thus add to belowPlacement  " << "\n";
         //PUSH BACK TO NEW VECTOR OPRV
	  scoreAssignAboveBelow(xStartPos, xEndPos, false, net_id);
	  return std::make_pair(0, 0);
         }	 

         else{ //means that two cells overlap in the middle    row above and below vector addedwith the score

	  std::cout << "2 cells in the same row, not top or front\n";    //I need to push_back into net id list of next filter cand

	  return std::make_pair(2, net_id);
         }	
   }



  else if (rowNum == 1){   //this code assumes 2 cells in a net only  
		
	std::cout << "Two cells are located separately in y coordinates with 1 spot separated" << "\n";
	rowsItr.push_back(  ( yList.front() - getMinRowPos() ) / (*_db)._rowDefs->getRowHeight()    );
	scoreAssign(xStartPos, xEndPos, rowsItr[0], net_id);	
	return std::make_pair(0, 0);   //

  }

  else if (rowNum > 1){

	std::cout << "Two cells are located separated more than 1 spot vertically; Thus next candidates" << "\n";
	return std::make_pair(3, net_id);
  }

    
} 
/*
for(int i=0; i < rowNum; i++){   //i need to generate applicable rovec number   if row separate by 1 => 1 if 2 => 2

  rowsItr.push_back(  ( yList.back() - getMinRowPos() ) / (*_db)._rowDefs->getRowHeight() - 1  - i   )

}
*/    //above is new idea now i need to modify distribution like score divided by rowNum


  
//this case cells stay at the same pos

  // }

  std::cout << "WARNING!!!!!   I should not be seeing this message after inserting new items!!!" << "\n";
 

//  scoreAssign(xStartPos, xEndPos, rowsItr[0], net_id);

/*
  std::cout <<"Scoreinc= "<<  scoreInc <<"\n";

  if (xEndPos > (RowScore_num - 1) )  xEndPos= RowScore_num - 1;  //meaning pad is beyond x postion
 


  while ( (xStartPos == xEndPos) || (xStartPos < xEndPos) ){
  //std::cout<< "Matrix Position[" <<  rowsItr[0] << "]" << "[" << xStartPos <<"]\n";

 // routeVect[ rowsItr[0] ][xStartPos].hScore = routeVect[ rowsItr[0] ][xStartPos].hScore + 1;
 // if( rowsItr.size() == 2 ) routeVect[ rowsItr[1] ][xStartPos].hScore = routeVect[ rowsItr[1] ][xStartPos].hScore + 1;


  for (int p=0; p < rowsItr.size(); p++ ){
  std::cout<< "Matrix Position[" <<  rowsItr[p] << "]" << "[" << xStartPos <<"]\n";
  routeVect[ rowsItr[p] ][xStartPos].hScore = routeVect[ rowsItr[p] ][xStartPos].hScore + scoreInc;
  routeVect[ rowsItr[p] ][xStartPos].net_id.push_back(net_id);
  
  }

  std::cout << "row 0 slot 3 =" <<routeVect[ 0 ][ 3 ].net_id.size()<< "\n";

  xStartPos = xStartPos + 1;


 }
*/












//else std::cout<< "The y back is above the highest row\n";
  //std::sort(cellIdsinNet.begin(), cellIdsinNet.end(), CompareCellIdsByY( pl ) ); //ypos low-> high
 // double HPWL_YnetId = (*_db).getNetlist().getCellByIdx(cellIdsinNet.back())._origin.y- (*_db).getNetlist().getCellByIdx( cellIdsinNet.front() )._origin.y;


return std::make_pair(1, net_id);
}













std::vector<unsigned> RDP::getCellidsByNetid(unsigned &netId) const{

  std::vector<unsigned> CellIdsList;  
  const dbNet& temNet = (*_db).getNetlist().getNetByIdx(netId);
  std::cout << "\n\nCalling Function:  getCellidsByNetid(int &netId)" << "\n";
//  std::cout << "The net " << netId << " has the following cells" <<"\n";
  for(unsigned i=0; i < (temNet).getNumCells(); i++)
  {
	CellIdsList.push_back(temNet._cells[i]->getIndex() );
//        std::cout << "\t cell ID= " << temNet._cells[i]->getIndex() << "\n";
//	std::cout << i+1 << "th CELL  \n" << (*_db).getNetlist().getCellByIdx( temNet._cells[i]->getIndex() ) <<"\n\n";
  	
  }
//  std::cout <<"\n\n";
  return CellIdsList;
}





std::vector<unsigned> RDP::connNetIds(unsigned &cellId, unsigned &cNetId){ //asd

  
  std::vector<unsigned> netIds;
  const dbCell& tempCell = (*_db).getNetlist().getCellByIdx( cellId );
  
  
  for ( auto nIt = tempCell.netsBegin(); nIt != tempCell.netsEnd(); nIt ++ )
    {
  	unsigned idx = (*nIt)->getId();
  	if (idx == cNetId) continue;
  	//double hpwl = (*_db).getNetlist().evalHalfPerimCost( idx, (pl), false);
  	
	
	



        netIds.push_back(idx);
    }	








  return netIds;  
}



std::vector<unsigned> RDP::getAllNetIds(unsigned &cellId){ //asd

  
  std::vector<unsigned> netIds;
  const dbCell& tempCell = (*_db).getNetlist().getCellByIdx( cellId );
  
  
  for ( auto nIt = tempCell.netsBegin(); nIt != tempCell.netsEnd(); nIt ++ )
    {
  	unsigned idx = (*nIt)->getId();
  	
  	//double hpwl = (*_db).getNetlist().evalHalfPerimCost( idx, (pl), false);
        netIds.push_back(idx);
    }	

  return netIds;  
}



void RDP::routingVecGen (){  //editnow

  std::cout <<"Routing Vector Generation begins " << "\n";

//        std::cout << "RowHeight=" << (*_db)._rowDefs->getRowHeight() << "\n";
//	std::cout << "Rowsize=" << (*_db)._rowDefs->stdRows.size() << "\n"; 
//	std::cout << "(*_db).stdRows[0]Xpos" << (*_db)._rowDefs->stdRows[0].lowerLeftX << "\n";
//	std::cout << "getXoffset" << (*_db)._rowDefs->getXOffset() << "\n";
//	std::cout << "getYoffset" << (*_db)._rowDefs->getYOffset() << "\n";
//	std::cout << "phaseC = " << phaseC << "\n";
//	std::cout << "(*_db).stdRows[0]=" << (*_db)._rowDefs->stdRows[0].lowerLeftY << "\n";
//	std::cout << "(*_db).stdRows[1]=" << (*_db)._rowDefs->stdRows[1].lowerLeftY << "\n";
//	std::cout << "(*_db).stdRows[2]=" << (*_db)._rowDefs->stdRows[2].lowerLeftY << "\n";
//	std::cout << "(*_db).stdRows[3]=" << (*_db)._rowDefs->stdRows[3].lowerLeftY << "\n";
//	std::cout << "(*_db).stdRows[4]=" << (*_db)._rowDefs->stdRows[4].lowerLeftY << "\n";
//	std::cout << "(*_db).stdRows[5]=" << (*_db)._rowDefs->stdRows[5].lowerLeftY << "\n";
//	std::cout << "Allthe info of stdrow[5]" << (*_db)._rowDefs->stdRows[5] << "\n";
//	std::cout << "Allthe info of stdrow[4]" << (*_db)._rowDefs->stdRows[4] << "\n";
  double x_1;
  double x_inc;
  double yPos = (*_db)._rowDefs->getYOffset();
  x_inc =   (*_db)._rowDefs->getChipWidth()  / RowScore_num;
  int rVecNum;
  rVecNum = (*_db)._rowDefs->stdRows.size() - 1;
  
//  std::cout <<"rVecNum=" << rVecNum << "\n";

 // routeVect.reserve(rVecNum);


//  std::cout << "ChipWidth=" << (*_db)._rowDefs->getChipWidth() << "\n";
//  std::cout << "getXoffset" << (*_db)._rowDefs->getXOffset() << "\n";
//  std::cout << "Rowsize=" << (*_db)._rowDefs->stdRows.size() << "\n"; 
  //std::cout << "ChipHeight= "<< (*_db)._rowDefs->getChipHeight() << "\n";
 // std::cout <<"routeVect.size()=" << routeVect.capacity() << "\n";





  for(int i=0; i < rVecNum ; i++){     //I need to test to see the values
	x_1 = (*_db)._rowDefs->getXOffset();
	routeVect.push_back( std::vector<RScore> ());
  	for(int j=0; j < RowScore_num; j++){
  	  routeVect[i].push_back( RScore( x_1,  x_1 + x_inc,  0.00, j, yPos ));  // giving error

	  if(i==0){  //one excution to generate RV at above and below
		aboveChip.push_back( RScore( x_1,  x_1 + x_inc,  0.00, j, yPos ) );
		belowChip.push_back( RScore( x_1,  x_1 + x_inc,  0.00, j, yPos ) );
	  }
	  x_1 = x_1 + x_inc;
//	  std::cout << "routeVect[" << i <<"]" << "[" << j << "]=" << routeVect[i][j].minX << "," << routeVect[i][j].belowY  << "\n";
	  	  
	}
	yPos = yPos + (*_db)._rowDefs->getRowHeight();

   }

  std::cout <<"Routing Vector Generation END " << "\n";
  //std::cout << "routeVect[i][j]=" << routeVect[0][3].minX << "\n";
//  std::cout <<"routeVect.size()=" << routeVect.size() << "\n";
return;
}





bool RDP::moreThanPhase (std::vector <unsigned> &cellid) const{ //, std::vector <int> &mcellid ){
/*test


	std::cout <<"Ymax-Ymin= " <<( (*_db).getNetlist().getCellByIdx(cellid.back())._origin.y - (*_db).getNetlist().getCellByIdx(cellid.front())._origin.y ) << "\n";
	std::cout<< "Testing row jump=" << ( ( (*_db).getNetlist().getCellByIdx(cellid.back())._origin.y - (*_db).getNetlist().getCellByIdx(cellid.front())._origin.y ) / (*_db)._rowDefs->getRowHeight() ) << "\n";
*/
  double Y_max= (*_db).getNetlist().getCellByIdx(cellid.back())._origin.y;
  double Y_min= (*_db).getNetlist().getCellByIdx(cellid.front())._origin.y;
  int rowHeight= (*_db)._rowDefs->getRowHeight();
  

  
//if(  (( ( (*_db).getNetlist().getCellByIdx(cellid.back())._origin.y - (*_db).getNetlist().getCellByIdx(cellid.front())._origin.y ) / (*_db)._rowDefs->getRowHeight() ) > phaseC)    )
		
   // return true;
	
  //else return false;

  
  if (   ( (Y_max - Y_min) / rowHeight ) > phaseC   ) return true;


  else return false;

}



//Calculates the allownce move for YUP
double RDP::yAllowanceUpCalc(const unsigned &mCellid, const double &cPath,  unsigned &netId){  //affect Net id
 
  Placement pl ( (*_db)._spatial.locations );
  double yAllowance;
  double HPWL_netId = (*_db).getNetlist().evalHalfPerimCost ( netId, (pl), false); //may need to change auto or const 


  
  //auto HPWL_YnetId = (*_db).getNetlist().evalHalfPerimCostY ( &tpNet, (pl), false); //may need to change auto or const
  auto cellIdsinNet = getCellidsByNetid(netId);
  

  std::sort(cellIdsinNet.begin(), cellIdsinNet.end(), CompareCellIdsByY( pl ) ); //ypos low-> high
  double HPWL_YnetId = (*_db).getNetlist().getCellByIdx(cellIdsinNet.back())._origin.y- (*_db).getNetlist().getCellByIdx( cellIdsinNet.front() )._origin.y;

  std::cout << "In this net " << netId <<" :Y HPWL=" << HPWL_YnetId <<"\n";

  if (mCellid == cellIdsinNet.front() ) //Meaning mCell is at the Bottom of the net
  {  
	yAllowance = cPath - HPWL_netId + 2*( HPWL_YnetId );
	std::cout << "Function yAllowanceUpCalc: conNet " << netId << " has the moving cellid= " << mCellid << " at the BOTTOM of the net." << "\n";
	std::cout <<"\n the net has y-move allowance of " << yAllowance << "\n";
	return yAllowance;
  }

   if (mCellid == cellIdsinNet.back() ) //Meaning mCell is at the Top of the net
  {  
	yAllowance = cPath - HPWL_netId;
	std::cout << "Function yAllowanceUpCalc: conNet " << netId << " has the moving cellid= " << mCellid << " at the TOP of the net." << "\n";
	std::cout <<"\n the net has y-move allowance of " << yAllowance << "\n";
	return yAllowance;
  }

   //Meaning mCell is at the MIDDLE of the net
  yAllowance = cPath - HPWL_netId + 2*( (*_db).getNetlist().getCellByIdx( cellIdsinNet.back() )._origin.y - (*_db).getNetlist().getCellByIdx( mCellid )._origin.y );

  std::cout << "Function yAllowanceUpCalc: conNet " << netId << " has the moving cellid= " << mCellid << " at the MIDDLE of the net." << "\n";
  std::cout <<"\n the net has y-move allowance of " << yAllowance << "\n";
  return yAllowance;
 }




bool RDP::MoveUpLogic( unsigned &moveCellid,  unsigned &cNetId, const double &cNetHPWL){
  
  std::vector <unsigned> affectedNet = connNetIds( moveCellid, cNetId );
  std::vector <double> yDeltaAllow;
  for(unsigned i=0; affectedNet.size() > i; i++ )
	yDeltaAllow.push_back( yAllowanceUpCalc(moveCellid, cNetHPWL, affectedNet[i] ) );


  std::sort( yDeltaAllow.begin(), yDeltaAllow.end()  ,compare_Allowance); //small ->big

  if (yDeltaAllow.front() > ( (*_db)._rowDefs->getRowHeight() * phaseC )  ) return true;

  return false;
}






double RDP::yAllowanceDownCalc(const unsigned &mCellid, const double &cPath,  unsigned &netId){
 
  Placement pl ( (*_db)._spatial.locations );
  double yAllowance;
  double HPWL_netId = (*_db).getNetlist().evalHalfPerimCost ( netId, (pl), false); //may need to change auto or const 

  auto cellIdsinNet = getCellidsByNetid(netId);  

  std::sort(cellIdsinNet.begin(), cellIdsinNet.end(), CompareCellIdsByY( pl ) ); //ypos low-> high

  double HPWL_YnetId = (*_db).getNetlist().getCellByIdx(cellIdsinNet.back())._origin.y- (*_db).getNetlist().getCellByIdx( cellIdsinNet.front() )._origin.y;

  std::cout << "In this net, Y HPWL=" << HPWL_YnetId <<"\n";


  if (mCellid == cellIdsinNet.front() ) //Meaning mCell is at the Bottom of the net
  {  
	yAllowance = cPath - HPWL_netId;
	std::cout << "Function yAllowanceUpCalc: conNet " << netId << " has the moving cellid= " << mCellid << " at the BOTTOM of the net." << "\n";
	std::cout <<"\n the net has y-move allowance of " << yAllowance << "\n";
	return yAllowance;	
  }


   if (mCellid == cellIdsinNet.back() ) //Meaning mCell is at the Top of the net
  {  
	yAllowance = cPath - HPWL_netId + 2*( HPWL_YnetId );
	std::cout << "Function yAllowanceUpCalc: conNet " << netId << " has the moving cellid= " << mCellid << " at the TOP of the net." << "\n";
	std::cout <<"\n the net has y-move allowance of " << yAllowance << "\n";
	return yAllowance;	
  }

   //Meaning mCell is at the MIDDLE of the net
  yAllowance = cPath - HPWL_netId + 2*( (*_db).getNetlist().getCellByIdx( mCellid )._origin.y -  (*_db).getNetlist().getCellByIdx( cellIdsinNet.front() )._origin.y );

  std::cout << "Function yAllowanceUpCalc: conNet " << netId << " has the moving cellid= " << mCellid << " at the MIDDLE of the net." << "\n";
  std::cout <<"\n the net has y-move allowance of " << yAllowance << "\n";
  return yAllowance;
 }







bool RDP::MoveDownLogic( unsigned &moveCellid,  unsigned &cNetId, const double &cNetHPWL){
  
  std::vector <unsigned> affectedNet = connNetIds( moveCellid, cNetId );
  std::vector <double> yDeltaAllow;
  for(unsigned i=0; affectedNet.size() > i; i++ )
	yDeltaAllow.push_back(  yAllowanceDownCalc(moveCellid, cNetHPWL, affectedNet[i])  );


  std::sort( yDeltaAllow.begin(), yDeltaAllow.end()  ,compare_Allowance); //small ->big
 
  if (yDeltaAllow.front() > ( (*_db)._rowDefs->getRowHeight() * phaseC )  ) return true;

  return false;
}



double RDP::MoveRightCalc( unsigned &moveCellid,  unsigned &cNetId, const double &cNetHPWL, unsigned &MaxcCellid){  

  std::vector <unsigned> affectedNet = connNetIds( moveCellid, cNetId );
  std::vector <double> xDeltaAllow;

  double X_maxpos= (*_db).getNetlist().getCellByIdx( MaxcCellid )._origin.x;
  double mCellxpos= (*_db).getNetlist().getCellByIdx( moveCellid )._origin.x;

  for(unsigned i=0; affectedNet.size() > i; i++ )
	xDeltaAllow.push_back( xAllowanceRightCalc(moveCellid, cNetHPWL, affectedNet[i]) );

  std::sort( xDeltaAllow.begin(), xDeltaAllow.end()   ,compare_Allowance );

  if (X_maxpos < xDeltaAllow.front()) return( xAggrMove*( X_maxpos - mCellxpos) );

  else return( xModMove*( xDeltaAllow.front() - mCellxpos) );

}


double RDP::MoveLeftCalc( unsigned &moveCellid,  unsigned &cNetId, const double &cNetHPWL, unsigned &MincCellid){  

  std::vector <unsigned> affectedNet = connNetIds( moveCellid, cNetId );
  std::vector <double> xDeltaAllow;

  double X_minpos= (*_db).getNetlist().getCellByIdx( MincCellid )._origin.x; //mincCellid=Ccpathcell.front() //leftside of mcell
  std::cout << "Test of X_minpos which should be x-orgin of MIN of critical net " << X_minpos << "\n";
  double mCellxpos= (*_db).getNetlist().getCellByIdx( moveCellid )._origin.x;

  for(unsigned i=0; affectedNet.size() > i; i++ )
	xDeltaAllow.push_back( xAllowanceLeftCalc(moveCellid, cNetHPWL, affectedNet[i]) );  

  std::sort( xDeltaAllow.begin(), xDeltaAllow.end()   ,compare_Allowance );// Need MAX of(mis pos that can be)

  if (X_minpos > xDeltaAllow.back()){
  std::cout << "The value when whole xlength is open " << xAggrMove*( mCellxpos - X_minpos ) <<"\n";
 return( xAggrMove*( mCellxpos - X_minpos ) );
 }

  else{
 std::cout << "The value when whole xlength is NOT open " << xModMove*( mCellxpos - xDeltaAllow.back()) <<"\n";
 return( xModMove*( mCellxpos - xDeltaAllow.back()) );
}
}


double RDP::xAllowanceLeftCalc(const unsigned &mCellid, const double &cPath,  unsigned &netId){ //return the max x pos to be relocated
 
  Placement pl ( (*_db)._spatial.locations );
  double xAllowancePos;
  double HPWL_netId = (*_db).getNetlist().evalHalfPerimCost ( netId, (pl), false); //may need to change auto or const 

  auto cellIdsinNet = getCellidsByNetid(netId);  

  std::sort(cellIdsinNet.begin(), cellIdsinNet.end(), CompareCellIdsByX( pl ) ); //xpos low-> high

  double mCellXPos = (*_db).getNetlist().getCellByIdx( mCellid )._origin.x;

  double HPWL_XnetId = (*_db).getNetlist().getCellByIdx(cellIdsinNet.back())._origin.x- (*_db).getNetlist().getCellByIdx( cellIdsinNet.front() )._origin.x;

  std::cout << "In this net, X HPWL=" << HPWL_XnetId <<"\n";
  
  std::cout << "In this net, mCellid=" << mCellid <<"\n";
  std::cout << "In this net, cellIdsinNet.front()=" << cellIdsinNet.front() <<"\n";
  std::cout << "In this net, cellIdsinNet.front()=" << cellIdsinNet.front() <<"\n";

  if (mCellid == cellIdsinNet.back() ) //Meaning mCell is at the Right of the net //correct Assu
  {  
	xAllowancePos = mCellXPos - (cPath - HPWL_netId) - 2*( HPWL_XnetId );
	std::cout << "Function xAllowanceRightCalc: conNet " << netId << " has the moving cellid= " << mCellid << " at the Right of the net." << "\n";
	std::cout <<"\n The cell can relocate from " << mCellXPos <<" to " << xAllowancePos << "\n";
	return xAllowancePos;	
  }


   if (mCellid == cellIdsinNet.front() ) //Meaning mCell is at the Left of the net
  {  
	xAllowancePos = mCellXPos - ( cPath - HPWL_netId );
	std::cout << "Function xAllowanceUpCalc: conNet " << netId << " has the moving cellid= " << mCellid << " at the Left of the net." << "\n";
	std::cout <<"\n The cell can relocate from " << mCellXPos <<" to " << xAllowancePos << "\n";
	return xAllowancePos;	
  }

   //Meaning mCell is at the MIDDLE of the net
  xAllowancePos =  mCellXPos - (cPath - HPWL_netId) + 2*( (*_db).getNetlist().getCellByIdx( mCellid )._origin.x -  (*_db).getNetlist().getCellByIdx( cellIdsinNet.front() )._origin.x ) + mCellXPos ;

  std::cout << "Function xAllowanceUpCalc: conNet " << netId << " has the moving cellid= " << mCellid << " at the MIDDLE of the net." << "\n";
  std::cout <<"\n The cell can relocate from " << mCellXPos <<" to " << xAllowancePos << "\n";
  return xAllowancePos;
 }










 //double xAggrMove = 0.66;
 //  double xModMove = 0.5;



double RDP::xAllowanceRightCalc(const unsigned &mCellid, const double &cPath,  unsigned &netId){ //return the max x pos to be relocated
 
  Placement pl ( (*_db)._spatial.locations );
  double xAllowancePos;
  double HPWL_netId = (*_db).getNetlist().evalHalfPerimCost ( netId, (pl), false); //may need to change auto or const 

  auto cellIdsinNet = getCellidsByNetid(netId);  

  std::sort(cellIdsinNet.begin(), cellIdsinNet.end(), CompareCellIdsByX( pl ) ); //xpos low-> high

  double mCellXPos = (*_db).getNetlist().getCellByIdx( mCellid )._origin.x;

  double HPWL_XnetId = (*_db).getNetlist().getCellByIdx(cellIdsinNet.back())._origin.x- (*_db).getNetlist().getCellByIdx( cellIdsinNet.front() )._origin.x;

  std::cout << "In this net, X HPWL=" << HPWL_XnetId <<"\n";


  if (mCellid == cellIdsinNet.front() ) //Meaning mCell is at the Left of the net
  {  
	xAllowancePos = (cPath - HPWL_netId) + 2*( HPWL_XnetId ) + mCellXPos ;
	std::cout << "Function xAllowanceRightCalc: conNet " << netId << " has the moving cellid= " << mCellid << " at the LEFT of the net." << "\n";
	std::cout <<"\n The cell can relocate from " << mCellXPos <<" to " << xAllowancePos << "\n";
	return xAllowancePos;	
  }


   if (mCellid == cellIdsinNet.back() ) //Meaning mCell is at the Right of the net
  {  
	xAllowancePos = cPath - HPWL_netId + mCellXPos ;
	std::cout << "Function xAllowanceUpCalc: conNet " << netId << " has the moving cellid= " << mCellid << " at the RIGHT of the net." << "\n";
	std::cout <<"\n The cell can relocate from " << mCellXPos <<" to " << xAllowancePos << "\n";
	return xAllowancePos;	
  }

   //Meaning mCell is at the MIDDLE of the net
  xAllowancePos = cPath - HPWL_netId + 2*( (*_db).getNetlist().getCellByIdx( cellIdsinNet.back() )._origin.x -  (*_db).getNetlist().getCellByIdx( mCellid )._origin.x ) + mCellXPos ;

  std::cout << "Function xAllowanceUpCalc: conNet " << netId << " has the moving cellid= " << mCellid << " at the MIDDLE of the net." << "\n";
  std::cout <<"\n The cell can relocate from " << mCellXPos <<" to " << xAllowancePos << "\n";
  return xAllowancePos;
 }



bool RDP::moveExecuter(){

  auto cPath = (const_cast< DB*>(_db))->acquireSameHPWLLNet();
 
  bool suc=0;

  std::cout << "Calling function RDP::moveExecuter()\n\n"; 
  for(unsigned i=0; cPath.size() > i; i++){
    
    suc = RDP::minimizeMaxWLSubr(cPath[i].first, cPath[i].second );
    std::cout<< "End of " << i <<"th same net iteration " << "\n";
    std::cout << "There are total num of the same HPWL" <<  cPath.size() << "\n";
    if(suc) return true;

  }

  return false;

}





void RDP::minimizeMaxWLr 
	( unsigned maxIt )
{
	
  std::cout << "\n\n************YUSUKE***************************************\n\n";
  std::cout << "\n\tOptimizing the placement of movable cells\n";
//  std:: cout << "(*_db).getNetlist().getCellByIdx(87)._origin.x=" << (*_db).getNetlist().getCellByIdx(87)._origin.x <<"\n";
//  std:: cout << "(*_db).getNetlist().getCellByIdx(87)._origin.x=" << (*_db).getNetlist().getCellByIdx(88)._origin.x <<"\n";
//  std:: cout << "(*_db).getNetlist().getCellByIdx(87)._origin.x=" << (*_db).getNetlist().getCellByIdx(89)._origin.x <<"\n";	
  auto cPath = findCriticalPath(_db,false);    //capturing the pair of critical net id and HPWL
  double initHpwl = cPath.second;
	
  bool succ = true;
  for (unsigned i=0; i < maxIt; i++)
  {
    std::cout << "\n\n+_+_+_+_+_+_+_+_+_+Iteration " << i << " _+_+_+_+_+_+_+_+_+_+\n\n";
   // succ = minimizeMaxWLSubr ();
    	succ =moveExecuter(); //yusuketemp
	if ( !succ ) break;
  }

  cPath = findCriticalPath(_db,false);
  double finalHpwl = cPath.second;
  
  double reduction = 100 * (abs(finalHpwl - initHpwl) / initHpwl);
  

  
  std::cout << "\n\t Cell reordering reduced the unlegalized critical path from " << initHpwl << " to " << finalHpwl << "(" << reduction << "%)\n\n";
  
  std::cout << "\n\n*************YUSUKE**************************************\n\n";
  std::cout <<"\n\n\n\n\n\n\n\n\n\n";
  
  return;
}


void RDP::MoveCell(Placement& pl,unsigned cellId, double x, double y){ //newadd

  //Placement pl ( (*_db)._spatial.locations);

 // const dbCell& temCell = (*_db).getNetlist().getCellByIdx( cellId )
  std::cout << "Calling the function MoveCell\n";
  //std::cout << "Before \n" << (*_db).getNetlist().getCellByIdx( cellId );
 
  Point movReq(x,y);

  Point mCell = (pl) [cellId];

  std::cout << "Before " << mCell ;

  mCell.moveBy( movReq );
  (pl) [cellId] = mCell;
  (*_db)._spatial.locations [ cellId ] = (pl)[ cellId ];
  

  (*_db).getNetlistForSurgery().getCellByIdxSurgery( cellId ).setCoordinate( mCell );

  std::cout << "\nAfter \n" << (*_db).getNetlist().getCellByIdx( cellId );
  std::cout << "\nLocation aft.   " << (*_db)._spatial.locations [ cellId ] ;


//(pl)[ fCell.getIndex() ] = med_f
  return;
}




	
	
bool RDP::minimizeMaxWLSubr(unsigned netIdx, double cNetHpwl)	
{
			
//  auto cPath = (const_cast<const DB*>(_db))->findCriticalPath(false); //pair vector
//  unsigned netIdx = cPath.first; //current worst HPWL
//  double cNetHpwl = cPath.second; //HPWL
  
  
  std::cout << "Cnet ID is " << netIdx << "\n";
  std::cout <<"cell id 1 " << (*_db).getNetlist().getNetByIdx(netIdx)._cells[0]->getIndex() << "\n";
  std::cout <<"cell id 2 " << (*_db).getNetlist().getNetByIdx(netIdx)._cells[1]->getIndex() << "\n";

  //std::cout <<"1st CELL in cPath \n" << (*_db).getNetlist().getCellByIdx( cCellIds.front() ) <<"\n";


  const dbNet& topNet = (*_db).getNetlist().getNetByIdx(netIdx) ; // at dbNet critical net info




   
  

  if ( topNet.getType().isClock() )
  {
	myWarn2 (0, "\n\n\t\tCritical path is a clk signal. Net:", topNet );  //CLK net cannot be optimized
	return false;
  }
  
  if ( topNet.getNumCells() > 2)  //He is only doing 2 pins...... Should I update???
  {
	myWarn2 (0, "\n\n\nTotal cells connected to critical net is >2: ", topNet.getNumCells() );
	return false;
  }	  



  std::vector<unsigned> mCellIds;  //movable cells ids
  std::vector<unsigned> cCellIds;  //critical net cells ids
  for(unsigned i=0; i < (topNet).getNumCells(); i++)
  {
	cCellIds.push_back(topNet._cells[i]->getIndex() );
  	if( ( topNet ).getCellByIdx(i).isFixed() == false) mCellIds.push_back( topNet._cells[i]->getIndex() );  //movablecells id list
  }

  if(mCellIds.size() < 1) return false;  //if no movable cells then STOP

  //Testing cCellIds
  for(unsigned i=0; i <cCellIds.size();i++ ) std::cout<< "In the Critical net cCellId=" <<cCellIds[i] << "\n";
  





  Placement pl ( (*_db)._spatial.locations );
  
  	//std::cout <<"_design._cellLib.size()=" << (*_db).getNetlist().getNumCells() <<"\n"; //shows the number of cells in the chip
  
  std::sort( cCellIds.begin(), cCellIds.end(), CompareCellIdsByY( pl ) );   //yshort->ylarge cell id of the critical cells


  std::cout <<"1st CELL in cPath \n" << (*_db).getNetlist().getCellByIdx( cCellIds.front() ) <<"\n";   //Show Cell Info
  std::cout <<"\n2nd CELL in cPath \n" << (*_db).getNetlist().getCellByIdx( cCellIds.back() ) <<"\n";





  bool yMovefg =moreThanPhase(cCellIds); 

  
  std::cout<<"yMovefg=0 means that rows are not separated more than phase constraint of " << phaseC <<" at cPath: yMovefg=" << yMovefg  <<"\n";



  random_shuffle( mCellIds.begin(), mCellIds.end() ); //shuffling movingcells
  bool moveDonefg = false;
  double yMovevalue=0;
  if(yMovefg==true)  
  for(unsigned i=0; mCellIds.size() > i; i++)
  {
	if( cCellIds.front() == mCellIds[i] )  //cell move up
	{ 
	  std::cout << "\n\n*********Evaluation of moving cell Up begins\n\n"; 
	  std::cout << "Selcted Cell is " << mCellIds[i] <<"\n";
	  

	  if ( MoveUpLogic( mCellIds[i], netIdx, cNetHpwl  ) == true)
          {
          
	  yMovevalue = ( phaseC *  (*_db)._rowDefs->getRowHeight() );
          std::cout<<"Cell will move in y-axis by " << yMovevalue << "\n";
          MoveCell(pl,mCellIds[i], 0, yMovevalue );
	  moveDonefg=1;
  	  break;
          }
	

	}


	if( cCellIds.back() == mCellIds[i] ) //cell move down
	{
	  std::cout << "\n\n*********Evaluation of moving cell DOWN begins\n\n";
	  std::cout << "Selcted Cell is " << mCellIds[i] <<"\n";

	  if ( MoveDownLogic( mCellIds[i], netIdx, cNetHpwl  ) == true)
          {
	  
          //subtract cCell to phase constrain * Row height
  	  yMovevalue = ( -1 * phaseC *  (*_db)._rowDefs->getRowHeight() );
	  
	  std::cout<<"Cell will move in y-axis by " << yMovevalue << "\n";
	  MoveCell(pl,mCellIds[i], 0, yMovevalue );
	  moveDonefg=1;
  	  break;
          }
	
	}

  }
 

//  moveDonefg=true; //testing

   

  double XmovVal=0;  //the maximu value that x can move.....
  std::sort( cCellIds.begin(), cCellIds.end(), CompareCellIdsByX( pl ) );   //xshort->xlarge cell id of the critical cells


  if(moveDonefg == false)
  for(unsigned i=0; mCellIds.size() > i; i++)
  {
	if( cCellIds.front() == mCellIds[i] )  //cell move right
	{
  	  std::cout << "\n\n*********Evaluation of moving cell RIGHT begins\n\n";
	  std::cout << "Selcted Cell is " << mCellIds[i] <<"\n";

	  XmovVal = MoveRightCalc( mCellIds[i], netIdx, cNetHpwl, cCellIds.back() );
	  std::cout<<"****Cell will move in x-axis by " << XmovVal << "\n";
          //ADD cCell to phase constrain * Row height
          MoveCell(pl,mCellIds[i], XmovVal, 0);
	  moveDonefg=1;
  	  break;
        }  

	if( (cCellIds.back() == mCellIds[i]) )  //cell move left
	{
  	  std::cout << "\n\n*********Evaluation of moving cell LEFT begins\n\n";  //makesure the flow
	  std::cout << "Selcted Cell is " << mCellIds[i] <<"\n";

	  XmovVal = MoveLeftCalc( mCellIds[i], netIdx, cNetHpwl, cCellIds.front());
	  std::cout<<"****Cell will move in x-axis by " << XmovVal << "\n";
	  MoveCell(pl,mCellIds[i], (-1 * XmovVal), 0);
          //ADD cCell to phase constrain * Row height
	  moveDonefg=1;
  	  break;
        } 
  }

//jump

//test
  auto affnets=connNetIds( cCellIds.front(), netIdx ); //affected net id works!

  for(unsigned i=0; affnets.size() > i; i++  ) std::cout << "connected Net id of cCells is " << affnets[i] << "\n";


//test
	//for(int i=0; i <cCellIds.size();i++ )
	//std::cout<< "Cellid=" <<cCellIds[i] << "\n";

	//for(int i=0; i <mCellIds.size();i++ )
	//std::cout<< "moveCellid=" <<mCellIds[i] << "\n";
//test  
  
  	//double ylength = (*_db).getNetlist().evalHalfPerimCostY(topNet, pl, false );
  	//std::cout << "ylength =" << ylength << "\n";
/*
	std::cout << "RowHeight=" << (*_db)._rowDefs->getRowHeight() << "\n";
	std::cout << "Rowsize=" << (*_db)._rowDefs->stdRows.size() << "\n"; 
	std::cout << "(*_db).stdRows[0]Xpos" << (*_db)._rowDefs->stdRows[0].lowerLeftX << "\n";
	std::cout << "getXoffset" << (*_db)._rowDefs->getXOffset() << "\n";
	std::cout << "getYoffset" << (*_db)._rowDefs->getYOffset() << "\n";
	std::cout << "phaseC = " << phaseC << "\n";
	std::cout << "(*_db).stdRows[0]=" << (*_db)._rowDefs->stdRows[0].lowerLeftY << "\n";
	std::cout << "(*_db).stdRows[1]=" << (*_db)._rowDefs->stdRows[1].lowerLeftY << "\n";
	std::cout << "(*_db).stdRows[2]=" << (*_db)._rowDefs->stdRows[2].lowerLeftY << "\n";
	std::cout << "(*_db).stdRows[3]=" << (*_db)._rowDefs->stdRows[3].lowerLeftY << "\n";
	std::cout << "(*_db).stdRows[4]=" << (*_db)._rowDefs->stdRows[4].lowerLeftY << "\n";
	std::cout << "(*_db).stdRows[5]=" << (*_db)._rowDefs->stdRows[5].lowerLeftY << "\n";
	std::cout << "Allthe info of stdrow[5]" << (*_db)._rowDefs->stdRows[5] << "\n";
	std::cout << "Allthe info of stdrow[4]" << (*_db)._rowDefs->stdRows[4] << "\n";
*/

  

	
  const dbCell& fCell = ( topNet ).getCellByIdx (0); //cell A
  const dbCell& sCell = ( topNet ).getCellByIdx (1); // Cell B
	//std::cout << "( topNet ).getCellByIdx (0)" <<fCell._name <<"\n";
  	//std::cout << "( topNet ).getCellByIdx (1)" <<sCell._name <<"\n";


  //Placement pl ( (*_db)._spatial.locations ); //original pos
  std::vector< std::pair<unsigned, double> > connNets;
  for (unsigned j=0; j < 1; j++)
  {
	const dbCell& tCell = ( j == 0) ? 
			( topNet ).getCellByIdx (0) : 
			( topNet ).getCellByIdx (1)	;
   
    for ( auto nIt = tCell.netsBegin(); 
  		nIt != tCell.netsEnd();
  		nIt ++ )
    {
  	unsigned idx = (*nIt)->getId();
  	if (idx == netIdx) continue;
  	double hpwl = (*_db).getNetlist().evalHalfPerimCost 
  	                               ( idx, (pl), false);
  	
      connNets.push_back ( {idx, hpwl} );
    }	
  }  
  std::cout << "\n\t\tTotal # of connected nets: " << connNets.size() << "\n";

  //placing cells in the median point of curr loc and median of cell locs  


//(*_db).getNetlist().getCellByIdx( cellId )

/*   int test_gone=0;
  if(test_gone)
{
  //temp placement vals  
  Point tf = (pl)[ fCell.getIndex() ];
  Point ts = (pl)[ sCell.getIndex() ];

  Point med = getMedian( tf, ts);
  
  Point med_f = getMedian ( tf, med );
  Point med_s = getMedian ( ts, med );
  
  (pl)[ fCell.getIndex() ] = med_f;
  (pl)[ sCell.getIndex() ] = med_s;
} */

//Point tf = (pl)[ fCell.getIndex() ]



//Point mCell = (pl) [cellId];


  
  //std::cout << "\n\tCell reordering changed 1: " << tf << 
  //" to " << med_f << " and 2: " << ts << " to " << med_s << "\n";

  
  
  for ( unsigned i=0; i < connNets.size(); i++ )
  {
	auto p = connNets.at (i);
	unsigned idx = p.first;  //netid
	double newHpwl = (*_db).getNetlist().evalHalfPerimCost  //netHPWL
	                               ( idx, (pl), false);
	
	//if by reordering one of the nets becomes critical net return
	if ( greaterThanDouble ( newHpwl, cNetHpwl ) )
	{
	  //reversing the placement reordering
	  //(pl)[ fCell.getIndex() ] = tf;
	  //(pl)[ sCell.getIndex() ] = ts; 
	  myWarn2 ( 0, "\tReordering introduces a new critical path. hpwl: ", newHpwl );
	  return false;	
	}
    	  
  }
  
 

  //if no new critical paths are introduced, accept move  //Confirmingmove
  //(*_db)._spatial.locations [ fCell.getIndex() ] = (pl)[ fCell.getIndex() ];
  //(*_db)._spatial.locations [ sCell.getIndex() ] = (pl)[ sCell.getIndex() ];

  std::cout << "\n\tCell reordering reduced critical path hpwl from "
  << cNetHpwl << " to " << (*_db).getNetlist().evalHalfPerimCost ( netIdx, (pl), false) << "\n";
  
  auto newCPath = findCriticalPath(_db,false);
  unsigned Cnet=newCPath.first;

//  if((cNetHpwl == newCPath.second)  && (newCPath.first == netIdx) ){
  if((cNetHpwl == newCPath.second)  && (Cnet == netIdx) ){
  std::cout << "\tNew critical net has HPWL: " << newCPath.second << "\n";  
  std::cout << "\tNew critical net ID: " << newCPath.first <<"\n";
  std::cout <<"We cant optimize anymore!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" <<"\n";
  return false;


}

  std::cout << "\tNew critical net has HPWL: " << newCPath.second << "\n\n";  
  std::cout << "\tNew critical net ID: " << newCPath.first <<"\n";
  return true;
}


bool compare_Allowance(double a, double b){ //yusuke
	return (a  < b );
}

bool compareLogic(double a, double b){  //For comparing size
	return (a  < b );
}

bool compareSlack(const std::pair<int,double> &a, const std::pair<int,double> &b ){ // low to high
	return (a.second < b.second);
}

bool compareRowMax(const std::pair<int,double> &a, const std::pair<int,double> &b ){ // low to high
	return (a.second < b.second);
}


bool compareScore(const RScore& a, const RScore& b){   //returns the higest score in front
	return(a.hScore > b.hScore);
}
