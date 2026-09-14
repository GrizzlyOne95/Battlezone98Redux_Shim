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
5. **Unknown third-party materials remain fail-open.** Enhanced must not infer
   PBR semantics from arbitrary Workshop content or silently reinterpret custom
   material channels.
6. **BZCC is clean-room behavioral inspiration only.** Its compiled shaders may
   be inspected to understand observable techniques and behavior, but must not
   be copied, translated mechanically, or redistributed.
7. Prefer Ogre 1.10's existing compositor/render-target APIs plus narrow
   OpenShim hooks over maintaining a custom Ogre distribution unless the
   shipped BZR ABI proves an essential operation unreachable.
8. Prefer explicit runtime capability reporting and narrow feature degradation
   over all-or-nothing renderer failure. Requested, supported, and effective
   state must remain distinguishable in diagnostics.

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

- median and P95 GPU frame time over a fixed capture window;
- relevant CPU frame cost where measurable;
- draw count;
- shader/permutation identifier;
- framebuffer/render-target format;
- active renderer/backend;
- active render profile and relevant feature gates;
- render-target and approximate VRAM allocation delta where a phase adds
  persistent scene buffers.

Continue requiring unchanged compatibility paths to remain DXBC-identical where
that is the appropriate regression contract.

The benchmark suite must also include lifecycle cases, not only locked-camera
screenshots:

- mission A -> shell -> mission B;
- repeated mission transitions in one process;
- resize/windowed transitions;
- Alt+Tab;
- supported fullscreen transitions;
- Enhanced/Redux/Retro profile changes where live switching is supported;
- clean shutdown.

This is especially important because BZR remains a 32-bit process: any new
persistent render target, compositor instance, texture, or material path must be
checked for cumulative retention and virtual-address pressure across mission
transitions.

This phase should close the pending acceptance work already described in CR's
`Docs/DX11_COLOR_SPACE_AUDIT.md` and OpenShim's
`Docs/OPENSHIM_RENDER_PROFILE_ARCHITECTURE.md`.

### 0.4 Freeze the Enhanced material and color-space contract

Before expanding the renderer, document one canonical interpretation for every
shader input class.

At minimum:

| Input class | Working interpretation |
| --- | --- |
| Artist-authored albedo/base color | color data; decode from sRGB where the resource path does not already do so |
| Artist-authored emissive color | color data; decode consistently before lighting/composition |
| Normal maps | numerical/vector data; never sRGB decode |
| Roughness/specular/mask channels | numerical material data; never sRGB decode |
| Shadow maps / depth | numerical data; never sRGB decode |
| BRDF LUT | numerical integration data; linear |
| Irradiance/specular IBL products | numerical lighting data; linear |
| Color-grading LUTs | use the transfer/working-space contract defined by the grading implementation; never infer from filename |
| Engine-provided sun/ambient/fog/material RGB constants | classify and calibrate explicitly; do not blindly apply texture-style decoding |

Alpha semantics must also be documented per material family. Do not assume one
meaning for alpha across legacy/custom content when it may represent opacity,
cutout, glow/mask data, or something family-specific.

The purpose of this contract is to stop each later phase from independently
re-deciding color semantics. CR's Stage-A linear-light experiment remains an
opaque-scene experiment, not proof that every world/UI/blended input already has
correct global semantics.

### 0.5 Define third-party/custom material compatibility

Enhanced must remain compatible with arbitrary Workshop materials.

Rules:

- use an Enhanced/PBR delegate only when the material family or technique has an
  explicit compatible contract;
- do not infer roughness, metallic, F0, normal-map meaning, or color-space
  semantics from an unknown custom material;
- unknown/foreign material schemes remain pass-through/fail-open, consistent
  with the render-profile architecture;
- a missing optional IBL, macro, bloom, LUT, AO, or other enhancement resource
  disables/degrades that feature rather than invalidating unrelated rendering;
- mandatory resource failures must report a precise fallback reason.

This compatibility rule should be preserved through every later phase.

### 0.6 Establish shader-permutation discipline

The full LOD chain, shadow/no-shadow variants, terrain/object families,
linear/HDR stages, and optional effects can otherwise create an unmaintainable
permutation matrix.

Policy:

- prefer runtime constants/branches where the cost is negligible and a compile-
  time permutation would add more maintenance than performance value;
- use compile-time variants only when they materially reduce work or are
  required by the Ogre program/material contract;
- keep all generic Enhanced program names OpenShim-namespaced;
- compile/validate every required shipped shader variant in CI;
- preserve DXBC identity for explicitly unchanged compatibility delegates where
  that remains the contract;
- record the active permutation in diagnostics/benchmark evidence.

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
- identical color-space conventions;
- consistent cutout/alpha-test behavior;
- consistent shadow-caster/receiver semantics at LOD transitions.

Reduce sample count or disable fine detail by LOD, but **do not switch material
models**. The goal is to eliminate visible lighting and reflection pops around
the existing ~250/300-unit LOD boundaries without introducing shadow or cutout
pops in their place.

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

IBL assets must be reproducible rather than opaque binary drops. For every
shipped environment, retain or document:

- source environment/provenance;
- cubemap face orientation/convention;
- source and generated resolutions/formats;
- irradiance convolution method;
- specular prefilter/convolution method;
- roughness-to-mip mapping;
- BRDF LUT generation/version;
- intensity/exposure calibration;
- hashes or version metadata for generated payloads.

Prefer a small repeatable conversion/build tool or script in CR/tooling so the
DDS products can be regenerated from their source assets.

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

During Phase 1, the explicit glow/material mask remains the authoritative bloom
source. Once Phase 2 provides meaningful HDR radiance above `1.0`, evaluate a
hybrid model in which authored emissive intent and HDR-radiance thresholding can
both contribute. Do not silently discard authored glow semantics merely because
an HDR threshold becomes available.

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

**Scope terminology:** in this roadmap, "HDR" initially means an **internal
linear FP16 scene pipeline**. The first target still presents through the normal
SDR `R8G8B8A8_UNORM` path after tone mapping/encoding. Windows HDR10, scRGB,
wide-gamut display negotiation, HDR metadata, and HDR-monitor output are **not**
part of this milestone and should be treated as a separate future presentation
track.

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
7. Encode once into the ordinary SDR presentation buffer.
8. Draw HUD, scope, PDA, and overlays afterward in display space.
9. Run spatial AA at the intended presentation boundary.

Ogre 1.10 already exposes FP16 compositor targets, MRT definitions, compositor
chains, and hardware-gamma controls. Prototype through those APIs plus OpenShim
hooks first. Do not create a custom Ogre distribution unless runtime/ABI
research proves a necessary operation is otherwise unreachable.

### 2.1 Transparency, particles, blending, and cutouts

This is a required part of the HDR migration, not polish to defer until later.
Define and validate:

- linear-space alpha blending;
- the straight-alpha versus premultiplied-alpha contract for each relevant
  material/effect family;
- additive emissive/thruster/projectile effects;
- alpha-test/cutout materials and matching depth/shadow behavior;
- particle texture color-space semantics;
- translucent depth-write/test policy;
- sorting/order dependencies;
- fog interaction with translucent objects;
- how bloom extraction treats transparent emissive radiance.

Mandatory visual qualification scenes should include explosions, smoke, dust,
weapon effects, thrusters/glows, transparent/cutout geometry, fog boundaries,
and particles crossing bright sky/terrain backgrounds.

Do not ship the FP16 path based only on opaque vehicle/building captures.

### 2.2 Exposure and tone mapping policy

Start with deterministic planet/mission exposure rather than immediately adding
adaptive auto-exposure. BZR has abrupt luminance changes from cockpits, muzzle
flashes, explosions, bright skies, scopes, and shell/UI transitions; automatic
exposure can create distracting pumping if introduced without a robust temporal
policy.

Initial requirements:

- explicit exposure per environment/mission with sane global defaults;
- one documented filmic tone-mapping operator/curve;
- exposure and grading applied before final SDR encoding;
- UI/HUD excluded from world exposure;
- deterministic screenshot/benchmark output.

Adaptive exposure can be evaluated later as an optional feature with luminance
metering regions, adaptation rates, clamps, history invalidation, and UI/camera
transition handling.

### Ownership

**OpenShim**

- render targets;
- compositor order;
- formats;
- feature gates;
- capability/fallback reporting;
- resize handling;
- device-loss handling;
- render-target/resource teardown across mission and renderer lifecycle events.

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

# Feature dependency and capability model

The roadmap phases are ordered for dependency, but not every Phase-1 feature
blocks every other Phase-1 feature. Treat the renderer as a capability graph,
not one monolithic "Enhanced v2" switch.

Baseline dependency shape:

```text
material/color-space contract
        |
        +--> full Enhanced LOD chain
        |
        +--> planet-specific IBL
        |
        +--> terrain anti-tiling

renderer ownership + lifecycle stability
        |
        +--> multi-scale post chain
        |
        +--> FP16 linear scene
                  |
                  +--> HDR bloom
                  +--> tone map / exposure / LUT
                  +--> correct transparent HDR composition
                  |
                  +--> depth exposure / prepass
                             |
                             +--> GTAO
                             +--> contact shadows
```

Each independently gated feature should report, where applicable:

- requested state;
- capability/support state;
- effective state;
- fallback/degradation reason.

A failure of one optional capability must not silently disable unrelated
capabilities. For example, missing planet-specific IBL may fall back to neutral
IBL while Enhanced LOD shading remains active; unavailable GTAO must not disable
the FP16 scene pipeline.

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

## HDR display output

HDR10/scRGB/wide-gamut monitor output is separate from the internal FP16 scene
pipeline. It requires presentation color-space negotiation, output capability
probing, transfer/gamut policy, metadata where applicable, UI luminance policy,
and independent platform qualification. Do not let this scope block the SDR-
presented linear/HDR scene pipeline.

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

1. Current terrain/lighting visual closeout plus frozen material/color-space
   contract and benchmark suite.
2. Canonical OpenShim shader ownership, third-party material fail-open policy,
   shader-permutation discipline, and full Enhanced LOD chain.
3. Planet-specific IBL plus reproducible asset-generation pipeline.
4. Terrain anti-tiling.
5. Multi-scale selective bloom plus SMAA option.
6. FP16 linear/HDR scene pipeline with lifecycle/resource teardown proof.
7. Correct transparent/particle/effect composition in the linear scene.
8. Tone mapping, fixed exposure, and planet LUTs.
9. Depth exposure and ambient-only GTAO.
10. Optional water/reflection/weather tracks.

Each PR/milestone should:

- be independently switchable where practical;
- fail back cleanly to Redux;
- preserve foreign/custom material behavior unless explicitly opted into a
  documented Enhanced contract;
- document requested/supported/effective capability and fallback state;
- preserve unaffected paths byte-for-byte or DXBC-identically where that is the
  established contract;
- include visual/performance evidence appropriate to the change;
- include lifecycle/resource-retention evidence when it allocates persistent
  GPU/CPU renderer resources.

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

For phases that add persistent compositor/render-target resources, release
qualification must also include repeated mission transitions and process-
lifetime memory/resource observations. A visual pass on the first mission is not
sufficient acceptance for a 32-bit renderer path.

---

# Current execution caveat — 2026-09-13

At the time this roadmap was written, CR's active renderer work was ahead of its
remote, while the OpenShim checkout contained uncommitted shader/diagnostic work
on a branch behind its remote. Those workstreams should be landed, split into
coherent branches, or otherwise reconciled before implementation begins. Do not
start roadmap work by absorbing unrelated local renderer changes into a new
feature branch.
