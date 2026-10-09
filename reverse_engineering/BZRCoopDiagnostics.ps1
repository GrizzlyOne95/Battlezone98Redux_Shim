# Private test-instance diagnostics. Session mute preserves native sound clocks.
function Set-BZRCoopIniValue([string]$Path, [string]$Section, [string]$Key, [string]$Value) {
    $text = [IO.File]::ReadAllText($Path)
    $sectionPattern = '(?ms)(^\[' + [regex]::Escape($Section) + '\]\s*\r?\n)(.*?)(?=^\[|\z)'
    $match = [regex]::Match($text, $sectionPattern)
    if (-not $match.Success) { throw "Missing [$Section] in $Path" }
    $body = $match.Groups[2].Value
    $keyPattern = '(?m)^\s*' + [regex]::Escape($Key) + '\s*=.*$'
    if ([regex]::IsMatch($body, $keyPattern)) {
        $body = [regex]::Replace($body, $keyPattern, "$Key=$Value")
    } else { $body += "$Key=$Value`r`n" }
    $text = $text.Substring(0, $match.Index) + $match.Groups[1].Value + $body + $text.Substring($match.Index + $match.Length)
    [IO.File]::WriteAllText($Path, $text)
}

function Set-BZRCoopMaxNetworkLogging([string]$Dir) {
    foreach ($key in 'RelayLogging', 'RelayLogAllControl', 'RelayLogDatagrams', 'RelayLoggingPrivateForensic', 'RelayLoggingAllUdp') {
        Set-BZRCoopIniValue (Join-Path $Dir 'openshim.ini') Diagnostics $key 1
    }
    Set-BZRCoopIniValue (Join-Path $Dir 'openshim.ini') Diagnostics RelayLoggingQueueRecords 65536
    foreach ($key in 'EnableLogging', 'LogSocketErrors', 'LogSocketLifecycle', 'LogSocketPackets', 'LogSockOptCalls', 'LogPacketReorder',
                     'EnableBufferLog', 'EnableRelayCapture', 'RelayLogAllControl', 'RelayLogDatagrams', 'EnableBZRNetTrace', 'BZRNetTracePrivate', 'BZRNetTraceAllUdp') {
        Set-BZRCoopIniValue (Join-Path $Dir 'net.ini') OpenShimSocket $key 1
    }
    # Interval zero means only the initial sample; one logs every packet.
    Set-BZRCoopIniValue (Join-Path $Dir 'net.ini') OpenShimSocket PacketLogInterval 1
    Set-BZRCoopIniValue (Join-Path $Dir 'net.ini') OpenShimSocket BufferLogPayloadBytes 2048
    # 65536 is the optimizer's default sentinel and is reduced by the forensic
    # preset. Use a distinct bounded capacity without inflating four clients'
    # memory enough to change network scheduling.
    Set-BZRCoopIniValue (Join-Path $Dir 'net.ini') OpenShimSocket BufferLogRingRecords 65535
    Set-BZRCoopIniValue (Join-Path $Dir 'net.ini') OpenShimSocket BZRNetTraceQueueRecords 65536
}

function Initialize-BZRCoopAudio {
    if ('BZRCoopAudio.Sessions' -as [type]) { return }
    Add-Type -Path (Join-Path $PSScriptRoot 'BZRCoopAudio.cs')
}

function Set-BZRCoopClientMute([int]$ProcessId) {
    Initialize-BZRCoopAudio
    [BZRCoopAudio.Sessions]::Mute($ProcessId)
}

function Test-BZRCoopDiagnosticEvidence([string]$RunDir, [int]$Clients) {
    $launch = Get-Content -LiteralPath (Join-Path $RunDir 'session-launch.json') -Raw | ConvertFrom-Json
    if (-not $launch.maxNetworkLogging -or -not $launch.muteClients -or @($launch.clients).Count -ne $Clients) {
        throw 'Missing complete maximum logging / mute launch manifest.'
    }
    foreach ($arg in '/netpktlog', '/netlog=3', '/bzrnetlog=3') {
        if ($launch.gameArgs -notcontains $arg) { throw "Missing native argument $arg" }
    }
    $mutes = @(Get-Content -LiteralPath (Join-Path $RunDir 'audio-mute.jsonl') | ForEach-Object { $_ | ConvertFrom-Json })
    $details = @()
    foreach ($i in 0..($Clients - 1)) {
        $client = $launch.clients | Where-Object index -eq $i
        $samples = @($mutes | Where-Object client -eq $i)
        $zeroEndpointMode = [bool]$launch.allowNoAudioEndpoint
        $invalidSamples = @($samples | Where-Object {
            $_.error -or ($_.mutedSessions -lt 1 -and (-not $zeroEndpointMode -or $_.activeAudioEndpoints -ne 0))
        })
        if (($client.mutedAudioSessions -lt 1 -and (-not $zeroEndpointMode -or $client.activeAudioEndpoints -ne 0)) -or
            -not $samples.Count -or $invalidSamples.Count) {
            throw "Client $i has no verified audio condition (muted session or explicit zero-endpoint mode)."
        }
        $logs = Join-Path $RunDir "client$i\logs"
        $capture = Get-Content -LiteralPath (Join-Path $logs 'bzrnet_session.json') -Raw | ConvertFrom-Json
        if (-not $capture.fullNetworkCapture -or -not $capture.privateForensic -or
            $capture.traceQueueCapacity -ne 65536 -or $capture.droppedEvents -ne 0 -or -not $capture.writerShutdownClean) {
            throw "Client $i capture was incomplete: $($capture | ConvertTo-Json -Compress)"
        }
        $shim = [IO.File]::ReadAllText((Join-Path $logs 'openshim.log'))
        if ($shim -notmatch 'relay_logging: capture=on allControl=on datagrams=on' -or
            $shim -notmatch 'profile=full privateForensic=1 allUdp=1 queueRecords=65536') {
            throw "Client $i did not enable full observational capture."
        }
        $native = [IO.File]::ReadAllText((Join-Path $logs 'BZLogger.txt'))
        if ($native -notmatch 'WebSocket Message Sent:' -or $native -notmatch 'TempStateSendAll Prev Bytes:') {
            throw "Client $i native level-3 logs are missing."
        }
        $details += @{ client = $i; audioSamples = $samples.Count;
            audioTimingQualified = ($client.mutedAudioSessions -gt 0 -and -not @($samples | Where-Object mutedSessions -lt 1).Count);
            allowNoAudioEndpoint = $zeroEndpointMode;
            droppedCaptureEvents = $capture.droppedEvents; cleanCaptureShutdown = $capture.writerShutdownClean }
    }
    foreach ($name in 'relay-trace.jsonl', 'protocol-trace.jsonl') {
        if ((Get-Item -LiteralPath (Join-Path $RunDir $name)).Length -lt 100) { throw "Missing server capture $name" }
    }
    $details
}
