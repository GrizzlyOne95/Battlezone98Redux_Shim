# Motion runner for the walker cockpit jitter investigation.
#
# Why this exists separately from run_lcwalk.ps1: Goto() does not move a vehicle
# that SetAsUser() has handed to the player, so the "fwd"/"slope" arms of the
# cycling matrix never actually moved anything. Reproducing the jitter needs the
# possessed walker driven through the NORMAL player input path, which means real
# keyboard input delivered to the game window while one walker stays possessed
# for the whole window (mission case "hold_<odf>").
#
# Input is sent as SET 1 SCAN CODES with KEYEVENTF_SCANCODE. Virtual-key-only
# sends are swallowed by Redux; extended keys additionally need
# KEYEVENTF_EXTENDEDKEY. INPUT is 40 bytes in this (x64) PowerShell host.
#
# The phase table is written to phases.csv with wall-clock timestamps so native
# [WALKF] frames (which carry their own timestamps) can be attributed to a phase.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet("avwalk","svwalk","bvwalk","cvwalk","avtank")]
    [string]$Variant = "avwalk",
    [ValidateSet("wasd","arrows")]
    [string]$KeySet = "wasd",
    [int]$LoadSeconds = 12,
    [string]$OutputRoot = "",
    [switch]$DisableMods
)

$ErrorActionPreference = "Stop"
$env:BZR_FORCE_WINDOWED = "1"
. "$PSScriptRoot\BZRHarness.ps1"

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$fixtureRoot = Join-Path $PSScriptRoot "test_missions\lcbench_walker"
$logRoot = Join-Path $GameRoot "logs"
$modsRoot = Join-Path $GameRoot "mods"
$parkRoot = Join-Path $GameRoot "openshim_test_backups\mods_parked_drive"

if (-not $OutputRoot) {
    $OutputRoot = Join-Path $GameRoot ("openshim_test_results\lcwalkdrive_" + (Get-Date -Format "yyyyMMdd_HHmmss"))
}
New-Item -ItemType Directory -Path $OutputRoot -Force | Out-Null

Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
public static class Drv {
  [StructLayout(LayoutKind.Sequential)]
  public struct KEYBDINPUT { public ushort wVk; public ushort wScan; public uint dwFlags; public uint time; public IntPtr dwExtraInfo; }
  // Size MUST be pinned to 40. The INPUT union is sized by MOUSEINPUT (32
  // bytes) plus the 4-byte type and 4 bytes of padding on x64. Declaring only
  // KEYBDINPUT marshals to 32 and SendInput then rejects the call with
  // ERROR_INVALID_PARAMETER (87).
  [StructLayout(LayoutKind.Explicit, Size = 40)]
  public struct INPUT { [FieldOffset(0)] public uint type; [FieldOffset(8)] public KEYBDINPUT ki; }
  [DllImport("user32.dll", SetLastError=true)] public static extern uint SendInput(uint n, INPUT[] p, int cb);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int n);

  public const uint KEYEVENTF_EXTENDEDKEY = 0x0001, KEYEVENTF_KEYUP = 0x0002, KEYEVENTF_SCANCODE = 0x0008;

  public static void Key(ushort scan, bool extended, bool down) {
    INPUT[] i = new INPUT[1];
    i[0].type = 1;
    i[0].ki.wVk = 0;
    i[0].ki.wScan = scan;
    uint f = KEYEVENTF_SCANCODE;
    if (extended) f |= KEYEVENTF_EXTENDEDKEY;
    if (!down) f |= KEYEVENTF_KEYUP;
    i[0].ki.dwFlags = f;
    i[0].ki.time = 0;
    i[0].ki.dwExtraInfo = IntPtr.Zero;
    uint sent = SendInput(1, i, Marshal.SizeOf(typeof(INPUT)));
    if (sent != 1) throw new Exception("SendInput failed err=" + Marshal.GetLastWin32Error());
  }
}
'@

# Set 1 scan codes. Arrow keys are extended (require the E0 prefix flag).
$keys = if ($KeySet -eq "wasd") {
    @{ fwd = @(0x11,$false); back = @(0x1F,$false); left = @(0x1E,$false); right = @(0x20,$false) }
} else {
    @{ fwd = @(0x48,$true); back = @(0x50,$true); left = @(0x4B,$true); right = @(0x4D,$true) }
}

$held = @{}
function KeyDown($name) { if (-not $held[$name]) { $k=$keys[$name]; [Drv]::Key([uint16]$k[0], [bool]$k[1], $true); $held[$name]=$true } }
function KeyUp($name)   { if ($held[$name])     { $k=$keys[$name]; [Drv]::Key([uint16]$k[0], [bool]$k[1], $false); $held[$name]=$false } }
function AllUp() { foreach ($n in @("fwd","back","left","right")) { KeyUp $n } }

# phase name -> keys held, duration seconds
$phases = @(
    @{ name = "stabilize"; keys = @();                dur = 3 },
    @{ name = "forward";   keys = @("fwd");           dur = 5 },
    @{ name = "stop1";     keys = @();                dur = 2 },
    @{ name = "turnleft";  keys = @("left");          dur = 5 },
    @{ name = "stop2";     keys = @();                dur = 2 },
    @{ name = "fwdturn";   keys = @("fwd","right");   dur = 5 },
    @{ name = "stop3";     keys = @();                dur = 2 },
    @{ name = "reverse";   keys = @("back");          dur = 4 },
    @{ name = "stop4";     keys = @();                dur = 2 }
)

$deployNames = @("lcbench.lua", "rmwcfg.odf")
$backupRoot = Join-Path $OutputRoot "pre_live"
New-Item -ItemType Directory -Path $backupRoot -Force | Out-Null
$originallyPresent = @{}
foreach ($name in $deployNames) {
    $live = Join-Path $missionRoot $name
    $originallyPresent[$name] = Test-Path -LiteralPath $live
    if ($originallyPresent[$name]) { Copy-Item -LiteralPath $live -Destination (Join-Path $backupRoot $name) -Force }
}

$parked = $false
$process = $null
$phaseLog = @()

try {
    if ($DisableMods) {
        # Renaming inside mods\ is NOT enough: the game enumerates every
        # subdirectory of mods\ regardless of name. The folder must leave mods\.
        $subdirs = @(Get-ChildItem $modsRoot -Directory -ErrorAction SilentlyContinue)
        if ($subdirs.Count -gt 0) {
            New-Item -ItemType Directory -Path $parkRoot -Force | Out-Null
            foreach ($d in $subdirs) { Move-Item $d.FullName (Join-Path $parkRoot $d.Name) }
            $parked = $true
            Write-Host "[drive] parked $($subdirs.Count) mod folder(s) out of mods\"
        }
    }

    Copy-Item -LiteralPath (Join-Path $fixtureRoot "rmwlk.lua") -Destination (Join-Path $missionRoot "lcbench.lua") -Force
    [System.IO.File]::WriteAllText((Join-Path $missionRoot "rmwcfg.odf"), @"
[Roadmap]
case = "hold_$Variant"
commit = "drive"
"@)

    $existing = @(Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue)
    if ($existing.Count -gt 0) { throw "Refusing to start while another Battlezone process is running" }

    $process = Start-Process -FilePath $gameExe -ArgumentList "lcbench.bzn" -WorkingDirectory $GameRoot -PassThru
    Write-Host "[drive] launched pid=$($process.Id); waiting ${LoadSeconds}s for mission load + possession"
    Start-Sleep -Seconds $LoadSeconds

    $process.Refresh()
    if ($process.HasExited) { throw "Game exited during load (exit=$($process.ExitCode))" }
    if ($process.MainWindowHandle -ne [IntPtr]::Zero) {
        [Drv]::ShowWindow($process.MainWindowHandle, 9) | Out-Null
        [Drv]::SetForegroundWindow($process.MainWindowHandle) | Out-Null
        Start-Sleep -Milliseconds 700
    }
    $fg = [Drv]::GetForegroundWindow()
    Write-Host "[drive] game hwnd=$($process.MainWindowHandle) foreground=$fg focused=$($fg -eq $process.MainWindowHandle)"

    foreach ($p in $phases) {
        $start = Get-Date
        AllUp
        foreach ($k in $p.keys) { KeyDown $k }
        Write-Host ("[drive] phase {0,-10} keys={1,-14} {2:HH:mm:ss.fff}" -f $p.name, ($p.keys -join "+"), $start)
        $phaseLog += [pscustomobject]@{
            phase = $p.name; keys = ($p.keys -join "+"); startUtc = $start.ToUniversalTime().ToString("o"); durationSec = $p.dur
        }
        Start-Sleep -Seconds $p.dur
    }
    AllUp
}
finally {
    try { AllUp } catch { }
    if ($process -and -not $process.HasExited) { Stop-BZRGame -Id $process.Id }

    foreach ($logName in @("BZLogger.txt", "openshim.log", "openshim_crash.log")) {
        $source = Join-Path $logRoot $logName
        if (Test-Path -LiteralPath $source) { Copy-Item -LiteralPath $source -Destination (Join-Path $OutputRoot $logName) -Force }
    }
    if ($phaseLog.Count -gt 0) {
        $phaseLog | Export-Csv -LiteralPath (Join-Path $OutputRoot "phases.csv") -NoTypeInformation -Encoding UTF8
    }

    foreach ($name in $deployNames) {
        $live = Join-Path $missionRoot $name
        if ($originallyPresent[$name]) { Copy-Item -LiteralPath (Join-Path $backupRoot $name) -Destination $live -Force }
        elseif (Test-Path -LiteralPath $live) { Remove-Item -LiteralPath $live -Force }
    }

    if ($parked) {
        foreach ($d in @(Get-ChildItem $parkRoot -Directory -ErrorAction SilentlyContinue)) {
            Move-Item $d.FullName (Join-Path $modsRoot $d.Name)
        }
        Remove-Item $parkRoot -Force -ErrorAction SilentlyContinue
        Write-Host "[drive] mod folders RESTORED to mods\"
    }
    Write-Host "[drive] complete -> $OutputRoot"
}
