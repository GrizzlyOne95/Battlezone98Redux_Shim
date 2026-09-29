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

Slot 23 takes no arguments (plain `ret`) and is a no-op stub in GameObject. It
fills the mode list at `this+0x1A4` through the thiscall
`ModeList::SetMode` (`0x0046FA60(slot, value, enabled)`). Slot 11 is
`SetActiveMode` and slot 13 is `GetCommand(GameObject*)`. The next section has
the full map.

### Why the fix is not just a new address

- Every call in `0x005AE660` is a thiscall: `ecx = this+0x1A4` (mode-list set),
  `ecx = [this+0x17C]`, or `ecx = this`. The hook is
  `__cdecl ProducerBuildMenuCallHook(void* producer, int slot, int flags)`. That
  contract fits the `StopSound` call it was modelled on, not any producer call.
- Armory and ConstructionRig override `UpdateModeList`, so a site inside
  `0x005AE660` never runs for them.
- The `BuildItem` tree at `buildMenu` (`0x009174C4`) is the **arcade-mode** build
  panel, not the producer menu. `ControlPanel::Render` walks it only when
  `UserPref_arcadeMode()` (`0x00451DE0`) is true, and it spawns leaves directly
  at the reticle with no scrap charge. Swapping that root can never change what
  a Recycler or Factory offers.

## Where producer nested menus have to hook (2026-09-28 follow-up)

Sources:
- the BZ 1.5 symbol decompile
  (`Battlezone_Source\BZ1\1.5\all_decompiled.c`, with `bzint.pdb`);
- a capstone map of the GOG Redux executable;
- a Steam `.rdata` cross-check of every vtable slot below.

Every address and byte in this section was re-read with capstone.

### How the stock producer menu works

1. `this+0x228` is the Craft **deploy state**, not a menu level: 0 = mobile,
   1 = deploying, 2 = deployed, 3 = packing up.
   - `Producer::Simulate` steps it, and `Craft::IsDeployed` tests `== 2`.
   - Recycler, Factory and Producer have no menu pages. They have one flat
     9-entry build list.
2. `UpdateModeList` (vtable `+0x5C`, slot 23) is **not** called by the UI.
   - Craft's per-frame function calls it for every craft on the user team, at
     `0x004AC08C` (`8B 42 5C FF D0`).
   - `GameObject::SetTeam` also calls it, at `0x004DB761`.
3. `ModeList` sits at `obj+0x1A4`: 11 values, then `enabledMask` at `+0x2C`, then
   `activeSlot` at `+0x30`.
   - `ControlPanel::Render` (`0x004A08E0`, vtable slot 6 of the ControlPanel at
     `0x00978E20`) copies the first selected object's list every frame
     (`rep movsd`, 13 dwords at `0x004A2DC4`) and intersects the others
     (`0x004A2E33`).
   - Only slots 1..10 are shown. Slot 10 is the fixed Pack Up / Cancel /
     Recycle button, so a page holds 9 entries.
4. How a mode value is drawn:

   | Value | Treatment | Evidence |
   |---|---|---|
   | `<= 0x1A` | Built-in mode, labelled from the `names` table at `0x008E7B00`. 0x12..0x15 are Cannons/Rockets/Mortars/Specials, 0x16 Back, 0x17 Cancel, 0x18/0x19 Cloak/Decloak. Never emit 0x1A: its table entry is garbage. | `83 BD 74 FD FF FF 1A 0F 86` at `0x004A51A9` |
   | `> 0x1A` | A `GameObjectClass*`. The label is `class+0x64` passed through the `names` lookup `0x0081CB40`, which appears to return the key itself when no entry exists. The scrap cost comes from `class+0x48` and the pilot cost from `class+0x50`. | label read at `0x004A51C8` |

   Both value tests are unsigned (`jbe`), so the large-address-aware image can
   hold stub classes above 2 GB.
5. A button press goes through `ControlPanel::BroadcastMode` (`0x004A7140`),
   which calls `SetActiveMode` through vtable `+0x2C` at `0x004A71A3`
   (`8B 42 2C FF D0`).
   - If every commandable selected object returns true, the panel closes with
     SelectNone.
   - Returning **false** keeps the panel open. The Armory uses this for its
     category pages.
6. `Producer::SetActiveMode` (`0x005AEAB0`) handles the special values first:
   0xB is geyser, 3 is pack up, 0x17 is stop. A value `> 0x1A` gives
   `SetCommand(CMD_BUILD=0x15, value, 0)` at `0x005AEB0B`. The process then
   calls `Producer::StartBuild` (`0x005AECB0`), which charges scrap and pilots.
   Nothing checks that the class is in the producer's list.
7. **The Armory already has nested pages.**
   - `Armory::SetActiveMode` (`0x00472C10`) keeps the page in `this+0x378`. Modes
     0x12..0x15 choose a page, 0x16 goes back, and all return false.
   - `Armory::UpdateModeList` (`0x00472780`) reads page arrays at
     `class+0x608/0x660/0x684/0x6A8/0x6CC`.
   - This is the stock template for producer submenus.

### Hook sites

| Target | Site | Original | Role |
|---|---|---|---|
| Producer/Recycler/Factory `UpdateModeList` | vtable slot 23 at `0x00886120`, `0x008864B0`, `0x008793E4` | `60 E6 5A 00` (→ `0x005AE660`) | Call the original, then, when `[this+0x228]==2` and a tree node is active, rewrite slots 1..9 with `SetMode`. Put Back (`0x16`) in a fixed slot below the root. |
| Producer/Recycler/Factory `SetActiveMode` | vtable slot 11 at `0x008860F0`, `0x00886480`, `0x008793B4` | `B0 EA 5A 00` (→ `0x005AEAB0`) | A submenu stub or `0x16` updates the node, re-runs `UpdateModeList` and returns false. Anything else chains to the original, so a leaf goes through the stock `CMD_BUILD` path. |
| Armory | slot 23 `0x00875D0C` / slot 11 `0x00875CDC` | `80 27 47 00` / `10 2C 47 00` | Same pair. Page state already lives at `this+0x378`. |
| ConstructionRig | slot 23 `0x008779F0` / slot 11 `0x008779C0` | `50 D5 49 00` / `E0 D0 49 00` | Same pair. The rig builds while mobile (state 0), in slots 3..9 (7 entries). A leaf means "select, then place" (`this+0x370` = class). |
| Optional: reuse the stock enable/cost logic | state-2 array load at `0x005AE893` | `8B 88 F8 00 00 00 81 C1 08 06 00 00` | Substitute the node's 9 class pointers for `class+0x608`. Entries must be real classes, because they are dereferenced at `0x005AE915` and by the cost functions. |

Slot swaps are the best fit:
- they cover each class separately;
- they need no code bytes, only a guarded 4-byte `.rdata` write (with
  `VirtualProtect`) whose guard is the stock target;
- the slot contents are identical on Steam.

The old `__cdecl` hook, the PDB vtable constants and the `buildMenu` root swap do
not carry over. The INI/ODF root selection code does carry over.

### Rules a producer submenu implementation must keep

- **Submenu entries.** A submenu entry must be a `GameObjectClass`-shaped stub,
  allocated once and never freed:
  - at least `0x150` bytes, zeroed;
  - label at `+0x64`;
  - costs `+0x48` and `+0x50` = 0;
  - the two category fields read at `0x005AE915`/`0x005AE927` = -1.

  It must never reach `SetCommand`: the Armory's and ConstructionRig's
  `GetCommand` and the save code dereference the active value as a real class.
  The renderer will print a "00" cost for a stub unless the cost block is
  detoured.
- **State.** Keep the per-object node in a side table. Reset it on deselect and
  on `SetTeam`. No page state is saved, just as the Armory's is not.
- **Multi-select and multiplayer.** Share one stub per node so `Intersect` keeps
  a matching entry when several producers are selected. Only `CMD_BUILD` with a
  real class crosses the network.
- **Leaf filtering.** Leaves loaded from a `[Builder]` tree must pass the same
  net-game filters that `ProducerClass`/`ArmoryClass` apply to `buildItemN`.
  The Armory caches its reload and repair items from its flat list.
- **Live validation.** Everything here is static. The label fallback in the
  `names` lookup and the one-frame refresh after a page change still need a
  live check.

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
