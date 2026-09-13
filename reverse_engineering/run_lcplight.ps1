<#
.SYNOPSIS
A/B repro for the pilot-flashlight scene-light flip.

.DESCRIPTION
Runs the lcbench pilot-flashlight fixture twice with everything held constant
except [SinglePlayer] PilotFlashlight, captures the same frames in both arms,
and prints the mean terrain luma per frame so the two arms can be compared
numerically.

Background: a 2026-09-13 play01.bzn capture showed the whole 3D scene stepping
between two light levels, co-timed to the frame with boarding and leaving a
craft (70.0 vs 39.3 of 255 on a fixed terrain patch, ~2.4x). Shading contrast,
hue and pure black were preserved and the sky dome was bit-identical, so it is
a scene light level and not a post-process. The only thing whose lifetime
matches every transition is the shim's own pilot flashlight.

Read the result like this:
  on-foot luma(arm=on) >> on-foot luma(arm=off)  -> the flashlight floods the
      scene and owns the bug.
  on-foot luma(arm=on) ~= on-foot luma(arm=off)  -> the flashlight is innocent;
      look at the craft headlight and at scheme/technique selection instead.

Both arms report what they actually did ([PILOTLIGHT] created / Stood down).
An arm that never engaged is reported as NOT ENGAGED rather than being averaged
into the comparison, because a dead arm otherwise reads exactly like a null
result.

Windowed is mandatory: an exclusive-fullscreen DXGI swapchain hands back black
to a screen grab, so a fullscreen run cannot produce visual evidence.

.EXAMPLE
pwsh -File reverse_engineering/run_lcplight.ps1
pwsh -File reverse_engineering/run_lcplight.ps1 -Arms on -RunSeconds 40
#>
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    # flashlight: does the shim's pilot flashlight change the scene? (arms on/off)
    # headlight:  does the craft headlight's solved attenuation range change it?
    #             (arms repair/stock/nolight, pilot flashlight off throughout)
    [ValidateSet("flashlight", "headlight")]
    [string]$Scenario = "headlight",
    [string[]]$Arms = @(),
    [ValidateRange(30, 300)]
    [int]$RunSeconds = 52,
    [string]$Color = "White",
    [string]$Beam = "Focused",
    [string]$OutputRoot = "",
    # Deploy bin\Release\winmm.dll over the installed shim. Off by default:
    # the reported capture was produced by whatever is already installed, and
    # swapping the binary changes the thing under test.
    [switch]$DeployDll
)

$ErrorActionPreference = "Stop"
$repoRoot = Split-Path -Parent $PSScriptRoot

# Capture a BURST, not three scheduled stills.
#
# Two things make a still-vs-still comparison across arms worthless here:
#   * the engine spends roughly 13 s on the loading screen before Start() runs,
#     so an early sample photographs the loading screen in every arm (observed:
#     identical 1257577-byte PNGs with identical luma, which is not a null
#     result, it is not a measurement);
#   * the pilot's spawn facing after HopOut is not reproducible run to run, so
#     the "same" rectangle lands on different geometry in different arms. A
#     first pass read 25.8 vs 35.1 off a hillside rectangle and that difference
#     was camera pose, not light.
#
# What IS trustworthy is a step WITHIN one run between two frames whose geometry
# is otherwise unchanged -- exactly the evidence the original capture gives at
# frames 707/708, where the light drops 2.4x one frame after the boarding camera
# move has already settled. So sample densely across the transition and let the
# analysis find a luma step that is not accompanied by a geometry change.
$BurstHz = 4.0
$BurstWindows = @(
    # FIRST STYLING. The capture's dark transition lands 0.16 s after boarding,
    # which is one `RefreshHeadlightState` tick (kHeadlightRefreshMs = 200): the
    # scene steps when the shim applies its state to a headlight for the first
    # time, not when the craft is entered. A fixture that starts the player
    # already in a craft only ever reaches that moment at mission start, so this
    # window has to straddle it. Start() runs about 13 s after launch.
    @{ Name = "styling"; From = 11.0; To = 21.0 },
    # The fixture hops out at mission T+8, i.e. about t+21 after launch.
    @{ Name = "hopout";  From = 21.0; To = 29.0 },
    # ...and would board again at mission T+26, about t+39, if anything on this
    # map could drive boarding. Nothing can: `input.map` has no enter-vehicle
    # action (an on-foot pilot boards by walking into the craft) and
    # `exu.SetAsUser` is unreachable from an addon mission chunk. Kept so the
    # window is sampled if that ever changes.
    @{ Name = "board";   From = 35.0; To = 43.0 }
)

# Per-arm ini overrides. Every arm writes every key the scenario varies, so an
# arm never inherits the previous arm's value by omission.
$ArmMatrix = @{
    flashlight = [ordered]@{
        on  = @{ PilotFlashlight = "1"; HeadlightFalloffRepair = "1"; Headlights = "1" }
        off = @{ PilotFlashlight = "0"; HeadlightFalloffRepair = "1"; Headlights = "1" }
    }
    headlight = [ordered]@{
        # Shipping behaviour: SolveInvisibleRange inflates the stock 600 m
        # attenuation range so the cone terminator falls below the 8-bit floor.
        repair  = @{ PilotFlashlight = "0"; HeadlightFalloffRepair = "1"; Headlights = "1" }
        # Same light, stock 600 m range. If the scene brightens here, the
        # inflated range is what is evicting lights map-wide.
        stock   = @{ PilotFlashlight = "0"; HeadlightFalloffRepair = "0"; Headlights = "1" }
        # No shim headlight policy at all: the floor of the comparison.
        nolight = @{ PilotFlashlight = "0"; HeadlightFalloffRepair = "0"; Headlights = "0" }
    }
}
if (-not $Arms -or $Arms.Count -eq 0) {
    $Arms = @($ArmMatrix[$Scenario].Keys)
}
foreach ($a in $Arms) {
    if (-not $ArmMatrix[$Scenario].Contains($a)) {
        throw "scenario '$Scenario' has no arm '$a'; valid: $($ArmMatrix[$Scenario].Keys -join ', ')"
    }
}

$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
if (-not $OutputRoot) {
    $OutputRoot = Join-Path $env:TEMP "bzr-lcplight-$stamp"
}
New-Item -ItemType Directory -Force -Path $OutputRoot | Out-Null

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$installedIni = Join-Path $GameRoot "openshim.ini"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$worldSource = Join-Path $repoRoot "reverse_engineering\test_missions\live_combat_scaling"
$fixture = Join-Path $repoRoot "reverse_engineering\test_missions\lcbench_pilotlight\rmplight.lua"
$builtDll = Join-Path $repoRoot "bin\Release\winmm.dll"

foreach ($p in @($gameExe, $installedIni, $worldSource, $fixture)) {
    if (-not (Test-Path -LiteralPath $p)) { throw "missing: $p" }
}
Get-Process battlezone98redux -ErrorAction SilentlyContinue | ForEach-Object {
    throw "the game is already running (PID $($_.Id)); close it first"
}

Add-Type -AssemblyName System.Drawing

Add-Type @"
using System;
using System.Runtime.InteropServices;
public static class LcpWin {
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
    // PW_RENDERFULLCONTENT (2) asks the window to redraw into a DC, which works
    // for a windowed DXGI swapchain without owning the foreground. A plain
    // CopyFromScreen behind another window captures the desktop, which reads
    // exactly like "the feature does nothing".
    [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr dc, uint flags);
}
"@

# Sets a key inside an existing section, or appends it to that section.
function Set-IniKey {
    param([string[]]$Lines, [string]$Section, [string]$Key, [string]$Value)
    $out = New-Object System.Collections.Generic.List[string]
    $inSection = $false
    $written = $false
    $lastSectionLine = -1
    for ($i = 0; $i -lt $Lines.Count; $i++) {
        $line = $Lines[$i]
        if ($line -match '^\s*\[(.+?)\]\s*$') {
            if ($inSection -and -not $written) {
                $out.Insert($lastSectionLine + 1, "$Key = $Value")
                $written = $true
            }
            $inSection = ($Matches[1] -eq $Section)
            $out.Add($line) | Out-Null
            if ($inSection) { $lastSectionLine = $out.Count - 1 }
            continue
        }
        if ($inSection -and -not $written -and $line -match "^\s*$([regex]::Escape($Key))\s*=") {
            $out.Add("$Key = $Value") | Out-Null
            $written = $true
            continue
        }
        $out.Add($line) | Out-Null
    }
    if (-not $written -and $lastSectionLine -ge 0) {
        $out.Insert($lastSectionLine + 1, "$Key = $Value")
    }
    return $out.ToArray()
}

# Two rectangles, because a light that only changes its own pool is a very
# different finding from one that changes the whole map. "offbeam" is the upper
# right hillside, which no player light points at and which no HUD panel covers;
# "beam" is the lower centre right, where a pilot torch or headlight pool lands.
# Measuring only the second is how a local pool gets mistaken for a scene-wide
# step. Subsampled: this is a ratio test, not photometry.
$LumaRegions = [ordered]@{
    offbeam = @{ X0 = 0.62; X1 = 0.95; Y0 = 0.10; Y1 = 0.42 }
    beam    = @{ X0 = 0.62; X1 = 0.82; Y0 = 0.62; Y1 = 0.85 }
}

function Measure-TerrainLuma {
    param([string]$Path)
    $bmp = New-Object System.Drawing.Bitmap $Path
    try {
        $out = [ordered]@{}
        foreach ($name in $LumaRegions.Keys) {
            $r = $LumaRegions[$name]
            $x0 = [int]($bmp.Width * $r.X0)
            $x1 = [int]($bmp.Width * $r.X1)
            $y0 = [int]($bmp.Height * $r.Y0)
            $y1 = [int]($bmp.Height * $r.Y1)
            $sum = 0.0
            $n = 0
            for ($y = $y0; $y -lt $y1; $y += 3) {
                for ($x = $x0; $x -lt $x1; $x += 3) {
                    $c = $bmp.GetPixel($x, $y)
                    $sum += (0.299 * $c.R + 0.587 * $c.G + 0.114 * $c.B)
                    $n++
                }
            }
            $out[$name] = if ($n -eq 0) { 0.0 } else { [math]::Round($sum / $n, 2) }
        }
        return $out
    }
    finally { $bmp.Dispose() }
}

# KNOWN LIMITATION -- read this before trusting a burst.
#
# PrintWindow against this game's windowed DXGI swapchain returns the LAST
# PRESENTED surface, and while the window is not in the foreground that surface
# stops changing. A burst captured behind another window therefore comes back as
# a run of bit-identical PNGs: a 2026-09-13 run produced styling_002..024 all at
# exactly 60.94 and every board frame at exactly 35.31, geometry difference
# 0.000. The simulation was live throughout (BZLogger kept growing), so this is
# a capture artefact, not a still scene.
#
# Bit-identical consecutive frames are the tell. They are not evidence that the
# scene held steady, and a single-frame light step inside such a run is simply
# not sampled. Until this is solved -- by fronting the window per shot, which
# costs about 900 ms and caps the rate near 1 Hz, or by instrumenting the shim
# instead of photographing it -- treat a burst with repeated identical frames as
# NO MEASUREMENT rather than as a null result.
function Save-WindowFrame {
    param([System.Diagnostics.Process]$Proc, [string]$Path)
    $hwnd = $Proc.MainWindowHandle
    if ($hwnd -eq [IntPtr]::Zero) { return $false }
    $rect = New-Object LcpWin+RECT
    if (-not [LcpWin]::GetWindowRect($hwnd, [ref]$rect)) { return $false }
    $w = $rect.R - $rect.L
    $h = $rect.B - $rect.T
    if ($w -le 0 -or $h -le 0) { return $false }
    $bmp = New-Object System.Drawing.Bitmap $w, $h
    $gfx = [System.Drawing.Graphics]::FromImage($bmp)
    $ok = $false
    try {
        $hdc = $gfx.GetHdc()
        try { $ok = [LcpWin]::PrintWindow($hwnd, $hdc, 2) } finally { $gfx.ReleaseHdc($hdc) }
        if ($ok) { $bmp.Save($Path, [System.Drawing.Imaging.ImageFormat]::Png) }
    }
    finally { $gfx.Dispose(); $bmp.Dispose() }
    return $ok
}

# --- world deployment -------------------------------------------------------
# The runner owns addon\lcbench only when it had to create it. If a baseline is
# already installed, its files are backed up and restored instead.
$createdMissionRoot = $false
$missionBackup = Join-Path $OutputRoot "pre_live"
$deployedNames = @()

$env:BZR_FORCE_WINDOWED = "1"
. (Join-Path $repoRoot "reverse_engineering\BZRHarness.ps1")

$iniBackup = Join-Path $OutputRoot "openshim.ini.orig"
Copy-Item -LiteralPath $installedIni -Destination $iniBackup -Force
$iniHash = (Get-FileHash -LiteralPath $installedIni -Algorithm SHA256).Hash

$results = @()

try {
    if (-not (Test-Path -LiteralPath $missionRoot)) {
        New-Item -ItemType Directory -Force -Path $missionRoot | Out-Null
        $createdMissionRoot = $true
        Write-Host "[lcplight] created $missionRoot"
    }
    New-Item -ItemType Directory -Force -Path $missionBackup | Out-Null
    foreach ($src in (Get-ChildItem -LiteralPath $worldSource -File)) {
        $live = Join-Path $missionRoot $src.Name
        if (Test-Path -LiteralPath $live) {
            Copy-Item -LiteralPath $live -Destination (Join-Path $missionBackup $src.Name) -Force
        }
        Copy-Item -LiteralPath $src.FullName -Destination $live -Force
        $deployedNames += $src.Name
    }
    $liveLua = Join-Path $missionRoot "lcbench.lua"
    Copy-Item -LiteralPath $fixture -Destination $liveLua -Force
    Write-Host "[lcplight] deployed lcbench world + rmplight.lua fixture"

    if ($DeployDll) {
        if (-not (Test-Path -LiteralPath $builtDll)) { throw "build first: $builtDll" }
        Copy-Item -LiteralPath $builtDll -Destination (Join-Path $GameRoot "winmm.dll") -Force
        Write-Host "[lcplight] deployed winmm.dll $((Get-FileHash -LiteralPath $builtDll -Algorithm SHA256).Hash)"
    }
    $shimHash = (Get-FileHash -LiteralPath (Join-Path $GameRoot "winmm.dll") -Algorithm SHA256).Hash
    Write-Host "[lcplight] shim under test: $shimHash"

    foreach ($arm in $Arms) {
        $armDir = Join-Path $OutputRoot "arm_$arm"
        New-Item -ItemType Directory -Force -Path $armDir | Out-Null

        $overrides = $ArmMatrix[$Scenario][$arm]
        $lines = Get-Content -LiteralPath $iniBackup
        foreach ($key in $overrides.Keys) {
            $lines = Set-IniKey $lines "SinglePlayer" $key $overrides[$key]
        }
        $lines = Set-IniKey $lines "SinglePlayer" "PilotFlashlightColor" $Color
        $lines = Set-IniKey $lines "SinglePlayer" "PilotFlashlightBeam" $Beam
        $lines = Set-IniKey $lines "Diagnostics" "PilotFlashlightTrace" "1"
        $lines = Set-IniKey $lines "Diagnostics" "HeadlightLightTrace" "1"
        Set-Content -LiteralPath $installedIni -Value $lines -Encoding ASCII
        $desc = ($overrides.Keys | ForEach-Object { "$_=$($overrides[$_])" }) -join " "
        Write-Host "[lcplight] --- $Scenario arm '$arm': $desc ---"

        $proc = Start-Process -FilePath $gameExe -ArgumentList "lcbench.bzn" `
            -WorkingDirectory $GameRoot -PassThru
        $launchedAt = Get-Date
        Write-Host "[lcplight] launched PID=$($proc.Id)"

        $samples = @()
        $pending = @()
        try {
            foreach ($window in $BurstWindows) {
                $frameIndex = 0
                $due = $launchedAt.AddSeconds($window.From)
                while ((Get-Date) -lt $due) {
                    Start-Sleep -Milliseconds 200
                    $proc.Refresh()
                    if ($proc.HasExited) { break }
                }
                $stop = $launchedAt.AddSeconds($window.To)
                while ((Get-Date) -lt $stop) {
                    $proc.Refresh()
                    if ($proc.HasExited) { break }
                    $at = [math]::Round(((Get-Date) - $launchedAt).TotalSeconds, 2)
                    $shot = Join-Path $armDir ("{0}_{1:D3}.png" -f $window.Name, $frameIndex)
                    # Capture only. Measuring here costs thousands of GetPixel
                    # P/Invokes per frame and drops the real sample rate to
                    # about 1 Hz, which is how a single-frame step gets stepped
                    # over. Luma is computed after the arm ends.
                    if (Save-WindowFrame -Proc $proc -Path $shot) {
                        $pending += [pscustomobject]@{
                            Arm = $arm; Window = $window.Name; Index = $frameIndex; At = $at
                            Path = $shot
                        }
                        $frameIndex++
                    }
                    Start-Sleep -Milliseconds ([int](1000.0 / $BurstHz))
                }
                Write-Host ("[lcplight]   burst '{0}': {1} frames" -f $window.Name, $frameIndex)
            }
            $tail = $launchedAt.AddSeconds($RunSeconds)
            while ((Get-Date) -lt $tail) {
                Start-Sleep -Milliseconds 500
                $proc.Refresh()
                if ($proc.HasExited) { break }
            }
        }
        finally {
            try { Stop-BZRGame -Id $proc.Id } catch { Write-Warning "Stop-BZRGame: $_" }
        }

        # Measure now that nothing is racing the capture rate.
        foreach ($frame in $pending) {
            $luma = Measure-TerrainLuma -Path $frame.Path
            $samples += [pscustomobject]@{
                Arm = $frame.Arm; Window = $frame.Window; Index = $frame.Index; At = $frame.At
                OffBeam = $luma.offbeam; Beam = $luma.beam; Path = $frame.Path
            }
        }
        $rates = $pending | Group-Object Window | ForEach-Object {
            $w = $_.Group | Sort-Object Index
            if ($w.Count -ge 2) {
                $span = [double]$w[-1].At - [double]$w[0].At
                if ($span -gt 0) {
                    "{0}={1:F1}Hz" -f $_.Name, (($w.Count - 1) / $span)
                } else { "{0}=n/a" -f $_.Name }
            } else { "{0}=n/a" -f $_.Name }
        }
        Write-Host ("[lcplight]   effective capture rate: {0}" -f ($rates -join " "))

        foreach ($log in @("openshim.log", "BZLogger.txt", "BZOgreLogfile.log")) {
            $src = Join-Path $GameRoot "logs\$log"
            if (Test-Path -LiteralPath $src) {
                Copy-Item -LiteralPath $src -Destination (Join-Path $armDir $log) -Force
            }
        }

        # An arm that never engaged is not a null result -- it is not a result.
        # Prove engagement from the arm's own log, from the value the arm was
        # supposed to change, before the numbers are allowed to mean anything.
        $armLog = Join-Path $armDir "openshim.log"
        $created = 0
        $ranges = @()
        $lightLines = @()
        if (Test-Path -LiteralPath $armLog) {
            $lightLines = @(Select-String -LiteralPath $armLog -Pattern "PILOTLIGHT|HEADLIGHT" |
                ForEach-Object { $_.Line })
            $created = @($lightLines | Where-Object { $_ -match "\[PILOTLIGHT\] created" }).Count
            foreach ($line in $lightLines) {
                if ($line -match "range=([0-9]+(?:\.[0-9]+)?)") { $ranges += [double]$Matches[1] }
            }
        }
        $observedRange = if ($ranges.Count) { ($ranges | Select-Object -Last 1) } else { $null }
        switch ($Scenario) {
            "flashlight" {
                $engaged = if ($arm -eq "on") { $created -gt 0 } else { $created -eq 0 }
            }
            "headlight" {
                # The whole point of the repair arm is a range above stock 600.
                $engaged = switch ($arm) {
                    "repair"  { $observedRange -ne $null -and $observedRange -gt 601 }
                    "stock"   { $observedRange -ne $null -and $observedRange -le 601 }
                    # No headlight policy means no probe line to check, so the
                    # only thing that can be verified is that frames were taken
                    # at all. A zero-frame arm is not a null result.
                    "nolight" { $samples.Count -gt 0 }
                    default   { $samples.Count -gt 0 }
                }
            }
        }
        Write-Host ("[lcplight] arm '{0}': pilotLightsCreated={1} headlightRange={2} engaged={3}" -f `
            $arm, $created, $(if ($observedRange -ne $null) { $observedRange } else { "n/a" }), $engaged)
        if (-not $engaged) {
            Write-Warning "[lcplight] arm '$arm' NOT ENGAGED -- its numbers prove nothing"
        }
        $lightLines | Where-Object { $_ -notmatch "HEADLIGHT-PROBE" } |
            Select-Object -Last 12 | ForEach-Object { Write-Host "    $_" }
        $lightLines | Where-Object { $_ -match "HEADLIGHT-PROBE" } |
            Select-Object -Last 1 | ForEach-Object { Write-Host "    $_" }

        $results += [pscustomobject]@{
            Arm = $arm; Engaged = $engaged; Created = $created; Range = $observedRange
            Samples = $samples
        }
    }
}
finally {
    Copy-Item -LiteralPath $iniBackup -Destination $installedIni -Force
    $iniNow = (Get-FileHash -LiteralPath $installedIni -Algorithm SHA256).Hash
    if ($iniNow -ne $iniHash) { throw "openshim.ini restore mismatch" }
    Write-Host "[lcplight] openshim.ini restored"

    foreach ($name in $deployedNames) {
        $live = Join-Path $missionRoot $name
        $saved = Join-Path $missionBackup $name
        if (Test-Path -LiteralPath $saved) {
            Copy-Item -LiteralPath $saved -Destination $live -Force
        } elseif (Test-Path -LiteralPath $live) {
            Remove-Item -LiteralPath $live -Force
        }
    }
    $liveLua = Join-Path $missionRoot "lcbench.lua"
    $savedLua = Join-Path $missionBackup "lcbench.lua"
    if (Test-Path -LiteralPath $savedLua) {
        Copy-Item -LiteralPath $savedLua -Destination $liveLua -Force
    } elseif (Test-Path -LiteralPath $liveLua) {
        Remove-Item -LiteralPath $liveLua -Force
    }
    if ($createdMissionRoot -and (Test-Path -LiteralPath $missionRoot)) {
        if (-not (Get-ChildItem -LiteralPath $missionRoot -Force)) {
            Remove-Item -LiteralPath $missionRoot -Force
        }
    }
    Write-Host "[lcplight] addon\lcbench restored"

    $ogreBackup = Join-Path $GameRoot "ogre.cfg.bzrharness-backup"
    if (Test-Path -LiteralPath $ogreBackup) {
        Copy-Item -LiteralPath $ogreBackup -Destination (Join-Path $GameRoot "ogre.cfg") -Force
        Remove-Item -LiteralPath $ogreBackup -Force
        Write-Host "[lcplight] ogre.cfg restored"
    }
}

$csv = Join-Path $OutputRoot "luma.csv"
$results | ForEach-Object { $_.Samples } | Select-Object Arm, Window, Index, At, OffBeam, Beam, Path |
    Export-Csv -LiteralPath $csv -NoTypeInformation
Write-Host ""
Write-Host "[lcplight] per-frame luma written to $csv"

# Report the largest frame-to-frame step INSIDE each burst. A cross-arm
# comparison of absolute luma is not reported on purpose: the pilot's facing
# after HopOut is not reproducible, so the same rectangle photographs different
# geometry in different runs. A step between two consecutive frames of one run
# is the claim this harness can actually support.
Write-Host "[lcplight] ===== largest within-run luma step per burst, scenario '$Scenario' ====="
Write-Host "[lcplight] offbeam = upper right hillside; beam = where a torch or headlight pool lands"
foreach ($r in $results) {
    foreach ($windowName in ($BurstWindows | ForEach-Object { $_.Name })) {
        $series = @($r.Samples | Where-Object { $_.Window -eq $windowName } | Sort-Object Index)
        if ($series.Count -lt 2) {
            Write-Host ("  arm={0,-8} burst={1,-7} (only {2} frame(s) -- no step measurable)" -f `
                $r.Arm, $windowName, $series.Count)
            continue
        }
        $bestDelta = 0.0
        $bestAt = $null
        $bestFrom = 0.0
        $bestTo = 0.0
        for ($i = 1; $i -lt $series.Count; $i++) {
            $d = [math]::Abs($series[$i].OffBeam - $series[$i - 1].OffBeam)
            if ($d -gt $bestDelta) {
                $bestDelta = $d
                $bestAt = $series[$i].At
                $bestFrom = $series[$i - 1].OffBeam
                $bestTo = $series[$i].OffBeam
            }
        }
        $ratio = if ($bestFrom -gt 0.01) { [math]::Round($bestTo / $bestFrom, 3) } else { "n/a" }
        Write-Host ("  arm={0,-8} burst={1,-7} biggest offbeam step at t+{2}: {3} -> {4} (x{5})" -f `
            $r.Arm, $windowName, $bestAt, $bestFrom, $bestTo, $ratio)
    }
}
Write-Host ""
foreach ($r in $results) {
    if (-not $r.Engaged) {
        Write-Host ("[lcplight] arm '{0}' NOT ENGAGED (pilotLights={1} range={2}) -- excluded from any conclusion" -f `
            $r.Arm, $r.Created, $(if ($r.Range -ne $null) { $r.Range } else { "n/a" }))
    }
}
Write-Host "[lcplight] artifacts in $OutputRoot"
