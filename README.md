# BZR Open Shim

An open-source runtime patch and compatibility layer for **Battlezone 98 Redux v2.2.301**.

OpenShim provides engine-level bug fixes, quality-of-life improvements, restored legacy behavior, multiplayer fixes, modding extensions, and optional experimental features that cannot be implemented through normal Redux modding alone.

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

### Global Gameplay Improvements

Optional improvements can be configured through `openshim.ini`, including:

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

Single-player-specific patches are automatically gated from multiplayer where required.

### Multiplayer & Networking

OpenShim also contains multiplayer fixes and diagnostic tooling, including:

- host ban controls and persistent ban lists
- multiplayer vehicle data fixes
- socket and buffer tuning
- UDP packet-reorder handling
- network route diagnostics
- optional packet/session capture tools
- multiplayer vehicle flag support

Experimental multiplayer features are disabled by default unless explicitly enabled.

### Modding Extensions

OpenShim exposes engine functionality that normal Redux mods cannot directly access.

Examples include:

- mission briefing asset overrides
- native configuration shared across campaigns and Instant Action
- Lua/ExtraUtilities bridge functions
- music-control bridge support
- native gameplay-state access for EXU
- runtime Ogre integration

When EXU and OpenShim expose the same feature, OpenShim can provide the native implementation while EXU provides the Lua-facing API.

## Configuration

Most user-facing options are configured through:

```text
openshim.ini
```

Copy:

```text
openshim.ini.example
```

to:

```text
openshim.ini
```

beside the game executable.

Networking-specific settings are available through:

```text
net.ini
```

Environment variables are also available for development, diagnostics, compatibility testing, and experimental features.

See the example configuration files and `reverse_engineering/` documentation for detailed options.

## Safety & Compatibility

OpenShim is designed to **fail safely**.

Before modifying native game code, hooks validate the executable, runtime state, and expected machine-code bytes. If a supported patch site does not match what OpenShim expects, that patch is skipped rather than blindly modifying memory.

Steam and GOG differences are handled separately where necessary.

The current target is:

```text
Battlezone 98 Redux 2.2.301
```

Other game versions should not be assumed compatible.

## Experimental Features

The repository also contains ongoing reverse-engineering work and experimental native extensions.

Examples include:

- legacy death-chunk rendering
- producer build-menu extensions
- additional multiplayer integration
- renderer/Ogre diagnostics
- input-system extensions

Experimental features are normally gated behind configuration or environment variables and should not be considered part of the stable feature set until validated.

Detailed research, addresses, traces, validation results, and test procedures belong under:

```text
reverse_engineering/
```

rather than this README.

## Installation

Copy the compiled:

```text
winmm.dll
```

into the Battlezone 98 Redux installation directory beside:

```text
BZR.exe
```

or:

```text
battlezone98redux.exe
```

Launch the game normally.

OpenShim writes runtime information and diagnostics to its log files in the game directory.

To uninstall OpenShim, remove `winmm.dll` and any optional OpenShim configuration files.

## Building

Requirements:

- Visual Studio 2022 or newer
- C++ development tools
- Win32/x86 target

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
