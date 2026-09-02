# DistributedObject reconstruction — macOS x86_64 2.2.301, correlated to Windows x86 2.2.301

Date: 2026-08-31
Branch: `agent/macos-x64-recon`
Continues: `BZR_MACOS_X64_RECON_20260831.md` (all prior findings preserved; §16 of that
report named this pass as the next experiment)

## Fixtures

| Role | Identity |
|---|---|
| Mac reference | depot `301651` / manifest `730966170255625169`, `Contents/MacOS/Battlezone 98 Redux (Steam)`, SHA-256 `DAE80722CE6B253F1C7F1FD4807BDB379822EFC3735E7DB799D40E2470BA2C00`, thin Mach-O x86_64 PIE, `__TEXT` @ `0x100000000` (all Mac VAs below are unslid) |
| Windows reference | GOG `Battlezone98Redux.exe`, 5,425,152 bytes, SHA-256 `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413`, PE32 i386, image base `0x00400000` |

Tooling added this pass: `BZR64_RESEARCH/tools/macho_probe.py` (read-only Mach-O
section/VA/vtable/RTTI probe). No binary was modified. No runtime patching was done.

Confidence vocabulary: **Proven** / **High** / **Probable** / **Speculative**.

---

## 1. Executive summary

`DistributedObject` is fully identified as a **root base class with no bases of its
own**, from which `GameObject` derives as the *second* base of a multiple-inheritance
pair. Its 21-slot virtual interface, its ctor/dtor, its identity and authority
fields, its three static registries, its ID composition rule and its perm-state
packet layout are all recovered from named code.

The single most consequential result is in §8: **the perm-state wire format is
byte-for-byte identical between the 32-bit Windows build and the 64-bit macOS
build.** That was established by disassembling the Mac *writer* and the Windows
*reader* independently and observing that they agree on every field offset and
width. It is direct evidence that Big Boat's replication protocol is
pointer-size-independent by construction.

The main thing this pass did **not** close is `sizeof(DistributedObject)`. A proven
lower bound of `0x180` exists; the upper bound is blocked for a specific, documented
reason (§3.4).

---

## 2. Inheritance

```
        Attachable                     DistributedObject
      (no base classes)               (no base classes)
      __class_type_info               __class_type_info
      typeinfo 0x100452E18            typeinfo 0x100451AB0
      size 0x28  [PROVEN]             size >= 0x180  [PROVEN lower bound]
              \                          /
               \  offset 0x00           /  offset 0x28
                \                      /
                 +------ GameObject --+
                    __vmi_class_type_info
                    typeinfo 0x10044FB00, base_count = 2
                    sizeof >= 0x1E4  [PROVEN]
```

`class GameObject : public Attachable, public DistributedObject` — **Proven**, from
the Itanium `__vmi_class_type_info` record. Decoded `base_info`:

| base | typeinfo | `offset_flags` | offset | access |
|---|---|---:|---:|---|
| 0 | `0x100452E18` `10Attachable` | `0x0002` | `0x00` | public, non-virtual |
| 1 | `0x100451AB0` `17DistributedObject` | `0x2802` | `0x28` | public, non-virtual |

The `0x28` offset is corroborated three further independent ways, any one of which
would be sufficient:

1. **`__ZThn40_` thunks.** The secondary vtable is populated with this-adjusting
   thunks named for a 40-byte (`0x28`) adjustment — e.g.
   `__ZThn40_N10GameObject7GetTeamEv` at `0x1000202D4`.
2. **Constructor.** `GameObject::GameObject(_OBJ76*, GameObjectClass*)` at
   `0x10001BC80` does `lea rdi,[rbx+0x28]; call __ZN17DistributedObjectC2Ev`
   at `0x10001BCC0`, then stores `_ZTV10GameObject+0x148` into `[rbx+0x28]`.
3. **Runtime upcast.** `UpdatePermState` at `0x10009FD59` performs a null-checked
   `lea rcx,[rax+0x28]` on `GameObject::userObject` in order to compare it against
   a `DistributedObject*`.

Point 2 also closes `Attachable`'s size at `0x28`: the ctor writes `+0x08/+0x10/+0x18`
as Attachable's own fields and then constructs the next base at `+0x28`.

### 2.1 Independent cross-check against prior Windows RE

Earlier Windows x86 Redux work — derived separately, from live disassembly rather
than from RTTI — placed the `DistributedObject` subobject at `GameObject+0x18`.
`Attachable` is a vptr plus three pointer-width fields plus an 8-byte tail:

| ABI | Computation | Predicted | Independently observed |
|---|---|---:|---|
| ILP32 (Windows x86) | `4 × 4 + 8` | `0x18` | `0x18` (prior RE) |
| LP64 (macOS x86_64) | `4 × 8 + 8` | `0x28` | `0x28` (this pass) |

Delta `0x10` = four pointer slots × 4 bytes of growth. Two independently derived
results agree exactly under pointer-width expansion. This corroborates the `0x28`
base offset from a direction that shares no evidence with §2's four arguments, and
it is why the 8-byte tail at `+0x20` is rated **High** rather than left unrecovered
— without it, neither figure works.

It is also a small, concrete demonstration of the report's central claim: the
layout differences between the 32-bit and 64-bit builds are exactly and only
pointer-width expansion.

> **Implication for reconstruction.** This is not a detail. Any Win64 rebuild that
> models `GameObject` as single-inheritance from a networking base will produce
> wrong `this` values on every call through a `DistributedObject*`, and the bug will
> present as plausible-but-wrong field reads rather than as a crash. This is the same
> class of failure already recorded in the repository's own notes about vtable
> subobject re-basing.

---

## 3. Class layout

Full annotated layout: `BZR64_RESEARCH/layouts/DistributedObject.hpp`.

### 3.1 Proven fields

Every row below is a direct load or store at that offset inside a named function.

| Offset | Width | Proposed name | Evidence | Confidence |
|---:|---:|---|---|---|
| `+0x000` | 8 | `__vptr` | ctor stores `_ZTV17DistributedObject+0x10` | Proven |
| `+0x008` | 1 | *(unnamed flag)* | ctor `mov byte [rdi+8], 0` | Proven (offset), Speculative (meaning) |
| `+0x05C` | 4 | *(unnamed)* | ctor zeroes dword | Proven (offset) |
| `+0x060` | 1 | *(unnamed)* | ctor zeroes byte | Proven (offset) |
| `+0x061` | 1 | `recycle` | ctor zeroes; `SetRecycle` `0x1000A15F0` | High |
| `+0x062` | 2 | `playerID` | `SetPlayerID` `0x10009FBA6` word store; `GetPlayerID` `0x1000A0538` `movzx` word | Proven |
| `+0x064` | 4 | `id` | `GetID` `0x1000A0786` dword load; map key | Proven |
| `+0x068` | 1 | `locality` | `IsLocal` `==1` `0x1000A0616`; `IsRemote` `==2` `0x1000A0606` | Proven |
| `+0x06C` | 4 | *(change accounting)* | ctor zeroes; read by `PermStateChanged`, `Destroy`, `GetRank` | Proven (offset), Probable (meaning) |
| `+0x070` | 1 | `dirty` | `SetDirty` `0x1000A04E4` stores literal `1` | Proven |
| `+0x074` | 4 | `permStateInterval` (f32) | ctor stores `0x3F800000` = `1.0f` | Proven (offset+value), Probable (name) |
| `+0x078` | 4 | *(expiry state)* | ctor zeroes; read by `ExpireRemoteObject` `0x1000A051E` | Proven (offset) |
| `+0x094` | 4 | *(send accounting)* | read by `TempStateSendAll` | Proven (offset) |
| `+0x0F0` | 4 | *(unnamed)* | read by `Explode` `0x1000A0626` | Proven (offset) |
| `+0x17C` | 4 | *(spawn/slot index)* | read by `SetLocal`, `Destroy`, `UpdatePermState`; used as `0x1200 + value` | Proven (offset), Speculative (meaning) |

### 3.2 Constructor — `0x10009F47A`

Sets the vptr, zeroes `+0x08`, `+0x5C`, `+0x60`, `+0x61`, `+0x62`, `+0x68`, `+0x6C`,
`+0x70`, `+0x78`, stores `1.0f` to `+0x74`, then **push_backs `this` onto
`allDistributedObjectList`**. Note it does **not** initialise `+0x64` — the object ID
is assigned later, by `SetLocal` or `Create`.

### 3.3 Destructor — `0x10009F4E8` (`D2`), `0x10009F5DC` (`D1`)

Restores the vptr, performs a linear scan + erase of `this` from
`allDistributedObjectList`, then branches on `locality` (`+0x68`) to erase the
`id` key from the local or remote map. Unregistration is complete and symmetric
with construction. **Proven.**

`DistributedObject` has **no virtual destructor** — slot 0 of its vtable is
`GetClass`, not a destructor pair. **Proven.** Destruction is therefore always
driven from the derived (`GameObject`) side.

### 3.4 Size — the one unresolved structural question

- **Lower bound `0x180`: Proven.** `SetLocal` reads `dword [rbx+0x17C]` where `rbx`
  is loaded from `rdi` at function entry and is never reassigned.
- **Upper bound: not established.** The natural probe — "where does the derived
  constructor start writing its own fields" — is unusable here, because
  `GameObject`'s constructor writes `+0xD0` and `+0xF8` of the *complete object*,
  both of which land inside the `DistributedObject` subobject (`DO+0xA8`, `DO+0xD0`).
  A derived constructor initialising protected base members is ordinary C++, so those
  stores carry no boundary information.

Recorded as open work rather than guessed. §11 lists what would settle it.

---

## 4. Vtable map

21 slots, recovered from the standalone vtable at `0x1004519F8` and cross-checked
against the secondary block of `_ZTV10GameObject` (which begins at `+0x148`, exactly
the value `GameObject`'s ctor stores into `this+0x28`). **Proven.**

| Slot | Signature | `GameObject` override |
|---:|---|---|
| 0 | `GetClass()` | `__ZThn40_` thunk → `0x10017F5E0` |
| 1 | `GetTeam()` | `__ZThn40_` thunk → `0x1000202D4` |
| 2 | `SetTeam(int)` | `__ZThn40_` thunk → `0x10001CC48` |
| 3 | `GetPosition()` | `__ZThn40_` thunk → `0x1000202E0` |
| 4 | `Remove()` | `__ZThn40_` thunk → `0x10001CC08` |
| 5 | `Explode()` | inherited |
| 6 | `GetRank(float,float)` | inherited |
| 7 | `GetHealth()` | `__ZThn40_` thunk → `0x10017F5F8` |
| 8 | `GetRecycle()` | inherited |
| 9 | `SetRecycle()` | inherited |
| 10 | `AddHealth(float)` | `__ZThn40_` thunk → `0x10001D5F6` |
| 11 | `GetEntity()` | `__ZThn40_` thunk → `0x100020310` |
| 12 | `GetOBJ76()` | `__ZThn40_` thunk → `0x10017F608` |
| 13 | `Getroot()` | inherited |
| 14 | `DamageAlloc(DAMAGE*, VECTOR_3D*)` | `__ZThn40_` thunk → `0x100020324` |
| 15 | `PackTempState(void*, size_t*)` | inherited |
| 16 | `UnPackTempState(void*, size_t*)` | inherited |
| 17 | `PackPermState(void*, size_t*)` | `__ZThn40_` thunk → `0x100020182` |
| 18 | `UnPackPermState(void*, size_t)` | `__ZThn40_` thunk → `0x10002026A` |
| 19 | `PermStateChanged(float)` | inherited |
| 20 | `ExpireRemoteObject(float)` | inherited |

Slots 0, 1 and 3 read as `0` on disk in the standalone vtable, consistent with pure
virtuals bound to `__cxa_pure_virtual` at load. **High** — the class is abstract.

**Architectural observation.** This interface is *not* a thin networking mixin. It
carries `GetTeam`/`SetTeam`/`GetHealth`/`AddHealth`/`GetRank`/`GetRecycle`/`Explode`/
`DamageAlloc`. `DistributedObject` in this engine is the **replicated game entity
base**, and the pack/unpack pairs at slots 15–18 are the per-class replication hooks.

---

## 5. Identity, authority and IDs

### 5.1 Network ID composition — Proven

`SetLocal` `0x1000A007A`, fresh-local path at `0x1000A0110`:

```
movzx eax, word [Net::myPlayerIDInt]     ; u16 @ 0x102ED0290
shl   eax, 0x10
add   eax, [DistributedObject::dwLocalIDCounter]
mov   [rbx+0x64], eax                    ; this->id
inc   [DistributedObject::dwLocalIDCounter]
```

```
id = (playerID << 16) | perPlayerCounter
```

The remote→local takeover path tests `id < 0x10000` — i.e. "was this authored by
player 0 / pre-placed in the map" — and only rewrites `playerID` and the
`keyLocalIDMap` entry for ids at or above `0x10000`.

This is an **intentional fixed-width distributed identifier**, not a truncated
pointer. It stays 32 bits wide in the 64-bit build, it is composed arithmetically
from a 16-bit player id, and it is the key type of both registries.

### 5.2 Authority state — Proven

`locality` at `+0x68` is a one-byte enum: `0` unowned, `1` Local, `2` Remote.
`SetLocal`/`SetRemote` are the only transitions and each one moves the object
between the two registries.

`playerID` at `+0x62` is `uint16_t`. The process-wide local identity is
`DistributedObject::local_user_id` (`0x102DF3AD8`), also `uint16_t`, written by
`SetGlobalPlayerID`.

### 5.3 Registries — Proven

| Symbol | Mac VA | Type |
|---|---|---|
| `localDistributedObjectMap` | `0x102E67F58` | `std::map<uint32_t, DistributedObject*>` |
| `remoteDistributedObjectMap` | `0x102E67F40` | `std::map<uint32_t, DistributedObject*>` |
| `allDistributedObjectList` | `0x102E67F70` | `std::vector<DistributedObject*>` |
| `keyLocalIDMap` (file-scope) | `0x100A95E80` | `std::map<std::pair<uint16_t,uint32_t>, uint32_t>` |
| `dwLocalIDCounter` | `0x100477AC8` | `uint32_t`, initialised `1` |
| `dwGlobalIDCounter` | `0x100477ACC` | `uint32_t`, initialised `1` |

Both maps are keyed **by the object's own `id` field** — the code passes `rbx+0x64`
directly as the key pointer. The map key type is `unsigned int`, confirmed from the
mangled `std::map<unsigned int, DistributedObject*>` instantiations.

`keyLocalIDMap`'s key is `{ playerID, 0x1200 + field_0x17C }` — **Proven** as a
construction, **Speculative** as to what `field_0x17C` means.

---

## 6. Lifecycle

```
  ctor 0x10009F47A
      vptr, zero flag block, permStateInterval = 1.0f
      allDistributedObjectList.push_back(this)
      (id is NOT assigned here)
            |
            v
  SetLocal 0x1000A007A                    SetRemote 0x10009FBB0
      locality 0 -> 1                         locality -> 2
      id = (myPlayerIDInt<<16) + counter++    erase from localMap
      localMap[id] = this                     remoteMap[id] = this
      -> UpdatePermState (tail call)
            |
            +--- takeover: TakeOwnershipFromPlayer 0x1000A1296
            |       remote -> local, rewrites playerID, fixes keyLocalIDMap
            |
            v
  steady state
      SetDirty 0x1000A04E4        -> dirty = 1
      PermStateChanged 0x1000A04EE
      UpdatePermState 0x10009FCF0 -> build + send perm-state packet
      TempStateSendAll 0x1000A08CA-> batched temp-state broadcast
      ReceiveTempState 0x10009EAA8/ ReadPermState 0x10009F122 (inbound)
            |
            v
  teardown
      Remove 0x10009F5E6 / Destroy 0x10009F60C / RemoteDelete 0x1000A06A2
      Cleanup 0x1000A0388 / RemoveOldObjects 0x1000A0382
            |
            v
  dtor 0x10009F4E8
      restore vptr
      linear erase from allDistributedObjectList
      erase id from localMap or remoteMap per locality
```

---

## 7. Replication and serialization entry points

| Direction | Function | Mac VA | Notes |
|---|---|---:|---|
| create/spawn | `Create(uint16, void*, size_t)` | `0x1000A0174` | decodes an inbound spawn packet; "Reviving id %08x" is the re-use path |
| update out | `UpdatePermState()` | `0x10009FCF0` | builds the perm-state packet into `packet_buffer` |
| update out | `TempStateSendAll(_ToBeSent const*, int)` | `0x1000A08CA` | batched, bandwidth-governed |
| update in | `ReceiveTempState(uint16, char*, size_t, float)` | `0x10009EAA8` | first arg is the u16 sender player id |
| update in | `ReadPermState(uint16, size_t, uint16, void*)` | `0x10009F122` | |
| per-class hooks | vtable slots 15–18 | | `Pack/UnPack` `Temp`/`Perm` state |
| damage | `ReceiveDamage(uint16, void*, size_t)` | `0x10009F05A` | |
| commands | `SendCommand(AiCommand, VECTOR_3D const&)` | `0x10009F7AA` | |
| raw send | `SendBuf(char*, int)` | `0x1000A1224` | |
| destroy | `RemoteDelete()` | `0x1000A06A2` | |

Network-manager boundary: `Net::OnP2PReceivedMapped(CGameNetP2P&, unsigned short,
unsigned char const*, unsigned long)` at `0x1002AA734` — a `(senderPlayerId, bytes,
length)` shape. Typed packet structs exist as named parameters:
`SNIPE_PACKET`, `BANDWIDTH_PACKET`, `PINGREPLY_PACKET`, `SPAWNPOINT_PACKET`.

---

## 8. Wire format — proven identical across 32-bit and 64-bit

Derived from the Mac **writer** (`UpdatePermState`, staging into
`DistributedObject::packet_buffer` @ `0x102DF3650`) and independently confirmed
against the Windows **reader** (`Create` @ `0x004B9350`).

| Offset | Width | Field | Mac writer evidence | Windows reader evidence |
|---:|---:|---|---|---|
| `+0x00` | 1 | packet length | length checks | `cmp edx,0x15` / `cmp edx,0x1C` |
| `+0x01` | 1 | flags: bit7 = is-local-user, bits 2–5 = class<<2 | `mov [pb+1],al` after `shl eax,2; and eax,0x3C; or eax,r12d` | `mov al,[edx+1]` @ `0x4B9403` |
| `+0x02` | 4 | **object network ID** | `mov [pb+2],eax` from `[r15+0x64]` | `mov ecx,[eax+2]` @ `0x4B93F4` |
| `+0x06` | 14 | reduced transform matrix | `NetUtil_ReduceMatrix` result stored as qword+dword+word | dwords at `+0`,`+4`,`+8` and word at `+0xC` from `eax=pkt+6` @ `0x4B93C6` |
| `+0x14` | 1 | compact class code \| `0x80` | `mov [pb+0x14],bl`, `bl = codes[] index + 0x80` | `movzx eax,[edx+0x14]; and eax,0x80` @ `0x4B9395` |

Compact form is `0x15` (21) bytes. The non-compact form substitutes the 8-byte ODF
class name for the 1-byte code, which is exactly the `0x1C` (28) minimum the Windows
reader enforces on the other branch: `0x15 − 1 + 8 = 0x1C`. Self-consistent.

**No field is pointer-width. No field offset or width differs between the builds.**

The class identity is transmitted as a **1-byte index** into `codes[]`, a 102-entry
(`0x66`) table of 8-byte ODF names masked with `0x7F7F7F7F7F7F7F7F`. That table lives
in `__bss` (`0x100A95EC0`) and is populated at runtime — so it is *not* usable as a
static byte anchor, which is why the correlation in §9 used strings instead.
Recorded as a negative finding.

---

## 9. Windows correlations

Full detail and method: `BZR64_RESEARCH/reports/evidence/macos_windows_correlations.txt`.

Method: string literals referenced from the Mac `DistributedObject.cpp` code range
were located in the Windows image; absolute-dword xrefs were collected from `.text`;
each xref was walked back to the nearest prologue preceded by `int3` padding. A
correlation is recorded only where **more than one independent string** converges on
one function start, or where the Windows function's **field-offset behaviour**
independently reproduces the Mac layout.

**Translation-unit anchor — Proven.** All 11 recovered literals resolve into one
contiguous Windows region, `0x004B76FA .. 0x004BA9AA`. That bounds the Windows
`DistributedObject` translation unit.

| Mac | Mac VA | Windows | Evidence | Confidence |
|---|---:|---:|---|---|
| `DistributedObject::Create` | `0x1000A0174` | `0x004B9350` | 3 strings converge **and** the reader reproduces all five packet field offsets (§8) | **Proven** |
| `DistributedObject::ReceiveTempState` | `0x10009EAA8` | `0x004B8460` | 4 strings converge | High |
| `DistributedObject::TempStateSendAll` | `0x1000A08CA` | `0x004B9C80` | 3 strings converge | High |
| *(unresolved)* | — | `0x004B76C0` | 1 string only (`"Invalid compact object id %d"`); sits ~`0x1D00` below the Windows `Create`, so it is a distinct function | Probable it is in the TU; Speculative as to which Mac function |

### Negative findings, recorded deliberately

- The Mac flag-byte build `C1 E0 02 83 E0 3C` does **not** occur in the Windows
  image — MSVC allocated different registers. Instruction-byte matching across the
  two toolchains is not a usable technique here.
- The Mac ID-composition idiom `shl reg,0x10` + `add reg,[abs]` + `inc [abs]` does
  **not** occur. The whole Windows `.text` contains only 17 distinct
  `inc dword ptr [abs32]` sites; MSVC emitted load/increment/store.
- `codes[]` is runtime-populated `__bss` on both sides — no static array anchor.
- **No Windows correlation was attempted for `SetLocal`/`SetRemote`/
  `UpdatePermState`.** They reference no string literals and no other evidence class
  was strong enough. This is left open rather than guessed.

---

## 10. What this says about the shared architecture

Collected here; the ratings live in `BZR64_FEASIBILITY_20260831.md`.

**Favourable, with evidence:**

- 32-bit object IDs and 16-bit player IDs are **intentional stable identifiers**,
  not artefacts of a 32-bit build — proven by their arithmetic composition and by
  their survival unchanged into the LP64 build.
- The replication protocol is byte-packed with explicit widths and **contains no
  pointers** (§8).
- Registries are keyed by ID, not by address.
- The Lua handle boundary is a 32-bit opaque ID in the 64-bit build (preserved from
  the prior pass).
- Save/load uses typed writes with explicit byte counts, not native struct dumps
  (preserved from the prior pass).
- `Net::OnP2PReceivedMapped` takes `(u16 sender, const unsigned char*, size_t)` — a
  transport-agnostic byte-buffer boundary.

**Risk, with evidence:**

- `GameObject`'s multiple inheritance means every `DistributedObject*` is an interior
  pointer at `+0x28`. Getting this wrong yields silent, plausible-looking corruption.
- `size_t`/`unsigned long` appears in the pack/unpack signatures
  (`PackTempState(void*, size_t*)`). These are **length** parameters, so they are
  pointer-width by nature; they are 8 bytes on Mac and 4 on Win32. They are not
  serialized — but a naive port that widens a serialized length field would break
  the wire format.
- `DistributedObject` has no virtual destructor.
- `packet_buffer` is a single process-wide static staging buffer, not per-connection.
- The class carries far more gameplay surface than its name suggests (§4), so it
  cannot be reimplemented as a networking shim independent of game logic.

---

## 11. Unresolved questions, ranked

1. **`sizeof(DistributedObject)`.** Blocked as described in §3.4. Would be settled by
   locating a class deriving from `DistributedObject` but *not* through `GameObject`,
   or by finding an `operator new` size at a direct allocation site.
2. **Ownership of `illumination` (`+0x110`) and `perceivedTeam` (`+0x1C8`).** Both
   fall inside the `DistributedObject` subobject under the size evidence in §3.4.
   The prior pass proved the offsets; this pass raises the question of which class
   declares them. Nothing previously proven is invalidated either way.
3. **Meaning of `field_0x17C`**, the `keyLocalIDMap` high-half input.
4. **Windows addresses for `SetLocal`/`SetRemote`/`UpdatePermState`.**
5. **Whether `packet_buffer`'s `0x480` size is real** — currently inferred from the
   gap to the next symbol (**High**, not Proven).
6. **`_ToBeSent` struct layout**, the input to `TempStateSendAll`.
7. **An actual cross-platform interop test** — a Mac-produced save or packet capture
   read by the Windows build. Not possible on this host.

---

## 12. Artifacts produced

| Path | Contents |
|---|---|
| `BZR64_RESEARCH/reports/DISTRIBUTEDOBJECT_RECON_20260831.md` | this document |
| `BZR64_RESEARCH/reports/BZR64_FEASIBILITY_20260831.md` | subsystem feasibility ratings and verdict |
| `BZR64_RESEARCH/layouts/DistributedObject.hpp` | annotated layout, confidence-tagged |
| `BZR64_RESEARCH/layouts/GameObject.hpp` | extended layout, prior findings preserved |
| `BZR64_RESEARCH/reports/evidence/macos_network_symbols.txt` | 86 `DistributedObject` + 88 `Net` symbols, demangled, with VAs |
| `BZR64_RESEARCH/reports/evidence/macos_windows_correlations.txt` | correlation table, method, negative findings, wire format |
| `BZR64_RESEARCH/tools/macho_probe.py` | read-only Mach-O section/VA/vtable/RTTI probe |
