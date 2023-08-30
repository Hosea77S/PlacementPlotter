//Originally obtained from http://web.cs.ucla.edu/classes/cs258f/2003_spring/parser/src/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <math.h>
#include "readScl.h"
#include "stdCellRow.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <algorithm>

using namespace std;

bool sclParser::compareHead(const char *strHead, const char *key)
{
    char tmp_str[80];
    unsigned int i;
    for (i = 0; i < strlen(strHead); i++)
    {
        if (strHead[i] != ' ')
            break;
    }
    int j=0;
    for (; i<strlen(strHead); i++)
        tmp_str[j++] = strHead[i];

    int key_len =strlen(key);
    if(strncmp(tmp_str, key, key_len)==0)
        return true;
    else return false;
}


void sclParser::readFromSclFile(const char *filename)
{
    char comment[256];
    ifstream fin;
    fin.open(filename);

    if (!fin)
    {
        cerr << "(E) Error opening input file: " << filename << endl;
        exit(-1);
    }

    //skip the title data
    fin.getline(comment, 256);
    do
    {
        fin.getline(comment, 256);
    }while (comment[0]=='#');

    char comm[20];
    int tot_nrow = 0;
    if (comment[0]=='N')
    {
        istringstream in(comment);
        in >> comment >> comm >> tot_nrow;
    }
    else
        fin >> comment >> comm >> tot_nrow;

    vector<double> botY;
    double rowW, rowH;
    for (int i = 0; i < tot_nrow; i++)
    {
        int row_y;
        int row_x=0;
        int row_height, row_width;
		double  site_width;
		double  site_spacing;
		unsigned  site_num;		
        char head[20];
        char head2[20];
        char comm2[20];
		rowType t = HorizontalStdRow;
		
        while(fin.getline(comment, 256))
        {
            if(strncmp(comment, "End", 3) == 0)
                break;
            if(compareHead(comment, "Coordinate"))
                sscanf(comment, "%s %c %d", head, comm,&row_y);
            else if(compareHead(comment, "Height"))
                sscanf(comment, "%s %c %d", head, comm,&row_height);
            else if(compareHead(comment, "Sitewidth"))
                sscanf(comment, "%s %c %lf", head, comm,&site_width);
			else if(compareHead(comment, "Sitespacing"))
                sscanf(comment, "%s %c %lf", head, comm,&site_spacing);			
            else if(compareHead(comment, "SubrowOrigin"))
                sscanf(comment, "%s %c %d %s %c %d", head, comm,&row_x, head2, comm2, &site_num);
        }
        row_x *= unitScale;
        row_y *= unitScale;
        row_width = unitScale*(site_width*site_num);;
        row_height *= unitScale;

        rowDef->stdRows.push_back(SingleRow(row_x, row_y, row_width, row_height, t));
		SingleRow& curCoreRow = rowDef->stdRows.back();
		curCoreRow.site_width = site_width;
		curCoreRow.site_spacing = site_spacing;
		curCoreRow.site_num = site_num;
		
        botY.push_back(row_y);
        rowH = row_height;
        rowW= row_width;
        if(i==0)
        {
            llx = row_x;
            rrx = row_x+row_width;
        }
        else
        {
            llx = min(llx, double(row_x));
            rrx = max(rrx, double(row_x+row_width));
        }
    }
    double stepY = botY[1]-botY[0];
    lly  = botY[0]+rowH/2-stepY/2;
    rry = lly + stepY*tot_nrow;

    fin.close();
}


StdCellRowDef  *sclParser::sclToStdCellRowDef(const char *fileName, const char * pathName)
{
	char * auxFileName = (char *) malloc(1 + strlen(pathName)+ strlen(fileName) );
    strcpy(auxFileName, pathName);
    strcat(auxFileName, fileName);

	
    unitScale = 1;
    getFileName(auxFileName);
	
	char * sclName = (char *) malloc(1 + strlen(pathName)+ strlen(sclFileName) );
	strcpy(sclName, pathName); strcat(sclName, sclFileName);		
	
    rowDef = new StdCellRowDef;
    readFromSclFile(sclName);
    return(rowDef);
}


void   sclParser::assignFileName(const char *fpName)
{
    char fileNameSuffix[80];
    int len = strlen(fpName);
    int head=0;
    for(int i=len-1; i>=0; i--)
    {
        if(fpName[i] == '.')
        {
            head = i;
            break;
        }
    }

    int j = 0;
    for(int i=head+1; i<len; i++)
        fileNameSuffix[j++]=fpName[i];
    fileNameSuffix[j++]= '\0';
    if(strncmp(fileNameSuffix, "scl", 3)==0)
        strcpy(sclFileName,fpName);
}


void   sclParser::getFileName(const char *auxName)
{
    char fpname[80];
    sclFileName[0]='\0';
    ifstream fin;
    fin.open(auxName);
    if(!fin)
    {
        cerr << "(E) Error opening input file: "<<auxName<<endl;
        exit(-1);
    }
    while( fin >> fpname)
    {
        assignFileName(fpname);
    }
    fin.close();
    if( strlen(sclFileName)==0)
    {
        cerr<<"wrong aux file: "<<auxName<<" can not find *.scl filename\n";
        exit(-1);
    }
}
