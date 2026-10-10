$ErrorActionPreference = 'Stop'
. "$PSScriptRoot\..\BZRCoopDiagnostics.ps1"
$temp = Join-Path ([IO.Path]::GetTempPath()) ("bzr-diagnostics-" + [Guid]::NewGuid())
New-Item -ItemType Directory -Path $temp | Out-Null
try {
    Copy-Item -LiteralPath "$PSScriptRoot\..\..\openshim.ini", "$PSScriptRoot\..\..\net.ini" -Destination $temp
    $before = [IO.File]::ReadAllText((Join-Path $temp 'net.ini'))
    Set-BZRCoopMaxNetworkLogging $temp
    $shim = [IO.File]::ReadAllText((Join-Path $temp 'openshim.ini'))
    $net = [IO.File]::ReadAllText((Join-Path $temp 'net.ini'))
    foreach ($required in 'RelayLogging=1', 'RelayLoggingAllUdp=1', 'RelayLoggingPrivateForensic=1', 'RelayLoggingQueueRecords=65536') {
        if (-not $shim.Contains($required)) { throw "Missing $required" }
    }
    foreach ($required in 'EnableLogging=1', 'PacketLogInterval=1', 'BZRNetTraceAllUdp=1', 'BufferLogPayloadBytes=2048', 'BufferLogRingRecords=65535') {
        if (-not $net.Contains($required)) { throw "Missing $required" }
    }
    $netTuneBefore = [regex]::Match($before, '(?s)\[Net\].*?\[OpenShimSocket\]').Value
    if (-not $net.Contains($netTuneBefore)) { throw 'Diagnostic setup changed gameplay network tuning.' }
    Set-BZRCoopMaxNetworkLogging $temp
    if ([IO.File]::ReadAllText((Join-Path $temp 'net.ini')) -ne $net) { throw 'Configuration is not idempotent.' }
    Set-BZRCoopIniValue (Join-Path $temp 'net.ini') OpenShimSocket NewDiagnosticKey 7
    if (-not ([IO.File]::ReadAllText((Join-Path $temp 'net.ini'))).Contains('NewDiagnosticKey=7')) { throw 'Missing key insertion failed.' }
    Initialize-BZRCoopAudio
    if ((Set-BZRCoopClientMute ([int]::MaxValue)) -ne 0) { throw 'Nonexistent PID matched an audio session.' }
    Write-Host 'PASS: unsampled diagnostics, preserved network tuning, idempotence, insertion and PID isolation'
} finally { Remove-Item -LiteralPath $temp -Recurse -Force }
