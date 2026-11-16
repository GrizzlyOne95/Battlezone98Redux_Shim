# RTS Markers

Ground rings that show RTS-style feedback for the local player. There are two features, and each has its own option:

- **Command pings** (`[Gameplay] RtsCommandPings`, Options > Controls > Command Pings, default on). Each order the local ControlPanel issues draws one short ring:
  - **Go to a point:** a green ring that shrinks onto the point and fades over 0.9 s.
  - **Attack on an object:** a red ring around the target that follows it and fades over 1.0 s.
  - **Any other order on a point or object:** a yellow ring that fades over 0.9 s.
- **Artillery range** (`[Gameplay] RtsArtilleryRange`, Options > Controls > Artillery Range, default on). It draws:
  - a blue max-range ring around every selected own-team howitzer (Howitzer vtables) that carries a gravity-ordnance cannon slot (at most 16 units); never around the piloted vehicle, whose mortar arc the laser sight already draws;
  - a 3 m ring at the aim point, green when at least one of those units can reach it and red when none can.

Both features are local visuals only:

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

## Known limits

- The cursor point is only refreshed in the views listed above. In other camera views it can be stale. UNVERIFIED.
- Pings for per-unit menu orders (Follow, Get repair, Get reload, Rescue, Recycle) are not drawn; see "Order paths".
- Draw order against terrain and the satellite view are UNVERIFIED in-game.
