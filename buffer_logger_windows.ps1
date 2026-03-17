[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("Start", "Stop", "Mark")]
    [string]$Action,
    [string]$GamePath = "",
    [int]$PayloadBytes = 32,
    [int]$RingRecords = 65536,
    [int]$SocketId = 0,
    [string]$PeerFilter = "",
    [string]$Message = ""
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSCommandPath
$stateRoot = Join-Path $repoRoot "test_bundles\openshim_buffer_state"
$currentFile = Join-Path $stateRoot "windows_current_session.txt"
New-Item -ItemType Directory -Path $stateRoot -Force | Out-Null

function Get-ResolvedGamePath {
    param([string]$Candidate)
    if ($Candidate -and (Test-Path $Candidate)) { return (Resolve-Path $Candidate).Path }

    $defaultPaths = @(
        "C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux",
        "C:\Program Files\Steam\steamapps\common\Battlezone 98 Redux",
        "$env:PROGRAMFILES\Steam\steamapps\common\Battlezone 98 Redux",
        "C:\GOG Games\Battlezone 98 Redux",
        "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux"
    )

    foreach ($path in $defaultPaths) {
        if (Test-Path $path) { return (Resolve-Path $path).Path }
    }

    return ""
}

function Get-GameExecutable {
    param([string]$ResolvedGamePath)

    $steamExe = Join-Path $ResolvedGamePath "battlezone98redux.exe"
    if (Test-Path $steamExe) { return $steamExe }

    $gogExe = Join-Path $ResolvedGamePath "BZR.exe"
    if (Test-Path $gogExe) { return $gogExe }

    return ""
}

function Collect-File {
    param(
        [string]$Source,
        [string]$DestinationDir,
        [string]$StatusFile
    )

    $base = Split-Path -Leaf $Source
    if (Test-Path $Source) {
        Copy-Item -Force $Source (Join-Path $DestinationDir $base)
        $bytes = (Get-Item $Source).Length
        Add-Content -Path $StatusFile -Value "found $base bytes=$bytes"
    } else {
        Add-Content -Path $StatusFile -Value "missing $base"
    }
}

function Build-EnvAssignments {
    param(
        [int]$PayloadBytesValue,
        [int]$RingRecordsValue,
        [int]$SocketIdValue,
        [string]$PeerFilterValue
    )

    $pairs = @(
        @{ Name = "BZ_BUFFER_LOG"; Value = "1" },
        @{ Name = "BZ_BUFFER_LOG_BYTES"; Value = "$PayloadBytesValue" },
        @{ Name = "BZ_BUFFER_LOG_RING"; Value = "$RingRecordsValue" }
    )

    if ($SocketIdValue -gt 0) {
        $pairs += @{ Name = "BZ_BUFFER_LOG_SOCKET"; Value = "$SocketIdValue" }
    }

    if ($PeerFilterValue) {
        $pairs += @{ Name = "BZ_BUFFER_LOG_PEER"; Value = $PeerFilterValue }
    }

    return $pairs
}

function Write-SteamLaunchOptions {
    param(
        [string]$OutFile,
        [int]$PayloadBytesValue,
        [int]$RingRecordsValue,
        [int]$SocketIdValue,
        [string]$PeerFilterValue
    )

    $parts = @()
    foreach ($pair in (Build-EnvAssignments -PayloadBytesValue $PayloadBytesValue -RingRecordsValue $RingRecordsValue -SocketIdValue $SocketIdValue -PeerFilterValue $PeerFilterValue)) {
        $parts += "set $($pair.Name)=$($pair.Value)"
    }

    $line = ($parts -join " && ") + " && %command%"
    @(
        "Steam launch options for this OpenShim buffer-capture session:",
        "",
        $line
    ) | Out-File -FilePath $OutFile -Encoding utf8
}

function Write-DirectLaunchScript {
    param(
        [string]$OutFile,
        [string]$GameExe,
        [int]$PayloadBytesValue,
        [int]$RingRecordsValue,
        [int]$SocketIdValue,
        [string]$PeerFilterValue
    )

    if (-not $GameExe) {
        @(
            "@echo off",
            "echo Game executable not found in the selected game folder.",
            "exit /b 1"
        ) | Out-File -FilePath $OutFile -Encoding ascii
        return
    }

    $gameDir = Split-Path -Parent $GameExe
    $lines = @("@echo off")
    foreach ($pair in (Build-EnvAssignments -PayloadBytesValue $PayloadBytesValue -RingRecordsValue $RingRecordsValue -SocketIdValue $SocketIdValue -PeerFilterValue $PeerFilterValue)) {
        $lines += "set $($pair.Name)=$($pair.Value)"
    }
    $lines += ('pushd "{0}"' -f $gameDir)
    $lines += ('start "" "{0}"' -f $GameExe)
    $lines += "popd"
    $lines | Out-File -FilePath $OutFile -Encoding ascii
}

function Get-CurrentSessionDir {
    if (-not (Test-Path $currentFile)) {
        return ""
    }

    $sessionDir = (Get-Content $currentFile -Raw).Trim()
    if (-not $sessionDir) {
        return ""
    }

    return $sessionDir
}

function Start-Session {
    $resolvedGamePath = Get-ResolvedGamePath -Candidate $GamePath
    if (-not $resolvedGamePath) {
        Write-Host "ERROR: game folder not found. Pass -GamePath explicitly." -ForegroundColor Red
        exit 1
    }

    $existing = Get-CurrentSessionDir
    if ($existing -and (Test-Path $existing)) {
        Write-Host "ERROR: an OpenShim capture session is already active: $existing" -ForegroundColor Red
        exit 1
    }

    $utcStamp = (Get-Date).ToUniversalTime().ToString("yyyyMMddTHHmmssZ")
    $sessionDir = Join-Path $repoRoot "test_bundles\openshim_buffer_windows_$env:COMPUTERNAME`_$utcStamp"
    New-Item -ItemType Directory -Path $sessionDir -Force | Out-Null

    $sessionDir | Out-File -FilePath $currentFile -Encoding utf8
    $resolvedGamePath | Out-File -FilePath (Join-Path $sessionDir "game_path.txt") -Encoding utf8
    $PayloadBytes | Out-File -FilePath (Join-Path $sessionDir "payload_bytes.txt") -Encoding utf8
    $RingRecords | Out-File -FilePath (Join-Path $sessionDir "ring_records.txt") -Encoding utf8
    $SocketId | Out-File -FilePath (Join-Path $sessionDir "socket_filter.txt") -Encoding utf8
    $PeerFilter | Out-File -FilePath (Join-Path $sessionDir "peer_filter.txt") -Encoding utf8
    (Get-Date).ToUniversalTime().ToString("o") | Out-File -FilePath (Join-Path $sessionDir "start_utc.txt") -Encoding utf8

    $gameExe = Get-GameExecutable -ResolvedGamePath $resolvedGamePath
    Write-SteamLaunchOptions -OutFile (Join-Path $sessionDir "steam_launch_options.txt") -PayloadBytesValue $PayloadBytes -RingRecordsValue $RingRecords -SocketIdValue $SocketId -PeerFilterValue $PeerFilter
    Write-DirectLaunchScript -OutFile (Join-Path $sessionDir "launch_with_buffer_log.cmd") -GameExe $gameExe -PayloadBytesValue $PayloadBytes -RingRecordsValue $RingRecords -SocketIdValue $SocketId -PeerFilterValue $PeerFilter

    @(
        "1. If you are using Steam, copy the launch line from steam_launch_options.txt.",
        "2. Otherwise run launch_with_buffer_log.cmd from this session folder.",
        "3. Reproduce the multiplayer issue.",
        "4. Optional marker: .\buffer_logger_windows.ps1 -Action Mark -Message ""loss spike during combat""",
        "5. When finished run: .\buffer_logger_windows.ps1 -Action Stop",
        "",
        "Files collected on stop:",
        "- openshim.log",
        "- BZLogger.txt",
        "- bz_buffer_log.bin",
        "- bz_buffer_log.meta.txt",
        "- net.ini",
        "- multi.ini"
    ) | Out-File -FilePath (Join-Path $sessionDir "README_NEXT_STEPS.txt") -Encoding utf8

    Write-Host "OpenShim buffer capture started."
    Write-Host "Session dir: $sessionDir"
    Write-Host "Steam launch options: $(Join-Path $sessionDir 'steam_launch_options.txt')"
    Write-Host "Direct launch helper: $(Join-Path $sessionDir 'launch_with_buffer_log.cmd')"
}

function Stop-Session {
    $sessionDir = Get-CurrentSessionDir
    if (-not $sessionDir -or -not (Test-Path $sessionDir)) {
        Write-Host "ERROR: no active OpenShim capture session found." -ForegroundColor Red
        Remove-Item -Force $currentFile -ErrorAction SilentlyContinue
        exit 1
    }

    $gamePathResolved = (Get-Content (Join-Path $sessionDir "game_path.txt") -Raw).Trim()
    $statusFile = Join-Path $sessionDir "collection_status.txt"
    Set-Content -Path $statusFile -Value ""

    Collect-File -Source (Join-Path $gamePathResolved "openshim.log") -DestinationDir $sessionDir -StatusFile $statusFile
    Collect-File -Source (Join-Path $gamePathResolved "BZLogger.txt") -DestinationDir $sessionDir -StatusFile $statusFile
    Collect-File -Source (Join-Path $gamePathResolved "bz_buffer_log.bin") -DestinationDir $sessionDir -StatusFile $statusFile
    Collect-File -Source (Join-Path $gamePathResolved "bz_buffer_log.meta.txt") -DestinationDir $sessionDir -StatusFile $statusFile
    Collect-File -Source (Join-Path $gamePathResolved "net.ini") -DestinationDir $sessionDir -StatusFile $statusFile
    Collect-File -Source (Join-Path $gamePathResolved "multi.ini") -DestinationDir $sessionDir -StatusFile $statusFile

    (Get-Date).ToUniversalTime().ToString("o") | Out-File -FilePath (Join-Path $sessionDir "stop_utc.txt") -Encoding utf8

    $zipPath = "$sessionDir.zip"
    if (Test-Path $zipPath) { Remove-Item -Force $zipPath }
    Compress-Archive -Path (Join-Path $sessionDir "*") -DestinationPath $zipPath

    Remove-Item -Force $currentFile -ErrorAction SilentlyContinue
    Write-Host "OpenShim buffer capture stopped."
    Write-Host "Bundle directory: $sessionDir"
    Write-Host "Archive created: $zipPath"
}

function Mark-Session {
    $sessionDir = Get-CurrentSessionDir
    if (-not $sessionDir -or -not (Test-Path $sessionDir)) {
        Write-Host "ERROR: no active OpenShim capture session found." -ForegroundColor Red
        exit 1
    }

    if (-not $Message) {
        Write-Host "ERROR: -Message is required for Action Mark." -ForegroundColor Red
        exit 1
    }

    $markerPath = Join-Path $sessionDir "markers.txt"
    Add-Content -Path $markerPath -Value ("{0}`t{1}" -f (Get-Date).ToUniversalTime().ToString("o"), $Message)
    Write-Host "Marker recorded in $markerPath"
}

switch ($Action) {
    "Start" { Start-Session }
    "Stop" { Stop-Session }
    "Mark" { Mark-Session }
}
