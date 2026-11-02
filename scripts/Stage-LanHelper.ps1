<#
.SYNOPSIS
Stage the separately built Win32 LAN helper into a game or preview directory.
.DESCRIPTION
Build the sibling DedicatedServer's build_lan_helper.py first. This script
checks the source manifest, hash and PE architecture before copying anything.
It does not download, run a server, change firewall rules, or edit game INIs.
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory)][string]$HelperDirectory,
    [string]$DestinationRoot = (Join-Path (Split-Path -Parent $PSScriptRoot) 'bin\Release')
)
$ErrorActionPreference = 'Stop'
$source = (Resolve-Path -LiteralPath $HelperDirectory).Path
$exe = Join-Path $source 'BZRServer.exe'
$manifestPath = Join-Path $source 'manifest.json'
$manifest = Get-Content -LiteralPath $manifestPath -Raw | ConvertFrom-Json
if ($manifest.format -ne 1 -or $manifest.architecture -ne 'win32' -or
    $manifest.discoveryProtocol -ne 'BZRLAN1' -or $manifest.dirty -ne $false -or
    $manifest.revision -notmatch '^[0-9a-f]{40}$') {
    throw 'The LAN helper must have a clean source revision and a Win32 BZRLAN1 manifest.'
}
$hash = (Get-FileHash -LiteralPath $exe -Algorithm SHA256).Hash
if ($hash -ne $manifest.sha256) { throw 'LAN helper SHA256 does not match its manifest.' }
$bytes = [IO.File]::ReadAllBytes($exe)
if ($bytes.Length -lt 64 -or $bytes[0] -ne 0x4D -or $bytes[1] -ne 0x5A) { throw 'Invalid LAN helper PE.' }
$pe = [BitConverter]::ToInt32($bytes, 0x3C)
if ($pe -lt 64 -or $pe -gt $bytes.Length - 6 -or
    [BitConverter]::ToUInt32($bytes, $pe) -ne 0x4550 -or
    [BitConverter]::ToUInt16($bytes, $pe + 4) -ne 0x14C) { throw 'LAN helper must be an i386 Win32 PE.' }
foreach ($name in @('LAN_DISCOVERY.md', 'LICENSE')) {
    if (-not (Test-Path -LiteralPath (Join-Path $source $name) -PathType Leaf)) { throw "Missing helper companion: $name" }
}
$licenses = @('licenses/python/LICENSE.txt', 'licenses/websockets/LICENSE', 'licenses/pyinstaller/COPYING.txt')
foreach ($name in $licenses) {
    $path = Join-Path $source $name
    $expected = $manifest.licenses.PSObject.Properties[$name].Value
    if (-not $expected -or -not (Test-Path -LiteralPath $path -PathType Leaf) -or
        (Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash -ne $expected) {
        throw "LAN helper runtime license missing or hash mismatch: $name"
    }
}
$target = Join-Path ([IO.Path]::GetFullPath($DestinationRoot)) 'tools\lan'
if ([IO.Path]::GetFullPath($source).TrimEnd('\') -ne $target.TrimEnd('\')) {
    New-Item -ItemType Directory -Force -Path $target | Out-Null
    foreach ($name in (@('BZRServer.exe', 'manifest.json', 'LAN_DISCOVERY.md', 'LICENSE') + $licenses)) {
        New-Item -ItemType Directory -Force -Path (Split-Path -Parent (Join-Path $target $name)) | Out-Null
        Copy-Item -LiteralPath (Join-Path $source $name) -Destination (Join-Path $target $name) -Force
    }
}
if ((Get-FileHash -LiteralPath (Join-Path $target 'BZRServer.exe') -Algorithm SHA256).Hash -ne $hash) {
    throw 'Staged LAN helper hash mismatch.'
}
Write-Host "LAN helper staged at $target (source $($manifest.revision), SHA256 $hash)"
