# Lobby websocket drop ends a healthy match — 2026-10-26

GOG 2.2.301 (`battlezone98redux.exe`, image base 0x00400000).
Patch: `src/patches/lobby_drop_keeps_match.cpp`, `[Network] LobbyDropKeepsMatch`
(default **on**). Sites registered in `scripts/patches.json` / `include/patches.h`
as `Lobby Drop Keeps Match Local` and `Lobby Drop Keeps Match Remote`; both
signatures and all seven helper resolves are unique in the shipped image.

## Field report

A player's PC with two adapters on one LAN lost its lobby websocket mid-mission
(`1006 Underlying Transport Error`). P2P UDP to the host was still flowing.
BZLogger, all in one frame:

```
BZRNetInterface reset active_con due to websocket connection close, remote 1006 , local 1006 Underlying Transport Error, reset Yes
DoNextFrame: Quiting Game Due to Net Execute failure
```

The chat showed "Lost connection to game". The websocket reconnected 46 ms later,
but the match was already gone.

## Local path (the client whose websocket dropped)

| Address | Role |
|---|---|
| `0x006BF0D0` | websocket close handler. Logs the line above, then, when a lobby is current (`this+0xC38`), calls the leave-lobby cleanup. **Site Local**: the `E8` at `0x006BF11B`. |
| `0x0074D250` | leave-lobby cleanup, `__thiscall(lobby)`, no stack args. It tears down the P2P session (`0x0075CEA0`), calls player-left for the local id (`0x00578640(&localId, 0)`), then resets the lobby UI state. |
| `0x00578640` | player-left, `cdecl(const NetId*, bool kicked)`. It calls FindPlayer `0x00577200`. For the local player (`Player+0x8E`) it stamps `NetManager+0x868` and calls `0x00570460`, which sets Net state (`[0x00917F48]+8`) to 5. For any other player it prints player_left / host_autokicked and removes them. |
| `0x005715D0` | Net Execute. Jump table on Net state: states 0, 5 and 6 return 0. |
| `0x00618130` | DoNextFrame. If Net Execute returns 0, game state `0x00434160` is not 2, and game-ended `0x00572A80` is false, it logs the quit (`push 0x0088B5B0` at `0x0061819C`), shows `multi_error/game_lost` and sets game state 2. |

So the websocket loss alone sets Net state 5, and the next frame quits.

The same call also queues both lobby-exit messages, which go out ahead of the
reconnect:

- **DoExitLobby:** `0x0074D250` → `CNetGameLobby::ExitLobby` `0x00740A90` →
  `.?AVBZRNetLobby@@` vtable (`0x0089ADDC`) slot +0x5C = `0x0074C290` → the send
  at `0x006C5760` (string `DoExitLobby`, push at `0x006C57E4`).
- **DoExitLounge:** `0x0074D250` → `CNetGameLobby::ExitLounge` `0x0073DDF0` →
  `0x00765C30` → the send at `0x006C65B0` (push at `0x006C6641`).

Neither sender has any other caller on the close path, so skipping
`0x0074D250` suppresses both messages.

## Remote path (everyone else)

The server unregisters the dropped session and broadcasts a lobby member-left
update. DedicatedServer `unregister()` calls `remove_from_lobby` on ws close; the
duplicate-login supersede work does the same on reconnect.
`CNetGameLobby::OnLobbyChatUpdate` `0x0073EEB0` then calls player-left for that
member (**Site Remote**: the `E8` at `0x0073F13F`, `cdecl(member, kicked||banned)`).
The other clients drop a player whose P2P is still live.

## Real P2P loss still ends the session

The ping check `0x00576B70` is unchanged. Every client runs it from Net
Execute (`0x005718C7`) once per NetManager+0x430 ms. That interval starts low
and grows by 10 ms per ping up to 3000 ms (`0x0057188F`).

- Each run pings every remote player over P2P (`0x00576480`, message `PP`) and shifts `Player+0x1B0` left. The reply handler sets bit 0 (`0x00572368`). `0x00575FF0` turns the low 10 bits into a loss figure: 100 minus 10 per answered ping.
- `Player+0x40` is **not** a last-heard time. It is stamped once, on first contact (`0x00576923`: only when zero). The 2026-10-26 harness run read it as 12 s stale on a healthy link, which was the time since launch.
- A player is lagging once `now > +0x40 + 10000` (`0x008E8D0C`) and the ping metrics are bad (average RTT `0x00575F80` > 1000 ms `0x008E8CF8`, or loss > 50 `0x008E8BFC`).
- The host (`0x00572A60`) auto-kicks after another 10000 ms of lagging (`0x008E8CE4`; "Auto kicking player ... due to ping failure", `0x00576A70`).

## Patch

`InMatch` means all of the following:

- the NetManager exists;
- Net state is 4 (in session);
- game state is 5 (mission running);
- game-ended is false.

A player is *live* when bit 0 or 1 of `Player+0x1B0` is set, meaning one of
the last two pings was answered (about 6 s at the 3000 ms cap).

**Local site:** when `InMatch` holds and at least one non-local player is live,
the hook skips `0x0074D250`. Both the P2P session and the Net
state survive, and the websocket reconnects as stock. With no live peer, the
stock leave runs and the match quits as before.

**Remote site:** when `InMatch` holds, the departure is not a kick or ban, and
the player is non-local and live, the hook skips
`0x00578640`. A player whose P2P really died is still removed by the host's
ping check.

Both hooks check that the stock call target matches its resolve before
redirecting, and log `[LOBBYDROP]` at each decision.

## Limitations

- Server side: DedicatedServer PR #16 (`agent/supersede-duplicate-login`) lets
  a same-PC reconnect take over the old session's lobby seat. It sends no
  member-removed message. Because the client sent no DoExitLobby/DoExitLounge,
  it is still a member of its game lobby after re-auth. Without PR #16, the
  server suffixes the id and drops the old seat once keepalive times out
  (20–50 s). The remote hook keeps the player in the match through that drop,
  but the client is then no longer a server-side lobby member, and the skipped
  leave is never replayed.
- If the host's websocket drops, the server may migrate lobby ownership. That
  case is out of scope here.

## Ping re-check for held leaves (2026-11-23)

Player report: the host quit through the menu, and the guest kept the host in
its player count for the rest of the match (units gone, player still listed).
The guest's log showed three `[LOBBYDROP] ... kept in the match` lines with
`replies=0x3FF`. A deliberate quitter answered the last pings before leaving,
so the Remote site skipped `PlayerLeft` and nothing ever replayed it. The
ping check's own auto-kick only runs on the host (gate `FUN_00572a60`), and
here the leaver was the host.

Citations (GOG exe, Ghidra `/battlezone98redux.exe-007c64`):

- `Net::Execute` `0x005715D0` calls the ping check `0x00576B70` at
  `0x005718C7` (only caller, `list_cross_references`). The call sits inside
  the `NetManager+0x430` ms interval block, behind `local id != 0`, so it runs
  on every peer, not just the host. Bytes at `0x005718A8`:
  `55b0898a30040000 8b45b08b4dac898828040000 0fb715d4809100 85d27405 e8a4520000`.
- Ping send `0x00576480` shifts `Player+0x1B0` left one bit per ping. A reply
  sets bit 0, so `replies & 3` = "answered one of the last two pings".
- NetId is 16 bytes: compare `0x0056F780` reads dwords 0, 2 and 3, and
  FindPlayer's `0x00577200` map node holds the value at `+0x10`.
- `PlayerLeft` `0x00578640` removes through `0x00576710` -> `0x005715A0`.

Fix: the new REL32 site "Lobby Drop Keeps Match Ping" wraps that call. A
Remote leave that is held back is recorded (NetId copy) and looked at again
before each stock ping check. After 3 checks with `replies & 3 == 0`, the
stock `PlayerLeft(id, 0)` runs and logs `stopped answering ... dropping it
now`. A player still answering after 20 checks is released from the table
and stays, which is the old lobby-only-drop behaviour. With no Ping hook,
nothing is held and the leave takes the stock drop.
