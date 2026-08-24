# Measures the generic chunk batch's rebuild rate before and after state-version
# reuse, on the lcbench workloads.
#
# Three modes share one binary so the comparison cannot drift on build
# differences:
#   observe  - takes the reuse decision, counts it, then rebuilds anyway. This
#              is the pre-optimization baseline *and* the dedup opportunity.
#   reuse    - the shipped behaviour: re-emit only on a source-state change.
#   rebuild  - the explicit opt-out, which must reproduce `observe` exactly.
#
# The frame count for the same window comes from the profiler's own fps line, so
# rebuilds/frame is derived from two numbers measured over the same interval
# rather than from a wall-clock guess.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet("DX11", "DX9")]
    [string[]]$Renderer = @("DX11"),
    [ValidateSet("observe", "reuse", "rebuild")]
    [string[]]$Mode = @("observe", "reuse"),
    [ValidateSet("quiet", "idle", "movement", "firing", "flight", "ai_idle", "combat", "dispersed")]
    [string[]]$Scenario = @("dispersed"),
    [int[]]$Count = @(20),
    [double]$WarmupSeconds = 5.0,
    [double]$MeasureSeconds = 25.0,
    [double]$SpinSeconds = 0.0,
    [switch]$ProfilerDisabled,
    [string]$OutputRoot = "",
    [string]$Label = ""
)

$ErrorActionPreference = "Stop"

if (-not $OutputRoot) {
    $OutputRoot = Join-Path $PSScriptRoot "snapshots\chunk_batch_reuse"
}
if (-not $Label) {
    $Label = Get-Date -Format "yyyyMMdd_HHmmss"
}
$runRoot = Join-Path $OutputRoot $Label
New-Item -ItemType Directory -Path $runRoot -Force | Out-Null

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$ogreConfig = Join-Path $GameRoot "Ogre.cfg"
$missionSourceRoot = Join-Path $PSScriptRoot "test_missions\live_combat_scaling"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$missionConfig = Join-Path $missionRoot "lcbcfg.odf"
$shimLog = Join-Path $GameRoot "logs\openshim.log"

if (-not (Test-Path -LiteralPath $gameExe)) { throw "Game not found: $gameExe" }

$ownedVariables = @(
    "OPENSHIM_CHUNK_BATCH_RATE_DIAGNOSTICS",
    "OPENSHIM_CHUNK_BATCH_REUSE_OBSERVE",
    "OPENSHIM_DISABLE_CHUNK_BATCH_REUSE",
    "OPENSHIM_PROFILE_OGRE_ANIMATION")
$priorValues = @{}
foreach ($name in $ownedVariables) {
    $priorValues[$name] = [Environment]::GetEnvironmentVariable($name, "Process")
}
$originalOgreConfig = [System.IO.File]::ReadAllText($ogreConfig)
$originalMissionConfig = if (Test-Path -LiteralPath $missionConfig) {
    [System.IO.File]::ReadAllText($missionConfig)
} else { $null }

$results = @()

try {
    foreach ($renderName in $Renderer) {
        foreach ($scenarioName in $Scenario) {
            foreach ($unitCount in $Count) {
                foreach ($modeName in $Mode) {
                    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
                        Stop-Process -Force
                    Start-Sleep -Seconds 2

                    $renderSystem = if ($renderName -eq "DX9") {
                        "Direct3D9 Rendering Subsystem"
                    } else {
                        "Direct3D11 Rendering Subsystem"
                    }
                    $config = $originalOgreConfig -replace '(?m)^Render System=.*$', "Render System=$renderSystem"
                    $config = $config -replace '(?m)^Full Screen=Yes$', 'Full Screen=No'
                    $config = $config -replace '(?m)^VSync=Yes$', 'VSync=No'
                    $config = $config -replace '(?m)^Video Mode=.*@ 32-bit colour$', 'Video Mode=1920 x 1080 @ 32-bit colour'
                    $config = $config -replace '(?m)^FSAA=.*$', 'FSAA=0'
                    [System.IO.File]::WriteAllText($ogreConfig, $config)

                    New-Item -ItemType Directory -Path $missionRoot -Force | Out-Null
                    Copy-Item -Path (Join-Path $missionSourceRoot "*") -Destination $missionRoot -Force
                    $invariant = [Globalization.CultureInfo]::InvariantCulture
                    [System.IO.File]::WriteAllText($missionConfig, @"
[Benchmark]
scenario = "$scenarioName"
unitOdf = "avtank"
count = $($unitCount.ToString($invariant))
distance = 50.0
orientation = "facing"
warmupSeconds = $($WarmupSeconds.ToString("0.0###", $invariant))
measureSeconds = $($MeasureSeconds.ToString("0.0###", $invariant))
clusterCount = 4
clusterRadius = 300.0
spinSeconds = $($SpinSeconds.ToString("0.0###", $invariant))
"@)

                    foreach ($name in $ownedVariables) {
                        [Environment]::SetEnvironmentVariable($name, $null, "Process")
                    }
                    [Environment]::SetEnvironmentVariable(
                        "OPENSHIM_CHUNK_BATCH_RATE_DIAGNOSTICS", "1", "Process")
                    switch ($modeName) {
                        "observe" {
                            [Environment]::SetEnvironmentVariable(
                                "OPENSHIM_CHUNK_BATCH_REUSE_OBSERVE", "1", "Process")
                        }
                        "rebuild" {
                            [Environment]::SetEnvironmentVariable(
                                "OPENSHIM_DISABLE_CHUNK_BATCH_REUSE", "1", "Process")
                        }
                        "reuse" { }
                    }
                    if (-not $ProfilerDisabled) {
                        [Environment]::SetEnvironmentVariable(
                            "OPENSHIM_PROFILE_OGRE_ANIMATION", "1", "Process")
                    }

                    if (Test-Path -LiteralPath $shimLog) {
                        try { Remove-Item -LiteralPath $shimLog -Force -ErrorAction Stop }
                        catch { Start-Sleep -Seconds 3; try { Remove-Item -LiteralPath $shimLog -Force -ErrorAction Stop } catch { } }
                    }

                    $tag = "{0}_{1}_{2}_{3:d3}" -f $renderName.ToLowerInvariant(), $scenarioName, $modeName, $unitCount
                    Write-Host "== $tag =="

                    $process = Start-Process -FilePath $gameExe -ArgumentList "lcbench.bzn" `
                        -WorkingDirectory $GameRoot -PassThru
                    $deadline = (Get-Date).AddSeconds($WarmupSeconds + $MeasureSeconds + 60)
                    while ((Get-Date) -lt $deadline) {
                        $process.Refresh()
                        if ($process.HasExited) { break }
                        Start-Sleep -Milliseconds 500
                    }
                    $process.Refresh()
                    if (-not $process.HasExited) { $process.WaitForExit(20000) | Out-Null }
                    Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
                        Stop-Process -Force
                    Start-Sleep -Seconds 1

                    $destination = Join-Path $runRoot "$tag.log"
                    if (Test-Path -LiteralPath $shimLog) {
                        Copy-Item -LiteralPath $shimLog -Destination $destination -Force
                    }
                    $results += [pscustomobject]@{
                        Tag = $tag
                        Renderer = $renderName
                        Scenario = $scenarioName
                        Count = $unitCount
                        Mode = $modeName
                        Log = $destination
                    }
                }
            }
        }
    }
}
finally {
    [System.IO.File]::WriteAllText($ogreConfig, $originalOgreConfig)
    if ($null -ne $originalMissionConfig) {
        [System.IO.File]::WriteAllText($missionConfig, $originalMissionConfig)
    }
    foreach ($name in $ownedVariables) {
        [Environment]::SetEnvironmentVariable($name, $priorValues[$name], "Process")
    }
}

$results | Export-Csv -Path (Join-Path $runRoot "runs.csv") -NoTypeInformation
$runRoot
