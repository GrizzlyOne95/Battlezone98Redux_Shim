# Safe runner for the lcbench pilot hardpoint-ordering matrix.
# It overlays only the Lua/config/ODF files needed by this experiment, records
# evidence outside addon, and restores the exact prior files in finally.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet("pctl", "pcrft", "paftr", "prevs", "ppart")]
    [string[]]$Cases = @("pctl", "pcrft", "paftr", "prevs", "ppart"),
    [ValidateRange(1, 20)]
    [int]$Repeats = 1,
    [ValidateRange(8, 120)]
    [int]$RunSeconds = 14,
    [string]$OutputRoot = ""
)

$ErrorActionPreference = "Stop"
$env:BZR_FORCE_WINDOWED = "1"
. "$PSScriptRoot\BZRHarness.ps1"

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$shimDll = Join-Path $GameRoot "winmm.dll"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$fixtureRoot = Join-Path $PSScriptRoot "test_missions\lcbench_roadmap"
$logRoot = Join-Path $GameRoot "logs"
$commit = (git -C (Split-Path $PSScriptRoot -Parent) rev-parse --short=12 HEAD).Trim()
$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
if (-not $OutputRoot) {
    $OutputRoot = Join-Path $GameRoot "openshim_test_results\lcroad_pilot_$stamp"
}

if (-not (Test-Path -LiteralPath $gameExe)) { throw "Game not found: $gameExe" }
if (-not (Test-Path -LiteralPath (Join-Path $missionRoot "lcbench.bzn"))) {
    throw "Existing lcbench baseline is not installed at $missionRoot"
}

$fixtureNames = @("pctl.odf", "pcrft.odf", "paftr.odf", "prevs.odf", "ppart.odf")
$deployNames = @("lcbench.lua", "rmpcfg.odf") + $fixtureNames
$backupRoot = Join-Path $OutputRoot "pre_live"
New-Item -ItemType Directory -Path $backupRoot -Force | Out-Null
$originallyPresent = @{}

foreach ($name in $deployNames) {
    $live = Join-Path $missionRoot $name
    $originallyPresent[$name] = Test-Path -LiteralPath $live
    if ($originallyPresent[$name]) {
        Copy-Item -LiteralPath $live -Destination (Join-Path $backupRoot $name) -Force
    }
}

$exeInfo = Get-Item -LiteralPath $gameExe
$exeHash = (Get-FileHash -LiteralPath $gameExe -Algorithm SHA256).Hash
$shimHash = (Get-FileHash -LiteralPath $shimDll -Algorithm SHA256).Hash
$runs = @()

try {
    Copy-Item -LiteralPath (Join-Path $fixtureRoot "rmpilot.lua") `
        -Destination (Join-Path $missionRoot "lcbench.lua") -Force
    foreach ($name in $fixtureNames) {
        Copy-Item -LiteralPath (Join-Path $fixtureRoot $name) `
            -Destination (Join-Path $missionRoot $name) -Force
    }

    foreach ($caseName in $Cases) {
        for ($repeat = 1; $repeat -le $Repeats; $repeat++) {
            $existing = @(Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue)
            if ($existing.Count -gt 0) {
                throw "Refusing to start while another Battlezone process is running"
            }

            $arm = "{0}_r{1:D2}" -f $caseName, $repeat
            $runRoot = Join-Path $OutputRoot $arm
            New-Item -ItemType Directory -Path $runRoot -Force | Out-Null

            $config = @"
[Roadmap]
case = "$caseName"
commit = "$commit"
"@
            [System.IO.File]::WriteAllText((Join-Path $missionRoot "rmpcfg.odf"), $config)

            $beforeDumps = @{}
            Get-ChildItem -LiteralPath $logRoot -Filter "openshim_crash_*.dmp" `
                -ErrorAction SilentlyContinue | ForEach-Object {
                    $beforeDumps[$_.FullName] = $_.LastWriteTimeUtc
                }

            $started = Get-Date
            $process = Start-Process -FilePath $gameExe -ArgumentList "lcbench.bzn" `
                -WorkingDirectory $GameRoot -PassThru
            $exited = $process.WaitForExit($RunSeconds * 1000)
            if (-not $exited) {
                Stop-BZRGame -Id $process.Id
            }
            try { $process.Refresh() } catch { }
            $exitCode = if ($process.HasExited) { $process.ExitCode } else { $null }

            foreach ($logName in @("BZLogger.txt", "openshim.log", "openshim_crash.log")) {
                $source = Join-Path $logRoot $logName
                if (Test-Path -LiteralPath $source) {
                    Copy-Item -LiteralPath $source -Destination (Join-Path $runRoot $logName) -Force
                }
            }

            $newDumps = @()
            Get-ChildItem -LiteralPath $logRoot -Filter "openshim_crash_*.dmp" `
                -ErrorAction SilentlyContinue | ForEach-Object {
                    if (-not $beforeDumps.ContainsKey($_.FullName) -or
                        $_.LastWriteTimeUtc -gt $beforeDumps[$_.FullName]) {
                        Copy-Item -LiteralPath $_.FullName -Destination $runRoot -Force
                        $newDumps += $_.Name
                    }
                }

            $markers = @()
            $bzPath = Join-Path $runRoot "BZLogger.txt"
            if (Test-Path -LiteralPath $bzPath) {
                $markers = @(Select-String -LiteralPath $bzPath -Pattern "\[LCROAD\]\[PILOT\]" |
                    ForEach-Object { $_.Line })
            }
            $markerText = $markers -join "`n"

            $manifest = [ordered]@{
                target = "pilot-hardpoint-ordering"
                case = $caseName
                repeat = $repeat
                reduxVersion = $exeInfo.VersionInfo.FileVersion
                executableSha256 = $exeHash
                deployedWinmmSha256 = $shimHash
                openShimCommit = $commit
                launchMode = "GOG lcbench.bzn; forced windowed"
                started = $started.ToString("o")
                processExitedBeforeTimeout = $exited
                stoppedByHarness = -not $exited
                exitCode = $exitCode
                newMinidumps = $newDumps
                sawStart = $markerText.Contains(" START ")
                sawBeforeBuild = $markerText.Contains(" BEFORE_BUILD ")
                sawAfterBuild = $markerText.Contains(" AFTER_BUILD ")
                sawResult = $markerText.Contains(" RESULT ")
                markers = $markers
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
        if ($originallyPresent[$name]) {
            Copy-Item -LiteralPath (Join-Path $backupRoot $name) -Destination $live -Force
        } elseif (Test-Path -LiteralPath $live) {
            Remove-Item -LiteralPath $live -Force
        }
    }
}

$runs | Export-Csv -LiteralPath (Join-Path $OutputRoot "summary.csv") -NoTypeInformation
Write-Host "Evidence: $OutputRoot"
$runs | Format-Table case, repeat, processExitedBeforeTimeout, exitCode, newMinidumps
