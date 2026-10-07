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

`misn02b-onfoot` holds the misn02b fixes: a pilot-only `.vxt`, spawns beside
the vehicles, camera-stack-safe `CameraFinish`, film shots that advance when
the leader's path ends, and the intro route renamed from `player_path` (see
below). Drop the override once a CR build that ships them is the staged
content.

To test whatever is in a CR checkout right now (several agents' uncommitted
work, a new EXU build), generate an override instead of hand-copying:

```
powershell -ExecutionPolicy Bypass -File reverse_engineering\New-CRFlowOverride.ps1 -Name coop-comms `
    -Extra C:\Users\iestu\Documents\GIT\ExtraUtilities\Release\exu.dll
```

It copies every file changed or added since the staged build's commit,
flattened to the Workshop layout, and records the source in `OVERRIDE.txt`.
Generated folders are git-ignored.

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
| misn02b | `win Override=misn02b-onfoot ExpectOnFoot=1 Skipper=none NaturalIntro=1` | Nobody skips: the intro plays as offline (lander shot until its path ends, then both cameras follow the living dummy tank), no stray team-0 craft, then the full win |
| misn03 | `C:\...\Campaign-Reimagined\Tools\Test-CoopCommsLive.ps1` (with `-ContentOverride` from `New-CRFlowOverride.ps1` + new `exu.dll`) | CR's co-op PDA comms: terrain/object pings both ways, explicit targeting, PDA Co-op page, J quick ping, expiry, pilot rescue request and host replies |
| misn04 | `win` | Relic: patrols, recon camera, relic film skip, relic secure, CCA base destroyed, end film, `misn04w1.des` |
| any | `film-preview` (`-ScenarioArgs @{ Path='endcin'; Variants=@('100,200,M.avrec','8000,9000,center'); Protect=@('avrec') }`) | Not a test: plays one camera path on the host with each height,speed,target (cm, cm/s, Lua handle or `center` = a pod at the path's middle) and screenshots it, to tune a film without playing up to it. Height/speed are cm: 100 is 1 m |
| misn04 | `endfilm` | Jumps the host to the win and checks the closing film on both clients: camera pod on the Face summit, both cameras on `endcin`, pod removed, `misn04w1.des` on both. Does not need audio |
| any | `host-leaves` | The host quits mid-mission; the guest detects leader departure, fails the mission and keeps running |
| misn03 | `replication-cases` | 20 isolated stock-Lua replication cases (see [REPLICATION_FINDINGS.md](REPLICATION_FINDINGS.md)) |
| misn03 | `coop-pda-controls` (with the `coop-comms` override) | CR's co-op PDA by real key presses on both clients: X open/close on the Co-op page, [ ] paging, arrow rows, PDA ping, quick-J terrain/object pings, cooldown, rescue request/replies, film and Esc-menu suppression, Q as a ping-key candidate |
| any | `gamekey-names` | Not a test: which real key presses reach the mission `GameKey` callback vs. the raw key state (network games drop many keys) |

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
- `Send-CRFlowKey <client> 0x20`: a posted key press (Space skips a film). Add `-Focused`
  for real input (SendInput scan codes; takes the desktop focus for the press,
  then gives it back). Keys the game polls (`exu.GetGameKey`) and the mission
  `GameKey` callback only see real input.
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
- `setCameraActive(v)` sets the mission's own film flag (`localCameraActive`) for
  code gated on it, e.g. PDA suppression; run the native camera yourself.
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
- **Variable names:** PowerShell names ignore case, so `$h`/`$g` inside a step
  are `$H`/`$G` (the client indexes). Use names like `$hostShot`.
- **Closing a client on purpose:** add its pid to `$script:CRFlowExpectedExit`
  first. Any other client exit fails the run within a second.
- **Craft trace:** the probe logs every craft/person created (`add`) and
  removed (`del`) with odf, team, label and position: `Get-CRFlowEvents 0 add`.

## Co-op map rules found by these tests

- Never name a path `player_path` in a co-op map. Online, the native mission
  builds an AI-piloted team-0 `player` ship there on the first frame, before
  any mission Lua runs. In misn02b it killed the intro dummy tank and froze
  the film; renaming the path removed it.
- A skip pops the skipper's camera. Any later `CameraFinish` on an empty stack
  raises "Camera Stack 0verfow" and silently aborts the rest of the Lua chunk.
  Track the peer's own camera and pop only what it pushed.

## Known environment gotchas

- Launching Windows PowerShell 5.1 from PowerShell 7 or Git Bash inherits
  PowerShell 7's `PSModulePath`; 5.1 then cannot load its own modules
  (`Get-FileHash` not found in Prepare). Clear it first (`env -u PSModulePath`).
- In a network game Redux calls the mission `GameKey` callback only for some keys
  (reliably Y, digits, /; J, [ ], arrows and Enter only sometimes), though the
  raw key state sees all of them (`scenarios\gamekey-names.ps1`). Y is the stock
  "ally with team" key online.

- `openshim.ini` `RawMouseInput = 1` ignores posted clicks. Prepare forces it
  to 0 in the test instances.
- The client size follows the user's display (584x720 over a portrait
  Remote Desktop, 624x393 from a phone). The shell scales with the client
  height, so the lobby script scales its 1280x720 coordinates by h/720 per
  anchor (centre / right edge), finds the map row by scanning, and
  confirms the pick and Sync Join through the server's `/captures`
  gameSettings. Stay connected: a disconnected RDP session may stop rendering.
- Background windows only change shell screens while they believe they are
  active. Input posts WM_ACTIVATEAPP/WM_ACTIVATE before clicks and keys, but
  never before typed text, because the focus change drops the text field.
- Clients are stopped with WM_CLOSE (`Stop-BZRGame -NoForce`), never
  TerminateProcess.
- Never dot-source `BZRHarness.ps1` from a scenario: it takes the launch lock,
  which the session coordinator holds, and the scenario blocks. The mission
  library already loads it with the lock skipped.
- A dead client fails the lobby step or the next probe call within a second.
  Suite runs are `-NonInteractive`, so a hidden prompt fails instead of hanging.
- The clients need an audio device. Without one (a phone Remote Desktop
  session set not to play sound) the log shows "Couldn't create a streaming
  ogg!" / `minFreeCopies(0)`, every voice-over counts as done at once, and
  films gated on `AudioDone` end on their first frame. The run summary warns
  "audio available"; fix the Remote Desktop sound setting and rerun.
- Redux's music streamer once crashed a client on the Multiplayer screen (null
  audio system at `0x43ee3c`, two clients sharing one audio device over RDP).
  Rare; rerun the case.
