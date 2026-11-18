# Daywrecker fall-on-spawn (`[DayWreckerClass] fallOnSpawn`)

A modder-facing ODF key. A Daywrecker whose object ODF sets it, and which is
created outside the Armory (Lua `BuildObject`, a map object), falls under
gravity from where it was made and detonates where it lands, exactly like an
Armory drop's landing. Without the key, stock behaviour is unchanged: such a
Daywrecker explodes on the tick it is made.

```ini
[DayWreckerClass]
fallOnSpawn = 1   ; default 0 (stock)
```

Single player only. Status: **implemented, live test pending** (checklist
below).

## Lua use

```lua
-- Drop a Daywrecker on a spot from 300 m up.
local h = BuildObject("apdwrck", 1, "drop_nav")  -- object ODF with fallOnSpawn = 1
local p = GetPosition(h)
p.y = p.y + 300
SetPosition(h, p)  -- same script tick: the first Simulate has not run yet
```

The bomb starts with no velocity, so it falls straight down; a spawn at
ground height lands at once and detonates on the next tick, as in stock.

## Why stock explodes it (GOG 2.2.301)

| Step | Evidence |
| --- | --- |
| `DayWrecker::Simulate` (0x004B0460) detonates on its first tick unless the PowerUp state flags (`[obj+0x228]+0x114`) have bit 0x4. With 0x4 set it runs `PowerUp::Simulate` instead. | Released decompile, the `& 4` test at the top of FUN_004b0460. |
| Only the Armory sets 0x4: `ObjectLobber` (0x00582190) builds the object (FUN_004E1190), then `flags \|= 0xC` before calling its Simulate. | FUN_00582190, the `\| 0xc` after the build. |
| With 0x4 set, `PowerUp::Simulate` (0x005A7D70) runs the airborne step (FUN_005A9A50) and clears 0x4 (and 0x1) once the object is at or below the terrain height (FUN_00785730). | FUN_005a7d70, the `& 0xfffffffb` branch. |
| `DayWrecker::Collide` (0x004B0610) also clears 0x4 on contact, after damaging what it hit (ODF damage at class +0x170). Bit 0x8 makes it ignore the launcher (+0x224). | FUN_004b0610. |

So a non-Armory Daywrecker only needs bit 0x4 at birth to behave like a
dropped one.

## Hook

- `DayWreckerBuildCtorCall` (0x004B0D85, call at +0x0B = 0x004B0D90) is the
  only call to `DayWrecker::DayWrecker` (0x004B0420; thiscall, `ret 8`,
  returns `this`) in `.text`, inside the class's object factory
  (0x004B0D40). Every creation path passes there. The call is redirected to
  a `__fastcall` stub (same contract) that calls the stock constructor, then:
  - checks the vtable is `.?AVDayWrecker@@`,
  - reads the class (`obj+0xF8`) and its packed ODF name (class +0x30),
  - reads `[DayWreckerClass] fallOnSpawn` once per class through the engine
    ParameterDB scope (`ParameterDB::OpenScope`, `WeaponPresentation::RawGet`,
    `WeaponPresentation::PopScope`, as `tracked_vehicle_class.cpp` does),
    cached by class pointer plus name,
  - in single player, ORs 0x4 into the flags when neither 0x4 nor 0x20
    (detonated) is set.
- The Armory path ORs 0xC after construction, so an Armory drop of a keyed
  class ends exactly as stock (0xC).
- Rules: `include/daywrecker_spawn_policy.h`; tests:
  `tests/daywrecker_spawn_policy_tests.cpp`.
- Kill switch: `OPENSHIM_DISABLE_DAYWRECKER_FALL_ON_SPAWN=1`.
- Fails closed: a guard-byte mismatch on either row, a missing ODF-scope
  resolve or a failed redirect leaves the call stock, with one log line.

## Limits

- **Multiplayer:** off. A remote replica is built by the same constructor
  (network create path, flags 0); arming it would let a replica fall on its
  own. Whether the owner's flags would replicate correctly is UNVERIFIED.
- **Map objects** of a keyed class also fall at mission start. That is the
  modder's choice with the key. A saved game restores the flags the object
  was saved with; whether load overwrites the constructor's flags is
  UNVERIFIED.
- No initial velocity or drop rate is set. A faster or slower drop is a
  separate item (see `Docs/FEATURE_IDEAS_SCOPING_20261118.md`).

## Live checklist (not yet run)

1. Stock ODF (no key): Lua `BuildObject` of a Daywrecker explodes at once,
   as before.
2. Keyed ODF: `BuildObject` + `SetPosition` 300 m up: it falls, detonates on
   landing, and leaves the stock crater and blast. `openshim.log` shows
   `[DAYWRECKER] <odf>: fallOnSpawn on` once.
3. Keyed ODF, dropped onto a unit: the unit takes the Collide damage, then
   the blast.
4. Keyed ODF from the Armory: the drop flies and lands exactly as stock.
5. Network game with a keyed ODF: Lua spawn explodes at once (stock), and
   Armory drops behave as stock.
6. Save mid-fall and load: no crash; note whether the bomb resumes falling.
