# Live validation for the satellite (view 3) Ogre visibility fix.
#
# Runs the canonical lcbench harness in its "satellite" scenario, which spawns
# one group per case the fix has to get right and emits a [SATBENCH] cue line
# at each step of its timeline. This script watches BZLogger for those cues and
# sends the matching view key, so every view change is ordered after the world
# change it is meant to observe rather than being timed blind.
#
# Scoring input is the shim's [SATVISCHK] capture (OPENSHIM_SATVIS_VALIDATE=1),
# which aggregates the arena into one row per team per second:
#   team=N n=<objects> illum=<illumination>0> ogreVis=<Ogre getVisible>
#          unreadable=<no entity> tracked=<in state map> orig=<pre-satellite
#          visible> applied=<fix's last decision>
#
# Expected while view=3 with the fix on (groupCount=3):
#   friendly   (team 1) n>=3 illum=n ogreVis=n     visible
#   detected   (team 6) n>=3 illum=n ogreVis=n     visible
#   undetected (team 7) n>=3 illum=0 ogreVis=0     hidden
#   preHide    (team 8) n=3  illum=3 ogreVis=0     hidden, orig=0
#   reveal     (team 9) n=3  illum=0 ogreVis=0 -> illum=3 ogreVis=3 after the
#                                                 reveal cue, without leaving
#                                                 view 3
# Expected outside view 3: every team ogreVis=n except preHide, which stays 0.
#
# NOTE on the view key: Apply_Satellite_View (BZ 1.5 0x0047B27F, and Redux's
# analogue) returns without doing anything unless ControlPanel_SatelliteEnabled()
# -- which in normal play means the player's team owns a recycler. lcbench.bzn
# ships with only the player in it, so the fixture spawns one; without it
# SHIFT+F10 is silently inert and the whole run measures first person. Redux
# also reads the keyboard through OIS/DirectInput, so keys must be injected as
# scan codes: a virtual-key-only SendInput is accepted by Windows and then
# never seen by the game.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string]$MissionArgs = "lcbench.bzn",
    [ValidateSet("DX11", "DX9")]
    [string]$Renderer = "DX11",
    [ValidateSet(
        "svtank", "svfigh", "avtank", "avfigh", "avrckt", "avartl",
        "avapc", "avwalk", "avmine", "avturr", "aspilo", "svapc",
        "svwalk", "svmine", "svturr", "sspilo")]
    [string]$UnitOdf = "avtank",
    [int]$GroupCount = 3,
    [double]$NearDistance = 60.0,
    [double]$FarDistance = 1400.0,
    [int]$FriendlyTeam = 1,
    [int]$DetectedTeam = 6,
    [int]$UndetectedTeam = 7,
    [int]$PreHideTeam = 8,
    [int]$RevealTeam = 9,
    [string]$RecyclerOdf = "avrecy",
    [int]$RunTimeoutSeconds = 90,
    [string]$OutputRoot = "",
    # Off disables the fix for a same-session control run; the capture still
    # records every row, so the two logs differ only in what the fix did.
    [ValidateSet("On", "Off")]
    [string]$Fix = "On",
    [switch]$NoPreHide,
    [switch]$KillExisting
)

$ErrorActionPreference = "Stop"
if (-not $OutputRoot) {
    $OutputRoot = Join-Path $PSScriptRoot "snapshots\satellite_visibility"
}

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$ogreConfig = Join-Path $GameRoot "Ogre.cfg"
$bzLogger = Join-Path $GameRoot "logs\BZLogger.txt"
$shimLog = Join-Path $GameRoot "logs\openshim.log"
$missionSourceRoot = Join-Path $PSScriptRoot "test_missions\live_combat_scaling"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$missionConfig = Join-Path $missionRoot "lcbcfg.odf"
$sourceMissionConfig = Join-Path $missionSourceRoot "lcbcfg.odf"

foreach ($required in @(
    $gameExe,
    $ogreConfig,
    (Join-Path $missionSourceRoot "lcbench.ini"),
    (Join-Path $missionSourceRoot "lcbench.bzn"),
    (Join-Path $missionSourceRoot "lcbench.trn"),
    (Join-Path $missionSourceRoot "lcbench.lua"),
    $sourceMissionConfig)) {
    if (-not (Test-Path -LiteralPath $required)) {
        throw "Required validation input not found: $required"
    }
}

foreach ($team in @($FriendlyTeam, $DetectedTeam, $UndetectedTeam, $PreHideTeam, $RevealTeam)) {
    if ($team -lt 1 -or $team -gt 15) {
        throw "Team numbers must be within 1..15 (got $team)"
    }
}
if (@($FriendlyTeam, $DetectedTeam, $UndetectedTeam, $PreHideTeam, $RevealTeam) |
        Group-Object | Where-Object { $_.Count -gt 1 }) {
    throw "Each fixture group needs its own team so the capture rows stay separable"
}

if ($KillExisting) {
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Stop-Process -Force
    Start-Sleep -Seconds 2
} elseif (Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue) {
    throw "Battlezone is already running. Stop it or pass -KillExisting."
}

# A locked or otherwise non-interactive console silently swallows SendInput, so
# the run would score the lock screen instead of the game. Fail loudly instead.
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public static class SatelliteValidationInput {
    public delegate bool EnumProc(IntPtr h, IntPtr l);
    [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc cb, IntPtr l);
    [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
    [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);

    // Process.MainWindowHandle is not dependable here: it is queried before the
    // render window exists and does not always recover. The render window is an
    // OgreD3D11Wnd/OgreD3D9Wnd owned by the game process, so find it by
    // enumeration instead -- that is also what makes the foreground check mean
    // something, since a wrong handle would read as "not foreground" forever.
    public static IntPtr FindGameWindow(uint wantPid) {
        IntPtr found = IntPtr.Zero;
        EnumWindows((h, l) => {
            uint pid;
            GetWindowThreadProcessId(h, out pid);
            if (pid != wantPid || !IsWindowVisible(h)) return true;
            StringBuilder cls = new StringBuilder(64);
            GetClassName(h, cls, cls.Capacity);
            if (cls.ToString().StartsWith("OgreD3D", StringComparison.Ordinal)) {
                found = h;
                return false;
            }
            return true;
        }, IntPtr.Zero);
        return found;
    }
    public const int SW_RESTORE = 9;
    public const ushort VK_SPACE = 0x20;
    public const ushort VK_SHIFT = 0x10;
    public const ushort VK_F10   = 0x79;
    public const ushort VK_D     = 0x44;
    public const uint KEYEVENTF_KEYUP = 0x0002;
    public const uint KEYEVENTF_SCANCODE = 0x0008;
    public const uint MAPVK_VK_TO_VSC = 0;
    public const uint INPUT_KEYBOARD = 1;
    [DllImport("user32.dll")] public static extern uint MapVirtualKey(uint code, uint mapType);
    [StructLayout(LayoutKind.Sequential)] public struct INPUT { public uint type; public InputUnion U; }
    // MOUSEINPUT is the largest union member, and SendInput rejects the whole
    // call with ERROR_INVALID_PARAMETER (87) when cbSize is not the full
    // sizeof(INPUT) -- 40 bytes on x64. Declaring only KEYBDINPUT here would
    // make that 32 and every send would silently fail.
    [StructLayout(LayoutKind.Explicit)] public struct InputUnion {
        [FieldOffset(0)] public MOUSEINPUT mi;
        [FieldOffset(0)] public KEYBDINPUT ki;
        [FieldOffset(0)] public HARDWAREINPUT hi;
    }
    [StructLayout(LayoutKind.Sequential)] public struct MOUSEINPUT { public int dx; public int dy; public uint mouseData; public uint dwFlags; public uint time; public IntPtr extra; }
    [StructLayout(LayoutKind.Sequential)] public struct KEYBDINPUT { public ushort wVk; public ushort wScan; public uint dwFlags; public uint time; public IntPtr extra; }
    [StructLayout(LayoutKind.Sequential)] public struct HARDWAREINPUT { public uint uMsg; public ushort wParamL; public ushort wParamH; }
    [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int n);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
    [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
    [DllImport("user32.dll")] public static extern bool AttachThreadInput(uint a, uint b, bool attach);
    [DllImport("kernel32.dll")] public static extern uint GetCurrentThreadId();
    [DllImport("user32.dll", SetLastError=true)] private static extern uint SendInput(uint n, INPUT[] p, int cb);

    // SetForegroundWindow is refused outright when the caller does not own the
    // foreground, which is exactly this script's situation. Attaching to the
    // current foreground thread first lifts that restriction. The caller must
    // still check the return value: SendInput goes to whatever is foreground,
    // so a failed activation would type the view keys into someone else's
    // window rather than the game.
    public static bool ForceForeground(IntPtr h) {
        if (h == IntPtr.Zero) return false;
        if (GetForegroundWindow() == h) return true;
        uint pid;
        uint fgThread = GetWindowThreadProcessId(GetForegroundWindow(), out pid);
        uint myThread = GetCurrentThreadId();
        bool attached = false;
        if (fgThread != 0 && fgThread != myThread) {
            attached = AttachThreadInput(myThread, fgThread, true);
        }
        ShowWindow(h, SW_RESTORE);
        BringWindowToTop(h);
        SetForegroundWindow(h);
        if (attached) AttachThreadInput(myThread, fgThread, false);
        return GetForegroundWindow() == h;
    }

    // Redux reads the keyboard through OIS/DirectInput, which works in scan
    // codes and ignores virtual-key-only injection: a VK-only SendInput is
    // accepted by the OS and then never seen by the game. Every key here is
    // therefore sent as KEYEVENTF_SCANCODE with wVk left at zero.
    private static INPUT Key(ushort vk, bool up) {
        INPUT i = new INPUT();
        i.type = INPUT_KEYBOARD;
        i.U.ki.wVk = 0;
        i.U.ki.wScan = (ushort)MapVirtualKey(vk, MAPVK_VK_TO_VSC);
        i.U.ki.dwFlags = KEYEVENTF_SCANCODE | (up ? KEYEVENTF_KEYUP : 0u);
        return i;
    }
    private static bool Send(params INPUT[] input) {
        return SendInput((uint)input.Length, input, Marshal.SizeOf(typeof(INPUT))) == input.Length;
    }
    public static bool KeyDown(ushort vk) { return Send(Key(vk, false)); }
    public static bool KeyUp(ushort vk)   { return Send(Key(vk, true)); }
}
"@

$script:LastForegroundDiag = ""

function Set-GameForeground {
    param([System.Diagnostics.Process]$Process, [int]$Attempts = 5)
    for ($i = 0; $i -lt $Attempts; $i++) {
        $hwnd = [SatelliteValidationInput]::FindGameWindow([uint32]$Process.Id)
        if ($hwnd -ne [IntPtr]::Zero) {
            if ([SatelliteValidationInput]::ForceForeground($hwnd)) {
                $script:LastForegroundDiag = "hwnd=0x{0:X} ok" -f $hwnd.ToInt64()
                return $true
            }
            try {
                (New-Object -ComObject WScript.Shell).AppActivate($Process.Id) | Out-Null
            } catch {
            }
            if ([SatelliteValidationInput]::ForceForeground($hwnd)) {
                $script:LastForegroundDiag = "hwnd=0x{0:X} ok-after-appactivate" -f $hwnd.ToInt64()
                return $true
            }
        }
        $fg = [SatelliteValidationInput]::GetForegroundWindow()
        $script:LastForegroundDiag =
            "hwnd=0x{0:X} fg=0x{1:X} attempt={2}" -f $hwnd.ToInt64(), $fg.ToInt64(), $i
        Start-Sleep -Milliseconds 250
    }
    return $false
}

# OVER_VIEW is SHIFT+F10 and COCKPIT_VIEW is D in the stock gamekey.map. Using
# the two absolute bindings rather than TOGGLE_OVERVIEW (BSP) means a missed
# keystroke cannot leave the run inverted for the rest of the timeline.
#
# Every send is gated on a confirmed foreground: SendInput has no target, so
# sending without that check would deliver "shift+F10" and "d" to whatever
# window the user happens to have in front.
function Send-KeyTap {
    param([ushort]$Vk, [ushort[]]$Modifiers = @(), [int]$HoldMs = 80)
    $ok = $true
    foreach ($m in $Modifiers) { $ok = [SatelliteValidationInput]::KeyDown($m) -and $ok }
    if ($Modifiers.Count -gt 0) { Start-Sleep -Milliseconds 40 }
    # The game samples the keyboard once per frame, so a zero-length press can
    # fall between two polls. Hold long enough to span several frames.
    $ok = [SatelliteValidationInput]::KeyDown($Vk) -and $ok
    Start-Sleep -Milliseconds $HoldMs
    $ok = [SatelliteValidationInput]::KeyUp($Vk) -and $ok
    if ($Modifiers.Count -gt 0) { Start-Sleep -Milliseconds 40 }
    foreach ($m in $Modifiers) { $ok = [SatelliteValidationInput]::KeyUp($m) -and $ok }
    return $ok
}

function Send-ViewKey {
    param([System.Diagnostics.Process]$Process, [string]$Cue)
    if (-not (Set-GameForeground $Process)) {
        return $false
    }
    if ($Cue -like "enter-*") {
        return Send-KeyTap -Vk ([SatelliteValidationInput]::VK_F10) `
            -Modifiers @([SatelliteValidationInput]::VK_SHIFT)
    }
    return Send-KeyTap -Vk ([SatelliteValidationInput]::VK_D)
}

function Read-LogText {
    param([string]$Path)
    if (-not (Test-Path -LiteralPath $Path)) {
        return ""
    }
    $stream = [System.IO.File]::Open($Path, 'Open', 'Read', 'ReadWrite')
    try {
        $reader = New-Object System.IO.StreamReader($stream)
        $text = $reader.ReadToEnd()
        $reader.Dispose()
    } finally {
        $stream.Dispose()
    }
    return $text
}

$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
$runRoot = Join-Path $OutputRoot ("{0}_fix{1}" -f $stamp, $Fix.ToLowerInvariant())
New-Item -ItemType Directory -Path $runRoot -Force | Out-Null

$originalOgreConfig = [System.IO.File]::ReadAllText($ogreConfig)
$priorEnv = @{}
foreach ($name in @(
    "OPENSHIM_SATVIS_VALIDATE",
    "OPENSHIM_SATVIS_VALIDATE_BUDGET",
    "OPENSHIM_SATVIS_TEST_PREHIDE_TEAM",
    "OPENSHIM_TRACE_SATELLITE_VISIBILITY_FIX",
    "OPENSHIM_DISABLE_SATELLITE_VISIBILITY_FIX",
    "OPENSHIM_PROFILE_OGRE_ANIMATION")) {
    $priorEnv[$name] = [Environment]::GetEnvironmentVariable($name, "Process")
}

try {
    New-Item -ItemType Directory -Path $missionRoot -Force | Out-Null
    Copy-Item -Path (Join-Path $missionSourceRoot "*") -Destination $missionRoot -Force

    $invariant = [Globalization.CultureInfo]::InvariantCulture
    $config = @"
[Benchmark]
scenario = "satellite"
unitOdf = "$UnitOdf"
count = 0
distance = $($NearDistance.ToString("0.0###", $invariant))
orientation = "facing"
warmupSeconds = 4.0
measureSeconds = 8.0

[Satellite]
friendlyTeam = $FriendlyTeam
detectedTeam = $DetectedTeam
undetectedTeam = $UndetectedTeam
preHideTeam = $PreHideTeam
revealTeam = $RevealTeam
groupCount = $($GroupCount.ToString($invariant))
nearDistance = $($NearDistance.ToString("0.0###", $invariant))
farDistance = $($FarDistance.ToString("0.0###", $invariant))
recyclerOdf = "$RecyclerOdf"
"@
    [System.IO.File]::WriteAllText($missionConfig, $config)

    $renderSystem = if ($Renderer -eq "DX9") {
        "Direct3D9 Rendering Subsystem"
    } else {
        "Direct3D11 Rendering Subsystem"
    }
    [System.IO.File]::WriteAllText(
        $ogreConfig,
        ($originalOgreConfig -replace '(?m)^Render System=.*$', "Render System=$renderSystem"))

    [Environment]::SetEnvironmentVariable("OPENSHIM_SATVIS_VALIDATE", "1", "Process")
    [Environment]::SetEnvironmentVariable("OPENSHIM_SATVIS_VALIDATE_BUDGET", "240", "Process")
    [Environment]::SetEnvironmentVariable(
        "OPENSHIM_TRACE_SATELLITE_VISIBILITY_FIX", "1", "Process")
    [Environment]::SetEnvironmentVariable(
        "OPENSHIM_SATVIS_TEST_PREHIDE_TEAM",
        $(if ($NoPreHide) { $null } else { "$PreHideTeam" }),
        "Process")
    [Environment]::SetEnvironmentVariable(
        "OPENSHIM_DISABLE_SATELLITE_VISIBILITY_FIX",
        $(if ($Fix -eq "Off") { "1" } else { $null }),
        "Process")
    # The animation profiler is unrelated here and only adds log noise.
    [Environment]::SetEnvironmentVariable("OPENSHIM_PROFILE_OGRE_ANIMATION", "0", "Process")

    Write-Host "Starting satellite validation (fix=$Fix, renderer=$Renderer)"
    $startedAt = Get-Date
    $process = Start-Process -FilePath $gameExe -ArgumentList $MissionArgs `
        -WorkingDirectory $GameRoot -PassThru

    $deadline = (Get-Date).AddSeconds($RunTimeoutSeconds)
    $handled = @{}
    $cueLog = New-Object System.Collections.Generic.List[string]
    $completed = $false
    $foregroundConfirmed = $false
    $nextLoadSkip = Get-Date

    while ((Get-Date) -lt $deadline -and -not $process.HasExited) {
        Start-Sleep -Milliseconds 200
        $tail = Read-LogText $bzLogger
        if (-not $tail) { continue }
        if ((Get-Item $bzLogger).LastWriteTime -lt $startedAt) { continue }

        if ($tail -match 'Waiting For VO' -and $tail -notmatch 'VO complete' -and
                (Get-Date) -ge $nextLoadSkip) {
            if (Set-GameForeground $process -Attempts 2) {
                [void](Send-KeyTap -Vk ([SatelliteValidationInput]::VK_SPACE))
            }
            $nextLoadSkip = (Get-Date).AddMilliseconds(500)
        }

        foreach ($cue in @(
            "enter-satellite", "exit-satellite",
            "enter-satellite-2", "exit-satellite-2", "done")) {
            if ($handled.ContainsKey($cue)) { continue }
            # BZLogger appends its own timestamp straight onto the line with no
            # separator ("cue=enter-satellite2026-08-22 ..."), so the cue name
            # cannot be anchored on trailing whitespace. A negative lookahead on
            # '-' is what keeps "enter-satellite" from also matching
            # "enter-satellite-2".
            if ($tail -notmatch [regex]::Escape("[SATBENCH]") + ".*cue=" +
                    [regex]::Escape($cue) + '(?!-)') {
                continue
            }
            $handled[$cue] = $true

            if ($cue -eq "done") {
                $completed = $true
                break
            }

            # Give the shim at least one [SATVISCHK] sample on the current side
            # of the transition before flipping the view.
            Start-Sleep -Milliseconds 1200
            $sent = Send-ViewKey $process $cue
            if ($sent) {
                $foregroundConfirmed = $true
            }
            $entry = "{0}  cue={1} sent={2} [{3}]" -f `
                (Get-Date).ToString("o"), $cue, $sent, $script:LastForegroundDiag
            $cueLog.Add($entry)
            Write-Host "  $entry"
        }
        if ($completed) { break }
    }

    # Two extra seconds of samples after the last transition so the final
    # restore is captured rather than inferred.
    if ($completed) {
        Start-Sleep -Seconds 2
    }

    if (-not $process.HasExited) {
        Stop-Process -Id $process.Id -Force
        $process.WaitForExit()
    }
    Start-Sleep -Milliseconds 750

    $tail = Read-LogText $bzLogger
    [System.IO.File]::WriteAllText((Join-Path $runRoot "BZLogger.slice.txt"), $tail)
    if (Test-Path -LiteralPath $shimLog) {
        Copy-Item -LiteralPath $shimLog -Destination (Join-Path $runRoot "openshim.log") -Force
    }
    $cueLog | Set-Content -LiteralPath (Join-Path $runRoot "cues.txt") -Encoding ASCII

    $shimText = if (Test-Path (Join-Path $runRoot "openshim.log")) {
        Get-Content -LiteralPath (Join-Path $runRoot "openshim.log") -Raw
    } else { "" }
    $satvischk = ([regex]::Matches($shimText, '(?m)^.*\[SATVISCHK\].*$') |
        ForEach-Object { $_.Value })
    $satvischk | Set-Content -LiteralPath (Join-Path $runRoot "satvischk.txt") -Encoding UTF8
    $satbench = ([regex]::Matches($tail, '(?m)^.*\[SATBENCH\].*$') |
        ForEach-Object { $_.Value })
    $satbench | Set-Content -LiteralPath (Join-Path $runRoot "satbench.txt") -Encoding UTF8

    $metadata = [ordered]@{
        run_id = Split-Path -Leaf $runRoot
        renderer = $Renderer
        unit_odf = $UnitOdf
        fix = $Fix
        pre_hide_team = $(if ($NoPreHide) { $null } else { $PreHideTeam })
        teams = [ordered]@{
            friendly = $FriendlyTeam
            detected = $DetectedTeam
            undetected = $UndetectedTeam
            preHide = $PreHideTeam
            reveal = $RevealTeam
        }
        group_count = $GroupCount
        near_distance = $NearDistance
        far_distance = $FarDistance
        cues_sent = $cueLog.Count
        foreground_confirmed = $foregroundConfirmed
        completed = $completed
        satvischk_lines = $satvischk.Count
        started_at = $startedAt.ToString("o")
        ended_at = (Get-Date).ToString("o")
    }
    $metadata | ConvertTo-Json -Depth 4 |
        Set-Content -LiteralPath (Join-Path $runRoot "metadata.json") -Encoding ASCII

    if (-not $foregroundConfirmed) {
        Write-Warning ("The game window never became foreground, so the view keys " +
            "were almost certainly swallowed (locked session?). Treat this run as void.")
    }
    if (-not $completed) {
        Write-Warning "Fixture did not reach cue=done"
    }
    if ($satvischk.Count -eq 0) {
        Write-Warning "No [SATVISCHK] lines captured; the validation capture did not arm"
    }
} finally {
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Stop-Process -Force
    [System.IO.File]::WriteAllText($ogreConfig, $originalOgreConfig)
    if (Test-Path -LiteralPath $sourceMissionConfig) {
        Copy-Item -LiteralPath $sourceMissionConfig -Destination $missionConfig -Force
    }
    foreach ($name in $priorEnv.Keys) {
        [Environment]::SetEnvironmentVariable($name, $priorEnv[$name], "Process")
    }
}

Write-Host "Satellite validation complete: $runRoot"
$runRoot
