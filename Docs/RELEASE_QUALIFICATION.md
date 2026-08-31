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
- OpenShim settings page opens and values are clickable
- keybindings page opens and values are clickable
- campaign mission launch
- Instant Action launch
- save, load, restart
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
- `BomberAiRange`
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
