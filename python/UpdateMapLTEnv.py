# P4 Force Sync
import sys
import fileinput
from os import system

def ShowUsage():
    print "Modify the path in the python file"

if __name__ == '__main__':
    fileinput = 'maplt.xml'
    map_bin = 'C:\p4lite\map\Trunk\Output\Bin\Map\Debug'
    OEM_Toolkit = 'c:\program files\autodesk\autocad oem jaws\Toolkit'
    map_env = '$(MAP_BIN))'
    oem_env = '$(OEM_Toolkit)'
    oldFile = open('maplt.xml', 'r')
    newFile = open('newMapLt.xml','w')
    try:
        for line in oldFile:
            if line.find(map_env) > 0:            
                line = line.replace(map_env, map_bin)
            if line.find(oem_env) > 0:
                line = line.replace(oem_env, OEM_Toolkit)
            newFile.writeLines(line)
    finally    
        newFile.close()
        oldFile.close()
        
        
    
