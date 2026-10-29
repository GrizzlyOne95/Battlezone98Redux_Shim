# Steam tunnel M2: live two-account test guide

Step-by-step acceptance test for the M2 Steam Sockets tunnel
([setup reference](STEAM_TUNNEL.md), [M2 results](STEAM_TUNNEL_M2_RESULTS_20261028.md)).
It closes the remaining M2 gates: remote P2P connect, lobby, a ten-minute
match, quality numbers and host-account coexistence.

## Already verified (2026-10-29, host PC, account A)

- `socket_tunnel.exe steam-self-test` passes from the staged tool directory and
  from an unrelated cwd: appid 301650, Sockets012/Utils004, owned session,
  reliable and unreliable both directions, clean shutdown.
- `socket_tunnel.exe bridge --steam --server 127.0.0.1` reaches SDR
  overall/config/relay/auth = 100 within about 6 s in that run ("25 valid,
  6 good+, 20 ok+" relays) and listens on virtual port 1337.
- The earlier "SteamAPI_Init failed" did not reproduce with the identical
  staged DLL/appid file. Likely cause (unproven): it ran inside a sandboxed
  agent shell that could not reach the Steam client, or Steam was logged out.
  **Run every Steam command below from a normal user shell with Steam logged in.**

## What you need

| Role | Machine | Account | Runs |
|---|---|---|---|
| Host | PC 1 | Steam account A (owns BZR) | Python server + `socket_tunnel.exe bridge --steam` |
| Client | PC 2 (different network ideal, same LAN acceptable) | Steam account B (owns BZR) | BZR (Steam) with OpenShim from this branch |

- PC 2 must not be able to reach PC 1 directly for the strongest result (for
  example a phone hotspot). No port forwarding on either side.
- A direct-connection baseline (step 6) needs PC 2 able to reach PC 1's
  server normally, e.g. same LAN.

## 1. Build and stage

On PC 1 (bridge) and, for the sanity check only, PC 2. From the repo root:

```powershell
./tools/socket_tunnel/build.ps1 -Out C:/BZRCoop/steam-tunnel -SteamDll '<Steam BZR folder>/steam_api.dll'
```

On PC 2 build `BZROpenShim.sln` Release | Win32 and install that
`openshim.dll` into the Steam BZR install (keep the previous DLL to restore).
The game uses the in-process client inside `openshim.dll`, not the standalone tool.

Sanity check on each PC (Steam logged in):

```powershell
cd C:/BZRCoop/steam-tunnel
./socket_tunnel.exe steam-self-test
```

Pass = `self-test PASS` line. A failure here stops the test; record the output.

## 2. Host: server and bridge (PC 1)

Start the unmodified Python server with pair relay ports (from the repo root):

```powershell
python reverse_engineering/bzrnet_server/server.py --relay-pair-ports --relay-pair-port-start 1340 --relay-pair-port-end 1369 --state-file C:/BZRCoop/steam-tunnel/state.json
```

Then the bridge, saving its log:

```powershell
cd C:/BZRCoop/steam-tunnel
./socket_tunnel.exe bridge --steam --server 127.0.0.1 --identity-map C:/BZRCoop/steam-tunnel/steam_tunnel_peers.txt 2>&1 | Tee-Object bridge.log
```

Wait for `SDR overall=100` and note the SteamID64 from the line starting
`Steam appid=301650 local=`. (Later quality lines also contain `local=0.xx`;
that is a delivery-quality value, not the SteamID.)

## 3. Client config (PC 2)

In the Steam BZR install's `net.ini`:

```ini
[OpenShimSocket]
SteamTunnelHost=<account A SteamID64 from step 2>
TunnelUdpBridge=
```

## 4. Connect and lobby

1. Launch BZR on PC 2 from Steam and open Multiplayer.
2. Expect within 30 s: lobby login succeeds and the server's lobby list
   appears.
3. On PC 1, `bridge.log` should show a `Steam status peer=<B SteamID> ...
   state=3` line (3 = connected), then 10 s quality lines with `relayed=1` and
   a `ping_ms=` value. `steam_tunnel_peers.txt` gains B's SteamID mapped to
   `127.0.1.N`.

| Check | Pass |
|---|---|
| Bridge logs B `state=3`, quality line `relayed=1` | |
| Game reaches lobby list | |
| Peer map entry written | |

## 5. Ten-minute match (forced `/iprelay`)

1. On PC 2 create a game, start a deathmatch or strategy map, and
   play ten minutes. A second client (account C, same setup) makes this a real
   P2P-through-relay match; with one client, play against AI on the hosted game.
2. Every 10 s the bridge logs ping, local/remote quality, bytes/sec and pending
   bytes. Keep `bridge.log` and the game's `openshim.log`.
3. Note visible problems: rubber-banding, warping, desync, chat delay.
4. Quit to menu, then exit the game. Both should exit cleanly (no hang, no
   crash dump). The bridge should log the disconnect and keep running.

Record: median and worst ping, lowest quality, any reconnects, visible issues.

## 6. Direct baseline (optional but wanted)

Clear `SteamTunnelHost=` on PC 2, connect to PC 1's server directly
(`/bzrserver=<PC1 IP>` or the saved server choice) and repeat a short match on
the same map. Compare in-game ping/feel against step 5.

## 7. Bridge loss and recovery

During a lobby session (not a match), stop the bridge with Ctrl+C on PC 1 and
restart it. The client retries 5 s after it sees the connection close; an
ungraceful loss takes up to the 15 s timeout to detect, so expect roughly
5-20 s, then the game's own WebSocket reconnect should land back in the lobby. B keeps the same `127.0.1.N`.

## 8. Host-account coexistence (PC 1, account A)

With the bridge still running, launch BZR on PC 1 from Steam (account A),
using the server **directly** (leave `SteamTunnelHost=` empty; self-tunnelling
is rejected by design). Check:

- The game starts and reaches the lobby while the bridge keeps logging
  `SDR overall=100`.
- PC 2's client stays connected through the bridge, and A and B can join the
  same game.
- Exiting the game on PC 1 does not stop or break the bridge.

Go/no-go: if Steam refuses the second appid session or either process loses
networking, coexistence fails and the bridge needs its own account or PC.

## Reporting

Attach `bridge.log`, both `openshim.log` files and the filled tables to the
tracking issue. Restore PC 2's original `openshim.dll` and `net.ini` afterwards.
