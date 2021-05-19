import linecache

import pandas as pd
import numpy as np
import re
import os
import time
import subprocess

sourcename = 'Eu152'
runmacpath = '/Users/roy/Documents/Geant4EX/lrd_v1/build/data/' + sourcename + '/runmac/'
runmacfileEx = ".mac"
runactionpath = '/Users/roy/Documents/Geant4EX/lrd_v1/src/RunAction.cc'

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
                  '/gps/source/intensity 28.\n' \
                  '/gps/particle gamma\n' \
                  '/gps/pos/centre ' + strdisnum + ' 0 0 cm\n' \
                    '/gps/direction -1 0 0\n'\
                    '/gps/ene/mono 0.12178 MeV\n'\
                        '/gps/source/add 7.4\n'\
                        '/gps/particle gamma\n'\
                        '/gps/ene/mono 0.24469 MeV\n'\
                        '/gps/source/add 26.2\n' \
                        '/gps/particle gamma\n' \
                        '/gps/ene/mono 0.34428 MeV\n' \
                        '/gps/source/add 2.2\n' \
                        '/gps/particle gamma\n' \
                        '/gps/ene/mono 0.41112 MeV\n' \
                        '/gps/source/add 3.04\n' \
                        '/gps/particle gamma\n' \
                        '/gps/ene/mono 0.44398 MeV\n'\
                        '/gps/source/add 12.7\n' \
                        '/gps/particle gamma\n' \
                        '/gps/ene/mono 0.77890 MeV\n' \
                        '/gps/source/add 4.09\n' \
                        '/gps/particle gamma\n' \
                        '/gps/ene/mono 0.86739 MeV\n' \
                        '/gps/source/add 14.23\n' \
                        '/gps/particle gamma\n' \
                        '/gps/ene/mono 0.96413 MeV\n' \
                        '/gps/source/add 9.56\n' \
                        '/gps/particle gamma\n' \
                        '/gps/ene/mono 1.08591 MeV\n' \
                        '/gps/source/add 1.727\n' \
                        '/gps/particle gamma\n' \
                        '/gps/ene/mono 1.08974 MeV\n' \
                        '/gps/source/add 13.35\n' \
                        '/gps/particle gamma\n' \
                        '/gps/ene/mono 1.11212 MeV\n' \
                        '/gps/source/add 1.38\n' \
                        '/gps/particle gamma\n' \
                        '/gps/ene/mono 1.21295 MeV\n'\
                        '/gps/source/add 1.6\n' \
                        '/gps/particle gamma\n' \
                        '/gps/ene/mono 1.29912 MeV\n' \
                        '/gps/source/add 20.57\n' \
                        '/gps/particle gamma\n' \
                        '/gps/ene/mono 1.40801 MeV\n' \
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
