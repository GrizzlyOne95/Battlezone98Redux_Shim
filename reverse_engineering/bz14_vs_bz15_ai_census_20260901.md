# BZ 1.4 → 1.5 — AI behaviour census

**Date:** 2026-09-01
**Corpora:** `BZ1_Source/1.4` (5722 fns, Shrinker-unpacked, unsymbolised) vs
`BZ1_Source/1.5` `bzone.exe` (14 832 fns, symbolised from exact-match `bzint.pdb`)
**Tooling / raw output:** `BZ1_Source/diff_14_15/`
**Companion:** `bz14_evasive_ai_investigation_20260823.md` — targeted study of the evasive tank AI,
which this generalises

---

## 0. Headline

**`UnitTask` — the shared unit state machine — was rewritten wholesale between 1.4 and 1.5.** It is
the most-changed behaviour class in the game (median similarity **0.289** over 19 reliable
functions), and ten of its state handlers sit in the 30 most-changed AI functions: `DoBlast`,
`UpdateWeapon`, `DoStand`, `DoStuck`, `DoFollow`, `Execute`, `DoFlee`, `GoTowards`, `DoSit`,
`GoHeading`.

**Pathfinding was replaced, not edited.** `ShortPath::Search` is the single most-changed AI function
in the image at similarity **0.136**.

This **independently corroborates** the 2026-08-23 evasive-AI investigation, which was a targeted
read of `AttackTask::DoState` and concluded the 1.4 evasive system was actively rewritten rather
than left dormant. That doc singled out `UnitTask::UpdateWeapon` as where the 1.4 missile-launcher
fire gate was relocated; this census, which knew nothing about that, independently ranks
`UnitTask::UpdateWeapon` at **0.203** and `AttackTask::DoState` at **0.295**.

**Scale:** 1.4 has 5722 functions, 1.5 has 14 832, and Lua is 1.5-only. 1.4→1.5 is a rewrite, not a
patch. Do not reason about it the way you would about 1.4→TRO.

---

## 1. Method

`BSimCensus.java` (`diff_14_15/bsim/`), p-code LSH signatures, `medium_nosize` template.
**Source is 1.5** so every row carries a real PDB name — that is what turns the output from a count
into a readable list. `SetPdbFile.java` is required as a pre-script; `PdbUniversalAnalyzer` will not
look next to the binary in headless mode, and without it 1.5 imports unsymbolised and the whole
exercise is pointless.

Raw verdicts: **MATCH 2867 · NOMATCH 6167 · UNSCORABLE 5577** of 14 611 named rows.

### 1.1 Do not read those numbers directly

**39 % of all MATCHes are shape collisions.** `medium_nosize` deliberately discards constants, so
boilerplate functions all match the same generic target with an identical score. 1123 of the 2867
MATCH rows sit on just 13 similarity values:

```
1.0000  0.9507  0.9310  0.7519  0.7400  0.7303  0.6767
0.5893  0.5781  0.5670  0.5634  0.5366  0.5304
```

`0.7519` alone is shared by 229 functions, `0.7400` by 172, `0.9310` by 92 — and `1.0000` is itself
a collision value, shared by 318. A first pass that took class medians at face value produced seven
unrelated classes tied at exactly 0.752; that number was measuring shape, not behaviour.

**Filter applied throughout:** a row counts only if body ≥ **256 bytes**, verdict ≠ UNSCORABLE, and
its similarity is not one of the collision values. 1338 of 14 611 rows survive. Large functions have
rich signatures and do not collide.

### 1.2 The control — the method works on these two builds

The obvious worry is that 1.5's different compiler generation (LTCG/size-optimised) depresses
similarity everywhere, making everything look "changed". It does not. Of 587 functions ≥ 512 bytes,
**39 still score ≥ 0.95**, and the top of that list is the software rasterizer, structurally
identical at **1.0000**:

| 1.5 function | Size | Similarity |
|---|---|---|
| `Terrain128PolyDouble` | 2255 B | 1.0000 |
| `Terrain_32PolyDouble` | 2255 B | 1.0000 |
| `Translucent_Perspective_Texture_Map_polygon` | 2098 B | 1.0000 |
| `Transparent_Perspective_Texture_Map_polygon` | 2098 B | 1.0000 |
| `Tile_Transparent_Texture_Map_polygon` | 1425 B | 1.0000 |

Large, untouched code is detected as untouched. So low similarity on a large AI function is real
behavioural change, not compiler drift. (376 of those 587 large functions score < 0.40 — 1.5 really
did change a great deal.)

---

## 2. Result — behaviour classes ranked by how much they changed

Median similarity over reliable rows only; lower = more rewritten.

| Class | fns | reliable | median | |
|---|---|---|---|---|
| `UserProcess` | 12 | 3 | **0.282** | |
| `UnitTask` | 43 | 19 | **0.289** | ← the shared unit state machine |
| `TugProcess` | 17 | 6 | 0.378 | |
| `UnitProcess` | 62 | 9 | 0.382 | |
| `SAVAttackVehicleTask` | 12 | 4 | 0.383 | |
| `DefendTask` | 10 | 3 | 0.407 | |
| `GotoTask` | 16 | 3 | 0.423 | |
| `AttackTask` | 16 | 3 | 0.436 | ← subject of the 20260823 doc |
| `ScavengerProcess` | 25 | 8 | 0.437 | |
| `RecycleTask` | 36 | 5 | 0.489 | |
| `RecyclerProcess` | 20 | 6 | 0.544 | |
| `ArmoryProcess` | 17 | 5 | 0.584 | |

Classes with fewer than 3 reliable rows are omitted rather than ranked on noise — that includes
`RocketTankProcess` (6 functions, all small), so this census cannot speak to it. The 20260823 doc
covers it directly.

### 2.1 The 20 most-changed AI functions

| Sim | 1.5 VA | Size | Function |
|---|---|---|---|
| 0.136 | `00462B4B` | 373 | `ShortPath::Search` |
| 0.164 | `0046E9C9` | 1124 | `UnitTask::DoBlast` |
| 0.179 | `00402F39` | 417 | `AiMission::Update` |
| 0.180 | `0041D473` | 319 | `LayMinesTask::LayoutMineField` |
| 0.195 | `0040D498` | 1966 | `ArtilleryProcess::DoAttack` |
| 0.203 | `0046C63E` | 2035 | `UnitTask::UpdateWeapon` |
| 0.210 | `0046FAD6` | 891 | `UserProcess::Execute` |
| 0.212 | `0046E668` | 865 | `UnitTask::DoStand` |
| 0.213 | `0045A44D` | 1663 | `RecycleTask::DoStuck` |
| 0.214 | `004585EF` | 466 | `PowerUpProcess::Execute` |
| 0.216 | `0046BCF3` | 1741 | `UnitTask::DoStuck` |
| 0.223 | `0046D31A` | 759 | `UnitTask::DoFollow` |
| 0.235 | `0046D84D` | 300 | `UnitTask::Execute` |
| 0.249 | `0046F103` | 940 | `UnitTask::DoFlee` |
| 0.253 | `0046F4DB` | 636 | `UnitTask::GoTowards` |
| 0.260 | `0046E4E4` | 388 | `UnitTask::DoSit` |
| 0.270 | `00469853` | 731 | `UnitProcess::ChangesState` |
| 0.285 | `0044DEC8` | 651 | `OffensiveProcess::DoSubTask` |
| 0.290 | `00467AC5` | 633 | `TurretTankProcess::DoSubTask` |
| 0.295 | `0040F25B` | 1709 | `AttackTask::DoState` |

Full list: `diff_14_15/out/ai_functions_changed.tsv` (71 reliable NOMATCH functions).

### 2.2 Reading this against the evasive-AI doc

The 20260823 investigation found the 1.4 evasive tank behaviour (damage-triggered flee/slide/stand
cycle) was actively rewritten in 1.5, with four deltas in `AttackTask::DoState` plus a
RocketTank-only hold-fire subsystem, and that the only surviving fragment was the missile FourCC
fire gate relocated into `UnitTask::UpdateWeapon`.

Every function that account touches shows up here as heavily changed —
`UnitTask::DoFlee` 0.249, `DoStand` 0.212, `DoStuck` 0.216, `UpdateWeapon` 0.203,
`AttackTask::DoState` 0.295 — reached independently, from p-code shape alone. That is a real
cross-validation of both results.

What the census adds is **breadth**: the rewrite was not confined to the evasive path. The whole
`UnitTask` state machine, `UnitProcess::ChangesState`, the per-role `DoSubTask` overrides,
mission-level `AiMission::Update`, and pathfinding all changed at the same time.

---

## 3. Limits — read before quoting any number here

* **`NOMATCH` conflates "rewritten" with "new".** `ShortPath::Search` at 0.136 may be a rewrite or a
  wholly new A* implementation; the census cannot tell. Deciding requires reading both
  decompilations, which is now cheap — both corpora exist.
* **Small classes are unrankable.** `RocketTankProcess`, `ScoutProcess`, `TankProcess`,
  `BomberProcess` have too few functions ≥ 256 bytes to survive the filter.
* **Similarity is not a behavioural delta.** 0.2 does not mean "80 % of the behaviour changed"; it
  means the p-code shape is largely unrelated. Use it to *rank where to look*, not to quantify.
* **The 6167 raw NOMATCH count is not a finding.** Most of it is 1.5-only code that never existed in
  1.4 — Lua, the netcode rewrite, the shell. Only the named, size-filtered subset in §2 is evidence.

## 4. Pairing the functions — BSim cannot, vtables can

To read a rewritten function side by side you first need to know *which* 1.4 function it is. The
obvious approach — take BSim's nearest match even when it is below threshold — **does not work, and
the failure is measurable.**

### 4.1 BSim's pairings for rewritten functions are noise

Best-match run over the 24 most-changed functions (`out/top_changed_bestmatch.csv`):

* 1.4 target `0x0046BBA0` came back as the best match for **three** different 1.5 functions
  (`RecycleTask::DoStuck`, `UnitTask::DoBlast`, `UnitTask::UpdateWeapon`); `0x0046E6B0` for two more.
* Three matches had **negative significance** — explicitly less likely than chance:
  `ShortPath::Search` −8.16, `UnitTask::DoStuck` −4.73, `UserProcess::Execute` −35.46.
* Sizes are wildly inconsistent: `UnitTask::UpdateWeapon` is 2035 bytes in 1.5, its "best match" 150.

Scored against ground truth (§4.2), **BSim got 1 of 3 right**:

| Function | vtable truth | BSim best | |
|---|---|---|---|
| `AttackTask::DoState` | `0x0040CDE0` | `0x00452E80` | **wrong** |
| `UnitTask::Execute` | `0x0046C980` | `0x004141D0` | **wrong** |
| `UnitTask::GoTowards` | `0x0046D580` | `0x0046D580` | correct |

This is self-consistent: a function rewritten hard enough to score 0.2 has nothing left to match on.
**Do not use BSim to pair the very functions the census flags as changed.**

### 4.2 Vtable slot alignment does work

A class's vtable lists virtual methods in a fixed slot order that rewriting the method *bodies*
does not disturb, so slot N in 1.4 is the counterpart of slot N in 1.5 however much the body changed.

The task hierarchy uses a **13-slot vtable**:

```
[0] scalar_deleting_destructor   [5] Init*        [10] CleanState
[1] Load                         [6] Done*        [11] DoState
[2] PostLoad                     [7] Execute*     [12] GoTowards*
[3] Save                         [8] DrawStateA*
[4] GetRtimeClass                [9] InitState          (* = inherited from UnitTask)
```

`AttackTask`, located in 1.5 at **`0x005CF8F8`** and in 1.4 at **`0x005E6E58`**:

| Slot | Method | 1.5 | 1.4 |
|---|---|---|---|
| 0 | `~AttackTask` | `0040EE7C` | `0040C4C0` |
| 1 | `Load` | `0040EC41` | `0040C6D0` |
| 2 | `PostLoad` | `0040ECA2` | `0040C740` |
| 3 | `Save` | `0040ECD7` | `0040C770` |
| 4 | `GetRtimeClass` | `0040EB9D` | `0040C500` |
| 5 | `UnitTask::Init` | `0046D785` | `0046C150` |
| 6 | `UnitTask::Done` | `0040BB57` | `00409360` |
| 7 | `UnitTask::Execute` | `0046D84D` | `0046C980` |
| 8 | `UnitTask::DrawStateA` | `0046B45E` | `0046CAF0` |
| 9 | `InitState` | `0040F193` | `0040CC40` |
| 10 | `CleanState` | `0040EDBA` | `0040CD50` |
| 11 | **`DoState`** | `0040F25B` | **`0040CDE0`** |
| 12 | `UnitTask::GoTowards` | `0046F4DB` | `0046D580` |

**Cross-validation:** slot 11 lands on `0x0040CDE0`, exactly the 1.4 `AttackTask::DoState` address the
20260823 investigation derived by hand from a completely different direction.

Anchoring generalises: once 1.4's inherited `UnitTask` slots are known, every task vtable can be
found by searching for them. **1.5 has 41 such vtables, 1.4 has 36** — five task classes added.

---

## 5. Worked example — `AttackTask::DoState` case 7

Both builds handle the identical state set (2,3,4,5,6,7,8,9,10,0xB,0xC), so the state machine was
**not** restructured; the rewrite is inside the handlers. 1.4's body is 399 decompiled lines against
1.5's 289 — 1.5 removed logic.

Case 7 is where the 20260823 doc located its F1 delta, and the two now read side by side.

**1.4** — slide-exit keyed on the *enemy's own task state*, no time cap:

```c
iVar8 = (**(code **)(*(int *)(*(int *)(param_1 + 0x1c) + 0x18) + 0x30))();
iVar8 = *(int *)(iVar8 + 0xac);            /* the ENEMY's task state */
if ((iVar8 != 2) && (iVar8 != 5)) {
    if (iVar8 == 7) { *(undefined4 *)(param_1 + 0x10) = 10; }   /* -> slide */
    else { ... FUN_00414340 (SidewaysAndClose) ... }
}
```

**1.5** — enemy-state predicate gone, replaced by a target-type test and a **10-second cap**:

```c
iVar7 = IsBuilding(p_Var6);
if (iVar7 != 0) goto LAB_0040f59d;
fVar15 = Get_Time();
if (fVar15 <= (float)this->_padding_ + 10.0) {      /* <-- time cap, absent in 1.4 */
    bVar3 = UnitTask::IsStuck((UnitTask *)this);
    if (!bVar3) {
        UnitTask::DoSlide((UnitTask *)this);
        ...
        iVar7 = SidewaysAndClose(p_Var8, p_Var6);
    }
}
```

So 1.5 swapped a predicate reading the *opponent's* state machine (`{2,5,7}` at object `+0xAC`) for
a self-contained one: is the target a building, has 10 seconds elapsed, am I stuck. That is the
20260823 doc's F1 in both directions, with 1.5's PDB names attached to the surviving helpers
(`IsStuck`, `DoSlide`, `SidewaysAndClose`, `AbleToHit`).

---

## 6. A gap in the 1.4 corpus

`0x0040CDE0` is a vtable target and therefore certainly a function, but the Ghidra run in
`BZ1_Source/1.4/ghidra` **did not create a function there** — its decompilation is missing from the
5832. The older partial corpus `BZ1_Source/decomp1.4` does have it (`all/0040cde0.c`), which is what
made §5 possible.

Cause: nothing seeds functions from vtable slots, and 1.4 has no RTTI to help. **Fix before relying
on the 1.4 corpus for coverage:** walk the 36 task vtables (and the process vtables) and force a
function at every slot target, then re-decompile. Until then, treat 1.4 function coverage as
incomplete rather than as 5832-of-5832.

---

## 7. Next

Repeat §4.2 across all 36 task vtables to get a verified 1.5→1.4 name map for every virtual method,
then walk §2.1 top-down. The non-virtual state handlers (`DoFlee`, `DoStand`, `DoStuck`, `DoBlast`,
`UpdateWeapon`) are not in the vtables and need one more hop — they are called from the aligned
`DoState`/`Execute` bodies, so call-site position identifies them once the virtual anchors are fixed.
