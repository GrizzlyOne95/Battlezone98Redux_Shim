<#
.SYNOPSIS
    Phase 1 four-team distant-combat attribution matrix.

.DESCRIPTION
    Drives run_live_combat_benchmark.ps1 through the complete Phase 1 matrix in
    one serial pass so every arm shares a machine state, a shim build and a
    mission package. The matrix has three parts and they answer different
    questions, which is why they are not merged:

      profiler   attribution. Per-contributor submissions, API draws, vertices,
                 indices and CPU time. Frame times from these runs are NOT
                 usable -- the profiler perturbs them substantially.
      isolation  category ownership. Same workload with one category of
                 renderable suppressed, so the frame-time cost of that category
                 is measured rather than inferred from its submission count.
      presentmon profiler-disabled external ETW capture. This is the only arm
                 whose frame times are treated as evidence.

    Nothing here is a shipped behavior change. The isolation arms deliberately
    render an incomplete scene and are labelled as such in every artifact.

.PARAMETER Part
    Which parts of the matrix to run. Defaults to all three.
#>
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string]$OutputRoot = (Join-Path $PSScriptRoot "snapshots\fourteam_phase1"),
    [ValidateSet("profiler", "isolation", "presentmon", "repeats")]
    [string[]]$Part = @("profiler", "isolation", "presentmon"),
    # Repeat count for the "repeats" part. Frame-time differences of a few
    # percent are not resolvable from one capture of a live battle, so the
    # isolation verdict is taken from repeated profiler-disabled captures.
    [int]$Repeats = 3,
    [int]$Count = 80,
    [double]$BaseDistance = 400.0,
    [double[]]$DistanceSweep = @(100.0, 200.0, 800.0),
    [double]$WarmupSeconds = 5.0,
    [double]$MeasureSeconds = 10.0
)

$ErrorActionPreference = "Stop"
$runner = Join-Path $PSScriptRoot "run_live_combat_benchmark.ps1"
if (-not (Test-Path -LiteralPath $runner)) {
    throw "Benchmark runner not found: $runner"
}
New-Item -ItemType Directory -Path $OutputRoot -Force | Out-Null

function Invoke-Arm {
    param([hashtable]$Arguments, [string]$Label)
    Write-Host "=== $Label ===" -ForegroundColor Cyan
    & $runner @Arguments
}

$common = @{
    GameRoot = $GameRoot
    OutputRoot = $OutputRoot
    Count = @($Count)
    WarmupSeconds = $WarmupSeconds
    MeasureSeconds = $MeasureSeconds
    KillExisting = $true
}

if ($Part -contains "profiler") {
    # Baseline attribution. Idle and firing share one layout, so the only
    # difference between the two captures is whether weapons are discharged.
    Invoke-Arm ($common + @{
        Renderer = @("DX11", "DX9")
        Scenario = @("fourteam", "fourteam_fire")
        Distance = @($BaseDistance)
    }) "profiler baseline DX11+DX9 idle+firing @ $BaseDistance m"

    # Distance sweep. Existing evidence says vehicle submissions do not fall
    # with distance at all; this re-tests that on a four-team layout and gives
    # the LOD investigation a workload where a distance policy could show.
    Invoke-Arm ($common + @{
        Renderer = @("DX11")
        Scenario = @("fourteam_fire")
        Distance = $DistanceSweep
    }) "profiler distance sweep DX11 firing"
}

if ($Part -contains "isolation") {
    foreach ($arm in @("glow", "shadow", "glow+shadow")) {
        Invoke-Arm ($common + @{
            Renderer = @("DX11")
            Scenario = @("fourteam_fire")
            Distance = @($BaseDistance)
            Isolate = $arm
        }) "profiler isolation DX11 firing isolate=$arm"
    }
}

if ($Part -contains "presentmon") {
    Invoke-Arm ($common + @{
        Renderer = @("DX11", "DX9")
        Scenario = @("fourteam", "fourteam_fire")
        Distance = @($BaseDistance)
        ProfilerDisabled = $true
        ExternalPresentMon = $true
    }) "presentmon baseline DX11+DX9 idle+firing @ $BaseDistance m"

    Invoke-Arm ($common + @{
        Renderer = @("DX11")
        Scenario = @("fourteam_fire")
        Distance = $DistanceSweep
        ProfilerDisabled = $true
        ExternalPresentMon = $true
    }) "presentmon distance sweep DX11 firing"

    foreach ($arm in @("glow", "shadow", "glow+shadow")) {
        Invoke-Arm ($common + @{
            Renderer = @("DX11")
            Scenario = @("fourteam_fire")
            Distance = @($BaseDistance)
            ProfilerDisabled = $true
            ExternalPresentMon = $true
            Isolate = $arm
        }) "presentmon isolation DX11 firing isolate=$arm"
    }
}

if ($Part -contains "repeats") {
    # Repeated profiler-disabled captures of the isolation arms, on both the
    # idle and the firing workload. Idle matters most here: it is very nearly
    # pure render work, so if suppressing a category does not move idle frame
    # time, that category is not the frame-time owner it looks like by
    # submission count. fourteam_ai is the control that separates the harness's
    # own per-frame scripting from the cost of the battle.
    for ($repeat = 1; $repeat -le $Repeats; $repeat++) {
        foreach ($scenario in @("fourteam", "fourteam_fire", "fourteam_ai")) {
            foreach ($arm in @("none", "glow", "shadow", "glow+shadow")) {
                if ($scenario -eq "fourteam_ai" -and $arm -ne "none") {
                    continue
                }
                Invoke-Arm ($common + @{
                    Renderer = @("DX11")
                    Scenario = @($scenario)
                    Distance = @($BaseDistance)
                    ProfilerDisabled = $true
                    ExternalPresentMon = $true
                    Isolate = $arm
                    RunTimeoutSeconds = 75
                }) "repeat $repeat/$Repeats $scenario isolate=$arm"
            }
        }
    }
}

Write-Host "Phase 1 matrix complete: $OutputRoot"
$OutputRoot
