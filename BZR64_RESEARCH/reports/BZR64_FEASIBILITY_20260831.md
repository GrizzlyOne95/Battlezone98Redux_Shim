# BZR64 feasibility assessment — evidence-based

Date: 2026-08-31
Branch: `agent/macos-x64-recon`
Companion: `DISTRIBUTEDOBJECT_RECON_20260831.md`
Builds on: `BZR_MACOS_X64_RECON_20260831.md` (all prior findings preserved)

---

## 0. The question, stated precisely

Two different questions get conflated, and they have different answers:

- **Q1. Is the Battlezone Redux game architecture 64-bit clean?**
  Answer: **Yes, and this is close to settled.** Not by inference — a shipping
  LP64 build of the same 2.2.301 game code exists, and the parts of it examined
  so far preserve fixed-width identifiers and wire formats exactly.

- **Q2. Is a native Windows x64 Battlezone Redux a realistic engineering target?**
  Answer: **Only as a large reconstruction project**, because the binding
  constraint is not architecture. It is that there is no source, and ~383
  translation units of game code would have to be rebuilt.

The macOS x86_64 executable answers Q1 strongly. It moves Q2 only insofar as it
removes ambiguity — it supplies names, hierarchy and 64-bit-correct layouts. It
does not supply code.

---

## 1. Evidence summary

### Favourable (all observed, not assumed)

| Finding | Evidence | Confidence |
|---|---|---|
| A full LP64 build of the same game code ships | thin Mach-O x86_64 PIE, `__PAGEZERO` 4 GiB, `__TEXT` @ `0x100000000`, bundle version 2.2.301 | Proven |
| Network object IDs are intentional fixed-width | `id` is `uint32` in the 64-bit build, composed as `(playerID<<16)+counter`; `playerID` is `uint16` | Proven |
| Replication wire format is pointer-independent and unchanged across 32/64 | Mac x86_64 writer and Windows x86 reader agree on all five perm-state field offsets and widths | Proven |
| Registries are keyed by ID, not address | `std::map<uint32_t, DistributedObject*>` keyed from `&this->id` | Proven |
| Lua handles are 32-bit opaque IDs, not pointers | prior pass: `PushHandle`, `GetObj` 12-bit slot / 20-bit generation | Proven |
| Save/load uses explicit widths, not struct dumps | prior pass: typed writes, 1/4/8/12-byte fields | High |
| Platform-specific code is a thin, named layer | **9 Objective-C `.mm` TUs out of 383 total (2.3%)**, each paired with a platform-neutral `.cpp` | Proven |
| Store/platform services already abstracted 3 ways | `Workshop.cpp` + `WorkshopGoG.cpp` + `WorkshopSteam.cpp`; `NetFriendsGog.cpp` + `NetFriendsSteam.cpp` | Proven |
| All middleware already ships x86_64 | Ogre 1.10.0, Plugin_ParticleFX, RenderSystem_GL are fat `x86_64+i386`; `libsteam_api`, `libGalaxy`, `libGalaxyPeer` fat | Proven |
| Transport boundary is a byte buffer | `Net::OnP2PReceivedMapped(CGameNetP2P&, uint16, const unsigned char*, size_t)` | Proven |

### Risk (all observed)

| Finding | Evidence | Confidence |
|---|---|---|
| `GameObject` uses multiple inheritance; `DistributedObject` is an interior subobject at `+0x28` | `__vmi_class_type_info` base_count 2; `__ZThn40_` thunks; ctor | Proven |
| No source exists; ~383 TUs, 979 RTTI classes must be reconstructed | symbol/TU census both builds | Proven |
| MSVC and Itanium ABIs differ — offsets are not transferable | libc++ `std::__1` vs MSVC 2013 STL, LP64 vs ILP32 | Proven |
| `DistributedObject` has no virtual destructor | vtable slot 0 is `GetClass` | Proven |
| `packet_buffer` is one process-wide static staging buffer | class static, 1152 bytes | Proven |
| `DistributedObject` carries heavy gameplay surface | 21-slot vtable includes health/team/rank/explode/damage | Proven |
| `size_t` appears in pack/unpack signatures | `PackTempState(void*, size_t*)` — 8 bytes Mac, 4 bytes Win32 | Proven |

### Notable absence of risk

Searching specifically for the classic 64-bit blockers, this pass found **none** in
the networking layer: no pointer-to-int truncation, no serialized pointers, no
native struct dumps on the wire, no pointer arithmetic embedded in packet
construction, and no `sizeof(void*)==4` assumption. The `size_t` parameters above
are *length* arguments, which are pointer-width by nature and are not serialized.
Recorded as a deliberate negative finding.

---

## 2. Subsystem ratings

Ratings answer: *how feasible is a native Win64 implementation of this subsystem,
given what the evidence shows?*

### Core simulation — **HIGH**
The whole simulation demonstrably compiles and runs as LP64 today. Task/AI classes
(`AttackTask`, `PatrolTask`, `HuntTask`, …) are platform-neutral `.cpp` TUs with no
platform dependency visible in their names or link imports. The work is
reconstruction volume, not architectural risk.

### GameObject / object system — **HIGH**
Handles are already a 32-bit slot+generation encoding deliberately decoupled from
pointers, and that survives unchanged into the 64-bit build. The one real trap is
the multiple-inheritance layout (§1 risk table): it is a correctness hazard for a
reconstruction, not a feasibility blocker, and it is now documented.

### DistributedObject / networking — **HIGH**
The strongest result in this pass. Fixed-width IDs, ID-keyed registries, a
byte-packed pointer-free wire format proven identical across the 32-bit and 64-bit
builds, and a byte-buffer transport boundary. A Win64 implementation could be
wire-compatible with existing 32-bit clients.

### Save / load — **MEDIUM**
Prior pass proved explicit-width typed serialization and matching ordered field
names across both builds — favourable. Not raised to HIGH because the
`out_ptr`/`in_ptr` eight-byte persistent-ID handling was flagged as unexamined in
the prior pass and remains unexamined, and no actual cross-platform save interop
test has been run.

### Resource management — **MEDIUM**
`Ogre76Archive`, `Zfsaux`, `FileUtil` are platform-neutral TUs, and the prior pass
proved the three `cWorkshop` rebuild functions map directly across architectures
with only offset expansion. Rated MEDIUM rather than HIGH because resource paths
and the ZFS layer were not examined for pointer-width assumptions in this pass.

### Renderer — **MEDIUM**
Favourable: rendering goes through Ogre 1.10, the shipped Ogre framework is already
fat `x86_64+i386`, and there is a clean seam (`Ogre3d_wrapper.cpp` shared, plus
`Ogre3d_wrapperOSX.mm` / `Ogre76HandlerOSX.mm` platform variants). A Win64 build
would keep Direct3D and only needs a 64-bit Ogre, which exists. Not HIGH because
the Windows renderer glue is the largest body of code the Mac binary gives the
least help with — Mac ships RenderSystem_GL, so there is no D3D reference on that
side at all.

### Audio — **MEDIUM**
The two platforms genuinely diverge: Mac calls OpenAL directly (`alGenSources`,
`alSourceQueueBuffers`, … as undefined imports) plus AudioToolbox; Windows links
`DSOUND.dll`. So the Mac binary provides no reusable reference here. The rating is
still MEDIUM rather than LOW for a concrete reason: **DirectSound, WINMM and the
whole Windows audio stack already exist as 64-bit**, so the existing Windows
approach needs recompiling for x64, not redesigning.

### Input — **MEDIUM**
Same shape as audio. Mac input is four `.mm` TUs (`inputmac`, `mousemac`,
`Keyboardmac`, `InputBridge`) over AppKit/IOKit — no reuse value for Windows. But
the Windows input path is Win32 message/raw-input based and has no 32-bit
dependency. Reconstruction effort, not architectural risk.

### Filesystem — **HIGH**
`FileUtil.cpp` and `Zfsaux.cpp` are platform-neutral, statically linked Boost
filesystem is present, and the Mac save code already uses `__sFILE*` stdio. Nothing
observed depends on pointer width.

### Threading — **HIGH**
A single `WorkerThread.cpp` TU, and the Mac build imports plain `pthread_*`. No
evidence of a thread-count or handle-width assumption. Windows already has a
64-bit-clean threading API.

### Lua / scripting — **HIGH**
Lua 5.1.5 is statically linked and builds 64-bit cleanly as a matter of record. The
decisive point is that the engine deliberately passes **32-bit opaque handles**
across the Lua boundary rather than object pointers, and does so *in the 64-bit
build*. That contract carries to Win64 unchanged, and it means existing mission
scripts remain valid.

### Steam / Workshop — **HIGH**
Already abstracted into `Workshop.cpp` + `WorkshopGoG.cpp` + `WorkshopSteam.cpp`
and `NetFriendsGog.cpp` + `NetFriendsSteam.cpp`. Both `libsteam_api` and
`libGalaxy` ship fat with x86_64 slices, and both vendors publish Win64 SDKs.

### Third-party middleware — **HIGH**
Every dependency observed already exists in 64-bit form: Ogre 1.10.0 (fat),
Plugin_ParticleFX (fat), RenderSystem_GL (fat), steam_api (fat), Galaxy /
GalaxyPeer (fat), Lua 5.1.5 (static), Boost/Asio/filesystem, websocketpp,
Vorbis/Ogg, Theora, libyuv. No middleware was found that exists only as a 32-bit
Windows binary. This is the single most-cited BZR64 blocker and the evidence does
not support it.

### Platform glue — **MEDIUM**
The seam is real and narrow — 9 of 383 TUs — and it is *named*, which makes the
boundary auditable. Rated MEDIUM rather than HIGH only because the Windows half of
that glue has to be written from scratch against a Mac reference that implements
the other platform.

### Summary

| Subsystem | Rating |
|---|---|
| Core simulation | HIGH |
| GameObject / object system | HIGH |
| DistributedObject / networking | HIGH |
| Save / load | MEDIUM |
| Resource management | MEDIUM |
| Renderer | MEDIUM |
| Audio | MEDIUM |
| Input | MEDIUM |
| Filesystem | HIGH |
| Threading | HIGH |
| Lua / scripting | HIGH |
| Steam / Workshop | HIGH |
| Third-party middleware | HIGH |
| Platform glue | MEDIUM |

No subsystem rated LOW or UNKNOWN. That is a genuine result and it should be read
narrowly: it says *no subsystem presents an architectural barrier to 64-bit*. It
does not say the work is small.

---

## 3. Network and save compatibility implications

| Question | Answer | Confidence |
|---|---|---|
| Could 32-bit and 64-bit clients share packet formats? | **Yes.** The perm-state packet is byte-identical between the shipped 32-bit and 64-bit builds — proven by disassembling the Mac writer and Windows reader independently. | Proven (for perm-state; other packet types unexamined) |
| Do object handles remain compatible? | **Yes.** 32-bit slot+generation encoding, unchanged in LP64. | Proven |
| Do network IDs remain compatible? | **Yes.** `uint32` `(playerID<<16)+counter`, unchanged in LP64. | Proven |
| Does serialization use explicit widths? | **Yes**, in both the save path and the wire path. | High |
| Do savegame formats remain fixed-width? | **Probably.** Prior pass proved explicit-width typed writes with matching field order, but the 8-byte persistent-ID path was never examined and no interop test has been run. | Probable |

**Nothing found so far would prevent compatibility.** A future BZR64 should
therefore preserve the externally visible identifiers and formats rather than
inventing replacements — the evidence says the originals were designed to survive
this exact transition.

Caveat, stated plainly: this is proven for the perm-state packet. The full packet
catalogue (`SNIPE_PACKET`, `BANDWIDTH_PACKET`, `PINGREPLY_PACKET`,
`SPAWNPOINT_PACKET`, and the temp-state path) has not been checked field-by-field.

---

## 4. Platform boundaries

| Layer | Contents | Evidence |
|---|---|---|
| Shared core engine + game logic | ~374 of 383 TUs — simulation, AI tasks, `GameObject`/`DistributedObject`, weapons, missions, UI, `Net.cpp`, `LuaMission.cpp`, `Workshop.cpp`, `FileUtil.cpp`, `Zfsaux.cpp` | TU census |
| Platform abstraction | paired TUs: `Ogre3d_wrapper.cpp`/`…OSX.mm`, `Ogre76Handler.cpp`/`…OSX.mm`, `appstartcommon.cpp`/`appstartapple.mm`, `Workshop.cpp`/`WorkshopGoG`/`WorkshopSteam` | TU naming |
| macOS-specific | 9 `.mm` TUs: `AppDelegateOSX`, `appstartapple`, `InputBridge`, `Keyboardmac`, `inputmac`, `mousemac`, `Ogre3d_wrapperOSX`, `Ogre76HandlerOSX`, `OgreViewOverlayOSX` | symbol census |
| Windows-specific | D3D9/D3D11 RenderSystem, `DSOUND.dll`, `WINMM.dll`, `WS2_32.dll`, Win32 windowing/input | Windows import table |
| Third-party middleware | Ogre 1.10 + plugins, Steam API, GOG Galaxy, Lua 5.1.5, Boost, websocketpp, Vorbis/Ogg, Theora, libyuv | link deps both builds |

**The shipped macOS x86_64 binary is direct evidence of a mostly portable core with
replaceable platform layers.** The macOS-specific surface is 2.3% of translation
units, it is confined to app lifecycle, input and renderer-context glue, and every
piece of it has a named platform-neutral counterpart.

---

## 5. Overall verdict

> ### Technically Possible but Major Reconstruction Required

Justification, and specifically why not the more optimistic option:

The tempting reading is "a 64-bit build exists, therefore BZR64 is Strongly
Plausible". That inference does not hold, and the evidence shows why: what exists
is a 64-bit build *of a codebase we do not have*. Every favourable finding in this
report is about **architecture** — identifiers, wire formats, layering, middleware
availability. None of them reduce the amount of code that would have to be written.

What the evidence genuinely establishes is that the *usual* reasons a project like
this dies are absent here. There is no 32-bit-only middleware. There are no
serialized pointers. There is no pointer-width identifier leaking into save files
or packets. There is no platform code smeared through game logic. Those were the
open risks, and they came back negative.

What remains is volume: ~383 translation units and 979 RTTI classes to reconstruct
without source, across two incompatible C++ ABIs, with the renderer and audio
backends being precisely the areas where the Mac reference helps least.

It is not "Plausible but High Risk" — the technical risk is now measurably low. It
is not "Currently Impractical" — the path is clear and productive, as this pass
demonstrates. It is not "Insufficient Evidence" — the evidence base is substantial.
It is a large, tractable, well-understood reconstruction.

**Strategic note.** Because the binding constraint is source availability rather
than architecture, the highest-leverage action may not be reverse engineering at
all. Obtaining source or build access would collapse a multi-year reconstruction
into a port that this report's evidence suggests would be comparatively routine.
Reconstruction should be pursued as the path that does not depend on someone else
saying yes — not because it is the cheapest one.

---

## 6. Next 3–5 highest-value reconstruction targets

1. **Close the `DistributedObject` / `GameObject` field boundary.**
   `sizeof(DistributedObject)` has a proven lower bound of `0x180` and no upper
   bound. Until it is closed, every field between `GameObject+0x28` and
   `+0x1A8` is attributed ambiguously — including two fields the prior pass proved
   (`illumination`, `perceivedTeam`). Method: find a class deriving from
   `DistributedObject` other than through `GameObject`, or an `operator new` size at
   a direct allocation site. Highest value because it gates everything downstream.

2. **Map the full replication packet catalogue.**
   The perm-state packet is proven cross-architecture identical. Extend the same
   writer/reader disassembly method to temp-state, `SNIPE_PACKET`,
   `BANDWIDTH_PACKET`, `PINGREPLY_PACKET`, `SPAWNPOINT_PACKET` and the damage path.
   The wire protocol is the interop contract a BZR64 must preserve, so it is the one
   artifact worth getting exhaustively right.

3. **Class-hierarchy census across all 979 RTTI types.**
   The `__vmi_class_type_info` decoding used here works generically. Running it over
   every Mac typeinfo would produce a complete, evidence-backed inheritance graph in
   one pass — converting the largest single body of unknown Windows structure into
   named hierarchy. Mechanically cheap relative to its value.

4. **Prove save/BZN cross-platform interop field-by-field.**
   Save/load is the weakest MEDIUM rating and the one with a concrete unexamined
   item (the 8-byte persistent-ID path). Resolving it also determines whether
   existing saves survive a BZR64, which is a user-visible requirement.

5. **Map the `Ogre76*` resource/renderer seam.**
   `Ogre76Archive`, `Ogre76Handler`, `Ogre3d_wrapper` are the boundary between
   portable game code and the renderer. It is the largest MEDIUM-rated area where
   the Mac binary still helps, and it determines how much of the renderer is
   genuinely replaceable versus entangled.

---

## 7. Evidence limitations

Stated so the confidence ratings are not over-read:

- The synchronized 2017-03-20 beta manifest pair remains **denied** by Valve
  (`Access Denied` on manifest-code request). All correlation here is
  final-to-final, so release-date drift cannot be fully separated from platform
  divergence.
- Windows correlations rest on string-literal anchors plus, for `Create`, structural
  field-offset agreement. Instruction-byte matching across MSVC and Clang was tried
  and **does not work** — recorded as a negative finding.
- No Mac build was executed. No cross-platform save or packet interop test was run.
  Nothing in this pass modified game behaviour or introduced a shim patch.
- `sizeof(DistributedObject)` is a lower bound only.
- Subsystem ratings for audio, input and renderer rest on link-dependency and TU
  naming evidence, not on disassembly of those subsystems.
