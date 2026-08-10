# BZCC / BZR DX11 Runtime Probe Report

Prepared: 2026-08-08
Baseline document: `BZCC_TO_BZR_SHADER_RENDER_BACKPORT_REPORT.md` (not superseded; this report supplements it)
Probe artifacts: `reverse_engineering/bzcc_bzr_dx11_probe/`

---

## 1. Executive summary

Six findings materially change the picture. All six are CONFIRMED from resource
headers or DXBC reflection, not inferred from filenames.

1. **BZCC is a genuine hardware-sRGB linear-light renderer.** 1,414 of its 1,788
   shipped DDS textures carry DX10 headers with explicitly `_SRGB` DXGI formats
   (`BC1_UNORM_SRGB`, `BC3_UNORM_SRGB`). The split is exactly by texture role:
   every `_n` normal map is `BC5_SNORM` (linear), and colour, specular,
   emissive and environment maps are `_SRGB`.

2. **BZR cannot be doing hardware sRGB decode, at the asset level.** All 789
   stock BZR DDS files use *legacy FourCC* headers (`DXT1`/`DXT3`/`DXT5`). The
   legacy FourCC path has no sRGB concept in D3D11 and always resolves to
   `BC*_UNORM`. Zero `_SRGB`-typed assets exist in BZR or CR. BZR's normal maps
   are `DXT1` — the *same format as its colour textures* — so BZR has no
   format-level distinction between colour and data textures at all.

3. **BZCC manually gamma-decodes vertex colours in the vertex shader.** 29
   vertex shaders contain `pow(COLOR.rgb, 2.2)` as an explicit
   `max`/`log`/`mul 2.2`/`exp` sequence, with alpha passed through untouched.
   This is exactly what a correct linear pipeline must do, because hardware
   sRGB decode applies to texture samples but never to vertex attributes.

4. **No BZCC pixel shader contains any gamma constant.** Scanning all 1,179
   shaders for the ten usual transfer-function immediates found `2.2` only in
   those 29 vertex shaders. There is no manual texture decode and no manual
   output encode anywhere in the pixel stage — consistent only with hardware
   performing both ends.

5. **47.4% of BZCC's shader package is redundant.** The 1,179 `.fxc` files
   contain only **620 distinct bytecode blobs**. Mining the 174 collision groups
   recovers real dependency rules between the filename feature letters — most
   importantly that **`o` is completely inert whenever `c` is present** (142
   cases), which resolves part of the `c`/`o` ambiguity the baseline report left
   open.

6. **BZCC's environment maps are per-world 1024x1024 with 11 mips**, not
   `reflection3.dds`. The baseline report treated `reflection3.dds` (256x256,
   9 mips, used as a *diffuse* source by 17 chrome materials) as the environment
   path. There is a separate family of 24 `*_environ.dds` files, one or more per
   world, whose full 11-mip chains match the explicit-LOD prefiltered sampling
   the shaders perform.

Taken together, 1–4 give an evidence-based explanation for the Stage A luminance
increase measured in Campaign Reimagined. See §6.4.

**What this probe could not do:** no runtime frame capture of BZCC was possible.
RenderDoc, PIX and Nsight are all absent from this machine, and installing a
capture tool that injects its own DLL was out of scope under the stated safety
constraints. Every question requiring live draw-call state — actual per-draw
permutation selection, runtime shadow constant values, t27 bindings, light
packing, water pass ordering, adaptive quality — remains **UNKNOWN**. §14 lists
the smallest experiment that would resolve each.

---

## 2. Local tooling and capability inventory

| Capability | Status | Detail |
|---|---|---|
| RenderDoc | **absent** | not installed |
| PIX for Windows | **absent** | not installed |
| NVIDIA Nsight | **absent** | not installed |
| PresentMon | **absent** | not installed |
| GPUView | **absent** | not in SDK Tools |
| WPR / ETW | present | `C:\Windows\System32\wpr.exe` |
| D3D11 debug layers | present | `d3d11sdklayers.dll`, `d3d11_1sdklayers.dll`, `d3d11_2sdklayers.dll` in System32 |
| `fxc.exe` | present | SDK 10.0.22621.0 x64 — **used heavily** |
| `dxc.exe` | present | SDK 10.0.22621.0 x64 |
| `dumpbin.exe` | present | VS 2022 Community, MSVC 14.38.33130 |
| Windows SDKs | present | 14393, 15063, 16299, 17134, **22621** |
| Visual Studio | present | 2022 Community |
| Python | present | 3.12.10 (`python`), 3.14.3 (`py`) — **used for all probe scripts** |
| PowerShell | present | 7.6.3 Core |
| GPU | — | NVIDIA RTX 5080, driver 32.0.16.1088 (also AMD Radeon iGPU, Meta Virtual Monitor) |
| BZCC | present | `BZ2R\battlezone2.exe` **2.0.185** |
| BZR (Steam) | present | 2.2.301 |
| BZR (GOG) | present | 2.2.301 — **this is the active CR runtime** (`modEnabled.dat` in the GOG tree, mod id 3686673790) |

**Version discrepancy:** the baseline report states BZCC source build
`2.0.200.0 / Steam build 18590733`. The installed executable reports **2.0.185**.
Either the depot changed or the baseline recorded a different figure; shader
observations here apply to 2.0.185. `LOW` impact but worth reconciling.

### Existing instrumentation reviewed

OpenShim already provides the BZR half of this investigation:
`src/patches/dx11_colorspace_diagnostic.cpp` is a read-only DX11 observer that
logs texture/SRV/RTV/DSV/viewport/shader-slot/device/feature-level/swap-chain
state, and its captured results are written up in CR's
`docs/DX11_COLOR_SPACE_AUDIT.md`. That capture is treated here as CONFIRMED
runtime evidence for BZR. There is no equivalent hook for BZCC.

---

## 3. BZCC runtime architecture findings

### 3.1 Shader package composition — CONFIRMED

| Metric | Value |
|---|---:|
| `.fxc` files | 1,179 |
| Distinct SHA-256 bytecode blobs | **620** |
| Redundant files | 559 (**47.4%**) |
| Colliding groups | 174 |
| Cross-family/layout/stage collisions | 20 groups |

Artifact: `shader_hashes.csv` (filename, sha256, size, family, layout, stage,
features, gamma constants).

This map is the tool the baseline report asked for: if a runtime capture ever
yields raw DXBC for a draw, hashing it resolves the exact installed permutation
filename even though the engine exposes no names. **Caveat now established:** a
hash resolves to a *set* of filenames in 174 cases, not a unique one, because
those permutations are genuinely the same program.

### 3.2 Feature-letter semantics recovered from bytecode identity — CONFIRMED

If two filenames differ only by letter X yet compile to identical DXBC, X
contributed nothing to that combination.

| Letter | Times inert | What that proves |
|---|---:|---|
| `o` | 142 | **`o` is inert whenever `c` is present.** `0pdelc` == `0pdeloc`. The combined-environment path collapses into the chrome path. |
| `n` | 64 | Normal map is inert without `l`. `0pd` == `0pdn`. |
| `s` | 64 | Specular map is inert without `l`. `0pd` == `0pds`. |
| `d` | 64 | Diffuse inert on layout 5. `5p` == `5pd`. |
| `e` | 40 | Emissive inert on layout 5. |
| `t` | 40 | Team colour inert on layout 5. |
| `x` | 32 | Cutout inert on layout 5. |
| `l` | 8 | Lights inert in some layout-2/3 vertex shaders. |
| `c` | 5 | Environment inert in some shadowed vertex shaders. |
| `a`, `z` | 0 | **Extra layers and shadows always change the code.** |

Two structural results fall out:

- **Layout 5 ignores every texture letter** (`5p` == `5pd` == `5pde` == `5pdt`
  == `5pdesx`). This upgrades the baseline's *inferred* "pretransformed
  untextured UI/effect geometry" classification for layout 5 to CONFIRMED.
- **Layouts 1 and 2 share pixel shaders exactly** (`1p` == `2p`, `1pd` == `2pd`,
  …). Layout 2's extra `normal3` is consumed only by the vertex stage.
- **Water and default share vertex shaders at layout 0** — `dx11_water_vsh_0v`
  is byte-identical to `dx11_default_vsh_0vc`/`0vl`/`0vlc`/`0vlo`/`0vloc`.
  Water's specialisation is entirely in the pixel stage.

Artifact: `scripts/analyze_permutation_collisions.py`.

### 3.3 Colour-space handling — CONFIRMED

Texture assets (`bzcc_dds_formats.csv`, 1,788 files):

| DDS format | Count | Header | sRGB? | Role correlation |
|---|---:|---|---|---|
| `BC1_UNORM_SRGB` | 859 | DX10 | **yes** | diffuse, `_c`, `_environ`, misc colour |
| `BC3_UNORM_SRGB` | 555 | DX10 | **yes** | `_s` specular (370), `_e` emissive (170) |
| `BC5_SNORM` | 373 | FourCC `BC5S` | no | **371 are `_n` normal maps** |
| uncompressed 32bpp | 1 | RGB | no | — |

The role split is essentially perfect: 371 of 373 linear-format files are `_n`
normal maps; every colour-bearing role is `_SRGB`.

Shader-side transfer functions (all 1,179 files scanned for ten gamma
immediates — 2.2, 1/2.2, 2.4, 1/2.4, 0.0031308, 0.04045, 12.92, 1/12.92, 1.055,
0.055):

- **`2.2` found in exactly 29 shaders, all vertex shaders, layouts 2 and 3.**
- **No pixel shader contains any gamma constant.**

Disassembly of `dx11_default_vsh_2v.fxc` (`fxc /dumpbin`):

```
dcl_input v2.xyzw                                  ; COLOR
max r0.xyz, v2.xyzx, l(0,0,0,0)
log r0.xyz, r0.xyzx
mul r0.xyz, r0.xyzx, l(2.200000, 2.200000, 2.200000, 0.000000)
exp o1.xyz, r0.xyzx
mov o1.w, v2.w                                     ; alpha NOT transformed
```

That is `pow(vertexColour.rgb, 2.2)` — a gamma→linear decode of the vertex
colour attribute, with alpha correctly excluded. Hardware sRGB decode covers
texture samples; vertex attributes must be decoded in-shader, and BZCC does
exactly that.

### 3.4 Shadow contract — CONFIRMED (static)

`fxc /dumpbin dx11_default_psh_0pdlz.fxc` resource bindings, with real HLSL
names recovered from the RDEF chunk:

```
g_Sampler0        sampler     s0
g_SamplerPCF      sampler_c   s7      <- comparison sampler
g_Texture0        texture 2d  t0
g_Texture28..31   texture 2d  t28-t31 <- four cascades
psfloats  cb0 / psshadow cb1 / pslights cb4
```

`psshadow` (cb1) layout:

| Field | Offset | Size |
|---|---:|---:|
| `g_ShadowSplitPoints` (float4) | 0 | 16 |
| `g_InvShadowMapSize1` (float2) | 16 | 8 |
| `g_InvShadowMapSize2` (float2) | 24 | 8 |
| `g_InvShadowMapSize3` (float2) | 32 | 8 |
| `g_InvShadowMapSize4` (float2) | 40 | 8 |

**New structural fact:** each cascade carries its *own* inverse map size. The
shader contract therefore permits per-cascade resolutions. Whether BZCC actually
uses differing sizes at runtime is **UNKNOWN** (needs a cb1 capture).

### 3.5 Material/lighting constant contract — CONFIRMED

`psfloats` (cb0):

| Field | Offset | Size | Note |
|---|---:|---:|---|
| `g_FogColor` | 0 | 16 | |
| `g_FogParams` | 16 | 16 | |
| `g_MaterialDiffuse` | 32 | 16 | |
| `g_MaterialSpecular` | 48 | 16 | |
| `g_MaterialEmissive` | 64 | 16 | |
| `g_LightAmbient` (float3) | 80 | 12 | |
| `g_LightCount` (**float**) | 92 | 4 | packed into the ambient slot's `.w` |
| `g_TeamColor` | 96 | 16 | |
| `g_EnvironmentColor` | 112 | 16 | |

`pslights` (cb4) per-light stride: `m_Pos` float4 @0, `m_Dir` float3 @16,
`m_Color` float3 @32, `m_Attenuation` float4 @48, `m_Spot` float3 @64.

`g_LightCount` being a **float** packed into `g_LightAmbient.w` is a real
implementation detail worth noting for anyone replicating the buffer.

### 3.6 Environment/reflection assets — CONFIRMED (assets) / UNKNOWN (binding)

| Asset | Dimensions | Mips | Format |
|---|---|---:|---|
| `Scion\Shared\reflection3.dds` | 256x256 | 9 | `BC1_UNORM_SRGB` |
| `Worlds\*\Sky\*_environ.dds` (24 files) | 1024x1024 | 11 | `BC1_UNORM_SRGB` |

The `*_environ.dds` family is per-world — `bane_environ`, `bane_dawn_environ`,
`bane_bright_environ`, `bane_tan_environ`, `core_environ`, `coreint_environ`,
`dark_environ`, `dunes_day_environ`, `dunes_night_environ`, `earth_day_environ`,
`mars_environ`, `metal_environ`, `mire_blue_environ`, … — i.e. **environment
maps vary by world and by time-of-day/lighting variant**, which answers one of
the Phase 6 questions at the asset level. Full 11-mip chains are consistent with
the explicit-LOD prefiltered sphere-map sampling the baseline report documented.

Which resource is actually bound to `t27` for a given draw is **UNKNOWN** — that
needs a runtime capture. The baseline report's association of `reflection3.dds`
with the environment path should be treated as unproven; those 17 materials use
it as a *diffuse* source, and the `_environ` family is the better structural
candidate for `t27`.

### 3.7 Everything requiring live draw state — UNKNOWN

Phases 5 (runtime shadow values), 6 (t27 binding), 7 (light packing), 8
(raster/blend/depth state), 9 (which materials are two-sided), 10 (water pass
ordering, t10 lifecycle, UV constant rates), 11 (terrain active-layer counts),
12 (adaptive quality) and 13 (frame/pass reconstruction) **could not be
established**. No capture tool is installed. See §14.

---

## 4. BZR runtime architecture findings

### 4.1 Colour space — CONFIRMED (runtime, via OpenShim)

From the OpenShim DX11 diagnostic capture recorded in CR's
`docs/DX11_COLOR_SPACE_AUDIT.md`:

1. Swapchain and backbuffer are ordinary `R8G8B8A8_UNORM` — neither `_SRGB` nor
   typeless.
2. Relevant RTVs are non-sRGB. RTV format was logged *independently* of the
   resource format, precisely because Ogre may legally pair an `_SRGB` RTV with
   a UNORM backbuffer. That pairing did not occur.
3. No `_SRGB` resource, SRV or RTV appeared anywhere, for any binding.
4. Ogre reports `sRGB Gamma Conversion = No`, consistent with observed D3D state.
5. Enhanced shaders contained no sRGB transfer functions prior to Stage A.

### 4.2 Asset formats — CONFIRMED (new this pass)

| Tree | DDS files | `_SRGB`-typed | Header style |
|---|---:|---:|---|
| BZR stock (Steam) | 789 | **0** | legacy FourCC: DXT1 x781, DXT5 x4, uncompressed x4 |
| Campaign Reimagined | 29 | **0** | FourCC DXT1 x8, DXT5 x2, uncompressed 24bpp x18, 32bpp x1 |

This independently corroborates the runtime capture from the asset side, and
adds a fact the runtime capture could not show: **BZR stores normal maps in
`DXT1`, the same format as colour**. There is no format-level signal
distinguishing colour from data textures, which is exactly why CR's Stage A had
to carry an explicit hand-maintained list of which samples to decode.

Upstream Ogre 1.10 only produces `_SRGB` formats when
`Texture::isHardwareGammaEnabled()` is set, and then creates the SRV with the
same format as the resource. BZR does not request it. So neither the assets nor
the engine configuration can produce hardware decode.

### 4.3 Unresolved for BZR

DXGI presentation colour space remains formally unresolved: no
`IDXGISwapChain3::SetColorSpace1` call was observed, and DXGI exposes no public
getter. Absence of an observed call is not proof of a particular selection.

---

## 5. BZCC vs BZR comparison matrix

| Feature | BZCC | BZR stock | CR Enhanced | Confidence | Backport implication |
|---|---|---|---|---|---|
| Texture transfer | Hardware `_SRGB` decode on all colour roles | None — legacy FourCC UNORM | Manual `pow` decode (Stage A), opt-in | CONFIRMED | CR's manual decode is the correct compensation; hardware route would need Ogre hwGamma + asset re-bake |
| Normal-map format | `BC5_SNORM` (linear, 2-channel) | `DXT1` (same as colour) | inherits BZR | CONFIRMED | BZR has no format-level colour/data split; explicit allowlists are unavoidable |
| Vertex-colour transfer | `pow(rgb, 2.2)` in VS, alpha untouched | none | none | CONFIRMED | **Gap in CR Stage A** — see P1 in §12 |
| Output encode | No shader encode; hardware RTV implied | none | Manual encode (Stage A) | CONFIRMED (no shader math) / STRONGLY INFERRED (hardware RTV) | CR's single explicit encode is the right shape |
| Shadow cascades | 4, `t28`–`t31` | 3 | 3 | CONFIRMED | unchanged from baseline |
| Shadow sampling | `sampler_c` `g_SamplerPCF` @ `s7` | manual depth compare | manual + enhanced PCF | CONFIRMED | comparison sampler is expressible in DX11; per-cascade texel sizes already in contract |
| Per-cascade texel size | 4 independent `float2` | shared assumption | shared | CONFIRMED | permits mixed-resolution cascades |
| Light buffer | 16 packed, `g_LightCount` as float in ambient `.w` | 1 or 8 | up to 24 | CONFIRMED (layout) / UNKNOWN (selection) | do not raise CR light count on this evidence |
| Environment map | Per-world 1024² 11-mip `_environ.dds`, sRGB | legacy reflection | cubemap IBL + BRDF LUT | CONFIRMED (assets) / UNKNOWN (binding) | sphere-map tier is viable; source asset identified |
| Shader redundancy | 47.4% duplicate | n/a | n/a | CONFIRMED | do not clone the permutation grammar |
| `o` vs `c` | `o` inert when `c` present | n/a | n/a | CONFIRMED | one environment path, not two |

---

## 6. Colour-space and resource-format detail

### 6.1 BZCC

| Resource / use | Texture format | SRV format | sRGB decode | sRGB encode | Notes |
|---|---|---|---|---|---|
| Diffuse/albedo | `BC1_UNORM_SRGB` / `BC3_UNORM_SRGB` | same (Ogre-style same-format SRV not applicable; BZCC is native DX11) | **yes, hardware** | n/a | CONFIRMED from DX10 DDS headers |
| Specular (`_s`) | `BC3_UNORM_SRGB` | — | **yes, hardware** | n/a | 370 files; sRGB-typed specular is a quirk but explicit |
| Emissive (`_e`) | `BC3_UNORM_SRGB` | — | **yes, hardware** | n/a | 170 files |
| Normal (`_n`) | `BC5_SNORM` | — | no (correct) | n/a | 371 files, 2-channel signed |
| Environment (`_environ`) | `BC1_UNORM_SRGB` 1024² 11 mips | — | **yes, hardware** | n/a | per-world |
| Vertex colour | n/a | n/a | **yes, shader `pow 2.2`** | n/a | CONFIRMED by disassembly |
| Shadow maps | UNKNOWN | UNKNOWN | n/a | n/a | needs capture; `sampler_c` confirmed |
| Intermediates / backbuffer | UNKNOWN | UNKNOWN | n/a | STRONGLY INFERRED hardware | no shader-side encode exists anywhere |

### 6.2 BZR / CR

| Resource / use | Texture format | SRV format | sRGB decode | sRGB encode | MSAA | Notes |
|---|---|---|---|---|---|---|
| Diffuse/albedo | `BC1_UNORM` (DXT1) | non-sRGB | **no** (Stage A: manual) | n/a | — | CONFIRMED both asset + runtime |
| Normal | `BC1_UNORM` (DXT1) | non-sRGB | no | n/a | — | same format as colour |
| Emissive/specular | `BC1_UNORM` | non-sRGB | no | n/a | — | |
| Static IBL (CR) | generated LDR DDS | non-sRGB | **must not decode** | n/a | — | linear numerical data in an LDR container |
| Backbuffer / swapchain | `R8G8B8A8_UNORM`, not typeless | n/a | n/a | **no** (Stage A: manual, once) | FSAA 8 configured | CONFIRMED runtime |
| RTVs | non-sRGB | n/a | n/a | no | — | logged independently of resource |

### 6.3 Which pipeline model each game follows

- **BZCC = hardware sRGB pipeline**, with the one manual patch a hardware
  pipeline actually requires (vertex colours). sRGB SRV → hardware decode →
  linear lighting → hardware encode on output. CONFIRMED on the input half;
  the output half is STRONGLY INFERRED from the total absence of shader-side
  encode math.
- **BZR stock = legacy nonlinear pipeline.** Gamma-encoded texel values enter
  the lighting math directly and are written unconverted. CONFIRMED from both
  ends.
- **CR with Stage A = manual decode pipeline.** Explicit shader decode of
  allowlisted colour samples, lighting, one explicit encode before the UNORM
  target. This is the correct choice given BZR's assets and engine config —
  the hardware route is unavailable without re-baking every texture *and*
  enabling Ogre hardware gamma.

### 6.4 Why Stage A raised luminance so sharply — evidence plus hypothesis

**Evidence.** The measured Stage A effect on the Moon scene (from the prior
calibration pass, identical camera, sky region as an exact control) was:

| Region | Linear OFF | Linear ON, same IBL | Change |
|---|---:|---:|---:|
| far ridge face | 25.23 | 57.47 | **+128%** |
| mid ridge shadow | 17.69 | 42.88 | **+142%** |
| foreground terrain | 41.01 | 66.25 | +62% |
| vehicle bodies | 33.27 | 66.02 | +98% |

**Hypothesis (consistent with, but not proven by, the above).** CR's additive
terms — legacy ambient, IBL irradiance, IBL specular, emissive — were numerically
calibrated in the *encoded* domain, because that is the only domain the legacy
pipeline ever had. Stage A moves those same additions into the linear domain and
then applies an sRGB encode. The sRGB encode curve is very steep near black
(linear 0.05 encodes to roughly sRGB 0.24), so an additive term that looked
modest when added to encoded values becomes dramatically larger once it is added
in linear space and encoded afterwards.

That predicts the lift should be *largest in the darkest regions and smallest in
the brightest*, which is exactly the ordering observed: shadowed slope +142% and
distant ridge +128% versus lit foreground +62%. The gradient is the signature of
the encode curve's low-end slope rather than of a uniform scale error.

BZCC does not have this problem because its material and light constants were
authored against a linear pipeline from the outset.

**This explains the observation; it does not by itself prove causation.** The
decisive experiment is cheap and stated in §14.

---

## 7. Remaining unknowns, and the smallest experiment for each

| Unknown | Smallest resolving experiment |
|---|---|
| BZCC backbuffer/RTV sRGB (Final Q2) | One RenderDoc capture; read the swapchain + RTV format in the texture viewer. Single frame is sufficient. |
| Actual per-draw permutation selection | RenderDoc pipeline state → hash the bound DXBC → look up in `shader_hashes.csv`. The tooling is already built and waiting. |
| `t27` actual binding, per material/world | Same capture; inspect PS SRV slot 27 for a chrome object. |
| Runtime `psshadow` values, cascade resolutions | Same capture; read cb1 contents and the four shadow texture descs. |
| Light packing behaviour | Same capture; read cb4 across two adjacent objects with differing local lights. |
| Water pass order, `t10` provenance | Same capture; event browser around the water draw. |
| Terrain active-layer counts in real maps | Same capture; read `vsterrain.g_ActiveLayers`. |
| Adaptive quality transitions | Requires artificial GPU load; low value, deprioritise. |
| Stage A causation for the luminance lift | Rebuild CR's static IBL assets and re-derive ambient/emissive constants in linear space, then re-measure. If the region-dependent gradient collapses, the encode-curve explanation is confirmed. |

---

## 8. Updated backport recommendations

| # | Recommendation | Priority | Rationale |
|---|---|---|---|
| 1 | **Apply `pow(rgb, 2.2)` to vertex colours in CR's Stage A path**, alpha excluded — **IMPLEMENTED 2026-08-08** | **P0** | BZCC does exactly this and CR did not. See §13 for what shipped and how it differs from BZCC. |
| 2 | Treat CR's generated static IBL DDS as linear data and never decode it | **P0** | Already correct; documented here so it is not "fixed" by mistake. |
| 3 | Re-derive ambient/IBL/emissive constants in linear space rather than rescaling them | **P1** | Addresses the cause rather than the symptom of the luminance lift. |
| 4 | Adopt per-cascade inverse-texel-size constants in CR shadows | **P1** | BZCC's contract proves the shape; enables mixed-resolution cascades later. |
| 5 | Use `SamplerComparisonState` on the DX11 Enhanced path | **P1** | `sampler_c` at s7 confirmed; DX11-expressible. |
| 6 | Build the sphere-map reflection tier against `*_environ.dds` semantics (1024², 11 mips) | **P2** | Asset shape now known; binding still needs a capture. |
| 7 | Do **not** clone BZCC's permutation grammar | **DO NOT PURSUE** | 47.4% of it is provably redundant. |
| 8 | Do **not** treat `c` and `o` as two environment paths | **DO NOT PURSUE** | `o` is inert whenever `c` is set. |
| 9 | Do not raise CR light count on this evidence | **DO NOT PURSUE (yet)** | Only the buffer *layout* is known; the selection policy is not. |
| 10 | Install RenderDoc and take four captures (A–D as specified) | **P1 — highest information-per-effort remaining** | Unblocks ~8 of the 12 outstanding questions at once. |

---

## 9. Evidence ledger

| Finding | Evidence source | Confidence | Reproduction |
|---|---|---|---|
| 1,414/1,788 BZCC textures `_SRGB`-typed | DDS DX10 headers | CONFIRMED | `python scripts/inventory_dds_formats.py --root "<BZ2R>" --label BZCC --out x.csv` |
| BZCC normal maps `BC5_SNORM`, 371 of 373 named `_n` | DDS headers + filename join | CONFIRMED | same, then group by suffix |
| 0/789 BZR and 0/29 CR textures `_SRGB`-typed; all legacy FourCC | DDS headers | CONFIRMED | same script, BZR/CR roots |
| BZR normal maps are DXT1, same as colour | DDS headers | CONFIRMED | same |
| BZCC VS does `pow(COLOR.rgb, 2.2)`, alpha untouched | `fxc /dumpbin dx11_default_vsh_2v.fxc` | CONFIRMED | disassemble, inspect `max`/`log`/`mul 2.2`/`exp` |
| No BZCC pixel shader contains gamma constants | bit-pattern scan of all 1,179 files | CONFIRMED | `python scripts/hash_bzcc_shaders.py` |
| BZCC output encode is hardware | absence of shader encode + presence of full linear input chain | STRONGLY INFERRED | needs RenderDoc |
| 1,179 files → 620 distinct blobs (47.4% redundant) | SHA-256 of DXBC | CONFIRMED | `hash_bzcc_shaders.py` |
| `o` inert whenever `c` present (142 cases) | bytecode identity | CONFIRMED | `analyze_permutation_collisions.py` |
| Layout 5 ignores all texture letters | bytecode identity | CONFIRMED | same |
| Layouts 1 and 2 share pixel shaders | bytecode identity | CONFIRMED | same |
| Water VS == default VS at layout 0 | bytecode identity | CONFIRMED | same |
| `g_SamplerPCF` is `sampler_c` at s7; cascades t28–t31 | DXBC RDEF | CONFIRMED | `fxc /dumpbin dx11_default_psh_0pdlz.fxc` |
| `psshadow` has 4 independent inverse map sizes | DXBC RDEF | CONFIRMED | same |
| `g_LightCount` is a float packed at offset 92 | DXBC RDEF | CONFIRMED | same |
| Environment maps are per-world 1024² 11-mip sRGB | DDS headers | CONFIRMED | `bzcc_dds_formats.csv`, filter `_environ` |
| BZR swapchain UNORM, no `_SRGB` anywhere | OpenShim DX11 diagnostic | CONFIRMED | CR `docs/DX11_COLOR_SPACE_AUDIT.md` |
| BZCC per-draw state, water order, light selection | — | **UNKNOWN** | requires capture tool |

---

## 10. Final decision questions

1. **Does BZCC use hardware sRGB texture decoding?** **Yes — CONFIRMED.** 1,414
   `_SRGB`-typed assets, split correctly by texture role.
2. **Does BZCC use hardware sRGB framebuffer encoding?** **STRONGLY INFERRED
   yes.** No pixel shader performs an encode, yet the entire input chain is
   linearised. Needs one capture to confirm.
3. **BZCC's effective colour pipeline?** Hardware sRGB linear-light, with manual
   `pow 2.2` for vertex colours. Not mixed, not legacy.
4. **BZR's effective DX11 colour pipeline?** Legacy nonlinear — CONFIRMED from
   both asset formats and runtime capture. CR Stage A converts it to a manual
   decode pipeline.
5. **Does this explain CR's Stage A luminance increase?** **Yes, with a
   consistent quantitative signature** — additive terms calibrated in encoded
   space, moved into linear space and then encoded through a curve that is steep
   near black. Predicted and observed lift is largest in the darkest regions.
   Explanation, not yet proof; §7 gives the decisive test.
6. **Can BZCC's sphere-map reflection be reproduced without guessing?**
   **Partly.** Sampling math and asset shape are known; the actual `t27` binding
   and material classification are not. One capture closes it.
7. **Can derivative-aware cutout be reproduced without guessing?** **Yes for the
   shader math** (baseline report, CONFIRMED). Whether render state contributes
   is **UNKNOWN**.
8. **Enough evidence for improved three-cascade DX11 shadows?** **Yes.**
   Comparison sampler, slot layout and per-cascade texel constants are all
   confirmed. Numeric split values are not, and should be derived from BZR's
   own scene scale anyway.
9. **What would BZCC-style water require?** Unchanged from the baseline report;
   this pass added only that water shares default's layout-0 vertex shader, so
   the work is entirely pixel-stage plus a scene-colour resource and lifecycle.
10. **Do we understand per-object light selection well enough to copy it?**
    **No.** Buffer layout CONFIRMED; selection policy UNKNOWN.
11. **Additional techniques not in the original report?** Yes — vertex-colour
    gamma decode; per-cascade inverse texel sizes; `g_LightCount` float packing;
    the `c`/`o` collapse; 47.4% package redundancy; per-world environment maps.
12. **Which unknowns actually matter for CR?** In order: BZCC's output encode
    (Q2), vertex-colour handling (already actionable), `t27` binding, runtime
    shadow constants. Water, adaptive quality and light selection do not block
    current CR work.
13. **What to implement next?** Recommendation 1 (vertex-colour decode in Stage
    A) — it is directly evidenced, small, and closes a real correctness gap.
    Then recommendation 3. Take the RenderDoc captures before anything
    reflection- or water-related.

---

## 11. Artifacts

| Path | Contents |
|---|---|
| `bzcc_dds_formats.csv` | 1,788 BZCC DDS: path, format, header type, dimensions, mips |
| `bzr_stock_dds_formats.csv` | 789 BZR stock DDS |
| `cr_dds_formats.csv` | 29 CR DDS |
| `shader_hashes.csv` | 1,179 `.fxc`: sha256, size, family/layout/stage/features, gamma constants |
| `scripts/inventory_dds_formats.py` | DDS DXGI/FourCC inventory (parameterised roots) |
| `scripts/hash_bzcc_shaders.py` | DXBC hashing + gamma-constant scan |
| `scripts/analyze_permutation_collisions.py` | Feature-letter semantics from bytecode identity |

All scripts are read-only, take paths as parameters, and exit non-zero on a
missing root. No game file was modified during this investigation.

---

## 13. Implementation follow-up: vertex-colour decode (recommendation 1)

Implemented 2026-08-08 in the canonical CR tree.

**Scope turned out to be narrower than the recommendation implied.** Checking the
actual entry-point signatures first:

- `CR_base-sm4.hlsl` has **no vertex COLOR input at all** — its VS inputs are
  `POSITION`, `TEXCOORD0`, `NORMAL`. Its `COLOR0`/`COLOR1` are interpolator
  channels carrying vertex-*lighting* results, not an authored attribute. **No
  change was made to the base shader.**
- `CR_terrain-sm4.hlsl` has a real `in float4 iColor : COLOR0`, passed through as
  `vColor`. It is used in exactly two places: `oColor.xyz = lightResult * vColor.xyz
  * diffuseTex.xyz` and `oColor.a = vColor.a`.

Because the terrain tint multiplies the decoded albedo directly, it is authored
display colour by construction, and leaving it encoded would multiply a linear
albedo by a gamma-space tint. Confirming this was not layer-weight data: BZCC's
terrain family (layout 8) contains the same `pow(COLOR.rgb, 2.2)` sequence in 10
of its vertex shaders, with `mov o1.w, v2.w` leaving alpha untouched.

**Deliberate deviation from BZCC:** BZCC decodes in the *vertex* stage, before
interpolation. CR decodes in the *pixel* stage, because Stage A is scoped to the
per-pixel path and the program-boundary guard forbids vertex programs from
defining `CR_LINEAR_LIGHT`. The tint is therefore interpolated encoded and
decoded afterwards. Over a single terrain triangle this is a small deviation, and
it is what allows Default and Retro to keep sharing the terrain vertex programs
byte-for-byte.

Validator changes required:

- `vertexTint` added to `$allowedDecodeTargets`, with the reasoning recorded
  inline.
- New `$familyScopedDecodeTargets` / `$familyScopedDecodeOwners` mechanism, so a
  target that exists in only one family is *required in its owner and forbidden
  elsewhere*. Without this the existing allow-list doubled as a required-list and
  failed the base shader for lacking a terrain-only input.
- The preprocessed-occurrence expectation gained `+1` for `CR_terrain-sm4.hlsl`.
  `ll0` cases still expect zero, so the legacy path remains provably untouched.

Negative tests (all rejected correctly): terrain dropping the decode; base
gaining the terrain-only target; the decode being widened to include alpha. Note
that the second case was caught by the occurrence-count guard rather than the
family-scope guard — the scope check does not match a declaration-form target
(`float3 vertexTint = ...`). The regression is rejected either way, but the scope
guard is less precise than intended.

**Not yet runtime-verified.** The workstation was locked when the change landed,
so no capture could be taken. Expected effect: terrain becomes slightly darker
under Enhanced, since a sub-unity tint decodes to a smaller linear value.
Default and Retro must be unchanged. Re-run `Run-ModeAcceptance.ps1` to confirm.

---

## 12. Non-destructive compliance

No executable was patched. No game installation file was modified. No system
DX11 component, driver, anti-cheat component or save game was touched. No
third-party DLL was downloaded or injected. CR shipping shaders were not
modified. All new files are confined to
`reverse_engineering/bzcc_bzr_dx11_probe/`. Nothing was committed.
