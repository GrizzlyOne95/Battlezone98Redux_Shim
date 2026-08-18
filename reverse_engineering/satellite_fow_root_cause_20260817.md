# Satellite fog-of-war: legacy behaviour, Redux comparison, root cause

Date: August 17, 2026
Scope: feature item 24 — restore Battlezone 1.5 satellite intelligence behaviour.
Method: static analysis only. No live process was run for this pass.

Supersedes the target selection in `satellite_fow_static_handoff_20260323.md`.
That note's high-level theory survives; several of its specifics do not, and two
address constants it relied on turn out to be wrong (section 11.1).

Sources used:

- `reverse_engineering/decompilation_from_1.5_exe-pdb/1.5/` — exact 1.5 decompile
  with imported PDB symbols, one file per function, plus `function_index.tsv`.
- `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\battlezone98redux.exe`
  — shipped GOG image, image base `0x00400000`, unencrypted, used for every
  Redux address in this document.
- `reverse_engineering/repo_corpora/bzr_gog_best_effort/pdb_reference/` — advisory
  Redux PDB export. **`reference.json` reports `match/guid_matches = False`**, so it
  is used here only as evidence of *what code exists*, never for addresses.

---

## 1. Legacy 1.5 behaviour

Legacy satellite fog of war is **object-level only**, computed from **current
radar/scanner detection**, expressed through a single float per object, and
enforced at exactly one place: the overview entity submission function.

The model in full:

| Object situation | Legacy result |
| --- | --- |
| Own team, or any team `FriendP` considers friendly | always visible |
| Marked `isObjective` | visible to **all 16 teams** unconditionally |
| Inside a scanner's range, not jammed | visible while in range |
| Current target of any scanner owner | visible (targeting reveals) |
| Left scanner range | fades over ~1 s, then hidden |
| Building (class category 2) | **sticky** — once seen, never re-hidden |
| Person/pilot (class category 4) | never detected by a sweep at all |
| Jammed (`Jammer::IsJamming`) | not detected |
| Scrap / ordnance / game features | never fogged; submitted separately |
| Terrain | never fogged |

Three points are easy to get wrong and matter for any patch:

**There is no "previously discovered" memory for mobile units.** `seen` is
maintained but `GameObject::HasBenSeen` (`0x0045A021`) has **zero callers** in the
1.5 image. `seen` is written by three functions, serialised by `Save`/`Load`, and
never read for a gameplay or rendering decision. Persistence of discovery exists
only as the building special case below.

**Building persistence is a side effect, not a feature flag.**
`Scanner::BasicVisibility` skips the per-frame reset for class category 2, so a
building's `isVisible` bits are never cleared once set. Mobile units are reset
every frame and re-established by the sweep.

**`unlimitedRadar` cannot apply in multiplayer.** `UserPref_unlimitedRadar`
(`0x004ADA4E`) returns 1 only when `Net_IsNetGame() == 0` *and*
`UserProfilePtr->playOption & 0x200`. The MP path is structurally excluded.

---

## 2. Exact 1.5 functions and control flow

### 2.1 State production — once per simulation tick

`Simulate` (`0x004789C5`) calls exactly one of two functions:

```
Simulate()
  if (!UserPref_arcadeMode())
      ... ClassSimulateAll / Update_Camera / GameObject_UpdateRange ...
      GameObject_ComputeVisibility()        // 0x004980AC   <- normal path
  else
      GameObject_MarkAllVisible()           // 0x004981BB   <- arcade only
```

`GameObject_MarkAllVisible` sets `illumination = 1.0` and `isVisible = 0xFFFFFFFF`
on every object. Arcade mode therefore has no fog of war by design.

`GameObject_ComputeVisibility` (`0x004980AC`):

```c
Scanner::BasicVisibility();                       // 0x004AE19D  reset + team bits
for (Scanner* s : Scanner::scannerList)
    Scanner::SweepVisibility(s);                  // 0x004ADC08  radar sweep

float dt   = TimeStep();
long  team = GameObject::userTeamNumber;

for (GameObject* o : *GameObject::objectList) {
    if (o->vtable[1]() < 0) {                     // GetTeam() < 0
        o->illumination = 0.0f;
        continue;
    }
    GameObject::AssignColor(o);
    if ((o->isVisible >> team) & 1)
        o->illumination = 1.0f;                   // currently detected
    else if (o->illumination <= dt)
        o->illumination = 0.0f;                   // fade complete
    else
        o->illumination -= dt;                    // linear fade, ~1 s
}
```

`illumination` is therefore a per-object, **user-team-relative** scalar in
`[0,1]`: 1.0 while detected, decaying linearly to 0 over one second after
detection is lost.

`Scanner::BasicVisibility` (`0x004AE19D`), per object:

```c
if (o->obj->flags & 1) {                          // not in world
    o->isVisible = 0;
    if (o->obj->flags & 0x10)  { o->isVisible |= 1<<own; o->seen |= 1<<own; }
}
else if (o->objClass->category != 2) {            // category 2 == BUILDING: skipped
    if (!o->isObjective) {
        o->isVisible = 0;                         // reset
        o->isVisible |= 1<<own;  o->seen |= 1<<own;
        for (t = 1; t < 16; ++t)
            if (GameObject::FriendP(o, t)) { o->isVisible |= 1<<t; o->seen |= 1<<t; }
    } else {
        o->isVisible = 0xFFFFFFFF;                // objectives: visible to all
    }
}
if (UserPref_unlimitedRadar()) {                  // SP only
    o->isVisible |= 1<<userTeam;  o->seen |= 1<<userTeam;
}
```

`Scanner::SweepVisibility` (`0x004ADC08`), per scanner:

```c
pos  = owner->vtable[3]();                        // GetPosition
team = owner->vtable[1]();                        // GetTeam

if (GameObject* tgt = GameObject::GetObj(owner->targetHandle))
    { tgt->isVisible |= 1<<team; tgt->seen |= 1<<team; }   // target always revealed

if (period > 0) { sweep += TimeStep();
                  if (sweep <= 0) { active = false; return; }   // duty cycle
                  sweep -= period; }
active = true;

Range::Search(GameObject::objectRange, pos.x, pos.z, range, &results);
while (Range_Search_Results::Get_Next_Object(&results, &h)) {
    o = GameObject::GetObj(h);
    if (!o || (o->obj->flags & 1))            continue;   // not in world
    if (o->objClass->category == 4)           continue;   // category 4 == PERSON
    if (o->jammer && Jammer::IsJamming(o->jammer)) continue;
    if (Dist3D_Squared(o->GetPosition(), pos) < range*range)
        { o->isVisible |= 1<<team; o->seen |= 1<<team; }
}
```

Category constants were confirmed by cross-referencing every `objClass+0x28`
comparison in the image: `== 2` appears in `Building_DamageAlloc`,
`Building_Explode`, `ConstructionRig_GetCommand` and `BettyVoice_BuildingLost`;
`== 4` appears in `KickEnemys`, `SniperInterface_Simulate` and every craft
`UpdateModeList`.

### 2.2 The visibility predicate

`GameObject_IsVisibleToUser` (`0x00496888`) — the entire predicate:

```c
int GameObject_IsVisibleToUser(_OBJ76 *e) {
    void *g = e ? e->gameObj : 0;
    return (g && 0.0f < *(float*)((char*)g + 0xDC)) ? 1 : 0;   // illumination > 0
}
```

It has exactly **one caller**: `Submit_Overview_Entities`.

---

## 3. The legacy satellite rendering path

This is the finding that reframes the problem. `Render_Hardware_Next_Frame`
(`0x004783FF`, and identically `Render_Software_Next_Frame` `0x00478536`):

```c
Submit_Terrain_Mesh(cam);                       // terrain: never fogged
if (View_Record.Current_View == OVER_VIEW)
    Submit_Overview_Entities(cam);              // 0x004EA805  <-- gated
else
    Submit_All_Entities(cam, exclude);          // 0x004EB693  <-- NOT gated
Ordnance_SubmitAll(cam);                        // outside the fork: never fogged
Submit_Scrounge_Objects(cam);                   // scrap: never fogged
GameFeature_SubmitAll(cam);                     // never fogged
```

`Submit_Overview_Entities` (`0x004EA805`):

```
for each entity in world[0 .. world_count):
    entity->mergeNext = entity->mergePoly = NULL
    if (entity->obj76 && GameObject_IsVisibleToUser(entity->obj76))    <-- THE GATE
        ... frustum test, ZSORTAdd ...
```

`Submit_All_Entities` (`0x004EB693`) was read in full: it performs the bounding
sphere and frustum tests, the dynamic/static split, `ComputeRenderQuality` and
`MergeAndAdd` — and contains **no reference to `illumination`, `isVisible`,
`seen`, or `GameObject_IsVisibleToUser`**.

So the complete legacy layering is:

```
Simulate            -> GameObject_ComputeVisibility -> illumination (per user team)
Render (OVER_VIEW)  -> Submit_Overview_Entities     -> IsVisibleToUser -> illumination > 0
Render (other)      -> Submit_All_Entities          -> no gate at all
```

Fog of war in 1.5 is **not a simulation-level concealment system**. It is a
render-submission filter that exists only in the overview branch. The gameplay
state (`illumination`) is computed unconditionally every tick and simply ignored
by the first-person renderer.

The same predicate is reused verbatim by the HUD panels — `MapRadar::Render`
(`0x004D2395`) and `CockpitRadar::Render` (`0x004C05B7`) both test
`0.0 < obj->illumination` before emitting a blip and then index a 16-entry colour
ramp by `illumination * 15.0`, which is what produces the radar fade.
`BuildTerrainOverview` (`0x00520D2A`) and `OverView::Render` (`0x004D37B2`) were
both checked and contain **no** visibility gate; `OverView::Render` is input,
selection, command and camera logic only.

---

## 4. Redux equivalents and what changed

### 4.1 Confirmed Redux ground truth (shipped GOG image)

`GameObject::Save` passes each field name as a literal to `::out(file, &field, size, "name")`.
Locating those strings in `.rdata` and their single code cross-reference each
gives the field offsets directly, with no reliance on the mismatched PDB:

| String | `.rdata` | xref | Instruction | Save-base offset |
| --- | --- | --- | --- | --- |
| `illumination` | `0x00879D3C` | `0x004DE199` | `add ecx, 0xE8` | `+0xE8` |
| `perceivedTeam` | `0x00879E2C` | `0x004DE7E0` | `add ecx, 0x180` | `+0x180` |
| `isVisible` | `0x00879CFC` | `0x004DE2D1` | `add eax, 0x18C` | `+0x18C` |
| `seen` | `0x00879CF4` | `0x004DE2F4` | `add eax, 0x190` | `+0x190` |

`GameObject::GetPerceivedTeam` (`0x00462450`) reads `[this + 0x15C]` on the
GameObject *interface* subobject, which fixes the Save base as `interface - 0x24`.
OpenShim independently established that the interface begins at `+0x18` of the
complete object. Both anchors agree, giving:

| Field | Interface-relative | **Complete-object** |
| --- | --- | --- |
| `illumination` | `+0xC4` | **`+0xDC`** |
| `perceivedTeam` | `+0x15C` | **`+0x174`** |
| `isVisible` | `+0x168` | **`+0x180`** |
| `seen` | `+0x16C` | **`+0x184`** |

### 4.2 Redux satellite view entry

`0x0061BD20` is the satellite view setter. At `0x0061BE27`:

```
mov dword ptr [0x008EAAD4], 0            ; previous view
mov dword ptr [0x008EAAD8], 3            ; Current_View = OVER_VIEW
mov dword ptr [0x008EACB8], ecx          ; overview object
mov dword ptr [0x008EAAD0], 0x0061BC90   ; Update_Camera = Set_Satellite_View
```

So the Redux `View_Record` base is **`0x008EAAD0`**, `Current_View` at `+8` =
`0x008EAAD8`. A full cross-reference scan of `.text` found **93** references to
`0x008EAAD8`: 12 compare against 3 (satellite), 12 against 9 (editor), and the
rest against other modes. None of the 12 satellite comparisons sits in an entity
submission loop; the two in the Ogre frame driver (`0x006831D3`, and
`0x00617715`) select HUD/overlay sets and viewport configuration.

### 4.3 What survives, what is missing

| Legacy element | Redux status | Evidence |
| --- | --- | --- |
| `illumination` field | **present** | Save/Load, `+0xDC` |
| `isVisible` / `seen` fields | **present** | Save/Load, zeroed together in ctor |
| `perceivedTeam` | **present** | `GetPerceivedTeam` `0x00462450` |
| `Scanner::BasicVisibility` | present in Redux source | advisory PDB public symbol `?BasicVisibility@Scanner@@SAXXZ` |
| `Scanner::SweepVisibility` | present in Redux source | advisory PDB public symbol `?SweepVisibility@Scanner@@QAEXXZ` |
| `GameObject_ComputeVisibility` | present in Redux source | advisory PDB public symbol |
| `GameObject_MarkAllVisible` | present in Redux source | advisory PDB public symbol |
| `UserPref_unlimitedRadar` | present in Redux source | advisory PDB public symbol |
| `OverView`, `MapRadar`, `CockpitRadar`, `RadarDamper` | **present** | RTTI in `.data` |
| `Scanner` class | **no RTTI found** | see 11.2 |
| `Submit_Overview_Entities` equivalent | **not located** | see 11.3 |

An exhaustive instruction-level scan of `.text` (1,489,189 instructions,
resyncing linear sweep) looked for per-team bit manipulation on the visibility
fields at all four candidate bases (`+0x168`, `+0x16C`, `+0x180`, `+0x184`).
The detector was validated first — across the whole image it finds 4,444
load-then-bit-operation sites spanning 110 distinct offsets — and it returns
**zero** hits at the visibility offsets, with the operation profile at those
offsets consisting exclusively of `mov`/`movss`/`cmp` and float arithmetic.

This is suggestive, not conclusive: those offsets are shared with unrelated
classes, so the float traffic is noise, and the absence of bit work is only
weak evidence against the Scanner pipeline still running. It is recorded here
as an observation to be settled live, not as a proof.

---

## 5. Does the legacy data still exist?

**Yes for the storage; unproven for the production.**

The three fields are allocated, zeroed by the constructor, and round-tripped
through `Save`/`Load` in the shipped image — verified directly. A Redux build's
PDB lists all four producer functions as public symbols, so the visibility
pipeline exists in Redux source. What could not be shown statically is that
`GameObject_ComputeVisibility` is still *called* per tick in the shipped build,
and that its output is non-degenerate.

This distinction decides the fix, and it is exactly what the live probe in
section 9 is designed to answer. **No new fog-of-war database should be built
until that probe has run.**

---

## 6. Root-cause hypothesis and evidence

Against the user's option list, the evidence favours **(C) / (E) jointly**:
Redux retains the fog-of-war *state* but the Ogre-era object submission no
longer consults it.

Supporting evidence:

1. In 1.5 the entire fog of war is one predicate in one function
   (`Submit_Overview_Entities`), and that function's whole reason to exist is the
   gate — its sibling `Submit_All_Entities` is the same loop without it.
2. That function is a ZSORT/software-rasteriser submitter. Redux replaced this
   renderer with Ogre. A renderer swap that dropped the overview-only submitter
   and routed satellite view through the ordinary Ogre scene would remove the
   gate and nothing else — which is precisely the reported symptom (satellite
   shows everything; nothing else about radar or targeting is reported broken).
3. Every *other* member of the legacy cluster survived into Redux with RTTI
   (`OverView`, `MapRadar`, `CockpitRadar`), and the state fields survived. A
   wholesale removal of fog of war would not have preserved `illumination`
   through `Save`/`Load`.
4. None of the 12 satellite-mode comparisons in Redux `.text` sits in a
   per-object submission loop.

Against a simulation-state cause (option D): `Scanner::SweepVisibility`'s
jamming, range and category filters are gameplay-visible through the cockpit and
map radars. If Redux had broken the state globally, the *radar panels* would be
wrong too, since in 1.5 they consume the identical `illumination > 0` predicate.
No such report exists. That argues the state is still broadly correct and only
the satellite presentation layer stopped filtering.

---

## 7. Candidate patch sites, ranked

Ranked by fidelity to 1.5 and risk. **None is recommended for implementation
yet** — see section 8.

**1. Restore the gate at the Redux overview object-submission site.**
Best fidelity: it is the same layer and the same predicate as 1.5. Data used:
`illumination` at complete-object `+0xDC`, exactly as legacy. Crash risk low
(read-only test, fail-closed to "visible"). Renderer dependency: whatever Redux
submits per object in overview mode. Multiplayer risk minimal — `illumination`
is already a per-client, user-team-relative value. Blocked on locating the site
(11.3).

**2. Hook `GameObject_IsVisibleToUser`'s Redux equivalent.** Same predicate,
one function, trivially guarded. Only viable if the function survives and is
still called; if the Ogre path does not call it, hooking it changes nothing.

**3. Filter Ogre object visibility during satellite mode only, driven by
`illumination`.** Reuses surviving state; correct predicate, wrong layer.
Higher maintenance burden and a real risk of leaking into the cockpit view if
the mode test is imprecise. Must key off `0x008EAAD8 == 3` and must restore
visibility on exit.

**4. Re-run / repair the state producers.** Only if the live probe shows
`illumination` is degenerate. Much higher risk: `BasicVisibility` and
`SweepVisibility` write simulation-visible state consumed by AI targeting
(`GetClosestObject`, `HuntTask_Choose_Next_Spot` both read `isVisible`), so
touching them can change AI behaviour and diverge host from client.

**5. Hiding all enemy Ogre entities while satellite is active.** Rejected. It is
not equivalent to 1.5: it would wrongly hide allied, objective, target-revealed
and recently-faded objects, and wrongly reveal nothing that was previously
hidden. It also loses the building-persistence and 1 s fade semantics entirely.

Steam/GOG applicability: both images share base `0x00400000` and section layout;
the GOG copy is unencrypted on disk and the Steam copy is SteamStub-packed but
identical once decrypted, so addresses derived here apply to both. This should
still be re-verified per build with byte guards before any patch ships.

---

## 8. Recommended implementation

**Do not patch the game yet.** Prerequisites, in order:

**8.1 Fix the diagnostic probe — DONE (branch `feature/satellite-fow-probe`).**
The probe was reading the wrong memory, which invalidates every SATVIS sample
taken before 2026-08-17 and is the most likely reason the two earlier passes
stalled. Corrected in `src/patches/bzr_hooks.cpp`:

| Constant | Was | Now | Consequence of the old value |
| --- | --- | --- | --- |
| `kViewRecordRva` | `0x004FD770` | `0x004EAAD0` | `IsSatelliteOverviewActive()` read an address with **zero** code cross-references; the satellite gate never meant anything |
| `kGameObjectIsVisibleOffset` | `0x184` | `0x180` | logged `seen` in the `isVisible` column |
| `kGameObjectSeenOffset` | `0x188` | `0x184` | logged an unrelated field as `seen` |

`kGameObjectIlluminationOffset = 0xDC` and `kGameObjectPerceivedTeamOffset = 0x174`
were already **correct** and are unchanged.

Added, all derived the same way (section 4.1): `kGameObjectIsObjectiveOffset = 0x17D`,
`kGameObjectIsSelectedOffset = 0x17E`.

The probe now also records `perceivedTeam`, the object class type, `isObjective`,
`isSelected`, and three derived booleans so a capture can be scored against the
section 1 table with no post-processing:

```
detected      = (isVisible >> userTeam) & 1     -- scanner pass says detected now
discovered    = (seen      >> userTeam) & 1     -- ever detected (dead in 1.5, see 1)
legacyVisible = illumination > 0                -- the exact 1.5 overview gate
```

The hidden/visible split in the summary now keys off `legacyVisible` rather than
the raw bitmask, so the two buckets mean precisely what 1.5's
`Submit_Overview_Entities` would have decided. Log line:

```
[SATVIS] view=3 userTeam=1 userObj=0x… total=… sampled=… illum=… visible=… seen=… detected=… discovered=… …
[SATVIS]   hidden obj=0x… team=2 perceivedTeam=2 class=1 objective=0 selected=0 illum=0.000 isVisible=0x00000004 seen=0x00000004 detected=0 discovered=0 legacyVisible=0 target=0x…
```

**The trace now defaults ON**, gated by `[Diagnostics] TraceSatelliteVisibility`
in `openshim.ini`, so an ordinary session produces a scoreable capture with no
launch-time setup. This is temporary — it should return to default-OFF once the
regression is characterised. Precedence, most specific first:

1. `[Diagnostics] TraceSatelliteVisibility` — explicit, either direction
2. `OPENSHIM_DISABLE_SAT_VIS` / `BZR_DISABLE_SAT_VIS`
3. the legacy positive `OPENSHIM_TRACE_SAT_VIS` aliases (still honoured, now
   redundant)
4. ON

The INI key is read directly rather than through the env-mapping shim in
`openshim_env_config.cpp`: that shim collapses to `EnvFlagEnabled`, which cannot
distinguish "absent" from "0", and a default-ON option needs that distinction.

The sample budget moved from 8 to 120. Eight was sized for an opt-in probe and
exhausts after eight seconds of cumulative satellite viewing — not enough to
walk the section 9 matrix. Budget is consumed only while the overview is
actually open, and sampling is rate-limited to once per second, so the trace
costs nothing in normal play. `OPENSHIM_SAT_VIS_BUDGET`,
`OPENSHIM_SAT_VIS_INTERVAL_MS` and `OPENSHIM_SAT_VIS_OBJECT_LIMIT` still tune it
and can be set from the INI's `[Environment]` section without a rebuild.

The startup banner now also prints the offsets each capture was produced with,
so a saved log stays interpretable if these are ever revised again:

```
[SATVIS] Satellite visibility trace: enabled budget=120 interval=1000ms objectLimit=96 viewRecord=0x008EAAD0 …
[SATVIS]   offsets illum=+0xDC isVisible=+0x180 seen=+0x184 perceivedTeam=+0x174 objective=+0x17D currentView=… expects=3
```

Release Win32 builds clean.

One caveat: the `class=` value is the Redux class-type enum read at
`objClass+0x1C`. Its mapping onto the legacy category values (2 = building,
4 = person) is **not confirmed**. The first capture containing a known building
and a known pilot establishes it empirically — that is deliberate.

**8.2 Run one live session and answer one question:** is `illumination` still
being produced correctly — 1.0 while detected, fading, 0 when not?

- If **yes** → the regression is presentational. Proceed with candidate 1,
  falling back to 3. This is the expected outcome.
- If **no** → the regression is in state production. Proceed to candidate 4 and
  re-scope; expect multiplayer implications.

Cheapest high-value observation to make in the same session: whether the cockpit
and map radar blips still fade correctly. In 1.5 they consume the identical
`illumination > 0` predicate, so if they behave, the state is intact and the
regression is localised to satellite submission (section 11.6).

**8.3 Exact 1.5 parity specification.** When the patch is written, the whole of
the legacy behaviour reduces to *one* test applied at *one* place. Everything
else in section 1 — allies, objectives, buildings persisting, pilots excluded,
jamming, target reveal, the fade — is already baked into `illumination` by the
producers. Do not reimplement any of it.

```
submit object to the satellite view  <=>  *(float*)((char*)gameObject + 0xDC) > 0.0f
```

Parity rules that follow, and the ways a patch can silently get this wrong:

1. **Test `illumination`, never `isVisible` directly.** Using
   `(isVisible >> userTeam) & 1` would drop the ~1 s fade and produce a hard
   pop-out that 1.5 never had.
2. **Use `> 0.0f`, not `>= ` and not an epsilon.** The producer writes exact
   `0.0f` when the fade completes.
3. **Do not apply it outside satellite view.** 1.5's first-person submitter has
   no gate; hiding objects in cockpit view would be a new bug, not parity.
   Gate on `[0x008EAAD8] == 3`. Editor mode (9) used the same `OVER_VIEW`-ish
   path in 1.5 via `EDIT_VIEW` and was *not* gated — leave editor alone.
4. **Do not gate terrain, scrap, ordnance or game features.** In 1.5 those are
   submitted outside the overview fork and were never fogged.
5. **Do not write `illumination`, `isVisible` or `seen`.** AI targeting reads
   `isVisible` (`GetClosestObject` `0x004093DB`, `HuntTask_Choose_Next_Spot`
   `0x004153FE`); a write is a gameplay change and an MP divergence risk.
6. **Fail open.** If the object pointer, the field read, or the mode test is
   unavailable, submit the object. Stock Redux behaviour is "everything
   visible", so failing open degrades to today's behaviour rather than hiding
   things the player should see.
7. **Nothing extra for multiplayer.** `illumination` is already local and
   user-team-relative; there is no replication to add and none to avoid.

When the branch is opened: byte-guard every site, fail closed to stock, gate on
an INI option defaulted ON for validation, and leave cockpit and radar untouched.

---

## 9. Single-player validation matrix

Scenario: player recycler and radar tower (own team), one enemy inside radar
range, one enemy outside, one enemy previously seen then moved out, one enemy
building, one neutral object, one scrap pool, one nav beacon/objective.

| # | Step | Expected per 1.5 | Notes |
| --- | --- | --- | --- |
| 1 | Enter satellite at mission start | own + allied units visible; enemies outside radar hidden | baseline |
| 2 | Enemy walks into radar range | appears, `illumination` → 1.0 | tests sweep |
| 3 | Enemy walks back out | fades over ~1 s, then hidden | tests the fade, not a hard cut |
| 4 | Same enemy re-enters | reappears immediately | no discovery memory for mobiles |
| 5 | Enemy **building** discovered, then radar lost | **stays visible** | category 2 skip |
| 6 | Enemy pilot on foot inside radar range | **not** visible | category 4 exclusion |
| 7 | Destroy the radar tower, re-enter satellite | mobile enemies hidden; buildings persist | tests scanner list |
| 8 | Objective-marked object anywhere | visible regardless of range | `isVisible = 0xFFFFFFFF` |
| 9 | Scrap pool outside radar range | visible | scrap is never fogged |
| 10 | Terrain outside radar range | fully drawn | terrain is never fogged |
| 11 | Target an enemy outside radar range | becomes visible while targeted | target reveal |
| 12 | Enemy under a jammer inside radar range | not visible | `Jammer::IsJamming` |
| 13 | Neutral (team 0) object | per `FriendP`; record actual | 1.5 semantics to be confirmed live |
| 14 | Cockpit and map radar blips | must match satellite exactly | same predicate in 1.5 |
| 15 | First-person view of a hidden enemy | **still drawn** | `Submit_All_Entities` has no gate — do not "fix" this |
| 16 | Enable unlimited radar preference (SP) | everything visible | `playOption & 0x200` |
| 17 | Arcade mode | everything visible | `MarkAllVisible` |
| 18 | Toggle satellite on/off repeatedly | no leakage into cockpit rendering | mode-gate hygiene |

---

## 10. Multiplayer validation matrix

`illumination` is **local, per-client, and relative to `GameObject::userTeamNumber`**
— it is derived each tick from `isVisible`, which is itself rebuilt from the
local scanner list. Nothing about it is replicated. Restoring the legacy
predicate therefore cannot by itself create host/client divergence, because it
reads a value each client already computes for itself.

| # | Check | Requirement |
| --- | --- | --- |
| 1 | Host and client satellite views of the same map | each shows only its own team's intelligence |
| 2 | Team-shared radar (ally's radar tower) | ally-detected units visible to both — `FriendP` loop must be honoured |
| 3 | Ally units | always visible, never fogged |
| 4 | Enemy building discovered by an ally | persistence must follow the same category-2 rule |
| 5 | Client with no radar unit | sees only own/allied units and objectives |
| 6 | `unlimitedRadar` in MP | must remain inert (`Net_IsNetGame` guard) |
| 7 | Targeting an enemy in MP | reveal must not leak to other clients |
| 8 | Late join / rejoin | visibility rebuilds from local state, no stale reveal |
| 9 | Simulation determinism | no simulation state may be written by the fix |
| 10 | Non-satellite views | cockpit, radar and targeting unchanged |

The fix must not write `isVisible`, `seen` or `illumination`. AI targeting reads
`isVisible` (`GetClosestObject` `0x004093DB`, `HuntTask_Choose_Next_Spot`
`0x004153FE`), so any write is a gameplay change, not a rendering change.

---

## 11. Remaining uncertainties

**11.1 Three OpenShim constants were wrong — now fixed, but unverified live.**
Detailed in 8.1. The `kViewRecordRva` error was the more serious: a `.text` scan
validated against a known-good control (the raw-input flag `0x00918424`, which
reproduced its six known reference sites exactly) finds **zero** references to
`0x008FD770`, whereas the real view record at `0x008EAAD0` is written by the
satellite setter at `0x0061BE27`–`0x0061BE44`. The corrections are derivations
from the shipped image, not observations of a running game; the first live
capture is what confirms them. Expect `view=3` in the summary line while
satellite is open — if it never appears, the view-record correction is wrong and
nothing downstream should be trusted.

**11.2 `Scanner` has no RTTI in the Redux image.** `OverView`, `MapRadar`,
`CockpitRadar`, `GameObject` and `RadarDamper` all do, so RTTI is enabled. In
1.5 `Scanner` has a `scalar_deleting_destructor` (`0x00484C25`) and therefore a
vtable. The advisory PDB shows Redux's `Scanner::BasicVisibility` as `SAX`
(static) and `SweepVisibility` as `QAE` (non-virtual), so Redux's `Scanner` may
simply be non-polymorphic and legitimately RTTI-free. **Unresolved.**

**11.3 The Redux `Submit_Overview_Entities` equivalent was not located.** This
is the single biggest gap and the reason no patch is proposed. The advisory PDB
cannot supply the address (wrong build), the legacy function was file-static so
it has no public symbol, and the local best-effort Ghidra corpus is unreliable
in this neighbourhood — a caveat the March note already recorded and this pass
reconfirmed.

**11.4 No live confirmation of anything.** Everything here is static. In
particular it is unproven that `GameObject_ComputeVisibility` still runs per
tick in the shipped build, and unproven that `illumination` holds sane values.

**11.5 Neutral-team semantics (matrix row 13) were not derived**, only the
`FriendP` call site. Worth reading `GameObject::FriendP` before relying on it.

**11.6 Whether the Redux radar panels still gate on `illumination`** was not
checked. If they do, and they behave correctly in game, that is strong evidence
the state is intact and localises the regression to satellite submission — a
cheap and high-value observation to make during the first live session.

---

ROOT CAUSE:
Battlezone 1.5 implemented satellite fog of war as a single render-submission
filter — `Submit_Overview_Entities` (`0x004EA805`) tested
`GameObject_IsVisibleToUser` (`illumination > 0`) per entity, while the
first-person submitter `Submit_All_Entities` deliberately had no such test.
Redux retains the underlying state (`illumination` at `+0xDC`, `isVisible`
`+0x180`, `seen` `+0x184`, all still serialised by `GameObject::Save`) but its
Ogre-era satellite view no longer applies that per-object predicate, so the
overview submits every entity — the same loop 1.5 used for the *cockpit* view.
The subsystem that stopped enforcing fog of war is the overview object
submission, not the scanner/visibility simulation.

BEST PATCH LAYER:
The Redux equivalent of `Submit_Overview_Entities` — i.e. the per-object
submission step taken while `[0x008EAAD8] == 3` — re-applying
`illumination > 0` read from complete-object `+0xDC`. Second choice: filtering
Ogre object visibility in satellite mode from the same field.

CONFIDENCE:
Medium.

WHY:
High confidence in the legacy model: it was read end to end from the exact 1.5
decompile, including the sibling-submitter contrast that proves fog of war lived
only in the overview branch, and the category-2/category-4 rules that produce
building persistence and pilot exclusion. High confidence in the Redux field
offsets: derived from `GameObject::Save`'s own field-name string
cross-references in the shipped image and independently corroborated by
`GetPerceivedTeam` at `0x00462450`. Confidence is held to Medium — not High —
because the Redux overview submission function itself was not located (11.3),
because no live run has confirmed `illumination` is still produced (11.4), and
because the diagnostic probe that was supposed to answer this has been reading
the wrong address and two wrong offsets (11.1), so no existing SATVIS capture
can be trusted as evidence either way.
