# Laser Sight

An optional beam from the player vehicle's selected weapon to the first
terrain or object it meets, up to 500 m, modelled on BZCC's laser sight. It is
purely cosmetic and fully shim-owned: no engine object is created, and no
engine state is written.

Code: `src/patches/laser_sight.cpp`. Pure logic: `include/laser_sight_policy.h`.
Generated assets: `include/laser_sight_assets.h`, plus
`NativeChunks::LaserBeamMesh`. Tests: `tests/laser_sight_policy_tests.cpp`, and
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

Also used, unchanged from ShellCasings, with no new RE:
- `Terrain::HeightAt`;
- `CollisionGrid::Objects/RangeQuery/RangeNext`;
- `WorldRenderOrigin`;
- GameObject `+0x0F0` render bridge, `+0x094` entity;
- obj76 `+0x14` dead flag `0x200`.

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
- **No allocation per frame.** The entity and node are created once per
  scene and only moved afterwards.
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
- **Override:** an asset pack replaces any of the four files by shipping a
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
4. With `TraceLaserSight = 1`, the `[LASERSIGHT]` lines should show
   recomputes in the tens of microseconds and `calls` averaging a few
   microseconds.
5. Multiplayer (same-PC harness): the beam is off with the option on. After
   `OpenShimSetLaserSightMode(1)` from EXU or a test harness, it shows.
6. Mission end, save load and restart: there should be no crash, and the beam
   should come back in the next mission.
