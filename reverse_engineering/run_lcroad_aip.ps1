# Safe runner for the lcbench AIP mixed stock/custom producer matrix.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet("sps", "spc", "spms", "spmc", "cps", "cpc", "cpms", "cpmc", "mp2", "ss2", "cc2", "posc", "bldc", "blds", "allc", "alls", "ccak")]
    [string[]]$Cases = @("sps", "spc", "spms", "spmc", "cps", "cpc", "cpms", "cpmc", "mp2", "ss2", "cc2", "posc", "ccak"),
    [ValidateRange(1, 20)]
    [int]$Repeats = 1,
    [ValidateRange(30, 240)]
    [int]$RunSeconds = 110,
    [string]$OutputRoot = "",
    [string]$WerDumpRoot = "C:\BZDumps",
    # Turns on the shim's [AIPRES] probe around PREREQ_WhatIs for the duration
    # of the run. openshim.ini is backed up and restored with the fixtures.
    [switch]$AipResolveTrace
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
              "cps.aip", "cpc.aip", "cpms.aip", "cpmc.aip", "mp2.aip",
              "ss2.aip", "cc2.aip", "posc.aip", "bldc.aip", "blds.aip", "allc.aip", "alls.aip", "ccak.aip")
# svrecy.odf is an OVERRIDE of the stock recycler that widens its build list to
# the same two-item menu the custom producer offers. It is installed only for
# the arms that need the stock-named producer to be able to offer the custom
# unit at all; "sps" is deliberately left on the untouched stock factory.
$overrideArms = @("sps", "spc", "spms", "spmc", "mp2", "ss2", "cc2", "bldc", "blds", "allc", "alls")
# posc deploys the customs-FIRST menu instead, to test whether build-slot
# position rather than ODF origin is what gates the custom unit.
$menuFirstArms = @("posc")
$deployNames = @("lcbench.lua", "rmacfg.odf", "mxfigh.odf", "mxturr.odf", "mxrecy.odf", "svrecy.odf", "svrecyf.odf") + $aipNames

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

$shimIni = Join-Path $GameRoot "openshim.ini"
$shimIniBackup = Join-Path $backupRoot "openshim.ini"
$shimIniPresent = Test-Path -LiteralPath $shimIni
if ($shimIniPresent) {
    Copy-Item -LiteralPath $shimIni -Destination $shimIniBackup -Force
}
if ($AipResolveTrace) {
    if (-not $shimIniPresent) { throw "openshim.ini is not installed at $shimIni" }
    Add-Type -Namespace Win -Name Ini -MemberDefinition @'
[System.Runtime.InteropServices.DllImport("kernel32.dll", CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
public static extern bool WritePrivateProfileString(string section, string key, string val, string file);
'@
    [void][Win.Ini]::WritePrivateProfileString("Diagnostics", "AipResolveTrace", "1", $shimIni)
}

$exeInfo = Get-Item -LiteralPath $gameExe
$exeHash = (Get-FileHash -LiteralPath $gameExe -Algorithm SHA256).Hash
$shimHash = (Get-FileHash -LiteralPath $shimDll -Algorithm SHA256).Hash

# The shim reads its patch table from the GAME's scripts\patches.json, not the
# repo's. A stale deployed copy silently drops every patch the working tree
# added -- the shim only says so in one [STALE-CONFIG] line deep in its log --
# so surface the mismatch here instead.
$livePatchesJson = Join-Path $GameRoot "scripts\patches.json"
$repoPatchesJson = Join-Path (Split-Path $PSScriptRoot -Parent) "scripts\patches.json"
$patchesHash = $null
$patchesMatchRepo = $null
if ((Test-Path -LiteralPath $livePatchesJson) -and (Test-Path -LiteralPath $repoPatchesJson)) {
    $patchesHash = (Get-FileHash -LiteralPath $livePatchesJson -Algorithm SHA256).Hash
    $repoPatchesHash = (Get-FileHash -LiteralPath $repoPatchesJson -Algorithm SHA256).Hash
    $patchesMatchRepo = ($patchesHash -eq $repoPatchesHash)
    if (-not $patchesMatchRepo) {
        Write-Warning ("Deployed scripts\patches.json does not match the repo copy. " +
            "Patches added in the working tree will NOT be installed for this run.")
    }
}
$runs = @()

try {
    Copy-Item -LiteralPath (Join-Path $fixtureRoot "rmaip.lua") `
        -Destination (Join-Path $missionRoot "lcbench.lua") -Force
    foreach ($name in @("mxfigh.odf", "mxturr.odf", "mxrecy.odf") + $aipNames) {
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
            $usesOverride = ($overrideArms -contains $caseName) -or ($menuFirstArms -contains $caseName)
            if ($usesOverride) {
                $srcMenu = if ($menuFirstArms -contains $caseName) { "svrecyf.odf" } else { "svrecy.odf" }
                Copy-Item -LiteralPath (Join-Path $fixtureRoot $srcMenu) `
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

            # openshim.log is appended to across runs, so remember where this
            # arm starts and slice from there rather than re-reading earlier arms.
            $shimLogPath = Join-Path $logRoot "openshim.log"
            $shimLogStart = 0
            if (Test-Path -LiteralPath $shimLogPath) {
                $shimLogStart = (Get-Item -LiteralPath $shimLogPath).Length
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

            # [AIPRES] is the shim's PREREQ_WhatIs probe: one line per AIP
            # construction-program item name plus a one-shot census of every
            # name the strategic AI can resolve at all.
            $aipResolve = @()
            if (Test-Path -LiteralPath $shimLogPath) {
                $stream = [System.IO.File]::Open($shimLogPath, 'Open', 'Read', 'ReadWrite')
                try {
                    # The shim truncates openshim.log on startup, so a start
                    # offset past the current end means the file rotated and
                    # the whole of it belongs to this arm.
                    if ($shimLogStart -gt $stream.Length) { $shimLogStart = 0 }
                    if ($shimLogStart -lt $stream.Length) {
                        [void]$stream.Seek($shimLogStart, 'Begin')
                        $reader = New-Object System.IO.StreamReader($stream)
                        $slice = $reader.ReadToEnd()
                        $aipResolve = @($slice -split "`r?`n" | Where-Object { $_ -match "\[AIPRES\]" })
                    }
                } finally { $stream.Dispose() }
                if ($aipResolve.Count -gt 0) {
                    Set-Content -LiteralPath (Join-Path $runRoot "aipres.txt") `
                        -Value $aipResolve -Encoding UTF8
                }
            }

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
                deployedPatchesJsonSha256 = $patchesHash
                deployedPatchesJsonMatchesRepo = $patchesMatchRepo
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
                aipResolveTrace = [bool]$AipResolveTrace
                aipResolveMisses = @($aipResolve | Where-Object { $_ -match "\[AIPRES\] MISS" }).Count
                aipResolveLines = $aipResolve.Count
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
    if ($shimIniPresent) {
        Copy-Item -LiteralPath $shimIniBackup -Destination $shimIni -Force
    }
}

$runs | Export-Csv -LiteralPath (Join-Path $OutputRoot "summary.csv") -NoTypeInformation
Write-Host "Evidence: $OutputRoot"
$runs | Format-Table case, repeat, usesStockFactoryOverride, sawResult, stockBuilt, customBuilt, looksLikeCrash
