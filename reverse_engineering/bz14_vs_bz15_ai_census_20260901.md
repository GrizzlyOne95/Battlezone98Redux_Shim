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

## 4. Next

The obvious follow-up is cheap now: take the top ~20 functions in §2.1 and diff the two
decompilations side by side. 1.5's side is named; 1.4's side can be named by transferring symbols
across the high-confidence BSim matches. That turns "`UnitTask::DoFlee` changed a lot" into the
specific behavioural deltas, the way the 20260823 doc did by hand for `AttackTask::DoState`.
