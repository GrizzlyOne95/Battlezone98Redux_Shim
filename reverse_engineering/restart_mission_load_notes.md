# Restart Mission vs Fresh Mission Load

Date: 2026-03-17

## Question

Why does `Pause > Restart Mission` behave differently from launching directly
into a mission or loading a save, with `misn04.lua` apparently missing a large
chunk of initialization after restart?

## Short Answer

`Restart Mission` is not the same native path as a fresh mission launch.

It does eventually converge on the same loading-screen wrapper and final
`FUN_004fc490(..., 0)` game-load call, but it reaches that point with different
pre-state and a different shutdown path:

1. Restart uses run state `6`, not the normal fresh-launch state `5`.
2. The current mission is torn down first.
3. That teardown skips at least one cleanup branch that normal non-restart
   shutdowns execute.
4. The Lua mission loader is sensitive to resumed/save-style state via
   `DAT_009173b7` (`missionSave`) and an internal `started` flag; if those are
   wrong, Lua `Start()` can be skipped.

That combination is consistent with "restart behaves like a partial resume"
instead of a truly fresh mission boot.

## UI / Run-State Chain

### Fresh mission launch

- Mission launch callback:
  - `FUN_0078ee60`
- It explicitly:
  - sets `DAT_00918314 = 0`
  - copies the selected mission filename into `DAT_00915540`
  - sets run state to `5` via `FUN_00434170(5)`
  - opens loading screen type `0x17`

### Restart mission

- Pause menu restart callback:
  - `FUN_00788ef0 -> FUN_00788f40`
- Mission-failed restart callback:
  - `FUN_00791f20 -> FUN_00791f50`
- Both explicitly:
  - set `DAT_00918133 = 1`
  - call `FUN_0078bb00()`
  - request screen type `0x17`
  - set run state to `6` via `FUN_00434170(6)`
  - clear `DAT_00918328`

### Load save

- Save-slot callback:
  - `FUN_0078b130`
- It:
  - requests screen type `0x17`
  - calls `FUN_004fddc0(slot + 1)`
  - `FUN_004fddc0` sets run state `8`

## Main Dispatcher

`FUN_004341c0` is the key bridge after the end-of-game/menu stage:

- Run state `5`:
  - copies `DAT_00915540 -> DAT_00945708`
  - calls `FUN_005d4980(&DAT_00945708)`
- Run state `6`:
  - copies `DAT_00915540 -> DAT_00945708`
  - calls `FUN_005d4980()`
  - then immediately changes state back to `5`
- Run state `8`:
  - extracts mission filename from the save into `DAT_00915540` via
    `FUN_004fdfe0`
  - calls `FUN_005d4980()`
  - then changes state back to `5`

So all three flows converge on the same loading-UI wrapper, but restart enters
it from a different state and after different teardown.

## Loading Wrapper

`FUN_005d4980` is the "loading game UI wrapper".

It:

- calls `FUN_004fc490(&DAT_00945708, 1)` first
  - this is a partial/bookmark-style parse
- enters UI screen `0x17`
- later simulator startup calls `FUN_006170a0`
- `FUN_006170a0` performs the real load with:
  - `FUN_004fc490(&DAT_00945708, 0)`

That means the final file load is shared, but the wrapper depends on globals
already being in the correct state before the real load starts.

## Lua Mission Sensitivity

The Lua mission glue around `FUN_0050a060` / `FUN_0050a970` is a likely failure
point.

Observations:

- `FUN_0050a060` reads load-time state and sets an internal `started` flag.
- `FUN_0050a970` only calls Lua `Start()` when that `started` flag is false.
- The code path is conditioned on `DAT_009173b7`, the global `missionSave`
  flag.

Implication:

- If restart arrives with stale or resume-like values for `missionSave` or
  `started`, Lua `Start()` can be skipped.
- That matches the observed symptom very well for a mission whose setup lives
  mainly in `Start()`.

## Important Teardown Difference

`FUN_00618370` performs large-scale simulation shutdown.

Near the end it has a special branch:

- if run state is **not** `6`, `8`, or `9`, it calls:
  - `FUN_00820fb0()`
  - `FUN_008205e0()`
- for restart (`6`) and load-save (`8`), those two calls are skipped

This is the strongest concrete sign that restart intentionally preserves some
runtime state that a more complete shutdown would reset.

`FUN_008205e0()` rebuilds the `DAT_0094672c` player/config blob and resets a
large set of defaults. That alone may not explain the `misn04.lua` behavior,
but it proves restart is not a clean process-level re-entry.

## Working Hypotheses

### Most likely

Restart leaves enough state alive that the subsequent mission load is treated as
"already started" or partially resumed, causing Lua `Start()` to be skipped.

### Also plausible

Restart-specific teardown skips cleanup that direct launch implicitly gets by
starting from a cold process, leaving singleton/object state alive across the
reload.

## Practical Next Step

If this needs confirmation in the shim, the highest-value instrumentation would
be:

1. Log run-state transitions at `FUN_00434170`.
2. Log `DAT_009173b7`, `DAT_00918314`, `DAT_0091831c`, `DAT_00915540`, and
   `DAT_00945708`:
   - before restart click
   - inside `FUN_004341c0`
   - just before `FUN_006170a0`
   - immediately after `FUN_004fc490(..., 0)`
3. Hook the Lua mission `Start` bridge (`FUN_0050a970`) to confirm whether
   `misn04` restart is skipping `Start()`.

If the restart path is confirmed to skip `Start()`, the most targeted fix is
likely to force the fresh-mission state flags back to the same values that
`FUN_0078ee60` establishes before it enters the loading wrapper.
