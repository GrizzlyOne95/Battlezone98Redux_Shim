# Builds steam_net_probe.exe (32-bit) and stages a run directory.
# Usage: build.ps1 [-Out <dir>]. Headers are fetched from ValveSoftware/GameNetworkingSockets
# at a pinned commit (BSD) and are NOT committed. Needs VS 2022 and the Steam install of BZR.
param([string]$Out = "$env:TEMP\steam_net_probe")
$ErrorActionPreference = 'Stop'
$sha = 'd534c19aa760df3fb75fd20db13ba1932b8a5463'
$inc = Join-Path $Out 'include\steam'
New-Item -ItemType Directory -Force $inc | Out-Null
foreach ($h in 'isteamnetworkingmessages.h','isteamnetworkingsockets.h','isteamnetworkingutils.h','steam_api_common.h','steamclientpublic.h','steamnetworkingcustomsignaling.h','steamnetworkingsockets.h','steamnetworkingsockets_flat.h','steamnetworkingtypes.h','steamtypes.h','steamuniverse.h') {
    if (-not (Test-Path "$inc\$h")) { Invoke-WebRequest "https://raw.githubusercontent.com/ValveSoftware/GameNetworkingSockets/$sha/include/steam/$h" -OutFile "$inc\$h" -UseBasicParsing }
}
$vs = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath
$run = Join-Path $Out 'run'; New-Item -ItemType Directory -Force $run | Out-Null
$steamDir = 'C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux'
Copy-Item "$steamDir\steam_api.dll" $run -Force
Set-Content "$run\steam_appid.txt" '301650' -NoNewline -Encoding ascii
$src = Join-Path $PSScriptRoot 'probe.cpp'
cmd /c "`"$vs\VC\Auxiliary\Build\vcvars32.bat`" >nul && cl /nologo /EHsc /O2 /I`"$Out\include`" `"$src`" /Fo`"$Out\probe.obj`" /Fe`"$run\steam_net_probe.exe`""
"Built: $run\steam_net_probe.exe  (run from that directory with Steam running)"
