#include "common.h"


std::string getCurrentDateTime()
{

   // current date/time based on current system
   time_t now = time(0);

   tm *ltm = gmtime(&now);
   std::string td;

   // print various components of tm structure.
   td += std::to_string(1900 + ltm->tm_year) + "_";
   td += std::to_string(1 + ltm->tm_mon)+ "_";
   td += std::to_string(ltm->tm_mday)+ "_";
   td += std::to_string((ltm->tm_hour)%24)+ "_";
   td += std::to_string(ltm->tm_min)  + "_";
   //td += std::to_string(ltm->tm_sec) ;

   return td;   
}


//https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
bool checkFileExists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}
