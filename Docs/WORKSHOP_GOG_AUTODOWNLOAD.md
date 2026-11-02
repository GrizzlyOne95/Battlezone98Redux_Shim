# GOG Workshop auto-download: findings and plan

Status: scoped, not implemented (2026-11-02).
Addresses are from the GOG `battlezone98redux.exe`. They were checked against the ghidrecomp corpus (`Battlezone_Source\BZ1\Redux\openshim_re_corpus\bzr_gog_best_effort`) and live Ghidra.

## Goal

When a GOG player joins a lobby whose host uses a Steam Workshop map, OpenShim fetches the map automatically. Steam players already get this from the engine.

## How the engine handles Workshop maps today

### Workshop manager

- The manager is a singleton at `DAT_00945478`. Its getter is `FUN_00764790` (`Workshop::GetManager` in `scripts/patches.json`).

| vtable slot | cWorkshopSteam (`0x0089D054`) | cWorkshopGoG (`0x0089CFD8`, written by ctor `FUN_00773920`) |
|---|---|---|
| 0 | dtor | dtor `0x00773940` |
| 1 `ensureItem(idString, bool download)` | `0x00773D80` | `0x00773990` (stub: `return 1`) |
| 2 content root | | `0x007739A0` (returns string `DAT_02cecf80`) |
| 3 `isReady` | `0x00773C40` | `0x00461C90` (stub: `return 1`) |

The GOG vtable data slots to patch are `0x0089CFDC` (slot 1) and `0x0089CFE4` (slot 3).

### Steam slot 1 (`0x00773D80`)

1. Parses the ID in base 10.
2. Calls `ISteamUGC::GetItemState` (vtable `+0xE8`); ready means `(state & 0x28) == 0`.
3. If the item isn't downloading and `download` is true, calls `DownloadItem` (vtable `+0xF4`, high priority).
4. Retries a given item at most once every 300 s.

### Install completion

- The Steam callbacks `FUN_00773BD0` and `FUN_00773C10` fire for app `0x49A52` (301650). They set `workshop+0x7C = 2`, or `1` if the result failed.
- The tick runs `FUN_00764A10` → `FUN_0076EE40`. When `+0x7C > 1` it:
  - rebuilds the map/mod list live (`FUN_007682A0`);
  - re-evaluates lobby readiness (`FUN_00743CB0`).
- **This is the hook point:** any code that finishes installing a mod can set `+0x7C = 2` and get the engine's own rescan and readiness recheck.

### MP join path

1. `CNetGameLobby::PopulateLobbyFromData` (`FUN_00743F40`) reads the lobby key `gameSettings`. `FUN_0073C450` parses it into the map name (`+0xDC`) and its Workshop ID (`+0xFC`).
2. `FUN_00742EE0` calls workshop slot 1 (ensure, download=true) and stores readiness at lobby `+0x48`.
3. `FUN_00743CB0` recomputes readiness into `+0xF4`.
4. On GOG the stubs return true, so a missing map is reported ready.

### Transports

Every OpenShim transport carries `gameSettings` verbatim:
- BZRNet
- the no-auth LAN model (#660, `src/network/embedded_lan_model.cpp`, `SetLobbyData` → `OnLobbyDataChanged`)
- the Steam tunnel (#646)

So a GOG joiner already receives the Workshop ID. No new lobby key is needed.

### Mounting: no restart needed

- Mods mount at each mission start, not at boot. `FUN_007647C0` → `FUN_0076E6C0(mode, mapname)` is called from:
  - Starting Game Simulator `FUN_00616FC0`
  - Load Game `FUN_004FDDC0`
  - Auto Load `FUN_004FDAB0`
  - the loading UI `FUN_005D4980`
- In MP (`mode != 0`), `FUN_0076E4A0` classifies the mods. `FUN_0076B350` then mounts every installed MP-safe mod (`+0x90`) into the Ogre group `Modable`, cached per map name (guard at `+0x8C`/`+0x90`).
- The map list scan `FUN_007682A0` covers three roots:
  - `\packaged_mods`
  - the slot-2 Workshop root
  - a `FUN_0041F870` path (OpenShim's GOG `mods\<id>`)
- It calls `FUN_0076C310` for each `.ini`/`.bzn`/`.des`/`.bmp`.
- A mod installed while in the lobby is listed after the rescan and mounted at launch. No restart or rejoin is needed.

### The MP-safe rule depends on file content

- `FUN_0076E020` checks every file in a mod against the whitelist that `FUN_00767A30` builds:
  `*.wav *.ogg *.ini *.inf *.jpg *.txt *.stb *.des *.dds *.png *.sta *mod.material`
- Any other file logs `UNSAFE %s : %s` and clears `+0x90`.
- Only the map's own mod gets mounted for the map. Other mods holding meshes or ODFs are skipped in MP.

## Plan (about 2.5–3.5 days)

1. Replace the two cWorkshopGoG vtable slots.
   - Add `patches.json` entries with vtable-identity signatures, plus one runtime check on the Steam exe.
   - New slot 1: if `mods\<id>` exists, return ready. Otherwise queue an async fetch and return not ready.
   - New slot 3: return false while a fetch is in progress.
2. Fetch with anonymous SteamCMD into a staging folder, then move the result to `mods\<id>`:
   `steamcmd +force_install_dir <cache> +login anonymous +workshop_download_item 301650 <id> +quit`
   - Prior art: `Battlezone_ModEngine` `steamcmd_utils.py` and `bz_mod_engine.py` `ensure_steamcmd`.
3. When the fetch finishes, set `workshop+0x7C = 2` on success, or `1` on failure. The engine then rescans and rechecks readiness by itself.
4. Steam users are unaffected; their native path stays as it is. Per "Steam = GOG at runtime", the code is not gated on `g_IsSteamExe`; it only replaces the cWorkshopGoG vtable.

### SteamCMD provisioning (decided)

- **Off by default.** It's enabled in the OpenShim settings UI. When enabled, OpenShim stages and runs SteamCMD.
- An existing `steamcmd.exe` path in `openshim.ini` is respected (for example a ModEngine install).
- SteamCMD runs with no window and a timeout, because it sometimes hangs. On its first run it updates itself, which takes about a minute.
- The decision on bundling versus fetching is in "SteamCMD distribution" below.

### SteamCMD distribution: fetch it from Valve, don't bundle it

**What Valve's terms allow.**
- The Steam Install Agreement that ships with SteamCMD (the Linux text, read via [Debian's copyright file](https://tracker.debian.org/media/packages/s/steamcmd/copyright-020180105-5)) allows redistribution under §1.B, on these conditions:
  - the program must be distributed whole and unmodified, and not integrated with other software;
  - no fee may be charged;
  - the license must be included and the user must accept it.
- Valve can revoke that permission at any time (§3).
- The Windows `steamcmd.zip` contains only `steamcmd.exe` and no license file. A shim that runs SteamCMD automatically arguably "integrates" it. So bundling is legally risky, and a bundled copy would go stale anyway, because SteamCMD updates itself.

**What other tools do.**
- These fetch SteamCMD from Valve at install or run time:
  - WindowsGSM (`Installer/SteamCMD.cs`)
  - LinuxGSM (`core_steamcmd.sh`)
  - the cm2network/steamcmd Docker image
  - ModEngine (`ensure_steamcmd`)
- The Debian package redistributes SteamCMD, but it shows a license prompt.

**URLs.** Both of these served the same 774,825-byte bootstrapper on 2026-11-02:
- `https://media.steampowered.com/installer/steamcmd.zip` (primary)
- `https://steamcdn-a.akamaihd.net/client/installer/steamcmd.zip` (fallback)

**Implementation.**
- Download SteamCMD on first use, and only when the setting is enabled.
- Skip the download if `steamcmd.exe` is already present.
- Run it unmodified, as a separate process.

No source says that anonymous Workshop downloads break Valve's terms. Items that require ownership or a login fail with a "No subscription" error. That error is unverified; the Valve wiki page couldn't be fetched.

## Live checks still needed

The game has not been launched for any of this.

- Whether a not-ready map (lobby `+0x48`/`+0xF4`) actually stops the GOG joiner from readying up or launching, and what happens today when a GOG joiner launches without the map.
- Whether `FUN_0076B350`'s per-map cache needs clearing after a mid-session install.
- The runtime value of `DAT_02cecf80` (the slot-2 root) on GOG.
- The Steam-exe runtime check for the patched addresses.

## Dropped: Workshop dependencies (BZCC-style)

**Decision: not worth doing.**
- Authors would have to type the dependency keys into their ini by hand.
- BZR's official uploader has no dependency field.

Kept for reference:
- BZCC's `FUN_00432108` maps `modType` `config`=0, `addon`=1, `asset`=2.
- Only `config` mods read `[WORKSHOP] modName` and `assetDependencies` (comma-split).
- The host's advertised list (`FUN_0060AB23`) is the active config mod plus all its dependencies.
- If this is revisited:
  - Dependencies would need mounting by OpenShim, because of the MP-safe rule above.
  - BZR has no host-advertised mod list.

## Alternatives considered for the fetch

| Option | Verdict |
|---|---|
| Plain HTTP via the Steam Web API | Impossible: `GetPublishedFileDetails` returns an empty `file_url` for these items. |
| DepotDownloader (GPL-2.0, .NET) | Works anonymously, but it's bigger than SteamCMD and adds nothing. |
| A native Steam download client inside the shim | Weeks of work. No. |
| Host sends files to the joiner over the lobby transport | No Steam needed and works on LAN, but the host must run OpenShim. Needs a file channel; about 3–5 extra days. Possible later for LAN/offline. |
