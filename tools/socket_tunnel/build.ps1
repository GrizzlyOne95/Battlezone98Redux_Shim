param([string]$Out = "$env:TEMP\bzr_socket_tunnel", [string]$SteamDll)
$ErrorActionPreference = 'Stop'
New-Item -ItemType Directory -Force $Out | Out-Null
$Out = (Resolve-Path -LiteralPath $Out).Path
$repo = (Resolve-Path (Join-Path $PSScriptRoot '../..')).Path
if ($SteamDll) {
    $source = (Resolve-Path -LiteralPath $SteamDll).Path
    $gameRoot = Split-Path -Parent $source
    if ($Out.Equals($gameRoot, [StringComparison]::OrdinalIgnoreCase) -or
        $Out.StartsWith($gameRoot + [IO.Path]::DirectorySeparatorChar, [StringComparison]::OrdinalIgnoreCase)) {
        throw 'Output must stay outside the source game/Steam directory'
    }
}
& (Join-Path $repo 'scripts/Fetch-SteamNetworkingHeaders.ps1')
$vs = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath
if (-not $vs) { throw 'Visual Studio C++ tools required' }
$batch = Join-Path $Out 'build.cmd'
@"
@echo off
call "$vs\VC\Auxiliary\Build\vcvars32.bat" >nul
if errorlevel 1 exit /b 1
cd /d "$Out"
cl /nologo /std:c++17 /EHsc /W4 /WX /O2 /I"$repo\include" /I"$repo\third_party\steam-networking" "$PSScriptRoot\main.cpp" "$repo\src\patches\socket_tunnel.cpp" "$repo\src\patches\steam_tunnel_transport.cpp" /Fe:socket_tunnel.exe /link ws2_32.lib
"@ | Set-Content -LiteralPath $batch -Encoding ascii
& cmd /c $batch
if ($LASTEXITCODE) { throw "Build failed: $LASTEXITCODE" }
if ($SteamDll) {
    $destination = Join-Path $Out 'steam_api.dll'
    if ($source -eq $destination) { throw 'Use an isolated output directory; do not build into the game/Steam install' }
    Copy-Item -LiteralPath $source -Destination $destination -Force
    Set-Content -LiteralPath (Join-Path $Out 'steam_appid.txt') -Value '301650' -NoNewline -Encoding ascii
}
Write-Output "Built: $Out\socket_tunnel.exe (Win32; plain UDP needs no Steam DLL; Steam modes use the explicitly staged shipped DLL)"
