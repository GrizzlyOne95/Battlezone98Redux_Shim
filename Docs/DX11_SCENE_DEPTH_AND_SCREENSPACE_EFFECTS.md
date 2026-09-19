# DX11 scene depth and screenspace-effects investigation

Status: research/design anchor; no renderer implementation in this change.

Target: GOG Battlezone 98 Redux 2.2.301, D3D11 backend, OpenShim DX11 Enhanced.

## Purpose

Investigate one reusable **OpenShim scene-depth service** rather than solving depth access separately for SSAO, weather soft particles, depth haze, interactive fog, water intersections, and future contact/depth-aware effects.

OpenShim owns renderer capability and generic rendering implementation. ExtraUtilities (EXU) may later express mission-scoped intent through a narrow request/status bridge, but EXU must not own D3D11 resources, hook the render system, or manage scene-depth/compositor lifetime.

This investigation is motivated by two external reference packages supplied for analysis. They are **behavior/algorithm references only**. No file, shader, texture, DLL, or code from either package is committed here.

## Reference archives and provenance

Keep the original archives byte-for-byte unchanged outside this repository.

| Archive | SHA-256 | Relevant contents |
| --- | --- | --- |
| `ShaderSSAO-215-3-0-1549132333.zip` | `4cb66a9c59e4308838dae916abbcb0a9f36900e664f5b533a51d69c2c7d8dbe3` | Native Ogre SSAO compositor/material/HLSL reference |
| `KENSHI ENHANCED 1.0-945-1-1-1777749127.zip` | `a27a3a3a61849d7d76a191c2734c9ee15d663774c93765cea8a848d1a1d00080` | ReShade AO/SSDO, depth haze, bloom, depth helpers, effect toggling |

### `ShaderSSAO` files inspected

- `ShaderSSAO/materials/compositors/SSSAO.compositor`
- `ShaderSSAO/materials/post/SSSAO.hlsl`
- `ShaderSSAO/materials/post/SSAOB.hlsl`
- `ShaderSSAO/materials/post/SSAOF.hlsl`
- `ShaderSSAO/materials/post/SSSAO.material`
- `ShaderSSAO/materials/random.png`

Observed design:

- Ogre 2.x-style `compositor_node` integration, so the script itself is **not** a BZR/Ogre 1.10 drop-in.
- Inputs are a normal buffer plus depth (`global_gbuffer` slots in the reference).
- AO runs at half resolution.
- AO kernel uses 16 sample vectors and a random/noise texture to rotate the sample pattern.
- AO includes configurable radius/range, strength, near/far cutoff, and distance falloff.
- The included blur is an expensive geometry-unaware radial filter (`12` angular steps x `10` radial steps, roughly 120 taps per pixel). Treat this as something to improve, not copy.

### Kenshi Enhanced files inspected

Priority references:

- `reshade-shaders/Shaders/PPFX_SSDO.fx`
- `reshade-shaders/Shaders/AstrayFX/GloomAO.fx`
- `reshade-shaders/Shaders/MXAO.fx`
- `reshade-shaders/Shaders/OtisFX/DepthHaze.fx`
- `reshade-shaders/Shaders/PD80/PD80_02_Bloom.fx`
- `reshade-shaders/Shaders/ReShade.fxh`
- `ReshadeEffectShaderToggler.ini`

Useful observed patterns:

1. **Normal reconstruction from depth.** `PPFX_SSDO.fx` samples neighboring linear depths and builds an approximate view-space normal with a cross product. `GloomAO.fx` contains a more elaborate depth/normal reconstruction path. This suggests BZR should first prototype AO from depth alone before adding a persistent normal MRT/G-buffer.
2. **Depth-bilateral filtering.** `PPFX_SSDO.fx` rejects/attenuates blur samples across depth discontinuities. This is a better model for BZR AO filtering than the reference ShaderSSAO radial blur.
3. **Depth-aware haze filtering.** `OtisFX/DepthHaze.fx` uses separable horizontal/vertical filtering and weights neighboring samples by depth difference to avoid bleeding across strong geometry edges.
4. **Multi-stage post processing.** The prod80 bloom reference is useful as architecture inspiration for staged post-processing, but OpenShim's existing Enhanced roadmap remains authoritative for bloom/HDR design.
5. **Scene/UI separation.** The ReShade effect-toggler configuration is evidence of the practical need to keep world post effects away from UI/HUD draws. BZR should solve that in its own renderer ordering rather than depend on shader-signature toggling.

## Licensing rule

Do **not** port these shader files mechanically.

The Kenshi package is a mixed-license collection. Examples observed in the archive include:

- `MXAO.fx`: CC BY-NC-ND 3.0;
- `AstrayFX/GloomAO.fx`: Attribution-NoDerivatives 4.0 for portions identified by its header;
- `PD80_02_Bloom.fx`: MIT for the identified prod80 portions;
- other effects have their own authorship/license provenance.

Therefore:

- use these packages to identify techniques, data flow, tuning categories, and failure modes;
- implement OpenShim code independently from first principles, papers, Microsoft/D3D11 documentation, Ogre 1.10 APIs, or clearly compatible permissive references;
- do not copy shader source, kernels, constants, comments, textures, binaries, or packaged assets unless a later change performs a specific license/provenance review.

## Existing BZR evidence that constrains the design

This investigation builds directly on:

- `Docs/FOG_COMPOSITOR_QUALIFICATION_20260908.md`
- `Docs/DX11_ENHANCED_RENDERING_ROADMAP.md`
- `Docs/DX11_ENHANCED_FXAA.md`
- `src/patches/dx11_enhanced_fxaa.cpp`
- PR #165 (`wip(fog): interactive fog wake renderer`) as a potential future depth-service consumer, not as the depth-service implementation.

The fog qualification established the important current constraints:

1. BZR's shipped Ogre D3D11 path creates an `R32_TYPELESS` main depth resource, but with the normal BZR `FSAA=8` configuration Ogre does **not** add `D3D11_BIND_SHADER_RESOURCE`.
2. At FSAA=0 Ogre can create a depth SRV, but its render-system member is not a reliable per-main-view depth handle: other render targets can overwrite it.
3. Sampling a depth resource while it remains bound as a writable DSV is invalid; the sampling pass must establish a safe read state.
4. The ordinary Ogre render queue is not a reliable "world complete, HUD not yet drawn" boundary in Redux. Vehicles pass through it, while terrain/cockpit/HUD have different ordering paths.
5. The existing Enhanced FXAA hook is a useful state-save/fullscreen-pass reference but is terminal and therefore too late for world-only SSAO/haze if HUD/cockpit are already present.

This means **depth resource access and effect insertion/order are separate problems**. Do not conflate them.

## Core architectural proposal

Build one internal OpenShim facility that can eventually expose:

```text
main-scene depth resource discovery
        |
        v
MSAA depth shader access / extraction
        |
        v
OpenShim-owned linear depth texture
        |
        +--> normal reconstruction
        +--> SSAO / SSDO-style obscurance
        +--> depth-aware haze
        +--> soft particles
        +--> interactive fog depth tests
        +--> water/intersection fades
        `--> later depth-aware effects
```

The first implementation should **not** require a normal G-buffer.

## Phase A - qualify the actual main-scene D3D11 depth resource

Before implementing AO, add diagnostic-only instrumentation that identifies depth resources unambiguously.

Record at minimum:

- `ID3D11Texture2D*` identity;
- width/height;
- `DXGI_FORMAT`;
- `SampleDesc.Count` and quality;
- bind flags;
- DSV format and view dimension;
- when the resource is bound/unbound as the active main DSV;
- render target/view dimensions active alongside it;
- whether the draw belongs to main gameplay, shadow/RTT, satellite, scope, shell/UI, etc. where this can be classified safely;
- resource creation/destruction across mission change, resize, fullscreen/window changes, and shutdown.

Acceptance for Phase A:

- prove which depth texture is the main gameplay depth surface under normal `FSAA=8`;
- distinguish it from shadow maps, satellite/secondary viewports, and temporary RTTs;
- prove its lifetime and resize behavior;
- do not mutate resource creation yet.

## Phase B - prototype shader-readable MSAA depth

The key experiment is whether OpenShim can make the main multisampled depth resource shader-readable without disabling BZR MSAA.

### Creation-time experiment

For the **qualified main scene depth texture only**, investigate augmenting the resource bind flags at creation time:

```cpp
D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE
```

The resource remains typeless (`R32_TYPELESS` is already expected from the shipped path), with appropriate typed views, e.g.:

```text
DSV: D32_FLOAT
SRV: R32_FLOAT + TEXTURE2DMS view dimension
```

Do not globally rewrite all depth resources. Shadow/RTT depth creation must remain untouched unless separately proven safe.

### Important D3D11 rule

D3D11 does not provide the ordinary color-style `ResolveSubresource` path for depth that we can assume here. The proposed experiment is instead:

1. expose the qualified MSAA depth texture as a `Texture2DMS<float>` SRV;
2. temporarily unbind the writable DSV before the sampling pass;
3. sample the individual MSAA depth samples in OpenShim HLSL;
4. reduce them manually into an OpenShim-owned single-sample depth texture;
5. restore the exact prior D3D11 state.

The reduction policy (`min`, `max`, representative sample, conservative rule, etc.) must be selected from BZR's actual depth convention and validated on geometry edges. Do not guess it from API convention.

### Required safety

Copy the state-preservation discipline of `dx11_enhanced_fxaa.cpp`: every mutated render target, DSV, SRV, viewport, shader, sampler, blend/depth/raster state, and binding must be restored on all paths.

Acceptance for Phase B:

- FSAA 8 remains enabled;
- extracted depth visually matches scene geometry and has stable edge behavior;
- no D3D11 debug-layer binding hazards;
- no corruption of shadows/RTTs/satellite view;
- clean resource teardown and recreation.

If augmenting the shipped depth texture is unsafe or impossible, document the failure precisely and fall back to evaluating an OpenShim-owned depth prepass. A prepass is a fallback, not the first choice, because it duplicates scene geometry work.

## Phase C - canonical OpenShim linear-depth product

Create an OpenShim-owned texture representing main-view linear depth with a documented contract.

Questions to settle explicitly:

- full versus half resolution;
- precision/format (`R32_FLOAT` initially unless evidence supports a smaller format);
- near/far/projection parameters and exact linearization formula;
- sky/background sentinel behavior;
- MSAA edge reduction policy;
- whether consumers access raw device depth as well as linear depth;
- frame validity and camera/view identity;
- alternate-camera behavior.

The service must expose state as **requested / supported / effective** rather than silently returning an invalid texture.

Suggested internal shape (names illustrative, not ABI):

```cpp
struct SceneDepthStatus {
    bool supported;
    bool effective;
    uint32_t width;
    uint32_t height;
    uint32_t sampleCount;
    const char* reason;
};

const SceneDepthStatus& GetSceneDepthStatus();
ID3D11ShaderResourceView* GetLinearSceneDepthSRV();
```

Raw COM pointers should remain internal to OpenShim. Any public/EXU bridge should expose capability/state and high-level effect parameters, not D3D11 objects.

## Phase D - reconstruct normals from depth before adding a normal MRT

Prototype view-space normals from neighboring linear-depth samples.

Start with a simple finite-difference/cross-product reconstruction, then improve edge selection if necessary by choosing the lower-depth-discontinuity neighbor on each axis.

Qualification scenes must include:

- flat terrain;
- steep terrain silhouettes;
- thin antenna/weapon geometry;
- vehicles against sky;
- overlapping units;
- building corners;
- grazing camera angles;
- MSAA edges.

Only add a dedicated normal target if captures demonstrate that depth-derived normals cannot meet the visual quality target.

Reason: BZR is a 32-bit process. Avoiding another persistent full-screen target saves both renderer complexity and address-space/VRAM pressure.

## Phase E - first AO prototype

Use the references only for high-level structure:

- half-resolution AO target;
- 8-16 sample quality tiers initially;
- per-pixel noise/rotation to suppress directional banding;
- linear depth + reconstructed view normal;
- radius/range rejection to avoid long-distance halos;
- near/far fade so AO does not fight atmospheric fog;
- physically conservative strength; AO should ground contact and creases, not globally dirty the image.

Do **not** copy the ShaderSSAO 120-tap radial blur.

Instead, use a separable depth-aware filter inspired by the general bilateral principle demonstrated by the references:

```text
AO half-res
  -> horizontal depth/normal-aware filter
  -> vertical depth/normal-aware filter
  -> composite
```

Keep an AO-only debug view and depth/normal debug views during development.

## Phase F - insertion/order integration

Do not ship SSAO by simply running it at today's terminal FXAA point.

The desired long-term ordering remains consistent with `DX11_ENHANCED_RENDERING_ROADMAP.md`:

```text
world / opaque scene
  -> world transparency / particles as defined by the HDR contract
  -> depth-aware world effects (AO/haze/etc.) at their qualified point
  -> bloom / tone mapping / grading
  -> presentation AA
  -> HUD / PDA / overlays at the intended display-space boundary
```

The exact order of AO relative to transparent effects must be chosen from the final linear/HDR scene contract, not from the reference packages.

The current render-order problem found by the fog qualification still requires one of:

- a qualified Redux render-path hook at the correct world/UI boundary; or
- the future OpenShim-owned scene-color/HDR target architecture, which can provide an explicit composition boundary.

Scene depth can be developed and debugged before that boundary exists; world-only post effects should not be considered release-ready until it does.

## Consumers and ownership

### OpenShim owns

- D3D11 depth-resource discovery/hooks;
- MSAA depth access/extraction;
- linear depth product;
- optional normal reconstruction;
- AO implementation and filtering;
- world post-effect render targets/compositor ordering;
- capability/fallback diagnostics;
- resize/device/mission lifecycle;
- quality/performance tiers.

### EXU may own

- mission-scoped requests such as enable/disable, AO strength/radius preset, haze/weather intent;
- Lua API and mission-facing status queries;
- weather/particle systems that consume OpenShim soft-particle capability indirectly.

EXU must **not** receive D3D11 SRVs, depth textures, or compositor instances.

### Campaign Reimagined may later own

- planet/mission tuning;
- artistic default intensity/radius/fade;
- exposure/fog interaction calibration;
- screenshots/visual acceptance for campaign environments.

No CR implementation should be required to qualify the generic depth service.

## Proposed narrow EXU/OpenShim bridge

Do not bind this ABI until OpenShim proves a useful renderer capability. When ready, prefer a versioned, renderer-agnostic surface such as:

```text
SetRenderEffectEnabled(name, enabled)
SetRenderEffectFloat(name, parameter, value)
GetRenderEffectStatus(name)
```

or a small versioned struct/enumeration equivalent.

Status must distinguish:

```text
requested = true
supported = false
effective = false
reason = "scene depth unavailable"
```

from a user-disabled effect.

The public bridge must not expose implementation details like `Texture2DMS`, SRVs, Ogre compositor handles, or shader program names.

## Diagnostics

Add a compact renderer diagnostic block before enabling effects by default. Suggested fields:

```text
SceneDepth requested=1 supported=1 effective=1
source=main-dsv format=R32_TYPELESS samples=8
linearDepth=1920x1080 R32_FLOAT
normalSource=reconstructed
AO requested=1 supported=1 effective=1 quality=medium halfRes=1
```

Failure examples should be equally explicit:

```text
SceneDepth requested=1 supported=0 effective=0 reason=main-depth-not-qualified
AO requested=1 supported=0 effective=0 reason=scene-depth-unavailable
```

## Test matrix

### Render modes

- Enhanced, Redux, Retro fallback behavior;
- FSAA 0/2/4/8 where supported;
- fullscreen/windowed;
- resize and Alt+Tab;
- mission -> shell -> mission;
- repeated mission transitions in one process.

### Cameras/passes

- normal gameplay camera;
- cockpit/interior view;
- sniper/scope where applicable;
- satellite/alternate viewport;
- shadow passes;
- loading/shell/UI-only states.

### Visual AO scenes

- terrain contact under vehicles;
- base buildings and corners;
- clustered units;
- sky silhouettes;
- foggy/distant terrain;
- explosions/particles/transparency crossing AO geometry;
- Moon/Mars/Venus/Titan benchmark saves from the Enhanced roadmap.

### Performance

Capture median/P95 GPU time and persistent render-target memory delta for:

- depth extraction only;
- depth + normal reconstruction;
- low/medium/high AO tiers;
- AO filter/composite;
- effect off baseline.

No effect should remain enabled by default until the cost is known at 1080p, 1440p, and 4K on the benchmark machine(s).

## Relationship to current work

- **PR #165 / interactive fog:** candidate consumer of scene depth if/when its renderer work resumes. Do not couple the depth service specifically to fog wakes.
- **EXU PR #24 / Kenshi-inspired weather:** baseline weather remains EXU/Ogre ParticleFX. The only dependency on this work is optional renderer-level soft-particle/depth-aware enhancement.
- **DX11 Enhanced HDR roadmap:** scene depth may be qualified earlier, but release integration of world post effects should follow the controlled scene-color/HUD ordering established by the renderer roadmap.

## Initial implementation checklist

- [ ] Add read-only D3D11 depth-resource diagnostics; identify main FSAA=8 DSV.
- [ ] Prove depth resource lifetime and distinguish main view from shadow/RTT/secondary views.
- [ ] Prototype creation-time `D3D11_BIND_SHADER_RESOURCE` augmentation for the qualified main depth texture only.
- [ ] Create and validate `Texture2DMS<float>` SRV on the multisampled depth surface.
- [ ] Implement a state-safe MSAA depth extraction pass into an OpenShim-owned single-sample texture.
- [ ] Document/validate BZR depth convention and linearization.
- [ ] Add depth debug visualization.
- [ ] Prototype depth-derived normals; add normal debug visualization.
- [ ] Prototype half-resolution AO with depth/range rejection.
- [ ] Add separable bilateral AO filtering.
- [ ] Measure GPU cost and render-target memory.
- [ ] Qualify the world/UI composition boundary before enabling AO/haze in production.
- [ ] Define the narrow EXU request/status ABI only after the OpenShim capability exists.

## Non-goals for this PR

- no third-party shader/assets import;
- no ReShade dependency;
- no Ogre fork;
- no DX9 depth implementation;
- no default-on SSAO;
- no normal G-buffer commitment;
- no public ABI commitment before the renderer experiment succeeds;
- no claim that a reference algorithm is suitable without BZR-specific visual/performance qualification.
