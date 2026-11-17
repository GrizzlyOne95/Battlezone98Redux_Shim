# Tracked vehicles (`classLabel = "tracked"`)

A modder-facing vehicle class for BZR: a tank that sits on its treads
instead of hovering, in the style of BZ2's `ivatank`. It is driven entirely
by the ODF. There is no openshim.ini option, menu entry or feature flag; an
ODF without `classLabel = "tracked"` is untouched.

Status: phase 1 (contact physics) and phase 2 (tread clips and
`treadSound`) implemented and live-checked; phase 2b (rotating turret,
`turretName`) implemented and live-checked with AI units; phase 3
(multiplayer) implemented, not yet live-tested; see "Verification" below.

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

### Rotating turret

A BZ2/BZCC assault-tank style turret, opt-in per class. The classLabel
stays `tracked` (BZCC uses a separate `assaulttank` label; here the turret
is one more `[TrackedClass]` key, so a tank gains or loses it without
changing class):

```ini
[TrackedClass]
turretName = "AGR11TUR" ; model node that turns; no turret when absent
yawRate = 2.0           ; turret slew rate (rad/s); omegaTurret also read
yawAlpha = 5.0          ; turret slew acceleration (rad/s^2); alphaTurret also read
yawMin = -1.6           ; optional limits, radians relative to the hull,
yawMax = 1.6            ; + = left; none when absent
```

`yawRate`/`yawAlpha`/`yawMin`/`yawMax` are BZCC's AssaultTankClass names
and defaults; the BZ1 TurretTankClass names `omegaTurret`/`alphaTurret`
are read too (the BZCC name wins when both are set). Rate is clamped to
0.05..20, alpha to 0.1..200. Limits are radians, not BZCC-style degrees:
limits outside +-pi or not including 0 are dropped with a `TRACKED` warning.
With limits, an AI that is not moving never turns its hull toward a
target outside them; it waits at the limit.
`turretName` is matched case-insensitively against the model's 8-character
node names.

- **The root is the turret.** The object's own transform (obj76) points
  where the turret points; the hull is a counter-rotated pose of the
  root's direct child nodes. So the camera, reticle and stock weapon aim
  (HoverCraft::UpdateWeaponAim poses each weapon node against the root)
  follow the turret, ordnance leaves along it, and the stock AI's steering
  aims it. This is what the stock BZ1 TurretTank does while deployed.
- **Controls.** Steering (mouse) slews the turret at up to `yawRate`; the
  strafe keys turn the hull (strafe right turns it right) and throttle
  drives it along its own heading. The camera follows the turret. The
  turret's rate is relative to the hull, so it turns with the hull.
- **AI.** No new AI: the stock pilot steers the root (now the turret) at
  its target or waypoint, and its throttle/strafe are read as a move
  intent in the turret frame. The hull turns toward that intent (steer
  2 per radian of error) and drives once it roughly faces it; a reverse
  intent backs up. A unit attacking from where it stands turns only its
  turret; one that closes in turns its hull toward the target as it moves.
- **Model.** Put the turret node anywhere below the root. Every direct
  child of the root is yawed with the hull (all of them, so LOD copies
  follow); keep weapon and gimbal nodes off that level. The turret node is
  re-posed to keep its rest heading relative to the root; a turret that is
  itself a direct child of the root also rides the hull's ring (its
  position turns with the hull). Only the first node matching
  `turretName` is posed, so LOD copies of the turret turn with the hull;
  keep them inside the turret node. Hardpoints
  under the turret fire exactly as on a stock tank; hull-mounted ones
  still aim along the turret (the stock aim is root-relative).
- **Multiplayer.** Only the owner runs the hull rule, so the local player
  flag is right there; other peers show the turret angle the owner sends
  (see "Multiplayer" below).
- **Save/load.** The turret angle is not saved. A loaded game starts with
  the hull under the turret's saved heading.
- **Fails closed.** If `Obj76::SyncNode` does not resolve, or the node is
  missing, unreadable or the root has more than 16 children, the unit runs
  as a plain tracked vehicle; one `TRACKED` line names why.

## Multiplayer

Every peer in a game that uses tracked units must run OpenShim and the
mod that ships the ODF. A stock peer does not know `classLabel =
"tracked"`, so it fails to load the map or silently lacks the unit; this
is deliberate (the label is not mapped onto a stock class). Maps without
tracked units are unaffected.

- **The owner simulates.** On the machine that owns the unit (its pilot's
  machine, or the host for AI) everything above runs unchanged.
- **Replicas dead-reckon.** On the other peers the unit is a remote
  replica (network game and `DistributedObject::IsRemote`). The stock
  `GameObject::Simulate` re-runs the Simulate slot from the last received
  pose in up to five sub-steps each frame. On a replica that slot skips
  the contact model and the hull rule, zeroes accel and alpha (they are
  not replicated), and runs the stock tail, so the unit coasts on the
  replicated velocity and omega until the next update. Tread clips and
  `treadSound` follow that motion: the speed along the hull's front and
  the hull's yaw rate (the replica's yaw rate less the owner's last
  received turret slew rate, 0 when that is more than 2 s old).
- **Turret angle.** The engine does not replicate it. Each peer
  broadcasts the turrets it owns in one OpenShim net message per frame,
  tag `'T','Y'`: a 4-byte header (tag, version 1, u8 record count 1-16)
  and 12-byte records (u32 object id, f32 delta, f32 rate), at most 196
  bytes. A record is keyed by the object's stock DistributedObject id
  (the id a Lua handle crosses the network with). A turret's record goes
  in when its angle moves more than 0.01 rad or its rate more than
  0.05 rad/s, at most five times a second, and at least once a second
  while the turret exists. The frame boundary is found by seeing an
  owned turret's PostSimulate a second time, so a batch leaves one frame
  late at most. A replica carries the
  last received angle forward by its rate (at most 0.25 s) and slews its
  displayed angle toward it at up to twice `yawRate`, once per frame;
  until the first message arrives, and when the last one is more than
  5 s old, it holds its angle (0 at spawn). A record with id 0, a delta
  beyond +-(pi + 0.001) or a non-finite one, or a non-finite rate or one
  above 1.01 times the largest `yawRate` is skipped; a bad header (count
  0 or above 16, or a short message) drops the message. The received
  angles are cleared when the network-game flag drops. A stock peer's
  `Net::Receive` ignores the unknown tag.
- **Fails closed.** Without the `DistributedObjectIsRemote` and
  `IsNetGameFlag` rows every object runs the owner model, as before;
  without `DistributedObject::GetLocalID`, `Net::BroadcastSend` or the
  receive handler, replicas dead-reckon with the turret at delta 0. One
  `TRACKED` line at install names the multiplayer state.

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
is missing, slots 3 and 4 stay plain thunks (slot 16 too, unless the
multiplayer turret sync uses it), one warning names it, and the tracked
physics runs unchanged. A fault inside an Ogre clip call
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
- Boost, jump and strafe inputs are ignored (on a turret tank strafe
  turns the hull).
- Turret tanks: the collision box turns with the root (the turret), not
  the hull, and everything outside this class (radar, AI formation and
  path code, Lua `GetTransform`) sees the turret's heading as the unit's.
  The turret angle is not saved. Root-level LOD copies of the turret (a
  4th name character `2` node directly under the root) follow the hull.
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

Phase 2b (rotating turret), live 2026-11-16, same harness: a tracked
avtank copy with `turretName = "AGR11TUR"`, `yawRate = 1.0`; an enemy
avtank 60 m to the hull's left, held still; a plain tracked copy; AI only
(independence on, then an Attack order, then idle, then Goto), then
SaveGame and reload:

- `turret node AGR11TUR found (parent AGR11BDA, nested ...)` in the fresh
  and the loaded run; the plain tracked copy logs no turret lines.
- Off-heading engagement, independence only: the root (turret) turned from
  0 to -109.0 degrees (target bearing -108.4) while the hull stopped at
  -29.6 degrees with zero hull steer and throttle; the target's health
  fell 3000 -> 1766 over those 3.3 s, so ordnance left along the turret,
  79 degrees off the hull.
- Slew rate: the turret's rate relative to the hull peaked at exactly
  1.000 rad/s (yawRate).
- Idle hold: after the target was removed, delta held at 0.131 rad and
  the root yaw at -115.97 degrees for 5 s.
- Goto: the hull turned toward the move intent and drove.
- Save/load: after reload delta restarted at 0 (hull under the turret's
  saved heading) and the unit drove on; no engine alert, empty crash logs.
- Not checked live: the user's own craft (mouse/strafe controls), yaw
  limits, a turret node directly under the root, hull-mounted weapons.
  Frame captures show the model intact (turret seated on the hull) but
  are too far away to measure the turret angle.

Phase 3 (multiplayer): not yet live-tested. Static only: the decompiled
GameObject::Simulate (0x004DEEC0) calls the Simulate slot for remote
objects in up to five sub-steps after copying true_transform, and the
PostSimulate wrapper (0x004DF370) calls slot 16 once with the frame time
step and no remote test; `tests/tracked_vehicle_net_tests.cpp` covers the
batch packet, the send policy and batching, the received-angle table, the
replica slew and the replica tread speeds.
Live checklist (two OpenShim peers, both with the mod):

1. Install logs `multiplayer: replica dead reckoning on, turret sync on`.
2. A tracked unit driven by the host moves smoothly on the guest and
   vice versa (no hover bob, no jitter at rest); its tread clips and
   sound follow its motion on the other peer.
3. The owner logs `first turret angle queued`; the other peer logs
   `replica turret follows the owner`; the turret on the replica matches
   the owner's within a few degrees while slewing and exactly at rest.
4. An AI turret tank owned by the host engages a target; the guest sees
   the turret turn and the hull hold.
5. A tracked unit that changes owner (its player leaves) keeps its
   turret angle and starts sending. Check the unit's dwLocalID is
   unchanged after the owner change: the `id=0x...` in the new owner's
   `first turret angle queued` line matches the one in the earlier
   `replica turret follows the owner` line.
6. A map without tracked units plays as before; a stock peer joining a
   map with tracked units fails as described under "Multiplayer".

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
