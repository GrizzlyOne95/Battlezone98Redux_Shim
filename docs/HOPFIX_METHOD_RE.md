# Hop-Fix Method RE (Workshop 3362534335)

This document captures the current static reverse-engineering results for:

- `reverse_engineering/workshop/3362534335/latest/_bzcp.dll`
- `reverse_engineering/workshop/3362534335/latest/winmm.bin` (renamed DLL)

Scope: pin down the method used to fix multiplayer map-list "hop/jump" behavior.

## Binary IDs

- `_bzcp.dll` SHA256: `9f38122f7ff6093df3bfe17c9177155efdb6e20a9ded41b5648badbb217b16bf`
- `winmm.bin` SHA256: `267ae25a46d0d6e0f6a720dd1b5ec220a489645f2d1ee0f42e73b9b84c9bf83b`

## Loader Chain (winmm.bin -> _bzcp.dll)

`winmm.bin` is a proxy `WINMM.dll` that:

1. Resolves path to `_bzcp.dll` from hardcoded strings:
   - `.\..\..\workshop\content\301650\3362534335\_bzcp.dll`
   - `.\mods\3362534335\_bzcp.dll`
2. Calls `GetProcAddress(module, "patch")`
3. Calls `patch(1)` when resolved

Evidence:

- DllMain entry: `10002E1B` (`winmm_bin.dumpbin.disasm.txt:3320`)
- Path pushes: `10001C4F`, `10001C91`
- Symbol lookup `"patch"`: `10001CB9`

## _bzcp.dll Patch Thread and Gate

The exported `patch` function starts a worker thread at `1000EB30`.

Evidence:

- `patch` export body at `10010280`, thread proc assignment at `100102B9`
- thread routine starts at `1000EB30`

Thread behavior (from disassembly):

1. Check file version field for `0x12D` (301) (`1000ED60`)
2. Poll `ReadProcessMemory` at `0x00868300` for 256-byte signature (`1000EF20`, `1000EF39`)
3. Apply a sequence of 5-byte JMP hooks via helper `10004930`

## Hop-Fix Hook Sites

The hop-fix is three detours:

| BZR site | Trampoline | Return pointer |
|---|---|---|
| `0x79B85F` | `1000CD10` | `0x79B86D` |
| `0x799279` | `1000CD40` | `0x79928C` |
| `0x799377` | `1000CD60` | `0x79937E` |

Evidence:

- hook installation: `1000F438`, `1000F4B5`, `1000F532`
- trampoline entries: `1000CD10`, `1000CD40`, `1000CD60`

Key globals used by hop-fix path:

- `DAT_1002AD84 -> 0x94555C` (map-list object pointer)
- `DAT_1002AD08 -> 0x7CAFA0` (call target used during restore)
- `DAT_1002ADB0 -> 0x7A3130` (repeated movement/update call)
- `DAT_1002AD60 -> 0x7D3360` (state query in map-list helper logic)

## What Each Hook Does

### Hook 1: `1000CD10` (site `0x79B85F`)

Sequence:

1. Replays overwritten prologue semantics.
2. Calls helper `1000CAF0`.
3. Calls original function pointer and jumps back.

`1000CAF0` captures list-selection context:

- reads list structures from `[ecx+0x1C8]` / `[ecx+0x17C]`
- stores index-like state into `DAT_1002A1C8`
- captures map identity text into `DAT_1002A1EC` (via call at `10012330`)

Interpretation:

- this is the "save current selection before rebuild" stage.

### Hook 2: `1000CD40` (site `0x799279`)

Sequence:

1. Loads map-list object via `DAT_1002AD84` (`0x94555C`).
2. Calls helper `1000CB40`.
3. Returns to original flow.

`1000CB40`:

- enumerates rebuilt list entries
- compares against saved map identity data (`DAT_1002A1EC`)
- computes matched index and calls list-select function pointer (`DAT_1002AD08`, i.e. `0x7CAFA0`)
- falls back to index `0` when needed

Interpretation:

- this is the "find same map in new list and restore selection" stage.

### Hook 3: `1000CD60` (site `0x799377`)

Sequence:

1. Replays overwritten `call edx`.
2. Loads frame-local context (`[ebp-0xA4]` path) and calls helper `1000CCA0`.
3. Replays `push 0x930` and returns.

`1000CCA0`:

- uses previously saved index state (`DAT_1002A1C8`)
- computes list span/count from `[...+0x168]`/`[...+0x16C]`
- loops `DAT_1002ADB0` (`0x7A3130`) up to saved index to restore visual position
- clears saved index state to `-1`

Interpretation:

- this is the "restore scroll/list visual position after refresh" stage.

## Pinned Hop-Fix Method

From static evidence, the hop-fix method is:

1. Capture selected map/list position before map-list refresh.
2. Let refresh/rebuild happen.
3. Re-identify and re-select the previously selected map in rebuilt data.
4. Replay list movement/update calls to return UI scroll to prior position.

This is not a simple branch flip; it is a stateful 3-hook restore pipeline.

## Clean-Room Implementation Status

The current shim now ports that method directly instead of using the older
scroll-delta heuristic:

- hook 1 saves the selected entry string and visible row
- hook 2 re-selects by matching rebuilt entry text
- hook 3 replays the native row-step and redraw path

Implementation lives in:

- `src/trampolines.cpp`
- `src/scroll_helper.h`
- `src/patcher.cpp`

## Notes on Confidence

- High confidence for hook locations and call chain (direct disassembly evidence).
- Medium-high confidence for semantic naming of helper internals (inferred from structure access patterns and control flow).
