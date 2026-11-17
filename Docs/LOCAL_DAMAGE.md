# Localized Damage Scorch

Weapon hits on craft leave a mark where they landed: a blotchy charred patch,
darkened to about a tenth and desaturated at the core, a ragged brown ring at
its edge, and orange-red embers that flicker and cool over a few seconds.
Bigger hits (more health lost) leave bigger marks. No assets: the look is
procedural in the Enhanced object shader. Render only: no gameplay, sim,
network or save state is written.

Code: `src/patches/local_damage.cpp` (capture and per-frame writes),
`include/local_damage_policy.h` (pure math), shader
`ose_local_scorch` in `resources/renderer/enhanced/openshim_surface_reactions.hlsl`.
Tests: `tests/local_damage_policy_tests.cpp`. Shared Entity walk:
`src/patches/ogre_entity_liveness.cpp` (moved out of GPU skinning).

## Switching it on

In game: Options > OpenShim > Video > **Hull Scorch** (On/Off). It applies
live: Off stops capture and clears the marks already on the hulls; On starts
marking at the next hit. It still only draws on DX11 with the Enhanced
profile. The row writes `HullScorch`, replacing an older `Enabled` line in
place (`Enabled` is also AutoSave's key, and menu rows need unique keys; both
spellings are read, `HullScorch` first).

Or `openshim.ini`:

```ini
[LocalDamage]
Enabled = 0          ; 1 to switch on (default off)
MaxMarksPerUnit = 8  ; 1..8; the oldest mark is replaced
EmberSeconds = 6     ; 0.5..60; time for a fresh mark's embers to cool
```

The setting is read at start-up, at every mission start and when the menu row
changes. Allowed in multiplayer. `MaxMarksPerUnit` and `EmberSeconds` have no
menu row; they are read at start-up, at mission start and whenever a live
options row changes.

## Behaviour

- Mark radius: `lerp(0.9, 2.4, saturate(lost * 5))` metres, `lost` = health
  ratio lost to that hit.
- Up to eight marks per unit in a ring. A hit within half an existing mark's
  radius merges into it instead: it grows by 1.1x (capped at 2.4 m) and is
  reheated, so sustained fire on one spot does not use up the ring.
- At most 256 units carry marks; further hits are dropped (counted in the
  mission summary log line).
- Embers cool linearly from full to nothing over `EmberSeconds`; the char
  stays. Frame gaps longer than 0.25 s count as 0.25 s.
- Repair: when a unit's health ratio rises back above 0.9 its marks clear.
- A unit's marks go when it dies or leaves the world, and all state goes at
  mission end.

## Limits

- Direct3D 11, Enhanced render profile only. Stock, Retro and DX9 are
  untouched (the uniforms exist only under `ENHANCED_MODE`).
- Only materials using the OpenShim Enhanced object programs
  (`openshim_enhanced_base.program`) show marks. Mod-supplied programs (for
  example ISDF Chronicles materials, or Campaign Reimagined's own shaders)
  do not bind custom parameters 1400..1410 and show nothing.
- Marks live in the root Entity's space (its parent SceneNode). Parts that
  move relative to the hull, such as turrets on their own node, render the
  mark in hull space, so it can slide across them as they turn.
- Only bullets (`Ordnance::Hit`) and explosion splash are marked. Collisions,
  scripted damage and other DamageAlloc callers are ignored. Buildings,
  pilots and powerups are not marked.
- Each player sees the hits their own game applied; nothing is sent over the
  network.
- A mark is a cylinder of its radius from the node centre out through the
  hit point, ending one radius past it, not a sphere around the hit point.
  Hits on a strongly concave part can mark the face nearer the centre too.
  Why (live, 2026-11-16): the sim reports a hit on its collision box, not
  the mesh. On svtank00 bullets struck the side at local x = -3.6 m (the
  same x for points 1.6 m apart along the hull, so a box face, not a sphere),
  while the visible side is nearer the centre; the mesh AABB is no help (it
  is padded to +-8.7 m, bounding radius 13.8 m). With a sphere test no
  surface pixel fell inside any mark although the shader received the marks
  and the key matched (diagnostic colour shader: the tank keyed green, no
  pixel inside a mark).
- Hit points further out than 0.6 x the Entity's bounding radius (3 m when
  unknown) are first pulled onto that sphere along the impact direction
  (splash centres in the air).
- GPU instancing (`[Experimental] GpuInstancing`): an instanced group takes
  the leader's parameters, so marks can show on the wrong instances.
- GPU skinning: the fragment shader's `inverse_worldview_matrix` is bone 0's
  under hardware skinning. If bone 0 is not at the node's pose, both the mark
  positions and the key test are off, and marks on that craft do not show.
- The key is the main view camera (the window's first viewport). Other
  viewports or render-to-texture cameras fail the key test and show no marks.
- Medium and Low Enhanced blocks do not bind `surfaceRainTime`, so embers
  there glow without flicker.
- The DXBC seed pack predates these uniforms: the changed programs miss it and
  compile at run time once.

## How it works

1. Capture (sim thread). `hud_feedback.cpp` already detours the craft
   DamageAlloc entry (`HudFeedbackCraftDamage`, 0x004AA630) with an inline
   JMP, so `_ReturnAddress()` inside `DamageHook<1>` is the engine caller's
   return address. `LocalDamage::BeforeCraftDamage` keeps the call only when
   that is the bullet or splash call site, copies the hit point, direction
   and health ratio, and `AfterCraftDamage` pushes `{handle, point, direction,
   radius}` into a fixed 128-entry ring under an SRW lock when health fell.
   No heap and no Ogre calls on this side. HudFeedback installs the adapters
   whenever `[LocalDamage] Enabled = 1`, even with its own features off.
2. Render (frame listener, `frameStarted`). Starts at the first world render
   of a mission (the same gate and teardown wait as GPU skinning). Returns at once
   while no unit has a mark and no hit is queued. Otherwise it drains the
   ring and resolves only the units that carry marks plus the objects of the
   frame's hits, each to its root Entity (bridge roots, RTTI check every
   frame; the SceneManager name proof when the Entity is new and every 15th
   frame). A unit whose handle no longer maps to its object is released. It
   converts each hit sim world -> render world (`x - ox, y - oy, -z - oz`)
   -> the Entity's parent node space (EXU `SurfacePointMath::ToLocal` port),
   places it on the hull sphere, and updates the unit's ring. Nothing walks
   the GameObject arena, so the cost scales with marked units, not the
   scene.
3. Write. `Renderable::setCustomParameter` on every SubEntity: indices
   1400..1407 = `osMark0..7` (local xyz, radius), 1408..1409 =
   `osMarkHeat0..1` (heat of marks 0-3, 4-7). Written only when a unit's
   marks changed, are still warm, or its Entity or sub-entities changed. A
   repaired unit (every mark cleared) gets its zeros written and is dropped.
4. Stale values. A Renderable that never set a custom parameter leaves the
   shared pass constant as the last Renderable wrote it. Two defences:
   - Key (index 1410, `osMarkKey`): for every unit with a mark, the main view
     camera's position in that Entity's local space (w = 1), written from the
     world render-queue hook after the frame's node and camera updates. The
     shader recomputes the camera from `surfaceViewToLocal` and applies marks
     only when it lies within `max(0.05, 0.002 * |key|)` local units of the
     key. Each object sees the camera at a different local position, so
     values carried over to debris, child Entities or anything else the walk
     never reaches, or left behind after mission end or a Disable, fail the
     test. The 0.2% tolerance is about 3 m at 1.5 km, far above float error.
   - No zero-on-first-sight walk. An earlier build zeroed every Entity in
     the arena once marks existed; the key makes that redundant. A
     Renderable that never set 1400..1410 inherits the values of the last
     draw of the same pass, and with them that object's key. The key matches
     only where the camera sits at the same local position relative to that
     other Entity's node, so the inherited marks show only on geometry at
     the same pose as the marked Entity: in practice its own Entities on the
     same node, where the marks belong anyway. An inherited zero key (w = 0)
     never matches. Marked Entities are still zeroed (each proven live) when
     their unit is released, at mission end and on Disable.
   Mark radii are kept in metres and divided by the node's largest scale on
   the way out; the bounding radius is already in mesh units.
5. Shader. `ose_local_scorch` runs after `ose_surface_finish` in
   `base_fragment`, returns at once when every radius is zero or the key is
   unset or does not match, and otherwise reconstructs the local position with
   `surfaceViewToLocal`.
6. Gate. `LocalDamage::WantsDamage()` is true only with `Enabled = 1` and the
   DX11 Enhanced gate passing, so DX9, Redux and Retro sessions install no
   damage adapters for this feature. The frame listener is added to the Root
   singleton the tick sees; a different (recreated) Root gets it again.

## Reverse engineering

Decompile corpus: `Battlezone_Source/BZ1/Redux/openshim_re_corpus/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/`.
Bytes checked in the shipping GOG 2.2.301 exe; rows in `scripts/patches.json`.

| Fact | Source |
| --- | --- |
| Bullet damage call: `(**(code **)(param_2[6] + 0x38))(local_8c + 0x60, *(int *)(local_8c + 0x14) + 0x38)`: DAMAGE at ordnance+0x60, third argument = ordnance OBJ76 + 0x38 | `FUN_00480750-00480750.c` line 46 |
| Bytes `8B 50 18 8B 42 38 FF D0` at 0x0048085F, `call eax` at 0x00480865, return 0x00480867 | shipping exe; row `LocalDamageBulletHitCall` |
| Splash damage call: DAMAGE built in `local_fc..local_f0` from `local_9c + 0x1c..0x28` (`local_9c = param_1`, the explosion, line 83), damage scaled by falloff, then `(**(code **)(*(int *)(local_a4 + 0x18) + 0x38))()` | `FUN_004c9ab0-004c9ab0.c` lines 83, 146-150, 154 |
| Bytes `8B 42 18 8B 50 38 FF D2` at 0x004CA0B4, `call edx` at 0x004CA0BA, return 0x004CA0BC | shipping exe; row `LocalDamageSplashCall` |
| Craft DamageAlloc: this = complete + 0x18, two stack args, RET 8 | row `HudFeedbackCraftDamage` |
| Health ratio at complete + 0x200 | `kill_ticker.cpp` `kHealthRatioOffset` (GameObject::Save "healthRatio") |

UNVERIFIED (not cited to a decompile line; taken from the design brief and
to be checked by the Phase 0 live probe):

- OBJ76 +0x38 front, +0x48/+0x50/+0x58 world position doubles (the bullet
  hit point is read at third argument + 0x10).
- DAMAGE +4 is the source OBJ76 for both callers, and for splash it is the
  explosion's own OBJ76, whose +0x48 is the blast centre.
- The splash call's third argument points at the explosion-to-target world
  vector (Ghidra dropped the call's arguments at lines 150 and 154).
- No other caller returns to 0x00480867 or 0x004CA0BC.

## Open questions for the Phase 0 live probe

- Log `BeforeCraftDamage` point and target position for a few bullet and
  splash hits: is the bullet point within a few metres of the target, and is
  the splash point the blast centre?
- Do marks sit on the side that was hit (Z mirror and quaternion order)?
- Any mark visible on gibs, cockpit or other entities nobody hit? Do marks
  flicker off on fast craft (key written too early for the draw)?
- Do marks show on GPU-skinned craft (bone 0 versus node space)?
- Cost once marks exist (now per marked unit, no arena walk), with GPU
  skinning on and off.
