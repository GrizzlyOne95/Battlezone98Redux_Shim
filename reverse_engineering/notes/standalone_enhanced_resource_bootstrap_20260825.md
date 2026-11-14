# Standalone Enhanced Resource Bootstrap — RE Report (2026-08-25)

Task: determine how Battlezone 98 Redux reaches filesystem/archive resources →
Ogre resource locations → resource groups → script parsing → GPU programs →
materials → techniques → schemes → runtime material selection, and find the
narrowest safe point where OpenShim can insert its own standalone Enhanced
resource tree without Campaign Reimagined.

Evidence classes used: shipped-runtime Ogre logfile capture (GOG install,
boot+shell session 2026-08-14 19:01), static RE of the shipped GOG
`battlezone98redux.exe` (rizin: string xrefs, IAT enumeration, targeted
disassembly), exported-symbol enumeration of shipped `OgreMain.dll`, local Ogre
1.10.0 source (the EXU vendored tree `ExtraUtilities/third_party/ogre-1.10.0-bzr`
is vanilla 1.10.0 plus two small patches, ABI-compared against the shipped DLL),
existing OpenShim/EXU production code paths, CR source/deployment inspection.

Raw captures: `reverse_engineering/snapshots/enhanced_resource_bootstrap_20260825/`.

Build identity: GOG `battlezone98redux.exe`
SHA256 `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`;
Steam copy checked for `bz_resources.cfg` parity only (exe differs by SteamStub).

---

## 1. Executive verdict

**Standalone Enhanced needs no new injection technology and no binary patching.
OgreMain.dll exports the complete resource API; stock resources are registered
through one plain config-file loop (`bz_resources.cfg` →
`ResourceGroupManager::addResourceLocation`) and parsed in a single eager
`initialiseAllResourceGroups()` call; material lookup is global-pool, so an
OpenShim-owned namespaced resource group initialised at any time after Root
construction is visible to stock content exactly like a native group; and stock
materials can be given Enhanced techniques collision-free through the exported
`MaterialManager::Listener::handleSchemeNotFound` arbitration hook, which fires
only when the active scheme (`en-*`, set by OpenShim's already-proven viewport
takeover) has no matching technique on the material.**

Recommended architecture: hybrid (static OSE_* donor materials/programs in an
OpenShim-owned resource group + scheme-arbitration retrofit). CR's current
per-object Enhanced path depends on game mod-staging that exposes only part of
its payload; OpenShim bypasses that machinery entirely.

---

## 2. Resource startup chain

### 2.1 Boot sequence (verified: runtime log + disassembly)

```
exe Ogre-bootstrap function (~0x663e00..0x666000 region)
 ├─ LogManager created, log "BZOgreLogfile.log"            (str push @0x663ff6)
 ├─ ConfigFile::load("Ogre.cfg")                           (str push @0x663f2f)
 ├─ Root::constructor                 [IAT 0x869cd8]
 │    └─ creates groups General / Internal / Autodetect          (log 19:01:49)
 ├─ plugin DLLs: D3D9, D3D11, GL, ParticleFX, Cg       (Root::loadPlugin [IAT 0x869ec8])
 ├─ game registers custom "i76FS" ArchiveFactory
 │    ("ArchiveFactory for archive type i76FS registered.";
 │     str refs @0x669aa7/0x669bae; helper ~0x667700; wrapper 0x669b00-0x669c52)
 ├─ ConfigFile::load("bz_resources.cfg")                   (str push @0x663f65)
 │    └─ FileNotFoundException NON-fatal (repo-dir run logs it and continues)
 ├─ config iteration loop:
 │    for each section S, each setting key=K value=V:
 │        getSingleton() [IAT 0x869cd4]
 │        .addResourceLocation(V /*name*/, K /*locType*/, S /*group*/, true, true)
 │        >>> exe's single direct IAT call site: 0x66485a <<<   ([IAT 0x869cd0])
 │    section = group name; setting key = archive type; value = path
 ├─ window/viewport setup (Viewport::setBackgroundColour/setOverlaysEnabled/…)
 ├─ TextureManager vtable+0xc0(0x7fffffff) ≈ setDefaultNumMipmaps
 ├─ initialiseAllResourceGroups()
 │    >>> exe's single direct IAT call site: 0x6659ed <<<       ([IAT 0x869ccc])
 │    parses groups in map order Autodetect → General → Internal → Modable
 │    (std::map alphabetical iteration; only UNINITIALSED groups parsed)
 └─ MaterialManager texture-filtering / anisotropy setup from settings
```

Structural facts:

- The exe calls `addResourceLocation` exactly once (0x66485a), inside the
  `bz_resources.cfg` loop. There is no second registration path at boot.
- `initialiseAllResourceGroups` runs exactly once, eagerly, before first render.
- Parse order inside a group: script-loader order (registered ScriptLoaders),
  then per-loader location order (registration order), files alphabetical per
  archive enumeration.

### 2.2 Mod lifecycle (separate subsystem)

A distinct cluster (~0x769f40–0x76b800; callers incl. 0x771470) performs, on
shell mod-staging, **every mission load, and leave-game-to-shell** (see
`docs/leave_game_freeze_shader_recompile_20260717.md`):

```
iterate enabled mods → refresh staged visibility
clearResourceGroup("Modable")      e.g. 0x76a18d   [IAT 0x86990c]
initialiseResourceGroup("Modable") e.g. 0x76a1c2   [IAT 0x869910]
```

Seven clear/init pairs exist in the cluster. Critical Ogre semantics
(`OgreResourceGroupManager.cpp:443`): **clearResourceGroup keeps all locations**;
it drops parsed/loaded resources and resets status to UNINITIALISED only, so
re-init reparses everything still attached — including anything mounted later.

How mod files become *visible* between boot init and re-init: no additional
`addResourceLocation` occurs (that API always logs; no such line appears), so
visibility changes live **inside the game's i76FS virtual-archive /
cWorkshop staging layer** (`cWorkshop::buildModResources/buildMPResources/
buildIAResources/listDir`, names recovered earlier in
`reverse_engineering/workshop/private_pdb_index/public_functions.csv`). In the
captured session the re-init exposed CR_*.* scripts and chunkMeshes/* but **not**
CR's loose stock-named `.material` overrides (`abbarr.material` et al. were
never parsed; only stock `pc/materials/abbarr.material`). See §13.

### 2.3 Scheme/technique selection at runtime

- The exe **never imports** `MaterialManager::setActiveScheme`. Scheme flow is
  exclusively `Viewport::setMaterialScheme` [IAT 0x869810] — exactly the import
  OpenShim's render-profile takeover already hooks (byte-verified ×3 sites).
- `Material::getBestTechnique` (`OgreMaterial.cpp:369`): active-scheme technique
  list → if absent, `MaterialManager::_arbitrateMissingTechniqueForActiveScheme`
  (listener arbitration) → else first scheme entry (native fallback).
- Stock `BZ_ASSETS_CORE/common/BZ_MATERIALS/BZBase.material` natively declares
  12 schemes + glow: `high|medium|low|lowest` × `-pssm|-noshadow|(plain)` +
  `glow`, referencing stock programs `Base*_vertex/_fragment`. CR_BZBase adds
  `en-*` and `og-*` variants of the same set referencing `CR_*` programs. The
  `en-*` family extends a real engine-native scheme family; nothing fabricated.

---

## 3. Resource-location inventory (stock boot + CR installed)

From the captured live boot log (full log in snapshots):

| # | When | Location | Group | Type | Recursive | Source |
|---|------|----------|-------|------|-----------|--------|
| 1 | boot | `./BZ_ASSETS_CORE` | General | i76FS | yes | `bz_resources.cfg [General]` |
| 2 | boot | `./BZ_ASSETS` | Modable | i76FS | yes | `bz_resources.cfg [Modable]` |
| 3 | staging/reinit | `mods\3686673790` subset via i76FS overlay of #2 | Modable | overlay (no new location) | – | game mod system |
| 4–5 | session | `<game>\BZ_ASSETS\pc\textures\MISC_DDS`, `<game>\mods\3686673790\OverlayFont` | EXUOverlayFontRuntime | FileSystem | no | EXU |
| 6–7 | session | same two paths | EXUOverlayRuntime | FileSystem | no | EXU |

- Groups at boot: General/Internal/Autodetect (Root), then Modable (game).
  Init order: Autodetect, General, Internal, Modable (alphabetical).
- Groups are initialized **eagerly** at boot; groups created post-boot are
  initialized explicitly by their owner (EXU pattern, proven mid-session at
  19:01:58 with rendering active).
- Steam vs GOG: `bz_resources.cfg` byte-identical; bootstrap imports identical;
  no material difference expected or observed.

---

## 4. Precedence behavior (duplicate-name semantics)

From Ogre 1.10 source (parse chain has no exception handlers between translator
and group init, so semantics are strict):

**Scripts (.material/.program/.compositor/...)**

- Every script in **every** location of the group is parsed — no cross-location
  dedup, no "later location replaces earlier file".
- Duplicate material/program name → `ResourceManager::addImpl`
  (`OgreResourceManager.cpp:107`):
  - No LoadingListener → `OGRE_EXCEPT(ERR_DUPLICATE_ITEM)`; nothing catches it
    in `ScriptCompiler::compile` → `ScriptCompilerManager::parseScript` →
    `parseResourceGroupScripts`, so **the whole group init aborts**. Duplicates
    are fatal by default — not merged, not first-wins.
  - With OpenShim's installed `OgreMaterialCollisionListener`
    (`src/patches/trampolines.cpp:79`, production code): MaterialManager
    collisions resolve **latest definition wins** (`removeByName` + Ogre's
    single permitted re-insert). Non-material managers decline → default fatal
    semantics. Listener chains politely with any pre-existing listener.
- After a clear+reinit cycle the namespace is fresh; within one re-parse the
  last-parsed definition of a name wins (subject to the listener when both
  parse in one pass without an intervening clear).

**Files (textures/meshes/skeletons)**

- Per-group name→Archive index built during `addResourceLocation` (`addToIndex`
  does not overwrite): **first location registering a path wins** for data
  opens; later same-path copies are shadowed for opens even though their
  scripts would still be parsed.

**GPU programs**

- Same manager machinery; duplicates follow listener/exception logic.
  OpenShim's guard deliberately covers materials only; program collisions stay
  fatal by policy unless extended deliberately.
- Unsupported-syntax programs are non-fatal: logged ("Invalid target for D3D11
  shader 'CR_Base*_vertexHLSL' - 'vs_3_0'" observed), registered as unsupported
  placeholders so referencing materials compile-with-error but parsing lives.

---

## 5. Proven OpenShim injection seam

Ranked candidates:

| Seam | Safety | Repeatability | DX9/DX11 | Steam | Reparses stock? | Unsupported internals | Double-init risk | Verdict |
|---|---|---|---|---|---|---|---|---|
| A: before Redux init (poll until group exists; mount into General hoping to beat parse) | racy | poor | same | same | if race won | none | yes | reject |
| B: hook `initialiseAllResourceGroups` IAT (0x869ccc), mount before delegating | deterministic | good | same | byte-verify (precedent: scheme takeover) | rides along | IAT patch only | low | viable, unnecessary |
| C: own group + explicit timing — `createResourceGroup("OSE…")` + `addResourceLocation(dir,"FileSystem",grp,true,true)` + `initialiseResourceGroup(grp)`, any time after Root ctor | high | idempotent w/ guards | identical | export-based, no addresses | **no** | none — plain exports | guarded | **chosen** |
| D: lazy per-request synthesis as registration | n/a | – | – | – | no | – | – | superseded by §8 |

Why C is safe:

1. **Export-only**: `ResourceGroupManager::getSingletonPtr /
   addResourceLocation / initialiseResourceGroup / resourceGroupExists`
   resolved by mangled name from OgreMain.dll — identical to shipping code:
   OpenShim briefing mount (`src/patches/trampolines.cpp:217`) and EXU font
   bridge (`ExtraUtilities/src/Ogre/OgreNativeFontBridge.cpp`). No patches,
   no addresses.
2. **Timing window**: valid from `Root::constructor` (groups exist) to process
   exit; OpenShim's backend observer already gives a post-plugin readiness
   signal. Mid-session creation proven live (EXU groups at 19:01:58).
3. **Lifecycle isolation**: the game clears/re-inits **Modable only**; a
   dedicated OSE group is never touched and never reparsed.
4. **Global visibility**: `getResourceByName(name, group)` falls back to the
   manager-wide global pool even when a specific group is requested, and all
   Redux groups are in-global-pool — a material parsed into "OSE" resolves for
   `getByName(name, "General")` callers identically.
5. **Fail-open**: missing exports / failed validation ⇒ capability bit stays
   off, `[RENDER] Enhanced unavailable: …`, effective profile Redux.

Phase-5 status: mechanism proven by three independent production paths (EXU
runtime groups incl. script parsing; OpenShim briefing mount; game clear/reinit
location persistence). Dedicated `OSE_BootstrapProbe.*` live run not yet
executed — procedure in §12; requires content drop + harness run only.

---

## 6. Bootstrap proof (existing runtime evidence)

Captured session log (snapshots):

```
19:01:58 Creating resource group EXUOverlayRuntime            ← createResourceGroup mid-session
19:01:58 Added resource location '...mods\3686673790\OverlayFont' of type 'FileSystem'
         to resource group 'EXUOverlayRuntime'                ← addResourceLocation (exported)
19:01:58 Initialising resource group EXUOverlayRuntime        ← initialiseResourceGroup
19:01:58 Finished parsing scripts for resource group EXUOverlayRuntime ← scripts parsed+used
```

These groups feed production overlay text rendering. OpenShim's own briefing
mount exercises the same exports from winmm.dll
(`[BRIEFING] Mounted enabled-mod overrides group=General ...`).

Probe package plan:

```
resources/renderer/enhanced/bootstrap/
    OSE_BootstrapProbe.program   (vertex/fragment_program OSE_BootstrapProbe_vp/_fp;
                                  sm4 delegates for DX11, sm3 for DX9)
    OSE_BootstrapProbe.material  (material OSE_BootstrapProbe with technique en-high-pssm
                                  + plain technique; shader sources reuse
                                  openshim_enhanced_base-sm4/-sm3.hlsl)
```

Live-run assertions (windowed harness per AGENTS.md):

1. `[RENDER]` line confirms create/mount/init.
2. Ogre log contains `Parsing script OSE_BootstrapProbe.material`.
3. Exported `MaterialManager::getSingletonPtr()->getByName("OSE_BootstrapProbe","")`
   returns non-null with ≥1 supported technique.
4. Stock namespace unchanged vs control run (e.g. `getByName("abbarr","")`,
   material counts).
5. No new compiler errors beyond the probe's own lines.

---

## 7. Stock material-family census

Sources: unique script inventory (298 unique scripts in capture),
`common/BZ_MATERIALS/*`, `pc/materials/*` (~237 object materials + TRO/
variants), asset audit (`reverse_engineering/asset_audit/`), CR comparison.

| Family | Stock pattern | Schemes | Programs | CR en-* today? | OpenShim treatment |
|---|---|---|---|---|---|
| Object/vehicle base | everything inheriting BZBase (~237 files incl. TRO/) | 12 native + glow, LOD 250/300 | `Base*` (common/programs/base.program) | yes via CR_BZBase-inheriting overrides (not parsed during captured shell staging) | **primary retrofit target** |
| Terrain | BZTerrainBase family | same family | base + terrain.program | yes (CR_BZTerrainBase) | **yes** — pairs with openshim_enhanced_terrain* |
| Glow pipeline | glow.material/compositor/program | glow chain | glow.program | parallel CR_glow.* | donor-only; don't hijack compositor |
| Transparent/additive | effect/simple/textured consumers (acloud*, smoke, stars…) | native | effect/simple/textured.program | partial (CR_effect/simple) | yes, conservative |
| Alpha-tested | subset of pc/materials | native | base/textured | partial | yes, conservative |
| Sky | xbio.material, sky.program consumers | native | sky.program | CR_sky parallel | defer (art-heavy) |
| Shadow caster/receiver | DepthShadowmap.material, content_type shadow units | shadow schemes | DepthShadowmap.program | CR_DepthShadowmap parallel | PSSM behavior already policy-owned; donors reference own receivers |
| UI/HUD/scope | ui.material, uitexmat.material, scope.material, CRBZoneOverlay.fontdef | Default/glow | ui/uitexmat/scope.program | parallels exist | **leave untouched** |
| Fullscreen quads | stdQuad.program | – | stdQuad | CR_stdQuad | leave untouched |
| Particles | weather_particles.particle | – | simple/textured | – | leave untouched |
| Chunk meshes (mod-side) | chunkMeshes/**/*_port.material | en-family (mod-supplied) | CR_* | mod-owned | leave untouched |

Stock-compatible identity criteria (for the arbiter, §8):

1. `Material::getOrigin()` inside stock script roots (`common/…`,
   `pc/materials/…`, known stock root scripts). Origin beats name matching.
2. Structural check: resolved technique pass references programs in the stock
   program set (`Base*_vertex/_fragment`, textured/simple/untextured/ui) —
   proves real lineage rather than naming.
3. Negative gates: names/origins containing `en-`, `og-`, `CR_`, `OSE_`,
   `openshim`, or materials carrying foreign-scheme techniques are ineligible
   (they manage their own schemes).
4. Unknown → arbitration returns NULL → engine-native fallback (today's exact
   behavior).

---

## 8. Retrofit strategy comparison

| Strategy | Compatibility | Maintainability | Mod safety | Perf | Startup complexity | DX9/DX11 | Fail-open | Verdict |
|---|---|---|---|---|---|---|---|---|
| A — explicit stock-named material scripts (OpenShim ships `abbarr : OSE_BZBase` etc.) | needs parse-after-stock ordering; duplicate names ride on collision-listener latest-wins; fights mods that replace same names | poor (~240 mirrors to track) | bad: hijacks same-named custom materials | fine | medium | fine | weak (name-keyed) | viable fallback for tiny allowlists |
| B — runtime technique cloning onto stock materials at load/create | good visually | poor: ABI-sensitive Technique/Pass surgery; illumination recompile handling | risky if identity slips | per-material load cost | high (creation-site hooks) | must re-derive per renderer | medium | reject |
| C — scheme arbitration listener: `MaterialManager::addListener(l, schemeName)` + `handleSchemeNotFound` returning an OSE donor technique | excellent: sanctioned extension point; exported by shipped DLL (`MaterialManager::addListener` @ 0x10002f59, `removeListener` @ 0x100094e4, `_arbitrateMissingTechniqueForActiveScheme` @ 0x1000f7b8, all VA); fires only on scheme miss | good: small decision fn + donor library | best: unknown/custom never rewritten; NULL = stock behavior | zero steady-state cost; Ogre caches best techniques per scheme | low | donors declare sm4+sm3; support filtering native | by construction | **preferred core** |
| D — hybrid: static OSE_* donors in OSE group (§5 seam) + C arbitration mapping eligible families to donor techniques | C's guarantees + declarative content | good | C's guarantees | C's profile | low | dual delegates | by construction | **recommended architecture** |

Note: pure C without D is impossible — `handleSchemeNotFound` must return a
real `Technique*`; the clean owner is an OpenShim-namespaced donor material
family (`OSE_BaseHighPSSM` …), not synthesized-from-nothing techniques. So D is
the design; A remains available for special cases where full replacement is
genuinely right (none identified in the census).

Precedence with CR installed: CR's overrides put `en-*` techniques directly on
materials, so `getBestTechnique` matches them and **never reaches the arbiter**
— art direction beats generic enhancement with zero coordination code. With CR
absent (or its unparsed loose materials), the arbiter supplies generic Enhanced
from OSE donors.

---

## 9. Workshop / custom-content compatibility (fail-open rules)

- Unknown schemes: pass through untouched (existing render-profile policy).
- Unknown materials: identity criteria (§7) gate the arbiter; non-stock gets
  NULL → native fallback identical to pre-OpenShim behavior.
- Custom GPU programs: untouched; collision guard stays materials-only.
- Mods replacing stock-named materials: their origin differs from stock roots →
  arbiter declines; their look survives Enhanced mode. Their definitions also
  win the namespace through normal parse/listener semantics.
- Mods adding techniques to stock-named materials: direct technique match
  short-circuits arbitration; mod intent wins.
- CR installed: §10. CR absent: standalone Enhanced works via donors+arbiter.
- Gating/opt-out: tier-3 capability validation (real `getByName()` resolution of
  donors) once seam C lands; proposed ini switch `Render.EnhancedStockRetrofit`
  (default on; off = never register listeners).

---

## 10. CR coexistence / migration map

| Concern | Owner | Rationale |
|---|---|---|
| Capability/policy (backend observation, profile resolution, scheme takeover, reporting) | **OpenShim** (done) | authoritative architecture |
| Generic programs/sources/IBL (`OSE_*`, `openshim_enhanced_*`, `openshim_ibl_*`) | **OpenShim** (migrated) | generic capability |
| Donor materials for stock families + scheme arbiter | **OpenShim** (new; this report) | standalone Enhanced |
| `en-*`/`og-*` scheme policy & normalization | **OpenShim** (done) | policy, not art |
| Sun/sky/fog/lighting/IBL *art values*, mission lighting | **CR** | art direction |
| `CR_*` program/material families (base/terrain/glow/effect/sky/ui/…) | **CR** (keep) | art-direction implementations; namespaces disjoint from OSE_* |
| Stock-named `.material` overrides inheriting CR_BZBase (×254 in Materials/) | **CR** (keep) | per-object art direction; outrank arbiter when parsed |
| Microcode/script caches | **OpenShim** (done) | renderer infrastructure |

Answers: (1) OpenShim always owns rows 2–4 plus policy. (2) CR keeps rows 6–7.
(3) Coexistence collision-free by namespace (verified disjoint program
inventories). (4) Both present ⇒ **CR wins by construction** (direct technique
match beats missing-scheme arbitration). (5) Yes — CR requests Enhanced via EXU
bridge and layers mission-specific overrides; unchanged. (6) Nothing forced now;
after arbiter parity validation, CR may retire generic families that merely
duplicate OSE donor coverage for stock-looking objects — CR-repo work, later.

---

## 11. DX9/DX11 differences

- Registration/parsing/namespace are render-system-agnostic; both plugins load
  at boot regardless of active backend.
- Syntax support differs at parse time: SM3 targets rejected under DX11
  (logged "Invalid target …", placeholder registered), SM4 under DX9 likewise.
  Materials referencing unsupported programs parse with compile errors but do
  not abort group init; technique support flags then steer selection natively.
- Donor materials must ship both `-sm4` and `-sm3` delegate sets (the migrated
  `openshim_enhanced_base/terrain[-sm3|-sm4].program` already do; GLSL variants
  exist but are unused by the shipped render systems).
- Device lost/reset is handled inside render systems; process-lifetime resource
  groups and parsed declarations are unaffected. DX9↔DX11 switching requires
  process restart (startup selection; documented limitation in the architecture
  doc).
- Arbitration listener runs on the render thread during technique lookup —
  implementation must be lock-free/read-only on hot path (same discipline as
  the existing profile state model).

---

## 12. Recommended Phase 2 implementation (smallest next task)

Goal: convert the proven seam into the smallest shippable bootstrap and prove
lifecycle behavior end-to-end.

1. Content: add `resources/renderer/enhanced/bootstrap/OSE_BootstrapProbe.{program,material}`
   (namespaced; reuse existing HLSL sources); bump `resources.version`.
2. Code (new `src/patches/ogre_resource_bootstrap.cpp`, ~100–150 LOC):
   - after the existing backend-observer readiness signal, resolve exports
     (`getSingletonPtr`, `resourceGroupExists`, `createResourceGroup`,
     `addResourceLocation`, `initialiseResourceGroup`, MaterialManager
     `getSingletonPtr/getByName`);
   - idempotently create group `OseEnhanced`, mount
     `<gamedir>\resources\renderer\enhanced` (recursive, FileSystem), init;
   - validate by `getByName()` on OSE probe + donor programs; log one
     `[RENDER] resources.ogre=yes/no reason=…` line; upgrade
     `CapIblResources` gating from file-tier to Ogre-resolution tier;
   - fail open: any exception/missing export ⇒ capability off, Redux profile.
3. Validation: existing render-profile matrix cases still green; new case
   asserts probe resolution on DX11 and DX9; stock namespace fingerprint
   (material count + spot getByName) unchanged; CR-installed and CR-absent runs.
4. Explicitly out of scope until a follow-up task: donor material library,
   arbiter listener, any stock-material changes.

No merge; prototype behind the standard opt-out switches.

---

## 13. Unknowns (not proven)

1. **cWorkshop staging selection rules**: which mod files become visible to
   i76FS enumeration per lifecycle event. Observed: shell staging exposed
   CR_*.* + chunkMeshes/* but not CR's loose stock-named `.material`s; whether
   mission-load staging exposes the full mod tree is unverified this session
   (captured boot ended before mission launch). Does not affect the OpenShim
   standalone path (bypasses staging entirely), but matters for understanding
   current CR behavior on Workshop installs.
2. **Live OSE_BootstrapProbe run** pending (procedure above). Existing evidence
   covers every individual API call; the probe closes the combined-path proof.
3. **Steam byte-level equality** of the two call sites (0x66485a, 0x6659ed):
   expected identical post-SteamStub-settle per repo precedent; not byte-diffed
   here (GOG static baseline used throughout).
4. **i76FS archive internals** (mod overlay refresh mechanics) not fully RE'd;
   treated as opaque game capability.
5. **Arbitration threading details** under the shipped build's work queue
   configuration (which contexts call getBestTechnique off the main thread);
   implement lock-free and verify empirically.
6. Whether the game ever registers its own MaterialManager::Listener (none
   imported at boot; runtime install unverified — the collision-guard chaining
   code already defends against it either way).

---

## Snapshot inventory

`reverse_engineering/snapshots/enhanced_resource_bootstrap_20260825/`

- `BZOgreLogfile_gog_boot_shell_20260814.log` — full captured session
- `bz_resources_gog.cfg` — stock resource manifest
- `exe_imports_ogre.txt` — exe import table (Ogre API surface actually used)
- `OgreMain_exports_resources.txt` — shipped DLL exports (resource/scheme APIs,
  incl. `_arbitrateMissingTechniqueForActiveScheme`, `addListener`)
- `rizin_resource_bootstrap_disasm.txt` — disassembly around the four key sites
  (config loop/addResourceLocation 0x66485a; initialiseAllResourceGroups
  0x6659ed; Modable clear+init pair; i76FS helper)
- `script_parse_inventory.txt` — all unique scripts parsed in the session
- `stock_bzbase_schemes_and_programs.txt` / `cr_bzbase_schemes_and_programs.txt`
  — scheme/program inventory proving the en-/og- family relationship
