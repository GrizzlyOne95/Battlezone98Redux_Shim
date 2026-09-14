# Phase 1.1: Enhanced shading through the full LOD chain

Roadmap item 1.1 asks for "dedicated DX11 Enhanced Medium and Low delegates
that retain the same material interpretation as High", to kill the lighting
and reflection pop at the ~250/300-unit LOD boundaries.

This records what the pop actually is, where the fix belongs, what constrains
it, and what was built. Sections 1-3 are the diagnosis; section 4 is the
implementation and its evidence.

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

## 3. Feasibility, established before building anything

Every permutation the fix needs compiled against the payload as it stood,
before a line of it was written:

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

## 4. Implemented

Twelve HLSL4 fragment programs — Medium and Low, NoShadow/Shadow/PSSM, base
and terrain. Each one's defines are the **legacy tier's, verbatim**, plus
`ENHANCED_MODE,OSE_LINEAR_LIGHT=1,OSE_RADIAL_FOG=1,OSE_ENHANCED_LOD_TIER=n`.

Starting from the legacy defines rather than from High's is the whole safety
argument. The pass that binds these was built for the legacy program, so its
texture registers, sampler slots and light-array size are what the fragment
has to expect. Copying High's defines would enable a normal map whose tangent
frame the bound vertex program never emits, and (on terrain) a specular map
some passes do not bind.

Only the **HLSL4** delegate of each unified `EN` program is repointed. GLSL,
GLSLES and HLSL keep their legacy delegates, so DX9 and GL are untouched and
fail back exactly as before.

`OSE_ENHANCED_LOD_TIER` is the one knob that distinguishes the tiers beyond
`MAX_LIGHTS`, `PCF_SIZE` and the absent normal map. It applies a roughness
floor, because the tiers below High lose the thing that was doing specular
antialiasing: `filter_roughness_from_normal_variance()` measures `ddx/ddy` of
the shading normal, and with no normal map that is a smoothly interpolated
geometric normal whose derivatives are near zero. A low-roughness surface
therefore keeps a hard highlight with none of the high-frequency detail that
justified it, and the highlight crawls as the object moves. The floor is the
same correction applied open-loop: 0.18 at Medium, 0.30 at Low, against the
0.35 ceiling the variance filter is allowed on the High path. **Those two
numbers are a starting calibration, not a result** — they want a visual pass.

### Verified

`scripts/Test-EnhancedLodPermutations.ps1` reads the permutations out of the
`.program` scripts rather than restating them, compiles every one, and
compares the High bytecode against a baseline compiled from git:

```
18 Enhanced permutations compile
6 High permutations DXBC-identical to the merge-base
```

That second line is the roadmap's "preserve unaffected paths DXBC-identically"
contract, proven rather than asserted. The check is negative-tested: seeding a
one-digit change to `OSE_PBR_MAX_VARIANCE_ROUGHNESS` makes it report the three
base High permutations as `CHANGED` and leaves terrain `identical`, which is
exactly the blast radius of that seed.

The tier knob is also proven not to be inert — the same Medium permutation
compiled at tier 0, 1 and 2 produces three distinct DXBC hashes. A define that
changes nothing would look identical to one that works.

CR's three gates pass against the updated payload, and their counters moved
the way they should: 595 -> 607 declared program names (+12), and the Enhanced
program-boundary guard now sees **24** Enhanced SM4 fragment programs opted
into the Enhanced-only flags rather than 12, with the 64 Default/Retro
programs still held on the legacy path.

### Still outstanding

**The visual pass at the boundary.** A test deployment put the new payload and
CR's dedup materials on the GOG install and confirmed the package loads and
90 of the 92 `OSE_` program references in `CR_BZBase.material` resolve. It did
not exercise the boundary: `lcbench` spawns its units at 50 units, which is
LOD 0, so Medium and Low never rendered. The real check is a capture with
units at ~240 and ~320 units, before and after:

```
powershell -ExecutionPolicy Bypass -File reverse_engineering\run_live_combat_benchmark.ps1 `
    -World moon -Scenario idle -Distance 240,320
```

**Frame cost at distance.** Enhanced Medium is ~2.1x the bytecode of the
legacy Medium it replaces. Bytecode is not frame time, but the direction is
not in doubt and the number has to be measured before this ships.

## 5. An unrelated defect this surfaced

The two remaining unresolved references are `OSE_BaseENHighPSSMV2_vertex` and
`OSE_TerrainENHighPSSMV2_vertex`, and they are **pre-existing, not caused by
this work or by CR's dedup**. CR's own `CR_BaseENHighPSSMV2_vertex` has the
identical shape — a unified program with a single HLSL4 delegate — and every
other unified vertex program in the file has four. Ogre reports
`reference to a non existing object` for the single-delegate ones and resolves
the other twelve.

CR's material already carries a comment acknowledging the HLSL4-only vertex
program and a duplicate "renderer fallback" technique immediately after the v2
pass, so the fallback is intended. What is worth checking separately is
whether the v2 pass is being rejected on **DX11 as well**, in which case PSSM
v2 is not actually running anywhere and the architecture doc's claim about it
needs the same correction the payload snapshot needed in Phase 0.

## 6. Plan

1. ~~Add real HLSL4 Enhanced fragment programs for Medium and Low.~~ Done (§4).
2. ~~Repoint only the HLSL4 delegate of each unified EN program.~~ Done (§4).
3. ~~Leave Lowest alone and document it.~~ Done (§2).
4. ~~Introduce `OSE_ENHANCED_LOD_TIER`.~~ Done (§4). It currently carries the
   roughness floor only; further cost shedding by tier — fewer IBL specular samples, one detail-normal octave
   instead of two, reduced PCF — without branching on tier in more than one
   place.
5. Measure LOD 0/1/2 frame time per world before and after, on the Phase 0
   benchmark set. A pop that is merely cheaper to look at is not the goal.
6. Visually confirm the 250 and 300 boundaries on Moon (harshest, airless) and
   Io (brightest emissive), approaching and retreating.

Steps 1-3 are mechanical once the tier define exists; step 4 is the only part
that touches shader logic, and it is where the specular-antialiasing and
lower-cost-IBL items from the roadmap live.
