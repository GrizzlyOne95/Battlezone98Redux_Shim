<#
.SYNOPSIS
Runs the pilot flashlight siting probe against a live on-foot pilot.

.DESCRIPTION
Temporarily replaces addon/lcbench/lcbench.lua with the endless pilot fixture,
launches the mission straight from the command line (no shell navigation),
attaches reverse_engineering/probe_pilot_flashlight.js, and restores the
original Lua byte-for-byte in a finally block.

lcbench is used rather than the standalone `pilot` addon because the latter's
terrain material set fails DX11 shader binding and closes the process on the
first frame.
#>
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [int]$ProbeSeconds = 45,
    [int]$AttachDelaySeconds = 12,
    [string]$OutDir = "",
    [switch]$Sweep
)

$ErrorActionPreference = "Stop"
$repoRoot = Split-Path -Parent $PSScriptRoot

if (-not $OutDir) {
    $stamp = Get-Date -Format "yyyyMMdd_HHmmss"
    $OutDir = Join-Path $env:TEMP "bzr-pilot-flashlight-$stamp"
}
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null

$exe = Join-Path $GameRoot "battlezone98redux.exe"
if (-not (Test-Path $exe)) { throw "exe not found: $exe" }

$missionLua = Join-Path $GameRoot "addon\lcbench\lcbench.lua"
$fixture = Join-Path $repoRoot "reverse_engineering\test_missions\pilot_anim_capture\pilot_flashlight_fixture.lua"
$probe = Join-Path $repoRoot "reverse_engineering\probe_pilot_flashlight.js"
foreach ($p in @($missionLua, $fixture, $probe)) {
    if (-not (Test-Path $p)) { throw "missing: $p" }
}

$backup = Join-Path $OutDir "lcbench.lua.orig"
Copy-Item $missionLua $backup -Force
$originalHash = (Get-FileHash $missionLua -Algorithm SHA256).Hash

# Force windowed so the run stays observable and capturable.
$env:BZR_FORCE_WINDOWED = "1"
. (Join-Path $repoRoot "reverse_engineering\BZRHarness.ps1")

$proc = $null
try {
    Copy-Item $fixture $missionLua -Force
    Write-Host "[probe] fixture deployed to $missionLua"

    # Bare basename only: the engine copies the mission argument into a
    # 16-byte buffer, so "addon/lcbench/lcbench.bzn" arrives truncated to
    # "addon/lcbench/l" and the load fails. run_lcwalk_drive.ps1 uses the
    # same bare form.
    $proc = Start-Process -FilePath $exe -ArgumentList "lcbench.bzn" `
        -WorkingDirectory $GameRoot -PassThru
    Write-Host "[probe] launched PID=$($proc.Id)"

    Start-Sleep -Seconds $AttachDelaySeconds
    $proc.Refresh()
    if ($proc.HasExited) { throw "game exited before the probe could attach (exit $($proc.ExitCode))" }

    # Pitch the view while the probe samples, so the log shows whether the
    # pilot's world node (and the FP gun bone) carry look pitch at all. The
    # sweep refuses to move the mouse unless the game owns the foreground
    # window, so an early exit cannot leave it dragging the real cursor.
    $sweepJob = $null
    if ($Sweep) {
        $sweepJob = Start-Job -ArgumentList $proc.Id, $ProbeSeconds -ScriptBlock {
            param($GamePid, $Seconds)
            Add-Type @"
using System;
using System.Runtime.InteropServices;
public static class Sweep {
    [StructLayout(LayoutKind.Sequential)] public struct MOUSEINPUT {
        public int dx; public int dy; public uint mouseData; public uint dwFlags;
        public uint time; public IntPtr dwExtraInfo; }
    [StructLayout(LayoutKind.Sequential)] public struct INPUT {
        public uint type; public MOUSEINPUT mi; }
    [DllImport("user32.dll", SetLastError=true)] public static extern uint SendInput(uint n, INPUT[] p, int cb);
    [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
    public static bool GameHasFocus(uint want) {
        uint got; GetWindowThreadProcessId(GetForegroundWindow(), out got); return got == want; }
    public static void Move(int dx, int dy) {
        INPUT[] a = new INPUT[1];
        a[0].type = 0; a[0].mi.dx = dx; a[0].mi.dy = dy; a[0].mi.dwFlags = 0x0001;
        SendInput(1, a, Marshal.SizeOf(typeof(INPUT))); }
}
"@
            Start-Sleep -Seconds 5
            $deadline = (Get-Date).AddSeconds($Seconds - 8)
            $dy = -12
            while ((Get-Date) -lt $deadline) {
                if ([Sweep]::GameHasFocus([uint32]$GamePid)) {
                    for ($i = 0; $i -lt 10; $i++) {
                        [Sweep]::Move(0, $dy)
                        Start-Sleep -Milliseconds 60
                    }
                    $dy = -$dy
                }
                Start-Sleep -Milliseconds 400
            }
        }
    }

    $probeLog = Join-Path $OutDir "probe.log"
    Write-Host "[probe] attaching for $ProbeSeconds s -> $probeLog"
    & "C:\Users\iestu\bin\bzr-frida.cmd" -p $proc.Id -l $probe -q -t $ProbeSeconds -o $probeLog
    Write-Host "[probe] frida exit=$LASTEXITCODE"
    if ($sweepJob) { Stop-Job $sweepJob -ErrorAction SilentlyContinue; Remove-Job $sweepJob -Force -ErrorAction SilentlyContinue }
}
finally {
    if ($proc -ne $null) {
        try { Stop-BZRGame -Id $proc.Id } catch { Write-Warning "Stop-BZRGame: $_" }
    }
    Copy-Item $backup $missionLua -Force
    $restoredHash = (Get-FileHash $missionLua -Algorithm SHA256).Hash
    if ($restoredHash -ne $originalHash) {
        throw "lcbench.lua restore mismatch: $restoredHash != $originalHash"
    }
    Write-Host "[probe] lcbench.lua restored ($originalHash)"

    # The harness restores ogre.cfg on the *next* dot-source; put it back now so
    # a probe run does not leave the install windowed.
    $ogreBackup = Join-Path $GameRoot 'ogre.cfg.bzrharness-backup'
    if (Test-Path $ogreBackup) {
        Copy-Item $ogreBackup (Join-Path $GameRoot 'ogre.cfg') -Force
        Remove-Item $ogreBackup -Force
        Write-Host "[probe] ogre.cfg restored"
    }

    foreach ($log in @("BZLogger.txt", "BZOgreLogfile.log", "openshim.log")) {
        $src = Join-Path $GameRoot "logs\$log"
        if (Test-Path $src) { Copy-Item $src (Join-Path $OutDir $log) -Force }
    }
    Write-Host "[probe] artifacts in $OutDir"
}
