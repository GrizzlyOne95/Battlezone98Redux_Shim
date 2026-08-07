[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("Start", "Stop", "Mark")]
    [string]$Action,
    [string]$GamePath = "",
    [int]$PayloadBytes = 2048,
    [int]$RingRecords = 32768,
    [int]$SocketId = 0,
    [string]$PeerFilter = "",
    [switch]$RelayCapture,
    [switch]$PrivateForensic,
    [switch]$AllUdp,
    [int]$TraceQueueRecords = 4096,
    [string]$Message = ""
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSCommandPath
$baseLogger = Join-Path $repoRoot "buffer_logger_windows.ps1"
$stateFile = Join-Path $repoRoot "test_bundles\openshim_buffer_state\windows_current_session.txt"

if (-not (Test-Path $baseLogger)) {
    throw "buffer_logger_windows.ps1 was not found beside this wrapper."
}

function Get-CurrentSessionDir {
    if (-not (Test-Path $stateFile)) { return "" }
    return (Get-Content $stateFile -Raw).Trim()
}

function Get-TraceEnvironmentLines {
    $lines = New-Object System.Collections.Generic.List[string]
    $lines.Add("set BZ_BZRNET_TRACE=1")
    $lines.Add("set BZ_BZRNET_TRACE_QUEUE=$TraceQueueRecords")
    if ($PrivateForensic) { $lines.Add("set BZ_BZRNET_TRACE_PRIVATE=1") }
    # Relay captures intentionally keep dynamic direct/candidate UDP visible as
    # well as 1338/1339 so fallback/selection attempts are not hidden.
    if ($AllUdp -or $RelayCapture) { $lines.Add("set BZ_BZRNET_TRACE_ALL_UDP=1") }
    return $lines
}

function Get-GameExecutableInfo {
    param([string]$ResolvedGamePath)

    $steamExe = Join-Path $ResolvedGamePath "battlezone98redux.exe"
    if (Test-Path $steamExe) {
        return [pscustomobject]@{ Platform = "Steam"; Path = $steamExe }
    }

    $gogExe = Join-Path $ResolvedGamePath "BZR.exe"
    if (Test-Path $gogExe) {
        return [pscustomobject]@{ Platform = "GOG"; Path = $gogExe }
    }

    return [pscustomobject]@{ Platform = "Unknown"; Path = "" }
}

function Get-SafeFileIdentity {
    param([string]$Path)

    if (-not $Path -or -not (Test-Path $Path)) { return $null }
    $item = Get-Item $Path
    $version = $null
    try { $version = $item.VersionInfo.FileVersion } catch { }
    $sha = (Get-FileHash -Algorithm SHA256 -Path $Path).Hash.ToLowerInvariant()
    return [ordered]@{
        fileName = $item.Name
        sizeBytes = $item.Length
        fileVersion = $version
        sha256 = $sha
    }
}

function New-LaunchProfile {
    return [ordered]@{
        bzrNetTrace = $true
        relayCaptureRequested = [bool]$RelayCapture
        privateForensic = [bool]$PrivateForensic
        allUdpHighlights = [bool]($AllUdp -or $RelayCapture)
        traceQueueRecords = $TraceQueueRecords
        bufferPayloadBytes = $(if ($RelayCapture) { 2048 } else { $PayloadBytes })
        bufferRingRecords = $RingRecords
    }
}

function Copy-ExistingLaunchProfile {
    param($ExistingProfile)

    if (-not $ExistingProfile) { return $null }
    return [ordered]@{
        bzrNetTrace = [bool]$ExistingProfile.bzrNetTrace
        relayCaptureRequested = [bool]$ExistingProfile.relayCaptureRequested
        privateForensic = [bool]$ExistingProfile.privateForensic
        allUdpHighlights = [bool]$ExistingProfile.allUdpHighlights
        traceQueueRecords = [int]$ExistingProfile.traceQueueRecords
        bufferPayloadBytes = [int]$ExistingProfile.bufferPayloadBytes
        bufferRingRecords = [int]$ExistingProfile.bufferRingRecords
    }
}

function Write-CaptureIdentity {
    param(
        [string]$SessionDir,
        [ValidateSet("start", "stop")]
        [string]$Stage
    )

    $gamePathFile = Join-Path $SessionDir "game_path.txt"
    if (-not (Test-Path $gamePathFile)) { return }
    $resolvedGamePath = (Get-Content $gamePathFile -Raw).Trim()
    $game = Get-GameExecutableInfo -ResolvedGamePath $resolvedGamePath
    $winmm = Join-Path $resolvedGamePath "winmm.dll"

    $identityPath = Join-Path $SessionDir "bzrnet_capture_identity.json"
    $existing = $null
    if (Test-Path $identityPath) {
        try { $existing = Get-Content $identityPath -Raw | ConvertFrom-Json } catch { }
    }

    $startUtc = if ($existing -and $existing.captureStartUtc) {
        [string]$existing.captureStartUtc
    } else {
        (Get-Date).ToUniversalTime().ToString("o")
    }

    # Stop is normally invoked without repeating Start's switches. Preserve the
    # profile captured at Start instead of accidentally rewriting it with Stop's
    # default parameter values.
    $launchProfile = $null
    if ($Stage -eq "stop" -and $existing -and $existing.launchProfile) {
        $launchProfile = Copy-ExistingLaunchProfile -ExistingProfile $existing.launchProfile
    }
    if (-not $launchProfile) {
        $launchProfile = New-LaunchProfile
    }

    $identity = [ordered]@{
        formatVersion = 1
        captureStartUtc = $startUtc
        captureStopUtc = $(if ($Stage -eq "stop") { (Get-Date).ToUniversalTime().ToString("o") } else { $null })
        platform = $game.Platform
        gameExecutable = $(Get-SafeFileIdentity -Path $game.Path)
        openShim = $(Get-SafeFileIdentity -Path $winmm)
        launchProfile = $launchProfile
        note = "Launch-profile fields record wrapper-requested settings, not proof of engine-effective values. Runtime trace/config evidence should be used for effective-state claims."
    }
    $identity | ConvertTo-Json -Depth 6 | Out-File -FilePath $identityPath -Encoding utf8
}

function Update-LaunchArtifacts {
    param([string]$SessionDir)

    $envLines = @(Get-TraceEnvironmentLines)
    $steamFile = Join-Path $SessionDir "steam_launch_options.txt"
    if (Test-Path $steamFile) {
        $lines = @(Get-Content $steamFile)
        for ($i = 0; $i -lt $lines.Count; $i++) {
            if ($lines[$i] -like "*%command%*" -and $lines[$i] -notlike "*BZ_BZRNET_TRACE=1*") {
                $prefix = ($envLines -join " && ") + " && "
                $lines[$i] = $prefix + $lines[$i]
            }
        }
        $lines | Out-File -FilePath $steamFile -Encoding utf8
    }

    $cmdFile = Join-Path $SessionDir "launch_with_buffer_log.cmd"
    if (Test-Path $cmdFile) {
        $lines = @(Get-Content $cmdFile)
        $newLines = New-Object System.Collections.Generic.List[string]
        if ($lines.Count -gt 0) {
            $newLines.Add($lines[0])
            foreach ($envLine in $envLines) { $newLines.Add($envLine) }
            for ($i = 1; $i -lt $lines.Count; $i++) { $newLines.Add($lines[$i]) }
        } else {
            $newLines.Add("@echo off")
            foreach ($envLine in $envLines) { $newLines.Add($envLine) }
        }
        $newLines | Out-File -FilePath $cmdFile -Encoding ascii
    }
}

function Add-CaptureReadme {
    param([string]$SessionDir)

    $readme = Join-Path $SessionDir "README_NEXT_STEPS.txt"
    Add-Content -Path $readme -Value @(
        "",
        "BZRNet native trace profile:",
        "- BZ_BZRNET_TRACE=1",
        "- private forensic trace: $([int][bool]$PrivateForensic)",
        "- all UDP semantic wire highlights: $([int][bool]($AllUdp -or $RelayCapture))",
        "- trace queue records: $TraceQueueRecords",
        "- relay capture: $([int][bool]$RelayCapture)",
        "",
        "Expected additional game log files:",
        "- logs\bzrnet_session.json",
        "- logs\bzrnet_trace.jsonl",
        "- bzrnet_capture_identity.json (platform/build/hash + requested capture profile)",
        "",
        "Raw binary/Wireshark captures and private-forensic traces may contain endpoint or identity data.",
        "Authentication tickets and lobby passwords are always redacted from bzrnet_trace.jsonl.",
        "Use ordinary stock-client UI actions only against the official service; do not fuzz production BZRNet."
    )
}

function Copy-NativeTraceBeforeBaseStop {
    param([string]$SessionDir)

    $gamePathFile = Join-Path $SessionDir "game_path.txt"
    if (-not (Test-Path $gamePathFile)) { return }
    $resolvedGamePath = (Get-Content $gamePathFile -Raw).Trim()
    foreach ($name in @("bzrnet_session.json", "bzrnet_trace.jsonl")) {
        $source = Join-Path $resolvedGamePath ("logs\" + $name)
        if (Test-Path $source) {
            Copy-Item -Force $source (Join-Path $SessionDir $name)
        }
    }
}

function Write-Hashes {
    param([string]$SessionDir)

    if (-not (Test-Path $SessionDir)) { return }
    $hashFile = Join-Path $SessionDir "SHA256SUMS.txt"
    $rows = New-Object System.Collections.Generic.List[string]
    foreach ($file in Get-ChildItem -Path $SessionDir -File | Sort-Object Name) {
        if ($file.Name -eq "SHA256SUMS.txt") { continue }
        try {
            $hash = Get-FileHash -Algorithm SHA256 -Path $file.FullName
            $rows.Add("$($hash.Hash.ToLowerInvariant())  $($file.Name)")
        } catch {
            $rows.Add("ERROR  $($file.Name)  $($_.Exception.Message)")
        }
    }
    $rows | Out-File -FilePath $hashFile -Encoding ascii
}

function Rebuild-ArchiveWithFinalHashes {
    param([string]$SessionDir)

    if (-not (Test-Path $SessionDir)) { return }
    Write-Hashes -SessionDir $SessionDir
    $zipPath = "$SessionDir.zip"
    if (Test-Path $zipPath) { Remove-Item -Force $zipPath }
    Compress-Archive -Path (Join-Path $SessionDir "*") -DestinationPath $zipPath
}

function Start-BzrNetCapture {
    if ($TraceQueueRecords -lt 256 -or $TraceQueueRecords -gt 65536) {
        throw "TraceQueueRecords must be between 256 and 65536."
    }

    $baseArgs = @{
        Action = "Start"
        GamePath = $GamePath
        PayloadBytes = $PayloadBytes
        RingRecords = $RingRecords
        SocketId = $SocketId
        PeerFilter = $PeerFilter
    }
    if ($RelayCapture) { $baseArgs["RelayCapture"] = $true }

    & $baseLogger @baseArgs

    $sessionDir = Get-CurrentSessionDir
    if (-not $sessionDir -or -not (Test-Path $sessionDir)) {
        throw "Base logger started but no active session directory was found."
    }

    Update-LaunchArtifacts -SessionDir $sessionDir
    Add-CaptureReadme -SessionDir $sessionDir
    Write-CaptureIdentity -SessionDir $sessionDir -Stage start

    @(
        "BZRNet native capture session prepared.",
        "Session: $sessionDir",
        "Steam: use the updated steam_launch_options.txt line.",
        "Direct/GOG: use the updated launch_with_buffer_log.cmd.",
        $(if ($RelayCapture) { "Relay profile includes /iprelay, dynamic UDP semantic highlights, and the 2048-byte binary UDP capture." } else { "BZRNet tracing is enabled without forcing relay." })
    ) | ForEach-Object { Write-Host $_ }
}

function Stop-BzrNetCapture {
    $sessionDir = Get-CurrentSessionDir
    if (-not $sessionDir -or -not (Test-Path $sessionDir)) {
        throw "No active OpenShim capture session found."
    }

    # Copy native artifacts before the base Stop creates its archive, then let
    # the base logger collect all legacy evidence in its established workflow.
    Copy-NativeTraceBeforeBaseStop -SessionDir $sessionDir
    Write-CaptureIdentity -SessionDir $sessionDir -Stage stop

    & $baseLogger -Action Stop

    # Rebuild once so SHA256SUMS.txt describes the final complete evidence
    # directory, including files collected by the base logger during Stop.
    Rebuild-ArchiveWithFinalHashes -SessionDir $sessionDir
    Write-Host "BZRNet native capture stopped: $sessionDir"
    Write-Host "Final archive: $sessionDir.zip"
}

function Mark-BzrNetCapture {
    if (-not $Message) { throw "-Message is required for Mark." }
    & $baseLogger -Action Mark -Message $Message
}

switch ($Action) {
    "Start" { Start-BzrNetCapture }
    "Stop" { Stop-BzrNetCapture }
    "Mark" { Mark-BzrNetCapture }
}
