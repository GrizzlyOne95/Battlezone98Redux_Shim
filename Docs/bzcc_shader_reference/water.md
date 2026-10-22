# BZCC `dx11_water_*` shader family: formula-level specification

Source: 40 pixel shaders (`dx11_water_psh_0p*`) and 10 vertex shaders (`dx11_water_vsh_0v*`), all SM5 DXBC.
Method: dumped with `fxc /dumpbin` (not committed; see README.md).
Every claim below comes from static disassembly. Nothing was run. Confidence tags: **[H]** read directly from the instructions, **[M]** inferred from the instructions plus convention, **[L]** guess.

Conventions used below:
- "view space" means the space of `WorldView * position`. +Z is forward, because the shaders divide by z.
- `sat(x)` is clamp to 0..1.
- `exp2` is the DXBC `exp` opcode, which is base 2.
- `mul(float4(u,v,0,1), M)` is the UV transform form.

---

## 1. Permutation grammar (decoded by minimal pairs) [H]

PS name: `0p` + `d` `e` + optional `n` `s` + optional lighting ladder + optional `a`.

| Letter | Meaning | Evidence |
|---|---|---|
| `0` | vertex layout 0 (POSITION3, NORMAL3, TEXCOORD0.xy) | VS input signature |
| `d` | layer-1 diffuse `t0`. Always present | present in all 40 |
| `e` | layer-1 emissive `t3`, times `g_MaterialEmissive`. Always present | present in all 40 |
| `n` | normal mapping. Adds `t1` (layer-1 normal) and `t4` (layer-1 "detail" normal, tiled 4x). Enables screen-space refraction distortion and the derivative-based tangent frame | `n` files add t1, t4, `deriv_*` and `frc` |
| `s` | specular map `t2`. Its RGBA multiplies `g_MaterialSpecular` | `s` files add t2 |
| `l` | dynamic light loop. Adds `pslights` (cb4), ambient, `g_LightCount` | cb4 and a `loop` appear |
| `z` | cascaded shadows, 4 cascades. Adds `psshadow` (cb1) and `t28..t31`. Only valid after `l`, and selects the shadow VS | `sample_c_lz` appears 16 times |
| `o` | environment sphere map `t27` plus `g_EnvironmentColor`. Only valid after `l` | t27 and cb0[7] |
| `a` | second surface layer. Adds `t5` (diffuse), `t6` (normal, with n), `t7` (specular, with s), `t9` (detail normal, with n). Also `g_WaterColor2` and `g_WaterUVOffset2` | cb2 grows from 5 to 7 registers |

The lighting ladder is `""`, `l`, `lo`, `lz`, `lzo`. That gives 2 (n) x 2 (s) x 5 x 2 (a) = 40 shaders.

**Texture slots.** Each layer has a five-slot group: diffuse, normal, specular, emissive, detail normal.

| Layer | diffuse | normal | specular | emissive | detail normal |
|---|---|---|---|---|---|
| 1 | t0 | t1 | t2 | t3 | t4 |
| 2 (`a`) | t5 | t6 | t7 | (t8 never sampled) | t9 |

Shared slots:
- t10: scene colour or "screen" copy
- t27: environment sphere map
- t28..t31: shadow cascades 1..4
- `s0`: ordinary sampler
- `s7`: comparison sampler for shadows (`g_SamplerPCF`)

No depth texture, no planar reflection texture and no foam or caustic texture exist anywhere in the family. [H]

## 2. Vertex shaders (10 files, only 2 distinct bodies) [H]

Files `0v`, `0va`, `0vl`, `0vla`, `0vlo`, `0vloa` share one body (18 instruction slots). Files `0vlz`, `0vlza`, `0vlzo`, `0vlzoa` share another (38 slots), which adds the shadow coordinates. The `a` and `o` letters do not change the VS.

```hlsl
// cb0 StdBuffer (see section 8)
clip.xyzw = mul(WorldViewProj, float4(pos, 1));      // SV_POSITION
uv_out    = uv_in;                                   // no animation or transform here
viewPos   = mul(WorldView, float4(pos, 1)).xyz;      // TEXCOORD1 -> PS v2
viewN     = mul((float3x3)WorldView, normal);        // TEXCOORD2 -> PS v3; NOT normalized, no inverse-transpose
clipDist  = dot(g_ClipPlane, mul(World, float4(pos, 1)));   // world-space user clip plane

// only in the 'z' VS:
float b   = 0.2 + 0.001 * max(viewPos.z, 0);         // normal-offset shadow bias, object-space units
float3 sp = pos + normal * b;
shadowCoord[i] = mul(ShadowWorldViewProj_i, float4(sp, 1));   // i = 1..4, TEXCOORD3..6 (xyzw kept for the PS divide)
```

- There is no vertex displacement, no time constant, and no wave function. The water mesh is flat except for the pixel normal map. [H]
- `g_ClipPlane` provides the reflection and underwater clipping. [M]
- The `psshadow` cbuffer in the VS holds 4 matrices (256 B). The same name in the PS holds 48 B of split points and texel sizes. Both bind at slot cb1, so they must be separate per-stage buffers. [M]

## 3. Animation and UV

- The only animation inputs are the two UV affine transforms `g_WaterUVOffset1` and `g_WaterUVOffset2`, and the two layer colours. There is no time constant in any shader. All motion (scroll, rotation, scale) is baked CPU-side into these matrices each frame. [H]
- Per-layer transform. The matrix is `float4x2`, column-major, with two registers. The code takes `.xyw` of each register:

```hlsl
uvL = float2( c0.x*u + c0.y*v + c0.w,
              c1.x*u + c1.y*v + c1.w );   // c0 = cb2[3] (layer 1) or cb2[5] (layer 2)
                                          // c1 = cb2[4] (layer 1) or cb2[6] (layer 2)
```

  Each is a 2x3 affine transform (rotation, scale and translation). The `.z` row is ignored. [H]
- Layer-1 samplers (diffuse, normal, specular, emissive) use `uv1`. Layer-2 samplers use `uv2`. [H]
- The "detail" normals (`t4`, and `t9` in `a`) use `frac(4.0 * meshUV)`. They are static (not animated) and tiled 4x. The `frac` makes mip selection jump at the tile seams. [H]
- Emissive `t3` uses `uv1` even in `a` variants. Layer-2 emissive is never sampled. [H]

## 4. Layer combine (`d`/`e`/`s`/`a`) [H]

Let `C1 = g_WaterColor1`, `C2 = g_WaterColor2`, `MD = g_MaterialDiffuse`, `ME = g_MaterialEmissive`, `MS = g_MaterialSpecular`.

Single layer (no `a`):
```hlsl
L1     = tex0(uv1) * C1;                  // RGBA
albedo = L1.rgb * MD.rgb;
alpha  = L1.a   * MD.a;
```

Two layers (`a`):
```hlsl
L1 = tex0(uv1) * C1;   T2 = tex5(uv2);
k  = C2.a / (C1.a * (1 - C2.a) + C2.a);   // depends ONLY on the two constant alphas; no epsilon, so C1.a=C2.a=0 gives NaN
rgbMix = lerp(L1.rgb, C2.rgb * T2.rgb, k);
a2     = T2.a * C2.a;
alpha  = (L1.a * (1 - a2) + a2) * MD.a;   // standard "over" on alpha using TEXTURE alpha
albedo = rgbMix * MD.rgb;
```
Colour weighting by `k` uses constants, while alpha uses the texture alpha. This is an approximate "over" operator. [H]

The same `k` blends every other layer-2 input: `normal`, `detail normal` and `specular` (below). In the `a` variants the second layer is therefore "k-weighted", not independently additive. [H]

Premultiplication: the water body colour is `albedo * alpha` (premultiplied) in all variants. [H]

Specular map (`s`): `spec = MS * texSpec(uv1)` (RGBA). With `a`, `texSpec = lerp(t2(uv1), t7(uv2), k)`. Without `s`, `spec = MS`. [H]
- `spec.rgb` is the specular colour, used as Fresnel F0.
- `spec.a` is a log2 shininess ("gloss"), roughly 0..10.

## 5. Normals

### 5.1 No `n`
`N = normalize(frontFacing ? viewN : -viewN)`. Flat, no perturbation. [H]

### 5.2 With `n`: derivative tangent frame (Schüler cotangent frame), computed per pixel [H]
```hlsl
Ng  = normalize(frontFacing ? viewN : -viewN);       // geometric normal
dp1 = ddx_coarse(viewPos);  dp2 = ddy_coarse(viewPos);
du  = ddx_coarse(meshUV);   dv  = ddy_coarse(meshUV);  // note: derivatives of the UNtransformed mesh UV
p1  = cross(Ng, dp1);  p2 = cross(dp2, Ng);
T   = p2*du.x + p1*dv.x;      // du.x = ddx(u), dv.x = ddy(u)
B   = p2*du.y + p1*dv.y;      // du.y = ddx(v), dv.y = ddy(v)
s   = rsqrt(max(dot(T,T), dot(B,B)));  T *= s; B *= s;
```
Normal-map decode (two layers summed, no renormalisation of the sum):
```hlsl
n1 = tex1(uv1).xy;                 // 'a': lerp(tex1(uv1).xy, tex6(uv2).xy, k)
n2 = tex4(frac(4*meshUV)).xy;      // 'a': lerp(tex4(..).xy, tex9(..).xy, k)
nxy = n1 + n2;                     // RAW .xy summed; no *2-1 decode
nz  = sqrt(max(0, 1 - dot(nxy,nxy)));
Np  = normalize( nxy.x*T - nxy.y*B + nz*Ng );   // note the minus on the B (green) term
```
- The shader does no `*2-1` decode. The `.xy` are added raw, so the textures are almost certainly signed two-channel formats (R8G8_SNORM or BC5_SNORM), or the engine bakes them that way. [M] Unresolved: see section 11.
- Only X and Y are used (reconstruct-Z). [H]
- Combined layers: base animated normal plus static 4x detail normal, summed in xy. With `a`, each member is first lerped by `k`. [H]

## 6. Reflection, refraction, Fresnel

There are three contributors: a screen-space scene copy (always present), an environment sphere map (`o` only), and Fresnel-tinted per-light specular (`l` only). There is no planar reflection texture and no depth-based absorption. [H]

### 6.1 Screen projection (shared helper)
```hlsl
float2 ScreenUV(float3 d) {        // d is a view-space position OR direction
    float2 p = d.xy / d.z;
    return float2( p.x*Proj[0][0]*0.5 + 0.5,
                  -p.y*Proj[1][1]*0.5 + 0.5 );   // uses only the Proj diagonal (cb3[4].x, cb3[5].y)
}
```
[H] about the formula. It ignores the principal-point offset, so it assumes a symmetric projection.

### 6.2 Scene lookup ("refraction")
- No `n`: `scene = t10.Sample(s0, ScreenUV(viewPos)).rgb`. This samples straight through the pixel with no distortion. [H]
- With `n`:
```hlsl
I  = viewPos;                          // unnormalised incident vector
R  = I - 2*dot(I,Np)*Np;               // reflect about the perturbed normal
R2 = R - 2*max(dot(R,Ng),0)*Ng;        // if R points out of the surface, mirror it back about the geometric normal
scene = t10.Sample(s0, ScreenUV(R2)).rgb;
```
  For a flat surface `R2 = I`, so there is no offset. The wave normal bends the lookup, so this acts as a normal-driven refraction distortion, not a reflection. [H] on the formula, [M] on the interpretation. The sample uses the surface view-space direction treated as a position. Rays that tilt past `z <= 0` would break the divide (no guard). [H]
- t10 is a screen-aligned colour image (the scene copy). Whether it is the opaque scene before water or the previous-frame colour is unknown (see section 11).

### 6.3 Fresnel tint (always computed, every variant) [H]
```hlsl
V   = normalize(viewPos);                    // eye -> surface
NV  = dot(V, N_used);                        // N_used = Np (n) or Ng (no n); signed
w   = spec.a;                                // shininess, 0..10+
s   = sat(w * 0.1);
f   = exp2(-9.28 * abs(NV));                 // Schlick-style falloff: ~0 at normal incidence, 1 at grazing
f   = min(f, 0.475*s);
f   = f * (1.041667*s) + (0.018229*s - 0.015625);   // range [-0.0156, 0.4974]
Fr  = sat( f + spec.rgb * ((0.75 + 0.25*s) - f) );   // per-channel "Fresnel colour"
```
For `s = 0`: `Fr = sat(-0.0156 + 0.7656*spec.rgb)`. For `s = 1`: `Fr = sat(f + spec.rgb*(1-f))`, with `f` in 0.0026..0.4974.

The sphere-map and the scene copy are both multiplied by `Fr`:
```hlsl
base = Fr * (scene + EnvColor * envSample);   // envSample term only with 'o'
```
So the scene copy is scaled by Fresnel, which rises toward grazing angles. The "transmitted" term brightens at the horizon. Whether this is "reflection" or "refraction" depends on what t10 holds (section 11). [H] on math, [L] on semantics.

### 6.4 Environment sphere map (`o` only) [H]
```hlsl
Rv  = V - 2*dot(V,Np)*Np;                    // view-space reflect vector (Np or Ng)
Rw  = mul(Rv, (float3x3)View);               // to WORLD space: dot(Rv, cb3[i].xyz) for i=0..2   [M on the world-space reading]
q   = Rw + float3(0,1,0);                    // sphere-map form with +Y as the axis
m2  = dot(q,q);
uvE = 0.5 + 0.5 * q.xz * rsqrt(m2);          // == standard sphere map with the axis along world +Y
dims, mips = GetDimensions(t27)
lodAuto  = 0.5*log2(max(|ddx(uvE*dims)|^2, |ddy(uvE*dims)|^2));
lodRough = (1 - sat(spec.a*0.1)) * mips;     // rougher = blurrier
lod      = max(lodRough, lodAuto);
env      = lerp( t27.SampleLevel(s0, (0.5,0.5), mips),      // ~global average colour (last mip)
                 t27.SampleLevel(s0, uvE, lod),
                 min(m2, 1) );                              // fade to the average colour as Rw -> straight down
```
- A reflection pointing straight up lands at the sphere-map centre. Pointing down (m2 -> 0) fades to the map average. [H]
- `+Y up` and the view-to-world step are inferred from the code shape, which matches the BZ2 Y-up convention. [M]

## 7. Lighting, specular, shadows (`l`, `lz`, `lo`, `lzo`)

Per-pixel setup (all `l` variants) [H]:
```hlsl
a_nv  = max(-dot(V, N_used), 0);                         // NdotV
alb   = albedo * alpha;                                  // premultiplied body colour
diffA = (1 - Fr) * g_LightAmbient;                       // ambient diffuse
specA = Fr * (scene + EnvColor*env);                     // from 6.3
F0    = spec.rgb;                                        // (1 - F0 precomputed as 1 - MS.rgb*texSpec.rgb)
alpha2 = 2.0 / (exp2(max(spec.a,0)) + 2.0);              // Blinn power p=2^w -> alpha^2 = 2/(p+2)
alphaR = sqrt(alpha2);
nl = g_LightCount (as int);                              // loop 0..nl-1 (no clamp to 16 in the shader)
shadow0 = ShadowFactor();                                // 'z' only; else 1.0. Applied ONLY to light 0
```

Per light `i` (`cb4[5*i + 0..4]`, view space), including the `n` horizon term [H]:
```hlsl
Lv   = Pos.xyz - viewPos * Pos.w;                         // Pos.w = 1 positional; 0 directional
d    = length(Lv);   L = Lv / d;
att  = max(1 - (d/Att.w)^2, 0) / (Att.x + Att.y*d + Att.z*d*d);   // Att = (c0,c1,c2,range)
cs   = dot(L, -Dir);                                      // Dir = light direction (cb4[+1])
spot = pow( sat((cs - Spot.y) / (Spot.x - Spot.y)), Spot.z );      // Spot = (cosInner, cosOuter, exponent)
rad  = att * spot * (i==0 ? shadow0 : 1);
if (HAS_N) rad *= smoothstep01( sat((dot(Ng, L) + 0.1) * 10) );    // horizon cut on the GEOMETRIC normal; n-variants only
b    = sat(dot(Np, L));                                   // NdotL (shaded normal)
rad *= b;  col = rad * Color;                             // cb4[+2]

H-terms:  NH = sat((b_raw + NdotV_signed)/|L+V|)            // b_raw = dot(Np,L); equals N.H
          VH = sat((1 - dot(L,V_eye_to_surface)) / |L - Vn|) // equals V.H
F    = F0 + (1 - F0) * pow(1 - VH, 5);                    // per-channel Schlick
Dd   = (NH*NH*(alpha2 - 1) + 1)^2;
X    = 2*a_nv*b + alphaR*(a_nv + b - 2*a_nv*b);           // Hammon mix(2ab, a+b, alpha)
spec = F * col * alpha2 / (2*Dd*X + 1e-6);                // = pi * D * V * F * col   (the 1/pi is omitted)
diffAcc += col * (1 - F);
specAcc += spec;
```
Notes: `Vn = normalize(viewPos)`, `V = -Vn`. The `+0.1 ... *10` smoothstep horizon cut appears only when `n` is present; the non-`n` loops use `col = rad*b*Color` with no horizon term. [H]

Result:
```hlsl
color = alb * (diffA + diffAcc) + (specA + specAcc);     // diffuse and spec accumulators start at diffA and specA
color += tex3(uv1) * ME;  → rgb += e.rgb * e.a;          // emissive, additive
```
Unlit (no `l`): `color = Fr*scene + albedo*alpha + e.rgb*e.a`. There is no ambient and no per-light term. [H]

### 7.1 Shadows (`z`) [H]
Cascade select by view-space z (`viewPos.z`) against `g_ShadowSplitPoints.xyzw`: cascade 1 if `z <= x`, else 2 if `z <= y`, 3 if `z <= z`, 4 if `z <= w`, else shadow = 1 (unshadowed).
```hlsl
p   = shadowCoord_c.xyz / shadowCoord_c.w;     // from VS TEXCOORD3..6
ref = min(p.z, 1);
tc  = p.xy / InvMapSize_c;                       // texel units
shadow = 0.25 * ( cmp(tc+(-1,-1)) + cmp(tc+(0,-1)) + cmp(tc+(-1,0)) + cmp(tc) ) ;  // each tap is a comparison-sampler (HW PCF) sample, offsets scaled back by InvMapSize
```
- Four hardware-PCF taps per pixel. No cascade blending and no fade at the far split. [H]
- The shadow factor multiplies only light 0 (the first in the cbuffer). Lights 1..15 are unshadowed. [H]
- The bias is the VS normal-offset (section 2). The PS applies no extra depth bias. [H]

## 8. Fog and alpha output [H]

```hlsl
dist = length(viewPos) - FogParams.y;                       // radial distance, NOT z-depth
t    = sat(dist / (FogParams.z - FogParams.y));
fog  = FogParams.x * t*t*(3 - 2*t);                         // smoothstep, scaled by FogParams.x (max amount)
out.rgb = lerp(color, FogColor.rgb * alpha, fog);           // fog target is PREMULTIPLIED by the water alpha
out.a   = alpha;                                            // = layer alpha * MD.a; no shaping, no clamp
```
- The fog target `FogColor * alpha` and the premultiplied body colour suggest the pipeline expects premultiplied blending `ONE, INV_SRC_ALPHA`. The blend state is not in the shader, so this is [L]. See section 11.
- There is no `discard` / alpha test, no depth-based edge fade, and no shore foam. [H]
- `FogColor.a`, `FogParams.w`, `TeamColor`, and `g_WaterColor3` are never read in any variant. [H]

## 9. Constant buffers (every field)

**cb0 `psfloats`** (PS, 128 B)
| Offset | Field | Used |
|---|---|---|
| 0 | `float4 g_FogColor` | rgb |
| 16 | `float4 g_FogParams` | x = max fog amount, y = start, z = end; w unused |
| 32 | `float4 g_MaterialDiffuse` | rgb and a |
| 48 | `float4 g_MaterialSpecular` | rgb = F0, a = log2 shininess |
| 64 | `float4 g_MaterialEmissive` | rgb and a |
| 80 | `float3 g_LightAmbient` | `l` variants |
| 92 | `float g_LightCount` | `l` variants (ftoi) |
| 96 | `float4 g_TeamColor` | never used |
| 112 | `float4 g_EnvironmentColor` | `o` variants |

**cb1 `psshadow`** (PS, `z` only, 48 B used)
| Offset | Field |
|---|---|
| 0 | `float4 g_ShadowSplitPoints` |
| 16 | `float2 g_InvShadowMapSize1` |
| 24 | `float2 g_InvShadowMapSize2` |
| 32 | `float2 g_InvShadowMapSize3` |
| 40 | `float2 g_InvShadowMapSize4` |

**cb2 `pswater`** (PS, 112 B)
| Offset | Field | Used |
|---|---|---|
| 0 | `float4 g_WaterColor1` | layer-1 tint (rgba) |
| 16 | `float4 g_WaterColor2` | `a` only |
| 32 | `float4 g_WaterColor3` | never used |
| 48 | `float4x2 g_WaterUVOffset1` | layer-1 UV affine |
| 80 | `float4x2 g_WaterUVOffset2` | `a` only |

**cb3 `psview`** (PS, 128 B)
| Offset | Field | Used |
|---|---|---|
| 0 | `float4x4 g_View` | `o` only (3x3 part: view -> world reflection vector) |
| 64 | `float4x4 g_Proj` | `[0][0]` and `[1][1]` only, for ScreenUV |

**cb4 `pslights`** (PS, `l` variants): `g_LightParams[16]`, 5 registers (80 B) per light, 1276 B total
| Offset in light | Field | Use |
|---|---|---|
| 0 | `float4 m_Pos` | view-space position; w = 1 positional, 0 directional |
| 16 | `float3 m_Dir` | spot axis |
| 32 | `float3 m_Color` | radiance colour |
| 48 | `float4 m_Attenuation` | xyz = constant, linear, quadratic; w = range |
| 64 | `float3 m_Spot` | x = cos inner, y = cos outer, z = exponent |

**cb0 `StdBuffer`** (VS)
| Offset | Field | Used |
|---|---|---|
| 0 | `float4x4 g_World` | clip-plane distance |
| 64 | `float4x4 g_WorldView` | view position and normal |
| 128 | `float4x4 g_WorldViewProj` | SV_POSITION |
| 192 | `float4 g_BackActive` | unused |
| 208 | `float4 g_ClipPlane` | world-space clip plane |

**cb1 `psshadow`** (VS, `z` VS only): `float4x4 g_ShadowWorldViewProj1..4` at offsets 0, 64, 128, 192.

## 10. Interstage layout [H]
VS to PS: `TEXCOORD0` = mesh uv (xy), `TEXCOORD1` = view position (xyz), `TEXCOORD2` = view normal (xyz), `TEXCOORD3..6` = shadow coords (xyzw, `z` only), `SV_ClipDistance0`, plus `SV_IsFrontFace` in the PS.

## 11. Unresolved
1. What t10 contains and when it is captured. Statically it is a screen-aligned colour image. Whether it is the opaque scene before water, a reflection copy, or a half-res copy cannot be seen from the shader.
2. The blend state. The `alb*alpha` premultiplication and the `FogColor*alpha` target suggest premultiplied blending, but the term `Fr*scene` would then double count the background unless the water pass overwrites or the pass is blended differently.
3. Normal-map texture format and range. The shader adds raw `.xy`, which implies signed storage. Needs a look at the actual DDS formats.
4. The sphere-map orientation. The view-to-world interpretation relies on the engine uploading `g_View` in the same convention as `WorldView`.
5. Light parameter conventions for directional and point lights (how `Att.w`, `Spot` and `Dir` are filled so `att` and `spot` evaluate to sensible values), and what the sun's cbuffer slot is (light 0 is the only shadowed light).
6. Whether `FogParams.x` is a density cap or an enable flag, and how `g_MaterialSpecular.a` is authored (the shader implies 0..10 log2 shininess).
7. The CPU-side generation of the UV matrices (scroll speed, rotation, scale). That lives in the exe, not the shaders.
8. Behaviour when `k` is NaN (both layer-colour alphas zero) and when the reflected ray satisfies `z <= 0`; both are unguarded in the shader.
