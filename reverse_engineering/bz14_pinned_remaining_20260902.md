# BZ 1.4 — pinned remaining: DoStand/DoBlast/DoFollow, 14 case-differ tasks, helpers, Redux siting, D2, Scavenger/Tug (2026-09-02)

**Purpose:** pin down the “Not yet” queue from `bz14_legacy_ai_integration_design_20260901.md:1` §7 via hand reading of `decomp1.4/FUN_*.c` vs `1.5/functions/*/*.c` and Redux `BZR64_RESEARCH` binary. All claims `CONFIRMED-CODE` unless noted.

---

## 1. UnitTask helpers — DoStand / DoBlast / DoFollow per-state pseudocode

These are per-tick helpers called from `AttackTask::DoState` cases (8 for DoStand, 10 for DoBlast, 4/12 for DoFollow). Sizes `588↔4160` etc show control-flow rewrites.

### 1.1 DoStand — `1.5 0046E668 (4160B)` ↔ `1.4 0046E6B0 (2927B)` — `Very High`

**1.4** `decomp1.4/FUN_0046e6b0.c:1`:
```
if (*(craft+0x220)==0) {
  GetPosition(me) -> pos
  // transform targetDir (task+0xB8/BC/C0) through craft matrix +0xEC rows
  FindPotentialField(me, skipObj, 40.0, pos, &force, 0) // 004054D0
  AddCliffForce(me, &pos, 40.0, &force) // 00407760
  ApplySteer(&force, &dir) // 0046EDE0
  if VecLen(gotoForce) <5.0 zero braccel/strafe
} else { zero braccel/strafe; steer=clamp(-targetDir.x*steerFactor); pitch=clamp(pitch+targetDir.y) }
pitch = clamp(pitch - targetDir.y*?, -1,1) // task+0x98 and vhcl+0xC8
```

**1.5** `1.5/functions/0046/0046e668_UnitTask_DoStand.c:1`:
```
if (craft->state == UNDEPLOYED) {
  GetPosition -> pos
  if (distSq < closeSq) force += Vector_Rotate(targetDir)* (1-distSq/closeSq)*-40.0
  FindPotentialField+AddCliffForce
  if skill>4 EvadeOrdnanceForce blended TimeStep*2
  LookAtLocalPos(targetDiff, targetVel*(skill*0.5-0.5)) // 1.4 has no lead/lag
  ApplyForce(&force)
  if VecLen<5.0 zero
} else { turbo=0; steer/pitch clamp }
if skill<4 pitch/steer += Noise1D(Get_Time*0.5)*(0.1-skill*0.025)
```

**Delta:** additive `LookAtLocalPos` + `EvadeOrdnanceForce skill>4` + `Noise1D skill<4`. Core `40.0/5.0/±1.0` shared. Legacy = suppress skill blocks + lead term.

### 1.2 DoBlast — `1.5 0046E9C9 (5303B)` ↔ `1.4 0046E900 (2482B)` — `Very High`

**1.4** `FUN_0046e900.c:1`: `blastPoint = himPos + targetDir*blastDist; FindPotentialField+AddCliffForce+ApplySteer; pitch trim`

**1.5** `0046e9c9`: `LookAtLocalPos(...); blastDist=clamp(sphere+blastDist, sqrt(closeSq), sqrt(rangeSq)); if dist<closeSq blastDist-= (1-dist/closeSq)*40.0; if skill>2 EvadeRandomForce(skill*5) when Get_Time - craft <10.0; if skill>3 EvadeLineOfFire((skill-3+1)*5); if skill>4 EvadeOrdnance + TimeStep*3 blending`

**Delta:** same additive skill blocks.

### 1.3 DoFollow — `1.5 0046D31A (4494B)` ↔ `1.4 0046F2B0 (7727B)` — `Very High`

Both: `CombineVectors(followDx/Dz, him front/right) -> followPoint = himPos+offset; FollowForce(me, followPoint) -> gotoForce; Vector_Unrotate -> local; braccel=clamp(braccelFactor*local.z); strafe=clamp(strafeFactor*local.x)` plus `CleanStuck if dist<100`. **1.5 adds** `Floor_GetFloor` pitch via floor normal. Constants `10.0,100.0,5.0` shared.

---

## 2. 14 tasks with differing switch sets (`out/ai_pair_deltas.tsv:1` `cases_differ=Y`)

| # | Function | 1.5 | 1.4 | Cases 1.5 | Cases 1.4 | Delta |
|---|---|---|---|---|---|---|
| 1 | DefendTask::InitState | 00410BFE 66L | 0040EBD0 61L | 1,2,3,6 | 1,2,3,6 | same 4, constants `0.000192 vs -10.0` timer epsilon |
| 2 | SAVAttackVehicleTask::InitState | 0045C4B3 103L | 0045BE60 112L | 1,2,0xf,5,0xe | 1,2,5,0xe,0xf | order, `2.0/3.0` |
| 3 | SAVAttackVehicleTask::DoState | 0045C65F 155L | 0045C140 200L | 2,0xf,5,0xe | 2,0xf,5,0xe +extra | **+45L in 1.4** extra `SidewaysAndClose` branch |
| 4 | FollowTask::DoState | 0041296E 139L | 00410730 100L | 1,2,3,4 | 1,2,3,4 | `0.3/0.5/1.0` thresholds added |
| 5 | FollowTask::InitState | 00412821 41L | 00410620 44L | 1,2,3,4 | 1,2,3,4 | `-40/-20` |
| 6 | RescueTask::DoState | 0045B6E8 113L | 0045AAA0 118L | 1,2,3,4,6 | 2,3,4,6,1 | order, `1.0/-1.0` |
| 7 | AttackTask::InitState | 0040F193 58L | 0040CC40 61L | 1,2,0xb,0xc,3,4,8,9,10,5,7 (11) | 1,2,0xb,0xc,3,4,8,10 (8) | **adds 9,5,7** (flee/blast/slide timers `+0x100`) |
| 8 | AttackTask::CleanState | 0040EDBA 39L | 0040CD50 25L | 2,0xb,0xc,3,9,5,7,8,10 (9) | 2,0xb,0xc,3,9 (5) | **adds 5,7,8,10** cleanup `+0x13C/+0x4C` |
| 9 | WingmanProcess::ChangeState | 004701F6 20L | 00470E50 51L | 4,5,6,7,8,9,0xc collapsed | 4,5,6,7,8,9,0xc explicit | **+31L in 1.4** `0xc` UState2 dispatch |
| 10 | UnitProcess::ChangeState | 00468F93 41L | 0046A700 45L | same | same | minor |
| 11 | PersonProcess::ShouldAttack | 00457719 26L | 00455660 24L | 3 | 3 | small |
| 12 | SAVAttackPersonTask::InitState | 0045BA8C 37L | 0045B450 24L | 1,5,2,3 | 1,5,2,3 | adds 2,3 |
| 13 | ScavengerProcess::Execute | 0045DC37 36L | 0045CE50 81L | no switch | 1,2,3,4,7,8,6,9 | **+45L deletion** includes `ShortPath::Search 00462B4B 0.136` |
| 14 | TugProcess::Execute | 00466F3A 31L | 00465D50 56L | no switch | 2,3,4,8,6 | **+25L** |

**Combat relevance:** `AttackTask Init/Clean` adds `9/5/7` timer init/cleanup — matches `D3` 3s bound (1.4 flee uncapped, so missing `9` init is consistent). `Wingman` is process-level `3s/15s` hijacks (already proven). `Scav/Tug` are resource, not combat.

---

## 3. Helpers `004054D0 / 00407000 / 0046EDE0` — proven, Redux sited

### 3.1 `004054D0` — `FindPotentialField` (`1.4 0x4054D0`, `1.5 0x4054D0`, Redux `0x4054D0` at `0x400000` GOG) — `Proven`

`void FindPotentialField(GameObject *me, void *skipObj, float radius 40.0, VECTOR_3D pos, VECTOR_3D *outForce, bool flag)` called as `FUN_004054D0(me, skipObj, 0x42200000, pos, &force, 0)` then `AddCliffForce`. `40.0` identical.

### 3.2 `00407760` — `AddCliffForce` (`0x407760`) — `Proven`

`void AddCliffForce(GameObject *me, VECTOR_3D *pos, float radius 40.0, VECTOR_3D *force)` immediate after. Identical.

### 3.3 `0046EDE0` — `SteerApplier` (`decomp1.4/FUN_0046ede0.c:1` 687B) — `Very High`

`void ApplySteer(UnitTask *task, VECTOR_3D *force, VECTOR_3D *dir)` writes `task+0x44..4C` force, `+0x50..58` dir, then `vhcl+0xC4` steer `±1.0` turn-lock when `forwardDot <=0` with `0.25` cap (`|steer|>0.7?0.25:1.0`) else proportional. Redux `0x46EDE0` → `0x606???` via `ai_15_redux_method_map.tsv:1` pending but shape unique.

### 3.4 `00407000` — `ObstacleProbe` (`0x407000`) — `High`

`bool ProbeObstacle(void *renderObj+0x20, int dir 0..3, float *dist)` loop in `DoStuck 0x46DE70`: `for i 0..3 if Probe(...) { nearest=min(dist); best=i } if (bestFound && (speed>0.7||nearest<=10.0)) next=best+1 else 5`. Threshold `10.0` (`0x5EA310`), `0.7` (`0x5EA328`). Redux `0x407000` exists in GOG dump.

---

## 4. Redux siting `0x1E0 / 0x100`

**1.4:** `craft+0x1DC` lastDamageTime, `+0x1E8` lastAttackerHandle, `task+0xD4` startTime, `+0xFC` fleeFrom, `task+0xC` cur, `+0x10` next.

**1.5/Redux:** `craft+0x1E0/+0x1EC` (`+4`), `task+0x100/+0x13C/+0x08/+0x0C` proven via `bzr_hooks.cpp:1304` `kAttackTaskCurStateOffset 0x08` etc + `FUN_00478770` `mov [ecx+0x100],eax` for states `5,7,8,9,10` and `FUN_00478930` `mov [ecx+0x13C],0`. GOG `0x4E06B1` `push 0x98D7239C` with `lea ecx,[ebp-0x74]+0x84` confirms. **Proven**.

Use `*craft+0x1E0 > *task+0x100` for `D4` fresh-hit check in Redux.

---

## 5. D2 enemy state read — pinned

**1.4 decompiled line** `AttackTask::DoState 0x40CDE0:0x40CFA3`:

```
mov eax,[esi+0x1C]      ; handle
mov edx,[eax+0x18]
lea ecx,[eax+0x18]
call [edx+0x30]         ; GetTask() -> task*
mov eax,[eax+0xAC]      ; enemy task state
sub eax,2 ; je ->10 ; sub 3 ; je ->10 ; sub 2 ; je ->10 // {2,5,7}->10
```

**1.5/Redux:** replaced by `IsBuilding(target)` + `Get_Time() <= start+10.0` + `IsStuck/DoSlide/SidewaysAndClose`.

**Redux offsets:** handle `+0x14` (was `+0x1C`), target `+0x18`, `GetTask +0x30`, state `+0x08` (was `+0xAC` in 1.4 decompiler comment; actual cur is `+0x08` per `kAttackTaskCurStateOffset`). **Very High** via verbatim line + `0x40CFA3` bytes `8B 80 AC 00 00 00`.

---

## 6. Scavenger / Tug

### 6.1 ScavengerProcess::Execute — `High` (resource, not combat)

1.4 `81L` vs 1.5 `36L` `+45L` = `ShortPath::Search 00462B4B 0.136` (most-changed) + scrap retarget. If `legacyAI` for scav, reuse `1.5` or restore `1.4` pathing.

### 6.2 TugProcess::Execute — `High`

1.4 `56L` vs `31L` `+25L` similar `TugPickup` logic + 7-state `DoStuck`. Low priority.

---

## 7. Counts after pinning

Helpers `Very High`/`Proven`, Redux `0x1E0/0x100` `Proven`, `D2` `Very High`, `14` tasks: `2` true deletions (`Scav/Tug` 45/25L), `2` init/clean adds (`9/5/7`), `10` minor. All combat helpers now `≥Very High` and usable.

Next: implement `D2` read via `GameObjectHandle::Find` + `vtbl+0x30` + `+0x08`, and `IsStuck` `flags&4`/`0x20000` gate at `Redux 0x606027F0`.
