# Steam tunnel M2 implementation — 2026-10-28

`agent/steam-tunnel-m2` is stacked on M1 draft #645 at
`b5d1055fc4072e39c465fee742dc4e81b0469f8b`. The M1 PR's three CI jobs were
green before branching. Open LAN drafts #642/#644 were inspected; this change
retains the independent higher-priority tunnel redirect guard.

## Result and validation boundary

The M2 transport is **implemented, not accepted**. It compiles against the
public Valve headers used by the proven #643 probe. It requests exactly
Sockets012/Utils004 through the shipped DLL's SteamClient017 generic accessor.
It implements client ConnectP2P, bridge CreateListenSocketP2P, native reliable
stream frames, unreliable datagrams, per-connection status callbacks, reconnects,
bounded queues, SDR diagnostics and persisted source identity.

The standalone live attempt returned **SteamAPI_Init failed** in the current
Steam session before acquiring any networking interface or connection. The
cause was not established. The earlier probe result is retained as earlier
evidence, not silently reclassified as a successful current M2 test. No current
SDR ping/quality, remote throughput or P2P connection was measured. A two-account
ten-minute match and clean exits remain required.

No game was launched or installed file replaced. A copy of the shipped DLL was
staged only in `%TEMP%/bzr_socket_tunnel_m2/`. The Python server source, firewall
and router configuration remain unchanged. Headers, Steam DLLs, logs, local
identity state and binaries are not committed.

## Ownership and behavior

- In-process client only obtains a reference to the loaded Steam module, waits
  for initialized user/pipe handles, checks appid/identity, and borrows the game
  callback pump. It never initializes, pumps or shuts down that Steam session.
  The standalone bridge/diagnostic agent own their own init/pump/shutdown.
- One Sockets P2P connection per authenticated public individual SteamID, max
  eight concurrent peers; no legacy SteamNetworking005 or interface-version
  fallback. Unauthenticated/unencrypted connection states and duplicate live
  identities are rejected. Same-account self-tunnelling is rejected; a host
  player can use the local Python endpoint directly, but simultaneous bridge
  and host-game Steam-session coexistence remains unverified.
- ICE disabled at listener/connection scope, virtual port 1337. No global config
  callback is installed. Callbacks copy status into a bounded locked queue;
  tunnel sockets and SDK connection operations stay on the worker. Callback
  code remains pinned until process exit to protect outstanding callbacks.
- Steam supplies reliability, ordering, retransmission and congestion handling.
  A reliable frame leaves the application queue only on successful submission;
  Busy retries preserve it without advancing sequence. UDP/PING use unreliable
  messages and drop on queue pressure. Steam does not use the M1 ACK/retry loop.
  One bounded receive frame can wait for local TCP backpressure. Stream frames
  received with the wrong native reliability flag are rejected.
- Connections retry after five seconds. A new native connection has a fresh
  tunnel session; old TCP streams/UDP sockets are destroyed. Persistent
  SteamID-to-127.0.1.N mapping is atomically saved before opening server sockets,
  locked against concurrent bridges, and reused across reconnects/restarts.
  Corrupt state and failed writes fail closed; slots never recycle automatically.
- Community-key derivation uses a logical tunnel-server namespace, not shared
  physical 127.0.0.1, so separate bridge accounts receive different per-server
  identity keys. The stock ticket-withholding and existing forced-relay guard
  remain in place. The Python server still does not verify platform tickets or
  bind its claimed user ID to the connecting Steam identity.
- Ten-second logs include SDR config/auth/relay availability, connection state,
  relayed flag, ping, local/remote delivery quality, bytes/sec, pending reliable
  and unreliable bytes, and unacked reliable bytes. These are implemented fields,
  not current measured remote results.

## Tests

- Standalone Win32 build succeeds with `/W4 /WX`.
- Targeted Win32 configuration/protocol/identity tests pass: disabled, mutually
  selected modes, malformed IDs/config, borrowed-session cancellation without
  loading another DLL; individual SteamID validation and overflow; stable map
  reuse, exhaustion, duplicate/corrupt state and per-server key separation.
- Real tunnel runtime over a **test-only ordered-message backend** passes
  concurrent byte-exact TCP/FIN, Busy-send backpressure, every UDP destination
  port, disconnect/reconnect, rejection of an unreliable stream frame, persisted
  source identity after process restart, concurrent map-lock rejection and
  corrupt-map rejection. This exercises the shared runtime and native-message
  branch; it does not prove the Steam DLL adapter, callbacks or SDR.
- Real M1/plain-UDP transport regression passes all 32 UDP ports, stable mapped
  UDP socket, distinct peers, concurrent TCP with selective loss/duplication,
  occupied ports, malformed frames, agent restart, bridge loss/restart and clean
  stop. Unmodified sibling Python-server synthetic auth/list/create/join,
  WebSocket signalling/chat smoke and UDP probe also pass through that adapter.
- WSL GCC/CTest codec and identity-policy tests pass. This is host validation,
  not Proton/Wine runtime qualification.
- Full `BZROpenShim.sln` Release | Win32 build passes; complete Release CTest
  passes **161/161** (247.79 seconds). Network correctness baseline and workflow
  YAML parse pass. No patch catalog sites or engine resolves were added.
- Static PE export inspection confirms the shipped DLL has no `SteamUtils`
  shortcut. The appid check uses its verified exported
  `SteamAPI_ISteamClient_GetISteamUtils` accessor with `SteamUtils008`, then
  `SteamAPI_ISteamUtils_GetAppID`. Networking still uses the exact generic
  Sockets/NetworkingUtils interfaces; no missing shortcut is assumed.
  Standalone `/W4 /WX`, full solution rebuild and five configuration tests pass
  after that accessor correction. Final WSL codec/policy rebuild passes 2/2.

Latest plain-UDP same-PC smoke: median UDP echo RTT 0.387 ms tunnel versus
0.107 ms direct, p95 0.591/0.266 ms; 256-KiB TCP echo throughput 4.80/18.16 MB/s.
These are loopback regression measurements while builds ran, not direct-LAN
comparisons and not Steam/SDR metrics. The real SDK `steam-self-test` command is
available, but successful Steam initialization is still needed to run it.

## Remaining acceptance

| Gate | Status |
|---|---|
| M1 native login/list/create/join + five-minute match | Pending; unchanged |
| M2 borrowed game session / actual Steam callbacks | Implemented; runtime unverified |
| M2 two owning accounts/PCs + ten-minute match / clean exit | Pending |
| Actual SDR status, ping, quality and LAN-vs-tunnel throughput | Pending |
| Host-account appid coexistence, forced-relay gameplay quality | Unknown |
| Bridge interruption during native gameplay and stock retry behavior | Pending |
| Windows Steam/GOG native smoke, Proton/Wine | Unverified |

M1's native harness uses a replacement Steam DLL and remains unused under the
task's shipped-DLL constraint. All native acceptance needs authentic staged
clients or separate PCs. Rich presence/friends Join Game, GOG/Galaxy transport,
server ticket verification, installer/UI and publication remain out of scope.
No merge, release or public deployment occurred.

Local evidence is under `%TEMP%/bzr-tunnel-m2-plain-final/`,
`bzr-tunnel-m2-server-final/`, `bzr-steam-runtime-*`,
`bzr-tunnel-m2-solution-final.log`, `bzr-tunnel-m2-ctest.log` and
`bzr-tunnel-m2-loader-build.log` and `bzr-tunnel-m2-linux-final.log`.
Setup and CLI/INI details are in
[STEAM_TUNNEL.md](STEAM_TUNNEL.md).
