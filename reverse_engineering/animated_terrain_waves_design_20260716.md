# Animated Terrain Tiles ("ctrl+shift+waves") — RE + Ogre/Redux Port Design

Date: 2026-07-16
Status: RE complete, implementation design (not yet built)

## What the 1.5 feature actually was

The 1.5 TRN `[NormalView] Wave=N` line and the `waves` debug toggle drove a
**vertical vertex-displacement animation** in the software terrain renderer — not a
texture animation. Confirmed from the 1.5 decomp:

- `WaveInit` / `Terrain_Create` (`0x00520818`, `0x00522eab`): precompute a 128-entry
  sine LUT — `WaveTable[i] = sin(i * 0.049087387)` (0.049087387 = 2π/128).
- `ReadTerrainIni` (`0x0051ef53` region, decomp line ~335562):
  `waveMat = GetINIInt("NormalView","Wave",-1,missionName)` and
  `lavaMat = GetINIInt("NormalView","Lava",-1,missionName)`.
  Global on/off `waveEnable = GetPrivateProfileIntA("NormalView","Waves",0,cfg)`.
- `BuildTerrainPolys` (`0x005220c6`): the animation itself. For each terrain vertex
  whose tile **material id** matches `waveMat`, it adds
  `WaveTable[(col*0x20 + lastWaveIndex) & 0x7f]` to the vertex Y. `lastWaveIndex`
  advances by 1 every 50 ms (`0x32 < now - lastWaveTime`). So `Wave=N` means
  "material/tile id N bobs up and down as a travelling sine wave."
- `waves` cheat toggles `waveEnable` live (`test_for_cheat("waves")`).

`Lava=N` is a *separate* feature: tiles of material id `lavaMat` are shaded from a
`LavaColors[]` ramp instead of `GreyColors[]` (see `0x00336882` in the 1.5 decomp) —
a color animation via the light ramp, no geometry motion.

## What survives in Redux (GOG 2.2.301)

The whole config + toggle path is **still present and live** in Redux:

- `0x0077E490` (render-config load): `DAT_009454c8 = GetPrivateProfileInt("NormalView","Waves",0,render.cfg)`.
  `DAT_009454c8` is Redux's `waveEnable`.
- `0x0061D2D0` (cheat handler): `test_for_cheat("waves")` toggles `DAT_009454c8`.
- Per-map `Wave=` / `Lava=` are still read into `waveMat` / `lavaMat` on mission load.

**But**: this only feeds the **legacy/software terrain path**. In hi-res mode Redux
renders terrain through Ogre, and the wave vertex displacement does not reach the
Ogre terrain mesh. So there are two very different implementation targets.

## Implementation avenues

### Avenue A — Legacy/classic renderer (cheap, verify-first)

In classic graphics mode the original `BuildTerrainPolys`-equivalent may still run,
in which case `Wave=N` + `Waves=1` (or the `waves` cheat) already animates tiles
today with **zero code**. Action: set `[NormalView] Waves=1` in the render cfg (or
trigger the `waves` cheat), load a map with `[NormalView] Wave=<tileMat>` in the
TRN, switch to classic renderer, and observe. If it works, document it as a
supported classic-mode feature and we are done for that mode.

Risk: classic mode is rarely used; users want this in hi-res.

### Avenue B — Hi-res Ogre (the real ask: animated lava/water)

Redux draws terrain as Ogre mesh chunks. To animate lava/water tiles we animate at
the **Ogre material** level, which also gives a *better* look than the old Y-bob
(scrolling/rippling texture rather than a jiggling mesh). Two sub-options:

- **B1 — UV/texture scroll (recommended).** Attach an Ogre `Controller` (or per-frame
  `TextureUnitState::setTextureScroll`) to the material(s) used by the Wave/Lava tile
  ids. Lava = slow scroll + additive emissive ramp (reuse `LavaColors` intent);
  water = faster dual-layer scroll. Cheapest, no vertex program, looks great.
- **B2 — Vertex wave program.** A small GLSL/HLSL vertex program that offsets Y by
  `sin(time + worldX)` — a faithful port of `WaveTable`. More work, needs shader
  assets, only worth it if we specifically want geometry motion.

#### What B needs from OpenShim (the actual work)

1. **Find the terrain material(s).** OpenShim already has the Ogre proc-resolution
   plumbing (`ResolveOgreProc`, `SubEntity::getMaterialName`, the SceneManager at
   `0x00920EA0`). Add a probe that dumps terrain-chunk entity → material names to
   identify which Ogre materials cover the terrain, and whether tile material id is
   recoverable per submesh. (Analogous to the existing `[SKINNING]` material probe.)
2. **Map TRN `Wave`/`Lava` id → Ogre material.** Determine whether Redux bakes the
   TRN tile-material id into distinct Ogre materials/submeshes or a texture atlas.
   This is the key unknown and gates B — if it's one atlased material for all
   terrain, we animate a specific atlas region (harder) rather than a named material.
3. **Drive the animation.** Resolve `MaterialManager::getByName` +
   `Technique/Pass/TextureUnitState` procs (not yet bound in `bzr_hooks.cpp` — only
   billboard/entity material procs are). Then either register a `ControllerManager`
   value or update scroll offset from the existing per-frame render-queue hook the
   chunk bridge already installs.
4. **Config + gating.** Read per-map `[NormalView] Wave`/`Lava` (already parsed by
   the engine — can also read the TRN directly), plus a global
   `[Display] AnimatedTiles` opt-in in `openshim.ini` (default off), consistent with
   the JetFlames/feature-registry pattern. Keep it SP-gated / MP-safe like other
   cosmetic features.

## Recommendation

1. First do **Avenue A verification** (minutes, possibly free) and document the
   result.
2. For hi-res, the gating unknown is **step B-2** (does tile material id survive into
   a targetable Ogre material?). Land the **terrain material probe (step B-1)** as a
   small diagnostic first; its output decides whether B1 is a clean named-material
   animation or an atlas-region problem. Only after that is the animation itself a
   short job on top of existing OpenShim Ogre plumbing.

## Key addresses

| Symbol | 1.5 | Redux (GOG) |
|--------|-----|-------------|
| waveEnable global | `waveEnable` | `DAT_009454C8` |
| `waves` cheat | `0x00234001` region | `0x0061D2D0` |
| render-cfg `Waves` load | `0x00335329` | `0x0077E490` |
| `Wave`/`Lava` per-map read | `~0x00335561` | mission-load (waveMat/lavaMat) |
| WaveTable sine LUT | `0x00520818` | (legacy path only) |
| Wave vertex displace | `0x005220C6` | (legacy path only) |
