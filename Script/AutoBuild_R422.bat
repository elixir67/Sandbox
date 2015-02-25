REM Setup Envrionment
set WORKSPACE=

if /I -%1- == -Volans- (set WORKSPACE="D:\p4root\S_Volans"
) else if /I -%1- == -Revit- (set WORKSPACE="d:\p4root\X_Volans_Revit"
) else (set WORKSPACE=%1)

echo %WORKSPACE%
if not exist %WORKSPACE%  (echo ERROR: %~n0: Fail to locate workspace %WORKSPACE%.
    					   exit /b 1)

REM sync
p4 sync

:build
REM build
BuildALX_console.exe
call CopyAlx.bat

set VS_TOOLS_VARIANT=amd64
if not exist "%VS110COMNTOOLS%..\..\VC\bin\%VS_TOOLS_VARIANT%" set VS_TOOLS_VARIANT=x86_amd64
call "%VS110COMNTOOLS%..\..\VC\vcvarsall.bat" %VS_TOOLS_VARIANT%

pushd %WORKSPACE%\Desktop\

for %%c in (Debug Release) do (
	echo msbuild AIM.sln /p:Platform=x64 /p:Configuration=%%c /nologo /maxcpucount /clp:Verbosity=minimal /t:rebuild
	msbuild AIM.sln /p:Platform=x64 /p:Configuration=%%c /nologo /maxcpucount /clp:Verbosity=minimal /t:rebuild
	if ERRORLEVEL 1 (
       echo ERROR: %~n0: Auto build AIM %%c failed.
    rem    popd
    rem    exit /b 1
    )
)

if errorlevel 0 goto succeed
echo "build error, fixed it first before submit"
echo %date%
echo %time%
exit

:succeed
echo "Build successfully"
echo %date%
echo %time%
pause





