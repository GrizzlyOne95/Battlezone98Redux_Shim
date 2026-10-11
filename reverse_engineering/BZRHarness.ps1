# Shared safety helpers for every harness script that launches the game.
#
# Background: on 2026-08-23 and 2026-08-24 the workstation hard-locked three
# times while agents drove these scripts in a loop -- total freeze, no bugcheck,
# no minidump, no WHEA entry, no TDR. The signature is a deadlock inside the
# kernel display stack, not a crash: the GPU scheduler itself wedges, so the
# TDR watchdog never fires and Windows never gets far enough to write a dump.
#
# Two harness behaviours produced it, and both are fixed here:
#
#   1. Ogre.cfg ships "Full Screen=Yes" at 3840x2160, so any script that did not
#      explicitly override it took an exclusive-fullscreen mode-set on every
#      launch -- dozens of times an hour.
#   2. The game was then torn down with Stop-Process -Force (TerminateProcess),
#      which kills it mid-frame while it still owns the D3D device and the
#      exclusive-fullscreen display mode. Terminating a process in that state
#      leaves the mode-set half-finished and the device never released.
#
# Dot-source this file from any script that starts battlezone98redux.exe:
#
#     . "$PSScriptRoot\BZRHarness.ps1"
#
# See docs/HARNESS_SAFETY.md for the full write-up.

# Deliberately no Set-StrictMode here: this file is dot-sourced, so it runs in
# the caller's scope and would silently change behaviour for every script that
# picks it up.

$script:BZRGameProcessName = 'battlezone98redux'

# Harness clients are driven by posted window messages, so a foreground test
# window that clips or re-centres the OS cursor only steals the real mouse from
# whoever is at the desk. Launched games inherit this; OpenShim then never
# calls ClipCursor/SetCursorPos for them. A script that genuinely needs stock
# mouse capture sets it to 0 before dot-sourcing this file.
if (-not $env:OPENSHIM_NEVER_CAPTURE_MOUSE) { $env:OPENSHIM_NEVER_CAPTURE_MOUSE = '1' }

# The user may be playing (or in a PvP match) while tests run, and a test
# window that activates itself steals their foreground and keyboard focus even
# with the mouse left alone. Launched games inherit this; OpenShim then never
# activates, raises or focuses the game window (ShowWindow -> SW_SHOWNOACTIVATE,
# SetForegroundWindow/BringWindowToTop/SetActiveWindow no-ops, SetWindowPos +
# SWP_NOACTIVATE). A script that genuinely needs an activated window (SendInput
# drivers) sets it to 0 before dot-sourcing this file and sets
# BZR_ALLOW_FOREGROUND_LAUNCH=1 (see Assert-BZRSafeToLaunch).
if (-not $env:OPENSHIM_NEVER_ACTIVATE) { $env:OPENSHIM_NEVER_ACTIVATE = '1' }

# Native helpers for the foreground-steal watchdog below.
if (-not ('BZRForegroundWatchdog' -as [type])) {
    Add-Type -TypeDefinition @'
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;

public static class BZRForegroundWatchdog
{
    [DllImport("user32.dll")] static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll")] static extern uint GetWindowThreadProcessId(IntPtr hwnd, out uint pid);
    [DllImport("user32.dll")] static extern bool SetForegroundWindow(IntPtr hwnd);
    [DllImport("user32.dll")] static extern bool IsWindow(IntPtr hwnd);
    [DllImport("user32.dll")] static extern bool AttachThreadInput(uint idAttach, uint idAttachTo, bool fAttach);
    [DllImport("kernel32.dll")] static extern uint GetCurrentThreadId();

    static readonly object Gate = new object();
    static readonly List<string> Events = new List<string>();
    static int running = 0;

    public static string LogPath = Path.Combine(Path.GetTempPath(), "bzr_foreground_watchdog.log");

    static void Note(string text)
    {
        string line = DateTime.Now.ToString("HH:mm:ss.fff") + " " + text;
        lock (Gate) { Events.Add(line); }
        try { File.AppendAllText(LogPath, line + Environment.NewLine); } catch { }
    }

    public static string[] Snapshot() { lock (Gate) { return Events.ToArray(); } }
    public static bool IsRunning() { return Interlocked.CompareExchange(ref running, 0, 0) != 0; }

    static bool IsGame(uint pid, string gameName)
    {
        if (pid == 0) return false;
        try { return string.Equals(Process.GetProcessById((int)pid).ProcessName, gameName, StringComparison.OrdinalIgnoreCase); }
        catch { return false; }
    }

    // Waits up to waitForGameMs for the game process to exist, then polls the
    // foreground window every intervalMs for watchMs. If it ever belongs to the
    // game, logs FOREGROUND-STOLEN and hands the foreground back to whatever
    // held it before. allowAttach enables the AttachThreadInput fallback.
    public static bool Start(string gameName, int waitForGameMs, int watchMs, int intervalMs, bool allowAttach)
    {
        if (Interlocked.CompareExchange(ref running, 1, 0) != 0) return false;
        Thread t = new Thread(delegate() {
            try { Run(gameName, waitForGameMs, watchMs, intervalMs, allowAttach); }
            catch (Exception ex) { Note("watchdog error: " + ex.Message); }
            finally { Interlocked.Exchange(ref running, 0); }
        });
        t.IsBackground = true;
        t.Name = "BZRForegroundWatchdog";
        t.Start();
        return true;
    }

    static void Run(string gameName, int waitForGameMs, int watchMs, int intervalMs, bool allowAttach)
    {
        IntPtr previous = IntPtr.Zero;
        Stopwatch wait = Stopwatch.StartNew();
        Stopwatch watch = null;
        int reported = 0;
        while (true)
        {
            IntPtr fg = GetForegroundWindow();
            uint pid = 0;
            if (fg != IntPtr.Zero) GetWindowThreadProcessId(fg, out pid);
            bool gameFg = IsGame(pid, gameName);

            if (watch == null)
            {
                if (Process.GetProcessesByName(gameName).Length > 0) { watch = Stopwatch.StartNew(); Note("game process seen; watching foreground for " + watchMs + " ms"); }
                else if (wait.ElapsedMilliseconds > waitForGameMs) { Note("game never appeared; watchdog done"); return; }
            }
            else if (watch.ElapsedMilliseconds > watchMs) { Note("watchdog window over; reported " + reported + " steal(s)"); return; }

            if (!gameFg)
            {
                if (fg != IntPtr.Zero) previous = fg;
            }
            else if (watch != null)
            {
                reported++;
                Note("FOREGROUND-STOLEN: game pid " + pid + " took the foreground (previous hwnd 0x" + previous.ToInt64().ToString("X") + ")");
                if (previous != IntPtr.Zero && IsWindow(previous))
                {
                    bool ok = SetForegroundWindow(previous);
                    Thread.Sleep(30);
                    IntPtr now = GetForegroundWindow();
                    uint nowPid = 0; if (now != IntPtr.Zero) GetWindowThreadProcessId(now, out nowPid);
                    if (!ok || IsGame(nowPid, gameName))
                    {
                        Note("plain SetForegroundWindow did not restore the previous window");
                        if (allowAttach)
                        {
                            uint fgThread = GetWindowThreadProcessId(now, out nowPid);
                            uint me = GetCurrentThreadId();
                            bool attached = AttachThreadInput(me, fgThread, true);
                            SetForegroundWindow(previous);
                            if (attached) AttachThreadInput(me, fgThread, false);
                            Note("AttachThreadInput fallback attempted (attached=" + attached + ")");
                        }
                    }
                    else Note("foreground restored to previous window");
                }
            }
            Thread.Sleep(intervalMs);
        }
    }
}
'@
}

function Start-BZRForegroundWatchdog {
    <#
    .SYNOPSIS
        Detects (and undoes) the game taking the foreground right after launch.
    .DESCRIPTION
        Background thread, so the caller is not blocked. Waits up to 60 s for the
        game process to appear, then for 15 s polls GetForegroundWindow every
        250 ms. If the foreground ever belongs to the game it logs a loud
        FOREGROUND-STOLEN line (Get-BZRForegroundWatchdogLog; also appended to
        %TEMP%\bzr_foreground_watchdog.log) and calls SetForegroundWindow on the
        previous foreground window. The AttachThreadInput fallback runs only when
        plain SetForegroundWindow failed AND BZR_WATCHDOG_ATTACH_INPUT=1 (opt-in
        until it has been verified on a supervised run).
        Disable with BZR_NO_FOREGROUND_WATCHDOG=1.
    #>
    [CmdletBinding()]
    param(
        [int]$WaitForGameSeconds = 60,
        [int]$WatchSeconds = 15,
        [int]$PollMilliseconds = 250
    )
    if ($env:BZR_NO_FOREGROUND_WATCHDOG -eq '1') { return $false }
    [BZRForegroundWatchdog]::Start($script:BZRGameProcessName, $WaitForGameSeconds * 1000,
        $WatchSeconds * 1000, $PollMilliseconds, ($env:BZR_WATCHDOG_ATTACH_INPUT -eq '1'))
}

function Get-BZRForegroundWatchdogLog {
    [CmdletBinding()]
    param()
    [BZRForegroundWatchdog]::Snapshot()
}

function Assert-BZRSafeToLaunch {
    <#
    .SYNOPSIS
        Launch guard: refuses to start the game unless it cannot steal input.
    .DESCRIPTION
        Throws unless OPENSHIM_NEVER_ACTIVATE=1 and OPENSHIM_NEVER_CAPTURE_MOUSE=1
        are both set in the environment the game will inherit. This file defaults
        both to 1, so the guard only fires when a script switched one off. User
        activity and other fullscreen apps never block a launch (tests are meant
        to run in the background while the user plays); a fullscreen foreground
        window only produces a warning.

        Scripts that genuinely need foreground (bzrdrive / SendInput drivers) set
        $env:BZR_ALLOW_FOREGROUND_LAUNCH = '1' (the older name
        BZR_ALLOW_LAUNCH_WHILE_BUSY is also honoured).

        Also starts the post-launch foreground watchdog (Start-BZRForegroundWatchdog),
        which covers the launch that follows this call.
    #>
    [CmdletBinding()]
    param()

    $override = ($env:BZR_ALLOW_FOREGROUND_LAUNCH -eq '1') -or ($env:BZR_ALLOW_LAUNCH_WHILE_BUSY -eq '1')
    if (-not $override) {
        $missing = @('OPENSHIM_NEVER_ACTIVATE', 'OPENSHIM_NEVER_CAPTURE_MOUSE' |
            Where-Object { [Environment]::GetEnvironmentVariable($_) -ne '1' })
        if ($missing.Count -gt 0) {
            throw ("Refusing to launch Battlezone: {0} must be '1' in the environment the game inherits, " +
                   "or the test window can steal the user's foreground/mouse. Scripts that truly need foreground " +
                   "set `$env:BZR_ALLOW_FOREGROUND_LAUNCH='1'.") -f ($missing -join ', ')
        }
    }
    [void](Start-BZRForegroundWatchdog)
}

function Stop-BZRGame {
    <#
    .SYNOPSIS
        Shuts the game down without deadlocking the display stack.
    .DESCRIPTION
        Sends WM_CLOSE and waits, so the engine can tear its swap chain down and
        hand the exclusive-fullscreen mode back to the driver. Only escalates to
        TerminateProcess for a process that ignored the close request, which is
        the genuinely-hung case where there is nothing gentler left to try.
        Pass -NoForce for probes that must leave an unresponsive game running
        rather than terminate it. The caller receives an error in that case.

        This is a drop-in replacement for the old
            Get-Process -Name "battlezone98redux" | Stop-Process -Force
        and is safe to call when the game is not running.
    #>
    [CmdletBinding(DefaultParameterSetName = 'ByName')]
    param(
        [Parameter(ParameterSetName = 'ByName')]
        [string[]]$Name = @($script:BZRGameProcessName),
        # Prefer -Id when the caller already holds the process it started:
        # matching by name also catches unrelated instances the harness did not
        # launch, which is how a careless call takes out a bystander.
        [Parameter(ParameterSetName = 'ById', Mandatory)]
        [int[]]$Id,
        # Generous by design: a DX11 fullscreen teardown at 4K can take several
        # seconds, and waiting is always cheaper than a hard restart.
        [int]$TimeoutSeconds = 15,
        [switch]$NoForce,
        # Time for the driver to finish releasing the adapter before the caller
        # launches again. Back-to-back mode-sets are what wedged the stack.
        [int]$SettleMilliseconds = 750
    )

    # Refuse obviously-wrong targets. During the 2026-08-24 investigation a test
    # called this with -Name 'pwsh', which force-killed every PowerShell on the
    # box -- including a harness run that was driving the game at the time. A
    # name-matched kill is blunt enough that it needs a floor.
    if ($PSCmdlet.ParameterSetName -eq 'ByName') {
        $protected = @('pwsh', 'powershell', 'cmd', 'conhost', 'WindowsTerminal',
                       'explorer', 'node', 'code', 'claude', 'opencode')
        foreach ($n in $Name) {
            if ($protected -contains $n) {
                throw ("Stop-BZRGame refuses to name-match '$n': killing every " +
                       "instance would take out unrelated shells and harness runs. " +
                       "Pass -Id if you really mean one specific process.")
            }
        }
    }

    $sawAnyProcess = $false

    $targets = if ($PSCmdlet.ParameterSetName -eq 'ById') {
        @($Id | ForEach-Object { ,@(Get-Process -Id $_ -ErrorAction SilentlyContinue) })
    } else {
        @($Name | ForEach-Object { ,@(Get-Process -Name $_ -ErrorAction SilentlyContinue) })
    }

    foreach ($procs in $targets) {
        $procs = @($procs)
        if ($procs.Count -eq 0) { continue }
        $sawAnyProcess = $true
        $procName = $procs[0].ProcessName

        # Ask first. CloseMainWindow returns $false when the process has no main
        # window yet (still starting up) or has stopped pumping messages; track
        # that so a process that cannot accept WM_CLOSE is not waited on for the
        # full timeout.
        $accepted = $false
        foreach ($p in $procs) {
            try {
                if (-not $p.HasExited -and $p.CloseMainWindow()) { $accepted = $true }
            } catch {
                # Process exited between Get-Process and here; nothing to close.
            }
        }

        $graceMs = if ($accepted -or $NoForce) { $TimeoutSeconds * 1000 } else { 2000 }
        $deadline = (Get-Date).AddMilliseconds($graceMs)

        foreach ($p in $procs) {
            $remaining = [int](($deadline - (Get-Date)).TotalMilliseconds)
            if ($remaining -le 0) { break }
            try { $p.WaitForExit($remaining) | Out-Null } catch { }
        }

        # Escalate only for whatever is still standing.
        foreach ($p in $procs) {
            $p.Refresh()
            if (-not $p.HasExited -and $NoForce) {
                throw ("{0} (pid {1}) is still running after the close request; -NoForce leaves it running." -f $procName, $p.Id)
            }
            try {
                $p.Refresh()
                if ($p.HasExited) { continue }
                $msg = "{0} (pid {1}) ignored WM_CLOSE after {2:N1}s; force-killing. " +
                        "If this recurs, capture the hang rather than looping."
                Write-Warning ($msg -f $procName, $p.Id, ($graceMs / 1000))
                Stop-Process -Id $p.Id -Force -ErrorAction SilentlyContinue
            } catch { }
        }
    }

    if ($sawAnyProcess -and $SettleMilliseconds -gt 0) {
        Start-Sleep -Milliseconds $SettleMilliseconds
    }
}

function Enter-BZRLaunchLock {
    <#
    .SYNOPSIS
        Serializes game launches across every harness process on this machine.
    .DESCRIPTION
        Two agents starting the game at once means two concurrent mode-sets
        against one adapter, which is the worst case for the deadlock above.
        Returns a mutex; pass it to Exit-BZRLaunchLock in a finally block.

        Local\ (not Global\) is deliberate: every harness process runs as the
        same user in the same session, and Global\ needs SeCreateGlobalPrivilege.
    #>
    [CmdletBinding()]
    param([int]$TimeoutSeconds = 1800)

    Assert-BZRSafeToLaunch

    $mutex = New-Object System.Threading.Mutex($false, 'Local\BZROpenShimGameLaunch')
    try {
        if (-not $mutex.WaitOne([TimeSpan]::FromSeconds($TimeoutSeconds))) {
            $mutex.Dispose()
            throw ("Timed out after {0}s waiting for the game-launch lock. " -f $TimeoutSeconds) +
                  "Another harness run is still holding it."
        }
    } catch [System.Threading.AbandonedMutexException] {
        # Expected, and not an error. Neither PowerShell.Exiting nor
        # AppDomain.ProcessExit runs reliably under `pwsh -File`, so the mutex is
        # released by the OS at process death and every normal exit abandons it.
        # We own it now either way; the wait is what mattered.
    }
    return $mutex
}

function Exit-BZRLaunchLock {
    [CmdletBinding()]
    param([Parameter(Mandatory)][AllowNull()]$Mutex)

    if ($null -eq $Mutex) { return }
    try { $Mutex.ReleaseMutex() } catch { }
    try { $Mutex.Dispose() } catch { }
}

function Set-BZROgreWindowed {
    <#
    .SYNOPSIS
        Forces ogre.cfg to windowed mode for the duration of a harness run.
    .DESCRIPTION
        Returns the original file contents so the caller can hand them back to
        Restore-BZROgreConfig in a finally block. Rewrites every render system's
        section, because which one is active depends on -Renderer.

        Windowed is not a cosmetic preference here: it removes the exclusive
        mode-set entirely, which is the half of the deadlock that the graceful
        shutdown in Stop-BZRGame cannot address on its own.
    #>
    [CmdletBinding()]
    param(
        [Parameter(Mandatory)][string]$GameRoot,
        [string]$VideoMode = '1600 x  900 @ 32-bit colour'
    )

    $ogreConfig = Join-Path $GameRoot 'ogre.cfg'
    if (-not (Test-Path -LiteralPath $ogreConfig)) {
        Write-Warning "No ogre.cfg at $ogreConfig; cannot force windowed mode."
        return $null
    }

    $original = [System.IO.File]::ReadAllText($ogreConfig)
    $config = $original -replace '(?m)^Full Screen=Yes\s*$', 'Full Screen=No'
    $config = $config -replace '(?m)^Video Mode=.*$', "Video Mode=$VideoMode"
    [System.IO.File]::WriteAllText($ogreConfig, $config)
    return $original
}

function Restore-BZROgreConfig {
    [CmdletBinding()]
    param(
        [Parameter(Mandatory)][string]$GameRoot,
        [AllowNull()][string]$Original
    )

    if ($null -eq $Original) { return }
    $ogreConfig = Join-Path $GameRoot 'ogre.cfg'
    try {
        [System.IO.File]::WriteAllText($ogreConfig, $Original)
    } catch {
        Write-Warning "Could not restore ogre.cfg at ${ogreConfig}: $_"
    }
}

# ---------------------------------------------------------------------------
# Automatic setup, applied on dot-source.
# ---------------------------------------------------------------------------

# Serialize launches across every harness process without needing a try/finally
# in each of the 15 scripts. Two agents mid-mode-set on one adapter is the worst
# case for the deadlock this file exists to prevent.
#
# The lock is released by the OS when the process exits -- there is deliberately
# no exit handler, because neither PowerShell.Exiting nor AppDomain.ProcessExit
# fires usefully for a script launched with `pwsh -File`.
#
# BZR_LAUNCH_LOCK_HELD guards against self-deadlock when one harness script
# invokes another (run_shim_ab_presentmon.ps1 calls run_live_combat_benchmark.ps1):
# the inner call inherits the variable and skips acquisition, so the outer run
# keeps the single lock for its whole duration.
if (-not $env:BZR_LAUNCH_LOCK_HELD) {
    $global:BZRAutoLock = Enter-BZRLaunchLock
    $env:BZR_LAUNCH_LOCK_HELD = $PID
}

# Opt-in windowed mode: set BZR_FORCE_WINDOWED=1 to strip exclusive fullscreen
# from every harness run in the shell.
#
# Opt-in rather than default on purpose. Windowed removes the exclusive-fullscreen
# mode-set that is one half of the deadlock, but it also changes what a run
# measures -- run_live_combat_benchmark.ps1 reports FPS, and windowed and
# fullscreen are not comparable numbers. Forcing it globally would silently
# invalidate benchmark results. Capture scripts that need windowed for
# CopyFromScreen already set it themselves and are unaffected either way.
#
# Recommended while debugging shim stability; leave unset for benchmark runs.

# Restore first, always: if a previous run left a backup behind it died before
# putting ogre.cfg back -- a crash, or the hard lock this file exists to prevent.
# Recovering on the next start rather than on exit is what makes this safe
# against a freeze, which by definition never runs a finally block.
$script:BZROgreBackupName = 'ogre.cfg.bzrharness-backup'

function Restore-BZROrphanedOgreConfig {
    [CmdletBinding()]
    param([Parameter(Mandatory)][string]$GameRoot)

    $backup = Join-Path $GameRoot $script:BZROgreBackupName
    if (-not (Test-Path -LiteralPath $backup)) { return $false }

    $ogreConfig = Join-Path $GameRoot 'ogre.cfg'
    try {
        Copy-Item -LiteralPath $backup -Destination $ogreConfig -Force
        Remove-Item -LiteralPath $backup -Force
        Write-Warning ("[BZRHarness] Recovered ogre.cfg from $script:BZROgreBackupName -- " +
            "the previous harness run did not exit cleanly.")
        return $true
    } catch {
        Write-Warning "[BZRHarness] Could not recover ogre.cfg from ${backup}: $_"
        return $false
    }
}

# Dot-sourcing runs in the caller's scope, so the caller's $GameRoot parameter is
# directly visible here.
$script:BZRGameRoot = if (Get-Variable -Name GameRoot -ErrorAction SilentlyContinue) {
    (Get-Variable -Name GameRoot).Value
} else { $null }

if ($script:BZRGameRoot -and (Test-Path -LiteralPath $script:BZRGameRoot)) {
    $null = Restore-BZROrphanedOgreConfig -GameRoot $script:BZRGameRoot

    if ($env:BZR_FORCE_WINDOWED -eq '1') {
        $backupPath = Join-Path $script:BZRGameRoot $script:BZROgreBackupName
        $ogrePath = Join-Path $script:BZRGameRoot 'ogre.cfg'
        if (Test-Path -LiteralPath $ogrePath) {
            Copy-Item -LiteralPath $ogrePath -Destination $backupPath -Force
            $null = Set-BZROgreWindowed -GameRoot $script:BZRGameRoot
            Write-Host ("[BZRHarness] BZR_FORCE_WINDOWED=1: ogre.cfg forced to windowed " +
                "(original saved to $script:BZROgreBackupName, restored on next run).")
        }
    }
} elseif ($env:BZR_FORCE_WINDOWED -eq '1') {
    Write-Warning "[BZRHarness] BZR_FORCE_WINDOWED=1 but no usable `$GameRoot in scope; ogre.cfg left alone."
}
