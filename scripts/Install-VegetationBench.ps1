# Installs the Achilles vegetation and water bench into the GOG addon tree.
#
# lcbveg is lcbench's shape asking a different question: one quiet scene with no
# combat, on the only world Redux ships that has grass, trees and a river in its
# terrain set, for judging what ground content actually looks like.
#
# Unlike Install-RenderWorldMaps.ps1, this map does NOT reuse lcbench's
# heightfield. lcbench's is a plain at raw height 0 with a berm through it --
# there is no low ground for a river to be in, and Achilles' river and waterfall
# tiles are the point. So the terrain, material grid and lightmap are generated
# by reverse_engineering\test_missions\lcbveg\Make-VegBenchTerrain.py, which is
# also why they are not committed: they are reproducible from that script.
#
# Only the .bzn comes from the lcbench fixture, because it holds nothing but the
# player and a spawn point.
#
#   powershell -ExecutionPolicy Bypass -File scripts\Install-VegetationBench.ps1 `
#       [-GameRoot <path>] [-WorldBuilder <repo>] [-Force]
#
# Exit codes: 0 installed, 1 an input was missing or generation failed.

[CmdletBinding()]
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",

    # Battlezone98Redux_WorldBuilder, which owns the .mat and .hg2 encoders.
    [string]$WorldBuilder,

    # Regenerate the terrain payload even when it is already present.
    [switch]$Force
)

$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$source = Join-Path $repoRoot "reverse_engineering\test_missions\lcbveg"
$fixture = Join-Path $repoRoot "reverse_engineering\test_missions\live_combat_scaling"
$destination = Join-Path $GameRoot "addon\lcbveg"

foreach ($dir in @($source, $fixture)) {
    if (-not (Test-Path -LiteralPath $dir -PathType Container)) {
        Write-Host "Missing input directory: $dir" -ForegroundColor Red
        exit 1
    }
}
if (-not (Test-Path -LiteralPath $GameRoot -PathType Container)) {
    Write-Host "Game root not found: $GameRoot" -ForegroundColor Red
    exit 1
}

# --------------------------------------------------------------- generate --
$generated = @("lcbveg.hg2", "lcbveg.mat", "lcbveg.lgt")
$missing = @($generated | Where-Object {
    -not (Test-Path -LiteralPath (Join-Path $source $_) -PathType Leaf) })

if ($Force -or $missing.Count -gt 0) {
    if ($missing.Count -gt 0) {
        Write-Host ("generating terrain payload ({0} missing)" -f $missing.Count)
    } else {
        Write-Host "regenerating terrain payload (-Force)"
    }
    $genArgs = @((Join-Path $source "Make-VegBenchTerrain.py"))
    if ($WorldBuilder) { $genArgs += @("--worldbuilder", $WorldBuilder) }

    # python writes its progress to stdout and its complaints to stderr; with
    # $ErrorActionPreference = "Stop" a single stderr line would become a
    # terminating NativeCommandError and abort a run that actually succeeded.
    # The exit code is the verdict.
    $previous = $ErrorActionPreference
    $ErrorActionPreference = "Continue"
    try {
        & python @genArgs 2>&1 | ForEach-Object { Write-Host "  $_" }
        $code = $LASTEXITCODE
    }
    finally { $ErrorActionPreference = $previous }

    if ($code -ne 0) {
        Write-Host "terrain generation failed (exit $code)" -ForegroundColor Red
        exit 1
    }
}

# ----------------------------------------------------------------- install --
New-Item -ItemType Directory -Force -Path $destination | Out-Null

# Authored in the repository.
$authored = @("lcbveg.trn", "lcbveg.lua", "lcbveg.ini", "lcbvcfg.odf")
$payload = $authored + $generated

$copied = 0
foreach ($name in $payload) {
    $from = Join-Path $source $name
    if (-not (Test-Path -LiteralPath $from -PathType Leaf)) {
        Write-Host "Missing: $from" -ForegroundColor Red
        exit 1
    }
    Copy-Item -LiteralPath $from -Destination (Join-Path $destination $name) -Force
    $copied++
}

# The only file taken from the benchmark fixture. lcbench.bzn contains the
# player and nothing else, which is exactly what this mission wants: everything
# on screen is placed by lcbveg.lua, so nothing can be attributed to the .bzn.
$bzn = Join-Path $fixture "lcbench.bzn"
if (-not (Test-Path -LiteralPath $bzn -PathType Leaf)) {
    Write-Host "Missing fixture: $bzn" -ForegroundColor Red
    exit 1
}
Copy-Item -LiteralPath $bzn -Destination (Join-Path $destination "lcbveg.bzn") -Force
$copied++

Write-Host ""
Write-Host ("installed {0} files to {1}" -f $copied, $destination) -ForegroundColor Green
foreach ($name in ($payload + @("lcbveg.bzn"))) {
    $item = Get-Item -LiteralPath (Join-Path $destination $name)
    Write-Host ("  {0,-16} {1,10:N0} bytes" -f $item.Name, $item.Length)
}

Write-Host ""
Write-Host "Launch it with:  battlezone98redux.exe lcbveg" -ForegroundColor Cyan
Write-Host "Tune it by editing addon\lcbveg\lcbvcfg.odf and relaunching."
Write-Host "Campaign Reimagined must be active: the grass mesh and material are"
Write-Host "CR's, and CR's TerrainClutter is what the bench is there to exercise."
exit 0
