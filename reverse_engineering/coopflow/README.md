# Co-op mission flow tests (Campaign Reimagined)

Two real Redux clients on this PC play a CR co-op mission against a private
loopback lobby server. A probe inside each client's mission script lets the
harness read state and act like a player; every step is checked on both the
host (authority) and the guest.

This exercises mission mechanics (gates, objectives, films, results,
replication), not real combat: scenarios kill enemies, pull timers forward
and teleport craft through the probe.

## Run

Windows PowerShell 5.1, from the repository root. Refuses to start while any
`battlezone98redux` is running.

```
powershell -ExecutionPolicy Bypass -File reverse_engineering\Run-BZRCoopMission.ps1 -Mission misn03 -Scenario win
powershell -ExecutionPolicy Bypass -File reverse_engineering\Run-BZRCoopSuite.ps1             # every known case
powershell -ExecutionPolicy Bypass -File reverse_engineering\Run-BZRCoopSuite.ps1 -Only misn04
```

Scenario parameters: `-ScenarioArgs @{ Skipper = 'host' }` (needs `-Command`,
not `-File`), or `misn03 win Skipper=host` as a suite case.

Each run takes 5-8 minutes and leaves evidence in `C:\BZRCoop\runs\<run>\`:
`flow-summary.md` (steps and checks), `flow-steps.jsonl`, `flow-shots\`
(both clients' screens after every step), the server log and both clients'
`BZLogger.txt`. Exit code 0 means PASS.

Hands-on: `-Scenario play` loads the mission and leaves everything running.
Drive it with `BZRCoopPlay.ps1` (`-Lua`, `-State`, `-Events`, `-Shot`, `-Key`,
`-Click`, `-Stop`). `Run-BZRCoopMission.ps1 -Mission <m> -Scenario <s> -Attach`
runs a scenario against that live session. The mission keeps running in the
meantime, so attach right after it loads (an idle misn03 is lost at about 77 s).

## Trying a CR content fix

`-ContentOverride <folder>` copies the files in that folder over the staged CR
content in both test instances, so a fix can be proven before it lands in CR.
The CR repository and the live install are not touched. Folders live in
`coopflow\overrides\`. In a suite case, write `Override=<folder>`.

`misn02b-onfoot` holds the misn02b fixes committed to CR as
`agent/misn02b-coop-start`: a pilot-only `.vxt`, spawns beside the vehicles,
and a guarded result `CameraFinish`. Drop the override once a CR build that
ships them is the staged content.

A `.vxt` that should offer only the pilot must use the stock line
`asuser aspilo.des<TAB>anims\aspil.avi NSDF Pilot`. The short `asuser ,` form
leaves staging at "Vehicle not selected", and Ready never completes.

## Cases

| Mission | Scenario | What it proves |
|---|---|---|
| misn03 | `win` | Full win path: defend, fortify, waves, evacuation film (guest skips), escort, both at the pad, outro, `misn03w1.des` on both |
| misn03 | `win Skipper=host` | Same, but the host skips the film and the guest keeps watching |
| misn03 | `lose-tower` | The Command Tower falls; the red objective and `misn03f1.des` reach both |
| misn02b | `win Override=misn02b-onfoot ExpectOnFoot=1` | Scavenger escort: start on foot beside the vehicles, intro film skip, fields, waves, retreat, second scavenger, `misn02w1.des` once on each |
| misn04 | `win` | Relic: patrols, recon camera, relic film skip, relic secure, CCA base destroyed, end film, `misn04w1.des` |
| any | `host-leaves` | The host quits mid-mission; the guest detects leader departure, fails the mission and keeps running |
| misn03 | `replication-cases` | 20 isolated stock-Lua replication cases (see [REPLICATION_FINDINGS.md](REPLICATION_FINDINGS.md)) |

Run any scenario with `-Scenario <name>`. The runner looks for
`scenarios\<mission>-<name>.ps1` first, then `scenarios\<name>.ps1`, or takes
a path.

## Writing a scenario

A scenario is a PowerShell file that `Run-BZRCoopMission.ps1` dot-sources
once both clients are in the mission. Client 0 is the host (player 1, team 1,
authority) and client 1 is the guest. Copy the closest existing scenario and
read the mission's `Update()` for the gates and `M` fields it drives.

Building blocks, from `BZRCoopMission.ps1`:

- `Invoke-CRFlowStep 'name' { ... } [-Soft]`: a named step. A throw fails the
  run, or only warns with `-Soft`. The result goes in the report, and both
  clients are screenshotted.
- `Invoke-CRFlow <client> '<lua>'` runs Lua in that client's mission and
  returns the value. `Wait-CRFlow <client> '<lua>'` polls until the result is
  truthy.
- `Wait-CRFlowOp <client> AddObjective 'x.otf'` waits until a presentation call
  reached that client's native API. `Wait-CRFlowEvent` handles any probe
  event with a `-Where` filter.
- `Send-CRFlowKey <client> 0x20`: a key press (Space skips a film).
- Checks: `Test-CRFlowResultParity`, `Test-CRFlowWorldParity`,
  `Test-CRFlowTransport`. The runner adds presentation-stream parity and a
  Lua-error scan at the end. A scenario that ends the session unevenly sets
  `$script:CRFlowSkipParity = $true` to skip the parity check.

Lua side (`CRFlowProbe.lua`): `M`, `CRCoop`, `native` and `L()` (mission locals:
`localCameraActive`, `cameraSkipped`, `events`, `receivedEvent`) are in scope,
plus these helpers:

- `role()`, `players()`, `me()`, `describe(h)`
- `tp(target, dist)` moves your own craft; `put(h, target, dist)` moves an object.
- `kill(h)`, `killTeam(team, odfPattern, near, radius)`, `clearAroundPlayers(team, odfPattern, radius)`
- `heal(h)`
- `ff('^timer_field$')` pulls a future `GetTime()` deadline in `M` to now.
- `every(name, seconds, fn)` runs a task until `fn` returns true; `cancel(name)`.
- `xyz(h)`, `findNear(odf, x, z, r)`, `inbox()` (test `Send` messages)

Variables a command assigns persist for later commands.

Rules that keep results meaningful:

- **Ownership:** each client only moves, damages or removes objects it owns.
  The host owns mission AI; each client owns its own craft. Any other
  combination does not replicate (REPLICATION_FINDINGS.md).
- **Guest state:** never drive the guest's `M` state. The guest must reach
  every state through CR's replication.
- **Starting:** start acting right after the mission loads, because the
  mission clock is running.
- **Send strings:** keep any `Send()` string under 128 bytes, or the receiver
  crashes.

## Known environment gotchas

- `openshim.ini` `RawMouseInput = 1` ignores posted clicks. Prepare forces it
  to 0 in the test instances.
- Over Remote Desktop the clients are clamped to 584x720. The lobby script
  converts its 1280x720 coordinates, finds the map row by scanning, and
  confirms the pick and Sync Join through the server's `/captures`
  gameSettings. Stay connected: a disconnected RDP session may stop rendering.
- Background windows only change shell screens while they believe they are
  active. Input posts WM_ACTIVATEAPP/WM_ACTIVATE before clicks and keys, but
  never before typed text, because the focus change drops the text field.
- Clients are stopped with WM_CLOSE (`Stop-BZRGame -NoForce`), never
  TerminateProcess.
