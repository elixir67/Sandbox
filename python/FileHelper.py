# python Output the path to a file
# name:XXX
# extension:XXX
# folder:

import os;
import sys;

def writeFile(msg, f):
    f.write(msg + "\n")
     
def parseFile(target, f):
    folder,name = os.path.split(target)
    str = "name:" + name + "\n" + "folder:" + folder
    writeFile(str, f)
    #return str

def parseTarget(targetfolder, includesubfolder, f):
    for name in os.listdir(targetfolder):
        target = os.path.join(targetfolder, name)
        if os.path.isdir(target) and includesubfolder:            
            parseTarget(target, includesubfolder, f)
        else:
            parseFile(target, f)    
    
def main():
    f = open('outfile.txt', 'w')
    target = 'G:\\sandbox'
    #writeFile(target, f)
    parseTarget(target, True, f)
    f.close()
    
main()