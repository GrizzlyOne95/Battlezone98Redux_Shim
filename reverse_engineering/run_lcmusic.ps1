<#
.SYNOPSIS
Live check for OpenShimSetMusicTrack / OpenShimStopMusic.

.DESCRIPTION
Takes the machine-wide launch lock, deploys this worktree's Release build with
scripts/Deploy-OpenShim.ps1, deploys the lcbench world plus the lcbench_music
fixture (music.lua), launches lcbench.bzn windowed, and waits for the fixture's
DONE marker.

While the mission runs it samples four Redux 2.2.301 music globals once every
~0.5 s through ReadProcessMemory, so each TRUE the fixture prints can be
checked against what the engine actually did:
  0x008E75F4 selected track   0x008E75F8 OggManager slot (-1 = none)
  0x00915580 playing flag     0x00915588 paused flag
These addresses are GOG 2.2.301 facts used only as test evidence; the shim
itself never reads them.

Expected on a working build (fixture lines, then sampled state after each):
  STEP SET07  result=true   -> track 7, slot >= 0, playing 1
  STEP SAME07 result=true   -> unchanged, no new "Starting Music Playback"
  STEP MISS98 result=false  -> still track 7, playing 1
  STEP STOP   result=true   -> slot -1, playing 0
  STEP STOP2  result=true   -> unchanged
  STEP SET12  result=true   -> track 12, slot >= 0, playing 1

.EXAMPLE
pwsh -File reverse_engineering/run_lcmusic.ps1
#>
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateRange(30, 400)]
    [int]$RunSeconds = 180,
    [string]$OutputRoot = ""
)

$ErrorActionPreference = "Stop"
$repoRoot = Split-Path -Parent $PSScriptRoot

$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
if (-not $OutputRoot) {
    $OutputRoot = Join-Path $env:TEMP "bzr-lcmusic-$stamp"
}
New-Item -ItemType Directory -Force -Path $OutputRoot | Out-Null

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$worldSource = Join-Path $repoRoot "reverse_engineering\test_missions\live_combat_scaling"
$fixtureRoot = Join-Path $repoRoot "reverse_engineering\test_missions\lcbench_music"
$pluginDll = Join-Path $GameRoot "plugins\openshim.dll"
$builtPlugin = Join-Path $repoRoot "bin\Release\plugins\openshim.dll"

foreach ($p in @($gameExe, $worldSource, $fixtureRoot, $builtPlugin)) {
    if (-not (Test-Path -LiteralPath $p)) { throw "missing: $p" }
}

$env:BZR_FORCE_WINDOWED = "1"
. (Join-Path $repoRoot "reverse_engineering\BZRHarness.ps1")

if (-not ("LcMusicMem" -as [type])) {
    Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public static class LcMusicMem {
    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr OpenProcess(int access, bool inherit, int pid);
    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern bool ReadProcessMemory(IntPtr h, IntPtr addr, byte[] buf, int size, out IntPtr read);
    [DllImport("kernel32.dll")]
    public static extern bool CloseHandle(IntPtr h);
    public static int ReadInt(IntPtr h, long addr) {
        byte[] b = new byte[4]; IntPtr n;
        if (!ReadProcessMemory(h, new IntPtr(addr), b, 4, out n)) return int.MinValue;
        return BitConverter.ToInt32(b, 0);
    }
}
"@
}

$deploy = @()
foreach ($src in (Get-ChildItem -LiteralPath $worldSource -File)) {
    $deploy += @{ Source = $src.FullName; Name = $src.Name }
}
$deploy += @{ Source = (Join-Path $fixtureRoot "music.lua"); Name = "lcbench.lua" }

$missionBackup = Join-Path $OutputRoot "pre_live"
New-Item -ItemType Directory -Force -Path $missionBackup | Out-Null
$createdMissionRoot = $false
$deployedNames = @()
$bzLogger = Join-Path $GameRoot "logs\BZLogger.txt"
$samplesPath = Join-Path $OutputRoot "music_globals.csv"
$mutex = $null
$gamePid = 0

try {
    $mutex = Enter-BZRLaunchLock
    # Not every launcher takes the lock. Wait out a run already in progress
    # rather than deploying over it; never stop a game this script did not start.
    $idleDeadline = (Get-Date).AddMinutes(15)
    while (Get-Process battlezone98redux -ErrorAction SilentlyContinue) {
        if ((Get-Date) -gt $idleDeadline) {
            throw "the game has been running for 15 minutes under another session; not touching it"
        }
        Start-Sleep -Seconds 5
    }

    & (Join-Path $repoRoot "scripts\Deploy-OpenShim.ps1") -GameDir $GameRoot | Out-Host
    $hashBefore = (Get-FileHash -LiteralPath $pluginDll -Algorithm SHA256).Hash
    $hashBuilt = (Get-FileHash -LiteralPath $builtPlugin -Algorithm SHA256).Hash
    Write-Host "[lcmusic] openshim.dll deployed: $hashBefore (built: $hashBuilt)"
    if ($hashBefore -ne $hashBuilt) { throw "deployed openshim.dll does not match this worktree's build" }

    if (-not (Test-Path -LiteralPath $missionRoot)) {
        New-Item -ItemType Directory -Force -Path $missionRoot | Out-Null
        $createdMissionRoot = $true
    }
    foreach ($item in $deploy) {
        $live = Join-Path $missionRoot $item.Name
        if ((Test-Path -LiteralPath $live) -and -not (Test-Path -LiteralPath (Join-Path $missionBackup $item.Name))) {
            Copy-Item -LiteralPath $live -Destination (Join-Path $missionBackup $item.Name) -Force
        }
        Copy-Item -LiteralPath $item.Source -Destination $live -Force
        $deployedNames += $item.Name
    }
    Write-Host "[lcmusic] deployed lcbench world + music fixture"

    $t0 = Get-Date
    # WMI, not Start-Process: a child of the agent shell dies with its job object.
    $r = Invoke-CimMethod -ClassName Win32_Process -MethodName Create -Arguments @{
        CommandLine      = '"' + $gameExe + '" lcbench.bzn'
        CurrentDirectory = $GameRoot
    }
    Write-Host "[lcmusic] launched (launcher pid $($r.ProcessId))"

    "t,pid,track,slot,playing,paused" | Set-Content -LiteralPath $samplesPath
    $deadline = $t0.AddSeconds($RunSeconds)
    $sawGame = $false
    $handle = [IntPtr]::Zero
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Milliseconds 500
        # battlezone98redux.exe re-execs: follow the newest instance started
        # after t0, never the launch pid.
        $game = @(Get-Process battlezone98redux -ErrorAction SilentlyContinue |
            Where-Object { $_.StartTime -ge $t0.AddSeconds(-2) } | Sort-Object StartTime -Descending)
        if ($game.Count -gt 0) {
            $sawGame = $true
            if ($game[0].Id -ne $gamePid) {
                if ($handle -ne [IntPtr]::Zero) { [LcMusicMem]::CloseHandle($handle) | Out-Null }
                $gamePid = $game[0].Id
                $handle = [LcMusicMem]::OpenProcess(0x0410, $false, $gamePid)
            }
            if ($handle -ne [IntPtr]::Zero) {
                $t = [math]::Round(((Get-Date) - $t0).TotalSeconds, 1)
                $row = @($t, $gamePid,
                    [LcMusicMem]::ReadInt($handle, 0x008E75F4),
                    [LcMusicMem]::ReadInt($handle, 0x008E75F8),
                    [LcMusicMem]::ReadInt($handle, 0x00915580),
                    [LcMusicMem]::ReadInt($handle, 0x00915588)) -join ","
                Add-Content -LiteralPath $samplesPath -Value $row
            }
        } elseif ($sawGame) { Write-Warning "[lcmusic] game exited early"; break }
        if ((Test-Path -LiteralPath $bzLogger) -and
            (Get-Item -LiteralPath $bzLogger).LastWriteTime -gt $t0 -and
            (Select-String -LiteralPath $bzLogger -Pattern "\[MUSICFIX\].*DONE" -Quiet)) {
            Write-Host "[lcmusic] fixture finished"
            break
        }
    }
    if ($handle -ne [IntPtr]::Zero) { [LcMusicMem]::CloseHandle($handle) | Out-Null }
    if ($gamePid -ne 0 -and (Get-Process -Id $gamePid -ErrorAction SilentlyContinue)) {
        try { Stop-BZRGame -Id $gamePid } catch { Write-Warning "Stop-BZRGame: $_" }
    }
}
finally {
    foreach ($log in @("BZLogger.txt", "openshim.log", "BZOgreLogfile.log")) {
        $src = Join-Path $GameRoot "logs\$log"
        if (Test-Path -LiteralPath $src) {
            Copy-Item -LiteralPath $src -Destination (Join-Path $OutputRoot $log) -Force
        }
    }
    foreach ($name in $deployedNames) {
        $live = Join-Path $missionRoot $name
        $saved = Join-Path $missionBackup $name
        if (Test-Path -LiteralPath $saved) {
            Copy-Item -LiteralPath $saved -Destination $live -Force
        } elseif (Test-Path -LiteralPath $live) {
            Remove-Item -LiteralPath $live -Force
        }
    }
    if ($createdMissionRoot -and (Test-Path -LiteralPath $missionRoot)) {
        if (-not (Get-ChildItem -LiteralPath $missionRoot -Force)) {
            Remove-Item -LiteralPath $missionRoot -Force
        }
    }
    Write-Host "[lcmusic] addon\lcbench restored"
    if ($mutex) { Exit-BZRLaunchLock -Mutex $mutex }
}

$hashAfter = (Get-FileHash -LiteralPath $pluginDll -Algorithm SHA256).Hash
if ($hashAfter -ne $hashBefore) {
    Write-Warning "[lcmusic] openshim.dll changed during the run; this run is not evidence about the deployed build"
}

Write-Host ""
Write-Host "[lcmusic] ===== openshim.log (music / Music:: resolves) ====="
$shimLog = Join-Path $OutputRoot "openshim.log"
if (Test-Path -LiteralPath $shimLog) {
    Select-String -LiteralPath $shimLog -Pattern "\[music\]|Music::|OpenShim(Set|Stop)Music" |
        ForEach-Object { Write-Host "  $($_.Line)" }
}

Write-Host ""
Write-Host "[lcmusic] ===== BZLogger (fixture + engine music) ====="
$log = Join-Path $OutputRoot "BZLogger.txt"
$fixture = @()
if (Test-Path -LiteralPath $log) {
    $fixture = @(Select-String -LiteralPath $log -Pattern "\[MUSICFIX\]|Music Playback|OggManager" | ForEach-Object { $_.Line })
}
if (-not ($fixture -match "MUSICFIX")) {
    Write-Warning "  no [MUSICFIX] markers -- the fixture never ran, so this run says NOTHING"
}
$fixture | ForEach-Object { Write-Host "  $_" }

Write-Host ""
Write-Host "[lcmusic] ===== music globals (changes only) ====="
if (Test-Path -LiteralPath $samplesPath) {
    $prev = ""
    foreach ($row in (Import-Csv -LiteralPath $samplesPath)) {
        $key = "$($row.track),$($row.slot),$($row.playing),$($row.paused)"
        if ($key -ne $prev) {
            Write-Host ("  t={0,6} track={1,4} slot={2,3} playing={3} paused={4}" -f $row.t, $row.track, $row.slot, $row.playing, $row.paused)
            $prev = $key
        }
    }
}
Write-Host ""
Write-Host "[lcmusic] artifacts in $OutputRoot"
