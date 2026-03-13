# Native Pause Menu Probe

Date: 2026-03-13

Goal: detect when the stock Escape pause UI is open from native external code so
custom HUD or subtitle rendering can be suppressed even while Lua is paused.

## Result

For Battlezone 98 Redux v2.2.301, a reliable external check is:

- Single-player:
  - `0x009454EC`: single-player pause root (`sEsc` / Escape screen singleton)
  - `0x00918320`: current UI screen pointer
  - `0x00918324`: UI wrapper active flag
  - `0x00918328`: current UI screen type
- Multiplayer:
  - `0x0094557C`: multiplayer pause root
  - `0x00945549`: multiplayer pause flag
  - plus `GetCursorInfo()` as a guard to avoid false positives

Single-player pause is open when:

1. `*(void**)0x009454EC != nullptr`
2. `*(uint32_t*)0x00918324 != 0`
3. and either:
   - `*(void**)0x00918320 == *(void**)0x009454EC`
   - or `*(uint32_t*)0x00918328` is one of:
     - `0x0B` pause
     - `0x03` options
     - `0x11` save game
     - `0x12` load game
     - `0x17` restart

This is what [`game_state.cpp`](/c:/Users/istuart/Documents/GIT/Battlezone98Redux_Shim/src/game_state.cpp)
now implements.

## Why This Looks Correct

The shipped GOG PDB is not a perfect GUID match for the executable, but it still
provides a coherent UI singleton cluster:

- `sEsc`
- `sLoad`
- `sOptionsAudio`
- `sOptionsGraphics`
- `sOptionsInput`
- `sOptionsJoystick`
- `sOptionsParent`
- `sOptionsPlay`
- `sSave`
- `sSinglePlayer`

Using `llvm-pdbutil` on `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb`
shows that these globals live together in the `.data` singleton block. That
matches the known absolute addresses already used successfully in:

- [`IO.cpp`](C:/Users/istuart/Documents/GIT/ExtraUtilities-G1/src/IO.cpp)
- [`usergui.cpp`](C:/Users/istuart/Documents/GIT/BZR-Subtitles/external/usergui.cpp)

## Binary Sanity Check

Both executables currently in scope share the same image base and section layout
for the relevant globals:

- `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe`
- `C:\Users\istuart\Downloads\Battlezone 98 Redux\battlezone98redux.exe`

The addresses above all land inside `.data` in both binaries, so the probe is
valid for both current installs.

## Commands Used

```powershell
C:\Program Files\LLVM\bin\llvm-pdbutil.exe dump --globals --global-name=sEsc `
  C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb

C:\Program Files\LLVM\bin\llvm-pdbutil.exe dump --globals --global-name=sOptionsPlay `
  C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb

C:\Program Files\LLVM\bin\llvm-pdbutil.exe dump --globals --global-name=sSave `
  C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb
```

Python `pefile` inspection also confirmed that `0x00918320`, `0x00918324`,
`0x00918328`, `0x009454EC`, `0x00945549`, and `0x0094557C` all resolve into
the `.data` section for both the GOG and Steam executables listed above.
