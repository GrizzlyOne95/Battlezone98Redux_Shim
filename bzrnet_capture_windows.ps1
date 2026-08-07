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
    if ($AllUdp) { $lines.Add("set BZ_BZRNET_TRACE_ALL_UDP=1") }
    return $lines
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
        "- all UDP semantic wire highlights: $([int][bool]$AllUdp)",
        "- trace queue records: $TraceQueueRecords",
        "- relay capture: $([int][bool]$RelayCapture)",
        "",
        "Expected additional game log files:",
        "- logs\bzrnet_session.json",
        "- logs\bzrnet_trace.jsonl",
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

    @(
        "BZRNet native capture session prepared.",
        "Session: $sessionDir",
        "Steam: use the updated steam_launch_options.txt line.",
        "Direct/GOG: use the updated launch_with_buffer_log.cmd.",
        $(if ($RelayCapture) { "Relay profile includes /iprelay and the 2048-byte binary UDP capture." } else { "BZRNet tracing is enabled without forcing relay." })
    ) | ForEach-Object { Write-Host $_ }
}

function Stop-BzrNetCapture {
    $sessionDir = Get-CurrentSessionDir
    if (-not $sessionDir -or -not (Test-Path $sessionDir)) {
        throw "No active OpenShim capture session found."
    }

    # The base Stop command zips every file already present in the session, so
    # copy the new native artifacts into it before delegating.
    Copy-NativeTraceBeforeBaseStop -SessionDir $sessionDir

    & $baseLogger -Action Stop

    # The base Stop command collects the legacy logs immediately before its ZIP
    # is created. Rebuild that archive once so SHA256SUMS.txt covers the final
    # complete evidence directory, including the newly collected legacy files.
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
