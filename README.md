# BZR Open Shim

An open-source native patch and compatibility layer for **Battlezone 98 Redux 2.2.301**. OpenShim fixes engine and gameplay bugs, restores selected Battlezone 1.5 behavior, improves multiplayer, and exposes functionality that normal Lua/ODF/Workshop mods cannot reach.

<img src="https://github.com/user-attachments/assets/7da1eab5-50d1-417a-9d76-4004dcd11300" width="960" alt="Battlezone 98 Redux with OpenShim" />

**Get the current release:** [OpenShimSetup.exe](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/releases/latest/download/OpenShimSetup.exe) · [Releases and checksums](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/releases/latest)

> **Release vs. development:** `main` changes frequently and may contain features or defaults that have not been released. The files and `openshim.ini` bundled with a release are authoritative for that release. Other Redux versions are not assumed compatible.

## Install

### Windows (Steam or GOG)

1. Download and run [OpenShimSetup.exe](https://github.com/GrizzlyOne95/Battlezone98Redux_Shim/releases/latest/download/OpenShimSetup.exe).
2. Select an install folder (Steam, GOG, or a custom game path) and an action:
   - **Install:** deploy the version embedded in the setup executable.
   - **Repair:** restore missing/changed files at the *same* installed version, preserving existing `openshim.ini` and `net.ini`.
   - **Update:** retrieve the latest published release; refuses downgrades. Use Repair for damaged files already at the latest version.
   - **Uninstall:** remove OpenShim-owned files and backups; keep player configuration and logs by default. An unchecked cleanup option can also remove OpenShim settings, logs, dumps, and uploader data.
3. Close the game before any of these actions. Start Redux normally afterward; no Windows launch option is needed.

**Note:** Normal Install/Update can replace `net.ini` after backing up the old file; Repair preserves an existing one. The full cleanup option removes current-user OpenShim data shared across installations, but retains shared `net.ini`, `BZLogger.txt`, and unrelated mods.

### Linux (Steam/Proton)

For native Steam or Flatpak Steam:

```bash
curl -fsSL https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_linux.sh | bash -s -- --native
```

For Snap Steam:

```bash
curl -fsSL https://raw.githubusercontent.com/GrizzlyOne95/Battlezone98Redux_Shim/main/scripts/install_linux.sh | bash -s -- --snap
```

Set Steam's **Launch Options** to:

```text
WINEDLLOVERRIDES="winmm=n,b;dsound=n,b" %command%
```

Keep the quotes: the semicolon otherwise splits the shell command. Remove `;dsound=n,b` if you do not use the separate `dsound` netcode proxy. Linux/GOG under a compatible Wine/Proton prefix is also in the support matrix, but needs an explicit game path; see [Installation and troubleshooting](Docs/INSTALLATION.md).

The installer downloads and verifies a matched release suite. **The same Win32 binaries run through Proton/Wine; OpenShim does not have a native Linux `.so` build.**

For Windows PowerShell alternatives, uninstall commands, Linux cleanup, offline setup, security notes, and troubleshooting, see [Installation and troubleshooting](Docs/INSTALLATION.md).

## Compatibility and loading

| Host | Distribution | Executable / runtime |
| --- | --- | --- |
| Windows | Steam | `battlezone98redux.exe` (Win32) |
| Windows | GOG | `BZR.exe` (the installer also detects `battlezone98redux.exe`) |
| Linux | Steam | Windows game/DLLs through Proton (native, Flatpak, or Snap Steam) |
| Linux | GOG | Windows game/DLLs through a compatible Wine/Proton prefix |

See the [shared platform compatibility policy](Docs/BZR_PLATFORM_COMPATIBILITY.md). Support policy is not proof that every current development commit has passed every runtime smoke test.

OpenShim does **not** modify the game's executable on disk. Its load chain is:

```text
Redux executable
  -> winmm.dll                 (Windows multimedia forwarding / bootstrap)
  -> bzloader.dll              (plugin host)
  -> plugins/openshim.dll      (runtime patches and hooks)
       + scripts/patches.json  (version-specific patch definitions)
```

These files form a matched set; a lone `winmm.dll` does not provide OpenShim's runtime. The project is independently developed and does not require any closed-source patch DLL.

## What it changes

The core patch layer and most player-facing features are implemented. Some are configurable, and some enabled fixes are restricted to single-player to avoid multiplayer simulation differences.

| Area | Examples |
| --- | --- |
| **Engine and gameplay** | AI/build-state fixes (APC, tug, constructor, howitzer, etc.); mission load/restart and briefing fixes; resource/material collision guards; DX11 device-loss recovery; sound-channel capacity; Battlezone 1.5 jump-sniping restoration |
| **Player options** | Native OpenShim Options/keybinding screens; raw mouse input; headlights; smart reticles and targeted/targetless weapon convergence; optional HUD, voice, turbo, and turret behavior |
| **Multiplayer** | Map-list preservation; host controls and persistent bans; vehicle flags and lobby selection; nickname/network preferences; socket/buffer tuning; guarded reliable-send backlog fix and route diagnostics |
| **Modding** | Lua/ExtraUtilities bridge; gameplay-state and music controls; mission briefing media overrides; Ogre integration; native death-chunk generation; experimental producer build-menu extensions |

An optional `ChunkMeshes` feature can generate destruction pieces directly from the source model and skeleton; **it does not require a separate chunk asset pack**. Existing authored assets remain fallback inputs for unsupported models. See [Native chunk meshes](Docs/NATIVE_CHUNK_MESHES.md).

OpenShim also supports installation without the Campaign Reimagined/Workshop asset pack. Native fixes and networking remain available; **Enhanced renderer resources and other asset-backed effects are enabled only when their required files are detected**. The settings UI reports missing or incompatible resources. Asset-pack installation is separate from the required DLL/patch load chain.

## Defaults, configuration, and current limitations

Open **Options → OpenShim Options** in game, or edit the installed `openshim.ini` and restart where a setting requires it. `openshim.ini.example` is the detailed reference for allowed values, compatibility variables, and live/restart behavior. `net.ini` holds lower-level network values.

- Confirmed and qualified fixes may default **on**; optional and experimental features are not universally off. **Check the exact preset shipped with your release.** Current `main` selects DX11 Enhanced, enables terrain micro-relief, and enables HD-terrain manifest auto-discovery; missing HD assets degrade to stock behavior. A released build can have different defaults.
- `RawMouseInput = 1` bypasses the legacy mouse-message smoothing/acceleration path; restart required.
- `[Network] GovernorTuning = OpenShim` retains measured governor/host auto-kick tuning. Use `Stock` for strict stock-policy parity; `net.ini` remains the granular source for low-level values.
- **World Builder source-folder saves are on by default** (`EditorSaveToSourceFolder = 1`) and show a destination/overwrite confirmation with Cancel as the default. Set `0` for stock root-addon saves. Full editor round-trip/platform qualification is still pending; see [feature status](Docs/BZN_SAVE_SOURCE.md).

Larger active development areas include whole-map HD terrain replacement, production-menu extensions, remaining Battlezone 1.5 multiplayer UI, shutdown/lifetime testing, and opt-in UDP packet-reordering experiments. Their presence in the source tree is **not** a promise that they are completed or enabled in a published release.

Native patch sites validate supported executable identity and expected bytes and are designed to skip a mismatched site rather than patch blindly. That safeguard is not a guarantee of universal crash-free behavior. Refer to [release qualification](Docs/RELEASE_QUALIFICATION.md) for the required Steam/GOG, multiplayer, and lifecycle smoke tests.

## Opt-in test-crew logging

Ordinary installs do **not** automatically upload session logs. Testers can explicitly install the private-channel logging configuration and launch through a separate wrapper. Multiplayer peers' public IP addresses can appear in those bundles because Redux uses peer-to-peer networking; share bundles only through a trusted private channel.

On Windows, configuring the uploader may also cause its installer to **attempt a Microsoft Defender exclusion for the current user's dedicated OpenShim uploader folder**. Review that behavior before opting in. The wrapper launch option is the upload opt-in, and any leftover Steam launch option must be removed manually after uninstalling.

Full setup, privacy, and platform-specific wrapper instructions: [Automatic session upload](upload/README.md).

## Build and contribute

- **Windows:** Visual Studio 2022+ with C++ tools. Run `./setup-dev.ps1` to fetch pinned Ogre 1.10 reference headers, open `BZROpenShim.sln`, and build **Release | Win32**. Deploy all three DLLs with matching `scripts/patches.json`; Redux remains a 32-bit executable.
- **Linux host tests:** run `./setup-dev.sh`, then `cmake -S tests -B tests/build`, `cmake --build tests/build -j`, and `ctest --test-dir tests/build --output-on-failure`. Linux does not build the full Windows proxy/runtime.
- The runtime integrates with the game's loaded Ogre module; it does not ship a replacement `OgreMain.dll`. The game's Ogre ABI differs in places from stock Ogre 1.10, so runtime hooks require actual Redux validation.

CI exercises the engine-independent suite, INI/config and network safety checks, shader compilation, and Win32 build/package checks. These automated gates complement, rather than replace, real-game release qualification. Detailed reverse-engineering research, diagnostic scripts, and ABI probes live in `Docs/` and `reverse_engineering/`.

## Security, scope, and license

- OpenShim is an unofficial community extension, not a replacement game engine. It requires a legitimate Battlezone 98 Redux installation and is not affiliated with the game's publisher or original developers.
- The release binaries are currently unsigned. SmartScreen or antivirus may warn about native proxy/hooking DLLs; **verify the release and SHA-256 hashes before deciding whether to allow a flagged file**. Do not disable antivirus globally.
- Project-owned code is licensed under **MIT**; see [LICENSE](LICENSE). This does not grant rights to the proprietary game or third-party assets.

## Credits

- **GrizzlyOne95** — primary implementation, reverse engineering, maintenance, and design
- **Piercing** — partner development, multiplayer testing, network investigation, technical collaboration
- **Kingfurykiller** — multiplayer/single-player testing, debugging, feedback, and technical assistance
- **VTrider**, **Business Lawyer**, **GoombaBZ** — technical collaboration and reverse-engineering assistance
- **Janne** — early Battlezone 98 Redux DLL-shimming and hooking research

### AI-assisted development

AI tools, including Claude Fable / Opus 5.5 and Codex, assist with code, analysis, documentation, and tests; Claude Fable notably helped resolve native destruction-chunk blockers. Maintainers review and integrate the work. Native addresses, patch sites, ABI claims, and gameplay behavior require evidence from binaries, tests, traces, or real-client testing rather than acceptance of AI output alone.
