@echo off
setlocal

set "REPO_DIR=%~dp0"
if "%REPO_DIR:~-1%"=="\" set "REPO_DIR=%REPO_DIR:~0,-1%"

set "SOURCE_DLL=%REPO_DIR%\bin\Release\winmm.dll"
if not exist "%SOURCE_DLL%" (
  echo Missing build output: "%SOURCE_DLL%"
  exit /b 1
)

if defined BZR_GAME_DIR (
  set "GAME_DIR=%BZR_GAME_DIR%"
) else (
  set "GAME_DIR=C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux"
)

set "GAME_EXE=%GAME_DIR%\battlezone98redux.exe"
set "TARGET_DLL=%GAME_DIR%\winmm.dll"

if not exist "%GAME_EXE%" (
  echo Missing game exe: "%GAME_EXE%"
  exit /b 1
)

copy /y "%SOURCE_DLL%" "%TARGET_DLL%" >nul
if errorlevel 1 (
  echo Failed to deploy "%TARGET_DLL%"
  exit /b 1
)

set "BZR_CHUNK_FORCE_FIRST_GEO=1"
set "BZR_CHUNK_TRACE=1"
set "BZR_TRACE_CHUNK_EFFECT=1"
set "BZR_CHUNK_LOG_BUDGET=400"

echo Deployed latest winmm.dll to "%GAME_DIR%"
echo Launching Battlezone with:
echo   BZR_CHUNK_FORCE_FIRST_GEO=1
echo   BZR_CHUNK_TRACE=1
echo   BZR_TRACE_CHUNK_EFFECT=1
echo   BZR_CHUNK_LOG_BUDGET=400

start "" /D "%GAME_DIR%" "%GAME_EXE%"
