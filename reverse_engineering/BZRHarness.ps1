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
if (-not ('BZRProcessLauncher' -as [type])) {
    Add-Type -TypeDefinition @'
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;

public static class BZRProcessLauncher
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    struct STARTUPINFO
    {
        public int cb; public string lpReserved; public string lpDesktop; public string lpTitle;
        public int dwX, dwY, dwXSize, dwYSize, dwXCountChars, dwYCountChars, dwFillAttribute, dwFlags;
        public short wShowWindow, cbReserved2; public IntPtr lpReserved2, hStdInput, hStdOutput, hStdError;
    }
    [StructLayout(LayoutKind.Sequential)]
    struct PROCESS_INFORMATION { public IntPtr hProcess, hThread; public int dwProcessId, dwThreadId; }

    [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
    static extern bool CreateProcessW(string app, string cmd, IntPtr pa, IntPtr ta, bool inherit, uint flags,
        IntPtr env, string cwd, ref STARTUPINFO si, out PROCESS_INFORMATION pi);
    [DllImport("kernel32.dll")] static extern bool CloseHandle(IntPtr h);

    const int STARTF_USESHOWWINDOW = 0x1;

    // CreateProcess with STARTF_USESHOWWINDOW + showCommand (SW_SHOWNOACTIVATE = 4)
    // so the game's first ShowWindow cannot activate the window. Inherits the
    // caller's environment. Returns the new process id.
    public static int Start(string exe, string args, string workingDirectory, short showCommand)
    {
        STARTUPINFO si = new STARTUPINFO();
        si.cb = Marshal.SizeOf(typeof(STARTUPINFO));
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = showCommand;
        PROCESS_INFORMATION pi;
        string cmd = "\"" + exe + "\"" + (string.IsNullOrEmpty(args) ? "" : " " + args);
        if (!CreateProcessW(exe, cmd, IntPtr.Zero, IntPtr.Zero, false, 0, IntPtr.Zero,
                string.IsNullOrEmpty(workingDirectory) ? null : workingDirectory, ref si, out pi))
            throw new System.ComponentModel.Win32Exception(Marshal.GetLastWin32Error());
        CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
        return pi.dwProcessId;
    }
}

public static class BZRForegroundWatchdog
{
    [DllImport("user32.dll")] static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll")] static extern uint GetWindowThreadProcessId(IntPtr hwnd, out uint pid);
    [DllImport("user32.dll")] static extern bool SetForegroundWindow(IntPtr hwnd);
    [DllImport("user32.dll")] static extern bool IsWindow(IntPtr hwnd);
    [DllImport("user32.dll", CharSet = CharSet.Unicode)] static extern int GetClassName(IntPtr hwnd, System.Text.StringBuilder text, int max);
    [DllImport("user32.dll")] static extern void SwitchToThisWindow(IntPtr hwnd, bool fAltTab);
    [DllImport("user32.dll")] static extern bool PostMessage(IntPtr hwnd, uint msg, IntPtr wParam, IntPtr lParam);
    [DllImport("user32.dll")] static extern bool EnumWindows(EnumWindowsProc cb, IntPtr lParam);
    delegate bool EnumWindowsProc(IntPtr hwnd, IntPtr lParam);
    [StructLayout(LayoutKind.Sequential)] struct POINT { public int X, Y; }
    [DllImport("user32.dll")] static extern short GetAsyncKeyState(int vk);
    [DllImport("user32.dll")] static extern bool GetCursorPos(out POINT pt);
    [DllImport("user32.dll")] static extern IntPtr WindowFromPoint(POINT pt);
    const uint WM_CLOSE = 0x0010;
    [DllImport("user32.dll")] static extern bool AttachThreadInput(uint idAttach, uint idAttachTo, bool fAttach);
    [DllImport("kernel32.dll")] static extern uint GetCurrentThreadId();

    static readonly object Gate = new object();
    static readonly List<string> Events = new List<string>();
    static int running = 0;

    public static string LogPath = Path.Combine(Path.GetTempPath(), "bzr_foreground_watchdog.log");

    // "class=<window class> process=<name>" for a window, captured while it is
    // foreground so a later steal can say what the OS took the foreground from.
    static string Describe(IntPtr hwnd, uint pid)
    {
        string cls = "?", proc = "?";
        try { System.Text.StringBuilder sb = new System.Text.StringBuilder(256); if (GetClassName(hwnd, sb, sb.Capacity) > 0) cls = sb.ToString(); } catch { }
        try { if (pid != 0) proc = Process.GetProcessById((int)pid).ProcessName; } catch { }
        return "class=" + cls + " process=" + proc;
    }

    // True when a physical left/right/middle button is down (or was pressed since the
    // last poll) with the cursor over a window owned by the game. PostMessage-driven
    // harness clicks change neither, so they never match.
    static bool PhysicalPressOverGame(string gameName)
    {
        bool pressed = false;
        foreach (int vk in new int[] { 0x01, 0x02, 0x04 })
            if ((GetAsyncKeyState(vk) & 0x8001) != 0) pressed = true;
        if (!pressed) return false;
        POINT pt;
        if (!GetCursorPos(out pt)) return false;
        IntPtr under = WindowFromPoint(pt);
        if (under == IntPtr.Zero) return false;
        uint upid;
        GetWindowThreadProcessId(under, out upid);
        return IsGame(upid, gameName);
    }

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
    // More than maxSteals steals ends the run: WM_CLOSE (never a kill) is posted
    // to the game's windows. A run that keeps stealing must end itself.
    public static bool Start(string gameName, int waitForGameMs, int watchMs, int intervalMs, bool allowAttach, int maxSteals)
    {
        if (Interlocked.CompareExchange(ref running, 1, 0) != 0) return false;
        Thread t = new Thread(delegate() {
            try { Run(gameName, waitForGameMs, watchMs, intervalMs, allowAttach, maxSteals); }
            catch (Exception ex) { Note("watchdog error: " + ex.Message); }
            finally { Interlocked.Exchange(ref running, 0); }
        });
        t.IsBackground = true;
        t.Name = "BZRForegroundWatchdog";
        t.Start();
        return true;
    }

    // Posts WM_CLOSE to every top-level window of one process. Graceful only.
    public static int PostCloseToProcess(int processId)
    {
        int posted = 0;
        EnumWindows(delegate(IntPtr hwnd, IntPtr lp) {
            uint wpid;
            GetWindowThreadProcessId(hwnd, out wpid);
            if (wpid == (uint)processId && PostMessage(hwnd, WM_CLOSE, IntPtr.Zero, IntPtr.Zero)) posted++;
            return true;
        }, IntPtr.Zero);
        return posted;
    }

    // Posts WM_CLOSE to every top-level window owned by the game. Graceful only.
    static int CloseGameWindows(string gameName)
    {
        int posted = 0;
        EnumWindows(delegate(IntPtr hwnd, IntPtr lp) {
            uint wpid;
            GetWindowThreadProcessId(hwnd, out wpid);
            if (IsGame(wpid, gameName) && PostMessage(hwnd, WM_CLOSE, IntPtr.Zero, IntPtr.Zero)) posted++;
            return true;
        }, IntPtr.Zero);
        return posted;
    }

    static void Run(string gameName, int waitForGameMs, int watchMs, int intervalMs, bool allowAttach, int maxSteals)
    {
        bool aborted = false;
        IntPtr previous = IntPtr.Zero;
        string previousDesc = "class=? process=?";
        Stopwatch wait = Stopwatch.StartNew();
        Stopwatch watch = null;
        int reported = 0;
        long lastGamePress = long.MinValue;
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
            else if (Process.GetProcessesByName(gameName).Length == 0) { Note("game exited; reported " + reported + " steal(s)"); return; }

            if (watch != null && PhysicalPressOverGame(gameName)) lastGamePress = Environment.TickCount;
            if (!gameFg)
            {
                if (fg != IntPtr.Zero)
                {
                    if (fg != previous) previousDesc = Describe(fg, pid);
                    previous = fg;
                }
            }
            else if (watch != null && lastGamePress != long.MinValue && unchecked(Environment.TickCount - (int)lastGamePress) < 1000)
            {
                // The user clicked the game window: activation is intentional.
                Note("user activated the game window (intentional); not a steal, focus left alone, watchdog done");
                return;
            }
            else if (watch != null)
            {
                reported++;
                Note("FOREGROUND-STOLEN: game pid " + pid + " took the foreground (previous hwnd 0x" + previous.ToInt64().ToString("X") + " " + previousDesc + ")");
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
                            now = GetForegroundWindow();
                            nowPid = 0; if (now != IntPtr.Zero) GetWindowThreadProcessId(now, out nowPid);
                            Note("AttachThreadInput fallback attempted (attached=" + attached + ", game still foreground=" + IsGame(nowPid, gameName) + ")");
                            if (IsGame(nowPid, gameName))
                            {
                                SwitchToThisWindow(previous, true);
                                Note("SwitchToThisWindow fallback attempted");
                            }
                        }
                    }
                    else Note("foreground restored to previous window");
                }
                if (!aborted && reported > maxSteals)
                {
                    aborted = true;
                    int posted = CloseGameWindows(gameName);
                    Note("aborted run: repeated foreground steals (" + reported + " > " + maxSteals + "); posted WM_CLOSE to " + posted + " game window(s)");
                }
            }
            Thread.Sleep(intervalMs);
        }
    }
}
'@
}

# Audio muting for harness-launched games. Sessions in the Core Audio mixer
# appear only after the game's audio init, so the mute is re-applied every
# ~250 ms until the game exits. Separate namespace/type guard from the block
# above so dot-sourcing twice (or an older already-loaded type) cannot collide.
if (-not ('BZRAudio.GameMute' -as [type])) {
    Add-Type -TypeDefinition @'
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;

namespace BZRAudio
{
    [ComImport, Guid("BCDE0395-E52F-467C-8E3D-C4579291692E")] class MMDeviceEnumerator {}

    [ComImport, Guid("A95664D2-9614-4F35-A746-DE8DB63617E6"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface IMMDeviceEnumerator
    {
        int EnumAudioEndpoints(int dataFlow, int stateMask, out IMMDeviceCollection devices);
        int GetDefaultAudioEndpoint(int dataFlow, int role, out IMMDevice device);
    }

    [ComImport, Guid("0BD7A1BE-7A1A-44DB-8397-CC5392387B5E"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface IMMDeviceCollection
    {
        int GetCount(out int count);
        int Item(int index, out IMMDevice device);
    }

    [ComImport, Guid("D666063F-1587-4E43-81F1-B948E807363F"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface IMMDevice
    {
        int Activate(ref Guid iid, int clsCtx, IntPtr activationParams,
                     [MarshalAs(UnmanagedType.IUnknown)] out object iface);
    }

    [ComImport, Guid("77AA99A0-1BD6-484F-8BC7-2C654C9A9B6F"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface IAudioSessionManager2
    {
        int GetAudioSessionControl(IntPtr guid, int flags, out IntPtr control);
        int GetSimpleAudioVolume(IntPtr guid, int flags, out IntPtr volume);
        int GetSessionEnumerator(out IAudioSessionEnumerator sessions);
    }

    [ComImport, Guid("E2F5BB11-0570-40CA-ACDD-3AA01277DEE8"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface IAudioSessionEnumerator
    {
        int GetCount(out int count);
        int GetSession(int index, [MarshalAs(UnmanagedType.IUnknown)] out object session);
    }

    [ComImport, Guid("bfb7ff88-7239-4fc9-8fa2-07c950be9c6d"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface IAudioSessionControl2
    {
        int GetState(out int state);
        int GetDisplayName(out IntPtr name);
        int SetDisplayName(IntPtr name, IntPtr ctx);
        int GetIconPath(out IntPtr path);
        int SetIconPath(IntPtr path, IntPtr ctx);
        int GetGroupingParam(out Guid param);
        int SetGroupingParam(ref Guid param, IntPtr ctx);
        int RegisterAudioSessionNotification(IntPtr client);
        int UnregisterAudioSessionNotification(IntPtr client);
        int GetSessionIdentifier(out IntPtr id);
        int GetSessionInstanceIdentifier(out IntPtr id);
        int GetProcessId(out uint pid);
    }

    [ComImport, Guid("87CE5498-68D6-44E5-9215-6DA47EF883D8"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface ISimpleAudioVolume
    {
        int SetMasterVolume(float level, ref Guid ctx);
        int GetMasterVolume(out float level);
        int SetMute([MarshalAs(UnmanagedType.Bool)] bool mute, ref Guid ctx);
        int GetMute([MarshalAs(UnmanagedType.Bool)] out bool mute);
    }

    public static class GameMute
    {
        static int running = 0;
        public static string LogPath = Path.Combine(Path.GetTempPath(), "bzr_foreground_watchdog.log");
        static readonly object Gate = new object();
        static readonly List<string> Events = new List<string>();

        static void Note(string text)
        {
            string line = DateTime.Now.ToString("HH:mm:ss.fff") + " " + text;
            lock (Gate) { Events.Add(line); }
            try { File.AppendAllText(LogPath, line + Environment.NewLine); } catch { }
        }

        public static string[] Snapshot() { lock (Gate) { return Events.ToArray(); } }

        // Mutes (or unmutes) every render session owned by pid on every active
        // render endpoint. Returns the number of sessions changed; 0 when the
        // process has no audio session (yet). Never throws.
        public static int Set(uint pid, bool mute)
        {
            int changed = 0;
            try
            {
                IMMDeviceEnumerator enumerator = (IMMDeviceEnumerator)new MMDeviceEnumerator();
                IMMDeviceCollection devices;
                if (enumerator.EnumAudioEndpoints(0 /*eRender*/, 1 /*DEVICE_STATE_ACTIVE*/, out devices) != 0) return 0;
                int deviceCount;
                devices.GetCount(out deviceCount);
                Guid iid = typeof(IAudioSessionManager2).GUID;
                Guid ctx = Guid.Empty;
                for (int d = 0; d < deviceCount; ++d)
                {
                    try
                    {
                        IMMDevice device;
                        if (devices.Item(d, out device) != 0) continue;
                        object managerObj;
                        if (device.Activate(ref iid, 23 /*CLSCTX_ALL*/, IntPtr.Zero, out managerObj) != 0) continue;
                        IAudioSessionManager2 manager = (IAudioSessionManager2)managerObj;
                        IAudioSessionEnumerator sessions;
                        if (manager.GetSessionEnumerator(out sessions) != 0) continue;
                        int count;
                        sessions.GetCount(out count);
                        for (int i = 0; i < count; ++i)
                        {
                            object sessionObj;
                            if (sessions.GetSession(i, out sessionObj) != 0) continue;
                            IAudioSessionControl2 control = sessionObj as IAudioSessionControl2;
                            if (control == null) continue;
                            uint owner;
                            if (control.GetProcessId(out owner) != 0 || owner != pid) continue;
                            ISimpleAudioVolume volume = sessionObj as ISimpleAudioVolume;
                            if (volume == null) continue;
                            if (volume.SetMute(mute, ref ctx) == 0) ++changed;
                        }
                    }
                    catch { }
                }
            }
            catch { }
            return changed;
        }

        // Waits up to waitForGameMs for the game, then re-applies the mute every
        // intervalMs until the game exits. Logs the first success per pid.
        public static bool Start(string gameName, int waitForGameMs, int intervalMs)
        {
            if (Interlocked.CompareExchange(ref running, 1, 0) != 0) return false;
            Thread t = new Thread(delegate() {
                try { Run(gameName, waitForGameMs, intervalMs); }
                catch (Exception ex) { Note("audio mute error: " + ex.Message); }
                finally { Interlocked.Exchange(ref running, 0); }
            });
            t.IsBackground = true;
            t.Name = "BZRGameAudioMute";
            t.SetApartmentState(ApartmentState.MTA);
            t.Start();
            return true;
        }

        static void Run(string gameName, int waitForGameMs, int intervalMs)
        {
            HashSet<int> logged = new HashSet<int>();
            Stopwatch wait = Stopwatch.StartNew();
            bool seen = false;
            while (true)
            {
                Process[] procs = Process.GetProcessesByName(gameName);
                if (procs.Length == 0)
                {
                    if (seen) { Note("audio mute: game exited"); return; }
                    if (wait.ElapsedMilliseconds > waitForGameMs) return;
                }
                else
                {
                    seen = true;
                    foreach (Process p in procs)
                    {
                        int n = Set((uint)p.Id, true);
                        if (n > 0 && logged.Add(p.Id)) Note("muted " + n + " audio session(s) for pid " + p.Id);
                        p.Dispose();
                    }
                }
                Thread.Sleep(intervalMs);
            }
        }
    }
}
'@
}

function Start-BZRGameAudioMute {
    <#
    .SYNOPSIS
        Keeps every audio session of the harness-launched game muted.
    .DESCRIPTION
        Background thread. Waits up to 60 s for the game process, then mutes all
        Core Audio render sessions it owns (all active render endpoints) every
        250 ms until it exits, because sessions only appear after the game's
        audio init. The first success is logged ("muted N audio session(s) for
        pid X") to %TEMP%\bzr_foreground_watchdog.log and Get-BZRForegroundWatchdogLog.
        On by default; set BZR_GAME_AUDIO=1 to leave the game audible.
    #>
    [CmdletBinding()]
    param([int]$WaitForGameSeconds = 60, [int]$PollMilliseconds = 250)
    if ($env:BZR_GAME_AUDIO -eq '1') { return $false }
    [BZRAudio.GameMute]::Start($script:BZRGameProcessName, $WaitForGameSeconds * 1000, $PollMilliseconds)
}

function Set-BZRProcessAudioMute {
    [CmdletBinding()]
    param([Parameter(Mandatory)][int]$ProcessId, [bool]$Mute = $true)
    [BZRAudio.GameMute]::Set([uint32]$ProcessId, $Mute)
}

function Start-BZRForegroundWatchdog {
    <#
    .SYNOPSIS
        Detects (and undoes) the game taking the foreground right after launch.
    .DESCRIPTION
        Background thread, so the caller is not blocked. Waits up to 60 s for the
        game process to appear, then polls GetForegroundWindow every
        100 ms for -WatchSeconds. If the foreground ever belongs to the game it logs a loud
        FOREGROUND-STOLEN line (Get-BZRForegroundWatchdogLog; also appended to
        %TEMP%\bzr_foreground_watchdog.log) and calls SetForegroundWindow on the
        previous foreground window. The AttachThreadInput fallback runs only when
        plain SetForegroundWindow failed (on by default; BZR_WATCHDOG_NO_ATTACH=1
        turns it off), followed by SwitchToThisWindow if the game still holds it.
        More than -MaxSteals steals (default 2) ends the run: WM_CLOSE (never
        TerminateProcess) is posted to the game's windows and "aborted run:
        repeated foreground steals" is logged.
        Disable with BZR_NO_FOREGROUND_WATCHDOG=1.
    #>
    [CmdletBinding()]
    param(
        [int]$WaitForGameSeconds = 60,
        [int]$WatchSeconds = 900,
        [int]$PollMilliseconds = 100,
        [int]$MaxSteals = 2
    )
    if ($env:BZR_NO_FOREGROUND_WATCHDOG -eq '1') { return $false }
    [BZRForegroundWatchdog]::Start($script:BZRGameProcessName, $WaitForGameSeconds * 1000,
        $WatchSeconds * 1000, $PollMilliseconds, ($env:BZR_WATCHDOG_NO_ATTACH -ne '1'), $MaxSteals)
}

function Get-BZRForegroundWatchdogLog {
    [CmdletBinding()]
    param()
    @([BZRForegroundWatchdog]::Snapshot()) + @([BZRAudio.GameMute]::Snapshot()) | Sort-Object
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
    param(
        # Multi-client launchers (BZRCoopSession) start several games on purpose.
        [switch]$AllowRunning
    )

    # Stop-BZRGame never force-kills, so a game that ignored WM_CLOSE is still
    # alive. Launching on top of it is how a wedged display stack happens.
    if (-not $AllowRunning) {
        $running = @(Get-Process -Name $script:BZRGameProcessName -ErrorAction SilentlyContinue)
        if ($running.Count -gt 0) {
            throw ("Refusing to launch Battlezone: {0} already running (pid {1}). Stop-BZRGame never " +
                   "force-kills; close it by hand or wait for it to exit.") -f $script:BZRGameProcessName, (($running | ForEach-Object { $_.Id }) -join ', ')
        }
    }

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
    [void](Start-BZRGameAudioMute)
}

function Start-BZRGameProcess {
    <#
    .SYNOPSIS
        Starts the game via CreateProcess with SW_SHOWNOACTIVATE.
    .DESCRIPTION
        Start-Process cannot set STARTUPINFO.wShowWindow without also going
        through ShellExecute, and the game's first ShowWindow(SW_SHOW*) call is
        replaced by the STARTUPINFO value, so an ordinary launch activates the
        window. This helper sets STARTF_USESHOWWINDOW + SW_SHOWNOACTIVATE
        (-WindowStyle Hidden = SW_HIDE, Minimized = SW_SHOWMINNOACTIVE). The
        environment is inherited. Drop-in for the
            Start-Process -FilePath <exe> -ArgumentList <args> -WorkingDirectory <dir> [-PassThru]
        form: array arguments are joined with spaces, exactly like Start-Process.
    #>
    [CmdletBinding()]
    param(
        [Parameter(Mandatory)][string]$FilePath,
        [object]$ArgumentList = @(),
        [string]$WorkingDirectory = '',
        [ValidateSet('Normal', 'Hidden', 'Minimized', 'Maximized')][string]$WindowStyle = 'Normal',
        [switch]$PassThru
    )
    $show = switch ($WindowStyle) { 'Hidden' { 0 } 'Minimized' { 7 } default { 4 } }
    $argText = (@($ArgumentList) | Where-Object { $_ -ne $null }) -join ' '
    $processId = [BZRProcessLauncher]::Start($FilePath, $argText, $WorkingDirectory, [int16]$show)
    if ($PassThru) { Get-Process -Id $processId }
}

function Stop-BZRGame {
    <#
    .SYNOPSIS
        Shuts the game down without deadlocking the display stack. Never kills it.
    .DESCRIPTION
        Posts WM_CLOSE to every top-level window of the game and re-posts it every
        5 s for up to -TimeoutSeconds (default 60), so the engine can tear its swap
        chain down and hand the exclusive-fullscreen mode back to the driver.
        A game that still ignores the request is LEFT RUNNING: the function logs
        "game ignored WM_CLOSE; left running (never force-kill)" and writes an
        error. Force-killing a process that owns the D3D device can hard-lock the
        workstation (AGENTS.md). Callers must not launch the next run while the
        process exists; Assert-BZRSafeToLaunch enforces that.

        -Force terminates a non-responsive process and exists for the rare manual
        case only. No script in reverse_engineering/ or scripts/ may pass it.
        -NoForce is accepted for old callers and is now the default behaviour.

        Safe to call when the game is not running.
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
        [int]$TimeoutSeconds = 60,
        [switch]$NoForce,
        [switch]$Force,
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
                throw ("Stop-BZRGame refuses to name-match '$n': closing every " +
                       "instance would take out unrelated shells and harness runs. " +
                       "Pass -Id if you really mean one specific process.")
            }
        }
    }

    $sawAnyProcess = $false
    $leftRunning = @()

    $targets = if ($PSCmdlet.ParameterSetName -eq 'ById') {
        @($Id | ForEach-Object { ,@(Get-Process -Id $_ -ErrorAction SilentlyContinue) })
    } else {
        @($Name | ForEach-Object { ,@(Get-Process -Name $_ -ErrorAction SilentlyContinue) })
    }

    $canPostAll = [bool]([BZRForegroundWatchdog].GetMethod('PostCloseToProcess'))
    $deadline = (Get-Date).AddSeconds($TimeoutSeconds)
    $alive = @()
    foreach ($procs in $targets) { $alive += @($procs) }
    if ($alive.Count -gt 0) { $sawAnyProcess = $true }

    while ($true) {
        # (Re-)ask every 5 s. CloseMainWindow covers a stale type without the helper.
        foreach ($p in $alive) {
            try {
                if ($canPostAll) { [void][BZRForegroundWatchdog]::PostCloseToProcess($p.Id) }
                elseif (-not $p.HasExited) { [void]$p.CloseMainWindow() }
            } catch { }
        }
        $sliceEnd = [DateTime]::Now.AddSeconds(5)
        foreach ($p in $alive) {
            $remaining = [int][Math]::Max(0, ([DateTime]$sliceEnd - (Get-Date)).TotalMilliseconds)
            try { [void]$p.WaitForExit($remaining) } catch { }
        }
        $alive = @($alive | Where-Object { try { $_.Refresh(); -not $_.HasExited } catch { $false } })
        if ($alive.Count -eq 0 -or (Get-Date) -ge $deadline) { break }
    }

    foreach ($p in $alive) {
        if ($Force) {
            Write-Warning ("{0} (pid {1}) ignored WM_CLOSE for {2}s; -Force terminating (manual use only)." -f $p.ProcessName, $p.Id, $TimeoutSeconds)
            Stop-Process -Id $p.Id -Force -ErrorAction SilentlyContinue
        } else {
            Write-Warning ("game ignored WM_CLOSE; left running (never force-kill): {0} pid {1}" -f $p.ProcessName, $p.Id)
            $leftRunning += $p.Id
        }
    }

    if ($sawAnyProcess -and $SettleMilliseconds -gt 0) {
        Start-Sleep -Milliseconds $SettleMilliseconds
    }

    if ($leftRunning.Count -gt 0) {
        Write-Error ("game ignored WM_CLOSE for {0}s; left running (never force-kill): pid {1}. Do not launch another run until it exits." -f $TimeoutSeconds, ($leftRunning -join ', '))
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

    Assert-BZRSafeToLaunch -AllowRunning

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
