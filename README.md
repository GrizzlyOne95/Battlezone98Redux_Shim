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
  └── Spawns patch thread
        │
        ├── Initializes startup-time Winsock hooks via net_optimizer.cpp
        └── Runs patcher.cpp::RunPatcher()
              │
              ├── Verifies BZR.exe file version == 301
              ├── Polls 0x00868300 for signature match
              └── Applies patches from patches.h via WriteProcessMemory
```

The shim now runs fully standalone and does not load or defer to any external
patch DLL.

## What is patched

### Hop-Fix (primary target)

The hop-fix prevents the multiplayer map list from jumping back to the top
when the list rebuilds. The current clean-room port follows the same
three-stage method confirmed during reverse-engineering:

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

### Legacy Chunk Render Bridge Experiment

The shim now includes a GOG-only test hook for the legacy chunk visibility
investigation tied to invisible death chunks in Redux.

What it does:

1. hooks the native resolve call inside the object render classifier
2. lets the stock resolver run first
3. if the stock path fails and the experiment is enabled, picks the first
   non-null geometry entry from the object's legacy geometry table
4. writes that handle back to the active render slot so the object can keep
   moving through normal render classification

This is intentionally narrow. It does not add native GEO rendering, and it
does not claim to be the final chunk fix. It is a bridge experiment meant to
prove whether chunk child objects are invisible because they fail to select an
active Ogre-backed render handle.

The hook is disabled by default. Enable it with either environment variable:

- `BZR_CHUNK_FORCE_FIRST_GEO=1`
- `OPENSHIM_CHUNK_FORCE_FIRST_GEO=1`

Current scope:

- validated against the GOG address `CALL 0x004E3620` at `0x00443B34`
- not enabled for Steam yet because the equivalent site has not been
  revalidated there

Suggested test asset:

- `agr11bda.geo` from `avtank.vdf`

The intent is to give a known good `VGEO` name a valid Redux mesh/material
pipeline, then see whether chunk child objects become visible once a valid
render handle is forced into the stock resolve/classify path.

## Building

1. Open `BZROpenShim.sln` in Visual Studio 2022+
2. Select **Release | Win32** (must be 32-bit to match BZR.exe)
3. Build → output is `bin\Release\winmm.dll`
4. Copy `winmm.dll` to the BZR.exe directory

For the Steam build, copy `winmm.dll` next to `battlezone98redux.exe`.

## Netcode Verification

1. Launch the game with OpenShim installed.
2. Enter multiplayer so the game creates its P2P sockets.
3. Exit the game.
4. Run `.\verify_windows.ps1` from the repo root, or pass `-GamePath` explicitly.

The verifier uses `openshim.log` as the source of truth and checks for:

- successful Winsock hook installation
- `SO_SNDBUF` readback reaching `524288`
- `SO_RCVBUF` readback reaching `4194304`

## Testing The Chunk Experiment

1. Build `bin\Release\winmm.dll`.
2. Copy it next to the GOG game executable in `C:\GOG Games\Battlezone 98 Redux`.
3. Set `BZR_CHUNK_FORCE_FIRST_GEO=1` before launching the game.
4. Make sure the test GEO you want to exercise has a valid Redux-side
   mesh/material pipeline. For the current working assumption, use
   `agr11bda` from `avtank.vdf`.
5. Start a scenario that reliably produces large death chunks from vehicles or
   structures.
6. Watch for either:
   - newly visible chunk geometry
   - changed behavior in chunk impacts that suggests the object now has a
     valid active render handle
7. Inspect the shim log for lines beginning with `[CHUNK]`.

Expected log signals:

- `Force-first-geo fallback: enabled`
- `Forced geometry entry ...`

If the hook never logs forced geometry for destroyed objects, the failure is
probably earlier than active-handle selection. If it does log forced geometry
but chunks still do not render, the next failure point is likely downstream in
render-class handling or Ogre proxy creation.

### Producer Build Menu Bridge Experiment

The shim now includes a first-pass native hook for testing submenu-capable
producer build menus on the GOG executable.

What it does:

1. hooks a call inside `Producer::UpdateModeList`
2. identifies common producer types by vtable
3. swaps the global native `buildMenu` root through the game's own
   `InitBuildItem` / `CleanupBuildItem` path
4. lets the original producer helper keep running afterward

Configuration:

- copy `openshim_producer_build_menus.ini.example` next to the game EXE as
  `openshim_producer_build_menus.ini`
- set root tokens under `[ProducerBuildMenus]` for:
  - `Recycler`
  - `Factory`
  - `Armory`
  - `ConstructionRig`

Current scope and cautions:

- GOG-only for now
- config-driven by producer type, not by ODF field yet
- this is the bridge experiment, not the finished submenu feature
- final submenu navigation and leaf-build handoff still need in-game validation

## Debug Metadata Inspection

If `llvm-pdbutil` is unavailable or blocked by local DIA/COM registration, use:

`python reverse_engineering/inspect_pdb.py --pe bin\Release\winmm.dll --pdb bin\Release\winmm.pdb --list-streams --show-paths`

The script reads PE RSDS records and PDB MSF metadata directly and can also
search raw PDB strings with repeated `--find` regex arguments.

## License

MIT - see LICENSE file

## Special Thanks to Piercing, VTrider and Business Lawyer for technical assistance and collaboration building this DLL patch.
