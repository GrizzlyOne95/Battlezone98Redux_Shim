# Steam tunnel: M1/M2 development preview

This branch implements an in-process OpenShim agent and a standalone Win32
bridge with two selectable transports: M1 plain UDP for trusted local tests,
and M2 Steam Networking Sockets P2P/SDR. Both INI keys ship empty. Native
gameplay and remote Steam acceptance remain pending; this is not a release.
See [M2 evidence](STEAM_TUNNEL_M2_RESULTS_20261028.md).

The game and Python server protocol stay unchanged. TCP 1337 becomes ordered,
reliable OPEN/DATA/CLOSE frames; UDP 1338-1369 retains individual datagrams,
destination ports and the original game socket's source-port identity. TCP 8080
is excluded. Each bridge peer receives a separate loopback source address
for both TCP and UDP, preserving the server's per-IP relay matching and bans.
Steam peers have persisted SteamID-to-127.0.1.N assignments. Plain UDP retains
ephemeral 127.0.0.N assignments, so IP bans alone cannot identify a returning
plain-UDP peer.

## Build and isolated test

Use VS C++ tools. Build scripts fetch public Valve headers at pinned revision
`d534c19aa760df3fb75fd20db13ba1932b8a5463` into ignored
`third_party/steam-networking/`; no SDK headers or DLLs are committed.
No Steam DLL or login is needed to run M1 or the offline tests:

```powershell
./tools/socket_tunnel/build.ps1
cmake -S tests -B build/tests -A Win32
cmake --build build/tests --config Release
ctest --test-dir build/tests -C Release -R "socket_tunnel|steam_tunnel" --output-on-failure
python tests/socket_tunnel_integration.py "$env:TEMP/bzr_socket_tunnel/socket_tunnel.exe" --out "$env:TEMP/bzr-tunnel-evidence"
python -B tests/socket_tunnel_server_smoke.py --server-repo ../Battlezone98Redux_DedicatedServer --exe "$env:TEMP/bzr_socket_tunnel/socket_tunnel.exe" --out "$env:TEMP/bzr-tunnel-server-evidence"
```

Socket tests need TCP 1337, UDP 1338-1369 and UDP 27030 free on loopback.
The first uses echo fixtures and a loss/duplicate proxy; the second runs the
unmodified sibling server with its existing protocol-test clients. All server
state and logs go to the requested output directory. Neither launches BZR or
edits either installed game. Tests stop their tunnel processes through temporary
stop files. Ctrl+C, `--seconds N` and `--stop-file PATH` also stop the CLI cleanly.

Build the complete OpenShim chain with `BZROpenShim.sln`, Release | Win32.
The agent compiles into `openshim.dll`; `ws2_32.dll` remains delay-loaded.
`Plugin_OpenShim.vcxproj` fetches the headers before compilation; CMake fetches
them for Win32 configuration tests. The portable policy/codec tests also run
on Linux without the SDK. The ordered-message runtime fixture is explicitly a
test backend, not evidence of Steam networking or authentication.

## Steam P2P/SDR setup (M2)

Use two Steam accounts owning appid 301650. On the bridge host, stage an isolated
tool directory using the **shipped Win32 DLL from your BZR Steam install**:

```powershell
./tools/socket_tunnel/build.ps1 -Out C:/BZRCoop/steam-tunnel -SteamDll '<your Steam BZR folder>/steam_api.dll'
```

This copies that DLL and writes `steam_appid.txt=301650` beside the standalone
tool. It never replaces the game's DLL. Output must be outside the source game
directory. Run from the isolated directory with Steam logged in:

```text
socket_tunnel.exe bridge --steam --server 127.0.0.1 --identity-map C:/BZRCoop/steam-tunnel/steam_tunnel_peers.txt
```

Start the unmodified Python server with bounded pair-relay ports 1340-1369.
For a separate server PC, its default bindings and bridge `--server 127.0.0.1`
are suitable. On a same-PC test where an agent also owns 127.0.0.1, bind the
server to 127.0.0.2 as shown below and use bridge `--server 127.0.0.2`.
The bridge logs its local SteamID64; use that as the client destination:

```ini
[OpenShimSocket]
SteamTunnelHost=76561198xxxxxxxxx
TunnelUdpBridge=
```

Replace the example with the bridge's complete numeric individual SteamID64.
The in-process client only borrows the loaded game's Steam API. It does not
call SteamAPI_Init, SteamAPI_RunCallbacks or SteamAPI_Shutdown; the game's
existing callback pump dispatches connection-status config callbacks. It waits
up to 30 seconds for the DLL and up to 30 seconds for initialized handles, then
blocks matchmaking if unavailable. No second client Steam process is started.

The standalone bridge owns its init/callback pump/shutdown. For a transport
diagnostic on a second account/machine, the same standalone executable also has
`agent --steam-host <bridge SteamID64>`; that diagnostic owns its own Steam
session and must not run alongside an in-process agent on the same local ports.
`steam-self-test` requests a real local SDK socket pair and checks both message
modes. It still needs successful Steam initialization and is not a remote P2P,
SDR or in-game acceptance test.

Only the exact pinned header interfaces `SteamNetworkingSockets012` and
`SteamNetworkingUtils004` are requested through SteamClient017's generic
accessor; no newer pointer is cast onto an older vtable, and there is no
SteamNetworking005 fallback. Steam appid and public individual identity are
checked before connecting. The client rejects a bridge with its own SteamID.
One authenticated, encrypted P2P connection is admitted per Steam peer, up to
eight peers. Duplicate live connections and unauthenticated/unencrypted states
are rejected. The bridge admits authenticated Steam identities; configure the
Python server's existing player-access controls for who may enter lobbies.
Steam authentication does not bind the claimed BZRNet lobby user ID to that
Steam identity, and the Python server still performs no Steam-ticket check.

Virtual port 1337 is scoped to this tunnel. ICE is disabled only on the tunnel
listener/connections, so they use SDR rather than direct P2P when connected.
No global networking callback or stock-game transport setting is changed.
Every ten seconds the tool logs SDR availability, auth, relayed flag, ping,
local/remote delivery quality, bytes/sec and pending/unacked bytes. Quality
values of -1 are unavailable estimates, not measured loss.

The default identity-map file is beside the bridge executable, or select it
with `--identity-map`. Its parent directory must already exist. Preserve this
file with server bans/state: mappings never expire or recycle. New identities
are saved with a flushed temporary file and atomic replacement **before** any
server socket is opened; reconnects and bridge restarts reuse the same IP.
A separate lock prevents simultaneous bridges using the file. Corruption,
write failure, address conflict or 254 assigned identities rejects service/new
admissions rather than silently reassigning bans. Source UDP ports can change
with a new session; the SteamID's source IP remains stable. The map contains
Steam IDs and should stay local.

## Same-PC setup

The agent exclusively binds 127.0.0.1 TCP 1337 and UDP 1338-1369. For a same-PC
test the Python server **must** bind a different loopback address, rather than
0.0.0.0, which conflicts with the agent:

```powershell
python server.py --ws-host 127.0.0.2 --udp-host 127.0.0.2 --relay-host 127.0.0.2 --relay-pair-ports --relay-pair-port-start 1340 --relay-pair-port-end 1369 --state-file C:/BZRCoop/tunnel-test/state.json
socket_tunnel.exe bridge --server 127.0.0.2
```

In an explicitly staged test game's `net.ini`:

```ini
[OpenShimSocket]
TunnelUdpBridge=127.0.0.1:27030
SteamTunnelHost=
```

Alternatively `socket_tunnel.exe agent --remote 127.0.0.1:27030` exercises the
same agent implementation without loading OpenShim. Do not run the standalone
agent and the in-process agent simultaneously: only one may own these ports.
The server's 8080 status endpoint stays local and never enters the tunnel.

## Trusted LAN setup

This M1 transport has **no encryption or authentication**. Use it only on
loopback or a trusted private test network; it is not an Internet service.
The bridge defaults to loopback. To listen on a chosen LAN address, explicitly
select it and allow the test client address(es):

```text
socket_tunnel.exe bridge --listen 192.168.1.44:27030 --allow 192.168.1.45,192.168.1.46 --server 127.0.0.1
```

Clients set `TunnelUdpBridge=192.168.1.44:27030`. The server can keep its normal
bindings on a separate host; enable its bounded pair-relay ports 1340-1369.
No router forwarding is needed for LAN tests. Existing firewall policy may block
LAN traffic; this implementation never changes firewall or router settings.
The allowlist bounds test access but is not authentication.

## Redirect, relay and failure behavior

When either tunnel key is nonempty, tunnel mode takes precedence over the
environment redirect, saved server selection and `/bzrserver=` host/port. The
existing matchmaking resolver points the official or launch host to
127.0.0.1:1337. Invalid/mutually selected modes, occupied local ports, a failed
worker or an unqualified relay flag produce DNS failure rather than fallback.
An unavailable bridge leaves the local agent listening, but it refuses TCP
streams until its transport handshake completes; stock reconnect can retry.

OpenShim uses the existing signature-qualified BZRNet route global to force
`/iprelay` behavior before returning a tunnel DNS result and whenever the route
preference is reapplied. It overrides a saved Direct preference. Failure to
qualify the existing resolve blocks matchmaking. Ticket withholding remains
active for the community endpoint. Literal-IP connections bypassing the game's
normal resolver seam are not socket-spliced; native `/bzrserver=` and reconnect
behavior still need qualification with the game.

Community identity keys use the logical Steam bridge identity rather than
127.0.0.1, so different bridge accounts receive different keys. Plain UDP uses
the remote bridge IP/transport port. These logical `.openshim.invalid` names
are only HMAC namespaces and are never resolved. Moving an existing plain-UDP
test server to this version changes its former loopback-derived key; use the
server's existing approval controls to reapprove that test identity if needed.

The worker owns every socket and its own WSAStartup reference. Shutdown signals
it and joins it before releasing state. Peer heartbeat timeout is 15 seconds;
the plain-UDP reliable-message timeout is 10 seconds, with 100 ms retry intervals. Losing a
peer closes its streams and UDP sockets; a restarted agent gets a new session.
Bridge restart during an active agent session recovers after that timeout.
UDP source mappings remain stable for the session, including long lobby idles;
they are released with the peer rather than aged out independently.
The preview caps sessions at eight, TCP streams at 16 per session, game UDP
source sockets at 64 per session, reliable queues at 256 KiB/512 frames per
direction, and datagrams at 60,000 bytes. Larger datagrams are dropped. Local
TCP backpressure stops reads while queues are full. Plain UDP uses stop-and-wait
and has no encryption or congestion controller. Steam uses native reliable
messages for OPEN/DATA/CLOSE/RESET, with unreliable messages for UDP/PING; no
plain-UDP ACK/retransmission runs on the Steam path. Stream frames are retained
until SDK submission succeeds, including when its send queue is full, and a
blocked receive retains one bounded frame until the local TCP socket drains.
The SDK send budget is separately capped at 256 KiB per connection. Unreliable
datagrams are dropped under pressure rather than retransmitted. A local SDK
submission means queued, not delivered. Full-size UDP frames can fragment.

Steam reconnects after a closed/failed connection with a five-second delay.
Old streams/sessions are discarded; the game must reconnect its WebSocket.
Callback code remains pinned until process exit so an already queued Steam
callback cannot call unmapped code. Shutdown disconnects this tunnel and stops
its callback queue; the borrowed game's Steam session remains owned by the game.

## Acceptance and remaining work

See [M1 results](STEAM_TUNNEL_M1_RESULTS_20261028.md) for measured evidence.
Socket and synthetic lobby tests do **not** complete M1: the redirected game
must log in, list, create, join and play a five-minute match through the bridge.
Direct-LAN versus tunnel-LAN performance is also pending.

M2 is implemented but unaccepted. The first standalone live attempt failed
SteamAPI_Init; a 2026-10-29 rerun of the same staged binary passed
`steam-self-test` and the bridge reached SDR Current, so that failure did not
reproduce. Remote acceptance follows the
[live test guide](STEAM_TUNNEL_LIVE_TEST_GUIDE.md).

Still required: two owning Steam accounts/PCs, ten-minute match and clean exits,
SDR status/ping/quality, host-account/bridge coexistence, forced-relay quality,
native bridge loss/recovery, 3-4 players and soak/loss testing. Rich presence, friends-list Join Game,
GOG/Galaxy transport, installers/UI and Python server ticket verification are
out of scope. Windows GOG/Steam native integration and Proton/Wine are unverified;
M1's independent socket tool is store-neutral, while SDR mode is Steam-only.

API references: [Valve Sockets documentation](https://partner.steamgames.com/doc/api/ISteamNetworkingSockets),
[public pinned header source](https://github.com/ValveSoftware/GameNetworkingSockets/tree/d534c19aa760df3fb75fd20db13ba1932b8a5463/include/steam).
