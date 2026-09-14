# Phase 1.1: Enhanced shading through the full LOD chain

Roadmap item 1.1 asks for "dedicated DX11 Enhanced Medium and Low delegates
that retain the same material interpretation as High", to kill the lighting
and reflection pop at the ~250/300-unit LOD boundaries.

This records what the pop actually is, where the fix belongs, and what
constrains it. No implementation yet.

---

## 1. Where the Enhanced model stops

`lod_values 250 300` in `CR_BZBase.material`: LOD 0 under 250 units, LOD 1 from
250 to 300, LOD 2 beyond.

Campaign Reimagined's materials are **already correctly wired**. Every `en-*`
technique, at every LOD, overrides the inherited pass's fragment program to an
Enhanced name:

```
technique { scheme en-high-pssm  lod_index 1
    pass : BZPassSchemeMediumNoShadow {
        fragment_program_ref OSE_BaseENMediumNoShadow_fragment { }
    }
}
```

The pop is one level down, in OpenShim's payload. `OSE_BaseENMediumNoShadow_fragment`
is a unified program, and every one of its delegates points at the **legacy**
program:

```
fragment_program OSE_BaseENMediumNoShadow_fragment unified
{
    delegate OSE_BaseMediumNoShadow_fragmentGLSLES
    delegate OSE_BaseMediumNoShadow_fragmentGLSL
    delegate OSE_BaseMediumNoShadow_fragmentHLSL4
    delegate OSE_BaseMediumNoShadow_fragmentHLSL
}
```

The `EN` name exists and is bound; it is an alias for the compatibility path.
The same is true of every `EN` tier except High, in both families:

| Unified program | Delegates to |
| --- | --- |
| `OSE_BaseENHigh{NoShadow,Shadow,PSSM}` | `OSE_BaseENHigh*` — genuinely Enhanced |
| `OSE_BaseENMedium{NoShadow,Shadow,PSSM}` | `OSE_BaseMedium*` — legacy |
| `OSE_BaseENLow{NoShadow,Shadow,PSSM}` | `OSE_BaseLow*` — legacy |
| `OSE_BaseENLowest{NoShadow,Shadow,PSSM}` | `OSE_BaseLowest*` — legacy |
| `OSE_TerrainEN*` | identical pattern |

So crossing 250 units does not soften the Enhanced shading — it **leaves it**.
Cook-Torrance GGX, the split-sum IBL, linear light and radial fog all stop at
once, and the legacy Blinn-Phong path takes over with no normal map. That is
the pop.

**This is entirely OpenShim's to fix**, which matches the roadmap's stated
ownership ("OpenShim shaders/programs; CR validates its materials"). No
material change is required on either side: the names are already referenced,
only what they resolve to has to change.

## 2. What constrains the fix

The abstract pass supplies the **vertex** program, and that is CR's material,
not OpenShim's. `BZPassSchemeMediumNoShadow` binds `OSE_BaseMediumNoShadow_vertex`,
whose HLSL4 declaration is:

```
MAX_LIGHTS=8
```

No `NORMALMAP_ENABLED`, so no tangent frame reaches the fragment stage; and
the light-array size is 8, not 24. An Enhanced Medium fragment bound into that
pass therefore has to be built as **High's defines minus the normal map, with
the matching light count**:

| Tier | Vertex program provides | Enhanced fragment can use |
| --- | --- | --- |
| High | `MAX_LIGHTS=24, NORMALMAP_ENABLED` | everything |
| Medium | `MAX_LIGHTS=8` | GGX, IBL, linear light, radial fog, specular map — no normal map |
| Low | `MAX_LIGHTS=1` | same, one light |
| Lowest | `VERTEX_LIGHTING, MAX_LIGHTS=1` | see below |

That is a good fit for what the roadmap actually asks: *"Reduce sample count or
disable fine detail by LOD, but do not switch material models."* Dropping the
normal map is disabling fine detail. Keeping albedo/F0/roughness, GGX, the IBL
split-sum, the colour-space convention and the fog model is not switching
models.

**Lowest is a real exception.** It is vertex-lit by construction, so there is
no per-pixel lighting to make physically based. Forcing `ENHANCED_MODE` there
compiles (1516 bytes, against 11712 for Enhanced High) but the define is
almost entirely inert, because `VERTEX_LIGHTING` short-circuits the lighting
loop before any of it runs. Lowest should stay as it is, and the reason should
be written down rather than rediscovered.

## 3. Feasibility is proven

Every permutation the fix needs compiles today, against the payload as it
stands, with no shader edit:

```
fxc /T ps_4_0 /E base_fragment    ... ENHANCED_MODE, OSE_LINEAR_LIGHT=1, OSE_RADIAL_FOG=1
```

| Permutation | Result | Size |
| --- | --- | --- |
| `ENMediumNoShadow` (8 lights, no normal map) | OK | 10164 |
| `ENLowNoShadow` (1 light) | OK | 9860 |
| `ENMediumPSSM` (8 lights, PSSM, PCF 4) | OK | 20600 |
| Terrain `ENMediumNoShadow` | OK | 8540 |
| Terrain `ENLowNoShadow` | OK | 8240 |
| `ENLowest` (vertex-lit) | OK | 1516 — inert, see §2 |
| *legacy* `MediumNoShadow` (today's LOD 1) | OK | 4848 |
| *legacy* `LowNoShadow` (today's LOD 2) | OK | 4440 |
| *Enhanced* `HighNoShadow` (today's LOD 0) | OK | 11712 |

The cost story is the honest part of this: an Enhanced Medium is roughly
**2.1x** the bytecode of the legacy Medium it replaces, and only ~13% smaller
than Enhanced High. Bytecode size is not frame time, but it says plainly that
the saving between LOD 0 and LOD 1 today comes mostly from *abandoning the
model*, not from the light count. Closing the pop will cost real GPU time at
distance, and the benchmark set exists to measure exactly that.

That is the first thing to measure, not assume:

```
powershell -ExecutionPolicy Bypass -File reverse_engineering\run_live_combat_benchmark.ps1 `
    -World moon -Scenario fourteam -Count 80
```

## 4. Plan

1. Add real HLSL4 Enhanced fragment programs for the Medium and Low tiers in
   both families, with the defines §2 allows.
2. Repoint only the **HLSL4** delegate of each `OSE_*EN{Medium,Low}*_fragment`
   unified program. GLSL, GLSLES and HLSL keep today's legacy delegates, so
   DX9 and GL fail back cleanly and unchanged.
3. Leave Lowest alone and document it (§2).
4. Introduce a single `OSE_ENHANCED_LOD_TIER` define so the shared shader can
   shed cost by tier — fewer IBL specular samples, one detail-normal octave
   instead of two, reduced PCF — without branching on tier in more than one
   place.
5. Measure LOD 0/1/2 frame time per world before and after, on the Phase 0
   benchmark set. A pop that is merely cheaper to look at is not the goal.
6. Visually confirm the 250 and 300 boundaries on Moon (harshest, airless) and
   Io (brightest emissive), approaching and retreating.

Steps 1-3 are mechanical once the tier define exists; step 4 is the only part
that touches shader logic, and it is where the specular-antialiasing and
lower-cost-IBL items from the roadmap live.
