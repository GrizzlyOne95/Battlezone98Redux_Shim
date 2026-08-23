param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string]$MissionArgs = "lcbench.bzn",
    [ValidateSet("DX11", "DX9")]
    [string[]]$Renderer = @("DX11"),
    [ValidateSet(
        "quiet", "idle", "movement", "firing", "flight", "ai_idle", "combat",
        "dispersed", "fourteam", "fourteam_fire", "fourteam_ai")]
    [string[]]$Scenario = @("quiet", "idle", "movement", "firing", "combat"),
    [ValidateSet(
        "svtank", "svfigh", "avtank", "avfigh", "avrckt", "avartl",
        "avapc", "avwalk", "avmine", "avturr", "aspilo", "svapc",
        "svwalk", "svmine", "svturr", "sspilo")]
    [string[]]$UnitOdf = @("avtank"),
    [int[]]$Count = @(0, 5, 10, 20, 40, 80),
    [double[]]$Distance = @(50.0),
    [ValidateSet("facing", "away")]
    [string[]]$Orientation = @("facing"),
    [double]$WarmupSeconds = 4.0,
    [double]$MeasureSeconds = 8.0,
    # Dispersed-scenario geometry. Ignored by every other scenario.
    [int]$ClusterCount = 4,
    [double]$ClusterRadius = 300.0,
    [double]$SpinSeconds = 0.0,
    [int]$RunTimeoutSeconds = 50,
    [string]$OutputRoot = "",
    [switch]$KillExisting,
    [switch]$ProfilerDisabled,
    [switch]$ExternalPresentMon,
    # Measurement-only render isolation passed through to the profiler as
    # OPENSHIM_PROFILE_ISOLATE. A run using this is NOT stock rendering and the
    # value is recorded in metadata.json so a capture can never be mistaken for
    # a baseline.
    [ValidateSet("none", "glow", "shadow", "glow+shadow")]
    [string]$Isolate = "none"
)

$ErrorActionPreference = "Stop"
$repoRoot = Split-Path -Parent $PSScriptRoot
if (-not $OutputRoot) {
    $OutputRoot = Join-Path $PSScriptRoot "snapshots\live_combat"
}

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$ogreConfig = Join-Path $GameRoot "Ogre.cfg"
$bzLogger = Join-Path $GameRoot "logs\BZLogger.txt"
$shimLog = Join-Path $GameRoot "logs\openshim.log"
$profileCsv = Join-Path $GameRoot "openshim_ogre_profile.csv"
$missionSourceRoot = Join-Path $PSScriptRoot "test_missions\live_combat_scaling"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$missionConfig = Join-Path $missionRoot "lcbcfg.odf"
$sourceMissionConfig = Join-Path $missionSourceRoot "lcbcfg.odf"
$presentMonExe = "C:\Program Files\AMD\CNext\CNext\PresentMon-x64.exe"

foreach ($required in @(
    $gameExe,
    $ogreConfig,
    (Join-Path $missionSourceRoot "lcbench.ini"),
    (Join-Path $missionSourceRoot "lcbench.bzn"),
    (Join-Path $missionSourceRoot "lcbench.trn"),
    (Join-Path $missionSourceRoot "lcbench.lua"),
    $sourceMissionConfig)) {
    if (-not (Test-Path -LiteralPath $required)) {
        throw "Required benchmark input not found: $required"
    }
}

if ($Count | Where-Object { $_ -lt 0 -or $_ -gt 200 }) {
    throw "Count values must be within 0..200"
}
if ($ClusterCount -lt 1 -or $ClusterCount -gt 8) {
    throw "ClusterCount must be within 1..8"
}
if ($ClusterRadius -lt 50.0 -or $ClusterRadius -gt 1500.0) {
    throw "ClusterRadius must be within 50..1500"
}
if ($SpinSeconds -lt 0.0 -or $SpinSeconds -gt 60.0) {
    throw "SpinSeconds must be within 0..60"
}
if ($ExternalPresentMon -and -not (Test-Path -LiteralPath $presentMonExe)) {
    throw "PresentMon was requested but not found: $presentMonExe"
}

if ($ExternalPresentMon) {
    # A benchmark killed mid-run leaves its ETW session behind, and a stale
    # lcbench session makes every later PresentMon start "Started recording"
    # and then write no CSV at all. That failure is silent and looks exactly
    # like a run that produced no frames, so clear the leftovers up front.
    $staleSessions = @(
        (logman query -ets 2>$null) |
            Select-String -Pattern '^(lcbench_\S+)' |
            ForEach-Object { $_.Matches[0].Groups[1].Value })
    foreach ($stale in $staleSessions) {
        Write-Host "Terminating stale PresentMon session $stale"
        & $presentMonExe --terminate_existing_session --session_name $stale *> $null
    }
}

if ($KillExisting) {
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Stop-Process -Force
    Start-Sleep -Seconds 2
} elseif (Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue) {
    throw "Battlezone is already running. Stop it or pass -KillExisting."
}

$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
$sessionRoot = Join-Path $OutputRoot $stamp
New-Item -ItemType Directory -Path $sessionRoot -Force | Out-Null

# Renderer/profile inputs are restored in finally. The task-owned IA package
# intentionally remains installed under addon\lcbench for manual reproduction.
$originalOgreConfig = [System.IO.File]::ReadAllText($ogreConfig)
$originalProfileCsv = if (Test-Path $profileCsv) {
    [System.IO.File]::ReadAllBytes($profileCsv)
} else { $null }
$priorProfileEnv = [Environment]::GetEnvironmentVariable(
    "OPENSHIM_PROFILE_OGRE_ANIMATION", "Process")
$priorIsolateEnv = [Environment]::GetEnvironmentVariable(
    "OPENSHIM_PROFILE_ISOLATE", "Process")

# Redux may pause mission startup for loading VO. Bounded synthetic Space input
# mirrors launch_mission_live.ps1 and is used only after that exact log cue.
Add-Type @"
using System;
using System.Runtime.InteropServices;
public static class LiveCombatBenchmarkInput {
    public const int SW_RESTORE = 9;
    public const ushort VK_SPACE = 0x20;
    public const uint KEYEVENTF_KEYUP = 0x0002;
    public const uint INPUT_KEYBOARD = 1;
    [StructLayout(LayoutKind.Sequential)] public struct INPUT { public uint type; public InputUnion U; }
    [StructLayout(LayoutKind.Explicit)] public struct InputUnion { [FieldOffset(0)] public KEYBDINPUT ki; }
    [StructLayout(LayoutKind.Sequential)] public struct KEYBDINPUT { public ushort wVk; public ushort wScan; public uint dwFlags; public uint time; public IntPtr extra; }
    [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int n);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
    [DllImport("user32.dll", SetLastError=true)] private static extern uint SendInput(uint n, INPUT[] p, int cb);
    public static bool Space() {
        INPUT[] input = new INPUT[2];
        input[0].type = INPUT_KEYBOARD; input[0].U.ki.wVk = VK_SPACE;
        input[1].type = INPUT_KEYBOARD; input[1].U.ki.wVk = VK_SPACE;
        input[1].U.ki.dwFlags = KEYEVENTF_KEYUP;
        return SendInput(2, input, Marshal.SizeOf(typeof(INPUT))) == 2;
    }
}
"@

function Send-LoadSkip {
    param([System.Diagnostics.Process]$Process)
    $Process.Refresh()
    if ($Process.MainWindowHandle -ne 0) {
        [void][LiveCombatBenchmarkInput]::ShowWindow(
            $Process.MainWindowHandle,
            [LiveCombatBenchmarkInput]::SW_RESTORE)
        [void][LiveCombatBenchmarkInput]::SetForegroundWindow(
            $Process.MainWindowHandle)
        try {
            (New-Object -ComObject WScript.Shell).AppActivate($Process.Id) |
                Out-Null
        } catch {
        }
        [void][LiveCombatBenchmarkInput]::Space()
    }
}

function Set-RendererConfig {
    param([string]$Name)
    $renderSystem = if ($Name -eq "DX9") {
        "Direct3D9 Rendering Subsystem"
    } else {
        "Direct3D11 Rendering Subsystem"
    }
    $config = $originalOgreConfig -replace
        '(?m)^Render System=.*$', "Render System=$renderSystem"
    # Unlocked presentation is required to reveal CPU scaling above the monitor
    # refresh rate; all other quality and resolution settings remain unchanged.
    $config = $config -replace '(?m)^VSync=Yes$', 'VSync=No'
    [System.IO.File]::WriteAllText($ogreConfig, $config)
}

function Write-BenchmarkConfig {
    param(
        [string]$ScenarioName,
        [string]$UnitOdfName,
        [int]$Population,
        [double]$SpawnDistance,
        [string]$ViewOrientation
    )
    $invariant = [Globalization.CultureInfo]::InvariantCulture
    $content = @"
[Benchmark]
scenario = "$ScenarioName"
unitOdf = "$UnitOdfName"
count = $($Population.ToString($invariant))
distance = $($SpawnDistance.ToString("0.0###", $invariant))
orientation = "$ViewOrientation"
warmupSeconds = $($WarmupSeconds.ToString("0.0###", $invariant))
measureSeconds = $($MeasureSeconds.ToString("0.0###", $invariant))
clusterCount = $($ClusterCount.ToString($invariant))
clusterRadius = $($ClusterRadius.ToString("0.0###", $invariant))
spinSeconds = $($SpinSeconds.ToString("0.0###", $invariant))
"@
    [System.IO.File]::WriteAllText($missionConfig, $content)
}

function Copy-LogIfPresent {
    param([string]$Source, [string]$Destination)
    if (Test-Path -LiteralPath $Source) {
        Copy-Item -LiteralPath $Source -Destination $Destination -Force
    }
}

try {
    # Deploy the complete IA package before launch. lcbench.bzn embeds both
    # msn_filename=lcbench.bzn and TerrainName=lcbench, matching its companions.
    New-Item -ItemType Directory -Path $missionRoot -Force | Out-Null
    Copy-Item -Path (Join-Path $missionSourceRoot "*") `
        -Destination $missionRoot -Force
    [Environment]::SetEnvironmentVariable(
        "OPENSHIM_PROFILE_OGRE_ANIMATION",
        $(if ($ProfilerDisabled) { "0" } else { "1" }),
        "Process")
    [Environment]::SetEnvironmentVariable(
        "OPENSHIM_PROFILE_ISOLATE",
        $(if ($Isolate -eq "none") { $null } else { $Isolate }),
        "Process")

    foreach ($rendererName in $Renderer) {
        Set-RendererConfig $rendererName
        foreach ($unitOdfName in $UnitOdf) {
            foreach ($scenarioName in $Scenario) {
                foreach ($population in $Count) {
                # quiet intentionally contains only the player; skip redundant
                # population and ODF permutations while preserving one baseline.
                if ($scenarioName -eq "quiet" -and $population -ne 0) {
                    continue
                }
                if ($scenarioName -eq "quiet" -and
                    $unitOdfName -ne $UnitOdf[0]) {
                    continue
                }
                if ($scenarioName -ne "quiet" -and $population -eq 0) {
                    continue
                }
                foreach ($spawnDistance in $Distance) {
                    foreach ($viewOrientation in $Orientation) {
                        Write-BenchmarkConfig $scenarioName $unitOdfName $population `
                            $spawnDistance $viewOrientation
                        if (Test-Path $profileCsv) {
                            Remove-Item -LiteralPath $profileCsv -Force
                        }

                        $runId = "{0}_{1}_{2}_{3:d3}_{4}_{5}" -f @(
                            $rendererName.ToLowerInvariant(),
                            $unitOdfName,
                            $scenarioName,
                            $population,
                            $spawnDistance.ToString("0", [Globalization.CultureInfo]::InvariantCulture),
                            $viewOrientation)
                        if ($Isolate -ne "none") {
                            $runId = "{0}_iso-{1}" -f @(
                                $runId, $Isolate.Replace("+", "-"))
                        }
                        $runRoot = Join-Path $sessionRoot $runId
                        New-Item -ItemType Directory -Path $runRoot -Force | Out-Null
                        Write-Host "Starting $runId"
                        $startedAt = Get-Date
                        $process = Start-Process -FilePath $gameExe `
                            -ArgumentList $MissionArgs `
                            -WorkingDirectory $GameRoot -PassThru
                        $deadline = (Get-Date).AddSeconds($RunTimeoutSeconds)
                        $completed = $false
                        $nextLoadSkip = Get-Date
                        $presentMon = $null
                        $presentMonSession = "lcbench_$($process.Id)"

                        while ((Get-Date) -lt $deadline -and -not $process.HasExited) {
                            Start-Sleep -Milliseconds 250
                            if (Test-Path $bzLogger) {
                                $logItem = Get-Item $bzLogger
                                if ($logItem.LastWriteTime -lt $startedAt) {
                                    continue
                                }
                                $stream = [System.IO.File]::Open(
                                    $bzLogger, 'Open', 'Read', 'ReadWrite')
                                try {
                                    $reader = New-Object System.IO.StreamReader($stream)
                                    $tail = $reader.ReadToEnd()
                                    $reader.Dispose()
                                } finally {
                                    $stream.Dispose()
                                }
                                if ($tail -match
                                    '\[LIVE_COMBAT_BENCH\].*benchmark-end') {
                                    $completed = $true
                                    break
                                }
                                if ($ExternalPresentMon -and -not $presentMon -and
                                    $tail -match '\[LIVE_COMBAT_BENCH\].*measure-begin') {
                                    # Starting ETW capture at the Lua marker keeps
                                    # profiler-disabled validation free of loading frames.
                                    $presentMonArgs = @(
                                        "--process_id", $process.Id,
                                        "--output_file", (Join-Path $runRoot "presentmon.csv"),
                                        "--no_console_stats",
                                        "--v1_metrics",
                                        "--terminate_on_proc_exit",
                                        "--session_name", $presentMonSession)
                                    $presentMon = Start-Process `
                                        -FilePath $presentMonExe `
                                        -ArgumentList $presentMonArgs `
                                        -RedirectStandardOutput (Join-Path $runRoot "presentmon.stdout.txt") `
                                        -RedirectStandardError (Join-Path $runRoot "presentmon.stderr.txt") `
                                        -WindowStyle Hidden -PassThru
                                }
                                if ($tail -match 'Waiting For VO' -and
                                    (Get-Date) -ge $nextLoadSkip) {
                                    Send-LoadSkip $process
                                    $nextLoadSkip = (Get-Date).AddMilliseconds(500)
                                }
                            }
                        }

                        if (-not $process.HasExited) {
                            Stop-Process -Id $process.Id -Force
                            $process.WaitForExit()
                        }
                        if ($presentMon) {
                            # Explicit session termination asks PresentMon to
                            # flush CSV/ETW state after the benchmark kills BZR.
                            $terminator = Start-Process `
                                -FilePath $presentMonExe `
                                -ArgumentList @(
                                    "--terminate_existing_session",
                                    "--session_name", $presentMonSession) `
                                -WindowStyle Hidden -PassThru -Wait
                            if (-not $presentMon.WaitForExit(5000)) {
                                # PresentMon belongs to this one benchmark run;
                                # terminate only that captured helper if ETW lingers.
                                Stop-Process -Id $presentMon.Id -Force
                                $presentMon.WaitForExit()
                            }
                        }
                        Start-Sleep -Milliseconds 750

                        # Current Redux truncates BZLogger on each launch. Copy
                        # the complete current-process log after the process is
                        # stopped so marker timestamps remain unambiguous.
                        if (Test-Path $bzLogger) {
                            $stream = [System.IO.File]::Open(
                                $bzLogger, 'Open', 'Read', 'ReadWrite')
                            try {
                                $reader = New-Object System.IO.StreamReader($stream)
                                $tail = $reader.ReadToEnd()
                                $reader.Dispose()
                            } finally {
                                $stream.Dispose()
                            }
                            [System.IO.File]::WriteAllText(
                                (Join-Path $runRoot "BZLogger.slice.txt"), $tail)
                        }
                        Copy-LogIfPresent $shimLog (Join-Path $runRoot "openshim.log")
                        Copy-LogIfPresent $profileCsv (Join-Path $runRoot "profile.csv")

                        $metadata = [ordered]@{
                            run_id = $runId
                            renderer = $rendererName
                            unit_odf = $unitOdfName
                            scenario = $scenarioName
                            count = $population
                            distance = $spawnDistance
                            orientation = $viewOrientation
                            profiler_enabled = -not $ProfilerDisabled
                            external_presentmon = [bool]$ExternalPresentMon
                            isolate = $Isolate
                            warmup_seconds = $WarmupSeconds
                            measure_seconds = $MeasureSeconds
                            cluster_count = $ClusterCount
                            cluster_radius = $ClusterRadius
                            spin_seconds = $SpinSeconds
                            started_at = $startedAt.ToString("o")
                            ended_at = (Get-Date).ToString("o")
                            completed = $completed
                            process_exit_code = $process.ExitCode
                        }
                        $metadata | ConvertTo-Json | Set-Content `
                            -LiteralPath (Join-Path $runRoot "metadata.json") `
                            -Encoding ASCII
                        if (-not $completed) {
                            Write-Warning "$runId did not reach benchmark-end"
                        }
                    }
                }
            }
            }
        }
    }
} finally {
    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Stop-Process -Force
    [System.IO.File]::WriteAllText($ogreConfig, $originalOgreConfig)
    if (Test-Path -LiteralPath $sourceMissionConfig) {
        Copy-Item -LiteralPath $sourceMissionConfig `
            -Destination $missionConfig -Force
    }
    if ($null -ne $originalProfileCsv) {
        [System.IO.File]::WriteAllBytes($profileCsv, $originalProfileCsv)
    } else {
        Remove-Item -LiteralPath $profileCsv -Force -ErrorAction SilentlyContinue
    }
    [Environment]::SetEnvironmentVariable(
        "OPENSHIM_PROFILE_OGRE_ANIMATION", $priorProfileEnv, "Process")
    [Environment]::SetEnvironmentVariable(
        "OPENSHIM_PROFILE_ISOLATE", $priorIsolateEnv, "Process")
}

Write-Host "Benchmark session complete: $sessionRoot"
$sessionRoot
