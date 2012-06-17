#coding:utf-8

import shutil
import os
import filecmp
from os import path 
from time import gmtime, strftime
import re
import codecs

PERSONAL = r'.+Me personal(.+)'
# line =r'1 4 C70D54B352FED7B1!604 1336793737 "SkyDrive" Me personal "D:\Dan\SkyDrive"  ' 
line2 = r'library = 1 4 C70D54B352FED7B1!604 1336793737 "SkyDrive" Me personal "D:\Dan\SkyDrive"'
# m = re.match(PERSONAL, line)  
# print m.group(1)

# idx = line.find('Me personal')
# print 'idx:' + str(idx)

# # PERSONAL = r'?.+ Me personal (.+)'
# PERSONAL = r'.+Me personal(.+)'
# appdata = os.environ['APPDATA']

s = 'Me personal'
print("type"+str(type(s)))
def getskydrivefolder():
    SKYDRIVESETTING = 'Microsoft\SkyDrive\settings\c70d54b352fed7b1.ini'
    skydrivesetting = path.join(os.environ['LOCALAPPDATA'], SKYDRIVESETTING)
    if path.exists(skydrivesetting):
        with open(skydrivesetting) as f:
            for line in f:
                print(line)
                print(line2)
                if len(line.strip())>0:
                    print("type"+str(type(line)))
                    # line = line.encode('ascii')
                    idx = line.find(s)
                    print('idx:' + str(idx))
    else:
        print('No Skydrive settings found!')
    if idx > 0:
        print('idx:'+idx)
    return "";
    
print(getskydrivefolder())
  