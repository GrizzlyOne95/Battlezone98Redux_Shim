# Safe runner for the lcbench Constructor double-recycle matrix.
#
# Reproduces the report that when two Constructors are ordered to recycle the
# same building, the one that loses the race is left permanently deployed.
# "solo" and "pair" are the controls that must come back clean.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet("same", "stag", "solo", "pair")]
    [string[]]$Cases = @("solo", "pair", "same", "stag"),
    [ValidateRange(1, 20)]
    [int]$Repeats = 1,
    [ValidateRange(30, 240)]
    [int]$RunSeconds = 120,
    [string]$RigOdf = "avcnst",
    [string]$BuildingOdf = "abcomm",
    [string]$OutputRoot = ""
)

$ErrorActionPreference = "Stop"
$env:BZR_FORCE_WINDOWED = "1"
. "$PSScriptRoot\BZRHarness.ps1"

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$shimDll = Join-Path $GameRoot "winmm.dll"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$fixtureRoot = Join-Path $PSScriptRoot "test_missions\lcbench_roadmap"
$baselineRoot = Join-Path $PSScriptRoot "test_missions\live_combat_scaling"
$logRoot = Join-Path $GameRoot "logs"
$commit = (git -C (Split-Path $PSScriptRoot -Parent) rev-parse --short=12 HEAD).Trim()
$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
if (-not $OutputRoot) {
    $OutputRoot = Join-Path $GameRoot "openshim_test_results\lcroad_recycle_$stamp"
}
# The lcbench world assets are not part of the game install. Lay them down if
# they are absent and take them away again afterwards, so a machine that never
# had lcbench is left exactly as it was found.
$installedBaseline = $false
if (-not (Test-Path -LiteralPath (Join-Path $missionRoot "lcbench.bzn"))) {
    if (-not (Test-Path -LiteralPath (Join-Path $baselineRoot "lcbench.bzn"))) {
        throw "No lcbench baseline to install from: $baselineRoot"
    }
    New-Item -ItemType Directory -Path $missionRoot -Force | Out-Null
    Copy-Item -Path (Join-Path $baselineRoot "*") -Destination $missionRoot -Force
    $installedBaseline = $true
    Write-Host "Installed lcbench baseline into $missionRoot (will be removed afterwards)"
}

$deployNames = @("lcbench.lua", "rmrcfg.odf")
$backupRoot = Join-Path $OutputRoot "pre_live"
New-Item -ItemType Directory -Path $backupRoot -Force | Out-Null
$present = @{}
foreach ($name in $deployNames) {
    $live = Join-Path $missionRoot $name
    $present[$name] = Test-Path -LiteralPath $live
    if ($present[$name]) {
        Copy-Item -LiteralPath $live -Destination (Join-Path $backupRoot $name) -Force
    }
}

# Windowing matters here: these arms run for half a minute of simulated time
# and the simulation stalls whenever an exclusive-fullscreen window loses
# focus. BZR_FORCE_WINDOWED (set above, before BZRHarness is dot-sourced) is
# what rewrites Ogre.cfg and restores it; the shim itself never reads it.
$exeInfo = Get-Item -LiteralPath $gameExe
$exeHash = (Get-FileHash -LiteralPath $gameExe -Algorithm SHA256).Hash
$shimHash = (Get-FileHash -LiteralPath $shimDll -Algorithm SHA256).Hash
$runs = @()

try {
    Copy-Item -LiteralPath (Join-Path $fixtureRoot "rmrcyc.lua") `
        -Destination (Join-Path $missionRoot "lcbench.lua") -Force

    foreach ($caseName in $Cases) {
        for ($repeat = 1; $repeat -le $Repeats; $repeat++) {
            if (Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue) {
                throw "Refusing to start while another Battlezone process is running"
            }
            $arm = "{0}_r{1:D2}" -f $caseName, $repeat
            $runRoot = Join-Path $OutputRoot $arm
            New-Item -ItemType Directory -Path $runRoot -Force | Out-Null
            [System.IO.File]::WriteAllText((Join-Path $missionRoot "rmrcfg.odf"), @"
[Roadmap]
case = "$caseName"
commit = "$commit"
rig = "$RigOdf"
building = "$BuildingOdf"
"@)

            $started = Get-Date
            $process = Start-Process -FilePath $gameExe -ArgumentList "lcbench.bzn" `
                -WorkingDirectory $GameRoot -PassThru
            $exited = $process.WaitForExit($RunSeconds * 1000)
            if (-not $exited) { Stop-BZRGame -Id $process.Id }
            try { $process.Refresh() } catch { }

            foreach ($name in @("BZLogger.txt", "openshim.log", "openshim_crash.log")) {
                $source = Join-Path $logRoot $name
                if (Test-Path -LiteralPath $source) {
                    Copy-Item -LiteralPath $source -Destination (Join-Path $runRoot $name) -Force
                }
            }

            $markers = @()
            $bzPath = Join-Path $runRoot "BZLogger.txt"
            if (Test-Path -LiteralPath $bzPath) {
                $markers = @(Select-String -LiteralPath $bzPath -Pattern "\[LCROAD\]\[RCYC\]" |
                    ForEach-Object { $_.Line })
            }

            # Shim-side evidence. An arm where the fix never engaged is not a
            # pass, it is an arm that did not run the fix -- record the count of
            # stale handles it actually released, not just the mission outcome.
            $shimMarkers = @()
            $shimPath = Join-Path $runRoot "openshim.log"
            if (Test-Path -LiteralPath $shimPath) {
                $shimMarkers = @(Select-String -LiteralPath $shimPath -Pattern "\[RIGRECYCLE\]" |
                    ForEach-Object { $_.Line })
            }
            $fixInstalled = [bool](@($shimMarkers | Where-Object { $_ -match "Installed constructor recycle" }).Count)
            $undeployedByFix = @($shimMarkers | Where-Object { $_ -match "Undeployed constructor whose recycle target vanished" }).Count

            $complete = @($markers | Where-Object { $_ -match " COMPLETE " })
            $deployed = -1; $moved = -1; $stuck = -1; $targetDownAt = [double]::NaN
            if ($complete.Count -gt 0) {
                $line = $complete[-1]
                if ($line -match "deployed=(\d+)")     { $deployed = [int]$Matches[1] }
                if ($line -match "\bmoved=(\d+)")      { $moved = [int]$Matches[1] }
                if ($line -match "stuck=(\d+)")        { $stuck = [int]$Matches[1] }
                if ($line -match "targetDownAt=(-?[\d.]+)") { $targetDownAt = [double]$Matches[1] }
            }

            $manifest = [ordered]@{
                target = "constructor-double-recycle-stale-deployed-state"
                case = $caseName
                repeat = $repeat
                rigOdf = $RigOdf
                buildingOdf = $BuildingOdf
                reduxVersion = $exeInfo.VersionInfo.FileVersion
                executableSha256 = $exeHash
                deployedWinmmSha256 = $shimHash
                openShimCommit = $commit
                launchMode = "GOG lcbench.bzn; forced windowed; Lua SetCommand RECYCLE"
                started = $started.ToString("o")
                processExitedBeforeTimeout = $exited
                stoppedByHarness = -not $exited
                sawStart = [bool](@($markers | Where-Object { $_ -match " START " }).Count)
                sawIssue = [bool](@($markers | Where-Object { $_ -match " ISSUE " }).Count)
                sawTargetDown = [bool](@($markers | Where-Object { $_ -match " TARGETDOWN " }).Count)
                sawResult = [bool]($complete.Count -gt 0)
                deployedAtEnd = $deployed
                movedAfterPoke = $moved
                stuckRigs = $stuck
                targetDownAt = $targetDownAt
                fixInstalled = $fixInstalled
                rigsUndeployedByFix = $undeployedByFix
                markers = $markers
                shimMarkers = $shimMarkers
            }
            $manifest | ConvertTo-Json -Depth 5 |
                Set-Content -LiteralPath (Join-Path $runRoot "manifest.json") -Encoding UTF8
            $runs += [pscustomobject]$manifest
        }
    }
} finally {
    $own = @(Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue |
        Where-Object { try { $_.Path -ieq $gameExe } catch { $false } })
    if ($own.Count -gt 0) { Stop-BZRGame -Id @($own.Id) }
    foreach ($name in $deployNames) {
        $live = Join-Path $missionRoot $name
        if ($present[$name]) {
            Copy-Item -LiteralPath (Join-Path $backupRoot $name) -Destination $live -Force
        } elseif (Test-Path -LiteralPath $live) {
            Remove-Item -LiteralPath $live -Force
        }
    }
    if ($installedBaseline -and (Test-Path -LiteralPath $missionRoot)) {
        Remove-Item -LiteralPath $missionRoot -Recurse -Force
    }
}

$runs | Select-Object case, repeat, sawStart, sawIssue, sawTargetDown, sawResult,
    deployedAtEnd, movedAfterPoke, stuckRigs, targetDownAt, fixInstalled, rigsUndeployedByFix |
    Export-Csv -LiteralPath (Join-Path $OutputRoot "summary.csv") -NoTypeInformation
Write-Host "Evidence: $OutputRoot"
$runs | Format-Table case, repeat, sawResult, deployedAtEnd, movedAfterPoke, stuckRigs, targetDownAt, fixInstalled, rigsUndeployedByFix
