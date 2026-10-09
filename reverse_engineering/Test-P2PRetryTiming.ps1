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
    Write-Host '[PASS] Prevalidation, section isolation, durable backup, and exact byte restoration.'
} finally {
    # Remove only the explicitly created temporary files; no recursive deletion.
    foreach ($file in @('client0\openshim.ini','client1\openshim.ini','backup\originals.json')) {
        Remove-Item -LiteralPath (Join-Path $root $file) -ErrorAction SilentlyContinue
    }
    foreach ($dir in @('client0','client1','backup','bad-backup')) { Remove-Item -LiteralPath (Join-Path $root $dir) -ErrorAction SilentlyContinue }
    Remove-Item -LiteralPath $root -ErrorAction SilentlyContinue
}
