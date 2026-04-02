param(
    [string]$GameRoot = "C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux",
    [string]$PackagedModsRoot = "C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\packaged_mods\3686673790",
    [string]$MissionArgs = "misn06.bzn /edit",
    [int[]]$SpaceDelaysMs = @(250, 500, 750, 1000),
    [int]$RunDurationSeconds = 45,
    [int]$MainWindowTimeoutSeconds = 20,
    [switch]$AttachFrida,
    [string]$FridaScript = "",
    [switch]$DeployShim,
    [switch]$KillExistingGame,
    [switch]$KeepGameOpen
)

$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$gameExe = Join-Path $GameRoot "battlezone98redux.exe"
$gameLog = Join-Path $GameRoot "openshim.log"
$bzLogger = Join-Path $GameRoot "BZLogger.txt"
$dumpRoot = "C:\BZDumps"
$snapshotRoot = Join-Path $PSScriptRoot "snapshots"
$stamp = Get-Date -Format "yyyyMMdd_HHmmss"
$seriesRoot = Join-Path $snapshotRoot "misn06_auto_$stamp"
$shimSourceDll = Join-Path $repoRoot "bin\Release\winmm.dll"
$shimSourcePdb = Join-Path $repoRoot "bin\Release\winmm.pdb"
$shimTargets = @(
    (Join-Path $GameRoot "winmm.dll"),
    (Join-Path $PackagedModsRoot "winmm.dll")
)
$pdbTargets = @(
    (Join-Path $GameRoot "winmm.pdb"),
    (Join-Path $PackagedModsRoot "winmm.pdb")
)

if (-not (Test-Path $gameExe)) {
    throw "Game executable not found: $gameExe"
}

if (-not (Test-Path $snapshotRoot)) {
    New-Item -ItemType Directory -Path $snapshotRoot -Force | Out-Null
}
New-Item -ItemType Directory -Path $seriesRoot -Force | Out-Null

if (-not $FridaScript) {
    $FridaScript = Join-Path $repoRoot "reverse_engineering\redux_chunk_trace.js"
}

function Get-HashOrNull {
    param([string]$Path)
    if (-not (Test-Path $Path)) {
        return $null
    }
    return (Get-FileHash -Algorithm SHA256 -LiteralPath $Path).Hash
}

function Stop-ProcessByNameIfPresent {
    param([string]$Name)
    Get-Process -Name $Name -ErrorAction SilentlyContinue | Stop-Process -Force
}

function Get-LineCount {
    param([string]$Path)
    if (-not (Test-Path $Path)) {
        return 0
    }
    try {
        return (Get-Content -LiteralPath $Path | Measure-Object -Line).Lines
    } catch {
        return 0
    }
}

function Get-LinesAfter {
    param(
        [string]$Path,
        [int]$StartLine
    )
    if (-not (Test-Path $Path)) {
        return @()
    }
    $all = Get-Content -LiteralPath $Path
    if ($StartLine -lt 0) {
        $StartLine = 0
    }
    if ($StartLine -ge $all.Count) {
        return @()
    }
    return $all[$StartLine..($all.Count - 1)]
}

function Send-SpaceToProcess {
    param([System.Diagnostics.Process]$Process)
    $shell = New-Object -ComObject WScript.Shell
    [void]$shell.AppActivate($Process.Id)
    Start-Sleep -Milliseconds 150
    $shell.SendKeys(" ")
}

function Wait-ForMainWindow {
    param(
        [System.Diagnostics.Process]$Process,
        [int]$TimeoutSeconds
    )
    $deadline = (Get-Date).AddSeconds($TimeoutSeconds)
    while ((Get-Date) -lt $deadline) {
        if ($Process.HasExited) {
            return $false
        }
        $Process.Refresh()
        if ($Process.MainWindowHandle -ne 0) {
            return $true
        }
        Start-Sleep -Milliseconds 200
    }
    return $false
}

function Start-FridaTrace {
    param(
        [int]$TargetPid,
        [string]$ScriptPath,
        [string]$OutPath,
        [string]$ErrPath
    )
    $quotedScript = '"' + $ScriptPath + '"'
    $cmdLine = "bzr-frida.cmd -p $TargetPid -q -t inf -l $quotedScript 1>`"$OutPath`" 2>`"$ErrPath`""
    return Start-Process -FilePath "cmd.exe" -ArgumentList "/c $cmdLine" -WorkingDirectory $repoRoot -PassThru -WindowStyle Hidden
}

function Score-Run {
    param(
        [string[]]$ShimLines,
        [string[]]$FridaLines,
        [string[]]$KnownGeoTokens,
        [bool]$Crashed
    )
    $createChunk = @($ShimLines | Where-Object { $_ -match '\[CHUNKSPAWN\] CreateChunk ' }).Count
    $createChunklet = @($ShimLines | Where-Object { $_ -match '\[CHUNKSPAWN\] CreateChunklet ' }).Count
    $fragFlush = @($ShimLines | Where-Object { $_ -match '\[CHUNKFRAG\] flush ' }).Count
    $fridaCreateChunk = @($FridaLines | Where-Object { $_ -match '\[CreateChunk\]' }).Count
    $geoHits = 0
    foreach ($token in $KnownGeoTokens) {
        if ($ShimLines -match [regex]::Escape($token)) {
            $geoHits++
        }
        if ($FridaLines -match [regex]::Escape($token)) {
            $geoHits++
        }
    }
    $score = ($createChunk * 50) + ($fridaCreateChunk * 60) + ($fragFlush * 30) + ($geoHits * 10) - ($createChunklet) - ($(if ($Crashed) { 200 } else { 0 }))
    return [ordered]@{
        create_chunk = $createChunk
        create_chunklet = $createChunklet
        chunkfrag_flush = $fragFlush
        frida_create_chunk = $fridaCreateChunk
        geo_hit_score = $geoHits
        score = $score
    }
}

$knownGeoTokens = @(
    "ARA11BDA","ARA11Gc1","ARA11Gc2","ARA11Gr1","ARA11Gs1","ARA11LGT","ARA11NRL","ARA11NRR","ARA11POV","ARA11ROR","ARA11RORL","ARA11RORT",
    "AGR11BDA","AGR11BDAT","AGR11BGA","AGR11GC1","AGR11Gc2","AGR11GM1","AGR11GS1","AGR11LGT","Agr11nrl","Agr11nrr","AGR11POV","AGR11ROR","AGR11TUR",
    "SFL11BDA","SFL11BDB","SFL11GC1","SFL11Gc2","SFL11GR1","SFL11Gs1","SFL11LGT","SFL11NFL","SFL11NFR","SFL11POV","SFL11ROR","SFL11RORp","SFL11RORt",
    "SCZ11BGA","SCZ11BGB","SCZ11GC1","SCZ11GC2","SCZ11GM1","SCZ11GS1","SCZ11LGT","SCZ11MOR","SCZ11POV","SCZ11RAD","scz11wgl","scz11wgr"
)

if ($KillExistingGame) {
    Stop-ProcessByNameIfPresent -Name "battlezone98redux"
    Stop-ProcessByNameIfPresent -Name "frida"
    Start-Sleep -Seconds 2
}

$deployment = [ordered]@{
    source_dll = $shimSourceDll
    source_pdb = $shimSourcePdb
    source_hash = Get-HashOrNull -Path $shimSourceDll
    deployed = @()
}

if ($DeployShim) {
    foreach ($target in $shimTargets) {
        Copy-Item -LiteralPath $shimSourceDll -Destination $target -Force
        $deployment.deployed += [pscustomobject]@{
            path = $target
            hash = Get-HashOrNull -Path $target
        }
    }
    foreach ($target in $pdbTargets) {
        if (Test-Path $shimSourcePdb) {
            Copy-Item -LiteralPath $shimSourcePdb -Destination $target -Force
        }
    }
}

$runs = @()

foreach ($delayMs in $SpaceDelaysMs) {
    Stop-ProcessByNameIfPresent -Name "frida"
    if ($KillExistingGame) {
        Stop-ProcessByNameIfPresent -Name "battlezone98redux"
        Start-Sleep -Seconds 1
    }

    $runRoot = Join-Path $seriesRoot ("delay_" + $delayMs.ToString("0000") + "ms")
    New-Item -ItemType Directory -Path $runRoot -Force | Out-Null

    $preShimLines = Get-LineCount -Path $gameLog
    $preBzLines = Get-LineCount -Path $bzLogger
    $preDumpNames = @()
    if (Test-Path $dumpRoot) {
        $preDumpNames = @(Get-ChildItem -LiteralPath $dumpRoot -File | Select-Object -ExpandProperty Name)
    }

    $gameProc = Start-Process -FilePath $gameExe -ArgumentList $MissionArgs -WorkingDirectory $GameRoot -PassThru
    $windowReady = Wait-ForMainWindow -Process $gameProc -TimeoutSeconds $MainWindowTimeoutSeconds
    $spaceSent = $false
    $spaceSentAt = $null

    if ($windowReady) {
        Start-Sleep -Milliseconds $delayMs
        if (-not $gameProc.HasExited) {
            Send-SpaceToProcess -Process $gameProc
            $spaceSent = $true
            $spaceSentAt = Get-Date
        }
    }

    $fridaLog = Join-Path $runRoot "frida.log"
    $fridaErr = Join-Path $runRoot "frida.err.log"
    $fridaProc = $null
    if ($AttachFrida -and -not $gameProc.HasExited) {
        $fridaProc = Start-FridaTrace -TargetPid $gameProc.Id -ScriptPath $FridaScript -OutPath $fridaLog -ErrPath $fridaErr
        Start-Sleep -Seconds 1
    }

    Start-Sleep -Seconds $RunDurationSeconds

    $exitCode = $null
    $exitedNaturally = $false
    $gameProc.Refresh()
    if ($gameProc.HasExited) {
        $exitCode = $gameProc.ExitCode
        $exitedNaturally = $true
    } elseif (-not $KeepGameOpen) {
        Stop-Process -Id $gameProc.Id -Force
        Start-Sleep -Seconds 1
    }

    if ($fridaProc) {
        try {
            if (-not $fridaProc.HasExited) {
                Stop-Process -Id $fridaProc.Id -Force
            }
        } catch {
        }
    }

    Start-Sleep -Seconds 2

    $shimLines = Get-LinesAfter -Path $gameLog -StartLine $preShimLines
    $bzLines = Get-LinesAfter -Path $bzLogger -StartLine $preBzLines
    $fridaLines = @()
    if (Test-Path $fridaLog) {
        $fridaLines = Get-Content -LiteralPath $fridaLog
    }

    $newDumpNames = @()
    if (Test-Path $dumpRoot) {
        $newDumpNames = @(Get-ChildItem -LiteralPath $dumpRoot -File |
            Where-Object { $preDumpNames -notcontains $_.Name } |
            Sort-Object LastWriteTime |
            Select-Object -ExpandProperty Name)
    }

    $shimSlicePath = Join-Path $runRoot "openshim.slice.log"
    $bzSlicePath = Join-Path $runRoot "BZLogger.slice.txt"
    $summaryPath = Join-Path $runRoot "summary.json"
    [System.IO.File]::WriteAllText($shimSlicePath, (@($shimLines) -join [Environment]::NewLine), [System.Text.Encoding]::UTF8)
    [System.IO.File]::WriteAllText($bzSlicePath, (@($bzLines) -join [Environment]::NewLine), [System.Text.Encoding]::UTF8)

    $score = Score-Run -ShimLines $shimLines -FridaLines $fridaLines -KnownGeoTokens $knownGeoTokens -Crashed ($newDumpNames.Count -gt 0)
    $run = [ordered]@{
        delay_ms = $delayMs
        pid = $gameProc.Id
        window_ready = $windowReady
        space_sent = $spaceSent
        space_sent_at = if ($spaceSentAt) { $spaceSentAt.ToString("o") } else { $null }
        attach_frida = [bool]$AttachFrida
        frida_script = if ($AttachFrida) { $FridaScript } else { $null }
        exited_naturally = $exitedNaturally
        exit_code = $exitCode
        new_dumps = $newDumpNames
        output_dir = $runRoot
        shim_slice = $shimSlicePath
        bz_slice = $bzSlicePath
        frida_log = if ($AttachFrida) { $fridaLog } else { $null }
        frida_err = if ($AttachFrida) { $fridaErr } else { $null }
    }
    foreach ($key in $score.Keys) {
        $run[$key] = $score[$key]
    }

    $run | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath $summaryPath -Encoding ASCII
    $runs += [pscustomobject]$run
}

$bestRun = $runs | Sort-Object @{ Expression = "score"; Descending = $true }, @{ Expression = "create_chunk"; Descending = $true }, @{ Expression = "geo_hit_score"; Descending = $true } | Select-Object -First 1
$seriesSummary = [ordered]@{
    captured_at = (Get-Date).ToString("o")
    game_root = $GameRoot
    mission_args = $MissionArgs
    deploy_shim = [bool]$DeployShim
    deployment = $deployment
    attach_frida = [bool]$AttachFrida
    frida_script = if ($AttachFrida) { $FridaScript } else { $null }
    run_duration_seconds = $RunDurationSeconds
    main_window_timeout_seconds = $MainWindowTimeoutSeconds
    space_delays_ms = $SpaceDelaysMs
    best_run = $bestRun
    runs = $runs
}

$seriesSummaryPath = Join-Path $seriesRoot "series_summary.json"
$seriesSummary | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $seriesSummaryPath -Encoding ASCII
$seriesSummary | ConvertTo-Json -Depth 6
