param([ValidateRange(4,160)][int]$Units = 40,
      [ValidateRange(15,300)][int]$Seconds = 60)
$script:CRFlowSkipParity = $true # Observer HUDs have no campaign presentation stream.
if ($Units % 2) { throw 'Units must be even.' }
$indices = @(Get-CRFlowClientIndices)
$samples = New-Object System.Collections.ArrayList
$samplePath = Join-Path $script:CRFlowRun.runDir 'battle-samples.jsonl'

function Sample-Battle([string]$Phase) {
    foreach ($i in $indices) {
        $sw = [Diagnostics.Stopwatch]::StartNew()
        $s = Invoke-CRFlow $i 'return BattleSnapshot()'
        $p = Get-Process -Id (Get-CRFlowClient $i).pid
        $record = [ordered]@{ at = (Get-Date).ToUniversalTime().ToString('o'); phase = $Phase;
            client = $i; commandMs = [math]::Round($sw.Elapsed.TotalMilliseconds,1);
            cpuSeconds = $p.TotalProcessorTime.TotalSeconds; workingSetBytes = $p.WorkingSet64; state = $s }
        [void]$samples.Add($record)
        ($record | ConvertTo-Json -Compress -Depth 5) | Add-Content -LiteralPath $samplePath
    }
}

Invoke-CRFlowStep 'idle baseline and native battle start' {
    Sample-Battle 'idle'
    Start-Sleep -Seconds 5
    Sample-Battle 'idle'
    foreach ($i in $indices | Where-Object { $_ -ne 0 }) { Invoke-CRFlow $i 'return BattleObserveBegin()' | Out-Null }
    Invoke-CRFlow 0 "return BattleBegin($Units, $Seconds)"
} | Out-Null

Invoke-CRFlowStep "$Units AI natural combat for $Seconds simulation seconds" {
    $clock = [Diagnostics.Stopwatch]::StartNew()
    do {
        Sample-Battle 'combat'
        $hostState = $samples[$samples.Count - $indices.Count].state
        if ($hostState.finished) { break }
        if ($clock.Elapsed.TotalSeconds -gt ($Seconds * 3 + 30)) { throw 'Battle simulation failed to finish within wall-time budget.' }
        Start-Sleep -Seconds 3
    } while ($true)
    $hostState
} | Out-Null

$hostState = $samples[$samples.Count - $indices.Count].state
foreach ($i in $indices | Where-Object { $_ -ne 0 }) { Invoke-CRFlow $i 'return BattleObserveEnd()' | Out-Null }
Add-CRFlowCheck 'native weapons consume ammo and damage units' ($hostState.ammoDrops -gt 0 -and $hostState.damageEvents -gt 0) $hostState
Add-CRFlowCheck 'native combat destroys units and produces new battlefield scrap' ($hostState.deaths -gt 0 -and $hostState.scrapObserved -gt 0 -and $hostState.peakScrap -gt 0) $hostState
Add-CRFlowCheck 'AI population reaches at least 75 percent of requested load' ($hostState.peakAI -ge [math]::Floor($Units * 0.75)) $hostState
$steady = @($samples | Where-Object { $_.client -eq 0 -and $_.phase -eq 'combat' -and $_.state.rampCompleted -and -not $_.state.finished })
$loaded = @($steady | Where-Object { ($_.state.army5 + $_.state.army6) -ge [math]::Floor($Units * 0.75) })
$loadFraction = if ($steady.Count) { $loaded.Count / $steady.Count } else { 0 }
Add-CRFlowCheck 'load is sustained after ramp rather than a brief population peak' ($loadFraction -ge 0.75 -and -not $hostState.rampFailed) @{ steadySamples=$steady.Count; loadedSamples=$loaded.Count; fraction=$loadFraction; capHit=$hostState.capHit }
foreach ($i in $indices | Where-Object { $_ -ne 0 }) {
    $last = @($samples | Where-Object client -eq $i)[-1].state
    Add-CRFlowCheck "guest $i observes both armies and new battlefield scrap" ($last.peakAI -ge [math]::Floor($Units * 0.5) -and $last.peakArmy5 -gt 0 -and $last.peakArmy6 -gt 0 -and $last.scrapObserved -gt 0) $last
}
Invoke-CRFlowStep 'host cleanup converges on all native peers' {
    Invoke-CRFlow 0 'return BattleCleanup()' | Out-Null
    foreach ($i in $indices) {
        Wait-CRFlow $i 'local s = BattleSnapshot(); return s.army5 == 0 and s.army6 == 0 and s' -TimeoutSeconds 45 | Out-Null
    }
    Sample-Battle 'cleanup'
} | Out-Null
@{ units = $Units; simulationSeconds = $Seconds; samples = $samples.Count; host = $hostState; steadyLoadFraction=$loadFraction;
   note = 'Command latency includes probe polling. Update counts/simulation clocks and CPU are diagnostic; these are not renderer FPS.' } |
    ConvertTo-Json -Depth 7 | Set-Content -LiteralPath (Join-Path $script:CRFlowRun.runDir 'battle-summary.json')
