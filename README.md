# BZR Open Shim

Open-source clean-room replacement for closed-source shims.

Repository name: Battlezone98Redux_Shim.

**Target**: Battlezone 98 Redux v2.2.301

The clean-room shim now supports both:
- `BZR.exe` (GOG)
- `battlezone98redux.exe` (Steam)

<img width="1377" height="758" alt="image" src="https://github.com/user-attachments/assets/b1f12ee2-5e57-46df-b467-1d5c69c6426e" />


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

Steam status as of March 16, 2026:

- manual refresh now preserves both the selected map and the visible list row
- wheel scrolling and first-click map selection no longer fault in the Steam
  refresh path
- the partial clean-room map-filter port is intentionally disabled on Steam for
  now, so filter and sort UI behavior falls back to the stock game

That last point is deliberate. The in-progress `_bzcp.dll` filter/sort port was
interfering with the Steam map-list UI and exposed only `All Maps` instead of
the full stock filter set. Until the remaining behavior is fully replicated,
OpenShim keeps the core map-list position fix active but does not patch the
custom filter/sort stack.

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
5. preserving the stock map-filter and sort UI until the clean-room filter port
   is complete

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

## Howitzer / Minelayer Weapon Mask Fix

There is now a Shim-side behavior patch for the hardcoded howitzer and
minelayer first-slot issue on the GOG executable.

- The patch biases `Carrier` slot `0` toward the decoded `weaponMask` target
  for `Howitzer` and `Minelayer` craft.
- Artillery AI reaches the bias helper through the existing artillery hook.
- Additional bias refreshes run through exact `weaponMask` getter hooks and the
  existing hovercraft flame path, which helps keep minelayers aligned without
  rewriting the full native AI state machine.
- Steam is still skipped until the equivalent sites are revalidated there.

Optional trace logging:

- Enable `OPENSHIM_TRACE_ARTILLERY_MASK=1` before launching the game.
- `[ARTYMASK]` lines in `winmm_shim.log` record `process`, `process vft`,
  `craft`, `craft vft`, raw `weaponMask`, decoded `weaponMask`,
  `modeList.enabledMask`, and `modeList.activeSlot`.
- Logging is budget-limited to the first `400` hits.

Current limitation:

- This fix has been build-validated but not yet gameplay-validated in a live
  Redux session.

## Audio Channel Override

OpenShim now includes a native GAS max-object override to help with sound
dropouts during large battles.

- The shim defaults to a conservative `150`-channel cap.
- Set `OPENSHIM_MAX_SOUND_CHANNELS=<n>` to choose a different limit.
- Set `OPENSHIM_MAX_SOUND_CHANNELS=0` to disable the override.
- `BZR_MAX_SOUND_CHANNELS` is also accepted as a legacy/testing alias.
- Values above `256` are clamped down to `256`.

Notes:

- This targets the legacy `GM->maxObjects` sound-channel cap, so it should help
  voice stealing and cutouts more than true mixer clipping/distortion.
- Current Steam runtime captures suggest the stock internal cap is `100`, so
  the default OpenShim setting is intentionally a modest step above stock.
- The shim locates the GAS globals at runtime. If Steam's runtime layout does
  not match the current anchor yet, the log will note that the override was
  skipped instead of patching blindly.

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

## LLDB Recovery

If the local LLVM `lldb.exe` crashes on startup because it cannot find a
complete Python 3.11 runtime, run:

`powershell -ExecutionPolicy Bypass -File .\install_lldb_shim.ps1`

The script installs user-level `lldb.cmd` and `lldb-dap.cmd` wrappers in
`%USERPROFILE%\bin`, points them at the LLVM debugger binaries, and supplies
the Python runtime from the Android Studio NDK LLDB bundle when present.

## Netcode Reorder Controls

The Windows shim now includes the first-pass UDP packet resequencer from the
netcode investigation work. It runs inside the existing `WSARecvFrom` hook and
holds small out-of-order bursts briefly so they can be delivered back to the
game in sequence.

Configure it through `net.ini` next to the game executable:

```ini
[OpenShimSocket]
EnablePacketReorder=1
PacketReorderWindowMs=30
LogPacketReorder=1
```

Notes:

- `EnablePacketReorder=1` enables the reorder buffer for synchronous UDP recv.
- `PacketReorderWindowMs` is clamped to `5`-`200` ms.
- `LogPacketReorder=1` enables detailed reorder diagnostics in `openshim.log`.
- Environment variables `BZ_REORDER`, `BZ_REORDER_WINDOW_MS`,
  `OPENSHIM_REORDER`, and `OPENSHIM_REORDER_WINDOW_MS` override the `net.ini`
  values for testing.
- The reorder path is bypassed for overlapped or async `WSARecvFrom` calls.

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

## Special Thanks to Piercing, VTrider and Business Lawyer for technical assistance and collaboration building this DLL patch. Thanks to Janne for their original work learning how to shim and hook DLL's into BZR.
