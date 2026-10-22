# BZCC DEFAULT (object) shader family: formula-level specification

Source: static analysis of `dx11_default_*.fxc` (1007 pixel + 31 vertex shaders, SM5 DXBC) from the BZ2R install, disassembled with `fxc /dumpbin`. Dumps are not committed; regenerate them as described in README.md. Nothing was launched, nothing under the Steam folder was modified. All constants were also confirmed bit-exact by scanning the float immediates in the DXBC (see section 7).

Confidence tags: **[H]** read directly off the instructions, **[M]** direct reading plus an inference about convention or semantics, **[L]** a guess. Where a claim depends on engine-side (CPU) data that the shader cannot show, it is marked and collected in section 10.

DXBC reminder that matters for several claims: `exp` and `log` in DXBC are base 2 (`exp2`, `log2`). So `exp r, x` means 2^x.

---

## 1. Filename grammar and which letters are actually live

`dx11_default_psh_<L>p<letters>.fxc`, `dx11_default_vsh_<L>v<letters>.fxc`. `<L>` is the vertex layout 0-7. Letters (order in names): `d t n e s l z o c x`.

Letters are independent compile flags, but many combinations compile to byte-identical code. Identical-code classes (verified by hashing the instruction stream):

| Rule | Evidence |
|---|---|
| `n` and `s` are dead unless `l` or `c` is also present. | `0pd = 0pdn = 0pdns = 0pds`; `0pde = 0pdes = 0pdne = 0pdnes`; same under `x` and `t`. [H] |
| `o` is a no-op when `c` is present. | `0pdlc == 0pdloc`, `0pdlzc == 0pdlzoc` and ~80 more pairs. [H] |
| `o` alone is always paired with `l` (no `0pdo`, no `0pdc`-style `o`-only unlit file). | file listing [H] |
| `z` always comes with `l`. No `z` without `l`. | file listing [H] |
| `l`, `c`, `o`, `n`, `s`, `z` are dead on layouts 1, 4, 5, 6, 7 (those layouts have none of those variants, or all are identical). Layout 3 compiles `l/c/o/n/s` variants but they are byte-identical to the plain screen-space shader (3pd == 3pdl == 3pdlc == 3pdn ...). | hash classes [H] |
| `t`, `e`, `x` are live on layouts 0, 1, 2, 3, 4. Layout 6 ignores `t`, `n`, `e`, `s` (all `6pd*` identical). Layouts 5 and 7 ignore every letter (all `5pd*` == `5p`, all `7pd*` == `7p`, including `x`). | [H] |
| Letters `d`: absent means "no t0 sample, albedo = material diffuse constant". | `0pl`, `0pc` etc. [H] |

Practical consequence: the live feature combinations are far fewer than 1007. There are 491 distinct pixel programs.

---

## 2. Constant buffers and resources

### 2.1 Pixel stage

`cb0 psfloats` (register / byte offset):

| reg | off | field | used as |
|---|---|---|---|
| cb0[0] | 0 | `g_FogColor` (rgb used, a unused) | fog target |
| cb0[1] | 16 | `g_FogParams` x=density, y=start, z=end | fog |
| cb0[2] | 32 | `g_MaterialDiffuse` rgba | albedo tint, alpha scale |
| cb0[3] | 48 | `g_MaterialSpecular` rgb = F0 scale, **w = log2(specular power)** | spec colour, shininess |
| cb0[4] | 64 | `g_MaterialEmissive` | **never read in any of the 1007 shaders** [H] |
| cb0[5] | 80 | `g_LightAmbient` rgb | ambient |
| cb0[5].w | 92 | `g_LightCount` (float, `ftoi`'d) | light loop bound |
| cb0[6] | 96 | `g_TeamColor` rgb, w = team strength | team lerp |
| cb0[7] | 112 | `g_EnvironmentColor` rgb = env tint / chrome colour, **w = chrome blend factor** | `o`/`c` paths |

`cb1 psshadow` (pixel view of slot b1; 48 bytes):

| reg | field |
|---|---|
| cb1[0] | `g_ShadowSplitPoints` xyzw (view-space z of the far edge of cascade 1..4) |
| cb1[1].xy / .zw | `g_InvShadowMapSize1` / `2` |
| cb1[2].xy / .zw | `g_InvShadowMapSize3` / `4` |

`cb3 psview`: `g_View` (float4x4, offset 0) and `g_Proj` (offset 64, never used by this family). Only the 3x3 rotation of `g_View` is used (environment reflection).

`cb4 pslights`: `LightParams g_LightParams[16]`, array stride 80 bytes (5 registers), total 1276 bytes (the last element's `m_Spot` is a float3). Per light `i`, `base = 5*i`:

| reg | field | meaning |
|---|---|---|
| cb4[base+0] | `m_Pos` xyzw | xyz = view-space position (point/spot) or direction toward the light (directional); **w = 1 for positional, 0 for directional** |
| cb4[base+1] | `m_Dir` xyz | spot axis, direction the light points (view space) |
| cb4[base+2] | `m_Color` xyz | radiance colour (intensity already baked in by the CPU) |
| cb4[base+3] | `m_Attenuation` | xyz = (c0, c1, c2) constant/linear/quadratic; **w = range** |
| cb4[base+4] | `m_Spot` xyz | x = cos(inner), y = cos(outer), z = falloff exponent |

All light vectors are compared against **view-space** position/normals, so the CPU supplies them in view space. [H for the math, M for the "inner/outer" naming]

Textures (all `Texture2D<float4>` unless noted), sampler `s0` for everything except shadows:

| slot | letter | content |
|---|---|---|
| t0 | d | diffuse/albedo RGBA (layout 6: `Texture3D`) |
| t1 | t | team mask: rgb = team-colour tint, **a = mask** |
| t2 | e | emissive: rgb = colour, **a = intensity multiplier** (output adds rgb*a) |
| t3 | n | normal map, only .xy read (BC5-style) |
| t4 | s | specular: rgb = F0 multiplier, **a = shininess multiplier** |
| t27 | o, c | environment sphere map (2D, mipmapped) |
| t28..t31 | z | shadow cascades 1..4, sampled through comparison sampler `s7` |

`s0` is `mode_default`, `s7` is `sampler_c`. Filter, address mode, comparison function and biases live in the CPU sampler state and cannot be read here. [H that they are not in the shader]

### 2.2 Vertex stage

`cb0 StdBuffer` (column-major: each register holds a matrix column, so `M*v = v.x*reg[0] + v.y*reg[1] + v.z*reg[2] + reg[3]`):

| offset | field |
|---|---|
| 0 | `g_World` (cb0[0..3]) |
| 64 | `g_WorldView` (cb0[4..7]) |
| 128 | `g_WorldViewProj` (cb0[8..11]) |
| 192 | `g_BackActive` (cb0[12]) |
| 208 | `g_ClipPlane` (cb0[13]) |

Vertex `cb1` ("psshadow" by name, but a different layout than the pixel stage): `g_ShadowWorldViewProj1..4`, four float4x4, 256 bytes, same column-major convention. Maps **object-space** positions directly to each cascade's clip space. [H]

---

## 3. Vertex shaders (31 files)

Common: `clipdist = dot(g_ClipPlane, World * float4(pos,1))` for layouts 0, 1, 2, 6, 7, so the clip plane is a **world-space** plane (water reflection/refraction clipping). Layouts 3/4/5 write 0. [H]

Layouts 0 and 2 (3D, with normal) come in 5 classes by suffix; suffix letters mirror the PS letters:

| VS | extra outputs vs the base |
|---|---|
| `0v` | `SV_POSITION = WVP*pos`; `TEXCOORD0 = uv`; `TEXCOORD1 = (WorldView*pos).xyz` (view-space position). No normal input read. |
| `0vc`, `0vl`, `0vlc`, `0vlo`, `0vloc` (all identical code) | adds `TEXCOORD2 = mat3(WorldView) * normal` (view-space normal, **not normalized**; the PS normalizes it). |
| `0vlz`, `0vlzc`, `0vlzo`, `0vlzoc` (identical) | adds four shadow coords `TEXCOORD3..6 = ShadowWVP_k * float4(pObj, 1)` where `pObj = pos + normal * (0.2 + 0.001*max(viewZ, 0))`, with `viewZ = (WorldView*pos).z`. See section 5.3. |

Layout 2 is the same set, but adds a vertex colour (see below) between `SV_POSITION` and `TEXCOORD0` in the output order: outputs are `COLOR0, TEXCOORD0 (uv), TEXCOORD1 (view pos), TEXCOORD2 (view normal), TEXCOORD3..6 (shadow), CLIPDIST`. [H]

Other layouts:

| layout | inputs | outputs | notes |
|---|---|---|---|
| 1 | pos3, color4, uv2 | SV_POS, color (passed through **unmodified**), uv, view pos | Unlit, vertex colour. |
| 2 | pos3, normal3, color4, uv2 | as above | **Colour is gamma-converted: `rgb = pow(max(c,0), 2.2)`**, `a` passed through. [H] |
| 3 | pos4, color4, color1(unused), uv2 | SV_POS, color, uv | Pretransformed (screen pixel) geometry. **Colour gamma 2.2** as layout 2. |
| 4 | pos4, color4, uv2 | same as 3 | Same, no second colour. |
| 5 | pos4, color4 | SV_POS, color | Untextured screen-space. Gamma 2.2. |
| 6 | pos3, color4, uv3 | SV_POS, color, uv3 | World geometry with a 3D texture coordinate. Gamma 2.2. No view position output, so no fog. |
| 7 | pos3, color4 | SV_POS, color, view pos (as TEXCOORD1) | World untextured; colour **passthrough (no gamma)**. Has fog. |

Screen-space transform (layouts 3, 4, 5): with `B = g_BackActive` = (offsetX, offsetY, 1/width, 1/height):
```
ndc.x =  2*(pos.x - B.x)*B.z - 1
ndc.y = -(2*(pos.y - B.y)*B.w - 1)      // 1 - 2*dy/height
ndc.zw = pos.zw                          // passed through
```
[H for the algebra; M for B's meaning, inferred from the formula.]

Matrix convention: `WorldView`/`WVP` are used with the register-as-column layout, so the engine uploads standard column-vector matrices. For the pixel stage `g_View` in `cb3`, the shader computes `float3(dot(R, cb3[0].xyz), dot(R, cb3[1].xyz), dot(R, cb3[2].xyz))` which is `transpose(mat3(View)) * R`. Provided cb3 is stored the same way as the vertex matrices, that is the **inverse rotation: view space to world space**. [M]

---

## 4. Pixel input interface per layout

Lit layouts: interpolants (after `SV_POSITION`):

| | layout 0 | layout 2 |
|---|---|---|
| vertex colour | not present | v1 |
| uv | v1.xy | v2.xy |
| view pos P | v2.xyz | v3.xyz |
| view normal | v3.xyz | v4.xyz |
| shadow clip 1..4 | v4..v7 (xyzw) | v5..v8 |
| front face | next-to-last SGV | ditto |

Layout 2 differs from layout 0 only in the albedo (section 6.1): `albedo = saturate(vcolor) * matDiffuse * tex0`. [H]

---

## 5. Lit pipeline: the maximal path decoded

Reference shader: `0pdtneslzo` / `0pdtneslzoc`. Everything else is a subset (section 8).

### 5.1 Albedo

```
tex   = t0.Sample(uv)                         // d
alb   = tex * matDiffuse                      // rgba (no `d`: alb = matDiffuse)
// layouts 1,2,3,4,5,6,7: alb *= saturate(vertexColor)   (applied BEFORE the team lerp)
// team (t):
mask  = t1.a * teamColor.w
alb.rgb = lerp(alb.rgb, teamColor.rgb * t1.rgb, mask)      // alpha untouched
// chrome (c) only:
alb.rgb *= (1 - envColor.w)
```
[H] Output alpha for lit shaders is `alb.a` (= tex.a * matDiffuse.a). Material emissive constant is never used.

### 5.2 Normal and view vector

```
N_geo = normalize(frontFace ? vNormalView : -vNormalView)      // two-sided handling
P     = viewPos;  I = normalize(P)                             // I = eye -> point;  V = -I
```
Two-sided: `movc(N, SV_IsFrontFace, +n, -n)` then normalize. Present in every lit and env shader (the unlit shaders read no normal). It is applied to the interpolated vertex normal **before** tangent-frame construction and before everything else. [H]

Normal map (`n`; live only with `l` or `c`):
```
dpx = ddx_coarse(P);  dpy = ddy_coarse(P);
duv_x = ddx_coarse(uv);  duv_y = ddy_coarse(uv);          // (dudx,dvdx), (dudy,dvdy)
dp1perp = cross(N_geo, dpx);   dp2perp = cross(dpy, N_geo);
T = dp2perp*duv_x.x + dp1perp*duv_y.x;
B = dp2perp*duv_x.y + dp1perp*duv_y.y;
invmax = rsqrt(max(dot(T,T), dot(B,B)));  T *= invmax;  B *= invmax;   // T,B share one scale; not orthonormalised
xy = t3.Sample(uv).xy;                                    // used RAW, no *2-1  (=> SNORM BC5, or loader remaps)
nx = xy.x;  ny = -xy.y;                                   // green flipped
(chrome only) nx *= (1 - envColor.w);  ny *= (1 - envColor.w);
nz = sqrt(max(1 - nx*nx - ny*ny, 0));
N  = normalize(nx*T + ny*B + nz*N_geo);
```
This is the Schueler "cotangent frame without precomputed tangents", built in view space with coarse derivatives. Because x,y are consumed without a 2x-1 remap, the texture is a signed format (BC5_SNORM) or the loader supplies signed data. [H on the math; M on the texture format]

Without `n` (or in layouts without the letter): `N = N_geo`, and the geometric-normal terminator term below is absent.

### 5.3 Shadows (`z`)

Applies **to light index 0 only** (the first entry of the light array). All other lights get shadow = 1. Ambient and environment are never shadowed. [H]

Cascade selection uses view-space depth `z = viewPos.z`:
```
if      (z <= split.x) { c = 0; coord = vShadow0; tex = t28; inv = invSize1 }
else if (z <= split.y) { c = 1; coord = vShadow1; tex = t29; inv = invSize2 }
else if (z <= split.z) { c = 2; coord = vShadow2; tex = t30; inv = invSize3 }
else if (z <= split.w) { c = 3; coord = vShadow3; tex = t31; inv = invSize4 }
else                    shadow = 1.0           // hard cutoff: no fade band, no cascade blending
```
(`ge cb1[0].x, v.z`: split >= z.) [H]

Per cascade:
```
p     = coord.xyz / coord.w;          // projective divide in PS, xy is used directly as UV (no *0.5+0.5)
ref   = min(p.z, 1.0);                // the ONLY depth adjustment in the PS: no constant/slope bias
uvT   = p.xy / inv;                   // texel space
shadow = 0.25 * ( cmp(tex, (uvT + (-1,-1)) * inv, ref)
                + cmp(tex, (uvT + ( 0,-1)) * inv, ref)
                + cmp(tex, (uvT + (-1, 0)) * inv, ref)
                + cmp(tex, (uvT + ( 0, 0)) * inv, ref) );
```
`cmp` is `SampleCmpLevelZero` with sampler `s7` (hardware 2x2 bilinear PCF per tap). So four hardware-PCF taps at integer-texel offsets {(-1,-1),(0,-1),(-1,0),(0,0)}, equal weight 0.25. The kernel footprint is therefore centred about half a texel toward (-u,-v); effective support about 3x3 texels with a tent-like weighting. Comparison direction (almost certainly "lit if ref <= stored depth") is a CPU sampler setting. [H on the taps/weights, L on the comparison function]

Bias: all bias is in the vertex shader as a **normal offset in object space**: `pObj = pos + normalObj * (0.2 + 0.001*max(viewZ,0))`, i.e. 0.2 units at the camera growing by 1 mm per unit of view depth (so 1.2 at 1000 units). `normalObj` is the raw, unnormalised vertex normal, so the offset scales with the normal length and is in object-space units (not world). The shadow matrices `ShadowWVP_k` already include the world matrix. [H]

### 5.4 Light loop

```
count = (int)g_LightCount          // clamp is the CPU's job (16 max)
diffAcc = ambient (or (1-envBRDF)*ambient with o/c)
specAcc = 0      (or env*envBRDF with o/c)
for i in 0..count-1:
    Lv   = Light.Pos.xyz - P * Light.Pos.w          // w=1: position - P;  w=0: just Pos.xyz (directional)
    d2   = dot(Lv,Lv);  d = sqrt(d2);  L = Lv / d
    rf   = max(1 - (d/Light.Atten.w)^2, 0)          // range window
    att  = rf / (Atten.x + Atten.y*d + Atten.z*d2)  // constant/linear/quadratic
    t    = saturate((dot(L, -Light.Dir) - Spot.y) / (Spot.x - Spot.y))
    spot = pow(t, Spot.z)                           // exp2(Spot.z * log2 t)
    stepG = smoothstep01(saturate((dot(N_geo, L) + 0.1) * 10))     // ONLY when n is live (see 5.2)
    shad  = (i == 0) ? shadow : 1
    NL    = saturate(dot(N, L))
    E     = Light.Color * att * spot * shad * stepG * NL
    ... BRDF (5.5)
```
`smoothstep01(x) = x*x*(3-2x)`.

* Directional lights are positional ones with `Pos.w = 0`: the direction vector is `Pos.xyz`, the code still divides by its length and computes `d = |Pos.xyz|`. For a unit direction `d = 1`, so the range window and polynomial attenuation become constants. Encoding of the other fields for directional lights is a CPU choice (section 9). [H on the math]
* There is no separate "type" field; spot vs point vs directional is entirely data. A point light must have `Spot` that makes `pow(t, z)` = 1 (for example z=0, or inner<=outer cosines producing t=1). Note `pow(0, 0)` via `exp2(0*log2(0))` is `exp2(0 * -inf) = NaN`; the CPU must avoid `t == 0` with `z == 0`. [M]
* The `stepG` term (the "geometric terminator", `(Ng.L + 0.1) * 10` saturated and smoothstepped) exists only in shaders with `n`; its job is to stop the normal-mapped N from lighting faces whose geometric normal faces away. [H]
* Attenuation is not divided by pi, `E` has no 1/pi anywhere. [H]

### 5.5 BRDF per light

Material terms (computed once):
```
specTex = s ? t4.Sample(uv) : 1.0
F0rgb   = matSpec.rgb * specTex.rgb
sExp    = matSpec.w * specTex.a                 // "log2 of power"
// chrome (c): F0rgb = lerp(F0rgb, envColor.rgb, envColor.w);  sExp = lerp(sExp, 10, envColor.w)
a2      = 2 / (max(exp2(sExp), 0) + 2)          // alpha^2 = 2/(power+2)
alpha   = sqrt(a2)
NV      = max(-dot(N, I), 0)                    // = max(dot(N,V),0)
```
So `matSpec.w` is **log2 of the Blinn-Phong power**: `power = 2^w`, `a2 = 2/(power+2)`. A stored value of 10 means power 1024; the chrome path fixes `sExp` to 10 when `envColor.w = 1`. [H]

Per light:
```
LdotI = dot(L, I)                               // = -dot(L,V)
invH  = rsqrt(2 - 2*LdotI)                      // 1/|L+V|
NL_u  = dot(N, L)                               // unsaturated here
NH    = saturate(invH * (NL_u + NV'))           // NV' = -dot(N, I), NOT clamped (differs from NV above)
VH    = saturate(invH * (1 - LdotI))            // = |L+V|/2 = cos(V,H)
F     = F0rgb + (1 - F0rgb) * (1 - VH)^5
den   = (NH*NH*(a2-1) + 1)^2                    // GGX denominator (D = a2/den, pi dropped)
vis   = lerp(2*NV*NL, NV + NL, alpha)           // Hammon 2017 approximate visibility denominator
spec  = F * E * a2 / (2 * den * vis + 1e-6)     // E already contains NL
diff  = E * (1 - F)
specAcc += spec;  diffAcc += diff
```
Equivalent: `D = a2/(den)`, `Vis = 0.5/vis`, `spec = F*D*Vis*E` with pi omitted. [H]

Final lit colour (before emissive/fog):
```
rgb = alb.rgb * diffAcc + specAcc
```
Diffuse is *not* divided by pi, and it is multiplied by `(1 - F)` (not by `1 - metalness`). Ambient enters `diffAcc` directly and is multiplied by albedo like any light. [H]

### 5.6 Environment (`o`, `c`)

Both letters add the t27 sphere-map term; `c` additionally applies the chrome rules (albedo *= 1-envA, F0/power lerped to envColor, normal-map strength scaled by 1-envA, emissive scaled by 1-envA). `o` is plain.

```
R_v   = I - 2*dot(N, I)*N                          // reflect, view space, uses the shading normal N
R_w   = transpose(mat3(g_View)) * R_v              // view -> world        [M: depends on cb3 packing]
s     = R_w + (0, 1, 0)
uv    = 0.5 + 0.5 * (s.x, s.z) / |s|               // sphere map around the world +Y axis
```
Geometry: `R_w = +Y` (up) maps to the texture centre (0.5,0.5); horizon reflections (R_y=0) map to radius 0.5/sqrt(2) = 0.354; straight down is the singular rim. `s.y` only enters through `|s|`. [H on the formula, M on "world space"]

Gloss, BRDF and LOD:
```
g       = saturate(sExp * 0.1)                     // sExp as defined in 5.5 (so power 2^10 => g = 1)
dims    = t27.mip0 size, M = t27 mip count         // via resinfo
gradLod = 0.5 * log2( max( |ddx(uv*dims)|^2, |ddy(uv*dims)|^2 ) )     // coarse derivs
lod     = max( (1 - g) * M , gradLod )             // note M, not M-1; clamped by the sampler to the last mip
env     = lerp( t27.SampleLevel((0.5,0.5), M).rgb,        // = the 1x1 average colour
                t27.SampleLevel(uv, lod).rgb,
                min(dot(s,s), 1) ) * envColor.rgb         // downward fade
```
The downward fade: `dot(s,s) = 2 + 2*R_w.y`, so the weight is 1 for `R_w.y >= -0.5` and falls linearly to 0 at straight down, blending toward the map's average colour. [H]

EnvBRDF (a mobile-style analytic fit, indexed by gloss and `|N.I|`):
```
c   = |dot(N, I)|
A   = (25/24)*g * min( exp2(-9.28*c), 0.475 ) + (7/384)*g - 1/64
B   = (0.75 + 0.25*g) - A
envBRDF = saturate( F0rgb * B + A )                // per channel
```
Exact float constants (DXBC hex): 1.041667 = 0x3F855555 = 25/24, 0.475 = 0x3EF33333, 0.018229 = 0x3C955555 = 7/384, 0.25 = 0x3E800000, -0.015625 = 0xBC800000 = -1/64, 0.75 = 0x3F400000, -9.28 = 0xC1147AE1. [H]

Combination (lit shaders):
```
diffAcc = (1 - envBRDF) * ambient          // initial value, per channel  ("ambient is multiplied by 1-EnvBRDF" in o/c paths)
specAcc = env * envBRDF                    // initial value (in addition to the per-light specular)
```
So with `o` or `c` the ambient term is energy-reduced by the environment Fresnel, and the environment specular uses the same F0/gloss as the direct specular. Shaders with only `l` have a plain `diffAcc = ambient`, `specAcc = 0`. `g_EnvironmentColor.rgb` tints the sampled environment (and sets chrome F0); `.w` is the chrome blend. The environment contribution is **not** shadowed, **not** attenuated by lights, and not multiplied by albedo. [H]

Chrome unlit (`c` without `l`, e.g. `0pc`, `0pdc`, `0pdec`): no ambient and no lights:
```
rgb = env * envBRDF + alb.rgb * (1 - envColor.w)        // alb = matDiffuse * tex (+team), alpha = alb.a (matDiffuse.a when no d)
```
with F0 = lerp(matSpec*specTex, envColor.rgb, envColor.w), sExp = lerp(.., 10, envColor.w). `0pc` (no `d`) uses the same with `matDiffuse.a` as alpha. [H]

### 5.7 Emissive (`e`), cutout (`x`), fog

Emissive, added after lighting and before fog:
```
e = t2.Sample(uv);   e.rgb *= (chrome ? 1 - envColor.w : 1);   rgb += e.rgb * e.a
```
(alpha channel scales the rgb; output alpha is untouched.) In `x` shaders the emissive add happens after the discard test. In `l`-less shaders (`0pde`) the emissive is simply added to the albedo; there is no ambient. [H]

Cutout (`x`):
```
a_full = matDiffuse.a * tex.a                       // layouts 1-7 additionally * vertex alpha
width  = max( |ddx_coarse(a_full)| + |ddy_coarse(a_full)|, 1e-4 )
cov    = (a_full - 0.5) / width + 0.5
dims   = t0.mip0 size;  uvp = uv * dims
lod    = max( 0.5*log2( max(|ddx(uvp)|^2, |ddy(uvp)|^2) ), 0 )
cov   *= 1 + 0.25 * lod                              // widens coverage with minification
if (cov < 0.5) discard;
outAlpha = cov                                       // NOT saturated here; the render target clamps
```
The output alpha of an `x` shader is the remapped `cov`, not the original alpha. [H] Using `coarse` derivatives, so the width estimate is per 2x2 quad. [H]

Fog (every shader that has a view position, i.e. all except layouts 3, 4, 5, 6):
```
d  = length(P)                                    // radial, view space
f  = smoothstep01( saturate((d - fogStart) / (fogEnd - fogStart)) ) * fogDensity
rgb = lerp(rgb, fogColor.rgb, f)                  // alpha untouched
```
FogParams = (density, start, end). Fog colour alpha is unused. In `x` shaders fog is applied after the discard test. [H]

---

## 6. Unlit pipeline (no `l`, no `c`)

```
alb = tex(d) * matDiffuse * saturate(vertexColor)(layouts 1-7) -> team lerp (t)
rgb = alb.rgb + (e ? t2.rgb*t2.a : 0)
-> optional cutout (x) -> fog (layouts 0,1,2,7)
alpha = alb.a  (or cutout coverage)
```
There is no ambient and no lighting: unlit "d" shaders are full-bright. [H]

Layout 3/4: same with `uv` at v2 and no fog. Layout 5: `rgb,a = saturate(vcol) * matDiffuse` (no texture). Layout 6: `Texture3D` sample * saturate(vcol) * matDiffuse, no fog. Layout 7: `saturate(vcol)*matDiffuse` with fog (no texture). [H]

---

## 7. Per-letter feature table (layout 0 unless noted)

| Letter | Adds | Needs | Notes |
|---|---|---|---|
| `d` | `t0` albedo sample multiplied by `matDiffuse` | | Without `d`: albedo = `matDiffuse`, alpha = `matDiffuse.a`. |
| `t` | `t1` team mask lerp: `lerp(alb, team.rgb*t1.rgb, t1.a*team.w)` | | After vertex-colour multiply, before chrome factor. |
| `n` | `t3` normal map, derivative TBN, geometric terminator `smoothstep((Ng.L+0.1)*10)` per light | `l` or `c` | Dead otherwise. With `c`, xy is scaled by `1-envColor.w`. |
| `e` | `t2` emissive `rgb*a` added before fog | | `matEmissive` never used. Scaled by `1-envA` in `c`. |
| `s` | `t4` multiplies F0 (rgb) and shininess exponent (a) | `l` or `c` | Dead otherwise. |
| `l` | `pslights` loop, ambient, GGX/Hammon/Schlick, `1-F` diffuse | | Reads `LightCount` and `LightAmbient`. |
| `z` | normal-offset shadow coords in VS; 4-cascade 4-tap PCF on **light 0 only** | `l` | Needs VS `*z` variant. |
| `o` | environment sphere map specular; ambient *= `1-envBRDF` | `l` | `envColor.w` unused. |
| `c` | `o` plus chrome: albedo *= `1-envA`; F0 = lerp(F0, envRGB, envA); power exponent = lerp(sExp, 10, envA); normal xy *= `1-envA`; emissive *= `1-envA` | | Also exists without `l`: unlit chrome (section 5.6). `co` == `c`. |
| `x` | derivative-sharpened alpha test, output alpha = coverage | | Section 5.7. |

Layout availability: layouts 0 and 2 have the full set (330 pixel shaders each); layout 3 carries the same names but, as shown, the lit/normal letters collapse to the unlit screen-space shaders; layouts 1 and 4 have 33 names each (collapsing to `d`/`t`/`e`/`x`); layouts 5 and 7 have 33 names each that all equal `5p` and `7p` respectively; layout 6 has 17 names that all equal the same textured 3D shader.

Hex check of constants: scanned DXBC float immediates in `0pc` (read-only), matching the values above to the bit.

---

## 8. Layout-by-layout summary

| layout | VS | PS live letters | lighting | fog | notes |
|---|---|---|---|---|---|
| 0 | pos,normal,uv | d t n e s l z o c x | yes | yes | standard world geometry |
| 1 | pos,color,uv | d t e x | no | yes | colour passthrough |
| 2 | pos,normal,color,uv | d t n e s l z o c x | yes | yes | colour gamma 2.2 then saturate in PS, multiplies albedo before team lerp |
| 3 | pretransformed pos4, color, uv | d t e x | no | no | screen pixel to NDC in VS |
| 4 | pretransformed pos4, color, uv | d t e x | no | no | |
| 5 | pretransformed pos4, color | none | no | no | |
| 6 | pos,color,uvw | d (3D tex) | no | no | `Texture3D` |
| 7 | pos,color | none | no | yes | untextured world colour, no gamma; fog |

(Layouts 1 and 4 have `d t e x` live, `n`/`s` dead. Layouts 5 and 7 have no live letters.)

---

## 9. Reference implementation (compact pseudo-HLSL)

```hlsl
float3 shadeLit(...) {
  float4 alb = d ? tex0.Sample(uv) * matDiffuse : matDiffuse;
  if (hasVertexColor) alb *= saturate(vcol);
  if (t) alb.rgb = lerp(alb.rgb, teamColor.rgb * tex1.rgb, tex1.a * teamColor.w);
  float chromeK = c ? (1 - envColor.w) : 1;           // c only
  alb.rgb *= chromeK;

  float3 Ng = normalize(front ? nView : -nView);
  float3 N  = Ng;  float3 I = normalize(P);
  if (n) N = cotangentFrameNormal(Ng, P, uv, chromeK);   // 5.2
  float4 sp  = s ? tex4.Sample(uv) : 1;
  float3 F0  = matSpec.rgb * sp.rgb;  float sE = matSpec.w * sp.a;
  if (c) { F0 = lerp(F0, envColor.rgb, envColor.w); sE = lerp(sE, 10, envColor.w); }
  float a2 = 2.0 / (max(exp2(sE), 0) + 2.0), alpha = sqrt(a2);
  float NdI = dot(N, I), NV = max(-NdI, 0);

  float3 diffAcc = ambient, specAcc = 0;
  if (o || c) { /* section 5.6 */ float3 eb = envBRDF(F0, saturate(0.1*sE), abs(NdI));
                diffAcc = (1 - eb) * ambient;  specAcc = envSample(N, I, sE) * eb; }

  for (int i = 0; i < (int)lightCount; i++) { /* sections 5.4, 5.5, shadow only for i == 0 */ }

  float3 rgb = alb.rgb * diffAcc + specAcc;
  if (e) rgb += tex2.rgb * tex2.a * chromeK;
  rgb = lerp(rgb, fogColor.rgb, fogFactor(length(P)));
  return float4(rgb, alb.a);                           // x: alpha = remapped coverage, discard if < 0.5
}
```

---

## 10. CPU-side hints and unresolved items

Hints about how the engine feeds these constants:

* `matSpec.w` goes through `exp2`, so the CPU stores **log2(specular power)** (for example `log2(1024) = 10`), and a spec texture alpha scales that exponent; the chrome path forces 10. (This corrects the working assumption of `ln(power)`; DXBC `exp` is base 2.) [H]
* `g_LightAmbient.w` carries the integer light count as a float. [H]
* `g_EnvironmentColor.w` is the chrome/biometal blend factor, selected per material by the engine (the `c` pixel variant is chosen when it is non-zero). `g_EnvironmentColor.rgb` is both env tint and chrome F0. [M]
* Light vectors, spot axis, and positions are in **view space**; colours include intensity; `Atten.w` is a hard range. [H]
* Layout-2/3/4/5/6 vertex colours are gamma-2.2 converted in the VS, so the CPU stores them as display-referred 8-bit colours. [H]
* The shadow matrices include the world transform; the normal-offset bias is object-space, so the CPU should keep object-scale uniform. [M]

Not resolvable from the shaders (engine state, not DXBC):

1. Directional-light encoding of `Atten` and `Spot` (almost certainly `Pos.w = 0`, `Atten = (1,0,0,huge)`, `Spot` = a pass-through). Only `Pos.w` is forced by the code.
2. Point-light `Spot` defaults and the `pow(0,0)` hazard.
3. Sampler filter and address modes (`s0`, `s7`) and the shadow comparison function; depth format and orientation (y flip is baked into the shadow matrices, since the PS uses `p.xy` directly).
4. Normal-map texture format (signed BC5 assumed).
5. Whether `g_View` in `cb3` is uploaded in the same column-major layout as the VS matrices (this determines whether the reflection is in world space; the up-axis `(0,1,0)` strongly suggests it is).
6. Blend state for `x` shaders (alpha-to-coverage vs plain alpha) and any fixed-function alpha-test; the shader outputs the remapped coverage in alpha.
7. Which materials are assigned `c`/`o` (not exposed by any `.material` key).
