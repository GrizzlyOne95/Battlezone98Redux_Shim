# Ogre load time and first-use hitches — measurement and recommendation (2026-10-03)

## Result

On this content, **material script parsing on every mod-set change** is the dominant
cost. Lazy texture, mesh and shader loading during play is not.

- A mod-set change (shell → addon mission, mission → shell) costs **~9 s wall**.
  That splits into ~2 s Modable unload/clear and ~6–7 s re-initialise/parse,
  with 5.1–5.6 s of main-thread CPU across the two phases.
- **36–40 % of the parse phase is Ogre re-importing the same base scripts.**
  `ScriptCompiler::compile()` clears its import cache after every file. So each
  of the 971 mod materials that does `import * from "BZBase.material"` (or
  `CR_BZBase`, `sprites`) re-lexes, re-parses and re-converts that base file.
- The **first destruction of a type costs only ~10–15 ms more** than a warm
  repeat in the measured scene (ISDF Chronicles + CR, chunk prewarm in place).
  Texture decode, GPU upload, mesh load and shader compile are each a few ms per
  event.
- Shader compile at load is small: DX9 0.2–0.4 s per load, DX11 0.04 s, with the
  microcode cache warm.

Two fixes are now built. Together they took the DX11 probe load from
18.4 s to 15.3 s:

- an **import cache** for the script compiler
  (`src/patches/ogre_script_import_cache.cpp`), which saves 1.2–1.7 s of script
  parsing per load;
- a **walk stat cache** (`src/patches/resource_walk_stat_cache.cpp`), which
  saves ~1 s per mod-set change.

The results sections below have the details; the remaining options are ranked
further down.

## Method

- Tool: OpenShim's native stack sampler (`OPENSHIM_PROFILE_NATIVE_CPU=1`,
  1 kHz, depth 64). It needs no hooks and attributes 100 % of main-thread
  samples, and a parked thread shows up as a wait leaf. Offline symbolisation
  used `reverse_engineering/analyze_cpu_samples.py` (PE exports). Every sample
  was classified with `reverse_engineering/load_hitch/attribute_load_hitch.py`
  by first match over the whole stack: shader compile, microcode cache, texture
  decode, texture upload, mesh load, script parse, material teardown, material
  compile, resource index, file I/O, wait, other.
- Scenario: the native-chunk pivot probe (`ncprobe.bzn` in ISDF Chronicles,
  with CR in `mods\`), extended to spawn **two** of each of ivsabr, ivrecy,
  ibcmmd, fbcomm and zvtnk. Ten destructions run 5 s apart. The first five are
  first use; the second five are the warm control for the same types.
  Destruction windows are −50..+1500 ms around the event, compared with the
  1.5 s before it.
- Build: installed 1.0.0.46, unchanged. Hashes of `winmm.dll`, `bzloader.dll`,
  `plugins\openshim.dll` and the exe were taken before and after every run, and
  were stable. Runs used the serialized launch lock, windowed mode and graceful
  `Stop-BZRGame`. They were launched through WMI so the game was outside the
  agent's job object. The session was unlocked (no LogonUI). Timings are
  sampled CPU, not frame times.
- Ogre resource-group phases come from `BZOgreLogfile.log`, which has 1 s
  timestamps. Phase windows are therefore ±1 s; per-category milliseconds
  inside them are exact sample counts.
- Evidence: `Documents\BZ_Ogre_Load_Hitch_20261003\` (`dx11-warm`,
  `dx9-texopt`, `dx11-texopt`). Each run folder has its capture,
  `attribution.json`, logs and `metadata.json`.

## Numbers (main thread, ms of samples)

| window | run | wall | sampled | script parse | other | resource index | shader compile | tex decode | tex upload | mesh | file I/O |
|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| start → sim | DX11 | 17 968 | 8 411 | 4 243 | 3 036 | 351 | 50 | 98 | 177 | 147 | 112 |
| start → sim | DX9 | 19 169 | 9 642 | 4 564 | 3 703 | 358 | 386 | 70 | 191 | 116 | 110 |
| start → sim | DX11 (textures optimised) | 18 545 | 9 202 | 4 312 | 3 650 | 401 | 35 | 107 | 186 | 182 | 114 |
| Modable unload → clear | DX11 | 2 000 | 1 439 | 0 | 1 270 | 161 | 0 | 0 | 0 | 0 | 3 |
| Modable clear → parsed | DX11 | 6 000 | 4 210 | 3 573 | 483 | 81 | 0 | 15 | 0 | 0 | 33 |
| Modable clear → parsed | DX9 | 7 000 | 5 075 | 3 894 | 742 | 103 | 212 | 63 | 8 | 0 | 36 |

Inside the DX11 parse phase (4 210 ms), the inclusive cost of each stage:

| stage | ms | share |
|---|---:|---:|
| `processImports` | 1 667 | 39.6 % |
| `loadImportPath` (lex + parse + convert of imported files) | 1 430 | 34.0 % |
| `ScriptTranslator` (material objects) | 1 113 | 26.4 % |
| `ScriptLexer` (all files) | 1 001 | 23.8 % |
| variable substitution / `setVariable` | 909 | 21.6 % |
| `processObjects` (inheritance) | 571 | 13.6 % |
| `ScriptParser` | 539 | 12.8 % |
| `convertToAST` | 391 | 9.3 % |
| `openResource` | 99 | 2.4 % |

DX9 shows the same shape (processImports 35.6 %, loadImportPath 30.5 %). Its
self time is heap allocation and free (`RtlpLocalInfoAllocFromCache`,
`RtlpFreeNTHeapInternal`), `memmove` and `ObjectAbstractNode::setVariable`: the
parse is allocation-bound AST churn, not I/O.

**Unload → clear (~1.3 s of "other")** is file metadata, not Ogre:
`GetFileAttributesExW` (530 ms), `GetFileAttributesW` (218 ms) and
`FindFirstFileW` (51 ms). It comes from a recursive directory walk at
`FUN_00667ed0` (self-recursive at `+0x26860d`). That walk is called by
`FUN_006679c0`, which `buildSingleIAResource` (`FUN_0076a600`) uses to
re-register every Modable resource location before
`clearResourceGroup("Modable")` / `initialiseResourceGroup("Modable")`.
`buildSingleIAResource` already skips all of this when the requested mod set
equals the last-built set and its dirty flag (`this+0x8c`) is clear. The
rebuild therefore happens when the set changes, and leaving an addon mission
for the shell is such a change.

**Destructions:** the mean first-use categories (decode, upload, mesh, shader,
material, file, index, parse) were cold 28.2 / warm 25.4 ms (DX11 baseline),
cold 31.4 / warm 17.8 ms (DX9) and cold 27.8 / warm 16.8 ms (DX11 optimised).
The largest single first-use cost seen was 22 ms of texture decode on the first
Sabre. ~10–19 ms of "material compile" appears in cold, warm *and* baseline
windows alike. Its leaves are OpenShim's own `RenderProfiles::IsSynthesisTarget`
and Ogre `Animation::clone`, so it is steady per-frame or per-spawn work, not a
first-use hitch.

## Options, ranked

1. **Import cache for the script compiler. Built** (see the next section).
2. **Resource-location walk. Built** as a scoped stat cache rather than a
   cross-load cache (see "Walk stat cache: results").
3. **Avoid the Modable re-parse altogether** (5–6 s per change, the largest
   prize). The engine already skips an unchanged set. Skipping a changed set
   means making Modable a union of all sets, or keeping per-set groups alive.
   That collides with "materials outlive the mission Lua state" and with the
   per-mission material overrides mods rely on. Highest risk; not recommended
   before 1 and 2.
4. **Texture conversion. Done** (see below). Decode of the converted content
   was never large in this scene (70–107 ms at load, ≤22 ms per first use).
   The payoff is load I/O, VRAM, bandwidth and aliasing, plus first-use decode
   on content-heavy mods that this scene did not exercise.
5. **Profile-guided preload / ODF explosion-chain preload.** Not justified:
   first-use cost per destruction is ~10–15 ms over warm here. Revisit only if
   a scene with heavier first-use content (Resurgence) shows otherwise.
6. **OS file-cache prefetch thread.** Not justified: file I/O is 30–110 ms per
   window with a warm cache, and the parse is CPU-bound.

## Import cache: design and results

`src/patches/ogre_script_import_cache.cpp` adds two inline detours on
OgreMain exports, both prologue-checked and failing closed:

- **`ScriptCompiler::loadImportPath`.** On a cache hit it returns
  `convertToAST(cached concrete list)`. On a miss it runs the original with a
  thread-local capture slot armed.
- **`ScriptParser::parse`.** When the slot is armed, it keeps a reference to the
  result. This only happens inside the original `loadImportPath`, whose single
  parse is the import itself.

Design notes:

- **What is cached.** Only the concrete node list. `AbstractTreeBuilder` only
  reads it, so one list can feed any number of compiles. The abstract tree is
  never shared, because `processImports`/`processObjects` mutate it and are not
  idempotent: overlays and override insertion repeat.
- **Lifetime.** Entries are keyed by resource group + import name and are
  dropped when no import is requested for 1.5 s. Each parse wave therefore
  starts empty, and an edit made between loads is read fresh.
- **Why not a listener.** A `ScriptCompilerListener::importFile` would also
  work, but a cache miss would then have to run Ogre's lexer and parser itself.
  The detour reuses Ogre's own miss path.
- **ABI, verified in the shipped DLL:**
  - `SharedPtr` is `{pRep, pInfo}`.
  - **`useCount` is at `SharedPtrInfo+0x14`, not the header's `+4`** (every
    retail copy and release site uses `+0x14`).
  - Release at zero is `vtbl[0](info, 0)` + `StdAllocPolicy::deallocateBytes`.
  - The first captured list must read `useCount == 1` at that offset, or the
    cache disables itself before it holds a reference.
- **Kill switch:** `OPENSHIM_DISABLE_SCRIPT_IMPORT_CACHE=1`.

Live runs used the same probe on the GOG install, running the
`agent/native-mesh-chunks` 1.0.0.46 build plus this change. Main-thread
sampled ms:

| run | script parse (whole load) | mission parse phase | `loadImportPath` in it | start → sim wall |
|---|---:|---:|---:|---:|
| DX11, cache off (kill switch) | 4 283 | 3 596 | 1 416 | 18.4 s |
| DX11, cache on | 3 050 | 2 531 | 11 | 17.2 s |
| DX9, earlier run without the cache | 4 564 | 3 894 | 1 546 | 19.2 s |
| DX9, cache on | 2 883 | 2 441 | 11 | 16.2 s |

- **Shell wave:** 220 hits from only 3 parsed imports.
- **Mission re-parse:** the phase fell from 6–7 s to 4–5 s of wall clock
  (1 s log stamps).
- **Unchanged:** all runs had the same 1 424 parsed scripts and 10/10
  destruction events.
- **Exits:** the DX11 runs, with and without the cache, ended in the known
  `nvwgf2um` shutdown fault (eip `…FCC6`) that open PR #396 fixes; DX9 exited 0.
- **Unusable arms:**
  - The first cache-on DX11 run paid 2.9 s of one-off shader recompilation
    because the deploy invalidated the microcode cache; it was rerun with the
    cache warm.
  - A DX9 cache-off arm was lost: the game and its runner were stopped
    externally 2 s after launch. The DX9 baseline is therefore the earlier
    no-cache run on the same content.

## Walk stat cache: design and results

`buildSingleIAResource` (`0x0076A600`, new `engine_addresses` row
`BuildSingleIAResource` with guard bytes and identity) re-registers every
Modable location through a recursive `std::tr2::sys` walk. That walk
enumerates with `FindFirstFileW`/`FindNextFileW`, then calls
`GetFileAttributesExW`/`GetFileAttributesW` on each entry it was just handed.

`src/patches/resource_walk_stat_cache.cpp` handles it like this:

- **Scope.** It detours `buildSingleIAResource` to open a per-thread scope.
- **Record.** Inside the scope, the executable's enumeration imports (IAT)
  remember each entry's `WIN32_FIND_DATAW` attributes.
- **Answer.** Stat calls for exactly those paths are answered from the record.
  Both APIs describe the same object without following reparse points, so the
  answer is what the OS would return a moment later.
- **Lifetime.** The record is dropped when the scope closes; nothing survives
  into another load or another code path.
- **Outside the scope**, every hook is a thread-local test and a tail call.
- **Coexistence.** It chains with the UiPerf file-scan counters when those are
  installed.
- **Kill switch:** `OPENSHIM_DISABLE_RESOURCE_WALK_STAT_CACHE=1`.

Live, on DX11 with the GOG install's chunks build plus both caches:

| | walk cache off | walk cache on |
|---|---:|---:|
| stat calls answered from enumeration | — | 33 212 (6 went to the OS; 33 470 entries) |
| `buildSingleIAResource` wall (BZLogger µs stamps) | 6.10 s | 4.95–5.17 s |
| attribute-query samples, start → sim | 947 ms | 65 ms |
| Modable unload → clear, sampled | 1 442 ms | 699 ms |
| start → sim wall | 16.7 s | 15.3 s |

Run notes:

- **Probe window.** These runs used a visible game window.
- **Stall in the off arm.** The sim stopped advancing 21 s into the mission,
  after 4 of 10 destructions, with no crash; the runner then closed it
  gracefully. That is the known focus-loss stall, and it comes after the load
  window being measured.
- **Exits.** Every DX11 exit ended in the known `…FCC6` driver-thread shutdown
  fault, which PR #396 fixes.

## Texture optimisation done in this workstream

Encoded with the Battlezone Modding Toolbox's `textures recompress` (DXT1/DXT5
by real alpha, per-file decode verify, backups), driven per mod. The toolbox
gaps found along the way are fixed on its branch `agent/texture-recompress-gaps`:

- frozen exe `--jobs` crash;
- terrain atlas protection;
- 4-alignment;
- mip append for BC files;
- a quality gate;
- `*_Normal` detection;
- a new `textures shrink-previews` command.

| mod | before | after | notes |
|---|---:|---:|---|
| Resurgence | 4 123 MiB | 1 496 MiB | 511 files to BC; 229 gained mip chains; 23 BC files had mips appended; 7 noisy normals kept uncompressed with mips |
| bz64port | 3 131 MiB | 130 MiB | 40 mission previews (`<mission>.bmp`, up to 8104², 197 MB each) downscaled to 1024 px; the shell decoded them for a 200 px window |
| N64Models | 708 MiB | 236 MiB | 242 files to BC with mips |
| coopzomb | 370 MiB | 243 MiB | 21 to BC (5 resampled to 4-aligned); 8192² `hersey_*` BC files gained mips |
| CR (`mods\3686673790`) | 77 MiB | 45 MiB | 1254² ports resampled to 1256² and BC1; chunk and dust-devil BC files gained mips (CR branch `agent/texture-optimization`) |
| IA Map Pack | 63 MiB | 53 MiB | three 1254² ports |
| ISDF Chronicles | 3 204 MiB | 3 234 MiB | canon caught up with the install; 18 normals an earlier pass had BC-encoded (8–30° error) restored to their originals; jakpilot uses the existing DDS set |
| **all addon\ + mods\** | **11 782 MiB** | **5 543 MiB** | |

Left alone on purpose:

- terrain atlases and `.trn`-named textures (their sizes and short mip chains
  are deliberate);
- UI art (HUD-material scan plus name heuristic);
- unaligned effect sheets under 1 MP;
- non-DDS images named by `.ini`/`.odf`/shell (looked up by exact name);
- small material-referenced effect PNGs (~3 MB total).

All 1 769 changed files in canon and install were validated: each parses,
DirectXTex decodes it, BC files are 4-aligned and mip chains are complete. The
one exception is the installed `coopzomb\hersey_S.dds`, a different, newer
1036² texture than the Drive canon, which was left untouched. DX9 and DX11
probe runs with the converted CR and ISDFC content logged the same Ogre
error set as before, with no texture errors.
