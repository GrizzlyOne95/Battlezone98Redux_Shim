# Ghidra DLL RE Notes

This note summarizes what headless Ghidra analysis confirmed for:

- `reverse_engineering/workshop/3362534335/latest/_bzcp.dll`
- `reverse_engineering/workshop/3362534335/latest/winmm.bin`

The reproducible workflow lives in:

- `scripts/ghidra_extract_dll_summary.py`

Generated output from the current sample binaries is stored at:

- `reverse_engineering/workshop/3362534335/ghidra_dll_summary.md`

## What Ghidra confirmed

### `winmm.bin`

Ghidra decompilation of `FUN_10001C20` confirms the loader chain directly:

1. Resolve `.\..\..\workshop\content\301650\3362534335\_bzcp.dll`
2. Fallback to `.\mods\3362534335\_bzcp.dll`
3. `GetProcAddress(..., "patch")`
4. Invoke `patch(1)`
5. Load the real system `WINMM.dll`
6. Populate the export-forwarding function pointers

This matches the existing disassembly-based conclusion, but the Ghidra output is cleaner and
easier to trust than the earlier generic decompilers.

### `_bzcp.dll`

Ghidra decompilation of the exported `patch` function confirms:

- it is idempotent (`DAT_1002ab10` guard)
- it allocates an 8-byte thread argument block
- it launches the worker at `FUN_1000EB30`
- it detaches the thread and returns

Ghidra decompilation of the three hop-fix helpers also cleanly confirms the earlier static RE:

- `FUN_1000CAF0`
  - saves the current map-list index-like state into `DAT_1002A1C8`
  - copies the currently selected map string into the stock string buffer at `1002A1EC`

- `FUN_1000CB40`
  - derives filter state
  - falls back to `"All Maps"` when the saved identity is not valid for the current filter context
  - scans rebuilt map entries for the saved identity string
  - restores the selection through `DAT_1002AD08` (`0x7CAFA0`)

- `FUN_1000CCA0`
  - uses the saved index in `DAT_1002A1C8`
  - bounds-checks it against the current list span
  - replays `DAT_1002ADB0` (`0x7A3130`) that many times
  - clears the saved index back to `-1`

This reinforces the conclusion that the hop-fix is a three-stage stateful pipeline:

1. capture selection and list position
2. rebuild list and re-select matching map
3. replay scroll movement to restore visible position

## Limitation: Steam EXE on disk

The local `battlezone98redux.exe` checked during Ghidra validation behaves like the Steam-packed
case already described in `docs/STEAM_VS_GOG.md`:

- patch-site VAs exist in the mapped `.text` range
- raw bytes at those addresses are zero on disk
- Ghidra does not auto-create meaningful functions there from the packed file alone

Implication:

- Ghidra is immediately useful for `_bzcp.dll` and `winmm.bin`
- for the game executable patch sites, use a decrypted memory image, unpacked build, or a GOG
  executable if deeper function-level Ghidra recovery is needed

## Regenerate

With `GHIDRA_INSTALL_DIR` set:

```powershell
python .\scripts\ghidra_extract_dll_summary.py `
  --out .\reverse_engineering\workshop\3362534335\ghidra_dll_summary.md
```
