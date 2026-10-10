# Multiplayer Lua replication: prerequisite qualification

Workstream started 2026-10-07 on `agent/mp-lua-replication-research`.

The higher-level API is **not implemented or qualified**. This pass establishes
exact-build static evidence and a Lua 5.1 diagnostic harness. Every operation
still needs an independent two-peer result before it can become an API contract.
No game DLL, mission, network configuration, or live deployment was changed.

## Evidence and reproducibility

- Executable: the GOG installation's `battlezone98redux.exe`.
- SHA-256: `8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`.
- Image base: `0x00400000`; all addresses below are **VAs**, not RVAs.
- Tools: Ghidra 12.1.3 through PyGhidra, plus PE parsing with pefile. A fresh
  Ghidra project was imported from this exact executable and analyzed. Lua
  registration table pointers were independently recovered directly from PE bytes.
- Older `Tools/bz_work` executable hash:
  `d298782fc9a13edb0665db934110440c45461031db5f7fe1a76c8784b61cc90d`.
  Its addresses were not reused. The existing exported corpus was used to guide
  investigation, then the relevant paths were re-exported from the fresh project.
- This machine's raw evidence is under the game directory at
  `logs/mp_lua_replication_20261007/`: `pe_triage.json`,
  `registration_strings.json`, `function_manifest.json`, `functions/*.asm`,
  `functions/*.c`, and the saved `ghidra/MultiplayerLuaExact.gpr` project.
  `triage.py`, `inspect_project.py`, and `export_functions.py` reproduce the work.
  Generated disassembly/decompilation remains outside this public repository.

**PROVEN** below means static released-build evidence, unless a runtime source
is explicitly named. **STRONG INFERENCE** is a design implication. **UNKNOWN**
means further tracing or runtime qualification is needed. A stock mutation
containing no direct send does not prove the field is absent from later object
serialization.

## Individually traced operations

| Case | Exact-build path / proven mechanics | Current runtime evidence and remaining gate |
| --- | --- | --- |
| Stock spawn | `BuildObject` Lua binding `0x004ffb70`; transform spawn `0x005c82b0` calls `0x00571c30` and conditionally calls `0x004b8460` on the object's distributed subobject. | Existing project notes report host/client asymmetry. **UNKNOWN:** client visibility, distributed-ID readiness, AI ownership, and callback order for each placement overload. |
| EXU sync/async spawn | EXU `src/Game/Multiplayer.cpp` temporarily patches the stock call through protected `lua_pcall` and restores the patch. Exact installed bytes at `0x005c833b` are `74 0b`; the 11-byte call block at `0x005c833d` matches EXU's expected bytes. Sync NOPs the host conditional; async NOPs the ownership call. | **PROVEN:** mechanism is changing the stock ownership path. **UNKNOWN:** successful client creation, intended owner, and observed peer identity for each object class. No higher-level protocol is supplied by these helpers. |
| Locality | `IsLocal`: `0x005005c0 -> 0x005c87a0 -> 0x004b9860`, tests distributed-subobject byte `+0x68 == 1`. `IsRemote`: `0x00500600 -> 0x005c87d0 -> 0x004b9830`, tests byte `+0x68 == 2`. Both wrappers reject unresolved handles. | **PROVEN:** neither predicate is the complement of the other; invalid and other states can make both false. **UNKNOWN:** all ownership transition states and when predicates settle on peers. |
| Ownership claim | `SetLocal`: `0x00500590 -> 0x005c8770 -> 0x004b8460`, with `ECX = object + 0x18`. The callee changes locality, registers identity, and calls `0x004b8000`; the remote branch can send through `0x004b7d70`. Another branch resets locality to zero when a virtual result has flag `0x80`; that flag's gameplay meaning is **UNKNOWN**. | Existing notes report remote AI damage from careless claims. **UNKNOWN:** coordinated transfer, AI controller lifetime, competing claim recovery, and migration. Do not automatically claim every remote object. |
| Remove | `RemoveObject`: `0x004ffca0 -> 0x005c83e0`, resolves a handle, sets `ECX = object + 0x18`, then invokes distributed-subobject vtable slot `+0x10`. | Existing notes report remote deletion being restored by owner updates. **UNKNOWN:** concrete subclass delete dispatch, owner tombstone transmission, timing, and handle reuse. Must test owner-only, remote-only, and explicit peer replay independently. |
| Name | `SetName`: `0x00507170 -> 0x005cd7f0`; `SetObjectiveName`: `0x00501e90 -> 0x005c9640`; both reach `0x004d9730`, which replaces the string at object `+0x184`. The wrappers use different handle resolvers. `0x00462630` additionally excludes objects whose queried flags include `0x200`; flag meaning is **UNKNOWN**. | Existing notes report local-only visible names. **PROVEN:** shared setter, but not identical wrappers for every handle. **UNKNOWN:** snapshot/delta serialization and name retention after ownership changes. |
| Objective markers | `SetObjectiveOn/Off`: `0x00501e30/0x00501e60 -> 0x005c95e0/0x005c9610 -> 0x0049f300`, which updates object byte `+0x189` and a process-local objective list. | Existing notes report unsynchronized markers. **UNKNOWN:** whether any initial object snapshot carries the flag; late arrival and owner transfer need separate checks. Visual observations are required because this probe does not assume a working objective iterator. |
| Objective text | `AddObjective` `0x00503a40 -> 0x004f6ab0`; `UpdateObjective` `0x00503ae0 -> 0x004ff0d0`; `RemoveObjective` `0x00503b80 -> 0x004ff100`; `ClearObjectives` `0x00503920 -> 0x004f6aa0`. | Existing project runtime notes establish local UI behavior, configurable duration, and the ten-objective limit. **UNKNOWN:** agreed replay/snapshot semantics and remaining duration for a late joiner. The probe owns one named objective and never clears unrelated objectives. |
| Weapons/loadout | `GiveWeapon` `0x00503520` selects `0x005cb050` (automatic slot) or `0x005cb0d0` (explicit slot), both reach `0x00612f10`. This removes/replaces a slot and updates weapon masks through local calls and a virtual call. | Existing notes recommend explicit messaging. **UNKNOWN:** weapon class vs ammo/mask replication, player/AI differences, rollback by the owner, and re-entry effects. Do not infer all loadout state from a successful return. |
| Team / movement | `SetTeamNum` `0x00500680 -> 0x005c8840` calls distributed vtable slot `+8`. `SetPosition` vector path `0x00501710 -> 0x005c8c80 -> 0x005873a0`; `SetVelocity` `0x00501900 -> 0x005c8e90 -> 0x0046fb20`. | Existing notes report velocity synchronization and ownership sensitivity for team/position. **UNKNOWN:** per-class owner/remote semantics, update ordering, AI process changes, and peer rollback. |
| Shared variables / custom events | `Send` binding `0x005060f0`, serializer `0x00505ea0`, `Receive` dispatch `0x0050b310`, decoder `0x00506010`. Receive is explicitly invoked on the local Lua VM with sender ID, one-byte type, and decoded arguments. | **STRONG INFERENCE:** shared Lua state and event delivery need an explicit protocol. **UNKNOWN:** loopback, delivery guarantees, ordering against object replication, duplicate behavior, loss recovery, and snapshot handling. |

### Calling conventions

Several decompilations infer bogus `__thiscall` parameters for stock Lua/native
wrappers. The assembly shows stack arguments and the explicit `ECX` setup before
member/virtual calls. In particular, ownership offsets above belong to the
distributed subobject at `object + 0x18`, not to the outer object. Do not copy
the decompiler's guessed signatures into native declarations.

## Transport findings that change the design

1. **PROVEN:** the type parameter supplies only its first byte (`Send`,
   `0x00506184..0x00506186`); `Receive` pushes exactly one byte from the packet.
   A protocol needs a reserved type byte and an internal magic/version namespace.
2. **PROVEN:** this build reserves a 1152-byte packet buffer, including the two
   header bytes. Assembly initializes the packet at `EBP-0x488`, the payload at
   `EBP-0x486`, and the serializer end pointer at `EBP-0x8`. This is a local
   packing bound, **not a qualified transport MTU**; the old approximately
   244-byte reference is not a correct description of this stack buffer.
3. **PROVEN:** an argument that cannot fit is rolled back to its starting cursor,
   a log is emitted, and the already-packed prefix can still be sent. `Send`'s
   returned boolean describes the underlying send result and is not proof that
   every argument arrived. A protocol must preflight the whole envelope and check
   a terminal field/expected shape at receipt.
4. **PROVEN:** a lightuserdata handle is converted to a distributed ID through
   `0x00505410 -> 0x004b9a90`. Decode uses `0x00505490 -> 0x004b9ab0`, then
   converts the resolved object back to a local handle and pushes it through
   `0x004ff770`. Failed resolution pushes nil. Copying numeric handle values
   between peers would bypass this remapping. An unresolved reference is not
   queued for later resolution by this decoder.
5. **PROVEN:** string lengths below 31 fit in the tag; longer lengths use a
   single extra byte (`0x005058d0`). The decoder sign-extends that byte with
   `MOVSX` at `0x005059ce`, then passes it as the Lua string length and advances
   the cursor by it. Length 128 becomes -128. Strings of 128 bytes or more cannot
   be a safe stock-wire contract; lengths of 256 or more additionally wrap the
   byte written by the encoder. This was established statically, **not by
   sending a dangerous packet to a live peer**.
6. **PROVEN:** table entry counts use a similar one-byte extension and signed
   decoder (`0x00505a10`, `0x00505b50`, `MOVSX` at `0x00505b70`). At 128 entries
   the decoded loop count becomes negative and cursor alignment fails. Recursive
   encoding has no visible cycle detection. Keep tables outside the initial
   protocol until bounded type/depth/count rules are qualified.
7. **PROVEN:** the explicit weapon-slot guard at `0x00612f23..0x00612f2d`
   cannot reject an integer: it only reaches its failure branch for an integer
   below zero and at least five. `0x00417f40` then directly indexes the slot.
   Require slots **0..4** before reaching this path. This is not runtime-tested
   with an invalid slot.

The probe uses scalar payloads, at most eight values, strings at most 127 bytes,
and a conservative total packing estimate at most 200 bytes. These are probe
constraints, not a claim that a production transport contract is established.

## Qualification harness

Source: `reverse_engineering/test_missions/mp_lua_replication/mprep.lua`.
Instructions: the neighboring `README.md` and `results_template.csv`.

The module separates local mutations from observer traffic: received packets
only log values or watch an announced disposable object. They never spawn,
remove, rename, change weapons, change team, or claim ownership. Each local
operation is invoked explicitly on the chosen peer. This makes owner-only,
remote-only, and explicit application on both peers different experiments.

Validated offline: **51 assertions under Lua 5.1** with `mock_test.lua`, including
nil argument preservation, reserved packet routing, sender removal, unresolved
handles, length/budget limits, objective reuse, invalid slots, and ownership
claim gating. These tests validate probe behavior, not game replication.
Two-client engine tests are **NOT RUN**.

## Gate before implementing the reusable API

- Establish identity and sender mapping independently of player team; record
  local net ID, host net ID, callback IDs, and migration behavior. Do not trust
  the first sender that announces itself as host.
- Qualify spawn/remove for every supported object class and placement overload;
  establish stable object identity, pending-reference behavior, owner execution,
  and deletion tombstones across late join and reused handles.
- Qualify names, text, markers, and each weapon/loadout field separately. A UI
  field that needs peer-local application must also have snapshot replay.
- Qualify unicast/broadcast, self-delivery, ordering, loss/duplicates, maximum
  safe envelope, and timing against distributed-object creation/removal.
- Qualify owner transfer with one claimant and a controller handoff. Where that
  cannot be demonstrated, the eventual API should reject the operation or route
  to the verified current owner; it must not silently call `SetLocal`.
- Only then choose the API contracts for host state revisions, per-object IDs,
  session/host epochs, readiness, acknowledgement/retry, deduplication, snapshots,
  and separate durable state vs transient events. Explicitly define whether host
  migration is supported or invalidates the session.

Repository routing remains: reusable runtime/Lua API in **EXU**; any required
native hooks and patch policy in **OpenShim**; campaign adoption in **CR**.
The roadmap item remains research in progress; no implementation completion is
claimed.
