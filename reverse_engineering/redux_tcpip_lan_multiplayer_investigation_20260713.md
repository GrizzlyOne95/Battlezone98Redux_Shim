# Redux TCP/IP and LAN Multiplayer Investigation

Date: 2026-07-13

Scope: Redux 2.2.301. Function addresses and pseudo-code come from the existing
GOG best-effort corpus, which is the accepted static baseline for this
workspace. The current Steam executable's imports/strings and the settled Steam
runtime log were checked separately. As usual for the bound Steam image, use a
settled runtime probe before turning any address below into a patch site.

## Conclusion

Battlezone 98 Redux has a functional direct LAN **gameplay transport**, but it
does not have a standalone LAN multiplayer mode or a manual TCP/IP host/join
mode that can simply be exposed in the UI.

In the default Redux/BZRNet backend, players first authenticate with the online
BZRNet service and enter a centrally coordinated lobby. BZRNet exchanges each
player's LAN and WAN UDP endpoints. The peers then automatically choose one of
three gameplay paths:

1. LAN UDP when the advertised local endpoints are usable;
2. direct WAN UDP otherwise;
3. the BZRNet relay when direct connection fails or relay is forced.

Therefore:

- same-LAN players already benefit from a direct LAN path after meeting in an
  online lobby;
- there is no LAN broadcast browser, offline lobby, or raw IP-address join;
- there is no TCP gameplay transport (TCP/WebSocket is used for the online
  control plane);
- adding "LAN" or "Direct IP" buttons would require a new session/discovery
  backend, not a visibility patch.

## Evidence

### The active Redux backend opens a native UDP peer socket

`FUN_006be750` at `0x006BE750` constructs and binds the BZRNet P2P socket. The
requested port is initially zero, so Winsock chooses an ephemeral port; the
bound port is then read back into `DAT_00945704`. The related completion path
logs:

```text
BZRNet P2P Socket Opened With %ld received buffer, %ld send buffer, port %ld
```

The current Steam runtime log independently confirms this path:

```text
2026-07-12 ... BZRNet P2P Socket Opened With 1048576 received buffer,
32768 send buffer, port 51330
```

The executable imports the Winsock functions required for this transport,
including `WSASocketW`, `bind`, `WSARecvFrom`, `WSASendTo`, `select`, and
`closesocket`.

### LAN, WAN, and relay are implemented connection states

`FUN_0075eea0` at `0x0075EEA0` is the BZRNet peer-connect decision path. It
contains explicit, live branches that log and enter:

```text
BZRNet P2P Starting LAN Connect For Client %s - HandleP2PConnect
BZRNet P2P Starting WAN Connect For Client %s (IP %s) - HandleP2PConnect
BZRNet P2P Starting RELAY Connect For Client %s - HandleP2PConnect
```

For LAN it sets the connection state to `1` and a 15-tick/second-class retry
counter; for WAN it uses state `3` and a 30-unit retry counter. Forced relay
bypasses both direct paths.

`FUN_0075d800` at `0x0075D800` completes all three handshake variants. Its
live messages include:

```text
BZRNet P2P Completing LAN Connect For Client %s
BZRNet P2P Completing WAN Connect For Client %s
BZRNet P2P Completing RELAY Connect For Client %s
BZRNet P2P Completed %s Connect For Client %s, using address %s
```

This is complete connection and packet-validation logic, not an unused UI
string table.

### The online server supplies endpoint information

`FUN_006c6e60` at `0x006C6E60` handles BZRNet endpoint discovery and updates.
It parses a server-observed `wanAddress`, enumerates `lanAddresses`, and sends
the WebSocket control messages `DoUpdateLAN` and `DoUpdateWAN` when either set
changes.

This explains the architecture: the LAN route is selected only after the
online service has identified lobby members and distributed their endpoint
records. There is no local broadcast enumeration in this path.

### Lobby creation and joining are online control-plane operations

The default backend's lobby-list request is `FUN_0074c190` at `0x0074C190`,
which logs `BZRNetLobby::GetLobbyList called, requesting lobbies`.

`FUN_006c3fb0` at `0x006C3FB0` builds and sends a `CreateLobby` WebSocket
message. `FUN_006c46b0` at `0x006C46B0` builds and sends `DoJoinLobby`, with a
lobby ID and password. These are required before the P2P peer entries used by
the direct LAN/WAN transport exist.

The current Steam log confirms the production sequence:

```text
Initializing BZR Network
BZRNetLobby::GetLobbyList called, requesting lobbies
BZRNetInterface starting connection to websocket
Websocket established!
Authenticated to BZRNet ...
```

### The UI has no hidden TCP/IP or LAN selection path

`FUN_0079ea90` at `0x0079EA90` constructs the Redux multiplayer lobby UI. The
available primary actions are `Create Game`, `Create Room`, and `Join Game`.
No TCP/IP, direct-address, or LAN-browser controls or handlers are present.

`FUN_0078eb50` at `0x0078EB50` gates multiplayer readiness through the active
online interface. When its status is "no internet" it disables the multiplayer
action and displays the localized `multi_message:no inet` string, "Connect to
internet". This prevents treating the existing UI as an offline LAN launcher.

The Redux executable contains no `TCP/IP`, `DirectPlay`, or `IPX` UI strings,
and imports no DirectPlay/IPX library. Some legacy localization rows still
mention IPX or an "internet transport", but their error keys have no code
references in the Redux decompilation and are data residue from the original
game.

### Hidden switches affect route preference, not session discovery

`FUN_007d5120` at `0x007D5120` parses two relevant command-line switches:

- `/ipdirect` clears `DAT_00946708`, allowing the LAN/WAN direct-connect
  decision path and its normal relay fallback;
- `/iprelay` sets `DAT_00946708`, causing `FUN_0075eea0` to start with the
  relay path.

It also accepts `/bzrnetport=<port>`. The default is zero/ephemeral, and the
actual bound UDP port is advertised through BZRNet.

These switches could safely be exposed as advanced troubleshooting options,
but they do not create direct-IP or offline LAN multiplayer.

## Comparison with the original network stack

The legacy 1.5 PDB corpus exposes the older Activision `dp_*`/ANet model,
including `dpCreate`, `dpEnumTransports`, `dpEnumServers`, `dpEnumSessions`,
`dpOpen`, `dpSend`, and `dpReceive`, plus transport/session UI callbacks. Redux
does not import or retain that old transport-enumeration stack. Its network
simulation remains, but lobby discovery, identity, and peer transport were
replaced by Steam/Galaxy/BZRNet abstractions.

This is why old Battlezone transport concepts cannot be restored by adding the
old labels to the Redux menu.

## What can reasonably be exposed

Low-risk UI/config additions:

- show the negotiated path for each peer: `LAN`, `WAN`, or `RELAY`;
- expose "Prefer Direct" (`/ipdirect`) versus "Force Relay" (`/iprelay`);
- optionally expose a fixed BZRNet UDP port for firewall administration.

These would describe/control behavior Redux already implements.

## What a real standalone LAN mode would require

A standalone LAN feature is feasible as a new OpenShim subsystem, but it is a
substantial implementation project. At minimum it needs:

1. host advertisement and client discovery (typically UDP broadcast or
   multicast), plus manual IP fallback;
2. a local replacement for lobby IDs, player identity, membership, passwords,
   map/mod metadata, ready state, and launch synchronization;
3. construction/removal of the internal BZRNet P2P peer records without an
   authenticated WebSocket lobby;
4. bypasses for the UI's internet/auth readiness gate;
5. host migration, disconnect, duplicate-ID, version, and mod mismatch
   handling;
6. two-machine validation, because two clients on one Windows host do not
   reproduce firewall, adapter, and broadcast behavior reliably.

The least invasive architecture would be to emulate the small portion of the
BZRNet lobby/control-plane contract locally and continue using the existing
LAN UDP handshake and game packet layer. Reintroducing the legacy ANet stack or
inventing a second game-packet protocol would be much higher risk.

## Recommendation

Do not add "TCP/IP" or "LAN" buttons to the existing Redux lobby as a simple
UI patch. Mark standalone TCP/IP/LAN as unsupported by stock Redux.

If the goal is transparency and troubleshooting, expose the existing automatic
LAN/WAN/relay route and direct/relay preference. If offline LAN is a desired
feature, scope it as a separate lobby-backend project with a two-PC test plan.
