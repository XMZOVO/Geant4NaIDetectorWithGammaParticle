import linecache

import pandas as pd
import numpy as np
import re
import os
import time
import subprocess

sourcename = 'Am241'
runmacpath = '/Users/roy/Documents/Geant4EX/lrd_v1/build/data/' + sourcename + '/runmac/'
runmacfileEx = ".mac"
runactionpath = '/Users/roy/Documents/Geant4EX/lrd_v1/src/RunAction.cc'

for distence in range(27,36):
    for num in range(1000000,20000001,1000000):
        strnum = str(num)
        strdis = str(distence)
        name = sourcename + '-' + strdis + '-' + strnum
        runmacname = name + runmacfileEx
        runmac = open(runmacpath + runmacname,'w')
        distencenum = distence + 4.45
        strdisnum = str(distencenum)
        content = '/run/initialize\n'\
                '/gps/source/intensity 1.\n'\
                '/gps/particle gamma\n'\
                '/gps/pos/centre ' + strdisnum +' 0 0 cm\n'\
                '/gps/direction -1 0 0\n'\
                '/gps/ene/mono 0.059 MeV\n\n'\
                '/run/printProgress 1000000\n'\
                '/run/beamOn ' + strnum
        dataname = name + '.root'
        runmac.write(content)
        runaction = open(runactionpath,'r+')
        theline = runaction.readlines()
        theline[48] = "    G4String fileName = \"/Users/roy/Documents/Geant4EX/lrd_v1/build/data/" + sourcename + "/" + dataname + "\";\n"
        runaction_new = open(runactionpath, 'w+')
        runaction_new.writelines(theline)
        runaction.close()
        runaction_new.close()
        os.system('make -j4')
        runmac = './lrdrun ' + runmacpath + sourcename + '-' + strdis + '-' + strnum + runmacfileEx
        os.system('cd /Users/roy/Documents/Geant4EX/lrd_v1/build\nsource /Users/roy/Downloads/geant4.10.07.p01/install/bin/geant4.sh\n' + runmac)
