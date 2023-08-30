#include "myAssert.h"


const char* SgnPartOfFileName(const char * fileName)
{
   const char *sp=fileName;
   const char *leftDelim=strchr(fileName,'/');
   const char *rightDelim=strrchr(fileName,'/');
   while(leftDelim!=rightDelim)
   {
       sp=++leftDelim;
       leftDelim=strchr(sp,'/');
   }
   return sp;
// static_cast<void>(pathDelimWindows);
// static_cast<void>(pathDelimUnix);
}

char* BaseFileName(char *fileName)
{
   char *leftDelim=strrchr(fileName,'/');
   if (leftDelim) leftDelim++;
   else leftDelim=fileName;
   char *rightDelim=strrchr(leftDelim,'.');
   if (rightDelim) *rightDelim='\0';
   return leftDelim;
}

