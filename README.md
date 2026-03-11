# BZR Open Shim

Open-source clean-room replacement for closed-source shims.

Repository name: Battlezone98Redux_Shim.

**Target**: BZR.exe v2.2.301 (GOG primary target)

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

## Building

1. Open `BZROpenShim.sln` in Visual Studio 2022+
2. Select **Release | Win32** (must be 32-bit to match BZR.exe)
3. Build → output is `bin\Release\winmm.dll`
4. Copy `winmm.dll` to the BZR.exe directory

## Workshop RE Workflow

Use `docs/WORKSHOP_RE_SETUP.md` and `scripts/Download-WorkshopItem.ps1`
to fetch and snapshot Workshop mods via SteamCMD for repeatable
reverse-engineering analysis.

Latest hop-fix reverse-engineering findings are tracked in
`docs/HOPFIX_METHOD_RE.md`.

## License

MIT - see LICENSE file
