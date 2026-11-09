# Join-flow check (no UI toggling): after the guest joins, wait for the host's
# anyNation publish and the guest's read, and record every [ANYNATION] and
# vehicle-pool log line plus the server's anyNation SetLobbyData frames.
function Get-ShimLines($client, [string]$Pattern) {
    $p = Join-Path $client.dir 'logs\openshim.log'
    $fs = [IO.File]::Open($p, 'Open', 'Read', 'ReadWrite')
    try { $t = (New-Object IO.StreamReader($fs)).ReadToEnd() } finally { $fs.Dispose() }
    @([regex]::Matches($t, "(?m)^.*(?:$Pattern).*$") | ForEach-Object { ($_.Value -replace '^\[[^\]]*\] \[pid:\d+ tid:\d+\] ', '').Trim() })
}
$deadline = (Get-Date).AddSeconds(25)
while ((Get-Date) -lt $deadline) {
    $g = @(Get-ShimLines $guestClients[0] 'read value=').Count
    $h = @(Get-ShimLines $hostClient 'publish value=|host lobby ready').Count
    if ($g -ge 2 -and $h -ge 1) { break }
    Start-Sleep -Milliseconds 500
}
Start-Sleep -Seconds 4
$serverLines = @(Select-String -LiteralPath $ServerLog -Pattern 'anyNation' | ForEach-Object { $_.Line.Substring(0, [Math]::Min(300, $_.Line.Length)) })
Write-Step 'anynation-join-check' 'ok' @{
    host = @(Get-ShimLines $hostClient 'ANYNATION')
    guest = @(Get-ShimLines $guestClients[0] 'ANYNATION')
    server = $serverLines
}
