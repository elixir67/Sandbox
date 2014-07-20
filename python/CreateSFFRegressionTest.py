import os.path
import sys
import shutil
import subprocess

cmd_pattern = r'"C:/Program Files/Autodesk/Navisworks Manage 2015/Roamer.exe" -NoGui -OpenFile "{0}" -ExecuteAddInPlugin NativeExportPluginAdaptor_LcSffExporterPlugin_Export.Navisworks "{1}" -Exit'

TestFiles = {
	'rac_basic_sample_project': r'\\shaaud1\aimshare\data\Volans\Revit\Defects\rac_basic_sample_project.rvt'
	,'gate_Demo': r'\\shaaud1\aimshare\data\Volans\Revit\Defects\gate_Demo.rvt'
	,'Sandi.rvt': r'\\shaaud1\aimshare\data\Volans\Revit\Defects\Sandi.rvt'
	,'Training Office': r'\\shaaud1\aimshare\data\Volans\Revit\Defects\Training Office.rvt'
	,'Petrol Station-Structure': r'\\shaaud1\aimshare\data\Volans\Revit\Defects\Petrol Station-Structure.rvt'	
	,'Meadow Gate': r'\\shaaud1\aimshare\data\Volans\Revit\Defects\Meadow Gate.rvt'
}

def createSFF(output_root) :
	for name, path in TestFiles.iteritems():
		if os.path.exists(path):
			outdir = os.path.join(output_root, name)
			
			# clean old data if it exists
			if os.path.exists(outdir):
				#os.removedirs(outdir)
				shutil.rmtree(outdir)

			# create folder again				
			os.makedirs(outdir)

			output = os.path.join(outdir, 'out.sff')
			cmd = cmd_pattern.format(path, output)
			print cmd + " starts... "
			#os.system(cmd)
			subprocess.call(cmd)
			print name + " is finished to convert to sff "
		else:
			print path + " doesn't exist!"


# main code

def main() :
	usage = '''
		CreateSFFRegressionTest.py SFF_Output_Folder
		Usage:
		1. In python script beginning, specify the input test files 
		2. Run CreateSFFRegressionTest SFF_Output_Folder
			2.a First argument specify the output sff folder 
			2.b By default it uses C:\temp\out as output folder
		3. Use SffViewer.exe to check the visual effect
	'''

	output_root = 'C:/temp/out'
	
	if len(sys.argv) != 2:
		print usage
		print 'Uses "C:/temp/out" as SFF output folder'
	else:
		output_root = sys.argv[1]

	createSFF(output_root)
	
main()