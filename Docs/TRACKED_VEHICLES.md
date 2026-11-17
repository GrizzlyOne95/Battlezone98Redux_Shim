# Tracked vehicles (`classLabel = "tracked"`)

A modder-facing vehicle class for BZR: a tank that sits on its treads
instead of hovering, in the style of BZ2's `ivatank`. It is driven entirely
by the ODF. There is no openshim.ini option, menu entry or feature flag; an
ODF without `classLabel = "tracked"` is untouched.

Phase 1 status: implemented, runtime qualification pending (see
"Verification" below).

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
```

Every `[TrackedClass]` key is optional; the values above are the defaults.
Out-of-range values are clamped (stiffness 10..5000, damping 0..500,
lateralFriction 0..5, maxSlope 5..85). Hover-only keys (`velocStrafe`,
`setAltitude`, `accelJump`, boost) have no effect on a tracked unit.

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
  model; every other slot, including PostSimulate (16) and UpdateWeaponAim
  (38), is a `jmp [stock slot]` thunk, so in-place rewrites of the stock
  table (the shot-convergence wrapper) still apply.
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

The `TRACKED` log component records the install, one line per tracked
class built (its effective keys and footprint), and a bounded Debug trace of
contact clearance, speed, omega, grounded contacts, slope, traction, the
engine box bottom, the floor normal under the origin and the footprint
plane normal for live checks.

## Limits (phase 1)

- Contacts use the engine floor query, which also returns object floors
  (bridges, roofs); only terrain has been checked live.
- No contact torque: pitch and roll follow the footprint plane rather than
  being pushed by individual contacts, so a tank cresting a ridge levels
  smoothly instead of teetering.
- Boost, jump and strafe inputs are ignored.
- The unit is a HoverCraft underneath: AI, weapons, sounds and the HUD
  treat it as one. An ODF that used `classLabel = "wingman"` loses
  Wingman-specific behaviour when switched to `tracked`.
- Tread visuals (animated treads or wheels) are not driven yet.
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

Two bugs found on the way: the tail called slot 39 without its `dt`
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
