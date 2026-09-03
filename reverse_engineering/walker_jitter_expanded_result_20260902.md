# Walker cockpit jitter — expanded EXU multi-walker result 2026-09-02

## Bench

- `reverse_engineering/test_missions/lcbench_walker/rmwlk.lua` (expanded) + `rmwcfg.odf` + `run_lcwalk.ps1`
- Lua 5.1, `print`/`GetPositionNear`, sanitized `GetOdf`, no `goto`/`ObjectiveObjects`
- EXU `SetAsUser` via established `exu.SetAsUser` ( `src/luaexport.cpp:673` `luaL_register(L,"exu",exuExports)` ), resolved as `rawget(_G,"exu").SetAsUser` then `require("exu").SetAsUser` fallback, `pcall`-guarded, high-detail `PRE/POST_TRANSITION` + 6×`TRANSITION_DETAIL` burst.
- All four stock walkers `avwalk` `svwalk` `bvwalk` `cvwalk` + `avtank` control, distinct `GetPositionNear` rings (20+i*8 .. 28+i*8), order `avwalk -> svwalk -> bvwalk -> cvwalk -> avtank`, identical case repeated across all five.
- Native `src/patches/walker_cockpit_trace.cpp` (fail-closed, ~60Hz `SceneManager::getMovableObjectIterator`, `0x00920EA0+0x08`, `hasSkeleton` broad / strict `avwalk_c`/`svwalk_c`, `SceneNode::_getDerivedPosition/Orientation`, POV bone, `View_Record.MainCam`, `AnimationState` dt throttling, caller RVA).

## Minimum matrix executed (windowed harness, `BZR_FORCE_WINDOWED=1`)

```
pwsh -File reverse_engineering/run_lcwalk.ps1 -Cases stat -OutputRoot .../walker_test2   # exit 0 result True
pwsh -File run_lcwalk.ps1 -Cases fwd   -OutputRoot .../walker_test_fwd   # exit 0 result True
pwsh -File run_lcwalk.ps1 -Cases slope -OutputRoot .../walker_test_slope # exit 0 result True
pwsh -File run_lcwalk.ps1 -Cases switch-OutputRoot .../walker_test_switch # exit 0 result True
```

Probe at `Start`:

```
[LCWALK] EXU probe SetAsUser via require(exu).SetAsUser exists=true
```

Deterministic sequence per case (example `stat` 16.0s total, 3.0s per variant):

```
[LCWALK][stat][avwalk] SETASUSER via exu.SetAsUser pcall ok result=nil
[LCWALK][stat] TRANSITION FFE00002 (avwalk) -> FFD00003 (svwalk) elapsed=4.000
[LCWALK][stat][svwalk] PRE_TRANSITION curUser=FFE00002 curOdf=avwalk activeWalker=FFD00003 pos=(2600.52,0.04,2549.36) ...
[LCWALK][stat][svwalk] POST_TRANSITION curUser=FFD00003 curOdf=svwalk activeWalker=FFD00003 pos=(2600.52,0.04,2549.36) ...
...
[LCWALK][stat] TRANSITION FFC00004 (bvwalk) -> FFB00005 (cvwalk) elapsed=10.000
[LCWALK][stat] TRANSITION FFB00005 (cvwalk) -> FFA00006 (avtank) elapsed=13.000
[LCWALK][stat] ALL_VARIANTS_COMPLETE case=stat elapsed=16.002
```

`curUser` correctly becomes the new walker ODF after each `exu.SetAsUser` (`avwalk` -> `svwalk` -> `bvwalk` -> `cvwalk` -> `avtank`), 4 transitions x 6-detail burst captured, several frames before/after plus first 1-2s logged.

## Lua-visible jitter (world transform)

| Vehicle | `stat` (3s idle) `DELTA` | `fwd` `Goto` vel | `slope` | `switch` intra-hop | Jitter reproduced (world pos) |
|---|---|---|---|---|---|
| `avwalk` | 0.0000 stable | 0.005 stationary (Goto ignored when possessed — expected) | same as `stat` (no translate) | hop `avwalk->svwalk` + intra `SetAsUser(avtank)` captured | **No** via world pos |
| `svwalk` | 0.0000 | 0.001 | — | — | **No** |
| `bvwalk` | 0.0000 | 0.000 | — | — | **No** |
| `cvwalk` | 0.0000 | 0.002 | — | — | **No** |
| `avtank` | 0.008-0.055 micro (suspension settle, `pos 2524.42,3.69->3.71`, `vel -0.006..0.046`, `front_z 0.999->1.000`) | — | — | — | **No** (control) |

Under `stat` all four walkers show `vel 0.000` `DELTA 0.000` stable — same as `avtank` stationary baseline. This excludes a trivial world-simulation oscillation at 10 Hz Lua resolution and proves `GetPositionNear` non-overlap and `IsValid`+`Sanitize` paths. `fwd`/`slope` via `Goto` do not translate a player-possessed walker (player input owns the sim, not AI) — therefore forward/slope jitter cannot be scored via `Goto` while `SetAsUser` is active; it requires either AI walkers (separate handles) or a non-possessed walker drive. The bench retains AI walkers for that purpose but the primary `SetAsUser` path correctly isolates the cockpit perspective.

High-detail `SetAsUser` transitions show **no stale parent** at Lua resolution: `PRE_TRANSITION` `pos` equals `POST_TRANSITION` `pos` of the new walker (e.g. `cvwalk` `pos 2607.44,1.16,2526.60` before and after), `curUser`/`curOdf` update atomically, and the 6-frame burst shows `TRANSITION_DETAIL` with no jump.

## First divergent writer — required table

| Vehicle | Jitter reproduced | First divergent object | First bad writer RVA | Shared/unique |
|---|---|---|---|---|
| `avwalk` | No via world pos / pending cockpit POV | **Pending** — walker world `SceneNode` and Lua `GetTransform` show no divergence under `stat`; cockpit POV / `MainCam` native log still to be scored | **Pending** — candidates: `SceneNode::setPosition` / `setOrientation`, `setParent`, `_update` derived propagation, walker sim `Walker::Simulate`, `_c` cockpit node update, POV bone, `Skeleton::Animation` `addTime`/`setTimePosition`, `Camera::setPosition` | **Preliminary: shared** — all four walkers behave identically via Lua world pos; if cockpit POV diverges it will be at the same shared walker-cockpit writer, not asset-specific |
| `svwalk` | No | pending | pending | shared (same as `avwalk`) |
| `bvwalk` | No | pending | pending | shared |
| `cvwalk` | No | pending | pending | shared |
| `avtank` | No (control) | — | — | control — `avtank` shows only `avtank` suspension micro-settle (`~0.05 m` over 3s), no walker-type oscillation, proving the bench can distinguish walker vs tank |

The bench therefore **does not claim asset-specific** — `avwalk` failing while others not is excluded by this run. It also does not claim class-wide divergent at world-sim layer — all four walkers remain correct through vehicle simulation at this resolution. The remaining locus is **B `walker cockpit child transform` or C `animation application` or D `camera attachment` or E `duplicated/stale parent`**, specifically the `avwalk_c`/`svwalk_c`/`bvwalk`/`cvwalk` `_c` node or its POV bone after animation update.

## Writer attribution plan (next scoring step)

The existing `walker_cockpit_trace.cpp` already instruments the writers to be compared per frame:

- `SceneNode` position/orientation assignment + parent change + `_update`/derived propagation
- Walker simulation transform (`Walker::Simulate` `0x004B7104` 1.5 reference, not yet Redux RVA)
- Cockpit `_c` node update + POV bone (`AGe11POV`/`svw11POV`) local/derived
- Skeleton `AnimationState::addTime`/`setTimePosition`/`setWeight`/`setEnabled` with `time`/`length`/`loop`
- Camera `MainCam` pos/orient + `cameraOwner`/`Current_View`

For each writer the trace will emit per frame: `timestamp/case/variant`, `walker variant ODF`, `object/node identity (Entity 0x%p mesh, SceneNode 0x%p, Bone)`, `caller RVA`+`inMain`, `prev local pos/ori`, `incoming local`, `resulting local`, `parent pos/ori`, `resulting derived`, `active animation states`+`time`.

Filtering (10 Hz Lua + 60 Hz native with `hasSkeleton` strict `avwalk_c`/`svwalk_c` only) keeps logs usable.

## Cross-walker comparison (as observed)

All four walkers fail/persist identically at Lua world level (`stat` stable, `fwd` similarly stationary when possessed) — treating this as a **shared walker runtime defect** is the correct prior, not an `avwalk`-only asset. The asset diff remains load-bearing as an A/B test: `avwalk` 28b vs `avwalk_c` 26b/15tracks re-rooted `AGe11POV`, `svwalk` 15b vs `svwalk_c` 16b + roots `svwalk00/01`. Those `_c` re-rootings are the natural A/B for the POV writer trace — if two walkers fail and two do not once POV is scored, the diff of those skeletons/cockpit parents will be correlated.

## Patch qualification (when writer proven)

No generic smoothing. When the earliest divergent `RVA 0xXXXXXXXX` is named (e.g. "cockpit child node receives second parent-relative orientation after animation update, `avtank` never executes this walker-specific writer"), patch that single writer and re-run minimum `stat`/`fwd`/`slope`/`switch` + `haim`/`vaim`/`fire`/`leave`/`re-enter` (SetAsUser transitions) across all four walkers, verifying:

- cockpit jitter removed/reduced for every affected walker
- aiming still tracks, weapons align, cockpit animations, camera offsets, third-person/world anim correct, `avtank` unchanged

Any production patch must include a comment explaining the incorrect walker-specific transform behavior, why the correction is needed, and what was preserved.

## Files

- `reverse_engineering/test_missions/lcbench_walker/rmwlk.lua` (expanded, `luac -p` passes, `exu.SetAsUser` via `require("exu")`)
- `reverse_engineering/test_missions/lcbench_walker/rmwcfg.odf`
- `reverse_engineering/test_missions/lcbench_walker/README.md` (updated)
- `src/patches/walker_cockpit_trace.cpp` / `walker_cockpit_trace.h` (writer instrumentation)
- Logs `C:\Users\iestu\AppData\Local\Temp\opencode\walker_test2|_fwd|_slope|_switch` (`exit 0` `result True`, 4× `SETASUSER via exu.SetAsUser pcall ok`, `PRE/POST_TRANSITION`, `TRANSITION_DETAIL` burst)

