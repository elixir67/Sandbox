@echo off
REM Author: Dan Lin
REM Date: 	 2012/5/6
REM Set Python envrionment path
REM run SetPy Ver
REM Ver = 2	set Python27
REM		  3	set Python32
REM		  * echo current Path 

if %1 == 2 set Path=%Path%;C:\Python27
if %1 == 3 set Path=%Path%;C:\Python32
echo %Path%
