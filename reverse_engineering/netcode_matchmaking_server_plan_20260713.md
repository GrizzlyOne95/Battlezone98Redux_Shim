# Redux Netcode Decompilation and Custom Matchmaking Plan

Date: 2026-07-13
Target: Battlezone 98 Redux 2.2.301, GOG SHA-256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`.
The settled Steam executable is treated as the same baseline unless a concrete
runtime mismatch is observed.

## Result

Yes, the netcode can be recovered well enough for resilient patching and a
clean-room matchmaking replacement. The executable has already been globally
decompiled: all 31,948 discovered current-build functions have individual
Ghidra C-like exports. The missing piece was a reproducible attribution layer,
not another whole-executable decompile.

`build_netcode_index.py` now selects 1,096 current-build functions from the
first-party network, platform, lobby, peer-transport, multiplayer UI, and
startup ranges. A one-level static call closure expands that to 1,869 functions
including JSON, WebSocket, and container dependencies. It also indexes 86
strongly named legacy `Net`/`NetPlayer` functions and 281 protocol/string
anchors.

The legacy clean-PDB corpus has C-like output for 15,045 of 15,070 functions.
The only failed function with a network name is the large legacy UI procedure
`NetGameDlgProc`; its complete disassembly is preserved as
`failed_asm/0055da02_NetGameDlgProc.asm`. This does not block understanding the
Redux transport or matchmaking protocol.

Run the focused indexer with:

```powershell
python reverse_engineering/build_netcode_index.py --call-depth 1
python reverse_engineering/build_netcode_index.py --call-depth 1 --output-dir tmp/netcode_index
```

## Current-build subsystem map

| Subsystem | Current VA range | Role |
|---|---:|---|
| Game transport | `0x0056F0F0`–`0x00579DC0` | `Net`/`NetPlayer`, game packets, sync, ping/loss, bandwidth, kick and host migration |
| BZRNet control | `0x006BE3E0`–`0x006C83F0` | WebSocket adapter, JSON messages, auth, endpoint discovery, UDP listener |
| Platform auth | `0x0073B130`–`0x0073CFFF` | Steam/Galaxy identity and authentication callbacks |
| Matchmaking | `0x0073D020`–`0x00751560` | `CNetGameLobby` and BZRNet/Galaxy/Steam lobby implementations |
| Peer transport | `0x00758C90`–`0x00763C90` | BZRNet LAN/WAN/relay handshake and Galaxy/Steam P2P adapters |
| Multiplayer UI | `0x0078E000`–`0x007A2000` | readiness gate, list/create/join/status screens |
| Startup config | `0x007D5120` | BZRNet URL and `/ipdirect`, `/iprelay`, `/bzrnetport` configuration |

These are evidence ranges for analysis, not recommended patch addresses.
Shipping hooks should resolve semantic anchors and validate surrounding bytes.

## Protocol recovered so far

The stock control plane uses unencrypted WebSocket JSON at
`ws://battlezone98mp.webdev.rebellion.co.uk:1337/`. The UDP discovery/probe and
relay services use ports 1338 and 1339. Authentication content includes the API
version, client version, platform identity, local endpoint list, observed WAN
endpoint, and a platform ticket. Tickets must never be copied into fixtures or
committed logs.

Confirmed client-to-server message types:

- `Authorization`
- `CreateLobby`, `CreateGame`, `DoJoinLobby`, `DoExitLobby`
- `DoEnterLounge`, `DoExitLounge`
- `SetLobbyData`, `DeleteLobbyData`, `SetLobbyMemberLimit`, `LockLobby`
- `SetPlayerData`, `DoSetLobbyOwner`
- `DoSendChat`
- `DoUpdateLAN`, `DoUpdateWAN`
- `DoP2PConnect`, `DoP2PRoute`

Confirmed server-to-client message types and nearby schema keys:

- `OnAuthorization`: `success`, `isAdmin`, `isAuth`, `isInLounge`, endpoint and version fields
- `OnLobbyListChanged`, `OnLobbyChanged`: `lobbies`, `lobby`, `users`, `owner`, `metadata`, `memberLimit`, `isPrivate`, `isChat`, `isLocked`, `userCount`
- `OnLobbyCreated`, `OnLobbyJoined`, `OnDoExitLobby`, `OnLobbyRemoved`
- `OnLobbyDataChanged`, `OnUserDataChanged`, `OnLobbyMemberListChanged`
- `OnChatMessage`: `lobbyId`, `speakerId`, `text`
- `OnWANUpdated`, `OnLANUpdated`, `OnHeartbeat`
- `OnLobbyMemberP2PConnect`, `OnP2PRoute`
- `OnWhitelistUpdated`, `OnFailure`, `OnServerShutdown`

The existing `Battlezone_LobbyMonitor` sibling repo independently confirms the
authorization, lobby-list, create/join, metadata, membership, and chat shapes.

## Resilient redirect seam

OpenShim now has an opt-in `getaddrinfo` redirect in `net_optimizer.cpp`.
This avoids patching the compiled URL or depending on an RVA. Configure a host
or IP only (no scheme, path, or port):

```ini
[OpenShimSocket]
MatchmakingRedirectAddress=127.0.0.1
```

Equivalent environment variables are `OPENSHIM_MATCHMAKING_ADDRESS` and
`BZ_MATCHMAKING_ADDRESS`. The stock ports remain 1337/1338/1339, allowing one
redirect to cover WebSocket, probe, and relay services. The option is empty and
inactive by default.

## Experimental control-plane server

`reverse_engineering/bzrnet_server/server.py` is a loopback-only-by-default
clean-room emulator. It implements:

- development authorization without retaining or logging platform tickets;
- lounge and lobby-list state;
- lobby/game creation, password/member-limit checks, join/leave and owner migration;
- owner-controlled lobby metadata and per-player metadata;
- chat and LAN/WAN endpoint updates;
- captured `DoP2PConnect` -> `OnLobbyMemberP2PConnect` routing;
- the captured UDP 1338 public-endpoint discovery response;
- deterministic protocol-state tests independent of WebSocket transport.

Start it with:

```powershell
python reverse_engineering/bzrnet_server/server.py
```

Then set `MatchmakingRedirectAddress=127.0.0.1`. Do not expose this development
server to the internet: it intentionally does not validate Steam tickets and
has not received a security review.

## Paired-capture update

The host/joiner capture from 2026-03-21 closed the direct-path gaps. It proves
the exact 18-byte big-endian UDP header, the 25-byte IPv4 endpoint-discovery
response, the `0x03 -> 0x04 -> 0x05` direct-connect handshake, and the exact
`OnLobbyMemberP2PConnect` routing semantics. The same-LAN game then exchanged
10,561 gameplay packets directly between peers without traversing Rebellion.

See `bzrnet_protocol_capture_20260321.md` for the redacted field map and hashes.

## What is still required for a complete internet replacement

The direct control-plane path is now implemented, but a production-quality
internet replacement still needs:

1. a forced-relay (`/iprelay`) paired capture to recover `DoP2PRoute`,
   `OnP2PRoute`, UDP 1339 framing, allocation, routing IDs, and timeouts;
2. relay implementation with authentication, rate limits, and abuse controls;
3. a separate two-network `/ipdirect` validation pass for NAT/WAN fallback;
4. production Steam-ticket verification, persistence/operations work, and a
   security review.

A same-LAN/direct-only release can proceed without item 1, provided its NAT
limitations are explicit.

After those are known, the safest architecture is:

```text
stock game -> OpenShim DNS redirect -> custom WebSocket control plane :1337
                                      -> custom endpoint probe       :1338/udp
                                      -> optional packet relay       :1339/udp
                         existing game Net/NetPlayer protocol remains unchanged
```

Keeping the stock gameplay packet layer is important: the large
`Net`/`NetPlayer` subsystem already handles simulation sync, loss, migration,
and mission traffic. Replacing only matchmaking and routing sharply reduces the
compatibility surface.

## Patch maintenance rules

- Resolve hooks from stable strings, imported APIs, RTTI, or multi-anchor
  patterns; treat listed addresses as analysis labels only.
- Validate complete expected instruction windows before installing a hook.
- Keep lobby/control-plane hooks separate from gameplay packet fixes.
- Prefer the import-level DNS redirect for server selection.
- Re-run `build_netcode_index.py` and compare category/anchor counts for every
  new executable before accepting a patch profile.
- Capture and redact protocol logs; never store platform authorization tickets.
