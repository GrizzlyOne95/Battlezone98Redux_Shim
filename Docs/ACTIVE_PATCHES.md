# OpenShim Active Patches

This file tracks compatibility fixes whose reverse-engineering/root-cause phase is sufficiently complete to move into production implementation or runtime qualification.

An item belongs here only when the failure mechanism is understood well enough that the proposed patch can be narrowly scoped. Research-only hypotheses should remain in the regression/reverse-engineering backlog until that gate is met.

## Active

| Patch | Classification | Phase | Next gate |
| --- | --- | --- | --- |
| CLI multi-parameter / `shellmap:<W>,<H>` parser repair | **Legacy 1.5 defect / OpenShim compatibility enhancement** | **Implementation ready** | Implement the post-parser repair from the pristine command-line snapshot, then qualify Steam + GOG runtime behavior. |
| Unit loadouts M1 (`[Gameplay] UnitLoadouts`, default off, single player; `OPENSHIM_DISABLE_UNIT_LOADOUTS`) | **OpenShim gameplay enhancement** | **Implemented, runtime qualification pending** | Live SP test of the checklist in `Docs/UNIT_LOADOUTS.md` (Alt+pick opens the loadout pages in the Recycler/Factory menu, weapon page lists Armory weapons with their price, build figure = stock + full Armory price, charge and cancel refund agree, chosen weapon fitted at FinishBuild, lock while building, no Armory = stock, unfitted weapons credited back, mission change resets loadouts); Alt reaching the game is unverified. M2 save sidecar not built. |
| Producer rally points (`[Gameplay] ProducerRallyPoints`) | **OpenShim gameplay enhancement** | **Implemented, runtime qualification pending** | Live SP test of the checklist in `Docs/PRODUCER_RALLY_POINTS.md` (V arms rally mode, the Reticle Command key sets the rally, V cancels, Shift+V clears, new units drive to the rally, HUD marker shows while selected, "V Rally Point" command panel row under TAB Cancel (aligned; inside or below the underlay), scavengers/constructors skipped, editor and MP untouched). |
| Single-player player paint (`[SinglePlayer] PlayerPaint`, Options row Paint) | **OpenShim gameplay enhancement** | **Implemented, live test pending** | Native, no mod needed: `src/patches/sp_player_paint.cpp` clones the player ship's materials per tint (t2/t3/t4) and binds the BC4 masks from `scripts/build_sp_paint_masks.py` on the en-high `teamMap` unit (no engine hook, no `patches.json` row). Off in network games. Gate: the live checklist in `Docs/SP_PLAYER_PAINT.md` (each tint, ship change, AI untouched, en-medium stock, MP off, reload with no clone leak, BC4 loads on D3D11). |
| Auto-group new units (`[Gameplay] AutoGroupNewUnits`) | **OpenShim gameplay enhancement** | **Implemented, runtime qualification pending** | Live SP test of the checklist in `Docs/PRODUCER_RALLY_POINTS.md` (new tank on an F1-F7 group, all-same-ODF grouping and the 10-unit cap, save/load keeps the group, MP untouched). |
| Extended unit cap (`[Gameplay] ExtendedUnitCap`) | **OpenShim gameplay enhancement** | **Implemented, runtime qualification pending** | Live SP test of the checklist in `Docs/PRODUCER_RALLY_POINTS.md` ("Group member list": an 11th offensive unit builds and joins a group, a slotless unit takes a freed slot, save/load, MP untouched). |
| Group member list (`[Gameplay] GroupMemberMenu`) | **OpenShim UI enhancement** | **Implemented, runtime qualification pending** | Live SP test of the same checklist (second F-key press lists the group on keys 1-0, Ctrl "All ..." labels, Ctrl+Offense adds grouped units). |
| HUD group strip (`[Gameplay] GroupStrip`) | **OpenShim UI enhancement** | **Implemented, runtime qualification pending** | Live test of the checklist in `Docs/PRODUCER_RALLY_POINTS.md` ("Group strip": unitName labels, no overlap with the scrap/pilot gauge from 640x480 to 4K, hidden in pause/shell/satellite). |
| Weapon-mount transform getters (`OpenShimGetHardpointTransform`, `OpenShimGetNodeTransform`; EXU `GetHardpointTransform`/`GetBoneTransform`) | **OpenShim read-only API for EXU** | **Implemented, SP live-tested** | MP live test of the getters; then the Lua mount module (`Docs/WEAPON_MOUNTS_SCOPE.md` section 5). |
| RTS command extras (`[Gameplay] RtsRemoteTarget`, `RtsSmartCommandMenu`, `RtsSmartRepairReload`, `RtsAreaSelect`, `RtsHold`, `RtsBuildAtNav`, `RtsIdleUnitAlert` (and the J idle-unit key), and the placement aids `RtsBuildGhost`, `RtsPendingBuildGhost`, `RtsPowerRange`, `RtsWaypointLines`, and the default-off under-attack rings `RtsAttackMarks` in `Docs/RTS_MARKERS.md`; the default-off Shift-queued orders `RtsOrderQueue` in `Docs/RTS_ORDER_QUEUE.md`; the default-off Recycler/Factory build queue `RtsBuildQueue` in `Docs/RTS_BUILD_QUEUE.md`) | **OpenShim gameplay enhancement** | **Implemented, runtime qualification pending** | Live test of the checklist in `Docs/RTS_COMMANDS.md` (mixed Ctrl+1 group keeps Hunt/Follow Close/Defend with smart skip, Repair/Reload only to units that need it, Shift+T/B target cycles, X/Shift+X area select incl. satellite, Z and Shift+Defend Hold in SP, Hold inert in MP, Build at Nav valid/refused/mixed/moving/MP, J/Shift+J idle select and the idle alert on scavengers, tugs and rigs). |
| Producer build badges (`[Gameplay] RtsProducerBadges`, default off) | **OpenShim UI enhancement** | **Implemented, runtime qualification pending** | Live test: a busy own Recycler/Factory/Armory/Constructor shows its item name and build percent matching the stock progress; idle and enemy producers show nothing; see `Docs/PRODUCER_BADGES.md`. |
| Scavenger instant start (part of `[SinglePlayer] SmartScavengerPathing`, no ini key of its own) | **OpenShim gameplay enhancement** | **Implemented, runtime qualification pending** | Built scavengers skip the 5 s coast in `ScavengerProcess::InitState`: the age-test `jbe` at 0x005C44EF becomes `jmp` (0x76 -> 0xEB), the path stock takes for units placed at mission start. The 5 s WAIT state (InitState case 1, `addss xmm0,[0x008A285C]` at 0x005C45F1; entered when a RecycleTask finishes with no scrap, DoState 0x005C4AA0 case 4) gets a 0.5 s floor instead: only the addss disp32 changes, to the existing read-only 0.5f at 0x008A2584. The wait is not removed because with no reachable scrap the scan and FindPlan would rerun every few frames. Side effect: every WAIT entry (also after Go To, Stop, or a finished Follow/Rescue/Retreat/Cash-out) lasts 0.5 s. Neither shared constant is written. Single player only: stock bytes restored online or when the option is off (`RefreshScavengerInstantStartState`, registry row `ScavengerInstantStart`); scrap scoring and en-route retarget also return to stock online, before any per-ODF `scrapPathingAI` override. Code: `src/patches/ai_odf_tuning.cpp`; sites `ScavengerInitStateAgeBranch` and `ScavengerInitStateWaitDelayOperand` in `scripts/patches.json`. That the reported idles after `BuildObject` and after a scrap run come from this WAIT path is UNVERIFIED. Gate: live SP test that a Recycler-built and a Lua-built scavenger start at once (log `[SCAVPATH] scavenger instant start: on`, `scavenger wait floor: 0.5 s`), that a scavenger with no scrap left re-polls about twice a second without frame-time cost, that it waits about 5 s with the option off, and that an MP session logs `off (network game)` for both. |
| Seismic walker launch scale (ODF `[SeismicWaveClass] walkerVelocityScale`, float, default 1.0 = stock) | **OpenShim gameplay enhancement** | **Implemented, runtime qualification pending** | Multiplies the linear velocity a seismic wave (Thumper) adds to `WALK` targets; 0 = no launch. Tumble stays on stock `walkerScale`. ODF-driven, but MP needs every peer on an OpenShim build with this patch (a stock peer still launches the walker and desyncs). Not inherited by child ODFs: an absent key is 1.0. Non-finite values fall back to 1.0. Code: `src/patches/seismic_walker_velocity_scale.cpp`; sites `SeismicWaveClassBuildingScaleRead` and `SeismicWaveSimulateAddVelocityCall` in `scripts/patches.json`. Gate: live test of a walker hit by a Thumper wave with and without the key. |
| Tracked vehicle class (ODF `classLabel = "tracked"`, no ini option) | **OpenShim modding enhancement** | **Implemented, live-checked 2026-11-16** | Phase 2 adds per-instance `tread_L`/`tread_R` skeleton clips and the ODF `treadSound` loop (PostSimulate slot 16, release in slots 0/3/4; fails closed to phase 1 if a resolve misses). Phase 2b adds an opt-in rotating turret (`[TrackedClass] turretName`, yawRate/yawAlpha/yawMin/yawMax): the root frame is the turret, the hull is a counter-rotated pose of the root's children, posed through the `Obj76::SyncNode` resolve (0x00681A00); fails closed to plain tracked. Phase 3 (multiplayer, live-checked with two LAN peers 2026-11-17): the owner simulates; a remote replica skips the contact model and hull rule and dead-reckons on the replicated veloc/omega (gate: `DistributedObjectIsRemote` + `IsNetGameFlag` rows, fails closed to the owner model); the turret angles a peer owns are broadcast in one `'T','Y'` batch per frame (up to 16 records of id/delta/rate) keyed by the stock DistributedObject id (`DistributedObject::GetLocalID`, `Net::BroadcastSend`, shared Net::Receive dispatcher). Every peer must run OpenShim and the mod. Optional tread texture scroll (`[TrackedClass] treadScrollU`, `treadMaterialL/R`; Direct3D 11 + Enhanced only): a signed U phase per side goes to Renderable custom parameter 1411 on the SubEntities using the named materials (GPU skinning clones included); OpenShim's Enhanced HLSL4 base vertex programs add a constant-0 `osTreadUV` to U, bound to custom 1411 at run time only on those materials' passes; the names are registered at ODF read so GPU skinning builds no instanced twin for their clones (other passes keep instancing); fails closed to clips only. Not yet exercised live: object floors, a destructor release with a live loop, the clip pose on a real tread rig, and the texture scroll; see `Docs/TRACKED_VEHICLES.md` Verification. |

### CLI multi-parameter parser repair

Technical plan:

`Docs/Archive/2026/CLI_MULTIPARAM_PARSER_ACTIVE_PATCH_20260831.md`

Primary RE deliverable:

`reverse_engineering/redux_cli_multiparam_parser_root_cause_20260831.md`

Proven invariant:

```text
1.5 top-level strtok delimiter:   " ,"
Redux top-level strtok delimiter: " ,\t"
option-specific shellmap grammar: ":%d,%d"
```

The comma conflict exists in both 1.5 and Redux. Redux's added tab delimiter is a real parser difference but is not the cause of the reproduced multi-value failure.

Selected production strategy:

```text
process attach
  -> preserve pristine GetCommandLineA()
  -> let stock Redux parser run unchanged
  -> after FUN_007D5120 returns, re-read only shellmap:<W>,<H>
     from the pristine snapshot using whitespace-only token boundaries
  -> validate both dimensions
  -> repair 0x009183D4 / 0x009183C4
  -> continue before the first known consumer at 0x00618D2C
```

Do not replace the complete stock parser for this patch.

### Promotion rule

Move the item out of **Active** only after:

- production repair is enabled;
- malformed-input tests pass;
- unrelated CLI switches remain unaffected;
- GOG 2.2.301 runtime qualification passes;
- Steam runtime qualification passes;
- diagnostics prove the repair is applied only when intended.

Once those gates are satisfied, preserve the case as a permanent regression test rather than deleting the documentation.
