#coding:utf-8
import sys
import os
from os import path
import codecs

def remove_empty_line(filename):
    with codecs.open(filename, encoding='utf-8') as f:
        result = ''
        for line in f:
            if line.strip() != "":
                result += line
    print result

def showusage():
    print "Usage: python remove_empty_line.py filepath"    
    
if __name__ == '__main__':
    if (len(sys.argv) != 2):
        showusage()
    filename = sys.argv[1]
    remove_empty_line(filename)  