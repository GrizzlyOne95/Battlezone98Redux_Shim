# Linux compatibility PR — notes for GrizzlyOne95

Private draft for PiercingXX to paste or adapt before opening the upstream PR.
Base: `GrizzlyOne95/Battlezone98Redux_Shim` @ OpenShim 1.0.0.13 (`0329c689`).

## Summary

Adds a **Linux developer and Proton deploy path** without changing the Windows
build story. The full `winmm.dll` still ships from **Release | Win32 / MSVC**;
Linux runs the engine-independent CTest suite and a deploy script that finds
native, Flatpak, and Snap Steam installs.

Also aligns OpenShim’s shipped networking preset with **battlezone-netcode-patch
V5.3** (`622fb74`), including the match-start governor poke that was still off
in OpenShim.

## Why

- Several of us play BZR under **Proton on Linux** (native Steam, Flatpak, and
  Snap on the same machine). The Windows deploy script does not help; we need
  path detection and a one-command deploy after building the DLL on Windows.
- The earlier laundry-bot merge claimed a MinGW cross-compile of the full shim;
  that CMake target was incomplete (two source files, MSVC-only naked forwarders
  and SEH). It is removed so the README does not lie.
- OpenShim already ported most of V5.3 in August 2025 (`a63069cc`), but
  **`GovernorStart` stayed at 0** while the netcode patch ships **`BZ_GOV_START=40000`**
  by default. That is the main remaining wire-behavior gap for parity with the
  community preset.

## Changes (by area)

### Linux / Proton

| File | Change |
|---|---|
| `scripts/steam_game_paths.sh` | **New.** Detects BZR under native, Flatpak, Snap, and extra Steam libraries via `libraryfolders.vdf`. |
| `scripts/install_linux.sh` | **New.** Pasteable `curl \| bash` installer (`--native` / `--snap`). |
| `scripts/install_windows.ps1` | **New.** Pasteable `irm \| iex` installer; no launch options on Windows. |
| `scripts/uninstall_windows.ps1` | **New.** Matching Windows one-line uninstall. |
| `setup-dev.sh` | Unchanged (already matched `setup-dev.ps1`). |
| `tests/CMakeLists.txt` + test tweaks | Unchanged intent: Linux CTest for engine-independent tests (`render_profile_resources` portability, locale skip, extra protocol/log tests). |
| `.github/workflows/build-linux-tests.yml` | **New.** Ubuntu job: configure/build/run `tests/` CTest on every PR/main push. |
| `CMakeLists.txt` (repo root) | **Removed.** Was a misleading MinGW stub, not a build of OpenShim. |
| `README.md` | Honest Linux workflow; Proton **must** set quoted `WINEDLLOVERRIDES="winmm=n,b;dsound=n,b" %command%` (Windows loads game-folder `winmm` without this). |
| `.gitignore` | `build-mingw/`; stop tracking machine-local `.venv` symlink. |

### Settings UI

The OpenShim Settings page caption was fitted into a 130px toolbar slot. The
engine ellipsizes at ~11px/glyph, so `"Page 2 of 3"` (~132px) became
`"Page 2 of..."`. Slot 3 is now 170px and the caption is set unfitted.

### Proton launch (required)

Wine/Proton will not load a game-folder `winmm.dll` unless it is in
`WINEDLLOVERRIDES`. The override string **must be quoted** because `;` splits
the Steam launch command. Same for `dsound` if the netcode patch is present.

### Netcode (V5.3 preset supersedes OpenShim defaults)

| Setting | Before | After (V5.3) |
|---|---|---|
| `GovernorStart` / `BZ_GOV_START` | `0` (disabled) | **`40000`** when `GovernorTuning = OpenShim` |
| `[Net]` tunables | Already V5.3 since `a63069cc` | Unchanged: 16000 / 320000 / 100 / 50 / 450, auto-kick 60000/2000/200/60000 |
| Duplicate suppressor | Off (`SendDup=false`) | Unchanged (correct per V5.3 revert) |

Code: `net_optimizer.cpp` defaults `GovernorStart` to **40000** when governor
tuning is on (same precedence as other keys: explicit `net.ini` / env still wins).
Shipped `net.ini` sets `GovernorStart=40000`.

Reference-only `[Net]` block: removed incorrect `MaxPingsLost=60`; V5.3 leaves
that global alone.

### Not in this PR (follow-ups)

- MinGW/Clang build of the **full** shim (needs GNU asm for naked winmm forwarders
  and a SEH strategy).
- Kernel UDP buffer sysctl tuning (netcode patch installer offers this; OpenShim
  deploy does not — same as Windows deploy).
- Workshop `net.ini` override warning (netcode patch checks this; could port later).

## Smoke test checklist (PiercingXX)

1. Windows: `Release | Win32` build → `bin/Release/winmm.dll`.
2. Linux: `./scripts/deploy_linux_proton.sh` (or `BZR_GAME_PATH=...` for one install).
3. Steam launch options: `WINEDLLOVERRIDES="winmm=n,b;dsound=n,b" %command%`
   (quotes required).
4. Launch via **each Steam variant you use** (native / Flatpak / Snap).
5. In `openshim.log`, confirm `[OpenShimNet]` lines show `govStart=40000` and
   NetTune values (16000, 320000, 100, 50, 450).
6. Host or join a short multiplayer session; confirm match start is not stuck at 4 KB/s.

## Risk / compatibility

- **Windows build and runtime:** unchanged toolchain; no MSVC project edits.
- **Networking defaults:** only affects installs that use shipped `net.ini` /
  `GovernorTuning = OpenShim` without an explicit `GovernorStart=0`. Hosts wanting
  strict stock cold-start can set `GovernorStart=0` or `GovernorTuning = Stock`.
- **Upstream merge:** squashed onto Grizzly `main` @ `9a1f9ea2` (README screenshot link from PR #105).
