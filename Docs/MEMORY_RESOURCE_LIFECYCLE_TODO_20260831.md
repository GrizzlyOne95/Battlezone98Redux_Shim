# Mission Resource Lifecycle / x86 Memory Mitigation TODO

Date: 2026-08-31  
Target: Battlezone 98 Redux 2.2.301 / OpenShim  
Status: **TODO / qualification required before implementation**

## Objective

Investigate whether Redux retains mission-specific Ogre/`Modable` assets across mission transitions, especially inside multi-mission custom campaigns, and determine whether OpenShim can safely force an unload or resource-group rebuild between missions to recover 32-bit virtual address space.

This is intended as an x86 memory-pressure mitigation. It does **not** remove the native 32-bit address-space ceiling and is not a substitute for a future Win64 reconstruction.

## Why this matters

The shipped Windows Redux 2.2.301 executable is already `IMAGE_FILE_LARGE_ADDRESS_AWARE`, so on 64-bit Windows it already has essentially the maximum useful 32-bit user virtual-address space (~4 GiB). There is no further PE-header/LAA upgrade available.

The practical problem is therefore one or both of:

- cumulative resource retention across mission loads;
- address-space fragmentation that leaves too little contiguous VA for large texture/mesh allocations.

This is especially relevant to large mod content. Repeated real-world failures have been observed with:

- large/high-resolution textures;
- high-poly meshes;
- large custom campaigns and content sets.

A mission-to-mission resource purge could materially extend the useful life of the existing x86 executable if Redux currently keeps prior-mission assets resident.

## Existing evidence

### 1. Windows Redux is already LAA

The shipped GOG 2.2.301 executable was qualified directly as:

```text
PE32 / i386
IMAGE_FILE_LARGE_ADDRESS_AWARE = enabled
IMAGE_FILE_32BIT_MACHINE = enabled
relocations stripped
ImageBase = 0x00400000
```

Therefore OpenShim should not treat LAA as an unresolved mitigation.

### 2. The shipped Mac build is a 64-bit peer build

A local reconstruction qualification of Steam depot `301651`, manifest `730966170255625169`, proved the shipped Mac executable is a thin PIE Mach-O **x86_64** image with product version 2.2.301.

The Mac binary preserves extensive C++ identity information, including named RTTI, vtables, translation units, function starts, and source paths, and has `PEER_BUILD_CONFIDENCE = HIGH` relative to Windows 2.2.301.

This gives us a strong 64-bit oracle for Redux resource/lifecycle code.

### 3. `cWorkshop` resource rebuild functions map directly across Windows and Mac

The following functions are already cross-mapped:

| Mode | Windows x86 | Mac x86_64 | Behavior |
|---:|---|---|---|
| 4 | `0x0076A030` | `0x1000A9FC8` `cWorkshop::buildModResources()` | guard mode; clear runtime/path state; remove mod paths; clear/reinitialize Ogre `Modable`; rebuild runtime resources |
| 2 | `0x0076A240` | `0x1000A9D7C` `cWorkshop::buildMPResources()` | same pattern |
| 1 | `0x0076A430` | `0x1000A9B48` `cWorkshop::buildIAResources()` | same pattern |

Shared behavior includes:

```text
Ogre76Archive::removeAllModPaths()
ResourceGroupManager::clearResourceGroup("Modable")
ResourceGroupManager::initialiseResourceGroup("Modable")
runtime resource rebuild
```

The corresponding fields also map across ABIs:

| Field | Windows x86 | Mac x86_64 |
|---|---:|---:|
| `cWorkshop::mode` | `+0x8C` | `+0x148` |
| remembered content identity | `+0x90` | `+0x150` |

This proves Redux already contains a supported internal concept of tearing down and rebuilding `Modable` resources. The open question is **when it is invoked** and whether ordinary mission-to-mission transitions inside one campaign bypass it.

### 4. The Mac peer build proves explicit fixed-width serialization

Mac `GameObject::Load/Save` uses typed field serialization with explicit byte counts rather than dumping native in-memory structs. Lua/game object handles also remain 32-bit opaque IDs on x86_64.

This is relevant because a resource-lifecycle change should not require altering save/BZN/Lua handle semantics.

## Primary hypothesis

Redux may initialize/rebuild `Modable` primarily when the content identity or game mode changes, while ordinary mission transitions inside the same campaign retain the same resource group and some or all prior mission assets.

Conceptually, stock behavior may resemble:

```text
Campaign starts
    -> Modable initialized
    -> Mission 1 loads resources
    -> Mission 1 ends
    -> Mission 2 loads additional resources
    -> Mission 2 ends
    -> Mission 3 loads additional resources
    -> ...
```

If prior mission resources remain referenced or registered in Ogre managers, memory pressure could grow until the 32-bit process cannot satisfy a large contiguous allocation.

The desired behavior, if safe, is closer to:

```text
Mission 1
    -> mission teardown
    -> purge old mission resources
    -> reinitialize retained resource locations
    -> Mission 2
```

This hypothesis is **not yet proven**. Instrument first; change behavior only after retention is demonstrated.

# TODO

## Phase 1 — Add memory / VA telemetry

Add development-only OpenShim instrumentation that can snapshot at least:

- process committed bytes;
- private bytes;
- working set;
- total free user virtual address space;
- largest contiguous free VA region;
- number of free VA regions;
- optionally counts of large committed regions / allocation size buckets.

Use `VirtualQuery`/Win32 APIs appropriate to a 32-bit process.

The most important value is **largest contiguous free VA region**, because a process can have substantial total free VA while still failing a large allocation due to fragmentation.

Suggested log form:

```text
[MEM] mission=misn01 phase=loaded committed=... private=... free_va=... largest_free=...
```

## Phase 2 — Add Ogre resource-count telemetry

Where safe against the shipped BZR Ogre ABI, record resource counts around mission transitions for at least:

- textures;
- meshes;
- skeletons;
- materials;
- resources in the `Modable` group.

Do not assume pristine upstream Ogre 1.10 ABI layouts; validate all runtime-facing calls against the shipped game Ogre binary.

Useful transition points:

```text
Mission A loaded
Mission A exit begins
Mission A teardown complete
Mission B before resource load
Mission B loaded
```

## Phase 3 — Prove or disprove cumulative retention

Build or use a deterministic multi-mission custom campaign with intentionally distinct heavy assets per mission.

Example fixture:

```text
Mission 1: unique texture/mesh set A
Mission 2: unique texture/mesh set B
Mission 3: unique texture/mesh set C
Mission 4: unique texture/mesh set D
```

Record VA and Ogre-resource snapshots at every transition.

Evidence for retention would look like:

```text
Mission 1 loaded: textures=400 meshes=250 committed=1.7 GB
Mission 1 exited: textures=395 meshes=246 committed=1.65 GB
Mission 2 loaded: textures=700 meshes=430 committed=2.4 GB
Mission 2 exited: textures=695 meshes=425 committed=2.35 GB
```

A healthy lifecycle should instead show most mission-specific resources disappearing or memory reaching a stable plateau.

Do not proceed to an automatic purge unless this phase proves a meaningful retention/fragmentation problem.

## Phase 4 — Identify the exact safe mission-lifecycle hook

Use both:

- named Mac x86_64 lifecycle/resource functions; and
- Windows 2.2.301 static/runtime mapping

to identify the point where:

```text
old mission objects are destroyed
old Lua mission state is gone
old terrain/render entities are released
no old GameObject/Ogre entity should hold mission resources
NEW MISSION HAS NOT YET CREATED NEW OBJECTS
```

This is the preferred purge window.

Do **not** clear `Modable` while old `GameObject`, terrain, UI, or renderer objects may still retain `Ogre::MeshPtr`, `MaterialPtr`, `TexturePtr`, `Entity*`, or related references.

Useful Mac symbols to inspect first include mission load/unload/destruction paths, `GameObject` teardown, Lua mission destruction, terrain cleanup, and `cWorkshop` rebuild callers.

## Phase 5 — Test conservative unload behavior first

If Redux/Ogre supports it safely in this lifecycle, test the least destructive option first, for example unloading unreferenced resources or `unloadResourceGroup("Modable")` semantics.

Qualification questions:

- does committed/private memory decrease?;
- does largest free VA recover?;
- are resource manager entries actually removed, or only GPU backing stores unloaded?;
- are campaign-global/shared assets immediately and correctly reloaded?;
- do later missions render correctly?;

For the x86 VA problem, merely unloading GPU state is not enough if CPU-side Ogre resource objects and allocations remain resident.

## Phase 6 — Test aggressive `Modable` clear/reinitialize

If conservative unloading does not reclaim enough address space, experimentally reproduce the already-proven Redux rebuild sequence at the safe transition point:

```text
ResourceGroupManager::clearResourceGroup("Modable")
ResourceGroupManager::initialiseResourceGroup("Modable")
```

Avoid `removeAllModPaths()` in the first experiment unless evidence shows it is required. The goal is to purge resources while preserving the current campaign's resource locations if possible.

Only expand toward the full `cWorkshop` rebuild sequence when necessary and understood.

## Phase 7 — Compare before/after memory recovery

For every experimental purge, log a paired snapshot:

```text
[MEM] transition purge before
  committed=...
  private=...
  free_va=...
  largest_free=...
  textures=...
  meshes=...

[MEM] transition purge after
  committed=...
  private=...
  free_va=...
  largest_free=...
  textures=...
  meshes=...
```

Primary success metrics:

- lower mission-to-mission committed/private growth;
- larger recovered contiguous VA regions;
- stable resource counts over repeated transitions;
- no missing materials/textures/meshes;
- no stale Ogre references or crashes;
- no save/load regression;
- no mission restart regression.

## Phase 8 — Stress qualification

Qualify against at least:

1. stock campaign mission transitions;
2. custom Lua campaign transitions;
3. mission restart;
4. save/load into the current mission;
5. Instant Action -> menu -> another IA mission;
6. Campaign -> menu -> Campaign;
7. large 4K/8K texture fixture;
8. high-poly mesh fixture;
9. repeated transition loop long enough to expose cumulative growth.

Single-player qualification should precede multiplayer. Any eventual multiplayer use must be separately evaluated for synchronization/lifecycle implications; resource purge itself should remain local-only and must not alter network-visible game state.

## Phase 9 — Possible OpenShim configuration

Only after runtime qualification, consider an opt-in setting such as:

```ini
[Memory]
MissionResourcePurge = 0
```

Possible semantics:

```text
0 = stock Redux lifecycle
1 = conservative unload of safe/unreferenced mission resources
2 = clear/reinitialize Modable between qualified mission transitions
```

Names and levels are provisional. Do not ship them until the underlying behaviors are proven safe and useful.

## Phase 10 — Long-term lifecycle model

If the brute-force purge proves valuable, investigate whether OpenShim can distinguish:

```text
CORE      - never unloaded
CAMPAIGN  - retained between missions in one campaign
MISSION   - destroyed on every mission transition
```

This would be preferable to repeatedly rebuilding the entire `Modable` group, but it is a later architectural improvement, not the first implementation target.

# Risks / failure modes

- Clearing Ogre resources while live objects still reference them can cause use-after-free crashes.
- Campaign-global materials/textures may currently depend on remaining resident across missions.
- Resource reload may introduce mission-start hitching.
- Renderer/material aliasing or BZR-specific Ogre ABI behavior may differ from pristine Ogre 1.10 assumptions.
- Audio assets may have a separate lifetime system and should not be assumed to follow `Modable`/Ogre semantics.
- UI/shell resources may share resource groups unexpectedly.
- A lower working set does not prove VA fragmentation was fixed; always record largest contiguous free VA.
- Successful `clearResourceGroup` calls do not prove all resource-manager entries or allocator regions were returned to the OS.

# Success gate

This TODO should be considered ready for an implementation PR only when the following are evidenced:

```text
RETENTION_OR_FRAGMENTATION_PROBLEM = PROVEN
SAFE_TRANSITION_HOOK = PROVEN
PURGE_RECLAIMS_MEANINGFUL_VA = PROVEN
MULTI_MISSION_RENDERING_STABLE = PROVEN
SAVE_RESTART_REGRESSIONS = NONE OBSERVED
```

A particularly strong result would be a stress campaign where stock behavior shows monotonically worsening VA/resource counts or an allocation failure, while the experimental purge causes memory use to plateau and the same campaign completes successfully.

# Relationship to BZR64 work

The macOS x86_64 peer build has made a source-equivalent Win64 reconstruction materially more credible, but that remains a much larger project.

Mission-lifecycle cleanup is valuable even if BZR64 is eventually achieved because it improves resource ownership correctness and may reduce unnecessary memory use on all architectures.

For the current Windows executable, however, this work is one of the strongest available paths to buying additional practical headroom without replacing the engine.