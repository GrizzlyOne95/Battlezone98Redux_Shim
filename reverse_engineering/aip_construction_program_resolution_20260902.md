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
`AddObjectClass`, which recurses a producer's nine `buildItem` slots. **The AI's
name universe is therefore whatever the build tree reached at init time, not
"every ODF on disk".** That is the standing hypothesis for why a custom clone
loads on demand and builds on an explicit `Build()` order yet is never selected
by an AIP: it was never enumerated, so `PREREQ_WhatIs` cannot name it.

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

**Conclusion.** The strategic AI's name universe is a fixed enumeration of stock
unit and building types. A custom ODF name can never be resolved by an AIP,
so every construction-program node, force-matching entry and building-matching
entry naming one is discarded at load time. This is not a scoring, ordering,
eligibility, producer or mixing problem — the AI is never told the unit exists.

This closes the localization in `lcbench_runtime_roadmap_pass_20260901.md`
section 2. Any fix has to widen the enumeration before `PREREQ_Init` freezes the
table; patching `AIP_Load_Account` alone would produce an id that nothing else
in `AIBuild_*` can map back to a buildable class.

The standing caveat still applies: the roadmap reports the AI building *only*
custom units, and what reproduces here is the AI building *never* the custom
units. The direction needs re-confirming against the original reporter's setup
before any fix is designed.
