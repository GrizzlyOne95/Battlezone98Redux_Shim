[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("Start", "Stop", "Mark")]
    [string]$Action,
    [string]$GamePath = "",
    [string]$PingTarget = "1.1.1.1",
    [string]$PeerPingTarget = "",
    [string]$Message = ""
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSCommandPath
$stateRoot = Join-Path $repoRoot "test_bundles\openshim_diag_state"
$currentFile = Join-Path $stateRoot "windows_current_session.txt"
New-Item -ItemType Directory -Path $stateRoot -Force | Out-Null

function Get-ResolvedGamePath {
    param([string]$Candidate)

    if ($Candidate -and (Test-Path $Candidate)) {
        return (Resolve-Path $Candidate).Path
    }

    $defaultPaths = @(
        "C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux",
        "C:\Program Files\Steam\steamapps\common\Battlezone 98 Redux",
        "$env:PROGRAMFILES\Steam\steamapps\common\Battlezone 98 Redux",
        "C:\GOG Games\Battlezone 98 Redux",
        "C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux"
    )

    foreach ($path in $defaultPaths) {
        if (Test-Path $path) {
            return (Resolve-Path $path).Path
        }
    }

    return ""
}

function Stop-PidIfAlive {
    param([int]$PidToStop)

    if ($PidToStop -le 0) {
        return
    }

    try {
        $process = Get-Process -Id $PidToStop -ErrorAction SilentlyContinue
        if ($process) {
            Stop-Process -Id $PidToStop -Force -ErrorAction SilentlyContinue
        }
    } catch {
    }
}

function Test-PublicIPv4 {
    param([string]$Ip)

    if (-not $Ip -or $Ip -notmatch '^(\d{1,3}\.){3}\d{1,3}$') {
        return $false
    }

    if (
        $Ip -match '^(0|10|127)\.' -or
        $Ip -match '^169\.254\.' -or
        $Ip -match '^192\.168\.' -or
        $Ip -match '^172\.(1[6-9]|2\d|3[0-1])\.' -or
        $Ip -match '^100\.(6[4-9]|[7-9]\d|1[01]\d|12[0-7])\.' -or
        $Ip -match '^(22[4-9]|23\d)\.'
    ) {
        return $false
    }

    return $true
}

function Write-PeerCandidatesFromSocketLog {
    param(
        [string]$SocketLogPath,
        [string]$BaselineTarget,
        [string]$OutputPath
    )

    if (-not (Test-Path $SocketLogPath)) {
        Set-Content -Path $OutputPath -Value ""
        return
    }

    $matches = Select-String -Path $SocketLogPath -Pattern '(\d{1,3}(?:\.\d{1,3}){3}):(\d+|\*)' -AllMatches |
        ForEach-Object { $_.Matches } |
        ForEach-Object { $_.Groups[1].Value } |
        Where-Object { $_ -ne $BaselineTarget } |
        Where-Object { Test-PublicIPv4 $_ }

    $matches |
        Group-Object |
        Sort-Object Count -Descending |
        ForEach-Object { '{0} {1}' -f $_.Count, $_.Name } |
        Out-File -FilePath $OutputPath -Encoding utf8
}

function Capture-RouteSnapshot {
    param(
        [string]$Target,
        [string]$OutFile
    )

    if (-not $Target) {
        return
    }

    tracert -d $Target | Out-File -FilePath $OutFile -Encoding utf8
}

function Capture-NoiseProfile {
    param(
        [string]$DefaultAdapterName,
        [string]$OutFile
    )

    $proxyInfo = (netsh winhttp show proxy) -join "`n"
    $vpnAdapters = @(Get-NetAdapter -ErrorAction SilentlyContinue | Where-Object {
        $_.Status -eq "Up" -and ($_.Name -match "vpn|tun|tap|wireguard" -or $_.InterfaceDescription -match "vpn|tun|tap|wireguard")
    })

    @(
        "proxy_winhttp_set=$([int](-not ($proxyInfo -match 'Direct access \(no proxy server\)')))",
        "vpn_adapter_up_count=$($vpnAdapters.Count)",
        "default_adapter=$DefaultAdapterName"
    ) | Out-File -FilePath $OutFile -Encoding utf8

    if ($proxyInfo) {
        $proxyInfo | Out-File -FilePath ($OutFile -replace '\.txt$', '_proxy.txt') -Encoding utf8
    }
}

function Capture-RateSample {
    param(
        [string]$AdapterName,
        [string]$OutFile
    )

    if (-not $AdapterName -or $AdapterName -eq "unknown") {
        return
    }

    $stat1 = Get-NetAdapterStatistics -Name $AdapterName -ErrorAction SilentlyContinue
    if (-not $stat1) {
        return
    }

    Start-Sleep -Seconds 5
    $stat2 = Get-NetAdapterStatistics -Name $AdapterName -ErrorAction SilentlyContinue
    if (-not $stat2) {
        return
    }

    @(
        "window_seconds=5",
        "adapter=$AdapterName",
        "rx_bytes_start=$($stat1.ReceivedBytes)",
        "rx_bytes_end=$($stat2.ReceivedBytes)",
        "tx_bytes_start=$($stat1.SentBytes)",
        "tx_bytes_end=$($stat2.SentBytes)",
        "rx_bytes_per_sec=$([int](($stat2.ReceivedBytes - $stat1.ReceivedBytes) / 5))",
        "tx_bytes_per_sec=$([int](($stat2.SentBytes - $stat1.SentBytes) / 5))"
    ) | Out-File -FilePath $OutFile -Encoding utf8
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

function Start-Diagnostics {
    $resolvedGamePath = Get-ResolvedGamePath -Candidate $GamePath
    if (-not $resolvedGamePath) {
        Write-Host "ERROR: game folder not found. Pass -GamePath explicitly." -ForegroundColor Red
        exit 1
    }

    if (Test-Path $currentFile) {
        $existing = (Get-Content $currentFile -Raw).Trim()
        if ($existing -and (Test-Path $existing)) {
            Write-Host "ERROR: OpenShim deep diagnostics already running: $existing" -ForegroundColor Red
            Write-Host "Run .\tester_diag_windows.ps1 -Action Stop first." -ForegroundColor Yellow
            exit 1
        }

        Remove-Item -Force $currentFile -ErrorAction SilentlyContinue
    }

    $defaultRoute = Get-NetRoute -DestinationPrefix "0.0.0.0/0" -ErrorAction SilentlyContinue |
        Sort-Object -Property RouteMetric, InterfaceMetric |
        Select-Object -First 1
    $defaultIfIndex = if ($defaultRoute) { [int]$defaultRoute.InterfaceIndex } else { 0 }
    $defaultAdapter = if ($defaultIfIndex -gt 0) { Get-NetAdapter -InterfaceIndex $defaultIfIndex -ErrorAction SilentlyContinue } else { $null }
    $defaultAdapterName = if ($defaultAdapter) { $defaultAdapter.Name } else { "unknown" }

    $utcStamp = (Get-Date).ToUniversalTime().ToString("yyyyMMddTHHmmssZ")
    $startIso = (Get-Date).ToUniversalTime().ToString("o")
    $hostName = $env:COMPUTERNAME
    $sessionDir = Join-Path $repoRoot "test_bundles\openshim_diag_windows_${hostName}_${utcStamp}"
    New-Item -ItemType Directory -Path $sessionDir -Force | Out-Null

    try {
        $sessionDir | Out-File -FilePath $currentFile -Encoding utf8
        $resolvedGamePath | Out-File -FilePath (Join-Path $sessionDir "game_path.txt") -Encoding utf8
        $PingTarget | Out-File -FilePath (Join-Path $sessionDir "ping_target.txt") -Encoding utf8
        $PeerPingTarget | Out-File -FilePath (Join-Path $sessionDir "peer_ping_target.txt") -Encoding utf8
        $startIso | Out-File -FilePath (Join-Path $sessionDir "start_utc.txt") -Encoding utf8

        @(
            "start_utc=$startIso",
            "host_name=$hostName",
            "user_name=$env:USERNAME",
            "game_path=$resolvedGamePath",
            "ping_target=$PingTarget",
            "peer_ping_target=$PeerPingTarget",
            "peer_detection_mode=$(if ($PeerPingTarget) { 'explicit' } else { 'auto' })",
            "default_adapter=$defaultAdapterName",
            "powershell_version=$($PSVersionTable.PSVersion)",
            "os_caption=$((Get-CimInstance Win32_OperatingSystem).Caption)",
            "os_version=$((Get-CimInstance Win32_OperatingSystem).Version)"
        ) | Out-File -FilePath (Join-Path $sessionDir "session_info.txt") -Encoding utf8

        ipconfig /all | Out-File -FilePath (Join-Path $sessionDir "ipconfig_start.txt") -Encoding utf8
        route print | Out-File -FilePath (Join-Path $sessionDir "route_start.txt") -Encoding utf8
        Capture-RouteSnapshot -Target $PingTarget -OutFile (Join-Path $sessionDir "route_baseline_start.txt")
        if ($PeerPingTarget) {
            Capture-RouteSnapshot -Target $PeerPingTarget -OutFile (Join-Path $sessionDir "route_peer_start.txt")
        }

        Get-NetAdapter -ErrorAction SilentlyContinue |
            Select-Object Name, InterfaceDescription, Status, LinkSpeed, MediaType, MacAddress |
            Format-Table -AutoSize | Out-File -FilePath (Join-Path $sessionDir "adapter_overview_start.txt") -Encoding utf8

        Get-NetAdapterStatistics -ErrorAction SilentlyContinue |
            Select-Object Name, ReceivedBytes, SentBytes, ReceivedUnicastPackets, SentUnicastPackets, ReceivedDiscardedPackets, OutboundDiscardedPackets, ReceivedPacketErrors, OutboundPacketErrors |
            Format-Table -AutoSize | Out-File -FilePath (Join-Path $sessionDir "adapter_stats_start.txt") -Encoding utf8

        Capture-NoiseProfile -DefaultAdapterName $defaultAdapterName -OutFile (Join-Path $sessionDir "noise_profile_start.txt")
        Capture-RateSample -AdapterName $defaultAdapterName -OutFile (Join-Path $sessionDir "net_rate_start.txt")

        if ($defaultAdapter -and $defaultAdapter.MediaType -match "Native 802\.11") {
            netsh wlan show interfaces | Out-File -FilePath (Join-Path $sessionDir "wifi_info_start.txt") -Encoding utf8
        }

        $pingProc = Start-Process -FilePath "ping.exe" -ArgumentList @($PingTarget, "-t") -RedirectStandardOutput (Join-Path $sessionDir "ping_timeline.log") -WindowStyle Hidden -PassThru
        $peerPingProc = $null
        if ($PeerPingTarget) {
            $peerPingProc = Start-Process -FilePath "ping.exe" -ArgumentList @($PeerPingTarget, "-t") -RedirectStandardOutput (Join-Path $sessionDir "peer_ping_timeline.log") -WindowStyle Hidden -PassThru
        }

        $netstatScript = @"
while (`$true) {
  Add-Content -Path '$($sessionDir -replace "'", "''")\\socket_timeline.log' -Value ('===== ' + [DateTime]::UtcNow.ToString('o') + ' =====')
  netstat -s | Add-Content -Path '$($sessionDir -replace "'", "''")\\socket_timeline.log'
  netstat -ano | Add-Content -Path '$($sessionDir -replace "'", "''")\\socket_timeline.log'
  netstat -e | Add-Content -Path '$($sessionDir -replace "'", "''")\\socket_timeline.log'
  Add-Content -Path '$($sessionDir -replace "'", "''")\\socket_timeline.log' -Value ''
  Start-Sleep -Seconds 5
}
"@
        $encoded = [Convert]::ToBase64String([Text.Encoding]::Unicode.GetBytes($netstatScript))
        $netstatProc = Start-Process -FilePath "powershell.exe" -ArgumentList @("-NoProfile", "-EncodedCommand", $encoded) -WindowStyle Hidden -PassThru

        try {
            netsh trace start capture=yes report=yes persistent=no maxsize=256 tracefile="$(Join-Path $sessionDir 'nettrace.etl')" | Out-Null
            "netsh_trace=started" | Out-File -FilePath (Join-Path $sessionDir "netsh_trace_status.txt") -Encoding utf8
        } catch {
            "netsh_trace=failed_or_not_admin" | Out-File -FilePath (Join-Path $sessionDir "netsh_trace_status.txt") -Encoding utf8
        }

        @(
            "1. Reproduce the bad session.",
            "2. Optional marker: .\tester_diag_windows.ps1 -Action Mark -Message ""relay fallback after join""",
            "3. Optional packet capture: start .\buffer_logger_windows.ps1 separately if you need recv-path binary logs.",
            "4. When finished run: .\tester_diag_windows.ps1 -Action Stop"
        ) | Out-File -FilePath (Join-Path $sessionDir "README_NEXT_STEPS.txt") -Encoding utf8

        @{
            sessionDir = $sessionDir
            startUtc = $startIso
            gamePath = $resolvedGamePath
            pingTarget = $PingTarget
            peerPingTarget = $PeerPingTarget
            defaultAdapterName = $defaultAdapterName
            pingPid = $pingProc.Id
            peerPingPid = if ($peerPingProc) { $peerPingProc.Id } else { 0 }
            netstatPid = $netstatProc.Id
        } | ConvertTo-Json -Depth 4 | Out-File -FilePath (Join-Path $sessionDir "state.json") -Encoding utf8

        Write-Host "OpenShim deep diagnostics started."
        Write-Host "Session dir: $sessionDir"
        Write-Host "Baseline ping target: $PingTarget"
        Write-Host "Peer ping target: $(if ($PeerPingTarget) { $PeerPingTarget } else { 'auto-detect' })"
        Write-Host ""
        Write-Host "Next:"
        Write-Host "1. Reproduce the session problem."
        Write-Host "2. Optional marker: .\tester_diag_windows.ps1 -Action Mark -Message ""relay fallback after join"""
        Write-Host "3. Run .\tester_diag_windows.ps1 -Action Stop"
    } catch {
        Write-Host "ERROR: failed to start diagnostics: $($_.Exception.Message)" -ForegroundColor Red
        if (Test-Path $currentFile) {
            Remove-Item -Force $currentFile -ErrorAction SilentlyContinue
        }
        if ($sessionDir -and (Test-Path $sessionDir)) {
            Remove-Item -Recurse -Force $sessionDir -ErrorAction SilentlyContinue
        }
        exit 1
    }
}

function Stop-Diagnostics {
    if (-not (Test-Path $currentFile)) {
        Write-Host "ERROR: no active OpenShim deep diagnostics session found." -ForegroundColor Red
        Write-Host "Run .\tester_diag_windows.ps1 -Action Start first." -ForegroundColor Yellow
        exit 1
    }

    $sessionDir = (Get-Content $currentFile -Raw).Trim()
    if (-not $sessionDir -or -not (Test-Path $sessionDir)) {
        Write-Host "ERROR: session directory missing: $sessionDir" -ForegroundColor Red
        Remove-Item -Force $currentFile -ErrorAction SilentlyContinue
        exit 1
    }

    $statePath = Join-Path $sessionDir "state.json"
    if (-not (Test-Path $statePath)) {
        Write-Host "ERROR: session state missing: $statePath" -ForegroundColor Red
        Remove-Item -Force $currentFile -ErrorAction SilentlyContinue
        exit 1
    }

    $state = Get-Content $statePath -Raw | ConvertFrom-Json
    Stop-PidIfAlive -PidToStop ([int]$state.pingPid)
    Stop-PidIfAlive -PidToStop ([int]$state.peerPingPid)
    Stop-PidIfAlive -PidToStop ([int]$state.netstatPid)

    try {
        netsh trace stop | Out-File -FilePath (Join-Path $sessionDir "netsh_trace_stop.txt") -Encoding utf8
    } catch {
        "netsh_trace_stop_failed_or_not_running" | Out-File -FilePath (Join-Path $sessionDir "netsh_trace_stop.txt") -Encoding utf8
    }

    ipconfig /all | Out-File -FilePath (Join-Path $sessionDir "ipconfig_end.txt") -Encoding utf8
    route print | Out-File -FilePath (Join-Path $sessionDir "route_end.txt") -Encoding utf8
    Write-PeerCandidatesFromSocketLog -SocketLogPath (Join-Path $sessionDir "socket_timeline.log") -BaselineTarget "$($state.pingTarget)" -OutputPath (Join-Path $sessionDir "peer_candidates.txt")

    if (-not $state.peerPingTarget -and (Test-Path (Join-Path $sessionDir "peer_candidates.txt"))) {
        $firstCandidate = Get-Content (Join-Path $sessionDir "peer_candidates.txt") | Select-Object -First 1
        if ($firstCandidate) {
            $parts = $firstCandidate -split '\s+'
            if ($parts.Length -ge 2) {
                $state.peerPingTarget = $parts[1]
                $state | ConvertTo-Json -Depth 4 | Out-File -FilePath $statePath -Encoding utf8
                $state.peerPingTarget | Out-File -FilePath (Join-Path $sessionDir "inferred_peer_target.txt") -Encoding utf8
            }
        }
    }

    if ($state.pingTarget) {
        Capture-RouteSnapshot -Target "$($state.pingTarget)" -OutFile (Join-Path $sessionDir "route_baseline_end.txt")
    }
    if ($state.peerPingTarget) {
        Capture-RouteSnapshot -Target "$($state.peerPingTarget)" -OutFile (Join-Path $sessionDir "route_peer_end.txt")
    }

    Get-NetAdapter -ErrorAction SilentlyContinue |
        Select-Object Name, InterfaceDescription, Status, LinkSpeed, MediaType, MacAddress |
        Format-Table -AutoSize | Out-File -FilePath (Join-Path $sessionDir "adapter_overview_end.txt") -Encoding utf8

    Get-NetAdapterStatistics -ErrorAction SilentlyContinue |
        Select-Object Name, ReceivedBytes, SentBytes, ReceivedUnicastPackets, SentUnicastPackets, ReceivedDiscardedPackets, OutboundDiscardedPackets, ReceivedPacketErrors, OutboundPacketErrors |
        Format-Table -AutoSize | Out-File -FilePath (Join-Path $sessionDir "adapter_stats_end.txt") -Encoding utf8

    Capture-NoiseProfile -DefaultAdapterName "$($state.defaultAdapterName)" -OutFile (Join-Path $sessionDir "noise_profile_end.txt")
    Capture-RateSample -AdapterName "$($state.defaultAdapterName)" -OutFile (Join-Path $sessionDir "net_rate_end.txt")

    $gamePathResolved = "$($state.gamePath)"
    $statusFile = Join-Path $sessionDir "collection_status.txt"
    Set-Content -Path $statusFile -Value ""

    if ($gamePathResolved -and (Test-Path $gamePathResolved)) {
        Collect-File -Source (Join-Path $gamePathResolved "openshim.log") -DestinationDir $sessionDir -StatusFile $statusFile
        Collect-File -Source (Join-Path $gamePathResolved "BZLogger.txt") -DestinationDir $sessionDir -StatusFile $statusFile
        Collect-File -Source (Join-Path $gamePathResolved "bz_buffer_log.bin") -DestinationDir $sessionDir -StatusFile $statusFile
        Collect-File -Source (Join-Path $gamePathResolved "bz_buffer_log.meta.txt") -DestinationDir $sessionDir -StatusFile $statusFile
        Collect-File -Source (Join-Path $gamePathResolved "net.ini") -DestinationDir $sessionDir -StatusFile $statusFile
        Collect-File -Source (Join-Path $gamePathResolved "multi.ini") -DestinationDir $sessionDir -StatusFile $statusFile
    }

    $verifyOut = Join-Path $sessionDir "verify_output.txt"
    try {
        & (Join-Path $repoRoot "verify_windows.ps1") -GamePath $gamePathResolved *>&1 | Tee-Object -FilePath $verifyOut | Out-Null
    } catch {
        $_ | Out-File -FilePath $verifyOut -Encoding utf8
    }

    (Get-Date).ToUniversalTime().ToString("o") | Out-File -FilePath (Join-Path $sessionDir "stop_utc.txt") -Encoding utf8

    $zipPath = "$sessionDir.zip"
    if (Test-Path $zipPath) {
        Remove-Item -Force $zipPath
    }

    Compress-Archive -Path (Join-Path $sessionDir "*") -DestinationPath $zipPath
    Remove-Item -Force $currentFile -ErrorAction SilentlyContinue

    Write-Host "OpenShim deep diagnostics stopped."
    Write-Host "Bundle directory: $sessionDir"
    Write-Host "Archive created: $zipPath"
}

function Mark-Diagnostics {
    if (-not (Test-Path $currentFile)) {
        Write-Host "ERROR: no active OpenShim deep diagnostics session found." -ForegroundColor Red
        Write-Host "Run .\tester_diag_windows.ps1 -Action Start first." -ForegroundColor Yellow
        exit 1
    }

    if (-not $Message) {
        Write-Host "ERROR: -Message is required for Action Mark." -ForegroundColor Red
        exit 1
    }

    $sessionDir = (Get-Content $currentFile -Raw).Trim()
    if (-not $sessionDir -or -not (Test-Path $sessionDir)) {
        Write-Host "ERROR: session directory missing: $sessionDir" -ForegroundColor Red
        exit 1
    }

    $markerPath = Join-Path $sessionDir "tester_markers.log"
    Add-Content -Path $markerPath -Value ("{0} | {1}" -f (Get-Date).ToUniversalTime().ToString("o"), $Message)
    Write-Host "Marker recorded in $markerPath"
}

switch ($Action) {
    "Start" { Start-Diagnostics }
    "Stop" { Stop-Diagnostics }
    "Mark" { Mark-Diagnostics }
}
