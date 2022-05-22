echo off
setlocal EnableExtensions EnableDelayedExpansion
cls
echo ...............................................
echo       Movie Ticket Booking System Build Scripts         
echo ...............................................
echo.    
echo. 
:missing_parameter  
IF [%1] == [] goto commandline 
set /a ID=%1
goto choices

:Commandline
echo Please choose the Target Build
echo.
echo.
echo Options : ^< 1. DEBUG_MODE_BUILD ^| 2. RELEASE_MODE_BUILD ^>
set /p ID= Enter the Number against the Target:
echo. 

:choices
REM Set the Debug and Release mode
IF %ID% == 1 ( 
  goto DEBUG
) ELSE IF %ID% == 2 (
  goto RELEASE
) ELSE ( 
  goto missing_parameter
)

:DEBUG
set Build_Type=Debug
echo %Build_Type%
goto Other_option

:RELEASE
set Build_Type=Release
echo %Build_Type%
goto Other_option

REM Choose other options
:Other_option
IF %ID% == 1 (
  set Folder="Build/Debug"
  goto CODEBLOCKS
) ELSE IF %ID% == 2 (
  set Folder="Build/Release"
  goto CODEBLOCKS
) 

:CODEBLOCKS
set generators=CodeBlocks
echo %generators%
goto delFolder

:delFolder
if not exist %Folder% goto build
rmdir /s/q %Folder%

:build
mkdir %Folder%
cd %Folder%

cmake -G "%generators%" -DCMAKE_BUILD_TYPE=%Build_Type% ..\..
cd ../..

:exit
IF [%1] == [] (
pause
)

Endlocal