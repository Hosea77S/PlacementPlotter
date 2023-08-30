import os
import sys
import argparse, os, timeit, sys, time, threading
from shutil import copyfile, copy2, move, rmtree, copy
import datetime
import shutil
import re

#for arg in sys.argv[1:]:
print (sys.argv[1:])

if len(sys.argv[1:]) < 2 :
	exit();  

#command line args: benchmarkPath benchmarkName(w/o .aux) STA_commands: ex -PLACEMENT -SETUP -HOLD -ROUTING -LOGIC	
cmdArgs = sys.argv[1:]
benchmarkPath = cmdArgs[0];
benchmarkName = cmdArgs[1];
rptHold = False
if "-RPT_HOLD" in cmdArgs:
  cmdArgs.remove("-RPT_HOLD")
  rptHold = True  

lefFileName =   "../../qLib/1.4.1/lef/lef_2_metals.lef"
if "-LEF" in cmdArgs:
  idx = cmdArgs.index("-LEF")
  if ( idx+1 < len(cmdArgs) ):
    lefFileName = cmdArgs[idx+1]  

num_metals = 2
#finding the number of metal layers from the name of the lef file
rex = r"lef_([0-9])_metals"
match = re.search(rex, lefFileName, re.IGNORECASE)
if match:
  try:
    tmp_num = match.group(1)
    if int(tmp_num) in range(2,8):
      num_metals = int(tmp_num)
  except: print("Warning: Could not parse the number of metal layers.")


curDir = os.getcwd()

b2dPath = "../converters/bookshelf2def/"
os.chdir (b2dPath)
b2dPath = os.getcwd()
os.chdir(curDir)
STAPath = "../qSSTA/"
os.chdir(STAPath)
STAPath = os.getcwd()
os.chdir(curDir)


#converting bookshelf 2 def
copyfile (b2dPath + "/bookshelf2def", benchmarkPath+ "/bookshelf2def")
os.chdir (benchmarkPath)
bnchFullPath = os.getcwd()
print ('bnchFullPath is: ', bnchFullPath)
os.chmod ("bookshelf2def", 755)
cmd1 = " ./bookshelf2def " + benchmarkName + ".aux " + " -M " + str(num_metals) +  " -lef " + lefFileName
print(cmd1)
os.system(cmd1)
os.remove ("bookshelf2def")

#creating a new directory for STA/SSTA
staDirCreated = False
staIdx = 0

staOrgCirName= benchmarkName+'-'+str(datetime.date.today()) 
staCirName = staOrgCirName+ "_" + str(staIdx)
staCirDir = STAPath+'/Circuits/'+staCirName
#print ('Initial staCirDir:', staCirDir)

while staDirCreated==False:
  if staIdx > 10000: 
    raise Exception('Error creating a new folder for sta')
  try:
    os.mkdir( staCirDir );
    print ('Created directory ', staCirDir)  
    staDirCreated = True  
  except:
    #print('An error occured trying to read the file.', exec)
    #print ('Failed to create Folder ', staCirDir, ' Exists')  
    staIdx +=1
    staCirName = staOrgCirName+ "_" + str(staIdx)
    staCirDir = STAPath+'/Circuits/'+staCirName  

copyfile(benchmarkName+".def", staCirDir+'/'+staCirName+'_route.def') #for placement only, the file that is copied should not have _route.def in the suffix

os.chdir(STAPath+'/'+'Sources')
staCmd = 'python3 qSSTA.py '+ staCirName + '/' + staCirName + '_route '
for arg in cmdArgs[2:]:
  staCmd += arg + ' '
  
print (staCmd)
os.system(staCmd)

#moving generated sta files to the corresponding directory under Circuits/
print ('Changing dir to: ', staCirDir)
os.chdir(staCirDir)

#report hold time violations
#assumption: benchmarkName ends with '_placed'
if rptHold:
  srcPath = staCirName+'_route_PLACEMENT_skew.slack' 
  desPath = bnchFullPath + "/" + benchmarkName[:-7] + "_hold.slack"
  print ('cp ', srcPath, ' ', desPath)
  shutil.copy( srcPath, desPath  )
  #the problem is benchmarkPath is relative to inital loc, and not qsta/circuits path

