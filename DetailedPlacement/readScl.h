//Originally obtained from http://web.cs.ucla.edu/classes/cs258f/2003_spring/parser/src/
#ifndef   SCL_TO_stdCellRow
#define SCL_TO_stdCellRow

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <list>
#include <set>
#include <utility>
#include <map>
#include "stdCellRow.h"

class    sclParser
{
    public:
        StdCellRowDef *sclToStdCellRowDef(const char *design_name, const char * pathName);
        double llx, lly, rrx, rry;

    private:
        int unitScale;
        char sclFileName[80];
        char designName[80];
        StdCellRowDef *rowDef;
        void getFileName(const char *designName);
        void assignFileName(const char *fpName);
        void readFromSclFile(const char *filename);
        bool compareHead(const char *strHead, const char *key);

};
#endif
