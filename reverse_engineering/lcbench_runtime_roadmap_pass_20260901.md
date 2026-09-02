# `lcbench` six-target runtime qualification pass — 2026-09-01

## Outcome

This pass produced two durable Redux 2.2.301 runtime matrices and tightened the
evidence gates for all six roadmap targets. Follow-up implementation now adds a
narrow pilot null-safety guard and an opt-in neutral attack-order UI policy.
Whether the pilot crash is a Redux regression or inherited legacy behavior no
longer blocks the defensive fix: the guard skips only the carrier-dependent
selected-mask read and continues normal `Person::Simulate` processing. The
neutral behavior remains a legacy UI targeting rule rather than a broken
Lua/native `Attack` path. The current binary also disproves the prior claim
that All Nations is merely a dormant settings row with an otherwise intact
Redux rule contract.

| Target | Result | Patch disposition | Confidence |
|---|---|---|---|
| Pilot hardpoint ODF ordering crash | Reproduced 3/3 in the closest failing arm; immediate null dereference mapped | **ACTIVE PATCH** — narrow null-carrier guard; legacy parity no longer blocks implementation | High for immediate cause and guard identity; unproven as Redux regression |
| AIP mixed stock/custom producer bug | **Reproduced and localized**: custom ODF never built by any AIP account, yet the same producer builds it on direct command | Instrument AIP account-to-ODF resolution; no patch until the routine is identified | High for localization; reported direction contradicted |
| Neutral unit attack/order asymmetry | Lua/native `Attack` works in both directions; 1.5 UI intentionally excludes team 0 | Opt-in `[Gameplay] AllowNeutralAttackOrders=0`; alter only explicit order-target eligibility | Very high, except MP host/client UI qualification remains |
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
| Status | **ACTIVE PATCH** — deterministic crash proven; Redux-regression classification still open |
| Reproduction | `run_lcroad_pilot.ps1`; `pctl`, `pcrft`, `paftr`, `prevs`, and `ppart` |
| Runtime evidence | Three valid controls survive; the closest malformed arm crashes 3/3 with new dumps |
| Static/RE evidence | Exact current call at `0x0059D76C` passes null carrier; callee faults at RVA `0x17F9A` reading `+0x30` |
| 1.5 comparison | Static source contains the same unguarded carrier use; no 1.5 runtime matrix yet |
| Root cause | Pilot is created without a carrier, then `Person::Simulate` consumes it unconditionally |
| Patch | Redirect only the selected-mask call through a null guard; return mask 0 for a missing carrier, log once per `Person`, and continue stock simulation |
| Qualification | Redux matrix and repeat control/failure run completed |
| Remaining risk | The tested misplaced-key semantic may be invalid in both engines; legacy runtime boundary remains relevant to classification, not safety |
| Roadmap recommendation | Keep as an active safety patch; retain the fixture and qualify the guarded runtime path |

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

The safety patch does not return early from `Person::Simulate` and does not
allocate or synthesize a carrier. It redirects only the exact call to
`Carrier::GetSelected`; a non-null carrier follows the original function, and
a null carrier yields selected mask 0. The first trip for each `Person` emits a
`[PILOTSAFE]` diagnostic. Both the call site and callee identity are resolved
from unique exact-current signatures and must agree before the patch applies.

Legacy runtime work remains useful for classification and ODF-authoring
guidance, but no longer blocks the defensive guard. Remaining gates:

1. Run the same five-arm matrix against an authentic 1.5 runtime.
2. Add one arm with a valid `GameObjectClass` hardpoint name that is absent
   from the pilot model to exercise the actual warning path.
3. Re-run `pctl` and `pcrft` against the patched Redux build. Both must reach
   `RESULT`; only `pcrft` should emit the once-per-object guard diagnostic.
4. If 1.5 survives the section-placement arms, trace where its carrier is
   allocated differently. If it also crashes, classify the patch as an
   inherited legacy safety fix rather than a Redux-regression repair.

## 2. AIP mixed stock/custom producer bug

| Evidence field | Finding |
|---|---|
| Status | **Reproduced, localized and root-caused**; responsible routine identified and instrumented |
| Reproduction | `run_lcroad_aip.ps1`; seventeen-arm matrix in `test_missions/lcbench_roadmap` |
| Runtime evidence | Custom ODF never built by any AIP, including a file naming no stock unit at all; the same producer builds it on a direct `Build()` command |
| Static/RE evidence | `PREREQ_WhatIs` at `0x006A04B0`; `AIP_Load_Account` at `0x00693520` discards any node it returns 0 for. See `aip_construction_program_resolution_20260902.md` |
| 1.5 comparison | Same code: 1.5 `PREREQ_WhatIs` at `0x00515466` matches instruction for instruction, so this is stock BZ1 behavior, not a Redux regression |
| Root cause | The strategic AI's name universe is a fixed 53-entry enumeration of stock unit/building types built by `PREREQ_Init`. A custom ODF name resolves to id 0, and `AIP_Load_Account` discards the node at load time |
| Patch | None yet. Instrumentation only (`[Diagnostics] AipResolveTrace`); a fix must widen the enumeration before `PREREQ_Init` freezes the table |
| Qualification | Known-good control arm (`ccak`) required alongside any negative, since every failure mode here is a silent zero |
| Remaining risk | Reported direction is contradicted (see below); the original report's setup may differ materially |
| Roadmap recommendation | Keep active; re-confirm the reported direction, then design the fix at `AddObjectClass`/`Units_Init`/`PREREQ_Init` |

A controlled matrix now reproduces the defect and bounds it. `svfigh` is the
stock unit and `mxfigh` a value-identical clone differing only in ODF identity,
so cost, build time, health and role are excluded by construction.

Three facts localize the defect:

1. The custom ODF is valid. Spawned directly every run, it reports
   `valid=true class=wingman`.
2. The producer builds it on command. With the Offense account neutered to
   `NUMBER_TO_HAVE 0`, `Build(producer, "mxfigh")` and
   `Build(producer, "svfigh")` each produced three units at identical times.
3. No AIP account ever builds it: zero when requested alone, paired with another
   custom, mixed with stock in either priority order, from either producer
   identity, and at either end of the producer's build menu.

A whole-file test closes the remaining account-scoped explanations. `allc` and
`alls` are shape-identical AIPs differing only in unit family. `alls` built six
units: 2 `svturr` from Slush at T+12 and T+19, then 4 `svfigh`. `allc`, which
names no stock ODF anywhere in the file, built nothing at all -- not even its
Slush account. Stock entries crowding out custom ones is therefore excluded, as
are priority order, build-slot position and producer identity.

The unit is constructible and the producer will construct it; the AI simply
never asks for it.

**Root cause, confirmed by native instrumentation on 2026-09-02.** OpenShim now
wraps all three `PREREQ_WhatIs` call sites (`[Diagnostics] AipResolveTrace`, or
`run_lcroad_aip.ps1 -AipResolveTrace`). `PREREQ_WhatIs` is the AI's only
ODF-name-to-type lookup, and `AIP_Load_Account` discards any construction-program
node it returns 0 for, logging an engine `tlog` message that the shipped build
never surfaces. Re-running the matched pair:

```
alls  account 'svturr' -> id=21   account 'svfigh' -> id=22   -> 6 units built
allc  account 'mxturr' -> id=0    account 'mxfigh' -> id=0    -> 0 units built
```

The probe's one-shot census of the whole prereq table is identical in both arms
and holds exactly 53 names: the two stock races plus `player`. It does not vary
with the mission's ODFs, the producer's build list, or the AIP loaded. The
custom clones are absent from it even though the producer in that very arm
offers them and `ODFPROBE` instantiates them successfully.

So the AI's name universe is a fixed enumeration built by `PREREQ_Init` from
`Units_Init`'s `vehicleClassList`/`buildingClassList`. A custom ODF name can
never resolve, and every account node, force-matching entry and
building-matching entry naming one is dropped at AIP load time. Scoring,
ordering, eligibility, producer classification and list iteration are all
exonerated. Full address map and method in
`aip_construction_program_resolution_20260902.md`.

**The reported direction is contradicted.** The roadmap records the AI building
*only the custom* units; what reproduces is the AI building *never the custom*
units. This should be re-confirmed against the original reporter's setup before
any selection routine is patched.

Two harness facts were required to get any signal at all, and both produce
silent zeros: `SetAIControl` must run at Lua chunk scope, and `Build()` issued
while the producer reports `IsBusy` is dropped without error. The full list is
in `test_missions/lcbench_roadmap/README.md`.

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
and rejection reason, and final ODF selection. That gate is now satisfied at the
only stage that turned out to matter: the `[AIPRES]` probe records the request
identity and the rejection reason for every construction-program item, and the
matched `allc`/`alls` pair settles the question before eligibility or selection
is ever reached. The remaining arms are retained as regression coverage rather
than as competing hypotheses.

## 3. Neutral unit attack/order asymmetry

| Evidence field | Finding |
|---|---|
| Status | Legacy UI behavior with an opt-in explicit-order enhancement |
| Reproduction | `run_lcroad_neutral.ps1`; `n2p`, `a2n`, `a2e`, and `a2f` |
| Runtime evidence | Redux accepts and executes both neutral-to-player and ally-to-neutral Lua/native attacks |
| Static/RE evidence | 1.5 `ControlPanel::Render` uses `Team::EnemyP`; that predicate excludes team 0 |
| 1.5 comparison | Static source establishes the same normal command-UI restriction |
| Root cause | The target-list/UI predicate omits neutral objects; the AI task itself does not |
| Patch | `[Gameplay] AllowNeutralAttackOrders=0`; hook only the current `ControlPanel` target-list `Team::EnemyP` call |
| Qualification | Four directed arms completed with enemy and friendly controls |
| Remaining risk | MP host/client UI-issued order qualification remains; no packet or authority change is introduced |
| Roadmap recommendation | Ship disabled by default as a narrow gameplay toggle, not as a regression fix |

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

The exact Redux owner is now identified at the sole `Team::EnemyP(int)` call in
the current `ControlPanel::Render` attack-target candidate scan. The opt-in
hook preserves every stock-accepted target and additionally accepts only team
0 when `AllowNeutralAttackOrders=1`. It does not change `Team::EnemyP`, global
team relations, autonomous target acquisition, AI diplomacy, command IDs, or
network serialization. Default 0 exactly preserves the legacy UI rule.

Qualification still requires a player-authored order in MP host and client
roles. The existing four-arm matrix already proves that the downstream attack
task and damage path can execute against team 0.

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
leaving exact evidence gates for the other four. Follow-up implementation adds
two fail-closed exact-call-site patches to `patches.json`: the pilot carrier
guard and the neutral target-list policy hook.

Final repository and live-state checks:

- Release Win32 solution build: passed; `bin/Release/winmm.dll` produced.
- Engine-independent CTest suite: 20/20 passed, including the narrow safety and
  target-policy unit cases.
- INI/config tests: 23/23 writer checks and 41/41 preset-migration checks
  passed; conservative/default completeness checks passed.
- `luac -p`: both `rmpilot.lua` and `rmneut.lua` passed.
- Fixture filename audit: every basename is at most eight characters.
- Live `addon/lcbench`: all 18 files match the pre-pass backup by SHA-256 and
  there are no overlay extras.
- The harness's orphaned windowed `Ogre.cfg` was restored from
  `ogre.cfg.bzrharness-backup`; no harness backup remains active.
