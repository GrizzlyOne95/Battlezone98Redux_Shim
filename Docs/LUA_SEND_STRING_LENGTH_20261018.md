# Stock bug: a Lua `Send` string longer than 127 bytes crashes every receiver

Date: 2026-10-18. Branch: `agent/lua-send-string-length-unsigned`.
Evidence: static analysis of the exact GOG image, plus the receiver crash at exe+0x430A0E (VA `0x00830A0E`) hit by the Campaign Reimagined co-op work. CR works around it by chunking strings to 127 bytes (`agent/misn17-coop`, commit `661497b3`).

**Status: patch implemented and unit-tested; live two-client validation pending (see the end).**

## Wire format

The Lua network packet codec stores a string's length (or a table's entry count) in the low five bits of the argument's type byte. Values 0..30 are the length itself; 31 means "one extension byte follows" and the length is that byte. `Docs/MP_LUA_REPLICATION_QUALIFICATION.md` (transport findings 5 and 6) records the static analysis.

## Mechanism (GOG Redux 2.2.301, SHA-256 `8d71f56c...3377413`)

| Address | Function | Stock bytes | Defect |
| --- | --- | --- | --- |
| `0x005059CE` | string decoder `FUN_005059B0` | `0F BE 11` `movsx edx, byte [ecx]` | the extension byte is sign-extended: 128..255 become -128..-1, and the negative length reaches `lua_pushlstring`, which faults at `0x00830A0E` |
| `0x00505B70` | table decoder `FUN_00505B50` | `0F BE 11` | same sign extension: the entry loop count goes negative and the cursor desyncs |
| `0x00505944` | string encoder `FUN_005058D0` | buffer-room check, `[ebp-4]` = length | writes only the low byte of the length, so 256+ wraps |
| `0x00505A7A` | table encoder `FUN_00505A10` | buffer-room check, `[ebp-4]` = count | same wrap for 256+ entries |

Each of the four byte sequences was verified unique in the whole GOG image on 2026-10-18.

## The fix

`[Fixes] LuaSendLengthUnsigned` (default on; `OPENSHIM_DISABLE_LUA_SEND_LENGTH_FIX` / `BZR_DISABLE_LUA_SEND_LENGTH_FIX` force it off) makes four writes:

1. **Decoders:** byte 1 of each `movsx edx, byte [ecx]` becomes `B6`, which turns it into `movzx`. A received 128..255 is read as itself. Nothing else in either decoder changes.
2. **Encoders:** the first whole instructions of each buffer-room check (12 bytes for strings, 8 for tables, no relative operands) are replaced by `jmp stub` plus NOP padding. The stub:
   * runs `cmp dword [ebp-4], 0xFF`;
   * on `ja`, jumps to the room check's own `xor al, al` failure exit, so `Send` rolls back the argument and logs it, exactly as it does for an argument that does not fit the packet;
   * otherwise replays the overwritten bytes and jumps back.
   A string of 256 bytes or more is therefore dropped from the packet instead of arriving truncated or desynchronized.

The byte facts and stub builders live in `include/lua_send_length.h` (engine-free). The installer is `src/patches/lua_send_length.cpp`.

## Fail-closed binding

* All four sites are named `resolves` in `scripts/patches.json`, each with a GOG fallback address:
  * `Lua::UnpackString length extension load`
  * `Lua::UnpackTable count extension load`
  * `Lua::PackString length room check`
  * `Lua::PackTable count room check`
* Before writing, the installer reads each site:
  * The decoders must hold exactly `0F BE 11`.
  * The encoders must hold the full stock room check: 20 bytes for strings, 16 for tables, including the `xor al,al` the stub jumps to.
* Any miss leaves all four sites stock.
* The four writes are applied together. If any write fails, the others are restored and the stubs are freed.

## Compatibility

* **Patched to patched:** strings and tables up to 255 work. Above 255, the encoder drops the argument and logs it.
* **Lengths of 127 or less:** the wire is unchanged in every peer mix.
* **Mixed sessions:** an unpatched receiver still crashes on a 128..255 string sent by a patched peer. The fix is per receiver. Mods that must interoperate with stock or older-OpenShim peers should keep strings at 127 bytes or less (CR's chunking stays correct and harmless).
* **Steam and other builds:** if the signatures do not match, the fix does not install and a `LUASENDLEN` warning is logged.

## Validation

* `tests/lua_send_length_tests.cpp` covers:
  * decoder classification (stock, patched, other);
  * site descriptions: fail offsets land on `32 C0`, replay lengths end on instruction boundaries, the frame offset is `-4`, the maximum is 255;
  * string and table stub bytes checked against hand-computed rel32 values for the GOG addresses;
  * detour encoding, including a negative displacement, and stub size limits.
* `patch_registration_tests` checks the four resolve names against `scripts/patches.json`.
* CTest (Win32 Release): 111 of 111 pass. `scripts/run_ini_tests.ps1` passes, with `Fixes/LuaSendLengthUnsigned` in the default-on allowlist.
* `lua_send_length.cpp` compiles warning-free in the Win32 Release build.
* **Not yet done:** a live two-client co-op run sending a 200-byte string (expected: arrives intact on a patched receiver) and a 300-byte string (expected: dropped through the stock argument-does-not-fit rollback and log on the sender). Until then, treat the runtime behaviour as statically derived.
