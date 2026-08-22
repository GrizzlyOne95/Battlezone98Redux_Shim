# Satellite (View 3) Ogre Visibility Fix — Implementation Plan

## Root Cause (Confirmed)

Redux creates persistent Ogre scene entities for every GameObject and leaves them
permanently visible (`ogreVis=1`). In BZ 1.5, satellite view ran
`Submit_Overview_Entities` which gated each object through `illumination > 0`
before submitting it to the renderer. Redux collapsed that path: satellite uses
the same ungated Ogre scene traversal as first-person.

The SATVIS probe proved this definitively: enemy mobiles with
`illumination=0, legacyVisible=0` remain `ogreVis=1` across
view-9 → view-3 → view-9 transitions with no entity recreation.

## Design

### Core idea

Interpose Ogre `MovableObject::setVisible` calls on every GameObject-backed
entity when the satellite overview (view 3) is active. The visibility decision
replicates the BZ 1.5 gate: `entity.visible = (originalVisible && illumination > 0)`.

### State management

Each tracked entity gets a `SatelliteEntityVisibility` record keyed by the
**GameObject pointer** (not the Ogre entity), storing both pointers plus the
pre-satellite visibility state and the last applied visibility. This lets us
validate lifecycle integrity on restore: a saved entry is only touched if the
same GameObject still lives and still owns the same Ogre entity.

```cpp
struct SatelliteEntityVisibility
{
    void* gameObject = nullptr;
    void* entity = nullptr;
    bool originalVisible = true;
    bool appliedVisible = true;
};
```

A `bool g_SatVisWasActive` flag tracks the previous tick's satellite state for
transition detection.

### Per-tick logic (`SyncSatelliteVisibility`)

Called from `ChunkEffectSimulateHook` on every sim tick.

```
if !config_enabled:
    return

currentSatellite = IsSatelliteOverviewActive()

// --- Transition: entering satellite ---
if currentSatellite && !g_SatVisWasActive:
    clear g_SatelliteVisibilityState map
    for each live GameObject in arena:
        resolve Ogre entity via +0xF0 → +0x94
        validate with LooksLikeOgreObject
        original = TryReadOgreVisible(getVisible, entity)
        illumination = read float at +0xE8
        desired = original && (illumination > 0.0f)
        call setVisible(entity, desired)
        store {gameObject, entity, original, desired} in map

// --- Steady-state: in satellite ---
if currentSatellite && g_SatVisWasActive:
    build set of currently live GameObjects
    // prune dead entries from map
    for each (key, state) in map:
        if state.gameObject not in live set:
            erase from map
    // update live entries, add new ones
    for each live GameObject in arena:
        resolve Ogre entity
        validate with LooksLikeOgreObject
        if not in map:
            // new object created during satellite — capture actual visibility
            original = TryReadOgreVisible(getVisible, entity)
            desired = original && (illumination > 0.0f)
            call setVisible(entity, desired)
            store {gameObject, entity, original, desired}
        else:
            verify stored entity matches current entity (lifecycle check)
            if entity mismatched: re-capture from scratch
            illumination = read float at +0xE8
            desired = state.originalVisible && (illumination > 0.0f)
            if desired != state.appliedVisible:
                call setVisible(entity, desired)
                state.appliedVisible = desired

// --- Transition: leaving satellite ---
if !currentSatellite && g_SatVisWasActive:
    for each live GameObject in arena:
        if in map and stored entity matches current entity:
            call setVisible(entity, state.originalVisible)
    clear map

g_SatVisWasActive = currentSatellite
```

### Why the map is necessary

Redux does not call `setVisible` on entities in view 9. After our satellite code
hides an entity (`setVisible(false)`), we must restore it when leaving satellite.
The stored original state preserves each entity's explicit Ogre visibility — not
frustum/distance/occlusion culling (those are separate Ogre internals), but the
object's own visibility flag that may have been set to false for animation,
destruction, or culling-setup reasons.

### Configuration

Follow the existing pattern (hop-out alert fix, attack reveal):

| Source | Key | Default |
|--------|-----|---------|
| `[SinglePlayer]` INI | `SatelliteVisibilityFix` | true |
| Environment | `OPENSHIM_DISABLE_SATELLITE_VISIBILITY_FIX` | — |
| Environment | `BZR_DISABLE_SATELLITE_VISIBILITY_FIX` | — |

Precedence: INI explicit > env disable > default ON.

## Implementation Steps

### Step 1: Add struct and globals (~bzr_hooks.cpp:9505)

Near the existing SATVIS globals (after `g_DamageRevealTraceBudget` at line 9507),
add:

```cpp
struct SatelliteEntityVisibility
{
    void* gameObject = nullptr;
    void* entity = nullptr;
    bool originalVisible = true;
    bool appliedVisible = true;
};

static bool g_SatelliteVisibilityFixEnabled = true;
static bool g_SatVisWasActive = false;
static std::unordered_map<void*, SatelliteEntityVisibility> g_SatelliteVisibilityState;
```

### Step 2: Add config loading in `ResolveBzrHooks` (~bzr_hooks.cpp:24966)

After the hop-out alert fix config block (ending line 24969), add a new block:

```cpp
{
    bool satVisFixConfig = false;
    if (TryGetUserConfigBool("SinglePlayer", "SatelliteVisibilityFix",
                             satVisFixConfig))
    {
        g_SatelliteVisibilityFixEnabled = satVisFixConfig;
    }
    else if (EnvFlagEnabled("OPENSHIM_DISABLE_SATELLITE_VISIBILITY_FIX") ||
             EnvFlagEnabled("BZR_DISABLE_SATELLITE_VISIBILITY_FIX"))
    {
        g_SatelliteVisibilityFixEnabled = false;
    }
    else
    {
        g_SatelliteVisibilityFixEnabled = true;
    }
    g_SatVisWasActive = false;
    g_SatelliteVisibilityState.clear();
}
```

### Step 3: Implement `SyncSatelliteVisibility` (~bzr_hooks.cpp:9941)

Place immediately after `MaybeLogSatelliteVisibilitySample()` (line 9940), before
`GetEngineFlamePrimary` (line 9942). Groups the satellite functions together.

The function:

1. Resolves `setVisible` once via `ResolveOgreProc<FnOgreSetVisible>(
   "?setVisible@MovableObject@Ogre@@UAEX_N@Z")` — function-local static,
   matching the pattern at `HideChunkProxyMesh` (line 5059-5060).

2. Resolves `getVisible` via `GetOgreVisibleProc()` (already exists at line 9545).

3. Calls `IsSatelliteOverviewActive()` (already exists at line 9487).

4. Walks the arena via `CollectLiveGameObjectsFromArena` (already exists at
   line 21944).

5. For each object:
   - Calls `TryGetGameObjectFieldBase` to validate (line 9364)
   - Reads `illumination` at `+kGameObjectIlluminationOffset` (0xE8)
   - Follows `+kGameObjectRenderOwnerOffset` (0xF0) → `+kRenderOwnerOgreEntityOffset` (0x94)
   - Validates with `LooksLikeOgreObject` (line 2232)
   - Performs the visibility decision under SEH

6. On satellite exit, walks currently live objects, matches against saved state,
   and restores only when both GameObject and entity pointers match. Clears the
   map after.

Key constants (all already defined):
- `kGameObjectRenderOwnerOffset = 0xF0` (line 2045)
- `kRenderOwnerOgreEntityOffset = 0x94` (line 2046)
- `kGameObjectIlluminationOffset = 0xE8` (line 2016)
- `kViewRecordRva = 0x004EAAD0` (line 1911)
- `kPresetViewCurrentViewOffset = 0x8` (line 2021)
- `kCameraTypeOverView = 3` (line 2057)

### Step 4: Hook into `ChunkEffectSimulateHook` (line 28679)

Call order in `ChunkEffectSimulateHook`:
```cpp
MaybeSuppressStaleHopOutAttackAlert();
SyncSatelliteVisibility();            // <-- NEW, before sampler
MaybeLogSatelliteVisibilitySample();  // <-- sampler sees post-fix state
RefreshChunkObjectIdentityCacheIfNeeded();
```

This ensures SATVIS diagnostic samples observe the actual post-fix Ogre state,
so `[SATVIS] hidden` entries with `LEAK` tags directly confirm the fix's effect.

### Step 5: Diagnostic logging

On satellite entry/exit transitions, log:

```
[SATVISFIX] satellite entered — synced N objects (M hidden)
[SATVISFIX] satellite exited — restored N objects
```

## Constraints

1. **Satellite-only**: The fix is gated on `IsSatelliteOverviewActive()`. Outside
   view 3, no entity visibility is touched.

2. **No persistence across sessions**: The map is cleared on satellite exit and
   on config reload (ResolveBzrHooks).

3. **SEH on every access**: All pointer dereferences and Ogre calls are wrapped
   in `__try/__except(EXCEPTION_EXECUTE_HANDLER)`.

4. **Minimal Ogre traffic**: `setVisible` is only called when the desired
   visibility state actually changes (`desired != appliedVisible`).

5. **Lifecycle safety**: Map keyed by GameObject pointer. On restore, both the
   GameObject and its Ogre entity are re-validated against the saved state.
   Stale entries (dead GameObjects, reused memory) are pruned without touching
   them.

6. **No vtable patches or JMP5 trampolines**: Pure runtime interpose from the
   existing sim-tick hook. No patches.json entries needed.

## Files Modified

| File | Change |
|------|--------|
| `src/patches/bzr_hooks.cpp` | Add struct, globals, `SyncSatelliteVisibility()`, config loading, hook call |

No header changes needed (all functions/file-local).
No patches.json changes needed.
No new files created.

---

## Outcome (2026-08-22)

**Shipped and verified in game.** Enemies placed at the edge of the map are no
longer drawn on the satellite view; they reappear on returning to first person.

The design above was implemented as written in `6fd63817`. What that commit did
not have was any runtime exercise, and a validation pass over it produced the
follow-up in `c2ea3369`:

| Case from the design | Outcome |
| --- | --- |
| Object created while already in satellite | Handled as designed (capture on first sight) |
| Object destroyed while satellite is active | Now swept by tick stamp instead of an O(arena x map) rescan |
| GameObject survives, Ogre `Entity*` changes | Now re-seeds `appliedVisible` as well as `originalVisible`; the new entity no longer inherits the old one's applied state |
| Detection changes dynamically inside view 3 | Handled as designed (recomputed every tick) |
| Repeated normal -> satellite -> normal | Handled as designed |
| Entity already hidden before entry | Handled as designed; now testable via `OPENSHIM_SATVIS_TEST_PREHIDE_TEAM` |
| Non-satellite views unaffected | Unchanged |

Three problems the design did not anticipate:

1. **The restore could clobber another owner.** An entity hidden by something
   else during satellite -- chunk fragmentation hiding a source mesh is the
   real case -- was restored to its pre-satellite value on exit. The restore
   now only fires when the entity still carries the visibility this pass last
   wrote to it, and reports the rest as deferred.
2. **The map could outlive the world.** A mission change destroys every
   GameObject with no teardown callback, and the arena is a fixed-address slot
   table, so the next mission reuses the same addresses. The map is now dropped
   outright when no live player object exists, without dereferencing anything
   in it.
3. **A transient entity-resolution failure could latch an object hidden.**
   Sweeping on "not visited this tick" dropped the record of an object whose
   entity failed to resolve for one tick; the next tick re-captured the
   already-applied hidden state as its `originalVisible`. Entries are now
   stamped on arena presence, not on a successful entity read.

### Measuring it

`reverse_engineering/run_satellite_visibility_validation.ps1` drives the lcbench
`satellite` scenario, which puts each case on its own team, and scores it from
the shim's bounded `[SATVISCHK]` capture (`OPENSHIM_SATVIS_VALIDATE=1`) -- one
row per populated team per second giving population, illumination, resulting
Ogre visibility, and what the fix believes it applied.

Three constraints on driving Redux from a script, all found the hard way:

* `Apply_Satellite_View` (1.5 `0x0047B27F`) is gated on
  `ControlPanel_SatelliteEnabled()`, which in normal play means the player's
  team owns a recycler. `lcbench.bzn` contains only the player, so the fixture
  spawns one; without it the view key is silently inert.
* Redux reads the keyboard through OIS/DirectInput, which works in scan codes.
  A virtual-key-only `SendInput` is accepted by Windows and never seen by the
  game.
* `SendInput` rejects the call with `ERROR_INVALID_PARAMETER` unless `cbSize`
  is the full `sizeof(INPUT)` -- 40 bytes on x64. A union declaring only
  `KEYBDINPUT` measures 32 and every send fails silently. The same defect is
  still present in `run_live_combat_benchmark.ps1`'s load-skip helper.

### Diagnostics

`[Diagnostics] TraceSatelliteVisibility` is back to its default of OFF now that
the characterisation is finished. Use `OPENSHIM_SATVIS_VALIDATE=1` to re-score
the fix; `OPENSHIM_TRACE_SATELLITE_VISIBILITY_FIX=1` logs the entry, exit and
teardown transitions with their counts.
