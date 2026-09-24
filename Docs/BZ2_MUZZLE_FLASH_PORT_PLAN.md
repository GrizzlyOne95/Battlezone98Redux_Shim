# BZ2-Style Muzzle Flash Port Plan for OpenShim

## Goal

Add Battlezone 2-style transient muzzle flash to Battlezone 98 Redux through OpenShim with the smallest practical native surface.

The target behavior is the classic BZ2 weapon flash system:

```text
successful weapon shot
    -> attach transient particle/billboard at muzzle hardpoint matrix
    -> hold for flashDuration (sim-time or tick-locked)
    -> detach and free, no gameplay side effects
```

This document is a design/research artifact only. It does not implement hooks or change runtime behavior.

## BZ2 behavior to preserve

Research against BZ2 `v1.3.7 / b131p` (`bzone.exe`, `bz2edit.exe`, `publics.txt`) recovers the following semantics (`GrizzlyOne95/BZ2_Source` `origin/main`, `docs/BZ2_MUZZLE_FLASH_SUBSYSTEM_ARCHITECTURE.md`, 126 lines):

- Base `Weapon` class owns the flash; all 10 derived types call it: `Cannon`, `MachineGun`, `Launcher`, `MultiLauncher`, `SalvoLauncher`, `TargetingGun`, `MagnetGun`, `RemoteDetonator`, `ChargeGun`, `DamageField`.
- Spawn entry: `Weapon::BuildFlashEffect 0x00584A67(Matrix *nodePlus0x90, SimParams*)`.
  - Callers pass `(FamilyNode +0x3DC) + 0x90` as the `Matrix*` argument.
  - Invokes `ParticleRenderClass* prototype (WeaponClass +0x5F0)->vtable+0x0C(this+0x450, node+0x90)` to attach the live instance.
  - Guard `*(this+0x450)==0` prevents double-attach.
  - Spawn guard requires `g_WorldCount>1 && CurrentWorld != g_ShowWorld` OR translation `param+0x30/0x34/0x38` ABS `>=0.0001f`.
- Config keys in `WeaponClass::WeaponClass 0x00585DC5` via CRC32:
  - `flashName CRC 0xa3c709c1` via `GetEffectClass -> WeaponClass +0x5F0`, raw string CRC `+0x6B4`.
  - `flashDuration CRC 0x1fe6f089` via `GetFloat -> WeaponClass +0x63C` (seconds).
- Instance state on `Weapon`: `+0x3DC FamilyNode*`, `+0x450 ParticleRenderPointer (0=inactive)`, `+0x454 float dt-mode remaining`, `+0x458 uint tick-mode deadline`, `+0x45C WeaponClass*`.
- Lifetime: `Weapon::UpdateFlashEffect 0x005849E4` every sim frame; `Weapon::DetachFlashEffect 0x00584A46`; `~Weapon 0x005853F6` final `Detach`.
  - Branch on `((uint)unaff_ESI >> 0x18)==0`: dt-mode (`+0x454=flashDuration`, `+0x458=0`, decrement by `*(float*)simParams`) vs tick-mode (`+0x458=__ftoui3()+TimeManager::s_pInstance+0x78`, `+0x454=0`, expire when `tick >= +0x458`).
  - Conditional early detach when `*(this+0x3EC)!=0 && ...+0x2B4 &0x80 && simParams+0x28==2`.
- Relation to siblings: flash is a visual particle at the converged muzzle matrix; recoil (`docs/BZ2_RECOIL_SYSTEM_ARCHITECTURE.md`) translates the recoil mesh (`-0.6`, `+3.0/s`, `0.2s`); convergence (`docs/BZ2_SHOT_CONVERGENCE_SUBSYSTEM_ARCHITECTURE.md`, `Craft::UpdateWeaponAim`, `BuildDirectionalMatrix`, `TurretControl::Control`) re-aims the hardpoint flash inherits. No `BuildDirectionalMatrix` inside `BuildFlashEffect` itself.

## BZ1 / Redux behavior already native in BZR

Research against BZ1 `origin/main` (`research/Redux_VFX_Sprite_Render_System_Analysis.md`, 220 lines, #19) plus stock ODFs:

- VFX is factory-based: ODF `RenderClass` -> `Render` instance. `MultiRenderClass` (`renderCount` hash `0x8c8e76ec`, `renderName%d`), `SpriteRender` billboard (`useterraincolor` hash `0x876e1b38` `+0x184`, terrain-light ARGB pack), `SphereRender draw_sphere` (6 deg->rad angles), `Ember/ParticleSimulate sim_ember` (`lifeTime +0xE0=1.0`, `StartDelay +0xE4`, `maxCount +0xE8=0x40`).
- Stock muzzle-adjacent assets are persistent ordnance beams, not BZ2-style transients: `flash.odf/flashb/flashg` (`[OrdnanceClass] classLabel=beam, renderName=flash.render, lifeSpan=90e-6, shotSpeed=1e6` + `[Render] renderBase=draw_multi` + `[Beam] renderBase=draw_bolt`), `gflashgb/gg/gn.odf` (`[WeaponClass] classLabel=beamgun, ordName=flashb/flashg/flash`). BZR `reference/migration-2026-09-22/StockODFFiles/` (6081 entries, incl. `flash*.odf`, `apflsh*.odf`, `blast.odf`) is ground truth.
- Conclusion: BZR already renders the ordnance-trail half natively. What is missing is the BZ2 transient muzzle-attached flash (`flashName/flashDuration` + `node+0x90` attach + sim-time detach). OpenShim should add only that layer, not reimplement `draw_multi/draw_bolt`.

## Proposed authoring compatibility

Accept the BZ2 naming convention directly:

```ini
flashName = "muzzle_flash_effect"
flashDuration = 0.12
```

This gives content authors a familiar and portable convention. ODF parse must be fail-closed: absent keys preserve stock behavior exactly.

Optional OpenShim extensions may be supported later:

```ini
flashScale1 = 1.0
flashLight1 = 0.0
```

Recommended defaults when omitted: mirror stock BZ2 `flashDuration` from the weapon class; do not invent a global flash if the ODF declares none. The first implementation should not require extension keys.

## Minimum runtime architecture

A compact transient controller is sufficient (schematic names; exact BZ1 vector/node types TBD during Phase 0):

```cpp
struct MuzzleFlashController
{
    void*  ownerWeapon;   // live weapon instance key, never dereferenced after free
    void*  billboard;     // Ogre BillboardSet / effect handle, null when inactive
    float  remaining;     // dt-mode remaining seconds
    unsigned deadline;    // tick-mode deadline (if BZ1 needs tick-locked parity)
    bool   active;
};
```

### Fire

```cpp
void Fire(MuzzleFlashController& flash, const Matrix& muzzleWorld, float duration)
{
    AttachBillboard(flash, muzzleWorld);
    flash.remaining = duration;
    flash.active = true;
}
```

### Update

```cpp
void Update(MuzzleFlashController& flash, float dt)
{
    if (!flash.active)
        return;
    flash.remaining -= dt;
    if (flash.remaining <= 0.0f)
        Detach(flash);
}
```

### Detach

Conceptually:

```cpp
DetachBillboard(flash); // free Ogre handle, null it
flash.remaining = 0.0f;
flash.active = false;
```

The implementation must use the existing BZ1 muzzle world matrix and must not introduce a parallel renderer-side transform system. Follow the BZ2 invariant: `current visual = attached to live muzzle matrix + sim-time expiry`, never incremental drift.

## Required integration points

### 1. ODF/config parse

At weapon/class initialization, inspect each weapon for `flashName` / `flashDuration`.

Requirements:

- absence of the keys must preserve stock behavior exactly;
- invalid/missing effect names must fail closed and leave that slot without flash;
- diagnostics should identify the ODF, slot, and missing effect when useful;
- parsing must respect whatever locale-safe ODF path OpenShim currently uses (`src/patches/odf_compat.cpp` effect keys).

### 2. Muzzle-pose resolution

Once the weapon/vehicle hierarchy exists, resolve the live muzzle world matrix (BZR already decodes this for convergence: `Weapon::Control 0x00611610`, `M=weapon+0x28`, `I=weapon+0x68`, `muzzle=weapon+0x1C`, `RefreshWeaponTransform 0x00681A00`, `UpdateWeaponAim 0x005F0930/0x005F27B0`, `include/weapon_convergence.h`, `include/bzr_object_layout.h:120-124`).

Do not search the hierarchy by name every simulation frame. Cache the node/handle at bind time; read the world matrix at fire time.

### 3. Successful-shot hook

This is the most important correctness requirement. Mirror `docs/BZ2_RECOIL_PORT_PLAN.md`:

Do not trigger flash on:

```text
fire key/button down
```

Trigger only when the game has actually committed a weapon shot/ordnance creation or equivalent accepted firing event (candidates, unproven: `Ordnance::Init 0x00480340 / detour 0x004803D4`, `FUN_00586ff0`, the 8 `0x005B…/0x004F…/0x0058…` firing sites, `Weapon::Trigger` vtable+8).

This is needed so flash naturally respects cooldown, ammo, enable/disable, AI firing, burst cadence, linked weapons, and refused triggers. Locate the narrowest common shot-commit path rather than patching every input path; share the trigger with the recoil controller where possible.

### 4. Simulation/update hook

Advance active flashes using simulation delta time (preferred) or tick counter if BZ1 parity requires it.

Preferred ownership: vehicle/weapon simulation path if a safe common hook exists; otherwise a bounded OpenShim per-weapon update registry keyed to live weapon instances. Avoid renderer-frame timing if possible so flash duration is stable across variable FPS.

### 5. Lifetime/destruction

Controllers must not outlive the associated weapon, vehicle, or effect handle. Required cleanup mirrors recoil plus renderer handles:

- weapon unmount/destruction (BZ2 `~Weapon` calls `Detach`);
- vehicle destruction;
- map unload / mission restart;
- object replacement/recycling;
- multiplayer object teardown;
- Ogre `BillboardSet` / effect handle release (null after free).

## Shared muzzle nodes / linked weapons

Multiple weapon slots may fire through the same hardpoint in one tick. Do not allow two controllers to fight over one billboard handle, and do not accumulate opacity/scale unintentionally.

Preferred design: one controller per weapon instance (mirrors BZ2 `Weapon+0x450`), with `Fire` re-arming the existing active flash (reset `remaining = flashDuration`) rather than allocating a second overlapping instance. This matches the BZ2 `+0x450==0` double-attach guard semantics while handling same-tick linked fire gracefully.

## Transform semantics

Mirror the BZ2 property:

```text
flash pose = live muzzle world matrix at fire time (+ follow if BZ1 node animates during flash)
```

Decide explicitly in Phase 0 whether the billboard follows the node for its short life (BZ2 attach semantics) or is a fire-time snapshot. Either is defensible; document the choice. Do not implement world-axis hard-coding; the pose must inherit convergence (`UpdateWeaponAim` output), consistent with BZ2 where flash follows the aimed hardpoint.

## Multiplayer/networking

Treat flash as deterministic local presentation derived from an already-networked firing event, exactly as recoil does.

Do **not** add a new flash network packet. Expected model:

```text
existing authoritative/replicated shot event
    -> each peer triggers same local flash controller
```

Qualification must verify local player, remote player, AI on host, AI visibility on clients, late replication, and linked cadence. If remote replicas do not execute the same shot-commit path, add a replica-side visual trigger at the existing ordnance/fire receive boundary (cf. `mp_ordnance_duplication_popgun_comparison_20260827.md`: `FUN_005a6460` gated vs `FUN_005da6e0` ungated — do not assume `FUN_00586ff0` is the net sender).

## Savegames

Do not patch the save format in Phase 1. Flash is transient (BZ2 durations are fractions of a second); restore all controllers to detached/inactive after load. Exact persistence can be revisited only with a compelling reason.

## Safety / compatibility requirements

The feature must be inert unless an ODF explicitly declares `flashName`.

Required failure behavior:

- unsupported executable/build: do not install hooks (fail closed, `BZR_EXPECTED_VERSION 301`, `scripts/patches.json` identity);
- missing effect asset: skip flash for that slot, stock firing unaffected;
- destroyed/stale weapon: never dereference cached pointers/handles;
- unknown weapon class: stock firing unaffected;
- config parse failure: no flash rather than broken weapon;
- renderer handle failure: detach and continue, never leak `BillboardSet`s.

The feature must not alter damage, projectile direction, cadence, ammo, hardpoint selection, or physics. It is presentation-only.

## Reusable OpenShim patterns (do not reinvent)

- `sun_flash` (`include/sun_flash.h`, `src/patches/sun_flash.cpp`): REL32 call-site redirect + naked thunk + fail-closed verify. Use this discipline for any `ScreenFlash`-adjacent exposure pump, and leave explosion callers `0x0047F605,0x004AD2C2` untouched unless explicitly in scope.
- `EngineFlame` fork (`include/bzr_hooks.h:104-106`, `reverse_engineering/engine_flame_color_notes.md`): hook before `AddFlame` while owner is known, route to cloned managers, patch vtable slots. Template if flash needs owner-aware routing.
- Ordnance/convergence detours (`src/patches/bzr_hooks.cpp:1180-1289`, `trampolines.cpp`): JMP5 over whole instructions preserving `EBP` frame. Reuse the shot-commit site if recoil already pins it.
- `render_effect_intent.h` (`SSAO/DepthHaze/SoftParticles`): long-term provider for soft-particle/HDR flash; `DX11_ENHANCED_RENDERING_ROADMAP.md:346-394` already reserves additive emissive/projectile + muzzle exposure.
- Compat payload (`src/engine/dx11_legacy_material_compat.cpp`, `resources/renderer/enhanced/`, `ENHANCED_RENDERER_MATERIAL_OWNERSHIP.md`): add a muzzle/additive technique here rather than forking materials per-weapon.

## Suggested implementation phases

### Phase 0 - BZ1 engine trace

Before editing runtime behavior, identify and document:

1. BZ1 weapon instance/class layout used by Redux (equivalents of BZ2 `+0x450/+0x454/+0x458/+0x45C`).
2. Per-weapon slot storage and weapon build path.
3. ODF parser path for weapon flash properties.
4. Muzzle hardpoint world-matrix source (`weapon+0x28/+0x68/+0x1C` validation).
5. Common successful-shot commit path (shared with recoil if possible).
6. Safe weapon/vehicle destruction hook.
7. Simulation delta-time / tick source.
8. Ogre world billboard/particle spawn path (only `BillboardSet` debug + chunk proxies exist today).

Deliverable: address/symbol report with no behavior patch. Register future sites in `scripts/patches.json` + `include/patches.h` + `src/engine/patcher.cpp` per `docs/AGENT_PATCH_WORKFLOW.md`.

### Phase 1 - One-shot proof of concept

Hard-code or debug-configure one known test vehicle/weapon and prove a billboard appears at the muzzle on committed fire and detaches on time. Do not ship hard-coded content behavior.

### Phase 2 - `flashName` / `flashDuration` parser and slot mapping

Add BZ2-compatible parsing and controller creation. Test: one weapon/one flash, two weapons/two flashes, two weapons rapid alternate fire, no flash keys, invalid flash name.

### Phase 3 - successful-shot trigger

Wire to the confirmed shot-commit path. Test: player single-shot, automatic, AI, empty ammo, held trigger during cooldown, linked weapons.

### Phase 4 - multiplayer qualification

Validate host/client visual agreement and lifetime. No flash-specific networking unless fire replication proves insufficient.

### Phase 5 - optional tuning keys

Only after stock-compatible behavior is proven, consider `flashScaleN` / `flashLightN` or HDR/bloom wiring. Keep default behavior identical to `flashDuration`.

## Recommended test asset

Create a deliberately simple vehicle with one cannon and a high-contrast muzzle marker. Test ODF:

```ini
flashName = "test_flash"
flashDuration = 0.12
```

Expected trace:

```text
t = 0.000  shot commits, billboard attached at muzzle, remaining = 0.120
t = 0.060  billboard still attached (or following node per Phase 0 decision)
t = 0.120  detach, handle nulled
```

Exact samples depend on sim tick; duration must be sim-time stable, not FPS-dependent.

## Instrumentation recommendations

For development builds, log only transitions:

```text
[Flash] bind weapon=<id> effect=test_flash duration=0.120
[Flash] fire weapon=<id> pose=<muzzle>
[Flash] detach weapon=<id> reason=expired|destroyed|unload
[Flash] missing weapon=<id> effect=missing_name
```

Optional verbose logging can include muzzle matrix and rest/axis for qualification builds.

## Explicit non-goals

Do not combine this work with camera kick, view sway, physics impulse, generic skeletal animation, renderer redesign, projectile/netcode changes, or BZ2 secondary joint recoil unless a concrete BZ1 use case is identified. Ordnance trails (`draw_bolt`/`draw_multi`) stay native.

## Remaining research gates

Before implementation is merge-ready, resolve:

1. Exact BZ1 successful-shot hook (shared with recoil?).
2. Exact BZ1 muzzle world-matrix source and follow-vs-snapshot semantics.
3. Exact Ogre world billboard/particle spawn + destroy path.
4. Transient-light spawn hook if flash should emit light (headlight/flashlight policy at bridge `+0xA8` exists but is not generalized).
5. Object/model lifetime safety for controllers + Ogre handles.
6. Replica behavior in multiplayer.
7. Whether any existing OpenShim transform hook can be reused instead of adding another patch site.

## Acceptance criteria

Shipping Phase 1 is successful when stock content without `flashName` is bit-for-behavior unaffected; a configured weapon shows a muzzle-anchored transient on actual fire (player + AI); duration honors `flashDuration` in sim time; shared/rapid fire does not leak or double-draw; destroyed/unloaded objects leave no stale handles; MP requires no new packet; no weapon gameplay values change.

## Sources

- `BZ2_Source origin/main c3e9488a`: `docs/BZ2_MUZZLE_FLASH_SUBSYSTEM_ARCHITECTURE.md`, `docs/BZ2_SHOT_CONVERGENCE_SUBSYSTEM_ARCHITECTURE.md`, `docs/BZ2_RECOIL_SYSTEM_ARCHITECTURE.md`.
- `BZ1_Source origin/main 6c05b7e31`: `research/Redux_VFX_Sprite_Render_System_Analysis.md`; stock `1.5/Battlezone_Install/stock/flash.odf`, `flashb/g.odf`, `gflash*.odf`.
- `BZR-OpenShim origin/main 36754d6e`: `docs/BZ2_RECOIL_PORT_PLAN.md`, `DX11_ENHANCED_RENDERING_ROADMAP.md`, `ENHANCED_RENDERER_MATERIAL_OWNERSHIP.md`, `src/patches/bzr_hooks.cpp`, `sun_flash.*`, `weapon_convergence.h`.
- `BZR-Workspace reference/migration-2026-09-22/StockODFFiles/`: `flash.odf`, `blast.odf`, `apflsh.odf`, `gflashgn.odf`.
