# HoverCraft::Simulate — full RE verification (2026-06-26)

Ghidra 12.1.2 headless import of **bzone.exe** (1.5 retail) with **bzint.pdb** auto-applied
(PDB Universal analyzer — GUID matched). Typed decompiles in `Tools/bz_work2/out/`.
This note CORRECTS `hovercraft_physics_analysis.md`, which mislabeled several offsets.

## HoverCraftClass param layout (authoritative, from the PDB struct dump)

The imported `HoverCraftClass` field list `0x545F` reports sizeof 952, but that layout conflicts with the
constructor and Simulate use sites because it omitted `coeffDrag`. The reconciled 960-byte conflict layout
below is corroborated by current Redux. Params are read via the prototype pointer at `proto + offset`
(base `velocForward` @ 768 = `0x300` in legacy):

| hex   | field          | ODF/default  | | hex   | field        | ODF/default |
|-------|----------------|--------------|-|-------|--------------|-------------|
| 0x300 | velocForward   | 20  (×perf)  | | 0x328 | accelDragStop| 4.0 |
| 0x304 | velocReverse   | 15  (×perf)  | | 0x32c | accelDragFull| 1.0 |
| 0x308 | velocStrafe    | 20  (×perf)  | | 0x330 | coeffDrag    | 0.01 default |
| 0x30c | accelThrust    | 20  (×perf)  | | 0x334 | alphaTrack   | 20  |
| 0x310 | accelBrake     | 75  (×perf later) | | 0x338 | alphaDamp | 5.0 |
| 0x314 | omegaSpin      | 3.5 (×perf)  | | 0x33c | pitchPitch   | 0.25|
| 0x318 | omegaTurn      | 1.5          | | 0x340 | pitchThrust  | 0.1 |
| 0x31c | alphaSteer     | 5.0 (×perf)  | | 0x344 | rollStrafe   | 0.1 |
| 0x320 | accelJump      | 20  (×perf)  | | 0x348 | rollSteer    | 0.1 |
| 0x324 | setAltitude    | 1.0          | |       |              |     |

> The old analysis doc claimed `accelDragStop@0x338 / accelDragFull@0x334`. WRONG —
> real coast-limit params are `0x328 / 0x32c`. A later audit also found that the first VERIFIED table
> had itself skipped `coeffDrag@0x330`, shifting every later name four bytes early. The 960-byte conflict
> layout, current Redux constructor, and exact Simulate use sites resolve the corrected table above.
> HoverZone originally lacked `coeffDrag`; the 2026-07-18 audit added its stock `0.01` default and use site.

## Control inputs (triple-confirmed: Simulate reads, ControlSpeed/Forward writes, UserProcess ramp)

| offset | field    | offset | field   |
|--------|----------|--------|---------|
| 0xc4   | steer    | 0xd4   | turbo   |
| 0xc8   | pitch    | 0xd8   | jump    |
| 0xcc   | strafe   | 0xdc   | eject   |
| 0xd0   | throttle | 0xe0   | deploy  |
|        | (braccel)| 0xe4   | abandon |

`turbo = (throttle == 0x10000) | turboKey` — full analog throttle auto-engages turbo.

## Control ramp (UserProcess::Execute, typed) — exact rates

`field += (target - field) * dt * rate`:
- **throttle (0xd0) & strafe (0xcc): rate 3.0** — always (analog AND keyboard). `0x40400000`.
- steer (0xc4) & pitch (0xc8): analog/mouse **5.0** (`0x40A00000`), keyboard **1.0** (no mult).
- analog axis normalized by `1/65536` (`0x37800000`).
- **No `last_*` previous-frame fields** — the control field is the ramped state itself.

## Hardcoded constants (all verified exact)

gravity 9.8 (`0x411ccccd`); LIFT_SPRING 19.6 = 2g; hover Kd −4.9 = −0.5g; thrustRatio
falloff `0.9/((h-1)²·0.25+1)+0.1`; ground-brake 12.0→2.0 (×100 ramp in the 0..0.1 band);
analog-throttle-full 0x10000.

### Look-ahead correction (2026-07-18, Redux-corrobated)

The earlier `look-ahead 0.2` statement was wrong. The legacy expression at raw-decompile lines
252–303 is `position + velocity * (collisionRadius / speedMagnitude + 0.5)`. Current Redux independently
confirms the field meanings: `+0x11c = |velocity|`, `+0x120 = 1/|velocity|`, `+0x12c..+0x134 = velocity`.
Therefore the exact probe is:

`lookPosition = position + velocity * 0.5s + normalize(velocity) * collisionRadius`

It is gated on total speed greater than `0.0001`, and consequently leads in every motion direction,
including reverse and strafe. Evidence: Redux raw `FUN_004ebfd0` lines 941–977 and `FUN_0046fb20`
lines 15–39. Do not use the stale 0.2-second or forward-only interpretation.

## Port assessment (updated 2026-07-18)

There are 19 movement class parameters. Released Redux applies both the speed-blended coast acceleration
limit and global quadratic `accel += -coeffDrag * |velocity| * velocity`, with stock `coeffDrag=0.01`.
The current HoverZone audit ports both mechanisms, along with total-speed/performance coast blending,
turn-carve injection, hull-up jump, damage performance, and the 0.5-second/radius look-ahead.

The remaining major kinematic simplification is pitch/roll attitude: HoverZone uses a terrain-target Euler
spring/damper plus the exact control angular-acceleration injections, whereas Redux tracks orientation with
vector/matrix angular dynamics. Turbo remains Shift + finite boost-meter gated by design; full raw analog
throttle auto-turbo is not reproduced.
