import linecache

import pandas as pd
import numpy as np
import re
import os
import time
import subprocess

sourcename = 'Cs137'
runmacpath = '/Users/roy/Documents/data?/Data from Sim/' + sourcename + '/runmac/'
runmacfileEx = ".mac"
eventactionpath = '/Users/roy/Downloads/Geant4-thesis-master/rdecay1/src/EventAction.cc'

for distence in range(25,36):
    for num in range(1000000,20000001,1000000):
        strnum = str(num)
        strdis = str(distence)
        name = sourcename + '-' + strdis + '-' + strnum
        runmacname = name + runmacfileEx
        runmac = open(runmacpath + runmacname,'w')
        distencenum = distence + 4.45
        strdisnum = str(distencenum)
        content = '/run/initialize\n' \
                  '/gps/particle ion\n' \
                  '/gps/ion 27 60\n' \
                  '/gps/direction -1 0 0\n' \
                  '/gps/pos/centre 24.45 0 0 cm\n' \
                  '/tracking/verbose 0\n' \
                  '/run/beamOn 10000000'
        runmac.write(content)
        eventaction = open(eventactionpath,'r+')
        theline = eventaction.readlines()
        theline[48] = ' FILE *opf1 = fopen(\"/Users/roy/Documents/data?/Data from Sim/' + sourcename + '/out' + sourcename + '.dat\",\"a\");\n'
        eventaction_new = open(eventactionpath, 'w+')
        eventaction_new.writelines(theline)
        eventaction.close()
        eventaction_new.close()
        os.system('make -j8')
        runmac = './rdecay01 ' + runmacpath + sourcename + '-' + strdis + '-' + strnum + runmacfileEx
        os.system('cd /Users/roy/Downloads/Geant4-thesis-master/rdecay1/build\nsource source /Users/roy/Downloads/geant4.10.07.p01/install/bin/geant4.sh\n' + runmac)
