import os
from os import path
import re
import shutil
import stat
import csv

sourceDir = "G:/p4root/IW_Main/Desktop/3rdParty"

replacedLog = csv.writer(open("filenames.csv", "wb"))
replacedLog.writerow(['Name','Description','Link'])

def replaceIconPathInXaml(forceReplace = False):
    for dirname, dirnames, filenames in os.walk(sourceDir):
        for filename in filenames:
            if xamlpattern.match(filename):
                if filename == 'DefaultRibbon_archive.xaml': 
                    continue
                filepath = path.join(dirname, filename)
                content = ''
                fileReplace = False
                with open(filepath) as f:
                    for line in f:
                        m = iconUsedByXamlPattern.match(line)
                        newline = line
                        lineReplace = False
                        if m and not re.search(r"pack://application:", line):
                            iconname = m.group(3) + m.group(4)
                            isExist = isIconExist(iconname)
                            if forceReplace:
                                lineReplace = True
                            else:
                                lineReplace = isExist
                            if lineReplace:
                                fileReplace = True
                                newline = m.group(1) + newIconDir + m.group(3) + m.group(4) + m.group(5) + '\n'
                            replacedLog.writerow([iconname,isExist,line.strip(),newline.strip(),filename,dirname])
                        content += newline
                if fileReplace:
                    os.chmod(filepath, stat.S_IWRITE)
                    f = open(filepath, 'w')
                    # print content
                    f.writelines(content)
                    f.close()
                            
def isIconExist(icon):
    for dirname, dirnames, filenames in os.walk(targetDir):
        for filename in filenames:
            if filename.lower() == icon.lower():
                return True
    return False
            
replaceIconPathInXaml(False) 
# namepattern = re.compile(r'.+\.(png|ico|gif|jpg|bmp)$', re.I)
# s = 'group_Users_16.ICO'
# m = namepattern.match(s)
# if m:
    # print 'Find ICO'