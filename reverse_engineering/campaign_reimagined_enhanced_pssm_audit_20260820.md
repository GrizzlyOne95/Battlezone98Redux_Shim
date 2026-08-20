# Campaign Reimagined DX11 Enhanced PSSM audit

Date: 2026-08-20
Branches: `agent/enhanced-pssm-bzcc` in OpenShim and Campaign Reimagined
Runtime references: BZR 1.5 GOG executable; installed BZCC 2.0.185 Steam depot

This report reconstructs the BZR/CR path, compares it with the actual shipped
BZCC shaders, and records the backport decision. `CONFIRMED` means direct source,
decompilation, binary table, shader reflection/disassembly, or compilation
evidence. `HIGH` means several direct facts support the conclusion but a named
engine call or runtime value was not observed directly. `MEDIUM` is a bounded
inference. `SPECULATIVE` identifies an unresolved hypothesis.

## Scope and result

The safe subset is implemented in CR content only:

- three cascades and all Ogre camera setup remain unchanged;
- hard cascade boundaries become two-unit smooth blend bands matching Ogre's
  existing one-unit split padding;
- the 16-read manual filtered-depth compare becomes four-tap hardware
  comparison PCF;
- object and terrain receivers receive a small, bounded, distance-growing normal
  offset adapted from BZCC;
- the final 24 units fade shadow contribution to fully lit and samples stop at
  the 256-unit outer limit.

No OpenShim runtime patch or Ogre binary change is required. DX9, DX11 Classic,
stock Redux materials, non-PSSM variants, gameplay, and multiplayer state are
unchanged. Stabilization was not implemented: the BZR Focused/LiSPSM path is
statically shown to permit swimming, but BZCC's CPU-side stabilization behavior
is not recoverable from its baked shaders and the appropriate BZR hook is much
higher risk than the shader-only subset.

## Evidence inventory

### Current BZR and Ogre

- `reverse_engineering/decompilation_from_1.5_exe-pdb/Redux/Raw .C/FUN_00680fe0-00680fe0.c`
- local Ogre 1.10 source:
  - `OgreMain/src/OgreShadowCameraSetupPSSM.cpp`
  - `OgreMain/src/OgreShadowCameraSetupFocused.cpp`
  - `OgreMain/src/OgreShadowCameraSetup.cpp`
  - `OgreMain/src/OgreTextureUnitState.cpp`
  - `RenderSystems/Direct3D11/src/OgreD3D11Mappings.cpp`
- CR material/program/HLSL sources named below

### BZCC

- installed shader depot:
  `C:/Program Files (x86)/Steam/steamapps/common/BZ2R/bz2r_res/baked/shaders`
- representative disassemblies:
  - `dx11_default_psh_0pdlz.fxc`
  - `dx11_default_vsh_0vlz.fxc`
  - `dx11_terrain_vsh_8vlz.fxc`
- existing local reflection/hash evidence:
  `reverse_engineering/bzcc_bzr_dx11_probe/`
- installed `BZCC_TO_BZR_SHADER_RENDER_BACKPORT_REPORT.md`

The local `BZ2_Source` checkout is the older Battlezone II mission/game source,
not the BZCC renderer. `BZCC-Source-Assets` contains source art/ODF assets but no
modern renderer HLSL. No recoverable modern BZCC HLSL was found. Consequently,
the installed shipped DXBC is the strongest available evidence for BZCC shader
behavior. Discussion-derived notes mentioning Ken were searched in the local
Git corpus; no shadow/PSSM-specific Ken note was found.

## Phase 1: current BZR/CR reconstruction

### CPU shadow selection and allocation — CONFIRMED

`FUN_00680fe0` reads the shadow-quality byte at settings offset `+0x25`, clamps
it to four, and indexes two executable tables:

| quality index | mode flag at `0x008ED0BC` | texture size at `0x008ED0C8` |
|---:|---:|---:|
| 0 | 0 (single) | 1024 |
| 1 | 0 (single) | 2048 |
| 2 | 1 (PSSM) | 1024 |
| 3 | 1 (PSSM) | 2048 |
| 4 | 1 (PSSM) | 4096 |

A negative quality disables shadows. For PSSM the executable calls the scene
manager shadow-texture setup with `(size, 3, 0x21, 0, 1)`. Ogre declares
`PF_FLOAT32_R = 33 (0x21)`, and the DX11 backend maps it to
`DXGI_FORMAT_R32_FLOAT`. The same function requests three directional-light
textures with `setShadowTextureCountPerLightType(LT_DIRECTIONAL, 3)`.

The nearby virtual calls pass `128.0`, `0.8`, and `192.0`. Their placement and
Ogre API shape identify the shadow far distance/directional texture
offset/extrusion settings with HIGH confidence; the raw constants themselves
are CONFIRMED. They are not modified by this work.

### PSSM camera setup — CONFIRMED

The executable constructs `Ogre::PSSMShadowCameraSetup`, enables aggressive
focus, supplies a camera/light direction threshold from the renderer settings,
and installs these explicit split points:

```text
0.1, 16.0, 64.0, 256.0
```

It sets all three per-split optimal-adjust factors to `0.0`, then installs the
setup on the scene manager. The four points produce three cascades:

```text
[0.1, 16], [16, 64], [64, 256]
```

Ogre's `PSSMShadowCameraSetup` constructor defaults `mSplitPadding` to `1.0`.
`getShadowCamera()` subtracts it from every non-first near plane and adds it to
every non-last far plane. Actual camera coverage therefore overlaps at
`[15,17]` and `[63,65]`. CR previously discarded that overlap by choosing one
cascade with a hard pixel-shader branch.

### Matrix and constant path — CONFIRMED

The CR program scripts bind:

```text
texWorldViewProj1 <- texture_worldviewproj_matrix 0
texWorldViewProj2 <- texture_worldviewproj_matrix 1
texWorldViewProj3 <- texture_worldviewproj_matrix 2
pssmSplitPoints   <- float4 0.1 16.0 64.0 256.0
```

Files and entry points:

| family | program | HLSL entry | projected outputs |
|---|---|---|---|
| objects | `Shaders/CR_base.program` | `base_vertex`, `base_fragment` in `CR_base-sm4.hlsl` | `TEXCOORD5/6/7` |
| terrain | `Shaders/CR_terrain.program` | `terrain_vertex`, `terrain_fragment` in `CR_terrain-sm4.hlsl` | `TEXCOORD6/7/8` |
| IBL overrides | `Shaders/CR_static_ibl.program` | same fragment entries | same shadow contract |

FXC places all five object/terrain vertex matrices in `cb0`: WVP at byte 0,
world-view at 64, and cascade matrices at 128, 192, and 256. The vertex shader
stores `oPosition.z` in `vDepth`; the pixel shader compares that exact
interpolant against `.y` (16) and `.z` (64). This is observed behavior, not an
interpretation of the variable name.

In the Enhanced PSSM+IBL object pixel shader the inverse texture sizes occupy
`cb0` bytes 16/32/48 and splits byte 64. Terrain uses bytes 0/16/32 and splits
byte 48. Ogre supplies each inverse size with `inverse_texture_size` for the
matching texture register.

### Texture and sampler registers — CONFIRMED

| family | ordinary maps | shadow maps/samplers | IBL after PSSM |
|---|---|---|---|
| objects | `t0..t3 / s0..s3` | `t4..t6 / s4..s6` | `t7..t9 / s7..s9` |
| terrain | `t0..t4 / s0..s4` | `t5..t7 / s5..s7` | `t8..t10 / s8..s10` |

The original abstract passes in `CR_BZBase.material` and
`CR_BZTerrainBase.material` declare border addressing with a white border but
no filter or comparison state. Ogre's texture-unit defaults are min/mag linear,
mip point, comparison disabled, comparison function greater-equal. Therefore
the old shader uses an ordinary linear sampler, not hardware PCF.

The current device was queried non-interactively with
`ID3D11Device::CheckFormatSupport(DXGI_FORMAT_R32_FLOAT)`. It reports shader
sample, shader comparison sample, and render-target support. This confirms that
the material can enable comparison sampling without changing Ogre textures.

### Caster and stored depth — CONFIRMED

`Shaders/CR_DepthShadowmap-sm4.hlsl` (`casterVP` / `casterFP`) transforms with
the shadow WVP, applies Ogre's texel offset, divides z by w, and writes that
depth to the float color target. `Materials/CR_DepthShadowmap.material` uses a
minimum blend operation and has no active caster bias.

The `fixedDepthBias = 0.0005` and gradient-clamp receiver code elsewhere in the
file is inside `#if 0`; the corresponding receiver material sections are also
commented out. It is not part of CR base/terrain PSSM. The `$bias` material
placeholder applies `depth_bias` to the visible material pass; it is not a
shadow receiver comparison bias.

### Original filtering, cascade and fade — CONFIRMED

`PCF_SIZE=4` in Enhanced High expands to 16 ordinary texture samples. Each
linearly filtered depth is compared afterward with:

```hlsl
step(receiverDepth, sampledDepth)
```

This filters depths before comparison, which is not comparison PCF. The
overlapping 2x2 sums/bilinear resolve do not change the 16 texture-read cost.
Classic High uses `PCF_SIZE=3`; this work does not alter it.

The original PSSM selection is hard: cascade 0 through depth 16, cascade 1
through 64, otherwise cascade 2. There is no transition blend, no check against
the `.w = 256` outer limit, and no explicit far fade. Enhanced remaps the raw
shadow factor to `shadow * 0.78 + 0.22`; that ambient floor remains unchanged.

## Stabilization audit

### BZR PSSM — HIGH confidence that texel snapping is absent

`DefaultShadowCameraSetup::getShadowCamera()` contains explicit light-space
world-texel snapping. PSSM delegates instead to LiSPSM/Focused setup. Searches
of the complete PSSM, LiSPSM, and Focused implementations find no equivalent
texel snap. The Focused header explicitly documents improved texel usage at the
expense of shadow-map “swimming,” and the mapping bounds are recalculated from
the current receiver/caster bodies.

This proves the PSSM projections are not stabilized by the Default setup's
snap. It does not quantify visible shimmer in BZR, and no live visual claim is
made. Implementing stable cascades would require changing or intercepting the
CPU shadow camera matrices; it is deliberately deferred.

### BZCC stabilization — SPECULATIVE / unresolved

Stabilization occurs before matrices reach a vertex shader. BZCC's baked DXBC
only exposes four supplied matrices and cannot prove how its CPU constructs or
snaps them. No renderer source was available. BZCC stabilization is therefore
unknown and was not copied by assumption.

## Phase 2: BZCC shipped shadow behavior

### Cascade contract — CONFIRMED

The shipped pixel shader reflects four shadow textures at `t28..t31`, a
comparison sampler `g_SamplerPCF` at `s7`, and `psshadow` at `cb1`:

| field | cb1 byte offset |
|---|---:|
| `g_ShadowSplitPoints` float4 | 0 |
| `g_InvShadowMapSize1` float2 | 16 |
| `g_InvShadowMapSize2` float2 | 24 |
| `g_InvShadowMapSize3` float2 | 32 |
| `g_InvShadowMapSize4` float2 | 40 |

The vertex counterpart supplies four shadow WVP matrices. Actual split values
and map dimensions are runtime data and remain unknown without an appropriate
mission capture.

### Selection, filter and cutoff — CONFIRMED

BZCC performs hard `<= split.x/y/z/w` selection and returns fully lit beyond
`.w`. It has no cascade transition blend and no gradual distance fade.

Every selected cascade executes four `sample_c_lz` comparison operations at a
2x2 one-texel offset pattern and averages them by 0.25. Because the comparison
sampler is bilinear, each instruction filters comparison results in hardware;
the compact pattern gives roughly a three-texel tent footprint at four reads.

This was not inferred from one permutation. All 312 shadow-enabled BZCC pixel
files were reduced to 246 unique DXBC hashes and disassembled. The 198 default,
32 terrain, and 16 water unique shaders all declare the comparison sampler,
split constant, and exactly 16 static comparison opcodes: four inside each of
four mutually exclusive cascade branches. No alternate large-kernel shadow
quality shader was found in the baked set.

### Bias — CONFIRMED

The representative object and terrain shadow vertex shaders compute the
equivalent of:

```text
shadowPosition = position + normal * (0.2 + 0.001 * max(viewDepth, 0))
```

and transform `shadowPosition` through all four shadow matrices. The shipped
pixel shader passes projected z directly as the comparison reference. It has no
constant receiver-depth subtraction, `N dot L` slope expression, tangent, or
normal offset in the pixel stage.

All four unique shadow-enabled object/terrain vertex hashes contain the same
`0.2` and `0.001` normal-offset sequence. This is normal-aware and
distance-growing, not a slope-bias formula. The constants depend on BZCC scene
scale and were not copied verbatim.

## Feature comparison and backport decision

| Feature | CR/BZR original | BZCC shipped | Backportable? | Decision / evidence |
|---|---|---|---|---|
| cascades | 3, splits 0.1/16/64/256 | 4, runtime splits | yes, but costly | Keep 3. Fourth cascade has no proven BZR need. CONFIRMED |
| matrices | Ogre texture WVP 0..2 | four supplied WVPs | already present | Preserve current contract. CONFIRMED |
| selection | hard at 16/64; samples outer indefinitely | hard at four splits; lit beyond last | yes | Blend CR's known overlap; stop beyond 256. HIGH adaptation |
| PCF | 16 ordinary linear depth reads, then manual compare | 4 bilinear comparison taps per selected cascade | yes | Implement four symmetric comparison taps. CONFIRMED technique, HIGH coordinate adaptation |
| transition | none despite Ogre overlap | none | yes | Implement smoothstep over `[15,17]`, `[63,65]`. CONFIRMED overlap; HIGH visual benefit |
| bias | no active shadow receiver bias | normal offset `0.2 + .001*depth` | yes | Bounded BZR adaptation `0.04 + .0002*depth`, max `.10`. CONFIRMED technique, MEDIUM tuning |
| slope bias | none | none in shipped PS | possible | Do not add unproven projective-depth math. CONFIRMED absence |
| stabilization | Focused path lacks Default snap | CPU behavior unknown | possible, high risk | Defer. HIGH BZR finding; SPECULATIVE BZCC parity |
| distance fade | none | hard fully-lit cutoff | yes | Fade last 24 units in lighting contribution. HIGH correctness, MEDIUM tuning |

## Candidate priority

| rank | change | benefit | confidence | cost | regression risk |
|---:|---|---|---|---|---|
| 1 | comparison PCF | cleaner, correct filtering; fewer reads | HIGH | lower normally | low-medium sampler-state pairing |
| 2 | cascade blending | removes seams/popping | HIGH | +4 taps only in 4 total depth units | low |
| 3 | bounded normal offset | reduces acne without large constant depth bias | MEDIUM tuning | small VS ALU | medium peter-panning tuning |
| 4 | far fade/cutoff | removes abrupt unsupported outer shadow | HIGH logic | saves reads beyond 256 | low-medium visual tuning |
| 5 | stable camera matrices | likely reduces swimming | MEDIUM benefit, low implementation confidence | CPU work | high; deferred |

## Implemented files

Campaign Reimagined owns the functional changes:

- `Shaders/CR_base-sm4.hlsl`
- `Shaders/CR_terrain-sm4.hlsl`
- `Shaders/CR_base.program`
- `Shaders/CR_terrain.program`
- `Shaders/CR_static_ibl.program`
- `Materials/CR_BZBase.material`
- `Materials/CR_BZTerrainBase.material`
- `Tools/Validate-DX11Shaders.ps1`
- `Tools/Test-EnhancedPssmV2.ps1`
- `Tools/Set-EnhancedPssmVersion.ps1`
- `.github/workflows/dx11-shader-validation.yml`
- `Docs/DX11_ENHANCED_PSSM_V2.md`

OpenShim receives this evidence report and a roadmap note only. No runtime hook,
patch pattern, configuration, or binary is needed.

## Non-interactive validation status

| Component | Static audit | Automated validation | Runtime non-interactive | Visual validation |
|---|---|---|---|---|
| Cascade blending | CONFIRMED overlap/logic | PASS: selection, bounds, continuity, 4/8-tap regions | shader assembly inspected | PENDING |
| PCF | CONFIRMED old and BZCC patterns | PASS: all variants compile; `sampler_c`/`sample_c_lz` emitted | R32 comparison support CONFIRMED | PENDING |
| Bias | CONFIRMED BZCC normal offset; CR adaptation implemented | PASS: finite, normalized, bounded for zero/grazing/extreme cases | compiled VS assembly inspected | PENDING |
| Stabilization | HIGH: BZR Focused path lacks Default snap | n/a; not implemented | no safe matrix capture performed | PENDING |
| Far fade | CONFIRMED original absence; implemented | PASS: exact endpoints, monotonicity, continuity, no lookup beyond end | shader assembly inspected | PENDING |

This is **IMPLEMENTED + STATICALLY VALIDATED**. It is not **LIVE VISUALLY
VALIDATED**. Remaining uncertainty is visual tuning of the half-texel kernel,
normal-offset magnitude, and final fade width, plus the separate stabilization
decision.

Classic object/terrain PSSM and compile-time Enhanced V1 object/terrain PSSM
were also compiled from both `origin/main` and the modified tree; all four DXBC
pairs were byte-identical.
