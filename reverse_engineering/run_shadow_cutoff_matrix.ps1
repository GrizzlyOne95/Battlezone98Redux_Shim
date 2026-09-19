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
    # Comma-separated shadow-far arms (OPENSHIM_SHADOW_FAR_DISTANCE). "stock"
    # is passed through literally, which the shim reads as an opt-out back to
    # the 128 m clip; the shipped default is 256. Example: "stock,256,384".
    [string]$ShadowFarDistances = "stock,256",
    # Shadow quality byte persisted into BZPLYR.DEF for the duration of the
    # run (3 = PSSM/2048, high detail). The original file bytes are restored
    # in finally. The workstation's stored value is -1 (shadows disabled),
    # which would measure the wrong pipeline entirely.
    [ValidateRange(-1, 4)]
    [int]$ShadowQuality = 3,
    # Exact shadowline station distances (comma-separated metres). Default
    # brackets both cutoff candidates: 128 m clip and 250/256 m LOD switch.
    [string]$StationDistances = "25,50,75,100,125,130,180,240,255,260,300",
    # shadowline geometry when StationDistances is empty: first station
    # distance and station count (25 m spacing, 3 craft per station).
    [int]$Stations = 28,
    [double]$FirstStation = 25.0,
    # The player craft keeps drifting for ~20 s after Game Simulation
    # Initialized. Capturing before it settles gives each arm a different
    # camera position, and a frame-to-frame A/B of two different viewpoints
    # measures the viewpoint. 26 s is past the settle.
    [double]$WarmupSeconds = 26.0,
    # [NormalView] Time written into the fixture terrain, as HHMM.
    #
    # This used to be hard-coded to 1200. Noon puts the sun overhead, which is
    # the shortest shadow the scene can cast -- so the fixture that exists to
    # find where sun shadows terminate was being run under the lighting least
    # able to show one. A grazing sun is the point: long shadows across the
    # station line make the cascade-3 coverage edge visible as a boundary
    # rather than as a subtle change in ground tone.
    [ValidatePattern('^\d{3,4}$')]
    [string]$SunTime = "0700",
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
    # Alternative Frida script (relative to reverse_engineering/) for ad-hoc
    # runtime probes; not needed when -ShadowQuality is used.
    [string]$FridaScript = "",
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
    [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
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

# Creates the game OUTSIDE this shell's job object. A Start-Process child is
# inside it, and an agent session's job carries
# JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE -- the game then dies partway through the
# run as a clean WM_CLOSE, which reads as the game quitting rather than as a
# killed capture.
function Start-ShadowMatrixGame {
    param([Parameter(Mandatory)][string]$Exe,
          [string]$Arguments = "",
          [Parameter(Mandatory)][string]$WorkingDirectory)

    $commandLine = if ($Arguments) { "`"$Exe`" $Arguments" } else { "`"$Exe`"" }
    $result = Invoke-CimMethod -ClassName Win32_Process -MethodName Create `
        -Arguments @{ CommandLine = $commandLine; CurrentDirectory = $WorkingDirectory }
    if ($result.ReturnValue -ne 0 -or -not $result.ProcessId) {
        throw "WMI process create failed (ReturnValue=$($result.ReturnValue)) for $commandLine"
    }
    $deadline = (Get-Date).AddSeconds(10)
    do {
        $proc = Get-Process -Id $result.ProcessId -ErrorAction SilentlyContinue
        if ($proc) { return $proc }
        Start-Sleep -Milliseconds 100
    } while ((Get-Date) -lt $deadline)
    throw "Game process $($result.ProcessId) started but could not be opened"
}

# PowerShell is a virtualised DPI client by default: ClientToScreen would hand
# back logical coordinates while CopyFromScreen reads physical ones, so every
# frame would be grabbed up and left of the window. That reads as a cropped or
# occluded capture rather than as a measurement taken from the wrong place.
[void][BzShadowWin]::SetProcessDPIAware()

$fars = $ShadowFarDistances -split ","

# BZPLYR.DEF layout (FUN_008205e0): 'PLYR' magic + version dword, then 0x50
# settings-struct bytes read straight into DAT_0094672c. The shadow-quality
# sbyte (struct +0x25) therefore lives at FILE OFFSET 0x2D. The workstation's
# stored value is 0xFF (-1 = vehicle shadows disabled). Save/restore the whole
# file around the run.
$playerDef = Join-Path $GameRoot "BZPLYR.DEF"
$originalPlayerDef = if (Test-Path -LiteralPath $playerDef) {
    [System.IO.File]::ReadAllBytes($playerDef)
} else { $null }

function Set-ShadowQualityByte {
    param([int]$Quality)
    if ($null -eq $originalPlayerDef -or $originalPlayerDef.Length -le 0x2D) {
        throw "BZPLYR.DEF missing or too short to carry the shadow-quality byte"
    }
    $bytes = [System.IO.File]::ReadAllBytes($playerDef)
    $bytes[0x2D] = [byte]($Quality -band 0xFF)
    [System.IO.File]::WriteAllBytes($playerDef, $bytes)
}

function Invoke-Arm {
    param([string]$RendererName, [string]$HeadlightState, [string]$ShadowFar)

    # Instances launched from THIS GameRoot only. Name-matching the process
    # also catches instances other harness runs/worktrees started from a
    # different install, which is how a parallel agent's session gets taken
    # out as a bystander (Stop-BZRGame's own docs prefer -Id for this reason).
    function Get-OwnBZRProcess {
        Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
            Where-Object {
                try { $_.Path -and
                    ($_.Path -ieq $gameExe) } catch { $false }
            }
    }

    $farLabel = if ($ShadowFar -eq "stock") { "far-stock" } else { "far-$ShadowFar" }
    $armLabel = "{0}_{1}_headlight-{2}" -f $RendererName.ToLowerInvariant(), $farLabel, $HeadlightState
    $runRoot = Join-Path $OutputRoot $armLabel
    New-Item -ItemType Directory -Path $runRoot -Force | Out-Null
    Write-Host "=== ARM $armLabel ==="

    $preExisting = @(Get-OwnBZRProcess)
    if ($preExisting.Count -gt 0) {
        Stop-BZRGame -Id @($preExisting.Id)
    }
    # A force-killed instance leaves the display stack busy; launching into it
    # is the documented hard-lock/crash window. Wait until every instance from
    # this GameRoot is gone (a half-teardown instance from a previous arm
    # counts too) and give the driver a settle margin before the next
    # mode-set. Instances from other installs are another run's property and
    # are left alone.
    $drainDeadline = (Get-Date).AddSeconds(60)
    while ((Get-Date) -lt $drainDeadline) {
        $remaining = @(Get-OwnBZRProcess)
        if ($remaining.Count -eq 0) { break }
        Stop-BZRGame -Id @($remaining.Id)
        Start-Sleep -Seconds 3
    }
    if (Get-OwnBZRProcess) {
        throw "battlezone98redux instances still alive after drain ($armLabel)"
    }
    Start-Sleep -Seconds 8

    # Shadow-quality byte: set before launch so the mission-load apply runs
    # the PSSM branch exactly once, with the stock scheme from the start.
    Set-ShadowQualityByte -Quality $ShadowQuality


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
    # The shadow-far arm rides in this same write. It cannot be a separate one:
    # this rewrites openshim.ini wholesale, so anything written earlier is
    # gone. And it cannot be a process environment variable either, because the
    # game is created through WMI (so it lands outside this shell's job object)
    # and a WMI-created process inherits none of our environment. The shim
    # reads this section before the real environment.
    #
    # "stock" is passed through literally rather than omitted: the correction
    # is on by default now, so an ABSENT setting means 256, and a stock arm
    # that said nothing would silently measure the fix and label it baseline.
    [System.IO.File]::WriteAllText($shimIni, @"
[SinglePlayer]
Headlights = $headlightsValue
OtherHeadlights = 0

[Diagnostics]
HeadlightLightTrace = 1
$(if ($WithProfiler) { "ProfileOgreAnimation = 1" } else { "" })

[Environment]
OPENSHIM_SHADOW_FAR_DISTANCE=$ShadowFar
"@)

    # Deploy the fixture package FIRST, then write the arm's mission config —
    # the fixture directory contains a default lcbcfg.odf that would otherwise
    # silently overwrite the arm configuration (this bit the first pipeline
    # check: the run executed the stock idle scenario at defaults).
    New-Item -ItemType Directory -Path $missionRoot -Force | Out-Null
    Copy-Item -Path (Join-Path $missionSourceRoot "*") -Destination $missionRoot -Force

    if ($DayLight) {
        # Edits on the deployed copy only. The fixture's night TIME and its
        # 175-250 m fog would otherwise mask the 128-256 m band, which is
        # exactly the region the shadow-cutoff question is about. The black
        # starry sky in captures is correct: this is the moon map and MOON.ACT
        # is its brightest available palette.
        #
        # -SunTime governs the rest. This block used to force noon, on the
        # reasoning that it gives the strongest ground contrast -- but an
        # overhead sun gives the SHORTEST cast shadows, so it suppressed the
        # very feature the fixture exists to locate. A grazing sun lays long
        # shadows down the station line instead, and the cascade-3 coverage
        # edge shows up as those shadows ending rather than as a shift in
        # ground tone.
        $trnPath = Join-Path $missionRoot "lcbench.trn"
        $trn = [System.IO.File]::ReadAllText($trnPath)
        $trn = $trn -replace 'Time=0300', "Time=$SunTime"
        $trn = $trn -replace 'FogStart=175', 'FogStart=999'
        $trn = $trn -replace 'FogEnd=250', 'FogEnd=999'
        $trn = $trn -replace 'VisibilityRange=250', 'VisibilityRange=999'
        [System.IO.File]::WriteAllText($trnPath, $trn)
    }

    # Deterministic shadowline mission config. With explicit station
    # distances the Lua derives the unit count from the list (3 per station).
    $invariant = [Globalization.CultureInfo]::InvariantCulture
    $stationLine = ""
    $countLine = "count = $($Stations * 3)"
    if ($StationDistances -ne "") {
        $stationLine = 'stationDistances = "' + $StationDistances + '"'
        $stationCount = ($StationDistances -split ",").Count
        $countLine = "count = $($stationCount * 3)"
    }
    [System.IO.File]::WriteAllText($missionConfig, @"
[Benchmark]
scenario = "shadowline"
unitOdf = "avtank"
$countLine
distance = $($FirstStation.ToString("0.0###", $invariant))
orientation = "facing"
warmupSeconds = $($WarmupSeconds.ToString("0.0###", $invariant))
measureSeconds = 60.0
clusterCount = 4
clusterRadius = 300.0
spinSeconds = 0.0
$stationLine
"@)

    if (Test-Path -LiteralPath $shimLog) {
        try { Remove-Item -LiteralPath $shimLog -Force -ErrorAction Stop } catch { Start-Sleep -Seconds 3; try { Remove-Item -LiteralPath $shimLog -Force -ErrorAction Stop } catch { } }
    }

    $process = Start-ShadowMatrixGame -Exe $gameExe -Arguments "lcbench.bzn" `
        -WorkingDirectory $GameRoot

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

    if ($FridaScript -ne "") {
        # Optional ad-hoc Frida probe. Runs in a background job so trace
        # scripts stay attached across the whole capture window; the job
        # pipes "exit" to the Frida REPL only after the capture closes.
        $fridaLog = Join-Path $runRoot "shadowset_frida.txt"
        $fridaScriptPath = Join-Path $PSScriptRoot $FridaScript
        $fridaPid = $process.Id
        $fridaJob = Start-Job -ScriptBlock {
            param($targetPid, $scriptPath, $logPath, $sessionSeconds)
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
        Stop-BZRGame -Id $process.Id
    }
    # Confirm the process is really gone before the next arm re-modes the
    # display; the launch lock serializes scripts, not in-flight teardowns.
    # Scoped to this GameRoot: a concurrent run's instance is not ours to wait
    # on, and waiting on it here would deadlock two serialized harness runs.
    $drainDeadline = (Get-Date).AddSeconds(30)
    while ((Get-Date) -lt $drainDeadline) {
        $remaining = @(Get-OwnBZRProcess)
        if ($remaining.Count -eq 0) { break }
        Stop-BZRGame -Id @($remaining.Id)
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
            foreach ($far in $fars) {
                Invoke-Arm -RendererName $rendererName `
                    -HeadlightState $state.Trim() `
                    -ShadowFar $far.Trim()
            }
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
    if ($null -ne $originalPlayerDef) {
        [System.IO.File]::WriteAllBytes($playerDef, $originalPlayerDef)
    }
    Remove-Item Env:OPENSHIM_SHADOW_FAR_DISTANCE -ErrorAction SilentlyContinue
    # Own instances only (same rule as Invoke-Arm): never a bystander session.
    $own = Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Where-Object { try { $_.Path -and ($_.Path -ieq $gameExe) } catch { $false } }
    if ($own) {
        Stop-BZRGame -Id @($own.Id)
    }
}

$OutputRoot




