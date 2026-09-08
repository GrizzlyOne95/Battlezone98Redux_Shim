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
| 2 | Insertion point after opaque, before HUD? | **No.** A `RenderQueueListener` works, but Ogre's queue carries only the movable objects. Terrain, cockpit and HUD are drawn outside it, so the boundary cannot be expressed there. |
| 3 | Is stock fog already baked into source colour? | **Yes.** Applied per-pixel in the object shaders. A compositor cannot un-fog; the wake must be an additional near-ground layer. |
| 4 | What breaks | Shadow passes re-enter the same listener and must be filtered — confirmed. Cockpit and HUD are outside the queue system entirely — confirmed by experiment. |
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

## 2. Insertion point — the Ogre queue is the wrong layer

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

That looks like the answer, and it is not. `renderQueueStarted` also hands out
`skipThisInvocation`, so the probe can suppress one group and photograph the
result (`[Diagnostics] SkipRenderQueueGroup`). Suppressing each group in turn
gives:

| Group suppressed | What disappeared |
|---|---|
| 0 (BACKGROUND) | nothing visible |
| **50 (MAIN)** | **the vehicles, and only the vehicles** |
| 60 | nothing identifiable |
| 62 | nothing identifiable |
| 95 (SKIES_LATE) | nothing identifiable |
| 100 (OVERLAY) | nothing — the HUD is still drawn |

With MAIN suppressed the frame still has terrain, the cockpit hull, the sky and
the complete HUD; the scavenger and the fighters are gone. So **Ogre's render
queue carries the movable objects. Redux draws the terrain, the cockpit and the
HUD through its own path**, which is consistent with the HUD surviving a
suppressed overlay queue, and with EXU having had to install an `OverlaySystem`
of its own at mission start rather than finding one.

That makes `renderQueueEnded(50)` "after the units", not "after the opaque
world". Fog composited there would be drawn under the terrain and would leave
the cockpit interior fogged, because neither has been drawn yet at that point,
and neither can be ordered against from inside the queue.

**A RenderQueueListener cannot express the required boundary.** The listener is
still useful — it is a working, ABI-qualified way to run code at known points
inside Ogre's scene render, and it is how this was measured — but item 6's
insertion point is not in this layer. It has to be a hook in Redux's own render
path, or at the D3D11 context level, and neither has been qualified here.

Note also that the group ids are Ogre's standard constants but the *contents* are
not what those names imply, so reasoning from `RENDER_QUEUE_MAIN` /
`RENDER_QUEUE_OVERLAY` semantics would have given the wrong answer. That is why
this was measured rather than read.

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

**Cockpit and HUD are outside the render queue.** Established by the suppression
table in section 2: with every candidate group suppressed in turn, both are still
drawn. The cockpit is still Ogre scene geometry — it hangs off `SceneRoot` as a
sibling node — but it is not reached through the render-queue groups a listener
sees, so a listener cannot order a pass against it.

An earlier attempt at this measurement produced five screenshots of the Windows
lock screen: the session was locked, so `GetForegroundWindow` returned
`Windows Default Lock Screen` while the game window was up and rendering at
(747,396)-(1828,1033). Check the foreground window before trusting a capture; the
run looks successful either way.

The suppression run for group 5 (SKIES_EARLY) landed on the in-game pause menu
and produced no usable frame. Group 5 is therefore untested, and is the one
remaining candidate for the sky.

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
- **The Ogre render queue as the ordering layer.** Measured, not assumed: it
  carries the movable objects only.

## Next step

Item 6 needs a different layer than the one it was looking in. Two candidates,
neither qualified:

1. **A hook in Redux's own render path**, between its terrain/world draw and its
   cockpit and HUD draw. Nothing in this repo currently identifies those call
   sites; finding them is a decompilation job, not an Ogre one.
2. **A D3D11 context-level hook** that detects the transition by what is being
   drawn. Note the standing hazard that the DX11 context vtable is reverted
   mid-frame, so a once-per-frame hook check loses draws in frame order.

Weigh that against the alternative that avoids the insertion point entirely:
pushing clearance into the object shaders as a material parameter. Given
section 1 (no readable depth under MSAA) and section 3 (fog already baked
per-pixel in those same shaders), the material route now avoids all three
obstacles, at the cost of touching every affected material. On this evidence it
is the more likely route to something that renders.
