<#
.SYNOPSIS
    Live repro for the HoverCraft turbo-sound stop bug (HoverCraft Turbo Sound Stop Guard).
.DESCRIPTION
    Launches a mission windowed, finds the player's hover craft in the Wingman
    pool, and cycles turbo by holding/releasing the throttle key. After every
    sample it checks that the craft's cached thrust loop (+0x2C0) is still in
    the engine's live sound list (head [0x00915598], next at +0x00).

    Stock behaviour with an ODF whose soundThrust == soundTurbo (ISDFC ivmisl):
    the first turbo stop frees the thrust loop by name, so +0x2C0 dangles
    ("DANGLING" rows) and the next SetSoundParams writes into freed heap.
    With the guard installed, +0x2C0 stays live and openshim.log carries
    [SNDFIX] lines.

    GOG Redux 2.2.301 addresses only (pool vtable, list head). Takes keyboard
    focus while it runs.
#>
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string]$Mission = "isdfms01.bzn",
    [string]$OutputRoot = (Join-Path $env:TEMP "bzr_turbo_sound_repro"),
    [int]$Cycles = 8,
    [int]$HoldSeconds = 3,
    [int]$ReleaseSeconds = 2,
    # Scancodes held during the "hold" phase. Default input.map on this rig:
    # Q = throttle_up, W = turbo.
    [int[]]$HoldScanCodes = @(0x10, 0x11),
    # Poke (default) needs no input focus: at the start of each "hold" phase it
    # writes the smoothed throttle at craft+0x2BC above the turbo gate (1.0 at
    # [0x008A2604]); HoverCraft::UpdateSounds starts the turbo loop, the value
    # eases back toward the idle target at 2.0/s, and the turbo-stop branch
    # runs as it drops through the gate. Keys mode drives the real controls
    # and only works when the game window can take the foreground.
    [ValidateSet('Poke', 'Keys')][string]$Mode = 'Poke',
    [single]$PokeThrottle = 1.8
)

$ErrorActionPreference = "Stop"
. (Join-Path $PSScriptRoot "BZRHarness.ps1")

Add-Type @"
using System;
using System.Runtime.InteropServices;
public static class TurboRepro {
    [DllImport("kernel32.dll")] public static extern IntPtr OpenProcess(int a, bool i, int pid);
    [DllImport("kernel32.dll")] public static extern bool ReadProcessMemory(IntPtr h, IntPtr a, byte[] b, int n, out int r);
    [DllImport("kernel32.dll")] public static extern bool CloseHandle(IntPtr h);
    [DllImport("kernel32.dll")] static extern bool WriteProcessMemory(IntPtr h, IntPtr a, byte[] b, int n, out int w);
    public static bool WriteF32(IntPtr h, long a, float v) { int w; var b = BitConverter.GetBytes(v); return WriteProcessMemory(h, (IntPtr)a, b, 4, out w) && w == 4; }
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
    [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int n);
    [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll")] static extern void keybd_event(byte vk, byte scan, uint flags, IntPtr extra);
    // A background process may not take the foreground; a synthetic ALT tap
    // satisfies the foreground-lock rule so SetForegroundWindow succeeds.
    public static bool Focus(IntPtr h) {
        if (h == IntPtr.Zero) return false;
        if (GetForegroundWindow() == h) return true;
        keybd_event(0x12, 0, 0, IntPtr.Zero); keybd_event(0x12, 0, 2, IntPtr.Zero);
        ShowWindow(h, 9); SetForegroundWindow(h);
        return GetForegroundWindow() == h;
    }
    [StructLayout(LayoutKind.Sequential)] public struct KEYBDINPUT { public ushort wVk; public ushort wScan; public uint dwFlags; public uint time; public IntPtr extra; }
    [StructLayout(LayoutKind.Explicit)] public struct INPUTU { [FieldOffset(0)] public KEYBDINPUT ki; [FieldOffset(0)] public long pad0; [FieldOffset(8)] public long pad1; [FieldOffset(16)] public long pad2; }
    [StructLayout(LayoutKind.Sequential)] public struct INPUT { public uint type; public INPUTU u; }
    [DllImport("user32.dll")] static extern uint SendInput(uint n, INPUT[] i, int cb);
    public static void Key(ushort scan, bool up) {
        var a = new INPUT[1]; a[0].type = 1; a[0].u.ki.wScan = scan; a[0].u.ki.dwFlags = 0x0008u | (up ? 0x0002u : 0u);
        SendInput(1, a, Marshal.SizeOf(typeof(INPUT)));
    }
    public static byte[] Read(IntPtr h, long addr, int n) {
        var b = new byte[n]; int r; if (!ReadProcessMemory(h, (IntPtr)addr, b, n, out r) || r != n) return null; return b;
    }
    public static uint U32(IntPtr h, long a) { var b = Read(h, a, 4); return b == null ? 0 : BitConverter.ToUInt32(b, 0); }
    public static float F32(IntPtr h, long a) { var b = Read(h, a, 4); return b == null ? float.NaN : BitConverter.ToSingle(b, 0); }
    // Wingman vtable 0x0088A464; player craft owner (+0xF4) has flag 0x10 at +0x14.
    public static uint FindPlayerCraft(IntPtr h) {
        const long lo = 0x02900000, hi = 0x02C00000; const int chunk = 0x10000;
        for (long a = lo; a < hi; a += chunk) {
            var b = Read(h, a, chunk); if (b == null) continue;
            for (int i = 0; i < chunk; i += 0x20) {
                if (BitConverter.ToUInt32(b, i) != 0x0088A464u) continue;
                uint obj = (uint)(a + i); uint owner = U32(h, obj + 0xF4);
                if (owner != 0 && (U32(h, owner + 0x14) & 0x10u) != 0) return obj;
            }
        }
        return 0;
    }
    public static bool SoundLive(IntPtr h, uint snd) {
        if (snd == 0) return true;
        uint p = U32(h, 0x00915598); int n = 0;
        while (p != 0 && n++ < 4096) { if (p == snd) return true; p = U32(h, p); }
        return false;
    }
}
"@

New-Item -ItemType Directory -Force -Path $OutputRoot | Out-Null
$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$samples = Join-Path $OutputRoot "samples.csv"
$env:BZR_FORCE_WINDOWED = "1"
$mutex = $null; $ogre = $null; $gamePid = 0; $handle = [IntPtr]::Zero
$dangling = 0; $turboStops = 0

try {
    $mutex = Enter-BZRLaunchLock
    if (Get-Process battlezone98redux -ErrorAction SilentlyContinue) { throw "game already running; not touching it" }
    $ogre = Set-BZROgreWindowed -GameRoot $GameRoot
    $t0 = Get-Date
    $r = Invoke-CimMethod -ClassName Win32_Process -MethodName Create -Arguments @{
        CommandLine = '"' + $gameExe + '" ' + $Mission; CurrentDirectory = $GameRoot }
    Write-Host "[turbo] launched $Mission (launcher pid $($r.ProcessId))"

    # Follow the re-exec'd instance, then wait for the player craft to exist.
    $craft = 0; $deadline = (Get-Date).AddSeconds(120)
    while ((Get-Date) -lt $deadline -and $craft -eq 0) {
        Start-Sleep -Milliseconds 1000
        $game = @(Get-Process battlezone98redux -ErrorAction SilentlyContinue |
            Where-Object { $_.StartTime -ge $t0.AddSeconds(-2) } | Sort-Object StartTime -Descending)
        if ($game.Count -eq 0) { continue }
        if ($game[0].Id -ne $gamePid) {
            if ($handle -ne [IntPtr]::Zero) { [TurboRepro]::CloseHandle($handle) | Out-Null }
            $gamePid = $game[0].Id; $handle = [TurboRepro]::OpenProcess(0x0438, $false, $gamePid)
        }
        # Space skips the load VO; harmless once in game.
        [TurboRepro]::Focus($game[0].MainWindowHandle) | Out-Null
        [TurboRepro]::Key(0x39, $false); Start-Sleep -Milliseconds 60; [TurboRepro]::Key(0x39, $true)
        $craft = [TurboRepro]::FindPlayerCraft($handle)
    }
    if ($craft -eq 0) { throw "player hover craft not found" }
    Write-Host ("[turbo] player craft 0x{0:X8}" -f $craft)
    Start-Sleep -Seconds 3

    "t,phase,throttle,thrust,turbo,thrustLive" | Set-Content -LiteralPath $samples
    $prevTurbo = 0
    for ($c = 0; $c -lt $Cycles; $c++) {
        foreach ($phase in @('hold', 'release')) {
            $proc = Get-Process -Id $gamePid -ErrorAction SilentlyContinue
            if (-not $proc) { throw "game exited during cycle $c" }
            if ($Mode -eq 'Keys') {
                if (-not [TurboRepro]::Focus($proc.MainWindowHandle)) { Write-Warning "[turbo] game window is not foreground; input may be lost" }
                foreach ($sc in $HoldScanCodes) { [TurboRepro]::Key([uint16]$sc, ($phase -eq 'release')) }
            } elseif ($phase -eq 'hold') {
                if (-not [TurboRepro]::WriteF32($handle, $craft + 0x2BC, $PokeThrottle)) { throw "WriteProcessMemory failed" }
            }
            $end = (Get-Date).AddSeconds($(if ($phase -eq 'hold') { $HoldSeconds } else { $ReleaseSeconds }))
            while ((Get-Date) -lt $end) {
                Start-Sleep -Milliseconds 50
                if ($Mode -eq 'Keys' -and $phase -eq 'hold') { foreach ($sc in $HoldScanCodes) { [TurboRepro]::Key([uint16]$sc, $false) } }
                $thr = [TurboRepro]::F32($handle, $craft + 0x2BC)
                $s0 = [TurboRepro]::U32($handle, $craft + 0x2C0)
                $s1 = [TurboRepro]::U32($handle, $craft + 0x2C4)
                $live = [TurboRepro]::SoundLive($handle, $s0)
                if ($prevTurbo -ne 0 -and $s1 -eq 0) { $turboStops++ }
                $prevTurbo = $s1
                if (-not $live) { $dangling++ }
                $t = [math]::Round(((Get-Date) - $t0).TotalSeconds, 1)
                Add-Content -LiteralPath $samples -Value ("{0},{1},{2:F3},0x{3:X8},0x{4:X8},{5}" -f $t, $phase, $thr, $s0, $s1, $(if ($live) { 'live' } else { 'DANGLING' }))
            }
        }
    }
    if ($Mode -eq 'Keys') { foreach ($sc in $HoldScanCodes) { [TurboRepro]::Key([uint16]$sc, $true) } }
}
finally {
    if ($handle -ne [IntPtr]::Zero) { [TurboRepro]::CloseHandle($handle) | Out-Null }
    if ($gamePid -ne 0 -and (Get-Process -Id $gamePid -ErrorAction SilentlyContinue)) {
        try { Stop-BZRGame -Id $gamePid } catch { Write-Warning "Stop-BZRGame: $_" }
    }
    Restore-BZROgreConfig -GameRoot $GameRoot -Original $ogre
    foreach ($log in @("BZLogger.txt", "openshim.log")) {
        $src = Join-Path $GameRoot "logs\$log"
        if (Test-Path -LiteralPath $src) { Copy-Item -LiteralPath $src -Destination (Join-Path $OutputRoot $log) -Force }
    }
    if ($mutex) { Exit-BZRLaunchLock -Mutex $mutex }
}

Write-Host "[turbo] turbo stops observed: $turboStops; samples with +0x2C0 dangling: $dangling"
Write-Host "[turbo] samples: $samples"
