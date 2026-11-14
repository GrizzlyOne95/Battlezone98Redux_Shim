# Leave-Game 30 s Freeze — Ogre Shader Recompile

## Symptom

Choosing **Leave Game** from a multiplayer match hangs for ~30 s, then recovers
into the shell. Reported 2026-07-17.

## Root cause

`logs/BZOgreLogfile.log` around the leave-game timestamp shows the game
tearing down and **reinitialising the `Modable` resource group**:

```
17:26:21: Setting viewports to game menu mode
17:26:23: Unloading resource group Modable
17:26:23: Clearing resource group Modable
17:26:23: Initialising resource group Modable
17:26:23: Parsing script CR_base.program
...
17:26:23: Invalid target for D3D11 shader 'CR_BaseLowest…_vertexHLSL4' - 'vs_4_0'   (skipped)
...
17:26:23 → 17:26:29 → 17:26:33 → 17:26:37 → 17:26:42   (multi-second gaps)
```

The multi-second gaps bracket the `CR_*EN*` (enhanced-mode) HLSL programs.
`CampaignReimagined/Shaders/CR_base.program` compiles them at **`target
ps_3_0`** with `preprocessor_defines MAX_LIGHTS=24,…,ENHANCED_MODE` and the
`.hlsl` body does `[unroll] for (i < MAX_LIGHTS)` (ps_3_0 cannot dynamically
index constant registers, so the 24-light loop is fully unrolled) plus 4×4 PCF
shadow unrolls. Each `D3DXCompileShader` of those variants costs seconds. The
group reinit fires on **every** mission load *and* on leave-game-to-shell, so
the same expensive compile runs every time.

(The `Invalid target … vs_4_0/ps_4_0` lines are the D3D11 SM4 variants being
skipped under the active D3D9 render system — harmless, and unrelated to the
stall. The cost is the D3D9 `ps_3_0` compiles that succeed.)

## Fix — enable Ogre's built-in GpuProgram microcode cache

The shipped `OgreMain.dll` (Ogre 1.10) already implements a microcode cache and
`RenderSystem_Direct3D9.dll` imports the full API
(`isMicrocodeAvailableInCache` / `getMicrocodeFromCache` /
`addMicrocodeToCache`, gated on `getSaveMicrocodesToCache`). The engine simply
never turns it on. New module `src/patches/ogre_shader_cache.cpp` enables it:

- **Enable the save flag.** `setSaveMicrocodesToCache` is *not* exported, but the
  exported getter `?getSaveMicrocodesToCache@GpuProgramManager@Ogre@@QAE_NXZ`
  disassembles to `mov al,[ecx+0xEC]; ret`. The module parses that byte offset
  from the getter body at runtime (fallback `0xEC`), writes `1` to `gpm+off`,
  then re-reads through the exported getter to verify; on mismatch it reverts
  and disables itself.
- **Load at startup / before compile.** Triggered from the `CreateFileW/A`
  hooks (`file_io_hooks.cpp`) the first time any module opens a `*.program`
  script. Ogre opens those via `fopen`/`_wfopen`/`_Fiopen` in `MSVCR120`/
  `MSVCP120` — whose `CreateFileW/A` IAT entries the shim already patches — so
  the trigger fires on the exact thread, *before* the group parse compiles the
  programs. Init resolves the GpuProgramManager + Root singletons, enables the
  flag, and `loadMicrocodeCache(openFileStream(cachePath))`.
- **Save when dirty.** From the per-sim-tick hook (`OgreShaderCacheTick` in
  `ChunkEffectSimulateHook`) and again on later `*.program` opens (covers
  shell-only sessions), throttled to 10 s: if `isCacheDirty` →
  `saveMicrocodeCache(createFileStream(cachePath))`.
- **Fingerprint guard.** `shader_cache/ogre_microcode.fp` stores an FNV-1a over
  the name/size/mtime of every shader source under `mods/`, `packaged_mods/`,
  and the Steam `workshop/content/301650` tree. If it changes, the stale
  `.cache` is dropped so edited shaders always recompile once.

### ABI notes (verified against the shipped OgreMain.dll)

- `SharedPtr<DataStream>` is 8 bytes (`{pRep, pInfo}`); `loadMicrocodeCache`
  ends `ret 8`, confirming the by-value SharedPtr arg is callee-cleaned.
- Streams come from `Root::openFileStream` / `Root::createFileStream`, which in
  Ogre 1.10 fall back to a direct `std::i/ofstream` open when the path is not
  found in the resource group — so absolute cache paths outside any archive
  work. The engine constructs each SharedPtr (refcount 1); the shim passes
  those 8 bytes by value **once** into load/save, whose callee-owned parameter
  releases the single reference on return/unwind. The shim declares the arg as
  a trivial 2-pointer POD so its own compiler never copies/destroys it → exactly
  one acquire, one release, no leak or double-free. Never touch the POD again.
- Every engine call is wrapped in a POD-frame `__try/__except` (Ogre throws
  `FileNotFound` etc., and C++ throws surface as SEH `0xE06D7363`).

### Result

Each unique GPU program compiles at most once per machine; later group reinits
(both mission load and leave-game) reload microcode instead of recompiling. The
in-memory cache also persists across the reinit within a single session, so even
the first run's leave-game is fast once the mission-load compiles have seeded it.

### Kill switch

`OPENSHIM_DISABLE_SHADER_CACHE` (or `BZR_DISABLE_SHADER_CACHE`) = `1`. The
module also auto-disables on any resolution/verification failure.

Log component: `[shadercache]` in `logs/winmm_shim.log` /
`logs/openshim.log`.
