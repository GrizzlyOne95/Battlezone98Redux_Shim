## Producer Build Menu RE Notes

Date: 2026-03-15

Goal: find a viable native path for submenu-capable producer build menus so
`Producer` descendants like Recycler, Factory, Armory, and Constructor can use
`Builder`-style nested menus instead of ODF hot-swapping tricks.

### Summary

- The shipped `build.odf` / `build_a.odf` / `b_amcmbt.odf` submenu system is
  real, native, and recursive.
- That submenu system appears to be the editor / placement build tree, not the
  stock in-mission producer build menu path.
- Stock producer units still use flat `[ProducerClass] buildItem1..10` lists.
- The best path forward is to graft the existing native `BuildItem` recursion
  onto the producer menu flow, gated by a new producer-side menu-root override.

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
`C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\Edit\stock`
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

1. Add a new producer-facing ODF field such as:
   - `buildMenuRoot = "..."`, or
   - `buildMenuRootPacked = "..."` and `buildMenuRootDeployed = "..."` if
     deployed vs packed producers need separate trees later.
2. Hook the producer menu setup path for `Producer` descendants.
3. If the selected unit is an eligible producer class and the new field exists,
   build a `BuildItem` tree from that root using the existing native recursive
   loader behavior instead of the stock flat `buildItem1..10` path.
4. Keep the stock behavior as fallback when the override field is absent.
5. Return leaf selections back into the normal `Producer::StartBuild` flow so
   actual construction remains native.

### Best Targets To Investigate Next

The likely producer-side hook area is the cluster around:

- `Producer::UpdateModeList`
- `Producer::SetActiveMode`
- `Producer::StartBuild`

The exact byte-perfect symbol alignment from the PDB should be rechecked before
patching, but these are the right semantic targets.

The builder-tree side to reuse is the cluster around:

- `0x0049F5C0` recursive `BuildItem` loader behavior
- `0x0049F880` recursive cleanup behavior
- `0x004A0185` `build.odf` root initialization behavior

### Why This Looks Safer Than ODF Hot-Swapping

- It preserves the game's existing native submenu semantics.
- It keeps leaf builds in the normal producer construction path.
- It can be opt-in per producer ODF.
- It avoids mutating global stock build ODFs at runtime.
- It should support class-specific menus for Recycler / Factory / Armory /
  Constructor without having to fake unit identities.

### Cautions

- The stock builder-tree path appears to use globals, which is fine for editor
  usage but may be unsafe to share directly across multiple live producer units.
- A producer implementation should probably create or cache a per-instance or
  per-class `BuildItem` tree instead of directly reusing the global editor menu
  state.
- Constructor uses `classLabel = "constructionrig"`, not `"constructor"`.
- The PDB is directionally useful, but byte-level patch points should always be
  revalidated against the Steam target EXE before shipping a hook.

### Current Best Guess

The most realistic forward path is an OpenShim native hook that:

- reads a custom producer menu root from ODF
- converts that root into a recursive `BuildItem` tree using the already-shipped
  Builder loader behavior
- exposes submenu navigation through the producer menu path
- hands final leaf selections back to the stock producer build code

That would give Recycler / Factory / Armory / Constructor nested menus without
the current ODF hot-swap hacks.
