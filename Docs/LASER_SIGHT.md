# Laser Sight

An optional beam from the player vehicle's selected weapon to the first
terrain or object it meets, up to 500 m, modelled on BZCC's laser sight. It is
purely cosmetic and fully shim-owned: no engine object is created, and no
engine state is written. When the selected weapon fires gravity ordnance
(mortars and other grenade launchers), the beam follows the predicted
trajectory arc instead; see "Ballistic arc".

Code: `src/patches/laser_sight.cpp`. Pure logic: `include/laser_sight_policy.h`.
Generated assets: `include/laser_sight_assets.h`, plus
`NativeChunks::LaserBeamMesh` and `LaserBeamSectionMesh`. Tests: `tests/laser_sight_policy_tests.cpp`, and
the beam-mesh block in `tests/native_chunk_mesh_tests.cpp`.

## Switching it on

- `[General] LaserSight = 1` in `openshim.ini`, or **Options > Effects > Laser
  Sight**. The default is off, including when the key is absent. The options
  row uses `ShimSettingApplyGroup::LiveEngineToggle`, so a change applies on
  the next rendered frame with no restart.
- Multiplayer: the beam is forced off while `IsNetGameFlag` (0x00917F7B) is
  set, unless an external owner calls `OpenShimSetLaserSightMode(1)`. If the
  user's option is off, the beam stays off whatever the mode is.
- Vehicles only. No beam is drawn when the player object is a Person (on foot,
  or after ejecting), when nothing is selected, or when the selected slot is
  empty.

## Exports (`plugins/openshim.dll`)

```c
int __cdecl OpenShimSetLaserSightMode(int mode); // returns the mode in effect
int __cdecl OpenShimGetLaserSightMode(void);
```

| mode | meaning |
|------|---------|
| 0 | default: follow `[General] LaserSight`; off in a network game |
| 1 | follow `[General] LaserSight`; also allowed in a network game |

Any other value is rejected and leaves the mode unchanged. The mode is not
saved, and it goes back to 0 whenever the game leaves a mission, so an owner
sets it again each mission (for example in the mission script's `Start`). These exports are modelled on
`OpenShimSetExternalHudOwnership` (`Docs/EXU_HUD_OWNERSHIP.md`). Calls are
thread-safe (interlocked).

## Verified engine facts

The decompile citations below are from the private GOG decompile corpus
(`openshim_re_corpus/bzr_gog_best_effort/ghidrecomp/.../decomps/`). Each was
checked against the shipping GOG exe (sha256 `8d71f56c...3377413`). The
addresses in code come from `scripts/patches.json` rows, never from literals.

1. **Muzzle world pose: VERIFIED.**
   - The pose is `Matrix_Multiply(*(weapon+0x10)+0x20, weapon+0x28)`:
     - `FUN_005d6330-005d6330.c:40` (SniperInterface::Simulate):
       `FUN_0081fe60(local_e8,*(int *)(local_9c + 0x10) + 0x20,local_9c + 0x28)`.
       The disassembly at exe `0x005D647D-0x005D649B` matches: `add eax,0x28;
       push; mov edx,[ecx+0x10]; add edx,0x20; push; lea; call 0x81fe60`.
     - The vehicle fire site `FUN_005dfcb0-005dfcb0.c:77` builds its ordnance
       matrix the same way, as do `FUN_005b2010.c:60`, `FUN_005a6f70.c:49` and
       `FUN_004f2210.c:50`. The beam therefore leaves from the frame the shot
       is spawned from. `include/weapon_convergence.h` records the same list.
   - `weapon+0x28` is refreshed on every tick by Weapon::Control:
     - `FUN_00611610-00611610.c:15-21` copies the 64-byte result of
       `FUN_006116a0` into `weapon+0x28`. In the exe, this is the `add edi,0x28;
       rep movsd` at `0x0061163F-0x0061164F`.
     - `FUN_006116a0` is `obj_rel_parent_matrix(weapon+0x14, ...)` (line 23),
       with the muzzle offset `weapon+0x1C` pushed through it (line 37). The
       matrix is therefore the muzzle frame in world space.
   - Layout: MAT_3D (`include/weapon_convergence.h`) is 64 bytes. The
     right/up/front rows come first as floats, then 4 bytes of padding, then
     the position as three doubles. `Matrix_Multiply` 0x0081FE60 uses the
     row-vector convention (left = child), and
     `WeaponConvergence::Multiply` mirrors it.
   - The same composition already drives
     `weapon_presentation_native.cpp` `CurrentWeaponPose`.

2. **Selected weapon: VERIFIED.**
   - `FUN_005d6330.c:25` `FUN_00417c70()` is GetPlayer:
     `FUN_00417c70-00417c70.c:5` `return DAT_00917afc`; exe `0x00417C73`
     `mov eax,[0x917afc]`. This is the `HudFadeGetPlayer` row.
   - `FUN_005d6330.c:29` `FUN_00417ca0()` is GetCarrier:
     `FUN_00417ca0-00417ca0.c:5` `[this+0x1a0]`; exe `0x00417CAA`. This is the
     `HudFadeGetCarrier` row.
   - `FUN_005d6330.c:34` `FUN_00417f90()` is the selection mask:
     `FUN_00417f90-00417f90.c:5` `[this+0x30]`. This is the
     `HudFadeGetSelected` row.
   - `FUN_005d6330.c:35-37` loops slots 0..4 over the set bits and calls
     `FUN_00417f60(slot)`, which is the `Carrier::GetWeapon` named resolve
     (45-byte pattern in `patches.json`). Exe: `0x005D640A-0x005D6463`.
   - The mask can have several bits set when weapons are linked. v1 draws one
     beam, from the lowest selected slot (`LaserSight::FirstSelectedSlot`).
   - Note: SniperInterface gates its own loop on the player's class (line 28,
     `== 4`, the sniper/person case). The beam does not use that gate. It
     relies on the generic Carrier/Weapon layout, which the vehicle fire
     sites above share.

3. **Render path renders: UNVERIFIED (needs the live test below).**
   - The beam uses the shim-owned entity and node path:
     `CreateShimOwnedMeshObject`, `SetShimOwnedObjectTransform` and
     `HideShimOwnedObject` (`chunk_proxy_render.cpp:2221`). Chunk proxies and
     SkinnedGibs render through it in shipped builds, and ShellCasings uses it
     too. The node hangs off the root scene node, so Ogre's own traversal
     queues it.
   - What is not yet seen live:
     - the generated `openshim_lasersight_beam` material on DX9 (fixed-function
       technique) and DX11 (SM4 technique);
     - the additive look;
     - sim-time muzzle sampling against the rendered hull.
   - The SM4 shader compiles with fxc `vs_4_0`/`ps_4_0`; see "Commands" below.

4. **Ballistic arc inputs: VERIFIED** (decompile lines below; every offset
   and signature is also guarded at bind time by a `LaserArc*` row in
   `scripts/patches.json`, whose expected bytes were read from the shipping
   exe and match exactly once in it).
   - `weapon+0x08` = WeaponClass: `FUN_00611300-00611300.c:22`
     `param_1[2] = param_3` (row `LaserArcWeaponClassField`, exe
     `0x00611321`).
   - `weapon+0x0C` = OrdnanceClass (WeaponClass `+0x30`):
     `FUN_00611300-00611300.c:27` `local_98[3] = *(param_3 + 0x30)` (row
     `LaserArcWeaponOrdnanceField`, exe `0x00611362`).
   - OrdnanceClass `+0x50` = lifeSpan and `+0x54` = shotSpeed:
     `FUN_00586440-00586440.c:165-166` (ODF hashes `0x7C7C544B`,
     `0xCAFE92D0`; rows `LaserArcOrdnanceLifeSpan`/`ShotSpeed`). The class
     signature sits at `+0x0C` (`FUN_00586440.c:51`).
   - Gravity ordnance signatures at OrdnanceClass `+0x0C` (rows
     `LaserArc*Sig`):
     - Grenade `0x4752454E` (`FUN_004e7f60-004e7f60.c:7-8`);
     - SprayBomb `0x53424D42` (`FUN_005dacf0-005dacf0.c:7-8`);
     - BounceBomb `0x42424D42` (`FUN_0047db90-0047db90.c:7-8`);
     - Popper `0x504F5052` (`FUN_005a6b00-005a6b00.c:7-8`).
   - Gravity: Grenade::Simulate 0x004E7D30 does `vy -= dt * 4.9` before and
     after the move (`FUN_004e7d30-004e7d30.c:8-10`; the constant at
     `0x008A2858` is `CD CC 9C 40` = 4.9f; row `LaserArcGrenadeGravity`).
     That is exactly `y(t) = y0 + vy0*t - 4.9*t^2`, g = 9.8 on -Y,
     hard-coded. The unit test integrates the engine's step and checks the
     closed form against it.
   - Launch velocity: Bullet::Init 0x00480340 sets velocity = shotSpeed *
     the ordnance matrix front; no carrier velocity is added
     (`FUN_00480340-00480340.c:19-33`).
   - Fire direction: Cannon::Simulate 0x0048EFE0 builds the shot matrix as
     `R(yaw = r*shotVariance, pitch = r*shotVariance - shotPitch)` composed
     onto the muzzle (`FUN_0048efe0-0048efe0.c:127-150`; the call is at
     lines 133-136). shotVariance is WeaponClass `+0x8C`, shotPitch `+0x90`
     (row `LaserArcCannonShotPitch`, exe `0x0048F4B7`; Cannon ODF load
     `FUN_0048f940.c:22-23`, both default 0 in `FUN_0048f860.c:12-13`).
   - Sign of shotPitch, checked in `FUN_0081ed60`: it builds right
     `(cosA, 0, -sinA)`, up `(sinA sinB, cosB, cosA sinB)`, front
     `(sinA cosB, -sinB, cosA cosB)` from (param_2 = B, param_3 = A), with
     `FUN_008205a0` returning (sin, cos) (`FUN_004178f0` = sinf,
     `FUN_004178b0` = cosf). Cannon passes B = r*var - shotPitch and A =
     r*var (push order at exe `0x0048F485-0x0048F4D5`). With the random
     terms at their mean of zero (`FUN_00822830.c:18-19`), front =
     `(0, sin(shotPitch), cos(shotPitch))` in the muzzle frame: a positive
     shotPitch aims up, `dir = cos(p)*F + sin(p)*U`. The value is used as
     radians as stored. The unit test composes the engine matrix and
     compares.
   - shotPitch applies only when the WeaponClass signature (`+0x0C`) is
     `'MORT'` 0x4D4F5254 (`FUN_0056b320-0056b320.c:7-8`, row
     `LaserArcMortarSig`) or `'CANN'` 0x43414E4E
     (`FUN_0048f860-0048f860.c:6-7`, row `LaserArcCannonSig`); MortarClass
     builds on CannonClass and fires through Cannon::Simulate. Any other
     weapon class fires the arc along the muzzle front (p = 0).
   - The stock `gmortar.odf` (1.5 install, `stock/gmortar.odf`) sets no
     shotPitch, so its arc leaves along the muzzle front; its `grenade.odf`
     has `shotSpeed = 50.0` and `lifeSpan = 1e30`.
   - Termination in the engine: terrain, object, off the map or lifeTimer
     <= 0 (Bullet::Simulate `FUN_00480470-00480470.c:22-64`; lifeTimer
     `ordnance+0x78` = lifeSpan, `FUN_00584fe0.c:140`).

Also used, unchanged from ShellCasings, with no new RE:
- `Terrain::HeightAt`;
- `CollisionGrid::Objects/RangeQuery/RangeNext`;
- `WorldRenderOrigin`;
- GameObject `+0x0F0` render bridge, `+0x094` entity;
- obj76 `+0x14` dead flag `0x200`.

## Ballistic arc

- **When:** the selected weapon's OrdnanceClass signature is Grenade,
  SprayBomb, BounceBomb or Popper (`LaserSight::IsBallisticOrdnance`). Every
  other weapon keeps the straight beam, unchanged.
- **Prediction** (render space, Y up, as the straight beam):
  `P(t) = P0 + v*dir*t + (0, -4.9*t^2, 0)` for `0 <= t <= lifeSpan`, where
  `P0` is the same muzzle point the straight beam uses, `v` is shotSpeed and
  `dir = cos(p)*F + sin(p)*U` from the muzzle front `F` and up `U`, with
  `p` = shotPitch for MORT/CANN weapon classes and 0 otherwise
  (`LaserSight::PitchedFireDirection`, `ArcPoint`).
- **Mean path only:** shotVariance spreads each real shot randomly in yaw
  and pitch around this direction. The arc is the zero-spread path, so
  single shots land around it, not on it.
- **Hit search** (`LaserSight::MarchArc`): ground samples every 8 m of path
  (time steps sized from the current speed, at most 0.5 s), the crossing
  refined by 6 bisections on the parabola itself, as the straight beam
  refines its line. Object boxes are tested against the polyline of those
  samples, span by span (about 50 m of path, at most 16 points per span,
  one collision-grid query per span); the walk stops at the first span with
  a hit. The arc ends at the first ground or object hit, at lifeSpan, after
  500 m of path (the straight beam's length), or where the ground can no
  longer be sampled (off the map; whether `Terrain::HeightAt` fails or
  clamps off the map is UNVERIFIED, in which case lifeSpan or the 500 m
  limit ends the arc).
- **Drawing:** 16 pieces of equal flight time from the muzzle to the end
  point (`LaserSight::kArcSegments`, `ArcSegment`). Piece k uses the
  generated `openshim_lasersight_arcNN.mesh`, section k of 16 of the
  straight beam's taper and texture, so the pieces read as one beam that
  fades from the muzzle to the impact. Same material, so DX11 (SM4) and DX9
  (fixed function) behave exactly as the straight beam. The chord of a
  piece is at most `g*dt^2/8` from the true curve (0.25 m for a 7 s flight).
- **Behaviour changes the arc does not model:**
  - Popper retargets at the apex of its flight, so the arc is only valid up
    to the apex for Popper weapons.
  - BounceBomb bounces on landing; the arc shows the first impact only.
  - SprayBomb, Popper and BounceBomb deriving from Grenade (sharing its
    gravity step) is VERIFIED in the 1.5 source only and UNVERIFIED in the
    GOG build.
  - The netgame ordnance matrix drops roll (1.5 `Ordnance::Init`); the
    effect on the mean path is negligible and the beam is MP-gated anyway.
  - PopperGun has its own Simulate (0x005A6F70); its shotPitch handling is
    UNVERIFIED, so its arc assumes p = 0 unless its class signature is
    MORT/CANN.
  - The engine back-dates the owner matrix by a sub-frame step before
    firing (`FUN_0048efe0.c:92-112`); the arc starts from the current
    muzzle pose, a difference of at most one simulation step.
- **Fallbacks:** if the `LaserArc*` rows do not bind (another exe build), a
  class field reads as invalid, or the arc pieces cannot be created or
  moved, the straight beam is drawn instead.

## Cost (framerate contract)

- **Option off:** a single branch per render-queue call. No engine call, no
  Ogre call, no clock read. The beam is hidden once, on the transition.
- **Gate closed (network game, mode 0):** one byte read more, and the same
  hide on the transition.
- **On, pose unchanged:**
  - Work is keyed on the selected weapon, the raw bytes of both matrices and
    the render origin. The render-queue hook runs several times per frame,
    once per camera/scheme traversal; repeat calls and frames without a
    simulation step skip the ray.
  - They cost three engine getters, two 64-byte copies, two `memcmp` and one
    `GetTickCount`.
  - The ray is refreshed at least every 50 ms, so objects crossing a still
    beam are seen.
- **Recompute:**
  - Terrain: about 63 `Terrain::HeightAt` samples at 8 m steps for a full
    500 m miss, plus 6 bisections in the crossing segment only.
  - Objects:
    - up to 10 collision-grid range queries, one per 50 m segment, only up to
      the terrain hit;
    - the walk stops after the first segment that contains a hit;
    - at most 64 distinct objects tested;
    - each object costs a handle lookup, two pointer reads, five Ogre getters
      (bounds, node, derived position/orientation/scale) and a slab test;
    - no `VirtualQuery` or any other OS call per object (Ogre object vtables
      are checked against the cached OgreMain range).
  - One `SetShimOwnedObjectTransform`: position, orientation, scale and
    visible.
- **Arc recompute** (gravity ordnance only), same bounds as the straight
  beam:
  - Ground: one `Terrain::HeightAt` per 8 m of path, at most 500 m, plus 6
    bisections: about 63 + 6 samples for the longest arc, never more than
    128 (`kMaxArcSamples`).
  - Objects: one grid range query per span of about 50 m of path (about 10
    for 500 m); each object's box is read once per recompute and cached
    (at most 64 objects, the same five Ogre getters as the straight beam),
    then slab-tested against the span's chords (at most 15 per span).
  - Drawing: 16 `SetShimOwnedObjectTransform` calls instead of 1, and 16
    small entities (16 triangles each) drawn instead of one.
  - Expected: roughly 20-60 us per recompute and 16 extra small draw calls
    while the arc shows. UNVERIFIED until a traced live run; the trace line
    adds `arc=... lastArcSamples=... lastArcSpans=...`.
- **No allocation per frame.** The entity and node are created once per
  scene and only moved afterwards. The 16 arc pieces are created the first
  time a gravity weapon is selected in a scene.
- **Expected cost:** a few microseconds per call when the pose is unchanged,
  and roughly 10-40 us per recompute, which happens at simulation rate. That
  is well under 0.1 ms per frame. This estimate is UNVERIFIED until a traced
  live run.
- **Measuring it:** set `[Diagnostics] TraceLaserSight = 1` or
  `OPENSHIM_TRACE_LASER_SIGHT=1`. Every five seconds the log then gets one
  `[LASERSIGHT] calls=... avg=...us max=...us recomputes=... avg=...us
  max=...us lastObjectsTested=... visible=...` line, measured with
  QueryPerformanceCounter. Without the flag, no clock is read.

Known limits:
- A terrain ridge narrower than the 8 m step can be stepped over (this is
  tested and documented in the unit tests).
- Object hits use each entity's bounding box, not its mesh.
- A box that contains the muzzle (a hull the gun is pressed against, a
  building the craft hovers over) is ignored rather than swallowing the beam.
- The muzzle pose is the simulation pose. If the hull is drawn interpolated,
  the beam can trail it by up to one simulation step at speed.

## Generated assets and shader deploy

No installer step and no `renderer\enhanced` deployment are needed. When the
chunk payload resource group is refreshed, before it initialises (the same
seam as ShellCasings, `chunk_payload_resolve.cpp`), the DLL writes these files
into the chunk cache root `<game>\openshim\cache\chunks\`:

| file | content |
|------|---------|
| `lasersight\v1\openshim_lasersight.mesh` | 8-sided open tube, z 0..1, radius 1 at the muzzle and 0.5 at the far end |
| `lasersight\v1\openshim_lasersight_arc00.mesh` .. `arc15.mesh` | the same tube cut into 16 sections of its taper and v range, each still z 0..1 (ballistic arc pieces) |
| `openshim_lasersight_beam.tga` | 64x128 red "cone smoke" streaks, bright at the muzzle and fading along the beam |
| `openshim_lasersight-sm4.hlsl` | `lasersight_vertex` / `lasersight_fragment` (SM4) |
| `openshim_lasersight.material` | programs plus material `openshim_lasersight_beam` |

- **Material techniques:**
  - Technique 0 uses the SM4 programs. DX11 picks it, which matters because
    D3D11 has no fixed pipeline.
  - Technique 1 is fixed function. DX9 cannot use `vs_4_0`, so it falls back
    to this one.
  - Both techniques are additive, `depth_write off`, `depth_check on`,
    unlit, with culling off. The SM4 path also fades the tube's silhouette
    (view-facing term) and fades to black in fog. The fixed-function path
    uses `fog_override true none`.
- **Rewrites:**
  - Files are rewritten only when their bytes differ.
  - Only marked files are rewritten: text assets whose first line starts with
    `// OpenShim LaserSight generated asset`, and TGAs whose image-id field
    starts with `OpenShim laser sight `. Unmarked files belong to the user.
  - The files are written whatever the option says, so switching it on later
    needs no restart.
- **Override:** an asset pack replaces the texture, shader or material by shipping a
  file of the same name at the top of a chunk payload directory. Our marked
  copy then removes itself.
- **Pruning:** `lasersight/v1/` is registered with the chunk-cache pruner
  (`include/native_chunk_prune.h`). Bumping the version makes the old tree
  obsolete.
- **Shader changes:** edit `ShaderSource()` in `include/laser_sight_assets.h`.
  The next game start rewrites the cache copy. Swapping in a rebuilt DLL is
  enough to test it.

## Teardown

| event | call |
|---|---|
| `clearScene`, `destroyAllMovableObjects` | `ForgetLaserSightSceneResources` |
| `destroyAllEntities` (mission end, save load, replay) | `DestroyLaserSightSceneObjects` |
| leaving the simulation | `DeactivateLaserSight` (hides) |
| option off, or gate closed | hide on the next tick |

A scene-manager change forgets the old objects. If the entity cannot be
created, creation is not retried until the scene changes.

## Live test recipe

1. Deploy the rebuilt `plugins\openshim.dll`. The assets generate themselves
   on start.
2. Single player, any vehicle, DX11:
   - Turn **Options > Effects > Laser Sight** on in-game. A thin red beam
     should appear at once from the selected weapon.
   - It should end on terrain or on a craft or building, or fade out at
     about 500 m.
   - Switch weapons (1-5): the beam moves to the new hardpoint. With linked
     weapons, it comes from the lowest slot.
   - Hop out: the beam disappears. Get back in: it returns.
   - Turn the option off: it disappears with no restart.
   - Look for:
     - no grey or white quad (that would mean the FFP technique on DX11);
     - no log spam of "without both vertex and fragment shaders";
     - a soft edge on the beam.
3. Repeat on DX9. Expect the same beam via the fixed-function technique, with
   a slightly harder edge and no fog fade.
4. Ballistic arc (DX11 and DX9), with a mortar (stock `gmortar`) selected:
   - The beam is a red arc from the muzzle, fading along its length, ending
     on the ground or on the first craft or building in its path.
   - Fire: shells land around the arc's end (spread is random; the arc is
     the mean path).
   - Pitch the craft up and down: the arc lengthens and shortens; a cliff or
     building in the way cuts it short.
   - Switch to a straight weapon: the straight beam returns at once.
   - The log shows `[LASERSIGHT] arc rows bound` and `arc pieces created
     count=16`, with no `arc piece creation failed` line.
5. With `TraceLaserSight = 1`, the `[LASERSIGHT]` lines should show
   recomputes in the tens of microseconds and `calls` averaging a few
   microseconds.
6. Multiplayer (same-PC harness): the beam is off with the option on. After
   `OpenShimSetLaserSightMode(1)` from EXU or a test harness, it shows.
7. Mission end, save load and restart: there should be no crash, and the beam
   should come back in the next mission.
