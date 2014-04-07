import os
from os import path
import re
import shutil

KindleDir = "F:/documents"
namepattern = re.compile(r'(.+)(\.sdr)$', re.I)
    
def cleanKindles():    
    # Find folder with .sdr post fix and the file name before .sdr
    # check the file exist or not

    for dirname, dirnames, filenames in os.walk(KindleDir):
        # Root folder
        if dirname == KindleDir or not namepattern.match(dirname):
            cachedFileBaseNames = map(lambda f: path.splitext(f)[0], filenames)
            #for f in cachedFileBaseNames:
            #    print "Cached :" + f
            for subdir in dirnames:
                m = namepattern.match(subdir)
                if m:            
                    basename = m.group(1) #without extension name
                    #print "Basename: " + basename
                    if basename not in cachedFileBaseNames:
                        #print "Remove useless folder: " + subdir
                        removePath = path.join(dirname, subdir)  
                        if path.exists(removePath):
                            print "Remove useless: " + removePath
                            shutil.rmtree(removePath)

cleanKindles();
