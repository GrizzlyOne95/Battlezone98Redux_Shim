param([string]$Out = "$env:TEMP\bzr_socket_tunnel")
$ErrorActionPreference = 'Stop'
New-Item -ItemType Directory -Force $Out | Out-Null
$Out = (Resolve-Path -LiteralPath $Out).Path
$repo = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
$vs = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath
if (-not $vs) { throw 'Visual Studio C++ tools required' }
$batch = Join-Path $Out 'build.cmd'
@"
@echo off
call "$vs\VC\Auxiliary\Build\vcvars32.bat" >nul
if errorlevel 1 exit /b 1
cd /d "$Out"
cl /nologo /std:c++17 /EHsc /W4 /WX /O2 /I"$repo\include" "$PSScriptRoot\main.cpp" "$repo\src\patches\socket_tunnel.cpp" /Fe:socket_tunnel.exe /link ws2_32.lib
"@ | Set-Content -LiteralPath $batch -Encoding ascii
& cmd /c $batch
if ($LASTEXITCODE) { throw "Build failed: $LASTEXITCODE" }
Write-Output "Built: $Out\socket_tunnel.exe (Win32, no Steam DLL required for M1)"
