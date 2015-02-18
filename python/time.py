import time
import os.path
import sys

navis_folder = 'E:\\NW\\fix\\12.0\\projects\\vc11\\x64\\dodt\\'
input = 'e:\\RevitFiles\\rac_basic_sample_project.rvt'

def runCMD(cmd) :
	print "Start execute: ", cmd
	ret = os.system(cmd)
	if ret :
		print "Failed to execute command with error ", ret
	else :
		print "Successful execute command"

def runLMVConverter() :
	output = 'e:\\output\\rac\\'
	
	cmd = navis_folder + 'LmvConverter.exe ' + output + ' ' + input
	runCMD(cmd)

def runSffConverter() :
	output = 'e:\\output\\rac_sff\\'
	cmd = navis_folder + 'Roamer.exe -NoGui -OpenFile ' + input +' -ExecuteAddInPlugin NativeExportPluginAdaptor_LcSffExporterPlugin_Export.Navisworks ' + output + 'out.sff  -Exit'
	runCMD(cmd)

start = time.time()
runLMVConverter()
#runSffConverter()
end = time.time()
elapsed = end - start
print "LMVConverer elapsed time is:" #+ string(elapsed)
print elapsed