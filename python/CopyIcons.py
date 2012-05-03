import os
from os import path
import re
import shutil
import filecmp
import csv

sourceDir = "G:/p4root/AIM/Main/i18n/en-US"
targetDir = 'G:/p4root/AIM/Main/Data/Resources/Visual_Assets/Icons/AirLookIcons'
namepattern = re.compile(r'.+\.(png|ico|gif|jpg|bmp)$', re.I)
igoreDirPattern = re.compile(r'.*jquery.*', re.I)
copyLog = csv.writer(open("copyLog.csv", "wb"))
copyLog.writerow(['IconName','Copied','SourceDir','ConflictDir'])

iconDirDict = {}

def cpfile(filepath, targetpath):
    dir,file = path.split(filepath)
    copied = False
    # duplicate = False
    # conflictDifferent = True
    conflictDir = ''
    # if path.exists(targetpath):
    if file in iconDirDict:
        if not filecmp.cmp(filepath, targetpath):
            conflictDir =  iconDirDict[file]
    else:
        shutil.copyfile(filepath, targetpath)
        copied = True
        iconDirDict[file] = dir
    copyLog.writerow([file, copied, dir, conflictDir])

    
def cpIcons():    
    if path.exists(targetDir):
        shutil.rmtree(targetDir)
    os.mkdir(targetDir)

    for dirname, dirnames, filenames in os.walk(sourceDir):
        #for subdirname in dirnames:
        #    print os.path.join(dirname, subdirname)
        if igoreDirPattern.match(dirname):
            continue
        for filename in filenames:
            if namepattern.match(filename):
                filepath = path.join(dirname, filename)
                targetPath = path.join(targetDir, filename)
                cpfile(filepath, targetPath)

cpIcons();
