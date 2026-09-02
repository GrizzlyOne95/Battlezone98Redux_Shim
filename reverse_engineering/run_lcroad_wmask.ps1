# Safe runner for lcbench weaponMask same-class hardpoint matrix.
# Overlays ODF fixtures and Lua, records evidence outside addon, restores in finally.
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateSet("hstk","hwh1","hwh2","hwh3","hwh4","hwh5","hwh6","hwh7","hwh8","hwv2","hwv4","mstk","mnm1","mnm2","mnm3","mnm4","mnm5","mnm6","mnm7")]
    [string[]]$Cases = @("hstk","hwh5","hwh6","hwv2","hwh3","hwv4","mstk","mnm5","mnm6","mnm3"),
    [switch]$All,
    [ValidateRange(1,20)][int]$Repeats = 1,
    [ValidateRange(8,240)][int]$RunSeconds = 62,
    [string]$OutputRoot = "",
    [switch]$EnableWeaponMaskFix
)

$ErrorActionPreference = "Stop"
$env:BZR_FORCE_WINDOWED = "1"
. "$PSScriptRoot\BZRHarness.ps1"

if ($All) {
    $Cases = @("hstk","hwh5","hwh6","hwv2","hwh3","hwv4","mstk","mnm5","mnm6","mnm3")
}

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$shimDll = Join-Path $GameRoot "winmm.dll"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$fixtureRoot = Join-Path $PSScriptRoot "test_missions\lcbench_wmask"
$logRoot = Join-Path $GameRoot "logs"
$commit = (git -C (Split-Path $PSScriptRoot -Parent) rev-parse --short=12 HEAD).Trim()
$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
if (-not $OutputRoot) {
    $OutputRoot = Join-Path $GameRoot "openshim_test_results\lcroad_wmask_$stamp"
}
if (-not (Test-Path -LiteralPath $gameExe)) { throw "Game not found: $gameExe" }
if (-not (Test-Path -LiteralPath (Join-Path $missionRoot "lcbench.bzn"))) {
    throw "Existing lcbench baseline is not installed at $missionRoot"
}

$fixtureNames = @("hwh1.odf","hwh2.odf","hwh3.odf","hwh4.odf","hwh5.odf","hwh6.odf","hwh7.odf","hwh8.odf","hwv2.odf","hwv4.odf","mnm1.odf","mnm2.odf","mnm3.odf","mnm4.odf","mnm5.odf","mnm6.odf","mnm7.odf")
$deployNames = @("lcbench.lua","rmwcfg.odf") + $fixtureNames
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

# handle ini toggle for weaponMask fix: [SinglePlayer] AiWeaponMaskSelection=1
$iniPath = Join-Path $GameRoot "openshim.ini"
$iniBackup = $null
$iniWasPatched = $false
if ($EnableWeaponMaskFix) {
    if (Test-Path -LiteralPath $iniPath) {
        $iniOriginal = Get-Content -LiteralPath $iniPath -Raw -ErrorAction SilentlyContinue
        $iniBackup = $iniOriginal
        if ($iniOriginal -notmatch "(?m)^\[SinglePlayer\]") {
            $iniOriginal += "`r`n[SinglePlayer]`r`n"
        }
        foreach ($key in @("AiWeaponMaskArtillery", "AiWeaponMaskMinelayer")) {
            if ($iniOriginal -match "(?m)^$key\s*=") {
                $iniOriginal = $iniOriginal -replace "(?m)^$key\s*=.*$", "$key=1"
            } else {
                $iniOriginal = $iniOriginal -replace "(?m)^(\[SinglePlayer\])", "`$1`r`n$key=1"
            }
        }
        Set-Content -LiteralPath $iniPath -Value $iniOriginal -Encoding ASCII
        $iniWasPatched = $true
        Write-Host "[WMASK] Enabled AiWeaponMaskArtillery=1 and AiWeaponMaskMinelayer=1 in $iniPath (single-player gate still applies)"
    } else {
        Write-Warning "No openshim.ini at $iniPath , fix gate remains default OFF"
    }
}

$exeInfo = Get-Item -LiteralPath $gameExe
$exeHash = (Get-FileHash -LiteralPath $gameExe -Algorithm SHA256).Hash
$shimHash = (Get-FileHash -LiteralPath $shimDll -Algorithm SHA256).Hash
$runs = @()

try {
    Copy-Item -LiteralPath (Join-Path $fixtureRoot "rmwmask.lua") -Destination (Join-Path $missionRoot "lcbench.lua") -Force
    foreach ($name in $fixtureNames) {
        Copy-Item -LiteralPath (Join-Path $fixtureRoot $name) -Destination (Join-Path $missionRoot $name) -Force
    }
    # ensure clean rmwcfg
    if (Test-Path -LiteralPath (Join-Path $missionRoot "rmwcfg.odf")) {
        Remove-Item -LiteralPath (Join-Path $missionRoot "rmwcfg.odf") -Force -ErrorAction SilentlyContinue
    }

    foreach ($caseName in $Cases) {
        for ($repeat=1; $repeat -le $Repeats; $repeat++) {
            $existing = @(Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue)
            if ($existing.Count -gt 0) { throw "Refusing to start while another Battlezone process is running" }

            $arm = "{0}_r{1:D2}" -f $caseName, $repeat
            $runRoot = Join-Path $OutputRoot $arm
            New-Item -ItemType Directory -Path $runRoot -Force | Out-Null

            $config = @"
[Roadmap]
case = "$caseName"
commit = "$commit"
"@
            [System.IO.File]::WriteAllText((Join-Path $missionRoot "rmwcfg.odf"), $config)

            $beforeDumps = @{}
            Get-ChildItem -LiteralPath $logRoot -Filter "openshim_crash_*.dmp" -ErrorAction SilentlyContinue | ForEach-Object {
                $beforeDumps[$_.FullName] = $_.LastWriteTimeUtc
            }

            $started = Get-Date
            $process = Start-Process -FilePath $gameExe -ArgumentList "lcbench.bzn" -WorkingDirectory $GameRoot -PassThru
            $exited = $process.WaitForExit($RunSeconds * 1000)
            if (-not $exited) {
                Stop-BZRGame -Id $process.Id
            }
            try { $process.Refresh() } catch {}
            $exitCode = if ($process.HasExited) { $process.ExitCode } else { $null }

            foreach ($logName in @("BZLogger.txt","openshim.log","openshim_crash.log")) {
                $source = Join-Path $logRoot $logName
                if (Test-Path -LiteralPath $source) {
                    Copy-Item -LiteralPath $source -Destination (Join-Path $runRoot $logName) -Force
                }
            }
            $newDumps = @()
            Get-ChildItem -LiteralPath $logRoot -Filter "openshim_crash_*.dmp" -ErrorAction SilentlyContinue | ForEach-Object {
                if (-not $beforeDumps.ContainsKey($_.FullName) -or $_.LastWriteTimeUtc -gt $beforeDumps[$_.FullName]) {
                    Copy-Item -LiteralPath $_.FullName -Destination $runRoot -Force
                    $newDumps += $_.Name
                }
            }
            $markers = @()
            $bzPath = Join-Path $runRoot "BZLogger.txt"
            if (Test-Path -LiteralPath $bzPath) {
                $markers = @(Select-String -LiteralPath $bzPath -Pattern "\[WMASK\]" | ForEach-Object { $_.Line })
            }
            $markerText = $markers -join "`n"
            $manifest = [ordered]@{
                target = "weaponMask-same-class"
                case = $caseName
                repeat = $repeat
                reduxVersion = $exeInfo.VersionInfo.FileVersion
                executableSha256 = $exeHash
                deployedWinmmSha256 = $shimHash
                openShimCommit = $commit
                weaponMaskFixEnabled = $EnableWeaponMaskFix.IsPresent
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
                sawCreated = $markerText.Contains(" CREATE ")
                markers = $markers
            }
            $manifest | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath (Join-Path $runRoot "manifest.json") -Encoding UTF8
            $runs += [pscustomobject]$manifest
            Write-Host "Case $caseName r$repeat markers=$($markers.Count) sawResult=$($manifest.sawResult) exit=$exitCode"
        }
    }
} finally {
    $own = @(Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue | Where-Object { try { $_.Path -ieq $gameExe } catch { $false } })
    if ($own.Count -gt 0) { Stop-BZRGame -Id @($own.Id) }
    foreach ($name in $deployNames) {
        $live = Join-Path $missionRoot $name
        if ($originallyPresent[$name]) {
            Copy-Item -LiteralPath (Join-Path $backupRoot $name) -Destination $live -Force
        } elseif (Test-Path -LiteralPath $live) {
            Remove-Item -LiteralPath $live -Force
        }
    }
    if ($iniWasPatched -and $iniBackup -ne $null) {
        Set-Content -LiteralPath $iniPath -Value $iniBackup -Encoding ASCII
        Write-Host "[WMASK] Restored openshim.ini"
    }
}

$runs | Export-Csv -LiteralPath (Join-Path $OutputRoot "summary.csv") -NoTypeInformation
Write-Host "Evidence: $OutputRoot"
$runs | Format-Table case, repeat, sawStart, sawResult, sawCreated, newMinidumps
