<#
.SYNOPSIS
    Asserts that a built or packaged OpenShim tree carries the whole load chain.

.DESCRIPTION
    OpenShim is three binaries now:

        battlezone98redux.exe -> winmm.dll -> bzloader.dll -> plugins\openshim.dll

    A missing plugin is deliberately survivable at runtime -- the game boots
    with the pre-main seams armed and no OpenShim at all. That is the right
    runtime behaviour and exactly the wrong packaging behaviour: a CI artifact
    or a release ZIP that ships winmm.dll alone builds green, installs clean,
    and reaches a user as "OpenShim's features don't work".

    So this checks the shape of the tree before it is published, and it checks
    identity rather than just presence: the bootstrap must still name the
    loader, the loader must still name the plugin directory, and the plugin
    must still export the v1 plugin ABI. Three unrelated files of the right
    names do not pass.

.PARAMETER Root
    Tree to validate. For -Layout Build this is the repository root (the chain
    is read from bin\<Configuration>\). For -Layout Suite it is the root of a
    staged or extracted OpenShim-Suite tree.

.PARAMETER Layout
    Build - a compiler output tree; checks the three binaries only.
    Suite - a packaged suite; also checks the companion files an install needs.

.EXAMPLE
    .\Test-PackageShape.ps1 -Root . -Layout Build

.EXAMPLE
    .\Test-PackageShape.ps1 -Root $extractedZip -Layout Suite
#>
[CmdletBinding()]
param(
    [string]$Root = ".",
    [ValidateSet('Build', 'Suite')]
    [string]$Layout = 'Build',
    [string]$Configuration = 'Release'
)

$ErrorActionPreference = 'Stop'

$Root = (Resolve-Path -LiteralPath $Root).Path
$binDir = if ($Layout -eq 'Build') { Join-Path $Root "bin\$Configuration" } else { Join-Path $Root 'bin\Release' }

$failures = @()
function Add-Failure([string]$message) {
    $script:failures += $message
    Write-Host "  FAIL  $message"
}
function Add-Pass([string]$message) {
    Write-Host "  ok    $message"
}

# Read a file once and keep both encodings. A PE holds its own DLL references
# as wide strings and its export names as ASCII, so both views are needed.
function Get-BinaryText([string]$path) {
    $bytes = [System.IO.File]::ReadAllBytes($path)
    return [pscustomobject]@{
        Ascii = [System.Text.Encoding]::ASCII.GetString($bytes)
        Wide  = [System.Text.Encoding]::Unicode.GetString($bytes)
        Size  = $bytes.Length
    }
}

Write-Host "Validating $Layout layout under $Root"

$chain = [ordered]@{
    'winmm.dll'            = (Join-Path $binDir 'winmm.dll')
    'bzloader.dll'         = (Join-Path $binDir 'bzloader.dll')
    'plugins\openshim.dll' = (Join-Path $binDir 'plugins\openshim.dll')
}

$present = @{}
foreach ($name in $chain.Keys) {
    $path = $chain[$name]
    if (-not (Test-Path -LiteralPath $path -PathType Leaf)) {
        Add-Failure "load-chain binary is missing: $name"
        continue
    }
    $info = Get-Item -LiteralPath $path
    if ($info.Length -eq 0) {
        Add-Failure "load-chain binary is empty: $name"
        continue
    }
    $present[$name] = Get-BinaryText $path
    $hash = (Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash.ToLowerInvariant()
    Add-Pass ("{0,-22} {1,10:N0} bytes  sha256={2}" -f $name, $info.Length, $hash)
}

# Identity, not just presence.
if ($present.ContainsKey('winmm.dll')) {
    if ($present['winmm.dll'].Wide -notmatch 'bzloader\.dll') {
        Add-Failure "winmm.dll no longer references bzloader.dll; it is not the bootstrap for this chain"
    } else {
        Add-Pass "winmm.dll references bzloader.dll"
    }
}
if ($present.ContainsKey('bzloader.dll')) {
    if ($present['bzloader.dll'].Ascii -notmatch 'BZLoader_GetSessionId') {
        Add-Failure "bzloader.dll does not export BZLoader_GetSessionId; it is not the plugin host"
    } else {
        Add-Pass "bzloader.dll exports the host entry points"
    }
}
if ($present.ContainsKey('plugins\openshim.dll')) {
    $pluginAscii = $present['plugins\openshim.dll'].Ascii
    foreach ($entry in @('BZPlugin_Query', 'BZPlugin_Load', 'BZPlugin_Shutdown')) {
        if ($pluginAscii -notmatch $entry) {
            Add-Failure "plugins\openshim.dll does not export $entry; it is not a BZLoader plugin"
        } else {
            Add-Pass "plugins\openshim.dll exports $entry"
        }
    }
}

if ($Layout -eq 'Suite') {
    # Everything an install needs beyond the three binaries. Kept in step with
    # Get-ArtifactSet in install_windows.ps1 and find_artifact_set in
    # install_linux.sh -- those refuse a bundle that fails any of these.
    $companions = [ordered]@{
        'scripts\patches.json'                        = 'the patch address table'
        'openshim.ini'                                = 'the shipped player config'
        'openshim.ini.example'                        = 'the documented config'
        'net.ini'                                     = 'the network config'
        'resources\renderer\enhanced\resources.version' = 'the Enhanced resource version marker'
        'resources\openshim\OpenShimAssets.ini'       = 'the asset manifest'
        'SHA256SUMS.txt'                              = 'the per-file checksum map'
        'release_metadata.json'                       = 'the source-identity record'
    }
    foreach ($rel in $companions.Keys) {
        $path = Join-Path $Root $rel
        if (-not (Test-Path -LiteralPath $path -PathType Leaf)) {
            Add-Failure "suite is missing $rel ($($companions[$rel]))"
        } else {
            Add-Pass "suite carries $rel"
        }
    }

    # The checksum map has to actually cover the new binaries, or a user
    # verifying a download proves only that the bootstrap arrived intact.
    $sums = Join-Path $Root 'SHA256SUMS.txt'
    if (Test-Path -LiteralPath $sums -PathType Leaf) {
        $sumText = Get-Content -LiteralPath $sums -Raw
        foreach ($required in @('winmm.dll', 'bzloader.dll', 'openshim.dll')) {
            if ($sumText -notmatch [regex]::Escape($required)) {
                Add-Failure "SHA256SUMS.txt does not cover $required"
            } else {
                Add-Pass "SHA256SUMS.txt covers $required"
            }
        }
    }
}

Write-Host ""
if ($failures.Count -gt 0) {
    foreach ($f in $failures) { Write-Host "::error::$f" }
    throw "package shape validation failed with $($failures.Count) problem(s)"
}
Write-Host "package shape OK: the whole load chain is present and identifies itself correctly"
