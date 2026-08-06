# BZCP Patch Atlas Notes

This note summarizes the current `_bzcp.dll` patch payload reconstruction for:

- `reverse_engineering/workshop/3362534335/latest/_bzcp.dll`
- `reverse_engineering/workshop/3362534335/latest/winmm.bin`
- `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe`

The reproducible workflow lives in:

- `scripts/build_bzcp_patch_atlas.py`

Generated outputs are stored at:

- `reverse_engineering/workshop/3362534335/bzcp_patch_atlas.md`
- `reverse_engineering/workshop/3362534335/bzcp_patch_atlas.json`

## What `_bzcp.dll` actually does

The worker thread in `_bzcp.dll` applies 36 writes to the game:

- 29 `jmp5` detours into `_bzcp.dll`
- 2 `rel32` rewrites of existing call operands
- 4 `u32` immediate or pointer rewrites
- 1 `u8` branch flip

By subsystem, the patch surface is:

- 22 map UI / filter / hop-fix patches
- 6 lobby / network / command patches
- 4 vehicle list / mod asset patches
- 3 version / CLI constant patches
- 1 Ogre resource loader hook

This confirms that the original closed-source shim is much broader than the hop-fix alone.

## High-value confirmed sites

The atlas now pins each original `_bzcp.dll` patch to the containing GOG instruction and function.
Examples:

- hop-fix detours
  - `0x0079B85F` in `FUN_0079b850`
  - `0x00799279` in `FUN_00796880`
  - `0x00799377` in `FUN_00796880`

- real version notice rewrites
  - `0x0078DD4E`
  - `0x00618C2F`
  - both replace the pushed string pointer with `_bzcp.dll`'s `2.2.301CP (Community Patch 0.2)` string

- real `/help` hook site
  - `0x0062480B`
  - inside `FUN_006247A0`, the slash-command handler
  - `_bzcp.dll` detour `0x1000D770 -> 0x1000D480` intercepts `/help` and `/ban`

- real vehicle branch flip
  - `0x007AA5A1`
  - inside `FUN_007AA560`
  - `_bzcp.dll` changes `JNZ` to `JMP`

- ban-button UI hooks
  - `0x00743C05` and `0x0073E71C`
  - the related `_bzcp.dll` helpers at `0x1000DF80` and `0x1000E1F0` construct `Ban User`
    UI elements and `Lobby` labels for host/client flows

## Implication for the clean-room shim

The clean-room shim is now corrected on three points exposed by the atlas:

- it no longer mislabels `0x0062480B` as a version notice site
- it now patches the real version string operands at `0x0078DD4E` and `0x00618C2F`
- it now names `0x007AA5A1` as the original vehicle-control branch fix

It also now matches the core hop-fix method more closely:

- hook 1 saves the selected entry text plus the visible row index
- hook 2 reselects by rebuilt-entry string match instead of replaying the old call blindly
- hook 3 replays the native map-list row-step and redraw path instead of using a synthetic scroll delta heuristic

The remaining deliberate gap is the command intercept at `0x0062480B`: the original `_bzcp.dll`
adds custom `/help` and `/ban` behavior there, but that detour is still intentionally unported.

The clean-room shim is still correctly aligned on the three hop-fix detours, but it models only a
small subset of the original `_bzcp.dll` patch surface.

## Next RE priority

The highest-value next step is to reverse the 30 unique `_bzcp.dll` hook targets as named
behaviors, starting with:

- map filter and map list support hooks around `0x1000A040` through `0x1000D0B0`
- vehicle list and mod asset hooks around `0x1000D330` through `0x1000D460`
- lobby / command / ban-button hooks around `0x1000D770` through `0x1000E360`
- map icon / resource hooks around `0x1000E560` through `0x1000EAF0`

That work should let us replace guesswork in `src/` with address-accurate, behavior-accurate
clean-room implementations.
