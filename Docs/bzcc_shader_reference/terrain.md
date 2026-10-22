# BZCC TERRAIN shader family: formula-level specification

Source: 81 pixel shaders (`dx11_terrain_psh_8p*.fxc`) and 10 vertex shaders (`dx11_terrain_vsh_8v*.fxc`), SM5, input layout 8.
Method: `fxc /dumpbin` disassembly, minimal-pair diffs, full decode of the maximal pixel variants `8pdneslzoa` and `8pdtneslzoa`, and every vertex shader.
Disassembly is not committed; regenerate it as described in README.md. The comparison object shader was `dx11_default_psh_0pdneslzo`.

Confidence tags: [H] read directly from the instructions, [M] inferred from instructions plus convention, [L] guess or unobservable from DXBC.

Conventions: all colors are in the shader's working space (see Section 9). `sat` = clamp to 0..1. `lerp(a,b,t)=a+t(b-a)`. DXBC `exp`/`log` are base 2. Every `pow` in the original appears as `log2, mul, exp2`.

---

## 0. Headline findings

1. The lighting core (GGX D, Hammon visibility, Schlick Fresnel, Lazarov-style environment BRDF, light loop, terminator, shadows, fog) is instruction-for-instruction the same as the BZCC object shader. [H] Terrain only differs in how the material inputs are produced (four-layer weighted lerp, detail normal, no back-face flip).
2. The filename grammar for terrain differs from the earlier survey. The letters are: `d` diffuse (always present), `t` team color constant (not a texture), `n` normal map plus tiled detail normal, `e` emissive (always present), `s` specular texture, `l` lights, `z` shadows, `o` environment, `a` layers 1-3. [H]
3. Terrain has **no** `t` team-mask texture. Terrain texture slots per layer are diffuse, normal, specular, emissive, detail-normal. This corrects the "diffuse/team/normal/emissive/specular" table in the backport report. [H]
4. Layer blending is a plain sequential lerp chain driven by `color1.xyz`. There is no height blending, no alpha-based blending, and no per-layer UV scale. [H]
5. The only tiling in the shader is a fixed 4x `frac()` detail-normal lookup. All layers share the one `texcoord0`. [H]
6. Specular exponent: the instruction is `exp2`, so `alpha^2 = 2 / (2^G + 2)` with `G = specTex.a * matSpec.w`. The briefing wrote `exp(...)`; if that was copied from the asm it is really base 2. Objects use the identical instruction. [H]

---

## 1. Permutation matrix

Name = `dx11_terrain_psh_8p` + `d` + [`t`] + [`n`] + `e` + [`s`] + [`l`] + [`z`] + [`o`] + [`a`], plus the bare `8p`. Count: 1 + 2(t) x 2(n) x 2(s) x 2(a) unlit + 64 lit = 81. [H]

| Letter | Effect | Conf |
|---|---|---|
| (none, `8p`) | No textures. `out = fog(sat(color0) * matDiffuse)`. | H |
| `d` | Diffuse texture t0 (+t5,t10,t15 with `a`). | H |
| `t` | Diffuse tint is `g_TeamColor` (rgba) instead of `sat(color0) * g_MaterialDiffuse`. Vertex color0 and `g_MaterialDiffuse` are ignored. No team texture exists. | H |
| `e` | Emissive texture t3 (+t8,t13,t18 with `a`). Present in all but `8p`. | H |
| `n`, `s` | **No effect without `l`.** `de`, `dne`, `des`, `dnes` compile to identical 21-slot programs. | H |
| `l` | Lighting enabled. | H |
| `n` (lit) | Normal map t1 plus detail normal t4 (per layer). Else geometric normal. | H |
| `s` (lit) | Specular texture t2 (per layer). Else constant `g_MaterialSpecular`. | H |
| `z` | 4-cascade shadow map on light 0 only (t28-t31, sampler s7). | H |
| `o` | Environment reflection and environment-scaled ambient (t27). | H |
| `a` | Layers 1-3 (second to fourth) for every texture group. Also enables the vertex-side `color1 * g_ActiveLayers` output. | H |

Unlit (`l` absent): `rgb = fog(diffuse + emissive.rgb * emissive.a)`, no lighting math at all. [H]

Inputs the pixel shader actually reads: unlit non-`a` uses color0 (non-`t`), uv, view position. Lit uses view position, interpolated view-space normal, uv, and with `a` the `color1` weights. With `t` the color0 input is dropped entirely. [H]

---

## 2. Vertex shaders (10): exact behavior

All ten share the same skeleton. Variants only add outputs. [H]

```hlsl
// StdBuffer (cb0): g_World, g_WorldView, g_WorldViewProj, g_BackActive(unused), g_ClipPlane
// Matrices are stored so that out = mul(M, float4(p,1)) (column-major, rows 8..11 = WVP).
o.pos        = mul(g_WorldViewProj, float4(pos, 1));
o.color0.rgb = pow(max(color0.rgb, 0), 2.2);   // gamma -> linear, plain 2.2 power, not sRGB piecewise
o.color0.a   = color0.a;                         // alpha untouched
o.uv         = texcoord0.xy;                     // no transform, no per-layer scale
o.viewPos    = mul(g_WorldView, float4(pos,1)).xyz;
o.clip       = dot(g_ClipPlane, mul(g_World, float4(pos,1)));   // SV_ClipDistance0, world-space plane
```

- `8v` (unlit, no `a`): outputs color0, uv, viewPos, clip. Normal and color1 are not read. [H]
- `l`: additionally `o.viewNormal = mul((float3x3)g_WorldView, normal)` (not normalized, not inverse-transpose). [H]
- `a`: additionally `o.color1 = color1 * g_ActiveLayers` (all four components; the pixel shader uses only xyz). [H]
- `z`: additionally four shadow-space positions with a **normal offset**:
  ```hlsl
  float off = max(viewPos.z, 0) * 0.001 + 0.2;      // object-space units
  float3 ps = pos + normal * off;                    // object-space normal, unnormalized-as-stored
  o.shadow[i] = mul(g_ShadowWorldViewProj[i], float4(ps, 1));   // i = 0..3, cb1 (psshadow in VS)
  ```
  The offset grows 0.1 per 100 view-z units. [H]
- `o` adds nothing (the `vlo` program is identical to `vl`). [H]
- `g_BackActive` is unused by terrain. [H]

Pixel input mapping differs per variant (registers shift), but semantics are as above.

---

## 3. Layer blending

Weights come only from vertex `color1`, scaled per-layer by `vsterrain.g_ActiveLayers`:

```hlsl
float3 w = sat(color1.xyz * g_ActiveLayers.xyz);   // VS multiply, PS saturate
// layer 1 = texture group 5..9, layer 2 = 10..14, layer 3 = 15..19
T = L0;
T = lerp(T, L1, w.z);
T = lerp(T, L2, w.y);
T = lerp(T, L3, w.x);
```

Equivalent explicit weights: w0=(1-wz)(1-wy)(1-wx), w1=wz(1-wy)(1-wx), w2=wy(1-wx), w3=wx. [H]

- Later layers override earlier ones. Weights are not renormalized, so painted weights need not sum to 1. [H]
- Layer 0 has no weight; it is the remainder. [H]
- The identical weights and identical lerp chain are applied to every texture group: diffuse rgba, normal xy, detail-normal xy, specular rgba, emissive rgba. [H]
- No height/heightmap blending, no alpha-based blending, no sharpness constants exist anywhere in the family. The diffuse alpha is simply lerped like the color, and becomes the output alpha. [H]
- `g_ActiveLayers`: xyz are almost certainly 0/1 enables (or scalars) that mask layers 3,2,1 as x,y,z. The `.w` multiplies color1.w, which is never read. [M] Actual CPU values: not observable. [L]
- Which byte of the on-disk vertex color becomes `.x/.y/.z` depends on the input-layout format (RGBA vs BGRA). In shader-register terms layer1 uses `.z`, layer2 `.y`, layer3 `.x`; whether those correspond to B, G, R of the stored color depends on the layout format; check against a real mesh. [L]
- Non-`a` variants sample only layer 0 (t0, t1, t2, t3, t4) and ignore color1. [H]

---

## 4. UV tiling

- One UV set. `uv = texcoord0.xy` passes through unchanged. No scale, offset, rotation, animation. All four layers and all slots (except the detail normal) sample the same uv. [H]
- Effective per-layer tiling is therefore baked in the mesh UVs and the (CPU-side) sampler address mode. Wrap vs clamp, filter, and anisotropy are in sampler `s0` state and are not visible in DXBC. [L]
- Detail normal (only with `n` and `l`): `uvD = frac(uv * 4.0)`, sampled with the same sampler `s0`. Fixed 4.0 for every layer and every variant (constant appears in all 32 `n`+`l` files). [H]
  - `frac()` makes the UV derivatives jump at tile edges. With hardware mip selection this produces a one-texel seam line at every 1/4 uv boundary unless the texture's mips are flat. [M] (Behavioral consequence of the instructions; not observed on screen.)
- No macro/distance texture, no triplanar, no distance fade of detail. [H]

---

## 5. Normal mapping

Only in lit `n` variants. Otherwise `N' = N` (normalized interpolated view-space geometric normal). Terrain does not flip normals for back faces (the object shader does via `is_front_face`). [H]

### 5.1 Tangent frame (per pixel, derivative based, coarse derivatives)

Computed in view space with `ddx_coarse/ddy_coarse` of view position and uv. This is the Schuler-style cotangent frame with no handedness term, identical to objects. [H]

```hlsl
float3 N   = normalize(viewNormal);
float3 dp1 = ddx_coarse(viewPos), dp2 = ddy_coarse(viewPos);
float2 du1 = ddx_coarse(uv),      du2 = ddy_coarse(uv);
float3 dp2perp = cross(dp2, N);
float3 dp1perp = cross(N, dp1);
float3 T = dp2perp * du1.x + dp1perp * du2.x;
float3 B = dp2perp * du1.y + dp1perp * du2.y;
float  inv = rsqrt(max(dot(T,T), dot(B,B)));      // "+0" in the source: no epsilon
T *= inv;  B *= inv;
```

Because there is no epsilon, degenerate uv derivatives (inv = infinity) can produce NaN. [M] (matches the stability item already in the backport report.)

### 5.2 Normal from textures

```hlsl
float2 nB = blend4(t1, t6, t11, t16).xy;         // base normal, same lerp chain/weights as diffuse
float2 nD = blend4(t4, t9, t14, t19).xy;         // detail normal at frac(uv*4)
float2 n  = nB + nD;                             // plain addition of xy, no UDN/whiteout scaling
float  nz = sqrt(max(1 - dot(n,n), 0));          // saturated: terrain already has the fix
float3 Np = normalize(T * n.x - B * n.y + N * nz);
```

- **No `*2-1` expansion** appears. The textures must be signed (SNORM, e.g. BC5_SNORM / R8G8_SNORM) or the sampled values are already in [-1,1]. [M] Objects decode identically.
- Y is negated (the green channel flips the bitangent). [H]
- If |n|>1, z clamps to 0 and the final normalize still rescales. Base+detail can exceed 1 easily. [H]
- The geometric normal (`N`, normalized, not `Np`) is used for the terminator term (Section 6.5), not the mapped normal. [H]
- One normal-map level and one detail level per layer; nothing is shared across layers. [H]

---

## 6. Lighting (lit variants)

### 6.1 Material inputs

```hlsl
// texture groups blended with the layer chain
D  = blend4(t0,t5,t10,t15)                          // rgba
if (t)  tint = g_TeamColor;                          // rgba
else    tint = sat(color0) * g_MaterialDiffuse;      // color0 already ^2.2 in VS
albedo = D * tint;                                   // alpha = D.a * tint.a (output alpha)

if (s)  S = blend4(t2,t7,t12,t17) * g_MaterialSpecular;   // rgba multiply
else    S = g_MaterialSpecular;
F0    = S.rgb;
G     = S.a;                       // gloss parameter (specTex.a * matSpec.w)
// a2 and alpha: see below
```

Precisely: `a2 = 2 / (max(exp2(G), 0) + 2)`, `alpha = sqrt(a2)`. [H]
`exp2` here is DXBC `exp`. The briefing's reference formula and the terrain formula match numerically only if both are base 2. [H]

### 6.2 Common vectors (view space)

```
I = normalize(viewPos)            // eye -> surface
NoVs = I . Np                      // negative for front-facing
NoV  = max(-NoVs, 0)
Rv   = I - 2 * NoVs * Np           // reflection of I
```

### 6.3 Light loop (`i = 0 .. int(g_LightCount.w) - 1`, max 16)

`pslights` holds 5 float4 per light: pos, dir, color, atten, spot. [H]

```hlsl
Lvec = light.pos.xyz - viewPos * light.pos.w;   // w=1 positional, w=0 directional [M]
d    = length(Lvec);   L = Lvec / d;
rangeTerm = max(1 - (d / light.atten.w)^2, 0);
att  = rangeTerm / (light.atten.x + light.atten.y*d + light.atten.z*d*d);   // dot(atten.xyz, (1,d,d^2))
// spot
c    = dot(L, -light.dir);
sp   = pow(sat((c - light.spot.y) / (light.spot.x - light.spot.y)), light.spot.z);
att *= sp;
if (i == 0) att *= shadow;       // ONLY the first light is shadowed (r9.w trick)
// terminator on the GEOMETRIC normal
att *= smoothstep01(sat((dot(N, L) + 0.1) * 10));   // s*s*(3-2s)
NoL  = sat(dot(Np, L));
E    = lightColor * att * NoL;
```

- For non-spot lights the cone term must evaluate to 1 (CPU sets `spot` to values that make it so). How is unobservable. [L]
- Positional vs directional split is via `pos.w`. [H] That `pos.xyz` is a unit vector for directionals: [L].

BRDF per light: [H]

```hlsl
// H-based terms from L and I only
invHL = rsqrt(2 - 2*dot(L, I));                    // 1/|L - I|, with I = -V
NoH   = sat((dot(Np,L) - NoVs) * invHL);            // n . (L+V) / |L+V|
LoH   = sat(invHL * (1 - dot(L, I)));               // = sqrt((1 - L.I)/2)
F     = F0 + (1 - F0) * (1 - LoH)^5;
dd    = (NoH*NoH*(a2 - 1) + 1)^2;                   // GGX denominator
vis   = lerp(2*NoL*NoV, NoL + NoV, alpha);           // Hammon; NoL here is sat(dot(Np,L))
spec += F * E * a2 / (2 * dd * vis + 1e-6);          // note: 0.5/vis folded into the 2*, no 1/pi
diff += E * (1 - F);                                 // energy-conserving, no 1/pi
```

So `spec = E * F * D_noPi * V` with `D_noPi = a2/dd`, `V = 0.5/vis`. [H] No 1/pi anywhere in D or diffuse. [H]

### 6.4 Final composition (lit)

```hlsl
color.rgb = albedo.rgb * diffAccum + specAccum + emissive.rgb * emissive.a;   // emissive Section 7
// diffAccum init  = ambient            (no 'o')   or  (1 - envBRDF)*g_LightAmbient   ('o')
// specAccum init  = 0                  (no 'o')   or  envSpec                        ('o')
// then fog (Section 8)
color.a = albedo.a;
```

Ambient is multiplied by albedo like any light. It is not multiplied by shadow. [H]

### 6.5 Terminator

`smoothstep(0,1, sat((dot(Ngeom, L) + 0.1) * 10))`, applied to every light's contribution, using the interpolated, renormalized **geometric** normal. Matches the object description exactly. [H]

### 6.6 Shadows (`z`)

Applies to light index 0 only, cascade chosen by view-space depth `viewPos.z`: [H]

```
if      (viewZ <= split.x) c = 0
else if (viewZ <= split.y) c = 1
else if (viewZ <= split.z) c = 2
else if (viewZ <= split.w) c = 3
else shadow = 1                         // beyond the last split: unshadowed, no blend band
p = shadowPos[c].xyz / shadowPos[c].w;  // already in [0,1] texture space (bias baked in matrices) [M]
ref = min(p.z, 1);
tex = p.xy / invMapSize[c];             // texel space
shadow = 0.25 * ( cmp(map[c], (tex + (-1,-1))*inv, ref)
                + cmp(map[c], (tex + ( 0,-1))*inv, ref)
                + cmp(map[c], (tex + (-1, 0))*inv, ref)
                + cmp(map[c], p.xy,               ref) );
```

- `cmp` = `SampleCmpLevelZero` with comparison sampler `s7`, textures t28..t31 for cascades 1..4. [H]
- The 4-tap kernel is offset toward -x/-y (not centered). If `s7` is a linear-filter comparison sampler, each tap is a bilinear PCF; filter mode is unobservable. [L]
- No cascade blending, no pixel-shader depth bias; the bias is the vertex normal offset (Section 2) plus any raster depth bias in CPU state. [H]
- Differences from objects: none in this stage. [H]

---

## 7. Emissive

```hlsl
E4 = blend4(t3, t8, t13, t18) * g_MaterialEmissive;     // rgba
color.rgb += E4.rgb * E4.a;
```

Alpha of the emissive texture acts as an intensity gate. Present in every variant except `8p`. In unlit variants it is the only addition. [H]

---

## 8. Ambient, environment and fog

### 8.1 Ambient (non-`o`) [H]
`diffAccum0 = g_LightAmbient.rgb` (cb0 offset 80), `specAccum0 = 0`.

### 8.2 Environment (`o`) [H for formulas; M for interpretation]

```hlsl
s     = sat(G * 0.1);                       // smoothness
// Lazarov-style analytic environment BRDF
k     = float4(1.041667, 0.475, 0.018229, 0.25) * s + float4(0, 0, -0.015625, 0.75);
e     = min(k.y, exp2(-9.28 * abs(dot(I, Np))));
b0    = k.x * e + k.z;
envBRDF = sat(F0 * (k.w - b0) + b0);        // per-channel
Rw    = mul(transpose(R3x3(g_View)), Rv);   // view->world via dot with the rows of cb3
q     = Rw + float3(0,1,0);
m2    = dot(q,q);
uvE   = Rw.xz * 0.5 * rsqrt(m2) + 0.5;      // sphere map, +Y axis at the center
lodNat= 0.5 * log2(max(|ddx(uvE*size)|^2, |ddy(uvE*size)|^2));
lod   = max((1 - s) * mipCount, lodNat);
envS  = EnvTex.SampleLevel(s0, uvE, lod).rgb;
envA  = EnvTex.SampleLevel(s0, (0.5,0.5), mipCount).rgb;   // coarsest mip = average color
env   = lerp(envA, envS, min(m2, 1)) * g_EnvironmentColor.rgb;
envSpec  = envBRDF * env;
diffAccum0 = (1 - envBRDF) * g_LightAmbient.rgb;
specAccum0 = envSpec;
```

- The environment texture (t27) is a 2D sphere-map style image in world space with +Y at its center; the singular direction (-Y, `m2 -> 0`) blends to the average color. [M]
- Reflection tint uses `g_EnvironmentColor` (cb0 offset 112). No separate fog or shadowing on the env term. [H]
- Same constants and code as the object shader. [H]
- The view matrix is used only for its 3x3 rotation (`g_Proj` unused). [H]

### 8.3 Fog (all 81 variants) [H]

```hlsl
d  = length(viewPos);                                  // radial, view space
t  = sat((d - g_FogParams.y) / (g_FogParams.z - g_FogParams.y));
f  = t*t*(3 - 2*t) * g_FogParams.x;                    // smoothstep * density
out.rgb = lerp(color.rgb, g_FogColor.rgb, f);
```

Matches the object fog: radial smoothstep fog, density is a final multiplier. Fog never touches alpha. [H]

---

## 9. Color space notes

- Vertex color0 is converted `^2.2` in the VS, so it is treated as a gamma-space value feeding a linear pipeline. Vertex color1 weights are not converted. [H]
- The shaders do not convert texture colors. Whether t0/t5/t10/t15 etc. are sRGB views is a CPU/texture-format fact not visible in DXBC. [L] The linearized vertex color and the lack of any output gamma strongly suggest sRGB texture views and a linear render path. [M]
- Output has no tonemap or gamma. [H]

---

## 10. Constant buffers: every field

### 10.1 `psfloats` (PS cb0), 128 bytes, used by all variants
| Offset | Field | Used by | Notes |
|---|---|---|---|
| 0 | `float4 g_FogColor` | all | rgb |
| 16 | `float4 g_FogParams` | all | x = density multiplier, y = start, z = end, w unused |
| 32 | `float4 g_MaterialDiffuse` | non-`t` | multiplies sat(color0) and diffuse alpha |
| 48 | `float4 g_MaterialSpecular` | lit | rgb = F0 tint, a = gloss multiplier (G) |
| 64 | `float4 g_MaterialEmissive` | all but `8p` | rgb tint, a gates intensity |
| 80 | `float3 g_LightAmbient` | lit | |
| 92 | `float g_LightCount` | lit | `ftoi`, loop bound (<=16) |
| 96 | `float4 g_TeamColor` | `t` | rgba, replaces vertex tint and matDiffuse |
| 112 | `float4 g_EnvironmentColor` | `o` | rgb |

### 10.2 `psshadow` (PS cb1), `z`
| Offset | Field |
|---|---|
| 0 | `float4 g_ShadowSplitPoints` (view-z far limits of cascades 1..4) |
| 16 | `float2 g_InvShadowMapSize1` |
| 24 | `float2 g_InvShadowMapSize2` |
| 32 | `float2 g_InvShadowMapSize3` |
| 40 | `float2 g_InvShadowMapSize4` |

### 10.3 `psview` (PS cb3), `o`
`float4x4 g_View` (rotation rows only; used to rotate the reflection vector to world space), `float4x4 g_Proj` (unused).

### 10.4 `pslights` (PS cb4), lit
`LightParams g_LightParams[16]`, 5 float4 each (1276 bytes, last light's spot is 12 bytes):

| Reg | Field | Use |
|---|---|---|
| 0 | `float4 m_Pos` | xyz position or direction, w = 1 positional / 0 directional |
| 1 | `float3 m_Dir` | spot axis |
| 2 | `float3 m_Color` | |
| 3 | `float4 m_Attenuation` | xyz = constant, linear, quadratic; w = range |
| 4 | `float3 m_Spot` | x = inner cos, y = outer cos, z = falloff exponent |

### 10.5 VS `StdBuffer` (cb0)
| Offset | Field | Use |
|---|---|---|
| 0 | `float4x4 g_World` | only for the clip distance |
| 64 | `float4x4 g_WorldView` | view position and view normal |
| 128 | `float4x4 g_WorldViewProj` | clip position |
| 192 | `float4 g_BackActive` | unused |
| 208 | `float4 g_ClipPlane` | world-space clip plane, SV_ClipDistance0 |

### 10.6 VS `psshadow` (cb1), `z`
`float4x4 g_ShadowWorldViewProj1..4` at offsets 0, 64, 128, 192.

### 10.7 VS `vsterrain` (cb2), `a`
`float4 g_ActiveLayers`, offset 0; multiplies `color1`.

### 10.8 Textures / samplers
| Slot | Content |
|---|---|
| t0,t5,t10,t15 | diffuse rgba, layers 0..3 |
| t1,t6,t11,t16 | base normal xy (`n`) |
| t2,t7,t12,t17 | specular rgb + gloss a (`s`) |
| t3,t8,t13,t18 | emissive rgba |
| t4,t9,t14,t19 | detail normal xy at frac(uv*4) (`n`) |
| t27 | environment sphere map (`o`) |
| t28..t31 | shadow cascades 1..4 (`z`) |
| s0 | general sampler; s7 | comparison sampler for shadows |

Slot usage was confirmed per letter combination from the resource bindings of all 81 files. [H] (Layer 0 for non-`a` is always t0..t4 as listed.)

---

## 11. Terrain vs object: differences

| Item | Object (`dx11_default`) | Terrain | Conf |
|---|---|---|---|
| GGX alpha^2 = 2/(2^G+2), Hammon V, Schlick, no 1/pi | yes | identical | H |
| Env BRDF constants, sphere-map lookup, ambient*(1-envBRDF) | yes | identical | H |
| Light loop, attenuation, spot, terminator, shadow cascades/PCF | yes | identical | H |
| Fog | radial smoothstep | identical | H |
| Tangent frame, normal decode (no *2-1, -Y) | same | same | H |
| Texture slots | diffuse t0, team t1, emissive t2, normal t3, spec t4 | diffuse/normal/spec/emissive/detail-normal per layer, 5 each | H |
| Team color | team-mask texture | constant tint only | H |
| Layering | none | 4 layers, `color1`-weighted lerp chain | H |
| Detail normal | none | frac(uv*4) per layer | H |
| Vertex color | n/a | color0^2.2 as tint (non-`t`) | H |
| Back-face normal flip | yes (`is_front_face`) | none | H |
| Cutout/derivative alpha test (`x`) | present | absent | H |
| Shadow normal offset in VS | not examined | `0.2 + 0.001*viewZ` | H |

---

## 12. Replication notes for BZR OpenShim Enhanced terrain

1. Keep the existing object lighting helper and feed it terrain-blended inputs; do not write a separate terrain BRDF.
2. Implement the layer chain exactly: `T = lerp(lerp(lerp(L0,L1,w.z),L2,w.y),L3,w.x)` per texture group, no normalization.
3. If BZR cannot bind 20 textures, any atlas/array must preserve the sequential-lerp semantics, since late layers fully override.
4. Add a detail normal at `frac(uv*4)` only if the BZR layer data supplies it; otherwise skip (it is a subtle effect).
5. Use `exp2` for the gloss mapping so the roughness matches objects.
6. Vertex color is a tint raised to 2.2; do not double-linearize.
7. Shadows: copy normal-offset-in-VS and the 4-tap offset PCF if matching look matters.

---

## 13. Unresolved / low confidence

- Byte order of vertex `color1` (which on-disk channel is layer 1/2/3). [L]
- Actual CPU values of `g_ActiveLayers`, `g_TeamColor`, `g_MaterialDiffuse`, spot defaults for non-spot lights, and `pos.w` conventions for directional lights. [L]
- Sampler states (`s0` address/filter/aniso, `s7` filter/comparison func) and texture formats (sRGB views, SNORM for normals, env map mip count). [L]
- Whether `frac(uv*4)` seams are visible in practice (depends on texture content and mip chain). [M]
- Whether terrain world space equals object space for the VS normal offset (offset is in object-space units). [M]
