## Producer Build Menu RE Notes

Date: 2026-03-15  
Current implementation status updated: 2026-08-12

Goal: find a viable native path for submenu-capable producer build menus so
`Producer` descendants like Recycler, Factory, Armory, and Constructor can use
`Builder`-style nested menus instead of ODF hot-swapping tricks.

### Summary

- The shipped `build.odf` / `build_a.odf` / `b_amcmbt.odf` submenu system is
  real, native, and recursive.
- That submenu system appears to be the editor / placement build tree, not the
  stock in-mission producer build menu path.
- Stock producer units still use flat `[ProducerClass] buildItem1..10` lists.
- OpenShim now has an opt-in producer bridge that reuses the native recursive
  `BuildItem` loader and can select a root directly from the producer's ODF.
- The remaining proof is runtime UI navigation and leaf handoff into the normal
  producer build path.

### Confirmed Native Builder Tree Behavior

Using the GOG EXE for analysis, with cross-checks against the Steam EXE:

- Both EXEs contain the same menu strings at the same mapped addresses:
  - `build.odf`
  - `b_amcmbt`
  - `b_ambldg`
  - `b_amprod`
  - `b_socmbt`
  - `b_sobldg`
  - `b_soprod`
  - `b_nebldg`
- In the GOG EXE, code around `0x004A0185` opens `build.odf`.
- If `build.odf` is unavailable, the EXE falls back to a hard-coded table of
  submenu roots stored into globals at:
  - root name: `0x009174C4`
  - menu table pointer: `0x009174DC`
- The fallback table includes entries for:
  - `b_amcmbt`
  - `b_amprod`
  - `b_ambldg`
  - `b_amsign`
  - `b_socmbt`
  - `b_soprod`
  - `b_sobldg`
  - `b_sosign`
  - `b_nebldg`

Code around `0x0049F5C0` behaves like the real recursive submenu loader:

- It formats `%.8s_mp.odf` first, then falls back to `<name>.odf`.
- It checks whether the target ODF is a `[Builder]` record.
- If it is a `[Builder]` record, it allocates ten child slots and recursively
  loads `buildItem1..10`.
- If it is not a `[Builder]` record, it resolves the name as a leaf buildable
  item instead.

This is the existing submenu mechanism we want to reuse.

### Stock ODF Evidence

The stock ODFs in
`<GAME_ROOT>\Edit\stock`
split cleanly into two systems:

Builder tree files:

- `build.odf`
- `build_a.odf`
- `build_s.odf`
- `build_b.odf`
- `build_c.odf`
- `build_h.odf`
- `build_o.odf`
- `build_pw.odf`
- `b_amcmbt.odf`
- `b_ambldg.odf`
- `b_amprod.odf`
- `b_socmbt.odf`
- `b_sobldg.odf`
- `b_soprod.odf`

Producer unit files:

- `avrecy.odf`
- `avmuf.odf`
- `avslf.odf`
- `avcnst.odf`

Those producer units still use flat `[ProducerClass] buildItemN = "..."` lists,
for example:

- Recycler: `avrecy.odf`
- Factory: `avmuf.odf`
- Armory: `avslf.odf`
- Constructor: `avcnst.odf`

Relevant stock class labels:

- Recycler: `classLabel = "recycler"`
- Factory: `classLabel = "factory"`
- Armory: `classLabel = "armory"`
- Constructor: `classLabel = "constructionrig"`

So simply editing `build.odf` does not automatically give nested producer menus.

### PDB Clues

The GOG PDB is not a perfect executable match, but it still gives useful names:

- `InitBuildItem`
- `CleanupBuildItem`
- `RecurseBuildItem`
- `buildMenu`
- `Producer::UpdateModeList`
- `Producer::SetActiveMode`
- `Producer::StartBuild`
- `Armory::UpdateModeList`
- `Armory::SetActiveMode`

That strongly supports the observed split:

- one native path for recursive `BuildItem` trees
- another native path for producer mode/build selection

### Important Implication

The existing submenu logic is already solved by the game. The missing feature is
that stock producers do not route through it.

The problem is therefore not "invent submenus from scratch".

The problem is "bridge Producer build selection to the existing BuildItem tree".

### Viable Patch Direction

Recommended implementation strategy:

1. Read a producer-facing ODF field such as `buildMenuRoot`.
2. Hook the producer menu setup path for `Producer` descendants.
3. If the selected unit is an eligible producer class and the field exists,
   build a `BuildItem` tree from that root using the existing native recursive
   loader behavior instead of the stock flat `buildItem1..10` path.
4. Keep the stock behavior as fallback when the override field is absent.
5. Return leaf selections back into the normal `Producer::StartBuild` flow so
   actual construction remains native.

Steps 1-4 now have a first implementation. Step 5 is the main live-validation
question.

### Builder-tree Side Reused

The bridge uses the native cluster around:

- `0x0049F5C0` recursive `BuildItem` loader behavior
- `0x0049F880` recursive cleanup behavior
- global build-menu root at `0x009174C4`

### Why This Looks Safer Than ODF Hot-Swapping

- It preserves the game's existing native submenu semantics.
- It aims to keep leaf builds in the normal producer construction path.
- It can be opt-in per producer ODF.
- It avoids mutating global stock build ODFs at runtime.
- It should support class-specific menus for Recycler / Factory / Armory /
  Constructor without having to fake unit identities.

### Cautions

- The stock builder-tree path uses global state, which may be unsafe to share
  across multiple live producer units if selection boundaries do not rebuild it
  reliably.
- A production implementation may need per-instance/per-class `BuildItem` state
  or deterministic root restoration.
- Constructor uses `classLabel = "constructionrig"`, not `"constructor"`.
- Steam still needs explicit runtime validation. Current `bzr_hooks.cpp` stops
  producer-menu config loading on Steam even though `patcher.cpp` has
  Steam-aware rel32 target resolution for the hook.
- Do not promote the feature until normal mission exit and producer switching
  have both been exercised.

## Current OpenShim Implementation

The first bridge is still present in current `main` and is more advanced than
the original March note described.

### Runtime hook

- patch name: `Producer Build Menu Root Hook`
- opt-in environment variables accepted by `patcher.cpp`:
  - `OPENSHIM_ENABLE_PRODUCER_BUILD_MENU=1`
  - `OPENSHIM_ENABLE_PRODUCER_BUILD_MENU_EXPERIMENT=1`
  - `BZR_ENABLE_PRODUCER_BUILD_MENU=1`
- the rel32 hook calls `MaybeApplyProducerBuildMenu(producerPtr)` before calling
  the original producer helper
- common producer types are classified as Recycler, Factory, Armory, and
  ConstructionRig

### Root selection precedence

For a selected producer, current code chooses the root in this order:

1. ODF-local `[ProducerClass] buildMenuRoot = <root>` or `buildMenu = <root>`
2. per-ODF override from `openshim_producer_build_menus.ini`
3. producer-type mapping (`Recycler`, `Factory`, `Armory`, `ConstructionRig`)
4. fallback root

The ODF-local path resolves the producer's real ODF token, looks for
`<token>_mp.odf` before `<token>.odf`, then reads the producer section. The
filesystem candidate list includes campaign/mod ODF roots and `Edit\stock`.

This means the intended mod-facing syntax now exists. A test Factory can use:

```ini
[ProducerClass]
buildMenuRoot = b_amcmbt
```

The root is a native eight-character `[Builder]` token, not an arbitrary file
path. Use an unquoted token for the first validation pass.

### Config requirement

`openshim_producer_build_menus.ini` must still exist and must contain at least
one configured mapping/override for the config loader to become enabled. The
recommended ODF-local smoke configuration is therefore:

```ini
[ProducerBuildMenus]
Enabled=1
Factory=build
```

Factories with no ODF-local field retain the stock `build` root; a test Factory
with `buildMenuRoot = b_amcmbt` overrides it.

This requirement is a convenience limitation of the current experiment, not a
fundamental requirement of the ODF-local design. Once runtime behavior is
proven, allowing `Enabled=1` with ODF-only roots would be a sensible cleanup.

### What still needs live proof

The hook and ODF parsing are implemented. The unanswered runtime questions are:

- Does the producer UI actually render and navigate the recursive children after
  the root is swapped?
- Does selecting a recursive leaf naturally reach the stock
  `Producer::SetActiveMode` / `Producer::StartBuild` path?
- Does the global `buildMenu` state remain correct while switching between
  producers and multiple producer instances?
- Does mission exit remain clean?

If nested entries render but leaf construction fails, the next implementation
should be a narrowly scoped leaf-handoff bridge around `SetActiveMode` and/or
`StartBuild`, not another submenu parser.

See `Docs/producer-build-menu-test.md` for the exact GOG live-test procedure and
failure interpretation.
