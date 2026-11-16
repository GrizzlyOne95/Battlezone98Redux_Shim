# OpenShim Release Qualification

This checklist is the final artifact-level gate for a public OpenShim release or Workshop payload. It supplements CI: automated tests qualify source and build output, while this matrix qualifies the exact frozen files that will be distributed.

## Release identity

Record before testing:

- tag / candidate commit SHA
- `winmm.dll` SHA-256
- `patches.json` SHA-256
- `openshim.ini` SHA-256
- `openshim.ini.example` SHA-256
- Campaign Reimagined / Workshop payload revision when applicable

Do not mix files from different commits or tags. The DLL, patch table, and configuration shipped to Workshop must come from the same qualified release candidate.

## Automated gate

The candidate must pass the repository's normal Build Win32 workflow, including:

- network safety baseline validation
- pinned Ogre header setup
- Ogre profiler algorithm tests
- INI/config tests
- complete CTest regression suite
- DX11 Enhanced FXAA shader compilation
- Release | Win32 MSBuild
- release output/hash verification

A tagged GitHub release must pass the same gates before publication.

## GOG 2.2.301

Test the exact release candidate files on the supported GOG executable.

### DX9

- startup to shell
- OpenShim Options (Options → OpenShim Options) opens, every category screen opens, and values are clickable
- keybindings page opens and values are clickable
- campaign mission launch
- Instant Action launch
- save, load, restart
  (`reverse_engineering/test_cr_saveload.ps1` automates this for every CR
  mission: a menu save and an OpenShim autosave per mission, each loaded in a
  fresh process and held past its first Updates)
- return mission -> shell -> mission
- clean process exit and relaunch

### DX11

Repeat the DX9 smoke matrix, then additionally verify:

- renderer/profile selection matches configuration
- no new Ogre/resource collision on campaign/mod transitions
- no obvious Enhanced/Redux profile contamination

### Input

- `RawMouseInput = 0`: legacy path behaves normally
- `RawMouseInput = 1`: raw-input path takes effect after restart
- settings UI restart requirement is correctly communicated

### Campaign thumbnail crash guard

Exercise the known malformed BITMAPV5HEADER case through the full lifecycle:

1. open/select the malformed thumbnail
2. navigate away
3. reselect it
4. close the campaign/list UI
5. reopen it
6. reselect it and launch if applicable

Acceptance:

- no crash
- bounded `[BMPFIX]` handling
- no stale/half-created material after navigation/reopen/reselect

### Display stress

Run once per candidate on a throwaway profile, on DX9 and DX11, windowed first and then
fullscreen. Launch one test game with the harness helpers (`reverse_engineering/BZRHarness.ps1`),
then:

```powershell
powershell -File reverse_engineering\Run-BZRDisplayStress.ps1 -Cycles 10 -ReportPath $env:TEMP\display-stress.json
```

Each cycle sends Alt-Tab, Alt-Enter, the fullscreen/windowed toggle key if the build has one
(`-ToggleVk <vk>`; skipped by default) and, with `-EditMode`, Shift-F9, waits, and reports per step: process exit
(CRASH), not responding for `-HangSeconds` (HANG), a new `.dmp` or new crash lines in
`openshim.log` (CRASH-LOG). The script never launches the game, caps at one process, closes it
with WM_CLOSE at the end or on timeout, and never force-kills it (AGENTS.md display-stack rule),
so a game that ignores WM_CLOSE must be closed by hand.

Shift-F9 only works in `/edit` mode (the editor). Launch the test game with `/edit` and pass `-EditMode`;
the script checks the running game's command line for `/edit` and refuses otherwise. Without `-EditMode`
the Shift-F9 step is skipped and the script says so.

Acceptance:

- 10 cycles complete with no CRASH, HANG or CRASH-LOG on the Alt-Tab, Alt-Enter and toggle steps
- the game still renders and responds to input afterwards, and exits cleanly
- with `-EditMode`, a failure on the Shift-F9 step is reported as `KNOWN-300`: it is the open editor task-mode crash
  (`Docs/Archive/2026/ROADMAP_CODE_VALIDATION_20261007.md`, item 300), not a new regression. It does not fail
  the gate (the run stops there with `Known300Stop` set, so run the remaining cycles on a relaunched game if needed), but any change in its behavior from the previous candidate needs explaining

### Mode-transition stress (unattended)

Run once per candidate, on DX9 and DX11, with Campaign Reimagined and the "Legacy Instant Action" addon
installed. It needs no input and can run while Windows is locked. One game process works through a plan of
CR missions, Instant Action maps, hosted one-player multiplayer games and main-menu idles, returning to the
main menu between loads, to catch stale pointers and use-after-free across mode transitions:

```powershell
powershell -File reverse_engineering\Run-BZRModeStress.ps1 -Renderer DX11
powershell -File reverse_engineering\Run-BZRModeStress.ps1 -Renderer DX9 -FrameCapture
```

The script takes `bzr_livetest.lock` (it refuses if the lock exists), runs `Assert-BZRSafeToLaunch`, and
launches the game windowed with `OPENSHIM_MODE_STRESS_PLAN`, `OPENSHIM_NEVER_ACTIVATE=1` and
`OPENSHIM_SOAK_TELEMETRY=1`. The native driver (`src/patches/mode_stress_driver.cpp`) replays the stock shell
button handlers from a frame listener and logs `[MODESTRESS] step i/n <kind> <arg> begin|launched|ready|end`.
It exits through the main-menu exit button after `[MODESTRESS] done`. On a timeout the script closes the game
with WM_CLOSE (`Stop-BZRGame`) and never force-kills it. The default plan is
`reverse_engineering/mode_stress_default.plan` (grammar in `include/mode_stress_plan.h`); pass `-PlanPath`
for another one.

An `mp_host <map.bzn> <seconds>` step hosts a multiplayer game in the same process, through the stock path:
it starts OpenShim's in-process no-sign-in LAN host, selects it as the server, waits for the network, calls
the stock Multiplayer button into the lobby, creates a game with the lobby Create button's direct branch,
picks the map in the game room, presses launch, holds for `<seconds>` after the sim loop runs, leaves the game
like the abort button, backs out of the room and lobby with their Back buttons, and stops the host. Each
stage fails as `[MODESTRESS] FAIL mp_host:<stage>` (`rows`, `no-auth-lan`, `host-start`, `select`,
`network`, `lobby`, `create`, `map`, `launch`, then the shared `load`/`leave` stages). Stock refuses a
one-player launch while Sync Join is on (CanLaunchGame `FUN_00573d00`) and ends a one-player game, so for a
plan with `mp_host` the script sets `OPENSHIM_DISABLE_SYNC_JOIN_DEFAULT_ON=1`, `multi.ini` `syncJoin=0` and
`openshim.ini` `[Network] NoAuthLan=1`, and restores both files afterwards. It does not cover a second
client joining; that stays with the two-client checks below.

Every log the game writes (`logs\*.log`/`*.txt` including `openshim.log`, `BZLogger.txt`,
`BZOgreLogfile.log`, `exu.log` and `openshim_crash.log`, plus the root `BZLogger.txt`) is snapshotted
before launch, and only the new content is scanned. Error, exception, fail, assert, crash, first-chance and
notable warning lines are de-duplicated, counted, and attributed to the step they happened in by
`[MODESTRESS]` markers and timestamps. Lines matched by `reverse_engineering/mode_stress_known_log_noise.txt`
are still printed with counts under "Allowlisted". Every rule there must say why its line is benign. The
report is `openshim_test_results\modestress_<renderer>_<stamp>\mode_stress_report.json`, with the new log
segments copied next to it. After you edit the allowlist, re-score a run without relaunching:
`Run-BZRModeStress.ps1 -AnalyzeOnly <report dir>`.

Acceptance:

- every step is PASS, the log has `[MODESTRESS] done`, and the game exits on its own
- no FAIL-CRASH (new `.dmp`, process exit or first-chance AV), FAIL-STALL (heartbeat gap or main-loop stall
  over `-StallFailSeconds`) or driver `[MODESTRESS] FAIL`
- no FAIL-LOG: every flagged line is either fixed or added to the allowlist with a written reason, never a
  blanket pattern; review any change in allowlisted counts against the previous candidate

## Steam 2.2.301

Test the exact same release candidate files on the supported Steam executable.

Minimum smoke matrix:

- DX9 startup + mission launch + clean exit
- DX11 startup + mission launch + clean exit
- settings and keybindings controls
- save/load/restart
- raw mouse toggle with restart
- campaign/mod transition

Any Steam-specific signature/resolver failure is a release blocker unless the affected feature demonstrably fails closed and is intentionally unsupported.

## Multiplayer

Perform at least one real two-machine/two-client qualification. Do not use local-only rendering evidence as a substitute for network behavior.

### OpenShim host + OpenShim client

Verify:

- lobby creation/join
- map transition
- normal vehicle/object replication
- host controls
- no unexpected kick/timeout behavior
- return to lobby / second match where practical

### Mixed OpenShim + stock client

Verify both network tuning policies:

#### `GovernorTuning = OpenShim`

- OpenShim client remains interoperable with stock peer
- measured tuning does not create a new disconnect or throttle regression
- OpenShim host's relaxed auto-kick behavior is understood as intentional

#### `GovernorTuning = Stock`

- strict-parity path leaves stock governor and auto-kick values in control
- no stale OpenShim tuning survives a restart/config switch

### Multiplayer safety gate

While in a network game, verify `[SinglePlayer]` features remain inactive, especially:

- `AttackRevealPerceivedTeam`
- `AiOdfGameplayTuning` (includes bomber range)
- `SatelliteVisibilityFix`
- other feature-registry entries intended to hard-disable online

Where a feature had been active in single-player immediately before entering multiplayer, verify its network transition cleanup restores any modified state.

## Lifecycle / stability

Exercise the release candidate through:

- game -> shell -> game
- save -> load
- mission restart
- mission transition
- shell/mod transition where applicable
- quit to desktop
- relaunch

Watch specifically for:

- stale Ogre entity/resource access
- chunk proxy teardown faults
- loader/shutdown hangs
- phantom BZR process after exit
- configuration migration loops
- stale first-person entity generations

## Release decision

A candidate is releasable when:

- all automated gates are green
- GOG and Steam smoke matrices pass
- the multiplayer matrix passes or any untested multiplayer surface is explicitly excluded from the release
- no new crash, hang, signature mismatch, or state leak remains unexplained
- the exact tested hashes match the files being uploaded to GitHub/Workshop

If code changes after qualification, create a new candidate and rerun the affected matrix. Do not carry forward a release PASS across a changed DLL or patch table.
