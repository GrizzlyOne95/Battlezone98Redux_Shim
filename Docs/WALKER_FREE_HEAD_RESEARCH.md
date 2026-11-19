# Walker free-turning head: research and plan (queue item 11)

Status: research and design only (2026-11-18, revised after the user's decisions). Nothing implemented, nothing run live. Anything without a cite is UNVERIFIED.
Path keys: BZ = `Battlezone_Source\BZ1`; C15 = `BZ\1.5\functions\004b\` (PDB-named 1.5 decompile); T = `BZ\derived\bz15_pdb\raw\types.txt`;
GD = `BZ\Redux\openshim_re_corpus\bzr_gog_best_effort\ghidrecomp\results\bins\battlezone98redux.exe-6777ca\decomps\` (GOG, no PDB names);
GI = `Battlezone_Source\BZ1\Redux\openshim_re_corpus\bzr_gog_best_effort\inventory\symbols.csv`; TV = `Docs/TRACKED_VEHICLES.md`; TC = `src/patches/tracked_vehicle_class.cpp`;
B2 = `Battlezone_Source\BZ2\_analysis\global_decompile\bzone_b131p_best_effort\results\bins\bzone.exe-6f4367\decomps\`.

## Executive conclusion
- **Feasible; v2 (independent MechWarrior-style twist) is the plan, split into milestones.** Mouse/aim turns the head; movement keys steer the legs, which keep their own heading.
- **Design in one line: "frame swap".** The root transform (obj76) is the *head* frame, so camera, reticle, weapon aim and ordnance work unchanged (proven for the tank
  turret, TV:131-135, 378-391). Around the stock Walker::Simulate the wrapper temporarily rotates the root to the *legs* frame, so stock locomotion, collision-free
  movement and the walk-clip choice (which read the root axes, C15 004b7104:127-165) see the leg heading; afterwards it rotates back and counter-poses the leg nodes.
- **Why not "head-only" (root = legs, rotate the torso node):** the stock weapon aim cancels the hardpoint chain's rotation and fires along the root (section 3), so
  the guns, camera, reticle and AI would all need separate patches. Frame swap needs none of them.
- **Unknowns that can break it** (all probed in milestone M0, section 5): that Simulate is vtable slot 15 of Walker; where the engine calls UpdateWeaponAim relative to
  Simulate; whether the walk clip rewrites leg nodes every tick; how mouse and keys reach `ctrl.steer`/`ctrl.strafe`.
- **Effort:** M0 probe S; M1 functional twist M; M2 leg pose, limits, shared helpers M; total about 2-3 weeks including live tests. AI, MP and svwalk are later.
- Ghidra was not used (bridge optional, not started), so no GOG vtable bytes were read.

## 1. Engine facts (verified from the corpus unless marked)
- Walker is a Craft subclass (T:97019-97024: curAnim, animHandle, last_strafe/steer/pitch). Three `WalkerParameters` sets (13 floats: omegaTurn, alphaSteer, velocForward...;
  T:97037-97050) sit at class +0x300 (T:96914); the stock ODF fills them from `[HoverCraftClass]` (avwalk.odf `omegaTurn = 1.0`, `alphaSteer = 5.0`).
- Control struct at `this+0x230`: steer +0xC4, pitch +0xC8, strafe +0xCC, throttle +0xD0 (GD FUN_0060bd60:228-240; same layout as hover, Docs/TRACKED_VEHICLE_SCOPE.md section 4).
  Player and AI write the same struct. Whether the mouse and the keyboard both land in `ctrl.steer` (and which key feeds `ctrl.strafe`) is UNVERIFIED.
- Yaw: steer sets a yaw acceleration `clamp(steer - omega.y/omegaMax, -1, 1) * alphaSteer` (C15 004b7104:278, 366, 381). GOG: omega at this+0x138..0x140 is clamped
  to +-12 (GD FUN_0060bd60:636-661); the rotation step is `FUN_00444d50` (line 622; builds a matrix from omega*dt, then copied into the obj76 transform at +0x20,
  lines 623-635). It matches 1.5 `Spinner` (C15 004b7104:467) by structure only: UNVERIFIED mapping. Velocity then adds into the position (lines 668-676).
- Anim clip: chosen from velocity dotted with the root axes (C15 004b7104:127-165), started/rated at 204 and 207.
- GOG identities: Walker::Simulate = `FUN_0060bd60` (structure match with C15 004b7104, UNVERIFIED by name); Walker ctor `FUN_0060bc40` (sets `Walker::vftable`, GD FUN_0060bc40:15-17);
  WalkerClass ctor `FUN_00610030` (class signature 'WALK' 0x57414C4B, GD FUN_00610030:7). `GI` lists two vtable labels for Walker, at decimal 8953956 and 8954044
  (= 0x0088A064 and 0x0088A0BC; the conversion is mine). Which one is the +0 vtable, and that Simulate is slot 15 as for HoverCraft (TC:172, 62), is UNVERIFIED.
  Treat both addresses as unconfirmed until the bytes are read (M0).
- GameObject::Simulate 0x004DEEC0 calls slot 15 in up to five sub-steps per frame (TC:61-63); the wrapper must be re-entrant per sub-step.

## 2. Rendering, nodes, camera
- Stock `avwalk.vdf` tree (Toolbox `read_vdf` on `BZ\1.5\Battlezone_Install\stock\avwalk.vdf`): root `age11bda` -> `age11ty1` (torso) ->
  { `age11lsh` -> `age11tx2` -> `AGe11GC1`; `age11rsh` -> `age11tx1` -> `AGe11GC2`; `AGe11GM1`; `age11hed` -> `AGe11LGT`, `AGe11POV` }; the legs
  (`lcv, lhl, lt1-3, lth` and mirror) are siblings of `ty1`. `bvwalk` has the same shape. avwalk.odf hardpoints GC1, GC2, GM1 are at lines 15-20 (`weaponMask` line 21).
- The VDF also holds an `age21hed` with parent `age21ty1` (and `bge21hed`/`bge21ty1` in bvwalk), probably damage-state or LOD torso variants: UNVERIFIED. If they are
  root children they would be counted as "legs" and rotated wrongly. Rule: the torso set is `torsoName` plus any node whose name differs from it only in the 4th-5th
  characters (`ty1` variants); otherwise fail closed with a log line (section 6).
- `svwalk`/`cvwalk` differ (torso is `svw11hed`; `svw11sup` has parent WORLD, a second root): out of scope for the first release.
- **The walk clip writes these nodes.** Sequences carry tracks for `ty1`, `hed`, `tx1/tx2`, `GC1/GC2`, `POV` and the leg nodes (VDF `tracks`: 26 for avwalk), so the leg
  pose must be composed on the animated pose (section 4, step 6). Cadence of the clip update versus Simulate: UNVERIFIED (M0).
- Native node locals are copied to Ogre by `ModelPose` 0x00681A00 (Docs/WEAPON_MOUNTS_SCOPE.md:122); the tank does write + sync (TC:1099-1102). Native leg nodes are live and animated
  (Docs/WEAPON_MOUNTS_SCOPE.md:125-128). Whether Redux leg meshes are rigid per node or skinned to bones fed from these nodes: UNVERIFIED.
- First-person: the cockpit `_c` entity sits on a separate first-person node and the camera follows its POV bone (`src/patches/walker_cockpit_trace.cpp:1020-1036`, 1196-1205); how that
  node is posed from the vehicle is UNVERIFIED. The torso (with the POV node) is left at its rest pose in the root frame and root = head, so the view follows the head either way.
  A prior jitter investigation exists (reverse_engineering/notes/walker_cockpit_jitter_native_result_20260902.md): write poses in the sim tick, re-run the `WalkerCockpitTrace` instrument after M2.

## 3. Weapons, reticle
- Stock Walker::UpdateWeaponAim builds a pitch matrix from the craft pitch, takes `obj_rel_parent_matrix(hardpoint, root)`, inverts it and composes (C15 004b865d:51, 62, 69), then adds the
  range-convergence correction `(-hx, 0, range - hz)` (C15 004b865d:117; geometry in reverse_engineering/notes/redux_walker_convergence_equivalence_20260921.md). GOG `0x0060F320`:
  pitch matrix line 60, relative matrix line 78, directional matrix line 155, weapon sync 0x00681A00 line 184 (scripts/patches.json:1140 for the address).
- The inverse cancels the node chain's rotation: barrels point along the **root** plus pitch; only their position follows the nodes. Hence frame swap (root = head) fires along the head with
  no weapon change, and the torso stays at rest relative to the root so hardpoint positions equal stock. Pitch is already independent of the body (craft pitch at this+0x280).
- Reticle convergence (OpenShim) wraps `UpdateWeaponAim` slot 38 for other classes (src/patches/weapon_convergence_hooks.cpp:560-570, 777-806) and is root-relative; it stays valid. The Walker's own slot is not wrapped there.
- **Open hazard:** if the engine calls UpdateWeaponAim from inside the Simulate chain (Craft::Simulate "AI/weapons", Docs/TRACKED_VEHICLE_SCOPE.md section 4, UNVERIFIED), it would run while the root
  is in the legs frame. Plan: set a "swapped" flag, and after swapping back call the stock UpdateWeaponAim once more (five weapons, cheap) so the final state uses the head frame; M0 logs the call order.

## 4. v2 design: data flow per Simulate call (player-driven, opted-in walker)
State per object (map keyed by object pointer, as TC:350-386): `delta` = head yaw relative to legs (+ left, radians), `rate`, torso node, leg nodes with `base` pose and `lastWritten`.
Gate: opted-in class (`torsoName` set), `ctrl` user flag (`kObj76FlagAimGate` 0x10 on the user's craft, TC:146, 900), not remote (SP only). Otherwise: stock call, plus `delta` relaxing to 0 (step 8).
1. **Read inputs** from the control struct: `mouse = ctrl.steer`, `turnKeys = ctrl.strafe`, throttle, pitch.
2. **Head slew**: `headCmd = mouse`; update with the tank's pure math (`include/tracked_vehicle_turret.h`: SlewRate, AdvanceDelta, Sanitize), limits from `yawMin/yawMax` (none unless set).
3. **Rewrite controls for the legs**: `ctrl.steer = turnKeys`, `ctrl.strafe = 0` (the stock call now turns the legs from the keys, and sidestepping is disabled while twisting is on; UNVERIFIED whether a separate strafe key exists to keep).
   Save the originals and restore them after the call.
4. **Swap in**: rotate the root's right/front about its up axis by `-delta` (`TU::HullAxes`, the tank's helper) so the transform is the legs frame; positions, velocity and omega are world vectors and are untouched.
5. **Stock call** (`g_StockSimulate`): moves, picks the walk clip, turns the legs from the keys, runs the Craft tail. Measure `dLegs` = change in the root's front yaw across the call.
6. **Swap out**: `delta_new = delta + headRate*dt - dLegs` (head is world-stabilised: turning the legs does not drag the aim; with limits the clamp drags the head), then rotate the root by `+delta_new`.
   If M0 shows UpdateWeaponAim ran inside the call, call it again here.
7. **Pose legs**: for each leg node (root direct children except the torso set): if its current local pose differs from `lastWritten`, the clip refreshed it, so `base = current`; write
   `Compose(base, -delta_new)` (rotate rotation and position about the root up axis) via `Obj76::SyncNode` 0x00681A00 and remember it in `lastWritten`. Same write-then-sync as TC:1099-1102 and 1197-1226.
   Skip when `delta_new` is unchanged and the clip did not refresh.
8. **Not user-driven** (player left the walker): no swap; `delta` decays to 0 at `yawRate` and the legs re-pose; the walker is then a stock walker whose root is the head.
Data after the frame: root = head (camera, reticle, weapons, HUD), legs nodes counter-yawed, locomotion and animation consistent with the legs heading.
Collision: the box turns with the root (head), as for the tank (TV:298-303); movement collision during the call used the legs frame. Live-check tight gaps.
Save/load: `delta` is not saved; a loaded game starts with delta 0 and legs under the head (TV:160-161).

## 5. Milestones (v2 splits naturally)
| Step | Content | Effort | Gate |
|---|---|---|---|
| M0 probe | read Walker vtable bytes (Ghidra or cdb); log ctrl steer/strafe with mouse only vs keys only; log lt1 local pose per frame for 120 frames; log UpdateWeaponAim call order vs Simulate | S | slot 15 confirmed, input split possible, anim cadence known |
| M1 functional twist | steps 1-6 without leg re-pose (legs mesh stays in the head frame, visually wrong), ODF opt-in, avwalk, SP; verify by log: root yaw = head, leg heading drives velocity and clip choice, guns fire along the head, camera follows | M | go/no-go for the frame swap |
| M2 legs and polish | step 7 with the animation-aware compose, limits, release relaxation (step 8), shared helper extraction (section 6), tests, docs, cockpit trace re-run | M | releasable |
| later | AI opt-in, co-op/MP delta sync (reuse the `'T','Y'` message, TV:186-209), svwalk `sup` tree | S-M each | not in this plan |
If M0 shows the frame swap cannot work (for example the weapon call order cannot be repaired), fall back to the earlier "root = head, legs follow" model (legs re-align at a fixed rate, no independent heading).

## 6. ODF keys, files, fail-closed
`[WalkerClass]`, all optional, **feature off unless `torsoName` is set**; names match the tank's `[TrackedClass]` keys (TV:112-125) so one parser serves both:
```ini
[WalkerClass]
torsoName = "AGE11TY1"  ; node(s) that stay with the head; legs = the root's other direct children; 8 chars, case-insensitive
yawRate   = 2.5         ; head slew rate, rad/s (default 2.5; clamped like the tank, 0.05..20)
yawAlpha  = 8.0         ; head slew acceleration, rad/s^2
yawMin    = -1.6        ; optional, radians, head relative to legs; no limit unless set (a limit that excludes 0 is dropped with a log line)
yawMax    =  1.6
```
Leg turn speed is the stock `omegaTurn`/`alphaSteer` (raise them in the ODF; avwalk's 1.0 is slow). Opt-in is per ODF, so any mod walker that names its torso gets it.
Files (extract, do not copy, per the decision below):
- new `src/patches/node_pose.h/.cpp`: `NodePose`, `ReadPose`, `WritePose` (with `Obj76::SyncNode`), node link/name readers, obj76 offsets, and the node-finder (from TC:138-151, 1076-1235). TC includes it; tank behaviour must not change.
- keep `include/tracked_vehicle_turret.h` as the pure math (slew, wrap, `HullAxes`, `TurretRotation`); add the leg `Compose` and `dLegs` helpers with unit tests in `tests/`.
- new `src/patches/walker_free_head.cpp` (wrapper, state, ODF read via the same `g_RawGet` path as TC:467-523, 211-254), registration in `bzr_hooks.cpp`/`bzr_hooks_internal.h`, `scripts/patches.json` rows, `ACTIVE_PATCHES.md`.
- Docs: `Docs/WALKER_FREE_HEAD.md` (modder doc), queue line in `Docs/FEATURE_WORK_QUEUE.md`.
Hook: Walker::Simulate by in-place vtable slot write behind an owner/opt-in check, as the convergence wrapper does for UpdateWeaponAim (weapon_convergence_hooks.cpp:824-870); per-class opt-in flag read at class build
(WalkerClass ctor `FUN_00610030`; the BuildClass/ODF-read detour address is UNVERIFIED).
Fail closed (stock walker plus one log line, as TV:162-164): SyncNode unresolved, torso missing or unreadable, more than 16 root children, an ambiguous torso variant (`age21ty1`-style nodes, UNVERIFIED) or an unexpected vtable.

## 7. AI, MP, BZ2 reference
- AI walkers stay stock (decision). The stock AI writes the same control struct, so a later opt-in could reuse the tank's reasoning: the AI steers the root (head) at its target (TV:141-146), with legs following.
- SP only: replicas re-run Simulate from received controls and the walker packet has no head angle (WALKER_STATE_PACKET, T:97075-97081), so MP needs the `'T','Y'`-style delta message later (TV:186-209).
- BZ2 split walker yaw at the joint: `Walker::UpdateTurretAim` runs `Walker_Neck_Control_Class::Control` (named "Yaw_joint"/"Pitch_joint", B2 UpdateTurretAim-0051f332.c:10-25, Walker_Neck_Control_Class-0042a0eb.c:22-29)
  or `TurretControl`, integrating a clamped angle with exponential smoothing (B2 Control-0042a1ca.c:14-33). Design reference only; BZ1 frame swap needs no joint names.

## Risks
1. Walk clip rewrites leg nodes (step 7 handles both cadences, M0 measures it). 2. Weapon aim called inside the swapped call (re-run after swap-back). 3. Mouse and keys sharing `ctrl.steer` makes the input split impossible: then
   fall back to "mouse head, strafe keys legs, arrows head". 4. Root yaw jumps by `delta` between sub-steps could confuse collision or Lua `GetTransform` readers (they see the head frame, which is intended). 5. Cockpit jitter regression.
6. Extracting the tank helpers touches shipped tracked code: run the tracked tests and one tank live check. 7. Seismic/other omega code acts on the root and so on the head (Docs/SEISMIC_WALKER_IMMUNITY_SCOPE.md:12-18): no change.

## Decisions recorded (user, 2026-11-18)
- Control model: v2 independent twist; mouse/aim turns the head, movement keys steer the legs. Walkers: generic opt-in for any ODF naming its torso; verify on avwalk first, svwalk `sup` later.
- AI: player only first, AI stays stock. Network: SP only for v1. Yaw limits: unlimited unless `yawMin`/`yawMax` are set. Shared code: extract the tank's node/pose helpers into a shared header, no duplication.

- Sidestep: losing the stock strafe on twist-enabled walkers is accepted (user). Head aim: world-stabilised. Milestones: M1 and M2 as separate PRs, M0 gates both, fallback "legs follow the head" if M0 fails.

## Open questions (still open)
None; next step is the M0 probe.
