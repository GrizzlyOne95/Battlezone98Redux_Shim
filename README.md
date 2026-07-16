# BZR Open Shim

Open-source clean-room replacement for closed-source shims.

Repository name: Battlezone98Redux_Shim.

**Target**: Battlezone 98 Redux v2.2.301

The clean-room shim now supports both:
- `BZR.exe` (GOG)
- `battlezone98redux.exe` (Steam)

<img width="1377" height="758" alt="image" src="https://github.com/user-attachments/assets/b1f12ee2-5e57-46df-b467-1d5c69c6426e" />

## High-Level Summary

- Standalone clean-room `winmm.dll` shim for Battlezone 98 Redux `2.2.301`, with
  live support for both GOG and Steam executables.
- Multiplayer/lobby fixes include the map-list hop-fix and refresh-position
  preservation work, BZRNET host/client integration hooks, host-side `/help`
  and `/ban` command handling, join-time ban enforcement support, ban button
  hooks, and multiplayer vehicle flag selection/generation helpers.
- Gameplay and simulation patches include the howitzer/minelayer weapon-mask
  bias fix, configurable turret aim-pitch multiplier hooks for `TurretCraft`
  and `TurretTank` so they are no longer hard-limited to the stock `0.5`
  radians behavior, target-reticle recent-hit popup filtering, under-attack
  alert throttling/toggling, global unit-voice queue policy and muting,
  engine-flame color routing, AI constructor
  death cleanup for stale scripted build claims, and sound-channel cap
  overrides for large battles.
- Single-player shell/load support includes the injected AutoSave load button
  and the restart-mission fresh-load repair so restart paths behave more like a
  true clean mission load instead of reusing stale save-style state.
- Steam compatibility work includes executable-name detection, startup settle
  polling for delayed byte sites, Steam-safe version-tag patching, Steam hook
  validation against live runtime bytes, and deliberate fallback to stock
  map-filter/sort UI while the clean-room filter port remains incomplete.
- Runtime and diagnostics work includes startup hook validation, verbose patch
  logging, Winsock buffer tuning, UDP packet reorder buffering, outbound route
  tagging, binary packet capture, shipped `net.ini` diagnostics, and bundled
  verification and session-capture scripts.
- The repo also carries guarded bridge experiments for larger native problems,
  including chunk render resolve fallback/proxy tracing and submenu-capable
  producer build menu work. Those remain explicitly scoped experiments rather
  than finished gameplay features.


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

That last point is deliberate. The in-progress experimental filter/sort hook set
was interfering with the Steam map-list UI and exposed only `All Maps` instead
of the full stock filter set. Until the remaining behavior is fully replicated,
OpenShim keeps the core map-list position fix active but does not patch the
custom filter/sort stack.

### Multiplayer ban controls

When hosting, highlight a player and click the injected `B` button to add that
player's Steam/GOG stable ID to `bans.cfg` and kick them. The same action is
available through `/ban`; `/help` lists the control. Banned identities are
checked again on lobby join events, so reconnects are removed automatically.
The ban hooks are independent of the optional BZRNET lobby integration.

### Multiplayer vehicle descriptions

The four-part vehicle-list back-port keeps `.vxt` description/control loading
scoped to the selected multiplayer map. Unrelated mod files can no longer
replace the displayed vehicle data merely because they were discovered first.
The vehicle-control refresh branch is independent of the map-list hop-fix.

### Steam-specific compatibility work

The Steam build needs a few extra guards beyond the original GOG-oriented
reverse-engineering notes:

- version-string operand sites are different on Steam
- some version-string bytes do not settle until shortly after process start
- calling `setvbuf(..., _IOLBF, 0)` during `DllMain` trips a UCRT fail-fast

The current patcher handles that by:

1. detecting the Steam executable name
2. waiting for the Steam version sites to reach their expected original bytes
3. limiting Steam version branding to the main-menu text patch so lobby-facing
   GameVersion metadata stays stock
4. leaving logger buffering at the CRT default and flushing explicitly
5. preserving the stock map-filter and sort UI until the clean-room filter port
   is complete

Current Steam multiplayer-safe status as of March 21, 2026:

- The main-menu informational label is `2.2.301 + Open Patch`.
- The shared Steam version-string patches remain disabled except for the
  main-menu-only text site, because patching the shared operand changed lobby
  GameVersion metadata, produced matching lobbies: 0 in BZLogger.txt,
  hid room/game/player lists, and removed the stock K control in the lobby
  UI.
- Steam Lobby BZRNET Integration HOST/CLIENT hooks are disabled by default.
  Re-enable them for testing with OPENSHIM_ENABLE_LOBBY_BZRNET_INTEGRATION=1.
- The ban feature is active independently of BZRNET integration: hosts get the
  `B` lobby control, `/ban` support, persistent stable-ID records in `bans.cfg`,
  and join-time enforcement.
- The Steam-safe baseline keeps stock lobby matching, adds only the independent
  ban controls to the stock lobby UI, and retains main-menu-only branding.

Steam hook-site validation status as of March 17, 2026:

- A clean `/nointro` launch of `battlezone98redux.exe` was tested with
  `winmm.dll` temporarily removed so the process stayed unpatched.
- After waiting 30 seconds at the main menu, the live Steam process matched the
  recorded GOG bytes at these addresses:
- `0x00443B35` `Chunk Render Resolve Hook`
- `0x0042BB1A` `Artillery Weapon Mask Trace`
- `0x00417C80` `Decoded Weapon Mask Carrier Bias Hook`
- `0x0046DD70` `Raw Weapon Mask Carrier Bias Hook`
- `0x004EAD78` `HoverCraft Engine Flame Emit Hook 1/2`
- `0x004EAFDF` `HoverCraft Engine Flame Emit Hook 2/2`
- `0x008791A4` `Engine Flame Control VTable Hook`
- `0x008791AC` `Engine Flame Submit VTable Hook`
- `0x005F1838` `TurretCraft Aim Pitch Multiplier`
- `0x005F561A` `TurretTank Aim Pitch Multiplier`
- `0x00494D35` `Under Attack Alert Hook 1/2`
- `0x0050E6DD` `Under Attack Alert Hook 2/2`

Practical takeaway:

- for these validated sites, Steam can use the same live addresses and
  original-byte expectations as GOG
- Steam still needs the startup settle/poll step before applying hooks
- if a Steam hook is still skipped, treat that as an OpenShim payload or
  resolver gap first, not proof that the site moved

### Ogre material-name collision guard

OpenShim installs an Ogre resource-loading listener that handles duplicate
material names instead of allowing Ogre's `ERR_DUPLICATE_ITEM` exception to
terminate the game. The policy is **latest definition wins**: existing entities
keep any material references they already hold, while future material lookups
resolve to the newly loaded definition. Collisions are recorded in
`openshim.log` with the material name.

The guard is enabled by default. For compatibility diagnosis it can be disabled
before launch with `OPENSHIM_DISABLE_OGRE_MATERIAL_COLLISION_GUARD=1` (the
`BZR_DISABLE_OGRE_MATERIAL_COLLISION_GUARD` alias is also accepted).

### Mission Briefing Asset Overrides

OpenShim can replace the stock mission-briefing backdrops and planet videos
from the currently enabled mod without modifying `BZ_ASSETS_CORE`.

Create this directory inside the enabled mod root:

```text
OpenShimBriefingAssets/
```

At startup, OpenShim reads `modEnabled.dat`, finds that child directory, and
adds it recursively as a late `FileSystem` location in Ogre's `General`
resource group. A file with the same resource name then supersedes the stock
copy. The mount is deliberately limited to this child directory; the rest of
the workshop item remains in its normal mod resource scope.

Common stock names include:

- briefing backdrops: `bd_load.bmp`, `bd_load2.bmp`, `elload.bmp`,
  `gaload.bmp`, and `singlep.bmp`
- planet videos: `elspin.ogv`, `emspin.ogv`, `jespin.ogv`, `jgspin.ogv`,
  `jispin.ogv`, `mrspin.ogv`, `stspin.ogv`, `uraspin.ogv`, and `vnspin.ogv`

Image replacements must currently retain the requested `.bmp` names and be
real BMP files. Planet videos should normally remain 15 FPS because the game
uses fixed frame-number loop points, not timestamps. See
`reverse_engineering/mission_briefing_ogv_loop_notes_20260712.md` for the
exact frame behavior.

### Multiplayer Vehicle Flags

OpenShim restores the legacy 64x32 multiplayer vehicle flags through an
Ogre billboard renderer. The feature is enabled by default; opt out with one
of:

```text
OPENSHIM_DISABLE_MP_FLAGS=1
OPENSHIM_DISABLE_MP_FLAG_UI=1
```

Place source images in a `flags` directory beside the shim. PNG, BMP, TGA,
JPG, and JPEG sources are accepted. The lobby `F` button cycles the catalog;
OpenShim resizes the selection to the legacy 64x32 monochrome mask, publishes
its 256-byte payload in player-data slot `0x0D`, and persists the selection in
`flags.cfg`.

In a match, flags are rendered above nearby eligible vehicles using the
original 100-unit range and terrain line-of-sight behavior. Each distinct
network flag remains visually unique; the local team is tinted green and
other teams red. Generated debug/network artifacts and Ogre runtime resources
are written under `flags/_generated`.

Live multiplayer validation on both host and client paths is still pending;
use the disable variables above if the renderer misbehaves in a session. The
aliases are provided for compatibility with earlier experimental builds.

### Global INI Improvements

OpenShim applies a stable set of global improvements even when a mission does
not load EXU. Copy `openshim.ini.example` to `openshim.ini` beside `winmm.dll`
to customize them.

- `[Display] ScrapPilotHud=Legacy|Stock` controls the compact legacy
  scrap/pilot text layout and its stock backing panels. EXU positioning and
  visibility calls act as mission overrides and reset to this INI baseline.
- `[Display] TargetPolicy=Default|ExplicitOnly|NeutralOnly` controls recent-hit
  target-reticle popups. `TargetReticle` remains an accepted alias.
- `[SinglePlayer] WeaponConvergence=1|0` enables converging weapon aim for
  hovercraft-derived AI craft.
- `[SinglePlayer] PlayerReticleConvergence=1|0` converges the local player's
  weapon hardpoints on the smart-reticle position after the stock aim update.
- `[SinglePlayer] SmartReticleRange=500` sets the maximum smart-reticle range
  in world units (valid range `1..10000`; stock is `200`). EXU
  `GetReticleRange`/`SetReticleRange` delegate to OpenShim when available.
- `[SinglePlayer] SmartScavengerPathing=1|0` enables path-length scrap scoring,
  unreachable-scrap cooldowns, and periodic en-route retargeting by default.
- `[SinglePlayer] Turbo=1|0` is shim-owned globally and per unit. EXU
  `Get/SetGlobalTurbo` and `Get/SetUnitTurbo` delegate to OpenShim when its
  ownership hooks are available; native EXU behavior remains the standalone
  fallback.
- `[SinglePlayer] TurretAimPitch=1|0` and `TurretAimPitchMultiplier=0.95`
  control the raised TurretCraft/TurretTank pitch range.
- `[SinglePlayer] JumpSnipeCrouch=1|0` controls the legacy crouch-on-landing fix.
- `[General] SoundChannels=256` controls the GAS sound-object cap; `0` disables
  the override.
- `[General] CustomBindsUi=1|0` controls the full native input/game-key binding
  replacement.

All `[SinglePlayer]` improvements are reconciled continuously against the live
network ID and return to stock behavior in multiplayer. Scripted EXU setters
remain higher priority for the current mission and revert to the INI baseline
when mission overrides reset. The convergence Lua APIs delegate to OpenShim
when its bridge exports are available, avoiding competing vtable patches.

### Legacy Jump-Sniping Crouch (INI-Configured, Single-Player Only)

Restores the 1.5 behavior where touching the ground with a sniper rifle
selected re-enters the crouch pose, even while the jump key is held. In stock
Redux the on-foot animation state machine checks the held-jump flag before the
sniper-selected flag, so holding jump keeps you out of the crouch after landing.

OpenShim owns the native patch: a single 11-byte, expected-bytes-guarded change
to the GOG `Person::Simulate` grounded branch. It is enabled by default for
single-player and configurable through:

```ini
[SinglePlayer]
JumpSnipeCrouch=1
```

EXU can still override it temporarily for scripted content:

```lua
local exu = require("exu")
exu.SetJumpSnipeCrouch(false)
```

Two hard guards keep it out of multiplayer: the shim refuses to apply the patch
while a network game is active (local net id non-zero) and reverts it on the
mission/network refresh, and it no-ops entirely on any build whose bytes do not
match. The net-id guard blocks it regardless of INI or script state.
See `reverse_engineering/jump_sniping_crouch_fix_20260713.md` for the full
analysis. Live host/client validation is still pending.

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

Any of the existing chunk trace/fallback env vars will also opt the chunk
experiment hooks in at startup. For a broad opt-in without a specific trace
flag, set `OPENSHIM_ENABLE_CHUNK_EXPERIMENTS=1`.

Current scope:

- validated against the GOG address `CALL 0x004E3620` at `0x00443B34`
- the matching Steam live bytes at `0x00443B35` were revalidated on March 17,
  2026 after a settled `/nointro` launch
- OpenShim still leaves this disabled on Steam until the payload path is wired
  up there cleanly

Suggested test asset:

- `agr11bda.geo` from `avtank.vdf`

The intent is to give a known good `VGEO` name a valid Redux mesh/material
pipeline, then see whether chunk child objects become visible once a valid
render handle is forced into the stock resolve/classify path.

### Chunk Mesh Self-Test And Payload Audit

OpenShim also includes a standalone Ogre payload self-test for the chunk mesh
bridge. This does not touch native chunk simulation; it only registers the same
payload resource roots and creates one visible Ogre entity from a requested
payload mesh.

Environment controls:

- `OPENSHIM_CHUNK_MESH_SELFTEST=<meshName>` creates one diagnostic entity after
  the Ogre scene manager becomes available. A bare name such as `agr11bda`
  searches the registered payload roots for `agr11bda.mesh`; a relative resource
  name such as `avtank/agr11bda.mesh` is also accepted.
- `OPENSHIM_CHUNK_MESH_SELFTEST_OFFSET=x,y,z` chooses the world position for
  the diagnostic entity. The default is `0,8,25`.
- `OPENSHIM_CHUNK_MESH_SELFTEST_SCALE=<n>` scales the diagnostic entity. The
  default is `1.0`.
- `OPENSHIM_CHUNK_PAYLOAD_AUDIT=1` adds explicit payload resolver hit/miss
  lines for observed chunk geos without requiring the mesh proxy to render.

Expected log tags:

- `[CHUNKMESH] selftest resolve ...` confirms the requested mesh mapped to an
  Ogre resource name.
- `[CHUNKMESH] selftest create ...` reports scene manager, root node, scene
  node, entity pointer, subentity count, attached object count, transform, and
  visibility intent.
- `[CHUNKMESH] payload audit hit ...` records the VDF/GEO candidates that
  resolved to a payload mesh during live chunk tracking.

### Vehicle Skinning Diagnostic

OpenShim inspects live Ogre entities reached through Redux's intact-object
bridge and reports whether their materials permit hardware skeletal animation
or force Ogre's CPU fallback. The diagnostic is enabled by default.

- Set `OPENSHIM_DISABLE_VEHICLE_SKINNING_DIAGNOSTICS=1` before launch to opt
  out. `OPENSHIM_DISABLE_SKINNING_DIAGNOSTICS=1` is accepted as a shorter
  alias.
- `OPENSHIM_TRACE_VEHICLE_SKINNING_INTERVAL_MS=<n>` controls the summary
  interval (default `5000`, clamped to `100`-`60000`).
- `OPENSHIM_TRACE_VEHICLE_SKINNING_BUDGET=<n>` limits distinct per-mesh detail
  lines (default `64`). Summary lines continue after this budget is exhausted.

`[SKINNING] mesh=...` lines include the effective mode (`gpu`,
`cpu-fallback`, `gpu+software-request`, or `cpu-requested`), Ogre visibility,
animation state, bone and matrix counts, explicit software-animation request
counts, subentity count, and material names. `[SKINNING] summary ...` lines
aggregate the active object list. Sampling runs after the stock world
render-queue update so Ogre's material-dependent decision is current, and the
diagnostic does not alter entity or animation state.

## Howitzer / Minelayer Weapon Mask Fix

There is now a Shim-side behavior patch for the hardcoded howitzer and
minelayer first-slot issue on the GOG executable.

- The patch biases `Carrier` slot `0` toward the decoded `weaponMask` target
  for `Howitzer` and `Minelayer` craft.
- Artillery AI reaches the bias helper through the existing artillery hook.
- Additional bias refreshes run through exact `weaponMask` getter hooks and the
  existing hovercraft flame path, which helps keep minelayers aligned without
  rewriting the full native AI state machine.
- The relevant Steam live bytes at `0x0042BB1A`, `0x00417C80`, and `0x0046DD70`
  were revalidated on March 17, 2026 after a settled `/nointro` launch.
- OpenShim still skips the Steam path today because those hooks do not yet get
  payloads assigned in the Steam branch.

Optional trace logging:

- Enable `OPENSHIM_TRACE_ARTILLERY_MASK=1` before launching the game.
- `[ARTYMASK]` lines in `winmm_shim.log` record `process`, `process vft`,
  `craft`, `craft vft`, raw `weaponMask`, decoded `weaponMask`,
  `modeList.enabledMask`, and `modeList.activeSlot`.
- Logging is budget-limited to the first `400` hits.

Current limitation:

- This fix has been build-validated but not yet gameplay-validated in a live
  Redux session.

## Constructor Remote-Build Cleanup Fix

OpenShim now patches the Redux `AI_UnitRemove` constructor-death branch so an
AI constructor killed mid-facility-build does not leave the old construction
claim alive for a replacement rig to satisfy from far away.

- The hook is active by default on the shared settled GOG/Steam
  `AI_UnitRemove` entry at `0x0068FC60`.
- On the affected `cc_construct_type != 0 && cc_constructing != 0` path, the
  shim now applies the missing cleanup subset from `AI_BuildingStalled`:
  `AIBuild_ConstructionEnd`, `AIBuild_ReservedAreaRemove`,
  `AI_SpentCreditRefund`, and clearing the constructor `cc_*` fields.
- OpenShim intentionally does not re-add the dead constructor to the
  unassigned-constructor pool, because that part of `AI_BuildingStalled` is
  correct for a live stalled rig, not a removed one.
- The stock stop-order helper is still called for parity, but current Redux
  resolves that site to a `RET` stub at `0x00416280`, so the effective fix is
  the construction-claim/accounting/state cleanup.
- Runtime logging uses the `[AICONSTRUCT]` tag in `winmm_shim.log`.
- The always-on success line is the `Applied constructor death cleanup
  action=death_cleanup ...` record, which captures both the pre-clear and
  post-clear `cc_*` values plus the helper entry points used for that cleanup.
- Trace mode adds budgeted structured lines with `action=` and `reason=`.
  `action=death_cleanup reason=applied` confirms the hook took the fix path,
  while `action=fallback` shows why a specific `AI_UnitRemove` call stayed on
  the stock path instead, such as `team_not_ai`, `not_constructor`,
  `construct_type_zero`, or `constructing_zero`.

Environment controls:

- `OPENSHIM_DISABLE_CONSTRUCTOR_REMOTE_BUILD_FIX=1` disables the hook.
- `OPENSHIM_TRACE_CONSTRUCTOR_REMOTE_BUILD=1` enables additional trace lines.
- `OPENSHIM_TRACE_CONSTRUCTOR_BUILD_CLEANUP=1` is accepted as an alias for the
  trace toggle.
- `OPENSHIM_TRACE_CONSTRUCTOR_REMOTE_BUILD_BUDGET=<n>` adjusts the trace budget
  from the default `32`.

Current limitation:

- This fix has been build-validated in OpenShim, but the exact gameplay repro
  still needs a fresh live Redux validation pass.

## Audio Channel Override

OpenShim now includes a native GAS max-object override to help with sound
dropouts during large battles.

- The shim defaults to a `256`-channel cap.
- Set `[General] SoundChannels=<n>` in `openshim.ini` to configure it normally.
- Set `[General] SoundChannels=0` to disable the override.
- Set `OPENSHIM_MAX_SOUND_CHANNELS=<n>` to choose a different limit.
- Set `OPENSHIM_MAX_SOUND_CHANNELS=0` to disable the override.
- `BZR_MAX_SOUND_CHANNELS` is also accepted as a legacy/testing alias.
- Values above `256` are clamped down to `256`.
- Set `OPENSHIM_TRACE_SOUND_CHANNELS=1` to log the selected GAS target, current
  `maxObjects` field, requested cap, and applied cap while the refresh thread
  is running.

Notes:

- This targets the legacy `GM->maxObjects` sound-channel cap, so it should help
  voice stealing and cutouts more than true mixer clipping/distortion.
- Current Steam runtime captures suggest the stock internal cap is `100`; the
  OpenShim default raises the available pool to the supported maximum of `256`.
- The shim locates the GAS globals at runtime. If Steam's runtime layout does
  not match the current anchor yet, the log will note that the override was
  skipped instead of patching blindly.

## Global Unit VO Policy

OpenShim owns the verified `Say -> QueueCB` unit-bark path, so duplicate/stale
queue handling and the global feedback preference work in the stock campaign
and Instant Action without EXU. Mission audio such as `misn*.wav` is excluded
by the unit-bark filename filter.

- `[Display] UnitVoFeedback=1` in `openshim.ini` keeps unit feedback enabled.
- Set it to `0` to mute likely stock unit barks globally.
- `OPENSHIM_TRACE_UNIT_VO=1` logs enqueue, drop, and queue-flush decisions.
- EXU's existing Unit VO Lua APIs bridge to the shim-owned scalar state when
OpenShim is present, so mission overrides remain higher priority and reset to
the user's global baseline when the mission ends.

## Stock Headlight Policy

OpenShim can now apply Campaign Reimagined's headlight preferences to the
stock campaign and Instant Action without EXU or the CR shader set. The shim
uses the Ogre light already attached to each game object and refreshes newly
created craft automatically.

The `[SinglePlayer]` keys in `openshim.ini` are:

- `Headlights=1|0` controls the player headlight.
- `OtherHeadlights=1|0` controls other craft/turret headlights.
- `HeadlightColor=Stock|White|Red|Green|Blue|Yellow|Cyan|Magenta|Orange|Purple|Teal|Rainbow`
  selects the player color. Custom `r,g,b` triples are also accepted.
- `HeadlightBeam=Stock|Focused|Wide` selects the player spotlight cone.

The named colors and beam strengths match the campaign PDA values. OpenShim
captures the original Ogre light state before changing it and restores that
state when the feature is gated off. It never applies in a network game and
stands down whenever EXU is loaded, so scripted campaign controls remain
authoritative. Set `OPENSHIM_TRACE_HEADLIGHTS=1` for periodic player/touched
light counts.

OpenShim also repairs the stock `draw_light` running-light lifecycle. Emission
lights now remain dormant while a craft is empty, become visible again when a
pilot re-enters, and continuously pulse between their stock start/end colors
at the configured rate. Set `OPENSHIM_DISABLE_EMISSION_LIGHT_FIX=1` to opt out
for compatibility testing.

## Lua Music Bridge

OpenShim exports a small music bridge through the `winmm.dll` proxy, and EXU can
resolve those exports for Lua scripts:

- `OpenShimSetMusicTrack(int index)`
- `OpenShimStopMusic()`
- `OpenShimPauseMusic()`
- `OpenShimResumeMusic()`
- `OpenShimGetMusicTrack(int* outIndex)`

EXU exposes matching Lua helpers:

- `exu.SetMusicTrack(index)`
- `exu.StopMusic()`
- `exu.PauseMusic()`
- `exu.ResumeMusic()`
- `exu.GetMusicTrack()`

Current native validation status:

- `SetMusicTrack` calls the decompilation-identified native `StartMusic(long,
  int)` entry at `0x00406670` and logs `[MUSIC]` success/fault lines.
- Stop, pause, and resume exports currently fail closed and log once because
  their native soundtrack control targets are not yet validated. They exist so
  Lua scripts can probe support without crashing or changing `StartSound` /
  `AudioMessage` behavior.

## Co-op Mission Sync Helper

The co-op campaign path should stay script-level first. A standalone helper is
provided in the EXU repo at `examples/openshim_coop_sync.lua`.

- Missions choose their own packet type and forward `Receive(from, type, ...)`
  into `sync:receive(from, type, ...)`.
- Host-side helpers broadcast objective text, objective markers, mission state,
  and delayed win/loss calls through stock Lua `Send`.
- Object existence and world simulation remain native/distributed; mission UI
  and objective state must be explicitly synchronized.

## Deferred Native Experiments

These items remain deliberately gated until their exact live bytes/function
bodies are validated on a launchable machine:

- Mission briefing scroll cutoff: the RE note points at `FUN_007ce110` and
  `FUN_007ce6d0`, but the currently loaded Redux image does not expose a
  usable executable-looking body at the noted address, so OpenShim does not
  patch it yet.
- Raw input trace: keep this as a future `OPENSHIM_TRACE_RAW_INPUT=1`
  logging-only hook after `ProcessMouseRawInput` bytes are revalidated.
- Bomber stand-off: keep the first pass as `OPENSHIM_TRACE_BOMBER_RANGE=1`
  instrumentation before enabling any `OPENSHIM_ENABLE_BOMBER_STANDOFF=1`
  behavior change.

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
- latest `BZLogger.txt` interval line when present, so a shipped `net.ini`
  test profile can be confirmed quickly

If buffer logging is enabled, the game's `logs` folder will also receive:

- `bz_buffer_log.bin`
- `bz_buffer_log.meta.txt`
- `bz_relay_control.jsonl` when relay capture is enabled

## LLDB Recovery

If the local LLVM `lldb.exe` crashes on startup because it cannot find a
complete Python 3.11 runtime, run:

`powershell -ExecutionPolicy Bypass -File .\install_lldb_shim.ps1`

The script installs user-level `lldb.cmd` and `lldb-dap.cmd` wrappers in
`<USER_HOME>\bin`, points them at the LLVM debugger binaries, and supplies
the Python runtime from the Android Studio NDK LLDB bundle when present.

## Netcode Reorder Controls

The Windows shim now includes the first-pass UDP packet resequencer from the
netcode investigation work. It runs inside the existing `WSARecvFrom` hook and
holds small out-of-order bursts briefly so they can be delivered back to the
game in sequence.

Netcode patching in OpenShim is maintained by `GrizzlyOne95`, with `Piercing`
providing captures, validation, and technical collaboration on the multiplayer
investigation path.

Configure it through `net.ini` next to the game executable:

```ini
[OpenShimSocket]
Dscp=46
EnablePacketReorder=1
PacketReorderWindowMs=100
PacketReorderMinWindowMs=5
EnableAdaptivePacketReorder=1
EnablePacketReorderWake=1
PacketReorderDepth=8
PacketReorderPeers=32
PacketReorderDrainCap=96
LogPacketReorder=1
SendDup=0
DupDelayMs=25
DupMaxPps=40
GovernorStart=0
GovernorScan=0
AutoKickRelax=1
AutoKickStart=60000
AutoKickPing=2000
AutoKickLoss=200
AutoKickTime=60000
EnableBufferLog=0
EnableRelayCapture=0
BufferLogPayloadBytes=32
BufferLogRingRecords=65536
BufferLogSocketId=0
BufferLogPeer=
```

Notes:

- `EnablePacketReorder=1` enables the reorder buffer for synchronous UDP recv.
- `PacketReorderWindowMs` is the adaptive ceiling and is clamped to `5`-`200` ms.
- `PacketReorderMinWindowMs` is the adaptive floor; clean links start at `5` ms.
- `EnablePacketReorderWake=1` starts a wake helper so held packets release even after the hook drains the socket.
- `PacketReorderDepth` is clamped to `1`-`8`.
- `PacketReorderPeers` is clamped to `1`-`32`.
- `PacketReorderDrainCap` is clamped to `1`-`128`.
- `Dscp=46` marks IPv4 UDP packets as EF priority (`0` disables).
- `SendDup=1` enables deprecated duplicate-send testing with `DupDelayMs` and `DupMaxPps`; leave it off for normal play.
- `GovernorStart` maps to `BZ_GOV_START`; `0` disables the data-only 4000 B/s cold-start lift.
- `AutoKickRelax=1` defaults the host-side data patch to start `60000`, ping `2000`, loss `200`, and time `60000`.
- `LogPacketReorder=1` enables detailed reorder diagnostics in `openshim.log`.
- `EnableBufferLog=1` writes a binary send/receive capture to
  `logs\bz_buffer_log.bin` plus a small metadata sidecar file.
- `EnableRelayCapture=1` enables the complete `/iprelay` investigation profile:
  full 2048-byte UDP datagrams in both directions, overlapped/IOCP receive
  completion capture, and route-related WebSocket JSON in
  `logs\bz_relay_control.jsonl`. The control logger whitelists LAN/WAN/P2P route
  messages and never writes `Authorization` messages or platform tickets.
- `BufferLogPayloadBytes` is clamped to `8`-`2048`.
- `BufferLogRingRecords` is clamped to `1024`-`1000000`.
- `BufferLogSocketId` limits binary capture to one OpenShim socket id.
- `BufferLogPeer` limits binary capture to one IPv4 peer, optionally with a
  port, for example `203.0.113.42:17770`.
- Environment variables `BZ_REORDER`, `BZ_REORDER_WINDOW_MS`,
  `BZ_REORDER_MIN_MS`, `BZ_REORDER_ADAPT`, `BZ_REORDER_WAKE`,
  `BZ_REORDER_DEPTH`, `BZ_REORDER_PEERS`, `BZ_REORDER_DRAIN`,
  `BZ_DSCP`, `BZ_SEND_DUP`, `BZ_DUP_DELAY_MS`, `BZ_DUP_MAX_PPS`,
  `BZ_GOV_START`, `BZ_GOV_SCAN`, `BZ_AUTOKICK_RELAX`,
  `BZ_AUTOKICK_START`, `BZ_AUTOKICK_PING`, `BZ_AUTOKICK_LOSS`,
  `BZ_AUTOKICK_TIME`,
  `OPENSHIM_REORDER`, `OPENSHIM_REORDER_WINDOW_MS`,
  `OPENSHIM_REORDER_MIN_MS`, `OPENSHIM_REORDER_ADAPT`,
  `OPENSHIM_REORDER_WAKE`, `OPENSHIM_REORDER_DEPTH`,
  `OPENSHIM_REORDER_PEERS`, `OPENSHIM_REORDER_DRAIN`,
  `OPENSHIM_DSCP`, `OPENSHIM_SEND_DUP`, `OPENSHIM_DUP_DELAY_MS`,
  `OPENSHIM_DUP_MAX_PPS`, `OPENSHIM_GOV_START`, `OPENSHIM_GOV_SCAN`,
  `OPENSHIM_AUTOKICK_RELAX`, `OPENSHIM_AUTOKICK_START`,
  `OPENSHIM_AUTOKICK_PING`, `OPENSHIM_AUTOKICK_LOSS`, and
  `OPENSHIM_AUTOKICK_TIME` override the `net.ini` values for testing.
- Environment variables `BZ_BUFFER_LOG`, `BZ_BUFFER_LOG_BYTES`,
  `BZ_BUFFER_LOG_RING`, `BZ_BUFFER_LOG_SOCKET`, `BZ_BUFFER_LOG_PEER`,
  `OPENSHIM_BUFFER_LOG`, `OPENSHIM_BUFFER_LOG_BYTES`,
  `OPENSHIM_BUFFER_LOG_RING`, `OPENSHIM_BUFFER_LOG_SOCKET`, and
  `OPENSHIM_BUFFER_LOG_PEER` override the buffer-capture settings for testing.
- `BZ_RELAY_CAPTURE=1` or `OPENSHIM_RELAY_CAPTURE=1` enables the dedicated
  relay profile without modifying `net.ini`.
- The reorder path is bypassed for overlapped or async `WSARecvFrom` calls.
- Direct `recvfrom` and `FIONBIO` mode changes are also captured when the
  binary buffer log is enabled, which helps correlate nonblocking socket
  transitions with packet loss or reorder bursts.
- Outbound route diagnostics now tag `connect` / `WSAConnect` / `sendto` /
  `WSASendTo` traffic in `openshim.log` as `bzrnet_ws`, `bzrnet_probe`,
  `bzrnet_relay`, `p2p_lan`, or `p2p_candidate` so relay fallbacks and direct
  peer traffic are easier to distinguish.
- The game uses overlapped/IOCP receives on native Windows; the reorder path
  still bypasses async `WSARecvFrom` calls to avoid the standalone patch's old
  launch-freeze failure mode.

## Test Net.ini

The repo now ships a diagnostic [`net.ini`](net.ini)
profile. Copy it next to the game executable to raise the default multiplayer
update rate and greatly relax auto-kick thresholds while you are diagnosing
packet loss.

Key changes in the shipped profile:

- `MaxPing=450`
- `MinBandwidth=16000` instead of the common `4000` workshop setting
- `MaxBandwidth=320000`
- `AutoKickStart=60000`
- `AutoKickPing=750`
- `AutoKickLoss=75`
- `AutoKickTime=45000`
- `MaxPingsLost=60`

After launching multiplayer once, check `BZLogger.txt` for a line like
`Net: Bandwidth usage now set to 16000, Interval ... ms`. The current target is
`33 ms` or lower.

## Buffer Capture Workflow

For Windows session bundles, use [`buffer_logger_windows.ps1`](buffer_logger_windows.ps1):

```powershell
.\buffer_logger_windows.ps1 -Action Start
.\buffer_logger_windows.ps1 -Action Mark -Message "loss spike during combat"
.\buffer_logger_windows.ps1 -Action Stop
```

For a forced-relay protocol capture, run:

```powershell
.\buffer_logger_windows.ps1 -Action Start -RelayCapture
# Use the generated Steam launch option or launch_with_buffer_log.cmd.
# Reproduce with both players, exit the game normally, then:
.\buffer_logger_windows.ps1 -Action Stop
```

Relay mode automatically selects 2048 payload bytes, a 32768-record ring, sets
`BZ_RELAY_CAPTURE=1`, and appends `/iprelay` to the generated launch command.
Both clients should use the generated relay launch command. Exit normally so
the in-memory ring is flushed before collecting the bundle.

Optional filters for tighter captures:

- `-SocketId <n>` captures only one OpenShim socket id
- `-PeerFilter 203.0.113.42:17770` captures only one IPv4 peer

`Stop` writes a zipped bundle under `test_bundles\` with `openshim.log`,
`BZLogger.txt`, `bz_buffer_log.bin`, `bz_buffer_log.meta.txt`, the optional
`bz_relay_control.jsonl`, and the active `net.ini` when present. Relay bundles
contain peer addresses, player identifiers, and raw relay datagrams; exchange
them privately and do not commit them.

Generate a redacted shape/count summary without printing endpoints or payloads:

```powershell
python reverse_engineering/analyze_relay_capture.py `
  test_bundles/<session>/bz_buffer_log.bin
```

## Deep Diagnostics Workflow

For broader Windows session bundles, use [`tester_diag_windows.ps1`](tester_diag_windows.ps1):

```powershell
.\tester_diag_windows.ps1 -Action Start
.\tester_diag_windows.ps1 -Action Mark -Message "relay fallback after join"
.\tester_diag_windows.ps1 -Action Stop
```

Optional targeting:

- `-PingTarget 1.1.1.1` changes the baseline ping timeline target
- `-PeerPingTarget 203.0.113.42` captures a second ping timeline for a known peer
- if `-PeerPingTarget` is omitted, `Stop` tries to infer likely public peers
  from the captured socket timeline and records them in `peer_candidates.txt`

The trimmed workflow captures:

- route snapshots at start and stop
- adapter overview and adapter statistics
- baseline ping timeline and optional peer ping timeline
- repeated `netstat` socket snapshots for peer inference
- optional `netsh trace` output when the shell has sufficient rights
- `openshim.log`, `BZLogger.txt`, optional buffer-log files, `net.ini`,
  `multi.ini`, and `verify_windows.ps1` output

Use `buffer_logger_windows.ps1` separately when you specifically need the
binary recv-path capture, and use `tester_diag_windows.ps1` when you need the
broader session-level networking bundle.

## Testing The Chunk Experiment

1. Build `bin\Release\winmm.dll`.
2. Deploy it next to the game executable.
   For Steam, use `launch_steam_chunk_force_geo.cmd` from the repo root to copy
   the latest build into the game directory and launch with the chunk test
   environment variables enabled.
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
7. Inspect `openshim.log` or `winmm_shim.log` for lines beginning with
   `[CHUNK]`.

Current logging note:

- chunk experiment diagnostics are mirrored into both `openshim.log` and
  `winmm_shim.log`
- older builds may only have the chunk diagnostics in `winmm_shim.log`
- the Steam build delays the `CreateChunk` / `CreateChunklet` detours until the
  executable bytes have settled, then logs whether the creator hooks are active

Expected log signals:

- `Force-first-geo fallback: enabled`
- `Forced geometry entry ...`
- `Create-path hooks: enabled`
- `CreateChunklet ... createdGeomName=chunk1|chunk2` for generic hit chunklets
- `CreateChunk ...` for real craft-fragment repurposing during death effects

If the hook never logs forced geometry for destroyed objects, the failure is
probably earlier than active-handle selection. If it does log forced geometry
but chunks still do not render, the next failure point is likely downstream in
render-class handling or Ogre proxy creation.

### Chunk Spawn Trace Notes

The shim now includes additional chunk-spawn instrumentation that is meant to
answer two different questions:

1. is Redux creating generic stock chunklets or real repurposed craft pieces
2. if the fragment is a real craft piece, can OpenShim still identify the
   originating VDF node after `CreateChunk` mutates the object

Relevant log families:

- `[CHUNKSPAWN]` logs the native `CreateChunk` and `CreateChunklet` paths
- `[CHUNKPROXY]` tracks the active runtime chunk objects after creation
- `[CHUNKEFFECT]` samples the live `ChunkEffect` manager entries
- `[CHUNKMESH]` reports payload mesh root registration, Ogre entity creation,
  payload assignment, and payload-resolution misses

Important field meanings:

- `srcGeomName` / `createdGeomName`
  direct runtime GEO identity when Redux still exposes a readable name
- `srcVdf`
  OpenShim's current best-effort VDF candidate list for the source fragment
- `[CHUNKSPAWN]   vdf ...`
  expanded source, parent, sibling, and child candidate names when any are
  available

Current Steam implementation details:

- creator hooks are installed only after settled-byte verification
- direct runtime GEO names are inconsistent across real craft fragments
- to reduce that inconsistency, OpenShim keeps a throttled intact-object cache
  while vehicles are still alive, then reuses that cached `obj76 -> mesh -> VDF`
  identity later in the death path
- `CreateChunk` bindings are keyed by the live `_OBJ76*`, not by vehicle name,
  so multiple identical units can fragment independently
- the intact-object cache refreshes at most once per second and currently caps
  itself at `1024` game objects and `256` object-tree nodes per object per pass

Practical interpretation:

- `CreateChunklet` plus `chunk1` / `chunk2` still means generic stock debris
- `CreateChunk` means Redux is repurposing a real child object from the craft
- decompiled 1.5 and unpacked Redux code agree on that split: `CreateChunk`
  changes an existing child `_OBJ76` to class/type `53`, while `CreateChunklet`
  allocates a new generic debris object from the chunk template list
- real vehicle pieces such as `AGR11BDA` should therefore be rendered by
  mirroring the native `ChunkEffect` entry transform, not by replacing native
  chunk simulation or treating the piece as a stock `chunk1` / `chunk2`
  template
- `caller` / `callerRva` on `[CHUNKSPAWN]` lines identify the native caller site
  that reached `CreateChunk` or `CreateChunklet`, which is useful when the
  upstream fragment-stage function has not been hooked directly yet
- `callerTag`
  a conservative OpenShim label for specific recurring caller RVAs observed in
  live Steam traces
- `path`
  an OpenShim classification for a known create-route signature, such as the
  observed Steam generic chunklet chain or observed Steam fragment-create chain
- `[CHUNKSPAWN]   bt ...`
  a short captured native backtrace for the same create event, useful when the
  immediate caller alone is not enough to distinguish a fragment walker from a
  generic debris helper
- `[CHUNKSPAWN]   stack ...`
  for `CreateChunk`, a raw snapshot of the native caller stack words at the
  fragment-creation callsite
- `[CHUNKSPAWN]   stackObj ...`
  for `CreateChunk`, OpenShim's best-effort decode of object-looking stack
  words, including any cached mesh or VDF identity already known for those
  fragment pointers
- when `srcVdf` resolves to names like `AGR11TUR`, `AGR11BDA`, or
  `Agr11nrr`, OpenShim has successfully matched that runtime fragment back to
  the source VDF tree
- when `srcVdf=<none>`, the fragment is still real, but the available runtime
  metadata was not unique enough for a safe name match in that run

Legacy validation as of March 26, 2026:

- a live legacy `bzone.exe` Frida trace against `avtank` destruction confirmed
  the expected craft-death chain:
  `Craft::Explode -> FullFragmentObject / PartialFragmentObject -> CreateChunk`
  with additional `CreateChunklet` calls around the same event
- that result is recorded in
  [`reverse_engineering/chunk_fragment_path_20260326.md`](<USER_HOME>\Documents\GIT\BZR-OpenShim\reverse_engineering\chunk_fragment_path_20260326.md)
  and the helper script used for the live legacy trace is
  [`reverse_engineering/legacy_bzone_chunk_trace.js`](<USER_HOME>\Documents\GIT\BZR-OpenShim\reverse_engineering\legacy_bzone_chunk_trace.js)
- practical takeaway: if a Steam `avtank` death only logs `CreateChunklet`
  and never logs `CreateChunk` from a fragment-style caller site, the blocker
  is upstream path divergence, not uncertainty about how legacy fragmentation
  works
- newer Steam traces have also identified a recurring fragment-create parent
  chain rooted at `0x00492565 <- 0x004924F5 <- 0x004AC5E0`, so OpenShim now
  tags those frames on `[CHUNKSPAWN]` backtraces for faster comparison against
  live Frida runs
- an automated April 2, 2026 `misn06.bzn /edit` repro now confirms that the
  clean shim logs preserve the same live craft root Frida sees for the
  `svtank` fragment batch, including `selectedOdf=svtank`, `rootOdf=svtank`,
  `rootGameObj=0x029E5320`, and a stable `ownerObj`
- the same automated repro is driven by
  [`run_misn06_auto_capture.ps1`](<USER_HOME>\Documents\GIT\BZR-OpenShim\reverse_engineering\run_misn06_auto_capture.ps1)
  using a `150ms` load-phase `SPACE` press after the first Redux window appears
- current builds now prefer runtime ODF identity over misleading inline owner
  strings, which removed the old `RocketTankFriend` fallback from the validated
  `svtank` fragment path
- this means the chunk mesh bridge can now key off `root + rootGameObj +
  ownerObj + piece VDF/geo`, which is the intended per-instance identity path
  for missions with many identical craft alive at once

Current payload-mesh path:

- when `OPENSHIM_DISABLE_CHUNK_MESH_PROXY` is not set, OpenShim tries to spawn
  a mesh proxy for each live chunk whose source piece resolves to a payload
  mesh
- the intended lookup order is `meshBase/GeomName.mesh` first, then
  `GeomName.mesh` as a flat fallback under the registered chunk payload roots
- example: `avtank` source mesh plus `AGR11BDA` source fragment resolves to
  `avtank/AGR11BDA.mesh` first, then `AGR11BDA.mesh`
- the payload proxy is keyed by the mutated chunk `_OBJ76*` and copies that
  native chunk object's world transform each frame, so the payload follows the
  native fragment velocity, bounce, and spin instead of running a second
  physics path
- mesh proxy visibility is handled only by the payload mesh path; the older
  debug/billboard path no longer hides the same scene node after Ogre creates a
  chunk entity
- the unfinished manual render-queue submission experiment is compiled out for
  now; the active path relies on a normal root-scene-node child plus Ogre entity
  visibility updates

Useful failure signatures:

- `[CHUNKMESH] payload resolve miss ...`
  payload mesh candidates were built successfully, but none of the candidate
  files existed under the registered payload roots
- `[CHUNKMESH] Entity creation failed ...`
  the payload mesh resolved, but Ogre could not create the proxy entity
- `[CHUNKPROXY] release ... reason=transform-read-failed`
  the chunk proxy lost access to the native chunk transform before expiry

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

- set `OPENSHIM_ENABLE_PRODUCER_BUILD_MENU=1` before launching the game
- copy `openshim_producer_build_menus.ini.example` next to the game EXE as
  `openshim_producer_build_menus.ini`
- set root tokens under `[ProducerBuildMenus]` for:
  - `Recycler`
  - `Factory`
  - `Armory`
  - `ConstructionRig`

The multiplayer vehicle flag-selection UI is also treated as experimental for
release builds now. Set `OPENSHIM_ENABLE_MP_FLAG_UI=1` before launch if you
want the lobby `F` button and flag-generation helpers visible.

The custom input-binding replacement UI is also testing-only for now. Set
`OPENSHIM_ENABLE_INPUT_BINDING_UI=1` before launch if you want OpenShim's
replacement keybind screen instead of the stock controls screen.

Current scope and cautions:

- GOG-only for now
- config-driven by producer type, not by ODF field yet
- this is the bridge experiment, not the finished submenu feature
- final submenu navigation and leaf-build handoff still need in-game validation

## ExtraUtilities Feature-List Compatibility Fixes

The July 2026 audit of the requested `FeaturesToLookInto.txt` items added these
default-on, fail-safe Redux 2.2.301 repairs:

- raw mouse input is enabled unless the stock `norawinput` command-line option
  or `OPENSHIM_DISABLE_RAW_MOUSE_INPUT=1` is present; native consumers can use
  `OpenShimGetRawMouseInputEnabled` and `OpenShimSetRawMouseInputEnabled`
- an APC targeting an ally falls through to its stock nearby-enemy scan when
  deploying soldiers (`OPENSHIM_DISABLE_APC_DEPLOY_FIX=1` opts out)
- a tug restored with cargo starts the stock deploy animation/state transition
  so later deployment drops that cargo
  (`OPENSHIM_DISABLE_TUG_CARGO_FIX=1` opts out)
- undeployed howitzers suppress only the stock recent-sniper target override
  until their deployment state is complete; follow/go behavior remains stock
  (`OPENSHIM_DISABLE_HOWITZER_DEPLOY_FIX=1`)
- zero/non-finite `MagnetClass` range values bypass only the unsafe attraction
  calculation while retaining base mine simulation
  (`OPENSHIM_DISABLE_MAGNET_ZERO_RANGE_FIX=1`)
- ScriptUtils `CanBuild` and `IsBusy` now accept the base `PROD` class signature
- mission briefing/archive scrolling uses the game's guarded scroll callbacks,
  removing the need for trailing blank lines
  (`OPENSHIM_DISABLE_BRIEFING_SCROLL_FIX=1`)

The splinter undead fix (46A) and constructor remote-build cleanup (47) were
already present. Detailed per-item status, including the items that still need
runtime mapping, is in
`reverse_engineering/features_to_look_into_requested_audit_20260714.md`.

## Debug Metadata Inspection

If `llvm-pdbutil` is unavailable or blocked by local DIA/COM registration, use:

`python reverse_engineering/inspect_pdb.py --pe bin\Release\winmm.dll --pdb bin\Release\winmm.pdb --list-streams --show-paths`

The script reads PE RSDS records and PDB MSF metadata directly and can also
search raw PDB strings with repeated `--find` regex arguments.

## License

MIT - see LICENSE file

## Credits

- `GrizzlyOne95` for primary implementation, maintenance, and ongoing clean-room patch work across the shim.
- `Piercing` for technical assistance, multiplayer testing, and netcode investigation support.
- `VTrider` and `Business Lawyer` for technical assistance and collaboration building this DLL patch.
- `Janne` for the original work learning how to shim and hook DLLs into BZR.

