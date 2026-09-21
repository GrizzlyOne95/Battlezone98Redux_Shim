# Redux Graphics — Consolidated RE Reference (stock UI, schemes, shadows, Glow)

Date: 2026-09-21
Scope: stock Redux graphics only — options UI screen, what each control toggles
and when, shadow/material-scheme primitive `FUN_00680fe0`, Glow compositor
pipeline (`FUN_0044d2a0` / `FUN_00663aa0` + listeners), material-scheme
architecture, view-mode `DAT_008fe240`, per-view record, sibling-compositor
survey. Legacy 1.5 material is baseline context only. OpenShim/EXU appear
solely in the appendix.

Provenance key used throughout: **Proven** = literal decomp bytes or on-disk
resource text. **Inferred** = consistent single-source mapping. **Unresolved**
= explicitly open. `FUN_*` paths are `BZ1_Source/Redux/Raw .C` (mismatched
PDB — names untrusted, behavior verified). Game-data paths are the GOG
install. Line numbers are physical file lines unless noted.

Related docs (not duplicated here): `renderer_startup_backend_selection_20260825.md`
(backend ladder, `Ogre.cfg`, cmdline), `save_load_format_20260921.md`
(save/load + autosave comparison).

## 1. Legacy 1.5 graphics dialog (baseline)

`BZ1_Source/1.5/functions/0057/0057406b_GraphicOptionsDlgProc.c`
(`bitmap\goptions.bmp`). Nine `OptionBox` rows + brightness scrollbar; Back
persists via `SaveUserProfile()`. Message: restart required for most changes.

| Row | Items | Field `graphicDetail.*` | Effect |
|---|---|---|---|
| 3D CARD | off/on | `hardware` | Software vs hardware rasterizer. Rebuilds res list (`read_video_mode(box,1)`, `00572ade`), forces `lineskip=0` + disables its button when on. Backend via `Device_Graphic_Init / Device_Set_Graphic_Mode` |
| SCREEN RESOLUTION | `"%dx%d"` per mode | `resolution` | Index into mode table filtered by `hardware`. Restart-applied; also fonts, menu thresholds, `ExitMainMenu` re-init |
| MONITOR BRIGHTNESS | scrollbar | `brightness` | Live. `brightness+1` → `ApplyGammaToPalette/QuadPalette`; `D3D_Flush_Texture_Cache()` on scroll |
| LINE SKIP | off/on | `lineskip` | Software scanline skip; disabled under hardware |
| SKY DETAIL | flat/smooth/textured/full | `clouds` | Sky/cloud path |
| TERRAIN DETAIL | flat/smooth/lowRes/hiRes | `terrain` | `SetTerrainPrefs`, `Terrain_Create(1,terrain,5.0)`, texture-state quality |
| OBJECT DETAIL | flat/mixed/textured/hiRes | `objDetail` | LOD flags in `ComputeRenderQuality` + z-sort threshold; read via `UserPref_objectDetail()` |
| COCKPIT DETAIL | off/solid/textured | `cockpit` | Cockpit render gate + LOD flags |
| SHADOW DETAIL | off/on (clamped 0/1) | `shadow` | Shadow-skip bit in `ComputeRenderQuality`; `CastBuildingShadow` gate; read via `UserPref_shadow()` |

Defaults: `GetMachineDefaults() = GraphicDefaults[3]` (`0054bc65`).

## 2. Redux stock graphics screen

Builder `FUN_007af4a0` (string-proven labels from the `graphic_options`
table); Apply handler `FUN_007aebc0`; renderer switch `FUN_007af170`.

### 2.1 Controls (Proven — label keys + widget names + value sources)

| Label key | Checklist widget | Values from | Profile byte |
|---|---|---|---|
| `monitor` | `adapterChecklist` (`:619`) | RS option `Rendering Device` vector | staged `+0x19d` |
| `screen_resolution` | `resChecklist` (`:835`) | RS `Video Mode`, skip `16-bit`, keep w>1023 && h>719 | staged `+0x19c/+0x1a0` |
| `anisotropic` | `anisoChecklist` (`:955`) | hardcoded Off + 1/2/4/8 | `+0x24`, live |
| `fullscreen` | `screenChecklist` (`:1067`) | RS `Full Screen` vector | staged `+0x19e` |
| `vehicle_shadows` | `vehicleChecklist` (`:1159`) | `FUN_007ae5b0`: Off + tiers (medium/very_high/ultra…), gated by `DAT_008f0684` | `+0x25`, live |
| (hud) | `hudChecklist` (`:1217`) | `option_box/display_hud` | staged `+0x1a0` |
| (mini-hud) | `mHudOnOffChecklist` (`:1281`) | on/off | global `DAT_008eaab0`, immediate |
| (FSAA option block) | `fsaaChecklist` (`:1365`) | RS FSAA-option vector | staged `+0x19f` |
| `detail` | `detailChecklist` (`:1479`) | `FUN_007ae5b0`: `detail_level` tiers incl. `very_low`, gated by `DAT_009455a8` | `+0x27`, live |
| `cockpit_display` | `cockpitChecklist` (`:1547`) | 3 fixed localized strings, ids 0/1/2 | `+0x17`, live |
| `screen_glow` | `glowChecklist` (`:1615`) | Off/On | `+0x28`, live |
| `shader` | `shaderChecklist` (`:1681`) | `getAvailableRenderers()` names | staged `+0x1a1` |
| `terrain_dist` | label only (`:465`) | no widget traced | — (gap, not absence-proof) |

Ogre options are read/written through the RenderSystem vtable (`+0xC` get,
`+0x10` set); game-side bytes live at `DAT_0094672c+offset`. The legacy
brightness scrollbar is gone — no `Brightness/Gamma` literals anywhere in the
options address range (Proven negative).

### 2.2 When things apply (Proven)

- **Live on click**: aniso (`+ MaterialManager::setDefaultAnisotropy`),
  vehicle shadows, detail level (both + `FUN_00680fe0()`), cockpit, glow
  (+ `FUN_0044d2a0()` + `FUN_00663aa0()`), mini-HUD global.
- **Staged flags → Apply button** (`Apply` → `FUN_007ae810` → `FUN_007aebc0`),
  three coarse groups (flags are group gates, not per-action selectors):
  - **A** (`+0x19e/+0x19c/+0x1a0`): set RS `Full Screen` + `Video Mode`, write
    `+0x26`, `FUN_00683620(1,1)` ("Updating Window mode via clicking apply").
    No restart prompt — window rebuilt live.
  - **B** (`+0x19f/+0x19d`): set RS `Rendering Device` + FSAA option,
    `saveConfig()`, `restart_required` alert.
  - **C** (`+0x1a1`): store chosen RS in `DAT_009455ac`, restart alert; the
    real switch is deferred to `FUN_007af170` (`setRenderSystem` +
    `saveConfig` + `Exiting Game from graphics options changing renderer` +
    `exit(0)`).
- Live vehicle/detail writes snapshot priors to `DAT_0260baac/baa8` and arm a
  `DAT_009455b0/b4 = FUN_00822ea0()+20000` deadline; reconciler `FUN_007ae480`
  (flush path, per-frame deadline path clearing the timer, ESC path) restores
  or stamps fallback tiers and re-invokes `FUN_00680fe0()` (mechanism Proven;
  exact branch trigger mapping Medium-Low — preserved literally, see §3.5).

## 3. `FUN_00680fe0()` — shadow + material-scheme re-apply (Proven)

Reads profile `+0x25` (vehicle tier, clamped high to 4) and `+0x27` (detail)
on every call; touches nothing else.

```c
tier = profile+0x25; sm = SceneManager;
if (tier < 0) sm->vft(+0x3c0)(1,1,0x21,0,0);
else if (nonPSSMtier) {
  sm->vft(+0x3c0)(sizeTable[tier],1,0x21,0,1);
  sm->vft(+0x394)(128.0f); sm->vft(+0x3c8)(0.8f); sm->vft(+0x38c)(192.0f);
  sm->setShadowTextureCountPerLightType(1,1);
  sm->setShadowCameraSetup(SharedPtr(new DefaultShadowCameraSetup()));
} else {
  sm->vft(+0x3c0)(sizeTable[tier],3,0x21,0,1);  // 3 = PSSM split count
  ...same three floats...;
  sm->setShadowTextureCountPerLightType(1,3);
  pssm = new PSSMShadowCameraSetup();
  pssm->vft(+0x10)(1); pssm->setUseAggressiveFocusRegion(true);
  pssm->vft(+0x18)(*FUN_0044c7a0(0));
  pssm->setSplitPoints({0.1,16,64,256});        // via 00683ab0/00416430/00683a00/00683ad0
  pssm->setOptimalAdjustFactor(0..2, 0.0);
  sm->setShadowCameraSetup(SharedPtr(pssm));
}
win = Root::getAutoCreatedWindow();
if (win && win->viewports)                       // self-skips without a window
  for each viewport: shadows on/off + setMaterialScheme(pick(detail,state));
```

Scheme pick (literal strings): `{high,medium,low,lowest}` × `-noshadow`
(shadows off) / plain (on, non-PSSM) / `-pssm` (on, PSSM tier), keyed by
detail 0/1/2/else. Ogre objects: SceneManager, Viewport, both shadow-camera
setups, RenderWindow. No cameras, no render targets, no resource reloads, no
LOD writes. Vtable→method mapping for the float setters is Inferred
(Low-Medium). The viewport loop's exact arg attribution
(`setShadowsEnabled(vp, index)` / scheme-pointer form as decompiled) is
suspicious — likely-intended form is per-viewport enable + scheme string;
marked Unresolved.

Callers: UI appliers (`007af310`, `007af3e0`), reconciler (`007ae480` ×2),
central view setup (`006658b0`), terrain sun-light setup (`0067df70`),
vehicle-select preview (`007a9590`), thunk (`0077bfe0`). Safe to re-invoke
whenever a scene exists (unguarded SceneManager dereference is the only
precondition); idempotent, SharedPtr-owned setups, already called live
mid-mission (Medium-High).

## 4. Glow path

### 4.1 `FUN_0044d2a0()` — pure getter (Proven)

Body: `return DAT_02cc2bf0;`. No args, writes, or calls; 30+ diverse callers.
Return discarded at every glow call site (the single exception,
`FUN_00684ddf`, calls `663aa0` alone). **No order dependency is demonstrated;
do not treat it as a prerequisite** (Medium-High). Referent unknown
(Unresolved — widely-needed singleton class).

### 4.2 `FUN_00663aa0(record* via ECX)` — per-view Glow evaluator (Proven)

```c
if (!FUN_00684ce0(0)) return;                    // frame gate (mutually recursive)
enable = (profile+0x28 == 1) && (DAT_008fe240 == 1) && (viewport->getVisibilityMask() == 1);
if (runningState /*DAT_008e706c*/ != 9 /*loading, Medium*/ && (cached != enable || (!inited && !enable))) {
  if (!inited) {
    inst = CompositorManager::addCompositor(viewport, Name /*"Glow", §5*/, 0);
    if (inst) {
      setCompositorEnabled(viewport, name, enable);
      +0x44 = new MatListener();                 // FUN_00662f60
      +0x48 = new RTListener(inst);              // FUN_00663210
      inited = 1;
    }
  } else setCompositorEnabled(viewport, name, enable);
  cached = enable;
}
```

`param_1` arrives via ECX (`__fastcall`, argless at all call sites); offsets
`+0x1c` viewport, `+0x40` cached, `+0x41` init flag, `+0x44/+0x48` listeners
match the record `006658b0` builds (Medium — reconstruction). Callers: central
view setup, viewport-mode switch (`00682540`, mask `0x10`↔`1` — glow
suppresses itself off mask 1), frame-pump paths (`00684ce0:89`,
`00684ddf:39` — so it already runs outside the UI), glow checkbox, `UI View
Started/Ended`. Redundant calls are cheap no-ops via the `+0x40` cache.

### 4.3 Compositor `Glow` — complete pipeline (Proven, on-disk)

`BZ_ASSETS_CORE\common\programs\glow.compositor`, sole `.compositor` on disk:

1. `rt_output` ← previous (full-res scene copy).
2. `glowMap` ← scene re-render, queues 10–90, `material_scheme glow`,
   `shadows off`, `visibility_mask 1`, cleared.
3. `rt0` (½-res) ← `Glow/Downsample(glowMap)`; 4. `rt1` ← `Glow/BlurV(rt0)`;
   5. `rt0` ← `Glow/BlurH(rt1)`; 6. output ← `Glow/Combine(rt_output, rt0)`.
   Textures: `rt_output/glowMap` full-res, `rt0/rt1` half-res, all `PF_R8G8B8`.

Materials (`glow.material`): Downsample/BlurV/BlurH/Combine + `Glow/Null`
(black untextured). All single-technique, depth-check off, shared vertex
program `StdQuad_Tex2a_vp` (`stdQuad.program`); fragment programs
`GlowDownsample_fp/GlowBlurV_fp/GlowBlurH_fp/Glow_fs` each in 5 syntaxes
(glsles/glsl/HLSL4/HLSL/unified) — no per-RS techniques needed. The `glow`
scheme (`BZBase.material:915-938`): ambient/diffuse = `$glow`, emissiveMap
only — the glow mask is the emissive channel. `Glow/Null` is a *material*,
`glow` a *scheme*, `glowMap` a *texture* — three distinct entities.

### 4.4 Listeners (Proven)

- `FUN_00662f60` → MatListener: pins material `Glow/Null` to
  self-illumination black (reference no-glow state; further callbacks
  untraced — Unresolved).
- `FUN_00663210` → RTListener (CompositorInstance::Listener +
  RenderTargetListener + RenderQueueListener, one vftable): resolves the
  instance's `glowMap` texture, locks HardwarePixelBuffer 0 (pointer kept at
  `+0x18`), registers on the target (`+0x70`) and hooks the RQ subobject into
  `(*FUN_0044d2a0()+8)->vft+800` (scene-side dispatcher — method unpinned).
  CPU bridge into the glow mask; `notify*` bodies untraced (Unresolved).

## 5. Material-scheme architecture (Proven from script text)

Defined in `common\BZ_MATERIALS\BZBase.material` + `BZTerrainBase.material`
(the only two files declaring these schemes, full-tree `findstr`). One
`abstract pass` per family × tier:

`high/medium/low/lowest` × `pssm/plain/noshadow` → `Base<Tier><PSSM|Shadow|
NoShadow>_vertex/fragment` shader pairs (12 pairs, `:1-559`). Every scheme
has 3 LOD techniques (`lod_index 0` tier-native, 1/2 stepping down to cheaper
`*NoShadow` passes). Plain vs `-noshadow` vs `-pssm` = different shader pairs
(sampler sets); tiers = different pairs + shorter LOD chains. Materials
without a scheme technique fall back to scheme-less techniques (Ogre fallback
imports present; stock relies on it forwarm materials). `BZBaseCockpit`:
`receive_shadows off`, all schemes mapped to `*NoShadow` — cockpit is
shadow-invariant (only file with that flag). Switching schemes reselects
techniques (compile-on-first-use hitch possible); stock does it live on every
shadow/detail click.

## 6. `DAT_008fe240` — view/mode state (Proven)

Sole writer `FUN_00820fe0(req)` (toggle-setter: `cur==req → 1`, else `req`).
Value set: **1** = normal 3D world (gates packet queues, `DoNextFrame`
present, Alt-keys, Glow); **4** = Ogre UI view (set by `UI View Started`,
cleared by `UI View Ended`); **2** = modal overlay (input-draining,
suspend/resume via slot `008fe23c`). Frame dispatcher masks `& 0xe`
(anticipates `8`). Glow's AND therefore reads: world view, not UI, not
overlay. Name it at most `ViewMode`.

## 7. Per-view record (Proven fragments, Inferred assembly)

`+0x1c` Viewport (created in `6658b0`), `+0x20/+0x24` zero, `+0x2c` Timer,
`+0x40/+0x41/+0x44/+0x48` glow state. Arrives via ECX through
`0043fe20 → 0067c820 → 006658b0` (all argless thunks; `0043fe20` gates on
`FUN_0067c830`). One viewport per record while schemes iterate all window
viewports → one record per render view, not per viewport (Medium). No
teardown found: `removeCompositor` has **zero** tree-wide references, `UI View
Ended` destroys FrameListeners but never this record — attach-monotonic,
toggle-only, effectively process-lifetime (Medium, negative static evidence).

## 8. Sibling compositors (Proven negative)

`addCompositor` and `setCompositorEnabled` each occur in exactly one function
tree-wide (`FUN_00663aa0`). **Glow is the only stock compositor effect.**

## 9. Renderer startup (summary; see dedicated doc)

`renderer_startup_backend_selection_20260825.md`: cmdline `/renderer:` →
`DAT_025F8D94`, else `Ogre.cfg: Render System=`, fallbacks to D3D9 then first
available; `FUN_00664905` enforces + `saveConfig()` persists; stock renderer
change = `exit(0)`.

## 10. Appendix — OpenShim/EXU graphics surface (context only)

OpenShim settings page (`src/patches/bzr_options_ui.cpp:2828`): Render
Profile Retro/Redux/Enhanced (live), DX11 FXAA + Local Lights (restart,
DX11-only, fail-closed), Sun Flashbang (live), headlight brightness/color/beam
(50–150%), Radar Size, HUD/target/alert rows. No Renderer row by design
(parses `[Graphics] Renderer`, steers via the `Ogre.cfg` transport seam).
EXU: read-only Lua (`GetFullscreen` `0x009183B8`, `GetGameResolution` from
mainCam, `GetUIScaling` `/5`; live Ogre shadow toggles, no persisted UI).

## 11. Implications for runtime rendering extensions

Descriptive only — what stock demonstrably supports:

1. New viewport schemes can be selected live; materials without them fall back
   to scheme-less techniques.
2. The scheme set is data-driven (`setMaterialScheme` + script techniques), so
   added techniques on existing materials are picked up by the same path.
3. A second compositor can attach via the already-linked
   `addCompositor`/`setCompositorEnabled`; stock never removes, only toggles.
4. The `+0x40/+0x41` cache pattern gives idempotent per-frame evaluation for
   any reused state evaluator.
5. `FUN_00680fe0` is re-invocable after arbitrary profile changes whenever a
   scene exists (only precondition: live SceneManager).
6. Hard limits: one viewport per view-record, one compositor instance per view
   (no removal path), shadow setup replaced wholesale per call.
