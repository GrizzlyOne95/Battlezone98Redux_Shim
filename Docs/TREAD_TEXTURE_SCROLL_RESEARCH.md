# Tread texture scroll: research (queue item 10)

Research only, no code. Paths are repo-relative; `GAME` is
`C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux` (read-only).
Anything not checked is marked UNVERIFIED.

## Conclusion

Feasible on Direct3D 11 with the Enhanced profile, as a **renderable custom
parameter feeding a UV offset in the vertex shader** (approach 2). It needs no
material clones. Per-unit, per-side tread speed already exists
(`src/patches/tracked_vehicle_class.cpp:1930-1943`). OpenShim would accumulate a
scroll phase beside the clip time and write it with
`Renderable::setCustomParameter`, the mechanism `local_damage.cpp` already ships
(`src/patches/local_damage.cpp:295,328`).

Three facts decide it:

1. The stock shaders cannot scroll. `GAME\BZ_ASSETS_CORE\common\programs\base.program`
   has 0 `texture_matrix` lines (grep count 0) and the stock vertex shader
   copies the coordinate through
   (`GAME\BZ_ASSETS_CORE\pc\programs\dx11\base-sm4.hlsl:135`,
   `vTexCoord = iTexCoord;`). OpenShim's Enhanced one does the same
   (`resources/renderer/enhanced/openshim_enhanced_base-sm4.hlsl:1002`).
   `Docs/TRACKED_VEHICLES.md:79-81` is correct. So a material scroll (EXU
   `SetMaterialTextureScroll`, `Docs/TRACKED_VEHICLE_SCOPE.md:31`) would show
   nothing on a stock-program material. That is inference from the two shaders;
   the EXU implementation was not read (UNVERIFIED).
2. A material is shared by every unit using the mesh, so a material-level
   scroll moves all units (`Docs/TRACKED_VEHICLES.md:81`). Per-unit state must
   live on the SubEntity (custom parameter) or on a per-unit material clone.
3. A shader change is unavoidable either way. The cheapest home is OpenShim's
   own Enhanced base program, which already binds custom parameters
   (`resources/renderer/enhanced/openshim_enhanced_base.program:2614-2624`,
   indices 1400..1410, so 1411+ is free; `include/local_damage_policy.h:21`).

Blocker: none for a DX11 Enhanced v1. Main risk is the GPU skinning and
instancing twin passes (Risk 1); verify that first.

## What does not exist

- No `texture_matrix` or UV offset in any stock vehicle program (above). The
  only users (UNVERIFIED: no repo-wide count) are `GAME\BZ_ASSETS_CORE\common\programs\uitexmat.program` (UI) and
  OpenShim's DX11 fixed-function programs
  (`resources/renderer/enhanced/openshim_dx11_fixedfunc.program:34`,
  `openshim_dx11_fixedfunc-sm4.hlsl:125`), which carry `scroll_anim` for legacy
  materials (`Docs/DX11_LEGACY_MATERIAL_COMPATIBILITY.md:131,276`). They are
  unlit and material-level, so they are not a lit, shadowed tank tread.
- No per-unit material cloning. Cloning exists only in GPU skinning
  (`src/patches/gpu_skinning.cpp:810,1301,1408`) for skinned and caster twins.
- `grep -i scroll src/` finds nothing relevant; `tracked_vehicle_class.cpp:45`
  is the comment saying scroll cannot work.

## Approaches

| # | Approach | Cost | Risk / side effects | Renderers | Verdict |
|---|----------|------|---------------------|-----------|---------|
| 1 | Per-unit clone of the tread material (as `gpu_skinning.cpp:1408`) plus shader with offset uniform | M-L: clone create/destroy per spawn, lifetime on death and save-load, `SetSubEntityMaterialByName` (`gpu_skinning.cpp:1531`) | Material count grows with units (limit UNVERIFIED); collides with skinning's own clones; still needs the shader change, so gains nothing over 2 | any with a shader | Reject |
| 2 | `SubEntity::setCustomParameter(1411, (uL,uR,0,0))` per tick; `param_named_auto osTreadUV custom 1411`; vertex shader adds the side's offset to `iTexCoord` | S-M: exports already resolved (`local_damage.cpp:295`), a few HLSL lines, ODF keys, phase state | Stale values and twin passes (Risks 1-2) | DX11 Enhanced in OpenShim's program. DX9 and stock DX11 only with a modder-supplied shader | **Recommended** |
| 3 | CPU UV rewrite of a per-unit clone of the tread sub-mesh | L: per-unit mesh clone breaks the shared vertex data skinning and instancing key on (`gpu_instancing.cpp:3-8`); lock and write per frame | My estimate, not measured: 100 units x ~500 tread verts x 8 B is about 0.4 MB/frame of locked writes. The cost is the lifecycle and losing instancing, not the bytes | all | Reject |
| 4 | Reuse existing scroll (fixed-function `scroll_anim`, EXU scroll) | none usable | Unlit and per material, so every unit scrolls | DX11 only | Reject |

## Recommended v1 plan (default off)

Scope: DX11 + Enhanced profile, the same gate as local damage
(`local_damage.cpp:310-316`). Stock, Retro and DX9 stay clips-only. A modder
who wants stock DX11 or DX9 can copy the one-line shader change into their own
program (document it, do not implement it).

ODF keys in `[TrackedClass]`, beside `treadCycleLength` (parsed at
`tracked_vehicle_class.cpp:518,663`):

- `treadScrollU = 0` : default off. Texture repeats per `treadCycleLength`
  metres of travel, so 1.0 is one UV loop per cycle, the same cycle the clips
  use (`Docs/TRACKED_VEHICLES.md:58-60`). Negative flips direction. U axis
  only in v1.
- `treadMaterialL` / `treadMaterialR` : names of the left and right tread
  materials. Explicit keys rather than a naming convention, because material
  names are mod-specific and a missing key then means "off". Alternative is
  the BZCC-style `*tread*` sub-mesh name (`Docs/TRACKED_VEHICLE_SCOPE.md:54`).
  Whether Ogre exposes a SubEntity's material or sub-mesh name through an
  export OpenShim can resolve is UNVERIFIED.

Phase: per unit and side, `phase += speed * dt * treadScrollU /
treadCycleLength`, wrapped with `fract` on the CPU (float precision over long
sessions), held in `TreadState` (read and written at
`tracked_vehicle_class.cpp`: read at :1932, written back at :1976) and cleared by the same cleanup hooks as
the clip state. Left uses `state.left`, right uses `state.right`, so a pivot
scrolls the treads in opposite directions with no extra code.

Files to touch:

- `src/patches/tracked_vehicle_class.cpp`: parse keys, accumulate phase, call
  the writer after `DriveClip` (`:1942-1943`).
- A small writer, reusing `local_damage.cpp`'s sub-entity walk (`:318-329`) and
  `src/patches/ogre_entity_liveness.cpp`: write `Vector4(phaseL, phaseR, 0, 0)`
  to custom index 1411 on every SubEntity whose material is in the unit's L/R
  set.
- `resources/renderer/enhanced/openshim_enhanced_base.program` and
  `openshim_enhanced_base-sm4.hlsl` (vertex entry `:954`, line `:1002`): add
  `uniform float4 osTreadUV` and `uniform float4 osTreadSide`, and
  `vTexCoord = iTexCoord + float2(dot(osTreadUV, osTreadSide), 0)`, behind a
  `TREAD_SCROLL` define so only tread passes pay. The `-sm3.hlsl` and GLSL
  siblings exist; the DX11 gate means only sm4 in v1.
- A new OpenShim-owned Enhanced material deriving the base with that define
  (`Docs/ENHANCED_RENDERER_MATERIAL_OWNERSHIP.md`). `osTreadSide` is a
  per-material constant: L `(1,0,0,0)`, R `(0,1,0,0)`.
- Docs: `Docs/TRACKED_VEHICLES.md:79-81` and `:309` say "no UV scroll"; update.
  Phase maths goes beside `StepTreadSpeed` in
  `include/tracked_vehicle_treads.h:43` with a unit test next to the existing
  tread tests (test file UNVERIFIED).

Modder workflow: split the tread geometry into an L and an R sub-mesh, give
each a material derived from the OpenShim tread material (own maps, U running
along the belt), set the ODF keys.

## Risks to settle first (UNVERIFIED unless stated)

1. GPU skinning clones each pass and builds a skinned vertex program from the
   source (`src/engine/gpu_skinning_hlsl.cpp`); instancing twins read only a
   per-instance float (`gpu_instancing.cpp:3-8`). Whether the clone keeps a
   custom auto-constant and the `TREAD_SCROLL` define is unchecked, and
   instancing would merge units that need different offsets, so tread passes
   likely must be excluded from instancing. Most probable source of rework.
   Checked: local damage already lives with the same instancing limit (an
   instanced group takes the leader's custom parameters,
   `Docs/LOCAL_DAMAGE.md:84-85`), and `GpuInstancing` is an Experimental
   option. Tread units carry `tread_L`/`tread_R` skeletons, so the GPU-skinned
   twin's vertex program is the one that must apply the offset. Local damage also notes that under hardware skinning `inverse_worldview_matrix` is bone 0's (`Docs/LOCAL_DAMAGE.md:86-88`); a UV offset from a `custom` auto-constant should not depend on that matrix, but this is UNVERIFIED.
2. Stale values: a Renderable that never wrote the parameter inherits the last
   value (`Docs/LOCAL_DAMAGE.md:124`). Safe only if every Renderable using the
   tread material is written every frame. State "tread material is for tracked
   units only", or add a key guard like `osMarkKey` (`LOCAL_DAMAGE.md:127`).
3. Cadence: PostSimulate runs per sim tick; render may run faster, so low sim
   rates could look steppy (clips share this).
4. Multiplayer: cosmetic and per client; nothing is sent or saved. Peers without
   OpenShim see an unscrolled texture. Remote replicas dead-reckon
   (`Docs/ACTIVE_PATCHES.md:22`); whether their tread speed feeds the phase
   the same way is unchecked.
5. Save, load, death: phase is cosmetic and may restart at 0; cleanup slots 0, 3
   and 4 (`Docs/TRACKED_VEHICLES.md:225-227`) can clear it.

## Open questions for the user

1. **Decided 2026-11-18:** DX11 Enhanced only for v1; stock and DX9 stay
   clips-only.
2. Marker: explicit `treadMaterialL/R` keys (recommended) or a `*tread*`
   sub-mesh name convention?
3. Is there a tracked test model with split tread sub-meshes? None found in this
   repo; no tread material in `GAME\BZ_ASSETS_CORE\common` (grep returned
   nothing). A fixture is needed for live verification.
4. Is U-only enough, or do your models run the belt along V?
5. If Risk 1 fails, accept excluding tread materials from skinning/instancing
   (tracked units draw unbatched), or defer the feature?
