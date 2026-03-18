param(
    [int]$RepeatCount = 3,
    [int]$ProbeTimeoutSeconds = 180,
    [double]$SampleWindowSeconds = 3.0,
    [int]$ChunkLogBudget = 600,
    [int]$ChunkTraceEntryLimit = 8,
    [int]$PostCaptureWaitSeconds = 10,
    [bool]$EnableChunkEffectTrace = $true,
    [bool]$EnableChunkProxyDebug = $true
)

$singleRunScript = Join-Path $PSScriptRoot "run_misn03_chunk_probe.ps1"
$snapshotRoot = Join-Path $PSScriptRoot "snapshots"
$seriesStamp = Get-Date -Format "yyyyMMdd_HHmmss"
$seriesRoot = Join-Path $snapshotRoot "misn03_chunk_series_$seriesStamp"
New-Item -ItemType Directory -Path $seriesRoot -Force | Out-Null

$runs = @()

for ($index = 1; $index -le $RepeatCount; $index++) {
    Write-Host "=== misn03 chunk probe run $index / $RepeatCount ==="

    $result = & $singleRunScript `
        -ProbeTimeoutSeconds $ProbeTimeoutSeconds `
        -SampleWindowSeconds $SampleWindowSeconds `
        -ChunkLogBudget $ChunkLogBudget `
        -ChunkTraceEntryLimit $ChunkTraceEntryLimit `
        -PostCaptureWaitSeconds $PostCaptureWaitSeconds `
        -EnableChunkEffectTrace $EnableChunkEffectTrace `
        -EnableChunkProxyDebug $EnableChunkProxyDebug `
        -KillExistingGame `
        -KillGameAfterCapture |
        ConvertFrom-Json

    $logPath = Join-Path $result.output_dir "winmm_shim.log"
    $trackingLines = @()
    $assignedLines = @()
    $releaseLines = @()
    $effectLines = @()
    $initLines = @()

    if (Test-Path $logPath) {
        $trackingLines = @(Select-String -Path $logPath -Pattern '^\[CHUNKPROXY\] tracking ')
        $assignedLines = @(Select-String -Path $logPath -Pattern '^\[CHUNKPROXY\] assigned ')
        $releaseLines = @(Select-String -Path $logPath -Pattern '^\[CHUNKPROXY\] release ')
        $effectLines = @(Select-String -Path $logPath -Pattern '^\[CHUNKEFFECT\].*count=')
        $initLines = @(Select-String -Path $logPath -Pattern '^\[CHUNKPROXY\] Initialized billboard debug')
    }

    $runSummary = [ordered]@{
        run_index = $index
        output_dir = $result.output_dir
        probe_exit_code = $result.probe_exit_code
        chunk_effect_samples_logged = $effectLines.Count
        proxy_initialized = ($initLines.Count -gt 0)
        proxy_tracking_events = $trackingLines.Count
        proxy_assigned_events = $assignedLines.Count
        proxy_release_events = $releaseLines.Count
        first_tracking = if ($trackingLines.Count -gt 0) { $trackingLines[0].Line } else { $null }
        first_assigned = if ($assignedLines.Count -gt 0) { $assignedLines[0].Line } else { $null }
        first_release = if ($releaseLines.Count -gt 0) { $releaseLines[0].Line } else { $null }
    }

    $runs += [pscustomobject]$runSummary
}

$summary = [ordered]@{
    captured_at = (Get-Date).ToString("s")
    repeat_count = $RepeatCount
    enable_chunk_effect_trace = [bool]$EnableChunkEffectTrace
    enable_chunk_proxy_debug = [bool]$EnableChunkProxyDebug
    chunk_log_budget = $ChunkLogBudget
    chunk_trace_entry_limit = $ChunkTraceEntryLimit
    runs = $runs
}

$summaryJson = Join-Path $seriesRoot "series_summary.json"
$summary | ConvertTo-Json -Depth 5 | Set-Content -Path $summaryJson -Encoding ASCII

$lines = @(
    "# misn03 Chunk Probe Series",
    "",
    "- Captured at: $($summary.captured_at)",
    "- Repeat count: $RepeatCount",
    "- ChunkEffect trace: $([bool]$EnableChunkEffectTrace)",
    "- Chunk proxy debug: $([bool]$EnableChunkProxyDebug)",
    "- Chunk log budget: $ChunkLogBudget",
    "- Chunk trace entry limit: $ChunkTraceEntryLimit",
    "- Post-capture wait seconds: $PostCaptureWaitSeconds",
    ""
)

foreach ($run in $runs) {
    $lines += "## Run $($run.run_index)"
    $lines += ""
    $lines += "- Output dir: $($run.output_dir)"
    $lines += "- Probe exit code: $($run.probe_exit_code)"
    $lines += "- ChunkEffect samples logged: $($run.chunk_effect_samples_logged)"
    $lines += "- Proxy initialized: $($run.proxy_initialized)"
    $lines += "- Proxy tracking events: $($run.proxy_tracking_events)"
    $lines += "- Proxy assigned events: $($run.proxy_assigned_events)"
    $lines += "- Proxy release events: $($run.proxy_release_events)"
    if ($run.first_tracking) {
        $lines += "- First tracking: ``$($run.first_tracking)``"
    }
    if ($run.first_assigned) {
        $lines += "- First assigned: ``$($run.first_assigned)``"
    }
    if ($run.first_release) {
        $lines += "- First release: ``$($run.first_release)``"
    }
    $lines += ""
}

$summaryMd = Join-Path $seriesRoot "series_summary.md"
$lines | Set-Content -Path $summaryMd -Encoding UTF8

$summary | ConvertTo-Json -Depth 5
