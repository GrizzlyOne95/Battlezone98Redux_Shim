# Runs the same live-combat workloads under the three craft-bounds
# architectures so they can be compared on identical mission state.
#
#   stock    infinite craft bounds, no OpenShim culling of any kind
#   private  PR #47: bounds untouched, OpenShim runs its own main-view frustum
#            rejection through Entity::_updateRenderQueue
#   restore  finite Ogre bounds put back on the meshes the first-person view
#            path made infinite; no private suppression at all
#
# Every mode runs the identical workload list in the identical order, so a
# comparison never straddles different mission state.

param(
    [ValidateSet("stock", "private", "restore")]
    [string[]]$Mode = @("stock", "private", "restore"),
    [string]$Label = "",
    [double]$RestoreScale = 2.0,
    [switch]$IncludeDx9,
    [switch]$WalkerOnly
)

$ErrorActionPreference = "Stop"
$harness = Join-Path $PSScriptRoot "run_live_combat_benchmark.ps1"
if (-not $Label) {
    $Label = Get-Date -Format "yyyyMMdd_HHmmss"
}
$root = Join-Path $PSScriptRoot "snapshots\craft_bounds\$Label"

# Everything this script sets, cleared before each mode so a leftover value from
# a previous mode can never contaminate the next one.
$ownedVariables = @(
    "OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING",
    "OPENSHIM_RESTORE_CRAFT_BOUNDS",
    "OPENSHIM_RESTORE_CRAFT_BOUNDS_SCALE",
    "OPENSHIM_RESTORE_CRAFT_BOUNDS_MODE",
    "OPENSHIM_RESTORE_CRAFT_BOUNDS_SCOPE",
    "OPENSHIM_BOUNDS_TRACE",
    "OPENSHIM_FRUSTUM_CULL_CENSUS")

function Clear-OwnedEnvironment {
    foreach ($name in $ownedVariables) {
        [Environment]::SetEnvironmentVariable($name, $null, "Process")
    }
}

# scenario, unit, count, orientation, renderer
$workloads = if ($WalkerOnly) {
    @(
        @{ scenario = "firing"; unit = "avwalk"; count = 20; orientation = "facing"; renderer = "DX11" },
        @{ scenario = "firing"; unit = "avwalk"; count = 20; orientation = "away";   renderer = "DX11" },
        @{ scenario = "firing"; unit = "avtank"; count = 20; orientation = "facing"; renderer = "DX11" },
        @{ scenario = "firing"; unit = "avtank"; count = 20; orientation = "away";   renderer = "DX11" }
    )
} else {
    $base = @(
        @{ scenario = "idle";      unit = "avtank"; count = 20; orientation = "facing"; renderer = "DX11" },
        @{ scenario = "firing";    unit = "avtank"; count = 20; orientation = "facing"; renderer = "DX11" },
        @{ scenario = "firing";    unit = "avtank"; count = 20; orientation = "away";   renderer = "DX11" },
        @{ scenario = "dispersed"; unit = "avtank"; count = 40; orientation = "facing"; renderer = "DX11" },
        @{ scenario = "firing";    unit = "avtank"; count = 80; orientation = "facing"; renderer = "DX11" }
    )
    if ($IncludeDx9) {
        $base += @(
            @{ scenario = "firing"; unit = "avtank"; count = 20; orientation = "facing"; renderer = "DX9" },
            @{ scenario = "firing"; unit = "avtank"; count = 20; orientation = "away";   renderer = "DX9" }
        )
    }
    $base
}

foreach ($modeName in $Mode) {
    Clear-OwnedEnvironment
    switch ($modeName) {
        "stock" {
            [Environment]::SetEnvironmentVariable(
                "OPENSHIM_DISABLE_ENTITY_FRUSTUM_CULLING", "1", "Process")
        }
        "private" {
            # PR #47 defaults: private culling on, bounds untouched.
        }
        "restore" {
            [Environment]::SetEnvironmentVariable(
                "OPENSHIM_RESTORE_CRAFT_BOUNDS", "1", "Process")
            [Environment]::SetEnvironmentVariable(
                "OPENSHIM_RESTORE_CRAFT_BOUNDS_SCALE",
                $RestoreScale.ToString("0.00", [Globalization.CultureInfo]::InvariantCulture),
                "Process")
        }
    }

    $modeRoot = Join-Path $root $modeName
    Write-Host "=== mode $modeName -> $modeRoot ==="
    foreach ($workload in $workloads) {
        & $harness `
            -Renderer $workload.renderer `
            -Scenario $workload.scenario `
            -UnitOdf $workload.unit `
            -Count $workload.count `
            -Orientation $workload.orientation `
            -OutputRoot $modeRoot `
            -KillExisting | Out-Null
    }
}

Clear-OwnedEnvironment
Write-Host "Matrix complete: $root"
$root
