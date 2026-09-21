# Redux scene/UI render boundary — where a world-only pass can run

Date: 2026-09-21
Scope: stock Redux gameplay render path only. Answers item 1 of the "Next step"
in `Docs/FOG_COMPOSITOR_QUALIFICATION_20260908.md` — *"a hook in Redux's own
render path, between its terrain/world draw and its cockpit and HUD draw.
Nothing in this repo currently identifies those call sites."* This document
identifies them.

Companion to `graphics_options_and_rendering_20260921.md` (options UI, schemes,
shadows, Glow internals), which is not duplicated here.

Provenance key: **Proven** = decompile literal cross-checked against the
shipping image, or on-disk resource text. **Inferred** = consistent
single-source mapping. **Unresolved** = explicitly open, listed in §9.

Image validated against `battlezone98redux.exe` in the GOG install:
5,425,152 bytes, machine 0x014C, ImageBase 0x00400000, `DYNAMIC_BASE` clear,
no `.reloc` — absolute VAs are valid as-loaded. `FUN_*` paths are
`BZ1_Source/Redux/Raw .C` (mismatched PDB; names untrusted, behaviour
verified).

---

## 1. Answer

**`SceneManager::renderQueueStarted(queueGroupId == 100)`, filtered to the main
window viewport**, is the point at which the world scene is complete and the
group-100 HUD layer has not begun. Redux implements that exact callback itself.

Two qualifications that change how the point may be used, both Proven:

1. **Stock Glow runs *after* the HUD, not before it.** There is no stock point
   that is "world complete, Glow complete, HUD not started". The boundary is
   *pre*-Glow.
2. **This is not a "no UI has drawn" point.** Render queue groups 60 and above
   carry screen-space content (identity view + identity projection) and are
   drawn *before* group 100. What occupies them during live gameplay, as
   opposed to shell/menu states, is **Unresolved** — see §9.1. Calling this
   boundary "scene-only" is not yet justified; calling it "before the group-100
   HUD layer" is.

---

## 2. Frame ownership

Redux's renderer identifies itself as **Onyx2015**
(`"Onyx2015 Renderer initialized!"`, `FUN_0067c830`, string at VA 0x008929B0).

`FUN_0044d2a0()` returns `DAT_02CC2BF0`, and `FUN_0067c830` assigns
`DAT_00920EA0 = FUN_0044d2a0()`. They are the same object: the **Onyx2015 view
record**. This resolves §4.1 of the graphics reference, which recorded the
referent as unknown.

| Offset | Contents | Evidence |
|---|---|---|
| `+0x04` | `Ogre::Root*` | `FUN_00682540` `renderOneFrame(*(Root**)(rec+4))` |
| `+0x08` | **`Ogre::SceneManager*`** | `FUN_00664110:489` store after `createSceneManager` |
| `+0x0C` | `Ogre::RenderWindow*` | `addViewport` in `FUN_006658b0` |
| `+0x10` / `+0x14` / `+0x18` | main / target / sniper `Camera*` | `FUN_006850e0` |
| `+0x1C` | **main `Viewport*`** (z-order 0, 0,0,1,1, mask 1) | `FUN_006658b0` |
| `+0x20` | target PiP `Viewport*` (z-order 2, mask 2) | `FUN_00682540` |
| `+0x24` | sniper `Viewport*` on the `SniperTex` RTT (mask 4) | `FUN_00682540` |
| `+0x28` | `Ogre::Log*` | `FUN_0067c830` |
| `+0x2C` | `Ogre::Timer*` | `FUN_006658b0` |
| `+0x40..+0x48` | Glow cache / init flag / listeners | graphics reference §4.2 |

**There is exactly one SceneManager.** `Ogre::Root::createSceneManager` occurs
once tree-wide (`FUN_00664110:485` and its SEH twin `FUN_00664905:305`),
storing to `record+8`. OpenShim already resolves it as
`*(void**)(*(uint8_t**)0x00920EA0 + 0x08)` (`src/patches/bzr_hooks.cpp:2696`).

One gameplay frame:

```text
DoNextFrame                        FUN_00618130
 |                                 ("DoNextFrame: Quiting Game Due to Net Execute failure")
 +- simulation / net / AI
 +- if (render && DAT_008FE240 == 1):
     +- FUN_006175c0 -> FUN_006176a0     BUILD 2D into DynamicGeometry (nothing draws)
     |    +- FUN_00617600   HUD / PDA / mini-HUD        -> groups 100, 50
     |    +- FUN_005dddc0   target PiP  (DynamicTarget)
     |    +- FUN_005d6500   sniper      (DynamicSniper)
     |    +- FUN_00616500   sky / backdrop              -> groups 0, 5
     |    +- FUN_00780c70   cUI-range call, every gameplay frame   [see 9.1]
     +- FUN_00682540   ONYX2015 RENDER FRAME
          +- camera pose / FOV for cameras +0x10/+0x14/+0x18
          +- create-or-destroy viewport +0x20 (target PiP) and +0x24 (sniper RTT)
          +- main viewport mask = (Current_View == 9 ? 0x10 : 1); FUN_00663aa0 re-evaluates Glow
          +- FUN_00687ac0 (queued text); FUN_006854f0 -> FUN_00678cd0 (lock / fill / unlock HW buffers)
          +- ### Ogre::Root::renderOneFrame ###
          +- FUN_006832b8 -> clear DynamicGeometry, reopen for next frame
```

**Build order is not draw order.** Every draw for the frame happens inside the
one `renderOneFrame`, and the render queue group is the only ordering
authority.

---

## 3. Render queue group map (Proven)

| Group | Content | Where the group is set |
|---|---|---|
| 0 | sky / backdrop quad | `FUN_00616500` -> `FUN_00685580(0)` |
| 5 | sky detail (`FUN_00615300`) | `FUN_00616500` -> `FUN_00685580(5)` |
| **10** | opaque world meshes — craft, buildings, **cockpit** | `FUN_0067e6a8:23`, `FUN_00681610:92`, `setRenderQueueGroup(DAT_008ED6A8)`; `[0x008ED6A8] = 10` |
| **40** | terrain clusters | `FUN_007778b0:84` `setRenderQueueGroup(0x28)`; matches `Docs/terrain-render-path.md:113` |
| 50 | world-space 2D sprites / effects | `FUN_00617600` -> `FUN_00685580(0x32)`, `FUN_004d46b0(0x32)` |
| **60 +** | **screen-space** cUI widgets and text (identity view + projection) | `FUN_007d2b70` / `FUN_007d3f20`: `0x3C + FUN_007d3ee0()` (widget nesting depth); `FUN_00686520` / `FUN_00686590`: `DAT_00920C6F + 0x3D` |
| **95** | transparent / fading world meshes | `FUN_00681610:99` `setRenderQueueGroup(DAT_008ED0E4)`; `[0x008ED0E4] = 95` |
| **100** | HUD / PDA / mini-HUD / screen-space sprites | `FUN_00617600` -> `FUN_00685580(100)`; and `FUN_00663800` `cmp eax, 64h` |

`DAT_008ED6A8` and `DAT_008ED0E4` have **no writers tree-wide**; the values
above are their `.data` initialisers read from the shipping image.

Shadow texture passes precede the main queues and re-enter the listener with
`invocation == "SHADOWS"` (observed in `FOG_COMPOSITOR_QUALIFICATION`, §4).

### 3.1 The engine corroborates its own map

`BZ_ASSETS_CORE\common\programs\glow.compositor`, the only `.compositor` on
disk, re-renders the scene for its mask with:

```text
target glowMap
{
    material_scheme glow
    shadows off
    visibility_mask 1
    pass render_scene { first_render_queue 10   last_render_queue 90 }
}
```

`10..90` brackets world content exactly and deliberately excludes sky (0, 5),
transparent objects (95) and the HUD (100). It does **not** exclude 60+, which
is part of why §9.1 matters.

### 3.2 How 2D reaches the queue

`FUN_006850e0` creates three `DynamicGeometry` MovableObjects, each attached to
its own SceneNode under the root and registered as a `Camera::Listener`
(`Camera` vtable `+0x20C`, subobject `DG+0xD4`):

| Global | Name | Visibility flags | Camera | Matching viewport |
|---|---|---|---|---|
| `DAT_02B3F014` | `DynamicMain` | `0x11` | `rec+0x10` | `rec+0x1C` (mask 1 / 0x10) |
| `DAT_02B79B30` | `DynamicTarget` | `2` | `rec+0x14` | `rec+0x20` (mask 2) |
| `DAT_02B79B28` | `DynamicSniper` | `4` | `rec+0x18` | `rec+0x24` (mask 4) |

`DAT_02B79B34` is the *current* bucket; `FUN_00684ed0` / `FUN_00684f10` /
`FUN_00684f50` switch it.

Its vtable is `0x008926A8`. Three slots matter:

| Slot | VA of slot | Target | Meaning |
|---|---|---|---|
| `+0x80` | `0x00892728` | `FUN_00679570` | `Ogre::MovableObject::_updateRenderQueue` |
| `+0xA8` | `0x00892750` | `0x0082B396` | `Ogre::MovableObject::setRenderQueueGroup` |
| `+0xB0` | `0x00892758` | `0x0082B38A` | `Ogre::MovableObject::getRenderQueueGroup` |

So `FUN_00685580(g)` is nothing but a group cursor on the current bucket, and
`FUN_00679ac0` stamps `renderable[0xAC] = DG->getRenderQueueGroup()` when a
batch opens; `FUN_00679570` later replays it as
`RenderQueue::addRenderable(rend, rend[0xAC])`. Screen-space batches are
marked by `Renderable::setUseIdentityView(true)` +
`setUseIdentityProjection(true)` (`FUN_00685620` -> `FUN_00684c60` /
`FUN_00684c80`).

**Correction to existing repo material:** slot `0x00892728`, which OpenShim
already hooks, is `DynamicGeometry::_updateRenderQueue` — not
"World::UpdateRenderQueue".

---

## 4. The boundary is stock-owned

`FUN_00663800` is slot 3 (`renderQueueStarted`) of the Glow RTListener's
`RenderQueueListener` vtable at `0x00892260`; the slot itself is at
`0x0089226C`. Its opening bytes in the shipping image:

```text
00663800: 55 8B EC 83 EC 18 89 4D E8      push ebp; mov ebp,esp; sub esp,18h; mov [ebp-18h],ecx
          0F B6 45 08                     movzx eax, byte ptr [ebp+8]     ; queueGroupId
          83 F8 64                        cmp   eax, 64h                  ; == 100
          0F 85 BE 00 00 00               jne   <return>
```

Body:

```c
vp = renderSystem->_getViewport();                       /* RS vtable +0x11C */
sm = vp->getCamera()->getSceneManager();
if (vp->getOverlaysEnabled() || sm->_getCurrentRenderStage() == IRS_RENDER_TO_TEXTURE)
     *skipThisInvocation = false;
else *skipThisInvocation = true;          /* HUD excluded from overlay-disabled targets */
if (!*skipThisInvocation
    && FUN_0044d2a0()->viewport[+0x1C] == vp
    && (dg = DAT_02B3F014 /*DynamicMain*/) != 0)
     dg->_updateRenderQueue(sm->getRenderQueue());       /* vtable +0x80 */
```

The literal `0x64` is the engine naming its own world/HUD seam. Group 100 is
where the HUD is submitted, gated and skipped.

### 4.1 Stock listener inventory

| Listener | Registration | Overridden slots |
|---|---|---|
| **Glow RTListener** `FUN_00663210` | `CompositorInstance::addListener`; `RenderTarget::addListener` on `glowMap` (`+0x70`); `SceneManager::addRenderQueueListener` (SM vtable `+0x320`; remove is `+0x324`, proven by `FUN_004fa2a0`) | `renderQueueStarted` = `FUN_00663800`; `preViewportUpdate` = `FUN_00663740`; `postViewportUpdate` = `FUN_006637A0`; `notifyMaterialSetup` / `notifyMaterialRender` = `FUN_006635D0` / `FUN_006635A0`. `preRenderQueues`, `postRenderQueues`, `renderQueueEnded`, `preRenderTargetUpdate`, `postRenderTargetUpdate` are **base stubs**. |
| **LensFlare** `FUN_004f9140` | `SceneManager::addRenderQueueListener` via `FUN_004f9430`; RQ subobject at `this+0x28`, vtable `0x0087B894` | `postRenderQueues` = `FUN_004FA1A0` (pulls two `HardwareOcclusionQuery` results). `renderQueueStarted` and `renderQueueEnded` are the same empty `ret` at `0x004FA190`. |

`FUN_00663740` / `FUN_006637A0` identify the Glow mask pass by
`Viewport::getMaterialScheme() == "glow"` (string at `0x00892124`, immediately
followed by `"glowMap"`), saving and restoring `getShadowsEnabled`. That string
comparison is the stock-verified way to tell the mask re-render apart from the
main scene render — the two are otherwise indistinguishable by invocation,
because a compositor `render_scene` pass fires the default (empty) invocation.

### 4.2 Two hazards

1. **`FUN_00663800` writes `*skipThisInvocation` unconditionally.** Ogre calls
   listeners in registration order sharing one `bool&`. The stock listener is
   registered at view setup (`FUN_006658b0` -> `FUN_00663aa0`), so a listener
   registered later wins — and one registered earlier has its decision silently
   discarded at group 100 and nowhere else.
2. **The HUD is submitted *inside* that callback**, not during visibility
   gathering. Anything that inspects group-100 contents before the stock
   listener has run will see an empty group.

---

## 5. Candidate boundaries

"Group-100 HUD not started" is the honest column heading. Read §9.1 before
treating any row as "no UI drawn".

| # | Candidate | Function / address | World complete? | Glow complete? | Cockpit included? | Group-100 HUD not started? | Confidence |
|---|---|---|---|---|---|---|---|
| 1 | **`renderQueueStarted(100)`**, filtered to `vp == *(Viewport**)(0x00920EA0 + 0x1C)` and default invocation | listener slot `0x0089226C`; stock impl `FUN_00663800` | Yes (0–95) | **No** | Yes (group 10) | **Yes** | **High** |
| 2 | `renderQueueEnded(95)` | slot `0x00892270` | Yes | No | Yes | Yes | Medium — group 95 is empty when nothing is fading, so it may not fire |
| 3 | `renderQueueEnded(40)` (post-terrain) | — | No — misses 50 and 95 | No | Yes | Yes | Low |
| 4 | `postRenderQueues` | slot `0x00892268`; stock user `FUN_004FA1A0` | Yes | No | Yes | **No** | High (fires) / unusable for this purpose |
| 5 | `Camera::Listener::cameraPostRenderScene` | `Camera` vtable `+0x20C`, subobject `DG+0xD4` | Yes | No | Yes | No | High / unusable |
| 6 | `RenderTargetListener::postViewportUpdate` on the window, `vp == +0x1C` | stock pattern `FUN_006637A0` | Yes | **Yes** | Yes | No | High / post-HUD |
| 7 | Compositor `Glow` `notifyMaterialSetup` / `notifyMaterialRender` | `FUN_006635D0` / `FUN_006635A0` | n/a | n/a | n/a | n/a | Dead when Screen Glow is off |
| 8 | `IDXGISwapChain::Present` (today's FXAA) | `src/patches/dx11_enhanced_fxaa.cpp` | Yes | Yes | Yes | **No** | High / too late |
| 9 | `DynamicGeometry::_updateRenderQueue` (OpenShim's existing main-thread hook) | vtable slot `0x00892728` -> `FUN_00679570` | No — submission, pre-draw | No | No | Yes | High / too early |

Not candidates: a second viewport, or a second compositor.
`addCompositor` / `setCompositorEnabled` occur only in `FUN_00663aa0`, nothing
ever removes one, and adding a chain changes the target topology instead of
providing an ordering point.

---

## 6. What has and has not rendered at candidate 1

**Rendered:** sky and backdrop (0, 5); all opaque world meshes including the
cockpit (10); the full terrain (40); world-space sprites and effects (50);
**screen-space cUI widgets and text in groups 60+, whatever they are in this
state (§9.1)**; transparent and fading world meshes (95); all stock shadow
texture passes.

**Not rendered:** the HUD, PDA, mini-HUD and screen-space sprites of group 100;
the entire stock Glow compositor (downsample, blurV, blurH, combine all run
after the scene render completes); the target PiP viewport (z-order 2);
Present.

### 6.1 Cockpit

The cockpit is ordinary world scene geometry, not a separate phase.
`FUN_0067f599` resolves `"%.16s_cockpit.mesh"` and hands it to `FUN_0067e5a0`
-> `FUN_0067e6a8`, the same entity-creation path every craft mesh uses, which
does `setCastShadows(false)` then `setRenderQueueGroup(DAT_008ED6A8 /*10*/)`.
A world-only pass at candidate 1 therefore **includes** the cockpit. If that is
not wanted, it has to be excluded by some means other than render order —
`BZBaseCockpit` is the only material file with `receive_shadows off` and maps
every scheme to `*NoShadow`, so a scheme- or material-based discriminator
exists.

---

## 7. State snapshot at candidate 1

| Property | Screen Glow **OFF** | Screen Glow **ON** |
|---|---|---|
| Active colour target | swapchain backbuffer | compositor texture **`rt_output`**, `PF_R8G8B8`, `target_width` x `target_height` |
| Active depth target | window depth-stencil; `R32_TYPELESS` with `D3D11_BIND_DEPTH_STENCIL` only under MSAA (`FOG_COMPOSITOR_QUALIFICATION` §1) | the compositor RTT's depth buffer |
| Viewport | `rec+0x1C`, z-order 0, full 0,0,1,1, background black, overlays **enabled**, autoUpdated | same |
| Visibility mask | `1` normally, `0x10` in editor (`Current_View == 9`) | `1` — Glow's three-way AND requires it |
| Material scheme | `{high,medium,low,lowest}` x `{-pssm, plain, -noshadow}` per `FUN_00680fe0` | same. **Not** `glow`; that belongs to the separate mask pass |
| MSAA | **Still unresolved at this point.** This install runs `FSAA=8` | `rt_output` inherits the main target's FSAA (`CompositionTechnique::TextureDefinition::fsaa` defaults true and the script carries no `no_fsaa`) — *Inferred*, must be confirmed live |
| Glow composited? | n/a | **No** |
| Is it the backbuffer? | Yes | **No** |

The consequential line: **the identity of the active colour target changes with
a user-facing graphics setting.** Any pass here must discover its target at
runtime rather than assume the swapchain.

The second consequential line: nothing has been resolved yet. FXAA-class AA
expects a resolved LDR image, so a pass at this point needs
resolve -> process -> write back into the MSAA target, and that write-back is
resolved again at Present.

---

## 8. Variant and failure cases

| View / state | `Current_View` (`DAT_008EAAD8`) | Status |
|---|---|---|
| Cockpit / external / chase | 0, 1, 2, 7 | **Valid.** |
| Satellite | 3 | **Valid structurally.** Sky build skipped in favour of `FUN_0067cb10(0,0,0)`; HUD still at 100; mask stays 1 so Glow can be on. |
| Editor | 9 | **Valid structurally.** Main viewport mask flips to `0x10`, so Glow self-disables and `FUN_004f95d0` bails out of the lens flare. |
| Mode 10 | 10 | HUD build partially skipped, lens flare off. Untyped — verify live. |
| **Sniper / scope** | — | **Excluded by stock.** Rendered into the `SniperTex` RTT through viewport `+0x24`, created with `setOverlaysEnabled(false)`, so `FUN_00663800` sets `skip = true` at group 100 there. A hook must filter on `vp == rec+0x1C` exactly as stock does. |
| **Target PiP** | — | Viewport `+0x20`, z-order **2**, mask 2, `clearEveryFrame(true, FBT_DEPTH)`, scheme `low-noshadow`. Renders **after** the main viewport, therefore after any pass at candidate 1 and after Glow. |
| **Glow mask pass** | — | Fires the same callbacks with the same default invocation but never reaches group 100, so it cannot trip a group-100 hook. Stock's discriminator is `Viewport::getMaterialScheme() == "glow"`. |
| **Shadow passes** | — | Re-enter with `invocation == "SHADOWS"`. Must be filtered. |
| **Shell / UI View** | `DAT_008FE240 == 4` | `DoNextFrame` does not render; the UI frame runs through `FUN_00684ce0(1)`. "World complete" is meaningless. Gate on `DAT_008FE240 == 1`. |
| **Modal overlay** | `DAT_008FE240 == 2` | No world render. |
| **Vehicle preview** | — | Separate viewport path (`FUN_007a9590`). Out of scope. |
| **HUD switched off by the player** | profile `+0x1A0` | If group 100 is never created in the `RenderQueue`, the callback may never fire. Needs a fallback latch. |

---

## 9. Unresolved

### 9.1 Classify render queue groups 60 and above — blocking for any "scene-only" claim

Groups 60+ carry **screen-space** renderables. Two producers are identified:

- cUI widgets are Ogre `ManualObject`s created in `FUN_007d2b70` with
  `setUseIdentityView(true)` + `setUseIdentityProjection(true)` and
  `setRenderQueueGroup(0x3C + FUN_007d3ee0())`, where `FUN_007d3ee0` returns
  the widget's nesting depth (recursive: parent depth + own `+0xE8`).
  `FUN_007d3f20` applies the same formula from roughly 60 cUI call sites
  spanning `0x0078xxxx` to `0x007Dxxxx`.
- `FUN_00686520` / `FUN_00686590` emit screen-space DynamicGeometry text at
  `DAT_00920C6F + 0x3D`. `DAT_00920C6F` is written per text entry by
  `FUN_00687ac0` from `(&DAT_02B7A4B0)[i * 0x97C]`, and is zeroed at the top of
  `FUN_00682540`.

The open question is **which, if any, of that is live during normal gameplay**
rather than only in shell and menu states. Two specific threads to pull:

- `FUN_006176a0` calls `FUN_00780c70(view)` on every gameplay frame, and
  `0x00780C70` sits inside the cUI address range. What it submits, and into
  which group, is unknown.
- The fog trace observed groups **60 and 62** in what was described as steady
  gameplay. `DAT_00920C6F + 0x3D` yields 62 for `DAT_00920C6F == 1` and 60 for
  `-1`, so both could be DynamicGeometry text layers — but one of them being a
  live cUI widget is not excluded.

Until this is closed, a pass at candidate 1 must be described as running
**before the group-100 HUD layer**. It must not be described as "scene-only",
as "world-only", or as "before any UI".

### 9.2 Possible double submission of `DynamicMain`

`FUN_00684f90` attaches every `DynamicGeometry` to a SceneNode under the root,
so `_updateRenderQueue` should fire during `_findVisibleObjects`; yet
`FUN_00663800` calls it again at group 100. Statically both paths appear to
run, which would duplicate renderables. Neither the guard `FUN_006796b0()`
(`this+0x2D`) nor `this+0xD8` closes it on inspection. This must be measured,
not reasoned about.

### 9.3 Contradiction with the fog qualification

`Docs/FOG_COMPOSITOR_QUALIFICATION_20260908.md` §2 reports that suppressing
group 100 removed nothing and *"the HUD is still drawn"*. Under this decompile
that cannot be right: group 100 **is** the HUD. The same run had documented
capture failures (a locked session producing lock-screen screenshots; the
group-5 run landing on the pause menu). That table also lists no group 10 and
no group 40, although this document shows world meshes at 10 and terrain at 40,
which suggests the trace was not captured in a live gameplay frame at all.

§4.2 above also gives a mechanism by which a suppression attempt can be
silently defeated: if OpenShim's listener were registered *before* the stock
one, `FUN_00663800` would overwrite `*skipThisInvocation` at group 100 and only
at group 100 — which is exactly the observed shape of the anomaly.

**Re-run protocol.** Log the registration order relative to the stock listener;
filter to `vp == rec+0x1C` and the default invocation; log `*skip` on both
entry and exit of the handler; verify the game window is foreground; capture in
live play, not paused.

### 9.4 Other open items

- `rt_output` and `glowMap` FSAA inheritance is Inferred from the Ogre 1.10
  header default, not observed.
- `DAT_008EAAD8` values 4, 10 and 0x0C are unnamed.
- `DAT_00920EE8`, whose `setVisibilityFlags` is driven `0` / `1` by
  `FUN_006864f0` from `FUN_00682540`, is unidentified.

---

## 10. Next milestone — instrumentation only

Deliberately smaller than a feature. The question to answer is only:

> Can OpenShim capture, process and write the world image at render queue
> group 100, and then let Redux continue rendering the HUD?

Scope:

1. Attach a `RenderQueueListener` and instrument `renderQueueStarted(100)`
   filtered to `vp == *(Viewport**)(0x00920EA0 + 0x1C)`, default invocation,
   `DAT_008FE240 == 1`. Log registration order relative to the stock listener,
   and `*skipThisInvocation` on both entry and exit.
2. At that point, report the active colour render target: `ID3D11Texture2D*`
   identity, dimensions, `DXGI_FORMAT`, `SampleDesc.Count` and quality, bind
   flags, and whether it is the swapchain backbuffer or an intermediate.
   Matrix: Screen Glow off/on x FSAA 0 / 2 / 4 / 8.
3. Perform a **diagnostic resolve or copy only** — no shading, no AA — with the
   full state-preservation discipline of `src/patches/dx11_enhanced_fxaa.cpp`.
4. Prove the HUD still renders afterwards, and that the stock Glow result is
   still correct with Glow on.
5. While the probe is in place, close §9.1 by logging the group ids and
   renderable counts actually seen in live gameplay, and close §9.2 by counting
   how many times `DynamicMain::_updateRenderQueue` runs per frame.

Explicitly **not** in this milestone: SMAA, FXAA relocation, any change to the
existing Present-time pass, and any change to stock BZR shaders or materials.

If steps 3 and 4 both pass, scene-only FXAA stops being speculative and becomes
a relocation of the existing pass.
