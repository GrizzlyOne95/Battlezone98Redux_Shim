# Stock bug: Lua `Formation(unit, leader, priority)` reads the leader as an integer

Date: 2026-10-14. Branch: `agent/fix-lua-formation-binding`.
Evidence: static analysis of the exact GOG image plus a live failure in the Campaign Reimagined co-op harness (misn11), where the Lua error then closed the host.

**Status: patch implemented and unit-tested; live validation pending (see the end).**

## Symptom

`Formation(unit, leader)` from Lua raises `bad argument #2 to 'Formation' (number expected, got userdata)`. `Formation(unit)` does not raise but forms the unit up on handle `1`. The priority is never read. Campaign Reimagined works around it with `SetCommand(unit, AiCommand.FORMATION, priority, leader)` (CR PR #198).

## Mechanism (GOG Redux 2.2.301, SHA-256 `8d71f56c...3377413`)

| Address | What it is |
| --- | --- |
| `0x00872370` | Lua registration row `{ "Formation" (0x0087CF64), 0x005079B0 }`, in `.rdata`. Neighbours: `{ "Recycle", 0x00507970 }` at `0x00872368` and `{ 0x0087D02C, 0x00507A00 }` at `0x00872378`. |
| `0x005079B0` | The `Formation` binding. A byte-for-byte copy of the `Recycle` binding at `0x00507970`: handle from argument 1 (`0x004FF750`), `luaL_optinteger(L, 2, 1)` (`0x0082C1FD`), then a call. |
| `0x005CE680` | Native `Formation(Handle me, Handle him, int priority)`: builds an AiCommand with code 6 (FORMATION), who = argument 2, priority = argument 3, issues it through `0x004DBAF0`. |

The stock binding pushes `(me, optinteger(L, 2, 1), 1)` for the native call. Recycle's native takes `(me, priority)`, so the copy was right there and wrong for Formation: argument 2 must be a handle and argument 3 the priority. `luaL_optinteger` on a userdata raises, which is the reported error; on an absent argument it returns the default `1`, so `Formation(unit)` forms on handle `1`.

## The fix

`[Fixes] LuaFormationBinding` swaps the function pointer at `0x00872374` (the second dword of the registration row) for an OpenShim `lua_CFunction`. No code byte is patched, the stock binding stays intact, and the Lua registration walk (which runs at Lua state creation, after the shim loads) simply registers the repaired function.

Repaired behaviour, `Formation(me, him, priority?)`:

1. `me` = `0x004FF750(L, 1)`, as stock (a bad first argument raises exactly as before).
2. Argument 2:
   * userdata (the `BZHandle`), or any other non-number, non-nil type: `him` = `0x004FF750(L, 2)`. A value that is not a handle raises the engine's normal checkudata error, a clean Lua error.
   * absent, nil or a number: the **stock reading is kept**, `him` = `luaL_optinteger(L, 2, 1)`. Rationale: the safer choice is not to turn a script that ran into one that raises. An integer is the only thing the stock binding ever accepted, and `Formation(unit)` (forming on handle `1`) was a harmless no-op target, not something worth a new Lua error in a mission script. Only the previously impossible case, a handle in argument 2, changes meaning.
3. `priority` = `luaL_optinteger(L, 3, 1)`. Stock hard-coded `1`, so every script that omitted argument 3 is unchanged; a script that passed one now has it honoured.
4. Calls `0x005CE680(me, him, priority)` and returns `0` results.

The decision logic lives in `include/lua_formation_fix.h` (engine-free); the installer is `src/patches/lua_formation_fix.cpp`.

## Fail-closed binding

* Every engine function is a byte-guarded `engine_addresses` row in `scripts/patches.json`: `LuaFormationBinding` (the stock binding, whole function), `LuaGetHandle`, `LuaType`, `LuaOptInteger`, `GameFormation`. A mismatch (Steam build, other GOG build) leaves the stock binding.
* The registration row is `LuaFormationRegistration` (data). At patch time the installer reads it and requires the name pointer to be `0x0087CF64`, that string to read `Formation`, and the function pointer to equal the byte-guarded stock binding. Any miss leaves the row alone.
* Logs use the `[LUAFORMATION]` tag: one `installed:` line with all addresses, `Formation called` for the first twelve calls (with argument 2's Lua type), and a warning naming the failed check otherwise.
* GOG-addressed only; other builds fail the byte guards.

## Switch

`[Fixes] LuaFormationBinding` (default 1). Legacy env alias to force it off: `OPENSHIM_DISABLE_LUA_FORMATION_FIX` / `BZR_DISABLE_LUA_FORMATION_FIX`. It is not simulation-affecting beyond making the documented call work, so it does not stand down in network games.

## Tests

* `tests/lua_formation_fix_tests.cpp` (CTest `lua_formation_fix_tests`): type classification, the leader handle reaching native `Formation` unchanged, argument 2 never read as an integer, priority default and override, and the stock reading kept for absent, nil and numeric argument 2.
* `scripts/run_ini_tests.ps1` covers the ini key; `tests/patch_registration_tests.cpp` and the resolve-table tests parse `patches.json`.

## Live validation still needed

Run the misn11 co-op harness (or any mission) with a script calling `Formation(unit, leader)` and confirm the unit forms on the leader and `[LUAFORMATION] installed:` appears in the session log.
