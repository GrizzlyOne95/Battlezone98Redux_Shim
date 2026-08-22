# Builds and runs the openshim.ini writer unit tests with the VS 2022 x86
# toolchain. No engine or game install required.
#
#   powershell -ExecutionPolicy Bypass -File scripts\run_ini_tests.ps1

$ErrorActionPreference = "Stop"
$repo = Split-Path -Parent $PSScriptRoot
$out = Join-Path $repo "bin\tests"
New-Item -ItemType Directory -Force $out | Out-Null

$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
$vsroot = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $vsroot) { throw "Visual Studio with C++ tools not found" }

$vcvars = Join-Path $vsroot "VC\Auxiliary\Build\vcvars32.bat"
$exe = Join-Path $out "ini_writer_tests.exe"

cmd /c "`"$vcvars`" >nul && cl /nologo /std:c++17 /EHsc /W4 /WX /I `"$repo\include`" `"$repo\tests\ini_writer_tests.cpp`" `"$repo\src\patches\openshim_ini.cpp`" /Fe:`"$exe`" /Fo:`"$out\\`""
if ($LASTEXITCODE -ne 0) { throw "test build failed" }

& $exe
if ($LASTEXITCODE -ne 0) { throw "ini writer tests FAILED" }
Write-Host "ini writer tests passed" -ForegroundColor Green
