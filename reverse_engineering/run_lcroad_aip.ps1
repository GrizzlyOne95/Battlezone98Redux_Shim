# Safe runner for the lcbench AIP mixed stock/custom producer matrix.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet("sps", "spc", "spms", "spmc", "cps", "cpc", "cpms", "cpmc", "mp2", "ccak")]
    [string[]]$Cases = @("sps", "spc", "spms", "spmc", "cps", "cpc", "cpms", "cpmc", "mp2", "ccak"),
    [ValidateRange(1, 20)]
    [int]$Repeats = 1,
    [ValidateRange(30, 240)]
    [int]$RunSeconds = 110,
    [string]$OutputRoot = "",
    [string]$WerDumpRoot = "C:\BZDumps"
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
    $OutputRoot = Join-Path $GameRoot "openshim_test_results\lcroad_aip_$stamp"
}
if (-not (Test-Path -LiteralPath (Join-Path $missionRoot "lcbench.bzn"))) {
    throw "Existing lcbench baseline is not installed at $missionRoot"
}

$aipNames = @("sps.aip", "spc.aip", "spms.aip", "spmc.aip",
              "cps.aip", "cpc.aip", "cpms.aip", "cpmc.aip", "mp2.aip", "ccak.aip")
# svrecy.odf is an OVERRIDE of the stock recycler that widens its build list to
# the same two-item menu the custom producer offers. It is installed only for
# the arms that need the stock-named producer to be able to offer the custom
# unit at all; "sps" is deliberately left on the untouched stock factory.
$overrideArms = @("sps", "spc", "spms", "spmc", "mp2")
$deployNames = @("lcbench.lua", "rmacfg.odf", "mxfigh.odf", "mxrecy.odf", "svrecy.odf") + $aipNames

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
    Copy-Item -LiteralPath (Join-Path $fixtureRoot "rmaip.lua") `
        -Destination (Join-Path $missionRoot "lcbench.lua") -Force
    foreach ($name in @("mxfigh.odf", "mxrecy.odf") + $aipNames) {
        Copy-Item -LiteralPath (Join-Path $fixtureRoot $name) `
            -Destination (Join-Path $missionRoot $name) -Force
    }

    foreach ($caseName in $Cases) {
        for ($repeat = 1; $repeat -le $Repeats; $repeat++) {
            if (Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue) {
                throw "Refusing to start while another Battlezone process is running"
            }
            $arm = "{0}_r{1:D2}" -f $caseName, $repeat
            $runRoot = Join-Path $OutputRoot $arm
            New-Item -ItemType Directory -Path $runRoot -Force | Out-Null

            $liveOverride = Join-Path $missionRoot "svrecy.odf"
            $usesOverride = $overrideArms -contains $caseName
            if ($usesOverride) {
                Copy-Item -LiteralPath (Join-Path $fixtureRoot "svrecy.odf") `
                    -Destination $liveOverride -Force
            } elseif (Test-Path -LiteralPath $liveOverride) {
                Remove-Item -LiteralPath $liveOverride -Force
            }

            [System.IO.File]::WriteAllText((Join-Path $missionRoot "rmacfg.odf"), @"
[Roadmap]
case = "$caseName"
commit = "$commit"
"@)

            $beforeDumps = @{}
            Get-ChildItem -LiteralPath $logRoot -Filter "openshim_crash_*.dmp" `
                -ErrorAction SilentlyContinue | ForEach-Object {
                    $beforeDumps[$_.FullName] = $_.LastWriteTimeUtc
                }
            $beforeWer = @{}
            if (Test-Path -LiteralPath $WerDumpRoot) {
                Get-ChildItem -LiteralPath $WerDumpRoot -Filter "*.dmp" `
                    -ErrorAction SilentlyContinue | ForEach-Object {
                        $beforeWer[$_.FullName] = $_.LastWriteTimeUtc
                    }
            }

            $started = Get-Date
            $process = Start-Process -FilePath $gameExe -ArgumentList "lcbench.bzn" `
                -WorkingDirectory $GameRoot -PassThru
            $exited = $process.WaitForExit($RunSeconds * 1000)
            if (-not $exited) { Stop-BZRGame -Id $process.Id }
            try { $process.Refresh() } catch { }

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
            # WER writes one full dump per dead process to C:\BZDumps --
            # including processes the harness terminates normally at timeout.
            # A dump here is therefore NOT by itself evidence of a crash; it is
            # recorded for correlation only. The real crash signals are a shim
            # dump in logs\, or an early exit without a RESULT marker.
            $newWerDumps = @()
            if (Test-Path -LiteralPath $WerDumpRoot) {
                Get-ChildItem -LiteralPath $WerDumpRoot -Filter "*.dmp" `
                    -ErrorAction SilentlyContinue | ForEach-Object {
                        if (-not $beforeWer.ContainsKey($_.FullName) -or
                            $_.LastWriteTimeUtc -gt $beforeWer[$_.FullName]) {
                            $newWerDumps += $_.FullName
                        }
                    }
            }

            $markers = @()
            $bzPath = Join-Path $runRoot "BZLogger.txt"
            if (Test-Path -LiteralPath $bzPath) {
                $markers = @(Select-String -LiteralPath $bzPath -Pattern "\[LCROAD\]\[AIP\]" |
                    ForEach-Object { $_.Line })
            }
            $markerText = $markers -join "`n"

            $stockBuilt = $null
            $customBuilt = $null
            $completeLine = $markers | Where-Object { $_ -match "COMPLETE" } | Select-Object -Last 1
            if ($completeLine -match "stock=(\d+)\s+custom=(\d+)") {
                $stockBuilt = [int]$Matches[1]
                $customBuilt = [int]$Matches[2]
            }

            # Only a shim dump, or an unexpected early exit, indicates a crash.
            $crashed = ($newDumps.Count -gt 0) -or
                       ($exited -and -not $markerText.Contains(" RESULT "))

            $manifest = [ordered]@{
                target = "aip-mixed-stock-custom-producer"
                looksLikeCrash = $crashed
                case = $caseName
                repeat = $repeat
                usesStockFactoryOverride = $usesOverride
                reduxVersion = $exeInfo.VersionInfo.FileVersion
                executableSha256 = $exeHash
                deployedWinmmSha256 = $shimHash
                openShimCommit = $commit
                launchMode = "GOG lcbench.bzn; forced windowed; SetAIP team 2"
                started = $started.ToString("o")
                processExitedBeforeTimeout = $exited
                stoppedByHarness = -not $exited
                sawStart = $markerText.Contains(" START ")
                sawAipInstalled = $markerText.Contains(" AIP INSTALLED ")
                sawResult = $markerText.Contains(" RESULT ")
                stockBuilt = $stockBuilt
                customBuilt = $customBuilt
                shimCrashDumps = $newDumps
                werCrashDumps = $newWerDumps
                markers = $markers
            }
            $manifest | ConvertTo-Json -Depth 5 |
                Set-Content -LiteralPath (Join-Path $runRoot "manifest.json") -Encoding UTF8
            $runs += [pscustomobject]$manifest

            if ($crashed) {
                Write-Warning ("Arm {0} looks like a CRASH. Shim dumps: {1}. Correlate WER: {2}" -f `
                    $arm, ($newDumps -join ', '), ($newWerDumps -join ', '))
            }
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
$runs | Format-Table case, repeat, usesStockFactoryOverride, sawResult, stockBuilt, customBuilt, looksLikeCrash
