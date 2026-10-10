$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot 'P2PRetryTiming.ps1')
function Assert([bool]$Condition, [string]$Message) { if (-not $Condition) { throw $Message } }
$root = Join-Path ([IO.Path]::GetTempPath()) ('bzr-retry-test-' + [guid]::NewGuid())
$null = New-Item -ItemType Directory -Path $root
$instances = @()
try {
    foreach ($i in 0..1) {
        $dir = Join-Path $root "client$i"
        $null = New-Item -ItemType Directory -Path $dir
        $instances += $dir
    }
    $original = [byte[]](239,187,191) + [Text.Encoding]::UTF8.GetBytes("[Graphics]`r`nRenderer=DX9`r`n[Network]`r`nReliableFirstRetryMs=1000`r`nReliableRetryIntervalMs=2500`r`nReliableSendBacklogFix=1`r`n[Other]`r`nReliableFirstRetryMs=777`r`nLabel=é`r`n")
    foreach ($dir in $instances) { [IO.File]::WriteAllBytes((Join-Path $dir 'openshim.ini'), $original) }
    # A malformed second client must prevent any write to the first client.
    [IO.File]::AppendAllText((Join-Path $instances[1] 'openshim.ini'), "[Network]`r`n")
    $rejected = $false
    try { Set-P2PRetryTiming $instances '300/800' (Join-Path $root 'bad-backup') | Out-Null } catch { $rejected = $true }
    Assert $rejected 'Repeated Network section was accepted.'
    Assert ([Convert]::ToBase64String([IO.File]::ReadAllBytes((Join-Path $instances[0] 'openshim.ini'))) -eq [Convert]::ToBase64String($original)) 'Prevalidation changed the first client.'
    [IO.File]::WriteAllBytes((Join-Path $instances[1] 'openshim.ini'), $original)
    $backup = Join-Path $root 'backup'
    $records = @(Set-P2PRetryTiming $instances '300/800' $backup)
    $updated = [Text.Encoding]::UTF8.GetString([IO.File]::ReadAllBytes((Join-Path $instances[0] 'openshim.ini')))
    Assert ($updated.Contains("ReliableFirstRetryMs = 300`r`nReliableRetryIntervalMs = 800`r`n")) 'Timer pair was not applied.'
    Assert ($updated.Contains("[Other]`r`nReliableFirstRetryMs=777`r`nLabel=é")) 'Another section or non-ASCII data changed.'
    Assert ($updated.Contains('ReliableSendBacklogFix=1')) 'The fix setting changed.'
    $saved = Get-Content -LiteralPath (Join-Path $backup 'originals.json') -Raw | ConvertFrom-Json
    Assert ($saved.Count -eq 2) 'Durable recovery records are missing.'
    foreach ($r in $saved) { Assert ($r.originalBase64 -eq [Convert]::ToBase64String($original)) 'Durable original bytes differ.' }
    Restore-P2PRetryTiming $records
    foreach ($dir in $instances) {
        Assert ([Convert]::ToBase64String([IO.File]::ReadAllBytes((Join-Path $dir 'openshim.ini'))) -eq [Convert]::ToBase64String($original)) 'Exact byte restoration failed.'
    }
    foreach ($token in @('49/800','300/10001','+300/800','300ms/800','99999999999999999/800')) {
        $rejected = $false
        try { ConvertTo-P2PRetryTiming $token | Out-Null } catch { $rejected = $true }
        Assert $rejected "Invalid timer pair accepted: $token"
    }
    $added = Set-P2PRetryTimingText '[Graphics]' '50/10000'
    Assert ($added.Contains("[Network]`nReliableFirstRetryMs = 50`nReliableRetryIntervalMs = 10000`n")) 'A missing Network section or timer range boundary failed.'
    # Early-receive token: explicit 0/1, round trip, replacement and removal confined to [Network].
    $plain = ConvertTo-P2PRetryTiming '1000/2500'
    $early = ConvertTo-P2PRetryTiming '1000/2500+early'
    Assert (($plain.early -eq 0) -and ($plain.token -eq '1000/2500') -and ($early.early -eq 1) -and ($early.token -eq '1000/2500+early')) 'Early token did not round trip.'
    foreach ($token in @('300/800+','300/800+Early','300/800+early+early','+early','49/800+early')) {
        $rejected = $false
        try { ConvertTo-P2PRetryTiming $token | Out-Null } catch { $rejected = $true }
        Assert $rejected "Invalid early token accepted: $token"
    }
    $withEarly = Set-P2PRetryTimingText "[Network]`r`nEarlyUnreliableAccept=0`r`nLabel=x`r`nEarlyUnreliableAccept = 1`r`n[Other]`r`nEarlyUnreliableAccept=7`r`n" '300/800+early'
    Assert ($withEarly -ceq "[Network]`r`nLabel=x`r`nReliableFirstRetryMs = 300`r`nReliableRetryIntervalMs = 800`r`nEarlyUnreliableAccept = 1`r`nEarlyNakAccept = 0`r`n[Other]`r`nEarlyUnreliableAccept=7`r`n") 'Early key was not replaced only inside [Network].'
    $off = Set-P2PRetryTimingText "[Network]`nEarlyUnreliableAccept=1`n" '300/800'
    Assert ($off -ceq "[Network]`nReliableFirstRetryMs = 300`nReliableRetryIntervalMs = 800`nEarlyUnreliableAccept = 0`nEarlyNakAccept = 0`n") 'Plain token did not write an explicit early 0.'
    Assert ((Set-P2PRetryTimingText '[Graphics]' '50/10000+early').Contains("EarlyUnreliableAccept = 1`n")) 'A missing Network section did not receive the early key.'
    # NAK token: canonical order early then nak, explicit EarlyNakAccept 0/1, same section rules.
    $both = ConvertTo-P2PRetryTiming '300/800+early+nak'
    $nakOnly = ConvertTo-P2PRetryTiming '300/800+nak'
    Assert (($both.early -eq 1) -and ($both.nak -eq 1) -and ($both.token -eq '300/800+early+nak') -and ($nakOnly.early -eq 0) -and ($nakOnly.nak -eq 1) -and ($nakOnly.token -eq '300/800+nak') -and ($plain.nak -eq 0)) 'NAK token did not round trip.'
    foreach ($token in @('300/800+nak+early','300/800+nak+nak','300/800+early+early+nak','300/800+NAK','300/800+Nak','300/800+early+','300/800+nakk','+nak')) {
        $rejected = $false
        try { ConvertTo-P2PRetryTiming $token | Out-Null } catch { $rejected = $true }
        Assert $rejected "Invalid NAK token accepted: $token"
    }
    $withNak = Set-P2PRetryTimingText "[Network]`r`nEarlyNakAccept=0`r`nLabel=x`r`nEarlyNakAccept = 1`r`n[Other]`r`nEarlyNakAccept=7`r`n" '300/800+nak'
    Assert ($withNak -ceq "[Network]`r`nLabel=x`r`nReliableFirstRetryMs = 300`r`nReliableRetryIntervalMs = 800`r`nEarlyUnreliableAccept = 0`r`nEarlyNakAccept = 1`r`n[Other]`r`nEarlyNakAccept=7`r`n") 'NAK key was not replaced only inside [Network].'
    $offNak = Set-P2PRetryTimingText "[Network]`nEarlyNakAccept=1`nEarlyUnreliableAccept=1`n" '300/800'
    Assert ($offNak -ceq "[Network]`nReliableFirstRetryMs = 300`nReliableRetryIntervalMs = 800`nEarlyUnreliableAccept = 0`nEarlyNakAccept = 0`n") 'Plain token did not write explicit early and NAK 0.'
    Assert ((Set-P2PRetryTimingText '[Graphics]' '50/10000+early+nak').Contains("EarlyUnreliableAccept = 1`nEarlyNakAccept = 1`n")) 'A missing Network section did not receive both keys.'
    Write-Host '[PASS] Prevalidation, section isolation, durable backup, and exact byte restoration.'
} finally {
    # Remove only the explicitly created temporary files; no recursive deletion.
    foreach ($file in @('client0\openshim.ini','client1\openshim.ini','backup\originals.json')) {
        Remove-Item -LiteralPath (Join-Path $root $file) -ErrorAction SilentlyContinue
    }
    foreach ($dir in @('client0','client1','backup','bad-backup')) { Remove-Item -LiteralPath (Join-Path $root $dir) -ErrorAction SilentlyContinue }
    Remove-Item -LiteralPath $root -ErrorAction SilentlyContinue
}
