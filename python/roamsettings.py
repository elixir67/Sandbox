#coding:utf-8

import shutil
import os
import filecmp
from os import path
from time import gmtime, strftime
import re
import codecs

appdata = os.environ['APPDATA']

# The file encoding for sky drive folder is unknown and wide characters.
# Which made problems, so I change the ini encoding to UTF-8 for testing
def getskydrivefolder():
    SKYDRIVESETTING = 'Microsoft\SkyDrive\settings\c70d54b352fed7b1.ini'
    skydrivesetting = path.join(os.environ['LOCALAPPDATA'], SKYDRIVESETTING)
    PERSONAL_PATTERN = r'.+ Me personal (.+)'
    if path.exists(skydrivesetting):
        with codecs.open(skydrivesetting, encoding='utf-16 LE') as f:
            for line in f:
                m = re.match(PERSONAL_PATTERN, line)
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
    if not path.exists(src):
        print src + 'is not found'
        return

    bCopy = False
    if path.exists(dst):
        if filecmp.cmp(src,dst):
            print dst + ' is latest with cloud and no need update'
            return
        else:
            override = confirm(prompt='Override settings', resp=True)
            if override:
                postfix = strftime("-%Y-%m-%d", gmtime())
                basename = path.basename(dst)
                pair = path.splitext(basename)
                bak = path.join(path.split(dst)[0], pair[0] + postfix + pair[1])
                print 'bakup:' + bak
                shutil.copyfile(dst, bak)
                bCopy = True
    else:
        bCopy = True
        dir,filename = path.split(dst)
        if not path.exists(dir):
            os.mkdir(dir)
    if bCopy:
        print "src:" + src
        print "dst:" + dst
        shutil.copyfile(src, dst)

## {{{ http://code.activestate.com/recipes/541096/ (r1)
# """prompts for yes or no response from the user. Returns True for yes and
# False for no.

# 'resp' should be set to the default value assumed by the caller when
# user simply types ENTER.

# >>> confirm(prompt='Create Directory?', resp=True)
# Create Directory? [y]|n:
# True
# >>> confirm(prompt='Create Directory?', resp=False)
# Create Directory? [n]|y:
# False
# >>> confirm(prompt='Create Directory?', resp=False)
# Create Directory? [n]|y: y
# True
def confirm(prompt=None, resp=False):
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

def update_npp():
    appfoldername = 'Notepad++'
    configs = ['config.xml', 'shortcuts.xml']
    updateconfig(appfoldername, configs)

#def update_vim():
#    appfoldername = 'Vim'
#    configs = ["_vimrc"]
#    localfolder = os.environ['ProgramFiles'] #'c:\Program Files (x86)'
#    updateconfig(appfoldername, configs, localfolder)

def updateconfig(appfoldername, configs, localfolder = appdata):
    cloudbakup = getcloudbakupfolder()
    for config in configs:
        # Roam Notepad++ settings
        localconfig = path.join(path.join(localfolder, appfoldername), config)
        cloudconfig = path.join(path.join(cloudbakup, appfoldername),config)
        msg = 'Bakup ' + appfoldername + '-' + config + ' local settings to cloud otherwise override local settings from cloud?'
        bakuptocloud = confirm(prompt = msg, resp = True)
        if bakuptocloud:
            copysettings(localconfig, cloudconfig)
        else:
            copysettings(cloudconfig, localconfig)

def update_totalcommander():
    appfoldername = 'GHISLER'
    configs = ['wincmd.ini', 'usercmd.ini']
    updateconfig(appfoldername, configs)

update_totalcommander()
update_npp()

