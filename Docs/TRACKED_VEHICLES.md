# Tracked vehicles (`classLabel = "tracked"`)

A modder-facing vehicle class for BZR: a tank that sits on its treads
instead of hovering, in the style of BZ2's `ivatank`. It is driven entirely
by the ODF. There is no openshim.ini option, menu entry or feature flag; an
ODF without `classLabel = "tracked"` is untouched.

Status: phase 1 (contact physics) and phase 2 (tread clips and
`treadSound`) implemented and live-checked; see "Verification" below.

## ODF

```ini
[GameObjectClass]
classLabel = "tracked"
; geometry, collision box, weapons ... as for any hover tank

[HoverCraftClass]
; the hover drive keys are reused
velocForward = 14.0   ; top tread speed forward (m/s)
velocReverse = 7.0    ; top tread speed in reverse (m/s)
omegaSpin = 2.0       ; turn rate when pivoting at standstill (rad/s)
omegaTurn = 1.0       ; turn rate at full forward speed (rad/s)
accelThrust = 10.0    ; tread acceleration limit (m/s^2)
accelBrake = 30.0     ; tread braking limit (m/s^2)
alphaSteer = 4.0      ; yaw acceleration limit (rad/s^2)

[TrackedClass]
stiffness = 400.0       ; ground spring, m/s^2 per metre (rests g/stiffness deep)
damping = 40.0          ; ground damper, m/s^2 per m/s
contactsPerSide = 3     ; 2..8 contact points per tread
lateralFriction = 1.0   ; sideways grip as a fraction of g (no strafe)
maxSlope = 40.0         ; full traction up to this slope; none 10 degrees past it
treadSound = "xvtrd0.wav" ; looping tread sound (BZCC key name); none when absent
treadCycleLength = 1.0  ; metres of tread travel per loop of a tread clip
```

Every `[TrackedClass]` key is optional; the values above are the defaults
(`treadSound` has none). Out-of-range values are clamped (stiffness
10..5000, damping 0..500, lateralFriction 0..5, maxSlope 5..85,
treadCycleLength 0.05..100). Hover-only keys (`velocStrafe`,
`setAltitude`, `accelJump`, boost) have no effect on a tracked unit.

### Tread clips and sound

Sides follow BZCC: `L` is the driver's left (-x), `R` the right. A tread's
speed is the contact model's commanded speed for that side (m/s, positive
when it drives the hull forward), eased toward its target at accelThrust
while speeding up and accelBrake while slowing. Driving forward both are
positive; a pivot to the left runs L backward and R forward; at rest both
are 0.

- **Clips.** Give the model's skeleton looping animations named `tread_L`
  and `tread_R` (exact case, as in BZCC). Each tracked object advances its
  own Entity's clips by `speed * dt * clipLength / treadCycleLength`
  seconds, so one loop of a clip is `treadCycleLength` metres of tread
  travel and a negative speed plays it backward. Animate bones that the
  engine does not drive itself (wheels, sprockets, tread-link bones; not
  turret, gun or nacelle bones). A missing clip is skipped, so a model
  with neither stays as it is. Other objects sharing the mesh, tracked or
  not, are untouched: the state lives on each Entity.
- **Blend mode.** An entity that has a tread clip has its skeleton
  instance switched to Ogre's `ANIMBLEND_CUMULATIVE`. Under the default
  `ANIMBLEND_AVERAGE`, Skeleton::setAnimationState (OgreMain 0x10443345
  in the shipped DLL) scales every enabled clip by 1/total weight, so
  `tread_L` and `tread_R` would each pose at half strength (measured live:
  0.50). The mode lives in the entity's own SkeletonInstance
  (SkeletonInstance::loadImpl 0x10444C4A copies it from the master), so
  other units using the mesh keep theirs. On craft models the engine
  enables only one clip itself, a looping `idle` if the skeleton has one
  (model loader 0x0067E6A8, GOG decomp); under cumulative it plays at full
  weight next to the tread clips instead of being averaged down. Keep the
  tread clips off bones `idle` animates, or the two add up. Do not key
  bones whose 4th name character is `1` or `2`: the model loader marks
  those for LOD hiding and takes manual control of them.
- **No UV scroll.** The stock vehicle shaders (`base.program`) bind no
  texture matrix, so a material scroll on a "tread" sub-mesh would not
  show, and a shared material would scroll every unit using it.
- **Sound.** `treadSound` loops through the engine's own looping-sound
  path, the one the hover thrust loop uses: the same start block and
  priority (higher for the user's craft), pitch `11025 + 5512.5 * t` Hz
  and volume `5 + 5 * t` (five times that for AI craft), where `t` is the
  faster tread's share of velocForward. It starts above `t = 0.05`; under
  it a playing loop is muted and only stopped after 1.5 s in a row, so an
  AI easing round the gate does not restart it. It is silent when
  the unit is dead, and past 150 m from the camera (the stock hover
  cutoff), and it is stopped when the object is cleaned up or destroyed
  (vtable slots 0, 3 and 4). Names longer than 15 characters are refused.
  A `treadSound` equal to `soundThrust`, `soundTurbo` or `soundFly` is
  refused with a warning: the stock sound code finds its loops by name and
  owner, so a shared name would stop the wrong loop.

The two treads sit at 85% of the ODF collision box half-width, each with
`contactsPerSide` points spread between 10% in from the back and 10% in
from the front. Their height comes from the engine's own ground reference:
the bottom of the object's collision box (obj76+0xB4), the point the
engine's terrain collision (0x004AA1D0) probes, minus a skin of
`2 * g / stiffness` (at least 0.05 m). At rest the spring sinks
`g / stiffness`, so that probe stays just above the floor and the engine
never has to clamp the hull.

## How it works

- `GameObjectClass::Find` compares an ODF's classLabel with each registered
  class through one `_stricmp` call site, which `pond_class_label.cpp` already
  redirects. That hook now also aliases `tracked` onto the registered
  `hover` descriptor, so a tracked ODF is built by the stock HoverCraftClass
  (4CC `HOVR` and rank kept). The class's label pointer is then stamped
  `"tracked"`, and `[TrackedClass]` and the collision box are read once per
  class.
- Each object built from a tracked class gets an OpenShim copy of the
  HoverCraft vtable (`HoverCraftVtable`, 42 slots, RTTI locator kept so it
  still reads as `.?AVHoverCraft@@`). Slot 15 (Simulate) runs the tracked
  model. Slot 16 (PostSimulate) calls the stock slot first, then drives
  the tread clips and sound; slots 0 (deleting destructor), 3 and 4 (the
  two paths that run the stock HoverCraft sound cleanup 0x004EE8F0) stop
  the tread loop and then call the stock slot. Every other slot, including
  UpdateWeaponAim (38), is a `jmp [stock slot]` thunk, so in-place rewrites
  of the stock table (the shot-convergence wrapper) still apply.
- `TrackedSimulate` replaces only the hover force model. It reads throttle
  and steer, samples the floor height and normal at every contact through
  the engine's floor query (`Terrain::FloorQuery`, the call stock hover
  makes, ignoring the craft itself), and computes:
  - a spring/damper shared by the grounded contacts along the footprint
    plane's normal, solved implicitly so it is stable at any step size;
  - forward acceleration toward the commanded tread speed, holding the hull
    against the slope's pull, limited by accelThrust/accelBrake;
  - lateral friction that cancels sideways sliding (no strafe);
  - a yaw rate from differential tread speeds, pivoting at omegaSpin at
    standstill and blending to omegaTurn at full speed; the outer tread is
    held to velocForward/velocReverse and forward speed gives way first;
  - pitch and roll steered toward the footprint plane;
  - traction from the load the ground carries (the contact push over the
    weight along the normal, so a hull resting on one contact of a crowned
    slope still grips), fading out from `maxSlope` to `maxSlope + 10`;
  - while any contact is grounded, no velocity into the ground; in every
    state the fall speed is capped at 60 m/s and the speed at 150 m/s.
  It then repeats the stock HoverCraft::Simulate tail unchanged: the
  half-step integration around vtable slot 39 (0x004A8AB0,
  `__thiscall(this, float dt)`, which moves the posit by veloc * dt and
  resolves collisions), the eyepoint update, the aim pitch, and
  `Craft::Simulate`. The model is in `include/tracked_vehicle_physics.h`
  (no clock, no RNG, fixed iteration order) and is covered by
  `tests/tracked_vehicle_physics_tests.cpp`.
- Damage slows a tracked unit the same way as a hover craft (the drive keys
  are scaled by the health curve HoverCraft::Simulate uses).

Every engine address is a byte-signature resolve in `scripts/patches.json`
(`HoverCraftClass::BuildClass`, `HoverCraftClass::Build`,
`HoverCraft::Simulate`, `HoverCraft::UpdateEyepoint`, the two
`HoverCraft::AimPitch*Gate` helpers, `Craft::Simulate`,
`ParameterDB::OpenScope`, `Terrain::FloorQuery`, plus the existing
`WeaponPresentation::RawGet` and `WeaponPresentation::PopScope`). Installation fails
closed: if any of them does not resolve, if `HoverCraftVtable` is not the
42-slot `.?AVHoverCraft@@` table with `HoverCraft::Simulate` in slot 15, if
either detour cannot be installed, or if the pond compare hook is not in
place, `tracked` stays an unknown classLabel exactly as in stock Redux. A
tracked object whose class data cannot be read falls back to the stock hover
Simulate.

Treads fail closed on their own: they also need `Sound::InitControl`,
`Sound::InitPrep`, `Sound::SetParams`, `Sound::Stop` (new), the existing
`PlayGlobalSound` and `Sound::Find` resolves, the `GetCameraRecord`
engine address, and twelve OgreMain exports (Entity animation-state lookup,
AnimationState length/time/addTime/enabled/loop, Entity::getSkeleton,
Skeleton get/setBlendMode, the Entity vtable). If any
is missing, slots 0, 3, 4 and 16 stay plain thunks, one warning names it,
and the tracked physics runs unchanged. A fault inside an Ogre clip call
or a blend-mode call turns tread clips off for the session (one warning).

The `TRACKED` log component records the install, one line per tracked
class built (its effective keys and footprint), and a bounded Debug trace of
contact clearance, speed, omega, grounded contacts, slope, traction, the
engine box bottom, the floor normal under the origin and the footprint
plane normal for live checks. For treads it logs which clips each object's
Entity has (when that changes), each tread loop start/stop/release, and a
bounded Debug trace of commanded and visual tread speeds, clip time
positions, volume and rate.

## Limits

- Contacts use the engine floor query, which also returns object floors
  (bridges, roofs); only terrain has been checked live.
- No contact torque: pitch and roll follow the footprint plane rather than
  being pushed by individual contacts, so a tank cresting a ridge levels
  smoothly instead of teetering.
- Boost, jump and strafe inputs are ignored.
- The unit is a HoverCraft underneath: AI, weapons, sounds and the HUD
  treat it as one. An ODF that used `classLabel = "wingman"` loses
  Wingman-specific behaviour when switched to `tracked`.
- Tread visuals are skeleton clips only (see "Tread clips and sound");
  there is no texture scroll. Clips follow the commanded tread speed, so
  treads keep turning against an obstacle and are still while the hull is
  pushed.
- Pitch (+omega.x raises the nose) and roll (+omega.z lowers the right side)
  signs follow BZ 1.5's convention (+omega.y turns left). The live run
  shows both converge onto the ground (see Verification); a wrong sign
  would tip the hull away from it.

## Verification

Static, on GOG Redux 2.2.301 (SHA-256 8d71f56c...3377413): every resolve
above is a unique whole-image match; the HoverCraftVtable's only code
references are the constructor and destructor vptr stores (0x004E9723,
0x004E9F1B), so nothing compares an object's vptr with it.

Live, 2026-11-16 (background harness runs, lcbench, test copy of the 1.5
avtank ODF, AI Goto orders):

- Alias, class read, vtable swap and save/load work: `built ODF trktest as
  tracked` in the fresh and the loaded run, tracked Simulate trace after
  load, no engine alert, empty crash logs.
- Flat rest: origin 0.026 m above the floor, contact clearance -0.024 m
  (`-g/stiffness`), 6/6 contacts grounded, traction 1.00, speed 0.00.
- 17.8 degree side slope: after landing the hull slid 2.7 m, then held
  (0.02 m drift over 12 s, speed under 0.5 m/s); ordered 25 m uphill it
  climbed at 3.6-9 m/s.
- Drive: forward reaches 19.96 m/s (velocForward 20); reverse reached
  -3.7 m/s before the AI turned round; turn rate up to 2.0 rad/s.
  Sideways speed stays near 0 driving straight; it reaches 3.8 m/s for
  under a second when the AI turns hard at speed (skid that lateral
  friction removes, not strafe). Highest speed in any state: 19.99 m/s.
- The hull aligns to the ground: parked on the 17.8 degree slope its
  right axis settles at y = -0.28 (16.4 degrees of roll); stopped on an
  8 degree rise its front axis settles at y = 0.133 (7.7 degrees of pitch).
- Not checked live: a pivot at standstill (AI Goto never gives zero
  throttle with full steer; the unit test covers it) and object floors.

Phase 2 (tread clips and sound), live 2026-11-16, same harness: three
tracked copies (one driven, one left idle 15 m away, one killed at T12),
a hover avtank, a fixture `avtank.skeleton` with 1 s `tread_L`/`tread_R`
clips on the nacelle bones, `treadSound = "avwalke0.wav"`,
`treadCycleLength = 2.0`, then SaveGame and reload:

- All tracked objects log `tread clips: tread_L=driven tread_R=driven`,
  in the fresh and the loaded run.
- Clip direction: over the sampled steps where a step is under 0.4 of a
  loop (faster samples alias), the clip time moved with the sign of the
  visual tread speed in 94 of 94 driven-unit samples (37 of them in
  reverse), including the turn-in-place phase (L -3.3..-9.6 m/s, R
  +8.5..+13.3 m/s, clips running opposite ways). At rest the clip time
  did not move (196 rest samples).
- Shared mesh: the idle unit's clip time stayed at 0.000 for all 246
  samples while the others drove at up to 20 m/s.
- Sound: vol 27 at 11455 Hz at 3 m/s, rising to vol 50 at
  16538 Hz at 20 m/s (AI craft); one start and one stop per phase;
  `stopped (dead)` on the kill; restarts after reload.
- No engine alert, empty crash logs, no tread warnings.
- Pose strength (temporary diagnostic build, not in the source): two new
  bones each keyed by its own clip, a full turn per loop; the measured
  bone angle over the authored angle, on samples under 0.5 m/s. Both
  clips with the cumulative switch: L 0.997, R 0.993 (median, n=54/92).
  One clip only: 1.000 (n=126). Both clips with the switch disabled (the
  old behaviour): L 0.506, R 0.498.
- Not exercised live: a tread rig on a real model (the first fixture
  animated nacelle bones, which the model loader controls itself, so the
  frames are not evidence of the look), a destructor or cleanup release while a loop is
  still playing (the loop had always stopped first), the user's own craft,
  the 150 m camera cutoff, and the fail-closed path (no resolve missed).

Bugs found in phase 2: the Entity vptr check used the wrong export
(`??_7Entity@Ogre@@6B@` instead of the ShadowCaster-base vftable), so no
clip bound; the loop restarted every few steps as AI throttle hovered
round the gate (now held, muted, for 1.5 s); the hold was first counted
in steps, about 0.25 s at the observed sim rate; and two clips posed at
half strength under the default blend mode (review finding, now
cumulative).

Phase 1 bugs found on the way: the tail called slot 39 without its `dt`
argument (the callee's `ret 4` corrupted the caller's stack and the posit
was never moved, so the hull stayed at its spawn height while its velocity
grew), and grip scaled by the share of touching contacts let a hull
resting on one contact slide off a crowned slope.

Live checklist (background, never-activate harness run):

1. A test copy of a stock hover tank ODF with `classLabel = "tracked"`
   spawns with no engine alert and logs `built ODF ... as tracked`.
2. It sits on flat ground and on a slope without floating or bobbing
   (trace clearance near `-g/stiffness`, about -0.025 m with defaults).
3. AI Goto drives it forward and back; it pivots in place; it never strafes.
4. Save and reload keep it tracked.
