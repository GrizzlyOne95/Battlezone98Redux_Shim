# Host leaving a multiplayer match: fix of 2026-10-27

When the host quits mid-mission in co-op, every AI unit disappears for the
players who stay. With two players, the remaining guest also gets Game Over
half a second later. The HostLeave case of `Run-BZRMpBugs.ps1` reproduces
both.

```
Run-BZRMpBugs.ps1 -Case HostLeave -Clients 2 -Expect Fixed
Run-BZRMpBugs.ps1 -Case HostLeave -Clients 3 -Expect Fixed
```

## Cause (GOG exe 2.2.301)

| Step | Evidence |
| --- | --- |
| The leaver's NetPlayer destructor clears the session's host id first. | `00575BF0`: `session+4 = 0` when it equals the leaver's id (`+0x28`). |
| It then destroys or localizes every object the leaver owned. In co-op the host owns all AI. | Owner check at `00575CDC` (`004B9800` reads `Distributed+0x62`); destroy at `00575D78`, SetLocal at `00575D86`. |
| The new host's takeover never runs, because the host id is already 0. | NotifyNowHost `00578760`: `if (host id != 0) { TakeOwnership(0); TakeOwnership(host id); }`. |
| TakeOwnership on an id that has left does nothing anyway: the player lookup fails. | `004BAAD0` calls `005771B0` at `004BAB2A`. On null it returns. |
| One player left with lives means Game Over (dialog 11). | `Net::Execute` calls `00577D50` at `0057191A`. |

## Fix: `[Fixes] HostLeave` (default on)

`src/patches/mp_host_leave.cpp`. Five hooks, installed together or not at all:

1. **Destructor entry.** If the leaver is the host, the patch remembers its
   id and team. It only does this while the session is in game (state 4).
   NetPlayers freed at teardown or in the lobby arm nothing.
2. **Owner check inside the destructor.** For the leaving host's objects it
   reports owner 0, so they are neither destroyed nor localized. They stay
   as remote copies on every peer.
3. **NotifyNowHost.** After stock runs, the newly elected host runs
   `TakeOwnership(0)` and `TakeOwnership(old host)`.
4. **Player lookup in TakeOwnership.** During that call only, the lookup
   returns a stand-in NetPlayer with the old host's id and team. So
   TakeOwnership does what stock intends: it destroys the leaver's own-team
   units and takes over (SetLocal) everything else, including all AI.
5. **Game Over check.** If "one player left" became true because someone
   left, the patch reports false. Losing on lives still ends the match. The
   suppression clears as soon as two or more players have lives again.

Consequence of 5: in a 2-player deathmatch, the survivor of a leave also gets
no automatic end screen. They keep playing and can quit from the menu.

Off switch: `[Fixes] HostLeave = 0`, or `OPENSHIM_DISABLE_MP_HOST_LEAVE=1`.
The HostLeave case's `-Expect Stock` arm turns it off. Under `-Expect
Fixed`, the case checks that no guest gets dialog 11 or leaves the mission,
and that the host-owned AI still exists after the leave and at the end.

Only patched peers change. An unpatched guest still loses the AI.

## Results

| Run | Finding |
| --- | --- |
| `mpbugs-hl-fixed-1` (2 players) | **Pass**, 21 checks. The host (player 1, team 1) quit. c1 kept 13 of its objects, became host, took them over, and suppressed Game Over. AI craft on c1: 7 before the leave, 7 just after, 7 at the end. The AI kept moving and fighting. |
| `mpbugs-hl3-fixed-1` (3 players) | **Pass**, 35 checks. Both guests kept all 7 AI craft and saw them move and take damage. c1 (player 2) became host and took over. When c1 closed at the end of the run, c2 also kept c1's 8 objects, became host and took them over: migration chains. |
| `mpbugs-hl-stock-1` (`-Expect Stock`, fix off) | **Pass**, 20 checks, 0 failed: with the fix off the stock defect still reproduces, so the fix is what changes the outcome. |
