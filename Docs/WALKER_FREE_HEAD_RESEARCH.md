# Walker free-turning head: research and plan (queue item 11)

Status: research and design; M0 probe done statically (2026-11-19, section 5a), verdict GO for the frame swap with two amendments. Nothing implemented, nothing run live. Anything without a cite is UNVERIFIED.
GX = shipping GOG `battlezone98redux.exe`, SHA256 8D71F56C...3377413 (bytes read offline, VA = file offset - 0x400 + 0x401000 for `.text`).
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
- **Unknowns that could break it: all resolved by M0 (section 5a).** Simulate is slot 15 of the primary vtable 0x0088A0BC; UpdateWeaponAim runs *inside* Simulate (re-run after
  swap-back, as planned); the walk clip rewrites leg nodes once per frame *after* all Simulates, so the leg re-pose moves to PostSimulate (slot 16); mouse and arrow keys share
  `ctrl.steer` but the raw inputs are separate globals, so the split is possible.
- **Effort:** M0 probe S; M1 functional twist M; M2 leg pose, limits, shared helpers M; total about 2-3 weeks including live tests. AI, MP and svwalk are later.
- Ghidra was not used; GOG vtable and call-site bytes were read offline from GX (M0).

## 1. Engine facts (verified from the corpus unless marked)
- Walker is a Craft subclass (T:97019-97024: curAnim, animHandle, last_strafe/steer/pitch). Three `WalkerParameters` sets (13 floats: omegaTurn, alphaSteer, velocForward...;
  T:97037-97050) sit at class +0x300 (T:96914); the stock ODF fills them from `[HoverCraftClass]` (avwalk.odf `omegaTurn = 1.0`, `alphaSteer = 5.0`).
- Control struct at `this+0x230`: steer +0xC4, pitch +0xC8, strafe +0xCC, throttle +0xD0 (GD FUN_0060bd60:228-240; same layout as hover, Docs/TRACKED_VEHICLE_SCOPE.md section 4).
  Player and AI write the same struct. Mouse X and the arrow keys both land in `ctrl.steer`; A/D feed `ctrl.strafe` (section 5a, Q2).
- Yaw: steer sets a yaw acceleration `clamp(steer - omega.y/omegaMax, -1, 1) * alphaSteer` (C15 004b7104:278, 366, 381). GOG: omega at this+0x138..0x140 is clamped
  to +-12 (GD FUN_0060bd60:636-661); the rotation step is `FUN_00444d50` (line 622; builds a matrix from omega*dt, then copied into the obj76 transform at +0x20,
  lines 623-635). It matches 1.5 `Spinner` (C15 004b7104:467) by structure only: UNVERIFIED mapping. Velocity then adds into the position (lines 668-676).
- Anim clip: chosen from velocity dotted with the root axes (C15 004b7104:127-165), started/rated at 204 and 207.
- GOG identities: Walker::Simulate = `FUN_0060bd60` (structure match with C15 004b7104, UNVERIFIED by name); Walker ctor `FUN_0060bc40` (sets `Walker::vftable`, GD FUN_0060bc40:15-17);
  WalkerClass ctor `FUN_00610030` (class signature 'WALK' 0x57414C4B, GD FUN_00610030:7). `GI` lists two vtable labels for Walker, at decimal 8953956 and 8954044
  (= 0x0088A064 and 0x0088A0BC). **Confirmed from GX bytes (M0):** 0x0088A0BC is the +0 vtable, slot 15 = 0x0060BD60 (Simulate), slot 38 = 0x0060F320
  (UpdateWeaponAim); 0x0088A064 is the secondary vtable at this+0x18 (section 5a, Q1).
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
  pose must be composed on the animated pose (section 4, step 7). Cadence: once per frame, after every object's Simulate and before PostSimulate (section 5a, Q3).
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
- **Confirmed hazard (M0):** the engine calls UpdateWeaponAim from inside the Simulate chain (section 5a, Q4), so it runs while the root is in the legs frame.
  Repair: after swapping back, call the stock slot 38 once more when `this+0x1A0` (weapon list) is non-null, as the stock tail does, so the final aim uses the head frame.

## 4. v2 design: data flow per Simulate call (player-driven, opted-in walker)
State per object (map keyed by object pointer, as TC:350-386): `delta` = head yaw relative to legs (+ left, radians), `rate`, torso node, leg nodes with `base` pose and `lastWritten`.
Gate: opted-in class (`torsoName` set), `ctrl` user flag (`kObj76FlagAimGate` 0x10 on the user's craft, TC:146, 900), not remote (SP only). Otherwise: stock call, plus `delta` relaxing to 0 (step 8).
1. **Read inputs**: `mouse` = the raw analog steer axis `*(int*)0x009198B0 / 65536` (mouse HorizVel only); `turnKeys` = `ctrl.strafe` (A/D, already low-passed)
   plus the arrow keys (`0x009198B5` left minus `0x009198B4` right). `ctrl.steer` alone cannot be used as "mouse": an arrow key held overrides the mouse in it (section 5a, Q2).
   UNVERIFIED: that 0x009198B0 still holds this frame's mouse value when Simulate runs (not cleared or consumed between UserProcess and Simulate). M1 logs it, change-only,
   next to `ctrl.steer` with mouse-only input, and they must track each other. Reading the raw axis also skips the stock steer-assist branch (taken when `0x009198B6` and
   `user+0x78` are set, GD FUN_0060a480:272-317), so twist-enabled walkers lose that assist on the head; accept it, or M1 falls back to `ctrl.steer` while the assist is active.
2. **Head slew**: `headCmd = mouse`; update with the tank's pure math (`include/tracked_vehicle_turret.h`: SlewRate, AdvanceDelta, Sanitize), limits from `yawMin/yawMax` (none unless set).
3. **Rewrite controls for the legs**: `ctrl.steer = turnKeys`, `ctrl.strafe = 0` (the stock call now turns the legs from the keys, and sidestepping is disabled while twisting is on; A/D are the only strafe binding in stock `input.map`, so no separate strafe key is lost beyond what the user accepted).
   Save the originals and restore them after the call.
4. **Swap in**: rotate the root's right/front about its up axis by `-delta` (`TU::HullAxes`, the tank's helper) so the transform is the legs frame; positions, velocity and omega are world vectors and are untouched.
5. **Stock call** (`g_StockSimulate`): moves, picks the walk clip, turns the legs from the keys, runs the Craft tail. Measure `dLegs` = change in the root's front yaw across the call.
6. **Swap out**: `delta_new = delta + headRate*dt - dLegs` (head is world-stabilised: turning the legs does not drag the aim; with limits the clamp drags the head), then rotate the root by `+delta_new`.
   UpdateWeaponAim ran inside the call (M0 Q4), so call stock slot 38 again here (only when `this+0x1A0` is non-null).
7. **Pose legs, in PostSimulate (slot 16), not here** (M0 Q3: the clip overwrites leg locals after Simulate and before PostSimulate, so writes made in Simulate are lost): for each leg node (root direct children except the torso set): if its current local pose differs from `lastWritten`, the clip refreshed it, so `base = current`; write
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
M0 result: GO, no fallback (section 5a). M1 also wraps slot 16 (PostSimulate) for step 7's hook point (M2 uses it).

## 5a. M0 results (static, 2026-11-19; no live run needed)
Paths: GD as above; C15F = `BZ\1.5\functions\` (PDB-named); IM = game root `input.map` (stock bindings).
**Q1 Walker vtable and slots (GX bytes).**
- Walker ctor stores `mov [this], 0x0088A0BC` and `mov [this+0x18], 0x0088A064` (GX `c7 02` at 0x0060BC80 and `c7 40 18` at 0x0060BC89; same pair at 0x0060BD3A/0x0060BD43 in the next function, the dtor side).
  So 0x0088A0BC is the primary (+0) vtable and 0x0088A064 the secondary one at this+0x18.
- 0x0088A0BC slots: 15 = 0x0060BD60 (Walker::Simulate, the only data reference to that address is 0x0088A0F8 = slot 15), 16 = 0x004ACBC0 (PostSimulate, inherited),
  38 = 0x0060F320 (UpdateWeaponAim, only data reference 0x0088A154 = slot 38), 39 = 0x004A8AB0 (same integrate slot as HoverCraft, TC:167-170). It has 42 slots: dword 42 is the
  ASCII `"walker"` class string, matching HoverCraft's 42-slot layout (TC:165-171). The slot 38 match agrees with the convergence wrapper's slot (weapon_convergence_hooks.cpp:560-570).
**Q2 Input mapping.**
- IM:217-232: analog `steer` = `mouse HorizVel`; `steer_right` = RightArrow, `steer_left` = LeftArrow. IM:256-265: `strafe_right` = D, `strafe_left` = A (no analog strafe binding).
- GOG UserProcess::Execute `FUN_0060a480` (identified by `gprox00.wav`/`cammo.wav`, as C15F 0046/0046fad6_UserProcess_Execute.c): `ctrl.steer` (+0xC4) = analog
  `*(int*)0x009198B0/65536` low-passed x5 when neither arrow byte is set (GD FUN_0060a480:253-260), else `(0x009198B5 - 0x009198B4)` x1 (lines 262-270); a steer-assist branch
  mixes a target term in when `0x009198B6` and `user+0x78` are set (lines 272-317). `ctrl.strafe` (+0xCC) = analog `0x009198A8` or digital `(0x009198AC - 0x009198AD)` x3 (lines 397-414).
  1.5 has the same blend by name (C15F 0046/0046fad6_UserProcess_Execute.c:127-131 steer, 155-161 strafe), which names the bytes: B5 steer_left, B4 steer_right, AC strafe_right, AD strafe_left.
- Conclusion: mouse and arrow keys share `ctrl.steer` (risk 3 is real at the struct level), but A/D reach only `ctrl.strafe`, and the raw globals keep mouse and arrows apart. The split
  is possible: read the mouse from 0x009198B0 directly (section 4, step 1). Not checked: Steam/relocated images (the raw-mouse doc's image-base guard applies; fail closed off 0x00400000).
**Q3 Animation cadence.**
- Frame step `FUN_00618060` (running branch): line 12 `FUN_0062bc80` walks every obj76 and calls class-function field +0 (`FUN_0062bd40`:14-15), which is GameObject::Simulate 0x004DEEC0
  for class indices 1-7 (GX table 0x008EC7AC + idx*0x34); that calls slot 15 in its sub-steps (GD FUN_004deec0:71, 103). Line 14 `FUN_0062b6b0` (AnimObj_Update) then runs once.
  Line 16 `FUN_0062cc50` sits between them: it only calls `FUN_0077c610` (GD FUN_0062cc50:5), which gets or creates a singleton (`FUN_0077c670`:16-26) and runs a 2D grid loop
  over it (`FUN_0077bf30`:9-19). None of that touches obj76 nodes at that depth; its callees `FUN_0077b000`/`FUN_00778450` were not followed (UNVERIFIED that they leave nodes alone).
  Line 17 `FUN_0062bdb0` calls field +4 (`FUN_0062bdf0`:14-15) = 0x004DF370, which calls slot 16 PostSimulate (GD FUN_004df370:11).
- AnimObj_Update advances every playing animation (state 1, GD FUN_0062b6b0:16-33) and walks the whole node tree from the root (`FUN_0062b3c0`:14-24); for each node with a matching
  track `FUN_0062afe0` builds the local 4x4 from keys (or the track's rest values when it has no keys, lines 26-36) and copies 16 dwords into node+0x20, then calls the sync
  0x00681A00 (lines 94-100). Walker::Simulate only starts/stops/rates the clip (GD FUN_0060bd60:349-358).
- Conclusion: leg locals are rewritten every frame while the clip plays, after all Simulate sub-steps and before PostSimulate. Leg writes must go in PostSimulate; they compose on the
  fresh clip pose each frame. When the clip is stopped nothing rewrites them, so step 7's `lastWritten` check is still needed. That Walker's class index has a PostSimulate entry
  is inferred from HoverCraft (TC uses PostSimulate, TC:66-70) and the shared table: UNVERIFIED for Walker, check with one log line in M1.
- Branch B of `FUN_00618060` (lines 28-47, when `FUN_00451de0` is true: not net game and `[0x0094672C+0x30]&1`) simulates only one object and runs no AnimObj_Update; meaning
  of that flag is UNVERIFIED (paused/single-step mode is the likely reading). The design is unaffected: no anim update means no overwrite.
**Q4 UpdateWeaponAim call order.**
- Walker::Simulate ends with `FUN_004ab380` (Craft::Simulate tail; GD FUN_0060bd60:731, GX call at 0x0060E0EB with `ecx = this`). That tail calls slot 38 when `this[0x68]`
  (+0x1A0, the weapon list) is non-null (GD FUN_004ab380:333-335; GX `mov edx,[eax+0x98]` 0x004AC0E1, `call edx` 0x004AC0E7). It is its last vtable call.
- No other per-frame caller for a Walker: the other slot-38 dispatches are `FUN_0059d340`:1121 (another class's Simulate) and `FUN_005faac0`:51 (a state switch on a different
  object); nothing calls 0x0060F320 directly.
- Conclusion: UpdateWeaponAim runs inside the stock Simulate, so under the swap it aims along the legs frame; re-running slot 38 after swap-back (section 4, step 6) repairs it.
**Verdict: GO for the frame-swap design (no fallback).** Amendments: (a) step 1 reads the raw mouse axis global, not `ctrl.steer`; (b) step 7 (leg re-pose) runs in a PostSimulate
(slot 16) wrapper. M1 verifies by log: root yaw = head, slot 38 re-run, PostSimulate reached for Walker, mouse/key split, and 0x009198B0 read in Simulate tracking `ctrl.steer` under mouse-only input.

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
1. Walk clip rewrites leg nodes every frame after Simulate (confirmed by M0): leg pose goes in PostSimulate. 2. Weapon aim called inside the swapped call (confirmed by M0; re-run after swap-back).
   3. Mouse and arrow keys share `ctrl.steer` (confirmed by M0), mitigated by reading the raw mouse axis 0x009198B0; if that read proves unreliable, fall back to "mouse plus arrows head, A/D legs". 4. Root yaw jumps by `delta` between sub-steps could confuse collision or Lua `GetTransform` readers (they see the head frame, which is intended). 5. Cockpit jitter regression.
6. Extracting the tank helpers touches shipped tracked code: run the tracked tests and one tank live check. 7. Seismic/other omega code acts on the root and so on the head (Docs/SEISMIC_WALKER_IMMUNITY_SCOPE.md:12-18): no change.

## Decisions recorded (user, 2026-11-18)
- Control model: v2 independent twist; mouse/aim turns the head, movement keys steer the legs. Walkers: generic opt-in for any ODF naming its torso; verify on avwalk first, svwalk `sup` later.
- AI: player only first, AI stays stock. Network: SP only for v1. Yaw limits: unlimited unless `yawMin`/`yawMax` are set. Shared code: extract the tank's node/pose helpers into a shared header, no duplication.

- Sidestep: losing the stock strafe on twist-enabled walkers is accepted (user). Head aim: world-stabilised. Milestones: M1 and M2 as separate PRs, M0 gates both, fallback "legs follow the head" if M0 fails.

## Open questions (still open)
None; next step is the M0 probe.
