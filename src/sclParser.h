//Originally obtained from http://web.cs.ucla.edu/classes/cs258f/2003_spring/parser/src/

#ifndef SCLPARSER_H
#define SCLPARSER_H

#include "dbRowDef.h"
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <list>
#include <set>
#include <utility>
#include <map>


class    sclParser
{
    public:
		sclParser():llx(0), lly(0), rrx(0), rry(0), rowWidth(0), rowHeight(0){}
        dbRowDef *sclToStdCellRowDef(std::string );
        double llx, lly, rrx, rry;
		double rowWidth, rowHeight;

    void writeSclFile (std::string fileName, dbRowDef dbRows);
    private:
        int unitScale;
        std::string sclFileName;
        dbRowDef *rowDef;
        void readFromSclFile(std::string  filename);
        bool compareHead(const char *strHead, const char *key);

		
};


#endif
