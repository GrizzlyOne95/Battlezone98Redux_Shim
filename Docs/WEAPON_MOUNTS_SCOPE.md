# Scope: "taps" / child turrets on hardpoints for BZR-OpenShim

**Status (2026-11-16):** BZ2 "taps" are power taps, so this is a new feature ("weapon mounts"). No go/no-go decision yet on the Lua slice.

Status: read-only scoping. Anything without a cite is UNVERIFIED.
D = <GIT>\Battlezone_Source\BZ2\_analysis\global_decompile\bzcc_battlezone2_20190509\results\bins\battlezone2_unpacked.exe-a533c2\decomps
S = <GIT>\BZCC-Source-Backup\BZCC 2.0.185 DLL Source Code

## 0. Premise check (important)
In BZ2/BZCC a "tap" is a POWER tap, not an autonomous child turret. The names show it:
- ODF keys are `powerTapN` (hardpoint node name), `powerNameN` (class of the child to build) and `AutoBuildTapN`, N=1..8
  (D/ReadTapHelperClass-00581a61.c, sprintf "powerTap%d", "powerName%d", "AutoBuildTap%d", loop of 8).
  Lives under `[PoweredBuildingClass]` / `[TurretCraftClass]` (D/PoweredBuildingClass-00573e08.c:
  `ReadTapHelperClass(...)` called from the class ctor; S/Missions/LuaMission/ScriptUtilsExtension.cpp:296-297 names both sections).
- Taps exist only on PoweredBuilding and TurretCraft (gun tower) (S/Source/fun3d/ScriptUtils.h:2272-2281 comment: "poweredbuilding (or derived)/turretcraft").
- Purpose: a power generator child must be built at the tap for the parent to be "powered"
  (D/TurretCraft UpdatePowerState-0058a29c.c; D/NeedsTap-0068d4dd.c; S/AI Processes/ConstructionRigProcess.cpp:1300-1375 builds the missing power class).

So "taps" as a way to get a walker with two autonomous arm guns is NOT a BZ2 feature. BZ2 has no autonomous-child-turret system that I found.
The nearest BZ2 thing for a walker arm is `turretName`/`turretObj` (TurretControl), which is aim limits for the craft's OWN gun node, not a separate object with its own AI
(D/TurretControl-00624844.c: stores limits/node data only; D/TurretCraft-0058aa7c.c creates one per turretName slot).
Candour: building the requested feature = a new OpenShim feature, not a port. Do not call it "taps" in docs (name clash with BZ2 power taps).

## 1. How BZ2/BZCC taps actually work (for reference / reuse of ideas)
- Class data: TapHelperClass, size 0x254 (D/TapHelperClass-00581a2f.c memset 0x254, flag 0x230 = 1 default, byte 0 = 1 default).
  ReadTapHelperClass reads 8 hardpoint names (0x40 chars each), 8 class refs, 8 AutoBuild bools, plus one bool at +0x230
  that is most likely DestroyTapsWithParent (CRC 0xf323a095; the BZCC source names the key at ScriptUtilsExtension.cpp:296; CRC to name match UNVERIFIED).
- Instance data: TapHelper (0x48 bytes): handles[8] at +0, saved handle copy at +0x20, count +0x40, power sum +0x44
  (D/TapHelper-00581c71.c, D/Constructor-00581c8d.c). Constructor resolves each hardpoint name with `obj_find_name()`
  and sets slot to -1 (build lazily) when AutoBuild is set, else 0.
- Spawn: `GetPowerObject(i)` lazily builds when slot == -1 (D/GetPowerObject-00573c65.c); `AddPowerObject(i)`
  computes the hardpoint's world matrix `FamilyNode::CalcSimWorldMatrix`, calls `GameObjectClass::Build(matrix, team = parent flags & 0xf, ...)`,
  `GameObject::SetOwner(parent)` and `AiMission::AddObject()` (D/AddPowerObject-00573b01.c). So the child is a normal independent GameObject built once at the hardpoint pose
  with parent as owner. I found NO per-frame re-attachment in what I read: buildings and gun towers are static (TurretCraft ctor calls SetMovable(0): D/TurretCraft-0058aa7c.c).
  "How the child follows the parent transform" = it does not; it is placed once. (A search for a per-frame follow was not exhaustive: UNVERIFIED.)
- AI/targeting: none for a power tap. Team = parent team (flags & 0xf at Build). Targeting is the child's own class AI if it had any.
- Script API: `GetTap(h, idx)` returns slot idx<8 handle (D/GetTap-004d2de3.c: vtable +0xe0 = IsPoweredBuilding -> obj+0x20b*4 table, vtable +0xfc = IsTurretCraft -> +0x25c table),
  `SetTap(h, idx, tap)` writes the slot (D/SetTap-004d2d8e.c). Lua docs: S/Missions/LuaMission/LuaMissionDocs.txt:2130-2136.
- Death/cleanup: ODF bool DestroyTapsWithParent (default true). BZCC's own Lua respawn helper copies taps back with SetTap only when it is false
  (S/Missions/LuaMission/ScriptUtilsExtension.cpp:293-314). Destruction path itself: not located. UNVERIFIED.
- Damage: no evidence that damage passes to the parent. UNVERIFIED (not searched in D).
- Save/load: TapHelper::Save writes a "powerHandle" array of count*4 bytes (D/Save-00581d1d.c); PostLoad runs `ConvertHandle` on each saved handle (D/PostLoad-00581d6e.c).
- MP sync: not found in decomps read. UNVERIFIED.
- Selection/commands: a tap is a separate object, so it is separately selectable/targetable. The rig builds missing taps (ConstructionRigProcess.cpp:1300-1375).

## 2. What BZR already has
BZR is BZ1-engine; the PDB-derived class list and exe have no tap concept (no match for powerTap/turretName/AutoBuildTap in OpenShim Docs or src/patches
by grep of Docs/*.md and src/patches/*.cpp; the BZ1 corpus grep for the strings was started but not read, so treat as UNVERIFIED for the BZ1 1.5 corpus).

Reusable pieces that exist:
1. Per-frame driver: `TickOpenShimEventLayer()` in `LegacyWorldUpdateRenderQueueHook`, "the shim's designated safe per-frame driver" (Docs/NATIVE_EVENT_LAYER.md section 2.1).
   Event sinks for damage/kill (Docs/NATIVE_EVENT_LAYER.md section 2.2, 3.1-3.2): SimDamage(victim, damager), SimKill. Damage hook sites 0x0047EFA0/0x004AA678/0x005A0CE2/0x005AA372, healthRatio at obj+0x200, death latch objectState+0x14 bit 0x200.
   Lifetime rule: re-resolve by handle, never cached pointer, the arena reuses slots (same doc).
2. Hardpoint/muzzle pose: OpenShim exports `OpenShimGetWeaponMuzzle` (src/patches/weapon_presentation_native.cpp:1401); EXU wraps it as `exu.GetWeaponMuzzlePosition(handle, slot)`
   (ExtraUtilities/src/Game/EntityRenderApi.cpp:332-345, Definitions/ExtraUtils.lua:3770). Position only; the full pose Matrix exists internally (WP::Matrix, weapon_presentation_native.cpp:114) but is not exported as a matrix. Native weapon hardpoint mask lives at [carrier+0x2C] (scripts/patches.json entry for Person::Simulate 0x0059D340).
3. Ogre bone attach exists for particles only: `exu.AttachParticleSystemToBone/Object` (ExtraUtils.lua:1020-1029). No GameObject attach.
4. Lua: `BuildObject`, `SetOwner/GetOwner`, `SetTransform/GetTransform`, `SetPosition`, `SetVelocity`, `RemoveObject` (Docs/BZR_LUA_AGENT_REFERENCE.md:619-700).
   Stock ownership: `SetOwner` exists. `exu.SetAsUser`, `exu.ClaimVehicleControl` exist (ExtraUtils.lua:1572, 2322).
5. Class hooks for AI quirks: TurretTank::GetCommand 0x005F5D10, InitAttack 0x005F7710, Craft::GetCommand 0x004AE110 (Docs/TURRET_ATTACK_ORDERS.md; src/patches/turret_attack_orders.cpp). Shows how OpenShim already patches per-class AI.
6. MP facts (project-validated, Docs/BZR_LUA_AGENT_REFERENCE.md:537-548): BuildObject is safest from the owning machine; SetPosition on a remote object has locality problems;
   RemoveObject on remote objects is restored by remote state; MP Lua replication is not qualified (Docs/MP_LUA_REPLICATION_QUALIFICATION.md header). BuildObject binding 0x004ffb70, transform spawn 0x005c82b0.
7. Walker: Docs list walker cockpit chain only as diagnostic (src/patches/walker_cockpit_trace.cpp); no walker arm-gun mechanism.

## 3. Designs

### A. EXU + Lua "mounted turret" (recommended minimal slice)
- Mod ODF side (no engine change): arm gun = an ordinary turret-class/gun-tower style unit ODF (immobile, own weapon, own AI) built via BuildObject, team = parent.
- Lua per frame (via an existing update hook): for each registered parent/mount pair, compute parent hardpoint pose, `SetTransform(child, pose)`, zero velocity, `SetOwner(child, parent)`; remove child when parent handle dies; mirror health optionally.
- Gap that needs native work: a hardpoint (or bone) world MATRIX getter. Add an export next to OpenShimGetWeaponMuzzle returning the full 4x4 (weapon_presentation_native.cpp:114 already holds a Matrix) and an EXU wrapper `exu.GetHardpointTransform(h, slot)`. For arm bones that are not weapon hardpoints, an Ogre bone world transform getter (the particle-attach code already resolves bones; ExtraUtils.lua:1022).
- Child must not collide with parent: needs either spawning with the engine's no-collision relationship (UNVERIFIED how) or letting SetTransform run before collision (UNVERIFIED).
- Effort: S-M (getter export + wrapper + a small Lua module, ~1 week of testing). Single-player first.
- Risks: lag of one frame behind parent motion; MP: SetTransform on non-local children (see 2.6) - run the follow only on the machine that owns both; save/load: children are normal objects so they save, but the pair registry in Lua must be rebuilt (use `GetOwner` of child as the pair key; ExtraUtilities Storage/Continuity.lua exist for this - not read).

### B. Native OpenShim feature (taps-like, ODF-driven)
- New ODF keys on the parent class (e.g. `mountN`, `mountClassN`, hardpoint/bone name), read in a hook on object creation (anchor: a Craft constructor; Walker class address not located by me), child built via the engine factory 0x00571c30/0x005c82b0, parent stored in child via SetOwner, per-tick pose follow from the event layer tick, clean-up on SimKill of parent.
- Needs: RE of the Walker/Craft ctor and save/load serialization (add a "mountHandle" array like TapHelper::Save), MP distributed-object handling (0x004b8460 call in spawn path, MP_LUA_REPLICATION_QUALIFICATION.md), selection suppression for children, damage forwarding.
- Effort: L (3-6 weeks incl. MP qualification). Do only after A proves the design.

### Minimal viable slice
1. Export + EXU wrapper for hardpoint full transform (or per-bone transform) [S].
2. Lua demo: walker with 2 mounted turret children, SP only, parent-death cleanup [S].
3. Defer MP, save/load restoration, damage forwarding, selection rules.

### Risks summary
- MP determinism: child pose written per frame on one peer only; SetPosition on remote objects has locality problems (2.6). Child targeting RNG/AI must run on the owning machine.
- Save/load: engine saves the child as a normal object; pairing must be re-derived (GetOwner), BZ2 saved a handle array (D/Save-00581d1d.c) and converted on load (D/PostLoad-00581d6e.c).
- Selection/commands: children are selectable and commandable unless the class is made unselectable; BZ2 taps were selectable objects too.
- Collision: parent/child overlap; stock physics may shove the parent. UNVERIFIED - needs a live test (use bzr_livetest.lock flow per CLAUDE.md).
- Lifetime: re-resolve by handle each tick (arena slot reuse, NATIVE_EVENT_LAYER.md 3.2).

## 4. Not checked / open
- BZ1 1.5 decompile (Battlezone_Source/BZ1/1.5/all_decompiled.c) for a native hardpoint-matrix function and Walker class - search started but not read.
- BZ2 destroy path for taps and damage forwarding.
- Whether `SetTransform` is safe every frame on a craft-class object in BZR (OpenShim docs say use SetTransform for orientation; no per-frame stress evidence read).
