# Enhanced renderer and material ownership

## Decision

OpenShim is the technical owner of Battlezone 98 Redux enhanced rendering.

Campaign Reimagined (CR) is a consumer of that renderer and remains the owner of campaign-specific art direction, replacement textures, normal/specular/emissive maps, reactive presentation, weather art, and intentionally custom CR materials.

The important consequence is that stock Battlezone content must not require Campaign Reimagined merely to route stock materials through OpenShim's enhanced shaders.

## Why this needs an explicit migration

The current system is already partly split this way:

- OpenShim owns the `OSE_*` enhanced shader programs under `resources/renderer/enhanced/`.
- CR's `CR_BZBase.material` and `CR_BZTerrainBase.material` bind their passes to those `OSE_*` programs.
- A large portion of CR's `Materials/` tree consists of stock or stock-derived material definitions whose main purpose is to inherit the CR base material and thereby route stock names through the enhanced renderer.

That last responsibility is not campaign content. It is a compatibility/adaptation layer for the renderer and should ultimately belong to OpenShim/OpenShimAssets.

## Ownership rule

Use this test when auditing an existing CR material:

> If deleting all Campaign Reimagined artwork would still leave the material useful as a way to render stock Battlezone content through OpenShim Enhanced, the generic/stock-compatible part belongs to OpenShim.

Conversely, if the material exists because CR supplies different artwork, presentation, weather, damage states, planet-specific tuning, or another campaign-specific visual decision, it remains in CR.

## OpenShim owns

- HLSL/GLSL implementation used by Enhanced rendering.
- Ogre `.program` declarations for those shaders.
- Generic base material templates for entities, terrain, effects, shadow receivers/casters, and other renderer-level material classes.
- Shadow pipeline material state required by OpenShim's renderer.
- Enhanced lighting, PSSM/shadow behavior, HDR/exposure, scene-depth services, SSAO/depth haze, post-processing, and other reusable renderer features.
- Renderer capability/fallback logic and D3D9/D3D11 distinctions.
- Generic texture-slot contracts such as DiffuseMap, NormalMap, SpecularMap, and EmissiveMap plus safe fallback maps.
- The mechanism that allows stock material names/content to use the enhanced renderer without CR being installed.

## Campaign Reimagined owns

- CR-specific diffuse, normal, specular, emissive, roughness, or other texture assets.
- Materials whose purpose is to select CR-specific replacement art.
- Planet/mission-specific art direction and tuning.
- CR reactive damage/hit materials and their artwork.
- CR weather billboard/skydome materials and their artwork.
- BZ2/upscaled/reauthored effect artwork selected by CR.
- Any intentional CR-only material behavior that is not a generic rendering capability.

## Phase 1: proven stock compatibility pack

Do not block the ownership correction on a new runtime Ogre interception system.

First, migrate the existing proven stock-derived redirect pattern into OpenShimAssets where appropriate.

Target shape:

```text
OpenShimAssets/
  renderer/
    enhanced/
      shaders + programs
      openshim_base.material
      openshim_terrain.material
      openshim_shadow.material
      openshim_effect.material

    stock_compat/
      stock entity/material redirects
      stock terrain/material redirects
      stock effect redirects where justified
```

The stock-compatible material definitions should preserve stock material names where necessary so existing BZN/TRN/mesh/ODF content does not have to be repointed.

The generic parents should use OpenShim names rather than CR names, for example:

```text
OpenShim/BZBase
OpenShim/BZTerrainBase
OpenShim/Effect
```

The exact names are implementation details; the architectural constraint is that CR must no longer be the namespace owner of reusable renderer base materials.

## Phase 2: runtime material enhancement

After Phase 1 is working and qualified, investigate reducing or eliminating the stock material-copy layer by adapting Ogre materials at runtime.

Desired flow:

```text
stock material name
    -> Ogre::Material resolves normally
    -> OpenShim classifies/qualifies material
    -> OpenShim adds or replaces an Enhanced technique
    -> original diffuse/content is retained
    -> missing enhanced maps receive safe fallbacks
    -> renderer uses OSE/OpenShim Enhanced programs
```

Candidate responsibilities for a runtime material enhancer:

- distinguish terrain/entity/effect/UI/transparent/sky/cockpit material classes;
- preserve existing texture aliases and stock behavior unless Enhanced explicitly replaces it;
- add flat-normal, neutral-specular, and black-emissive fallbacks when the source material lacks enhanced maps;
- avoid touching UI, overlays, cockpit, special render targets, or other excluded classes unless explicitly supported;
- remain reversible when Enhanced mode is disabled;
- survive mission reload, renderer/resource reload, and resolution/device lifecycle;
- emit diagnostics explaining whether a material was upgraded, skipped, or rejected and why.

Runtime enhancement is preferable long-term because it avoids shipping a second copy of a large stock material catalog. It is not required for the initial ownership migration.

## Resource precedence

The intended dependency direction is:

```text
Stock Redux resources
        |
        v
OpenShim generic renderer + stock compatibility/adaptation
        |
        v
Campaign Reimagined optional art/material overrides
```

OpenShim must never depend on CR resource names or require CR to be installed.

CR may depend on stable OpenShim material/shader contracts.

When CR provides richer D/N/S/E maps for a stock material name, OpenShim should render those richer inputs through the same generic renderer path rather than requiring a separate CR renderer.

## Existing code/resources to inspect

OpenShim:

- `resources/renderer/enhanced/openshim_enhanced_base.program`
- `resources/renderer/enhanced/openshim_enhanced_base-sm4.hlsl`
- `resources/renderer/enhanced/openshim_enhanced_base-fragment.glsl`
- `resources/renderer/enhanced/openshim_enhanced_terrain.program`
- `resources/renderer/enhanced/openshim_enhanced_terrain-sm4.hlsl`
- `resources/renderer/enhanced/openshim_enhanced_terrain-fragment.glsl`

Campaign Reimagined references to audit:

- `Materials/CR_BZBase.material`
- `Materials/CR_BZTerrainBase.material`
- `Materials/CR_DepthShadowmap.material`
- `Shaders/CR_DepthShadowmap*`
- `Shaders/CR_effect-*`
- stock-named/stock-derived material files inheriting `CR_BZBase`

Do not assume every CR material moves. Classify each file by purpose.

## Coordination with scene-depth work

This ownership decision complements OpenShim PR #191 (`docs(dx11): investigate reusable scene depth and screenspace effects`).

PR #191 establishes that scene depth, AO, depth-aware haze, soft-particle support, renderer lifecycle, and related effects are OpenShim responsibilities. This document extends the same rule to the shader/material front end: reusable rendering infrastructure and stock compatibility belong beside that renderer rather than in the campaign mod.

## Migration checklist

### Inventory

- [ ] Enumerate CR `Shaders/` and classify generic renderer code versus CR-only shader behavior.
- [ ] Enumerate CR `Materials/` and classify each file as renderer infrastructure, stock compatibility redirect, mixed, or CR-specific content.
- [ ] Identify exact duplicates or near-duplicates already present under OpenShim `resources/renderer/enhanced/`.
- [ ] Record stock origin/provenance for copied stock material definitions where practical.

### OpenShim generic resources

- [ ] Move/replace generic base material templates under OpenShim ownership.
- [ ] Move/replace generic shadow material/program resources under OpenShim ownership.
- [ ] Consolidate generic effect shaders so OpenShim is the single source of truth.
- [ ] Remove CR-prefixed naming from generic renderer contracts.
- [ ] Preserve Classic/non-Enhanced behavior and existing fallback paths.

### Stock compatibility

- [ ] Select a representative stock entity, terrain, effect, transparent material, and special material for qualification.
- [ ] Prove stock campaign content can receive Enhanced rendering without CR installed.
- [ ] Expand the stock compatibility set only after representative tests pass.
- [ ] Verify Workshop/mod materials are not unexpectedly overridden merely because they share textures or similar names.

### CR consumer migration

- [ ] Update CR-specific materials to inherit/import OpenShim-owned generic bases.
- [ ] Keep CR-specific D/N/S/E and presentation resources in CR.
- [ ] Delete CR stock copies only after equivalent stock rendering works through OpenShim.
- [ ] Document the minimum OpenShim/OpenShimAssets version required by CR after migration.

### Runtime enhancement research

- [ ] Locate the safest Ogre material lifecycle interception point after resource resolution but before first use/render.
- [ ] Determine whether techniques can be added/replaced without breaking material inheritance, aliases, LOD, shadow schemes, or resource reload.
- [ ] Prototype diagnostics-only classification before mutating materials.
- [ ] Compare runtime enhancement against the Phase 1 stock compatibility pack for visual and behavioral equivalence.

## Acceptance criteria

The ownership migration is successful when all of the following are true:

1. OpenShim Enhanced can visibly enhance representative stock Redux missions with Campaign Reimagined absent.
2. CR no longer needs to own generic base/shadow/effect shader infrastructure merely to activate OpenShim rendering.
3. CR retains control over its own replacement artwork and intentional campaign presentation.
4. Stock compatibility does not require editing every stock BZN/TRN/mesh/ODF reference.
5. Enhanced-off/Classic behavior remains compatible with stock Redux.
6. The architecture has one authoritative implementation of each generic shader/material path rather than parallel CR and OpenShim copies.

## Non-goal for this planning PR

This document does not move renderer resources or alter shipped material behavior yet. The first implementation PR should begin with the inventory/classification and a small representative stock-material qualification set rather than bulk-moving the CR tree.