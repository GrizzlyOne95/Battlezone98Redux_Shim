# BZCC shader reference

This folder is a formula-level specification of every compiled shader that
BZCC (Steam BZ2R) ships in `bz2r_res\baked\shaders`: 1,179 SM5 DXBC programs.
It is the reference for porting BZCC's look into OpenShim Enhanced.

| File | Family | Programs |
|---|---|---|
| [objects.md](objects.md) | `dx11_default_*` (objects, effects, UI layouts 0-7) | 1,007 PS / 31 VS (491 distinct PS bodies) |
| [terrain.md](terrain.md) | `dx11_terrain_*` (layout 8) | 81 PS / 10 VS |
| [water.md](water.md) | `dx11_water_*` | 40 PS / 10 VS |

The specs are written as maths and pseudo-HLSL. Raw disassembly is
deliberately not committed (AGENTS.md: no decompiler output in the repo). Each
claim carries a confidence tag: **[H]** read directly off the instructions,
**[M]** a direct reading plus an inference about convention, **[L]** a guess.

To regenerate the dumps locally, outside the repo:

```powershell
$fxc = "C:\Program Files (x86)\Windows Kits\10\bin\10.0.26100.0\x64\fxc.exe"
Get-ChildItem "<BZ2R>\bz2r_res\baked\shaders\dx11_*.fxc" |
    ForEach-Object { & $fxc /dumpbin $_.FullName > "$env:TEMP\bzcc_fxc\$($_.BaseName).asm" }
```

## One lighting core across all three families

Objects, terrain and water share an instruction-identical lighting core:

- **Specular.** Schlick Fresnel with `F0 = matSpec.rgb * specTex.rgb`.
  GGX `D` without the 1/π. Hammon visibility `lerp(2·NL·NV, NL+NV, α)`.
- **Roughness.** `α² = 2 / (2^(matSpec.w · specTex.a) + 2)`. The CPU stores
  **log2 of the Blinn-Phong power**, so this is exactly Walter's
  `α = sqrt(2/(n+2))`.
- **Diffuse.** `albedo · Σ L·NL·(1−F)·atten`, with no 1/π.
- **Terminator.** On normal-mapped variants, each light is multiplied by
  `smoothstep(sat((Ngeom·L + 0.1)·10))`.
- **Lights.** Up to 16 in view space. `Pos.w = 0` means directional.
  Attenuation is `max(1−(d/range)², 0) / (c0 + c1·d + c2·d²)`.
- **Shadows.** Light 0 only. Four cascades picked by view z, with a hard
  switch. Each cascade uses 4 comparison taps at (−1,−1), (0,−1), (−1,0) and
  (0,0) texels, equally weighted. Bias is a vertex normal offset of
  `0.2 + 0.001·viewZ`, with none in the pixel shader.
- **Environment.** A per-world sky sphere map with +Y at the centre and mip
  chosen from gloss. It uses an analytic EnvBRDF (bit-exact constants in
  objects.md §5.6) and is tinted by `g_EnvironmentColor.rgb`. It fades to the
  map's average colour for downward reflections. With it present, ambient
  becomes `(1 − EnvBRDF)·ambient`.
- **Fog.** `smoothstep(sat((|P| − start)/(end − start))) · density`, radial.
- **Colour space.** Colour textures are sRGB views (linear lighting).
  Vertex colours get `pow(c, 2.2)` in the vertex shader. Normal maps are
  signed two-channel (BC5_SNORM), z is reconstructed, and the tangent frame is
  derived per pixel from derivatives. Terrain and water add a 4×-tiled detail
  normal via `frac(uv·4)`.
- **Tone mapping.** None.

## How it maps onto OpenShim Enhanced

The table compares BZCC with `openshim_enhanced_base-sm4.hlsl` and
`openshim_enhanced_terrain-sm4.hlsl`.

| Aspect | BZCC | OpenShim Enhanced today | Port action |
|---|---|---|---|
| Shininess → α | `sqrt(2/(n+2))` | Was `2/(n+2)` (double-squared); PR #572 fixes objects | Fix terrain to match after a look check |
| D normalisation | no 1/π | 1/π inside GGX, ×1.0 compensation | Keep the physically normalised form; calibrate peak instead |
| Visibility | Hammon approx | Smith-Schlick `k=(r+1)²/8` | Optional; close in practice |
| Diffuse scale | 1.0 | 2.7/π ≈ 0.86 | Raise with terrain in one exposure pass |
| Terminator | smoothstep on geometric N·L | none | Add; cheap |
| Normal maps | BC5, no sharpening, detail ×4 on terrain | DXT1, XY×1.85 sharpening, variance roughness | Reduce sharpening; BC5 re-encode is an asset task |
| Environment | per-world sphere map + analytic EnvBRDF + env tint | none on stock path; CR IBL = neutral cubemap, 18% tint | Port EnvBRDF; per-planet env source; ambient·(1−EnvBRDF) |
| Ambient / light colour space | raw v/255, not decoded; fog pow 2.2 (captured) | not decoded under linear light | At parity; keep |
| Shadows | 4 cascades, 4-tap, light 0, normal-offset bias | 3 cascades PSSM v2, PCF 4, floor 0.22 | Normal-offset bias is worth trying |
| Cutout | derivative coverage remap + mip-aware widening | no shader-side discard or coverage (material state only) | Port (objects.md §5.7) |
| Two-sided | flip N on back faces | no `SV_IsFrontFace` use | Port for cull-none materials only |
| Water | screen-copy refraction, `exp2(−9.28·|N·V|)` Fresnel, CPU UV matrices | none comparable | Separate project |

## CPU-side state (RenderDoc capture)

These values can't be read from DXBC. They come from a RenderDoc 1.46 D3D11
capture of stock `isdf01.bzn` (Pluto), taken 2026-10-22. The capture was one
frame at 1268x513 windowed. Confidence tags are as above.

### Constant buffers

The names below come from the shader reflection.

| Buffer | Contents |
|---|---|
| PS `psfloats` (128 B) | `FogColor`@0, `FogParams`@16, `MaterialDiffuse`@32, `MaterialSpecular`@48, `MaterialEmissive`@64, `LightAmbient`@80 (float3), `LightCount`@92, `TeamColor`@96, `EnvironmentColor`@112 |
| PS `pslights` | 16 lights × 80 B: `Pos` f4 @0, `Dir` f3 @16, `Color` f3 @32, `Attenuation` f4 @48, `Spot` f3 @64 |
| PS `psshadow` | cascade split points, inverse shadow-map sizes |
| PS `psview` | `g_View`, `g_Proj` |
| PS `pswater` | `g_WaterColor1..3`, `g_WaterUVOffset1/2` |
| VS `StdBuffer` | `g_World`, `g_WorldView`, `g_WorldViewProj`, `g_BackActive`, `g_ClipPlane` |
| VS `psshadow` / `vsterrain` | `g_ShadowWorldViewProj1..4` / `g_ActiveLayers` |

### Answers

1. **Light and ambient colours are uploaded raw: v/255, with no decode [H].**
   - For isdf01, ambient (10,15,15)/255 is uploaded as (0.0392, 0.0588,
     0.0588).
   - The sun colour is exactly 50/255.
   - Material diffuse 204/255 is 0.8, and specular 10/255 is 0.0392.
   - **Fog is the one exception:** `g_FogColor` is pow(v/255, 2.2). For
     example, 8/255 is uploaded as 0.00049.
   - Textures are `*_SRGB` views. So BZCC lights linear textures with
     gamma-authored light colours, exactly as OpenShim Enhanced does today.
     **There is no colour-space gap to close here.**
2. **`g_EnvironmentColor` is (1,1,1,0) on every object, terrain and water draw [H].**
   The env tint is white, and with w=0 the chrome (`c`) blend is off. The sphere
   map is t27: 1024², BC1_SRGB, 11 mips. On Pluto it is probably the
   `.sky`-listed `pluto_environ` [M]. So the planet colour of the sheen comes
   entirely from the map itself.
3. **Specular power: `MaterialSpecular.w = log2(specularPower)` [H].** Terrain
   uses w=10.0 for `.trn` SpecularPower 1024. Objects use w = 4.32, 5.0 and
   6.64 (powers 20, 32 and 100). Water uses w ≈ 11.97 (power ≈ 4000).
4. **Light encoding.**
   - **Layout [H].** The directional sun is always slot 0, with `Pos.w=0`.
     `Pos` holds the unit vector towards the sun and `Dir = −Pos`.
     `Attenuation` is (1,0,0,—) and `Spot` is (1,0,0).
   - **Point-light attenuation [H].** Point lights have `Pos.w=1`, and
     `Attenuation` = (c0, c1, c2, range) = (1, 0, 0.006, 50).
   - **Point-light colour [H].** Colours may exceed 1. A red (3,0,0) light
     appeared in the frame.
   - **Spot [L].** Every point light had `Spot` = (0.969, 0.540, 1.0). The
     frame had no true spotlight, so this field's meaning is unconfirmed.
5. **Pipeline state [H].**
   - **Samplers.** The PS has two:
     - s0 is used for colour, normal, spec and env. It is anisotropic 16×,
       wrap, LOD bias 0.
     - s7 is the shadow sampler: linear min/mag, point mip, comparison
       `GreaterEqual`, border clamp.
   - **Depth.** Reverse-Z (`GreaterEqual`).
   - **Shadows.** Four cascades at 4096² (R32), with splits at
     14.8 / 44.5 / 133.3 / 400. The shadow pass has no PS, no cull and zero
     raster depth bias, so all bias is the VS normal offset.
   - **Cutout.** Cutout draws never use alpha-to-coverage, so cutout is the
     shader's discard and coverage remap.
   - **Blend.** Water is premultiplied (One / InvSrcAlpha). Particles are
     additive.
   - **Formats.** The scene target is R16G16B16A16_FLOAT with 8× MSAA and
     D32. The backbuffer is R8G8B8A8_SRGB.
6. **Post-processing: none [H].**
   1. Shadows, then opaque objects and terrain.
   2. MSAA resolve into the water copy.
   3. Water, particles and HUD, drawn into the same target.
   4. A second resolve.
   5. One plain fullscreen quad into the sRGB swapchain.

   There is no bloom, no tone map and no AA pass beyond the MSAA. HDR values
   above 1 clip at output.
7. **Water `t10` is a resolved FP16 copy of the scene colour [H].** It is taken
   after all opaque objects and terrain, and before the first water draw.

Still open:

- The `Spot` semantics.
- Which BZCC materials ship the `c`/`o` variants.
- Values on other planets. Only Pluto was captured.

### What this changes for the port

- **Ambient and lights.** Finding 3 in
  [the gap doc](../REDUX_GRIZZLY_BZCC_SHADING_GAP.md) is withdrawn: do not
  decode the engine colours. Only `ambient·(1−EnvBRDF)` remains to port.
- **Env tint.** `g_EnvironmentColor` = 1 means the env term is
  `envMap · EnvBRDF` with no extra tint. The per-planet map is the part that
  matters.
- **Samplers.** Match 16× anisotropic filtering on the Enhanced colour and
  normal samplers, if they use less.
- **Render target.** 8× MSAA on an FP16 target with no tone map is BZCC's
  whole "post" stack. Matching MSAA matters more than adding post effects.
