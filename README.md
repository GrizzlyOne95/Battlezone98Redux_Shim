# BZR Open Shim

Open-source clean-room replacement for the closed-source `winmm.dll` / `_bzcp.dll` shims from the Battlezone 98 Redux Community Patch.

**Target**: BZR.exe v2.2.301 (GOG release)

## Architecture

```
winmm.dll (this project)
  │
  ├── Proxies all winmm.dll exports → C:\Windows\System32\winmm.dll
  │
  ├── Loads _bzcp.dll (optional, for compatibility during development)
  │
  └── Spawns patch thread → patcher.cpp::RunPatcher()
        │
        ├── Verifies BZR.exe file version == 301
        ├── Polls 0x00868300 for signature match
        └── Applies patches from patches.h via WriteProcessMemory
```

## What is patched

All 27+ patches from `_bzcp.dll` are reimplemented here as clean-room code:

| Category | Count | Status |
|---|---|---|
| Map Sorting | 1 | TODO: address |
| Map Filters | 8 | TODO: addresses |
| Hop-Fix (scroll preservation) | 3 | TODO: addresses |
| Map List UI | 6 | TODO: addresses |
| Version Notice | 2 | TODO: addresses |
| Vehicle List Mod Fix | 4 | Partial (1 address hardcoded) |
| BZRNET hooks | 2 | TODO: addresses |
| Ban Button hooks | 2 | TODO: addresses |
| Misc (Joiner, Icons, CLI) | 4+ | TODO: addresses |

### Hop-Fix (primary target)

The hop-fix prevents the multiplayer map list from jumping (resetting scroll
position) when Steam workshop updates or data checks occur. It works by
installing 3 inline hooks that preserve and restore scroll state around map
list rebuilds.

Reconstruction of the replacement code is in `trampolines.cpp` / `scroll_helper.h`.

## Building

1. Open `BZROpenShim.sln` in Visual Studio 2022+
2. Select **Release | Win32** (must be 32-bit to match BZR.exe)
3. Build → output is `bin\Release\winmm.dll`
4. Copy `winmm.dll` to the BZR.exe directory

## Completing the TODO addresses

The BZR.exe addresses are stored at runtime in `_bzcp.dll`'s data section and
are not static. To extract them, attach x64dbg to a running patched BZR v2.2.301
(GOG) and set a breakpoint on `WriteProcessMemory`. Each call logs:
- The target address in BZR.exe
- The patch bytes written

Match these to the patch names printed in `bzcp.log` and fill in `patches.h`.

See `C:\Users\iestu\Documents\ref\X64DBG_VERIFICATION_GUIDE.md` for detailed instructions.

## License

MIT - see LICENSE file

## Credits

- Reverse engineering analysis in `C:\Users\iestu\Documents\ref\` 
- Original Community Patch by Nielk1
- ExtraUtilities infrastructure by VTrider (LGPL, used as reference)
