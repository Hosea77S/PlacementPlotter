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


#include "timingParser.h"
#include <iostream>
#include <fstream>
#include <boost/regex.hpp>

std::string timingParser::getHoldRegExPattern()
{
  std::string re="(path)";	// Word 1
  re+="(\\s+)";	// White Space 1
  re+="(from)";	// Word 2
  re+="(\\s+)";	// White Space 2
  re+="((?:[A-Za-z0-9_]+))";	// Variable Name 1
  re+="(\\s+)";	// White Space 3
  re+="(to)";	// Word 3
  re+="(\\s+)";	// White Space 4
  re+="((?:[A-Za-z0-9_]+))";	// Variable Name 2
  re+="(,)";	// Any Single Character 1
  re+="(\\s+)";	// White Space 5
  re+="(hold)";	// Word 4
  re+="(\\s+)";	// White Space 6
  re+="(slack)";	// Word 5
  re+="(:)";	// Any Single Character 2
  re+="(\\s+)";	// White Space 7
  re+="([+-]?\\d*\\.*\\d*)(?![-+0-9\\.])";	// Float 1
  re+="(e*)([-+]*\\d*)";	// e 
  
  return re; 
}

std::string timingParser::getSlackRegExPattern()
{

  //"path from or2_638_n638 to and2_639_n639, setup slack: 5.4, hold slack: 2.1";

  std::string re="(path)";	// Word 1
  re+="(\\s+)";	// White Space 1
  re+="(from)";	// Word 2
  re+="(\\s+)";	// White Space 2
  re+="((?:[A-Za-z0-9_]+))";	// Variable Name 1
  re+="(\\s+)";	// White Space 3
  re+="(to)";	// Word 3
  re+="(\\s+)";	// White Space 4
  re+="((?:[A-Za-z0-9_]+))";	// Variable Name 2
  re+="(,)";	// Any Single Character 1
  re+="(\\s+)";	// White Space 5
  re+="(setup)";	// Word 4
  re+="(\\s+)";	// White Space 6
  re+="(slack)";	// Word 5
  re+="(:)";	// Any Single Character 2
  re+="(\\s+)";	// White Space 7
  re+="([+-]?\\d*\\.*\\d*)(?![-+0-9\\.])";	// Float 1
  re+="(e)?"; //0 or 1 time
  re+="([-+]?\\d*)";
  re+="(,)";	// Any Single Character 3
  re+="(\\s+)";	// White Space 8
  re+="(hold)";	// Word 6
  re+="(\\s+)";	// White Space 9
  re+="(slack)";	// Word 7
  re+="(:)";	// Any Single Character 4
  re+="(\\s+)";	// White Space 10
  re+="([+-]?\\d*\\.*\\d*)(?![-+0-9\\.])";	// Float 2
  re+="(e)?"; //0 or 1 time
  re+="([-+]?\\d*)";
	
  return re;	
  	
}


std::vector< tuple4dStr >
  timingParser::readSlackFile (std::string fileName)
{

  std::vector< tuple4dStr > out;	

  std::ifstream fin;
  fin.open(fileName);
  if (!fin)
	myWarn2(0, "(E) Error opening input file: ", fileName);


  std::string line;
  std::string pattern = getSlackRegExPattern();  
  boost::regex rePattern(pattern);
  

  bool f;
  do {
    f = (bool) getline(fin, line);	  
	if ((line.c_str())[0]=='#')
	{
	  //f = (bool) getline(fin, line);
      continue;	  
	}
      		
    boost::smatch match;
    boost::regex_search(line, match, rePattern);

    if (match.size() == 0){
	  f = (bool) getline(fin, line);
      continue;	  		
	}	
		
/*      for (unsigned i=0; i < match.size(); i++)
      std::cout << i << ":" << match[i] << " ";
    std::cout << "\n";  
 */
	
	//changed on 1.21.2020 to comply with qSSTA v.1.7
    std::string s_slack =  match.str(17) + match.str(18) + match.str(19);
    std::string h_slack =  match.str(27) + match.str(28) + match.str(29);
    
	h_slack.erase(remove_if(h_slack.begin(), h_slack.end(), isspace), h_slack.end());
	s_slack.erase(remove_if(s_slack.begin(), s_slack.end(), isspace), s_slack.end());
	
	
	out.push_back( std::make_tuple( match.str(5), match.str(9),  h_slack, s_slack) );
	
  } while (f);
 		
  return out;	  	
}


std::vector< tuple3dStr >
  timingParser::readHoldSlackFile (std::string fileName)
{

  std::vector< tuple3dStr > out;	

  std::ifstream fin;
  fin.open(fileName);
  if (!fin)
	myWarn2(0, "(E) Error opening input file: ", fileName);


  std::string line;
  std::string pattern = getHoldRegExPattern();  
  boost::regex rePattern(pattern);
  

  bool f;
  do {
    f = (bool) getline(fin, line);	  
	if ((line.c_str())[0]=='#')
	{
	  //f = (bool) getline(fin, line);
      continue;	  
	}
      		
    boost::smatch match;
    boost::regex_search(line, match, rePattern);

    if (match.size() == 0){
	  f = (bool) getline(fin, line);
      continue;	  		
	}	
		
/*     for (unsigned i=0; i < match.size(); i++)
      std::cout << i << ":" << match[i] << " ";
    std::cout << "\n";  */

    //std::string::size_type sz;	
	
    std::string slack =  match.str(17);//, NULL);		
	if (match.size() > 18)
    for (unsigned i=18; i<match.size();i++)
      slack += match.str(i);		
        		
	out.push_back( std::make_tuple( match.str(5), match.str(9),slack) );
	
  } while (f);
 	
	
  return out;	
}
