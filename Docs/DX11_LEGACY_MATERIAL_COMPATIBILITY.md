# DX11 legacy material compatibility proposal

Date: 2026-09-16

Status: design / implementation plan

Branch: `agent/dx11-fixedfunc-fallback`

## Problem statement

Battlezone 98 Redux can load legacy/custom Ogre material content that was authored for the D3D9-era fixed pipeline or references only Shader Model 2/3 programs. Under D3D9 that content is usually still renderable because the renderer either accepts the old programs or falls back to fixed-function state. D3D11 has no fixed-function fallback and rejects legacy shader profiles.

The failure is confirmed by the 2026-09-16 ISDF Chronicles run:

- `BZLogger.txt` contains 1,300 copies of:
  - `Attempted to render to a D3D11 device without both vertex and fragment shaders - there is no fixed pipeline in d3d11`
- `BZOgreLogfile.log` contains 264 `Invalid target for D3D11 shader` messages for `vs_3_0`, `ps_3_0`, and some older targets.
- Examples include stock/legacy families such as `Base*`, `Effect_*`, `Sky_*`, `Textured_*`, `Untextured_*`, `UI_*`, terrain programs, and simple one-texture programs.
- Some mod materials are true fixed-function definitions with no `vertex_program_ref` / `fragment_program_ref` at all.
- Other mod materials are programmable but reference only legacy program families such as `Effect_vertex/fragment`.

The user-visible result is a black scene plus exception spam even though the same content works under D3D9.

The goal of this work is **not** to require mod authors or users to edit every `.material` file. OpenShim should provide a compatibility layer so old content can render under DX11 automatically where practical.

## Existing OpenShim seam

`src/patches/ogre_render_profile.cpp` already owns the renderer-profile material scheme listener and the `EnhancedSchemeFallback` compatibility path.

The current resolver can inspect material techniques through a deliberately small reverse-resolved Ogre ABI surface (`getNumTechniques`, `getTechnique`, scheme name, LOD, `isSupported`). Today it only returns an already-supported technique. If no supported technique exists, it returns `nullptr` and Ogre can eventually reach the D3D11 render path without both shaders bound.

That is the natural first seam for a compatibility resolver, but implementation should keep ABI growth narrow and avoid per-draw mutation.

## Compatibility goals

1. No manual edits to third-party mod `.material`, texture, or shader files for common legacy cases.
2. Preserve the original material's render state as closely as possible:
   - scene blending
   - depth test/write
   - culling
   - alpha rejection
   - diffuse/ambient/specular/emissive colours
   - texture units
   - addressing/filtering
   - texture transforms and animation (`scroll_anim`, rotation, scale)
   - fog participation
3. Leave valid native DX11 techniques untouched.
4. Leave DX9 behaviour untouched.
5. Cache compatibility techniques/materials at load/first-use time; do not synthesize them per draw.
6. Unknown custom shaders must fail safely and diagnostically rather than producing hundreds of exceptions per frame.
7. Avoid silently replacing a genuinely custom programmable effect with a flat texture unless an explicit aggressive compatibility option is enabled.

## Recommended compatibility ladder

Use an ordered resolver. Each level is progressively less exact.

### Level 0 - existing native supported technique

Keep the current behaviour first:

1. exact requested scheme + requested LOD, supported
2. exact scheme + degraded/compatible LOD, supported
3. compatible base/default scheme, supported

If this succeeds, return it unchanged.

### Level 1 - known legacy shader-family remap

Some mod materials are not fixed-function; they reference BZR/legacy program names whose only available implementation is SM2/SM3.

Examples from the failing run include:

- `Effect_vertexHLSL` / `Effect_fragmentHLSL`
- `Textured_vertexHLSL` / `Textured_fragmentHLSL`
- `Untextured_vertexHLSL` / `Untextured_fragmentHLSL`
- `Sky_vertexHLSL` / `Sky_fragmentHLSL`
- `simple_one_tex*`
- selected UI/simple utility shader families

For known families, clone the source technique/pass state and replace only the incompatible program references with OpenShim-owned SM4 equivalents.

Example mapping concept:

```text
Effect_vertexHLSL      -> OSE_Compat_Effect_vertex
Effect_fragmentHLSL    -> OSE_Compat_Effect_fragment
Textured_vertexHLSL    -> OSE_Compat_Textured_vertex
Textured_fragmentHLSL  -> OSE_Compat_Textured_fragment
```

This should be table-driven and case-insensitive. Do not rewrite files on disk.

The mapping table should live in a pure/testable engine module rather than being scattered through the Ogre hook.

### Level 2 - true fixed-function emulation

If a pass has no usable VS/PS and its semantics are fixed-function, generate a DX11-compatible pass using OpenShim-owned shaders.

Suggested resources:

```text
resources/renderer/enhanced/openshim_dx11_fixedfunc.program
resources/renderer/enhanced/openshim_dx11_fixedfunc-sm4.hlsl
```

Suggested logical programs:

```text
OSE_FixedFunc_Textured_vertex
OSE_FixedFunc_Textured_fragment
OSE_FixedFunc_Untextured_vertex
OSE_FixedFunc_Untextured_fragment
```

Ship normal SM4 targets and feature-level-9.x compatible targets if required by the supported DX11 floor.

The first implementation should cover the overwhelmingly common legacy path:

```text
world/view/projection transform
vertex diffuse colour
material diffuse/ambient contribution
texture unit 0
texture matrix / UV animation
fog
alpha
```

The shader should consume Ogre automatic constants rather than reaching into Battlezone scene state directly.

Important: copying a `TextureUnitState` is not enough by itself once a programmable fragment shader is attached. Texture-stage combine operations that were previously executed by the fixed pipeline must be represented in the compatibility shader.

Start with a bounded support set and expand based on real mod telemetry:

```text
0 texture units
1 texture unit:
  modulate
  replace
  add
  alpha_blend / common alpha cases
```

Log unsupported combinations once per material/pass instead of guessing.

### Level 3 - optional RTSS-generated fallback

Ogre's RT Shader System is designed to generate shaders for fixed-function material state. Redux already exposes evidence of `ShaderGeneratorDefaultScheme` in runtime behaviour, so RTSS may be available in some form.

Investigate whether the shipped Ogre build exposes enough RTSS functionality to ask the existing generator for a DX11-compatible technique for arbitrary fixed-function materials.

If this can be invoked safely from the game's existing Ogre runtime, it may provide broader fixed-function coverage than a hand-maintained shader for:

- multiple texture stages
- more blend operations
- lighting variants
- generated texture coordinates
- more complex legacy state

Do **not** make RTSS the only path until its availability, ownership, thread requirements, and interaction with OpenShim's scheme takeover are proven. Treat it as a possible higher-coverage backend behind the same resolver.

### Level 4 - aggressive generic compatibility mode

Optional and OFF by default.

For unknown legacy programmable shader families that have unusable SM2/SM3 programs, an `Aggressive` mode may substitute a generic textured/untextured compatibility shader based on pass state.

This will not preserve custom shader semantics, so it should be clearly marked as best-effort. Its purpose is to prefer visible-but-imperfect geometry over black geometry for abandoned mods.

Do not enable this by default until tested against a representative mod corpus.

### Level 5 - shaderless-draw guard

Add a final DX11 safety net so one unsupported material cannot spam exceptions or stall rendering.

Before the render system reaches the known D3D11 `_render` exception path, detect the absence of a usable vertex or fragment program and skip the draw.

The guard must:

- be DX11-only
- log once per unique material/technique/pass/program combination
- include material name when that context can be captured earlier in the pass-binding path
- increment counters for diagnostics
- never be the normal compatibility path

Suggested message:

```text
[DX11COMPAT] skipped shaderless draw material=xrain technique=0 pass=0 vs=<none> ps=<none>
```

This converts catastrophic black-screen exception spam into a bounded compatibility miss.

## Technique construction: clone state, do not reconstruct it field-by-field

Where possible, copy/clone the original technique and passes, then replace only unusable GPU program references.

Avoid a hand-written list such as:

```text
copy scene_blend
copy depth_write
copy cull
copy texture_unit
...
```

because legacy material scripts can contain state we did not anticipate. Ogre's own technique/pass copy semantics are preferable if the required ABI can be resolved safely.

If direct cloning cannot be reached safely through the current binary ABI, prefer creating an OpenShim-owned companion material/technique through a narrow set of resolved methods rather than mutating the source material in place.

Generated compatibility objects should be cached by something equivalent to:

```text
(material identity, requested scheme, lod, source technique, compatibility variant)
```

and invalidated only when the material is unloaded/reloaded.

## Source-technique selection

When no supported technique exists, the compatibility generator still needs the best semantic source.

Recommended search order:

1. exact requested scheme + requested LOD, even if unsupported
2. exact requested scheme + closest LOD, unsupported allowed
3. base/default/blank scheme + requested or closest LOD
4. first technique as last semantic template

Do not simply clone technique 0 unless all better matches fail.

## Fixed-function vs legacy-program classification

Treat these as separate cases.

### True fixed-function

```text
no vertex program
no fragment program
```

Use fixed-function emulation.

### Known legacy programmable family

```text
vertex/fragment program references exist
program target unsupported by DX11
program name matches known BZR/legacy family
```

Use the family-specific SM4 adapter.

### Unknown custom programmable family

```text
program references exist
program is unsupported
family is unknown
```

Default behaviour:

- log once
- do not pretend the custom effect is fixed-function
- allow shaderless guard to skip it safely if no better path exists

Aggressive mode may use the generic adapter.

## Proposed implementation structure

Keep policy/testable classification separate from Ogre binary hooks.

Suggested files:

```text
include/dx11_legacy_material_compat.h
src/engine/dx11_legacy_material_compat.cpp
src/patches/ogre_render_profile.cpp
src/patches/dx11_legacy_material_runtime.cpp   # if the runtime seam becomes large
resources/renderer/enhanced/openshim_dx11_fixedfunc.program
resources/renderer/enhanced/openshim_dx11_fixedfunc-sm4.hlsl
```

Pure engine module responsibilities:

- classify legacy program families
- choose fallback variant
- map program names
- decide safe/aggressive behaviour
- build cache keys
- expose reason codes for logging/tests

Runtime module responsibilities:

- resolve the minimum Ogre ABI needed to inspect/copy techniques and passes
- instantiate/cache compatibility techniques
- bind OpenShim GPU programs
- capture material/pass context for diagnostics
- install shaderless-draw guard if required

## Suggested settings

Names are proposals; do not ship them until the implementation exists.

```ini
[Fixes]
DX11LegacyMaterialCompat = 1
DX11ShaderlessDrawGuard = 1
DX11LegacyMaterialAggressive = 0
```

`DX11LegacyMaterialCompat` should default ON once qualified because there is no mod-side setting capable of fixing abandoned content automatically.

`DX11LegacyMaterialAggressive` should default OFF because it may intentionally replace unknown custom shader semantics with a generic approximation.

Keep this independent of `EnhancedSchemeFallback`:

- `EnhancedSchemeFallback` selects an existing usable base technique when an Enhanced scheme is missing.
- `DX11LegacyMaterialCompat` makes an otherwise DX9-only/fixed-function technique executable on DX11.

## Resource deployment

Extend the existing render-profile resource validation/deployment contract rather than creating a second resource loader.

Any new mandatory compatibility shader files should be included in `render_profile_resources` validation and its unit tests so a partial installation cannot silently enable the feature with missing shader assets.

If the feature is compiled in but resources are missing, fail closed to:

```text
compat feature unavailable + one clear startup warning
```

rather than enabling a half-working path.

## Diagnostics

Add bounded diagnostics that answer why a material failed or which path repaired it.

Examples:

```text
[DX11COMPAT] material=xrain source=default/0 path=fixedfunc-textured cached=1
[DX11COMPAT] material=White_Clouds path=family-remap family=Effect
[DX11COMPAT] material=FancyWater unsupported custom programs vs=ModWaterVS ps=ModWaterPS action=skip
```

Recommended counters for exit/summary logging:

```text
native supported techniques
legacy family remaps
fixed-function generated techniques
RTSS generated techniques (if implemented)
aggressive generic fallbacks
unsupported custom shader passes
shaderless draws skipped
```

Do not emit per-frame messages after the first unique occurrence.

## Validation plan

### Automated

Add engine-independent tests for:

- known shader-family mapping
- case-insensitive aliases
- fixed-function classification
- unknown custom family classification
- safe vs aggressive policy
- source-technique selection policy where it can be modeled independently
- stable cache-key generation
- config default/parse coverage once settings are implemented
- renderer resource validation for any new `.program` / `.hlsl` files

Run:

```text
scripts/run_ini_tests.ps1
scripts/run_render_profile_tests.ps1
ctest
scripts/verify_windows.ps1
```

Compile the HLSL targets as part of validation where tooling is available.

### Live DX11 corpus

At minimum test:

1. stock Redux map on DX11
2. Enhanced profile on DX11
3. ISDF Chronicles case that reproduced the black screen
4. a pure fixed-function material such as the observed `xrain` case
5. a legacy-program material such as the observed `Effect_*` / `White_Clouds` case
6. texture scrolling / animated texture state
7. alpha-blended particles/clouds
8. fogged geometry
9. untextured geometry
10. a deliberately unknown custom SM3 shader to verify safe degradation

Start live diagnosis windowed with FSAA disabled so material compatibility is isolated from unrelated driver/device issues. Then re-test at high resolution/FSAA after the material errors are eliminated.

Acceptance criteria:

- no recurring `Attempted to render to a D3D11 device without both vertex and fragment shaders` exceptions
- no black-screen failure caused by fixed-function-only mod materials
- known legacy shader families render through SM4 adapters
- unsupported custom shaders produce bounded diagnostics, not exception floods
- DX9 output/path is unchanged
- native DX11 materials are unchanged
- common fixed-function state visually matches DX9 closely enough for compatibility use

## Implementation phases

### Phase 1 - diagnostics and safety

- add classification helpers/tests
- capture material/pass/program names around the failing path
- add once-only diagnostics
- add DX11 shaderless-draw guard

This immediately prevents a single bad mod material from producing thousands of render exceptions.

### Phase 2 - fixed-function compatibility

- add OpenShim fixed-function SM4 shaders
- add the smallest Ogre ABI required to build/cache a compatibility technique
- preserve source pass/texture state through cloning/copy semantics
- support 0/1 texture unit common operations, texture matrix animation, fog, alpha

This should solve pure fixed-function materials without any mod edits.

### Phase 3 - known legacy shader-family adapters

- map stock/BZR SM2/3 families seen in real logs to SM4 equivalents
- reuse existing OpenShim Enhanced SM4 implementations where semantics match
- add dedicated adapters only where necessary

This should solve materials that reference old BZR shader families without editing those materials.

### Phase 4 - broader compatibility

- investigate existing RTSS integration as an automatic generator for complex fixed-function state
- expand multi-texture and blend-op coverage from real corpus telemetry
- optionally add aggressive generic fallback for abandoned custom shaders

## Recommendation

Implement the compatibility resolver rather than telling mod authors to add DX11 techniques manually.

The best long-term architecture is:

```text
legacy/custom material
        |
        v
existing supported technique? ---- yes ---> render unchanged
        |
        no
        v
known legacy shader family? ------ yes ---> cached SM4 family adapter
        |
        no
        v
true fixed-function pass? -------- yes ---> cached OSE fixed-function shader
        |
        no
        v
RTSS can safely generate it? ----- yes ---> cached generated technique
        |
        no
        v
aggressive compatibility enabled?  yes ---> generic best-effort shader
        |
        no
        v
log once + skip shaderless draw safely
```

That provides a global compatibility layer for old Workshop/community content while retaining native behaviour for correctly authored DX11 materials and keeping DX9 untouched.
