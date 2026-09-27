# ResolveBzrHooks refactor: design (audit P2-1, plan step 1)

Status: design, awaiting approval. Source: `src/patches/bzr_hooks.cpp` on main
`6b5a7bc6`, lines 2173-3416 (1,243 lines).

## What the function is today

`ResolveBzrHooks(isSteam)` runs once per process, from `patcher.cpp:1311`,
after `ResolvePointers` and before the JMP5/rel32 payload fills. Its body falls
into six kinds of work, interleaved:

| Kind | Where | Size | Notes |
|---|---|---|---|
| A. Reset | 2175-2414 | ~240 lines | Nulls, install flags, log budgets, cache clears. Mostly repeats static initializers, but not all: some pointers are re-derived from detour trampolines (`RecordDeath`, `ChunkEffectCreate*`, `AttackTaskDoState`, `ArtilleryDoAttack`, `ScriptCanBuild/IsBusy`, `EarthQuake`, `RecycleTaskDoGotoScrap`), and `g_ChunkEffectCreateHooksReadyTick` depends on `isSteam`. It also calls `RefreshXState()` four times and `InitializeMpauthConfig()`, and reads one env switch. |
| B. Engine addresses | 2416-2527, 2663-2677 | ~90 assignments | 67 raw `0x00xxxxxx` literals, about 15 `kGog*Addr` constants, and 7 `ResolveNamedAddress` calls. None of the literals is verified. |
| C. Inline feature installs | 2528-2659 | ~130 lines | Dynamic alpha batching detour, the DynamicGeometry profiler detour and the RenderQueue IAT hook. This is feature code that the mechanical split left behind. |
| D. Install calls | 2679-2768, 2847, 2989-2990, 3388-3398 | ~45 calls | `Install*IfPossible`, `Initialize*Config`, `Ensure*Scaffold`. |
| E. Switch reads | 2694-2756, 2776-3243 | ~500 lines | About 25 copies of `!(Env("OPENSHIM_DISABLE_X") \|\| Env("BZR_DISABLE_X"))`, about 15 opt-in pairs, and about 12 clamped `TryGetEnvLong`/`Float` reads, some with ini overrides. |
| F. Status log | 3267-3415 | ~150 lines | One line per feature (`[CHUNK]`, `[SATVIS]`, `[MAGNET]` and so on). |

### Ordering constraints the refactor must keep

1. The named resolves in B come before `ResolveEngineFlameRuntimeTargets()`, which retries whichever of the three came back 0.
2. `Assets::RefreshAssetCapabilities()` comes before the chunk-mesh gate.
3. The frustum-cull switches come before `InstallEntityFrustumCullingIfEnabled()`. The existing comment records that a call placed earlier did nothing.
4. `InitializeBzrNetConfig()` has to run before the game reaches BZRNet init, while the P2P socket is still closed.
5. Each fix's enable flag is set before its `Install*` call. The current D block already respects this.
6. `MigrationRequiresSafeFallbackForAttackReveal()` takes precedence over the ini value and the env value.
7. For `OwnedObjectReveal`, `ConstructorRemoteBuild` and `SplinterUndead`, the flag is set twice: a default in A, then the config value in E. Each is followed by a `Refresh*State()` call. The last write wins, and its Refresh call has to follow it.
8. The status log (F) reads the final state, so it stays last.

The magnet zero-range flag is set after `InstallMineTeamFilterHooksIfPossible()`, but the hook reads it at runtime (`team_filter_mines.cpp:276`), so that order is safe.

## Target shape

```cpp
void ResolveBzrHooks(bool isSteam)
{
    g_IsSteamExe = isSteam;
    ResetBzrHookRuntimeState();   // A: bzr_hooks_reset.cpp
    BindEngineAddresses();        // B: one table, one loop
    ReadFeatureSwitches();        // E: switch table plus the few bespoke reads
    RunFeatureInitSteps();        // C+D: ordered step table; constraints 1-7 as comments
    LogBzrHookStatus();           // F: bzr_hooks_status.cpp
}
```

The switch table covers the common case:

```cpp
struct FeatureSwitch {
    bool* flag;
    const char* suffix;        // "MAGNET_ZERO_RANGE_FIX" -> OPENSHIM_DISABLE_ / BZR_DISABLE_
    SwitchPolarity polarity;   // default-on kill switch, or opt-in trace
    bool defaultValue;
    const char* iniSection;    // optional; ini beats env where it does today
    const char* iniKey;
    void (*refresh)();         // optional Refresh*State() called after
};
```

The precedence rules for each switch get a pure helper with a unit test under `tests/`. Bespoke reads stay bespoke: the attack-reveal migration, raw input, skinning trace, and the clamped budgets. The table exists to remove the roughly 40 copies, not to force every read into one form.

## PR slicing (same one-group-per-PR discipline as steps 1-45)

| PR | Change | Behavior change |
|---|---|---|
| R1 | Move C (dynamic alpha batching, profiler detour and IAT hook) into `dynamic_geometry_hooks.cpp`, verbatim. | none |
| R2 | Extract A as `ResetBzrHookRuntimeState()` and F (the contiguous log block) as `LogBzrHookStatus(rawInputActive, rawInputSource)`, verbatim. Both stay in `bzr_hooks.cpp`: moving them out would carry 127 (reset) and 6 (status) feature-state definitions into files named for the reset and the log. Those definitions only stayed in the spine because the reset touches them; their real homes are the feature files (see decision 2). | none |
| R3 | Switch tables for E, plus a unit test. As landed there are two tables: the eleven `[Fixes]` kill switches (read as one block ahead of their installs; each `Refresh*State()` reads only its own flag) and the four frustum/bounds switches. The other env reads are interleaved with logic that depends on them (the generic batch needs the mesh proxy gate, raw input and the budgets clamp), so they stay as written. Every env name is preserved, and the status log must match main exactly. | none |
| R4 | Address table in C++ (`{name, address, void** target}`) replacing the ~90 assignments. Values unchanged; log `[ADDR] bound N of M`. | none |
| R5 | Move the table into `scripts/patches.json` with a prologue `expected_original` per function, so a mismatch leaves the pointer null (fail closed). Needs a null-safety audit of every caller first, because some call unconditionally (for example `native_ui.cpp:1064` after a check at :153, while others don't check). | **yes**: pointers can now be null |
| R6 | Ordered init-step table for D, with constraints 1-7 written beside the steps. | none |

Validation for each PR is what the split used: Release build, ctest, one GOG dx11 boot compared to main. For R3-R6 the comparison adds a diff of the F block and the `[RESOLVE]`/`[DONE]` lines, since those lines expose any change in order or value.

## Decisions needed

1. **R5: move the addresses into `patches.json` and fail closed.** This is the audit's "address table (to patches.json)", and it follows AGENTS.md ("build-specific sites... in patches.json; fail closed"). It is the only slice that changes behavior, and it needs the caller audit plus a Steam boot. Recommendation: yes, as the last slice, and only after R1-R4 land.
2. **Reset placement.** Distributing A into each feature file would touch about 40 files. Recommendation: keep it in one function for now, and move pieces only when a feature file changes for another reason.
