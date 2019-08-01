@echo off
setlocal enabledelayedexpansion

rem == Setup path to nmake.exe ==
call "%VS120COMNTOOLS%vsvars32.bat"

:start
set TTEXE=..\..\devtools\bin\timeprecise.exe
if not exist %TTEXE% goto no_ttexe
goto no_ttexe_end

:no_ttexe
set TTEXE=time /t
:no_ttexe_end


echo.
echo ~~~~~~~~~~~~ buildshaders_flashlight %* ~~~~~~~~~~~~
%TTEXE% -cur-Q
set tt_all_start=%ERRORLEVEL%
set tt_all_chkpt=%tt_start%

set BUILD_SHADER=call buildshaders.bat

@REM dynamic shaders only builds the required files (inc) to build stdshader_dx*.dll
set dynamic_shaders=0

REM ****************
REM PC SHADERS
REM ****************
%BUILD_SHADER% stdshader_flashlight_dx9_20b		-game %GAMEDIR% -source %SOURCEDIR%
echo --------------------------------------------------------------------------------------------
%BUILD_SHADER% stdshader_flashlight_dx9_30			-game %GAMEDIR% -source %SOURCEDIR% -dx9_30 -force30
echo --------------------------------------------------------------------------------------------
@REM %BUILD_SHADER% stdshader_flashlight_dx10			-game %GAMEDIR% -source %SOURCEDIR% %dynamic_shaders% -dx10
@REM dx10 is empty right now
echo.

REM ****************
REM END
REM ****************
:end

rem echo.
if not "%dynamic_shaders%" == "1" (
  echo Finished full buildallshaders %*
) else (
  echo Finished dynamic buildallshaders %*
)

%TTEXE% -diff %tt_all_start% -cur
echo.

pause