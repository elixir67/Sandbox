cd /d %WORKSPACE%\Desktop\
BuildALX_console.exe
call CopyAlx.bat

set VS_TOOLS_VARIANT=x86
if not exist "%VS110COMNTOOLS%..\..\VC\bin\%VS_TOOLS_VARIANT%" set VS_TOOLS_VARIANT=x86_amd64
call "%VS110COMNTOOLS%..\..\VC\vcvarsall.bat" %VS_TOOLS_VARIANT%

pushd %WORKSPACE%\Desktop\

for %%c in (Debug Release) do (
	echo msbuild AIM.sln /p:Platform=x64 /p:Configuration=%%c /nologo /maxcpucount /clp:Verbosity=minimal /t:rebuild
	msbuild AIM.sln /p:Platform=x64 /p:Configuration=%%c /nologo /maxcpucount /clp:Verbosity=minimal /t:rebuild
	if ERRORLEVEL 1 (
           echo ERROR: %~n0: Auto build AIM %%c failed.
        )
)

echo %date%
echo %time%

if errorlevel 0 goto succeed
echo Build error, fixed it first before submit
exit

:succeed
echo Build successfully