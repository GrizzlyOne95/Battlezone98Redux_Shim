# Strategy battle load: every one of the 4 clients owns its own AI army (teams
# 5..8, sides 5+6 versus 7+8). Exercises cross-client hit registration (damage
# is applied by the victim's owner) and remote-unit position replication.
# Units is the TOTAL across clients and must be divisible by 4.
param([ValidateRange(4,160)][int]$Units = 40,
      [ValidateRange(15,300)][int]$Seconds = 60,
      [ValidateRange(0,16)][int]$Beacons = 0,
      [ValidateRange(0,128)][int]$Powerups = 0)
$script:CRFlowSkipParity = $true # Observer HUDs have no campaign presentation stream.
if ($Units % 4) { throw 'Strategy mode: Units must be divisible by 4.' }
if ($Beacons -or $Powerups) { throw 'Strategy mode does not stage beacons or powerups.' }
$per = [int]($Units / 4)
$indices = @(Get-CRFlowClientIndices)
if ($indices.Count -ne 4) { throw "Strategy mode needs exactly 4 clients, found $($indices.Count)." }
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

function Get-LastArmy([int]$Index) {
    $rows = @($samples | Where-Object { $_.client -eq $Index })
    $rows[$rows.Count - 1].state.army
}

# Per-client replication/warp table plus per-team hit-registration proxy.
function Get-StrategyTable {
    $clients = [ordered]@{}
    $byTeam = @{}
    foreach ($i in $indices) {
        $a = Get-LastArmy $i
        if ($null -eq $a) { continue }
        $rate = $null
        if ($a.rSamples -gt 0) { $rate = [math]::Round(1000.0 * $a.rWarps / $a.rSamples, 3) }
        $localRate = $null
        if ($a.lSamples -gt 0) { $localRate = [math]::Round(1000.0 * $a.lWarps / $a.lSamples, 3) }
        $clients["$i"] = [ordered]@{ team = $a.team; remoteUnitFrames = $a.rSamples; remoteWarps = $a.rWarps;
            remoteWarpsPer1000UnitFrames = $rate; remoteJumpsOver25m = $a.rBig; remoteMaxJumpM = [math]::Round($a.rMax,1);
            remoteWarpDistanceSumM = [math]::Round($a.rDist,1);
            localUnitFrames = $a.lSamples; localWarps = $a.lWarps; localWarpsPer1000UnitFrames = $localRate;
            peaks = @($a.p5, $a.p6, $a.p7, $a.p8); spawnFailed = $a.spawnFailed; localOwned = $a.localOwned }
        $byTeam[[int]$a.team] = $a
    }
    $teams = [ordered]@{}
    foreach ($t in ($byTeam.Keys | Sort-Object)) {
        $a = $byTeam[$t]
        $enemyShots = 0
        foreach ($o in $byTeam.Keys) { if ((($o -le 6) -ne ($t -le 6))) { $enemyShots += $byTeam[$o].ammoDrops } }
        $perShot = $null
        if ($enemyShots -gt 0) { $perShot = [math]::Round($a.damageEvents / $enemyShots, 4) }
        $teams["$t"] = [ordered]@{ spawned = $a.spawned; deaths = $a.deaths; damageTaken = $a.damageEvents;
            ownShots = $a.ammoDrops; enemyShots = $enemyShots; damagePerEnemyShot = $perShot }
    }
    [ordered]@{ clients = $clients; teams = $teams }
}

Invoke-CRFlowStep 'idle baseline and strategy battle start on all clients' {
    Sample-Battle 'idle'
    Start-Sleep -Seconds 5
    Sample-Battle 'idle'
    # Back-to-back so every client's clock starts within about a second.
    foreach ($i in $indices) { Invoke-CRFlow $i "return ArmyBegin($per, $Seconds)" | Out-Null }
} | Out-Null

Invoke-CRFlowStep "$Units AI ($per per client) strategy combat for $Seconds simulation seconds after ramp" {
    $clock = [Diagnostics.Stopwatch]::StartNew()
    do {
        Sample-Battle 'combat'
        $done = $true
        foreach ($i in $indices) { $a = Get-LastArmy $i; if ($null -eq $a -or -not $a.finished) { $done = $false } }
        if ($done) { break }
        if ($clock.Elapsed.TotalSeconds -gt ($Seconds * 3 + 60)) { throw 'Strategy battle failed to finish within wall-time budget.' }
        Start-Sleep -Seconds 3
    } while ($true)
} | Out-Null

$table = Get-StrategyTable
$floorPeak = [math]::Max(1, [math]::Floor($per * 0.5))
$teamsSeen = @{}
foreach ($i in $indices) {
    $a = Get-LastArmy $i
    $teamsSeen["$($a.team)"] = $i
    Add-CRFlowCheck "client $i owns a distinct army team 5..8 and created its whole army" ($a.team -ge 5 -and $a.team -le 8 -and $a.spawnFailed -eq 0 -and $a.spawned -ge $per) $a
    # Replication of every owner's BuildSyncObject army to this peer.
    $missing = @()
    foreach ($t in 5..8) { if ($a."p$t" -lt $floorPeak) { $missing += "team $t (peak $($a."p$t") < $floorPeak)" } }
    Add-CRFlowCheck "client $i observed all four armies (BuildSyncObject replication): $($missing -join '; ')" ($missing.Count -eq 0) $a
    Add-CRFlowCheck "client $i army took damage and lost units (cross-client combat)" ($a.damageEvents -gt 0 -and $a.deaths -gt 0) $a
}
Add-CRFlowCheck 'four distinct army teams across the four clients' ($teamsSeen.Count -eq 4) $teamsSeen
# Remote warp metrics are reported, not pass/fail.
Write-Host ('Strategy remote warp / hit-registration table: ' + ($table | ConvertTo-Json -Depth 6 -Compress))
$summary = [ordered]@{ mode = 'strategy'; units = $Units; perClient = $per; simulationSeconds = $Seconds;
    samples = $samples.Count; table = $table; cleanupQualified = $false;
    perClientSnapshots = [ordered]@{} }
foreach ($i in $indices) { $summary.perClientSnapshots["$i"] = @($samples | Where-Object { $_.client -eq $i })[-1].state }
$summaryPath = Join-Path $script:CRFlowRun.runDir 'battle-summary.json'
$summary | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $summaryPath
Invoke-CRFlowStep 'each owner removes its own army; every client converges to zero army craft' {
    foreach ($i in $indices) { Invoke-CRFlow $i 'return ArmyCleanup()' | Out-Null }
    foreach ($i in $indices) {
        Wait-CRFlow $i 'local s = BattleSnapshot(); return s.army.cleaned and s.army.craft == 0 and s' -TimeoutSeconds 45 | Out-Null
    }
    Sample-Battle 'cleanup'
} | Out-Null
$summary.cleanupQualified = $true
$summary.note = 'Command latency includes probe polling. Warp rates use per-frame GetPosition deltas against 80 m/s * dt + 10 m; not renderer FPS.'
$summary | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $summaryPath
