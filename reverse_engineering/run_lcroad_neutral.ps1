# Safe runner for the lcbench neutral Attack-command matrix.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet("n2p", "a2n", "a2e", "a2f")]
    [string[]]$Cases = @("n2p", "a2n", "a2e", "a2f"),
    [ValidateRange(1, 20)]
    [int]$Repeats = 1,
    [ValidateRange(12, 120)]
    [int]$RunSeconds = 16,
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
    $OutputRoot = Join-Path $GameRoot "openshim_test_results\lcroad_neutral_$stamp"
}
if (-not (Test-Path -LiteralPath (Join-Path $missionRoot "lcbench.bzn"))) {
    throw "Existing lcbench baseline is not installed at $missionRoot"
}

$deployNames = @("lcbench.lua", "rmncfg.odf")
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

$exeInfo = Get-Item -LiteralPath $gameExe
$exeHash = (Get-FileHash -LiteralPath $gameExe -Algorithm SHA256).Hash
$shimHash = (Get-FileHash -LiteralPath $shimDll -Algorithm SHA256).Hash
$runs = @()

try {
    Copy-Item -LiteralPath (Join-Path $fixtureRoot "rmneut.lua") `
        -Destination (Join-Path $missionRoot "lcbench.lua") -Force

    foreach ($caseName in $Cases) {
        for ($repeat = 1; $repeat -le $Repeats; $repeat++) {
            if (Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue) {
                throw "Refusing to start while another Battlezone process is running"
            }
            $arm = "{0}_r{1:D2}" -f $caseName, $repeat
            $runRoot = Join-Path $OutputRoot $arm
            New-Item -ItemType Directory -Path $runRoot -Force | Out-Null
            [System.IO.File]::WriteAllText((Join-Path $missionRoot "rmncfg.odf"), @"
[Roadmap]
case = "$caseName"
commit = "$commit"
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
                $markers = @(Select-String -LiteralPath $bzPath -Pattern "\[LCROAD\]\[NEUT\]" |
                    ForEach-Object { $_.Line })
            }
            $markerText = $markers -join "`n"
            $manifest = [ordered]@{
                target = "neutral-attack-order-asymmetry"
                case = $caseName
                repeat = $repeat
                reduxVersion = $exeInfo.VersionInfo.FileVersion
                executableSha256 = $exeHash
                deployedWinmmSha256 = $shimHash
                openShimCommit = $commit
                launchMode = "GOG lcbench.bzn; forced windowed; Lua Attack"
                started = $started.ToString("o")
                processExitedBeforeTimeout = $exited
                stoppedByHarness = -not $exited
                sawStart = $markerText.Contains(" START ")
                sawIssue = $markerText.Contains(" ISSUE ")
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
        if ($present[$name]) {
            Copy-Item -LiteralPath (Join-Path $backupRoot $name) -Destination $live -Force
        } elseif (Test-Path -LiteralPath $live) {
            Remove-Item -LiteralPath $live -Force
        }
    }
}

$runs | Export-Csv -LiteralPath (Join-Path $OutputRoot "summary.csv") -NoTypeInformation
Write-Host "Evidence: $OutputRoot"
$runs | Format-Table case, repeat, processExitedBeforeTimeout, sawStart, sawIssue, sawResult

