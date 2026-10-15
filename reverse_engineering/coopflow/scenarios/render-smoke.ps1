# Short multi-client rendering control; no mission progression is claimed.
param([ValidateRange(5, 180)][int]$ObserveSeconds = 45)
Invoke-CRFlowStep 'all clients answer probes before rendering observation' {
    foreach ($client in Get-CRFlowClientIndices) {
        Wait-CRFlowEvent $client attach -TimeoutSeconds 120 | Out-Null
        Wait-CRFlow $client 'return role().ready and role()' -TimeoutSeconds 60 | Out-Null
    }
    $true
}
Invoke-CRFlowStep 'clients remain responsive during rendering observation' {
    $end = (Get-Date).AddSeconds($ObserveSeconds)
    do {
        foreach ($client in Get-CRFlowClientIndices) {
            Invoke-CRFlow $client 'return {time=GetTime(), role=role()}' | Out-Null
        }
        Start-Sleep -Seconds 3
    } while ((Get-Date) -lt $end)
    $true
}
foreach ($client in Get-CRFlowClientIndices) {
    $root = (Get-CRFlowClient $client).dir
    $log = Join-Path $root 'logs\openshim.log'
    $hits = @(Select-String -LiteralPath $log -Pattern 'device recreation #|device lost|hardware adapter did not settle' | ForEach-Object { $_.Line.Trim() })
    Add-CRFlowCheck "c$client no device-loss/recreation diagnostics" ($hits.Count -eq 0) $hits
}
