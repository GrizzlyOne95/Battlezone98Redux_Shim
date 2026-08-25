# Shadow-cutoff reproduction matrix runner.
#
# Runs the lcbench "shadowline" scenario (a line of idle craft at known
# station distances) for every {renderer} x {headlight} arm and captures
# frames plus the logs needed to attribute where sun shadows terminate.
#
# Headlight arms write a minimal [SinglePlayer] block so the engine's own
# headlight is used unchanged: "stock" leaves Headlights=1 with no colour or
# beam override, and "off" writes Headlights=0, which the shim implements as
# Ogre setVisible(false) on the stock light. Neither arm touches falloff.
#
# The game is forced windowed for CopyFromScreen; Ogre.cfg / openshim.ini /
# lcbcfg.odf are saved and restored around the run. Launches are serialized
# through BZRHarness.ps1 and shutdown is always Stop-BZRGame.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet("DX11", "DX9", "both")]
    [string]$Renderer = "both",
    # Comma-separated headlight arms: "off,on" (default), or a single state.
    [ValidateSet("off", "on", "off,on")]
    [string]$Headlights = "off,on",
    # shadowline geometry: first station distance and station count
    # (25 m spacing, 3 craft per station).
    [int]$Stations = 28,
    [double]$FirstStation = 25.0,
    [double]$WarmupSeconds = 8.0,
    [int]$Frames = 6,
    [int]$FrameIntervalMs = 1500,
    # Enable the Ogre contributor profiler for this run so caster/technique
    # rows land in openshim_ogre_profile.csv alongside the frames.
    [switch]$WithProfiler,
    # Patch the DEPLOYED lcbench.trn copy (never the repo fixture) to a
    # noon, fog-free view so sun shadows are high-contrast and nothing beyond
    # the shadow cutoff is hidden by the fixture's night atmosphere
    # (stock lcbench ships Time=0300, Fog 175-250, VisibilityRange=250).
    [switch]$DayLight,
    # Apply the game's own shadow settings (quality=3 PSSM/2048, detail=high)
    # at runtime via Frida, replicating what the graphics options UI writes.
    # Without this the install's stored settings apply (this workstation's
    # GOG copy currently has vehicle shadows disabled, scheme high-noshadow).
    [switch]$ForceShadowsOn,
    # Alternative Frida script (relative to reverse_engineering/) that also
    # applies the shadow settings, e.g. trace_light_lists.js.
    [string]$FridaScript = "set_shadow_quality.js",
    [string]$OutputRoot = ""
)

# Graceful game shutdown + launch serialization.
. "$PSScriptRoot\BZRHarness.ps1"

$ErrorActionPreference = "Stop"
Add-Type -AssemblyName System.Drawing

if (-not $OutputRoot) {
    $OutputRoot = Join-Path $PSScriptRoot "snapshots\shadow_cutoff_20260825"
}
New-Item -ItemType Directory -Path $OutputRoot -Force | Out-Null

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$ogreConfig = Join-Path $GameRoot "Ogre.cfg"
$shimIni = Join-Path $GameRoot "openshim.ini"
$missionSourceRoot = Join-Path $PSScriptRoot "test_missions\live_combat_scaling"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$missionConfig = Join-Path $missionRoot "lcbcfg.odf"
$shimLog = Join-Path $GameRoot "logs\openshim.log"

if (-not (Test-Path -LiteralPath $gameExe)) { throw "Game not found: $gameExe" }
foreach ($dep in @("lcbench.bzn", "lcbench.lua", "lcbench.trn", "lcbench.ini")) {
    $path = Join-Path $missionSourceRoot $dep
    if (-not (Test-Path -LiteralPath $path)) { throw "Missing fixture file: $path" }
}

Add-Type @"
using System;
using System.Runtime.InteropServices;
public static class BzShadowWin {
    [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] public static extern bool ClientToScreen(IntPtr h, ref POINT p);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
    [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr h, IntPtr after, int x, int y, int cx, int cy, uint flags);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
    [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
}
"@

$originalOgreConfig = [System.IO.File]::ReadAllText($ogreConfig)
$originalShimIni = if (Test-Path -LiteralPath $shimIni) {
    [System.IO.File]::ReadAllText($shimIni)
} else { $null }
$originalMissionConfig = if (Test-Path -LiteralPath $missionConfig) {
    [System.IO.File]::ReadAllText($missionConfig)
} else { $null }

$renderers = if ($Renderer -eq "both") { @("DX11", "DX9") } else { @($Renderer) }
$states = $Headlights -split ","

function Invoke-Arm {
    param([string]$RendererName, [string]$HeadlightState)

    $armLabel = "{0}_headlight-{1}" -f $RendererName.ToLowerInvariant(), $HeadlightState
    $runRoot = Join-Path $OutputRoot $armLabel
    New-Item -ItemType Directory -Path $runRoot -Force | Out-Null
    Write-Host "=== ARM $armLabel ==="

    Stop-BZRGame
    # A force-killed instance leaves the display stack busy; launching into it
    # is the documented hard-lock/crash window. Wait until EVERY instance is
    # gone (a half-teardown instance from a previous arm counts too) and give
    # the driver a settle margin before the next mode-set.
    $drainDeadline = (Get-Date).AddSeconds(60)
    while ((Get-Date) -lt $drainDeadline) {
        $remaining = Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue
        if (-not $remaining) { break }
        Stop-BZRGame
        Start-Sleep -Seconds 3
    }
    if (Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue) {
        throw "battlezone98redux instances still alive after drain ($armLabel)"
    }
    Start-Sleep -Seconds 8

    # Renderer/window config (same constraints as capture_headlight_falloff).
    $renderSystem = if ($RendererName -eq "DX9") {
        "Direct3D9 Rendering Subsystem"
    } else {
        "Direct3D11 Rendering Subsystem"
    }
    $config = $originalOgreConfig -replace '(?m)^Render System=.*$', "Render System=$renderSystem"
    $config = $config -replace '(?m)^Full Screen=Yes$', 'Full Screen=No'
    $config = $config -replace '(?m)^VSync=Yes$', 'VSync=No'
    $config = $config -replace '(?m)^Video Mode=.*@ 32-bit colour$', 'Video Mode=1920 x 1080 @ 32-bit colour'
    $config = $config -replace '(?m)^FSAA=.*$', 'FSAA=0'
    [System.IO.File]::WriteAllText($ogreConfig, $config)

    # Minimal shim config: stock headlight visibility control only, plus the
    # light-parameter trace that documents what Ogre actually had each frame.
    $headlightsValue = if ($HeadlightState -eq "on") { 1 } else { 0 }
    [System.IO.File]::WriteAllText($shimIni, @"
[SinglePlayer]
Headlights = $headlightsValue
OtherHeadlights = 0

[Diagnostics]
HeadlightLightTrace = 1
$(if ($WithProfiler) { "ProfileOgreAnimation = 1" } else { "" })
"@)

    # Deploy the fixture package FIRST, then write the arm's mission config —
    # the fixture directory contains a default lcbcfg.odf that would otherwise
    # silently overwrite the arm configuration (this bit the first pipeline
    # check: the run executed the stock idle scenario at defaults).
    New-Item -ItemType Directory -Path $missionRoot -Force | Out-Null
    Copy-Item -Path (Join-Path $missionSourceRoot "*") -Destination $missionRoot -Force

    if ($DayLight) {
        # Same-length in-place edits on the deployed copy only. The fixture's
        # night atmosphere would otherwise mask everything past 175-250 m,
        # which is exactly the region the shadow-cutoff question is about.
        $trnPath = Join-Path $missionRoot "lcbench.trn"
        $trn = [System.IO.File]::ReadAllText($trnPath)
        $trn = $trn -replace 'Time=0300', 'Time=1200'
        $trn = $trn -replace 'FogStart=175', 'FogStart=999'
        $trn = $trn -replace 'FogEnd=250', 'FogEnd=999'
        $trn = $trn -replace 'VisibilityRange=250', 'VisibilityRange=999'
        [System.IO.File]::WriteAllText($trnPath, $trn)
    }

    # Deterministic shadowline mission config.
    $invariant = [Globalization.CultureInfo]::InvariantCulture
    [System.IO.File]::WriteAllText($missionConfig, @"
[Benchmark]
scenario = "shadowline"
unitOdf = "avtank"
count = $($Stations * 3)
distance = $($FirstStation.ToString("0.0###", $invariant))
orientation = "facing"
warmupSeconds = $($WarmupSeconds.ToString("0.0###", $invariant))
measureSeconds = 60.0
clusterCount = 4
clusterRadius = 300.0
spinSeconds = 0.0
"@)

    if (Test-Path -LiteralPath $shimLog) {
        try { Remove-Item -LiteralPath $shimLog -Force -ErrorAction Stop } catch { Start-Sleep -Seconds 3; try { Remove-Item -LiteralPath $shimLog -Force -ErrorAction Stop } catch { } }
    }

    $process = Start-Process -FilePath $gameExe -ArgumentList "lcbench.bzn" `
        -WorkingDirectory $GameRoot -PassThru

    $handle = [IntPtr]::Zero
    $deadline = (Get-Date).AddSeconds(90)
    while ((Get-Date) -lt $deadline) {
        $process.Refresh()
        if ($process.HasExited) { throw "Game exited before a window appeared ($armLabel)" }
        if ($process.MainWindowHandle -ne [IntPtr]::Zero) { $handle = $process.MainWindowHandle; break }
        Start-Sleep -Milliseconds 250
    }
    if ($handle -eq [IntPtr]::Zero) { throw "No game window appeared within 90s ($armLabel)" }

    # Warmup + loading-VO margin before capturing. HWND_TOPMOST keeps system
    # popups (firewall prompts, notifications) from occluding the client area
    # mid-capture; the window is parked at (0,0) so the region is predictable.
    Start-Sleep -Seconds ([int][math]::Ceiling($WarmupSeconds + 10))

    if ($ForceShadowsOn) {
        # Attach Frida in a background job so trace scripts stay attached
        # across the whole capture window; the job pipes "exit" to the Frida
        # REPL only after the capture window closes. The game's own apply
        # function rebuilds shadow textures and re-schemes viewports, so a
        # short settle is enough before frames are taken.
        $fridaLog = Join-Path $runRoot "shadowset_frida.txt"
        $fridaScriptPath = Join-Path $PSScriptRoot $FridaScript
        $fridaPid = $process.Id
        $fridaJob = Start-Job -ScriptBlock {
            param($targetPid, $scriptPath, $logPath, $sessionSeconds)
            # The delayed "exit" keeps the Frida REPL's stdin open for the
            # whole capture window; writing it immediately would detach the
            # hooks after the first few intercepted calls.
            & { Start-Sleep -Seconds $sessionSeconds; "exit" } |
                & bzr-frida -p $targetPid -l $scriptPath -q 2>&1 |
                Out-File -FilePath $logPath -Encoding utf8
        } -ArgumentList $fridaPid, $fridaScriptPath, $fridaLog, 90
        Start-Sleep -Seconds 6
        if (Test-Path -LiteralPath $fridaLog) {
            Get-Content $fridaLog |
                Select-String "SHADOWSET|SHADOWFAR" |
                ForEach-Object { Write-Host $_ }
        }
    }

    $HWND_TOPMOST = [IntPtr](-1)
    $SWP_NOSIZE = 0x0001
    $SWP_SHOWWINDOW = 0x0040
    [void][BzShadowWin]::SetWindowPos($handle, $HWND_TOPMOST, 0, 0, 0, 0, $SWP_NOSIZE -bor $SWP_SHOWWINDOW)
    [void][BzShadowWin]::SetForegroundWindow($handle)
    Start-Sleep -Milliseconds 750

    $captured = 0
    for ($index = 0; $index -lt $Frames; $index++) {
        $process.Refresh()
        if ($process.HasExited) { break }
        $rect = New-Object BzShadowWin+RECT
        if (-not [BzShadowWin]::GetClientRect($handle, [ref]$rect)) { break }
        $origin = New-Object BzShadowWin+POINT
        [void][BzShadowWin]::ClientToScreen($handle, [ref]$origin)
        $width = $rect.Right - $rect.Left
        $height = $rect.Bottom - $rect.Top
        if ($width -le 0 -or $height -le 0) { break }

        $bitmap = New-Object System.Drawing.Bitmap $width, $height
        $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
        $graphics.CopyFromScreen(
            (New-Object System.Drawing.Point $origin.X, $origin.Y),
            [System.Drawing.Point]::Empty,
            (New-Object System.Drawing.Size $width, $height))
        $bitmap.Save((Join-Path $runRoot ("frame_{0:d3}.png" -f $index)))
        $graphics.Dispose()
        $bitmap.Dispose()
        $captured++
        Start-Sleep -Milliseconds $FrameIntervalMs
    }

    if (Get-Variable -Name fridaJob -ErrorAction SilentlyContinue -Scope Local) {
        # Let the trace flush, then tear the Frida session down.
        Start-Sleep -Seconds 2
        Stop-Job $fridaJob -ErrorAction SilentlyContinue
        Receive-Job $fridaJob -ErrorAction SilentlyContinue |
            Out-Null
        Remove-Job $fridaJob -Force -ErrorAction SilentlyContinue
        if (Test-Path -LiteralPath $fridaLog) {
            Get-Content $fridaLog |
                Select-String "LIGHTLIST|SHADOWFAR" |
                Select-Object -First 60 |
                ForEach-Object { Write-Host $_ }
        }
    }

    $process.Refresh()
    if (-not $process.HasExited) {
        $process.WaitForExit(25000) | Out-Null
    }
    Stop-BZRGame
    # Confirm the process is really gone before the next arm re-modes the
    # display; the launch lock serializes scripts, not in-flight teardowns.
    $drainDeadline = (Get-Date).AddSeconds(30)
    while ((Get-Date) -lt $drainDeadline) {
        if (-not (Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue)) { break }
        Stop-BZRGame
        Start-Sleep -Seconds 3
    }
    Start-Sleep -Seconds 4

    foreach ($log in @(
        @{ src = $shimLog; dst = "openshim.log" },
        @{ src = (Join-Path $GameRoot "logs\BZLogger.txt"); dst = "BZLogger.txt" },
        @{ src = (Join-Path $GameRoot "BZOgreLogfile.log"); dst = "BZOgreLogfile.log" },
        @{ src = (Join-Path $GameRoot "openshim_ogre_profile.csv"); dst = "openshim_ogre_profile.csv" })) {
        if (Test-Path -LiteralPath $log.src) {
            Copy-Item -LiteralPath $log.src -Destination (Join-Path $runRoot $log.dst) -Force
        }
    }
    Write-Host "Captured $captured frame(s) to $runRoot"
}

try {
    foreach ($rendererName in $renderers) {
        foreach ($state in $states) {
            Invoke-Arm -RendererName $rendererName -HeadlightState $state.Trim()
        }
    }
}
finally {
    [System.IO.File]::WriteAllText($ogreConfig, $originalOgreConfig)
    if ($null -ne $originalShimIni) {
        [System.IO.File]::WriteAllText($shimIni, $originalShimIni)
    }
    if ($null -ne $originalMissionConfig) {
        [System.IO.File]::WriteAllText($missionConfig, $originalMissionConfig)
    }
    Stop-BZRGame
}

$OutputRoot


