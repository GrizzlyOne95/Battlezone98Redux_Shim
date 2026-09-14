# Checks the per-world benchmark terrains against what the install can resolve.
#
# The failure mode this exists to catch is silent. A .map name in a .trn is a
# key into that world's detail atlas, not a file on disk, so a name the atlas
# does not carry resolves to the atlas's default tile and the terrain renders
# -- just wrong, and only in the places that used the missing tile. Likewise a
# [TextureType] the shared material grid names but the .trn does not declare
# leaves those cells pointing at nothing. Neither reports anything.
#
# So every claim the fixtures make is checked mechanically:
#
#   1. the texture-type index set matches Moon's, because lcbench.mat was
#      authored on Moon and every index it can name must be declared
#   2. every .map inside a [TextureType] resolves in <xx>_detail_atlas.csv
#   3. the [Atlases] material the .trn names exists
#   4. the file is ASCII with CRLF only, and declares one [Size] matching the
#      shared heightfield
#
#   powershell -ExecutionPolicy Bypass -File scripts\Test-RenderWorldMaps.ps1 `
#       [-GameRoot <path>] [-ShowResolved]
#
# Exit codes: 0 all worlds check out, 1 at least one finding, 2 inputs missing.

[CmdletBinding()]
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [switch]$ShowResolved
)

$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$trnSource = Join-Path $repoRoot "reverse_engineering\test_missions\render_worlds"
$csvRoot = Join-Path $GameRoot "BZ_ASSETS\common\materials"
$materialRoot = Join-Path $GameRoot "BZ_ASSETS\pc\materials"

# Moon's declared set. lcbench.mat is a Moon-authored grid, so this is the
# contract every world in the matrix has to meet -- not a stylistic choice.
$requiredTypes = @(0, 3, 4, 5, 6)

$worlds = @(
    @{ Name = "moon";  Trn = "lcbmoon.trn";  Prefix = "mn" }
    @{ Name = "mars";  Trn = "lcbmars.trn";  Prefix = "ma" }
    @{ Name = "venus"; Trn = "lcbvenus.trn"; Prefix = "ve" }
    @{ Name = "titan"; Trn = "lcbtitan.trn"; Prefix = "ti" }
)

foreach ($required in @($trnSource, $csvRoot)) {
    if (-not (Test-Path -LiteralPath $required)) {
        Write-Host "Required input not found: $required" -ForegroundColor Red
        exit 2
    }
}

# The CSV lists only the 0 rotation of each tile; the engine derives 1-3. So a
# lookup normalises the trailing rotation digit before asking.
function Get-AtlasKey([string]$mapName) {
    return [regex]::Replace($mapName.ToLowerInvariant(), '([a-z])[0-9](\.map)$', '${1}0${2}')
}

function Get-AtlasVocabulary([string]$prefix) {
    $csv = Join-Path $csvRoot "${prefix}_detail_atlas.csv"
    if (-not (Test-Path -LiteralPath $csv)) { return $null }
    $vocab = New-Object 'System.Collections.Generic.HashSet[string]'
    foreach ($line in [System.IO.File]::ReadAllLines($csv)) {
        $name = ($line -split ',')[0].Trim().ToLowerInvariant()
        if ($name) { [void]$vocab.Add($name) }
    }
    return $vocab
}

$findings = @()
$summary = @()

foreach ($world in $worlds) {
    $path = Join-Path $trnSource $world.Trn
    if (-not (Test-Path -LiteralPath $path)) {
        $findings += "$($world.Name): terrain not found: $path"
        continue
    }

    $bytes = [System.IO.File]::ReadAllBytes($path)

    # --- encoding and line endings -----------------------------------------
    $nonAscii = @($bytes | Where-Object { $_ -gt 127 }).Count
    if ($nonAscii -gt 0) {
        $findings += "$($world.Name): $nonAscii non-ASCII byte(s); the BZ ini reader is ANSI"
    }
    $text = [System.Text.Encoding]::ASCII.GetString($bytes)
    $bareLf = ([regex]::Matches($text, "(?<!`r)`n")).Count
    if ($bareLf -gt 0) {
        $findings += "$($world.Name): $bareLf bare LF line ending(s); mixed endings ship silently"
    }

    # --- size block ---------------------------------------------------------
    $sizeBlocks = ([regex]::Matches($text, '(?m)^\[Size\]\r?$')).Count
    if ($sizeBlocks -ne 1) {
        $findings += "$($world.Name): $sizeBlocks [Size] block(s); exactly one is authoritative"
    }
    foreach ($pair in @(@('Width', '5120'), @('Depth', '5120'))) {
        $m = [regex]::Match($text, ('(?m)^{0}=(\S+)\r?$' -f $pair[0]))
        if (-not $m.Success -or $m.Groups[1].Value -ne $pair[1]) {
            $findings += ("$($world.Name): [Size] {0}={1}, expected {2} to match the shared heightfield" -f
                $pair[0], $(if ($m.Success) { $m.Groups[1].Value } else { "<absent>" }), $pair[1])
        }
    }

    # --- texture types ------------------------------------------------------
    $declared = @([regex]::Matches($text, '(?m)^\[TextureType(\d+)\]') |
        ForEach-Object { [int]$_.Groups[1].Value } | Sort-Object -Unique)
    $missingTypes = @($requiredTypes | Where-Object { $declared -notcontains $_ })
    if ($missingTypes.Count -gt 0) {
        $findings += ("$($world.Name): [TextureType] {0} not declared; lcbench.mat names them" -f
            ($missingTypes -join ', '))
    }

    # --- atlas --------------------------------------------------------------
    $atlasName = ([regex]::Match($text, '(?m)^MaterialName[ \t]*=[ \t]*(\S+)')).Groups[1].Value
    if (-not $atlasName) {
        $findings += "$($world.Name): no [Atlases] MaterialName; the terrain has nothing to sample"
    } elseif ($atlasName -ne "$($world.Prefix)_detail_atlas") {
        $findings += "$($world.Name): [Atlases] names $atlasName, expected $($world.Prefix)_detail_atlas"
    }
    if ($atlasName -and (Test-Path -LiteralPath $materialRoot)) {
        $material = Join-Path $materialRoot "$atlasName.material"
        if (-not (Test-Path -LiteralPath $material)) {
            $findings += "$($world.Name): atlas material not installed: $material"
        }
    }

    # --- every terrain tile resolves ---------------------------------------
    # Scoped to [TextureType] sections on purpose: sky, star and cloud entries
    # in the same file are ordinary textures and are not atlas keys.
    $vocab = Get-AtlasVocabulary $world.Prefix
    if ($null -eq $vocab) {
        $findings += "$($world.Name): atlas vocabulary not found: ${csvRoot}\$($world.Prefix)_detail_atlas.csv"
        continue
    }

    $inTextureType = $false
    $tiles = @()
    foreach ($line in ($text -split "`r`n")) {
        if ($line -match '^\[TextureType\d+\]') { $inTextureType = $true; continue }
        if ($line -match '^\[') { $inTextureType = $false; continue }
        if (-not $inTextureType) { continue }
        $m = [regex]::Match($line, '=\s*(\S+\.map)\s*$', 'IgnoreCase')
        if ($m.Success) { $tiles += $m.Groups[1].Value }
    }

    $unresolved = @()
    foreach ($tile in ($tiles | Sort-Object -Unique)) {
        if (-not $vocab.Contains((Get-AtlasKey $tile))) {
            $unresolved += "$tile (key $(Get-AtlasKey $tile))"
        }
    }
    foreach ($u in $unresolved) {
        $findings += "$($world.Name): $u is not in the $($world.Prefix) atlas; it would fall back to the default tile"
    }

    $sunTime = ([regex]::Match($text, '(?m)^Time=(\d+)')).Groups[1].Value

    $summary += [pscustomobject]@{
        World      = $world.Name
        Types      = ($declared -join ',')
        Tiles      = @($tiles | Sort-Object -Unique).Count
        Unresolved = $unresolved.Count
        Atlas      = $atlasName
        SunTime    = $sunTime
    }

    if ($ShowResolved) {
        Write-Host "$($world.Name) tiles: $((@($tiles | Sort-Object -Unique)) -join ', ')"
    }
}

$summary | Format-Table -AutoSize | Out-String | Write-Host

if ($findings.Count -gt 0) {
    foreach ($f in $findings) { Write-Host "FINDING: $f" -ForegroundColor Red }
    Write-Host ""
    Write-Host "$($findings.Count) finding(s)" -ForegroundColor Red
    exit 1
}

Write-Host "all worlds resolve against the installed atlases" -ForegroundColor Green
exit 0
