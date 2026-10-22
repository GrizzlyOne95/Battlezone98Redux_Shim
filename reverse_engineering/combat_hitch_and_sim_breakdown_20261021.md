# Combat hitches and the "simulation" share of a combat frame (2026-10-21)

Follow-up to `frame_time_breakdown_20261020.md`. Two questions, measurement
only; nothing here changes shipping behaviour.

1. In a sustained 40-craft fight, what are the 1%/0.1% lows, and what runs on
   each spike frame?
2. What is inside the ~2.5 ms that the earlier breakdown called "simulation",
   and how does it scale with craft and projectile count?

## Bottom line

- **Every in-play spike has a named cause, and most are OpenShim's own.** A
  40-craft fight with deaths has 5-7 frames over 20 ms per minute after load.
  The fight without deaths (`firing`) has exactly one: the first frame.
- **At 40 craft the lows are set by deaths.**

  | | 1% low | 0.1% low |
  |---|---|---|
  | With deaths | 58-66 fps | 21-24 fps |
  | Without deaths | 72-86 fps | 49-59 fps |

- **At 80 craft the lows are set by volleys.** Frames over 20 ms come about
  every 0.3 s, 300 a minute. About 4.5 ms of each is OpenShim reading
  `openshim.ini` from disk inside the damage hook.
- **The ranked spike causes** (one sampled 60 s fight, 6 spikes, plus the
  matching first frame of the `firing` run):

  | # | Cause | Owner | Frames hit | Cost each | Fix |
  |---|---|---|---|---|---|
  | 1 | First chunk-mesh proxy / skinned-gib set for a craft type: Ogre texture prepare walks every resource location (`FindFirstFileExW`), plus gib cache read | OpenShim (`ChunkMeshes = 1`) | 1 per new debris type; 112-188 ms | ~90 ms over budget | Pre-warm at mission load |
  | 2 | Career-stats file rewrite on every local kill/death: load + `ReplaceFileW` on the main thread | OpenShim (`career_stats.cpp`) | 1-2 per local kill | 27-32 ms (10-13 ms in I/O) | Defer: dirty flag, flush on a worker or at mission end |
  | 3 | First frame of play: DirectSound secondary-buffer connect (stock `0x0043CC20` path, AudioSes RPC), first-use textures from dynamic geometry, first GPU-skin buffer map | stock + OpenShim | 1 per mission | 61-69 ms | Partly pre-warmable (touch a silent buffer and the dynamic-geometry materials during load) |
  | 4 | First AI-tuning lookup for a new ODF (first pilot ejection): `std::filesystem::exists` over every ODF directory candidate | OpenShim (`ai_odf_tuning.cpp`) | 1 per new ODF | 23 ms | Pre-warm the cache at mission load, or cache directory listings |

- **Frames cost, ranked:** chunk-proxy first load (≈90 ms over a 16.7 ms budget
  per new debris type) > first frame (≈50 ms, once) > career-stats saves
  (≈12 ms over budget, but per local kill, so it repeats all mission) >
  AI-tuning ODF probe (≈7 ms, per new ODF). Only #2 repeats without bound.
- **The "simulation" block is mostly not simulation.** `0x006175C0` is stock
  `Render_Next_Frame`, the CPU side of the render (object render lists, HUD,
  cockpit radar); that alone is 1.5 ms. True `Simulate` (`0x00618060`) is
  0.8-1.3 ms, and **half to two thirds of it is OpenShim's chunk-effect
  tracking hook** (0.40-0.81 ms), which calls `VirtualQuery` per chunk per
  frame. That is the same pattern #541 removed from the GPU-skin scan.
- **Scaling with craft count (20 → 80, `firing`):**

  | Block | 20 craft | 80 craft | Growth |
  |---|---|---|---|
  | `Render_Next_Frame` | 1.2 ms | 2.0 ms | slow |
  | `Simulate` | 0.6 ms | 2.1 ms | about linear |
  | `ControlWeapons` (ordnance) | 0.12 ms | 1.24 ms | faster than linear |

  In a real fight AI grows faster than linear too: 0.14 → 1.12 ms.

## Method

- **Scene:** `run_live_combat_benchmark.ps1` (lcbench), avtank, 40 craft at
  50 m, facing.
  - `combat`: craft fight and die; no refill.
  - `firing`: craft fire at each other with health and ammo refilled; no
    deaths, same ordnance load.
- **Settings:** GOG build at `main` 4772e5544, DX11, `BZR_FORCE_WINDOWED=1`,
  `OPENSHIM_GPU_SKINNING=1`, `[SinglePlayer] VehicleGeometryContact = 0`
  (confirmed by the `[geometrycontact] global vehicle geometry OFF` log line),
  PSSM 2048 (`BZPLYR.DEF` byte 0x2D = 3). The user's ini otherwise as found,
  including `ChunkMeshes = 1`. Ini and `BZPLYR.DEF` restored after each study.
- **Arms:**
  - **clean** (`-ProfilerDisabled -ExternalPresentMon -PerfTelemetry`):
    `frames.bin` frame times only.
  - **sampled** (`-SampleCpu`): the native CPU sampler at about 1 sample per
    1.37 ms on the main thread, frame-pointer stacks.
- **Windows:** in-play means every `RUN_STARTED` frame after the
  `Game Simulation Initialized ... Playing` log line. The sim breakdown uses
  lcbench's own `measure-begin`/`measure-end` window.
- **Attribution:** each sample is binned into its frame by QPC. For a spike
  frame, its samples are categorised by the first matching frame in the stack
  (career save, ODF probe, DirectSound, texture load, chunk proxy, GPU-skin
  map, render, game code).
- Game functions are named from the 1.5 symbol transfer tables already in this
  repository (`editor_shiftf10_object_placement_20260817.md` and others).
  Where none exists, the address is given with what its callees show. No PDB
  or decompiler output is reproduced here.

## 1. Combat hitch study

### Pre-play frames are load, not gameplay

Every run has 17-18 `RUN_STARTED` frames over 20 ms, about 10.2-10.4 s in all,
before "Playing". They are the 7.9 s mission-load frame, then about 13 frames
of 100-230 ms while vertex generation (576 ms) and mesh preload ("83
automatically identified") run. They are excluded below.

### Lows, in-play

| Run | Length | Mean | p99 | 1% low | 0.1% low | Spikes > 20 ms (ms @ s after Playing) |
|---|---|---|---|---|---|---|
| combat, clean #1 | 63.8 s | 6.89 ms (145 fps) | 11.28 ms | 15.23 ms (66 fps) | 47.07 ms (21 fps) | 63@0.06, 35@0.13, 24@1.61, 33@31.38, 27@31.41, 20@37.74, 188@58.94 |
| combat, clean #2 | 64 s | 7.00 ms (143 fps) | 13.94 ms | 17.18 ms (58 fps) | 41.51 ms (24 fps) | 61@0.05, 56@18.61, 27@18.66, 22@33.95, 20@42.80, 112@47.47 |
| firing, clean | 93.9 s | 7.73 ms (129 fps) | 10.65 ms | 11.63 ms (86 fps) | 16.91 ms (59 fps) | 63@0.08 only |
| combat, sampled | 64 s | 8.53 ms | — | 17.62 ms | 44.56 ms | 69@0.05, 23@26.93, 32@40.16, 27@40.19, 114@51.39, 28@62.88 |
| firing, sampled | 94 s | 8.50 ms | — | 13.95 ms | 20.21 ms | 66@0.08 only |

Scaling runs, all sampled, 60 s each:

| Run | Mean | 1% low | 0.1% low | Spikes > 20 ms |
|---|---|---|---|---|
| firing 20 | 5.17 ms (193 fps) | 8.43 ms (119 fps) | 15.06 ms (66 fps) | 1 (first frame) |
| firing 80 | 13.76 ms (73 fps) | 34.00 ms (29 fps) | 79.34 ms (13 fps) | 308 (volley beat) |
| combat 20 | 4.96 ms (202 fps) | 9.35 ms (107 fps) | 19.64 ms (51 fps) | 4 |
| combat 80 | 12.57 ms (80 fps) | 29.90 ms (33 fps) | 72.34 ms (14 fps) | 221 (one 180 ms chunk first load; the rest is the volley beat) |

The sampler adds about 1.5 ms to the mean. Lows from the sampled runs are
for attribution, not for comparison with the clean runs.

The pairs at about 30 ms a few frames apart (33+27, 56+27, 32+27) match the
career-stats double save seen in the sampled run. The one 112-188 ms spike
per combat run matches the chunk-proxy first load. The clean runs carry no
stacks, so for them this is a pattern match, not an attribution.

### Spike-by-spike, sampled combat run

Sample counts are main-thread samples inside that frame.

- **69 ms, first frame (54 samples).**
  - 19: DirectSound. Stock audio (`0x0043A170` → `0x0043AD20` → `0x0043B360`
    → `0x0043CC20`) starts its first secondary buffer. `CLeapSecondaryRenderWaveBuffer::Thaw`
    connects the renderer through an AudioSes RPC.
  - 14: first-use textures, reached through OpenShim's
    `DynamicGeometryAddRenderableHook` over stock `0x00679570`
    (`Material::loadImpl` → `D3D11Texture::loadImpl` → FreeImage decode).
  - 8: OpenShim GPU skinning on its first frame
    (`OptimisedUtil::_detectImplementation` and the first buffer map).
  - The `firing` first frame (66 ms) is the same shape, with 25 samples in
    texture loads.
- **23.5 ms at +26.9 s, the first pilot ejection (17 samples).** 9 samples are
  in OpenShim `CalcRangeCraftHook` → `TryGetAiTuningForObject`, a cache miss
  for the new pilot ODF. That runs `TryReadAiTuningFromOdfFile` →
  `OdfSearchPath::FindOdfFile`, which calls `std::filesystem::exists`
  (`GetFileAttributesExW`) over every ODF directory candidate. The cache
  (`g_AiTuningCache.odfEntries`) makes this once per ODF token.
- **32 ms and 27 ms at +40.16/+40.19 s, and 28 ms at +62.9 s.** 13, 6 and 11
  samples are in OpenShim `CareerStatsEventSink` → `CareerRecordDerivedKill`
  → `LoadCareerStatsFile` + `SaveCareerStatsFile`. That path reads the whole
  file, sorts the keys, writes it, and `ReplaceFileW`s it on the main thread,
  under `g_CareerStatsLock`, once for every local kill or death. The
  `DynamicSniper: add vertex buffer` log line at +40.2 s lands in the same
  frames but costs 1-2 samples.
- **114 ms at +51.4 s (94 samples).**
  - The first full fragment of a craft goes through stock
    `0x005A1180` → OpenShim `ChunkEffectFullFragmentHook` →
    `SkinnedGibsBeginFullFragment` → `prepareGibs`, then `SpawnFromCapture`
    → `TryCreateChunkMeshProxyObjects` → `CreateChunkMeshProxyEntity`.
  - 41 samples are Ogre `TextureManager::prepare` for the proxy's
    materials. Most of that is `ResourceGroupManager::findGroupContainingResourceImpl`
    probing every file-system archive with `_stat64` → `FindFirstFileExW` /
    `ZwOpenFile`.
  - 10 samples are entity creation, 8 are `prepareGibs` resource reads and
    the `NativeChunks::ReadGibCache` match.
  - Later fragments of the same type are cheap: no other combat-run frame
    reaches 20 ms through this path.

### What could be pre-warmed

| Cause | Pre-warm? | How |
|---|---|---|
| Chunk-proxy / skinned-gib first load | **Yes** | At mission load, for each craft ODF present, run the gib/chunk preparation and touch the proxy materials (`Material::load`), so the textures are resident before the first death. A per-name resource-location cache would also remove most of the 41 `FindFirstFileExW` samples. |
| Career-stats save | No; it is a write | Keep the data in memory and mark it dirty. Flush it on a worker thread, or at mission end and on exit. The load per event is also unnecessary once the map is resident. |
| First-frame DirectSound connect | Partly | Play one silent buffer during load. The stock audio path is not OpenShim's, so this needs a small hook. |
| First-frame textures (dynamic geometry) | Yes | Touch the dynamic-geometry materials (sniper, tracer and main dynamic buffers) during load. |
| AI-tuning ODF probe | Yes | Fill `g_AiTuningCache` at mission load for every ODF in the world and its pilots, or cache the directory listing once. |

## 2. What the "simulation" ~2.5 ms contains

The frame body is stock `0x00618130`. From the 1.5 transfer table
(`editor_shiftf10_object_placement_20260817.md`), it calls `Simulate`
(`0x00618060`), `ControlWeapons` (`0x00617FA0`), `Render_Next_Frame`
(`0x006175C0`) and then the Ogre render (`0x00682540`). The phase-1 "world
tick (`0x6175C0`/`0x6176A0`)" row is therefore **`Render_Next_Frame`, the CPU
half of rendering**, not the object simulation.

Inclusive ms per frame, measure window, main thread, outside `0x00682540`:

| Block (GOG address) | firing 20 | firing 40 | firing 80 | combat 20 | combat 40 | combat 80 |
|---|---|---|---|---|---|---|
| frame mean (sampled) | 5.21 | 8.61 | 14.00 | 5.09 | 8.92 | 12.97 |
| **frame body outside Ogre render** `0x00618130` | 2.23 | 3.55 | 6.00 | 1.88 | 3.20 | 5.12 |
| **`Render_Next_Frame`** `0x006175C0` → `0x006176A0` | 1.24 | 1.54 | 2.00 | 1.07 | 1.58 | 2.02 |
| · per-object render-list build `0x00451F80` (`0x0044E7F0`/`0x0044E880` renderer lists) | 0.58 | 0.87 | 1.28 | 0.30 | 0.46 | 0.57 |
| · HUD / display list `0x00617600` → `0x004B6F10` → `0x004B6DB0` | 0.61 | 0.62 | 0.66 | 0.59 | 0.62 | 0.77 |
| · · of which CockpitRadar render `0x00493EC0` | 0.51 | 0.51 | 0.52 | 0.42 | 0.41 | 0.44 |
| **`Simulate`** `0x00618060` | 0.64 | 1.29 | 2.12 | 0.45 | 0.82 | 1.30 |
| · OpenShim `ChunkEffectSimulateHook` (over stock `0x004D4580`) | 0.39 | 0.81 | 1.20 | 0.23 | 0.40 | 0.61 |
| · object-class step `0x0062BC80` → `0x0062BD40` → `0x004DEEC0` | 0.21 | 0.40 | 0.77 | 0.15 | 0.29 | 0.49 |
| · · of which Craft::Simulate analog `0x004AB380` | 0.17 | 0.32 | 0.63 | 0.11 | 0.21 | 0.33 |
| **`ControlWeapons`** `0x00617FA0` (ordnance) | 0.12 | 0.36 | 1.24 | 0.06 | 0.15 | 0.30 |
| · bullet simulate `0x00480470` → `0x00480750` (hit → damage) | 0.08 | 0.28 | 0.85 | 0.03 | 0.08 | 0.18 |
| **AI / mission processes** `0x0045BF90` → `0x0050AA10` → `0x0045D240` → UnitProcess `0x005FA6E0` | 0.04 | 0.09 | 0.26 | 0.14 | 0.39 | 1.12 |
| pairwise object loop `0x00442E70` | 0.02 | 0.07 | 0.13 | 0.01 | 0.02 | 0.04 |
| music/sound update `0x0043A170` | 0.12 | 0.15 | 0.17 | 0.11 | 0.15 | 0.20 |

`firing` keeps every craft alive and shooting. `combat` loses craft during
the window, so its columns understate the nominal count. In `firing`, `FireAt`
replaces most AI decisions, so its AI row stays small.

### How each block scales

- **`Render_Next_Frame` grows slowly**: about 1.0 ms of fixed cost plus about
  0.013 ms per craft. The fixed part is mostly the HUD, and 0.4-0.5 ms of that
  is the cockpit radar alone, at any craft count. The per-object list build is
  the part that grows.
- **`Simulate` grows about linearly with live objects**: about 0.025 ms per
  craft in `firing`. Debris adds to it. Half to two thirds is OpenShim's chunk
  hook (next section), and the rest is the stock per-class object step.
- **`ControlWeapons` grows faster than linearly** with the number of craft
  firing: 0.12 → 0.36 → 1.24 ms for 20 → 40 → 80. The step from 40 to 80 is
  3.4×. Bullet movement and hit tests (`0x00480470`/`0x00480750`) are most of
  it, plus the per-hit damage path (`0x004AA630`) and impact sounds
  (`0x0043AA30` / `0x0043B520`). Some of that growth is OpenShim's damage hook
  (below).
- **AI grows faster than linearly in a real fight**: 0.14 → 0.39 → 1.12 ms.
  At 80 craft, 0.80 ms of the 1.09 ms in UnitProcess `0x005FA6E0` is inside
  OpenShim's `AttackTaskDoStateTuningHook`, measured inclusive, so it also
  counts the stock attack-task state it wraps. Split it with a probe before
  blaming the hook.
- **The pairwise collision loop is small here** (≤0.13 ms) because
  `VehicleGeometryContact` is off. Compare 0.7 ms with it on in the
  2026-10-20 breakdown.

### OpenShim's own share

These are per-frame costs inside the blocks above, read as inclusive time
from the same captures:

| OpenShim cost | firing 20 | firing 40 | firing 80 | combat 40 | combat 80 | Cause |
|---|---|---|---|---|---|---|
| `TrackChunkEffectActiveEntries` | 0.30 | 0.60 | 0.91 | 0.29 | 0.43 | For every active chunk, every frame, it calls `CaptureChunkBridgeSnapshot` → `TryReadOgreLinks` → `MemoryAccess::RangeAllows` → `VirtualQuery`. `ZwQueryVirtualMemory` self time is 0.38 / 0.72 / 1.24 / 0.36 / 0.54 ms. This is the pattern #541 removed from the GPU-skin scan. It runs when `ChunkMeshes` is on, and its `TrackChunkProxyDebugEntry` half runs even with debug off. |
| ini read from disk on each damage event | 0.06 | 0.23 | 0.62 | — | 0.15 | `DamageRevealProbeHook` → `ShouldTraceOwnedObjectReveal` → `EnvFlagEnabled` → (IAT) `OpenShimGetEnvironmentVariableA` → `TryReadIniValue` → `GetPrivateProfileStringA` (disk) for two trace flags on every hit. |
| `WingmanUpdateWeaponAimWithConvergence` | 0.15 | 0.29 | 0.56 | 0.17 | 0.25 | Weapon-convergence range lookups. Not broken down further. |
| `HudPalette` `GridDraw` | 0.21 | 0.20 | 0.22 | 0.14 | 0.14 | Radar grid redraw; fixed cost. |

### The 80-craft volley hitch

`firing` at 80 craft hitches over 20 ms on 304 frames a minute, on a regular
~0.3 s beat: the volley cadence. Each hitch frame is about 25 ms against a
12.7 ms median. Compared with normal frames, hitch frames carry these extra
costs:

- `ControlWeapons` +8.6 ms per hitch frame. It is bullets hitting at the same
  time: `0x00480750` → damage `0x004AA630` → `0x004CB7B0`/`0x004C9AB0`.
- **4.5 ms of each hitch frame is the ini-from-disk read above**
  (`GetPrivateProfileStringA`, 18.5% of hitch samples against 2.5% in normal
  frames).
- About 2.5 ms is impact sounds (`0x0043AA30` → `0x0043B520` → `0x0043BDC0`).

Caching the trace flag would remove about half of each volley hitch. At 80
craft the lows (1% 29 fps, 0.1% 13 fps) are set by this beat, not by deaths.

`combat` at 80 craft shows the same beat between 49 s and 63 s, about 21-28 ms
per frame, while the fight is densest. It also has one 180 ms chunk-proxy
first load at +41.7 s.

## Follow-ups (not done here)

Ranked by value per effort. Every one is OpenShim code. Nothing was changed
in this study.

1. **Cache `ShouldTraceOwnedObjectReveal`** (and audit other `EnvFlagEnabled` calls on hot
   paths). `GetEnvironmentVariableA` is redirected to an on-disk ini lookup,
   so an uncached flag check costs a file read. The win is 0.2-0.6 ms per
   frame in fights, and about 4.5 ms off every 80-craft volley hitch.
2. **Cache the chunk-bridge readability probe in `TrackChunkEffectActiveEntries`**
   the way #541 did for `ScanFrame`. Also gate `TrackChunkProxyDebugEntry` on
   `g_EnableChunkProxyDebug`. The win is 0.3-0.9 ms per frame with debris
   active.
3. **Make the career-stats write asynchronous**: keep the stats in memory,
   mark them dirty, and flush at mission end or on a worker. This removes the
   27-32 ms hitch on every local kill or death.
4. **Pre-warm the chunk-proxy and skinned-gib resources at mission load.** This
   removes the one 110-190 ms hitch per new debris type. A resource-location
   lookup cache would also help any later first-use texture.
5. **Pre-warm `g_AiTuningCache` at mission load.** This removes the 23 ms hitch
   on the first pilot ejection and on each later new ODF.
6. **Probe `AttackTaskDoStateTuningHook`** at 80 craft in combat to split the
   OpenShim and stock costs inside its 0.8 ms.
7. **Stock items worth knowing, but not OpenShim's to fix cheaply:**
   - cockpit radar at 0.4-0.5 ms per frame regardless of load;
   - the first-frame DirectSound connect;
   - bullet and impact-sound costs that grow faster than linearly with
     shooters.
