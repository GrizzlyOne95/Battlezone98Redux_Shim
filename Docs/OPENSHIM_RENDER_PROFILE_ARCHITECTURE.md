# OpenShim Render Profile Architecture

Status: implemented (state model, policy, EXU bridge, resource ownership);
stock-material retrofit is scaffolded but runtime validation pending. See
"Known limitations / future work".

Related work orders: canonical Enhanced renderer ownership migration
(this document); PSSM terrain cutoff investigation (next dedicated task).

---

## 1. Ownership model

### Old model (before migration)

| Concern | Owner | Mechanism |
| --- | --- | --- |
| Lighting-mode state (Default/Enhanced/Retro) | EXU `Environment.cpp` | `g_desiredLightingMode`, never cleared |
| Viewport scheme application | EXU | `setMaterialScheme` IAT takeover (`0x869810`, 3 call sites) + Lua-driven per-frame enforcement |
| Scheme naming (`en-`, `og-`) | EXU string builders | `"en-" .. modern` / `"og-" .. modern` |
| All Enhanced shaders/materials | Campaign Reimagined | `CR_base-sm4.hlsl`, `CR_terrain-sm4.hlsl`, ~300 stock-named materials with `en-*`/`og-*` techniques |
| Light selection for `en-*` schemes | OpenShim | `ogre_enhanced_light_selection.cpp` budget keyed on scheme prefix |
| User-facing lighting mode UI | CR `PersistentConfig.lua` | `LightingMode = 1/2/3` |

Problems: two renderer owners evolving in parallel, Enhanced impossible without
CR installed, mission overrides never cleared, no requested-vs-effective
distinction, no capability reporting, no resource/deployment integrity story.

### New model

```
OpenShim owns renderer CAPABILITY + POLICY
    RendererBackend (DX9/DX11 observation, restart-scoped preference)
    RenderProfile state: user preference (openshim.ini) +
                         content override (EXU bridge, mission-scoped)
                         -> resolver -> effective profile + fallback reason
    Scheme policy application (viewport setMaterialScheme takeover)
    Capability reporting ([RENDER] diagnostics + winmm ABI)

EXU owns content INTENT
    exu.RequestRenderProfile(Inherit|Retro|Redux|Enhanced) -> winmm bridge
    Legacy SetLightingMode/SetRetroLightingMode forward when bridge present;
    full legacy behavior preserved on old/absent shims.

Campaign Reimagined owns CONTENT + ART DIRECTION
    sun color/intensity, ambient, fog, sky, IBL art assets unique to CR,
    mission light placement, custom material variants.
    Consumes the canonical renderer via EXU; no rendering implementation.
```

Core principle: **OpenShim owns renderer capabilities. EXU communicates
content intent. Campaign Reimagined owns content and art direction.**

---

## 2. RendererBackend semantics

- `Auto` (default): use whatever the game selects this session. Observation
  watches which render system module loads (`RenderSystem_Direct3D11.dll` vs
  `RenderSystem_Direct3D9.dll`).
- `DX9` / `DX11`: a persistent user preference in openshim.ini, applied at
  next process start via the backend-selection transport seam (Seam A):
  OpenShim rewrites ONLY the `Render System=` line of the game's Ogre.cfg
  before the game reads it (from DllMain, so it wins even on fast machines),
  after validating the requested renderer plugin is present. The preference
  itself lives only here - stock `saveConfig()` may rewrite Ogre.cfg freely
  without redefining it. Requested vs effective remain distinct: the
  observation layer classifies every boot as
  `requested/effective/reason` (`none`, `cli-override`,
  `backend-unavailable`, `no-establishment`, `stock`) under `[RENDER]`.
  A `/renderer:...` command-line token overrides this key for its launch
  only; a GL token is recognized but unsupported and falls through to stock.
  Because startup control is new and not yet UI-proven, the settings-UI
  backend row remains hidden; hand-edited ini values drive the seam.
  Evidence and validation matrix:
  `reverse_engineering/renderer_startup_backend_selection_20260825.md`.
- EXU/content cannot force a backend; the bridge exposes read-only queries.

## 3. RenderProfile semantics

- **Redux** — stock Battlezone 98 Redux rendering behavior as closely as
  practical on the selected backend. The compatibility baseline; the engine's
  native scheme flow passes through untouched (fail-open by construction).
- **Enhanced** — OpenShim's canonical graphics upgrade. Supported on BOTH
  backends, capability-dependent rather than all-or-nothing:
  - DX11 (primary development platform): linear-lighting/colorspace path,
    enhanced terrain/object shader families, modern PSSM behavior (cascade
    blending, comparison PCF, receiver normal offset, terminal fade),
    contribution-ranked enhanced light selection, neutral IBL resources.
  - DX9 (feature-frozen maintenance mode): proven legacy enhancements only —
    distance-faded normal-map sharpening plus the SM3 enhanced technique
    delegates. Correctness/crash fixes yes; new visual work targets DX11
    first. A missing DX11-only bit is an expected report, NOT a fallback
    failure: DX9+Enhanced remains effective rather than silently degrading
    to Redux.
- **Retro** — classic-style presentation through the `og-*` material scheme
  family (fewer texture units, simpler lighting, Glow compositor suppressed).
  Status: **experimental**. The scheme family legitimately exists (it is not
  fabricated), but OpenShim asserts glow suppression only on explicit
  reapplies, so engine viewport rebuilds can temporarily re-enable bloom
  until the next reassert. Documented limitation, not a fabricated mode.

Profiles are policy layered over the backend; shadow QUALITY controls remain
independent of shadow BEHAVIOR, as do FXAA, sun-flash suppression, FOV/UI,
raw input, chunk/TRN/satellite correctness repairs — none of those are profile
semantics and none were folded into Enhanced.

## 4. Profile precedence

1. Hard compatibility/safety constraints (scheme layer unavailable → Enhanced
   reports itself unsupported rather than half-working).
2. Content override via EXU (mission/session scoped).
3. User preference from openshim.ini.

Examples:

| Backend | User | Content override | Effective |
| --- | --- | --- | --- |
| DX11 | Redux | Inherit | Redux |
| DX11 | Redux | Enhanced | Enhanced |
| DX11 | Enhanced | Redux | Redux |
| DX9 | Enhanced | Inherit | **Enhanced (legacy capability set)** |
| any | Enhanced | – | Redux only if scheme layer inactive, reason logged |

The resolver lives in `src/engine/render_profile.cpp` (pure, unit-tested via
`scripts/run_render_profile_tests.ps1`).

## 5. EXU API

Native winmm exports (stable integer ABI, mirrored in EXU's
`src/RenderProfileBridge.h`; requests: 0=Inherit, 1=Retro, 2=Redux, 3=Enhanced):

- `OpenShimGetRenderApiVersion()`
- `OpenShimRequestRenderProfile(req)` → applied-live / stored-deferred / rejected
- `OpenShimGetUserRenderProfile()`, `OpenShimGetRequestedContentRenderProfile()`,
  `OpenShimGetEffectiveRenderProfile()`
- `OpenShimGetActiveRendererBackend()`
- `OpenShimGetRenderCapabilities()` (bitmask), `OpenShimSupportsRenderProfile(p)`

Capability negotiation: presence of the `OpenShimRequestRenderProfile` export
means the render-profile API exists; version query guards future evolution.
Absent export ⇒ old shim ⇒ EXU uses its legacy local path unchanged; new EXU
APIs map onto it so content written either way keeps working.

Lua surface (documented in EXU `Definitions/ExtraUtils.lua`):
`RequestRenderProfile`, `GetRequestedRenderProfile`,
`GetEffectiveRenderProfile`, `GetUserRenderProfile`,
`SupportsRenderProfile`, `GetRenderCapabilities`.

## 6. Mission lifecycle

Content overrides are cleared by the authoritative mission-lifecycle seam:
`ResetMissionHookOverridesFromBridge()` (exported as
`OpenShimResetMissionHookOverrides`, invoked by EXU at mission init) now also
calls `ClearContentRenderProfileOverride`. Shell → CR Enhanced mission → shell
→ stock mission → shell resolves to user preference at every transition; an
override cannot leak into unrelated subsequent content.

## 7. Material compatibility strategy

Policy (implemented in the scheme hook):

```
known modern base (high-pssm … lowest-noshadow)  -> profile prefix applied
OpenShim's own en-/og- prefixed schemes          -> renormalized to effective profile
foreign/custom scheme (Workshop mods)            -> PASSED THROUGH UNTOUCHED (fail open)
```

Unknown custom rendering is never rewritten; rate-limited `[RENDER]` logging
identifies rewrites without spamming. This deliberately improves on the legacy
EXU behavior, which rewrote unrecognized schemes to the last known modern base.

Stock-family retrofit (giving stock materials real `en-*` techniques without
CR installed) is the next task: it requires Ogre resource-location injection
and per-family technique generation driven by the stock asset audit
(`reverse_engineering/asset_audit/`), validated in-game before enabling.
The capability bit `CapIblResources` already gates on deployed-resource
validation so the retrofit path can fail closed cleanly.

## 8. Resource packaging and deployment integrity

- OpenShim ships the generic Enhanced core under `resources/renderer/enhanced/`:
  `openshim_enhanced_{base,terrain}[-sm4|-sm3].hlsl` (+ GLSL variants),
  `openshim_enhanced_*.program` (program names namespaced `OSE_*` so they can
  never collide with CR's during transition), neutral IBL set renamed
  `openshim_ibl_*.dds`, and a `resources.version` marker.
- `Deploy-OpenShim.ps1` deploys winmm.dll + patches.json + renderer resources
  together, extending the existing "DLL and patch definitions move as one
  unit" rule.
- At startup the DLL validates the deployment in two tiers before granting
  `CapIblResources`:
  1. `resources.version` must match the DLL's compiled expectation. Mismatch ⇒
     `[RENDER] Enhanced unavailable: resource version mismatch` ⇒ effective
     profile falls back to Redux. A stale pairing can never silently run.
  2. Every mandatory file — both `.program` scripts, all GLSL/HLSL vertex,
     fragment, and SM3/SM4 delegates for base/terrain/glow families, and the
     three neutral IBL DDS textures — must exist and be non-empty. A missing
     or empty payload (even with a correct version marker) fails validation
     with the offending filename logged.
  This is a file-level contract; actual Ogre resource resolution (the
  strongest tier) remains future work until retrofit lands.

## 9. Diagnostics

One concise block on change only:

```
[RENDER] backend.requested=Auto backend.effective=DX11
[RENDER] profile.user=Redux profile.content=Enhanced profile.effective=Enhanced profile.source=EXU
[RENDER] enhanced.supported=yes resources.compatible=yes capabilities=0x000000FF
[RENDER] enhanced.sharpening=yes enhanced.linearLighting=yes enhanced.pssm=yes enhanced.lightSelection=yes
```

Fallback example:

```
[RENDER] fallback=Enhanced unavailable: scheme policy layer inactive
```

## 10. Validation matrix

Automated (this branch):

- `tests/render_profile_tests.cpp`: resolution table (override precedence,
  inherit, DX9 legacy retention, scheme-layer fallback with reason,
  requested-vs-effective backend reporting, override clearing, invalid inputs),
  scheme mapping round-trips, stable ABI values.
- `tests/ini_writer_tests.cpp`: lossless INI writes still green.
- Release Win32 build of winmm.dll and exu.dll green; exports verified via
  dumpbin.
- **Headless runtime qualification** (GOG install, lcbench harness; driver:
  `scripts/render_profile_matrix.ps1`, full report and evidence index in
  `Docs/RENDER_PROFILE_RUNTIME_QUALIFICATION_20260824.md`, per-case logs under
  `reverse_engineering/snapshots/render_profile_matrix/`). All cases PASS:

| Case | Asserts |
| --- | --- |
| DX11 + Redux | takeover installed ×3 (byte-verified), backend observed DX11, resources compatible, Redux passthrough with zero rewrites, full modern capability bits, FXAA attach unchanged |
| DX11 + Enhanced | effective Enhanced, engine schemes rewritten to `en-*` by the takeover, modern bits incl. light selection, FXAA unchanged |
| DX11 + Enhanced + new EXU | canonical chain: bridge-capable EXU paired with shim; same asserts as above |
| DX11 + Retro | effective Retro, `og-*` rewrites applied |
| DX9 + Redux | backend observed DX9, baseline intact, legacy-only bits |
| DX9 + Enhanced | **stays Enhanced** (no silent degrade), `en-*` SM3 delegates requested, DX11-only bits honestly absent, no fallback fired |
| resources.version mismatch | deterministic detection, `resources.compatible=no`, retrofit path gated while scheme layer stays intact |
| resource set absent | clean detection line, CR-supplied techniques path unaffected |
| old EXU + new shim | legacy EXU keeps working; new bridge untouched by it |
| new EXU + pre-migration shim | no render-profile block emitted; EXU legacy behavior unchanged |
| baseline control | pre-migration stack shows identical harness behavior for subsystem installs driven by EXU-bearing content |

Defects caught and fixed by this pass: init-before-compatibility-gate,
plugin-order backend race, cached-null export resolution (see commit
"three defects caught by the runtime qualification matrix").

Remaining manual/interactive sign-off (requires real content and eyes):
visual parity captures per profile, in-process Enhanced→Retro→Redux→Enhanced
cycling contamination checks, CR mission → shell → stock mission → IA/MP
transition matrix, restart persistence through the actual UI.

## 11. Known limitations / future work

1. **Stock-material retrofit** (Phase 8 completion): scaffold exists
   (capability gating, resource validation, fail-open policy); technique
   injection for audited stock families needs in-game iteration. Until then,
   non-CR Enhanced renders through whatever techniques the active content
   provides (stock materials keep their native look).
2. **PSSM terrain cutoff**: explicitly deferred to the next dedicated task,
   per sequencing: canonical ownership first, then cutoff fix, then broader
   quality/performance refinement.
3. **Retro glow drift**: glow suppression asserted on explicit reapplies;
   engine viewport rebuilds can transiently re-enable bloom until the next
   reassert (~1 Hz) — acceptable for experimental status.
4. **Renderer forcing**: implemented as of the backend-selection seam
   (Seam A): `Renderer=DX9/DX11` steers startup via the pre-read Ogre.cfg
   transport, with requested/effective/reason diagnostics and a hard opt-out
   (`[Startup] BackendTransport=0`). The settings-UI backend row stays hidden
   until the runtime matrix has soaked across releases; see §2 and
   `reverse_engineering/renderer_startup_backend_selection_20260825.md` for
   the ownership contract and validation evidence. Profile changes are applied
   via a pending flag drained by the scheme hook on the game thread, so
   viewport feedback lands within one ~1 Hz reassert pass rather than from an
   unsafe off-thread apply.
5. **CR duplicate removal** (Phase 14) happens in the CR repo only after
   parity validation above; both implementations coexist harmlessly meanwhile
   (disjoint program namespaces).
