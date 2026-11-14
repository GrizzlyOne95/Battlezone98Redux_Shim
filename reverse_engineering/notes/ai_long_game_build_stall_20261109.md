# AI stops building after ~60 min: candidate ranking (Redux 2.2.301 GOG)

Status: static analysis only. No game launched, no code written. Companion to
`constructor_remote_build_bug_notes_20260319.md` and the draft PR #772
(`AIConstructionCounterRepair`, `src/patches/ai_construction_counter_repair.cpp`).

Citation key. `R:<addr>.c:<line>` is
`reverse_engineering/repo_corpora/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/FUN_<addr>-<addr>.c`
(shipping GOG exe, ghidrecomp). `1.5:<line>` is
`Battlezone_Source/BZ1/1.5/all_decompiled.c` (named PDB build). Anything
without a citation is marked UNVERIFIED.

Name map used (1.5 name = Redux address, matched by body and by strings):
AIBuild_ConstructionBegin = 0x00690570, End = 0x006905D0,
AIBuild_BuildListWhatToMakeWith = 0x00690FC0, AI_UnitAdd(End+init) = 0x0068FAC0,
AI_UnitAdd(init only) = 0x0068FB10, AI_UnitRemove = 0x0068FC60,
AI_BuildingStalled = 0x0068FE40, AI_SpentCreditRefund = 0x00690020,
AI_SpentCreditRemove = 0x0068FFB0, AIBuild_ReservedAreaAdd/Remove =
0x00690870/0x00690920, AISchedule_Simulate = 0x006A3490,
Build_ConstructUnit/Build = 0x006A4230/0x006A4380, UnitAttachment ctor =
0x006A0FA0, BuildAttachment ctor = 0x006A1820, Producer::StartBuild =
0x005AECB0, Team::AddScrap = 0x005E1010.

## What the planner needs in order to issue a build (how it can go quiet)

A node is only put in the build list when `HowMany(type) + number_under_construction[team][type] < wanted`
(NUMBER_TO_HAVE: R:006912b0.c:18-21; RATIO_TO_HAVE: R:00691450.c uses the same sum;
1.5 equivalent 1.5:311675). The list is rebuilt from scratch every AI tick
(R:00690e80.c:11, `nodes = 0`), capped at 40 nodes (R:00690df0.c:9), so list
size does not accumulate. A node is then consumed only if `credit[account] >= cost`
(R:00690fc0, the `FUN_00690d20` cost compare) and, for buildings, a site is found.
So the only state that can silently saturate over a long game is:
(1) `number_under_construction` (uc), (2) the reserved-area slots, (3) the AI's
private credit mirror, (4) lifetime "number to build" tokens in the AIP nodes.
Everything time-based (below) checks out clean.

## Ranked candidates

### 1. Begin without a matching End, per completed building-type node (uc leak). Confidence: static path verified; live UNVERIFIED

Status (2026-11-09):
- Static: the CNST idle check FUN_006a3490 (R:006a3490.c:37-48) takes the success
  branch at 0x006A35E0 and calls `AIBuild_UnassignedCCAdd` (0x00690770) at
  0x006A35F5 with no `AIBuild_ConstructionEnd` before it. The stalled-crew path
  is the only crew path that Ends (R:0068fe40.c:11, `End(team, *(undefined4*)(rec+0x30))`),
  so the prereq is a 4-byte read.
- Live (inconclusive): in two 7-minute ccak runs with `TraceAIBuildLedger=1`
  (baseline and with the fix), kind=1 prereqs 46/47 logged a Begin and no End,
  but the constructor never finished a building in either run (no building
  BUILT event, 400 scrap unused), so neither End path (FUN_006a3490 line 41 or
  line 44) was reached and the hook did not fire. A run where a constructor
  actually completes a building is still needed: look for
  `[AICOUNTER] Constructor finished building` in openshim.log.
- Side finding (UNVERIFIED cause): in the ccak case the constructor holds its
  prereq for minutes without building, which by itself pins uc=1 for that type.
- Fix (PR #772): `AiBuildCnstDoneCCAddCall` redirects the call at 0x006A35F5 to
  a hook that Ends once (guarded: team range, prereq <= 0xFFFF, count > 0) and
  then forwards to `UnassignedCCAdd`. The stalled path's own call site is not
  redirected, so there is no double End.

Verified facts:
- `AIBuild_ConstructionBegin` is called from exactly one place, the shared node
  consume step (R:00690fc0.c:45). It runs for unit nodes and for building nodes
  (building = prereq kind byte 1; FUN_006A05C0).
- `AIBuild_ConstructionEnd` (0x006905D0) has exactly five callers in the whole
  exe: R:0068fac0.c:6 (new unit object), R:0068fc60.c:~37 (assigned crew shot
  dead), R:0068fe40.c (stalled crew), R:006a4230.c and R:006a4380.c (Build_Construct*
  failure paths). A grep of every decompiled function for `FUN_006905d0` returns only those
  files. The 1.5 building hooks that call End (`AI_BuildingCompleted`,
  `AI_BuildingRemove` order 3, `...RemoveUnderConstruction/Upgrade`,
  1.5:307339-307420) have **zero callers in 1.5** (grep of all_decompiled.c finds only
  their definitions) and their strings do not exist in Redux at all. So they are
  dead in both builds.
- The unit path ends the count in the UnitAttachment ctor (R:006a0fa0.c:50-51,
  after the "bump to 1 if 0" guard at R:006a0fa0.c:44-48, 1.5:327976-327983).
  The attachment iterator that creates those only visits crafts that are not
  FACT/RCYC/ARMR and not TURR (R:006a3ad0.c:16-19; 1.5 `IsUnit`, 1.5:326768).
- Structures, turrets and the three building-vehicles get a **BuildAttachment**
  (R:006a1820.c) whose ctor only does `PREREQ_Add` (R:006a1820.c:28) and never
  calls End (1.5 ctor, 1.5:326668, identical). The class split is the one in 1.5
  `IsBuilding(GameObjectClass*)` (1.5:324139).
- The successful end of a crew's build (R:006a3490.c:38-46: crew not busy and
  `cc_constructing` set) only calls UnassignedCCAdd (R:00690770) and zeroes
  +0x30/+0x34/+0x38. No End, no ReservedAreaRemove.

Prediction if no other End exists: every completed structure/turret/factory/
armory/recycler leaves uc[team][type] one higher forever, so a type with wanted
count N stops after N builds counted over the whole game, not N alive at once.
Destroyed buildings are rebuilt only until `HowMany + uc` reaches N, then never.
That is a cumulative, time-correlated stall that hits most AIP content.

Conflict with the report: the user says rebuilding destroyed factories works.
If End really never fires for building nodes, a wanted-1 factory type would not
rebuild. So either the factory type has wanted > 1 / is RATIO, or there is an End
path I did not find. This is why the first live check (below) is a 5-minute
check, not a 60-minute one.

Other leak paths into the same counter, in order of how often they can happen:
- 1a. PR #772 coverage gap. The PR ends the count only if the record's cached
  state (+0x20) still reads 3 at destruction. Producer::Simulate cancels the
  build when the object's flag 0x200 is set (1.5:217266, Redux equivalent
  R:005ac580.c, calls FUN_005aed80 CancelBuild), after which IsBusy is false and
  the per-tick refresh (R:006a1590.c, state calc lines ~58-80) rewrites the
  cached state to 1 or 0xB. If an AI tick runs between the cancel and the record
  destruction the PR sees 1, not 3, and does not End. UNVERIFIED ordering;
  cheap to avoid by tracking "last prereq issued" independent of the cached state.
- 1b. Unit created but the AI never sees it (killed or consumed before the
  attachment iterator visits it). Rare. UNVERIFIED.
- 1c. Unit whose object field +0xA8 is > 0 at attachment creation (the "special
  force" flag, R:006a0f70.c = `0 < *(obj+0xa8)`, 1.5 equivalent reads +0xAC,
  1.5:324221). The ctor still bumps 0->1 (R:006a0fa0.c:44-48) but skips End
  (R:006a0fa0.c:50), and the later flip back to alive goes through
  FUN_0068fb10, which has no End (R:006a3490.c:28-31). Net +1 permanently, but
  only when uc was 0 and only for flagged units. Meaning of +0xA8 not established
  (UNVERIFIED); 1.5 uses it for scripted special forces, so likely rare.
- 1d. Producer::StartBuild result ignored. See candidate 3.
- 1e. REFUTED LIVE: "producer-built TURR/FACT/RCYC/ARMR never End".
  - Static reading (kept for reference): the unit iterator filter FUN_006a3ad0
    rejects FACT/RCYC/ARMR (R:006a3ad0.c:15, R:006a07e0.c:6) and TURR
    (R:006a3ad0.c:19); those objects get a BuildAttachment whose ctor only calls
    PREREQ_Add (R:006a1820.c:28).
  - Live ledger, ccak bench, 380 s, 2026-11-09, repair off and on: every svturr
    (prereq 21, 4 builds) and the svmuf build (prereq 33) Begin at 0x00691123
    and End at 0x0068FAFF, the UnitAttachment path (R:0068fac0.c:6). The
    turrettank class does not carry the TURR sig, and a freshly built factory
    is still a unit when its attachment is made.
  - Deploying the recycler and factory Begins building prereqs 46/47 (kind=1)
    that stock never Ends. An experimental BuildAttachment ctor detour ended
    them (1 -> 0), but the AI's behaviour did not change, so it was not kept.
  - Same bench, both runs: after the Defense account filled (T+117) the AI never
    started svtank (Offense, 10 wanted) in the remaining 260 s, with or without
    the repair. The census rules out resources and deployment (every POLL to
    T+379: scrap=400 pilots=50 recycler/factory deployed), and the earlier
    builds rule out a missing AIP or AI control. Most likely bench content
    (e.g. a plan entry such as svslf that cannot be built blocks the order).
    Not evidence about the 60-minute stall: no bench has run past 6 minutes.

### 2. Reserved-area slot leak on successful crew builds (32 slots per team). Confidence: verified mechanism, impact UNVERIFIED

- Pool is 32 flags per team (R:00690870.c:8-11); a full pool returns -1 and the
  build still proceeds (R:00690870.c:19).
- `ReservedAreaRemove` (R:00690920.c) has exactly two callers, AI_UnitRemove
  (R:0068fc60.c:37,42) and AI_BuildingStalled (R:0068fe40.c). Crew build success
  (R:006a3490.c:44-46) never frees the slot; the next assignment overwrites the
  crew's +0x3c with a new slot (R:006925e0.c: `*(local_8+0x3c) = FUN_00690870(...)`), losing
  the id. 1.5 has the same structure (1.5:308489-308516 are the only Remove calls).
- Consequence: after 32 completed facility builds the pool is permanently full of
  ghost rectangles. Site search treats them as blocked
  (`IsAreaReserved`, R:00690950.c; callers R:00691d60.c, R:00692150.c), so
  destroyed-building footprints are never reusable and base space near the
  locator shrinks. When the search finds no free site, `WhatToMakeWith` skips the
  node (R:00690fc0.c:42-43 only consumes on a non-zero location result).
  Affects structure nodes only, not factory-built units. Time-correlated (32
  facility builds is plausible in an hour with turret-heavy AIPs).

### 3. StartBuild failure swallowed in Build_ConstructUnit/Build. Confidence: verified mechanism, low frequency for stock vehicles

- `Producer::StartBuild` returns false when scrap OR pilots are short or the
  producer is already busy (R:005aecb0.c:11-15; 1.5:216079-216100).
- The AI pre-check compares scrap only (R:006a4230.c:24-28), then calls StartBuild
  and **ignores its result** (R:006a4230.c:32, same in R:006a4380.c:32,
  1.5:326947/326996), debits its own credit mirror and returns 1
  (R:006a4230.c:33-36). Result on a silent StartBuild failure: Begin never
  matched (uc +1), credit[0] debited, real scrap unspent, producer idle, so the AI
  retries on the next tick and leaks again.
- Pilots: the AI model has no pilot concept (1.5 `AISchedule_AddPilot` is empty,
  1.5:324723). Stock vehicle ODFs have no pilotCost (checked
  `ISDFC-isriflfp/ivscout.odf`), but person units do (`fspilo.odf: pilotCost = 1`),
  and mods (CR, ISDFC) can set it. Pilots only come back from recycling and
  Barracks/Recycler init (1.5:149707, 1.5:156616, 1.5:218153), never from combat
  losses, so a pilot-cost AIP node would starve over a long game and then leak uc
  every tick. Applies only to nodes whose class has pilotCost > 0.

## Checked and ruled out (with evidence)

- Float game time: time is kept as int milliseconds (`DAT_02cc1b28/30`) and
  converted to float seconds (R:00822ae0.c:38-52). At 3600 s a float32 has about
  0.24 ms resolution, far below a 7-17 ms frame. No overflow before ~24 days.
- AI tick gate: `acc += dt; if (0.016666 <= acc) acc = 0` (R:006a3490.c:16-19),
  resets every tick, no drift. Tick counter `DAT_00931014` is an int, used mod 16
  (R:00696380.c), no saturation at 60 min (216 000 ticks).
- AIP random picker: 140-entry table with wraparound (R:006a0690.c:12-16).
- Build list overflow: regenerated each tick (see above).
- Scrap/credit mirror: the AI hook `FUN_006a3730` only forwards positive deltas
  (R:006a3730.c:`-1 < param_2`), called from both Team::AddScrap variants
  (R:005e1010.c:25, R:005e10f0.c:23). Planner spends (WhatToMakeWith debit,
  Build_Construct* StartBuild, refunds on cancel) are balanced, so the mirror does
  not drift low over time. It can drift high after non-planner spending on the AI
  team (Lua AddScrap with negative values); that makes builds fail the scrap
  pre-check (R:006a4230.c:24-28) and take the refund+End path (clean), not stall.
  `prespent_credits` is only dumped (R:006928f0.c), never read as a gate.
  Facility builds leave `prespent` raised forever (success path never calls
  SpentCreditRemove, R:0068ffb0 callers = 006a4230/006a4380 only) but it gates nothing.
- Team unit counts: `DAT_02ce9b0c` is only written by the attachment ctor/dtor
  (R:006a0fa0.c:40, R:006a11d0.c:~24); nothing in the Redux build path reads it.
- AIP "wait" timers (+0x58C/0x590/0x594) only count down (R:006927b0.c:12-20).
- Object handle table exhaustion: not examined. UNVERIFIED.

## Diagnostics OpenShim can log

### D1 (answers candidate 1 and 3 in minutes): Begin/End ledger plus periodic uc dump

Detour `0x00690570` (Begin) and `0x006905D0` (End), both `cdecl(int team, int prereq)`.
Do not change behaviour. Log one line per call:
`LEDGER B|E team prereq uc_after caller=<return addr> tick=<DAT_00931014>` where
`uc_after = (*(int**)(0x00930FC0 + team*4))[prereq]` read after the original runs.
A histogram of End callers shows which paths ever end each prereq. If building
prereqs show B lines and no E lines after the building completes, candidate 1
(building leak) is confirmed within the first AI build, long before 60 min.

Every 10 s (reuse the PR's 2 s tick throttle, `kLogIntervalMs`), for each team t
with `*(char*)(0x02CE9B18 + t*0x1E0) != 0`:
- `Σ uc[t][p]` over p = 1..(DAT_02ceb7fc-1), and the per-prereq rows where
  uc > 0: `p, kind=*(char*)(DAT_02ceb7e8 + p*0x9c)` (0 unit, 1 building),
  `HowMany=*(int*)(DAT_02ceb7e8 + p*0x9c + 0x1c + t*4)`,
  `canMake=*(char*)(DAT_02ceb7e8 + p*0x9c + 0x6c + t)`, name from the same entry.
- `facilities_under_construction[t]` = `*(int*)(0x02BFDFB0 + t*4)`.
- Invariant to flag leaks: Σ uc should equal (producers currently busy, i.e.
  Producer +0x300 != 0, plus crews with record +0x30 != 0) at all times. A
  difference that persists across samples while the AI is idle is the leak size.
- Reserved-area occupancy: count of non-zero bytes in
  `0x02BFDDB0 + t*0x20 .. +0x20` (candidate 2; 32 means full).
- Planner inputs: team AI struct `ai = *(int*)(0x00920F04 + t*4)`:
  `credit0 = ai+0xBC`, `prespent = ai+0xB8`, `budget_valid = ai+0x240`,
  `nodes = ai+0x264`, plus real scrap `Team+0x16C ^ 0x33333333`, pilots `Team+0x174`
  (max `+0x178`) (R:005e10b0.c, R:005e1220.c, R:005e11b0.c). If nodes > 0 for many
  samples while nothing starts building, the gate is downstream of the list
  (credits, site search, producer state). If nodes == 0 the gate is uc or
  HowMany (candidate 1).
- Per producer record state histogram (0 other, 1 idle, 3 busy, 0xB blocked;
  R:006a1590.c) to prove factories are not stuck busy.

### D2 (candidate 3): StartBuild result trace

Detour `0x005AECB0` (thiscall, producer in ECX, class in stack) and log
`StartBuild fail team scrap pilots cost pilotCost` whenever it returns 0 while
the caller is `0x006A4230`/`0x006A4380` (check return address). Zero lines in a
long run rules candidate 3 out.

## Shape of the fixes (building-node fix implemented in PR #772: call-site redirect at 0x006A35F5)

Candidate 1 (exact pairing, preferred over the PR's cached-state approach):
- Building nodes: on the crew success branch (R:006a3490.c:44) call
  `End(team, record+0x30)` once before the fields are zeroed. The stalled path
  (R:0068fe40.c) already Ends, so guard against a double End (set a flag in a
  detour of 0x0068FE40, or detour at the R:006a3490 call site rather than
  `UnassignedCCAdd`, because `UnassignedCCAdd` is also called by the stalled and
  unit-add paths). Alternative if only per-type correctness is wanted: mimic the
  UnitAttachment ctor in the BuildAttachment ctor (bump-if-zero then End).
- Producer path: record "prereq last issued" when Build_Construct* succeeds (as the
  PR does) and End on dtor regardless of cached state; also End when the producer
  returns to idle without a new unit appearing.
Candidate 2: on the same success branch call `ReservedAreaRemove(team, record+0x3c)`
and set `+0x3c = -1` (the placed building is already excluded by the real-cell
check, R:00691ae0.c), so ghost rectangles never outlive the crew's job.
Candidate 3: check StartBuild's result in 0x006A4230/0x006A4380; on false take
the existing failure path (refund R:00690020, End R:006905d0, order = 1), and
restore the NUMBER_TO_BUILD token (the node counter at node+8 is decremented at
R:00690fc0 via `param_1[local_8*5+0x9e]`; a failed build never restores it).

## Open questions for the user

1. Which AIP and which unit/building types stop? A building (turret, power) vs a
   vehicle stall points at candidate 1/2; a person/pilot unit points at 3.
2. Do destroyed turrets/power plants get rebuilt in the same game? Under
   candidate 1 they stop after N lifetime builds; under 2 they rebuild elsewhere.
