# Multiplayer pre-lobby: design

Status: **nickname + flag + server selection (Rebellion / Custom, host only)
implemented** as an OpenShim shell screen (`src/patches/prelobby_screen.cpp`,
opt-in `[Network] PreLobby = 1`). LAN and non-default ports are not built. Static RE for the GOG build
(sha256 `8d71f56c…3377413`, byte-identical to the decompile corpus). The live
checks listed at the end have not run.

## Summary

Battlezone 1.5 went **Main menu → transport/character screen → lobby**. Redux
goes **Main menu → lobby**. The proposal is to put a 1.5-style pre-lobby back in
front of the Redux lobby. The player sets a nickname and flag there, and picks
**Official**, **Custom server** or (later) **LAN**. Continue applies the choices
and then runs the stock Multiplayer path.

Two decisions follow from the RE below:

1. **The pre-lobby is an OpenShim shell screen** (`kPreLobbyScreenId`), built by
   the shell-screen framework (`include/shell_screens.h`,
   `src/engine/shell_screens.cpp`). The earlier premise, that the shell factory
   is a closed switch and the page must be built in place on the title screen,
   no longer holds: the framework detours the factory and builds registered ids
   the way stock screens are built, with the stock background, a painted centre
   panel, history-stack navigation and Esc/Back. The old in-place variant
   (hide/restore of the title controls) is gone.
2. **Force re-auth; do not defer auth.** Redux connects and authenticates at
   process startup, and invite/launch-argument joins rely on that. The
   pre-lobby edits saved preferences. When something identity-bearing changed,
   it recycles the websocket so the stock reconnect sends a fresh
   `Authorization`. The main menu is the safest place to do that, because the
   player is not in a lounge yet.

## What 1.5 did

All in `bzone.exe` 1.5.2.27. The detail is in
[`bz15-multiplayer-ui-port.md`](bz15-multiplayer-ui-port.md); this is the flow
that matters here.

- **Shell modes:** `DispatchDialog` switches on `nShellMode`. Mode 1 is the main
  menu. MULTI PLAYER sets mode `0xd`, which runs `do_stransport` /
  `STransportDlgProc`. Lobby mode is `0xe` (`do_shell`).
- **What the pre-lobby holds:**
  - **Character record:** name, e-mail, URL, flag and description, stored in
    `netnam2.txt`. A flag change saves immediately.
  - **Transport:** from `dpEnumTransports`: Modem, Null Modem, Internet, IPX,
    LAN.
  - **Server:** for Internet, a live server list (`dpEnumServersEx` polled every
    100 ms, showing ping and players). Picking a server calls
    `dpSetGameServerEx`. There is no free-form address.
- **NEXT:** commits the name (`Net_SetPlayerName`), transport and params,
  creates the connection, saves `network.def`, and switches to mode `0xe`.
- **When identity reaches the network:**
  - The name is first sent when the lobby opens and calls `dpCreatePlayer`.
  - E-mail, URL and description follow via `dpSetPlayerData` key `0xe`.
  - The flag is not sent in the lobby at all: it goes in-game as player data
    key `0xd` (`SetMyFlag`).
- **Back:** from the lobby it does `Net::Close` + `dpDestroy` and returns to mode
  `0xd`. 1.5 never re-authenticates; it tears down and rebuilds.

## What Redux does

Confidence labels follow the gate-status convention (**CONFIRMED** from code,
**HIGH**, **INFERRED**, **UNKNOWN**).

### Connection and auth happen at startup — CONFIRMED

- **Startup order:** `FUN_00618c10` runs argument parsing (`FUN_007d5120`), then
  `FUN_00764d80`, then window creation, then provider init (`FUN_00764f50`).
- **Client creation:** in mode 4 (the shipped default), `FUN_00764d80` creates
  the BZRNet client (`FUN_006c6830` → ctor `FUN_006be3e0`). The ctor also opens
  the UDP P2P socket. The websocket connect (`FUN_006c35c0`, logs "starting
  connection to websocket") proceeds once the platform ticket or name arrives:
  - Steam: encrypted-ticket callback `FUN_00765de0`.
  - GOG: Galaxy listener `FUN_0073aef0`.
- **Client state at `client+4`:**

  | Value | Meaning | Where set |
  |---|---|---|
  | 1 | websocket open | `FUN_006bee20` |
  | 2 | `Authorization` sent | `FUN_006c6e60` |
  | 3 | authorised | `FUN_006bf2a0` |

  A failed auth re-requests the Steam ticket.
- **Readiness:** `isNetworkInit` (`FUN_00764870`) needs platform-ready plus
  client state 3. `getLobby` (`FUN_00764760`, `DAT_00945470`) is non-null from
  startup.
- **Menu and lobby:** the main menu is usable before auth completes, and
  Multiplayer reads "Not Ready" until state 3. `Click_MultiPlayer`
  (`FUN_0078c6c0`) checks those two things and pushes screen `0x0E`. The lobby
  ctor (`FUN_0079EA90`) sends `DoEnterLounge`.

### The name is read once per connection — CONFIRMED

- **Where it is read:** the `Authorization` body is built in `FUN_006c6e60`, only
  on the state 1 → 2 transition. That is where the `/nickname=` buffer
  `0x009453E0` is read; an empty buffer falls back to the platform `realname`.
- **What `SendAuthorization` does:** `0x006C6DF0` only re-posts that handler. On
  an authorised socket it puts nothing on the wire, which matches what OpenShim
  observed.
- **Existing OpenShim re-auth:** `src/patches/bzrnet_settings.cpp`
  (`[Network] ReauthOnNicknameChange`) closes the port-1337 TCP socket
  (`RecycleBzrNetWebSocket`) and relies on the stock reconnect. It does not
  re-send on the same socket. Treat
  `reverse_engineering/bzrnet_nickname_reauth_design_20260905.md` as out of
  date on that point.
- **Recycle gate:** the recycle is only taken with a valid lobby object and no
  in-game net id.

### The engine reconnects by itself — CONFIRMED

`FUN_006bf0d0` handles websocket close. It clears `client+4`:

- If the old state was 3 or higher, it reconnects immediately (`FUN_006c35c0`).
- Otherwise it re-arms a retry timer (`DAT_0260b0a0`).
- A connect failure (`FUN_006bef70`) also retries on the timer, with no limit.

**When a lounge is registered** (`client+0xC38 != 0`), the close handler first
calls `FUN_0074d250`, the lounge-exit path. So:

- **Recycling from inside the lobby** tears the lounge down locally. What
  screen `0x0E` does then is **UNKNOWN**.
- **Recycling from the main menu** has no lounge to tear down: Back from
  `0x0E` (`FUN_0079dd60`) has already run `DoExitLounge`.

That is the strongest argument for doing identity changes in a pre-lobby rather
than in the lobby itself.

**After Back from the lobby**, no websocket close is visible: the session stays
authorised and nothing re-authenticates (CONFIRMED in code; confirm live).

### Where the endpoint lives — CONFIRMED / INFERRED

- **`/bzrserver=`:** parsed in `FUN_007d5120`, `strncpy` into the 4 KB global
  `0x008F0690`. The client ctor copies it once into a `std::string` at
  `client+0xC`. Writing the global after startup does nothing.
- **Per attempt:** `FUN_006c35c0` re-reads `client+0xC` on every connect
  attempt.
- **Re-resolution:** whether each attempt calls `getaddrinfo` again, and so
  passes through OpenShim's redirect (`net_optimizer.cpp`,
  `[OpenShimSocket] MatchmakingRedirectAddress`), is **INFERRED**: the call is
  inside the networking library.
- **UDP probe target:** the websocket's remote address at port+1, so it follows
  the endpoint (INFERRED from code; check live).
- **No teardown path:** there is no teardown or re-create path for the net
  objects after startup (HIGH, not exhaustive).

### Flag — CONFIRMED / UNKNOWN

- **Where it is sent:** `SetMyFlag` (`0x0056FA50`) stores the image in NetPlayer
  data slot `0x0D`. Its callers are the player-joined path and a throttled
  in-game resend. The flag travels on the gameplay Net layer, not the
  websocket, so **it needs no re-auth.**
- **How OpenShim changes it:** `SetMyFlag` exits early once slot `0x0D` exists,
  so OpenShim's lobby flag picker overwrites the cache and slot itself.
- **How `-flagfile:` reaches the image:** the argument fills `0x00918404`, but
  `SetMyFlag` loads from `0x00917FAC`. The link between the two is **UNKNOWN**.

### Entry paths that never see the main menu — CONFIRMED

- **Launch arguments:** `-connect_lobby=` and `-connect-galaxy-lobby=` set
  `DAT_009183ec` and the lobby id. `FUN_005d42e0` then busy-waits up to 15 s on
  `isNetworkInit`:
  - On success it sets the next screen to `0x0F` and joins (`FUN_00741840`).
  - On timeout it falls through silently to the main menu.
- **In-session invites:** `FUN_007408c0` (OnGameLobbyJoinRequested) exits a
  running match into the same wait, or queues a pending join from the shell.

These joins **require auth to be done at startup**. Deferring auth until a
pre-lobby closes would make every invite time out.

## Design

### Model: saved preferences, applied at every auth

The preferences are the single source of truth. The pre-lobby is an editor for
them, and every connection, including invite joins, uses them.

| Preference | Stored | Applied by | Needs reconnect? |
|---|---|---|---|
| Nickname | `openshim.ini` (existing) | `/nickname=` buffer `0x009453E0` before connect | yes, if changed while authorised |
| Flag | existing flag config | existing `lobby_ui.cpp` / slot-`0x0D` path | no |
| Endpoint | `openshim.ini` (new `[Network] Endpoint` / `CustomEndpoints`) | redirect hook, or `/bzrserver=` at launch | yes, if changed |

Changing the preferences writes them out first and unconditionally, as the
nickname apply already does. The persisted value is what a restart or invite
will use, whatever happens to the live session.

### Surface

1. `Click_MultiPlayer` (`FUN_0078c6c0`) is detoured. With `[Network] PreLobby`
   on (read at click time) it calls `ShellScreens::RequestScreen` for the
   pre-lobby; otherwise, or if that fails, it runs the stock body. While
   Continue is running the detour passes straight through.
2. The title screen disables the Multiplayer button every frame until BZRNet
   authorises, so the click would never arrive while it reads "Not Ready". The
   one call site of the MP-status refresh (`0x0078EB30` -> `0x0078EB50`) is
   redirected to run the stock refresh and then re-enable the button when the
   setting is on.
3. The screen is a Top Screen with a painted 1440x1080 panel
   (`osh_prelobby_center.png`, `mkscreens.py` `PRELOBBY_LAYOUT`):
   - title "MULTIPLAYER"
   - PLAYER box: the nickname entry (`CreateNicknameAndRouteWidgets`, with its
     `AppendChar` focus path) and the flag `<` / preview / `>`
     (`CreateFlagButtonCommon`), borrowed from `lobby_ui.cpp` and parented to
     the centre panel
   - CONNECTION box: `Network: Ready | Connecting... | Status unknown`, and a
     `Server:` row with two stock-style option slots, **Rebellion** and
     **Custom** (the selected one is captioned `> Rebellion <`), plus a text
     entry for the custom host that exists only while Custom is selected. A
     note under it reads "Custom servers never receive your sign-in
     ticket." When a test redirect is active
     (`GetMatchmakingRedirectTarget`) the row is instead the read-only label
     `Server: <addr> (test redirect)` and no toggle or entry is built.
   - Back (top corner) and Continue (bottom centre)
4. Typed characters reach whichever entry is being edited (nickname or custom
   server; a click on one makes it the active entry and ends the other) through
   the screen's own char slot (cUI_View slot 2), via the framework's `onChar`
   callback. Enter ends the edit and applies nothing. The per-frame
   status and Continue polling run from the `tick` callback (slot 13, after the
   stock update). Both run under SEH.
5. **Continue:**
   1. End both edits. Resolve the selector to a host (Rebellion's, or the
      validated custom host); an empty or malformed address, or any port other
      than 1337, stops here with a note and no recycle. If the host differs
      from the one in effect (live override, else the launch server), persist
      `[Network] Server` / `CustomServer` and set the live override. This runs
      before the nickname step so the reconnect's lookup sees the new host.
   2. If the typed name differs from the persisted one, persist it and, when
      the connection is authorised outside a match, recycle the websocket
      (`ApplyBzrNetNicknameForPreLobby`). If only the server changed, or the
      nickname apply did not recycle, the screen recycles directly, so exactly
      one recycle covers both.
   3. If the connection was recycled or is not yet authorised, show
      "Connecting..." and wait in the tick for `isNetworkInit` (2 s grace for
      the old authorisation to drop, 20 s timeout).
   4. Call the original `Click_MultiPlayer` with `this` = the pre-lobby screen
      (it only uses the shell manager at `+0x138`, which every OpenShim screen
      stores). Its `isNetworkInit` check is the gate, so a failed reconnect
      leaves the player on the screen. The lobby is pushed on top and lobby
      Back returns here.
6. **Back / Esc:** the shell pops the screen. An unapplied typed name or
   server choice is dropped (the next build reads the persisted state).
7. With the setting on, the nickname and flag pickers are no longer built on the
   in-lobby host/client setup screens (the net-route readout stays there).

The in-lobby `/nickname` command keeps working either way. Its recycle runs
while a lounge is registered, which is the unknown case above.

### Endpoint switching

The redirect at `getaddrinfo` swaps the **host** only. The URL, its port (1337)
and the path come from `client+0xC`.

**Implemented, host only:**
1. Set the live override (`SetMatchmakingServerOverride`, net_optimizer).
2. Recycle the websocket.
3. The reconnect resolves the new host.

The reconnect calling `getaddrinfo` again is live-confirmed (the redirect log
line repeats after a recycle).

**Precedence, highest first:**
1. The test redirect (net.ini `[OpenShimSocket] MatchmakingRedirectAddress` or
   `BZ_MATCHMAKING_ADDRESS` / `OPENSHIM_MATCHMAKING_ADDRESS`). Fail-closed guard
   for the test harness: it redirects the official host as before, nothing
   below applies while it is set, and the pre-lobby selector is read-only.
2. The saved choice: `[Network] Server = Rebellion | Custom` with
   `CustomServer = <host or IP>[:1337]`, loaded at startup into the live
   override (so the first connection and invites use it) and updated by
   Continue. Absent or blank means no override.
3. The `/bzrserver=` launch switch.
4. The official host.

The hook substitutes the override for lookups of the **launch host** (the host
of `/bzrserver=` parsed from the command line, else the official host). The
override is a mutex-guarded runtime value; the hook logs each substitution.
Parsing and validation live in `include/matchmaking_server.h` (unit-tested).
This needs the socket hooks, i.e. `[Network] NetImprovements` on.

**A different port or path** needs `client+0xC` rewritten. That is an MSVC
`std::string` inside the client object, owned by the game's CRT. Writing it
from OpenShim means matching that layout and allocator exactly, which is the
`StableId`/`BzrString` overlay mistake waiting to happen. **Do not do this in
the first version.** For non-default ports, persist the endpoint and apply it
as `/bzrserver=` on the next launch, with OpenShim offering a relaunch.

**Security: the platform ticket is withheld from non-official servers.** The
`Authorization` body carries the Steam/Galaxy ticket; a malicious server could
try to replay it against Rebellion's service while it is still valid. So
OpenShim never lets it leave for any host other than
`battlezone98mp.webdev.rebellion.co.uk`, whichever way the server was chosen
(`[Network] Server=Custom`, `/bzrserver=`, or the test redirect):

- A BZRNet lookup that resolves to a non-official host records its addresses.
  On every send, a connected TCP socket whose peer is one of them (port 1337)
  withholds; the verdict comes from `getpeername` each time, so it also covers
  the sockets the game's IOCP library creates and connects outside our
  `socket()`/`connect()` hooks. Its outbound WebSocket call is scrubbed in place
  in `net_optimizer.cpp` (`ScrubWebSocketTicketsPerCall`,
  `bzrnet_protocol.cpp`) before it reaches ws2_32: `steamAppTicket`,
  `gogAppTicket`, `authTicket` and `platformTicket` string values become
  `"withheld"` (or `""` for a value shorter than that), padded with JSON
  spaces so the frame length and mask key are unchanged. One
  `ticket_withheld sid= key= length=` line is logged per rewrite, never the
  value. Traffic to the official host is never inspected.
- Fail closed: each call must be the HTTP upgrade request or a whole number
  of complete frames (IOCP may re-issue a partial tail, so no state is kept
  across calls). A call that is not, or a text frame that could carry a ticket but
  cannot be rewritten in place (payload split across send calls, fragmented or
  continuation frame, RSV bits / permessage-deflate, over 256 KiB, ticket value
  that is not a string) is not
  sent; the send returns `SOCKET_ERROR` / `WSAECONNABORTED`.
- Needs the socket hooks, i.e. `NetImprovements` on (the same gate as the
  redirect itself); independent of `RelayCapture`.
- The community server therefore sees `withheld` as the ticket and must not
  require a valid platform ticket. The reference `bzrnet_server/server.py`
  skips ticket validation.

### Why not defer auth

Deferring would mean stalling `FUN_006c35c0` until the panel closes:

- Every launch-argument and invite join would hit the 15 s `isNetworkInit`
  timeout and silently drop to the main menu.
- Multiplayer would stay "Not Ready" until the player opened a panel the
  readiness check does not know about.
- The engine already reconnects, so a forced reconnect gets the same result
  through a stock-tested path.

### LAN

Not a toggle. Redux has no standalone LAN mode. The lobby service coordinates
every game, even when gameplay traffic stays on the LAN
(`reverse_engineering/redux_tcpip_lan_multiplayer_investigation_20260713.md`).

A real LAN option means an OpenShim-hosted control plane on the host machine,
found by broadcast, with the security work above. Until then, "LAN" is a Custom
endpoint pointing at a LAN machine running the dev server.

## Phases

1. **Pre-lobby with nickname + flag.**
   - Shell-screen surface (done); the live checks below still apply.
   - Recycle-on-Continue.
   - Acceptance: a second client sees the new name.
2. **Endpoint picker, apply on relaunch.**
   - Official / Custom persisted; `/bzrserver=` or the redirect at launch.
   - Ticket withholding (done; see Security above).
3. **Live endpoint switch.** Host-only redirect + recycle, once live checks 1
   and 6 pass.
4. **LAN-hosted control plane.** Its own design.

## Live checks before implementation

1. Does `getaddrinfo` run again on each reconnect, and what is the retry delay
   (`DAT_0260b0a0`)?
2. After a recycle on the main menu (no lounge), does the lobby come back
   cleanly at state 3, with no stale lounge state?
3. Recycle inside the lounge: what happens to screen `0x0E`, and does `inLounge`
   carry over? This decides whether the in-lobby editor can keep recycling.
4. What starts `Authorization` on the second and later connections, given that
   `client+0x324` is only set in the ctor?
5. Does setting `client+4 = 1` and posting `SendAuthorization` produce a second
   `Authorization` on the same socket, and does the service accept it? This
   would be an alternative to recycling; it is not proposed.
6. Does `/bzrserver=ws://host:port` correctly move the UDP probe to port+1?
7. Does a second client see the renamed player? This is still open from the
   lobby nickname work.
8. How does `-flagfile:` reach `0x00917FAC`?
9. On GOG without a Galaxy sign-in, does the connect never start, and what
   should the panel show then?
