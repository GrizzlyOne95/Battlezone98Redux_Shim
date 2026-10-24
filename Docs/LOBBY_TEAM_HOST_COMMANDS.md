# Lobby /team, /swap and /host commands

Status: **prototype, not live-tested.** The engine addresses and argument
order come from static analysis of the GOG executable. Nothing has run in a
real lobby yet.

## Why

The stock pre-game lobby numbers teams for you. The owner gives each new
member the lowest team number nobody holds (`CNetGameLobby` user populate,
`0x00744A50`), so join order sets the teams and the first player in is always
the host. Stock offers no command to change either.

The engine already has both operations a host needs:

| Native | Address | What it does |
|---|---|---|
| `CNetGameLobby::AssignTeam(cUser*, int team)` | `0x007468B0` | Owner only; team 1–15. For the host's own row it calls `SetPlayerData team/miniid`. For anyone else it sends the lobby chat message `AT~<id>~<team>~<miniid>`, which that client turns into its own metadata (`OnChatMessage`, `0x0073F460`). |
| lobby vtable `+0x6C` `SetLobbyOwner(LobbyId*, UserId*)` | BZRNet `0x0074B9F0` | Sends the websocket message `DoSetLobbyOwner`. Stock calls it only to hand ownership back during `PopulateLobbyFromData` (`0x0074423F`). |

`src/patches/lobby_team_commands.cpp` calls these through the same
multiplayer command hook that already serves `/help`, `/nickname` and
`/ban`. It never writes team or owner state itself.

## Commands

The *selected player* is the row selected in the lobby player list. It is
the same target the K/M/B buttons use.

| Command | Effect |
|---|---|
| `/team <1-15>` | Move the selected player to that team. |
| `/team <name> <1-15>` | Move the named player. The name is matched exactly first, then as a unique prefix, ignoring case. |
| `/swap <a> <b>` | Swap whoever holds team *a* with whoever holds team *b*. If one side is empty, this is a plain move. |
| `/host` / `/host <name>` | Ask the lobby service to make that player the owner. |

`/team` refuses a team someone else already holds and points you to `/swap`.
All three commands refuse, with a chat-log line, in these cases:

- the caller is not the lobby owner;
- the screen is not the shell, or the pause menu is open;
- the live lobby is not a `BZRNetLobby`;
- any guarded engine row fails to bind.

Every action also logs a `[LOBBY]` line to the OpenShim log.

## Fail-closed guards

`scripts/patches.json` `engine_addresses` gives each call and struct offset
its own guarded row, on an instruction that uses it:

- `BzrNetGetLobby`, `BzrNetLobbyVtable`: the live lobby, which must be BZRNet.
- `BzrNetLobbySetLobbyOwner`: the live vtable slot `+0x6C` must hold this address.
- `NetGameLobbyIsOwner`, `NetGameLobbyFindRecord`, `NetGameLobbyAssignTeam`: the calls.
- `NetGameLobbyFindRecordIdCompare`: the record's lobby id at `+0x10`.
- `NetGameLobbyAssignTeamRange`: the 1..15 team range.
- `NetGameLobbyMemberListRead`: the `std::list<cUser>` at record `+0xB8`.
- `NetGameLobbyMemberTeamRead`: the team at cUser `+0x80`.
- `NetGameLobbyMemberLog`: miniid `+0x28`, team `+0x80` and name `+0x2C`, all
  pinned by the stock "Player %s set to Team" log.
- `NetGameLobbyOwnerRestore`: user id `+0x08` and the `SetLobbyOwner` argument order.

If any row misses, the whole feature stands down and the command prints
"unavailable on this game build".

## Open questions the live test must answer

1. **Does the shell gate hold?** In the pre-game lobby, `ReadShellUiState()`
   must report `wrapperActive`. If it does not, every command refuses with
   "works only in the pre-game lobby". That fails safe, but the gate is
   then wrong.
2. **Does a re-team stick?** If the target already has a miniid, AssignTeam
   does not write cUser `+0x80` locally. The change only lands once the
   target client sees the `AT~` message and republishes its `team` metadata.
   Check that:
   - the target accepts an `AT~` for a player that already has a team;
   - every peer's list then shows the new number;
   - the host's own lowest-free pass does not undo it.
3. **Does the receiver check the `AT~` sender?** If any client honours an
   `AT~` from a non-owner, that is a pre-existing stock weakness. These
   commands neither add to it nor depend on it, but record the answer.
4. **Does Rebellion's server honour `DoSetLobbyOwner`?** This is the big
   unknown for `/host`. The local `bzrnet_server` honours it, but that is our
   own clean-room code and proves nothing about Rebellion's server.
5. **Does the launch follow the new host?** After `/host`, the new owner must
   be able to change the map and start the game, and the old owner must lose
   those controls.

## Two-client BZRNet test plan

Both clients run this branch's DLL **and** its `scripts/patches.json`; deploy
with `scripts/Deploy-OpenShim.ps1`. Launch through
`reverse_engineering/BZRHarness.ps1` with `BZR_FORCE_WINDOWED=1`. Stop with
`Stop-BZRGame -Id`, never a force kill. Snapshot `logs\` before every launch.

Two Redux instances on one machine share Steam/GOG identity and the harness
launch lock, so use two machines: this workstation and a second PC with the
GOG install, as clients **A** and **B**.

### Phase 1: local control plane (deterministic)

1. On A, run `python reverse_engineering/bzrnet_server/server.py`, bound to
   an address B can reach. The server binds to loopback by default; never
   expose it beyond the LAN.
2. On both clients set `[OpenShimSocket] MatchmakingRedirectAddress=<A's LAN address>`.
3. A creates a lobby and B joins. Expect A = team 1 (host) and B = team 2.
4. `/help` on A: the three new lines appear.
5. **Refusals.** On B (not the owner), `/team 3` must print "only the lobby
   host". On A:
   - `/team 16`, `/swap 2 2` and `/team Nobody 3` each print usage or "no player named".
   - `/team 2` with A selected prints "Team 2 belongs to …".
6. **Move.** On A, select B and send `/team 5`. Expect:
   - A's log has `[LOBBY] AssignTeam … team 2 -> 5`;
   - B's log has stock "Assigned Team";
   - both lists show B on 5 within a few seconds;
   - it stays 5 after a third chat message and after toggling ready.
7. **Swap.** `/swap 1 5` makes A team 5 and B team 1, on both screens.
   Launch a deathmatch and check that each player spawns on their new team
   (team colour and start spot).
8. **Host.** Back in a fresh lobby, A sends `/host B`. Expect:
   - A's log has `SetLobbyOwner … result=1`;
   - the server log shows the owner change;
   - B gains the host controls (map, launch, `/kick`) and A loses them;
   - B can run `/team` and A gets "only the lobby host".
9. **Rejoin edge.** B leaves and rejoins after a swap. Record which team
   it gets back.

### Phase 2: Rebellion's live service

Remove `MatchmakingRedirectAddress` on both clients and repeat steps 3–8.
Use a passworded or locked lobby (`/lock` once B is in) so strangers do not
join. Record whether step 8's owner change happens. If the service ignores
`DoSetLobbyOwner`, `/host` still prints "Asked the server…" but nothing
changes. In that case, change the message to say the service declined, or
drop `/host` on BZRNet.

### Evidence to keep

For each client, keep:

- the OpenShim log `[LOBBY]` and `[ADDR]` lines;
- the stock log "Assigned Player"/"Assigned Team"/"set to Team" lines;
- one screenshot per step showing both player lists.

No binaries, dumps or decompiler output go into this public repository.
