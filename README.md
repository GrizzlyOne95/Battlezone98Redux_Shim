# BZR Open Shim

Open-source clean-room replacement for closed-source shims.

Repository name: Battlezone98Redux_Shim.

**Target**: Battlezone 98 Redux v2.2.301

The clean-room shim now supports both:
- `BZR.exe` (GOG)
- `battlezone98redux.exe` (Steam)

## Architecture

```
winmm.dll (this project)
  │
  ├── Proxies all winmm.dll exports → C:\Windows\System32\winmm.dll
  │
  └── Spawns patch thread → patcher.cpp::RunPatcher()
        │
        ├── Verifies BZR.exe file version == 301
        ├── Polls 0x00868300 for signature match
        └── Applies patches from patches.h via WriteProcessMemory
```

## What is patched

### Hop-Fix (primary target)

The hop-fix prevents the multiplayer map list from jumping back to the top
when the list rebuilds. The current clean-room port follows the same
three-stage method confirmed in `_bzcp.dll`:

1. save the selected entry and visible row before rebuild
2. reselect the matching entry after rebuild
3. replay the native row-step routine to restore the viewport

Reconstruction of the replacement code is in `trampolines.cpp` / `scroll_helper.h`.

### Steam-specific compatibility work

The Steam build needs a few extra guards beyond the original GOG-oriented
reverse-engineering notes:

- version-string operand sites are different on Steam
- some version-string bytes do not settle until shortly after process start
- calling `setvbuf(..., _IOLBF, 0)` during `DllMain` trips a UCRT fail-fast

The current patcher handles that by:

1. detecting the Steam executable name
2. waiting for the Steam version sites to reach their expected original bytes
3. patching the main menu and version-notice string operands to point at the
   OpenShim version tag
4. leaving logger buffering at the CRT default and flushing explicitly

## Building

1. Open `BZROpenShim.sln` in Visual Studio 2022+
2. Select **Release | Win32** (must be 32-bit to match BZR.exe)
3. Build → output is `bin\Release\winmm.dll`
4. Copy `winmm.dll` to the BZR.exe directory

For the Steam build, copy `winmm.dll` next to `battlezone98redux.exe`.

## Debug Metadata Inspection

If `llvm-pdbutil` is unavailable or blocked by local DIA/COM registration, use:

`python reverse_engineering/inspect_pdb.py --pe bin\Release\winmm.dll --pdb bin\Release\winmm.pdb --list-streams --show-paths`

The script reads PE RSDS records and PDB MSF metadata directly and can also
search raw PDB strings with repeated `--find` regex arguments.

## License

MIT - see LICENSE file
