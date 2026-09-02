# AIP Construction Program: Name Resolution Map (Redux 2.2.301 GOG)

Companion to `lcbench_runtime_roadmap_pass_20260901.md` section 2 and to
`test_missions/lcbench_roadmap/README.md`. The fixture matrix localized the
custom-unit AIP failure to "the construction program cannot resolve or select a
custom ODF name"; this document names the exact code that does the resolving,
gives its verified addresses in the shipped GOG executable, and describes the
OpenShim probe now wrapping it.

## Where the names come from

Battlezone 1.5 ships a PDB, and its AIP subsystem is fully named. Redux is a
direct derivative: `AIP_Load_Account` decompiles instruction-for-instruction
against the 1.5 function of the same name. Every Redux address below was taken
from the shipped GOG executable (SHA-256 recorded by the harness), not from the
`redux_unpacked_beta` PDB reference — that PDB is a different build and its RVAs
for these symbols are wrong by roughly 0x10B000, which is exactly why they were
verified rather than trusted. See `redux-pdb-is-advisory-only` in the agent
memory index.

## The pipeline

```
Lua SetAIP(team, "name")
  -> AI_AIPLoad / AIP_load_AIP            parse the .aip via IParse
       -> AIP_Load_UCP                    unit_construction_program[] accounts
       -> AIP_Load_Account                per account: priority levels + nodes
            -> PREREQ_WhatIs(item_name)   ODF NAME -> prereq id   <-- the gate
            -> AIBuild_PriorityLevelNodeIs(account, level, node, id, amount)
       -> AIP_Load_Force_Matching         My_Force_Matchings[].unit_name
       -> AIP_Load_Building_Matching      My_Building_Matchings[].unit_name
  -> AI_Team_Assign_AIP / AIBuild_TeamExecuteConstructionProgram
  -> AIBuild_TeamProcess -> AIBuild_BuildListGenerateAccount
       -> AIBuildListGeneratePriorityLevel_{NUMBER,RATIO}_TO_{HAVE,BUILD}
       -> AIBuild_BuildListWhatToMakeWith -> AIBuild_ProcessUnitConstruction
```

`AIP_Load_Account` is the decisive step. Its inner loop reads `item_name`,
calls `PREREQ_WhatIs`, and **when that returns 0 it logs
`UNKOWN UNIT OR BUILDING TYPE '%s' ADDED TO ACCOUNT '%s'` and skips
`AIBuild_PriorityLevelNodeIs` entirely**. The node is not queued, not scored,
not deferred: it never enters the account. Nothing downstream can recover it.

That engine-side diagnostic goes to `tlog`, which is not wired to BZLogger in
the shipped build — no run in the fixture matrix ever printed it. The probe
below exists to surface exactly that decision.

## Verified addresses (GOG `battlezone98redux.exe`, image base 0x00400000)

| Symbol (1.5 PDB name) | Redux VA | Evidence |
| --- | --- | --- |
| `AIP_Load_Account` | `0x00693520` | contains the only xref to the `UNKOWN UNIT...` string |
| `PREREQ_WhatIs` | `0x006A04B0` | body matches 1.5 `0x00515466` instruction for instruction |
| `AIBuild_AccountNew` | `0x00693380` | called by `AIP_Load_Account` in 1.5 call order |
| `AIBuild_PriorityLevelIs` | `0x00693430` | same |
| `AIBuild_PriorityLevelNodeIs` | `0x006934E0` | same; two-store body matches 1.5 |
| `IParse_Get_Struct_Array_Element_Count` | `0x0069D0A0` | same |
| `IParse_Get_Runtime_Int_Field` | `0x0069CE40` | same |
| `IParse_Get_Runtime_String_Field` | `0x0069CFA0` | same |
| `tlog` | `0x006A5F50` | `(level, fmt, ...)` |
| `"UNKOWN UNIT OR BUILDING TYPE..."` | `0x00893EB4` | `.rdata`, single xref |

`PREREQ_WhatIs` call sites — all three, found by scanning `.text` for `E8`
operands resolving to `0x006A04B0`:

| Call site (the `E8`) | Caller |
| --- | --- |
| `0x00693872` | `AIP_Load_Account` (construction-program items) |
| `0x00693C59` | `AIP_Load_Force_Matching` |
| `0x00693ED9` | `AIP_Load_Building_Matching` |

`AIP_Load_Account` itself has exactly one caller, at `0x00693AA6`.

## The prereq table

`PREREQ_WhatIs` is a linear walk, not a hash lookup:

```
for (i = 1; i < PREREQ_maxassigned; ++i) {
    entry = PREREQ_table + i * 0x9C;
    name  = entry.kind == 0 ? entry.data + 0x14      // unit type
          : entry.kind == 1 ? entry.data + 0x40      // building type
          : <undefined>;
    if (strncmp(argument, name, 0x51) == 0) return i;
}
return 0;
```

Globals in this build: `PREREQ_table` at `0x02CEB7E8`, `PREREQ_maxassigned` at
`0x02CEB7FC`. The probe does not hard-code these — it reads the two `disp32`
operands back out of the resolved function body (guarded on `3B 0D` at +27 and
`A1` at +46), so a build whose data layout moved fails the guard and skips the
census instead of reading a wrong address.

The table is filled once by `PREREQ_Init`, which enumerates
`Units_UnitTypeCount()` / `Units_GetTypePtr(i)` and `buildingtypes[]`. Those in
turn come from `Units_Init`, which walks `vehicleClassList` and
`buildingClassList` — two `std::vector<ObjectClassInfo*>` populated by
`AddObjectClass`. **The AI's name universe is therefore whatever the build tree
reached at init time, not "every ODF on disk".**

## Where the universe comes from: `InitObjectClasses`

`InitObjectClasses` (1.5 `0x0051A19B`) seeds it from exactly four roots:

1. `builders[]` — two 8-character names, the two stock recyclers, each passed to
   `RecurseBuildItem`.
2. **Every craft already in `Craft::craftList` at mission load** whose
   `class_id` is `CLASS_ID_VEHICLE` or `CLASS_ID_HELICOPTER`, added with
   `buildClass = nullptr`. This is what "the AIP expects a recycler at mission
   load" means in code: an object the mission *starts* with is enumerated, and
   one a Lua script spawns later is not.
3. `defaultObjClass` = `apcamr`.
4. Two mission-named ODFs: `"b_" + <first 6 chars of the mission filename>` and
   `<first 8 chars of the mission filename>`. For `lcbench.bzn` those are
   `b_lcbenc.odf` and `lcbench.odf`.

`RecurseBuildItem(name)` opens `<name>.odf` and branches on one key:

- **`[GameObjectClass] classLabel` present** → the file names a real object.
  `AddObjectClass(Find(name), nullptr)` and stop.
- **absent** → the file is a list. Read `[Builder] buildItem1..N` and recurse
  each.

Those four `ParameterDB` hashes are FNV-1a/32 (lowercased, basis `0x811C9DC5`,
prime `0x01000193`) and were confirmed by computation, not guessed:
`GameObjectClass` = `0xD3DD9CEC`, `classLabel` = `0x92D04727`,
`Builder` = `0xE4350540`, `buildItem` = `0xF1915444` (the digit is appended to
the seeded hash).

`AddObjectClass(objClass, buildClass)` then registers the pair and, when
`objClass` is a `CNST` or a building-vehicle, recurses **`buildItem` slots 0..8
only — nine of them**. `Units_Init` later calls `SetMaker` for every entry whose
`buildClass` is non-null, and `SetMaker` writes a *single* `makers[0]` slot.

## The OpenShim probe

Three `REL32` call-site patches, all wrapping the same original and all pure
pass-throughs — the stock return value is handed back untouched, so installing
them cannot move a build decision:

- `AIP Prereq Name Resolve Probe` (account)
- `AIP Prereq Name Resolve Probe Force Matching`
- `AIP Prereq Name Resolve Probe Building Matching`

Each verifies callee identity against the `PREREQ_WhatIs` resolve entry before
patching and stands down otherwise, the same fail-closed contract the pilot and
neutral-order hooks use.

Enable with `[Diagnostics] AipResolveTrace=1` in `openshim.ini` (default off),
or run the fixture harness with `-AipResolveTrace`, which sets and restores the
key alongside the mission fixtures. Output:

```
[AIPRES] prereq universe: count=N
[AIPRES]   id=1 kind=unit name='svfigh'
...
[AIPRES] account item='svfigh' -> id=12
[AIPRES] account item='mxfigh' -> id=0  MISS (entry discarded)
```

The census is emitted once, on the first lookup of a mission, so it reflects the
universe as it stood when the AIP was loaded. Both the census flag and the
512-line budget reset on the mission lifecycle seam.

## Reading a result

- **Names resolve but nothing is built** — resolution is exonerated; move the
  investigation to `AIBuild_BuildListGenerateAccount` and
  `AIBuild_BuildListWhatToMakeWith`.
- **The custom name misses and is absent from the census** — confirms the
  enumeration hypothesis above. The fix belongs at `AddObjectClass` /
  `Units_Init` / `PREREQ_Init`, before the table is frozen, not in the AIP
  loader.
- **The custom name misses but IS in the census** — the mismatch is in the
  comparison itself (`strncmp` against the wrong field for that entry kind).

## Result: 2026-09-02, `alls` / `allc` matched pair

Evidence:
`openshim_test_results\lcroad_aip_20260902_033933\{alls_r01,allc_r01}\openshim.log`.
Both arms are the same mission, the same producer and the same AIP shape; the
only difference is whether the file names stock ODFs or the custom clones.

```
alls  [AIPRES] account item='svturr' -> id=21
      [AIPRES] account item='svfigh' -> id=22
      [AIPRES] account item='svfigh' -> id=22
      [AIPRES] force_matching    item='svfigh' -> id=22
      [AIPRES] building_matching item='svrecy' -> id=45
      -> 6 units built

allc  [AIPRES] account item='mxturr' -> id=0  MISS (entry discarded)
      [AIPRES] account item='mxfigh' -> id=0  MISS (entry discarded)
      [AIPRES] account item='mxfigh' -> id=0  MISS (entry discarded)
      [AIPRES] force_matching    item='mxfigh' -> id=0  MISS (entry discarded)
      [AIPRES] building_matching item='mxrecy' -> id=0  MISS (entry discarded)
      -> 0 units built
```

The census is **identical in both arms** and contains exactly 53 names:

```
avscav aprepa apammo avturr avfigh avtank avltnk avhaul avartl avmine avrckt
avapc avhraz avwalk apcamr apwrck avcnst svscav sprepa spammo svturr svfigh
svtank svltnk svhaul svartl svmine svrckt svapc svhraz svwalk spcamr svcnst
player avrecy avmuf avslf abspow abtowe abcomm abbarr absilo absupp abhang
svrecy svmuf svslf sbspow sbtowe sbcomm sbbarr sbsilo sbsupp sbhang
```

That is the two stock races plus `player`, and nothing else. It does not vary
with the mission's ODFs, with the producer's build list, or with which AIP is
loaded — `mxfigh`, `mxturr` and `mxrecy` are absent from both arms even though
`allc`'s own producer offers them and `ODFPROBE` instantiates them successfully.

That is the whole universe reachable when **no producer exists at mission
load** — the fixture spawns its producer from Lua, which is after
`InitObjectClasses` has already run.

## Result: 2026-09-02, load-time seeding

The original reporter's note that "the AIP expects a recycler at mission load —
if you just put a useless rec somewhere on a geyser offmap you'll see that it
works" names root 2 above. The fixture reaches the same seeding through root 4
instead, without editing the BZN: `lcbench.odf` is a `[Builder]` list naming
`mxrecy`, deployed by `run_lcroad_aip.ps1 -SeedBuilder`.

With the seeder present the census grows from 54 to 56, gaining exactly
`mxfigh` (id 35, unit) and `mxrecy` (id 56, building), and `allc`'s items now
resolve:

```
[AIPRES] account item='mxfigh' -> id=35
[AIPRES] account item='mxturr' -> id=0  MISS (entry discarded)
```

`mxturr` still misses, and that turned out to be a fixture authoring error, not
an engine defect. `ProducerClass`'s ODF parser at `0x005B03C0` reads exactly
**nine** build items — `buildItem1`..`buildItem9`, into
`GameObjectClass + 0x608 + i*4` — and every consumer (`AddObjectClass`, the
build menu at `0x005AE660`, the menu-flag scan at `0x004A0160`) iterates the
same nine. Menu position 10 is the reserved back/exit button. So
`buildItem10 = "mxturr"` in `mxrecy.odf` was never parsed, never displayed and
never buildable by anyone; there is no tenth slot to lose.

## Result: 2026-09-02, the reported bug reproduced

With the custom producer (`mxrecy`) deployed for the AI team and the seeder on,
all four arms resolve every name they use. What differs is what gets built:

| Arm | AIP Offense account | Resolution | Built |
| --- | --- | --- | --- |
| `cpc` | custom only | `mxfigh` -> 35 | **4 custom** |
| `cps` | stock only | `svfigh` -> 22 | **0** |
| `cpms` | mixed, stock first | both resolve | **0** — the account stalls |
| `cpmc` | mixed, custom first | both resolve | **4 custom, 0 stock** |

`cpmc` is the reported defect verbatim: *"When you mix custom and stock units in
a custom producer, the AI will only build the custom units, even when stock
units are defined in the AIP."* `cpms` shows it is worse than reported — put the
stock entry first and the account produces nothing at all.

**Mechanism.** `SetMaker` writes a *single* `makers[0]` slot per unit type, from
the `buildClass` recorded when `AddObjectClass` registered the pair. The stock
unit is registered under the stock recycler by `builders[]`, so its one maker is
the stock recycler — a team holding only the custom producer can never build it,
and `AIBuild_BuildListWhatToMakeWith` finds nothing to make with. The custom unit
is registered under the custom producer and builds normally. That is also
exactly why the reporter's workaround works: cloning the stock ODFs makes them
new classes, registered under the custom producer, so they inherit it as their
maker.

## Two defects, not one

1. **Never enumerated.** A custom ODF that no load-time build tree reaches is
   absent from the prereq table; `PREREQ_WhatIs` returns 0 and
   `AIP_Load_Account` discards the node. **Not patched.** Modders have a clean
   workaround already: a mission-named `[Builder]` ODF, or a producer placed in
   the BZN.
2. **Single maker slot.** Even once enumerated, a class carries one maker.
   **Patched** — see below.

Both are Dark Reign-derived stock BZ1 code, present identically in 1.5.

## The fix: `[Fixes] AiMultiProducerMakers`

The naive fix — make `SetMaker` append instead of overwrite — does nothing on
its own, because `SetMaker` is never called with the second producer.
`FindObjectClass` at `0x006A2150` keys the class list on the **built class
alone**: a second `AddObjectClass(svfigh, mxrecy)` finds the existing
`(svfigh, svrecy)` entry, sees its build class already set, and returns. The
pair never reaches `Units_Init`, so nothing ever asks `SetMaker` for it.

So the fix has two halves, both exact-call-site `REL32` hooks:

- **`AI Multi Producer Maker Collect`** wraps the `FindObjectClass` call at
  `0x006A220F`, inside `AddObjectClass`'s prologue. A true return with a
  non-null build class is precisely the pair stock drops; record it.
- **`AI Multi Producer Maker Apply`** wraps the `Units_Init` call at
  `0x006A1AE4` — the last call in `0x006A1AC0`, and `PREREQ_Init` does not run
  until `0x006A1AF0`. Run stock `Units_Init` first so `makers[0]` is filled
  exactly as before, then append each recorded pair's `GetPrereq(buildClass)`
  into the first free slot.

`makers[]` is four wide in both type structs (unit `+0x66`, building `+0x16`),
`PREREQ_Init` copies all four behind a zero terminator, and
`PREREQ_CanThisMakeThat` walks to that terminator — so slots 1..3 were already
consumed by stock code. Nothing but `SetMaker`'s single write was stopping them
from being populated. Slot 0 still goes to the first registrant, so
`PREREQ_Init`'s `canmake` flag is computed exactly as before.

Six named resolves back it (`AI FindObjectClass`, `AI Units_Init`,
`AI IsBuilding`, `AI Class2UnitType`, `AI Class2BuildingType`, `AI GetPrereq`);
if any one fails to verify, both sites stand down and stock registration runs.

### Measured effect

All arms seeded, custom producer, identical config, one repeat each:

| Arm | fix OFF | fix ON |
| --- | --- | --- |
| `cps` stock only | 0 | **4 stock** |
| `cpms` mixed, stock first | 0 | **4 stock + 1 custom** |
| `cpmc` mixed, custom first | 4 custom, 0 stock | **4 custom + 1 stock** |
| `ccak` shipped `ccatank.aip` | 0 | 2 stock + 6 `svscav` + 1 `svcnst` |

13 extra makers registered in each. Unseeded — the closest thing here to stock
content — the fix registers 5 extra makers, `sps` is identical either way, and
`ccak` produced one extra `svfigh` inside the 90-second window (1 event vs 2).
That is a single repeat against an unmeasured noise floor, so treat it as "small
but not nil" rather than as a quantified regression.

Also still open, reported separately and not yet investigated: **the AIP stops
running after roughly an hour regardless of available resources, and calling
`SetAIP` again restarts it.**
