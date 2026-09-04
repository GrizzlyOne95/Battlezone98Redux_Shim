@echo off
setlocal
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0openshim_support_wrap.ps1" %*
set "OPENSHIM_SUPPORT_EXIT=%ERRORLEVEL%"
endlocal & exit /b %OPENSHIM_SUPPORT_EXIT%
