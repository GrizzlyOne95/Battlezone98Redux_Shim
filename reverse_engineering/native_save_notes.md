# Native Save Notes

Date: March 12, 2026

## Scope

Goal: identify the game's native save entry point so Lua can trigger a real engine save instead of synthesizing `.sav` files in script.

Primary inputs:

- GOG EXE: `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe`
- GOG PDB: `C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb`
- Steam EXE: `C:\Users\istuart\Downloads\Battlezone 98 Redux\battlezone98redux.exe`

## Current Script Baseline

`Battlezone98Redux_CampaignReimagined-1/_Source/Scripts/AutoSave.lua` writes save files directly and only calls the mission-level Lua `Save()` callback to serialize script state.

That is not the same as the engine's native save path.

## GOG Findings

The GOG build exposes save-related symbol names in the PDB and save-format strings in the EXE:

- `fun3d\\LoadSaveGame.cpp`
- `SaveGame`
- `LoadGame`
- `SaveShellGame`
- `LoadShellGame`
- `PostLoadGame`
- `_save_bzone_game`
- `_load_bzone_game`

Static string/xref tracing in the EXE identifies a large serializer at:

- Candidate `SaveGame`: `0x004FD190`

Evidence:

- The function uses `[ebp+8]` as a path-like input.
- The function uses `[ebp+0xC]` as a mode/type value.
- It writes the canonical top-level save-file fields:
  - `binarySave`
  - `msn_filename`
  - `seq_count`
  - `missionSave`
  - `runType`
  - `saveGameDesc`
  - `TerrainName`
- It references `Failed to save game`.
- It returns with plain `ret`, which strongly suggests `cdecl`.

Working hypothesis:

```cpp
bool __cdecl SaveGame(char* filename, int nType);
```

There is also an auto-save related helper cluster around:

- `0x004FDAB0`
- `0x004FDC20`

Those functions reference:

- `auto.sav`
- `auto2.sav`
- `Auto Load Game: Run state set to bookmark`

They look like shell or bookmark helpers around the main save/load flow, not the core serializer itself.

## Signature

This GOG `.text` signature is unique in the file and lands on the candidate `SaveGame` start:

```text
55 8B EC 81 EC 94 00 00 00 C6 45 FF 01 E8 ?? ?? ?? ??
89 85 78 FF FF FF 68 ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4 04
0F B6 05 ?? ?? ?? ?? 85 C0 0F 84 ?? ?? ?? ?? 6A 2E
```

## Steam Findings

The Steam executable is not byte-identical to the GOG executable.

What matches:

- `.rdata`
- `.data`
- `.rsrc`

What differs:

- `.text`
- Steam adds a `.bind` section
- Steam entrypoint moves into `.bind`

Interpretation:

- The Steam binary is likely wrapped or transformed on disk.
- GOG RVAs should not be assumed to work directly against the Steam file-on-disk `.text`.
- The real opportunity is likely runtime scanning after the wrapper hands control to the engine image.

## Practical Next Step

1. Prove the GOG call end-to-end first by wiring a guarded native call from a shim or EXU export.
2. Trigger it only from a safe in-game context, not from shell menus or load screens.
3. For Steam, pattern scan runtime memory after startup instead of scanning the packed on-disk `.text`.
4. If needed, dump the post-wrapper in-memory `.text` and compare it to the GOG engine code.

## Helper Script

Use:

`reverse_engineering/locate_native_save.py`

It prints:

- section hashes for GOG and Steam
- the GOG save-field xref cluster
- the candidate `SaveGame` start
- the GOG-only save signature hit
- the cross-build `.text` mismatch summary
