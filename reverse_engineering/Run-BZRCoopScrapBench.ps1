# Scrap-accumulation frame-time bench: 2-client co-op (host + 1 guest) on the
# private nbattle map (Run-BZRBattleLoad's lcbench terrain), host-owned AI
# armies held at $Units, scrap never cleaned unless -ClearAtSeconds. Reuses
# Run-BZRCoopMission.ps1 (lobby, launch lock, watchdog, BZRHarness launch).
#
#   powershell -ExecutionPolicy Bypass -File reverse_engineering\Run-BZRCoopScrapBench.ps1 -Units 80 -Seconds 300
#   ... -ClearAtSeconds 200                    # control: delete scrap from 200 s on
#   ... -SampleCpu -CpuDelay 330 -CpuDuration 60  # native CPU sampler (attribution only)
#
# Uses the instances' installed OpenShim (no redeploy). Output: C:\BZRCoop\runs\<RunName>\
# (scrapbench-samples.jsonl, frames\*.bin, scrapbench-report.md).
param([ValidateRange(4,160)][int]$Units = 40,
      [ValidateRange(15,1800)][int]$Seconds = 300,
      [int]$ClearAtSeconds = 0,
      [switch]$SampleCpu,
      [int]$CpuDelay = 330,
      [int]$CpuDuration = 60,
      [switch]$CullCensus,
      [ValidateRange(120,3600)][int]$HardTimeoutSeconds = 600,
      [string]$ServerRepo = (Join-Path $HOME 'Documents/GIT/Battlezone98Redux_DedicatedServer'),
      [string]$Python = 'python',
      [string]$RunName = ('scrapbench-' + (Get-Date -Format 'yyyyMMdd-HHmmss')))
$ErrorActionPreference = 'Stop'
if ($Units % 2) { throw 'Units must be even.' }
$override = Join-Path 'C:\BZRCoop\runs' ($RunName + '-map')
& $Python (Join-Path $PSScriptRoot 'coopflow\battleload\prepare_battle_map.py') --output $override
if ($LASTEXITCODE -ne 0) { throw 'Battle map staging failed.' }
# Staged copy only: lift the 300 s / 640-spawn limits, append the census.
$lua = Join-Path $override 'nbattle.lua'
$text = [IO.File]::ReadAllText($lua)
foreach ($pair in @(@('seconds <= 300', 'seconds <= 1800'), @('640 - M.spawned', '100000 - M.spawned'),
                    @('M.spawned >= 640', 'M.spawned >= 100000'))) {
    if (-not $text.Contains($pair[0])) { throw "nbattle.lua no longer contains '$($pair[0])'" }
    $text = $text.Replace($pair[0], $pair[1])
}
$text += [IO.File]::ReadAllText((Join-Path $PSScriptRoot 'coopflow\battleload\scrapbench_addon.lua'))
[IO.File]::WriteAllText($lua, $text)
$scenario = Join-Path $override 'nbattle-scrapbench.ps1'
Copy-Item -LiteralPath (Join-Path $PSScriptRoot 'coopflow\scenarios\nbattle-scrapbench.ps1') -Destination $scenario

$label = ($RunName -replace '[^A-Za-z0-9_-]', '_')
$env:OPENSHIM_PERF_TELEMETRY = '1'
$env:OPENSHIM_PROFILE_NATIVE_CPU_LABEL = $label
if ($SampleCpu) {
    $env:OPENSHIM_PROFILE_NATIVE_CPU = '1'
    $env:OPENSHIM_PROFILE_NATIVE_CPU_DELAY = "$CpuDelay"
    $env:OPENSHIM_PROFILE_NATIVE_CPU_DURATION = "$CpuDuration"
} else { Remove-Item Env:OPENSHIM_PROFILE_NATIVE_CPU* -ErrorAction SilentlyContinue; $env:OPENSHIM_PROFILE_NATIVE_CPU_LABEL = $label }
if ($CullCensus) { $env:OPENSHIM_FRUSTUM_CULL_CENSUS = '1' } else { Remove-Item Env:OPENSHIM_FRUSTUM_CULL_CENSUS -ErrorAction SilentlyContinue }

$code = 1
try {
    & (Join-Path $PSScriptRoot 'Run-BZRCoopMission.ps1') -Mission nbattle -Scenario $scenario `
        -MapListY 99 -ContentOverride $override -Clients 2 -SkipPrepare `
        -RunName $RunName -ServerRepo $ServerRepo -Python $Python -HardTimeoutSeconds $HardTimeoutSeconds `
        -ScenarioArgs @{Units=$Units; Seconds=$Seconds; ClearAtSeconds=$ClearAtSeconds}
    $code = $LASTEXITCODE
} finally {
    foreach ($n in 'OPENSHIM_PERF_TELEMETRY', 'OPENSHIM_PROFILE_NATIVE_CPU', 'OPENSHIM_PROFILE_NATIVE_CPU_DELAY',
                   'OPENSHIM_PROFILE_NATIVE_CPU_DURATION', 'OPENSHIM_PROFILE_NATIVE_CPU_LABEL', 'OPENSHIM_FRUSTUM_CULL_CENSUS') {
        Remove-Item "Env:$n" -ErrorAction SilentlyContinue
    }
    # Collect this run's telemetry from both instances' logs\ (named by label).
    $runDir = Join-Path 'C:\BZRCoop\runs' $RunName
    $dest = New-Item -ItemType Directory -Force -Path (Join-Path $runDir 'frames')
    foreach ($i in 0, 1) {
        $logs = "C:\BZRCoop\instances\Instance$i\Battlezone 98 Redux\logs"
        Get-ChildItem -LiteralPath $logs -File -Filter "openshim_*_${label}_*" -ErrorAction SilentlyContinue |
            Move-Item -Destination $dest.FullName -Force
        Copy-Item -LiteralPath (Join-Path $logs 'openshim.log') -Destination (Join-Path $dest.FullName "openshim-client$i.log") -ErrorAction SilentlyContinue
    }
    if (Test-Path -LiteralPath (Join-Path $runDir 'scrapbench-samples.jsonl')) {
        & $Python (Join-Path $PSScriptRoot 'coopflow\battleload\report_scrapbench.py') $runDir |
            Tee-Object -FilePath (Join-Path $runDir 'scrapbench-report.md')
    }
}
exit $code
