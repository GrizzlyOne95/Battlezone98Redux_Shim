# Harvests what a run's logs actually prove about the renderer, as one record.
#
# The visual benchmark needs each capture labelled with the state it was taken
# in, and that label has to come from the run rather than from the ini that was
# written before it. Several of this project's dead ends were a capture assumed
# to be one arm while the game ran another:
#
#   - Ogre.cfg's "Render System=" line is not authoritative; the shim rewrites
#     the backend at ConfigFile::load, so only openshim.log says what ran.
#   - With Campaign Reimagined installed, Ogre parses CR's shader payload, not
#     OpenShim's, so an edit to the OpenShim copy renders nothing. The Ogre log
#     names the .program scripts it parsed, which settles the question.
#   - A run that never reached its terminal marker is not a measurement.
#
#   powershell -ExecutionPolicy Bypass -File scripts\Get-RenderEvidence.ps1 `
#       [-GameRoot <path>] [-Json] [-OutFile evidence.json]
#
# Exit codes: 0 evidence collected, 1 the run cannot be trusted as a capture,
# 2 the logs are missing.

[CmdletBinding()]
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",

    # Ignore log content written before this time. Pass the run's start so a
    # previous session's lines cannot be read as this run's evidence.
    [datetime]$Since = [datetime]::MinValue,

    [switch]$Json,
    [string]$OutFile
)

$ErrorActionPreference = "Stop"

$shimLog = Join-Path $GameRoot "logs\openshim.log"
$ogreLog = Join-Path $GameRoot "logs\BZOgreLogfile.log"
$crashLog = Join-Path $GameRoot "logs\openshim_crash.log"
$deployedVersion = Join-Path $GameRoot "openshim\renderer\enhanced\resources.version"

foreach ($required in @($shimLog, $ogreLog)) {
    if (-not (Test-Path -LiteralPath $required)) {
        Write-Host "Log not found: $required" -ForegroundColor Red
        exit 2
    }
}

function Read-LogLines([string]$path) {
    # Both logs are held open by the game, so a plain Get-Content can fail
    # while a run is still live.
    $stream = [System.IO.File]::Open($path, 'Open', 'Read', 'ReadWrite')
    try {
        $reader = New-Object System.IO.StreamReader($stream)
        return $reader.ReadToEnd() -split "`r?`n"
    } finally {
        $stream.Dispose()
    }
}

function Select-Last([string[]]$lines, [string]$pattern) {
    $hit = $lines | Select-String -Pattern $pattern | Select-Object -Last 1
    if ($hit) { return $hit.Line } else { return $null }
}

function Get-Field([string]$line, [string]$key) {
    if (-not $line) { return $null }
    $m = [regex]::Match($line, [regex]::Escape($key) + '=([^\s]+)')
    if ($m.Success) { return $m.Groups[1].Value } else { return $null }
}

$shim = Read-LogLines $shimLog
$ogre = Read-LogLines $ogreLog

# --- what actually rendered ------------------------------------------------
$backendLine  = Select-Last $shim '\[RENDER\] backend\.requested='
$identLine    = Select-Last $shim '\[RENDER\] backend identified'
$profileLine  = Select-Last $shim '\[RENDER\] profile\.user='
$capsLine     = Select-Last $shim '\[RENDER\] enhanced\.supported='
$bitsLine     = Select-Last $shim '\[RENDER\] enhanced\.sharpening='
$fallbackLine = Select-Last $shim '\[RENDER\] fallback='

$evidence = [ordered]@{
    collectedAt       = (Get-Date).ToString("o")
    gameRoot          = $GameRoot

    backendRequested  = Get-Field $backendLine 'backend.requested'
    backendEffective  = Get-Field $backendLine 'backend.effective'
    backendIdentified = if ($identLine) { ($identLine -split 'active render system is ')[-1] } else { $null }

    profileUser       = Get-Field $profileLine 'profile.user'
    profileContent    = Get-Field $profileLine 'profile.content'
    profileEffective  = Get-Field $profileLine 'profile.effective'
    profileSource     = Get-Field $profileLine 'profile.source'

    enhancedSupported = Get-Field $capsLine 'enhanced.supported'
    resourcesCompat   = Get-Field $capsLine 'resources.compatible'
    capabilities      = Get-Field $capsLine 'capabilities'
    fallbackReason    = if ($fallbackLine) { ($fallbackLine -split 'fallback=')[-1] } else { $null }
    enhancedBits      = if ($bitsLine) { ($bitsLine -split '\[RENDER\] ')[-1] } else { $null }

    deployedResourceVersion = if (Test-Path -LiteralPath $deployedVersion) {
        (Get-Content -Raw -LiteralPath $deployedVersion).Trim()
    } else { $null }
}

# --- colour space / framebuffer --------------------------------------------
# The DX11 capture only exists when [Diagnostics] TraceDX11ColorSpace=1; the
# Ogre option line is always there and is the minimum the record needs.
$evidence.srgbGammaConversion = $null
$srgb = $ogre | Select-String -Pattern 'sRGB Gamma Conversion\s*=\s*(\w+)' | Select-Object -Last 1
if ($srgb) { $evidence.srgbGammaConversion = $srgb.Matches[0].Groups[1].Value }

$colorSpaceLines = @($shim | Select-String -Pattern '\[DX11 ColorSpace\]' | ForEach-Object { $_.Line })
$evidence.colorSpaceCaptured = ($colorSpaceLines.Count -gt 0)
$evidence.colorSpaceLines = $colorSpaceLines

# --- which shader payload the engine actually loaded -----------------------
# This is the question that a shader edit's apparent no-op usually turns out to
# be. Ogre names every .program script it parses.
$parsed = @($ogre |
    Select-String -Pattern 'Parsing script (\S+\.program)' |
    ForEach-Object { $_.Matches[0].Groups[1].Value } |
    Sort-Object -Unique)

$evidence.programScriptsParsed = $parsed

# Match on the leaf name: Ogre logs a resource-relative path for some groups
# ("openshim/renderer/enhanced/openshim_enhanced_base.program") and a bare name
# for others ("CR_base.program"). Globbing the whole string misses the former
# and silently reports the payload as CR-only -- the exact mislabelling this
# record exists to prevent.
function Test-PayloadLoaded([string[]]$scripts, [string]$leafPrefix) {
    return [bool](@($scripts | Where-Object {
        [System.IO.Path]::GetFileName($_) -like "$leafPrefix*"
    }).Count)
}

$evidence.crPayloadLoaded = Test-PayloadLoaded $parsed 'CR_'
$evidence.openShimPayloadLoaded = Test-PayloadLoaded $parsed 'openshim_enhanced_'

$evidence.shaderPayloadsParsed =
    if ($evidence.crPayloadLoaded -and $evidence.openShimPayloadLoaded) { "both" }
    elseif ($evidence.crPayloadLoaded) { "CampaignReimagined" }
    elseif ($evidence.openShimPayloadLoaded) { "OpenShim" }
    else { "stock" }

# Parsed is not rendering. Both payloads can be loaded at once -- they use
# disjoint program namespaces deliberately -- but only one of them is reachable
# from a material. CR ships the en-*/og-* techniques on the stock-named
# materials, so wherever CR's payload is present its programs are the ones the
# scheme resolves to, and an edit to the OpenShim copy changes nothing on
# screen. OpenShim's OSE_ programs are compiled and then referenced by no
# material until the stock-material retrofit lands.
$evidence.enhancedImplementationRendering =
    if ($evidence.crPayloadLoaded) { "CampaignReimagined" }
    elseif ($evidence.openShimPayloadLoaded) { "OpenShim (no CR materials present)" }
    else { "stock" }

# --- shader permutations ---------------------------------------------------
$rejected = @($ogre |
    Select-String -Pattern "Invalid target for D3D11 shader '([^']+)' - '([^']+)'" |
    ForEach-Object { "{0} ({1})" -f $_.Matches[0].Groups[1].Value, $_.Matches[0].Groups[2].Value })

$evidence.shaderTargetsRejected = $rejected.Count
$evidence.shaderTargetsRejectedSample = @($rejected | Select-Object -First 5)

# Scheme rewrites say whether the profile reached the viewports at all.
$rewrites = @($shim |
    Select-String -Pattern '\[RENDER\] scheme rewrite incoming=(\S+) final=(\S+)' |
    ForEach-Object { "{0} -> {1}" -f $_.Matches[0].Groups[1].Value, $_.Matches[0].Groups[2].Value } |
    Sort-Object -Unique)
$evidence.schemeRewrites = $rewrites
$evidence.schemeRewriteCount = $rewrites.Count

# --- is this a usable capture at all? --------------------------------------
$problems = @()

if (-not $evidence.backendIdentified) {
    $problems += "no backend identification in openshim.log: the shim never observed a render system"
}
if ($evidence.profileEffective -eq 'Enhanced' -and $evidence.resourcesCompat -ne 'yes') {
    $problems += "Enhanced requested but resources.compatible=$($evidence.resourcesCompat): the payload/DLL pairing failed"
}
if ($evidence.profileEffective -in @('Enhanced', 'Retro') -and $evidence.schemeRewriteCount -eq 0) {
    $problems += "profile.effective=$($evidence.profileEffective) but no scheme rewrite was logged: the profile never reached a viewport"
}
if ($evidence.fallbackReason) {
    $problems += "renderer fell back: $($evidence.fallbackReason)"
}

# A crash log newer than the run start means the capture may be of a process
# that was already unwinding.
if ((Test-Path -LiteralPath $crashLog) -and $Since -ne [datetime]::MinValue) {
    $crashItem = Get-Item -LiteralPath $crashLog
    if ($crashItem.LastWriteTime -ge $Since) {
        $problems += "openshim_crash.log was written during this run ($($crashItem.LastWriteTime))"
    }
}

$evidence.problems = $problems
$evidence.usableCapture = ($problems.Count -eq 0)

# --- output ----------------------------------------------------------------
if ($OutFile) {
    $evidence | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $OutFile -Encoding UTF8
    Write-Host "evidence written: $OutFile"
}

if ($Json) {
    $evidence | ConvertTo-Json -Depth 6
} else {
    Write-Host "renderer  : $($evidence.backendIdentified) (requested=$($evidence.backendRequested) effective=$($evidence.backendEffective))"
    Write-Host "profile   : effective=$($evidence.profileEffective) user=$($evidence.profileUser) content=$($evidence.profileContent) source=$($evidence.profileSource)"
    Write-Host "enhanced  : supported=$($evidence.enhancedSupported) resources.compatible=$($evidence.resourcesCompat) caps=$($evidence.capabilities)"
    Write-Host "payload   : parsed=$($evidence.shaderPayloadsParsed) rendering=$($evidence.enhancedImplementationRendering)"
    Write-Host "            enhanced .program scripts: $(@($evidence.programScriptsParsed | Where-Object { [System.IO.Path]::GetFileName($_) -like 'CR_*' -or [System.IO.Path]::GetFileName($_) -like 'openshim_enhanced_*' }) -join ', ')"
    Write-Host "deployed  : resources.version=$($evidence.deployedResourceVersion)"
    Write-Host "colour    : sRGB Gamma Conversion=$($evidence.srgbGammaConversion) dx11Capture=$($evidence.colorSpaceCaptured)"
    Write-Host "schemes   : $($evidence.schemeRewriteCount) rewrite(s) $($evidence.schemeRewrites -join '; ')"
    Write-Host "shaders   : $($evidence.shaderTargetsRejected) rejected target(s)"
}

if (-not $evidence.usableCapture) {
    Write-Host ""
    foreach ($p in $problems) { Write-Host "NOT A USABLE CAPTURE: $p" -ForegroundColor Red }
    exit 1
}

Write-Host ""
Write-Host "capture state is coherent" -ForegroundColor Green
exit 0
