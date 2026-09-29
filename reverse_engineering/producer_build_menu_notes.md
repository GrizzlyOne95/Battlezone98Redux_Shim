## Producer Build Menu RE Notes

Date: 2026-03-15  
Current implementation status updated: 2026-08-12  
Hook site audit: 2026-09-28. **The runtime hook is parked.** See "Hook site
audit" at the end; it supersedes the "Runtime hook" description below.

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
- the runtime patch is enabled through `openshim_producer_build_menus.ini`; no
  process environment variable is required
- `[ProducerBuildMenus] Enabled=1` is the test/default state and `Enabled=0`
  opts out before the producer hook is applied
- legacy producer-menu environment names remain accepted only as compatibility
  aliases through OpenShim's INI-aware environment shim
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

`openshim_producer_build_menus.ini` must still exist and contain at least one
configured mapping/override for the current producer config loader to become
active. The checked-in example is ready for testing as-is after it is copied
beside the executable:

```ini
[ProducerBuildMenus]
Enabled=1
Factory=build
```

Factories with no ODF-local field retain the stock `build` root; a test Factory
with `buildMenuRoot = b_amcmbt` overrides it. No launch environment setup is
needed.

The remaining file/mapping requirement is a convenience limitation of the
current experiment, not a fundamental requirement of the ODF-local design.

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

## Hook site audit (2026-09-28)

The `Producer Build Menu Root Hook` never hooked `Producer::UpdateModeList`. It
is now parked: the `globals` entry in `scripts/patches.json` carries a `parked`
reason and no address, and `include/patches.h` no longer lists it. The INI, ODF
and `BuildItem` code is kept but cannot run, because nothing calls
`ProducerBuildMenuCallHook`.

### What the old site was

The fallback `0x004FFA9F` (guard `B6 BF 32 00`) is the rel32 operand of the
first call in the Lua `StopSound` binding. GOG, capstone:

```text
004FFA90  55                 push ebp                ; StopSound(lua_State* L)
004FFA91  8B EC              mov ebp, esp
004FFA93  83 EC 14           sub esp, 0x14
004FFA96  6A 00              push 0
004FFA98  6A 01              push 1
004FFA9A  8B 45 08           mov eax, [ebp+8]        ; L
004FFA9D  50                 push eax
004FFA9E  E8 B6 BF 32 00     call 0x0082BA59         ; luaL_checklstring(L, 1, NULL)
```

The `luaL_Reg` table has `{"StopSound", 0x004FFA90}` at `0x00871BF8`, next to
`{"StartSound", 0x004FF960}`, which calls `0x0082BA59` the same way. The table
is identical in the Steam executable's `.rdata`. With the experiment enabled,
every Lua `StopSound` would have passed its `lua_State*` to
`MaybeApplyProducerBuildMenu` as if it were a producer. That function reads
`*L` as a vtable and `L` as a GameObject for the ODF token, and then runs
`CleanupBuildItem`/`InitBuildItem` on the global root. It was dormant only
because no shipped config enables the experiment. The checked-in `.ini.example`
has `Enabled=1`, so copying it beside the executable, as the live-test doc says,
would have armed it.

`0x004FFA90` is where the address came from. The leaked PDB lists
`?UpdateModeList@Producer@@MAEXXZ` at segment 1 offset `0xFFA90`, and `0xFFA90`
plus `0x400000` is `0x004FFA90`. That sum skips the `.text` section RVA and
assumes the PDB build matches the release, and neither holds. The classifier's
ten producer "vtables" (`kRecyclerDistributedVft` and the rest, in
`producer_build_menu.cpp`) have the same origin. Each is a PDB segment 2
(`.rdata`) offset plus `0x400000`. For example, `??_7Armory@@6BDistributedObject@@@`
is at offset `0x89C0`, and the constant is `0x004089C0`. On GOG these point
into `.text`, so no object could ever classify as a known producer.

### Where Producer::UpdateModeList actually is

The addresses below were found from RTTI (`.?AVProducer@@` → TypeDescriptor →
CompleteObjectLocator → vtable) in the GOG executable. The Steam `.rdata` gives
identical vtables and slot contents:

| Class | primary vtable (offset 0) | slot 23 (`UpdateModeList`) |
|---|---|---|
| Producer | `0x008860C4` | `0x005AE660` |
| Recycler | `0x00886454` | `0x005AE660` (inherited) |
| Factory | `0x00879388` | `0x005AE660` (inherited) |
| Armory | `0x00875CB0` | `0x00472780` (override) |
| ConstructionRig | `0x00877994` | `0x0049D550` (override) |
| GameObject | `0x00879ED4` | `0x00417C60` (base) |

Three slots (11, 13 and 23) hold a Producer function that Recycler and Factory
inherit and that Armory and ConstructionRig both override. That matches the
PDB, where those two, and not Recycler or Factory, define `UpdateModeList` and
`SetActiveMode`. Slots 11 and 13 take one argument (`ret 4`) and return a bool
in `al`, the `SetActiveMode(int)` shape. Slot 23 takes no arguments (plain
`ret`) and is a stub in GameObject. Its body settles the question: it switches
on `this+0x228` (menu level) and fills the
mode list at `this+0x1A4` through the thiscall `0x0046FA60(slot, a, b)`. At
levels 1 and 2 it loops over the producer class's flat build list at
`[this+0xF8]+0x608`.

### Why the fix is not just a new address

- Every call in `0x005AE660` is a thiscall: `ecx = this+0x1A4` (mode-list set),
  `ecx = [this+0x17C]`, or `ecx = this`. The hook is
  `__cdecl ProducerBuildMenuCallHook(void* producer, int slot, int flags)`. That
  contract fits the `StopSound` call it was modelled on, not any producer call.
- Armory and ConstructionRig override `UpdateModeList`, so a site inside
  `0x005AE660` never runs for them.
- The global root at `0x009174C4` is read only by `FUN_004a08e0` (at
  `0x004A1BE1`) and `FUN_00594950` (at `0x005949FD`), besides its own
  initialisation in `FUN_004a0160` and cleanup in `FUN_004a06c0`. `Producer::UpdateModeList` builds its menu
  from `ProducerClass+0x608`, so swapping that root is not shown to change a
  producer menu at all.

A future attempt needs a thiscall shim at a site proven to run for each
producer type, and the RTTI vtables above. It also needs proof that the
producer UI reads the `BuildItem` tree before any root swap is worth
installing.

### Re-verifying

This needs Python with `pefile` and `capstone`. On the unencrypted GOG
executable:

```python
import pefile, capstone, struct
pe = pefile.PE(r"C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\battlezone98redux.exe", fast_load=True)
img, base = pe.get_memory_mapped_image(), pe.OPTIONAL_HEADER.ImageBase
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
for va in (0x4FFA90, 0x5AE660):
    for i in list(md.disasm(img[va - base:va - base + 0x40], va))[:10]:
        print(f"{i.address:08X} {i.bytes.hex(' '):<22} {i.mnemonic} {i.op_str}")
u32 = lambda va: struct.unpack_from("<I", img, va - base)[0]
print(img[u32(0x871BF8) - base:][:9], hex(u32(0x871BFC)))  # b'StopSound' 0x4ffa90
print(hex(u32(0x8860C4 + 23 * 4)))                         # 0x5ae660
```

Steam's `.text` is SteamStub-encrypted on disk (entropy 8.0), so only its
`.rdata` checks, the `luaL_Reg` row and vtable slots, can be repeated offline.
Evidence executables: GOG SHA-256 `8d71f56c…3377413`, Steam SHA-256
`d298782f…b61cc90d`.
