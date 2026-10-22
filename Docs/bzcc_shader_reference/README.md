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
| Ambient / light colour space | Unknown CPU-side; see below | not decoded under linear light | Settle with RenderDoc first |
| Shadows | 4 cascades, 4-tap, light 0, normal-offset bias | 3 cascades PSSM v2, PCF 4, floor 0.22 | Normal-offset bias is worth trying |
| Cutout | derivative coverage remap + mip-aware widening | no shader-side discard or coverage (material state only) | Port (objects.md §5.7) |
| Two-sided | flip N on back faces | no `SV_IsFrontFace` use | Port for cull-none materials only |
| Water | screen-copy refraction, `exp2(−9.28·|N·V|)` Fresnel, CPU UV matrices | none comparable | Separate project |

## Open CPU-side questions (need a frame capture)

These cannot be read from DXBC. They are queued for a RenderDoc capture of a
BZCC frame with the Grizzly in view:

1. **Light and ambient colours.** Are `g_LightAmbient` and light `m_Color`
   uploaded linear, or raw 8-bit gamma? The ambient calibration in BZR
   depends on this.
2. **Environment colour.** `g_EnvironmentColor` values per world, and which
   materials get the `c`/`o` variants.
3. **Specular power.** Confirm `matSpec.w = log2(specularPower)`. For the
   Grizzly's 38.44 that is ≈ 5.26, giving α ≈ 0.22.
4. **Light encodings.** How directional and point lights fill `Atten` and
   `Spot`.
5. **Pipeline state.** Sampler states, the shadow comparison function and
   the cutout blend state.
6. **Water's screen copy.** What `t10` holds and when it is captured.
