set VS_TOOLS_VARIANT=amd64
if not exist "%VS110COMNTOOLS%..\..\VC\bin\%VS_TOOLS_VARIANT%" set VS_TOOLS_VARIANT=x86_amd64
call "%VS110COMNTOOLS%..\..\VC\vcvarsall.bat" %VS_TOOLS_VARIANT%

for %%c in (Debug Release) do (
	   REM build win32 solution
       msbuild RCObject.sln /p:Configuration=%%c /p:Platform=win32 /m /t:Rebuild /v:quiet /nologo    
       if ERRORLEVEL 1 (
       echo ERROR: %~n0: Rebuild failed.
       popd
       exit /b 1
    )
)

echo %~n0: finished successfully.
exit /b 0