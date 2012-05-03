# This script helps to load test container for ant runtests.
#
# If the test project has any class which is not Test Class but uses or inherits
# the class from other assembly, like the Helper class, it cannot load the test container when run
# mstest in commandline by ant without the referenced assembly.
#
# In Win7 or other OS, which support symlink, it creates symbolic links in %Map_Root%\runtime\api_TB\bin 
# pointing to the files in %MAP_TB_BIN%.
#
# In WinXP which doesn't support symlink but might still be used in Automation Test.
# It copies the asseblies from  %MAP_TB_BIN% to %Map_Root%\runtime\api_TB\bin.
#
# In addition, we cannot do this(create symlinks) in build like CopyLocal or PostBuild events
# because it will bring conflict problem in parallel build and lower the build speed.

import os
import sys
import platform
from os import system
from os import path
import shutil

# Create symlink for a target file,      
# or just copy the target file in WinXP.
def makelink(target, linkfolder):
    dir,filename = path.split(target)
    link = path.join(linkfolder, filename);
    if path.exists(link):
        os.remove(link)
    # It has no way to create symlink in XP, and Junction or Hardlink are not suitable.
    # so let's copy the file instead.
    if platform.release() == 'XP':
        shutil.copy(target, link)
    # Besides WinXP, currently Win7 is mostly used and it supports symlink.
    else:
        # in python 2.7 it doesn't support os.symlink, so we run the command instead
        statement = "mklink " + link + " " + target
        system(statement)

# Create symlink or copy files for all the files in target folder
def makelinks(targetfolder, linkfolder, includesubfolder = False):
    if not path.exists(linkfolder):
        os.mkdir(linkfolder)
        
    for name in os.listdir(targetfolder):
        target = path.join(targetfolder, name)
        if path.isfile(target):
            makelink(target, linkfolder)
        elif path.isdir(target) and includesubfolder:
            sublinkfolder = path.join(linkfolder, name)
            makelinks(target, sublinkfolder, includesubfolder)

def main():
    targetfolder = os.getenv("MAP_TB_BIN")
    linkfolder = path.join(os.getenv("Map_Root"),"runtime","api_TB","bin")
    if platform.release() == 'XP':
        print("To load test container, copy files from " + targetfolder + " to " + linkfolder)
    else:
        print("To load test container, create symlinks from " + targetfolder + " to " + linkfolder)

    # It's OK without the files in the subfolders, 
    # so we don't do it to save time
    makelinks(targetfolder, linkfolder, False)                     
    
main()
