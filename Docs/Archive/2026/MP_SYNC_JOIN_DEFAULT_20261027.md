# Sync Join on by default: `[Fixes] SyncJoinDefaultOn`

A player who joins a game already in progress loads the mission's BZN fresh
and pushes its own starting units to the host. That duplicates them and
desyncs the game. Sync Join prevents it: once the game starts, the lobby is
locked. Stock defaults Sync Join to on, but the lobby toggle saves its last
value to multi.ini (`[multi] syncJoin`). A host who turned it off once hosts
every later game unlocked.

## Engine (GOG 2.2.301)

| Site | Role |
| --- | --- |
| `0x00742090` | Game-info loader, called for each new hosted lobby (`0x007436C0`, from `CNetGameLobby::OnLobbyCreated` `0x0073DF60`). It reads `syncJoin` (default `"1"`, `0x00873EF0`) and stores 1 if the value starts with `'1'`, else the immediate 0 at `0x0074216E`, into game-info `+0x114`. |
| `0x0079B880` | Lobby toggle: flips `+0x114` and writes multi.ini. |
| `0x00742DF0` | At launch, reads `+0x114` and locks the lobby through backend vtable `+0x34` (Steam `0x00750BD0`, Galaxy `0x0074DF20`, BZRNet `0x0074B540`). |

## Patch

`Sync Join Default On` in `scripts/patches.json` writes `01` over the else
arm's immediate (`0x0074216E`). Every new lobby starts with Sync Join on, and
the host can still turn it off for that game. Off switch:
`[Fixes] SyncJoinDefaultOn = 0` or `OPENSHIM_DISABLE_SYNC_JOIN_DEFAULT_ON=1`.

## Verification

In both runs the host instance had `syncJoin = 0` saved in multi.ini. The
co-op lobby script logs the value the host advertises in `gameSettings`
(field 4) before it clicks anything.

| Run | Patch | Advertised |
| --- | --- | --- |
| `mpbugs-syncjoin-default-1` | not applied (name not registered yet) | `syncJoin=0` |
| `mpbugs-syncjoin-default-4` | applied (`wrote 1 bytes to 0x0074216E`) | `syncJoin=1`; multi.ini still `0` afterwards, so no toggle was clicked. MissionEnd flow passed 19/19. |
