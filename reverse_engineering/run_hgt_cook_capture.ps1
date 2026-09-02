<#
.SYNOPSIS
    Capture Redux's own HGT->HG2 cook and compare it against our offline converter.

.DESCRIPTION
    Redux caches its legacy-HGT cook by writing the result next to the addon as
    <mission>.hg2 (FUN_00786340). That makes the game itself a bytewise oracle
    for the conversion: delete the cached HG2, launch the mission, and whatever
    the game writes is ground truth.

    Runs both arms:
      smoothed    default cook  -> should match `--smoothed` output
      unsmoothed  -nohgtsmoothing -> should match the default converter output

    The stock addon terrain is never modified. The cached .hg2 is backed up
    outside `addon` and restored in a finally block.

.NOTES
    Requires a connected interactive session; the game cannot create a D3D
    device from a disconnected/locked session and will exit without cooking.
#>
[CmdletBinding()]
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string]$Mission = "ccafun01",
    [string]$MissionBzn = "ccafun01.bzn",
    # Where the legacy .hgt actually lives, relative to the game root.
    [string]$AddonSubdir = "addon\CCA Fun",
    [ValidateSet("smoothed", "unsmoothed", "both")]
    [string]$Arm = "both",
    [int]$LoadTimeoutSeconds = 180,
    [string]$OutDir
)

$ErrorActionPreference = "Stop"
. (Join-Path $PSScriptRoot "BZRHarness.ps1")

$exe = Join-Path $GameRoot "battlezone98redux.exe"
if (-not (Test-Path $exe)) { throw "Game executable not found: $exe" }

$hgt = Join-Path $GameRoot "$AddonSubdir\$Mission.hgt"
if (-not (Test-Path $hgt)) { throw "Legacy heightmap not found: $hgt" }

# Redux writes the cooked file into the addon root, not beside the .hgt.
$cooked = Join-Path $GameRoot "addon\$Mission.hg2"

if (-not $OutDir) {
    $stamp = Get-Date -Format "yyyyMMdd_HHmmss"
    $OutDir = Join-Path $GameRoot "openshim_test_backups\hgtcook_$stamp"
}
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null
Write-Host "[hgtcook] evidence -> $OutDir"

$backup = $null
if (Test-Path $cooked) {
    $backup = Join-Path $OutDir "$Mission.hg2.pre"
    Copy-Item $cooked $backup -Force
    Write-Host "[hgtcook] backed up existing cache -> $backup"
}

function Invoke-CookArm {
    param([string]$Name, [string[]]$ExtraArgs)

    Write-Host "[hgtcook] arm '$Name': args = $($ExtraArgs -join ' ')"
    if (Test-Path $cooked) { Remove-Item $cooked -Force }

    $argList = @($MissionBzn) + $ExtraArgs
    $proc = Start-Process -FilePath $exe -ArgumentList $argList `
        -WorkingDirectory $GameRoot -PassThru

    try {
        $deadline = (Get-Date).AddSeconds($LoadTimeoutSeconds)
        $seen = $false
        while ((Get-Date) -lt $deadline) {
            if (Test-Path $cooked) {
                # Wait for the write to settle before reading it.
                $a = (Get-Item $cooked).Length
                Start-Sleep -Milliseconds 1200
                $b = (Get-Item $cooked).Length
                if ($a -eq $b -and $b -gt 12) { $seen = $true; break }
            }
            if ($proc.HasExited) {
                Write-Warning "[hgtcook] arm '$Name': game exited (code $($proc.ExitCode)) before writing the cache."
                break
            }
            Start-Sleep -Milliseconds 750
        }
    } finally {
        Stop-BZRGame -Id $proc.Id
    }

    if (-not $seen) {
        Write-Warning "[hgtcook] arm '$Name': no cooked HG2 appeared at $cooked"
        return $null
    }
    $dest = Join-Path $OutDir "$Mission.$Name.hg2"
    Copy-Item $cooked $dest -Force
    $h = (Get-FileHash $dest -Algorithm SHA256).Hash
    Write-Host "[hgtcook] arm '$Name': captured $((Get-Item $dest).Length) bytes  SHA256=$h"
    return $dest
}

$results = @{}
try {
    if ($Arm -in @("smoothed", "both")) {
        $results["smoothed"] = Invoke-CookArm -Name "smoothed" -ExtraArgs @()
    }
    if ($Arm -in @("unsmoothed", "both")) {
        $results["unsmoothed"] = Invoke-CookArm -Name "unsmoothed" -ExtraArgs @("-nohgtsmoothing")
    }
} finally {
    if (Test-Path $cooked) { Remove-Item $cooked -Force -ErrorAction SilentlyContinue }
    if ($backup) {
        Copy-Item $backup $cooked -Force
        Write-Host "[hgtcook] restored the original cached HG2"
    }
}

Write-Host ""
Write-Host "[hgtcook] captured arms:"
foreach ($k in $results.Keys) {
    Write-Host ("  {0,-11} {1}" -f $k, ($results[$k] ?? "<not captured>"))
}
Write-Host ""
Write-Host "Compare against the offline converter with:"
Write-Host "  python scripts/convert_legacy_hgt.py convert `"$hgt`" -o ours.hg2"
Write-Host "  python scripts/convert_legacy_hgt.py compare ours.hg2 `"$($results['unsmoothed'])`""
