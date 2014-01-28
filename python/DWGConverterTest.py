import os.path
import sys
import shutil
import subprocess

cmd_pattern = r'"G:\p4root\AIM\Main\Output\x64\Debug\AIM_DwgConvertor.exe" "{0}"  "{1}"'

TestFiles = {
	'2013_ACAD_Sheboygan_Roads.dwg': r'\\shamapqa4\MapGuide\Data\Jedi\DWG on Server\2013_ACAD_Sheboygan_Roads.dwg'
	,'2013_SDF_Sheboygan_Trees.dwg': r'\\shamapqa4\MapGuide\Data\Jedi\DWG on Server\2013_SDF_Sheboygan_Trees.dwg'
	,'2010_object_data_realtor_neighborhoods_more_properties.dwg': r'\\shamapqa4\MapGuide\Data\Jedi\DWG on Server\DWG\2010_object_data_realtor_neighborhoods_more_properties.dwg'
	,'2000_Lines.dwg': r'\\shamapqa4\MapGuide\Data\Jedi\DWG on Server\DWG\2000_Lines.dwg'
	#,'Sandi.rvt': r'\\shaaud1\aimshare\data\Volans\Revit\Defects\Sandi.rvt'
	#,'Training Office': r'\\shaaud1\aimshare\data\Volans\Revit\Defects\Training Office.rvt'
	#,'Petrol Station-Structure': r'\\shaaud1\aimshare\data\Volans\Revit\Defects\Petrol Station-Structure.rvt'	
	#,'Meadow Gate': r'\\shaaud1\aimshare\data\Volans\Revit\Defects\Meadow Gate.rvt'
}

def convert(output_root) :
	for name, path in TestFiles.iteritems():
		if os.path.exists(path):
			outdir = os.path.join(output_root, name)
			
			# clean old data if it exists
			if os.path.exists(outdir):
				#os.removedirs(outdir)
				shutil.rmtree(outdir)

			# create folder again				
			os.makedirs(outdir)

			output = os.path.join(outdir, 'out.sqlite')
			cmd = cmd_pattern.format(path, output)
			print cmd + " starts... "
			#os.system(cmd)
			subprocess.call(cmd)
			print name + " is finished to convert "
		else:
			print path + " doesn't exist!"


# main code

def main() :
	usage = '''
		DWGConverterTest.py Output_Folder
		Usage:
		1. In python script beginning, specify the input test files 
		2. Run DWGConverterTest SFF_Output_Folder
			2.a First argument specify the output sff folder 
			2.b By default it uses C:\temp\out as output folder
		3. Use Infraworks.exe to check the visual effect
	'''

	output_root = 'C:/temp/out'
	
	if len(sys.argv) != 2:
		print usage
		print 'Uses "C:/temp/out" as SFF output folder'
	else:
		output_root = sys.argv[1]

	convert(output_root)
	
main()