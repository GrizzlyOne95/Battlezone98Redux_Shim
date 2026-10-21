# Reactive surface prototype

OpenShim supplies zero-default surface uniforms in its DX11 Enhanced HLSL object shaders,
an optional leased EXU debris-material bridge, and the existing qualified
weapon presentation adapter's real firing-mount positions. EXU owns material
references and local-point conversion; Campaign Reimagined owns event queues,
wetness, damage/repair easing, power polling and presentation budgets.

The source techniques, textures, render states and GPU vertex programs survive
material cloning. GPU skinning accepts an EXU variant only after the existing
render-thread entity walk proves the entity is live and every vertex program
matches the stable native template, including after EXU releases a previous
variant. A bounded 64-entry queue carries names across that boundary. No new
world walk or retained cross-DLL callback is introduced.

## Rendering

- Wetness gently darkens the source and lowers Enhanced roughness. Enhanced
  High on DX11 adds procedural surface beads and narrow animated runoff trails.
  They perturb the existing lighting normal and add a reflective clear wet coat
  with droplet rims and moving runoff highlights, preserving the original paint.
  Fine detail fades between 12 and 28 metres and filters subpixel beads.
  Lower tiers retain the inexpensive wet finish. Dry surfaces bypass water
  calculations. Ogre's automatic shader clock animates runoff; there are no
  extra meshes, texture resources, draw passes or per-object Lua animation calls.
  Nearby wet High/IBL pixels take one extra lookup in the already-bound
  environment map; dry and distant pixels skip it.
- Cockpit damage preserves panel art, introduces restrained scratches and dims
  emission with a smooth warning pulse. Hull repair eases back to the source.
- Two local hit masks and two native muzzle anchors provide scorch and subtle
  heat. These are presentation only, with no gameplay/network writes.
- Metal destruction pieces share one burnt material per source, at most 128
  variants. Flesh retains its separate material. The bridge runs when resources
  or batches are created, not for each piece every frame.

Runoff uses the upright object's local Y axis and a rigid parent transform.
Banked/articulated models need further visual qualification; this is not fluid
simulation or bone-following damage. Medium/Low and non-HLSL paths do not gain
the detailed water layer. Unsupported APIs or programs retain their source.

Reactive surfaces are DX11 Enhanced only. Stock (Redux) and Retro programs declare
no surface uniforms and compile to the stock output; they keep only the shared
object-position interpolant, because their vertex programs also feed Enhanced
fragments. DX9 (SM3) shaders are frozen at stock: DX9 is fixes-only.

## Validation and remaining work

The Windows/GOG DX11 fixture exposed a real shader-layout defect: global reactive
uniforms generated a `$Globals` buffer alongside the lighting `$Params` buffer.
The retail renderer did not populate that layout correctly, leaving craft black.
All uniforms now occupy the entry-point parameter buffer. Compile validation
checks generated assembly for a second constant buffer, so successful fxc
compilation alone cannot hide this regression.

The isolated Moon fixture loads HD terrain and Very High shadows. GOG live
readback verifies cockpit hull/repair state, engine tower power loss, real
BulletHit masks, native firing mounts and stable GPU-skinned material variants.
Captured visuals and exact remaining acceptance are recorded in
`C:/BZRCoop/reactive-surfaces-live/REVIEW.md` (local evidence, not a shipped file).

Checks: 139 OpenShim CTests; 210 distinct HLSL compilations covering 214 declared
programs; CR's 232 DX11 compilations and preprocessor guards; EXU x86 host checks,
build and hardening checks; CR Lua scheduling/ownership regression and program
references. Visual acceptance, moving/rotating mesh alignment, debris timing,
combat FPS, long sessions, co-op, Steam, Proton and Wine remain separate gates.
