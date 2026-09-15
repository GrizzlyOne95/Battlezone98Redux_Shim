# Installs the four per-world renderer benchmark maps into the GOG addon tree.
#
# The roadmap's Phase 0 benchmark wants fixed scenes on Moon, Mars, Venus and
# Titan. These four are lcbench: the same heightfield, the same material grid,
# the same lightmap, the same mission script and the same spawn point, with
# only the .trn swapped. That is deliberate -- holding the geometry fixed is
# what lets a difference between two captures be attributed to the planet's
# atlas, palette, fog and sun rather than to the terrain under them.
#
# Because the payload is shared, the repository stores only the four .trn
# files. This script composes the rest from the lcbench fixture at install
# time, which also means the worlds can never drift away from the scene
# lcbench itself measures.
#
#   powershell -ExecutionPolicy Bypass -File scripts\Install-RenderWorldMaps.ps1 `
#       [-GameRoot <path>] [-World moon,mars] [-SunTime 0300] [-Force]
#
# Exit codes: 0 installed, 1 an input was missing or a world failed to
# compose, 2 bad usage.

[CmdletBinding()]
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",

    [ValidateSet("moon", "mars", "venus", "titan", "achilles", "io", "europa",
                 "ganymede", "elysium")]
    [string[]]$World = @("moon", "mars", "venus", "titan", "achilles", "io",
                         "europa", "ganymede", "elysium"),

    # Overrides [NormalView] Time in every installed .trn. BZ reads it as a
    # HHMM clock and places the sun from it, so this is the grazing-angle
    # sweep: 0300 puts the sun on the horizon, which is the condition the
    # N.V diffuse repair and the shadow bias were fixed for. Omit to keep
    # each world's own authored time.
    [ValidatePattern('^\d{3,4}$')]
    [string]$SunTime,

    # Reinstall even when the destination already holds a map of that name.
    [switch]$Force
)

$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$trnSource = Join-Path $repoRoot "reverse_engineering\test_missions\render_worlds"
$payloadSource = Join-Path $repoRoot "reverse_engineering\test_missions\live_combat_scaling"
$destRoot = Join-Path $GameRoot "addon\lcbworld"

# Copied verbatim from the lcbench fixture and renamed to the world's
# basename. The .lua has no dependency on the map name -- it reads lcbcfg.odf
# and nothing else -- so one script serves all four.
$renamedPayload = @("hg2", "mat", "lgt", "lua", "ini", "bzn")

# Shared across the whole package: the benchmark config the runner rewrites
# per scenario, and the unit ODFs the scenarios spawn.
$sharedPayload = @("lcbcfg.odf", "wrbase.odf", "wreng.odf", "wrmin.odf", "wrturr.odf")

$worldBasename = @{
    moon     = "lcbmoon"
    mars     = "lcbmars"
    venus    = "lcbvenus"
    titan    = "lcbtitan"
    achilles = "lcbachil"
    io       = "lcbio"
    europa   = "lcbeurop"
    ganymede = "lcbganym"
    elysium  = "lcbelys"
}

function Fail([string]$message, [int]$code = 1) {
    Write-Host $message -ForegroundColor Red
    exit $code
}

if (-not (Test-Path -LiteralPath $GameRoot)) {
    Fail "Game root not found: $GameRoot" 2
}
foreach ($required in @($trnSource, $payloadSource)) {
    if (-not (Test-Path -LiteralPath $required)) {
        Fail "Required source directory not found: $required"
    }
}

# The BZN is ASCII with CRLF line endings and names itself twice. Both lines
# have to follow the rename or the engine loads lcbench's terrain under the
# new mission -- which looks exactly like the world swap silently not working.
# Rewritten as bytes: a hand-edited BZN that picks up one bare LF passes
# git status and then kills the ASCII parser mid-object.
function Set-BznIdentity {
    param(
        [Parameter(Mandatory)][string]$Path,
        [Parameter(Mandatory)][string]$Basename
    )

    $bytes = [System.IO.File]::ReadAllBytes($Path)
    $text = [System.Text.Encoding]::ASCII.GetString($bytes)

    $text = [regex]::Replace($text, '(?m)^msn_filename = \S+', "msn_filename = $Basename.bzn")
    $text = [regex]::Replace($text, '(?m)^TerrainName = \S+', "TerrainName = $Basename")

    $rewritten = [System.Text.Encoding]::ASCII.GetBytes($text)
    [System.IO.File]::WriteAllBytes($Path, $rewritten)

    # Prove both fields took, and that nothing acquired a bare LF.
    $check = [System.Text.Encoding]::ASCII.GetString(
        [System.IO.File]::ReadAllBytes($Path))
    if ($check -notmatch [regex]::Escape("msn_filename = $Basename.bzn") -or
        $check -notmatch [regex]::Escape("TerrainName = $Basename")) {
        throw "BZN identity rewrite did not take for $Basename"
    }
    $bareLf = ([regex]::Matches($check, "(?<!`r)`n")).Count
    if ($bareLf -gt 0) {
        throw "BZN $Basename gained $bareLf bare LF line ending(s)"
    }
}

# Time= is the only value this script is allowed to touch in a .trn. Rewriting
# it in place keeps everything else byte-identical to the committed fixture, so
# a capture's lighting is either "the world's own" or "this one named override"
# and never something in between.
function Set-TrnSunTime {
    param(
        [Parameter(Mandatory)][string]$Path,
        [Parameter(Mandatory)][string]$Time
    )

    $text = [System.Text.Encoding]::ASCII.GetString(
        [System.IO.File]::ReadAllBytes($Path))
    $updated = [regex]::Replace($text, '(?m)^Time=\d+', "Time=$Time")
    if ($updated -eq $text) {
        throw "no [NormalView] Time= line to override in $Path"
    }
    [System.IO.File]::WriteAllBytes($Path, [System.Text.Encoding]::ASCII.GetBytes($updated))
}

New-Item -ItemType Directory -Path $destRoot -Force | Out-Null

foreach ($name in $sharedPayload) {
    $from = Join-Path $payloadSource $name
    if (-not (Test-Path -LiteralPath $from)) {
        Fail "Shared benchmark input not found: $from"
    }
    Copy-Item -LiteralPath $from -Destination (Join-Path $destRoot $name) -Force
}

$installed = @()

foreach ($w in $World) {
    $basename = $worldBasename[$w]
    $trn = Join-Path $trnSource "$basename.trn"
    if (-not (Test-Path -LiteralPath $trn)) {
        Fail "World terrain not found: $trn"
    }

    $destTrn = Join-Path $destRoot "$basename.trn"
    if ((Test-Path -LiteralPath $destTrn) -and -not $Force) {
        Write-Host "$basename already installed; pass -Force to overwrite" -ForegroundColor Yellow
        continue
    }

    foreach ($ext in $renamedPayload) {
        $from = Join-Path $payloadSource "lcbench.$ext"
        if (-not (Test-Path -LiteralPath $from)) {
            Fail "Benchmark payload not found: $from"
        }
        Copy-Item -LiteralPath $from -Destination (Join-Path $destRoot "$basename.$ext") -Force
    }

    Copy-Item -LiteralPath $trn -Destination $destTrn -Force
    Set-BznIdentity -Path (Join-Path $destRoot "$basename.bzn") -Basename $basename
    if ($SunTime) {
        Set-TrnSunTime -Path $destTrn -Time $SunTime
    }

    $time = ([regex]::Match(
        [System.Text.Encoding]::ASCII.GetString([System.IO.File]::ReadAllBytes($destTrn)),
        '(?m)^Time=(\d+)')).Groups[1].Value
    $atlas = ([regex]::Match(
        [System.Text.Encoding]::ASCII.GetString([System.IO.File]::ReadAllBytes($destTrn)),
        '(?m)^MaterialName[ \t]*=[ \t]*(\S+)')).Groups[1].Value

    $installed += [pscustomobject]@{
        World    = $w
        Mission  = "$basename.bzn"
        Atlas    = $atlas
        SunTime  = $time
    }
}

if ($installed.Count -eq 0) {
    Write-Host "nothing installed"
    exit 0
}

$installed | Format-Table -AutoSize | Out-String | Write-Host
Write-Host "installed to: $destRoot"
Write-Host ""
Write-Host "run one with:" -ForegroundColor Green
Write-Host ("  powershell -ExecutionPolicy Bypass -File " +
            "reverse_engineering\run_live_combat_benchmark.ps1 -World " +
            $installed[0].World)
exit 0
