param(
    [int]$ProbeTimeoutSeconds = 120,
    [double]$PollIntervalSeconds = 0.05,
    [double]$SampleWindowSeconds = 2.0,
    [int]$MaxEntries = 16,
    [int]$MaxObjects = 8,
    [int]$ChunkLogBudget = 400,
    [int]$ChunkTraceEntryLimit = 16,
    [int]$PostCaptureWaitSeconds = 10,
    [switch]$EnableChunkEffectTrace,
    [switch]$EnableChunkProxyDebug,
    [switch]$KillExistingGame,
    [switch]$KillGameAfterCapture
)

$repoRoot = Split-Path -Parent $PSScriptRoot
$gameRoot = "C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux"
$gameExe = Join-Path $gameRoot "battlezone98redux.exe"
$shimLog = Join-Path $gameRoot "winmm_shim.log"
$probeScript = Join-Path $PSScriptRoot "probe_chunk_effect_runtime.py"
$snapshotRoot = Join-Path $PSScriptRoot "snapshots"
$stdoutLog = Join-Path $env:TEMP "run_misn03_chunk_probe.stdout.log"
$stderrLog = Join-Path $env:TEMP "run_misn03_chunk_probe.stderr.log"
$python = (Get-Command python -ErrorAction SilentlyContinue)
if (-not $python) {
    $python = Get-Command py -ErrorAction Stop
}

New-Item -ItemType Directory -Path $snapshotRoot -Force | Out-Null

if ($KillExistingGame) {
    Get-Process battlezone98redux -ErrorAction SilentlyContinue | Stop-Process -Force
    Start-Sleep -Seconds 2
}

if (Test-Path $shimLog) {
    $stamp = Get-Date -Format "yyyyMMdd_HHmmss"
    Copy-Item $shimLog (Join-Path $snapshotRoot "preprobe_winmm_shim_$stamp.log") -Force
    Clear-Content $shimLog -ErrorAction SilentlyContinue
}

Remove-Item $stdoutLog,$stderrLog -ErrorAction SilentlyContinue

$env:OPENSHIM_CHUNK_LOG_BUDGET = "$ChunkLogBudget"
$env:OPENSHIM_CHUNK_TRACE_ENTRY_LIMIT = "$ChunkTraceEntryLimit"
if ($EnableChunkEffectTrace) {
    $env:OPENSHIM_CHUNK_EFFECT_TRACE = "1"
} else {
    Remove-Item Env:OPENSHIM_CHUNK_EFFECT_TRACE -ErrorAction SilentlyContinue
}
if ($EnableChunkProxyDebug) {
    $env:OPENSHIM_CHUNK_PROXY_DEBUG = "1"
} else {
    Remove-Item Env:OPENSHIM_CHUNK_PROXY_DEBUG -ErrorAction SilentlyContinue
}

$probeArgs = @(
    $probeScript,
    "--process-name", "battlezone98redux.exe",
    "--timeout", $ProbeTimeoutSeconds,
    "--poll-interval", $PollIntervalSeconds,
    "--sample-window", $SampleWindowSeconds,
    "--max-entries", $MaxEntries,
    "--max-objects", $MaxObjects,
    "--output-root", $snapshotRoot
)

$probeProc = Start-Process -FilePath $python.Source -ArgumentList $probeArgs -PassThru `
    -RedirectStandardOutput $stdoutLog -RedirectStandardError $stderrLog -WindowStyle Minimized

$gameProc = Start-Process -FilePath $gameExe -ArgumentList "misn03.bzn" -PassThru -WorkingDirectory $gameRoot

$probeFinished = $probeProc.WaitForExit(($ProbeTimeoutSeconds + 15) * 1000)
if (-not $probeFinished) {
    try {
        $probeProc.Kill()
    } catch {
    }
    throw "Chunk probe timed out after $ProbeTimeoutSeconds seconds."
}

$stdoutText = Get-Content $stdoutLog -Raw -ErrorAction SilentlyContinue
$stderrText = Get-Content $stderrLog -Raw -ErrorAction SilentlyContinue

if ($stderrText) {
    Write-Warning $stderrText.Trim()
}

$outputDir = $null
foreach ($line in ($stdoutText -split "`r?`n")) {
    if ($line -like "OUTPUT_DIR=*") {
        $outputDir = $line.Substring("OUTPUT_DIR=".Length).Trim()
        break
    }
}

if (-not $outputDir) {
    $outputDir = Get-ChildItem $snapshotRoot -Directory -ErrorAction SilentlyContinue |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First 1 -ExpandProperty FullName
}

if (-not $outputDir) {
    throw "Chunk probe did not produce an output directory."
}

Start-Sleep -Seconds $PostCaptureWaitSeconds

if ($KillGameAfterCapture) {
    Get-Process battlezone98redux -ErrorAction SilentlyContinue | Stop-Process -Force
    Start-Sleep -Seconds 2
}

for ($attempt = 0; $attempt -lt 10; $attempt++) {
    if (Test-Path $shimLog) {
        try {
            Copy-Item $shimLog (Join-Path $outputDir "winmm_shim.log") -Force
            break
        } catch {
            Start-Sleep -Milliseconds 500
        }
    }
}

$probeProc.Refresh()
$probeExitCode = $null
if ($probeProc.HasExited) {
    $probeExitCode = $probeProc.ExitCode
}

$result = [ordered]@{
    output_dir = $outputDir
    probe_stdout = $stdoutLog
    probe_stderr = $stderrLog
    game_pid = $gameProc.Id
    probe_exit_code = $probeExitCode
}

$resultJson = Join-Path $outputDir "run_result.json"
$result | ConvertTo-Json | Set-Content -Path $resultJson -Encoding ASCII
$result | ConvertTo-Json -Depth 3
