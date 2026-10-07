# Handoff: co-op PDA controls scenario (real input) + ping key choice

Written 2026-10-07. For the next agent picking up CR co-op PDA testing.

## Goal

Prove the co-op PDA and pings work the way a player uses them, with real key
presses on two real clients, not by calling `CRCoopComms` functions from Lua.
The existing live test only exercises the protocol; this one must exercise
the controls and what each player sees.

Also settle which key pings (see the last section).

## Where things are

| What | Where |
|---|---|
| CR comms/PDA code | `Documents\GIT\Campaign-Reimagined`, branch `agent/coop-comms-pings` (pushed, no PR). `Scripts\CRCoopComms.lua` (protocol), `Scripts\CRCoopPda.lua` (Co-op page), `Scripts\CRCoopPingHud.lua` (markers), `Scripts\PersistentConfig.lua` (PDA, input), design `Docs\COOP_COMMS_PINGS.md` |
| EXU | `Documents\GIT\ExtraUtilities`, branch `agent/coop-comms-pings` (pushed): `exu.GetReticleHit` (70b78a0), camera getter guards (7338d04). Built DLL: `ExtraUtilities\Release\exu.dll` |
| Harness | `Documents\GIT\BZR-OpenShim-coopflow\reverse_engineering`, branch `agent/coop-mission-flow` (pushed). Read `coopflow\README.md` first |
| Existing protocol test | `Campaign-Reimagined\Tools\Test-CoopCommsLive.ps1` (passed live, run `C:\BZRCoop\runs\cr-misn03-comms-1`) |
| CR edit rules | Only the canonical CR checkout; no extra worktrees (CR `AGENTS.md`) |

Build the test content from the CR working tree plus the new EXU each time:

```
powershell -ExecutionPolicy Bypass -File reverse_engineering\New-CRFlowOverride.ps1 -Name coop-comms -Extra C:\Users\iestu\Documents\GIT\ExtraUtilities\Release\exu.dll
powershell -ExecutionPolicy Bypass -Command "& 'reverse_engineering\Run-BZRCoopMission.ps1' -Mission misn03 -Scenario <scenario> -ContentOverride 'reverse_engineering\coopflow\overrides\coop-comms'"
```

## What is and is not covered today

Covered live (Lua calls, `Test-CoopCommsLive.ps1`): host terrain ping reaches
the guest; guest object ping reaches the host; `TargetPing`; `GameKey("J")`
called from Lua sends a terrain ping via `GetReticleHit`; pings expire on both
after 10 s; guest `RequestRescue`, host `Respond` 1 ("Coming") and 2 ("No craft
available"), guest `CancelRescue`.

Not covered (this handoff):

- Opening/closing the PDA with **Y**; opening during co-op should land on the
  Co-op page.
- **[ / ]** page switching; Co-op page present only in co-op.
- **Up/Down** row selection, **Left/Right** changing a row's value (ping kind,
  rescue request, host reply).
- **J** activating the selected row with the PDA open; **J** with the PDA
  closed pinging the reticle target (real key, not `GameKey()` from Lua).
- Suppression: no action during a cinematic, while paused, while dead, after
  the mission result (doc says these contexts suppress actions).
- What the other player sees: the ping marker/label drawn on screen (object
  ping follows the craft; terrain ping with off-screen direction arrow), the
  `DisplayMessage` notices, PDA request/reply status text.
- Not implemented at all, so nothing to test yet: unit ownership transfer,
  automatic craft assignment, AI rescue orders ("Coming" is only a message).
  Design only: CR branch `agent/coop-pda-sharing-design`.

## Scenario to write: `coopflow\scenarios\coop-pda-controls.ps1`

Mission misn03 (start in tanks; misn02b starts on foot). Dot-sourced by the
runner; copy the style of `misn02b-win.ps1`. Every step screenshots both
clients automatically; assert from state, keep the shots as visual evidence.

Input: `Send-CRFlowKey <client> <vk>` posts WM_ACTIVATE + key down/up to that
client's window (it worked for Space skips). VKs: Y 0x59, J 0x4A, [ 0xDB,
] 0xDD, Up 0x26, Down 0x28, Left 0x25, Right 0x27, Esc 0x1B.

**First, prove the input path** (one small step): press Y on the host and
check that the PDA opened (read PersistentConfig's PDA state through the probe,
e.g. `package.loaded.PersistentConfig`; find the open/page fields in
`PersistentConfig.lua`). If posted keys do not reach the PDA (it may poll a
raw input state that posted messages do not set), report that before writing
the rest: the fix is either a different send method in
`BZRWindowInput.ps1` (SendInput needs the window focused) or a probe hook.

Then, per client where it matters:

1. Y opens the PDA on the Co-op page (page number from
   `CoopPda.PageNumber`); Y again closes it.
2. [ and ] walk the pages and wrap; the Co-op page is reachable both ways.
3. Up/Down move the selected row; Left/Right change the selected value; read
   the selection back from the PDA state after every key.
4. Guest: select "ping", aim at its own position or a known object (use the
   probe to face a target, `put`/`tp` own craft only), press J. Host: the
   ping exists (`CRCoop.GetComms().GetPings()`) and the HUD has a live marker
   for it (`CRCoopPingHud` state; find what it stores per marker). Screenshot
   the host: the marker should be visible.
5. PDA closed, host presses J with the reticle on terrain, then on an object:
   correct kinds arrive on the guest. Point the craft at the ground with the
   probe first; `exu.GetReticleHit()` tells you what the reticle sees.
6. Rescue through the UI: guest hops out (`HopOut(GetPlayerHandle())` is fine
   as setup), opens the PDA, selects rescue, J. Host's PDA shows the request;
   host selects "Coming" with Left/Right and J; guest sees the status and the
   DisplayMessage. Then "No craft available". Then guest cancels via the PDA.
7. Suppression: start a film on the host (`native.CameraReady()` plus a
   `CameraPath` task, as `film-preview.ps1` does) and press J: no ping. Same
   after the mission result if practical.
8. Cooldown: two J presses inside 1.5 s send one ping.

`$script:CRFlowSkipParity = $true` (target selection is local by design).

## Ping key: J now; Q or middle mouse?

Stock bindings (`input.map` in the game root):

- **Middle mouse = `weapon_special`** (fire special weapon; LeftShift is the
  alternate). Not usable: every ping would also fire.
- **Q = `throttle_up`** (digital throttle forward, a step). A quick tap nudges
  the throttle; most players use the mouse/analog throttle, so likely
  harmless. Unknown: whether the mission's `GameKey` callback even fires for
  a key the engine binds. J and X are the only stock-unbound letters (X is
  ISDFC reload, J is ISDFC locker take; J is fine in co-op missions).

Test before switching: in the PDA scenario, press Q on the host and check
(a) a ping is sent (GameKey received it), (b) how much the throttle changed
(`GetVelocity`/speed before and after, craft parked). If (a) fails, Q is out
without rebinding. Making the key configurable (PDA settings) is the safest
answer either way.

## Environment rules learned the hard way

- Never launch while the user's own game runs; test clients live only in
  `C:\BZRCoop\instances` (force-kill those is fine; never the main GOG/Steam
  game without asking).
- Watch every run (Monitor on the run log, plus a stall check); a dead client
  now fails the run within a second. Do not wait on a hung client.
- Clients need audio (summary warns "audio available"); without it every
  voice-over is instantly "done" and films end on frame one.
- Client size follows the user's display (584x720 RDP, 624x393 phone); the
  lobby script scales for it. Do not resize client windows (Codex's
  `Test-CoopCommsLive.ps1` step 2 does `SetWindowPos` 1296x759; avoid copying
  that, it persisted and broke later lobby runs).
- PowerShell names ignore case: never use `$h`/`$g` in scenarios (`$H`/`$G`
  are the client indexes).
- Never dot-source `BZRHarness.ps1` from a scenario (launch-lock deadlock).
- Never name a path `player_path` in a co-op map (engine spawns a stray
  team-0 tank there).
- Commit on `agent/*` branches only; PRs/merges need the user.
