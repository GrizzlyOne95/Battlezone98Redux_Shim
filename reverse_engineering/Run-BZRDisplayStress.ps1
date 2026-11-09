# Display stress for pre-Workshop release qualification (Docs/RELEASE_QUALIFICATION.md,
# "Display stress"). Drives an ALREADY-RUNNING test game through N cycles of
# Alt-Tab, Alt-Enter, an optional fullscreen/windowed toggle key, and Shift-F9, and
# reports crash / hang / new crash-dump / new crash-log lines per step.
#
# This script never launches the game. Launch it first with the normal harness
# helpers (BZRHarness.ps1: Assert-BZRSafeToLaunch + Start-BZRGameProcess), then
# run this against it. One game process only: refuses to run if more than one exists.
#
# Windows PowerShell 5.1 (BZRWindowInput.ps1 needs System.Drawing).
# Shift-F9 is the editor toggle; its task-mode crash is already a known open
# roadmap item (Docs/ROADMAP_CODE_VALIDATION_20261007.md, item 300), so a failure on
# that step is reported as KNOWN-300 and does not by itself fail the run.
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
      [string]$ReportPath = '')
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

$VK_MENU = 0x12; $VK_SHIFT = 0x10; $VK_TAB = 0x09; $VK_RETURN = 0x0D; $VK_F9 = 0x78

$games = @(Get-Process -Name $script:BZRGameProcessName -ErrorAction SilentlyContinue)
if ($games.Count -eq 0) { throw 'No running game. Launch the test game first via the BZRHarness.ps1 helpers; this script does not launch.' }
if ($games.Count -gt 1) { throw "More than one game process running ($($games.Id -join ', ')); this stress test caps at one." }
$game = $games[0]
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

function Invoke-Step([int]$Cycle, [string]$Name, [scriptblock]$Action) {
    if ($clock.Elapsed.TotalSeconds -gt $HardTimeoutSeconds) { $script:aborted = "hard timeout ${HardTimeoutSeconds}s"; return $false }
    $err = ''
    try { & $Action } catch { $err = $_.Exception.Message }
    Start-Sleep -Milliseconds $StepWaitMs
    $state = Test-GameState
    $evidence = @(Get-NewCrashEvidence)
    $status = if ($err) { 'INPUT-ERROR' } elseif ($state -eq 'exited') { 'CRASH' } elseif ($state -eq 'hang') { 'HANG' } elseif ($evidence.Count) { 'CRASH-LOG' } else { 'ok' }
    if ($Name -eq 'Shift-F9' -and $status -in 'CRASH', 'HANG', 'CRASH-LOG') { $status = "KNOWN-300 ($status)" }
    $detail = (@($err) + $evidence | Where-Object { $_ }) -join ' / '
    $results.Add([pscustomobject]@{ Cycle = $Cycle; Step = $Name; Status = $status; Detail = $detail })
    Write-Host ("[{0,3}] {1,-10} {2} {3}" -f $Cycle, $Name, $status, $detail)
    return ($state -eq 'ok')
}

try {
    $hwnd = Get-BZRClientWindow $procId
    for ($c = 1; $c -le $Cycles; $c++) {
        $steps = @(
            @{ N = 'Alt-Tab';   A = { [BZRStress.Keys]::Chord([byte[]]@($VK_MENU), [byte]$VK_TAB, 120); Start-Sleep -Milliseconds 600; [void][BZRStress.Keys]::Focus($hwnd) } },
            @{ N = 'Alt-Enter'; A = { [void][BZRStress.Keys]::Focus($hwnd); Start-Sleep -Milliseconds 150; [BZRStress.Keys]::Chord([byte[]]@($VK_MENU), [byte]$VK_RETURN, 120) } }
        )
        if ($ToggleVk) { $steps += @{ N = 'Toggle'; A = { [void][BZRStress.Keys]::Focus($hwnd); Start-Sleep -Milliseconds 150; [BZRStress.Keys]::Chord([byte[]]@(), [byte]$ToggleVk, 120) } } }
        $steps += @{ N = 'Shift-F9'; A = { [void][BZRStress.Keys]::Focus($hwnd); Start-Sleep -Milliseconds 150; [BZRStress.Keys]::Chord([byte[]]@($VK_SHIFT), [byte]$VK_F9, 120) } }
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
