# Sanitized evidence fixtures: never launches a client or touches its files.
$ErrorActionPreference = 'Stop'
. "$PSScriptRoot\BZRCoopDiagnostics.ps1"
$fixture = Join-Path ([IO.Path]::GetTempPath()) ('bzr-evidence-' + [guid]::NewGuid())
New-Item -ItemType Directory -Path $fixture | Out-Null
try {
    $logs = Join-Path $fixture 'client0\logs'
    New-Item -ItemType Directory -Path $logs -Force | Out-Null
    $capture = @{fullNetworkCapture=$true; privateForensic=$true; traceQueueCapacity=65536; droppedEvents=0; writerShutdownClean=$true}
    $capture | ConvertTo-Json | Set-Content (Join-Path $logs 'bzrnet_session.json')
    Set-Content (Join-Path $logs 'openshim.log') 'relay_logging: capture=on allControl=on datagrams=on profile=full privateForensic=1 allUdp=1 queueRecords=65536'
    Set-Content (Join-Path $logs 'BZLogger.txt') 'WebSocket Message Sent: TempStateSendAll Prev Bytes:'
    foreach ($name in 'relay-trace.jsonl','protocol-trace.jsonl') { Set-Content (Join-Path $fixture $name) ('x' * 120) }

    function Check-Case([string]$Name, [bool]$Allow, [int]$Muted, $Endpoints, [bool]$MustPass, [bool]$Qualified, [switch]$WatcherError, [switch]$MissingSample) {
        $client = @{index=0; mutedAudioSessions=$Muted; activeAudioEndpoints=$Endpoints}
        @{maxNetworkLogging=$true; muteClients=$true; allowNoAudioEndpoint=$Allow;
          gameArgs=@('/netpktlog','/netlog=3','/bzrnetlog=3'); clients=@($client)} |
            ConvertTo-Json -Depth 5 | Set-Content (Join-Path $fixture 'session-launch.json')
        $sample = @{client=0; mutedSessions=$Muted; activeAudioEndpoints=$Endpoints}
        if ($WatcherError) { $sample.error = 'synthetic watcher error' }
        if ($MissingSample) { Set-Content (Join-Path $fixture 'audio-mute.jsonl') '' }
        else { $sample | ConvertTo-Json -Compress | Set-Content (Join-Path $fixture 'audio-mute.jsonl') }
        $failed = $false
        try { $result = @(Test-BZRCoopDiagnosticEvidence $fixture 1) } catch { $failed = $true }
        if ($MustPass -eq $failed) { throw "Unexpected verdict: $Name" }
        if ($MustPass -and [bool]$result[0].audioTimingQualified -ne $Qualified) { throw "Incorrect audio qualification: $Name" }
        Write-Host "PASS: $Name"
    }
    Check-Case 'default muted audio and complete capture' $false 1 1 $true $true
    Check-Case 'explicit zero endpoints is audio-unqualified' $true 0 0 $true $false
    Check-Case 'zero endpoints rejected by default' $false 0 0 $false $false
    Check-Case 'active endpoint with missing mute rejected' $true 0 1 $false $false
    Check-Case 'missing endpoint provenance rejected' $true 0 $null $false $false
    Check-Case 'persisted watcher error rejected' $true 0 0 $false $false -WatcherError
    Check-Case 'missing periodic observation rejected' $true 0 0 $false $false -MissingSample
    $capture.writerShutdownClean = $false
    $capture | ConvertTo-Json | Set-Content (Join-Path $logs 'bzrnet_session.json')
    Check-Case 'unclean capture still rejected with zero endpoints' $true 0 0 $false $false
} finally {
    # Only remove the exact newly created fixture beneath the temp directory.
    $resolved = [IO.Path]::GetFullPath($fixture)
    $tempRoot = [IO.Path]::GetFullPath([IO.Path]::GetTempPath()).TrimEnd('\') + '\'
    if (-not $resolved.StartsWith($tempRoot, [StringComparison]::OrdinalIgnoreCase)) { throw 'Fixture cleanup escaped temp root' }
    Remove-Item -LiteralPath $resolved -Recurse -Force
}
