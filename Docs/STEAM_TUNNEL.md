# Steam tunnel: M1 development preview

This branch implements the **plain-UDP milestone**, including an in-process
OpenShim agent and a standalone Win32 bridge. It does not yet carry traffic over
Steam. Both INI keys ship empty. Setting `SteamTunnelHost` blocks matchmaking in
this M1 build; it never selects the plain transport implicitly.

The game and Python server protocol stay unchanged. TCP 1337 becomes ordered,
reliable OPEN/DATA/CLOSE frames; UDP 1338-1369 retains individual datagrams,
destination ports and the original game socket's source-port identity. TCP 8080
is excluded. Each bridge session receives a separate 127.0.0.N source address
for both TCP and UDP, preserving the server's per-IP relay matching and bans.
These are ephemeral session identities; persistent SteamID-to-IP assignment is
an M2 requirement, so IP bans alone do not identify a returning plain-UDP peer.

## Build and isolated test

Use VS C++ tools, with no Steam SDK or DLL required for M1:

```powershell
./tools/socket_tunnel/build.ps1
cmake -S tests -B build/tests -A Win32
cmake --build build/tests --config Release
ctest --test-dir build/tests -C Release -R socket_tunnel_protocol --output-on-failure
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

## Same-PC setup

The agent exclusively binds 127.0.0.1 TCP 1337 and UDP 1338-1369. For a same-PC
test the Python server **must** bind a different loopback address, rather than
0.0.0.0, which conflicts with the agent:

```powershell
python ../Battlezone98Redux_DedicatedServer/server.py --ws-host 127.0.0.2 --udp-host 127.0.0.2 --relay-host 127.0.0.2 --relay-pair-ports --relay-pair-port-start 1340 --relay-pair-port-end 1369 --state-file C:/BZRCoop/tunnel-test/state.json
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

The worker owns every socket and its own WSAStartup reference. Shutdown signals
it and joins it before releasing state. Peer heartbeat timeout is 15 seconds;
reliable-message timeout is 10 seconds, with 100 ms retry intervals. Losing a
peer closes its streams and UDP sockets; a restarted agent gets a new session.
Bridge restart during an active agent session recovers after that timeout.
UDP source mappings remain stable for the session, including long lobby idles;
they are released with the peer rather than aged out independently.
The preview caps sessions at eight, TCP streams at 16 per session, game UDP
source sockets at 64 per session, reliable queues at 256 KiB/512 frames per
direction, and datagrams at 60,000 bytes. Larger datagrams are dropped. Local
TCP backpressure stops reads while queues are full. There is no custom byte
compression, packet encryption or congestion controller. Stop-and-wait limits
TCP throughput over high RTT paths; Steam's reliable transport replaces this
adapter in M2. Full-size UDP frames can fragment at LAN MTUs.

## Acceptance and remaining work

See [M1 results](STEAM_TUNNEL_M1_RESULTS_20261028.md) for measured evidence.
Socket and synthetic lobby tests do **not** complete M1: the redirected game
must log in, list, create, join and play a five-minute match through the bridge.
Direct-LAN versus tunnel-LAN performance is also pending.

M2 must resolve the exact current networking interfaces through the shipped
Steam DLL's generic accessor, reusing the game's initialization on the client.
The bridge must be Win32/appid 301650, with one Sockets P2P connection per
Steam peer, reliable stream frames, unreliable datagrams and status config
callbacks pumped by SteamAPI_RunCallbacks. Never cast an older interface to a
newer SDK vtable or fall back to SteamNetworking005. Fetch pinned headers at
build time as the probe does; do not vendor headers or Steam DLLs.

Still required: two owning Steam accounts/PCs, ten-minute match and clean exits,
SDR status/ping/quality, host-account/bridge coexistence, forced-relay quality,
bridge loss/recovery, 3-4 players and soak/loss testing. SteamID source mapping
must remain stable across reconnects. Rich presence, friends-list Join Game,
GOG/Galaxy transport, installers/UI and Python server ticket verification are
out of scope. Windows GOG/Steam native integration and Proton/Wine are unverified;
M1's independent socket tool is store-neutral, while eventual SDR mode is Steam-only.

## Review qualifications (2026-10-29)

`Ready()` confirms only that the worker bound its local ports. The resolver
waits up to one second for that startup; it does not probe bridge reachability.
The separate relay-flag check verifies the game's forced-relay setting, not a
remote service. If the bridge is down, accepted local TCP connections close
until the handshake completes; the stock client must reconnect.

Winsock hooks patch the import tables of battlezone98redux.exe, Galaxy.dll,
GalaxyPeer.dll and steam_api.dll. They do not patch ws2_32's exports or
openshim.dll's import/delay-import table. The in-process tunnel calls Winsock
from openshim.dll, so its worker sockets bypass the optimizer's reorder,
duplication and socket-tuning hooks. The standalone tool is a separate process.
Installing observation hooks with the optimizer disabled does not change this
module boundary. Native lobby/gameplay qualification is still required.

M1 stop-and-wait sends at most one 1-KiB reliable frame per round trip, about
20 KiB/s at 50 ms RTT before overhead, and a frame unacknowledged for ten seconds
kills the peer. The measured 5 MB/s is loopback-only. M1 is a trusted local test
milestone; it is not accepted for remote play. M2 replaces this ACK/retry path
with Steam's reliable messages and congestion handling.

The local Python server conflicts with the agent if both bind 127.0.0.1:1337
or UDP 1338-1369; 0.0.0.0 also conflicts. Bind the server to 127.0.0.2 for
same-PC tests. Use the sibling Battlezone98Redux_DedicatedServer/server.py,
which implements --relay-pair-ports and --state-file; the older emulator in
reverse_engineering/bzrnet_server/server.py does not implement those flags.
