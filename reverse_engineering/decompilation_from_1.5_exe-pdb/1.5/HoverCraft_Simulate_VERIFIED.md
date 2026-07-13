# HoverCraft::Simulate — full RE verification (2026-06-26)

Ghidra 12.1.2 headless import of **bzone.exe** (1.5 retail) with **bzint.pdb** auto-applied
(PDB Universal analyzer — GUID matched). Typed decompiles in `Tools/bz_work2/out/`.
This note CORRECTS `hovercraft_physics_analysis.md`, which mislabeled several offsets.

## HoverCraftClass param layout (authoritative, from the PDB struct dump)

`HoverCraftClass` field list `0x545F`, class sizeof 952. Params are read in `Simulate`
via the prototype pointer at `proto + offset` (base `velocForward` @ 768 = `0x300`):

| hex   | field          | ODF (avtank) | | hex   | field        | ODF |
|-------|----------------|--------------|-|-------|--------------|-----|
| 0x300 | velocForward   | 20  (×perf)  | | 0x328 | accelDragStop| 4.0 |
| 0x304 | velocReverse   | 15  (×perf)  | | 0x32c | accelDragFull| 1.0 |
| 0x308 | velocStrafe    | 20  (×perf)  | | 0x330 | alphaTrack   | 20  |
| 0x30c | accelThrust    | 20  (×perf)  | | 0x334 | alphaDamp    | 5.0 |
| 0x310 | accelBrake     | 75  (×perf later) | | 0x338 | pitchPitch | 0.25|
| 0x314 | omegaSpin      | 3.5 (×perf)  | | 0x33c | pitchThrust  | 0.1 |
| 0x318 | omegaTurn      | 1.5          | | 0x340 | rollStrafe   | 0.1 |
| 0x31c | alphaSteer     | 5.0 (×perf)  | | 0x344 | rollSteer    | 0.1 |
| 0x320 | accelJump      | 20  (×perf)  | | 0x324 | setAltitude  | 1.0 |

> The old analysis doc claimed `accelDragStop@0x338 / accelDragFull@0x334`. WRONG —
> those offsets are `pitchPitch` / `alphaDamp`. Real drag params are `0x328 / 0x32c`.
> The UE port nonetheless used the correct ODF *values* (read straight from avtank.odf),
> so no numeric error reached the port — only the doc's narrative was off.

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
look-ahead 0.2; analog-throttle-full 0x10000.

## Port assessment (Source/HoverZone/BZTank.cpp)

Nothing crucial missing. All 18 class params present with correct values; all constants
exact; control ramp exact (3.0). Deliberate kinematic simplifications:
1. **Drag**: port adds `-vel·lerp(Stop,Full,|throttle|)` as a force. BZ folds
   accelDragStop/accelDragFull into a *speed*-blended accel **limit** (`local_24`,
   = hi->accelLimit), gated by `(1 - throttle²-strafe²)` and ×thrustRatio. Same intent
   (more drag slow, less fast), different mechanism. Optional refinement, not a bug.
2. **alphaDamp (5.0)** not modeled separately — folded into the FInterpTo attitude +
   alphaSteer omega approach (both inherently damped).
3. turbo is shift-key + boost-meter gated (port design), vs BZ's full-throttle auto-turbo.
