# Terrain clutter and foliage — plan

Status: **not started.** Design anchor. No renderer implementation exists yet.

Target: GOG Battlezone 98 Redux 2.2.301, Ogre 1.10, D3D9 and D3D11 backends.

Motivating case: **Achilles**, whose terrain atlas is grass, dirt, mossy rock,
water and a waterfall. It is the one stock world where bare ground reads as
missing content rather than as a design choice. Everything here generalises, but
Achilles is what should prove it.

## Ownership

This is renderer capability, so it belongs in OpenShim, on the same contract
already written down in `DX11_SCENE_DEPTH_AND_SCREENSPACE_EFFECTS.md`: OpenShim
owns the D3D/Ogre resources and their lifetime, EXU expresses per-mission intent
through a narrow bridge, and EXU never holds a device object or a batch handle.

A mission says *"this world has knee-high grass out to 120 units"*. It does not
say how that is batched.

## What Ogre gives us, verified against the shipped DLL

Ogre 1.10 has no grass system. It has three batching primitives that grass gets
built out of, and all three are exported from Redux's `OgreMain.dll` — checked
against the export table, not against Ogre's documentation:

| Mechanism | Key exports present |
| --- | --- |
| **`StaticGeometry`** | `SceneManager::createStaticGeometry`, `addEntity`, `addSceneNode`, `build`, `setRegionDimensions`, `setRenderingDistance`, `setCastShadows`, `setVisibilityFlags`, `reset`, `destroy` |
| **Hardware instancing** | `SceneManager::createInstanceManager`, `InstanceBatchHW`, `BaseInstanceBatchVTF` |
| **`BillboardSet`** | both `createBillboardSet` overloads |

`StaticGeometry` is the right starting point. Ogre's own Grass sample is built on
it, and it needs no per-frame CPU work once built — which matters more here than
instancing's flexibility, because clutter never moves between rebuilds.

`PagedGeometry`, the standard Ogre grass/tree addon, targets Ogre 1.x. If LOD'd
trees are ever wanted it is a porting job rather than a rewrite. Out of scope for
a first cut.

## What Redux gives us for free

- **Placement is solved.** `GetTerrainHeightAndNormal` and
  `GetFloorHeightAndNormal` are both live Lua engine functions in the shipped
  exe. Height and slope alignment need no new native work.
- **The distance budget is small and already bounded.** `achilles.trn` sets
  `VisibilityRange=250`, `FogEnd=250`, `FlatRange=250`. Clutter never needs to
  exist beyond 250 units, which is also roughly where Enhanced's LOD tiers stop.
- **Wind already exists as a number.** `CRWeather.GetWind()` returns direction ×
  speed, weighted by how much weather is actually present, and
  `CRWeather.GetWindSpeed()` gives the scalar. CR's `aiCore.lua` already
  classifies `achilles` as a wind world alongside Mars and Titan. A waving grass
  shader should consume the wind the weather system is already computing rather
  than inventing a second one — grass leaning into a gust and dust accelerating
  in the same gust is one value, not two.

## What today's approach cannot do

Scenery today is game objects. `mbush01` in the addon folder is a real `.mesh`,
but its ODF makes it `classLabel = "i76building2"` — a full GameObject with a
handle, collision and AI presence. That is fine for a dozen pieces of set
dressing and impossible for a grass field. Batched geometry is the entire point.

## Three things that will bite

These are not speculative; each has already cost time elsewhere in this project.

1. **A material with no `en-*` Enhanced technique renders black on DX11
   Enhanced.** Ogre falls back to a technique whose parameters are never
   populated and the result NaNs. This has already happened to custom terrain. A
   clutter material must ship its Enhanced technique from the first commit, not
   as a follow-up.
2. **A mission change destroys scene state silently.** Process lifetime is not
   mission lifetime. `StaticGeometry` must be built per mission and torn down
   with it, and the "does it already exist" check must not be a name lookup —
   the same trap `CRWeather.ResetSystems` exists to work around for particles.
3. **The shadow budget is three sun cascades at 128m with no fourth slot.**
   Clutter must be `setCastShadows(false)`. It should still *receive* shade from
   the terrain lighting it inherits, which is free.

## Phasing

**Phase A — one static patch, no wind, no LOD.** Build a single
`StaticGeometry` region of grass cards on Achilles from a fixed seed, sitting on
`GetTerrainHeightAndNormal`. Prove it renders on both D3D9 and DX11 Enhanced and
that nothing is black. Measure the frame cost with the Ogre profiler, remembering
that its CPU column overstates by roughly 2× and that profiler-enabled frame
times are load-sensitive.

**Phase B — coverage and density.** Drive placement from the terrain atlas key so
grass appears on grass tiles and not on rock or water. `.trn` map names are atlas
keys, and an absent key silently draws the default tile, so the lookup must fail
loudly here. Add `setRenderingDistance` and region dimensions tuned against the
250-unit visibility range.

**Phase C — wind.** A vertex shader that displaces the card top by
`CRWeather.GetWind()`, phase-offset per instance so the field does not move as
one sheet. This is the phase that makes it look alive and the one most likely to
reveal a scheme-miss problem, which is why it is not first.

**Phase D — the settings row and the bridge.** A density setting with
`defaultIndex` matching "off", so an absent key changes nothing for existing
players. The EXU-side intent bridge lands here, not earlier.

## Open questions to settle before Phase A

- **Card or mesh?** Cross-quad grass cards are cheapest and read badly at a
  shallow camera angle, which BZ has a lot of. Worth a visual A/B before
  committing the asset pipeline.
- **Where does the art come from?** No vegetation exists in the stock tree beyond
  `mbush01`, and the Kenshi `DriftingFoliage*` set was rejected for this project
  as terrestrial seed pods and dry leaves. Achilles grass is new authored art.
- **Does clutter belong in the save?** It is derived from a seed and the terrain,
  so it should be reconstructible rather than serialised — but that needs
  confirming against how the save path tears down and rebuilds the scene.

## Related

- `DX11_SCENE_DEPTH_AND_SCREENSPACE_EFFECTS.md` — the ownership contract this
  follows, and the scene-depth service that soft-particle-style clutter blending
  would eventually want.
- `DX11_ENHANCED_RENDERING_ROADMAP.md`
- `ENHANCED_RENDERER_MATERIAL_OWNERSHIP.md` — where the `en-*` technique rule
  is written down.
