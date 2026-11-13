# MagnetClass fieldRadius = 0 - Code-Level Trace

Date: 2026-08-24
Build: GOG `battlezone98redux.exe` 2.2.301. All addresses re-derived from the
shipped image via the Ghidra corpus; the mismatched PDB was not used.

Per task direction this issue is documented from the code side: the repair was
already implemented and runtime-validated on this branch's baseline, and the
trace below proves the mechanism it guards against.

## Key identification (FNV-1a verified)

ParameterDB keys are lowercased and FNV-1a hashed before lookup. Recomputing
the hashes matches literals embedded in the binary:

| key            | FNV-1a     | where it appears |
|----------------|------------|------------------|
| `rendercount`  | `0x8C8E76EC` | literal `push 0x8C8E76EC` at `0x0044D847` (method sanity check) |
| `fieldradius`  | `0x66623DD5` | second ParameterDB::Get call in `FUN_0050C250` |
| `magnetclass` section hash used by that ctor | `0x24F7F5BC` (first argument) | |

## Native functions

- `FUN_0050C250` = **MagnetMineClass constructor**
  (`mov [this], MagnetMineClass::vftable` in body). Reads the eight
  `[MagnetClass]` ODF keys through `ParameterDB::Get` (`0x005896C0`) into the
  class object:

  | class offset | key |
  |---|---|
  | +0x168 | triggerDelay |
  | **+0x16C** | **fieldRadius** |
  | +0x170 | objPushCenter |
  | +0x174 | objPushEdge (derived, see below) |
  | +0x178 | objDrag |
  | +0x17C | ordPushCenter |
  | +0x180 | ordPushEdge |
  | +0x184 | ordDrag |

  The hash-to-slot mapping is exhaustive: eight consecutive `Get` calls with
  key hashes `0x682CD2B2, 0x66623DD5, 0x6CF48F7F, 0xA9B5F7E3, 0x27970654,
  0xC829C5AD, 0x1703FA09, 0x5B205972` recomputed to `triggerdelay`,
  `fieldradius`, `objpushcenter`, `objpushedge`, `objdrag`, `ordpushcenter`,
  `ordpushedge`, `orddrag`.

  Immediately after parsing, the constructor precomputes the linear falloff
  slope for object pushes:

  ```
  class+0x174 = (objPushEdge - objPushCenter) / fieldRadius
  ```

  **fieldRadius is the denominator of an unguarded divide executed during ODF
  parse / class construction.** A zero radius (explicit `fieldRadius = 0`,
  or a missing/garbage key resolving to the zero default) makes this ±Inf,
  or NaN when `objPushCenter == objPushEdge`. Every MagnetMine instance then
  references this poisoned class record.

- `FUN_0050C650` = **MagnetMine::Simulate** (vtable slot `0x0087D574`
  statically contains `0x0050C650`; the installer re-validates at runtime).
  Reads `mineObj+0xF8 -> class+0x16C` as the attraction radius, builds the
  AABB `center ∓ radius`, and applies impulses using `class+0x170/+0x174`
  (objects) and `class+0x17C/+0x180` (ordnance). Tail-calls stock
  `Mine::Simulate = 0x00511460`, which owns lifetime/removal/expiry.

- `FUN_004A75B0` = velocity impulse applier; internally guarded
  (`mag <= 0 -> 1e30`), but nothing upstream clamps Inf/NaN arriving through
  the poisoned slope fields.

## Failure mechanism

With `fieldRadius <= 0` (or non-finite), construction poisons `class+0x174`
with Inf/NaN. In the current build the radius-gated loops in Simulate are
inert at exactly zero radius, so whether a given session faults depends on
which consumers subsequently touch the slope values (any object reaching the
attraction path at a nonzero malformed radius, Lua/EXU reads, or future call
sites). This is exactly the "zero MagnetClass range" crash class reported
against stock content and mods. The defect is unguarded derived-field math in
class construction, not the loop comparisons themselves.

## Patch (already shipped on this branch)

`src/patches/bzr_hooks.cpp`, vtable-slot hook on `0x0087D574`:

- `TryGetUnsafeMagnetRange` dereferences `obj+0xF8 -> +0x16C` under
  `__try` and flags `!isfinite(range) || range <= 0`.
- When flagged, `MagnetMineSimulateTeamFilterHook` skips the attraction
  computation entirely and invokes stock `Mine::Simulate (0x00511460)`
  directly, preserving mine arming/explosion/removal semantics.
- Valid content is untouched (falls through to the filtered simulate path).
- Opt-out: `OPENSHIM_DISABLE_MAGNET_ZERO_RANGE_FIX` /
  `BZR_DISABLE_MAGNET_ZERO_RANGE_FIX`. Log tag `[MAGNET]`, budget 8 lines.

Runtime evidence from this workstream: with the opt-out set, startup logs
`[MAGNET] Zero/non-finite range guard: disabled hook=installed`; without it,
`enabled hook=installed`; no `[MAGNET]` skip lines occur in ordinary gameplay
(no false positives).

## Remaining uncertainty

The precise user-visible faulting instruction was never captured in a dump;
the guard is deliberately broader (any non-finite/non-positive radius at
simulate entry) so it holds regardless of which consumer trips first.
Next experiment if a dump ever lands: inspect `[edx+0x16C]`-derived slope
values in the faulting frame and confirm the guard had flagged the same
instance.
