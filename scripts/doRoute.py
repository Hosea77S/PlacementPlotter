import os
import sys
import argparse, os, timeit, sys, time, threading
from shutil import copyfile, copy2, move, rmtree, copy
import datetime
import shutil

for arg in sys.argv[1:]:
  print (arg)

if len(sys.argv[1:]) < 2 :
	exit();  

benchmarkPath = sys.argv[1:][0];
benchmarkName = sys.argv[1:][1];


b2dPath = "../../converters/bookshelf2def/"

qroutPath = "../../qGDR_0.5/"

STAPath = "../../qSTA"



copyfile (b2dPath + "/bookshelf2def", benchmarkPath+ "/bookshelf2def")
os.chdir (benchmarkPath)
bnchFullPath = os.getcwd()
print ('bnchFullPath is: ', bnchFullPath)
os.chmod ("bookshelf2def", 755)
cmd1 = " ./bookshelf2def " + benchmarkName + ".aux " 
print(cmd1)
os.system(cmd1)
copyfile(benchmarkName+".def", qroutPath + "/"+benchmarkName+".def")
os.remove ("bookshelf2def")
os.chdir (qroutPath)
#cmd2 = " ./qrouter_1.2 " + benchmarkName + ".def -c configs/route_2_metals.cfg"  
cmd2 = " ./qrouter " + benchmarkName + ".def -c configs/route_2_metals.cfg"  
print(cmd2)
os.system(cmd2)
#copyfile(benchmarkName+"_route.def", bnchFullPath)
shutil.copy( qroutPath+benchmarkName+"_route.def", bnchFullPath)
