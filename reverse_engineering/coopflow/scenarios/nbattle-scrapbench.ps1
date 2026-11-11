# Scrap-accumulation bench scenario (Run-BZRCoopScrapBench.ps1). The host
# keeps $Units AI (two armies) alive for $Seconds sim seconds; scrap is never
# cleaned unless -ClearAtSeconds > 0, after which every sample also removes all
# scrap on every client (control arm). Census goes to scrapbench-samples.jsonl;
# frame times come from OPENSHIM_PERF_TELEMETRY in each client's logs\.
param([ValidateRange(4,160)][int]$Units = 40,
      [ValidateRange(15,1800)][int]$Seconds = 300,
      [int]$ClearAtSeconds = 0,
      [ValidateRange(1,60)][int]$SampleEvery = 5)
$script:CRFlowSkipParity = $true
$indices = @(Get-CRFlowClientIndices)
$samplePath = Join-Path $script:CRFlowRun.runDir 'scrapbench-samples.jsonl'

function Write-ScrapSample([string]$Phase, [double]$Elapsed, [hashtable]$Extra = @{}) {
    foreach ($i in $indices) {
        $s = Invoke-CRFlow $i 'return ScrapBenchCensus()'
        $rec = [ordered]@{ local = (Get-Date).ToString('o'); elapsed = [math]::Round($Elapsed, 1); phase = $Phase
            client = $i; pid = (Get-CRFlowClient $i).pid; state = $s }
        foreach ($k in $Extra.Keys) { $rec[$k] = $Extra[$k] }
        ($rec | ConvertTo-Json -Compress -Depth 6) | Add-Content -LiteralPath $samplePath
    }
}

Invoke-CRFlowStep 'idle baseline and battle start' {
    Write-ScrapSample 'idle' -10
    Start-Sleep -Seconds 10
    Write-ScrapSample 'idle' 0
    foreach ($i in $indices | Where-Object { $_ -ne 0 }) { Invoke-CRFlow $i 'return BattleObserveBegin()' | Out-Null }
    Invoke-CRFlow 0 "return BattleBegin($Units, $Seconds, 0, 0)"
} | Out-Null

$finalState = Invoke-CRFlowStep "$Units AI for $Seconds s, scrap kept$(if ($ClearAtSeconds) { " until $ClearAtSeconds s" })" {
    $clock = [Diagnostics.Stopwatch]::StartNew()
    do {
        $t = $clock.Elapsed.TotalSeconds
        $extra = @{}
        $phase = 'combat'
        if ($ClearAtSeconds -gt 0 -and $t -ge $ClearAtSeconds) {
            $phase = 'cleared'
            $extra.removed = @($indices | ForEach-Object { Invoke-CRFlow $_ 'return ScrapBenchClear()' })
        }
        Write-ScrapSample $phase $t $extra
        $hostState = Invoke-CRFlow 0 'return BattleSnapshot()'
        if ($hostState.finished) { break }
        if ($t -gt ($Seconds * 2 + 60)) { throw 'Battle did not finish within the wall-time budget.' }
        Start-Sleep -Seconds $SampleEvery
    } while ($true)
    $hostState
}
Add-CRFlowCheck 'combat produced deaths' ($finalState.deaths -gt 0) @{ deaths = $finalState.deaths; spawned = $finalState.spawned }
