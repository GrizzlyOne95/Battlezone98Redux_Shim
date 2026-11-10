# Display stress for pre-Workshop release qualification (Docs/RELEASE_QUALIFICATION.md,
# "Display stress"). Drives an ALREADY-RUNNING test game through N cycles of
# Alt-Tab, Alt-Enter, an optional fullscreen/windowed toggle key, and (with -EditMode) Shift-F9, and
# reports crash / hang / new crash-dump / new crash-log lines per step.
#
# This script never launches the game. Launch it first with the normal harness
# helpers (BZRHarness.ps1: Assert-BZRSafeToLaunch + Start-BZRGameProcess), then
# run this against it. One game process only: refuses to run if more than one exists.
#
# Windows PowerShell 5.1 (BZRWindowInput.ps1 needs System.Drawing).
# Shift-F9 only works in /edit mode (the editor), so it runs only with -EditMode, and the
# already-running game must have been launched with /edit (the script checks its command
# line and refuses otherwise). Without -EditMode the step is skipped. Its task-mode crash is already a known open
# roadmap item (Docs/ROADMAP_CODE_VALIDATION_20261007.md, item 300), so a failure on
# that step is reported as KNOWN-300 and does not by itself fail the run.
#
# Window geometry is checked after every step (per-monitor DPI-aware, physical pixels) and
# recorded in the report: after Alt-Enter (or -ToggleVk) into fullscreen the client area must
# cover the monitor the window is on within 2 px and the window must have no caption or
# sizing border; after Alt-Enter back the client size must return to the windowed size seen
# first; after Alt-Tab back the window must not be minimised or off every monitor. A failed
# check is reported as GEOMETRY and fails the run. Keystrokes need an unlocked desktop: with
# the session locked the run aborts at once. -InputMode Post posts Alt-Enter to the window
# instead (works while locked or in the background) and skips Alt-Tab, which only real input
# can do.
#
# Timeout handling follows the harness rule (BZRHarness.ps1 Stop-BZRGame): the game is
# closed with WM_CLOSE and NEVER force-killed, because terminating a process that owns
# the D3D device can wedge the display stack. If it ignores WM_CLOSE it is left running
# and the run exits non-zero; close it by hand.
param([ValidateRange(1,200)][int]$Cycles = 10,
      [int]$ProcessId = 0,
      # Virtual key of the fullscreen/windowed toggle, if the build under test has one
      # (0 = skip that step). Not assumed: no toggle hotkey is documented in the repo.
      [ValidateRange(0,255)][int]$ToggleVk = 0,
      [ValidateRange(200,10000)][int]$StepWaitMs = 1500,
      [ValidateRange(5,120)][int]$HangSeconds = 15,
      [ValidateRange(30,7200)][int]$HardTimeoutSeconds = 900,
      # Run the Shift-F9 step. Requires the running game to have been launched with /edit.
      [switch]$EditMode,
      [string]$ReportPath = '',
      # Keys = real keystrokes (default). Post = posted Alt-Enter, no Alt-Tab (see header).
      [ValidateSet('Keys', 'Post')][string]$InputMode = 'Keys',
      # How long a geometry check keeps re-measuring before it fails.
      [ValidateRange(0,30000)][int]$GeometrySettleMs = 5000)
$ErrorActionPreference = 'Stop'
. "$PSScriptRoot\BZRHarness.ps1"
. "$PSScriptRoot\BZRWindowInput.ps1"

if (-not ('BZRStress.Keys' -as [type])) {
    Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
namespace BZRStress {
public static class Keys {
    [DllImport("user32.dll")] static extern void keybd_event(byte vk, byte scan, uint flags, UIntPtr extra);
    [DllImport("user32.dll")] static extern uint MapVirtualKey(uint code, uint mapType);
    [DllImport("user32.dll")] static extern bool SetForegroundWindow(IntPtr h);
    // Press mods in order, then key, then release in reverse. Real input.
    public static void Chord(byte[] mods, byte key, int holdMs) {
        foreach (byte m in mods) keybd_event(m, (byte)MapVirtualKey(m, 0), 0, UIntPtr.Zero);
        keybd_event(key, (byte)MapVirtualKey(key, 0), 0, UIntPtr.Zero);
        System.Threading.Thread.Sleep(holdMs);
        keybd_event(key, (byte)MapVirtualKey(key, 0), 2, UIntPtr.Zero);
        for (int i = mods.Length - 1; i >= 0; i--) keybd_event(mods[i], (byte)MapVirtualKey(mods[i], 0), 2, UIntPtr.Zero);
    }
    public static bool Focus(IntPtr h) { return SetForegroundWindow(h); }
}
}
'@
}

if (-not ('BZRStress.Geom' -as [type])) {
    Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
namespace BZRStress {
public class Snap {
    public int[] Window; public int[] Client; public int[] Monitor;  // left, top, width, height
    public string Style; public string ExStyle;
    public bool Framed; public bool CoversMonitor; public bool Iconic; public bool OnMonitor;
    public bool Topmost; public bool Foreground;
}
public static class Geom {
    [StructLayout(LayoutKind.Sequential)] struct RECT { public int L, T, R, B; }
    [StructLayout(LayoutKind.Sequential)] struct POINT { public int X, Y; }
    [StructLayout(LayoutKind.Sequential)] struct MONITORINFO { public int cb; public RECT mon; public RECT work; public uint flags; }
    [DllImport("user32.dll")] static extern bool GetWindowRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] static extern bool GetClientRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] static extern bool ClientToScreen(IntPtr h, ref POINT p);
    [DllImport("user32.dll")] static extern int GetWindowLong(IntPtr h, int i);
    [DllImport("user32.dll")] static extern bool IsIconic(IntPtr h);
    [DllImport("user32.dll")] static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll")] static extern IntPtr MonitorFromWindow(IntPtr h, uint flags);
    [DllImport("user32.dll")] static extern bool GetMonitorInfo(IntPtr m, ref MONITORINFO mi);
    [DllImport("user32.dll")] static extern IntPtr SetThreadDpiAwarenessContext(IntPtr ctx);
    [DllImport("user32.dll")] static extern IntPtr OpenInputDesktop(uint flags, bool inherit, uint access);
    [DllImport("user32.dll")] static extern bool CloseDesktop(IntPtr h);
    [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint msg, IntPtr w, IntPtr l);
    const int WS_CAPTION_OR_SIZEBOX = 0x00C40000;  // WS_CAPTION | WS_THICKFRAME
    const int WS_EX_TOPMOST = 0x00000008;

    // Physical pixels on every monitor: per-monitor-v2 for this thread while measuring
    // (falls back to the process's system DPI awareness before Windows 10 1607).
    public static Snap Measure(IntPtr h) {
        IntPtr old = IntPtr.Zero;
        try { old = SetThreadDpiAwarenessContext(new IntPtr(-4)); } catch (EntryPointNotFoundException) { }
        try {
            RECT w, c; GetWindowRect(h, out w); GetClientRect(h, out c);
            POINT p = new POINT(); ClientToScreen(h, ref p);
            MONITORINFO mi = new MONITORINFO(); mi.cb = Marshal.SizeOf(typeof(MONITORINFO));
            GetMonitorInfo(MonitorFromWindow(h, 2 /* NEAREST */), ref mi);
            int style = GetWindowLong(h, -16), ex = GetWindowLong(h, -20);
            Snap s = new Snap();
            s.Window = new[] { w.L, w.T, w.R - w.L, w.B - w.T };
            s.Client = new[] { p.X, p.Y, c.R - c.L, c.B - c.T };
            s.Monitor = new[] { mi.mon.L, mi.mon.T, mi.mon.R - mi.mon.L, mi.mon.B - mi.mon.T };
            s.Style = "0x" + style.ToString("X8"); s.ExStyle = "0x" + ex.ToString("X8");
            s.Framed = (style & WS_CAPTION_OR_SIZEBOX) != 0;
            s.Iconic = IsIconic(h);
            s.OnMonitor = !s.Iconic && MonitorFromWindow(h, 0 /* NULL */) != IntPtr.Zero;
            s.CoversMonitor = Math.Abs(p.X - mi.mon.L) <= 2 && Math.Abs(p.Y - mi.mon.T) <= 2 &&
                              Math.Abs(p.X + c.R - mi.mon.R) <= 2 && Math.Abs(p.Y + c.B - mi.mon.B) <= 2;
            s.Topmost = (ex & WS_EX_TOPMOST) != 0;
            s.Foreground = GetForegroundWindow() == h;
            return s;
        } finally {
            if (old != IntPtr.Zero) SetThreadDpiAwarenessContext(old);
        }
    }

    // False while the workstation is locked (or the session disconnected): keystrokes
    // then go to the lock screen, not the game.
    public static bool InputDesktopAvailable() {
        IntPtr d = OpenInputDesktop(0, false, 0x0100 /* DESKTOP_SWITCHDESKTOP */);
        if (d == IntPtr.Zero) return false;
        CloseDesktop(d);
        return true;
    }
}
}
'@
}

$VK_MENU = 0x12; $VK_SHIFT = 0x10; $VK_TAB = 0x09; $VK_RETURN = 0x0D; $VK_F9 = 0x78

$games = @(Get-Process -Name $script:BZRGameProcessName -ErrorAction SilentlyContinue)
if ($games.Count -eq 0) { throw 'No running game. Launch the test game first via the BZRHarness.ps1 helpers; this script does not launch.' }
if ($games.Count -gt 1) { throw "More than one game process running ($($games.Id -join ', ')); this stress test caps at one." }
$game = $games[0]
if ($EditMode) {
    $cmd = [string](Get-CimInstance Win32_Process -Filter "ProcessId=$($game.Id)").CommandLine
    if ($cmd -notmatch '(^|\s)/edit(\s|$)') { throw "-EditMode needs the game launched with /edit; command line is: $cmd" }
} else {
    Write-Host 'Shift-F9 step skipped: it only works in /edit mode (relaunch with /edit and pass -EditMode to include it).'
}
if ($ProcessId -and $ProcessId -ne $game.Id) { throw "-ProcessId $ProcessId is not the running game (pid $($game.Id))." }
$procId = $game.Id
$gameDir = try { Split-Path -Parent $game.MainModule.FileName } catch { '' }

# Crash evidence: dump files and growth of the shim log since the last step.
function Get-CrashEvidence {
    $dumps = @()
    if ($gameDir) { $dumps += @(Get-ChildItem -Path $gameDir -Recurse -Filter '*.dmp' -ErrorAction SilentlyContinue | ForEach-Object { $_.FullName }) }
    $dumps += @(Get-ChildItem -Path "$env:LOCALAPPDATA\CrashDumps" -Filter 'battlezone98redux*.dmp' -ErrorAction SilentlyContinue | ForEach-Object { $_.FullName })
    $logs = @()
    if ($gameDir) { $logs = @(@('openshim.log', 'logs\openshim.log') | ForEach-Object { Join-Path $gameDir $_ } | Where-Object { Test-Path -LiteralPath $_ }) }
    $lens = @{}
    foreach ($l in $logs) { $lens[$l] = (Get-Item -LiteralPath $l).Length }
    [pscustomobject]@{ Dumps = $dumps; Lens = $lens }
}
$script:base = Get-CrashEvidence

function Get-NewCrashEvidence {
    $now = Get-CrashEvidence
    $out = @()
    $new = @($now.Dumps | Where-Object { $script:base.Dumps -notcontains $_ })
    if ($new) { $out += "new dump: $($new -join '; ')" }
    foreach ($log in $now.Lens.Keys) {
        $prev = 0
        if ($script:base.Lens.ContainsKey($log)) { $prev = $script:base.Lens[$log] }
        if ($now.Lens[$log] -gt $prev) {
            $fs = [IO.File]::Open($log, 'Open', 'Read', 'ReadWrite')
            try { [void]$fs.Seek($prev, 'Begin'); $text = (New-Object IO.StreamReader($fs)).ReadToEnd() } finally { $fs.Dispose() }
            $hits = @($text -split "`r?`n" | Where-Object { $_ -match '(?i)crash|access violation|unhandled|fatal|minidump' } | Select-Object -First 3)
            if ($hits) { $out += "log: $($hits -join ' | ')" }
        }
    }
    $script:base = $now
    $out
}

function Test-GameState {
    # 'ok', 'exited', or 'hang' (not responding for HangSeconds straight).
    $until = (Get-Date).AddSeconds($HangSeconds)
    while ($true) {
        try { $game.Refresh(); if ($game.HasExited) { return 'exited' } } catch { return 'exited' }
        if ($game.Responding) { return 'ok' }
        if ((Get-Date) -ge $until) { return 'hang' }
        Start-Sleep -Milliseconds 500
    }
}

$results = New-Object System.Collections.Generic.List[object]
$clock = [Diagnostics.Stopwatch]::StartNew()
$script:aborted = ''
$script:known300Stop = ''

function Measure-GameWindow {
    try { [BZRStress.Geom]::Measure((Get-BZRClientWindow $procId)) } catch { $null }
}
function Get-WindowMode($g) {
    if ($g -and $g.CoversMonitor -and -not $g.Framed -and -not $g.Iconic) { 'fullscreen' } else { 'windowed' }
}
# Mode the game is in; the windowed client size (width, height) Alt-Enter must return to.
$script:mode = 'windowed'
$script:windowedSize = $null

# Returns the failure text ('' = pass) and the last measurement, re-measuring until it
# passes or GeometrySettleMs runs out.
function Test-StepGeometry([string]$Name) {
    $toggle = $Name -in 'Alt-Enter', 'Toggle'
    $expect = if (-not $toggle) { '' } elseif ($script:mode -eq 'fullscreen') { 'windowed' } else { 'fullscreen' }
    $until = (Get-Date).AddMilliseconds($GeometrySettleMs)
    while ($true) {
        $g = Measure-GameWindow
        $fail = if (-not $g) { 'no game window to measure' }
        elseif ($expect -eq 'fullscreen') {
            if ($g.Iconic) { 'fullscreen: window is minimised' }
            elseif ($g.Framed) { "fullscreen: window still has a caption or sizing border (style $($g.Style))" }
            elseif (-not $g.CoversMonitor) { "fullscreen: client $($g.Client -join ',') does not cover monitor $($g.Monitor -join ',')" }
            else { '' }
        } elseif ($expect -eq 'windowed') {
            if ($g.Iconic) { 'windowed: window is minimised' }
            elseif (-not $g.OnMonitor) { "windowed: window $($g.Window -join ',') is off every monitor" }
            elseif ($script:windowedSize -and ([Math]::Abs($g.Client[2] - $script:windowedSize[0]) -gt 2 -or
                                               [Math]::Abs($g.Client[3] - $script:windowedSize[1]) -gt 2)) {
                "windowed: client $($g.Client[2])x$($g.Client[3]) is not the starting $($script:windowedSize -join 'x')"
            } else { '' }
        } elseif ($Name -eq 'Alt-Tab') {
            if ($g.Iconic) { 'after Alt-Tab back: window is minimised' }
            elseif (-not $g.OnMonitor) { "after Alt-Tab back: window $($g.Window -join ',') is off every monitor" }
            else { '' }
        } else { '' }
        if (-not $fail -or (Get-Date) -ge $until) { break }
        Start-Sleep -Milliseconds 250
    }
    $before = $script:mode
    # A toggle flips the game's own mode even when the window ends up wrong, so the next
    # toggle is expected to go back; other steps re-read the mode from the window.
    $script:mode = if ($expect) { $expect } else { Get-WindowMode $g }
    if ($g -and $script:mode -eq 'windowed' -and -not $script:windowedSize -and -not $fail) { $script:windowedSize = @($g.Client[2], $g.Client[3]) }
    $note = if ($Name -eq 'Alt-Tab' -and $before -ne $script:mode) { "mode changed by Alt-Tab: $before -> $($script:mode)" } else { '' }
    [pscustomobject]@{ Fail = $fail; Note = $note; Expect = $expect; Mode = $script:mode; Geometry = $g }
}

function Invoke-Step([int]$Cycle, [string]$Name, [scriptblock]$Action) {
    if ($clock.Elapsed.TotalSeconds -gt $HardTimeoutSeconds) { $script:aborted = "hard timeout ${HardTimeoutSeconds}s"; return $false }
    $err = ''
    try { & $Action } catch { $err = $_.Exception.Message }
    Start-Sleep -Milliseconds $StepWaitMs
    $state = Test-GameState
    $evidence = @(Get-NewCrashEvidence)
    $geo = if ($state -eq 'ok') { Test-StepGeometry $Name } else { $null }
    $status = if ($err) { 'INPUT-ERROR' } elseif ($state -eq 'exited') { 'CRASH' } elseif ($state -eq 'hang') { 'HANG' } elseif ($evidence.Count) { 'CRASH-LOG' } elseif ($geo -and $geo.Fail) { 'GEOMETRY' } else { 'ok' }
    if ($Name -eq 'Shift-F9' -and $status -in 'CRASH', 'HANG', 'CRASH-LOG') { $status = "KNOWN-300 ($status)" }
    $detail = (@($err) + $evidence + @($(if ($geo) { $geo.Fail; $geo.Note })) | Where-Object { $_ }) -join ' / '
    $results.Add([pscustomobject]@{ Cycle = $Cycle; Step = $Name; Status = $status; Detail = $detail
                                    Expect = $(if ($geo) { $geo.Expect }); Mode = $(if ($geo) { $geo.Mode }); Geometry = $(if ($geo) { $geo.Geometry }) })
    $where = if ($geo -and $geo.Geometry) { " client=$($geo.Geometry.Client -join ',') monitor=$($geo.Geometry.Monitor -join ',') style=$($geo.Geometry.Style)" } else { '' }
    Write-Host ("[{0,3}] {1,-10} {2} {3}{4}" -f $Cycle, $Name, $status, $detail, $where)
    return ($state -eq 'ok')
}

try {
    $hwnd = Get-BZRClientWindow $procId
    if ($InputMode -eq 'Keys' -and -not [BZRStress.Geom]::InputDesktopAvailable()) {
        $script:aborted = 'session is locked: keystrokes would reach the lock screen, not the game (unlock, or use -InputMode Post)'
    }
    # Starting mode and, if windowed, the size Alt-Enter must return to.
    $g0 = Measure-GameWindow
    $script:mode = Get-WindowMode $g0
    if ($g0 -and $script:mode -eq 'windowed') { $script:windowedSize = @($g0.Client[2], $g0.Client[3]) }
    Write-Host ("start: mode=$($script:mode)" + $(if ($g0) { " client=$($g0.Client -join ',') monitor=$($g0.Monitor -join ',') style=$($g0.Style)" }))
    for ($c = 1; $c -le $Cycles -and -not $script:aborted; $c++) {
        $steps = if ($InputMode -eq 'Post') {
            # WM_SYSKEYDOWN/UP for Alt+Enter (context bit 29 = Alt held, scan 0x1C).
            @(@{ N = 'Alt-Enter'; A = { [void][BZRStress.Geom]::PostMessage($hwnd, 0x104, [IntPtr]$VK_RETURN, [IntPtr]0x201C0001)
                                        [void][BZRStress.Geom]::PostMessage($hwnd, 0x105, [IntPtr]$VK_RETURN, [IntPtr][int]0xE01C0001) } })
        } else {
            @(
                @{ N = 'Alt-Tab';   A = { [BZRStress.Keys]::Chord([byte[]]@($VK_MENU), [byte]$VK_TAB, 120); Start-Sleep -Milliseconds 600; [void][BZRStress.Keys]::Focus($hwnd) } },
                @{ N = 'Alt-Enter'; A = { [void][BZRStress.Keys]::Focus($hwnd); Start-Sleep -Milliseconds 150; [BZRStress.Keys]::Chord([byte[]]@($VK_MENU), [byte]$VK_RETURN, 120) } }
            )
        }
        if ($ToggleVk) { $steps += @{ N = 'Toggle'; A = { [void][BZRStress.Keys]::Focus($hwnd); Start-Sleep -Milliseconds 150; [BZRStress.Keys]::Chord([byte[]]@(), [byte]$ToggleVk, 120) } } }
        if ($EditMode) { $steps += @{ N = 'Shift-F9'; A = { [void][BZRStress.Keys]::Focus($hwnd); Start-Sleep -Milliseconds 150; [BZRStress.Keys]::Chord([byte[]]@($VK_SHIFT), [byte]$VK_F9, 120) } } }
        foreach ($s in $steps) {
            $healthy = Invoke-Step $c $s.N $s.A
            if ($script:aborted) { break }
            if (-not $healthy) {
                if ($s.N -eq 'Shift-F9') { $script:known300Stop = "game down after Shift-F9 in cycle $c (known item 300); remaining cycles not run" }
                else { $script:aborted = "game not healthy after $($s.N) in cycle $c" }
                break
            }
            try { $hwnd = Get-BZRClientWindow $procId } catch { }
        }
        if ($script:aborted -or $script:known300Stop) { break }
    }
} finally {
    # Graceful close only (never force-kill; see header). Skip if the game already died.
    if (Get-Process -Id $procId -ErrorAction SilentlyContinue) {
        try { Stop-BZRGame -Id $procId -TimeoutSeconds 60 } catch { Write-Warning $_.Exception.Message }
    }
}

$bad = @($results | Where-Object { $_.Status -ne 'ok' -and $_.Status -notlike 'KNOWN-300*' })
$known = @($results | Where-Object { $_.Status -like 'KNOWN-300*' })
$summary = [pscustomobject]@{
    Cycles = $Cycles; StepsRun = $results.Count; Failures = $bad.Count; Known300 = $known.Count
    Aborted = $script:aborted; Known300Stop = $script:known300Stop; Pass = ($bad.Count -eq 0 -and -not $script:aborted)
}
Write-Host ($summary | ConvertTo-Json -Compress)
if ($ReportPath) { @{ summary = $summary; steps = $results } | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath $ReportPath -Encoding UTF8 }
if ($summary.Pass) { exit 0 } else { exit 1 }
