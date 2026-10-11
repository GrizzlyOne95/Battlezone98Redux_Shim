# DX11LegacyMaterialCompat qualification driver (background, never-activate).
#
# Runs each mission with DX11LegacyMaterialCompat=0 and =1 (arm order alternates
# per mission; the first run of the first arm is a cold-cache run and is
# discarded), collects logs, [DX11COMPAT] counts, Ogre errors, crash evidence,
# and PrintWindow screenshot pairs, and writes metrics.json per run plus
# summary.json. pwsh 7 only. Never activates the game window, never uses
# SendInput, never force-kills: launch = Assert-BZRSafeToLaunch +
# Start-BZRGameProcess, teardown = Stop-BZRGame -Id.
#
#   pwsh -File reverse_engineering\run_compat_qualification.ps1 [-Missions lcbench,misn01]
#
# The ini key is edited in place and restored to the original value in finally.
[CmdletBinding()]
param(
    [string]$GameRoot = "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux",
    [string[]]$Missions = @(),
    [string]$OutputRoot = "",
    [int]$HoldSeconds = 45,
    [switch]$SkipMenuNav,
    # Turn on the shim's Ogre profiler ([Diagnostics] ProfileOgreAnimation=1) so
    # per-second fps/frame-time lines land in openshim.log. Restored in finally.
    [switch]$Profiler
)

$ErrorActionPreference = "Stop"
if ($PSVersionTable.PSVersion.Major -lt 7) { throw "Run under pwsh 7." }

. "$PSScriptRoot\BZRHarness.ps1"
# BZRWindowInput.ps1 does not compile under pwsh 7 (System.Drawing Bitmap), so
# shell-menu clicks run in a Windows PowerShell 5.1 child (Invoke-ShellClick).

$gameExe   = Join-Path $GameRoot "battlezone98redux.exe"
$iniPath   = Join-Path $GameRoot "openshim.ini"
$logDir    = Join-Path $GameRoot "logs"
$bzLog     = Join-Path $logDir "BZLogger.txt"
$shimLog   = Join-Path $logDir "openshim.log"
$ogreLog   = Join-Path $logDir "BZOgreLogfile.log"
$crashLog  = Join-Path $logDir "openshim_crash.log"
$wdLog     = Join-Path $env:TEMP "bzr_foreground_watchdog.log"
$shotTool  = Join-Path $PSScriptRoot "Capture-BZRWindow.ps1"
$stamp     = Get-Date -Format "yyyyMMdd_HHmmss"
if (-not $OutputRoot) { $OutputRoot = Join-Path $GameRoot "openshim_test_results\compat_qual_$stamp" }
New-Item -ItemType Directory -Force -Path $OutputRoot | Out-Null

# id, argument, init timeout (s), kind
$table = @(
    @{ id = 'lcbench';  arg = 'lcbench.bzn'; timeout = 120; kind = 'game' },
    @{ id = 'misn01';   arg = 'misn01.bzn';  timeout = 150; kind = 'game' },
    @{ id = 'misn06';   arg = 'misn06.bzn';  timeout = 180; kind = 'game' },
    @{ id = 'misns1';   arg = 'misns1.bzn';  timeout = 150; kind = 'game' },
    @{ id = 'misns5';   arg = 'misns5.bzn';  timeout = 150; kind = 'game' },
    # Mission argument must be <= 15 chars: a "mods/<id>/" prefix is silently
    # ignored and the game sits at the main menu. Bare names resolve to CR's
    # copies in mods\3686673790 (they shadow StockODFFiles).
    @{ id = 'cr_misn03'; arg = 'misn03.bzn'; timeout = 180; kind = 'game' },
    @{ id = 'cr_misn05'; arg = 'misn05.bzn'; timeout = 180; kind = 'game' },
    @{ id = 'isdfms01'; arg = 'isdfms01.bzn'; timeout = 180; kind = 'game' },
    @{ id = 'shell';    arg = '';            timeout = 90;  kind = 'shell' }
)
$Missions = @($Missions | ForEach-Object { $_ -split ',' } | Where-Object { $_ })   # -File passes "a,b" as one string
if ($Missions.Count -gt 0) { $table = @($table | Where-Object { $Missions -contains $_.id }) }

function Read-Shared([string]$Path) {
    if (-not (Test-Path -LiteralPath $Path)) { return "" }
    $fs = [System.IO.File]::Open($Path, 'Open', 'Read', 'ReadWrite')
    try { $sr = New-Object System.IO.StreamReader($fs); return $sr.ReadToEnd() } finally { $fs.Dispose() }
}
function Len([string]$Path) { if (Test-Path -LiteralPath $Path) { (Get-Item -LiteralPath $Path).Length } else { 0 } }

$origIni = [System.IO.File]::ReadAllText($iniPath)
if ($origIni -notmatch '(?m)^DX11LegacyMaterialCompat\s*=') { throw "ini has no DX11LegacyMaterialCompat key" }
function Set-Compat([int]$Value) {
    $t = [System.IO.File]::ReadAllText($iniPath)
    $t = [regex]::Replace($t, '(?m)^DX11LegacyMaterialCompat\s*=.*$', "DX11LegacyMaterialCompat = $Value")
    [System.IO.File]::WriteAllText($iniPath, $t, (New-Object System.Text.UTF8Encoding($false)))
}

function Set-IniKey([string]$Key, [string]$Value) {
    $t = [System.IO.File]::ReadAllText($iniPath)
    if ($t -notmatch "(?m)^$([regex]::Escape($Key))\s*=") { throw "ini has no $Key key" }
    $t = [regex]::Replace($t, "(?m)^$([regex]::Escape($Key))\s*=.*$", "$Key = $Value")
    [System.IO.File]::WriteAllText($iniPath, $t, (New-Object System.Text.UTF8Encoding($false)))
}
if ($Profiler) { Set-IniKey 'ProfileOgreAnimation' '1' }

# One "[OgreProfile] fps= frameMean= p50= p95= p99= max=" line per second when
# [Diagnostics] ProfileOgreAnimation=1. Returns medians over the post-init lines.
function Get-PerfStats([string]$ShimText) {
    $rows = @([regex]::Matches($ShimText, '\[OgreProfile\] fps=([\d\.]+) frameMean=([\d\.]+) p50=([\d\.]+) p95=([\d\.]+) p99=([\d\.]+) max=([\d\.]+)') |
        ForEach-Object { [pscustomobject]@{ fps = [double]$_.Groups[1].Value; mean = [double]$_.Groups[2].Value; p95 = [double]$_.Groups[4].Value; p99 = [double]$_.Groups[5].Value } })
    if ($rows.Count -lt 3) { return $null }
    $rows = @($rows | Select-Object -Skip 2)   # drop the load-hitch intervals
    $med = { param($v) $s = @($v | Sort-Object); $s[[int][Math]::Floor(($s.Count - 1) / 2)] }
    [ordered]@{ samples = $rows.Count; medianFps = (& $med ($rows.fps)); medianFrameMeanMs = (& $med ($rows.mean)); medianP95Ms = (& $med ($rows.p95)); medianP99Ms = (& $med ($rows.p99)) }
}

function Get-SamplePixels([string]$Path) {
    Add-Type -AssemblyName System.Drawing
    $bmp = [System.Drawing.Bitmap]::FromFile($Path)
    try {
        $gx = 48; $gy = 27; $out = New-Object 'int[]' ($gx * $gy * 3); $i = 0
        for ($y = 0; $y -lt $gy; $y++) { for ($x = 0; $x -lt $gx; $x++) {
            $c = $bmp.GetPixel([int](($x + 0.5) * $bmp.Width / $gx), [int](($y + 0.5) * $bmp.Height / $gy))
            $out[$i++] = $c.R; $out[$i++] = $c.G; $out[$i++] = $c.B } }
        return @{ w = $bmp.Width; h = $bmp.Height; px = $out }
    } finally { $bmp.Dispose() }
}
function Compare-Shots([string]$PathA, [string]$PathB) {
    if (-not ((Test-Path $PathA) -and (Test-Path $PathB))) { return $null }
    $a = Get-SamplePixels $PathA; $b = Get-SamplePixels $PathB
    if ($a.px.Count -ne $b.px.Count) { return $null }
    $n = $a.px.Count / 3; $changed = 0; $sum = 0.0; $blackA = 0
    for ($i = 0; $i -lt $n; $i++) {
        $d = 0
        for ($k = 0; $k -lt 3; $k++) { $d += [Math]::Abs($a.px[$i*3+$k] - $b.px[$i*3+$k]) }
        $sum += $d / 3.0; if ($d -gt 36) { $changed++ }
        if (($a.px[$i*3] + $a.px[$i*3+1] + $a.px[$i*3+2]) -lt 12) { $blackA++ }
    }
    [pscustomobject]@{ changedFrac = [Math]::Round($changed / $n, 4); meanAbsDiff = [Math]::Round($sum / $n, 2); blackFracA = [Math]::Round($blackA / $n, 4) }
}

function Take-Shot([string]$Path) {
    & powershell.exe -NoProfile -ExecutionPolicy Bypass -File $shotTool -Out $Path | Out-Null
    return (Test-Path $Path)
}

function Get-Metrics([string]$RunDir, [datetime]$Start, $Info) {
    $shim = Read-Shared $shimLog; $ogre = Read-Shared $ogreLog; $bz = Read-Shared $bzLog
    $cl = @($shim -split "`r?`n" | Where-Object { $_ -match '\[DX11COMPAT\]' })
    $cnt = [ordered]@{
        instantiated = @($cl | Where-Object { $_ -match 'source=\S+ path=\S+ cached=' -and $_ -notmatch 'declined|failed' }).Count
        skipped      = @($cl | Where-Object { $_ -match 'skipped shaderless draw|action=skip-draw' }).Count
        declined     = @($cl | Where-Object { $_ -match 'instantiate declined' }).Count
        failed       = @($cl | Where-Object { $_ -match 'instantiate failed' }).Count
        # "instantiation failed ... action=stock-fallback" follows every "instantiate declined ... excluded-class"
        # (UI/HUD classes are deliberately left on stock programs); counted apart from real failures.
        stockFallback = @($cl | Where-Object { $_ -match 'instantiation failed' -and $_ -match 'stock-fallback' }).Count
        instantiationFailedOther = @($cl | Where-Object { $_ -match 'instantiation failed' -and $_ -notmatch 'stock-fallback' }).Count
        guard        = @($cl | Where-Object { $_ -match 'native-input-guard|path=suppress' }).Count
        familyRemap  = @($cl | Where-Object { $_ -match 'path=family-remap' }).Count
        unsupported  = @($cl | Where-Object { $_ -match 'unsupported custom programs' }).Count
        total        = $cl.Count
    }
    $summary = ($cl | Where-Object { $_ -match '\[DX11COMPAT\] summary' } | Select-Object -Last 1)
    $ogErr = @($ogre -split "`r?`n" | Where-Object { $_ -match '(?i)error|exception|failed|Invalid target|compile|without both vertex' })
    $layout = @(($ogre + "`n" + $shim) -split "`r?`n" | Where-Object { $_ -match '(?i)input ?layout|vertex ?declaration|VertexElement|semantic' -and $_ -match '(?i)fail|error|invalid|mismatch|cannot|unable' })
    $norm = { param($l) ($l -replace '^\S+\s+\S+\s+', '' -replace '\d+(\.\d+)?', '#').Trim() }
    $ogClasses = @($ogErr | ForEach-Object { & $norm $_ } | Sort-Object -Unique)
    $layClasses = @($layout | ForEach-Object { & $norm $_ } | Sort-Object -Unique)
    $dumps = @(Get-ChildItem $logDir -Filter *.dmp -ErrorAction SilentlyContinue | Where-Object { $_.LastWriteTime -ge $Start } | ForEach-Object Name)
    $crashNew = ""
    if (Test-Path $crashLog) { if ((Get-Item $crashLog).LastWriteTime -ge $Start) { $crashNew = (Read-Shared $crashLog) -split "`r?`n" | Select-Object -Last 12 | Out-String } }
    $backend = ($shim -split "`r?`n" | Where-Object { $_ -match '\[RENDER\] backend identified' } | Select-Object -Last 1)
    $init = if ($bz -match 'Game Simulation Initialized after ([\d\.]+) seconds') { [double]$Matches[1] } else { $null }
    $lc = @([regex]::Matches($bz, '\[LCGIBS\] T\+([\d\.]+)') | ForEach-Object { [double]$_.Groups[1].Value })
    [ordered]@{
        mission = $Info.mission; arm = $Info.arm; rep = $Info.rep; discarded = $Info.discarded
        backend = $backend; dx11 = [bool]($backend -match '(?i)direct3d ?11|d3d11')
        reachedGameplay = $Info.reached; initSeconds = $init; shellReached = [bool]($bz -match 'UI View Started')
        exitedEarly = $Info.exitedEarly
        logGrowthBz = $Info.growthBz; logGrowthShim = $Info.growthShim
        lcbenchSmokeLines = [regex]::Matches($bz, '\[SMOKE\] (OK|ERR)').Count
        lcbenchSmokeErr = [regex]::Matches($bz, '\[SMOKE\] ERR').Count
        lcbenchLastT = if ($lc.Count) { ($lc | Measure-Object -Maximum).Maximum } else { $null }; lcbenchMarkers = $lc.Count
        simDelta = $Info.simDelta
        perf = (Get-PerfStats $shim)
        compat = $cnt; compatSummary = $summary
        ogreErrorLines = $ogErr.Count; ogreErrorClasses = $ogClasses
        layoutFailureLines = $layout.Count; layoutFailureClasses = $layClasses
        dumps = $dumps; crashLogTail = $crashNew
        watchdogSteals = $Info.steals
    }
}

function Invoke-Run($M, [int]$Arm, [int]$Rep, [bool]$Discard, [string]$Label) {
    $runDir = Join-Path $OutputRoot "$($M.id)\$Label"
    New-Item -ItemType Directory -Force -Path $runDir | Out-Null
    Set-Compat $Arm
    if (@(Get-Process battlezone98redux -ErrorAction SilentlyContinue).Count -gt 0) { throw "battlezone98redux already running; refusing to launch" }
    $wdBefore = Len $wdLog
    $start = Get-Date
    Assert-BZRSafeToLaunch
    $argv = if ($M.arg) { @($M.arg) } else { @() }
    $proc = Start-BZRGameProcess -FilePath $gameExe -ArgumentList $argv -WorkingDirectory $GameRoot -PassThru
    $info = @{ mission = $M.id; arm = $Arm; rep = $Rep; discarded = $Discard; reached = $false; exitedEarly = $false; steals = 0; growthBz = $null; growthShim = $null; simDelta = $null }
    $marker = if ($M.kind -eq 'shell') { 'UI View Started' } else { 'Game Simulation Initialized after' }
    $deadline = $start.AddSeconds($M.timeout); $got = $false
    try {
        while ((Get-Date) -lt $deadline -and -not $proc.HasExited) {
            Start-Sleep -Milliseconds 1500
            # BZLogger is truncated at launch, but a poll can still catch the previous
            # run's file; only accept a marker line stamped at or after this launch.
            $hit = [regex]::Matches((Read-Shared $bzLog), "(?m)^(\d{4}-\d\d-\d\d \d\d:\d\d:\d\d\.\d+) .*" + [regex]::Escape($marker))
            foreach ($h in $hit) { if ([datetime]::Parse($h.Groups[1].Value) -ge $start.AddSeconds(-1)) { $got = $true } }
            if ($got) { break }
        }
        $info.reached = $got
        if ($proc.HasExited) { $info.exitedEarly = $true }
        $shots = @()
        if ($got -and -not $proc.HasExited) {
            $t0 = Get-Date
            $early = if ($M.id -eq 'lcbench') { 3 } else { 10 }
            $late  = if ($M.id -eq 'lcbench') { 9 } else { $HoldSeconds }
            Start-Sleep -Seconds $early
            $p1 = Join-Path $runDir "shot1.png"; if (Take-Shot $p1) { $shots += $p1 }
            $b1 = Len $bzLog; $s1 = Len $shimLog
            $left = $late - ((Get-Date) - $t0).TotalSeconds
            if ($left -gt 0) { Start-Sleep -Seconds ([int]$left) }
            if (-not $proc.HasExited) {
                $p2 = Join-Path $runDir "shot2.png"; if (Take-Shot $p2) { $shots += $p2 }
            }
            $info.growthBz = (Len $bzLog) - $b1; $info.growthShim = (Len $shimLog) - $s1
            $info.exitedEarly = $proc.HasExited
        }
        # collect before teardown so a clean shutdown cannot truncate evidence
        $metrics = Get-Metrics $runDir $start $info
        foreach ($f in @($bzLog, $shimLog, $ogreLog, $crashLog)) { if (Test-Path $f) { Copy-Item $f $runDir -Force -ErrorAction SilentlyContinue } }
    } finally {
        if (-not $proc.HasExited) { try { Stop-BZRGame -Id $proc.Id } catch { Write-Warning "Stop-BZRGame: $_" } }
    }
    # final logs after clean shutdown (summary line is likely written at exit)
    $final = Get-Metrics $runDir $start $info
    foreach ($f in @($bzLog, $shimLog, $ogreLog, $crashLog)) { if (Test-Path $f) { Copy-Item $f $runDir -Force -ErrorAction SilentlyContinue } }
    $wdNew = if ((Len $wdLog) -gt $wdBefore) { (Read-Shared $wdLog).Substring([int][Math]::Min($wdBefore, (Read-Shared $wdLog).Length)) } else { "" }
    $steals = @($wdNew -split "`r?`n" | Where-Object { $_ -match 'FOREGROUND-STOLEN' })
    $final.watchdogSteals = $steals.Count
    $s1p = Join-Path $runDir "shot1.png"; $s2p = Join-Path $runDir "shot2.png"
    $d = Compare-Shots $s1p $s2p
    $final.simDelta = $d
    # Proxy: log growth during the hold window AND/OR a changed frame. Static
    # scenes (lcbench, menus) legitimately produce identical frames, so both
    # signals are kept in metrics.json and simProgress is true if either moves.
    $final.simProgress = [bool]((($final.logGrowthBz -gt 0) -or ($final.logGrowthShim -gt 0)) -or ($d -and $d.changedFrac -gt 0.002))
    $final | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath (Join-Path $runDir "metrics.json") -Encoding UTF8
    if ($steals.Count -gt 0) { throw "FOREGROUND-STOLEN seen in $wdLog during ${Label}: $($steals[0])" }
    Start-Sleep -Seconds 2
    return $final
}

$results = @()
try {
    $idx = 0
    foreach ($M in $table) {
        $first = if ($idx % 2 -eq 0) { 0 } else { 1 }; $second = 1 - $first
        $plan = @(
            @{ arm = $first;  rep = 1; disc = $true  },
            @{ arm = $first;  rep = 2; disc = $false },
            @{ arm = $second; rep = 1; disc = $false },
            @{ arm = $second; rep = 2; disc = $false })
        foreach ($p in $plan) {
            $label = "compat$($p.arm)_r$($p.rep)"
            Write-Host ("[compatqual] {0} {1}{2}" -f $M.id, $label, $(if ($p.disc) { ' (cold, discarded)' } else { '' }))
            try { $r = Invoke-Run $M $p.arm $p.rep $p.disc $label }
            catch {
                if ($_.Exception.Message -match 'FOREGROUND-STOLEN|already running') { throw }
                Write-Warning "run $M.id $label errored: $_"
                $results += [pscustomobject]@{ mission = $M.id; arm = $p.arm; rep = $p.rep; discarded = $p.disc; error = "$_" }
                continue
            }
            $results += [pscustomobject]$r
            Write-Host ("    reached={0} init={1} dx11={2} compat={3} ogreErr={4} dumps={5} sim={6}" -f $r.reachedGameplay, $r.initSeconds, $r.dx11, ($r.compat | ConvertTo-Json -Compress), $r.ogreErrorLines, $r.dumps.Count, $r.simProgress)
        }
        $idx++
    }
} finally {
    [System.IO.File]::WriteAllText($iniPath, $origIni, (New-Object System.Text.UTF8Encoding($false)))
    $results | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath (Join-Path $OutputRoot "summary.json") -Encoding UTF8
    # Cross-arm screenshot diff: compat0 vs compat1, same repeat number (r2), both shots.
    try {
        $cross = foreach ($dir in (Get-ChildItem $OutputRoot -Directory)) {
            foreach ($s in 'shot1', 'shot2') {
                $pa = Join-Path $dir.FullName "compat0_r2\$s.png"; $pb = Join-Path $dir.FullName "compat1_r2\$s.png"
                $c = Compare-Shots $pa $pb
                if ($c) { [pscustomobject]@{ mission = $dir.Name; shot = $s; changedFrac = $c.changedFrac; meanAbsDiff = $c.meanAbsDiff; blackFrac0 = $c.blackFracA; pathA = $pa; pathB = $pb } }
            }
        }
        $cross | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $OutputRoot "cross_arm_diff.json") -Encoding UTF8
    } catch { Write-Warning "cross-arm diff failed: $_" }
    Write-Host "[compatqual] ini restored; results: $OutputRoot"
}
