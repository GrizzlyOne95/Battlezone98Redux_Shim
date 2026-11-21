# Daywrecker drop rate (`[DayWreckerClass] dropRate`)

A modder-facing ODF key that speeds up or slows down a Daywrecker's flight
without moving where it lands. `dropRate = 2` makes the bomb arrive in half
the time along the same arc. `dropRate = 0.5` gives the target twice as long.

```ini
[DayWreckerClass]
dropRate = 2.0   ; default 1 (stock); clamped to 0.25..3
```

It applies to every airborne Daywrecker of the class: Armory drops, and
Daywreckers armed by `fallOnSpawn` (`Docs/DAYWRECKER_FALL_ON_SPAWN.md`).
Single player only. Status: **implemented, live test pending** (checklist
below).

## How the Armory throws a Daywrecker (GOG 2.2.301)

| Step | Evidence |
| --- | --- |
| `ObjectLobber` (0x00582190) picks a launch speed `s = sqrt(d * 9.8) + 20` (d = distance to the target), capped by the weapon class's +0x84. | Released decompile of FUN_00582190. |
| The aim solve (0x00581F80) finds the launch velocity for that speed. It solves `k*u^2 - (s^2 - 9.8*dy)*u + 24.01*h^2 = 0` (h^2 = horizontal distance squared, k = d^2/h^2) and takes the smaller root, which is the **high, lofted arc**. Without a real root (speed too low) it uses the vertex. The velocity is `(dx*w, dy*w + 4.9/w, dz*w)` with `w = sqrt(u/h^2)`, so the flight time is `1/w`. | Disassembly of 0x00581F80: constants 9.8, 24.01 (4.9^2), 4.0, 4.9 at 0x008A28A8/0x008A2914/0x008A2828/0x008A2858; `max(0, disc)` via 0x0044FB20; `b - sqrt(disc)`. |
| Each tick `PowerUp::Simulate` (0x005A7D70) resets the acceleration (+0x144) to the gravity vector at 0x00871A80 `(0, -9.8, 0)`. During descent (bit 0x1) it adds drag (`0.1 * vy^2` upwards) and drift terms, then integrates velocity in two half steps around the position step. | Disassembly of 0x005A7D70: the copy from 0x00871A80 at 0x005A7E05; the `0.5 * dt` multiply-adds of +0x144 into +0x12C at 0x005A8E97 and again after the position step. |

So "dropping faster" cannot be done by raising the launch speed: on the high
arc a faster launch goes higher and stays up longer. Changing gravity alone
makes the bomb fall short of the aim point.

## What the key does

`DayWrecker::Simulate` is vtable slot 15 (+0x3C) of the DayWrecker vtable
(0x00878508, RTTI `.?AVDayWrecker@@`). It is the only `.rdata` pointer to
0x004B0460, and it is the slot the lobber calls for the launch tick. A
wrapper on that slot hands the stock Simulate `dt * dropRate` while the
PowerUp airborne bit (0x4) is set. Gravity, drag, drift and the terrain test
all advance by the larger step, so the flight is fast-forwarded: it follows
the same path and lands at the same point (up to step-size error) in
`1 / dropRate` of the time.

- Grounded ticks (bit 0x4 clear; this Simulate is the detonation itself) and
  detonated bombs (0x20) get the stock `dt`.
- The wrapper only reads before the stock call. A detonating tick may free the
  object, and nothing touches it afterwards.
- The ODF is read once per class, through the same ParameterDB scope and
  per-class cache as `fallOnSpawn`.
- Chaining: the MP Armory-collision hold
  (`src/patches/mp_daywrecker_armory_collision.cpp`) replaces the same slot.
  Whichever installs second forwards to the first, in either order:
  `ComVtablePatch::PatchEntry` saves what the slot held. This install accepts
  the slot holding either stock Simulate or a wrapper inside the OpenShim
  module, and fails closed on anything else.
- If the MPAUTH trace (`OPENSHIM_TRACE_MPAUTH`, diagnostic) detoured the
  Simulate entry first, the `DayWreckerSimulate` guard bytes no longer match
  and dropRate stands down for that run.
- Rules: `include/daywrecker_spawn_policy.h` (`ParseDropRate`, `ScaledStep`);
  tests: `tests/daywrecker_spawn_policy_tests.cpp`, which includes a
  gravity-and-drag model at a 10 Hz step: at 2x it lands within 5% of the
  stock point, and at the 3x cap within 10%.
- Kill switch: `OPENSHIM_DISABLE_DAYWRECKER_DROP_RATE=1`.
- Audit: `scripts/audit_vtable_hooks.py` lists the slot. It is the only copy.

## Limits

- **Step size.** At `dropRate = 3` each tick moves the bomb three times as
  far. Landing is a height test against the terrain and cannot be stepped
  over. A hit on a unit (`DayWrecker::Collide`) is coarser, so a fast bomb can
  pass through a small unit in one step and land behind it. That is why the
  value is capped at 3.
- **Multiplayer:** stock. A scaled flight would run ahead of the other
  peers' copies.
- Anything else that reads the bomb's flight time does not see the change.
  For example, whether AI threat timing reads the flight time is UNVERIFIED.
- A slower drop (`< 1`) is the counterplay knob. It gives defenders time but
  does not make AI shoot at the bomb (work queue item 14a).

## Live checklist (not yet run)

1. Stock ODF: Armory drop flies and lands as before; no `dropRate` log line.
2. `dropRate = 2`: an Armory drop at short and at long range lands on the
   aimed spot in about half the time. `openshim.log` shows
   `[DAYWRECKER] <odf>: dropRate 2.00` once.
3. `dropRate = 0.5`: same spot, about twice the time.
4. `dropRate = 3` onto a single tank: note whether it hits the tank or lands
   beside it.
5. `fallOnSpawn = 1` and `dropRate = 2`, Lua spawn 300 m up: falls faster,
   detonates on landing.
6. With the MP Armory-collision hold on (the default) and off
   (`OPENSHIM_DISABLE_MP_DAYWRECKER_ARMORY_COLLISION=1`): the dropRate install
   line is in the log both times, and the drop behaves the same.
7. Network game with a keyed ODF: drops fly at stock speed.
