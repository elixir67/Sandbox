import os
import re
import shutil

sourceDir = "M:/aim/GBU/AIM/Main/Source"
targetDir = "h:/icons/"
namepattern = re.compile(r'.+\.(png|ico|gif|jpg|bmp)$', re.I)
igoreDirPattern = re.compile(r'.*jquery.*', re.I)

def mvfile(filepath, targetpath):
    #print "moving file " + filepath + " to targetPath: " + targetpath
    if os.path.exists(targetPath):
        print filepath + "not copied " + targetPath + " aready exist"
    shutil.copyfile(filepath, targetpath)

for dirname, dirnames, filenames in os.walk(sourceDir):
    #for subdirname in dirnames:
    #    print os.path.join(dirname, subdirname)
    if igoreDirPattern.match(dirname):
        continue
    for filename in filenames:
        if namepattern.match(filename):
            filepath = os.path.join(dirname, filename)
            targetPath = os.path.join(targetDir, filename)
            mvfile(filepath, targetPath)

