<#
.SYNOPSIS
    Sets up and reads back a [SUNFLASH] trace run.

.DESCRIPTION
    The sun whiteout is one fullscreen quad fed by

        flash = visiblePixels * dot(cameraForward, sunDirection)^32 * scale

    computed in LensFlare::Render and handed to the global ScreenFlash. See
    include/sun_flash.h for the full trace. This script drives the two-arm
    validation of the opt-out:

      -Arm Stock       [Display] SunFlashbang = 1, trace on  (whiteout renders)
      -Arm Suppressed  [Display] SunFlashbang = 0, trace on  (whiteout gone)
      -Arm Off         trace off, SunFlashbang left alone

    Run it once with -Arm Stock, fly the sweep, quit, then -Summarize. Repeat
    with -Arm Suppressed. The two summaries should report the same flash values
    and the same saturation angle, and differ only in which arm ran and in what
    you see on screen.

.PARAMETER Arm
    Which arm to configure for the next launch.

.PARAMETER Summarize
    Read the [SUNFLASH] lines already in the log instead of configuring a run.

.PARAMETER GameDir
    Battlezone 98 Redux install directory. Defaults to the GOG test install.

.EXAMPLE
    .\Invoke-SunFlashTrace.ps1 -Arm Stock
    # launch the game, fly the sweep, quit
    .\Invoke-SunFlashTrace.ps1 -Summarize
#>
[CmdletBinding(DefaultParameterSetName = 'Configure')]
param(
    [Parameter(ParameterSetName = 'Configure')]
    [ValidateSet('Stock', 'Suppressed', 'Off')]
    [string]$Arm = 'Stock',

    [Parameter(ParameterSetName = 'Summarize', Mandatory = $true)]
    [switch]$Summarize,

    [string]$GameDir = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux"
)

$ErrorActionPreference = 'Stop'

$iniPath = Join-Path $GameDir 'openshim.ini'
$logPath = Join-Path $GameDir 'logs\openshim.log'

function Set-IniValue {
    param([string]$Path, [string]$Section, [string]$Key, [string]$Value)

    $lines = [System.Collections.Generic.List[string]](Get-Content -LiteralPath $Path)

    $sectionIndex = -1
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($lines[$i].Trim() -eq "[$Section]") { $sectionIndex = $i; break }
    }
    if ($sectionIndex -lt 0) {
        $lines.Add('')
        $lines.Add("[$Section]")
        $sectionIndex = $lines.Count - 1
    }

    # Search only within this section.
    for ($i = $sectionIndex + 1; $i -lt $lines.Count; $i++) {
        if ($lines[$i].Trim() -match '^\[') { break }
        if ($lines[$i] -match "^\s*$([regex]::Escape($Key))\s*=") {
            $lines[$i] = "$Key = $Value"
            Set-Content -LiteralPath $Path -Value $lines
            return
        }
    }

    $lines.Insert($sectionIndex + 1, "$Key = $Value")
    Set-Content -LiteralPath $Path -Value $lines
}

if ($Summarize) {
    if (-not (Test-Path -LiteralPath $logPath)) {
        Write-Error "No log at $logPath"
        return
    }

    $records = @()
    foreach ($line in Get-Content -LiteralPath $logPath) {
        if ($line -notmatch '\[SUNFLASH\]') { continue }
        if ($line -match 'dot=(?<dot>-?[\d.]+)\s+angle=(?<angle>[\d.]+)deg\s+dot\^32=(?<t32>[\d.eE+-]+)\s+px=(?<px>\d+)\s+scale=(?<scale>[\d.eE+-]+)\s+flash=(?<flash>[\d.eE+-]+)\s+alpha=(?<alpha>\d+)/255(?<sat>\s+SATURATED)?\s+(?<arm>STOCK|SUPPRESSED)') {
            $records += [pscustomobject]@{
                Angle     = [double]$Matches['angle']
                DotPow32  = [double]$Matches['t32']
                Pixels    = [int]$Matches['px']
                Scale     = [double]$Matches['scale']
                Flash     = [double]$Matches['flash']
                Alpha     = [int]$Matches['alpha']
                Saturated = [bool]$Matches['sat']
                Arm       = $Matches['arm']
            }
        }
    }

    $install = Get-Content -LiteralPath $logPath | Select-String -Pattern '\[SUNFLASH\] installed=' | Select-Object -Last 1
    if ($install) { Write-Host $install.Line.Trim() }

    if ($records.Count -eq 0) {
        Write-Warning 'No verified [SUNFLASH] records. Either the trace was off, the sun was never in front of the camera with visible occlusion pixels, or the frame read did not verify (check for "frame unverified" lines).'
        return
    }

    $arms = $records | Group-Object Arm | ForEach-Object { "$($_.Name)=$($_.Count)" }
    $saturated = @($records | Where-Object Saturated)
    $peak = $records | Sort-Object Flash -Descending | Select-Object -First 1

    Write-Host ""
    Write-Host "records        : $($records.Count)  ($($arms -join ', '))"
    Write-Host "angle range    : $('{0:N2}' -f ($records | Measure-Object Angle -Minimum).Minimum) .. $('{0:N2}' -f ($records | Measure-Object Angle -Maximum).Maximum) deg"
    Write-Host "peak flash     : $('{0:N4}' -f $peak.Flash) at $('{0:N2}' -f $peak.Angle) deg (px=$($peak.Pixels), alpha=$($peak.Alpha)/255)"
    Write-Host "saturated      : $($saturated.Count) of $($records.Count) frames clamp at the 224/255 ceiling"
    if ($saturated.Count -gt 0) {
        $widest = ($saturated | Measure-Object Angle -Maximum).Maximum
        Write-Host "saturates out to: $('{0:N2}' -f $widest) deg off axis"
    }
    Write-Host "pixel range    : $(($records | Measure-Object Pixels -Minimum).Minimum) .. $(($records | Measure-Object Pixels -Maximum).Maximum)"
    Write-Host ""
    Write-Host "flash vs angle (nearest-first):"
    $records | Sort-Object Angle | Select-Object -First 40 |
        Format-Table @{ n = 'deg'; e = { '{0:N2}' -f $_.Angle } },
                     @{ n = 'dot^32'; e = { '{0:N5}' -f $_.DotPow32 } },
                     Pixels,
                     @{ n = 'flash'; e = { '{0:N4}' -f $_.Flash } },
                     @{ n = 'alpha'; e = { "$($_.Alpha)/255" } },
                     Saturated, Arm -AutoSize
    return
}

switch ($Arm) {
    'Stock' {
        Set-IniValue -Path $iniPath -Section 'Display' -Key 'SunFlashbang' -Value '1'
        Set-IniValue -Path $iniPath -Section 'Diagnostics' -Key 'TraceSunFlash' -Value '1'
    }
    'Suppressed' {
        Set-IniValue -Path $iniPath -Section 'Display' -Key 'SunFlashbang' -Value '0'
        Set-IniValue -Path $iniPath -Section 'Diagnostics' -Key 'TraceSunFlash' -Value '1'
    }
    'Off' {
        Set-IniValue -Path $iniPath -Section 'Diagnostics' -Key 'TraceSunFlash' -Value '0'
    }
}

Write-Host "openshim.ini configured for arm '$Arm':"
Select-String -LiteralPath $iniPath -Pattern 'SunFlashbang|TraceSunFlash' |
    ForEach-Object { "  $($_.Line.Trim())" }
Write-Host ""
Write-Host "Launch the game, then in a mission:"
Write-Host "  1. find the sun and look straight at it"
Write-Host "  2. sweep slowly across it, left to right, past it on both sides"
Write-Host "  3. put a hill or building between you and it, then step out again"
Write-Host "  4. quit to desktop so the log flushes"
Write-Host ""
Write-Host "Then: .\Invoke-SunFlashTrace.ps1 -Summarize"
