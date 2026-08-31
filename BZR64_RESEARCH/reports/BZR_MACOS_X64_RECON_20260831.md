# Battlezone 98 Redux macOS x64 reconstruction qualification

Date: 2026-08-31

App: Battlezone 98 Redux (`301650`)

Primary Windows reference: shipped GOG 2.2.301 executable

Mac fallback fixture actually obtained: depot `301651`, manifest `730966170255625169`

## Executive conclusion

`MAC_ARCHITECTURE = PROVEN`: the shipped Mac executable is a thin, PIE, Mach-O 64-bit **x86_64** image. It is not ARM64 and not a universal main executable.

`PEER_BUILD_CONFIDENCE = HIGH` for the obtained 2.2.301 Mac final versus the Windows 2.2.301 game. This is supported by matching product versions, game subsystem and class identities, Lua 5.1.5 integration, Ogre 1.10.0, an identical three-mode `cWorkshop` resource rebuild design, the same ordered `GameObject::Save` fields, and the same loose-data topology. Platform backends and C++ ABIs differ, but the game layer is recognizably a peer build rather than a separate port.

The Mac binary materially reduces the difficulty of source-equivalent Win64 reconstruction. It preserves exact C++ names, RTTI, vtables, translation-unit names, function-start and unwind metadata, and direct 64-bit layouts. This turns many Windows x86 naming and layout questions into cross-checkable hypotheses.

The strongest concrete results are:

- three Windows `cWorkshop` resource rebuild functions map directly to named Mac functions;
- `cWorkshop::mode` expands from Windows `+0x8C` to Mac `+0x148`, while the remembered content identity moves from `+0x90` to `+0x150`;
- four `GameObject` fields have proven x86-to-x64 offsets through the same named serialization labels;
- the Mac Lua bridge deliberately retains 32-bit game handles rather than exposing object pointers;
- Mac save code serializes typed fields with explicit byte counts instead of dumping native structs.

The user-requested synchronized beta pair—Mac `8544972427174986303` and Windows `1071688624677329472`, both recorded by SteamDB at 2017-03-20 09:38:35 UTC—could not be acquired. SteamCMD's content service returned `Access Denied` while requesting a manifest code for both IDs. No substitute was used. Consequently, this report does **not** claim beta-to-beta comparisons.

## 1. Acquisition evidence

### Windows references

The common GOG and Steam locations were searched. Both installed executables report `FileVersion` and `ProductVersion` 2.2.301 and were copied into the analysis workspace; neither live executable was modified.

| Build | Installed path | Size | SHA-256 |
|---|---|---:|---|
| GOG, primary unwrapped reference | `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\Battlezone98Redux.exe` | 5,425,152 | `8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413` |
| Steam, secondary reference | `C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\Battlezone98Redux.exe` | 5,554,832 | `D298782FC9A13EDB0665DB934110440C45461031DB5F7FE1A76C8784B61CC90D` |

### Final Mac manifest obtained

Exact command:

```text
C:\steamcmd\steamcmd.exe +login iankf1 +download_depot 301650 301651 730966170255625169 +quit
```

Steam retrieved the requested manifest and 20,837 regular files. It then failed to create nine standard macOS framework symlinks because the Windows process lacked symlink privilege (`Win32 result 1314`). A local protobuf manifest parser proved the manifest contains 20,837 regular files, 93 directories, and nine symlinks. Every symlink points to already-present versioned Ogre framework content. No downloaded file was edited.

| Item | Value |
|---|---|
| Exact manifest | `301651 / 730966170255625169` |
| Manifest SHA-256 | `187735A9893ACE0BFF3EA5A5066B893A15B52CC04A1DD1D6D9165F41492C2183` |
| Manifest content size | 2,280,957,958 bytes |
| Analysis copy | `BZR64_RESEARCH/macos_x64/depot_301651_730966170255625169` |
| Primary executable SHA-256 | `DAE80722CE6B253F1C7F1FD4807BDB379822EFC3735E7DB799D40E2470BA2C00` |

### Synchronized beta acquisition gate

The following exact requests were attempted:

```text
download_depot 301650 301651 8544972427174986303
download_depot 301650 301652 1071688624677329472
```

The Mac request was also repeated after setting `@sSteamCmdForcePlatformType macos`. All attempts failed before depot download. The local Steam content log records:

```text
App: 301650, Depot: 301651, Manifest: 8544972427174986303 ... 'Access Denied'
App: 301650, Depot: 301652, Manifest: 1071688624677329472 ... 'Access Denied'
```

No cached copy of either manifest was found under the local SteamCMD, Steam client, or repository paths. This is a server authorization result, not an architecture or tool-parsing failure. The exact command evidence is preserved in `reports/evidence/steam_depot_acquisition.txt`.

## 2. Windows x86 binary qualification

The primary GOG executable is PE32/COFF i386 with:

- PE timestamp `2017-03-28 03:21:48 UTC` (`0x58D9D6CC`);
- image base `0x00400000`, entry RVA `0x43EE5E`, image size 43,053,056;
- linker version 12.0 and imports of `MSVCP120.dll`/`MSVCR120.dll`, consistent with the Visual C++ 2013 generation;
- `IMAGE_FILE_LARGE_ADDRESS_AWARE` and `IMAGE_FILE_32BIT_MACHINE`;
- relocations stripped and no usable ASLR relocation table;
- no COFF symbol table and only two non-game exports (GPU selection hints);
- embedded CodeView path `D:\code\BattleZoneTest\build\bin\Release\battlezone\battlezone98redux.pdb`.

This reconfirms that LAA is already present. It is not a remaining memory-limit fix.

Significant imports are `OgreMain.dll`, `Plugin_TheoraVideoSystem.dll`, `libtheoraplayer.dll`, `libvorbisfile.dll`, `Galaxy.dll`, `steam_api.dll`, `DSOUND.dll`, `WINMM.dll`, `WS2_32.dll`, and standard Windows system DLLs.

## 3. Mac architecture proof and Mach-O metadata

`llvm-readobj` identifies the primary executable conclusively as `Mach-O 64-bit x86-64`:

| Property | Evidence |
|---|---|
| Magic | `0xFEEDFACF` (`Magic64`) |
| CPU | `0x01000007`, x86_64 |
| Subtype | 3, x86-64 all |
| Container | Thin; one Mach-O header, not fat/universal |
| PIE | Yes, Mach flags `0x218085` include `PIE` |
| Preferred unslid base | `__TEXT` at `0x100000000` |
| Runtime behavior | dyld applies an ASLR slide because PIE is set |
| UUID | `A31437EC-6EC1-3F44-9045-0CD95C8245B0` |
| Minimum OS / SDK | macOS 10.9 / SDK 10.12 (`16C58`) |
| Bundle version | 2.2.301, build 301 |
| Entry | `LC_MAIN` file offset `0x1AB20` |
| Signing | no `LC_CODE_SIGNATURE` in the executable |
| Encryption | no `LC_ENCRYPTION_INFO` command |

The `__PAGEZERO` segment occupies the first 4 GiB of virtual address space, a standard 64-bit null/low-address guard. `__TEXT` is based at `0x100000000`; `__DATA` begins at `0x10044C000`. This is true 64-bit code and data, not a 32-bit executable packaged in a 64-bit bundle.

## 4. Runtime and dependency inventory

| Component | Architecture | Size | SHA-256 / version notes |
|---|---|---:|---|
| Main executable | thin x86_64 | 10,064,980 | `DAE807...2C00` |
| `Ogre.framework/.../Ogre` | fat x86_64+i386 | 17,604,384 | `EC0E7F...BE837`, install/current version 1.10.0 |
| `Plugin_ParticleFX.framework` | fat x86_64+i386 | 512,992 | `41DA0B...38203`, version 1.10.0 |
| `RenderSystem_GL.framework` | fat x86_64+i386 | 3,310,576 | `470749...A62B`, version 1.10.0 |
| `libGalaxy.dylib` | fat i386+x86_64 | 12,206,064 | `1157CB...9FEF` |
| `libGalaxyPeer.dylib` | fat i386+x86_64 | 27,725,672 | `64F553...6821` |
| `libsteam_api.dylib` | fat i386+x86_64 | 540,944 | `BAAD1F...33ED` |

The main executable dynamically links the three Ogre 1.10.0 frameworks, Galaxy, Steam API, `libc++.1.dylib`, `libSystem`, AppKit/Foundation/CoreGraphics, IOKit, OpenAL, AudioToolbox, Security, and SystemConfiguration.

Lua is statically linked and identifies itself exactly as Lua 5.1.5. Symbol evidence also shows statically linked Boost/Asio/filesystem, websocketpp, Vorbis/Ogg, Theora player code, and libyuv. No bundled SDL or OIS binary exists; five OIS text/symbol matches are not evidence of a linked OIS runtime. FreeImage and zlib identities were not found in the main executable. Mac input/windowing code uses native AppKit/IOKit; audio uses system OpenAL/AudioToolbox.

The Ogre framework version and retained `Ogre76Archive` source name place the Mac renderer in the expected Redux/Xalafu-era Ogre 1.10 generation.

## 5. Symbols, RTTI, vtables, and compiler artifacts

The Mac executable is unusually strong as a reconstruction oracle.

| Category | Windows x86 2.2.301 | Mac x86_64 2.2.301 |
|---|---|---|
| Game C++ exports | none; two GPU-hint exports only | 1,729 external definitions plus extensive local names |
| Printable symbols | COFF symbol table absent | 26,610 via `llvm-nm`; Mach table has 101,824 entries |
| RTTI identity | 979 unique MSVC RTTI-name strings; structures recoverable | 996 `typeinfo for`, 977 `typeinfo name for` symbols |
| Vtables | recoverable heuristically/MSVC RTTI | 815 named vtable symbols |
| Source artifacts | one PDB path | 383 named `.cpp`/`.mm` translation-unit initializers plus source/header paths |
| Function boundaries | heuristic; no x86 exception directory | `LC_FUNCTION_STARTS`, symbols, unwind and exception metadata |
| Unwind/exception data | limited x86 SEH patterns | `__unwind_info`, `__eh_frame`, `__gcc_except_tab` |

Exact Mac class identities include `GameObject`, `Craft`, `HoverCraft`, `Walker`, `Weapon`, `Building`, `Factory`, `Recycler`, `Armory`, `Howitzer`, `DistributedObject`, `AttackTask`, `PatrolTask`, and `LuaMission`. Translation-unit names include `GameObject.cpp`, `HoverCraft.cpp`, `Walker.cpp`, `Weapon.cpp`, `DistributedObject.cpp`, `AttackTask.cpp`, `PatrolTask.cpp`, `LuaMission.cpp`, and `Net.cpp`.

String inventory found 1,184 unique absolute `/Users/...` source/code paths and 858 unique `../../source/...` paths in the Mac final. The Windows final has no comparable source-path strings beyond its single CodeView PDB path. One concrete Mac path is `/Users/brianlloyd/code/Battlezone98/source/OgreRender/Ogre76Archive.cpp`. The presence of `___clang_call_terminate`, Itanium mangling (`_ZTV`, `_ZTI`, `_ZTS`), `std::__1`, and `libc++` proves a Clang/libc++/Itanium-ABI toolchain. The precise Apple Clang release string was not embedded.

The final-build assertion baseline is 21 unique Mac strings containing `assert` versus nine on Windows. Most are runtime/third-party artifacts (`___assert_rtn`, Ogre `RuntimeAssertionException`, Lua `assert`, and websocketpp proxy assertions), so this count does not prove a game-code debug build. It provides an exact baseline for detecting additional beta-only assertions if the synchronized manifests become available.

Because the synchronized beta manifests were denied, whether either beta retains *additional* assertions, names, or paths remains untested. The obtained final Mac already retains far more identity than the Windows final.

## 6. Proven resource-system function and layout match

Direct disassembly gives the following mapping:

| Mode | Windows x86 | Mac x86_64 | Shared behavior |
|---:|---|---|---|
| 4 | `0x0076A030`, `buildMainResources` | `0x1000A9FC8`, `cWorkshop::buildModResources()` | guard mode; clear runtime/path state; remove mod paths; clear and initialize Ogre `Modable`; rebuild runtime resources |
| 2 | `0x0076A240`, `buildMPResources` | `0x1000A9D7C`, `cWorkshop::buildMPResources()` | same sequence |
| 1 | `0x0076A430`, `buildIAResources` | `0x1000A9B48`, `cWorkshop::buildIAResources()` | same sequence |

The functions are not matched merely by a shared string. They use the same mode constants, early-return guard, resource-path reset, `Ogre76Archive::removeAllModPaths`, `ResourceGroupManager::clearResourceGroup("Modable")`, `initialiseResourceGroup("Modable")`, and runtime rebuild order.

The layouts are:

| Field | Windows x86 | Mac x86_64 | Evidence |
|---|---:|---:|---|
| mode | `+0x8C` | `+0x148` | direct reads/stores in all three functions |
| remembered content identity | `+0x90` | `+0x150` | Windows existing static RE; Mac constructor initializes a 24-byte libc++ string to `**INVALID**` |

The Mac mode remains a four-byte integer. Four bytes of padding follow it so the 24-byte libc++ string starts at an eight-byte-aligned address. The larger shift is consistent with preceding pointer-rich containers expanding under LP64. No claim is made that Windows and Mac STL objects are ABI-compatible.

## 7. Proven `GameObject` field comparison

Windows shipped-binary work had already proven four complete-object offsets from `GameObject::Save` field-name xrefs. The named Mac `GameObject::Save(__sFILE*)` at `0x10001EE4A` serializes the same labels directly:

| Field | Windows x86 | Mac x86_64 | Serialized size |
|---|---:|---:|---:|
| `illumination` | `+0xDC` | `+0x110` | 4 |
| `perceivedTeam` | `+0x174` | `+0x1C8` | 4 |
| `isVisible` | `+0x180` | `+0x1DC` | 4 |
| `seen` | `+0x184` | `+0x1E0` | 4 |

This is a high-value 64-bit layout map: semantic fields and wire sizes remain stable while in-memory offsets expand.

The Mac object arena also exposes handle mechanics. `GameObject::InitHandles()` creates 4,096 slots at a `0x600`-byte arena stride. `GameObject::GetObj(int)` interprets the upper 12 bits as the slot index, masks the lower 20 bits as a generation value, and returns a 64-bit pointer only after comparing that generation with the slot's `+0x1A0` field. The arena stride is an allocation-slot stride, not asserted as `sizeof(GameObject)`.

## 8. Lua integration

The Mac binary contains a full static Lua 5.1.5 implementation and named bindings including `BuildObject(lua_State*)`, `OpenODF(lua_State*)`, `GetODFBool`, `GetODFInt`, `GetODFFloat`, and `GetODFString`.

The handle boundary is proven fixed-width:

- `BuildObject(lua_State*)` reads Lua integers but passes team and handle-like values in 32-bit registers to engine overloads returning `int`;
- `PushHandle(lua_State*, int)` tests a 32-bit integer, sign-extends it, and passes it to `lua_pushlightuserdata`; zero maps to Lua `nil`;
- callbacks reconstruct handles from `GameObject`'s 12-bit slot index and 20-bit generation fields;
- `GameObjectHandle::GetObj(int)` accepts the same 32-bit encoding.

Thus a Lua “handle” is not a native object address even on x86_64. A Win64 reconstruction should preserve this 32-bit opaque ID contract.

## 9. Serialization, BZN/ODF, and network observations

The Mac `GameObject::Load/Save` pair does not read or write raw native structs. It calls typed overloads with explicit sizes: booleans are one byte; `int`, `unsigned int`, and `float` fields are four bytes; `VECTOR_3D` is 12 bytes; selected persistent IDs are explicitly eight bytes. The same ordered field labels seen in Windows—including `illumination`, `seqNo`, `isVisible`, `seen`, `independence`, `curPilot`, `perceivedTeam`, `wpnID`, `enabled`, and `selected`—survive in Mac.

This is **high-confidence evidence of deliberate fixed-width serialization**, including 32-bit game handles and 32-bit team/state fields. It is not yet proof that every BZN, save, or network packet is cross-platform identical. The following remain to be checked field-by-field:

- `out_ptr`/`in_ptr` eight-byte persistent-ID handling;
- `DistributedObject::ReadPermState` and packet schemas;
- structure packing in network-only messages;
- an actual Mac-produced save/BZN loaded by Windows and vice versa.

ODF semantics are strongly shared: both game logic and named Mac Lua bindings use the same ODF vocabulary. BZN/TRN resource strings and parsers are present, but this pass did not manufacture a layout for an unproven parser structure.

## 10. Data and topology comparison

The final Mac bundle and current Windows install have identical relative file counts in the shared loose roots: 1,605 `BZ_ASSETS`, 370 `BZ_ASSETS_CORE`, 15 `giddi`, 26 `music`, and 22 `packaged_mods` files. Most files also have matching sizes; samples from core Ogre materials and packaged campaign content are byte-identical by SHA-256. Some detail-atlas CSVs differ, consistent with comparing a historical final depot against a later/current Windows content install.

This supports shared data expectations but is not used as proof of exact build synchronization. The denied 2017-03-20 beta pair is the correct future asset-diff fixture.

## 11. Compiler and ABI assessment

Windows uses the MSVC 12.0 generation, the MS ABI, four-byte pointers, MSVC RTTI, x86 `thiscall`, and MSVC 2013 STL layouts. Mac uses Clang, the Itanium C++ ABI, LP64 eight-byte pointers, libc++ (`std::__1`), and System V x86_64 calling conventions.

Consequences for reconstruction:

- class meaning and member order can be transferred; raw offsets cannot;
- libc++ `std::string`/`std::vector` layouts cannot be copied to MSVC Win64;
- vtable slot semantics can be correlated, but RTTI headers and member-function ABI differ;
- pointer-bearing fields expand and alignment padding changes;
- serialized integer widths must be preserved explicitly rather than using C++ `long` or pointer-sized types;
- Mac exception/unwind metadata is useful for function boundaries, not binary compatibility.

The target is semantic/source reconstruction, not cross-platform binary ABI compatibility.

## 12. True-peer assessment

Evidence supports option **A: same Redux source generation and game code with different platform backends**.

Reasons for `PEER_BUILD_CONFIDENCE = HIGH`:

- both final executables report 2.2.301;
- the exact game class hierarchy and source units survive on Mac;
- resource-mode constants and Ogre call order match across architectures;
- `GameObject::Save` field identity and ordering match;
- Lua 5.1.5 and binding names match Redux behavior;
- both use Ogre 1.10-era integration and the same `Ogre76Archive` abstraction;
- the shared data roots and packaged content topology align;
- Mac platform-specific code is concentrated in AppKit/IOKit/OpenGL/Galaxy/Steam boundaries.

Confidence is not `PROVEN` for every subsystem. The synchronized beta fixture and more call-graph matches are needed to distinguish release-date drift from platform divergence in individual functions.

## 13. Win64 feasibility

### Path A — remain x86 and mitigate memory pressure

This remains the least disruptive path. Useful work includes allocation/fragmentation telemetry, resource-group lifetime analysis, targeted Ogre resource unloading, texture/mesh cache limits, asset deduplication, and large-allocation reduction. LAA must not be proposed; it is already enabled.

### Path B — reconstructed native Win64 Redux

This is technically plausible but large. A source-equivalent executable must recreate game/AI code, the Ogre renderer boundary, Lua integration, Steam/GOG services, networking, input, audio, filesystem/resource mounting, UI, and persistence. The Mac binary directly helps with class identities, game subsystem boundaries, vtable topology, 64-bit-safe in-memory layouts, and pointer-to-ID conversions. Windows-specific renderer/input/audio/store glue still needs a native Win64 implementation.

### Path C — Mac-assisted reconstruction

This is the most promising investigative path. The Mac names can seed evidence-qualified Windows mappings, and named Mac load/save/handle functions expose which widths Big Boat deliberately preserved. The resource and `GameObject` examples show that this is already productive, not hypothetical.

### Path D — iOS ARM64 reference

Do not prioritize iOS yet. Mac x86_64 is closer to a Win64 target in machine architecture and already has strong symbol identity. Use iOS only for gaps where Mac symbols/code are absent or where a second 64-bit ABI is needed to distinguish semantic width from platform ABI width.

## 14. How much difficulty the Mac build removes

The Mac build does not provide missing source, a compatible Win64 object ABI, or Windows backend code. It does remove much of the naming and 64-bit intent ambiguity:

- exact function/class names replace many anonymous Windows functions;
- named vtables and RTTI expose hierarchy and virtual boundaries;
- constructors and serialization reveal real LP64 offsets;
- Lua handle code proves where pointers were intentionally avoided;
- function starts and unwind metadata improve decompilation boundaries;
- source paths and translation-unit names organize the executable by subsystem.

Assessment: **material reduction in reconstruction difficulty**, especially for architecture, layouts, persistence, and gameplay logic; **limited reduction** for Direct3D, Windows input/audio, packaging, and platform-service implementation.

## 15. Remaining blockers

1. Valve currently denies manifest-request codes for both synchronized 2017-03-20 manifests.
2. No branch password, manifest request code, or cached copy was available locally.
3. Network packet layouts and `DistributedObject` persistence are not yet mapped field-by-field.
4. Only selected class fields—not complete class definitions—are proven across ABIs.
5. A cross-platform save/BZN interoperability test was not possible on this Windows host without running the Mac build.
6. The precise Apple Clang version is not embedded.

A separate Ghidra project, `BZR_Windows_Mac_2_2_301`, was created under `BZR64_RESEARCH/ghidra`; the obtained Mac final was imported and analysis completed. Further final-build decompilation was stopped after the synchronized-beta request so the beta pair can become the primary fixture if access is restored.

## 16. Recommended next experiment

First obtain authorization for the exact historical manifests: a Steam branch password/request code, a legitimate local cache, or a Steam-provided route that makes `8544972427174986303` and `1071688624677329472` downloadable. Then preserve each depot in a manifest-named directory, hash the executables, and import both into a fresh paired Ghidra project.

The first synchronized comparison should be mechanical and narrow:

1. compare version metadata, binary timestamps, runtime dependencies, RTTI/vtable/source-path counts, and loose assets;
2. map `cWorkshop::{buildModResources,buildMPResources,buildIAResources}` beta-to-beta;
3. map `GameObject::{Load,Save,GetObj}` and `PushHandle` beta-to-beta;
4. inspect `DistributedObject::{ReadPermState,WritePermState}` and network message constructors for explicit 1/2/4/8-byte widths;
5. only then expand names into AI, weapon, mission, terrain, and renderer subsystems.

If historical access cannot be restored, the next best experiment is a final Mac-to-final Windows `DistributedObject` serialization map, using the Mac names as anchors and recording only Windows addresses supported by literal/call-shape evidence.

## Evidence and machine-readable artifacts

- `reports/evidence/steam_depot_acquisition.txt`
- `reports/evidence/windows_reference_metadata.txt`
- `reports/evidence/mac_architecture_and_symbols.txt`
- `reports/bzr_x86_x64_function_map.csv`
- `reports/bzr_x86_x64_layout_map.csv`
- `tools/parse_steam_manifest.py`
