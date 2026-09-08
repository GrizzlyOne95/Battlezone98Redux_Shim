# Fog compositor qualification (2026-09-08)

Contract item 6 of [INTERACTIVE_FOG_WAKES.md](INTERACTIVE_FOG_WAKES.md): *qualify
a scene-depth source and a pass before HUD/cockpit overlays.*

This is an investigation, not an implementation. Nothing here renders. Every
verdict below says what it rests on, and the two questions that are **not**
settled say so.

Target: GOG Battlezone 98 Redux 2.2.301, D3D11 backend, `RenderSystem_Direct3D11.dll`.

## Summary

| # | Question | Verdict |
|---|----------|---------|
| 1 | Scene depth readable? | **No, as shipped.** Ogre creates no depth SRV when MSAA is on, and this install runs FSAA=8. Fixable, but it is a precondition, not a detail. |
| 2 | Insertion point after opaque, before HUD? | **Yes — qualified.** A `RenderQueueListener` works on the shipped OgreMain and exposes boundaries at queue groups 60, 62, 95 and 100, all after MAIN (50). |
| 3 | Is stock fog already baked into source colour? | **Yes.** Applied per-pixel in the object shaders. A compositor cannot un-fog; the wake must be an additional near-ground layer. |
| 4 | What breaks | Shadow passes re-enter the same listener and must be filtered — confirmed. Cockpit/transparent group membership **not identified** (blocked, see below). |
| 5 | DX9 | **Out of scope.** Ogre 1.10's D3D9 backend has no depth-as-texture path at all. |

---

## 1. Scene depth source — not available as shipped

`D3D11RenderSystem::_createDepthBufferFor` picks the depth format and bind flags:

```cpp
descDepth.Format    = DXGI_FORMAT_R32_TYPELESS;      // feature level >= 10.0
descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
if (!mReadBackAsTexture && mFeatureLevel >= D3D_FEATURE_LEVEL_10_0
    && BBDesc.SampleDesc.Count == 1)
    descDepth.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
```

The format is typeless, which is the hard part — a typeless resource can carry
both a `D32_FLOAT` DSV and an `R32_FLOAT` SRV. So the design is *capable* of
handing out scene depth. Three conditions gate it, and one fails here:

- `mFeatureLevel >= 10.0` — satisfied (`Max Requested Feature Levels = 11.0`).
- `!mReadBackAsTexture` — satisfied by default; it is a per-material stencil
  parameter, not a config option, and resets to `false`.
- `BBDesc.SampleDesc.Count == 1` — **fails.** This install runs FSAA 8.

Evidence it is the shipped code and not just upstream: the error string
`"Unable to create the view of the depth texture"` is present in the shipped
`RenderSystem_Direct3D11.dll`, alongside `"D3D11RenderSystem::_createDepthBufferFor"`.

Evidence MSAA is live, from `logs/BZOgreLogfile.log`:

```
D3D11: RenderSystem Option: FSAA = 8
D3D11RenderSystem::_createRenderWindow "Battlezone 98 Redux (2.2.301) DX11",
    3840x2160 fullscreen  miscParams: FSAA=8 ...
```

So with the shipped defaults **no depth SRV is created at all**, and the depth
texture cannot be bound as one even if we found it.

Two further constraints that survive even at FSAA=0:

- The SRV is stored in a single render-system member, `mDSTResView`, not per
  depth buffer. Every render target that creates a depth buffer overwrites it —
  shadow maps, RTTs, the satellite view. "The depth SRV" is whichever was
  created last, not necessarily the main scene's.
- The DSV is created with `descDSV.Flags = 0` and an upstream TODO noting that
  read-only depth is what would allow *"bind depth buffer as depth view AND
  texture simultaneously"*. D3D11 will not let a resource be a writable DSV and
  an SRV at once, so a pass that samples depth must run with the DSV unbound,
  and cannot depth-test against the buffer it reads.

**Consequence.** Interactive fog on DX11 needs one of:
(a) FSAA=0, accepting the visual cost and that it silently disables the feature
otherwise; (b) intercepting `CreateTexture2D` to force a non-MSAA, SRV-capable
depth path, which changes the engine's rendering; or (c) a depth pre-pass of our
own into a texture we own. (c) is the only option that does not fight the
engine, and it costs a full scene re-draw.

*Not verified live:* a `CreateTexture2D` hook logging actual depth descs. The
source path is confirmed present in the shipped binary and the MSAA count is
confirmed from the engine's own log, so the conclusion follows, but the direct
observation has not been made.

## 2. Insertion point — qualified

Neither render hook OpenShim already owns is usable:

- the world `_updateRenderQueue` hook runs during visibility gathering, **before
  any draw**;
- the Enhanced FXAA pass runs *"immediately before Present"* — after everything,
  HUD included.

That is what the design doc meant by existing hooks being references, not proof.

A third point does exist. `?addRenderQueueListener@SceneManager@Ogre@@UAEXPAVRenderQueueListener@2@@Z`
is exported, and a listener attaches and runs correctly on the shipped OgreMain.
`src/patches/render_queue_trace.cpp` implements one with a **hand-built vtable**
rather than by inheriting from the repo's copy of the 1.10 header, so the ABI
assumption is explicit and each slot reports its own index. It reads cleanly,
which qualifies the interface as well as the insertion point.

Observed sequence, one camera, steady state:

```
preRenderQueues
  queueStarted/Ended group=0    (BACKGROUND)
  queueStarted/Ended group=5    (SKIES_EARLY)
  queueStarted/Ended group=50   (MAIN)
  queueStarted/Ended group=60
  queueStarted/Ended group=62
  queueStarted/Ended group=95   (SKIES_LATE)
  queueStarted/Ended group=100  (OVERLAY)
postRenderQueues
```

So there are **four boundaries after the opaque world and before the overlay
queue**. `renderQueueEnded(50)` is the natural candidate: opaque geometry is
resolved, and groups 60/62/95/100 have not run.

`renderQueueStarted` also hands out `skipThisInvocation`, which makes it possible
to suppress a group and see what disappears — the probe supports this via
`[Diagnostics] SkipRenderQueueGroup`.

## 3. Stock fog is already baked in

Applied per-pixel in the object shaders, not as a post-process. From
`CR_base.hlsl`:

```hlsl
float fogValue = saturate((vDepth - fogParams.y) * fogParams.w);
oColor.xyz = lerp(oColor.xyz, fogColour.xyz, fogValue);
```

and the shim already reads the matching engine state through
`getFogColour` / `getFogStart` / `getFogEnd` / `getFogDensity` on `SceneManager`.

By the time any post-opaque pass runs, distant geometry has **already** been
lerped toward the fog colour. A compositor therefore cannot *remove* fog — the
original colour is gone — so "vehicles clear a trail through the fog" cannot be
implemented by reducing stock fog from a later pass.

This does not sink the feature, but it does fix its shape. The wake has to be an
**additional near-ground layer** composited on top, with `(1 - clearance)` driving
its density, which is what the design doc's item 5 already describes. Stock fog
stays as distance haze. The two will stack, so `fogStart` likely needs raising so
the near layer is not applied on top of a curve that already darkened the same
pixels. Alternatively the clearance field could be pushed into the object shaders
as a parameter, which is a material change rather than a compositor and sidesteps
both this and the depth problem — worth weighing before committing to item 6.

## 4. What breaks

**Shadow passes re-enter the listener.** Confirmed: from the third frame on,
every group is announced twice per frame, once with an empty invocation and once
with `SHADOWS`:

```
frame=2 step=4 queueStarted group=50 invocation=SHADOWS
```

A pass that does not filter on invocation would composite into shadow render
targets. The probe already filters, and any real pass must.

**Cockpit and transparents: not identified.** The plan was to suppress groups 60,
62, 95 and 100 in turn and photograph the result. Five runs were made and all
five screenshots captured the Windows lock screen: the session was locked, so
`GetForegroundWindow` returned `Windows Default Lock Screen` while the game
window was up and rendering at (747,396)-(1828,1033). No pixels could be
obtained. The probe and the `SkipRenderQueueGroup` key are in place, so this is
one run on an unlocked session away from an answer.

This matters because the cockpit is scene geometry, not an overlay — it hangs off
`SceneRoot` as a sibling node — so it is drawn in one of these queue groups and
would be fogged by a pass inserted before it. Which group it is decides whether
`renderQueueEnded(50)` is actually the right boundary or whether the pass has to
go later.

**Alternate cameras** (satellite, sniper scope) were not exercised. The trace
showed a single `preRenderQueues`/`postRenderQueues` pair per frame in normal
play, so a second viewport would appear as an extra pair — worth confirming while
the probe is in place, since a pass must run per relevant camera and not on the
satellite view.

## 5. DX9 — out of scope

Ogre 1.10's D3D9 backend has no depth-as-texture path: `RenderSystems/Direct3D9`
contains no `INTZ`, `RAWZ` or depth-texture handling of any kind. Reading scene
depth there would need a vendor-specific format hack implemented from scratch in
the render system.

The D3D9 plugin is installed and selectable (`logs/BZOgreLogfile.log`:
`Installing plugin: D3D9 RenderSystem`), and this install runs D3D11
(`Render System=Direct3D11 Rendering Subsystem`). OpenShim's only existing DX
post-process watches `RenderSystem_Direct3D11.dll` and states outright that DX9 is
untouched.

Recommendation: fog stays D3D11-only and fails closed on D3D9, as the design doc
already requires.

---

## What was ruled out

- **The Enhanced FXAA insertion point.** It is a working fullscreen-pass pattern
  worth copying — MSAA resolve into an owned texture, draw, and a `SavedContextState`
  RAII that restores every mutated piece of context state — but it runs before
  Present, after the HUD. Not usable for fog.
- **The world `_updateRenderQueue` hook.** Submission stage, before any draw.
- **Removing fog from a later pass.** Impossible: the original un-fogged colour
  does not survive the object shaders.

## Next step

One run on an unlocked session with `[Diagnostics] TraceRenderQueues = 1` and
`SkipRenderQueueGroup` set to 60, then 62, then 95, then 100, comparing frames.
That identifies the cockpit's group and settles whether `renderQueueEnded(50)` is
the boundary to use.

After that, the decision to make is item 6's shape: a compositor layer that must
solve the depth problem (section 1) and stack with baked fog (section 3), versus
pushing clearance into the object shaders as a material parameter, which avoids
both but touches every affected material.
