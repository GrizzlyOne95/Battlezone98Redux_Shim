<#
.SYNOPSIS
    Deploys the built shim to a Battlezone 98 Redux install.

.DESCRIPTION
    winmm.dll and scripts/patches.json must move together. The DLL carries the
    patch list by name; patches.json carries the address and guard bytes for
    each name. Deploying only the DLL leaves every new patch resolving to
    address 0, where it is silently skipped -- the only symptom is one [SKIP]
    line in openshim.log among forty, which is exactly how a shipped sun-flash
    opt-out spent a test run doing nothing.

    Both files are backed up with a timestamp before being overwritten, and the
    deployed patches.json is checked against the repo copy afterwards so a
    partial copy cannot pass silently.

.PARAMETER GameDir
    Battlezone 98 Redux install directory. Defaults to the GOG test install.

.PARAMETER Configuration
    Build configuration to deploy from. Defaults to Release.

.EXAMPLE
    .\Deploy-OpenShim.ps1
#>
[CmdletBinding()]
param(
    [string]$GameDir = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet('Release', 'Debug')]
    [string]$Configuration = 'Release'
)

$ErrorActionPreference = 'Stop'

$repoRoot = Split-Path -Parent $PSScriptRoot
$stamp = Get-Date -Format 'yyyyMMdd-HHmmss'

$pairs = @(
    @{ Source = Join-Path $repoRoot "bin\$Configuration\winmm.dll"; Target = Join-Path $GameDir 'winmm.dll' },
    @{ Source = Join-Path $repoRoot 'scripts\patches.json';         Target = Join-Path $GameDir 'scripts\patches.json' }
)

# Renderer resources move with the DLL by the same rule as patches.json: a new
# DLL paired with stale Enhanced shaders must fail loudly, not silently.
$renderSourceDir = Join-Path $repoRoot 'resources\renderer\enhanced'
$renderTargetDir = Join-Path $GameDir 'openshim\renderer\enhanced'
$uiSourceDir = Join-Path $repoRoot 'resources\ui\custom_widgets'
$uiTargetDir = Join-Path $GameDir 'BZ_ASSETS_CORE\common\ui\CustomWidgets'

foreach ($pair in $pairs) {
    if (-not (Test-Path -LiteralPath $pair.Source)) {
        throw "Missing build output: $($pair.Source). Build $Configuration|Win32 first."
    }
}

foreach ($pair in $pairs) {
    $targetDir = Split-Path -Parent $pair.Target
    if (-not (Test-Path -LiteralPath $targetDir)) {
        New-Item -ItemType Directory -Force -Path $targetDir | Out-Null
    }
    if (Test-Path -LiteralPath $pair.Target) {
        Copy-Item -LiteralPath $pair.Target -Destination "$($pair.Target).bak-$stamp" -Force
    }
    Copy-Item -LiteralPath $pair.Source -Destination $pair.Target -Force
    $info = Get-Item -LiteralPath $pair.Target
    Write-Host ("deployed {0,-14} {1,9:N0} bytes" -f $info.Name, $info.Length)
}

# Verify rather than trust: every patch name the repo declares must be present
# in the deployed json, or the DLL will resolve it to address 0.
$repoJson = Get-Content -Raw -LiteralPath (Join-Path $repoRoot 'scripts\patches.json') | ConvertFrom-Json
$gameJson = Get-Content -Raw -LiteralPath (Join-Path $GameDir 'scripts\patches.json') | ConvertFrom-Json

$missing = @()
foreach ($group in 'patches', 'globals', 'static_pointers') {
    $repoNames = @($repoJson.$group | ForEach-Object { $_.name })
    $gameNames = @($gameJson.$group | ForEach-Object { $_.name })
    $missing += $repoNames | Where-Object { $gameNames -notcontains $_ }
}

if ($missing.Count -gt 0) {
    throw "Deployed patches.json is missing: $($missing -join ', ')"
}

# Deploy the OpenShim-owned Enhanced renderer resources (winmm.dll and these
# files must move together; the DLL validates the version marker at startup).
if (-not (Test-Path -LiteralPath (Join-Path $renderSourceDir 'resources.version'))) {
    throw "Missing renderer resource manifest: $renderSourceDir\resources.version"
}
New-Item -ItemType Directory -Force -Path $renderTargetDir | Out-Null
Copy-Item -Path (Join-Path $renderSourceDir '*') -Destination $renderTargetDir -Force
$deployedVersion = Get-Content -Raw -LiteralPath (Join-Path $renderTargetDir 'resources.version')
Write-Host ("renderer resources deployed: {0} files, resources.version={1}" -f
    @((Get-ChildItem -LiteralPath $renderTargetDir).Count, $deployedVersion.Trim()))

# The native Settings/Keybind pages assemble these passive tiles at runtime:
# one flat fill per surface, in colours sampled from the stock UI art. Keep
# them with the DLL so a clean install cannot silently fall back to
# missing-texture panels.
$uiFiles = @(
    'uiline.png', 'uiplate.png', 'uibtn.png', 'uibtnhv.png'
)
New-Item -ItemType Directory -Force -Path $uiTargetDir | Out-Null
foreach ($name in $uiFiles) {
    $source = Join-Path $uiSourceDir $name
    $target = Join-Path $uiTargetDir $name
    if (-not (Test-Path -LiteralPath $source)) {
        throw "Missing OpenShim UI resource: $source"
    }
    Copy-Item -LiteralPath $source -Destination $target -Force
    if ((Get-FileHash -Algorithm SHA256 -LiteralPath $source).Hash -ne
        (Get-FileHash -Algorithm SHA256 -LiteralPath $target).Hash) {
        throw "UI resource verification failed: $name"
    }
}
Write-Host ("UI resources deployed: {0} flat tiles" -f $uiFiles.Count)

Write-Host ""
Write-Host "patches.json verified: all $(@($repoJson.patches).Count + @($repoJson.globals).Count + @($repoJson.static_pointers).Count) declared names present."
Write-Host "Backups written with suffix .bak-$stamp"
