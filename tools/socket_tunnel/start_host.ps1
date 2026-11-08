# Host a Steam-tunnel game on this PC: starts the dedicated server on
# 127.0.0.2 and a Steam bridge in front of it. Steam friends then use Join Game
# or an invite (docs/STEAM_TUNNEL.md, "Steam invite / Join Game"). You play on
# this PC with OpenShim Server = Custom, CustomServer = 127.0.0.2.
# Ctrl+C (or closing this window) stops both.
# -InGameBridge: start only the server; the game hosts the bridge itself
# (net.ini [OpenShimSocket] SteamTunnelBridge = auto, the default), so no
# socket_tunnel.exe. Steam build only.
param(
    [string]$ServerRepo = (Join-Path $PSScriptRoot '../../../Battlezone98Redux_DedicatedServer'),
    [string]$Tunnel = 'C:/BZRCoop/steam-tunnel',   # build.ps1 -Out folder
    [string]$Python = 'python',
    [string]$BindIp = '127.0.0.2',
    [switch]$InGameBridge
)
$ErrorActionPreference = 'Stop'
$serverPy = Join-Path $ServerRepo 'server.py'
$exe = Join-Path $Tunnel 'socket_tunnel.exe'
$required = if ($InGameBridge) { @($serverPy) } else { @($serverPy, $exe, (Join-Path $Tunnel 'steam_api.dll')) }
foreach ($p in $required) {
    if (-not (Test-Path -LiteralPath $p)) { throw "missing $p (see docs/STEAM_TUNNEL.md setup)" }
}
$state = Join-Path $Tunnel 'server_state.json'
$peers = Join-Path $Tunnel 'steam_tunnel_peers.txt'

$server = Start-Process -FilePath $Python -PassThru -NoNewWindow -ArgumentList @(
    "`"$serverPy`"", '--ws-host', $BindIp, '--udp-host', $BindIp, '--relay-host', $BindIp,
    '--relay-pair-ports', '--relay-pair-port-start', '1340', '--relay-pair-port-end', '1369',
    '--state-file', "`"$state`"")
$bridge = $null
try {
    Start-Sleep -Seconds 2
    if ($server.HasExited) { throw "server.py exited with code $($server.ExitCode)" }
    if ($InGameBridge) {
        Write-Host "server pid $($server.Id). In OpenShim set Server = Custom, CustomServer = $BindIp and start BZR from Steam (not GOG); the game hosts the Steam bridge itself while this server runs (net.ini SteamTunnelBridge=auto, SteamTunnelHost and TunnelUdpBridge empty)."
        $server.WaitForExit(); Write-Warning "server.py stopped (code $($server.ExitCode))"; return
    }

    # The bridge needs Steam running and signed in on this Windows session; it
    # announces itself to the game (same account) so friends see Join Game.
    $bridge = Start-Process -FilePath $exe -PassThru -NoNewWindow -WorkingDirectory $Tunnel -ArgumentList @(
        'bridge', '--steam', '--server', $BindIp, '--identity-map', "`"$peers`"")
    Write-Host "server pid $($server.Id), bridge pid $($bridge.Id). In OpenShim set Server = Custom, CustomServer = $BindIp."
    while (-not $server.HasExited -and -not $bridge.HasExited) { Start-Sleep -Seconds 1 }
    if ($server.HasExited) { Write-Warning "server.py stopped (code $($server.ExitCode))" }
    if ($bridge.HasExited) { Write-Warning "bridge stopped (code $($bridge.ExitCode))" }
} finally {
    if ($bridge -and -not $bridge.HasExited) { Stop-Process -Id $bridge.Id -ErrorAction SilentlyContinue }
    # /T: a python launcher (py.exe, Store alias) runs the real server as a child.
    if (-not $server.HasExited) { & taskkill.exe /T /F /PID $server.Id | Out-Null }
}
