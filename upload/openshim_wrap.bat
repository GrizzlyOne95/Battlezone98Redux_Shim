@echo off
REM One-line shim so the Steam launch option stays readable:
REM
REM   cmd /c ""%LOCALAPPDATA%\openshim\openshim_wrap.bat" %command%"
REM
REM The doubled outer quotes are load-bearing. Steam's launch-option field
REM does not cope well with a PowerShell invocation full of quoting, so the
REM quoting lives here instead.
REM
REM Everything here is logged to openshim_wrap.log as well as the console.
REM Steam runs this in a console that dies with the process, so a launch that
REM failed here used to leave nothing at all behind.
set "BZLOG=%LOCALAPPDATA%\openshim\openshim_wrap.log"
if not exist "%LOCALAPPDATA%\openshim" mkdir "%LOCALAPPDATA%\openshim" 2>nul
>>"%BZLOG%" echo [bat] %DATE% %TIME% invoked with: %*

if not exist "%~dp0openshim_wrap.ps1" goto :plain

REM Resolve powershell.exe explicitly: if it is not on PATH (it has been
REM missing from a stripped install), the bare name fails with no output.
set "PSEXE=%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe"
if not exist "%PSEXE%" set "PSEXE=powershell"

"%PSEXE%" -NoProfile -ExecutionPolicy Bypass -File "%~dp0openshim_wrap.ps1" %*
set "RC=%ERRORLEVEL%"
>>"%BZLOG%" echo [bat] wrapper exited with %RC%
exit /b %RC%

:plain
REM If openshim_wrap.ps1 is gone (antivirus quarantine is the usual reason),
REM the one job that still matters is launching the game - do that plain
REM rather than leaving the tester with a Steam button that does nothing.
echo [openshim_wrap] openshim_wrap.ps1 is missing (quarantined?) - launching the game without the uploader
>>"%BZLOG%" echo [bat] openshim_wrap.ps1 MISSING - launching the game without the uploader
%*
set "RC=%ERRORLEVEL%"
>>"%BZLOG%" echo [bat] game exited with %RC% (no uploader)
exit /b %RC%
