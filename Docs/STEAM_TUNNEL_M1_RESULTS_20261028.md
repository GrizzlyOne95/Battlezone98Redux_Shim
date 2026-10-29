# Steam tunnel M1 evidence — 2026-10-28

Branch `agent/steam-tunnel-m1`, based on
`research/steam-networking-probe` at `9c98e9fe0ecccae10d424659ebdc4160b0d4d150`
(draft #643). Open draft #642 was checked: its server-selection edits overlap
`net_optimizer.cpp`. This work keeps a separate higher-priority tunnel guard
and does not import or alter the LAN preview.

## Milestone verdict

| Milestone | Implemented and validated | Acceptance still required |
|---|---|---|
| M1 | In-process agent, Win32 bridge, plain-UDP adapter, framing/reliability, bounded resources, loopback redirect and existing qualified forced-relay seam. Real socket tests and synthetic clients against the unmodified server pass. | Native client login/list/create/join and a five-minute match; direct LAN comparison. **M1 is not accepted yet.** |
| M2 | Prior shipped-DLL probe from #643 retained unchanged. | Steam transport implementation and two owning accounts/PCs; ten-minute match, clean exit, SDR metrics, host-account coexistence. |
| M3 | Setup, keys, limits and this evidence; feasibility and both Roadmap source files updated. | Final native/Steam section-5 results and release qualification. |

No game was launched. Neither installed game nor Steam installation was
modified. No router ports or firewall rules were changed. The Python server
checkout stayed untouched (its pre-existing untracked `.claude/` remained).
No Steam DLLs/SDK headers, game content, raw captures or local logs are committed.

The existing same-PC native runner in `BZRCoopSession.ps1` replaces
`steam_api.dll` with Goldberg to obtain independent identities. That conflicts
with this task's shipped-DLL requirement, so it was not used as M1 acceptance.
A later native test needs authentic clients in separately staged roots or on
separate PCs, with the installed copies preserved. Synthetic profiles do not
establish native platform authentication or gameplay correctness.

## Checks

- `BZROpenShim.sln` Release | Win32: complete proxy/loader/plugin chain builds.
  Incremental rebuild after final worker-shutdown and UDP-mapping changes also passes.
- Win32 CTest: 154/154 existing-plus-protocol tests pass; the subsequently added
  three configuration cases, protocol and patch-registration tests pass 5/5
  after the final edit.
- `tools/validate-network-baseline.ps1`: passes. No patch catalog addresses or
  signatures were added. `EnsureBzrNetTunnelRelay` reuses existing qualified
  BZRNet settings resolves; game-time qualification remains untested.
- WSL Ubuntu 24.04 CMake/GCC protocol target and CTest: pass. This validates the
  portable codec/queue, **not** Win32 runtime behavior under Proton/Wine.
- `tools/socket_tunnel/build.ps1`: Win32 standalone builds with `/W4 /WX`.
- `socket_tunnel_integration.py`: all 32 UDP ports, one stable server-side UDP
  source endpoint across destinations, two distinct peer source IPs, byte-exact
  TCP plus data after FIN, four concurrent streams through selective first-copy
  loss/duplication, rejected malformed/non-game-port frames, occupied-port
  rejection, agent timeout/restart, bridge loss/restart without agent restart,
  and graceful standalone tunnel shutdown all pass. Twelve reliable frames were
  deliberately dropped; retransmission restored the TCP streams without
  duplication. UDP datagrams are intentionally not retransmitted.
- `socket_tunnel_server_smoke.py`: server
  `fbf7f87963dedee1394a4cad8b536290debb17c7` (`agent/gui-overhaul`), read and run
  unchanged with temporary state/logs. Two existing synthetic stock-profile
  clients authorize, enter lounge, list, create and join. Existing WebSocket
  auth/update/create/P2P-signalling/chat smoke also passes. Probe bytes survive
  unchanged, and the response correctly reports the bridge's `127.0.0.10`
  endpoint, establishing why forced relay is required.

## Local measurements

Final socket run, same Windows PC, 100 sequential 772-byte UDP echoes spread
over all 32 ports, and one 256-KiB TCP echo including half-close. The tunnel path
also traverses the Python test proxy. Values are **round-trip** times; throughput
is application bytes divided by complete echo duration (not link capacity).

| Path | UDP RTT median | UDP RTT p95 | TCP echo throughput |
|---|---:|---:|---:|
| Direct loopback | 0.100 ms | 0.273 ms | 25.41 MB/s |
| Plain-UDP tunnel loopback | 0.391 ms | 0.558 ms | 5.01 MB/s |

Earlier socket-ready runs ranged from 0.21 to 0.39 ms tunnel median and 4.09 to
9.41 MB/s tunnel throughput while builds ran on the machine. These are bounded
smoke measurements, not a benchmark distribution or LAN/SDR performance claim.
The initial Sleep-based poll loop added about 60 ms; it was replaced with socket
readiness waits before the accepted socket runs. No system timer setting changed.

Local raw evidence (not committed):

- `%TEMP%/bzr-tunnel-m1-stable-source/`: `metrics.json` and agent/bridge logs.
- `%TEMP%/bzr-tunnel-server-stable-source/`: `result.json`, server and tunnel logs.
- `%TEMP%/bzr-tunnel-ctest.log`, `bzr-tunnel-solution-stable-source.log`.

Built artifacts at this checkpoint (not packaged/released):

| Artifact | SHA-256 |
|---|---|
| `socket_tunnel.exe` | `E72739D0068D73722783E63CD0668CF958F3F0833E2CACC71DC586B72BA2C8E5` |
| `plugins/openshim.dll` | `C2EF654E5651D476F9DE319D65E5EFC0991351055B4A503C227892FAEEC668AA` |

## Section-5 test design status and risks

1. Baseline: socket and synthetic lobby paths pass; genuine two-client native
   login/relay/five-minute match and LAN comparison remain open.
2. Steam: no new P2P connection tested or transport implemented here. Keep the
   exact header interface versions, generic accessor and shipped DLL approach
   established by #643; status callbacks must use the connection config callback.
3. Metrics: loopback numbers above; real LAN, SDR status/ping/connection quality,
   packet-loss rate under gameplay and high-RTT reliable throughput are unknown.
4. Join Game/rich presence: deliberately excluded by the revised task scope.
5. Negative controls: local bridge unavailable, disappearing bridge, reconnects,
   malformed frames, invalid config and listener conflict covered at socket or
   configuration level. Native retry behavior and GOG-only Steam-mode rejection
   remain open. M1's reserved SteamHost setting blocks rather than downgrades.

The host account also playing appid 301650 is still **unknown**. Forced-relay
quality and the extra host hop are still **unknown** under real gameplay. Plain
UDP is a trusted-test adapter, has no encryption/authentication/congestion
control, may fragment large datagrams, and limits TCP on high-RTT paths through
stop-and-wait. It must not be exposed on the Internet. Per-session IP identity
is bounded and distinct but not persistent across reconnects; M2 needs stable
SteamID-based assignment for useful IP bans. Win32 GOG/Steam native integration,
Proton and Wine remain unverified. No merge, release or public deployment occurred.

## October 29 feedback validation

Complete Release Win32 solution builds. All 158 existing CTests pass; the new
immediate-startup configuration regression also passes separately with the
other four targeted tunnel cases. The resolver waits up to one second for local
binding only. It does not establish bridge reachability; the forced-relay
qualification is a game flag check. M1 remains a trusted local-test milestone:
one 1-KiB frame per RTT (about 20 KiB/s at 50 ms) and a ten-second unacked-frame
timeout. M2 replaces that loop with Steam reliability/congestion handling.

The real M1 integration passes all 32 UDP ports, stable source mapping,
distinct peers, byte-exact concurrent TCP/FIN through loss/duplication,
malformed/8080 rejection, exclusive bind, restart/timeout and clean stop.
The companion DedicatedServer synthetic login/list/create/join, WebSocket
signalling/chat and UDP probe also pass. These are synthetic protocol clients,
not a native multiplayer match. No five-minute native gameplay acceptance,
real two-PC comparison or Proton/Wine result is claimed.

A read-only native IAT check on task-owned isolated GOG PID 75552 confirms the
module boundary: the game's ioctlsocket import targets openshim.dll, while the
tunnel module's socket/sendto/recvfrom/ioctlsocket delay imports target WS2_32.dll.
The agent logs readiness on 127.0.0.1 with game/Galaxy IAT hooks installed and
continues sending its handshake with the bridge absent. The executable is GOG
2.2.301, SHA256 8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413.
This is native hook-boundary evidence, not lobby or match acceptance. The owned
process exits through Stop-BZRGame. Raw IAT/log evidence stays local under
C:/bzt/pr-feedback-game; no game binary or memory dump is committed.
