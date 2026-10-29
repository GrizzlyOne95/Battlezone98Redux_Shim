# Steam networking for BZR multiplayer: feasibility spike (2026-10-28)

Original research snapshot; the probe and M1 implementation now live in separate
stacked workstreams. Question: could OpenShim carry
BZR multiplayer (WS lobby TCP 1337, BZRNet UDP 1338 probe / 1339-1369 relay / P2P)
over Steam networking so Steam friends can "just join" a home-hosted community
server with no port forwarding?

**Current design and implementation status (M1):**
[Steam tunnel setup and limits](STEAM_TUNNEL.md),
[M1 validation results](STEAM_TUNNEL_M1_RESULTS_20261028.md).
Section 1b establishes the generic-accessor approach. Use
`ISteamNetworkingSockets` via the shipped DLL's generic accessor, one P2P
connection per client, reliable TCP frames and unreliable UDP datagrams. Use
the exact current header interface version; never cast older versions to it.
The host bridge is Win32, appid 301650. The in-process client reuses game Steam
initialization. Do not replace Steam DLLs, vendor SDK headers, add server ticket
verification, friends-list Join Game or rich presence in this workstream.
M1 currently implements only the plain-UDP adapter; native five-minute gameplay
acceptance, M2 and the two-account section-5 tests remain open.

Confidence labels: **CONFIRMED** (read from files/binaries this session),
**INFERRED**, **UNKNOWN**. Exe addresses come from existing repo RE docs, not
re-verified in Ghidra here.

## Verdict

**Interface access is confirmed; remote P2P/SDR feasibility is UNKNOWN.** The
shipped DLL's generic accessor supplies Sockets012/Utils004. The proposed seam
is a loopback TCP/UDP tunnel, with a Steam-backed bridge on the server PC.

No connection between two accounts has succeeded. Relay availability reaching
Current and creating a P2P listener do not establish that appid 301650 permits
remote SDR P2P without publisher-side Steamworks configuration. That dependency
remains **UNKNOWN** until two owning accounts connect. Any solution requiring
Rebellion's keys, client secrets or publisher approval is out of scope.

The Steam transport is unavailable to the GOG executable, which does not load
`steam_api.dll`; this is a transport capability limit, not an executable/store
gate on other multiplayer paths. The Galaxy bridge remains blocked because it
requires Rebellion's client secret. Friends-list Join Game and host-account /
bridge session coexistence also remain unverified.

## 1. Steam SDK version and interfaces (CONFIRMED)

Steam install exists at
`C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux` (appid
`301650`, `steam_appid.txt`). The GOG install has none.

- `steam_api.dll` (32-bit, 217,376 bytes, "Steam Client API", file version
  3.62.82.82, 796 exports). Dated 2026-10-24, i.e. as shipped by Rebellion.
- **No** `ISteamNetworkingSockets`, `ISteamNetworkingMessages`,
  `ISteamNetworkingUtils`, SDR or `SteamNetworking*_v###` exports. It has
  `ISteamNetworking` (legacy P2P + the old socket API), `ISteamMatchmaking` (+Servers),
  `ISteamFriends` (incl. `SetRichPresence`, `InviteUserToGame`), `ISteamUser`,
  `ISteamUtils`, UGC, UnifiedMessages, Controller, HTMLSurface, Inventory, Video.
  That is the shape of roughly SDK 1.3x.
- Interface-version strings in the exe: `SteamClient017`, `SteamUser019`,
  `SteamUtils008`, `SteamFriends015`, `SteamMatchMaking009`,
  `SteamMatchMakingServers002`, `SteamNetworking005`, `STEAMAPPS_INTERFACE_VERSION008`,
  `STEAMUGC_INTERFACE_VERSION009`.
- Exe imports from `steam_api.dll` are only the context/callback plumbing:
  `SteamAPI_Init`, `RunCallbacks`, `Shutdown`, `Get{HSteamPipe,HSteamUser}`,
  `Register/UnregisterCallback(+CallResult)`, `SteamInternal_CreateInterface`,
  `SteamInternal_ContextInit`.
- The exe already contains Steam backends: RTTI for `cNetFriendsSteam`
  (`GameRichPresenceJoinRequested_t` callback), `CSteamP2P`
  (`P2PSessionRequest_t`, `P2PSessionConnectFail_t`, "remote end isn't calling
  AcceptP2PSessionWithUser()"), `CSteamLobby` (`GameLobbyJoinRequested_t`, log
  "Exiting game because of steam invite acceptance"), plus the `-connect_lobby=` arg.
  Per `reverse_engineering/netcode_matchmaking_server_plan_20260713.md`, peer
  transport `0x00758C90-0x00763C90` holds "Galaxy/Steam P2P adapters" and lobby
  backends sit at `0x0073D020-0x00751560` (Steam backend vtable `0x00750BD0`).
- The shipped default platform mode is **4 (auto)**: lobbies are the BZRNet
  websocket ones; Steam (or Galaxy) only supplies identity and the auth ticket
  (`mp_not_ready_readiness_chain.md`). The Steam lobby/P2P code is dormant legacy
  from the pre-BZRNet era (modes 1/3). Whether it is still functional is UNKNOWN.

The absence of flat Sockets/Messages exports does not prevent access through
`SteamAPI_ISteamClient_GetISteamGenericInterface`. Section 1b confirms that route
with the shipped DLL. Use exact Sockets012/Utils004 header interfaces for the
spike; no legacy SteamNetworking005 recommendation or DLL replacement is needed.
Remote P2P/SDR acceptance remains UNKNOWN independently of interface access.

### 1b. Live probe: the Steam client serves the new interfaces (CONFIRMED 2026-10-28)

`tools/steam_net_probe/` (32-bit exe, `build.ps1`; `steam_appid.txt=301650`, the
shipped Steam-install `steam_api.dll` copied beside it, no game files or Steam
install modified). It calls `SteamAPI_ISteamClient_GetISteamGenericInterface`
(the legacy `ISteamClient017` accessor) with each versioned name, using headers
from ValveSoftware/GameNetworkingSockets @ `d534c19`. Result on this PC:

| Interface | Served versions |
|---|---|
| `SteamNetworkingSockets` | 006, 008, 009, 010, 011, **012** (current), 013 |
| `SteamNetworkingUtils` | 001, 002, 003, **004** (current) |
| `SteamNetworkingMessages` | **002** (current); 001 returned null |

Using the 012/004/002 pointers with the header vtables worked:
`GetIdentity` returned a SteamID identity (type 16), `CreateListenSocketP2P(vport 0)`
returned a valid listen socket, and the SDR config was fetched for appid 301650
(`ISteamApps/GetSDRConfig/v1?appid=301650`).

SDR status after `InitRelayNetworkAccess` with callbacks pumped through the shipped
dll's `SteamAPI_RunCallbacks`: certificate request then `auth status: OK` within
~0.6 s; ping measurement completed at ~6.2 s with
`relay: overall=100 (Current) ... 26 valid, 1 great, 6 good+, 18 ok+, 6 ignored`;
ping location string was produced (ord/iad/dfw/sea/atl at 27-50 ms from this PC).

Verdict: generic interface access is confirmed; remote SDR remains UNKNOWN. The shipped DLL needs no replacement; the game
process can use `ISteamNetworkingSockets`/`Messages` with SDR through the generic
accessor. Not yet tested: an actual two-account P2P connection (probe is
single-account), reliable-stream behaviour, and coexistence of two processes on the
same appid/account (the probe ran while an unrelated Steam game was running and
Battlezone was not).

## 2. How the `[OpenShimSocket]` layer intercepts today (CONFIRMED from `src/patches/net_optimizer.cpp`, `net.ini`)

- Hooks resolved from `ws2_32.dll`: `WSASendTo`, `WSARecvFrom`, `sendto`,
  `recvfrom`, `WSAConnect`, `getaddrinfo` (+ socket(), `ioctlsocket`, `WSAIoctl`,
  `GetQueuedCompletionStatus` for IOCP completions the game's asio uses). It
  applies tuning (Nodelay, keepalive, buffers, DSCP), packet reorder, send-dup,
  buffer-log and relay capture.
- `MatchmakingRedirectAddress` (or `OPENSHIM_MATCHMAKING_ADDRESS`): a
  `getaddrinfo` hook (`Hook_getaddrinfo`, ~line 4139) substitutes the configured
  hostname/IP for the stock `battlezone98mp.webdev.rebellion.co.uk` lookup and
  fails closed otherwise. Hostname/IP only; ports unchanged.
- Why one redirect covers everything (CONFIRMED, `MP_PRELOBBY_DESIGN.md`,
  `BZRNET_CLIENT_DECOMP_VALIDATION_20261006.md`): the UDP probe target is the
  websocket remote endpoint with port+1; the relay endpoint is the server address
  with the port taken from `OnP2PRoute.port` (no token, no envelope; relay speaks
  the exact bytes the peer would).
- Limits: the seam is **address-level**. It cannot carry bytes over a non-IP
  transport. The TCP websocket runs on asio/IOCP overlapped I/O; splicing a Steam
  message pipe underneath it by hooking `WSASend/WSARecv/ConnectEx/IOCP` is
  possible but far more fragile than a local proxy. Do not do that.

### Recommended seam: loopback tunnel

```
game --getaddrinfo--> 127.0.0.1
 TCP 1337 / UDP 1338 / UDP 1339-1369  (local tunnel agent, in OpenShim or a sidecar)
        |  ISteamNetworkingSockets (reliable stream frames, unreliable UDP messages)
        v   Steam relay / direct
 host bridge (Steam-logged-in, appid 301650) --> 127.0.0.1 Python server 1337/1338/1339-1369
```

The tunnel agent listens on those loopback ports and speaks a tiny framed
protocol: `OPEN(stream)`, `DATA`, `CLOSE` for TCP, and datagram passthrough
tagged with the local port for UDP. The bridge is the mirror image.

Gameplay specifics (INFERRED from the decomp notes, must be tested):

- The probe response (1338) returns the client's "public" endpoint; through the
  tunnel it is the bridge's loopback view, so advertised WAN endpoints are wrong.
  Direct P2P between two tunnelled players then fails. Force `/iprelay` (global
  `0x00946708`, `[Network]` or CLI) for tunnelled sessions so gameplay goes
  through the relay path, which the tunnel carries. Relay hop = Steam latency +
  server hop; no direct P2P.
- The stock relay limitation (one relay endpoint per client) is already solved by
  the pair-relay port range 1340-1369; the tunnel must forward that whole range.
- Clients also advertise LAN endpoints; overlapping 192.168.x ranges across homes
  can mislead the LAN attempt. Pre-existing, not tunnel-specific.
- Bridge-to-server source identity: every remote player appears from 127.0.0.1.
  The Python server matches relay senders by source address and may do per-IP
  limits/bans. Give each Steam user their own loopback source address
  (127.0.0.N, Windows accepts all of 127/8) and distinct source ports.

## 3. Does the Python dedicated server need a bridge? Yes (but not a rewrite)

`Battlezone98Redux_DedicatedServer` is pure Python, no native DLL
(`AGENTS.md`). It has no Steam code and should not gain any. Add a **sidecar
bridge process** on the host:

- Needs a Steam client logged in on the server PC, owning BZR, plus
  `steam_appid.txt=301650` next to it. P2P/relay traffic is scoped per appid, so
  the bridge must present as that app (Spacewar 480 would not interoperate with
  clients running 301650).
- Needs a 64-bit Steam API library with the networking entry points. Python
  `ctypes` over the flat legacy exports of a redistributable `steam_api64.dll` is
  feasible; a small C++/C# bridge is less brittle. Either way it calls
  `SteamAPI_RunCallbacks`, accepts `P2PSessionRequest_t`, opens loopback sockets
  to the server.
- Identity: the bridge can pass the connecting SteamID into the server out-of-band
  (loopback source mapping, or an extra header) so the lobby server's ticket
  validation stays meaningful. The game's `Authorization` still carries its own
  Steam ticket (stock behaviour); the community server currently does not verify
  tickets (`bzrnet_server/README.md`), so this is no regression.
- Failure mode: the host's Steam session conflicts with the host also playing
  from the same account (one session per appid). A second account owning BZR, or
  hosting while not playing, avoids it. UNKNOWN until tested.

## 4. GOG Galaxy equivalent and the cross-store limit

- GOG clients load `Galaxy.dll` / `GalaxyPeer.dll` (present in the install;
  OpenShim already instruments them, `bzrnet_instrumentation.cpp`). Galaxy SDK has
  `INetworking` P2P (`SendP2PPacket`, `GetP2PPacket`, NAT traversal through GOG
  relays) and lobbies/friends invites. The exe has the matching Galaxy lobby
  backend (vtable `0x0074DF20`, `-connect-galaxy-lobby=`).
- Same tunnel design applies with Galaxy P2P as the transport. A Galaxy-hosted
  bridge needs a Galaxy-logged-in host and a Galaxy client id registered for BZR;
  we do not hold Rebellion's client secret, and we can only reach it through the
  loaded `Galaxy.dll` instance (GalaxyPeer from the running game). **UNKNOWN and
  likely blocked** for a standalone bridge.
- **Cross-store**: Steam networking (SteamIDs, appid 301650) and Galaxy P2P
  (GalaxyIDs) are disjoint networks. Steam players cannot reach GOG players over
  either. A host would need two bridges (one per store), each bridging into the
  same local server; both land on the same Python lobby, so Steam and GOG players
  could still share a match via the server relay. That means the host needs both a
  Steam and a Galaxy login. Practical v1: Steam only; GOG players keep
  Tailscale/port-forward.

## 5. Plan, effort, risks, test design

### Plan

| # | Step | Effort |
|---|---|---|
| 0 | Run the unmodified Steam build with `MatchmakingRedirectAddress` at a manual port forward to confirm baseline, and trace via existing BZRNet trace. | 0.5 d |
| 1 | Proof of tunnel without Steam: loopback agent + bridge over a plain UDP/TCP socket pair. Verifies the whole game works through 127.0.0.1 with forced relay. | 2-3 d |
| 2 | Swap transport to `ISteamNetworking005` legacy P2P (`SendP2PPacket` reliable for TCP stream frames, unreliable for UDP; `AcceptP2PSessionWithUser`; callback pump). | 3-4 d |
| 3 | OpenShim integration: ini `[Network] SteamTunnelHost=<SteamID64>`; start agent on game start; fail-closed redirect to 127.0.0.1. Host side bridge as a managed service. | 3-4 d |
| 4 | UX: rich presence `connect` + `steam_display` on the host's bridge/player so friends get "Join Game"; handler maps the `+connect` string to the tunnel (the exe has a `GameRichPresenceJoinRequested_t` handler in `cNetFriendsSteam`, but whether it sets rich presence is UNKNOWN). | 2-3 d |
| 5 | Qualification: 2 accounts, 3-4 players, soak, packet-loss. | 2-3 d |

Total roughly 2-3 weeks, ~1 week to a steam-less tunnel and first Steam-routed
lobby join.

### Riskiest unknowns

1. **Legacy `ISteamNetworking` availability/performance.** Deprecated; relay path
   throughput and reliable-stream head-of-line behaviour for the websocket.
   (Mitigation: step 1 keeps the framing transport-neutral, v2 swaps in
   `SteamNetworkingSockets` via `GetISteamGenericInterface`.)
2. **Does the host bridge coexist with the host's own game session** and does a
   non-game process get the appid P2P identity? UNKNOWN; must test.
3. **Forced relay quality**: no direct P2P between players, every gameplay packet
   crosses Steam and the host PC. The 1339-range relay has only had limited live
   validation (`NETWORK_UI_INTEGRATION_20261009.md`, `COOP_TRANSPORT_20261015.md`).
4. **Friends-list "Join Game"**: depends on rich presence the game may not set; we
   would set it from OpenShim and must verify the Steam launch-arg route and the
   in-game `GameRichPresenceJoinRequested_t` handler both reach our code. Host also
   has to be "in game" for friends to see it.
5. **Steam-only**; GOG players excluded; operational burden on the host (Steam
   client must be up; Valve ToS acceptable for an unlisted community bridge but not
   verified).
6. **Shipped dll churn**: Rebellion updated `steam_api.dll` on 2026-10-24; a future
   change could break an ABI assumption. Keep the agent resolving interfaces through
   `SteamClient017`/generic interface, not raw offsets.

### Minimal 2-account test design

Two machines (or one machine + VM), two Steam accounts that each own BZR, mutual
friends.

1. **Baseline:** host runs the Python server and a *loopback-only* tunnel pair.
   Account A = host, account B = remote. Do not use Steam yet; connect B via a
   LAN/VPN IP to the bridge to prove 127.0.0.1 redirect + `/iprelay` yields a full
   lobby create/join and a 5-minute match. Collect `BZRNet` trace.
2. **Steam transport:** replace the socket pair with `SendP2PPacket`. Pass:
   B logs into BZRNet through the bridge (state 3), sees lobby list, creates and
   joins a game with A, plays 10 minutes, both exit cleanly.
3. **Metrics:** reliable-stream throughput (lobby JSON), per-datagram latency vs
   direct, loss; confirm relay used (probe shows loopback endpoint).
4. **Join Game:** with A in the lobby and rich presence set, B uses Steam's
   friend-list "Join Game" from a closed game and from a running game; confirm the
   `+connect` string reaches the tunnel config and the lobby join.
5. **Negative controls:** B without A running the bridge; kill the bridge during a
   match (does the client reconnect through its existing retry timer); GOG-only
   player cannot connect (expected).

## Is it worth it

For a *community server for Steam friends*: moderately. It removes port forwarding
and gives a "Join Game" click, but adds a Steam-bound bridge and forced relay.
Tailscale gives the same "no forwarding" with zero code, direct P2P between
players, and supports GOG, at the cost of installing and inviting. A playit-style
TCP/UDP tunnel is the lightest route for exposing 1337/1338/1339-1369 without
touching players at all (the client still just uses `MatchmakingRedirectAddress`).
Suggested order: stay on a tunnel/Tailscale now; build step 1 (loopback tunnel
agent) only if Steam-friends UX becomes a priority, since step 1 is reusable by
any transport.

## Sources read

`steam_api.dll` and `battlezone98redux.exe` (Steam install), `src/patches/net_optimizer.cpp`,
`net.ini`, `docs/STEAM_VS_GOG.md`, `docs/MP_PRELOBBY_DESIGN.md`,
`reverse_engineering/netcode_matchmaking_server_plan_20260713.md`,
`reverse_engineering/mp_not_ready_readiness_chain.md`,
`reverse_engineering/bzrnet_server/README.md`,
`Battlezone98Redux_DedicatedServer/BZRNET_CLIENT_DECOMP_VALIDATION_20261006.md`,
`BZRNET_INTEROPERABILITY_RESEARCH_20260824.md`.
Not done: Ghidra confirmation of the Steam P2P/lobby adapter functions, live tests,
and the private `Battlezone_Source` corpus search (timed out; the RTTI strings and
existing repo RE docs were sufficient for this spike).
