# P4 Force Sync
import sys
import fileinput
from os import system

def ShowUsage():
    print "Usage: ForceSync p4log.txt"

if __name__ == '__main__':
    if (len(sys.argv) != 2):
        ShowUsage()
    else:
        for line in fileinput.input():
            target = 'Can\'t clobber writable file'
            idx = line.find(target)
            print 'Sync ', line[(idx + len(target) + 1):] # skip "WARNING: Can't clobber writable file"
            system ("p4 sync -f \"" + line[(idx+len(target) + 1):] + "\"")