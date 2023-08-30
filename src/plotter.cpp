#include "plotter.h"

#define PIN_OFFSET 10.0
/* plots the whole core area to a .png image file */
/*void Plotter::plot_area (std::string filename){

	char cmd[1024];
	gnuplot_ctrl *h;	//a plotting handler used by gnuplot
	
	double coreAreaWidth = (*_db)._rowDefs->getChipBbox().getWidth ();
	double coreAreaHeight= (*_db)._rowDefs->getChipBbox().getHeight();

	h = gnuplot_init();
	gnuplot_resetplot(h);

	printf("\tPlotting  0%%"); fflush(stdout);

	//plot the cells
	for ( auto itC = (*_db).getNetlist().cellsBegin();
		  itC != (*_db).getNetlist().cellsEnd();
		  itC ++ ) 
    {
		auto id = (*itC)->getIndex();
		Point pos = (*_db)._spatial.locations[id];
		Point center = (*itC)->getCenter( pos );
		
		//print empty rectangle for a cell
		if(! (*itC)->isFixed() ) 
			sprintf(cmd, "set object rect from %lf,%lf to %lf,%lf fillstyle empty border 2;", 
		center.x - (*itC)->getWidth()  / 2, 
		center.y - (*itC)->getHeight() / 2, 
		center.x + (*itC)->getWidth()  / 2, 
		center.y + (*itC)->getHeight() / 2);

		//print filled rectangle for a pin
		else sprintf(cmd, "set object rect from %lf,%lf to %lf,%lf fc rgb 'grey' fs solid;", 
		center.x - (*itC)->getWidth()  / 2, 
		center.y - (*itC)->getHeight() / 2, 
		center.x + (*itC)->getWidth()  / 2, 
		center.y + (*itC)->getHeight() / 2);

		gnuplot_cmd(h, cmd);

		//just for printing the percentage of the completed plotting proccess
		//#if (PRINTING==FULL)
		//if((int)(print_ctr*100/cellsCtr) > last_print){
		//	last_print = (int)(print_ctr*100/cellsCtr);
		//	printf("\b\b\b%2d%%", last_print); fflush(stdout);
		//	}
		//print_ctr++;
		//#elif (PRINTING==COMPACT)
		//if((int)(print_ctr*100/cellsCtr) > last_print){
		//	last_print = (int)(print_ctr*100/cellsCtr);
		//	printf("\rPlotting\t[%2d%%]", last_print); fflush(stdout);
		//	}
		//print_ctr++;	
		//#endif 
		}


	//plot the core area borders
	sprintf(cmd, "set object rect from 0,0 to %lf,%lf lw 2.0 fillstyle empty border 1;", 
	coreAreaWidth, 
	coreAreaHeight);
	gnuplot_cmd(h, cmd);

	//make the plot to a pop-up window
	//gnuplot_cmd(h, "set term wxt persist");
	//gnuplot_cmd(h, "set terminal wxt title 'GORDIAN Placement';");

	//make the plot to a png image file
	sprintf(cmd, "set output '%s.png';", filename.c_str());
	gnuplot_cmd(h, cmd);
	gnuplot_cmd(h,"set terminal png size 1600,1200;" );


	//make the plot visible
	gnuplot_cmd(h, "set key off;");		//disable the legend
	sprintf(cmd, "set xrange [%lf:%lf]; set yrange [%lf:%lf];", coreAreaWidth * (PADDING_PERCENTAGE) * (-1.0), coreAreaWidth * (PADDING_PERCENTAGE + 1), coreAreaHeight * (PADDING_PERCENTAGE) * (-1.0), coreAreaHeight * (PADDING_PERCENTAGE + 1));
	gnuplot_cmd(h, cmd);
	gnuplot_cmd(h, "plot -100000;");

	printf("\rPlotting\t[OK] "); fflush(stdout);

	gnuplot_close(h);
} */

std::string Plotter::drawCell 
	(  dbCell* cell, const Point& center, bool writeCellNames,
	bool writeLevels) 
{
	std::string out ;
	std::string style;
	auto llx = center.x - (*cell).getWidth()  / 2 ;
    auto lly = center.y - (*cell).getHeight() / 2 ;
    auto urx = center.x + (*cell).getWidth()  / 2 ;
    auto ury = center.y + (*cell).getHeight() / 2 ;
	
	out += "set object " + std::to_string((*cell).getIndex()+1) + " rect from " 
	+ std::to_string (llx)
	+ ","
	+ std::to_string (lly)
	+ " to " 
	+ std::to_string ( urx )
	+ ","
	+ std::to_string ( ury );
	
	if(! (*cell).isFixed() ){
	  if ( !( *cell ).isClkSpl() )  
	    out += " lw 1 fs empty border lc rgb '#0000FF' ";
	  else
	    out += " lw 1 fs empty border lc rgb '#DC143C' ";
	}	
	else 
	{ //cell is Fixed (pads)
		if ( (int)(*cell).getIndex() == (*_db).getNetlist().findGCLKCell() ) //draws a red rectangle for gclk
			out += " fc rgb 'red' fs solid ";
		else
			out += " fc rgb 'grey' fs solid ";			
	} 
	
	if (writeCellNames && !writeLevels)
		out += ";\n set label " + std::to_string((*cell).getIndex()+1) + " at "+ std::to_string (llx+5.0) + ","+ std::to_string (lly-10.0) +" \"" + (*cell).getName()  + "\"   rotate by 90 font \"arial,8\"";
	    //rotate by 90

	if (!writeCellNames && writeLevels)
		out += ";\n set label " + std::to_string((*cell).getIndex()+1) + " at "+ std::to_string (llx+10.0) + ","+ std::to_string (lly+20.0) +" \"" + std::to_string((*cell).getLevel())  + "\"   font \"arial,8\"";

		
	out += ";\n";
	
	return out;
	
}


void Plotter::plot_area_gnu 
  ( std:: string filename, bool wCellN, bool wL) 
{
//Gnuplot gp;

	auto bb = *((*_db)._rowDefs);

	std::cout << "Plotting  0%%" << std::endl;

	std::string pltFileName = filename + ".plt";
	std::ofstream gp(pltFileName);
	//plot the cells
	for ( auto itC = (*_db).getNetlist().cellsBegin();
		  itC != (*_db).getNetlist().cellsEnd();
		  itC ++ ) 
    {
		auto id = (*itC)->getIndex();
		Point pos = (*_db)._spatial.locations[id];
		Point center = (*itC)->getCenter( pos );
		
		gp << drawCell ( (*itC), center, wCellN, wL);

	}
	
	double w = bb.getChipWidth();
	double pad = (PADDING * w);
	
	gp << "set object rect from " 
	<< std::to_string( bb.getXOffset() - pad )
	<< ","
	<< std::to_string (	bb. getYOffset() - pad  )
	<< " to "	
	<< std::to_string (bb.getChipXEnd() + pad  )
	<< ","
	<< std::to_string ( bb. getChipYEnd() + pad  )
	<<" lw 2.0 fillstyle empty border 1;\n", 
	

	//make the plot to a pop-up window
	//gnuplot_cmd(h, "set term wxt persist");
	//gnuplot_cmd(h, "set terminal wxt title 'GORDIAN Placement';");

	//make the plot to a png image file
	gp << "set output '" << filename << ".png'\n";
	gp << "set terminal png size 1600,1200;\n" ;


	//make the plot visible
	gp <<  "set key off;\n";		//disable the legend
	gp << "set xrange ["
	<< std::to_string( bb.getXOffset() - pad )
	<< ":"
	<< std::to_string (bb.getChipXEnd() + pad  )
	<< "];\n";

	
	gp << "set yrange ["
	<< std::to_string (	bb. getYOffset() - pad  )
	<< ":"
	<< std::to_string ( bb. getChipYEnd() + pad  )
	<< "];\n";
	gp <<  "plot -10000000;";

	
	gp.close();
	
	std::string cmd = "gnuplot " + pltFileName;
	system (cmd.c_str());
	//std::cout << "cmd: " << cmd << std::endl;
	cmd = "rm -r " + pltFileName;
	system (cmd.c_str());
	//std::cout << "cmd: " << cmd << std::endl;
	
	
	std::cout << "\rPlotting\t[Finished] \n";	
	std::cout << "\nSaved the plot: " << filename << ".png\n";
}

void Plotter::plotBoxPLT
  ( std::ofstream& stream, double x1, double y1, double x2, double y2 )
{
    stream << x1 << ", " << y1 << std::endl << x2 << ", " << y1 << std::endl
           << x2 << ", " << y2 << std::endl << x1 << ", " << y2 << std::endl
           << x1 << ", " << y1 << std::endl << std::endl;
		   
    //	<<" lw 2.0 fillstyle empty border 1;\n", 
		   
}



void 
Plotter::plotPlacementResult
 ( std:: string filename, bool wCellN, bool wL)
{
	auto bb = *((*_db)._rowDefs);
	double w = bb.getChipWidth();
	double h = bb.getChipHeight();
	double pad_x = Constants::PAD_OFFSET;//(PADDING * w);
	double pad_y = Constants::PAD_OFFSET;//(PADDING * h);
	//double pad = 0.0;
	std::cout << "Plotting  0%%" << std::endl;
	
    std::string pltFileName = filename + ".plt";	
    std::ofstream outfile( pltFileName );
    outfile << " " << std::endl;
    outfile << "set title \"name = " << filename << 
	" #Cells: " << std::to_string( (*_db).getNetlist().getNumCells() ) <<
	" #Nets: " << std::to_string( (*_db).getNetlist().getNumNets() ) << "\"" << "font \"Times, 22\"" << std::endl;
	
    outfile << "set size ratio 1" << std::endl;
    outfile << "set nokey" << std::endl << std::endl;
    //outfile << "plot[:][:] '-' w l lt 3 lw 2, '-' w l lt 1" << std::endl << std::endl;
    outfile << "plot[:][:] '-' w l lt 3, '-' w l lt 4, '-' w l lt 1, '-' w l lt 7, '-' w l lt 8, '-' w l lt 5, '-' w l lt 2, '-' w l lt 9" << std::endl << std::endl;
	
    outfile << "# bounding box" << std::endl;
    plotBoxPLT( outfile, bb.getXOffset() - pad_x, bb. getYOffset() - pad_y, bb.getChipXEnd() + pad_x , bb. getChipYEnd() + pad_y );
	
    outfile << "# die area" << std::endl;
    plotBoxPLT( outfile, 0, 0, 0, 0);
	
    //outfile << "EOF" << std::endl;
    outfile << "# modules" << std::endl << "0, 0" << std::endl << std::endl;
/*     for( size_t i = 0; i < _placement.numModules(); ++i ){
        Module &module = _placement.module(i);
        plotBoxPLT( outfile, module.x(), module.y(), module.x() + module.width(), module.y() + module.height() );
    }
 */  

	for ( auto itC = (*_db).getNetlist().cellsBegin();
		  itC != (*_db).getNetlist().cellsEnd();
		  itC ++ ) 
    {
        if ((*itC)->isFixed()) continue;
        if ((*itC)->isClkSpl()) continue; 		
		auto id = (*itC)->getIndex();
		Point pos = (*_db)._spatial.locations[id];
		plotBoxPLT(outfile, pos.x, pos.y, 
		   pos.x + (*itC)->getWidth(), pos.y + (*itC)->getHeight() );
	}
 
    outfile << "EOF\n" << std::endl << std::endl;

    outfile << "# fixed blocks" << std::endl << "0, 0" << std::endl << std::endl;
	for ( auto itC = (*_db).getNetlist().cellsBegin();
		  itC != (*_db).getNetlist().cellsEnd();
		  itC ++ ) 
    {
        if (!(*itC)->isFixed()) continue;		
		auto id = (*itC)->getIndex();
		Point pos = (*_db)._spatial.locations[id];		
		plotBoxPLT(outfile, pos.x, pos.y, 
		   pos.x + (*itC)->getWidth(), pos.y + (*itC)->getHeight() );
	}
    outfile << "EOF\n" << std::endl << std::endl;

    outfile << "# clk splitters" << std::endl << "0, 0\n" << std::endl << std::endl;

	for ( auto itC = (*_db).getNetlist().cellsBegin();
		  itC != (*_db).getNetlist().cellsEnd();
		  itC ++ ) 
    {
        //if ((*itC)->isFixed()) continue;
        if (!(*itC)->isClkSpl() ) continue; 		
		auto id = (*itC)->getIndex();
		Point pos = (*_db)._spatial.locations[id];
		plotBoxPLT(outfile, pos.x, pos.y, 
		   pos.x + (*itC)->getWidth(), pos.y + (*itC)->getHeight() );
	}

    outfile << "EOF\n" << std::endl << std::endl;
	
    outfile << "# cell move" << std::endl << "0, 0\n" << std::endl << std::endl;
    outfile << "EOF\n" << std::endl << std::endl;

    outfile << "# nets" << std::endl << "0, 0" << std::endl << std::endl;

	for ( auto itN = (*_db).getNetlist().netsBegin();
		  itN != (*_db).getNetlist().netsEnd();
		  itN ++ ) 
    {
      if ( (*itN)->getType().isClock() ) continue;		
      for (auto itC = (*itN)->cellsBegin();
	  itC !=  (*itN)->cellsEnd(); itC++ )
	  {
		auto id = (*itC)->getIndex();
        //finding out if the pin common between net & cell is input or output

        bool isInput = false;		
        const dbNet*      tmpNet; 
		for(auto pinItr = (*itC)->pinsBegin(); pinItr != (*itC)->pinsEnd(); pinItr++)
		{
			if(!(*pinItr)->isConnected() ) continue;
			tmpNet= &((*pinItr)->getNet() );
		    if( (*itN) == tmpNet )
              if ((*pinItr)->isDirInput()) isInput = true;
		}
		
		
		
		Point pos = (*_db)._spatial.locations[id];
		Point center = (*itC)->getCenter( pos );
		if (isInput) { center.x -= PIN_OFFSET; center.y -= PIN_OFFSET; }
	    else { center.x += PIN_OFFSET; center.y += PIN_OFFSET; }
        outfile << center.x << ", " << center.y << std::endl;		   
	  }
      outfile << std::endl;	  
	}	
    outfile << "EOF" << std::endl;

    outfile << "# clk nets" << std::endl << "0, 0" << std::endl << std::endl;

	for ( auto itN = (*_db).getNetlist().netsBegin();
		  itN != (*_db).getNetlist().netsEnd();
		  itN ++ ) 
    {
      if ( ! (*itN)->getType().isClock() ) continue;		
      for (auto itC = (*itN)->cellsBegin();
	  itC !=  (*itN)->cellsEnd(); itC++ )
	  {
		auto id = (*itC)->getIndex();
		Point pos = (*_db)._spatial.locations[id];
		Point center = (*itC)->getCenter( pos );		
        outfile << center.x << ", " << center.y << std::endl;		   
	  }
      outfile << std::endl;	  
	}	
    outfile << "EOF" << std::endl;

	
    outfile << "# dummy modules" << std::endl << "0, 0\n" << std::endl << std::endl;
    outfile << "EOF\n" << std::endl << std::endl;

    outfile << "# pin" << std::endl << "0, 0\n" << std::endl << std::endl;
    outfile << "EOF\n" << std::endl << std::endl;
	
	//outfile << "set output '" << filename << ".png'\n";
	//outfile << "set terminal png size 1920,1280;\n" ;
    outfile << "pause -1 'Press any key to close.'" << std::endl;
	//outfile <<  "plot -10000000;";
    outfile.close();

    /* if( isPrompt ){
        char cmd[ 200 ];
        sprintf( cmd, "gnuplot %s", outfilename.c_str() );
        if( !system( cmd ) ) { cout << "Fail to execute: \"" << cmd << "\"." << std::endl; }
    } */
		
	std::string cmd = "gnuplot " + pltFileName;
	//system (cmd.c_str());
	std::cout << "To see the output plot type cmd: \n$ " << cmd << std::endl;
	//cmd = "rm -r " + pltFileName;
	//system (cmd.c_str());
	//std::cout << "cmd: " << cmd << std::endl;
		
	std::cout << "\rPlotting\t[Finished] \n";	
	std::cout << "\nSaved the plot: " << filename << ".plt\n";
	//std::cout << "Saved the plot: " << filename << ".png\n";
	
}
