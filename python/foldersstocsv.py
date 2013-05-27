import os
import re
import shutil
import stat
import csv
import sys

sourceDir = "G:/p4root/IW_Main/Desktop/3rdParty"

def showusage():
    print "Usage: python folderstocsv.py parentfolder"    

def exportfolders(parent):
    for name in os.listdir(parent):
        print name

def exportcsv(parent):
    basename = os.path.basename(parent)
    csvname = basename + '.csv'
    out = csv.writer(open(csvname, "wb"))
    out.writerow(['Name'])
    for name in os.listdir(parent):
        out.writerow([name])

if __name__ == '__main__':
    if(len(sys.argv) != 2):
        showusage()
    parentfolder = sys.argv[1]
    exportcsv(parentfolder)
    
