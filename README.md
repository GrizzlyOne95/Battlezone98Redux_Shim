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
  alert throttling/toggling, engine-flame color routing, AI constructor
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
- The current active patch list also leaves these multiplayer experiments out
  until they can be reintroduced safely: Custom Command /help Handler,
  Joiner Event Hook, Ban Button Hook 1/2, and Ban Button Hook 2/2.
- The Steam-safe baseline for now is hop-fix/map-refresh fixes on, stock lobby
  matching behavior, stock lobby controls, and main-menu-only branding.

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
  action=death_cleanup ...` record, which captures the pre-clear `cc_*` values
  and the helper entry points used for that cleanup.
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
- latest `BZLogger.txt` interval line when present, so a shipped `net.ini`
  test profile can be confirmed quickly

If buffer logging is enabled, the same game folder will also receive:

- `bz_buffer_log.bin`
- `bz_buffer_log.meta.txt`

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

Netcode patching in OpenShim is maintained by `GrizzlyOne95`, with `Piercing`
providing captures, validation, and technical collaboration on the multiplayer
investigation path.

Configure it through `net.ini` next to the game executable:

```ini
[OpenShimSocket]
EnablePacketReorder=1
PacketReorderWindowMs=45
PacketReorderDepth=8
PacketReorderPeers=32
PacketReorderDrainCap=96
LogPacketReorder=1
EnableBufferLog=0
BufferLogPayloadBytes=32
BufferLogRingRecords=65536
BufferLogSocketId=0
BufferLogPeer=
```

Notes:

- `EnablePacketReorder=1` enables the reorder buffer for synchronous UDP recv.
- `PacketReorderWindowMs` is clamped to `5`-`200` ms.
- `PacketReorderDepth` is clamped to `1`-`8`.
- `PacketReorderPeers` is clamped to `1`-`32`.
- `PacketReorderDrainCap` is clamped to `1`-`128`.
- `LogPacketReorder=1` enables detailed reorder diagnostics in `openshim.log`.
- `EnableBufferLog=1` writes a binary recv-path capture to `bz_buffer_log.bin`
  plus a small metadata sidecar file.
- `BufferLogPayloadBytes` is clamped to `8`-`256`.
- `BufferLogRingRecords` is clamped to `1024`-`1000000`.
- `BufferLogSocketId` limits binary capture to one OpenShim socket id.
- `BufferLogPeer` limits binary capture to one IPv4 peer, optionally with a
  port, for example `203.0.113.42:17770`.
- Environment variables `BZ_REORDER`, `BZ_REORDER_WINDOW_MS`,
  `BZ_REORDER_DEPTH`, `BZ_REORDER_PEERS`, `BZ_REORDER_DRAIN`,
  `OPENSHIM_REORDER`, `OPENSHIM_REORDER_WINDOW_MS`,
  `OPENSHIM_REORDER_DEPTH`, `OPENSHIM_REORDER_PEERS`, and
  `OPENSHIM_REORDER_DRAIN` override the `net.ini` values for testing.
- Environment variables `BZ_BUFFER_LOG`, `BZ_BUFFER_LOG_BYTES`,
  `BZ_BUFFER_LOG_RING`, `BZ_BUFFER_LOG_SOCKET`, `BZ_BUFFER_LOG_PEER`,
  `OPENSHIM_BUFFER_LOG`, `OPENSHIM_BUFFER_LOG_BYTES`,
  `OPENSHIM_BUFFER_LOG_RING`, `OPENSHIM_BUFFER_LOG_SOCKET`, and
  `OPENSHIM_BUFFER_LOG_PEER` override the buffer-capture settings for testing.
- The reorder path is bypassed for overlapped or async `WSARecvFrom` calls.
- Direct `recvfrom` and `FIONBIO` mode changes are also captured when the
  binary buffer log is enabled, which helps correlate nonblocking socket
  transitions with packet loss or reorder bursts.
- Outbound route diagnostics now tag `connect` / `WSAConnect` / `sendto` /
  `WSASendTo` traffic in `openshim.log` as `bzrnet_ws`, `bzrnet_probe`,
  `bzrnet_relay`, `p2p_lan`, or `p2p_candidate` so relay fallbacks and direct
  peer traffic are easier to distinguish.

## Test Net.ini

The repo now ships a diagnostic [`net.ini`](net.ini)
profile. Copy it next to the game executable to raise the default multiplayer
update rate and greatly relax auto-kick thresholds while you are diagnosing
packet loss.

Key changes in the shipped profile:

- `MinBandwidth=8000` instead of the common `4000` workshop setting
- `AutoKickStart=180000`
- `AutoKickPing=2000`
- `AutoKickLoss=100`
- `AutoKickTime=180000`
- `MaxPingsLost=60`

After launching multiplayer once, check `BZLogger.txt` for a line like
`Net: Bandwidth usage now set to 8000, Interval ... ms`. The current target is
`33 ms` or lower. If the interval is still above that on your build, the next
safe test step is usually raising `MinBandwidth` to `16000`.

## Buffer Capture Workflow

For Windows session bundles, use [`buffer_logger_windows.ps1`](buffer_logger_windows.ps1):

```powershell
.\buffer_logger_windows.ps1 -Action Start
.\buffer_logger_windows.ps1 -Action Mark -Message "loss spike during combat"
.\buffer_logger_windows.ps1 -Action Stop
```

Optional filters for tighter captures:

- `-SocketId <n>` captures only one OpenShim socket id
- `-PeerFilter 203.0.113.42:17770` captures only one IPv4 peer

`Stop` writes a zipped bundle under `test_bundles\` with `openshim.log`,
`BZLogger.txt`, `bz_buffer_log.bin`, `bz_buffer_log.meta.txt`, and the active
`net.ini` when present.

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
  [`reverse_engineering/chunk_fragment_path_20260326.md`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\chunk_fragment_path_20260326.md)
  and the helper script used for the live legacy trace is
  [`reverse_engineering/legacy_bzone_chunk_trace.js`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\legacy_bzone_chunk_trace.js)
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
  [`run_misn06_auto_capture.ps1`](C:\Users\iestu\Documents\GIT\BZR-OpenShim\reverse_engineering\run_misn06_auto_capture.ps1)
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

