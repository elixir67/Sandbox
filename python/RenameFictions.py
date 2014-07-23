#!user/bin/python
#coding:utf-8
# python Output the path to a file
# 1. iterate the sub-directories, each subfolder is a author's name
# 2. add the folder name, the authour's name to each file
# 3. flatten the structure move all the txt files into a folder
# 4. the other files(ebooks) into another folder

import os;
import sys;
import shutil;

newTxtFolder = 'f:\\fiction\\Fiction.Author.Text\\'
newEbookFolder = 'f:\\fiction\\Fiction.Author.Ebook\\'

def flattern(targetfolder):
    for authorname in os.listdir(targetfolder):
        subfolder = os.path.join(targetfolder, authorname)
        if os.path.isdir(subfolder):
            print subfolder        
            for filename in os.listdir(subfolder):
                ext = os.path.splitext(filename)[1]
                oldfile = os.path.join(subfolder, filename)     
                newFolder = ''
                if ext == '.txt':                           
                    newFolder = newTxtFolder               
                else:
                    newFolder = newEbookFolder
                newfile = os.path.join(newFolder, authorname + "¡ª¡ª" + filename)
                print newfile
                shutil.copyfile(oldfile, newfile)
            
            
def main():
    target = 'e:\\Downloads\\Fictions\\Fictions.Authors\\'
    flattern(target)
    
main()