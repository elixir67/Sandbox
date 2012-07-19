#coding:utf-8
import sys
import os
from os import path
import codecs

def remove_empty_line(filepath):
    with open(filepath, 'r') as f:
        result = ''
        for line in f:
            line = line.rstrip('\n')
            if line != "":
                result += line+'\n'
    #print result
    with open (filepath, 'w') as f:
        f.writelines(result)

def showusage():
    print "Usage: python remove_empty_line.py filepath"    
    
if __name__ == '__main__':
    if (len(sys.argv) != 2):
        showusage()
    filepath = sys.argv[1]
    remove_empty_line(filepath)  