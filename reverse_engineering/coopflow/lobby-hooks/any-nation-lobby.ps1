# Any Nation lobby hook (dot-sourced by BZRCoopLobby.ps1 after every guest has
# joined, before they ready). Drives the host's Any Nation button and reads the
# evidence from each client's openshim.log and the server's SetLobbyData frames.
# Sees: $hostClient $guestClients $allClients $UI Click Wait-Until Write-Step
#       $StepTimeoutSeconds. The button is created at (760,580) size 300x60 in
#       the shell's 1280x720 layout (FUN_00796880 disasm 0x797B0E..0x797AE4).
$anLogs = @{}
foreach ($c in $allClients) { $anLogs[$c.index] = Join-Path $c.dir 'logs\openshim.log' }
$anMarks = @{}
foreach ($c in $allClients) { $anMarks[$c.index] = 0 }  # whole log: the host side finishes before this hook starts
function Get-AnyNationLines($client, [string]$Pattern) {
    $fs = [IO.File]::Open($anLogs[$client.index], 'Open', 'Read', 'ReadWrite')
    try { $null = $fs.Seek($anMarks[$client.index], 'Begin'); $t = (New-Object IO.StreamReader($fs)).ReadToEnd() } finally { $fs.Dispose() }
    @([regex]::Matches($t, "(?m)^.*(?:$Pattern).*$") | ForEach-Object { ($_.Value -replace '^\[[^\]]*\] \[pid:\d+ tid:\d+\] ', '').Trim() })
}
function Wait-AnyNation([string]$Name, $client, [string]$Pattern, [int]$Count = 1) {
    $null = Wait-Until $Name { $l = @(Get-AnyNationLines $client $Pattern); if ($l.Count -ge $Count) { $l[-1] } }
}
$candidates = @(@(860, 403, 'C'), @(780, 403, 'C'), @(910, 610, 'C'))
function Click-AnyNation([string]$expectValue) {
    $before = @(Get-AnyNationLines $hostClient 'host click').Count
    foreach ($xy in $candidates) {
        Click $hostClient $xy
        $deadline = (Get-Date).AddSeconds(6)
        while ((Get-Date) -lt $deadline) {
            if (@(Get-AnyNationLines $hostClient 'host click').Count -gt $before) { return "clicked at $($xy -join ',')" }
            Start-Sleep -Milliseconds 300
        }
    }
    throw 'Any Nation button never registered a click (see steps.jsonl)'
}

# Host finished its side (button shown, list set, anyNation not published while ON).
Wait-AnyNation 'host-anynation-ready' $hostClient 'host lobby ready'
foreach ($g in $guestClients) { Wait-AnyNation "c$($g.index)-anynation-first-read" $g 'read value=' }
Write-Step 'anynation-initial-on' 'ok' @{ host = @(Get-AnyNationLines $hostClient 'ANYNATION'); guest = @(Get-AnyNationLines $guestClients[0] 'ANYNATION') }

# Step 2: host toggles OFF; clients must shrink without rejoining.
$how = Click-AnyNation '0'
Write-Step 'anynation-click-off' 'ok' @{ evidence = $how }
foreach ($g in $guestClients) {
    Wait-AnyNation "c$($g.index)-read-off" $g 'read value=0'
    Wait-AnyNation "c$($g.index)-apply-off" $g 'apply value=0'
}
Start-Sleep -Seconds 2
Write-Step 'anynation-off-evidence' 'ok' @{
    host = @(Get-AnyNationLines $hostClient 'ANYNATION');
    guest = @(Get-AnyNationLines $guestClients[0] 'ANYNATION')
}
# Toggle back ON then OFF again: the pool must restore and re-prune.
$null = Click-AnyNation '1'
foreach ($g in $guestClients) { Wait-AnyNation "c$($g.index)-read-on-again" $g 'read value=1' 2 }
Start-Sleep -Seconds 2
$null = Click-AnyNation '0'
foreach ($g in $guestClients) { Wait-AnyNation "c$($g.index)-read-off-again" $g 'read value=0' 2 }
Start-Sleep -Seconds 2
Write-Step 'anynation-final-off' 'ok' @{
    host = @(Get-AnyNationLines $hostClient 'ANYNATION');
    guest = @(Get-AnyNationLines $guestClients[0] 'ANYNATION')
}
