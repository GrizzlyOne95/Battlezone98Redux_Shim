# Live test for [SinglePlayer] HowitzerAttackApproach: loads the lcbench world
# with the howitzerapproach.lua overlay, which builds a friendly avartl, an enemy
# svrecy EnemyGap m beyond it (out of shell reach) and an unarmed enemy decoy
# beside the path, and orders Attack(avartl, svrecy) at T+3. With the feature on
# the howitzer should pack up, drive, deploy in reach and fire, keeping the
# ordered target as it passes the decoy; off, it should stay put (stock "out of
# range"). Debug only; it deploys addon/lcbench/lcbench.lua and restores the
# prior file and openshim.ini when the game exits. Requires the lcbench
# baseline in addon\lcbench and the build deployed to the game.
#
#   pwsh -File reverse_engineering/run_lchowapproach.ps1              # feature on
#   pwsh -File reverse_engineering/run_lchowapproach.ps1 -FeatureOff  # A/B: stock out of range
#   pwsh -File reverse_engineering/run_lchowapproach.ps1 -SaveLoad    # save mid-drive, load, resume
#
# -SaveLoad runs two launches. The first lets OpenShim's autosave write
# Save\auto.sav while the approach is driving (InitialDelaySeconds = 10), copies
# it to Save\lchowa_saveload.sav and stops; the second loads that copy (the
# engine's LoadGame path, positional argument) with the autosave off and runs
# -RunSeconds. The overlay's Save/Load keeps the mission state across the
# load. Save\auto* files are backed up and restored, and the copy removed.
# -StopAfterLoad N orders Stop N s after the load, ending the attack state
# while the approach still drives (exercises EndAttack on a restored task).
#
# Runs in the background (never takes the foreground): RunInBackground is set
# to 1 for the run. Takes bzr_livetest.lock in the game root and refuses if
# another holder has it. Use Stop-BZRGame, never kill the process.

param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [ValidateRange(0, 300)]
    [int]$RunSeconds = 170,   # ~18 s of loading + the 130 s script
    [switch]$FeatureOff,
    [switch]$SaveLoad,
    [ValidateRange(0, 60)]
    [int]$StopAfterLoad = 0,  # -SaveLoad only: order Stop this many seconds after the load (0 = never)
    [ValidateRange(15, 120)]
    [int]$SaveTimeoutSeconds = 60,
    [ValidateRange(50, 1200)]
    [int]$EnemyGap = 800,
    [string]$OutputRoot = ""
)

$ErrorActionPreference = "Stop"
$env:BZR_FORCE_WINDOWED = "1"
$env:OPENSHIM_RUN_IN_BACKGROUND = "1"
. "$PSScriptRoot\BZRHarness.ps1"

$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$missionRoot = Join-Path $GameRoot "addon\lcbench"
$overlay = Join-Path $PSScriptRoot "test_missions\lcbench_howitzerapproach\howitzerapproach.lua"
$ini = Join-Path $GameRoot "openshim.ini"
$logRoot = Join-Path $GameRoot "logs"
$lock = Join-Path $GameRoot "bzr_livetest.lock"
$watchdog = Join-Path $env:TEMP "bzr_foreground_watchdog.log"
$watchdogStart = if (Test-Path -LiteralPath $watchdog) { @(Get-Content -LiteralPath $watchdog).Count } else { 0 }
$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
$tag = if ($FeatureOff) { "off" } else { "on" }
if ($SaveLoad) { $tag += "_saveload" }
if ($StopAfterLoad -gt 0) {
    if (-not $SaveLoad) { throw "-StopAfterLoad needs -SaveLoad" }
    $tag += "_stop"
}
if (-not $OutputRoot) { $OutputRoot = Join-Path $GameRoot "openshim_test_results\lchowapproach_${tag}_$stamp" }

if (-not (Test-Path -LiteralPath $gameExe)) { throw "Game not found: $gameExe" }
if (-not (Test-Path -LiteralPath (Join-Path $missionRoot "lcbench.bzn"))) {
    throw "The lcbench baseline is not installed at $missionRoot"
}
if (@(Get-Process -Name "battlezone98redux" -ErrorAction SilentlyContinue).Count -gt 0) {
    throw "Refusing to start while another Battlezone process is running"
}
# CreateNew takes the lock atomically: it fails if another holder has it.
try {
    $stream = [IO.File]::Open($lock, [IO.FileMode]::CreateNew, [IO.FileAccess]::Write)
} catch {
    throw "Live-test lock held: $(Get-Content -LiteralPath $lock -Raw -ErrorAction SilentlyContinue)"
}
$bytes = [Text.Encoding]::UTF8.GetBytes("run_lchowapproach.ps1 pid=$PID $(Get-Date -Format o)")
$stream.Write($bytes, 0, $bytes.Length)
$stream.Dispose()
$process = $null
$saveRoot = Join-Path $GameRoot "Save"
$saveCopy = Join-Path $saveRoot "lchowa_saveload.sav"
$saveBackup = Join-Path $OutputRoot "save.orig"

# The game holds its logs open for writing.
function Read-SharedText([string]$Path) {
    if (-not (Test-Path -LiteralPath $Path)) { return "" }
    $fs = [IO.FileStream]::new($Path, [IO.FileMode]::Open, [IO.FileAccess]::Read,
        [IO.FileShare]::ReadWrite -bor [IO.FileShare]::Delete)
    try { return [IO.StreamReader]::new($fs).ReadToEnd() } finally { $fs.Dispose() }
}
function Set-AutoSaveIni([int]$Enabled) {
    $t = [IO.File]::ReadAllText($ini)
    $values = [ordered]@{ Enabled = $Enabled; InitialDelaySeconds = 10; IntervalSeconds = 3600; BackupExisting = 0; RespectExternalAutoSave = 0 }
    if ($t -notmatch '(?m)^\[AutoSave\]\s*$') { $t = $t.TrimEnd() + "`r`n`r`n[AutoSave]`r`n" }
    foreach ($k in $values.Keys) {
        $section = [regex]::Match($t, '(?ms)^\[AutoSave\]\s*$.*?(?=^\[|\z)')
        $body = $section.Value
        $line = "$k = $($values[$k])"
        if ($body -match "(?m)^\s*$k\s*=") { $body = [regex]::Replace($body, "(?m)^\s*$k\s*=.*$", $line) }
        else { $body = [regex]::Replace($body, '(?m)^\[AutoSave\]\s*$', "[AutoSave]`r`n$line", 1) }
        $t = $t.Substring(0, $section.Index) + $body + $t.Substring($section.Index + $section.Length)
    }
    [IO.File]::WriteAllText($ini, $t)
}
function Copy-RunLogs([string]$Suffix) {
    foreach ($name in @("BZLogger.txt", "openshim.log")) {
        $source = Join-Path $logRoot $name
        if (Test-Path -LiteralPath $source) {
            $leaf = [IO.Path]::GetFileNameWithoutExtension($name) + $Suffix + [IO.Path]::GetExtension($name)
            Copy-Item -LiteralPath $source -Destination (Join-Path $OutputRoot $leaf) -Force
        }
    }
}

$live = Join-Path $missionRoot "lcbench.lua"
$had = Test-Path -LiteralPath $live
$iniBackup = Join-Path $OutputRoot "openshim.ini.orig"
try {
    New-Item -ItemType Directory -Path $OutputRoot -Force | Out-Null
    if ($had) { Copy-Item -LiteralPath $live -Destination (Join-Path $OutputRoot "lcbench.lua.orig") -Force }
    Copy-Item -LiteralPath $ini -Destination $iniBackup -Force
    if ($SaveLoad) {
        New-Item -ItemType Directory -Path $saveBackup -Force | Out-Null
        foreach ($f in @(Get-ChildItem -LiteralPath $saveRoot -File -Filter "auto*")) {
            Copy-Item -LiteralPath $f.FullName -Destination (Join-Path $saveBackup $f.Name) -Force
        }
    }

    $prefix = "EnemyGap = $EnemyGap`n"
    if ($StopAfterLoad -gt 0) { $prefix += "StopAfterLoad = $StopAfterLoad`n" }
    [IO.File]::WriteAllText($live, $prefix + [IO.File]::ReadAllText($overlay))
    $text = [IO.File]::ReadAllText($ini)
    $text = [regex]::Replace($text, '(?m)^(\s*RunInBackground\s*=\s*)0\b', '${1}1')
    $value = if ($FeatureOff) { '0' } else { '1' }
    if ($text -match '(?m)^\s*HowitzerAttackApproach\s*=') {
        $text = [regex]::Replace($text, '(?m)^(\s*HowitzerAttackApproach\s*=\s*)\d\b', "`${1}$value")
    } else {
        $text = [regex]::Replace($text, '(?m)^\[SinglePlayer\]\s*$', "[SinglePlayer]`r`nHowitzerAttackApproach = $value", 1)
        if ($text -notmatch '(?m)^\s*HowitzerAttackApproach\s*=') { throw "[SinglePlayer] not found in $ini" }
    }
    [IO.File]::WriteAllText($ini, $text)

    $dll = Join-Path $GameRoot "plugins\openshim.dll"
    Write-Host "openshim.dll SHA256: $((Get-FileHash -LiteralPath $dll -Algorithm SHA256).Hash)"
    Assert-BZRSafeToLaunch   # refuses unless the game cannot steal foreground/mouse; starts the watchdog
    if ($SaveLoad) {
        # Launch 1: autosave mid-drive, then stop.
        Set-AutoSaveIni 1
        $process = Start-BZRGameProcess -FilePath $gameExe -ArgumentList "lcbench.bzn" -WorkingDirectory $GameRoot -PassThru
        $deadline = (Get-Date).AddSeconds(20 + $SaveTimeoutSeconds)
        $saved = $false
        while (-not $process.HasExited -and (Get-Date) -lt $deadline) {
            Start-Sleep -Milliseconds 500
            $shim = Read-SharedText (Join-Path $logRoot "openshim.log")
            if ($shim -match "\[pid:$($process.Id) [^\]]*\] \[INFO\] \[autosave\] Saved .*auto\.sav") { $saved = $true; break }
        }
        if ($saved) { Copy-Item -LiteralPath (Join-Path $saveRoot "auto.sav") -Destination $saveCopy -Force }
        Start-Sleep -Seconds 2
        if (-not $process.HasExited) { Stop-BZRGame -Id $process.Id }
        $process.WaitForExit(30000) | Out-Null
        Copy-RunLogs ".save"
        if (-not $saved) { throw "FIXTURE: the autosave did not land within $SaveTimeoutSeconds s of the mission" }
        Copy-Item -LiteralPath $saveCopy -Destination (Join-Path $OutputRoot "lchowa_saveload.sav") -Force
        $phaseLines = @([regex]::Matches((Get-Content -LiteralPath (Join-Path $OutputRoot "openshim.save.log") -Raw),
            '(?m)^.*(\[HOWAPPR\] \w+ -> \w+|\[autosave\] Saved).*$') | ForEach-Object { $_.Value.Trim() } |
            Where-Object { $_ -match "\[pid:$($process.Id) " })
        $phaseLines | ForEach-Object { Write-Host "  save run: $_" }
        # Precondition: the save landed while the approach was driving.
        $atSave = ""
        foreach ($l in $phaseLines) {
            if ($l -match '\[autosave\] Saved') { break }
            if ($l -match '-> (\w+) process') { $atSave = $Matches[1] }
        }
        Write-Host "Phase when the save landed: $atSave"
        if ($atSave -ne "drive" -and -not $FeatureOff) { Write-Warning "FIXTURE: the save did not land mid-drive (phase '$atSave'); results are not evidence." }

        # Launch 2: load that save, autosave off.
        Set-AutoSaveIni 0
        Write-Host "openshim.dll SHA256: $((Get-FileHash -LiteralPath $dll -Algorithm SHA256).Hash)"
        $process = Start-BZRGameProcess -FilePath $gameExe -ArgumentList "Save\lchowa_saveload.sav" -WorkingDirectory $GameRoot -PassThru
    } else {
        $process = Start-BZRGameProcess -FilePath $gameExe -ArgumentList "lcbench.bzn" -WorkingDirectory $GameRoot -PassThru
    }
    if ($RunSeconds -gt 0) {
        if (-not $process.WaitForExit($RunSeconds * 1000)) { Stop-BZRGame -Id $process.Id }
    } else {
        $process.WaitForExit()
    }
} finally {
    # Only the PID this run started.
    if ($process -and -not $process.HasExited) { Stop-BZRGame -Id $process.Id }
    # The game may still be writing auto.sav or the ini while it exits.
    if ($process) { $process.WaitForExit(30000) | Out-Null }
    if (Test-Path -LiteralPath $iniBackup) { Copy-Item -LiteralPath $iniBackup -Destination $ini -Force }
    if ($SaveLoad -and (Test-Path -LiteralPath $saveBackup)) {
        try {
            foreach ($f in @(Get-ChildItem -LiteralPath $saveRoot -File -Filter "auto*")) {
                if (-not (Test-Path -LiteralPath (Join-Path $saveBackup $f.Name))) { Remove-Item -LiteralPath $f.FullName -Force }
            }
            foreach ($f in @(Get-ChildItem -LiteralPath $saveBackup -File)) {
                Copy-Item -LiteralPath $f.FullName -Destination (Join-Path $saveRoot $f.Name) -Force
            }
            if (Test-Path -LiteralPath $saveCopy) { Remove-Item -LiteralPath $saveCopy -Force }
        } catch { Write-Warning "Save restore: $_" }
    }
    if ($had) { Copy-Item -LiteralPath (Join-Path $OutputRoot "lcbench.lua.orig") -Destination $live -Force }
    elseif (Test-Path -LiteralPath $live) { Remove-Item -LiteralPath $live -Force }
    foreach ($name in @("BZLogger.txt", "openshim.log")) {
        $source = Join-Path $logRoot $name
        if (Test-Path -LiteralPath $source) { Copy-Item -LiteralPath $source -Destination (Join-Path $OutputRoot $name) -Force }
    }
    Remove-Item -LiteralPath $lock -Force -ErrorAction SilentlyContinue
}
# Only lines this run added; the watchdog log is cumulative.
if ((Test-Path -LiteralPath $watchdog) -and
    (@(Get-Content -LiteralPath $watchdog | Select-Object -Skip $watchdogStart) -match "FOREGROUND-STOLEN").Count -gt 0) {
    Write-Warning "FOREGROUND-STOLEN in $watchdog - stop launching and report."
}
# Fixture check: the run must have loaded the lcbench mission (for -SaveLoad:
# the save launch loaded it and the load launch ran the overlay's Load).
$bzLog = Join-Path $OutputRoot $(if ($SaveLoad) { "BZLogger.save.txt" } else { "BZLogger.txt" })
if (-not ((Test-Path -LiteralPath $bzLog) -and
        (Select-String -LiteralPath $bzLog -SimpleMatch "addon\lcbench\lcbench.bzn" -Quiet))) {
    Write-Warning "FIXTURE: $bzLog does not show addon\lcbench\lcbench.bzn loading; results are not evidence."
}
if ($SaveLoad -and -not (Select-String -LiteralPath (Join-Path $OutputRoot "BZLogger.txt") -SimpleMatch "[LCHOWA]" -Quiet -ErrorAction SilentlyContinue |
        Where-Object { $_ }) ) {
    Write-Warning "FIXTURE: the load launch shows no [LCHOWA] lines; results are not evidence."
}
Write-Host "Logs: $OutputRoot (look for [LCHOWA] in BZLogger.txt and [HOWAPPR] in openshim.log)"
