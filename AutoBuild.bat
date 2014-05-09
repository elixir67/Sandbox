REM Setup Envrionment
set WORKSPACE="C:\p4root\83811KW_Volans"
set P4CLIENT=83811KW_Volans
set P4PORT=shaicpp4:1672
set p4user=lind
set StreamName=S_Volans
set Passwd=Furture670

echo p4client=%P4CLIENT% >%WORKSPACE%\p4config.txt
echo p4port=%P4PORT% >>%WORKSPACE%\p4config.txt
echo p4user=%P4USER% >>%WORKSPACE%\p4config.txt

REM TODO
echo p4passwd=%Passwd% >>%WORKSPACE%\p4config.txt
echo %Passwd%|p4 login

cd /d %WORKSPACE%\Desktop\
p4 set p4config=p4config.txt

REM sync
p4 sync

REM merge
echo %Passwd%|p4 login
set LAST_LABEL=Main_LAST_CHANGE
del %WORKSPACE%\integrate.txt
p4 interchanges -r -S //IW/%StreamName%  @%LAST_LABEL% 1>%WORKSPACE%\interchanges.txt 2>%WORKSPACE%\integrate.txt
for /F "tokens=*" %%v in (%WORKSPACE%\integrate.txt) do if /I "%%v"=="All revision(s) already integrated." exit /b 0

for /F "tokens=1,2,* delims=:@ " %%v in ('p4 label -o %LAST_LABEL%') do if /I [%%v] == [Revision] set LAST_CHANGE=%%x

p4 -q merge -S //IW/%StreamName% -r @%LAST_LABEL%
p4 -q resolve -at Build/...
p4 -q resolve -at GitSubModules/...
p4 -q resolve -at Shared/...
p4 -q resolve -at Desktop/3rdParty/...
p4 -q resolve -at Desktop/Build/...
p4 -q resolve -at Desktop/INSTALL/...
p4 -q resolve -at Desktop/Data/...
p4 -q resolve -at Desktop/Documents/...
p4 -q resolve -at Desktop/Source/Tools/...
p4 -q resolve -at Desktop/Source/Tools/... 
p4 -q resolve -at Desktop/Source/Workflow/...
p4 -q resolve -at Server/3rdParty/...
p4 -q resolve -at Server/Chef/...
p4 -q resolve -at Mobile/...
p4 -q resolve -am

echo Integrating //IW/Main/...@%LAST_CHANGE% to //IW/%StreamName% > %WORKSPACE%\integrate.txt
echo. >>%WORKSPACE%\integrate.txt
echo Following changes are integrated: >>%WORKSPACE%\integrate.txt
type %WORKSPACE%\interchanges.txt >>%WORKSPACE%\integrate.txt

set SUBDOC="Merge from //IW/Main/...@%LAST_CHANGE% to //IW/%StreamName% through automatic script."
p4 resolve -n
if errorlevel 0 goto build
goto resolve_error

:build
REM build 

rem start BuildAIM.bat /d /q
start BuildAIM.bat /q
if errorlevel 0 goto succeed
echo "build error, fixed it first before submit"
exit

:resolve_error
echo "resolve failed, you need to resolve manually"

:succeed
echo "Merge successfully"
echo %SUBDOC%
pause

:test
rem p4 client



