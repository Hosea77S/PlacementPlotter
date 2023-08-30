#include "sclParser.h"



//=================== Implementations =======================//


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


void sclParser::readFromSclFile(std::string filename)
{
    std::string comment;
    std::ifstream fin;
    fin.open(filename);

    if (!fin)
    {
        std::cerr << "(E) Error opening input file: " << filename << std::endl;
        exit(-1);
    }

    //skip the title data
    getline(fin, comment);
    do
    {
	getline(fin, comment);
    } while (comment[0]=='#');

    std::string comm;
    int tot_nrow = 0;
    if (comment[0]=='N')
    {
        std::istringstream in(comment);
        in >> comment >> comm >> tot_nrow;
    }
    else
        fin >> comment >> comm >> tot_nrow;

    std::vector<double> botY;
    double rowW  = 0; double rowH = 0;
    for (int i = 0; i < tot_nrow; i++)
    {
        int row_y=0;
        int row_x=0;
        int row_height=0; int row_width=0;
		double  site_width = 0;
		double  site_spacing= 0;
		unsigned  site_num = 0;		
        char  head [20];
        char  head2[20];
        char  comm2[20];
		char  comm3[20];
		rowType t = HorizontalStdRow;
		
		char commentL[256];
        while(fin.getline(commentL, 256))
        {
            if(strncmp(commentL, "End", 3) == 0)
                break;
            if(compareHead(commentL, "Coordinate"))
                sscanf(commentL, "%s %c %d", head, comm3,&row_y);
            else if(compareHead(commentL, "Height"))
                sscanf(commentL, "%s %c %d", head, comm3,&row_height);
            else if(compareHead(commentL, "Sitewidth"))
                sscanf(commentL, "%s %c %lf", head, comm3,&site_width);
			else if(compareHead(commentL, "Sitespacing"))
                sscanf(commentL, "%s %c %lf", head, comm3,&site_spacing);			
            else if(compareHead(commentL, "SubrowOrigin"))
                sscanf(commentL, "%s %c %d %s %c %d", head, comm3,&row_x, head2, comm2, &site_num);
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
		rowWidth = std::max(rowW, rowWidth);
		rowHeight = std::max(rowH, rowHeight);
        if(i==0)
        {
            llx = row_x;
            rrx = row_x+row_width;
        }
        else
        {
            llx = std::min(llx, double(row_x));
            rrx = std::max(rrx, double(row_x+row_width));
        }
    }
    double stepY = botY[1]-botY[0];
    lly  = botY[0]+rowH/2-stepY/2;
    rry = lly + stepY*tot_nrow;
	
    fin.close();
}


dbRowDef* sclParser::sclToStdCellRowDef(std::string sclName)
{		
    unitScale = 1;
    rowDef = new dbRowDef;
    readFromSclFile(sclName);
    return(rowDef);
}

void sclParser::writeSclFile
  (std::string outFilename, dbRowDef rows)
{

    std::ofstream fout;
    fout.open(outFilename);
	//std::cout << "\n\tWriting to scl file   : \t" << outFilename << "\n\n\n";
	
    if (!fout)
    {
		myAssert2 (0, "(E) Error opening output file: " , outFilename);
    }

    fout << "UCLA scl 1.0\n";
    fout << "# Created by Soheil Nazar Shahsavani (nazarsha@usc.edu)\n\n";

    fout << "NumRows : " << rows.stdRows.size() << "\n\n";
    for (auto& i:rows.stdRows)
	{
      fout << "CoreRow ";
	  if (i.hvType == HorizontalStdRow) fout << "Horizontal";
	  else fout << "Vertical";
	  fout << "\n";
	  
	  fout << "  Coordinate    :   " << i.lowerLeftY << "\n";
	  fout << "  Height    :   " << i.height << "\n";
	  fout << "  Sitewidth    :   " << i.site_width << "\n";
	  fout << "  Sitespacing    :   " << i.site_spacing << "\n";
	  fout << "  Siteorient    :   1\n";
	  fout << "  Sitesymmetry    :   1\n";
	  fout << "  SubrowOrigin    :   " << i.lowerLeftX << "  NumSites  :   " << 
	  i.site_num<< "\n";
	  fout << "End\n";		
	}

    fout.close();	
}





