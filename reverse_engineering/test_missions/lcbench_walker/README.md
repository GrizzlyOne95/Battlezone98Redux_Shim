# lcbench walker cockpit jitter fixture — `lcbench_walker` (expanded 2026-09-02)

Deterministic first-person walker laboratory built as an overlay on the existing
`addon/lcbench` world. It does not replace `lcbench.bzn`/`lcbench.trn`/`lcbench.mat`
and is deployed the same way as the pilot/neutral/aip harnesses: the runner
temporarily installs `rmwlk.lua` as `addon/lcbench/lcbench.lua` and `rmwcfg.odf`
beside it, launches `lcbench.bzn` through `BZRHarness.ps1` with
`BZR_FORCE_WINDOWED=1`, captures `BZLogger.txt`/`openshim.log`/`[LCWALK]` markers
outside `addon`, and restores the prior files in a `finally` block.

All filenames are ≤8 chars. Lua is 5.1-only, uses `print`, `GetPositionNear`,
and sanitizes `GetOdf()`/`GetPilotClass()` etc. against trailing NULs. No
`goto`, no `ObjectiveObjects()`. Expanded to use ExtraUtilities `SetAsUser`
via the established `exu.SetAsUser` interface (see `src/luaexport.cpp:673`
`{ "SetAsUser", &GameObject::SetAsUser }` registered as `luaL_register(L,"exu",…)`),
resolved via `rawget(_G,"exu")` + `require("exu")` fallback and `pcall`-guarded.

## Walker variants — all four stock walkers + control

Spawns and tests all stock walker variants to distinguish class-wide vs
asset-specific vs subclass-dependent defects:

- `avwalk` (NSDF Walker)
- `svwalk` (CCA Walker)
- `bvwalk` (Black Dog Walker)
- `cvwalk` (CRA Walker)
- `avtank` (principal non-walker control; additional scout/tank can be added)

Stock ODFs are used verbatim unless a controlled derivative is required for
instrumentation. `avtank` is the required baseline for the tank-vs-walker
control methodology.

## Test matrix

The brief requires at least 15 points. Each `rmwcfg.odf` case is now run
sequentially across all five vehicles before moving to the next case:

| Vehicle | `stat` | `fwd` | `slope` | `switch` | `rev` | `rot` | `movturn` | `haim` | `vaim` | `movaim` | `fire` | `enter` | `leave` |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| `avwalk` | yes | yes | yes | yes | reuse harness | reuse | reuse | reuse | reuse | reuse | reuse | yes | yes |
| `svwalk` | yes | yes | yes | yes |  |  |  |  |  |  |  |  |  |
| `bvwalk` | yes | yes | yes | yes |  |  |  |  |  |  |  |  |  |
| `cvwalk` | yes | yes | yes | yes |  |  |  |  |  |  |  |  |  |
| `avtank` | yes | yes | yes | yes | control |  |  |  |  |  |  |  |  |

`stat`/`fwd`/`slope`/`switch` are the minimum gates (run first). If jitter does
not reproduce, the existing 14/15-case harness is reused rather than creating
another fixture.

## Deterministic EXU test sequence (per walker)

For each `walker in avwalk -> svwalk -> bvwalk -> cvwalk -> avtank`:

1. Spawn via `BuildObject(odf,1, GetPositionNear(controlledPoint, 20+i*8, 28+i*8))` so no overlap.
2. Validate `IsValid`.
3. Record ODF after sanitizing NUL padding (`Sanitize(GetOdf(h))`).
4. `TrySetAsUser(handle)` via `exu.SetAsUser` (pcall-guarded, logs `prev->new` + source `exu.SetAsUser`/`require(exu).SetAsUser`).
5. High-detail burst: 6 polls (~0.6s, 0.1s poll) with `TRANSITION_DETAIL` budget + `PRE_TRANSITION`/`POST_TRANSITION` snapshots.
6. Allow frames for camera/owner stabilization, then run the requested case (`stat` idle, `fwd` Goto, `slope` to 800,800, `haim` Attack, etc.).
7. Capture Lua (`POS`/`VEL`/`TRANSFORM`/`DELTA`/`ODF`/`curUser`/`isPilot`) and native trace (see below) at 10 Hz + 0.5s heartbeat.
8. Exit/switch cleanly via `SetAsUser(nextVehicle)` capturing several frames before, transition frame, and 1–2s after (old user, new user, camera owner via `GetPlayerHandle`, cockpit entity/node derived via `getParentSceneNode`, local/derived transforms, animation states/time, caller RVA).
9. Move to next walker. Suggested order `avwalk -> svwalk -> bvwalk -> cvwalk -> avtank` repeats identical case across all five before next case.

Example log (2026-09-02 stat run, `C:\Users\iestu\AppData\Local\Temp\opencode\walker_test2`):

```
[LCWALK] EXU probe SetAsUser via require(exu).SetAsUser exists=true
[LCWALK][stat][avwalk] SETASUSER via exu.SetAsUser pcall ok result=nil
[LCWALK][stat] TRANSITION FFE00002 (avwalk) -> FFD00003 (svwalk) elapsed=4.000
[LCWALK][stat][svwalk] PRE_TRANSITION curUser=FFE00002 curOdf=avwalk ...
[LCWALK][stat][svwalk] POST_TRANSITION curUser=FFD00003 curOdf=svwalk ...
```

## What it logs (expanded)

Per poll (10 Hz) per walker:
- `POS` via `GetPosition(activeWalker)` / `VEL` via `GetVelocity` / `TRANSFORM` via `GetTransform` (front/right/up/posit)
- `DELTA` inter-poll distance, `ODF` sanitized + rawLen, `curUser`/`curOdf`/`activeWalker`/`isPilot( IsPerson(GetPlayerHandle()))`
- `TRANSITION_DETAIL` burst for 6 frames around every `SetAsUser(old->new)`

Per transition (explicitly exercised by `switch`/`leave`):
- old user vehicle, new user vehicle, camera owner (`GetPlayerHandle` before/after), MainCam via native trace, cockpit entity/node, cockpit parent, local/derived transforms, animation states/time, caller RVA

Native `walker_cockpit_trace.cpp` (fail-closed, windowed-only, ~60Hz) enumerates
`SceneManager::getMovableObjectIterator("Entity")` via global `0x00920EA0+0x08`,
broad `hasSkeleton` / strict `avwalk_c`/`svwalk_c`/`avtank`, logs
`SceneNode::_getDerivedPosition/Orientation` (world->Ogre node->cockpit parent),
POV bone derived, `View_Record.MainCam` pos/orient/cameraOwner, `AnimationState`
inventory + throttled `dt`, and caller RVA (`_ReturnAddress()-mainBase` + `inMain`).

## How to run

```powershell
pwsh -File reverse_engineering/run_lcwalk.ps1 -Cases stat -Repeats 1
pwsh -File reverse_engineering/run_lcwalk.ps1 -Cases stat,fwd,slope,switch -Repeats 1
pwsh -File reverse_engineering/run_lcwalk.ps1 -All -Repeats 1
# custom output root (allowed temp) to inspect BZLogger without elevation:
pwsh -File reverse_engineering/run_lcwalk.ps1 -Cases stat -OutputRoot "C:\Users\iestu\AppData\Local\Temp\opencode\walker_test"
```

The runner hashes/backs up `addon/lcbench`, installs `rmwlk.lua`→`lcbench.lua` + `rmwcfg.odf`,
launches via `BZRHarness.ps1`, writes `manifest.json` (`case`,`commit`,`exeSHA`,`dllSHA`,`start/end`,`looksLikeCrash`,`everInCockpit`), restores in `finally`.
A run without `RESULT` is not evidence — re-run (window must stay foreground).

## Qualification gates for a patch (unchanged)

No smoothing/interpolation until:
1. Walker's world and `_c` root/head/POV matrices captured per frame and earliest divergent writer identified (camera vs cockpit vs skeleton).
2. Same capture on `avtank` shows no divergence under identical conditions.
3. `enter`/`leave`/`switch` with `SetAsUser` transitions captured at high detail — stale parent test.
4. Candidate fix removes only unwanted component while retaining yaw/aim/recoil/cockpit anim/offsets/world anim.

## Status 2026-09-02 expanded bench

- Lua bench expanded to 4 walkers + `avtank`, EXU `exu.SetAsUser` via `require("exu")` proven working (`pcall ok result=nil`, `curUser` correctly becomes `svwalk`/`bvwalk`/… per transition, 4 transitions x 6-detail burst).
- Minimum matrix `stat`/`fwd`/`slope`/`switch` executed 2026-09-02 (`walker_test2`, `walker_test_fwd`, `walker_test_slope`, `walker_test_switch`) each `exit 0` `result True` `dumps 0`; `stat` per-variant `DELTA 0.000` stationary as expected, `fwd` shows `Goto` ordering but player-possessed walkers do not translate via `Goto` (requires AI — expected).
- High-detail `PRE/POST_TRANSITION` + `TRANSITION_DETAIL` around every `SetAsUser(avwalk->svwalk->bvwalk->cvwalk->avtank)` captured (old/new handles + ODFs, curUser/curOdf, pos/vel/transform).
- Native per-frame cockpit/POV/camera log (`walker_cockpit_trace.cpp`) is code-complete but pending build integration; Lua side already provides world pos/orient per spec. Next step is to score per-frame `nodePos->cockpit POV->MainCam` delta walker vs `avtank` to name earliest writer/RVA.

## References

- Prior asset comparison: `lcbench_runtime_roadmap_pass_20260901.md §4`, walker `avwalk_c`/`svwalk_c` re-rooted POV.
- Pilot FP trace reused: `src/patches/pilot_fp_animation_trace.cpp`, `PILOT_FP_ANIMATION_TRACE.md`, `walker_cockpit_trace.cpp`.
- Walker::Simulate 1.5 `004B7104`, `bzr.h` `GameObject+0x1A0` carrier etc.

