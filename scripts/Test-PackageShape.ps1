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

.PARAMETER ExpectedVersion
    Dotted version the tag promises, e.g. 1.0.0.32. When given, every module
    must carry it in both the string and numeric version fields, and must
    name itself correctly. v1.0.0.31 shipped binaries reporting 1.0.0.30
    because the tag moved and the resource did not; with three independently
    identifiable binaries that invariant is worth enforcing rather than
    remembering.

.PARAMETER ExpectedTag
    Suite layout only. release_metadata.json must record this tag.

.PARAMETER ExpectedCommit
    Suite layout only. release_metadata.json must record this commit.

.EXAMPLE
    .\Test-PackageShape.ps1 -Root . -Layout Build -ExpectedVersion 1.0.0.32

.EXAMPLE
    .\Test-PackageShape.ps1 -Root $extractedZip -Layout Suite -ExpectedTag v1.0.0.32
#>
[CmdletBinding()]
param(
    [string]$Root = ".",
    [ValidateSet('Build', 'Suite')]
    [string]$Layout = 'Build',
    [string]$Configuration = 'Release',
    [string]$ExpectedVersion = "",
    [string]$ExpectedTag = "",
    [string]$ExpectedCommit = ""
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

# Tag, binary versions and self-identification must agree. The names are part
# of it: one resource file feeds all three modules, so a module that forgets
# to define its token silently inherits winmm.dll's identity.
if ($ExpectedVersion) {
    $identity = @{
        'winmm.dll'            = 'winmm.dll'
        'bzloader.dll'         = 'bzloader.dll'
        'plugins\openshim.dll' = 'openshim.dll'
    }
    foreach ($name in $chain.Keys) {
        if (-not $present.ContainsKey($name)) { continue }
        $failuresBefore = $failures.Count
        $info = [System.Diagnostics.FileVersionInfo]::GetVersionInfo($chain[$name])

        # The string fields and the numeric FILEVERSION are separate lines in
        # the .rc and can disagree, so check both rather than either.
        $numeric = "$($info.FileMajorPart).$($info.FileMinorPart)." +
                   "$($info.FileBuildPart).$($info.FilePrivatePart)"
        foreach ($pair in @(
            @{ What = 'FileVersion';    Got = $info.FileVersion },
            @{ What = 'ProductVersion'; Got = $info.ProductVersion },
            @{ What = 'FILEVERSION';    Got = $numeric })) {
            if ($pair.Got -ne $ExpectedVersion) {
                Add-Failure "$name $($pair.What) is '$($pair.Got)', expected '$ExpectedVersion'"
            }
        }

        $wanted = $identity[$name]
        foreach ($pair in @(
            @{ What = 'InternalName';     Got = $info.InternalName },
            @{ What = 'OriginalFilename'; Got = $info.OriginalFilename })) {
            if ($pair.Got -ne $wanted) {
                Add-Failure "$name $($pair.What) is '$($pair.Got)', expected '$wanted'"
            }
        }

        if ($failures.Count -eq $failuresBefore) {
            Add-Pass ("{0,-22} v={1} identifies as {2}" -f $name, $info.FileVersion, $info.InternalName)
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

    # Provenance: the archive states which tag and commit produced it, and
    # that claim is only worth something if something checks it.
    $metaPath = Join-Path $Root 'release_metadata.json'
    if (($ExpectedTag -or $ExpectedCommit) -and (Test-Path -LiteralPath $metaPath -PathType Leaf)) {
        $meta = Get-Content -LiteralPath $metaPath -Raw | ConvertFrom-Json
        if ($ExpectedTag -and $meta.Tag -ne $ExpectedTag) {
            Add-Failure "release_metadata.json Tag is '$($meta.Tag)', expected '$ExpectedTag'"
        } elseif ($ExpectedTag) {
            Add-Pass "release_metadata.json records tag $($meta.Tag)"
        }
        if ($ExpectedCommit -and $meta.Commit -ne $ExpectedCommit) {
            Add-Failure "release_metadata.json Commit is '$($meta.Commit)', expected '$ExpectedCommit'"
        } elseif ($ExpectedCommit) {
            Add-Pass "release_metadata.json records commit $($meta.Commit.Substring(0, 8))"
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
