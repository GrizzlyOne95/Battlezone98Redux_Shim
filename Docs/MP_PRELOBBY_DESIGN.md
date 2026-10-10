# Multiplayer pre-lobby: design

Status: **design only, nothing implemented.** Static RE for the GOG build
(sha256 `8d71f56c…3377413`, byte-identical to the decompile corpus). The live
checks listed at the end have not run.

## Summary

Battlezone 1.5 went **Main menu → transport/character screen → lobby**. Redux
goes **Main menu → lobby**. The proposal is to put a 1.5-style pre-lobby back in
front of the Redux lobby. The player sets a nickname and flag there, and picks
**Official**, **Custom server** or (later) **LAN**. Continue applies the choices
and then runs the stock Multiplayer path.

Two decisions follow from the RE below:

1. **The pre-lobby is an in-place MainScreen surface, not a new shell screen.**
   The shell factory is a closed switch. Redux already does in-place modes for
   Credits and Intro (`reverse_engineering/REDUX_SHELL_UI_GATE_STATUS.md`).
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

1. Hook `Click_MultiPlayer` (`FUN_0078c6c0`) behind a setting. The hook only
   decides whether to show the panel; the stock body still runs on Continue.
2. Show the panel as an in-place MainScreen mode: hide the stock central
   controls, and build the panel's widgets under `MainScreen_Overlay`.
3. Follow the documented injection rules:
   - Keep plates input-transparent (`+0xE9`).
   - Both callback slots on every active button, never on `cUI_Text` /
     `cUI_TextEntry`.
   - Blank text instead of relying on `SetActive`.
   - Build at screen setup.
   - Validate widgets with `IsWidgetLiveChildOfParent`.
   - Hold no widget pointers across a MainScreen generation (singleton
     `0x0094551C`).
4. Reuse rather than rebuild:
   - The nickname row is `CreateNicknameAndRouteWidgets` with its `AppendChar`
     focus path.
   - The flag pair is `CreateFlagButtonCommon` / `CycleSelectedFlag`.
   - Both currently live in `lobby_ui.cpp` and are parented to the lobby.
5. The panel shows:
   - nickname entry
   - flag `<` / preview / `>`
   - endpoint selector: Official, Custom (host[:port], recent list), LAN
     (disabled until phase 4)
   - a status line: platform, auth state (`client+4`), current endpoint
   - Back and Continue
6. **Continue:**
   1. Persist.
   2. If the nickname or endpoint changed and the client is authorised (state
      3): set the new name or endpoint, recycle the websocket (the existing
      `RecycleBzrNetWebSocket`), and show "Connecting…" until state 3 returns.
   3. Call the original `Click_MultiPlayer`. Its `isNetworkInit` check is the
      gate, so a failed reconnect leaves the player on the panel with the stock
      "Not Ready" state, not in a half-built lobby.
7. **Back:** restore the stock controls. Changes are kept only if applied.

The existing in-lobby nickname editor can stay. Its recycle runs while a lounge
is registered, which is the unknown case above. Once the pre-lobby exists, it
should point the player to the pre-lobby rather than recycle in place.

### Endpoint switching

The redirect at `getaddrinfo` swaps the **host** only. The URL, its port (1337)
and the path come from `client+0xC`.

**Runtime switch, host only:**
1. Update the redirect target.
2. Recycle the websocket.
3. The reconnect resolves the new host.

This depends on the reconnect calling `getaddrinfo` again (live check 1).

**A different port or path** needs `client+0xC` rewritten. That is an MSVC
`std::string` inside the client object, owned by the game's CRT. Writing it
from OpenShim means matching that layout and allocator exactly, which is the
`StableId`/`BzrString` overlay mistake waiting to happen. **Do not do this in
the first version.** For non-default ports, persist the endpoint and apply it
as `/bzrserver=` on the next launch, with OpenShim offering a relaunch.

**Security: the platform ticket goes to whatever server you choose.** The
`Authorization` body carries the Steam/Galaxy ticket, and a custom server
receives it. A malicious server could try to replay it against Rebellion's
service while it is still valid.

- The UI must label Custom as "sends your platform login ticket to this server".
- The reference `bzrnet_server/server.py` skips ticket validation. It stays
  LAN/dev only until it validates tickets.
- Whether a custom endpoint should send a ticket at all, or an
  OpenShim-specific auth type, is a decision for the community-server
  workstream.

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

## Phase 1 implementation notes

What the shipped surface had to account for, found while building it on GOG
2.2.301:

- **`Click_MultiPlayer` is `__thiscall`.** `this` is the MainScreen singleton
  (`0x0094551C`). It decompiles as `void(void)`, but it saves `ecx` and
  requests screen `0x0E` through `[this+0x138]`, and the button wrapper
  `0x0078C550` loads `ecx` from the singleton. Treated as `__cdecl`, the request
  went to whatever `ecx` held and the lobby never opened. The detour is
  `__fastcall(this)`, and Continue passes the live singleton.
- **The "Not Ready" state disables the button, not the click handler.** The
  MP-status refresh (`0x0078EB50`) sets the Multiplayer button's enabled byte to
  0 every frame until BZRNet authorises, so a click never reaches
  `Click_MultiPlayer`. The pre-lobby must open in exactly that state, because
  that is where the player waits for sign-in. The refresh's single call site
  (`0x0078EB30`, `MainScreenMpStatusRefreshCall` in `scripts/patches.json`) is
  redirected: the stock refresh runs first, then the button is re-enabled
  while the page is closed. With `PreLobby` off the page is never built, and the
  stock lock-out is unchanged.
- **Typing.** The title screen never forwards characters to a text entry. The
  nickname edit takes them through MainScreen vtable slot 2 (the base
  `cUI_View` char dispatcher). Esc closes the page from the same hook.
- **`/nointro` skips the surface.** With `/nointro` the MainScreen setup at
  `0x0078D000` is not reached, so the Career tab and the pre-lobby are not
  injected, and Multiplayer behaves as stock. Test without it.
- **Flag preview is blank on DX11.** The `[DX11COMPAT]` filter skips the
  shaderless `openshim_flagprev_*` material, which the lobby flag picker also
  uses. This predates the pre-lobby. The flag choice itself still applies.
- **Live check 2 passed.** A rename on the title screen recycles the socket.
  The client reconnects, re-authorises, and Continue reaches the lounge (screen
  `0x0E`) in about 0.6 s, with no stale lounge state.
- **Live check 7 passed: a second client sees the new name.** Two Goldberg
  clients against the local BZRNet server, 2026-10-10. Client 2 waited in the
  lounge, and client 1 renamed to `PreLobbyOK` on the pre-lobby and pressed
  Continue. The server logged `Authorized ... name=PreLobbyOK`, and client 2's
  Players in Room list showed `PreLobbyOK`.
- **Two misleading readouts.** After the recycle, client 1's BZLogger still
  printed `Authenticated to BZRNet As <id>:BZRCoop1`, so that line is not the
  name the server received. Use the server's `Authorized` line or a second
  client to check a rename. The page's status line also reads
  `Server: Official` while `MatchmakingRedirectAddress` points elsewhere. The
  phase 2 endpoint work should report the redirect target.

## Phases

1. **Pre-lobby with nickname + flag.**
   - Main-menu surface: needs the open `MainScreen_Overlay` hit-test/z-order
     gate from `REDUX_SHELL_UI_GATE_STATUS.md` passed live first.
   - Recycle-on-Continue.
   - Acceptance: a second client sees the new name.
2. **Endpoint picker, apply on relaunch.**
   - Official / Custom persisted; `/bzrserver=` or the redirect at launch.
   - Ticket warning.
3. **Live endpoint switch.** Host-only redirect + recycle, once live checks 1
   and 6 pass.
4. **LAN-hosted control plane.** Its own design.

## Live checks before implementation

1. Does `getaddrinfo` run again on each reconnect, and what is the retry delay
   (`DAT_0260b0a0`)?
2. After a recycle on the main menu (no lounge), does the lobby come back
   cleanly at state 3, with no stale lounge state? **Yes** (phase 1 notes).
3. Recycle inside the lounge: what happens to screen `0x0E`, and does `inLounge`
   carry over? This decides whether the in-lobby editor can keep recycling.
4. What starts `Authorization` on the second and later connections, given that
   `client+0x324` is only set in the ctor?
5. Does setting `client+4 = 1` and posting `SendAuthorization` produce a second
   `Authorization` on the same socket, and does the service accept it? This
   would be an alternative to recycling; it is not proposed.
6. Does `/bzrserver=ws://host:port` correctly move the UDP probe to port+1?
7. Does a second client see the renamed player? This is still open from the
   lobby nickname work. **Yes** for a rename on the pre-lobby (phase 1 notes).
8. How does `-flagfile:` reach `0x00917FAC`?
9. On GOG without a Galaxy sign-in, does the connect never start, and what
   should the panel show then?
