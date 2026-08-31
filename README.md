# BZR Open Shim

An open-source runtime patch and compatibility layer for **Battlezone 98 Redux v2.2.301**.

OpenShim provides engine-level bug fixes, quality-of-life improvements, restored legacy behavior, multiplayer fixes, modding extensions, and opt-in native features that cannot be implemented through normal Redux modding alone.

Supported executables:

- **GOG:** `BZR.exe`
- **Steam:** `battlezone98redux.exe`

<img width="1377" height="758" alt="Battlezone 98 Redux OpenShim" src="https://github.com/user-attachments/assets/b1f12ee2-5e57-46df-b467-1d5c69c6426e" />

## What is OpenShim?

OpenShim is a standalone `winmm.dll` proxy loaded automatically when Battlezone 98 Redux starts.

It forwards the normal Windows Multimedia API calls to the real system `winmm.dll`, then initializes OpenShim inside the game process.

This allows the project to safely hook or patch native Redux behavior at runtime without modifying the game executable on disk.

```text
Battlezone 98 Redux
        │
        ▼
    winmm.dll
    (OpenShim)
        │
        ├── Forwards WinMM calls to Windows
        │
        └── Starts OpenShim
                │
                ├── Detects Steam/GOG build
                ├── Validates expected game code
                ├── Installs native hooks
                ├── Applies runtime fixes
                └── Loads OpenShim configuration
```

OpenShim is a clean-room implementation and runs independently of any closed-source patch DLL.

## Project Status

OpenShim is mature enough that most of the repository should **not** be read as unfinished end-user functionality. Much of its size is reverse-engineering evidence, validation tooling, diagnostics, compatibility infrastructure, and records of experiments used to arrive at the current implementations.

### Working functionality

The main runtime patch layer and most user-facing features are implemented and usable. This includes the engine/gameplay fixes described below plus features such as:

- native legacy death-chunk rendering using `chunkMeshes`
- native input/options UI extensions
- multiplayer host controls and persistent bans
- multiplayer vehicle flags and flag-selection UI
- native nickname and network-preference UI
- Lua/ExtraUtilities bridge functionality
- mission briefing and media compatibility fixes
- Ogre/resource compatibility fixes and runtime integration

Some working features are still opt-in because they intentionally change stock behavior. **Opt-in does not automatically mean experimental.**

### Active development

The remaining larger feature work is concentrated in a few areas:

- **HD terrain replacement:** the semantic terrain path, mission lifecycle, shader specialization, and initial texture-array path exist; whole-map HD replacement and the remaining material/lifetime validation are still in progress.
- **Producer build-menu extensions:** native recursive build-menu behavior has been reverse engineered and is being exposed as an opt-in nested-menu path for testing before it is promoted to a supported modding extension.
- **Battlezone 1.5 multiplayer UI restoration:** flag selection and nickname/network controls are implemented; game-option controls and persistent profile/player-card functionality remain.
- **Shutdown/lifetime validation:** renderer and Ogre ownership fixes exist, but normal-exit regression coverage and loader-lock-safe shutdown remain completion work.
- **UDP packet reordering:** retained as an opt-in networking experiment/diagnostic until its long-term design is settled.

Developer probes, packet capture, renderer diagnostics, ABI tests, reverse-engineering scripts, and similar tooling are intentionally not part of the normal user-facing feature set.

## What does it do?

OpenShim is primarily intended to fix or extend parts of Redux that are inaccessible to Lua, ODFs, shaders, or normal Workshop mods.

Major areas include:

### Engine & Gameplay Fixes

Native fixes and restorations for Redux behavior, including:

- multiplayer map-list position preservation
- constructor/build-state cleanup
- APC, tug, howitzer, minelayer, and other AI/gameplay fixes
- mission restart/load behavior improvements
- mission briefing scrolling fixes
- Ogre resource/material collision handling
- legacy jump-sniping behavior
- engine light and visual-state fixes
- increased sound-channel capacity
- restored legacy death-chunk rendering

### Global Gameplay Improvements

Optional improvements can be configured through:

```text
openshim.ini
```

including:

- smart reticle range
- weapon and player reticle convergence
- improved scavenger targeting
- turret aim-pitch limits
- turbo behavior
- unit voice-feedback policy
- player and AI headlights
- scrap/pilot HUD behavior
- target-reticle behavior
- sound-channel limits
- native input and options UI extensions

Single-player-specific patches are automatically gated from multiplayer where required.

### Multiplayer & Networking

OpenShim also contains multiplayer fixes and diagnostic tooling, including:

- host ban controls and persistent ban lists
- multiplayer vehicle data fixes
- multiplayer vehicle flag support and flag selection
- native nickname and network-preference controls
- socket and buffer tuning
- network route diagnostics
- optional packet/session capture tools
- opt-in UDP packet-reorder experimentation

Diagnostics and experimental networking behavior are disabled by default unless explicitly enabled.

### Modding Extensions

OpenShim exposes engine functionality that normal Redux mods cannot directly access.

Examples include:

- mission briefing asset overrides
- native configuration shared across campaigns and Instant Action
- Lua/ExtraUtilities bridge functions
- music-control bridge support
- native gameplay-state access for EXU
- runtime Ogre integration
- legacy `chunkMeshes` rendering support
- ongoing native producer build-menu extensions

When EXU and OpenShim expose the same feature, OpenShim can provide the native implementation while EXU provides the Lua-facing API.

## Configuration

Normal player defaults are shipped in:

```text
openshim.ini
```

That file contains every first-class OpenShim setting with conservative,
stock-preserving values. OpenShim fixes, enhancements, UI replacements,
autosave, and diagnostics are opt-in. To disable the legacy mouse path's
smoothing/Windows acceleration, set `[General] RawMouseInput = 1` and restart
the game. Users can edit the file directly or enable the native OpenShim
Settings page where supported.

The exhaustive technical reference remains:

```text
openshim.ini.example
```

Use the example when you need accepted values, aliases, ranges, restart/live-apply behavior, implementation notes, or legacy `OPENSHIM_*` / `BZR_*` compatibility variables. It is a reference, not the recommended player preset.

Networking-specific low-level settings are available through:

```text
net.ini
```

See the configuration files and `Docs/` / `reverse_engineering/` documentation for detailed options and validation notes.

## Safety & Compatibility

OpenShim is designed to **fail safely**.

Before modifying native game code, hooks validate the executable, runtime state, and expected machine-code bytes. If a supported patch site does not match what OpenShim expects, that patch is skipped rather than blindly modifying memory.

Steam and GOG differences are handled separately where necessary.

The current target is:

```text
Battlezone 98 Redux 2.2.301
```

Other game versions should not be assumed compatible.

## Development & Diagnostics

The repository contains substantial reverse-engineering and validation material alongside the runtime patch itself. This is intentional: native hooks depend on exact executable behavior, ABI layout, ownership rules, and patch-site validation.

Examples include:

- renderer/Ogre diagnostics and profiling
- terrain semantic/parity validation
- multiplayer packet/session capture and route diagnostics
- UI ABI probes and Battlezone 1.5 UI recovery tools
- producer/build-menu reverse engineering
- executable address, signature, and lifecycle research

These tools may be incomplete, highly specialized, or development-only even when the runtime feature they helped produce is already working.

Detailed research, addresses, traces, validation results, and test procedures belong under:

```text
Docs/
reverse_engineering/
```

rather than being treated as the public feature list.

## Installation

Copy the compiled:

```text
winmm.dll
```

and the shipped player configuration:

```text
openshim.ini
```

into the Battlezone 98 Redux installation directory beside:

```text
BZR.exe
```

or:

```text
battlezone98redux.exe
```

Launch the game normally. `openshim.ini.example` may be kept alongside it as an offline reference, but OpenShim reads `openshim.ini` for normal configuration.

OpenShim writes runtime information and diagnostics to its log files in the game directory.

To uninstall OpenShim, remove `winmm.dll` and any optional OpenShim configuration files.

## Building

Requirements:

- Visual Studio 2022 or newer
- C++ development tools
- Git
- Win32/x86 target

Fetch the pinned Ogre 1.10.0 reference headers once after cloning:

```powershell
.\setup-dev.ps1
```

The current renderer diagnostics compile against these reference declarations. OpenShim does **not** build or link a replacement `OgreMain.dll`; runtime integration continues to target the game's already-loaded Ogre module. The shipped BZR Ogre binary has known ABI differences from pristine upstream 1.10.0, so runtime-facing hooks must still validate the actual BZR DLL.

Open:

```text
BZROpenShim.sln
```

Build:

```text
Release | Win32
```

Output:

```text
bin\Release\winmm.dll
```

Redux is a 32-bit application, so OpenShim must also be built as **32-bit**.

## Project Scope

OpenShim is not a replacement game engine and does not attempt to rewrite Battlezone 98 Redux.

Its purpose is to provide a maintainable native patch layer for targeted fixes and extensions where the stock game does not expose enough functionality through its normal modding interfaces.

Where possible, features remain:

- narrowly scoped
- configurable
- backwards compatible
- signature validated
- disabled when unsafe
- compatible with normal Redux mods and EXU

## License

MIT — see [LICENSE](LICENSE).

## Credits

- **GrizzlyOne95** — primary implementation, reverse engineering, and maintenance
- **Piercing** — multiplayer testing, network investigation, and technical collaboration
- **VTrider** — technical assistance and collaboration
- **Business Lawyer** — technical assistance and collaboration
- **Janne** — early work investigating DLL shimming and hooking in Battlezone 98 Redux
