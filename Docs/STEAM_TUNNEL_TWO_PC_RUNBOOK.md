# Steam tunnel: two-PC runbook for the open Join Game checks

Closes the items still marked UNVERIFIED in
[STEAM_TUNNEL.md, Steam invite / Join Game](STEAM_TUNNEL.md#steam-invite--join-game).
Written so a Claude session on each PC can run its side. Each step has a host
part (PC 1) and a joiner part (PC 2). The basic friend join and the passworded
invite already passed live on 2026-11-08; this runbook does not repeat them.

## Roles and rules

| Role | PC | Needs |
|---|---|---|
| Host | PC 1, Steam account A | Steam BZR with OpenShim from `main`, server via `./tools/socket_tunnel/start_host.ps1 -InGameBridge`, game on `Server = Custom`, `CustomServer = 127.0.0.2` |
| Joiner | PC 2, Steam account B (A's Steam friend) | Steam BZR with OpenShim from `main`; `net.ini` with no `TunnelUdpBridge` and no `SteamTunnelHost` |

- Both PCs: before launching, take the live-test lock and run the launch
  safety check if the harness is installed there; release it in cleanup.
- Evidence comes from `logs\openshim.log` in each game folder (component
  `TUNNELJOIN`, bridge tag `[SteamBridge]`). Copy the log after every step
  before relaunching; a relaunch truncates it.
- Steam UI checks (friends list, invite Accept, Join Game) use computer use:
  screenshot, then click. A person approves app access once per PC at the
  start and handles any Steam sign-in or Steam Guard prompt. Leave both PCs
  alone during the run.
- Sync points are marked **SYNC**. If both sessions run under one Claude
  account with Remote Control, they message each other. Otherwise the two
  people relay "ready" / "done" by voice or chat, and each session waits for
  its person to say so.
- Cap retries at 2 per step, then record FAIL with the logs and move on.

## 0. Host up (PC 1)

1. Start the server with `start_host.ps1 -InGameBridge`, launch BZR from Steam
   and stay in the main menus (not in a lobby).
2. Pass: the log shows `[SteamBridge]` running, then
   `advertising tunnel bridge <SteamID> in Steam presence` and
   `no lobby advertised: Join Game opens this server's lounge`.
   If it shows `own presence not readable yet; lounge Join Game waits` and
   never the lounge line, record it: steps 2 and 5 then cannot pass.
3. **SYNC**: host ready, with A's SteamID64.

## 1. Rich presence read on first join (PC 2)

Tests: does `GetFriendRichPresence` return A's keys at callback time with no
prior `RequestFriendRichPresence`?

1. Launch BZR fresh from Steam (menus only; no earlier join this session).
2. Trigger the join (same callback as the friends-list button):
   `Start-Process 'steam://rungame/301650/<A SteamID64>/-openshim-steam-tunnel'`.
3. Pass: `join request from <A> (lounge): tunnel presence <bridge SteamID>, target <bridge SteamID>`
   followed by `tunnel now <bridge SteamID>; BZRNet reconnect ...`, and the
   game lands in the host server's lounge (screenshot).
   Fail: `tunnel presence none`.
4. Quit to the main menu. **SYNC**: done.

## 2. Join Game button visible (PC 2)

1. Host stays in the menus (lounge advertised).
2. Joiner opens the Steam friends list, opens A's entry menu and screenshots it.
3. Pass: a Join Game entry is present. Click it; expect
   `join request from <A> (lounge): tunnel presence <id>, ...` (not `none`).
   No `tunnel now` line follows: the tunnel already points at A's bridge
   since step 1, and a same-host join returns without logging.
4. Return to the main menu. **SYNC**: done.

## 3. Pending stock-lobby join survives the BZRNet recycle

1. Host (PC 1): create a public (not passworded) stock lobby; stay in it.
   Send a Steam invite to B from the in-game invite.
2. Joiner (PC 2): exit BZR fully and relaunch it from Steam, so the tunnel is
   back on the startup config (a join to the host it already points at
   switches nothing and logs no `tunnel now`). Open the Multiplayer screen so
   a BZRNet socket is open, then click Accept on the Steam invite.
3. Pass, joiner log: `join request from <A> (lobby): tunnel presence <id>, ...`,
   then `tunnel now <id>; BZRNet reconnect started` (`not needed (no socket
   open)` means the recycle was not exercised: retry from the Multiplayer
   screen), then the joiner reaches
   A's lobby (screenshot) within 30 s. Host screenshot lists both players.
   Fail: joiner stays on "gathering information from the server", or lands
   in the lounge instead of the lobby.
4. Both leave the lobby to the main menus. **SYNC**: done.

## 4. Join Game does not flap

1. Host (PC 1), about 5 minutes: menus 60 s, create lobby 60 s, leave to
   menus 60 s, create lobby 60 s, leave to menus.
2. Joiner (PC 2): screenshot A's friends-list entry every 30 s and note
   whether Join Game is shown.
3. Pass: the joiner's screenshots show Join Game in every menus window and
   no flicker within a window. The screenshots are the only evidence for the
   `connect` key: OpenShim sets and clears it without logging. The host log
   covers only the `openshim_tunnel` key: at most one
   `tunnel presence was cleared; re-advertising` per menu/lobby change and no
   repeated `SetRichPresence failed; retrying`. Record the screenshot
   timeline either way.
4. **SYNC**: done.

## 5. Cold launch from Join Game (PC 2)

The source says how a launch with the lounge token on the command line behaves
is UNVERIFIED (`steam_tunnel_join.cpp`, header comment). This step records what
happens; it has no fixed pass line yet.

1. Host in the menus (lounge advertised). Joiner: exit BZR fully.
2. Joiner: click Join Game on A in the Steam friends list; Steam starts BZR.
3. Record: does the game start; does the log contain any `join request`
   line; where does the game end up after 60 s (screenshot); any crash dump.
4. Return to the main menu. **SYNC**: done.

## 6. Join request during a mission (PC 2)

Expected by design: no switch, no crash.

1. Joiner: start any Instant Action mission and stay in it.
2. Trigger the join with the step 1 `steam://rungame` command.
3. Pass: `join request from <A> (lounge): ...` then
   `in a mission: tunnel not switched; join from the menus`. The lounge token
   never reaches the stock join handler, so nothing else should happen. The mission
   keeps running for 60 s, and no crash dump.
4. Quit the mission, then trigger the join again from the menus: it should
   now pass as in step 1.

## Cleanup and report

- Both: exit the game, stop the host server, release the lock.
- Fill this table and attach both `openshim.log` copies per step and the
  screenshots to the PR or issue. Then update the UNVERIFIED list in
  [STEAM_TUNNEL.md](STEAM_TUNNEL.md) with the date and result.

| Step | Item | Result | Evidence |
|---|---|---|---|
| 1 | Presence read on first join | | |
| 2 | Join Game button visible | | |
| 3 | Pending lobby join survives recycle | | |
| 4 | No Join Game flapping | | |
| 5 | Cold launch from Join Game | (record) | |
| 6 | Join during a mission | | |
