import os
import time
import subprocess

FWHMfile = '/Users/roy/Documents/Geant4EX/lrd_v1/build/FWHM.cpp'
sourcename = 'Am241'

for distence in range(25,36):
    for num in range(1000000,20000001,1000000):
        strnum = str(num)
        strdis = str(distence)
        fwhm = open(FWHMfile,'r+')
        lines = fwhm.readlines()
        lines[17] = "    TString filename= \"/Users/roy/Documents/Geant4EX/lrd_v1/build/data/" + sourcename + "/" + sourcename + "-" + strdis + '-' + strnum + "\";\n"
        lines[18] = "    TString filepath = \"/Users/roy/Documents/Geant4EX/lrd_v1/build/data/" + sourcename + "/Fin/" + sourcename + "-" + strdis + '-' + strnum + "\";\n"
        fwhm_new = open(FWHMfile,'w+')
        fwhm_new.writelines(lines)
        fwhm_new.close()
        fwhm.close()
        subp = subprocess.Popen('root /Users/roy/Documents/Geant4EX/lrd_v1/build/FWHM.cpp',shell=True)
        time.sleep(3.5)
        subp.kill()