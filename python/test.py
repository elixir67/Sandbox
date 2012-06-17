#coding:utf-8

import shutil
import os
import filecmp
from os import path 
from time import gmtime, strftime
import re
import codecs
import unicodedata

PERSONAL = r'.+Me personal(.+)'
# line =r'1 4 C70D54B352FED7B1!604 1336793737 "SkyDrive" Me personal "D:\Dan\SkyDrive"  ' 
line2 = r'library = 1 4 C70D54B352FED7B1!604 1336793737 "SkyDrive" Me personal "D:\Dan\SkyDrive"'
m = re.match(PERSONAL, line2)  
print m.group(1)

idx = line2.find('Me personal')
print 'idx:' + str(idx)

# PERSONAL = r'?.+ Me personal (.+)'
PERSONAL = r'.+Me personal(.+)'
appdata = os.environ['APPDATA']

foo = u'Ｍｅ　ｐｅｒｓｏｎａｌ'
print unicodedata.normalize('NFKC', foo)
# u'1234567890'
normal = u' 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!"#$%&()*+,-./:;<=>?@[\\]^_`{|}~'
wide = u'　０１２３４５６７８９ａｂｃｄｅｆｇｈｉｊｋｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺ！゛＃＄％＆（）＊＋、ー。／：；〈＝〉？＠［\\］＾＿‘｛｜｝～'
widemap = dict((ord(x[0]), x[1]) for x in zip(normal, wide))
normalmap = dict((ord(x[0]), x[1]) for x in zip(wide, normal))
print u'Hello, world!'.translate(widemap)
print foo.translate(normalmap)

def getskydrivefolder():
    SKYDRIVESETTING = 'Microsoft\SkyDrive\settings\c70d54b352fed7b1.ini.bak'
    skydrivesetting = path.join(os.environ['LOCALAPPDATA'], SKYDRIVESETTING)
    if path.exists(skydrivesetting):
        # with codecs.open(skydrivesetting, encoding='gbk') as f:
        with open(skydrivesetting) as f:
            for line in f:
                # print unicodedata.normalize('NFKC', line)
                # print unicodedata.normalize('NFKD', line)
                # print unicodedata.normalize('NFC', line)
                # print unicodedata.normalize('NFD', line)
                # print line
                # print len(line)
                # print line2
                # print len(line2)
                # s = line.translate(normalmap)
                ss = unicode(line).encode('utf-8')
                s = ss.decode('utf-8')
                s = s.translate(normalmap)
                print s 
                print len(s)
                    # idx = line.find(u'Ｍｅ　ｐｅｒｓｏｎａｌ')
                    # print 'idx:' + str(idx)
                    # line = line.encode('utf-8')
                    # print line2

    else:
        print 'No Skydrive settings found!'
    return "";
    
print getskydrivefolder()



