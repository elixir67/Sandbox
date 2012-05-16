#coding:utf-8

import shutil
import os
import filecmp
from os import path 
from time import gmtime, strftime
import re
import codecs

NPP = 'Notepad++'
NPPCONFIG = 'config.xml'
# PERSONAL = r'?.+ Me personal (.+)'
PERSONAL = r'.+Me personal(.+)'
appdata = os.environ['APPDATA']

# The file encoding for sky drive folder is unknown and wide characters.
# Which made problems, so I change the ini encoding to UTF-8 for testing
def getskydrivefolder():
    SKYDRIVESETTING = 'Microsoft\SkyDrive\settings\c70d54b352fed7b1.ini'
    skydrivesetting = path.join(os.environ['LOCALAPPDATA'], SKYDRIVESETTING)
    if path.exists(skydrivesetting):
        with codecs.open(skydrivesetting, encoding='utf-8') as f:
            for line in f:
                uline = line.encode('utf-8')
                m = re.match(PERSONAL, line)
                if m:
                    cloudfolder = m.group(1).strip()
                    cloudfolder = cloudfolder.replace('\"','').strip()
                    return cloudfolder
    else:
        print 'No Skydrive settings found!'
    return "";

def getcloudbakupfolder():
    skydrivefolder = getskydrivefolder()
    bakup = 'bakup'
    if path.exists(skydrivefolder):
        bakup = path.join(skydrivefolder, 'bakup')
    return bakup

def copysettings(src, dst):
    print "src:" + src
    print "dst:" + dst
    if path.exists(dst) and not filecmp.cmp(src,dst):
        override = confirm(prompt='Override settings', resp=True)
        if override:
            postfix = strftime("-%Y-%m-%d", gmtime())
            basename = path.basename(dst)
            pair = path.splitext(basename)
            bak = path.join(path.split(dst)[0], pair[0] + postfix + pair[1])
            print 'bakup:' + bak
            shutil.copyfile(src, bak)
            shutil.copyfile(src, dst)
    else:
        print 'No need update ' + dst

## {{{ http://code.activestate.com/recipes/541096/ (r1)
def confirm(prompt=None, resp=False):
    """prompts for yes or no response from the user. Returns True for yes and
    False for no.

    'resp' should be set to the default value assumed by the caller when
    user simply types ENTER.

    >>> confirm(prompt='Create Directory?', resp=True)
    Create Directory? [y]|n: 
    True
    >>> confirm(prompt='Create Directory?', resp=False)
    Create Directory? [n]|y: 
    False
    >>> confirm(prompt='Create Directory?', resp=False)
    Create Directory? [n]|y: y
    True

    """
    
    if prompt is None:
        prompt = 'Confirm'

    if resp:
        prompt = '%s [%s]|%s: ' % (prompt, 'y', 'n')
    else:
        prompt = '%s [%s]|%s: ' % (prompt, 'n', 'y')
        
    while True:
        ans = raw_input(prompt)
        if not ans:
            return resp
        if ans not in ['y', 'Y', 'n', 'N']:
            print 'please enter y or n.'
            continue
        if ans == 'y' or ans == 'Y':        
        
            return True
        if ans == 'n' or ans == 'N':
            return False
     
def updatenpp():    
    cloudbakup = getcloudbakupfolder()    
    nppcloud = path.join(path.join(cloudbakup, NPP),NPPCONFIG)
    # Roam Notepad++ settings
    npplocal = path.join(path.join(appdata, NPP), NPPCONFIG)    
    bakuptocloud = confirm(prompt='Bakup local settings to cloud otherwise override local settings from cloud?', resp=True)        
    if bakuptocloud:
        CopySettings(npplocal, nppcloud)
    else:
        CopySettings(nppcloud, npplocal)
        
print getcloudbakupfolder()
        

    
