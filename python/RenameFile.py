# coding:utf-8
# Rename file to replace the "：" to "-"
import os
from os import path
import re
import shutil
import filecmp
import csv

sourceDir = "F:\SkyDrive\Books"
namepattern = re.compile(r'(.*)(：)(*.)')
igoreDirPattern = re.compile(r'.*jquery.*', re.I)
log = csv.writer(open("log.csv", "wb"))
log.writerow(['OriginalName','NewName','Folder'])

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

    
def iter_dir():    
    if path.exists(targetDir):
        shutil.rmtree(targetDir)
    os.mkdir(targetDir)

    for dirname, dirnames, filenames in os.walk(sourceDir):
        #for subdirname in dirnames:
        #    print os.path.join(dirname, subdirname)
        if igoreDirPattern.match(dirname):
            continue
        for filename in filenames:
			m = namepattern.match(filename)
			if m:
				newname = m.group(1) + '-' + m.group(2)
				log.writerow([filename, newname, dirname])
				print filename + '-'+newname
iter_dir();
