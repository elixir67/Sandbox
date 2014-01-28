import os
from os import path
import sys

#src folders
FDO_Folder = 'c:/Program Files/Autodesk/AutoCAD Longbow/MAP/bin/FDO/'
MAP_FOLDER  = 'c:/Program Files/Autodesk/AutoCAD Longbow/MAP/'
#des folders
ARX_FOLDER  = 'c:/Program Files/Autodesk/AutoCAD Longbow'

#FDOFiles = ['FDO.dll','FDOGemometry.dll', 'FDOSpatial.dll','FDOCommon.dll',]
DesignService = 'AcDsDesignService.dll'
DesignServiceFiles = ['AcDsDesignService.dll', 'AcDsDesignServiceManaged.dll', 'AcDsDesignServiceResource.dll']

def quote(s) :
	return "\"" + s + "\""

def runCMD(cmd) :
	print "Start execute: ", cmd
	ret = os.system(cmd)
	if ret :
		print "Failed to execute command with error ", ret
	else :
		print "Successful execute command"

def runCreateLink(link, target) :
	if os.path.exists(link) :
		print "remove existed link: ", link
		cmd = "rm " + quote(link)
		runCMD(cmd)

	#create file link
	cmd = "mklink " + quote(link) + " " + quote(target)
	runCMD(cmd)

def createLinks():
	for filename in DesignServiceFiles:
		target = path.join(MAP_FOLDER, filename)
		link = path.join(ARX_FOLDER, filename)
		runCreateLink(link, target)

	#create link for FDOs
	# for dirname, dirnames, filenames in os.walk(FDO_Folder):
	# 	for filename in filenames:
	# 		target = path.join(dirname, filename)
	# 		link = path.join(ARX_FOLDER, filename)
	# 		runCreateLink(link, target)

createLinks()