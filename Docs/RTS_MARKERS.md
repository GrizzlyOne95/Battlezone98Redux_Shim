# RTS Markers

Ground rings that show RTS-style feedback for the local player. There are two features, and each has its own option:

- **Command pings** (`[Gameplay] RtsCommandPings`, Options > HUD > Command Pings, default off). Each order the local ControlPanel issues draws one short ring:
  - **Go to a point:** a green ring that shrinks onto the point and fades over 0.9 s.
  - **Attack on an object:** a red ring around the target that follows it and fades over 1.0 s.
  - **Any other order on a point or object:** a yellow ring that fades over 0.9 s.
- **Artillery range** (`[Gameplay] RtsArtilleryRange`, Options > HUD > Artillery Range, default off). It draws:
  - a blue max-range ring around every selected own-team howitzer (Howitzer vtables) that carries a gravity-ordnance cannon slot (at most 16 units); never around the piloted vehicle, whose mortar arc the laser sight already draws;
  - a 3 m ring at the aim point, green when at least one of those units can reach it and red when none can.

The native range rings for selected units (direct-fire weapon, radar, own-team mine trigger, and the labels on them) are documented in `Docs/RTS_RANGE_RINGS.md`: `[Gameplay] RtsWeaponRange`, `RtsRadarRange`, `RtsMineRange` and `RtsRangeLabels`, all off by default. They use slots 167-222 of this pool.

Both features above are local visuals only:

- Nothing is sent, saved or written to the engine.
- They have no network gate; the rings are shim-owned Ogre ManualObjects.
- They hide while the HUD is hidden (Ctrl+=, `HudVisibility::IsHidden()`).

Where the code lives:

- Code: `src/patches/rts_markers.cpp`.
- Pure logic: `include/rts_markers_policy.h`.
- Generated assets: `include/rts_markers_assets.h`.
- Tests: `tests/rts_markers_policy_tests.cpp`.

## Ring renderer

The pool has `RtsMarkers::kPoolSize` = 23 slots:

| Slots | Use |
|---|---|
| 0-15 | artillery range |
| 16 | cursor |
| 17-22 | pings |

Each slot is one dynamic ManualObject on its own child of the root scene node.

- **Lifetime:** a slot is created on first use. After that it is only rebuilt (`beginUpdate`), moved and shown or hidden; it is never created or destroyed per frame.
- **On scene teardown** (`clearScene`, `destroyAllMovableObjects`), `lifecycle_seams.cpp` drops the pointers without an Ogre call, and Ogre frees the objects.
- **When leaving the simulation**, every ring is hidden and pending pings are dropped.

Geometry:

- **Strip:** a triangle strip of `SegmentsFor(r)` segments (one per 4 m of circumference, clamped to 48-96).
- **Band width:** `RingWidthFor(r)`, from 0.5 to 2.5 m.
- **Height:** every vertex samples `Terrain::HeightAt` and sits `kLift` = 0.4 m above it, so the ring follows the ground. Between samples, chords can still cut through sharp ridges on large rings.
- **Placement:** the node sits at the ring centre in render space (x, y, -z minus the render origin). The vertices are local offsets that do not depend on the origin.
- **Rebuilds:** geometry is rebuilt only when the centre, radius or colour changes.

Material `openshim_rtsmarker_ring`:

- It is written to the chunk cache root as `openshim_rtsmarker.material` plus `openshim_rtsmarker-sm4.hlsl`, and loaded in the `OpenShimChunkPayloads` group.
- Pass states: unlit, vertex colour and alpha, `scene_blend alpha_blend`, `depth_check on`, `depth_write off`, `cull none`, no shadows.
- Technique 0 is an SM4 pass-through shader for DX11.
- Technique 1 is fixed-function for DX9, with fog off.
- The ManualObject keeps Ogre's default queue (50), after terrain's 0x28 (Docs/terrain-render-path.md:137). The transparent pass is sorted after opaque geometry.
- An asset pack overrides either file by shipping the same name, as for LaserSight.

The tick is `TickRtsMarkers(dt)`:

- It is called from `ChunkEffect::Simulate` on the game thread (bzr_hooks.cpp), after the rally beacons.
- It is skipped while `InsideRenderQueueHookWithDeferral()` is true.
- Ping animation advances on simulation dt, so it pauses with the game.

## Order paths

The decompile corpus is `reverse_engineering/repo_corpora/bzr_gog_best_effort/ghidrecomp/.../decomps/`. Addresses are on GOG Redux 2.2.301.

| Path | Hooked | Citation |
|---|---|---|
| `ControlPanel::BroadcastCommand(what, VECTOR_3D*)` 0x004A70C0, ground orders | Yes, by a listener on the existing ProducerRally detour (`SetBroadcastCommandListener`); no second detour | `FUN_004a70c0-004a70c0.c` lines 9-13 (see Docs/PRODUCER_RALLY_POINTS.md); OverView `FUN_00587ef0-00587ef0.c` line 211 |
| `ControlPanel::BroadcastCommand(what, GameObject*)` 0x004A7050, orders on an object | Yes, by the new `RTS Markers Object Command Hook` (JMP5 entry detour, pass-through) | `FUN_004a7050-004a7050.c` lines 9-13 (selection walk, CanCommand vtable+0x38, then `FUN_004dbd60(what, target)`); `FUN_004dbd60-004dbd60.c` line 21 (what stored at +0xCC), line 30 (target+0x18, so the target is a GameObject*); OverView `FUN_00587ef0-00587ef0.c` line 214 |
| Number-key menu orders (Defend, Attack, Go to nav) | Yes, they reach 0x004A7050 | `FUN_004a08e0-004a08e0.c` lines 946, 1141, 1270 |
| Per-unit menu `FUN_004a8560`: Follow me 5, Get repair 10, Get reload 11, Rescue 17, Recycle 18 | **No ping** (bypasses both broadcasters; not hooked) | `FUN_004a8560-004a8560.c`; called from the unit classes `FUN_00511c20`, `FUN_005aeab0`, `FUN_005c2250`, `FUN_005ed1f0`, `FUN_005f5ce0`, `FUN_006136a0` |
| Selection (`FUN_004dbce0(1)`, `FUN_004a7a20`, `FUN_0049d0e0`) | No ping by design (select is not an order) | the files of the same names |

Only orders from the global ControlPanel (row `ControlPanelGlobal`) with a non-empty selection make a ping.

### `what` mapping

The values are the AiCommand enum: 0 NONE, 1 SELECT, 2 STOP, 3 GO, 4 ATTACK, 5 FOLLOW, 6 FORMATION, 7 PICKUP, 8 DROPOFF, 9 NO_DROPOFF, 10 GET_REPAIR, 11 GET_RELOAD, 12 GET_WEAPON, 13 GET_CAMERA, 14 GET_BOMB, 15 DEFEND, 16 GO_TO_GEYSER, 17 RESCUE, 18 RECYCLE, 19 SCAVENGE, 20 HUNT, 21 BUILD, 22 PATROL, 23 STAGE, 24 SEND, 25 GET_IN, 26 LAY_MINES.

- The enum comes from the BZ1 source documentation. It agrees with the rally's CMD_GO = 3 (Docs/PRODUCER_RALLY_POINTS.md). The values above 4 are UNVERIFIED against a decompile line.
- `RtsMarkers::ClassifyPing` maps them as follows:

| `what` | Ping |
|---|---|
| 0-2 or above 26 | none |
| 3 | Go (green) |
| 4 on an object | Attack (red) |
| anything else | Neutral (yellow) |

## Artillery range

A unit qualifies when a Carrier weapon slot 0-4 holds a weapon that passes `LaserSight::AppliesShotPitch` and fires ordnance that passes `LaserSight::IsBallisticOrdnance`. This uses the same rows (`LaserArc*`) and layout as LaserSight:

- weapon class +0x08;
- ordnance class +0x0C;
- class signature +0x0C;
- lifeSpan +0x50 (`FUN_00586440.c` line 165);
- shotSpeed +0x54 (line 166).

Max range is `FlatMaxRange(v, T)`:

- v²/g at 45°;
- shortened to v²·sin(2·asin(gT/2v))/g when lifeSpan T ends the flight first;
- g = 9.8, the constant the Mortar test uses (24.01 = 4.9², lines 48-56); the `LaserArcGrenadeGravity` row only guards the layout.

The cursor test `CanReach` matches the engine's own Mortar reach test (`FUN_0056af20-0056af20.c`):

- speed is read from [weapon+0xC]+0x54 (line 37);
- the discriminant is D = (v² − 9.8·dy)² − 4·(1 + dy²/d²)·24.01·d² (lines 48-56);
- the target is reachable when D ≥ 0 (line 74).

The tests check that the two forms are equivalent. `CanReach` also rejects a target when the low-arc flight time exceeds lifeSpan; the engine does not do this (line 74 has no lifeSpan term).

Aim point: ControlPanel+0x1124, a VECTOR_3D* (row `RtsMarkersCursorPointField`, guarding the store at 0x004A720F).

- It is written by `FUN_004a71e0.c` line 12, and by `FUN_004a7230.c` lines 13-18, which sets it to the target position or null.
- Reticle::Simulate `FUN_005ba560.c` lines 157-175 refresh it every frame in views 0, 1, 2 and 7 (line 115), and leave it null when aiming at the sky.
- OverView (satellite) `FUN_00587ef0.c` lines 158, 163, 169, 285 and 288 point it at the satellite cursor, and line 74 clears it.
- The satellite cursor ring is therefore supported by the code path, but this is UNVERIFIED in-game.

## Addresses

| Name | Kind | Purpose |
|---|---|---|
| `RTS Markers Object Command Hook` (0x004A7050) | patch, unique pattern | object-order pings; prologue `55 8B EC 83 EC 0C` is checked before the trampoline |
| `RtsMarkersCursorPointField` (0x004A720F) | engine row | +0x1124 layout guard |
| `ControlPanelGlobal`, `GameObjectHandleGetObj`, `HudFadeGetPlayer`, `HudFadeGetCarrier` | engine rows | shared |
| `LaserArc*` rows | engine rows | shared |
| `Carrier::GetWeapon`, `Terrain::HeightAt` | named addresses | shared |

If any row fails to bind, the feature fails closed:

- Without the base rows there are no rings at all.
- Without the cursor row there is no cursor ring.
- Without the artillery rows there are no range rings.
- Without the hook there are no object-order pings.

## Attack marks

`[Gameplay] RtsAttackMarks` (Options > Controls > RTS Commands, default **off**) draws a pulsing red ring around each of the local player's own-team objects, units and buildings, for 2 s after an enemy hit it.

- **Detection:** no new hook. Stock damage code writes `GameObject::enemyShot = Get_TimeLocal()` when the damage source is an enemy team (BZ1 1.5 decomp `all_decompiled.c:184486-184489`), and `CockpitRadar::Render` flashes the blip while `enemyShot + 2.0 > now` (`all_decompiled.c:241928`). The offset is `0x1E8` (the same field `satellite_visibility.cpp` reads); "now" is the same game-local clock, the `HudFadeRadarTime` row (not `GetGameTime`, which follows the network time offset in multiplayer).
- **Scan:** from the per-frame tick, at most every 100 ms, over the engine's object vector (`GameObject::objectList`, at most 4096 entries). An object counts when its team equals the local player's, it is not the piloted object, it is not dead (obj76 flags 0x200), and `0 <= now - enemyShot <= 2.0`. A stamp of 0, non-finite, or more than 0.1 s ahead of the clock (left over from a previous mission) is ignored. Each frame the marked objects' stamps are re-read, so a fresh hit restarts the pulse and an expired one ends at once.
- **Cap:** at most 16 rings (slots 87-102); with more objects hit, the 16 most recently hit keep theirs.
- **Style:** the attack colour (`kAttackColour`), the radius of a target ring (the object's bounding radius, clamped to 3-40 m, plus 1 m, never above 41 m), pulsing 1 + 0.15 sin(2 pi * 2 Hz * age). Full alpha to 1.5 s, then a smoothstep to zero at 2.0 s.
- **Log:** change-only lines, budgeted at 64 per mission: `[RTSMARKERS] attack mark handle=0x%08X on age=%.2f`, `... off`, and one `[RTSMARKERS] attack marks enabled=%d` at config load and when the option state changes. The state is cleared when the mission ends.
- **Multiplayer:** a local visual with no network gate, like the pings. Whether `enemyShot` is written for remote-owned objects on a multiplayer client is **UNVERIFIED**; rings may only appear for objects the local simulation damaged itself.
- Pure rules: `AttackMarkAge`, `AttackMarkStyle`, `KeepMostRecent` in `include/rts_markers_policy.h`, tested in `tests/rts_markers_policy_tests.cpp`.

## Radar pings

`[Gameplay] RtsRadarPings` (Options > HUD, default **off**) also draws a short expanding, fading ring on the cockpit radar at the position of each order the local player gives, in the colour of the ground ping (green Go, red attack, yellow other). It works with or without `RtsCommandPings`. Local only, nothing is sent.

- **Orders:** the same two paths as the ground pings (`QueuePing`); the radar ping records the world position and the game-local time (`HudFadeRadarTime`, so it pauses with the game).
- **Draw seam:** `contextual_hud.cpp` owns the radar render slot (`HudFadeRadarRenderSlot`). `RegisterRadarPostDraw` (same shape as the command panel one) puts its wrapper in the slot with or without the radar fade; the callback runs right after the stock radar render, inside the fade scope when the fade is on (alpha is scaled by the fade opacity). It is skipped while the radar is hidden (`HudFadeRadarShow` = 0), in the alternate layout (`CommandMenuAltLayoutFlag`), or while EXU owns the radar.
- **Projection (reads of the stock radar, GOG 2.2.301):** `FUN_004933e0` lines 91-117 and `FUN_00493ec0` lines 225-230 give the CockpitRadar fields: +0x08 scanner and +0x0C user object (non-null when the radar works), +0x10 range, +0x14 range squared, +0x20/+0x24/+0x28 user position, basis rows right +0x30..+0x38, up +0x3C..+0x44, front +0x48..+0x50. The radar-space vector is `d = world - userPos`; if `|d|^2 > range^2` then `d *= range/|d|` (the native rim clamp, so off-range orders sit on the rim like contacts); `v = (right.d, up.d, front.d)`. The stock projector `FUN_00493330` is `s = projRadius*5 / (range*5 + v.z)`, `x = centreX + round(v.x*s)`, `y = centreY - round(v.y*s)`. The shim re-implements it in `include/rts_radar_pings_policy.h` (it does not call the engine function) and reads `RadarProjRadius/CentreX/CentreY` live, because `radar_layout.cpp` rescales them.
- **Primitive:** `HudLine` (0x0068AF40, `55 8B EC 8B 45 20 50 8B 4D 1C 51 E8 00 FD FF FF 83 C4 08 50 8B 55 18 52`, read from the shipping exe), cdecl `(buffer, x1, y1, x2, y2, ARGB, mode)`, mode 0 = colour passthrough, buffer = `*HudPaneBuffer`. The native radar grid caller is `FUN_00493ec0` (line 259 area), which calls it as `FUN_0068af40(DAT_00917580, x1, y1, cx, cy, 0xafffffff)`. No new hook: the row is only called. `HudSpriteZ` is raised by 0.0005 around the ring and restored, like the native radar overlays.
- **Style:** 12 segments; lives 1.5 s; radius grows from 0.04 to 0.14 of the projection radius (minimum 3 px); alpha 1 to 0 linearly. At most 8 pings (the oldest is replaced). A ping born after the current clock (clock reset by a mission restart) is dropped.
- **Log:** `[RTSMARKERS] radar pings enabled=%d installed=%d` (change-only) and the first 8 drawn pings (`radar ping drawn at x,y`, with `(clamped to the rim)`).
- Pure rules: `Project`, `Evaluate`, `RadarPingQueue` in `include/rts_radar_pings_policy.h`, tested in `tests/rts_radar_pings_policy_tests.cpp`.
- UNVERIFIED in game: that `HudLine` draws at the expected depth over the radar disc, and the ring look at every radar size. See live checklist item 13.

## Queued-order chain

`[Gameplay] RtsOrderQueue` (`Docs/RTS_ORDER_QUEUE.md`) adds its own pool slots after the attack rings: 48 line slots (`kFirstQueueLineSlot`, one per queued leg) and 16 ring slots (`kFirstQueueRingSlot`, one per distinct queued object target), amber (`RtsOrderQueuePolicy::kQueueColour`). For each selected own unit (at most 16) with a queue, the chain starts where its current order ends and runs through each queued point; a leg to a gone object, or an enemy the player cannot detect, is skipped. Drawn whenever the option is active, independent of `RtsWaypointLines`. The pool-size check is in `tests/rts_placement_policy_tests.cpp`.

## Placement aids

Four more local-only features share the tick and the ring pool. Their rows are on Options > Controls > RTS Commands; all ship off, stock value off.

- **Build Ghost** (`[Gameplay] RtsBuildGhost`). While the stock placement square shows, a see-through copy of the picked building's own mesh stands at the rig's drop matrix, tinted like the square: green valid, yellow no power, red blocked. While the Go To Nav submenu is open and Build at Nav is active for a selected rig with a building picked, a neutral blue-white copy stands at every listed nav (at most 10), on the terrain, facing the player's heading.
- **Pending Build Ghost** (`[Gameplay] RtsPendingBuildGhost`). For each of the local player's Construction Rigs with a BUILD order (the stock reticle order or Build at Nav), a dim pale blue copy of the ordered building stands at the rig's drop matrix, from the order until construction starts, the order is replaced or cancelled, or the rig dies. At most 8 rigs: the first 8 in the engine's object list order; with more than 4096 objects in the list none show. The rig the cursor ghost is previewing shows only the cursor ghost.
- **Power Range** (`[Gameplay] RtsPowerRange`). While a ghost of a `COMM`, `TURR` or `SHLD` class shows (cursor or nav), a yellow ground ring of `powerRadius` around each allied power plant, nearest 16 first. This works with Build Ghost off.
- **Waypoint Lines** (`[Gameplay] RtsWaypointLines`). For each selected own-team unit (at most 16, never the piloted vehicle), a 0.6 m draped ribbon from the unit to its current order's destination (green Go, red Attack, blue Follow / Formation / Defend, yellow anything else; when two units target one object with different orders, the first selected unit's colour wins), and a dimmer one (alpha x0.45) from there to its pending order's destination. Idle units and orders without a path or target draw nothing. An order on an object (the record's `who` handle is set and still resolves) ends its line at the object's live position, replacing the stale last route point, and puts a ring in the line's colour around that object (sized like the attack ping; one ring per object however many units target it, at most 16). The change-only log line `[RTSMARKERS] unit line source=route|straight what=N [target=live]` records which kind each unit drew.

Where the code lives:

- Code: `src/patches/rts_placement.cpp` (ghosts, preview record, plant and command reads); the rings and lines are drawn by `rts_markers.cpp`.
- Pure logic: `include/rts_placement_policy.h`; ghost materials in `include/rts_markers_assets.h`.
- Tests: `tests/rts_placement_policy_tests.cpp`.

### Pool slots

The pool grows to 103 slots with the placement aids and attack marks, 167 with the queued-order chain and 223 (`RtsMarkers::kSlotCount`) with the range rings; slots 0-22 keep the layout above.

| Slots | Use |
|---|---|
| 23-38 | power rings |
| 39-54 | waypoint lines (current order) |
| 55-70 | waypoint lines (pending order) |
| 71-86 | target rings (current order's object) |
| 87-102 | attack marks (under-attack rings) |
| 103-150 | queued-order lines (48), then queued-order target rings (16): `Docs/RTS_ORDER_QUEUE.md` |
| 167-182 | direct-fire weapon rings (`RtsWeaponRange`) |
| 183-198 | radar rings (`RtsRadarRange`) |
| 199-222 | mine trigger rings (`RtsMineRange`) |

`kSlotCount` is 223 with the range rings. See `Docs/RTS_RANGE_RINGS.md`.

A line is the ring strip's other shape: a triangle strip sampled every 4 m (`LineSegmentsFor`, at most 96 segments, the ring vertex budget), each pair lifted `kLift` above `Terrain::HeightAt`. It uses the ring material, `g_PoolFailed` and the rebuild key (now 10 floats: centre, radius or -1 for a line, colour, end x/z).

### How the preview is read

The ghost never drives the preview; it copies what the stock code already decided.

- `ConstructionRig::GetCommand(const VECTOR_3D*)` 0x0049D230 is ConstructionRig vtable 0x00877994 slot 12 (`scripts/audit_vtable_hooks.py`: the slot is its only copy in the image). OpenShim replaces the slot with a pass-through post-hook after checking the RTTI name `.?AVConstructionRig@@` and that the slot still holds 0x0049D230; otherwise nothing is patched and the three rows read Unavailable.
- After the stock call returns, the hook records the rig, the class at rig+0x370, the 64-byte drop matrix at rig+0x378, the result and the tick number. It records only result 8 with the green sprite, or result 9 with the yellow or red sprite. The sprite comes from the global ConstructionDisplay 0x009786D8: +0x68 is the sprite the quad will draw this frame, +0x6C/+0x70/+0x74 the G/Y/R sprites (Init `FUN_0049c390` D lines 7-13). GetCommand sets +0x68 only for a rig allied to the user object (`FUN_0049d230` D lines 50-52, 91-99), so a foreign rig never makes a ghost.
- ConstructionDisplay::Render `FUN_0049c3e0` clears +0x68 after drawing (0x0049C4E1), so the stock quad is one-shot per frame. The ghost does the same: it shows only while the record is from this tick or the last, and never while the flag at 0x02CECF74 is set (Render skips the quad then).
- Build at Nav's own validation call (`NavPickHook`, through the bound function pointer, not the slot) runs inside `SuppressRtsGhostRecord(true/false)`, so it never moves the ghost.
- Mesh: `GameObjectClass::Build` `FUN_004e1190` copies the 8-byte base name at class+0x28 (D lines 80-82), and `FUN_0067f480` creates the entity from `"%.*s.mesh"` of the same bytes (D lines 26-38). The ghost does the same (`MeshNameFor`, printable bytes only) with `SceneManager::createEntity`, then `Entity::setMaterialName` with one of `openshim_rtsghost_g/_y/_r/_n`. The mesh's own materials are never touched. A mesh that fails to load is logged once and not retried until the scene's entities are destroyed or the simulation ends (64 remembered classes).
- Before the first ghost in a scene, all four ghost materials must exist (`MaterialManager` `resourceExists`). Ogre 1.10 `setMaterialName` silently falls back to BaseWhite, so a missing material would draw an opaque white building; instead the ghost stays off for that scene, with one log line.
- Teardown: on `clearScene` and `destroyAllMovableObjects` the pointers are dropped without an Ogre call. On `SceneManager::destroyAllEntities` (mission change, load, replay; the exe keeps one SceneManager per process) `DestroyRtsPlacementSceneObjects` destroys the ghost entities before the original runs and keeps their nodes (lifecycle_seams.cpp, next to LaserSight). The remembered failed classes are cleared there and when leaving the simulation.
- Entities: up to 8 cached cursor ghosts, one per class, one visible at a time (least recently shown is destroyed when a ninth class appears); 10 nav ghosts, rebuilt only when the picked class changes; 8 pending build ghosts, a slot keeping its class while the same orders stand. Names come from Ogre's auto-named `createEntity` overload, so they are unique.
- Materials `openshim_rtsghost.material` and `openshim_rtsghost-sm4.hlsl` are written next to the ring assets. Technique 0 (DX11): an SM4 shader returning the material's `tint`, brightened (x1.15 + 0.05). Technique 1 (DX9): fixed function with ambient, diffuse and specular black and the same brightened colour as emissive, so no scene light changes it. Both: `alpha_blend`, `depth_write off`, `depth_check on`, no fog, back faces culled.

Nav ghosts:

- The submenu is open when ControlPanel+0x117C equals the nav menu id at 0x008E7BF4 (`ControlPanel::Render` `FUN_004a08e0`, gate at 0x004A465A).
- The navs are the user team's slots 0x23..0x2C (`FUN_004a08e0` D lines ~1255-1260; `Team::GetSlot` 0x005E0F70 reads `team + slot*4`, a GameObject*). The user team is the global read by `FUN_00462370`. Empty slots are skipped. GetCommand is never called for them.
- The heading is the player's front vector (GameObject+0xF4, +0x38: `FUN_00462490`), flattened; GetCommand turns a building the same way.

Pending build ghosts:

- Each tick walks the engine object vector (`GameObject::objectList`, as `lua_handle_sync.cpp`). A rig qualifies when its vtable is `ConstructionRigVtable`, its team (+0x174) is the user object's, its byte +0x80 is not 2 (a network replica, as `rts_commands.cpp`) and its obj76 flags lack 0x200 (dead).
- Its AI process is GameObject+0xFC. `RigProcess::InitUState` 0x0049E940 stores `new BuildGoto(rig, ..., class)` at process+0x38 (0x0049E9D5); `ExitUState` 0x0049E9F0 deletes it and clears +0x38. The task must carry `BuildGotoVtable` 0x00877C40 (RTTI `.?AVBuildGoto@@`, checked at bind) and its owner at +0x10 must be the rig.
- The BuildGoto ctor 0x0049DFA0 sets the class at +0x150 and the stage at +0x14C to 0 (0x0049DFF0, 0x0049E003). The stage step 0x0049E3D0 returns early when +0x08 is 13 (0x0049E3E9) and switches over the stage 0..4 (0x0049E416-0x0049E423). Stages (jump table 0x0049E924): 0 travelling (0x0049E433); 1 and 4 final approach (0x0049E5B7, 0x0049E78D), which call the rig's Deploy (vtable +0x60, 0x004AE2B0) and set stage 2 (0x0049E6F6, 0x0049E8EA); 2 deploying (0x0049E72B), set to 3 at 0x0049E741 once vtable +0x68 (0x004AE300, rig +0x228 == 2) reports deployed; 3 deployed and building (0x0049E753), which waits on 0x00472400, calls Undeploy (+0x64) and sets +0x0C to 13 (done). The ghost shows at stages 0, 1, 2 and 4 and hides at 3 or when +0x08 or +0x0C is 13.
- Position and facing are the rig's drop matrix (+0x378), which FinishBuild builds at; the class is the task's +0x150. Material `openshim_rtsghost_n` (the nav ghost's).

Power rings:

- The plant list is the global `std::vector<PowerPlant*>` at 0x025CCE7C (begin +0, end +4; filled by the PowerPlant ctor `FUN_005a7500`, erased by its dtor `FUN_005a75d0`; every team's plants). The read checks alignment, order and at most 1024 entries.
- Each plant must pass `GameObject::IsAlly(rig, plant)` 0x004DB510, called under SEH exactly as GetCommand does (0x0049D429).
- The radius is the plant class's +0x160 (`powerRadius`, read by `FUN_005a77f0`); rings with a radius outside (0, 2000] are dropped.
- The tower test is the class signature at +0x14 against COMM/TURR/SHLD (0x0049D369-0x0049D38D).

Waypoint lines:

- Each GameObject has two 0x20-byte command records: current at +0xA8 and pending at +0xC8 (promote `FUN_004dbb40` copies one over the other; D lines 10-31). `what` is at +0x04, the target object's handle (`who`, 0 without one) at +0x08 (Docs/RTS_COMMANDS.md; FUN_004dbd60.c lines 20-34) and the AiPath* at +0x0C.
- An AiPath has its point count at +0x04 and `{x, z}` float pairs at +0x08 (ctor `FUN_00460490`). The destination is the last point; its height comes from the terrain.
- `what` 0-2 (none, select, stop) or above 26 draws nothing; so does a count of 0 or above 4096, or a non-finite point, unless the order has a live target (below).
- Target lines and rings: `who` resolves through the handle table every tick, so a dead target falls back to the path's end. No live target is used when it is the unit itself, or when it belongs to another team and the local team's bit in its `isVisible` mask (+0x18C, per-team detection bits as `satellite_visibility.cpp` reads them) is clear: the line then ends at the planned destination, so it never tracks an enemy the player cannot see. An order on the piloted vehicle (Follow me, Defend me) ends its line at the player's live position but draws no ring under the camera; the change-only line `[RTSMARKERS] unit line on player what=N end=(x,z)` logs that end each time it moves 25 m. While an order ping already rings the same object, the target ring waits for it to fade. Pings keep their colours (Follow and Defend pings stay yellow); only lines and rings use blue.

### Rows

| Row | Address | Used for |
|---|---|---|
| `ConstructionRigVtable`, `ConstructionRigGetCommandPos` | 0x00877994, 0x0049D230 | slot 12 post-hook (shared with Build at Nav) |
| `RtsGhostDisplaySetBox` | 0x0049D328 | ConstructionDisplay address (imm32 at +0x0E), matrix offset 0x378 |
| `RtsGhostDisplayInit` | 0x0049C390 | sprite fields +0x68..+0x74 |
| `RtsGhostDisplayRender` | 0x0049C3E0 | +0x68 one-shot, the 0x02CECF74 flag (imm32 at +0x18) |
| `RtsGhostPreviewResults` | 0x0049D4C2 | result 8/9 and sprite pairing |
| `RtsGhostMeshName` | 0x004E1297 | class+0x28 base name, 8 bytes |
| `RtsGhostTowerSigCheck` | 0x0049D360 | COMM/TURR/SHLD at class+0x14; class at rig+0x370 |
| `RtsPowerPlantList` | 0x0049D3C5 | plant vector address (imm32 at +0x03) |
| `RtsPowerIsAlly` | 0x004DB510 | IsAlly, called |
| `RtsPowerRadius` | 0x0049D47C | plant class +0x160 |
| `RtsNavSubmenuOpen` | 0x004A465A | +0x117C and the menu id address (imm32 at +0x0E) |
| `RtsNavSlotLoop` | 0x004A49BE | slots 0x23..0x2C |
| `RtsUserTeam` | 0x00462370 | user Team* global (imm32 at +0x04) |
| `RtsTeamGetSlot` | 0x005E0F70 | team + slot*4 |
| `RtsUserFront` | 0x00462490 | +0xF4, +0x38 front vector |
| `RtsCommandPromote` | 0x004DBB40 | record offsets 0xA8/0xC8, what/path |
| `RtsAiPathCtor` | 0x00460490 | AiPath count +4, points +8 |
| `BuildGotoVtable` | 0x00877C40 | BuildGoto task identity (data row, RTTI checked) |
| `RtsPendingBuildTask` | 0x0049E999 | task at process +0x38 |
| `RtsPendingBuildGotoCtor` | 0x0049DFE1 | task vtable, class +0x150, stage +0x14C |
| `RtsPendingBuildStage` | 0x0049E3E6 | done flag +0x08, owner +0x10, stages 0..4 |
| `GameObject::objectList` | named address | the object vector walked for rigs |

Each group binds once on the patch thread (all or nothing, byte-checked); every engine read and call runs under SEH. Without the core rows or the slot there is no ghost and no power ring; without the nav rows no nav ghosts; without the power rows no power rings; without the two waypoint rows no lines; without the pending rows (or the core rows) no pending build ghosts.

### Not verified

- UNVERIFIED: which per-frame caller runs GetCommand(VECTOR), and whether it runs before or after ConstructionDisplay::Render. The two-tick window covers either order, at the cost of the ghost lingering one frame after the quad.
- UNVERIFIED: the meaning of the flag at 0x02CECF74 (it looks like an alternate render pass guard).
- UNVERIFIED: the default `powerRadius` (100 in older notes).
- UNVERIFIED: record bytes +0x10/+0x14 (never read here).
- UNVERIFIED: multiplayer. Everything is local and reads only the local player's own selection and rigs, but nothing was run in a network game.
- The power ring is flat (2D); the stock test is 3D distance from the plant to the building's sphere centre, so on slopes a spot just inside a ring can still be yellow.
- Animated or skinned building meshes show in bind pose.
- UNVERIFIED: whether anything other than GetCommand moves a rig's drop matrix between the order and FinishBuild. A later reticle hover over the same rig moves it; the pending ghost of that rig is hidden while the cursor ghost shows, and follows the moved matrix afterwards.

### Live checklist (not yet run)

1. Select a Construction Rig, pick a gun tower: the green ghost follows the reticle over open ground, matches the stock square's footprint and faces the same way.
2. Move it away from every power plant: the ghost and square turn yellow together. Onto a cliff or another building: red.
3. Power Range: with the gun tower picked, a yellow ring shows around each allied power plant; an enemy plant has none. Pick a non-powered building (a factory): no rings.
4. Deselect the rig, cancel the pick, or switch to another unit: the ghost and rings vanish the same frame as the square.
5. Pick a Comm Bunker on a rig and open Go To Nav with Build at Nav active: a pale blue ghost at every nav, on the ground, facing your way; power rings show too. Close the menu: they go. Pick a nav: the cursor ghost does not jump to the nav.
6. Pick a building whose mesh does not exist (a mod class with a bad baseName): no ghost, one warning in openshim.log, no repeat.
7. Waypoint Lines: select three units, Go to a far point: three green lines on the ground, following hills. Queue an order with a pending record (Shift-queue, if the mod has it): a dimmer second line from the first destination. Idle units: no line.
8. Hide the HUD (Ctrl+=): ghosts, rings and lines all hide.
9. DX9 and DX11: ghosts are see-through, unlit, unaffected by fog, and hidden behind hills.
10. Turn each option off in Options > Controls > RTS Commands: its visuals go on the next frame; the others stay.
11. Multiplayer: repeat 1-7 and 12 as a client and as the host; nothing appears for other players.
12. Pending Build Ghost: order two rigs to build different buildings far away (one from the reticle, one with Build at Nav): a dim ghost at each spot while they drive. Each goes when its rig starts building. Cancel one order (give it Go): its ghost goes. Kill a rig on its way: its ghost goes.
13. Radar Pings (`[Gameplay] RtsRadarPings` = 1): select a unit and give a Go order on open ground: a green ring grows and fades on the radar at the right bearing. An order beyond radar range: the ring sits on the radar rim. An attack order: red. Pause the game: the ring freezes. Option off: nothing is drawn. Check with Radar Fade on and off (the ring fades with the radar when it fades), and with Radar Size changed.

Producer build badges (name and build percent over busy own producers, `[Gameplay] RtsProducerBadges`, default off) are a HUD overlay, not a ring: see `Docs/PRODUCER_BADGES.md`.

## Known limits

- The cursor point is only refreshed in the views listed above. In other camera views it can be stale. UNVERIFIED.
- Pings for per-unit menu orders (Follow, Get repair, Get reload, Rescue, Recycle) are not drawn; see "Order paths".
- Draw order against terrain and the satellite view are UNVERIFIED in-game.
