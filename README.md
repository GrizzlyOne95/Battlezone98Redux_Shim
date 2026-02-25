# BZR Open Shim

Open-source clean-room replacement for closed-source shims.

**Target**: BZR.exe v2.2.301 (Steam release)

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

## License

MIT - see LICENSE file
