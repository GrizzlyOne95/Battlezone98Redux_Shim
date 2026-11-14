# BZRNet Paired-Capture Protocol Recovery

Date analyzed: 2026-07-13
Captured session: 2026-03-21, Redux `2.2.301`

## Capture scope

The Drive capture set contains synchronized views from a host and joiner in
the same ordinary Rebellion-hosted game. Both PCs were behind the same public
NAT and on the same `192.168.0.0/24` LAN. The host created a passworded game,
the joiner entered it, both launched, exchanged gameplay traffic, and exited.

The raw files remain outside the repository because they contain Steam auth
tickets, player identifiers, private addresses, and a public address. Stable
provenance is recorded by hash only:

| Role | Packets | Duration | SHA-256 |
|---|---:|---:|---|
| Host | 69,335 | 354.418 s | `c83b79c8a31961afae0ff0af1ec789b2cbd1018c9bf5491a023ce105eeac97c2` |
| Joiner | 26,956 | 326.118 s | `75006cc7570f44567382dced1b75fe7b5845d1d8b4ac505161a254b5c4429310` |

The two Windows clocks differed by roughly 0.6 seconds. Packet order within
each capture is reliable; cross-machine timestamps need that offset applied.

## WebSocket control plane

The stock service is JSON over an unencrypted WebSocket on TCP 1337. The
captured game exercised the following client requests:

- `Authorization`, `DoEnterLounge`, `DoExitLounge`
- `CreateGame`, `DoJoinLobby`, `DoExitLobby`
- `SetLobbyData`, `SetLobbyMemberLimit`, `LockLobby`
- `SetPlayerData`, `DoSendChat`, `DoP2PConnect`

Every request has the outer form:

```json
{"content": {}, "type": "MessageName"}
```

`content` is not always an object. Confirmed scalar cases are
`SetLobbyMemberLimit` (integer), `LockLobby` (boolean), `DoExitLobby` (lobby
ID), `DoEnterLounge`/`DoExitLounge` (boolean), and `DoSendChat` (string).

Server events use:

```json
{
  "type": "EventName",
  "data": {
    "type": "EventName",
    "time": "YYYY-MM-DD HH:MM:SS",
    "success": true
  }
}
```

Confirmed event-specific fields include:

- `OnLobbyCreated`: `id`
- `OnLobbyJoined`: `id`, `reason`, `reasonCode`
- `OnLobbyMemberListChanged`: `member`, `lobbyId`, `removed`
- `OnLobbyDataChanged`: `changedLobby`
- `OnUserDataChanged`: `member`, `lobbyId`
- `OnChatMessage`: `text`, `lobbyId`, `speakerId`
- `OnLobbyMemberP2PConnect`: `member`, `lobbyId`, `connect`, `reset`
- `OnLobbyRemoved`: `id`

`OnLobbyChanged.data.lobbies` and `OnLobbyListChanged.data.lobbies` are maps
keyed by decimal lobby ID strings. A lobby record has:

```text
userCount, memberLimit, isPrivate, isLocked, metadata, owner, isChat,
clientVersion, id, createdTime, users
```

A user record has:

```text
isInLounge, lanAddresses, wanAddress, metadata, ipAddress, isBB, isAdmin,
isAuth, lobby, name, clientVersion, authType, id, isTest
```

Per-player game values such as `miniid`, `team`, `knownPlayers`, `vehicle`,
`ready`, `clientsconnected`, `clientsremotedup`, and `launched` live under the
user's `metadata` object. They are not flattened into the user record.

### P2P-connect routing

The captured request is:

```json
{"content":{"player":"TARGET_ID","reset":false},"type":"DoP2PConnect"}
```

The server delivers this event to `TARGET_ID`:

```json
{
  "type":"OnLobbyMemberP2PConnect",
  "data":{
    "member":"REQUESTER_ID",
    "lobbyId":1356,
    "connect":true,
    "reset":false
  }
}
```

This is the control-plane signal that causes the target client to begin its
LAN/WAN/relay decision for the requesting lobby member. A self-targeted request
is echoed back and initializes the local/self peer entry.

## Common UDP header

Endpoint discovery, connect negotiation, acknowledgements, and gameplay all
use the same 18-byte big-endian BZRNet header:

| Offset | Size | Meaning |
|---:|---:|---|
| `0x00` | 1 | flags: `0x40` final/unfragmented; `0x80` reliable; `0xC0` reliable + final |
| `0x01` | 1 | low-nibble message kind |
| `0x02` | 8 | Unix epoch milliseconds, big-endian |
| `0x0A` | 4 | reliable send sequence, big-endian |
| `0x0E` | 4 | peer receive/ack sequence, big-endian |

The decompiled serializers `FUN_0075A490`, `FUN_0075A710`, and
`FUN_0075BEB0` construct these fields. `FUN_0075D800` validates and dispatches
them. Confirmed kinds are:

| Kind | Purpose |
|---:|---|
| `0x0` | gameplay payload or transport keepalive |
| `0x2` | public-endpoint discovery |
| `0x3` | direct-connect offer/probe |
| `0x4` | direct-connect accept |
| `0x5` | direct-connect confirmation |
| `0x6` | connected-peer endpoint update |
| `0x7` | basic sequence acknowledgement |

Reliable kind-0 traffic uses flag byte `0xC0`; ordinary unreliable game
traffic uses `0x40`. The gameplay payload begins immediately at offset 18 and
is the existing Redux `Net`/`NetPlayer` datagram. A matchmaking replacement
does not need to decode or replace that simulation protocol.

## UDP 1338 endpoint discovery

The client sends exactly the 18-byte common header with flags `0x40`, kind
`0x2`, current timestamp, and zero sequence fields. The server echoes that
header and appends:

| Size | Meaning |
|---:|---|
| 1 | address byte length (`4` for IPv4) |
| 4 or 16 | observed source IP in network byte order |
| 2 | observed UDP source port, big-endian |

Thus the captured IPv4 response is 25 bytes. Both clients sent a probe about
every 30 seconds. `FUN_006C6E60` requires the response to match the configured
probe-server endpoint, rejects stale timestamps beyond approximately 60
seconds, validates the address length, and emits `DoUpdateLAN`/`DoUpdateWAN`
when the local or observed public endpoint changes.

## Direct same-LAN handshake

After `OnLobbyMemberP2PConnect`, each peer sends a kind-`0x3` packet to every
advertised candidate address. Its payload is the sender's platform ID as
ASCII, including the terminating NUL. Reachable peers exchange:

```text
0x03 offer/probe -> 0x04 accept -> 0x05 confirmation
```

`FUN_0075D800` associates the packet with a known lobby member by the NUL-
terminated ID, chooses the source endpoint that answered, and marks the peer
connected after kind `0x5`. In this capture it selected the two private LAN
endpoints. Gameplay then remained direct between the PCs: 10,561 UDP packets,
about 2.24 MB, over roughly 204 seconds. No game payload traversed Rebellion.

## Stock lobby-startup trace (2026-07-13)

A second, short capture filtered to TCP `1337` and UDP `1338` recorded one
stock client entering the Rebellion multiplayer lobby. The control-plane order
was:

```text
Authorization
OnAuthorization
OnWhitelistUpdated
DoEnterLounge
OnLobbyListChanged
DoJoinLobby
OnLobbyChanged
OnLobbyMemberListChanged
OnLobbyJoined
SetPlayerData
OnLobbyChanged
OnUserDataChanged
OnLobbyChanged
OnLobbyDataChanged
OnLobbyChanged
OnLobbyDataChanged
```

The important compatibility detail is that `OnLobbyListChanged` already
contains a persistent `~chat~pub~~default` lobby and bridge service user. The
client joins that existing lobby; it does not create the initial chat lobby.
Reproducing that seeded state, including the derived `userCount` and fixed-width
`userPack` metadata, lets the stock 2.2.301 client clear its gathering overlay
and reach a ready multiplayer lobby against the local server.

The same trace contained three 18-byte kind-`0x2` endpoint probes and three
25-byte IPv4 responses, independently confirming the UDP `1338` format above.
The raw trace was kept only in the temporary directory during analysis and was
deleted after the redacted results were recorded.

## What this capture does not cover

There is no UDP 1339 traffic and no `DoP2PRoute`/`OnP2PRoute` message because
the LAN path succeeded. A complete internet replacement therefore still needs
one forced-relay (`/iprelay`) paired capture to recover the relay envelope,
allocation response, routing identifiers, timeout behavior, and abuse limits.
A separate two-network `/ipdirect` capture would validate WAN fallback and NAT
behavior, but it is not required for a same-LAN/direct-only first release.

## Reproduction

Use the redacting analyzer rather than opening or copying raw authorization
payloads into repository artifacts:

```powershell
python reverse_engineering/analyze_bzrnet_capture.py <host.pcapng> <joiner.pcapng>
```

The analyzer reports message counts and UDP wire classes without printing
Steam tickets, player IDs, IP addresses, or gameplay payloads.
