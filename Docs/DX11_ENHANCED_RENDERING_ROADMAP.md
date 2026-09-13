# DX11 Enhanced Rendering Roadmap

Status: proposed canonical direction for future DX11 Enhanced rendering work.

Last updated: 2026-09-13.

The preferred direction is to turn DX11 Enhanced into **one coherent rendering
pipeline**, rather than continuing to layer isolated effects onto the current
LDR renderer.

This document is a roadmap, not a promise that every phase will ship exactly as
written. Each milestone must remain independently switchable, preserve a clean
fallback to Redux, and be validated against the supported platform lanes before
release.

## Design principles

1. **OpenShim owns renderer capability and generic rendering implementation.**
2. **Extra Utilities (EXU) communicates mission-scoped intent only where static
   material aliases are insufficient.**
3. **Campaign Reimagined (CR) owns art direction, material aliases, environment
   assets, exposure defaults, LUTs, and mission-specific calibration.**
4. **Redux remains the compatibility baseline and fail-open fallback.**
5. **BZCC is clean-room behavioral inspiration only.** Its compiled shaders may
   be inspected to understand observable techniques and behavior, but must not
   be copied, translated mechanically, or redistributed.
6. Prefer Ogre 1.10's existing compositor/render-target APIs plus narrow
   OpenShim hooks over maintaining a custom Ogre distribution unless the
   shipped BZR ABI proves an essential operation unreachable.

Related architecture and evidence:

- [OpenShim Render Profile Architecture](OPENSHIM_RENDER_PROFILE_ARCHITECTURE.md)
- [DX11 Enhanced FXAA](DX11_ENHANCED_FXAA.md)
- [OpenShim DX11 Color-Space Diagnostic](DX11_COLORSPACE_DIAGNOSTIC.md)
- [BZCC/BZR DX11 Runtime Probe Report](../reverse_engineering/bzcc_bzr_dx11_probe/BZCC_BZR_DX11_RUNTIME_PROBE_REPORT.md)
- Campaign Reimagined: `Docs/DX11_COLOR_SPACE_AUDIT.md`
- Campaign Reimagined: `Docs/DX11_STATIC_IBL.md`

---

## What BZCC suggests

Inspection of BZCC's compiled DX11 shaders provides several useful behavioral
reference points. These are **not** a source-code port target.

| BZCC technique | Current BZR Enhanced state | Recommendation |
| --- | --- | --- |
| SM5 forward lighting with roughness-aware environment reflection | GGX plus static split-sum IBL already exists | Keep BZR's model; add planet-specific environments |
| Four PSSM cascades with hardware-comparison PCF | Three cascades with comparison PCF, overlap blending, bias, and far fade | Validate the existing system first; add a fourth cascade only if captures justify it |
| Up to 16 lights | Enhanced High already supports 24 contribution-ranked lights | BZR is ahead; do not increase the light count |
| Four-layer terrain material blending | BZR receives a legacy atlas without equivalent layer-weight data | Borrow the visual goal through macro variation, anti-tiling, and HD semantic terrain rather than attempting a literal port |
| Dedicated animated water with normal blending and reflection | No equivalent CR water pipeline | Useful as an optional later feature for maps that actually contain water |
| LOD-consistent material model | Enhanced PBR/IBL currently falls back to compatibility shading at medium/low LOD | One of the first problems to fix |

---

# Recommended roadmap

## Phase 0 — Finish and stabilize today's renderer

### 0.1 Close out current terrain-normal and lighting work

Visually validate the recent:

- `N·V` diffuse correction;
- detail-normal derivation;
- shadow-bias changes.

Resolve the remaining terrain dark-region / cotangent-frame question.

Qualification should explicitly include:

- camera motion;
- grazing sun angles;
- normal-map mip transitions;
- the High-to-Medium LOD boundary.

### 0.2 Complete renderer ownership migration

Make OpenShim's namespaced shader payload the canonical generic Enhanced
implementation.

Campaign Reimagined remains responsible for:

- art direction;
- aliases;
- materials;
- environment assets;
- mission configuration.

Remove duplicated CR/OpenShim shader implementations **only after binary and
visual parity is proven**.

EXU should carry mission-scoped renderer intent only when static material aliases
or mission configuration are insufficient.

### 0.3 Establish a repeatable visual benchmark

Create fixed saves and camera positions for at least:

- Moon;
- Mars;
- Venus;
- Titan;
- a dense base battle.

Capture comparison sets for:

- Redux;
- Enhanced;
- Retro;
- shadows off/high;
- each effect off/on where a feature gate exists.

Record with each capture:

- GPU frame time;
- draw count;
- shader permutation;
- framebuffer format;
- active renderer/backend;
- active render profile and relevant feature gates.

Continue requiring unchanged compatibility paths to remain DXBC-identical where
that is the appropriate regression contract.

This phase should close the pending acceptance work already described in CR's
`Docs/DX11_COLOR_SPACE_AUDIT.md` and OpenShim's
`Docs/OPENSHIM_RENDER_PROFILE_ARCHITECTURE.md`.

---

## Phase 1 — Highest-return upgrades without rebuilding the renderer

### 1.1 Enhanced shading through the full LOD chain

Create dedicated DX11 Enhanced Medium and Low delegates that retain the same
material interpretation as High:

- identical albedo / F0 / roughness conventions;
- simplified GGX direct lighting;
- lower-cost IBL;
- specular antialiasing;
- identical normal orientation;
- identical color-space conventions.

Reduce sample count or disable fine detail by LOD, but **do not switch material
models**. The goal is to eliminate visible lighting and reflection pops around
the existing ~250/300-unit LOD boundaries.

**Ownership:** OpenShim shaders/programs; CR validates its materials.

### 1.2 Planet-specific IBL

Replace the neutral bootstrap environment with curated Moon, Mars, Venus,
Titan, and space environments:

- diffuse irradiance cube;
- prefiltered specular cube with a full roughness mip chain;
- shared BRDF LUT;
- optional mission exposure/intensity calibration.

OpenShim should select and bind the environment. CR should own the art assets
and aliases. If environment selection must change during a mission, add a narrow
EXU/OpenShim intent bridge rather than campaign code manipulating Ogre directly.

This is likely the highest-return immediate improvement for vehicles and
buildings because the BRDF infrastructure already exists. See CR
`Docs/DX11_STATIC_IBL.md`.

### 1.3 Terrain anti-tiling and material coherence

Implement progressively:

1. low-frequency world-space macro color variation;
2. hash-selected quarter turns / mirroring of repeat-detail samples;
3. distance-faded detail-normal and roughness influence;
4. slope-aware rock response;
5. optional triplanar detail only on steep slopes;
6. consistent filtering and mip behavior across atlas boundaries.

Do **not** attempt BZCC-style four-layer blending until BZR supplies trustworthy
per-vertex or per-tile weights. OpenShim's semantic/HD terrain work may
eventually provide that data, but it should not block the shader-only anti-tiling
pass.

**Ownership:** generic math in OpenShim; planet tuning and optional macro
textures in CR.

### 1.4 Better bloom and antialiasing

Replace the current single half-resolution 13-tap glow blur with a namespaced,
multi-scale bloom implementation:

- 1/2-resolution level;
- 1/4-resolution level;
- 1/8-resolution level;
- Dual-Kawase or a similar low-cost downsample/upsample filter;
- preserve the explicit glow-material mask initially;
- prevent HUD and overlays from becoming bloom sources;
- keep dirt/anamorphic effects optional and purely artistic.

For antialiasing:

- retain FXAA as the inexpensive setting;
- prototype SMAA 1x as the sharper quality setting.

SMAA's local-contrast and diagonal-pattern handling makes it a sensible spatial
alternative without requiring motion vectors. Move AA into the controlled post
chain when possible so it can run after tone mapping but before HUD composition.
The current terminal FXAA processes the HUD too; see
[DX11 Enhanced FXAA](DX11_ENHANCED_FXAA.md).

Reference: the original SMAA paper/reference implementation should be treated as
algorithmic guidance, not BZR-specific code.

---

## Phase 2 — Proper linear/HDR renderer

This is the largest architectural upgrade and the prerequisite for truly modern
bloom, grading, exposure, and transparent lighting.

### Target pipeline

1. Render the world into `R16G16B16A16_FLOAT`.
2. Mark artist-authored color textures for sRGB decoding while keeping normals,
   masks, shadow maps, LUTs, and numerical IBL data linear.
3. Remove per-object final sRGB encoding and preserve values above `1.0`.
4. Migrate sky, terrain, objects, particles, effects, fog, and translucent world
   passes into the same linear working space.
5. Extract bloom from HDR radiance before tone mapping.
6. Apply controlled exposure, a filmic tone mapper, and a planet/mission
   color-grading LUT.
7. Encode once into the ordinary presentation buffer.
8. Draw HUD, scope, PDA, and overlays afterward in display space.
9. Run spatial AA at the intended presentation boundary.

Ogre 1.10 already exposes FP16 compositor targets, MRT definitions, compositor
chains, and hardware-gamma controls. Prototype through those APIs plus OpenShim
hooks first. Do not create a custom Ogre distribution unless runtime/ABI
research proves a necessary operation is otherwise unreachable.

### Ownership

**OpenShim**

- render targets;
- compositor order;
- formats;
- feature gates;
- resize handling;
- device-loss handling.

**Campaign Reimagined**

- grading LUTs;
- exposure defaults;
- bloom art direction;
- planet-specific calibration.

**Ogre**

- reference implementation and existing API surface initially;
- not a new distribution fork by default.

---

## Phase 3 — Depth-aware grounding

Begin only after HDR and render-target ownership are stable.

1. Expose a shader-readable depth buffer, or add a controlled depth/normal
   prepass.
2. Implement half-resolution spatial GTAO with depth-aware denoising.
3. Bind the AO result into world shaders and modulate **ambient/IBL only** — not
   direct sunlight, emissive, fog, or HUD.
4. Add optional short-range screen-space contact shadows after AO is stable.

Intel's XeGTAO reference describes the required depth preprocessing, AO
evaluation, and denoise stages and confirms that depth, plus optionally
screen-space normals, are the key integration inputs.

Do **not** implement AO by multiplying the finished LDR frame. That would
incorrectly darken direct lighting, emissive surfaces, atmospheric effects, and
presentation overlays.

---

## Phase 4 — Optional specialty tracks

Pursue these only when a real campaign scene demonstrates a need:

- water with dual animated normals, Fresnel reflection, shallow/deep absorption,
  shoreline foam, and optional planar reflection;
- local or box-projected reflection probes for hero interiors;
- weather-driven wetness, dust accumulation, snow/frost, or heat shimmer;
- optional parallax/height mapping on explicitly authored hero materials;
- a fourth shadow cascade or limited PCSS **only if benchmarks show distant
  shadow quality is a real problem**;
- upscaling plus sharpening for low-end hardware.

---

# Deferred for now

## Temporal AA / temporal upscaling / DLSS-class features

TAA, FSR2-style temporal upscaling, and DLSS-class integration require a much
larger prerequisite set:

- camera jitter;
- reliable motion vectors for rigid and skinned geometry;
- history invalidation;
- transparency handling;
- reactive masks.

Do not start here.

## Screen-space reflections

SSR requires robust depth/normal buffers and still provides poor coverage for
BZR's large open landscapes. Revisit only after the depth infrastructure exists
and a scene demonstrates sufficient value.

## Deferred rendering

A deferred renderer is too large an architectural rewrite for the likely return.
Keep the forward renderer and improve its supporting pipeline.

## More than 24 dynamic lights

Do not increase the current Enhanced High light budget. Contribution-ranked 24
lights already exceed the BZCC reference point and further growth is more likely
to increase cost than visible quality.

## Literal BZCC terrain or shadow ports

Do not attempt a literal port. The engine inputs, content model, and scale are
different. Borrow visual goals and validate independent BZR-native solutions.

---

# Suggested PR sequence

1. Current terrain/lighting visual closeout.
2. Canonical OpenShim shader ownership and full Enhanced LOD chain.
3. Planet-specific IBL.
4. Terrain anti-tiling.
5. Multi-scale selective bloom plus SMAA option.
6. FP16 linear/HDR scene pipeline.
7. Tone mapping, exposure, and planet LUTs.
8. Depth exposure and ambient-only GTAO.
9. Optional water/reflection/weather tracks.

Each PR/milestone should:

- be independently switchable where practical;
- fail back cleanly to Redux;
- document runtime capability/fallback state;
- preserve unaffected paths byte-for-byte or DXBC-identically where that is the
  established contract;
- include visual/performance evidence appropriate to the change.

---

# Validation and release policy

Primary development and first live qualification should use GOG because it is
the controlled reference install. Before release, validate:

1. Windows GOG;
2. Windows Steam;
3. Linux/Steam under Proton;
4. Linux/GOG under the supported Wine/Proton lane where applicable.

Final Steam evidence for Workshop-delivered rendering resources must come from an
**uploaded-and-redownloaded Workshop payload**, never from a direct edit of the
Steam Workshop cache.

The benchmark set from Phase 0 should remain the visual regression suite for all
later phases.

---

# Current execution caveat — 2026-09-13

At the time this roadmap was written, CR's active renderer work was ahead of its
remote, while the OpenShim checkout contained uncommitted shader/diagnostic work
on a branch behind its remote. Those workstreams should be landed, split into
coherent branches, or otherwise reconciled before implementation begins. Do not
start roadmap work by absorbing unrelated local renderer changes into a new
feature branch.
