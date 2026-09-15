# The terrain detail map contract — what `DetailMap` art has to be

Date: 2026-09-15
Shaders: stock `BZ_ASSETS_CORE/pc/programs/dx11/terrain-sm4.hlsl`,
OpenShim `resources/renderer/enhanced/openshim_enhanced_terrain-sm4.hlsl`
Reference art: the seven stock maps under
`BZ_ASSETS/pc/textures/TerrainTextures/Detail/`

A terrain detail map is not an ordinary texture, and authoring it like one
produces a specific, diagnosable artefact. This is the contract, measured from
the shaders that consume it and the art that ships with the game.

---

## 1. What the shader does

Stock, `terrain-sm4.hlsl:402`:

```hlsl
float3 detailTex   = detailMap.Sample(detailSam, frac(vTexCoord * 8)).xyz * 2;
float  detailDistance = saturate(vDepth * 0.025);
float3 detailColor = lerp(detailTex, fullbrightDetail, detailDistance);
oColor.xyz = lerp(oColor.xyz, oColor.xyz * detailColor, diffuseTex.a);
```

Four facts follow, and each one matters:

**0.5 is neutral, not 0.** The sample is multiplied by 2, so a map averaging
0.5 multiplies terrain by 1.0. A map averaging 0.26 multiplies by 0.52.

**The tiling rate is fixed in the shader** (`frac(vTexCoord * 8)`), not in the
material. So the file's resolution is what sets on-screen detail density — there
is no UV scale to compensate with.

**The effect is near-field only.** `saturate(vDepth * 0.025)` reaches white at
**40 units**. A wrong mean is therefore not a global tint: it is a brightness
disc roughly 40 m across, centred on the camera, that slides along with the
player. That is the artefact to recognise.

**It is gated by `diffuseTex.a`.** A DXT1 atlas with no 1-bit-alpha block decodes
`a = 1`, so the gate is open — which is the normal case.

The texture units set no `gamma` anywhere in `BZTerrainBase.material`, so the
map is sampled **linearly**. It is numerical modulation, not colour.

## 2. What Enhanced does differently

`openshim_enhanced_terrain-sm4.hlsl` keeps the same neutral point deliberately:

```hlsl
static const float OSE_TERRAIN_DETAIL_CONTRAST = 0.55;
float3 detail_modulation(float3 rawDetail)
{   return 1.0 + (rawDetail * 2.0 - 1.0) * OSE_TERRAIN_DETAIL_CONTRAST; }
```

with a comment recording why: an sRGB decode "would turn 0.5 into ~0.214, so the
neutral point would become ~0.43 and the whole terrain would darken by more than
half".

Enhanced then differs in three ways: contrast is damped to **0.55**, the whole
contribution is weighted by a further **0.35**, and a **second octave** is
sampled at `vTexCoord * 32` and multiplied in, fading out by 12.5 units while the
base octave reaches 66.

Net effect on authoring:

| path | multiplier | 1σ brightness swing at stock contrast |
|---|---|---|
| Redux / stock | `raw * 2` | **±28% to ±41%** |
| Enhanced | `1 + (raw*2−1)·0.55`, ×0.35, two octaves | ~±5–8% per octave |

**Tune for stock.** It applies the full swing, so it is the demanding case; a map
that reads correctly there is merely subtler under Enhanced, never broken. The
one thing Enhanced prefers is resolution, because its `*32` octave samples four
times tighter than stock ever does.

## 3. The stock envelope, measured

All seven stock maps: **2048², DXT1, 2.67 MB**, full mip chain.

| | min | median | max |
|---|---|---|---|
| mean | 0.4634 | 0.5053 | 0.5479 |
| std | 0.1389 | 0.1617 | 0.2029 |
| saturated texels | 0.010% | 0.268% | 1.567% |

Two things to take from this. The mean tolerance is roughly ±0.05, not an exact
0.5. And stock **uses the full 0..1 range** — every stock map has texels at both
0 and 255 — so a correction budget that forbids saturation is tighter than the
art it is imitating.

## 4. Budget the two ends separately

A texel at 1.0 becomes a **2× multiplier** — that is what "blinding" means. A
texel at 0.0 becomes **0×**, which reads as dark speckle. They are not the same
risk, so they do not deserve the same budget.

Worked example, from correcting ISDF Chronicles' `bane_detail` (σ 0.065, far
below the band, so its detail was doing almost nothing — about a 2% swing under
Enhanced):

| | σ | % at 0 | % at 1 | p99 multiplier | % above 1.5× |
|---|---|---|---|---|---|
| stock `ac_detail` | 0.203 | 0.54% | 1.03% | **2.00** | 8.92% |
| stock `io_detail` | 0.162 | 0.08% | 0.18% | 1.87 | 9.62% |
| `bane` lifted to band | 0.162 | 2.92% | **0.00%** | **1.49** | 0.63% |

Lifting it to full stock contrast peaks at 1.49× where stock peaks at 2.00×. A
single symmetric budget refuses that correction — the dark end exhausts it while
the bright end sits unused — and stops short for a reason unrelated to glare.

## 5. Gotchas

- **`white.png` is the placeholder** in `BZTerrainBase.material`. White raw = 1.0
  → a **2× multiplier**. A world that fails to alias `DetailMap` renders at
  double brightness in the near field, not unchanged.
- **BC1 costs these maps essentially nothing.** Measured on 4096² detail art:
  pre-compression σ 0.1164, decoded 0.1169. Uncompressed detail maps are pure
  waste — ISDF Chronicles shipped 8192² uncompressed at 256 MB each against
  stock's 2.67 MB.
- **Verify by decoding the written file, not the array you meant to write.**
  Correcting the mean and then reporting the target rather than the achieved
  value hides exactly the cases that failed; on heavy-tailed art, applied gain
  and achieved contrast are different quantities because clipping takes the
  added variance back.

## 6. Tooling

`Battlezone98Redux_WorldBuilder/scripts/cc_atlas/detail_maps.py` implements all
of the above: mean to 0.50, contrast into the stock band only when it falls
outside, split saturation budgets, DXT1 with a full mip chain, and verification
by decoding the output.
