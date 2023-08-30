<div align="center">

<h3> <b>qPlace: Placement for Single Flux Quantum Circuits </b> </h3>              

Written by **Soheil Nazar Shahsavani** and **Massoud Pedram**          
**SPORT Lab** <br> 
<a href="http://sportlab.usc.edu/">http://sportlab.usc.edu/</a> <br>
**ColdFlux Project** <br> 
<a href="http://coldflux.usc.edu">http://coldflux.usc.edu</a> <br>
**University of Southern California** <br> 
Los Angeles, CA 90089
      
                                                                              
</div>

The development is supported by Office of the Director of National Intelligence (ODNI),                      
Intelligence Advanced Research Projects Activity (IARPA) SuperTools Program, 
via the U.S. Army Research Office grant W911NF-17-1-0120. 

qPlace performs placement and clock tree synthesis for SFQ logic circuits.


# License:

Please refer to the LICENSE file.
                            

# Compile:

In the 'DetailedPlacement' directory:
```
 $ make
```
In the 'CTS/clockSyn/BSTsource1.2' directory:
```
 $ make
```
In the 'lib/SparseLib++/1.7/' directory:
```
 $ make sp
```
In the 'qPlace' directory:
```
 $ make
```
In the scripts directory do:
```
 $ chmod +x PlaceUtil-Lnx64.exe 
```
# Run:

In the 'qPlace' directory, run: ./qPlace -h

Usage : 
```
$ ./qPlace <CIRCUIT-DIRECTORY> <CIRCUIT-NAME (.aux File)> [options]
```

Input format is as follows: (Path To Benchmark) (AUX File Name) [optional]
```
+--------------- Description ---------------+
	Path To Benchmark: Absolute/Relative path to directory with the benchmark files, should end in '/'
	AUX File Name    : Name of the aux File Ex: Adder.aux

	-nGP [int]       : Number of Global Placement Iterations. Default: 100, Max: 400
	-CONF [string]       : Absolute/Relative path + Name of the configuration file
	-LEF [string]        : Absolute/Relative path + Name of the lef file
	-RDP             : Perform Routability Driven Detailed Placement(RDP). Default: off 
	-BAL             : Balance the clock tree by adding buffers and replacing the clock gates. Default: off
	-X               : Extra X spacing between adjacent logic cells in a row. Must be integer. Default: 0
	-Y               : Extra Y spacing between consecutive rows. Must be integer. Default: 0
	-LP              : Linear Program Solver (CTS): Default: 0
	                   Options 0 : no LP (Degrades quality of CTS in terms of max clock skew)
	-fixHold           : Internally calls the qSTA tool and fixes hold time violations. (Default: false)
	-LAYOUT            : Generates layouts for netlist. Default: false
	                           -AR [aspect ratio] (Width/Height) (Default: 1.0)
	                           -WS [whitespace %] (Default: 10)


+--------------------------------
```

Example:
```
$ ./qPlace ../results/KSA4_directory/ KSA4.aux -nGP 400 -BAL -LP 0 -fixHold  -LAYOUT -AR 2.0 -WS 10 -CONF ../qLib/1.4.1/qPlace_config.txt  -lef ../qLib/1.4.1//lef/lef_2_metals.lef
```

When the placement is completed, the following files will be generated in ../results/KSA4_directory/

KSA4_placed.aux 
KSA4_placed.nodes
KSA4_placed.nets
KSA4_placed.scl
KSA4_placed.pl

which contains placement information


Additionally, plot files (in the format of gnuplot plotting tool) are generated.
The figure can be plotted using the following command:

```
$ gnuplot ../results/KSA4_directory/KSA4_final.plt
```

Input and output formats are both in Bookshelf format.
For a complete description of this format see 

BookshelfFormat/BookshelfFormat.txt in this directory.

or 
 
<https://vlsicad.ucsd.edu/GSRC/bookshelf/Slots/Placement/plFormats.html>



# Directories & Files Structure:
```

├── lib: contains boost and Sparselib++ libraries.
├── src: Contains all the source files.
├── CTS: contains clock tree synthesis package, interfaces, etc.
├── DetailedPlacement: stand-alone program for performing legalization and detailed placement
└── scripts: contains scripts for running benchmarks and performing static timing analysis.
```
