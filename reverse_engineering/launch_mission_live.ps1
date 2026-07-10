param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string]$MissionArgs = "mods/3686673790/misn03.bzn",
    [int]$SpaceRetryWindowSeconds = 25,
    [int]$SpaceRetryIntervalMs = 500,
    [switch]$KillExisting
)

$ErrorActionPreference = "Stop"

Add-Type @"
using System;
using System.Runtime.InteropServices;
public static class LiveInput {
    public const int SW_RESTORE = 9;
    public const ushort VK_SPACE = 0x20;
    public const uint KEYEVENTF_KEYUP = 0x0002;
    public const uint INPUT_KEYBOARD = 1;
    [StructLayout(LayoutKind.Sequential)] public struct INPUT { public uint type; public InputUnion U; }
    [StructLayout(LayoutKind.Explicit)]  public struct InputUnion { [FieldOffset(0)] public KEYBDINPUT ki; }
    [StructLayout(LayoutKind.Sequential)] public struct KEYBDINPUT { public ushort wVk; public ushort wScan; public uint dwFlags; public uint time; public IntPtr dwExtraInfo; }
    [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int n);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
    [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr h);
    [DllImport("user32.dll", SetLastError=true)] private static extern uint SendInput(uint n, INPUT[] p, int cb);
    public static bool Space() {
        INPUT[] a = new INPUT[2];
        a[0].type = INPUT_KEYBOARD; a[0].U.ki.wVk = VK_SPACE;
        a[1].type = INPUT_KEYBOARD; a[1].U.ki.wVk = VK_SPACE; a[1].U.ki.dwFlags = KEYEVENTF_KEYUP;
        return SendInput(2, a, Marshal.SizeOf(typeof(INPUT))) == 2;
    }
}
"@

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$bzLogger = Join-Path $GameRoot "BZLogger.txt"
if (-not (Test-Path $gameExe)) { throw "exe not found: $gameExe" }

if ($KillExisting) {
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue | Stop-Process -Force
    Start-Sleep -Seconds 2
}

$preLen = 0L
if (Test-Path $bzLogger) { $preLen = (Get-Item $bzLogger).Length }

Write-Host "Launching: $gameExe $MissionArgs"
$proc = Start-Process -FilePath $gameExe -ArgumentList $MissionArgs -WorkingDirectory $GameRoot -PassThru
Write-Host "PID=$($proc.Id)"

# wait for main window
$deadline = (Get-Date).AddSeconds(20)
while ((Get-Date) -lt $deadline -and -not $proc.HasExited) {
    $proc.Refresh()
    if ($proc.MainWindowHandle -ne 0) { break }
    Start-Sleep -Milliseconds 200
}

function Activate {
    param($p)
    $p.Refresh()
    if ($p.MainWindowHandle -ne 0) {
        [void][LiveInput]::ShowWindow($p.MainWindowHandle, 9)
        [void][LiveInput]::BringWindowToTop($p.MainWindowHandle)
        [void][LiveInput]::SetForegroundWindow($p.MainWindowHandle)
        try { (New-Object -ComObject WScript.Shell).AppActivate($p.Id) | Out-Null } catch {}
    }
}

# Space-skip the load VO, watching BZLogger for the cue.
$off = $preLen
$voSeen = $false; $skipDone = $false
$stop = (Get-Date).AddSeconds($SpaceRetryWindowSeconds)
$nextSpace = Get-Date
while ((Get-Date) -lt $stop -and -not $proc.HasExited -and -not $skipDone) {
    if (Test-Path $bzLogger) {
        $len = (Get-Item $bzLogger).Length
        if ($len -gt $off) {
            $fs = [System.IO.File]::Open($bzLogger,'Open','Read','ReadWrite')
            try {
                [void]$fs.Seek($off,'Begin')
                $sr = New-Object System.IO.StreamReader($fs)
                $txt = $sr.ReadToEnd(); $sr.Dispose()
            } finally { $fs.Dispose() }
            $off = $len
            if ($txt -match 'Waiting For VO') { $voSeen = $true }
            if ($txt -match 'Stopping load voice due to space keypress') { $skipDone = $true }
            if ($txt -match 'VO complete' -or $txt -match 'First Frame after' -or $txt -match 'Game Simulation Initialized after') { $skipDone = $true }
        }
    }
    if ($voSeen -and (Get-Date) -ge $nextSpace) {
        Activate $proc
        [void][LiveInput]::Space()
        $nextSpace = (Get-Date).AddMilliseconds($SpaceRetryIntervalMs)
    }
    Start-Sleep -Milliseconds 100
}

Start-Sleep -Seconds 2
$proc.Refresh()
Write-Host "vo_seen=$voSeen skip_done=$skipDone has_exited=$($proc.HasExited) pid=$($proc.Id)"
Write-Host "LEFT RUNNING. Attach probes to PID $($proc.Id)."
