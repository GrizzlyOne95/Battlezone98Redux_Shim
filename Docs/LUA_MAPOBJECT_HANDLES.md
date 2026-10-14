# Lua `Send` of map-authored objects (label-derived handle ids)

Setting: `[Network] LuaMapObjectHandles` (default ON; legacy env alias `OPENSHIM_LUA_MAPOBJECT_HANDLES`; restart required).
Code: `src/patches/lua_handle_sync.cpp`, pure logic in `include/lua_handle_sync.h`, tests in `tests/lua_handle_sync_tests.cpp`.

## Defect

Lua `Send(to, ...)` packs a Handle argument as one dword, the object's `DistributedObject::dwLocalID`, and the
receiver turns that dword back into an object. `dwLocalID` is only ever assigned by
`DistributedObject::SetLocal` (`owner << 16 | counter`), so objects that came out of the `.bzn` and were never
networked (geysers, beacons, scenery) have id 0. The sender writes 0, the receiver finds nothing and pushes nil;
the argument vanishes from the receiver's argument list.

Seen live in Campaign Reimagined misn06: the leader's `SetObjectiveOff(geyser)` reached guests with args `[]`.

Labels, by contrast, resolve to the same object on every peer (`GetHandle(label)`).

## Evidence (exact GOG Redux 2.2.301, SHA-256 `8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`)

Bytes read from the GOG executable with Rizin on 2026-10-13; the Redux Ghidra export numbering matches this image.
Every pattern below is a unique whole-image match.

| Address | Function | Bytes / role |
|---|---|---|
| `0x00505410` | Lua handle packer (1.5 `PackHandle` @ `0x0041911C`), cdecl `(buf**, limit, L, idx)` | `55 8B EC 83 EC 0C 8B 45 14 50 8B 4D 10 51 E8 ...`; `0x0050541E` Lua value to handle, `0x0050542D` `GameObjectHandle::GetObj` (`0x004DA060`), then writes 4 bytes and bumps the type byte's count |
| `0x00505463` | pack: `mov ecx,[ebp-4]; add ecx,0x18` | `8B 4D FC 83 C1 18`: GameObject to its DistributedObject subobject |
| `0x00505469` | pack: **`call 0x004B9A90`** | `E8 22 46 FB FF`, result stored verbatim (`mov [edx],eax`, `0x00505479`) |
| `0x004B9A90` | `DistributedObject::GetLocalID` | `55 8B EC 51 89 4D FC 8B 45 FC 8B 40 64 8B E5 5D C3`: `mov eax,[ecx+0x64]` |
| `0x00505490` | Lua handle unpacker (1.5 `UnpackHandle` @ `0x0041C1B7`), cdecl `(buf**, L)` | `55 8B EC 83 EC 08 C7 45 FC 00 00 00 00 8B 45 08 ...`; reads 4 bytes only when the type byte's low 5 bits (count) are non-zero |
| `0x005054C5/6` | unpack: `push eax; call 0x004B9AB0; add esp,4` | `50 E8 E5 45 FB FF 83 C4 04`; the call is rewritten |
| `0x004B9AB0` | `DistributedObject::GetGameObject(id)`, cdecl | looks the id up in two distributed-object maps (`0x0094E29C`, then `0x0094E28C`) and returns map value minus `0x18` |
| `0x00477590` | object to handle (0 for null) | called right after the lookup, then `0x004FF770` pushes the handle or nil |
| `0x004623E0` | `GameObject::GetLabel` | `55 8B EC 51 89 4D FC 8B 45 FC 8B 80 00 01 00 00 8B E5 5D C3`: label `char*` at `+0x100` |
| `0x00917A74` | `GameObject::objectList` | read by `mov eax,[0x917A74]` at `0x005C7E96`, the engine's `GetHandle(label)` walker; the pointed-to vector has `_Myfirst` at `+0`, `_Mylast` at `+4` (what `0x0041FBD0`/`0x0041FC30` return) |

1.5 reference (PDB-matched): `SetLocal` @ `0x0048F80B` is the only writer of `dwLocalID`; `GetHandle(char*)` @ `0x00460D8B`.

## Design

Only the two call sites above are rewritten (REL32 patches with the original five bytes verified). `GetID` and
every other consumer of `GetLocalID`/`GetGameObject` stay stock.

* **Pack.** Id from the stock accessor. If it is non-zero it is returned untouched. If it is 0, the object has a
  label, and that label is unique among live objects, the id sent is
  `0x80000000 | (fnv1a32(label) & 0x7FFFFFFF)`. The payload stays four bytes, so packet sizes and the 1150-byte
  `Send` buffer accounting are unchanged.
* **Unpack.** The stock lookup runs first, so a real object always wins. Only when it finds nothing and the id has
  the high bit set does the shim scan the engine's own object vector, hash each label, and return the one object
  that owns the hash. Unknown, ambiguous or colliding hashes return null, so the receiver pushes nil exactly as
  before.
* **No wire collision.** Real ids are `owner << 16 | counter`; a high-bit real id would need a network owner id of
  `0x8000` (32768) or more, and the unpack side lets the stock lookup win regardless.
* **Collisions fail closed.** The index is rebuilt on use (pack side reuses it for 100 ms; unpack always rebuilds
  because it returns a pointer). A hash shared by two different labels, or a label carried by two objects, is
  neither sent nor resolved, and is logged (budgeted). So there is nothing to rebuild per mission load: the
  index is derived from live objects at use time and cannot go stale across loads.
* **Labels are read through the engine** (`GameObject::GetLabel`, SEH-guarded, 127-byte cap) and objects come from
  the engine's object vector (bounded to the 0x1000-slot pool), so no `GameObject` offset is hardcoded except
  the `0x18` the pack signature itself contains.
* **Mixed lobbies.** A stock receiver looks the reserved id up, finds nothing, pushes nil: the same outcome as the
  id 0 it got before. A stock sender never emits a reserved id. Shim-to-shim peers resolve the object.
* **Gating.** Six `resolves` entries in `scripts/patches.json` (`Lua::PackHandle id load call`,
  `Lua::UnpackHandle object lookup call`, `DistributedObject::GetLocalID`, `DistributedObject::GetGameObject`,
  `GameObject::GetLabel`, `GameObject::objectList`), all `require_unique`. The installer additionally requires
  each call site to target its expected accessor, both sites to be `E8` calls, and restores the pack site if the
  unpack site cannot be patched. Any miss leaves the engine untouched and logs once. Steam uses the same image
  behind SteamStub; the install runs at the same plugin stage as the faction-pool patch.
* **Config.** `[Network] LuaMapObjectHandles = 1` (default). `0` skips installation entirely. Logged once at install
  (`[LUAHANDLE] installed: ...` or `disabled`).

## Limitations

* Only objects present in the receiver's own object list under the same label resolve. An object that exists on
  the sender but was created at run time without a network id and without a label is still nil.
* Two live objects sharing a label (the engine's `GetHandle(label)` returns the first) are treated as ambiguous
  and are not sent.
* Both peers need OpenShim with the setting on for the object to arrive.
* Handles inside Lua tables go through the same packer and are covered; this was not separately exercised live.

## Verification

Unit tests (`lua_handle_sync_tests`): FNV-1a vectors, pinned wire ids, reserved-bit rules, unique round trip,
duplicate-label ambiguity, a brute-forced real hash collision (both insertion orders), foreign-label lookups,
length cap, clear. Full CTest suite 101/101, `run_ini_tests.ps1` clean, `patch_registration_tests` clean.

Live (2026-10-13, two real clients via `Run-BZRCoopMission.ps1 -Mission misn03 -Scenario replication-cases
-OpenShimRepo <this worktree>`; new case **C3** in `coopflow/scenarios/replication-cases.ps1`): the host sends
the map-authored geyser `shot_geyser` (`eggeizr1`, `IsLocal` false, never networked).

| Setting | Guest receives | Evidence |
|---|---|---|
| `LuaMapObjectHandles = 0` | `#args == 1`, handle missing (`local-only`) | run `handlesync-off-1`; log `[LUAHANDLE] disabled` |
| `LuaMapObjectHandles = 1` | `#args == 2`, same object as `GetHandle('shot_geyser')`, 0.2 s (`replicated`) | run `handlesync-on-2`; host `sending map object "shot_geyser" as reserved id 0xB36E9649`, guest `reserved id 0xB36E9649 -> map object "shot_geyser"` |

Both runs stop at the pre-existing scenario step I1 after the deliberate 128-byte `Send` crash case (J3) and fail
identically with the fix on and off; they are not a regression signal. Both clients logged
`[LUAHANDLE] installed: pack=0x00505469 unpack=0x005054C6 getLocalId=0x004B9A90 getGameObject=0x004B9AB0
getLabel=0x004623E0 objectList=0x00917A74`.

To repeat: build `Release|Win32`, prepare instances (the test instances' `[Network] PreLobby` must be `0` or the
lobby step stalls on the multiplayer setup screen), then run the command above with `-OpenShimRepo` pointing at the
checkout. Add `LuaMapObjectHandles = 0` under `[Network]` in the instances' `openshim.ini` for the stock baseline.
The raw-handle probe is C3; CR's own Lua sends labels, so only a raw `Send` of a handle proves the native path.
