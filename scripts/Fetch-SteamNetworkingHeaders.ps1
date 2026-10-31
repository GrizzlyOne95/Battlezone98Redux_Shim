# Public Valve headers only. No SDK binaries or headers are committed.
param([string]$Out = (Join-Path $PSScriptRoot '../third_party/steam-networking'))
$ErrorActionPreference = 'Stop'
$sha = 'd534c19aa760df3fb75fd20db13ba1932b8a5463'
$include = Join-Path $Out 'steam'
New-Item -ItemType Directory -Force $include | Out-Null
$stamp = Join-Path $Out 'revision.txt'
$current = if (Test-Path -LiteralPath $stamp) { (Get-Content -LiteralPath $stamp -Raw).Trim() } else { '' }
foreach ($header in 'isteamnetworkingsockets.h','isteamnetworkingutils.h','steam_api_common.h','steamclientpublic.h','steamnetworkingtypes.h','steamtypes.h','steamuniverse.h') {
    $path = Join-Path $include $header
    if ($current -ne $sha -or -not (Test-Path -LiteralPath $path)) {
        Invoke-WebRequest "https://raw.githubusercontent.com/ValveSoftware/GameNetworkingSockets/$sha/include/steam/$header" -OutFile "$path.tmp" -UseBasicParsing
        Move-Item -LiteralPath "$path.tmp" -Destination $path -Force
    }
}
Set-Content -LiteralPath $stamp -Value $sha -Encoding ascii
Write-Output "Steam networking headers: $sha at $Out"
