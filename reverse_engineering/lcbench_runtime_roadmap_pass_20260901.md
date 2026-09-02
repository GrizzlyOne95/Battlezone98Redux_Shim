# `lcbench` six-target runtime qualification pass — 2026-09-01

## Outcome

This pass produced two durable Redux 2.2.301 runtime matrices and tightened the
evidence gates for all six roadmap targets. It did **not** add a production
patch. The pilot crash is deterministic and its immediate fault is mapped, but
the exact 1.5 source has the same unguarded carrier assumption, so the current
evidence does not justify calling it a Redux regression. The neutral behavior
is a legacy UI targeting rule rather than a broken Lua/native `Attack` path.
The current binary also disproves the prior claim that All Nations is merely a
dormant settings row with an otherwise intact Redux rule contract.

| Target | Result | Patch disposition | Confidence |
|---|---|---|---|
| Pilot hardpoint ODF ordering crash | Reproduced 3/3 in the closest failing arm; immediate null dereference mapped | No patch until 1.5 runtime parity and valid/invalid ODF contract are established | High for immediate cause; unproven as Redux regression |
| AIP mixed stock/custom producer bug | Fixture design and evidence gate defined; no runtime matrix completed | No speculative selection patch | Speculative/open |
| Neutral unit attack/order asymmetry | Lua/native `Attack` works in both directions; 1.5 UI intentionally excludes team 0 | Reclassify as legacy UI rule; any change is an opt-in enhancement | Very high, except a manual Redux UI confirmation remains |
| Walker cockpit jitter | World/cockpit asset topology compared; old imported function label rejected | No transform patch until the live cockpit update path is traced | Proven asset delta; speculative cause |
| Multiplayer freecam exploit | Prior imported free-eye label rejected; multiplayer gate remains unmapped | No patch until real state/gate and two-client behavior are captured | Speculative/open |
| All Nations multiplayer option | Hidden/no-op row exists, but current loader/launch/list flow has no recovered rule contract | Do not invent a rule byte; revalidate wire and consumers or treat as a larger compatibility port | High for current shell/data-flow findings |

## Qualification environment and preservation

- Repository branch: `agent/lcbench-runtime-roadmap-pass-clean`, based on
  `6108e2a6`.
- Durable fixture commits:
  - `973c5fa8` — pilot ordering runner and five-arm fixture.
  - `14689ef9` — neutral attack runner and four-arm fixture.
- Runtime: GOG Battlezone 98 Redux 2.2.301.
- `battlezone98redux.exe`: 5,425,152 bytes, SHA-256
  `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`.
- Deployed Release Win32 `winmm.dll`: SHA-256
  `AD1E52CB7B83B7BE8263330D67A196A711D33780776C4541A6749B25A3B80A71`.
- The complete pre-pass live `lcbench` tree was backed up outside `addon` at
  `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\openshim_test_backups\lcbench_pre_20260901_6108e2a6`.
  Its 18-file inventory and hashes were captured before any overlay.
- Every runner temporarily installs only its short-named Lua/ODF overlay,
  launches through `BZRHarness.ps1` with `BZR_FORCE_WINDOWED=1`, shuts down
  through `Stop-BZRGame -Id`, captures evidence outside `addon`, and restores
  the exact previous files in a `finally` block.
- All added in-game filenames are at most eight characters before the
  extension. Lua uses the 5.1-compatible shared-reference subset, emits
  `[LCROAD]` markers through `print`, uses `GetPositionNear`, and does not use
  `ObjectiveObjects()`.

The first pilot attempt at `lcroad_pilot_20260901_101520` had a fixture bug: it
called `GetODFString` with the wrong argument shape and produced a Lua error.
That run is invalid and is deliberately excluded from every finding below.

Harness-stopped control arms can report process code `C0000005` during the
known shutdown/DInput tail. That is not classified as the experimental crash.
A pilot failure requires all of: `AFTER_BUILD`, no `RESULT`, early process
exit, and a newly created minidump. Controls reach `RESULT`, have no new dump,
and are stopped by the harness.

## 1. Pilot hardpoint ODF ordering crash

| Evidence field | Finding |
|---|---|
| Status | Deterministic Redux crash proven; Redux-regression classification still open |
| Reproduction | `run_lcroad_pilot.ps1`; `pctl`, `pcrft`, `paftr`, `prevs`, and `ppart` |
| Runtime evidence | Three valid controls survive; the closest malformed arm crashes 3/3 with new dumps |
| Static/RE evidence | Exact current call at `0x0059D76C` passes null carrier; callee faults at RVA `0x17F9A` reading `+0x30` |
| 1.5 comparison | Static source contains the same unguarded carrier use; no 1.5 runtime matrix yet |
| Root cause | Pilot is created without a carrier, then `Person::Simulate` consumes it unconditionally |
| Patch | None; a generic null guard is not yet justified as legacy-compatible behavior |
| Qualification | Redux matrix and repeat control/failure run completed |
| Remaining risk | The tested misplaced-key semantic may be invalid in both engines; legacy runtime boundary is unknown |
| Roadmap recommendation | Keep active, replace the unsupported Redux-specific claim with the exact crash and parity gate |

### Reproduction

The fixture derives five pilots from `aspilo` and varies only section/key
placement:

| Case | Placement | Runtime result |
|---|---|---|
| `pctl` | `weaponHard1`/`weaponName1` in `GameObjectClass` | Survives, live `Person`, no dump |
| `pcrft` | pair in `CraftClass`, before `PersonClass` | Crashes on first simulation frame |
| `paftr` | pair after `PersonClass` begins | Crashes on first simulation frame |
| `prevs` | `PersonClass`, then pair in `CraftClass` | Crashes on first simulation frame |
| `ppart` | `weaponHard1` only in `GameObjectClass` | Survives, live `Person`, no dump |

Primary matrix:

`C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\openshim_test_results\lcroad_pilot_20260901_102052`

Repeat matrix for the stock-valid control and closest failing arm:

`C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\openshim_test_results\lcroad_pilot_20260901_102435`

The separate corrected control run is at
`lcroad_pilot_20260901_102018`. Across valid runs, `pctl` survives 3/3 and
`pcrft` crashes 3/3. The five failing-arm dumps are:

- `openshim_crash_20260901_102116.dmp` (`pcrft`)
- `openshim_crash_20260901_102126.dmp` (`paftr`)
- `openshim_crash_20260901_102136.dmp` (`prevs`)
- `openshim_crash_20260901_102518.dmp` (`pcrft` repeat 1)
- `openshim_crash_20260901_102528.dmp` (`pcrft` repeat 2)

### Exact Redux fault

All failing arms have the same signature:

- Exception: `C0000005`, read of `0x00000030`.
- EIP: `0x00417F9A`, executable RVA `0x00017F9A`.
- Stable relevant state: `EAX=0` at the dereference.
- Caller return address on the stack: `0x0059D771`, inside current
  `Person::Simulate` (`FUN_0059d340`).

Exact current instructions at the call site are:

```text
0059d760  mov edx,[ebp-340]
0059d766  mov ecx,[edx+1a0]
0059d76c  call 00417f90
0059d771  mov [ebp-500],eax
```

The callee at `FUN_00417f90` dereferences its `this` pointer at `+0x30`:

```text
00417f97  mov eax,[ebp-4]
00417f9a  mov eax,[eax+30]
```

`BuildObject` succeeds and returns a valid handle. On its first simulation
frame, the `Person` object's carrier pointer at `+0x1A0` is null and
`Person::Simulate` calls the carrier getter unconditionally. This is the
immediate crash cause.

### Legacy comparison and patch decision

The exact 1.5 source does not support the old roadmap claim that this placement
is merely warned about safely. `Person::Simulate` likewise reads
`this->carrier` and then unconditionally evaluates the carrier's selected
state. `GameObject::GameObject` initializes the carrier null and allocates it
only when `weaponHard` is nonempty. The legacy warning path covers a hardpoint
name that exists in the expected class data but is missing from the model; it
does not prove tolerance for moving the keys outside `GameObjectClass`.

No null guard was shipped. Such a guard could improve safety, but without the
ODF contract and 1.5 runtime behavior it could also preserve a malformed pilot
in an invalid state and conceal later faults. Required next gate:

1. Run the same five-arm matrix against an authentic 1.5 runtime.
2. Add one arm with a valid `GameObjectClass` hardpoint name that is absent
   from the pilot model to exercise the actual warning path.
3. If 1.5 survives the section-placement arms, trace where its carrier is
   allocated differently. If it also crashes, reclassify this as inherited
   malformed-ODF behavior before considering an opt-in safety guard.

## 2. AIP mixed stock/custom producer bug

| Evidence field | Finding |
|---|---|
| Status | Still open |
| Reproduction | Seven-arm stock/custom producer/unit matrix specified below but not yet implemented or run |
| Runtime evidence | None from this pass |
| Static/RE evidence | Shipped AIP examples and producer grammar checked; no responsible filter/scorer identified |
| 1.5 comparison | Not yet reconstructed at the responsible stage |
| Root cause | Unknown; parsing, identity resolution, eligibility, ordering, and scoring remain candidates |
| Patch | None |
| Qualification | Requires decision-level instrumentation and repeated build outcomes, not visual observation alone |
| Remaining risk | A weak fixture could confuse random priority, prerequisites, or resources with ODF-origin filtering |
| Roadmap recommendation | Leave active with the exact matrix/instrumentation gate |

No runtime result was manufactured for this target. Stock mission AIP examples
and grammar were checked, including producer definitions using `avmuf` and
`svmuf`, but the report is not specific enough to patch a selection routine
without observing the requested, eligible, and finally selected unit.

The implementation-ready evidence gate is a seven-arm matrix using one stock
producer, one byte-for-byte custom clone producer, one stock unit, and one
byte-for-byte custom clone unit:

1. stock producer / stock unit only;
2. stock producer / custom unit only;
3. stock producer / mixed list, stock first;
4. stock producer / mixed list, custom first;
5. custom producer / stock unit only;
6. custom producer / custom unit only;
7. custom producer / mixed list with order reversed between repeats.

Each arm must log AIP request identity, producer candidate, build eligibility
and rejection reason, and final ODF selection. Repeat against 1.5 before
assigning regression status. Until that trace exists, producer classification,
ODF namespace resolution, and AIP list iteration remain competing hypotheses.

## 3. Neutral unit attack/order asymmetry

| Evidence field | Finding |
|---|---|
| Status | Disproven as a broken Attack path; reclassified as legacy UI behavior |
| Reproduction | `run_lcroad_neutral.ps1`; `n2p`, `a2n`, `a2e`, and `a2f` |
| Runtime evidence | Redux accepts and executes both neutral-to-player and ally-to-neutral Lua/native attacks |
| Static/RE evidence | 1.5 `ControlPanel::Render` uses `Team::EnemyP`; that predicate excludes team 0 |
| 1.5 comparison | Static source establishes the same normal command-UI restriction |
| Root cause | The target-list/UI predicate omits neutral objects; the AI task itself does not |
| Patch | None; a behavior change belongs behind an optional gameplay policy |
| Qualification | Four directed arms completed with enemy and friendly controls |
| Remaining risk | A manual current-Redux UI-issued order run remains to anchor the modern UI owner |
| Roadmap recommendation | Mark as legacy UI rule, not a Redux regression |

### Runtime matrix

Evidence directory:

`C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\openshim_test_results\lcroad_neutral_20260901_102731`

The mission creates a team-1 ally (`avfigh`), team-0 neutral (`svfigh`), and
team-2 enemy (`svfigh`) at separate `GetPositionNear` results, with team
independence disabled. It polls command, command target, health, ammo, and
`GetWhoShotMe` every 0.5 seconds.

| Arm | T+8 evidence | Conclusion |
|---|---|---|
| `n2p` neutral -> player | command 4 targeting player; ammo `1.000 -> 0.907`; player health `1.000 -> 0.440`; player shot by neutral | Neutral can attack and damage player |
| `a2n` ally -> neutral | command 4 targeting neutral; ammo `1.000 -> 0.949`; neutral health `1.000 -> 0.663`; neutral shot by ally | Lua/native Attack can attack and damage neutral |
| `a2e` ally -> enemy | ally ammo `1.000 -> 0.857`; enemy destroyed | Ordinary hostile control passes |
| `a2f` ally -> friendly player | no attack command and no health/ammo change | Friendly/default-priority negative control passes |

### Legacy UI boundary

The asymmetry is not in `Attack()` or the resulting AI task. Exact 1.5 source
shows `ControlPanel::Render` populating its target list only when
`Team::EnemyP` is true. `Team::EnemyP` explicitly returns false for target team
numbers below 1, excluding neutral team 0. Clicking a listed target then emits
`CMD_ATTACK`. Thus a direct/internal attack can target neutral while the normal
player target-list UI intentionally cannot offer that target.

No compatibility patch is justified. The roadmap item should be reclassified
as a legacy UI rule. A user-visible change could be designed separately as an
opt-in gameplay enhancement. One manual Redux UI run should still confirm the
reported front-end behavior and identify the exact current target-list owner;
it is not needed to establish that the Lua/native order path works.

## 4. Walker cockpit jitter

| Evidence field | Finding |
|---|---|
| Status | Static asset groundwork complete; runtime cause still open |
| Reproduction | No controlled walker runtime capture completed |
| Runtime evidence | None from this pass |
| Static/RE evidence | `_c` meshes use distinct skeletons and re-root cockpit/head/POV bones; old current-function label rejected |
| 1.5 comparison | Not yet performed at the relevant render/camera path |
| Root cause | Unknown; stale/double parent, animation order, interpolation, and camera attachment remain hypotheses |
| Patch | None |
| Qualification | Requires per-frame transform capture across the walker motion/camera matrix |
| Remaining risk | A global inheritance change could break animation, aiming, attachments, or ordinary cockpits |
| Roadmap recommendation | Leave active and replace label-led work with a live transform-writer trace |

Loose stock meshes and skeletons were converted to XML in a temporary
directory; neither the repository nor the game assets were modified. The
comparison establishes that the first-person cockpit uses distinct `_c.mesh`
and `_c.skeleton` assets with deliberately changed bone topology:

- `avwalk.mesh` / `avwalk.skeleton`: 28 bones. `AGe11POV` and `age21hed` are
  children of `age11hed`.
- `avwalk_c.mesh` / `avwalk_c.skeleton`: 26 bones and 15 animated tracks.
  `AGe11POV` and `age21hed` are re-rooted.
- `svwalk.mesh` / `svwalk.skeleton`: 15 bones and 10 tracks. `svw11POV` is a
  child of `svw11hed`; `svw21hed` is a child of `svwalk`.
- `svwalk_c.mesh` / `svwalk_c.skeleton`: 16 bones and 10 tracks. Both named
  cockpit/head bones are re-rooted, and roots `svwalk00`/`svwalk01` are added.

Mesh links and submesh vertex counts also differ: `avwalk` is
`5260/88/153` versus cockpit `4177/88/153`; `svwalk` is `6912/197` versus
cockpit `6398/197`. The jitter therefore cannot safely be treated as a generic
copy of the world entity's parent transform.

The imported/advisory `OgreUpdateCockpit` label at `0x00577AE0` is rejected:
the exact current containing function `FUN_00577AD0` is a small lookup routine
with no demonstrated cockpit semantics. Required next gate: trace the active
first-person walker camera/cockpit transform writers from a live mode switch,
record the world and `_c` root/head/POV matrices each frame, and identify the
first divergent writer before attempting a hook. Qualification must cover both
walkers, idle/walk/turn/aim, enter/eject, save/load, and non-walker controls.

## 5. Multiplayer freecam exploit

| Evidence field | Finding |
|---|---|
| Status | Still open |
| Reproduction | No real host/client session completed |
| Runtime evidence | None from this pass |
| Static/RE evidence | Advisory `Set_Free_Eye_View` mapping is invalid for the exact current executable |
| 1.5 comparison | Not yet relevant until the actual Redux camera transition is identified |
| Root cause | Unknown; both the active free-eye transition and authoritative participant gate remain unmapped |
| Patch | None |
| Qualification | Requires the two-client and spectator/state-transition matrix below |
| Remaining risk | A hotkey-only or weak multiplayer proxy could leave alternate entry paths open or break spectators |
| Roadmap recommendation | Leave active with exact-current trace and real-network gates |

No network runtime session was completed, and no camera patch was added. The
imported/advisory `Set_Free_Eye_View` label at `0x00554EE0` is rejected: that
address lies inside current `FUN_00554C80`, whose exact behavior is
serialization/array loading rather than a proven free-eye switch.

The next evidence gate is intentionally strict:

1. Trace the actual current free-eye state transition from live input/camera
   state, using exact 2.2.301 xrefs rather than transferred labels.
2. Identify the authoritative current participant states for active player,
   host, client, dead/ejected player, observer/spectator, editor, and SP.
3. Run a real two-client matrix: host and client attempts while active,
   spectator use, death/ejection transitions, reconnect, and match end.
4. Only then gate the transition narrowly. Preserve legitimate SP, editor,
   replay/cinematic, and spectator behavior.

## 6. Restore the 1.5 All Nations multiplayer option

| Evidence field | Finding |
|---|---|
| Status | Legacy 1.5 option confirmed, but Redux restoration is not implementation-ready |
| Reproduction | Exact current shell/settings/launch/list data flow inspected; no two-client toggle exists to run |
| Runtime evidence | None; option remains hidden/inert |
| Static/RE evidence | Current hidden `AnyNationButton` is proven, but loader, callback, launch flow, logs, and list literals do not recover the claimed contract |
| 1.5 comparison | Stock 1.5 has the All Nations host rule; transferred same-RVA identities are not current-Redux proof |
| Root cause | Redux retains a shell artifact after the usable rule path was removed or relocated beyond current evidence |
| Patch | None; no private variable, packet, or protocol extension added |
| Qualification | Must first prove an existing current wire byte and consumer, then run OFF/ON two-client lifecycle tests |
| Remaining risk | Treating the UI field as sufficient could create a nonfunctional or incompatible host option |
| Roadmap recommendation | Correct the retained-contract overclaim; scope as a larger compatibility port if the wire/consumers are absent |

### Exact current Redux findings

The prior roadmap description overstates what survives in Redux 2.2.301:

- `FUN_00796880` (RVA `0x396880`) creates an `AnyNationButton` at exact string
  address `0x0089E90C`, stores it at UI field `+0x68`, then invokes a virtual
  operation consistent with hiding/disabling it.
- Its callback `FUN_00795D70` (RVA `0x395D70`) calls `FUN_00417C60` (RVA
  `0x17C60`), which is an empty nullsub. The row is both hidden and inert.
- Settings loader `FUN_00742090` (RVA `0x342090`) reads Sync Join, Comm Sat,
  Barracks, Sniper, and Splinter fields. It contains a separate duplicated
  Barracks read into the same field, but no Any Nation read and no write to the
  adjacent candidate field.
- Launch assembly `FUN_00799D70` (RVA `0x399D70`) copies the other settings but
  no recovered nations rule. Launch logging in `FUN_005740A0` (RVA `0x1740A0`)
  likewise names the other host rules and not Nations.
- Current vehicle-list paths `FUN_0045DD40` (RVA `0x5DD40`),
  `FUN_00766900` (RVA `0x366900`), and the UI constructor default only to
  `netveh.odf`.
- An exact search of the current executable finds no `netveh1.odf` literal.

This proves a dormant shell artifact, not an intact host-rule contract. Earlier
claims that Redux retains `Net::bNations`, its serialized byte, and downstream
consumers came from advisory/private-PDB same-RVA mappings that do not survive
exact-current validation. Those mappings are not identity evidence and must
not drive a hook.

No new network field or private variable was invented. Restoration remains
blocked on locating an exact current existing wire byte and current downstream
consumer with independent identity evidence. If neither exists, this should be
planned as a larger 1.5 compatibility port with protocol/versioning review,
not described as re-enabling one settings row.

## Validation and remaining work

The committed runners are:

- `reverse_engineering/run_lcroad_pilot.ps1`
- `reverse_engineering/run_lcroad_neutral.ps1`
- `reverse_engineering/test_missions/lcbench_roadmap/`

They provide repeatable qualification for the two strongest targets while
leaving exact evidence gates for the other four. No address, hook, or signature
was added to `patches.json`, and no production behavior changed in this pass.

Final repository and live-state checks:

- Release Win32 solution build: passed; `bin/Release/winmm.dll` produced.
- Engine-independent CTest suite: 18/18 passed from
  `build/consolidation-tests` in Release configuration.
- INI/config tests: 23/23 writer checks and 41/41 preset-migration checks
  passed; conservative/default completeness checks passed.
- `luac -p`: both `rmpilot.lua` and `rmneut.lua` passed.
- Fixture filename audit: every basename is at most eight characters.
- Live `addon/lcbench`: all 18 files match the pre-pass backup by SHA-256 and
  there are no overlay extras.
- The harness's orphaned windowed `Ogre.cfg` was restored from
  `ogre.cfg.bzrharness-backup`; no harness backup remains active.
