# Proves that OpenShim's canonical Enhanced payload and Campaign Reimagined's
# CR_* shader fork are the same implementation, differing only by namespace.
#
# The roadmap gates deleting CR's duplicate on "binary and visual parity
# proven". Visual parity needs eyes; THIS is the binary half, and it is exact:
# every CR source is put through the same mechanical re-namespacing the port
# used, then compared byte-for-byte against the deployed OpenShim file. Any
# real divergence -- a fix landed on one side only, a constant retuned, a
# stray edit -- shows up as a diff. Drift cannot hide behind the prefix.
#
#   powershell -ExecutionPolicy Bypass -File scripts\Compare-EnhancedShaderParity.ps1 `
#       -CampaignReimaginedRoot "C:\path\to\CampaignReimagined"
#
# Exit codes: 0 parity, 1 divergence (or a missing counterpart), 2 bad usage.

[CmdletBinding()]
param(
    # CR checkout root. The shader sources are read from its Shaders\ folder,
    # which is the authored copy -- Local\Workshop\content\ is staging output
    # and is regenerated at publish, so it is routinely behind.
    [string]$CampaignReimaginedRoot,

    # Print the differing lines, not just the file names.
    [switch]$ShowDiff
)

$ErrorActionPreference = "Stop"
$repo = Split-Path -Parent $PSScriptRoot
$openShimDir = Join-Path $repo "resources\renderer\enhanced"

if (-not $CampaignReimaginedRoot) {
    $candidates = @()
    if ($env:BZR_CAMPAIGN_REPO) { $candidates += $env:BZR_CAMPAIGN_REPO }
    $candidates += Join-Path (Split-Path -Parent $repo) "Campaign-Reimagined"
    $CampaignReimaginedRoot = $candidates | Where-Object { Test-Path -LiteralPath (Join-Path $_ "Shaders") } | Select-Object -First 1
}

if (-not $CampaignReimaginedRoot -or -not (Test-Path -LiteralPath (Join-Path $CampaignReimaginedRoot "Shaders"))) {
    Write-Host "Campaign Reimagined checkout not found. Pass -CampaignReimaginedRoot." -ForegroundColor Yellow
    exit 2
}

$crDir = Join-Path $CampaignReimaginedRoot "Shaders"
Write-Host "CR sources : $crDir"
Write-Host "OpenShim   : $openShimDir"
Write-Host ""

# CR name -> OpenShim payload name. Order matters inside ApplyNamespace:
# longest file token first, so CR_base-sm4.hlsl is consumed before CR_base.hlsl
# can match its prefix.
$fileMap = [ordered]@{
    "CR_base-sm4.hlsl"              = "openshim_enhanced_base-sm4.hlsl"
    "CR_base-vertex.glsl"           = "openshim_enhanced_base-vertex.glsl"
    "CR_base-fragment.glsl"         = "openshim_enhanced_base-fragment.glsl"
    "CR_base.program"               = "openshim_enhanced_base.program"
    "CR_base.hlsl"                  = "openshim_enhanced_base-sm3.hlsl"
    "CR_terrain_glow-sm4.hlsl"      = "openshim_enhanced_terrain_glow-sm4.hlsl"
    "CR_terrain_glow-vertex.glsl"   = "openshim_enhanced_terrain_glow-vertex.glsl"
    "CR_terrain_glow-fragment.glsl" = "openshim_enhanced_terrain_glow-fragment.glsl"
    "CR_terrain_glow.hlsl"          = "openshim_enhanced_terrain_glow-sm3.hlsl"
    "CR_terrain-sm4.hlsl"           = "openshim_enhanced_terrain-sm4.hlsl"
    "CR_terrain-vertex.glsl"        = "openshim_enhanced_terrain-vertex.glsl"
    "CR_terrain-fragment.glsl"      = "openshim_enhanced_terrain-fragment.glsl"
    "CR_terrain.program"            = "openshim_enhanced_terrain.program"
    "CR_terrain.hlsl"               = "openshim_enhanced_terrain-sm3.hlsl"
}

# The only non-namespace difference the comparison tolerates: the attribution
# line at the top of each SM4 source, which names the owner rather than the
# implementation. Kept as two exact, whole-line mappings -- not a pattern --
# so nothing else can drift through this hole.
$headerMap = [ordered]@{
    "// DX11 SM4 shader path for Campaign Reimagined." =
        "// DX11 SM4 shader path for the OpenShim canonical Enhanced renderer."
    "// DX11 SM4 terrain shader path for Campaign Reimagined." =
        "// DX11 SM4 terrain shader path for the OpenShim canonical Enhanced renderer."
}

function ApplyNamespace([string]$text) {
    foreach ($entry in $headerMap.GetEnumerator()) {
        $text = $text.Replace($entry.Key, $entry.Value)
    }
    foreach ($entry in $fileMap.GetEnumerator()) {
        $text = $text.Replace($entry.Key, $entry.Value)
    }
    # CR authors the IBL art; OpenShim ships the neutral generated set.
    $text = $text.Replace("cr_ibl_", "openshim_ibl_")
    # Everything left is an identifier, macro, or Ogre program name.
    return $text.Replace("CR_", "OSE_")
}

$divergent = 0
$missing = 0
$compared = 0

foreach ($entry in $fileMap.GetEnumerator()) {
    $crPath = Join-Path $crDir $entry.Key
    $osPath = Join-Path $openShimDir $entry.Value

    if (-not (Test-Path -LiteralPath $crPath)) {
        Write-Host ("MISSING (CR)       {0}" -f $entry.Key) -ForegroundColor Yellow
        $missing++
        continue
    }
    if (-not (Test-Path -LiteralPath $osPath)) {
        Write-Host ("MISSING (OpenShim) {0}" -f $entry.Value) -ForegroundColor Yellow
        $missing++
        continue
    }

    # Read as raw text so CRLF is preserved: both payloads are CRLF throughout,
    # and a line-ending change is a real difference worth failing on.
    $ported = ApplyNamespace (Get-Content -Raw -LiteralPath $crPath)
    $actual = Get-Content -Raw -LiteralPath $osPath
    $compared++

    if ($ported -ceq $actual) {
        Write-Host ("PARITY             {0}" -f $entry.Value) -ForegroundColor Green
        continue
    }

    $divergent++
    Write-Host ("DIVERGED           {0}" -f $entry.Value) -ForegroundColor Red

    if ($ShowDiff) {
        $left  = $ported -split "`r?`n"
        $right = $actual -split "`r?`n"
        $delta = Compare-Object -ReferenceObject $left -DifferenceObject $right
        foreach ($line in $delta) {
            $side = if ($line.SideIndicator -eq "<=") { "CR only" } else { "OpenShim only" }
            Write-Host ("    [{0}] {1}" -f $side, $line.InputObject)
        }
    }
}

Write-Host ""
Write-Host ("compared={0} diverged={1} missing={2}" -f $compared, $divergent, $missing)

if ($divergent -gt 0 -or $missing -gt 0) {
    Write-Host "Enhanced shader parity FAILED" -ForegroundColor Red
    Write-Host "Re-run with -ShowDiff to see the differing lines." -ForegroundColor Yellow
    exit 1
}

Write-Host "Enhanced shader parity holds" -ForegroundColor Green
exit 0
