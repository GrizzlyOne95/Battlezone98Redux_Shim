<!-- Reviewer worksheet from the 2026-09-25 repository audit. Line numbers refer to commit 17e40c0f (main before the audit branch); bzr_hooks.cpp line numbers shift by up to ~530 lines after the dead-code removal in the same PR. See Docs/CODE_AUDIT_20260925.md for the consolidated, prioritized view. -->

# Hook engine, patcher, resolve table, trampolines

Scope: `src/engine/hook_engine.cpp`, `include/hook_engine.h`, `src/engine/patcher.cpp`, `include/patcher.h`, `include/patches.h`, `src/engine/resolve_table.cpp`, `include/resolve_table.h`, `src/patches/trampolines.cpp`, `include/trampolines.h`, `include/iat_patch.h`, `scripts/patches.json`, `tests/patch_registration_tests.cpp`, `tests/resolve_table_tests.cpp`. All files read end to end. Both host tests were built and run on Linux from a throwaway build directory (`resolve_table_tests: all checks passed`, `patch_registration_tests: 65 patch-list entries cross-checked (22 signature, 54 global), 28 resolves`), which is how the two test-coverage gaps below were confirmed rather than inferred.

## Summary

Overall the engine is in reasonable shape: the resolve table is data-driven, tested off-Windows, fail-closed on ambiguity when `require_unique` is set, and most REL32 sites verify the call target's identity before redirecting. The defects are concentrated in the edges of the patch pipeline rather than the core scan. Top three:

1. The signature-miss **fallback path builds the byte guard from the wrong bytes** (`patcher.cpp:888`): it takes pattern bytes from index 0 instead of `offset`, and turns `??` wildcards into `0x00`. For the two HoverCraft REL32 patches the documented fallback can therefore never apply; a coincidental match would write a redirect over unverified bytes.
2. **Two 52-byte JMP5 writes are guarded by 5 bytes** ("Under Attack Alert Hook 1/2 and 2/2"): `ApplyPatch` verifies `expected_original.size()` bytes and then writes `payload.size()` bytes with no check that the second is not larger than the first.
3. **Malformed `patches.json` terminates the game**: `PatcherConfig::GetStaticPointer` uses `std::stoul`/`get<std::string>()` with no `try`, ~40 call sites have none either, `RunPatcher` has none, and `PatchThreadProc` (`src/plugin/openshim_plugin.cpp:64-90`) has none, so any `nlohmann` `type_error` or `std::invalid_argument` becomes `std::terminate` on the patch thread.

Also material: the registration test scans only two source files for `ResolveNamedAddress` names, so three undefined names in `ui_performance_hooks.cpp` (`ShellRequest`, `ShellTransition`, `ShellBack`) fall back to raw addresses and the test passes; and eleven `globals` entries are walked by nothing.

## Findings

### [Medium][High] Fallback-path expected bytes ignore `offset` and map wildcards to 0x00 — src/engine/patcher.cpp:883-891

```cpp
p.address = t.fallback_addr; p.verified = true;
auto ida = HookEngine::ParseIdaPattern(t.ida_pattern);
if (t.expected_size > 0) { p.expected_original.clear(); for (size_t j = 0; j < t.expected_size && j < ida.size(); ++j) p.expected_original.push_back(static_cast<uint8_t>(ida[j])); }
```

Why wrong: `t.fallback_addr` is the address of `match + offset`, but the guard is built from `ida[0..expected_size)`, i.e. the bytes at `match + 0`. `ParseIdaPattern` encodes a wildcard as `0x100`, which `static_cast<uint8_t>` truncates to `0x00`, so any wildcard in that window becomes a demand for a zero byte. Of the five non-`require_unique` entries that can reach this path, the three Steam Hop-Fix entries have `offset 0` and no wildcards in the first five bytes (works by luck); "HoverCraft Engine Flame Emit Hook 1/2" (`offset 17`) and "2/2" (`offset 13`, wildcards at pattern index 2-3) get guards of `0F 11 04 24` and `8D 95 00 00` compared against the rel32 operand at the fallback address, so the fallback is inoperative and, if the bytes ever coincide, the guard would pass on the wrong site. `ApplyPatch` then writes `payload.size()` bytes.

Fix: build the guard from `ida[t.offset .. t.offset + expected_size)`, and if any byte in that window is a wildcard, leave `expected_original` empty and *do not* mark the patch verified (fallback refused, log `[PATCH-SCAN] ... fallback-unguarded`). Make `ScanTarget::offset` signed to match `ResolveTarget::offset` (see Low finding below). Verifiable on Linux only if the derivation is moved into a Windows-free helper (like `resolve_table.cpp`) and unit-tested; otherwise Windows.

### [Medium][High] 52-byte JMP5 writes are guarded by 5 bytes — src/engine/patcher.cpp:922, src/engine/hook_engine.cpp:65-72, scripts/patches.json ("Under Attack Alert Hook 1/2", "2/2")

```cpp
size_t l = (...) ? 8 : (... "Reveal" ... ? 12 : (... "Volley" ... ? 6 : (p.name.find("Attack Alert") != std::string::npos ? 52 : 5)));
p.payload = HookEngine::MakeJmp5Payload(p.address, ..., l);
```
and in `ApplyPatch`:
```cpp
std::vector<uint8_t> current(patch.expected_original.size());
...
return WriteMemory(patch.address, patch.payload.data(), patch.payload.size());
```

Why wrong: both "Under Attack Alert" globals carry `expected_original = "0F 2F 05 D0 73"` (5 bytes) while the payload written is JMP5 + 47 NOPs (52 bytes; `RetAddr_UnderAttack1_Offset` 0x34). 47 bytes at a fixed GOG address are overwritten with no verification at all, on both distributions (no `platforms` gate). The TurretCraft/TurretTank entries do this correctly (8-byte guard, 8-byte payload), so this is an omission, not a design choice. The general rule is missing from `ApplyPatch`: nothing checks `expected_original.size() >= payload.size()`.

Fix: (a) in `ApplyPatch`, `if (!patch.expected_original.empty() && patch.expected_original.size() < patch.payload.size()) return false;` with a log line; (b) extend the two JSON `expected_original` strings to the full 52 bytes of the replaced block (guard bytes only; the addresses stay as they are). (b) is checked by the existing registration test on Linux; (a) is Windows-only, but the size rule itself is pure and could be unit-tested if `ApplyPatch`'s guard logic were split out.

### [Medium][High] C++ exceptions from JSON accessors escape the patch thread — src/engine/patcher.cpp:54-61, :573, :1136; src/plugin/openshim_plugin.cpp:64-90

```cpp
uint32_t GetStaticPointer(const std::string& name, uint32_t defaultVal = 0) {
    if (data.contains("static_pointers")) {
        for (const auto& p : data["static_pointers"]) {
            if (p["name"] == name) return std::stoul(p["address"].get<std::string>(), nullptr, 16);
```
```cpp
auto pVec = HookEngine::ParseIdaPattern(g_Config.data["audio_gas_pattern"]["pattern"]);
```

Why wrong: `std::stoul` throws `std::invalid_argument`/`std::out_of_range` on a bad hex string; `get<std::string>()` and the implicit conversion at :573 throw `nlohmann::json::type_error` when the value is not a string; `p["name"]` on a `const json` object lacking the key is undefined behaviour in nlohmann (asserts in debug, dereferences `end()` in release). `GetStaticPointer` is called ~40 times (lines 566, 611-612, 710, 725, 747-829, 1159) and none of the callers, `RunPatcher`, or `PatchThreadProc` has a `try`. `ScanForPatchAddresses` and `PatchNameHasJsonEntry` do wrap in `try { } catch (...) { }`, so the intent to be tolerant exists but is inconsistent. A deployed `patches.json` with one bad `static_pointers` entry (the file is hand-deployed per `Docs/AGENT_PATCH_WORKFLOW.md`) therefore kills the game rather than logging and falling back to the in-code default.

Fix: wrap the body of `GetStaticPointer` (and the :573 access) in `try { ... } catch (const std::exception& e) { Log(...); return defaultVal; }`, use `p.contains("name") && p["name"].is_string()` guards, and add a last-resort `try/catch(...)` around the body of `RunPatcher` (or in `PatchThreadProc`) that logs and returns. The `GetStaticPointer` parse logic is Windows-free and could join `resolve_table.cpp` under a Linux test; the thread wrapper is Windows-only.

### [Medium][Med] Non-unique REL32 redirect with no call-target identity check and a silent first-hit scan — src/engine/patcher.cpp:1074, src/engine/hook_engine.cpp:223-228, scripts/patches.json ("HoverCraft Engine Flame Emit Hook 1/2", "2/2")

```cpp
else if (p.name.find("HoverCraft Engine Flame Emit Hook") != std::string::npos) target = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(Trampoline_EngineFlameHoverCraftEmit));
```
and in `ScanForPatterns`:
```cpp
if (!target.require_unique)
    break;
...
if (matchCount > 0 && !target.require_unique)
    break;
```

Why wrong: every other REL32 hook that replaces a call (`Pilot Carrier *`, `Neutral Attack Order`, `AIP Prereq`, `AI Multi Producer`, `Splinter Emitter`, `Sun Screen Flash`) first checks `ResolveRelCallTarget(p.address - 1) == ResolveNamedAddress(<callee>)` and stands down on mismatch. The two HoverCraft sites do not, yet they are the only REL32 entries whose signatures are *not* `require_unique`, and the "2/2" pattern (`8D 95 ?? ?? ?? ?? 52 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? E9 ?? ?? ?? ?? 83 BD ?? ?? ?? ?? 00 0F 8E`) is generic enough to match another `lea/push/mov ecx,imm/call/jmp/cmp/jle` sequence. For a non-unique target `ScanForPatterns` stops at the first hit and logs nothing (the `[PATCH-SCAN]` line is emitted only when `require_unique`), so a wrong first hit is invisible until the trampoline (which reads `[ebp-0x698]`) faults. A resolve for the callee already exists (`EngineFlame::AddFlame`, `prefer: fallback`).

Fix: add the same identity gate: resolve `EngineFlame::AddFlame`, compare with `ResolveRelCallTarget(p.address - 1)`, `continue` on mismatch with a `[FLAME]` log. In `ScanForPatterns`, always count all matches and emit the `[PATCH-SCAN]` line for every target (Info when 1, Warn when >1) instead of only for `require_unique`, mirroring `ResolveNamedAddress`. Consider flipping the two entries to `require_unique: true` after a live `[PATCH-SCAN] matches=1` confirms it. Windows-only to observe; the JSON change is registration-test neutral.

### [Medium][Med] Code bytes are rewritten while game threads execute, with no suspend or atomic write — src/engine/hook_engine.cpp:45-59, src/engine/patcher.cpp:1234-1242

```cpp
if (!VirtualProtect(ptr, len, PAGE_EXECUTE_READWRITE, &oldProtect)) return false;
SIZE_T written = 0;
BOOL ok = WriteProcessMemory(hProc, ptr, data, len, &written);
```

Why it matters: `RunPatcher` runs on `PatchThreadProc` while the main thread is already initialising the shell. `WriteProcessMemory` is a plain kernel memcpy, not an atomic store; a thread whose EIP is at byte 1-4 of a site when the 5-byte `E9` lands executes a torn instruction. Most sites (lobby, ban, multiplayer list) are not live during startup, but the three ODF item detours (`UseItem`/`GetItemSize`/`UnlockItem`) are on the loader path that the comment at `patcher.cpp:900-907` says feeds "the sprite and font tables", i.e. exactly the code the main thread is running during the patch window, and the 52-byte Under Attack writes cover ten-plus instructions. There is no `SuspendThread` pass and no 8-byte interlocked write. This is a probabilistic startup crash, not a determinism bug, which is why it is Medium rather than High.

Fix: for a 5-byte write that does not cross an 8-byte boundary, read the aligned 8-byte window and commit with `InterlockedCompareExchange64` (a single atomic store the CPU serialises correctly for cross-modifying code on x86); for longer writes (the 52-byte NOP sleds) either write only the JMP5 atomically and leave the tail bytes untouched (the trampoline returns past them anyway) or suspend all other threads around the write. Windows-only.

### [Medium][High] Registration test misses six files that call `ResolveNamedAddress`, and the `globals` orphan direction — tests/patch_registration_tests.cpp:262, :234-244; tests/CMakeLists.txt:147-151

```cpp
const std::set<std::string> used = ResolveNamedAddressCallSites({patcher, hooks});
```

Why wrong: `ResolveNamedAddress` is also called from `file_io_hooks.cpp`, `openshim_updater.cpp`, `terrain_tile_blend.cpp`, `pond_class_label.cpp`, `ui_performance_hooks.cpp`, `mp_faction_restrict.cpp`. Verified result: `ui_performance_hooks.cpp:2007-2012` asks for `"ShellRequest"`, `"ShellTransition"`, `"ShellBack"`, none of which exist in `resolves`; each call logs `[RESOLVE] ... has no entry` and the code then uses `0x007C7930`, `0x007C7070`, `0x007C79A0` inline (exactly the raw-address-in-feature-code pattern the project rule forbids, and exactly the silent-fallback failure the test header says it exists to catch). The test passed on Linux with this state. Separately, the orphan check (`:234-244`) walks `jsonPatches` only; eleven `globals` entries are absent from `patches.h` and are therefore never walked and never diagnosed: "Map Filters 1/8" through "8/8", "Version Notice 1/2 OpenShim", "2/2", "3/3".

Fix: have CMake pass a list of all `src/**/*.cpp` (or glob at test runtime from `BZR_SRC_DIR`) and run `ResolveNamedAddressCallSites` over all of them; extend the orphan check to `jsonGlobals`. Then either add the three `Shell*` resolves with identity notes or delete the inline fallbacks. Fully verifiable on Linux (the test will fail until the JSON/code are reconciled).

### [Low][High] `static_pointers` names in JSON do not match the names the code asks for — scripts/patches.json:766-771, src/engine/patcher.cpp:747, :755-756

JSON defines `"HopFix1_Fallback"` and `"HopFix2_Fallback"`; the code reads `"HopFix1Call_Fallback"` and `"HopFix2Select_Fallback"`. The JSON overrides are dead and the in-code constants (`0x005D4260`, `0x007CAFA0`) are what runs. Values coincide today, so no behavioural change, but the override mechanism is broken for the one Steam-only feature that most needs it. Also code-only keys with no JSON entry: `BZR_EXPECTED_VERSION`, `BZR_SIGNATURE_ADDR`, `RetAddr_*_Offset` (all fall through to in-code defaults). Fix: rename the two JSON keys (or the two code strings) and add a `GetStaticPointer("...")` vs `static_pointers` cross-check to the registration test. Linux-verifiable.

### [Low][High] "Splinter Emitter Owner Propagation" carries `pattern`/`require_unique`/`identity` in `globals`, where they are ignored — scripts/patches.json (globals), src/engine/patcher.cpp:871-879

`ScanForPatchAddresses` builds `ScanTarget`s only from `patches`; a `globals` entry is assigned `fallback` directly. So this entry's 49-byte pattern and `require_unique: true` are never evaluated and its address is used blindly on both distributions. Impact is contained because `FillRel32Payloads` (`:1058-1069`) still verifies the call target against the `GameObjectClass::Build` resolve, but the JSON reads as if a scan protects it. Fix: move the entry to `patches` (keeping the same `fallback`, `offset`, `expected_size`) so it is scanned, or strip the unused keys; add a schema check to the registration test that rejects `pattern` inside `globals`. Linux-verifiable.

### [Low][High] `WaitForSignature` result is discarded and `ReadExeSignature` never checks `ReadFile` — src/engine/patcher.cpp:704-732, :1173

```cpp
IMAGE_DOS_HEADER dos; DWORD r; ReadFile(h, &dos, sizeof(dos), &r, nullptr);
IMAGE_NT_HEADERS32 nt; SetFilePointer(h, dos.e_lfanew, nullptr, FILE_BEGIN); ReadFile(h, &nt, sizeof(nt), &r, nullptr);
...
std::vector<uint8_t> sig; if (ReadExeSignature(sig)) WaitForSignature(sig);
```

A short or unreadable file leaves `dos`/`nt` uninitialised and the signature buffer as whatever `ReadFile` produced; and after `PATCH_MAX_RETRIES` (10 s) `WaitForSignature` returns `false` and patching proceeds anyway. The per-patch guards make this fail-safe in practice for `globals`, but for scanned patches the guard is derived from the same live bytes, so nothing independent remains. Fix: check every `ReadFile`/`r` and `e_lfanew` range; log the timeout and, on GOG (no SteamStub), return from `RunPatcher` when the signature never settles. Windows-only.

### [Low][High] `MakeJmp5Payload` has no minimum-length guard and computes `rel` in signed arithmetic — src/engine/hook_engine.cpp:86-93

```cpp
int32_t rel = static_cast<int32_t>(dst) - static_cast<int32_t>(src + 5);
std::vector<uint8_t> buf(total_len, 0x90);
buf[0] = 0xE9;
memcpy(&buf[1], &rel, 4);
```

`total_len < 5` is a heap overflow (both current callers pass >= 5, so latent), and `int32 - int32` overflows (UB) when the DLL and exe straddle 0x80000000, which a `/LARGEADDRESSAWARE` process can do. `FillRel32Payloads:1078` and `FillArtilleryVolleyPayloads:1093` have the same subtraction. Fix: `if (total_len < 5) total_len = 5;` and compute `uint32_t rel = dst - (src + 5);` (unsigned wrap is defined and yields the right encoding). Pure function; could be Linux-tested if lifted out of the Windows TU.

### [Low][Med] `ScanTarget::offset` is `uint32_t` while the JSON field and the resolve table are signed — include/hook_engine.h:30, src/engine/patcher.cpp:868, src/engine/hook_engine.cpp:217-221

```cpp
uint32_t offset;
...
t.offset = p["offset"];
...
for (size_t j = 0; j < target.expected_size && (i + target.offset + j) < read; ++j)
```

A negative JSON offset (legal for `resolves`, and documented as such in `resolve_table.h:51-53`) wraps to ~4 GB here; on 32-bit the pointer arithmetic happens to land in the right place but the bounds test `(i + offset + j) < read` no longer protects the read of `buf`, and no check confirms `region.first + i + offset` is inside the module (the resolve path's `AnchorToAddress` does this correctly). No entry uses a negative offset today. Fix: make it `int32_t`, and reuse `AnchorToAddress`-style bounds checks in `ScanForPatterns`. Windows-only.

### [Low][High] A match near the end of a region yields a truncated guard — src/engine/hook_engine.cpp:219-221

`matchedExpected` stops at `read`, so `expected_original` can be shorter than `expected_size` and `ApplyPatch` then verifies fewer bytes than it writes. Fix: if fewer than `expected_size` bytes are available, treat the hit as not matching. Windows-only.

### [Low][Med] `FindPatchesJsonPath` trusts the current directory before the exe directory — src/engine/hook_engine.cpp:263-283

The DLL that must match `patches.json` lives next to the exe, but the search starts with `scripts/patches.json` relative to the CWD, so a shortcut with a different "Start in", or a launcher that sets the CWD to another install, silently loads another install's addresses. It is also ANSI (`GetModuleFileNameA` + narrow `ifstream`), which fails on install paths outside the ANSI code page and then falls back for every resolve. Fix: exe directory first, CWD second, and log which one won; use the wide API and `std::filesystem::path`. Windows-only.

### [Low][High] `ApplyPatch` ignores `verified` — src/engine/hook_engine.cpp:61-73

The ODF stand-down at `patcher.cpp:913-918` sets `p.verified = false` and relies on the payload still being empty to make `ApplyPatch` fail (via `VirtualProtect` with `len == 0`). Any future path that sets a payload before clearing `verified` would write anyway. Fix: `if (!patch.verified || patch.payload.empty()) return false;`. Windows-only.

### [Low][High] `iat_patch.h` leaves the page unprotected if the store faults — include/iat_patch.h:241-260

```cpp
if (!VirtualProtect(entry, sizeof(void*), PAGE_READWRITE, &oldProtect)) return Result::Faulted;
...
*entry = replacement;
DWORD ignored = 0;
VirtualProtect(entry, sizeof(void*), oldProtect, &ignored);
```

On the fault path the `__except` returns `Faulted` without restoring `oldProtect`; the retry then re-protects, so in practice the page ends up correct, but a permanently failing patch leaves an IAT page writable. `FlushInstructionCache` on a data slot is a no-op. Minor; restore in the handler if `oldProtect` was captured. Windows-only.

### [Low][Med] `resolve_table.cpp` accepts out-of-range `offset` and silently ignores a non-boolean `require_unique` — src/engine/resolve_table.cpp:166, :201-202

`get<int32_t>()` truncates a 64-bit JSON integer without complaint, and `require_unique: "true"` (a string) is dropped rather than rejected, unlike every other field, which appends to `error`. Fix: range-check the offset, and report a non-boolean `require_unique` the same way as `mode`/`prefer`. Linux-verifiable (add cases to `TestBadEntriesAreRejectedIndividually`).

## Raw addresses outside patches.json (project rule)

Grep `0x00[4-9A-F][0-9A-F]{5}\b` over `src/` and `include/`: 1237 literals in 37 files, of which 532 are in code (not comments). Per-file (total / in-code): `src/patches/bzr_hooks.cpp` 771/360; `src/patches/trampolines.cpp` 60/7; `src/patches/mp_ready_diagnostic.cpp` 54/21; `src/patches/bzr_options_ui.cpp` 50/21; `include/bzr_object_layout.h` 45/0; `src/patches/ui_performance_hooks.cpp` 43/37; `src/engine/patcher.cpp` 34/32; `include/sun_flash.h` 28/0; `src/patches/cli_multiparam_parser.cpp` 19/0; `src/patches/ogre_render_profile.cpp` 17/4; `include/weapon_convergence.h` 16/0; `src/patches/terrain_proxy.cpp` 13/13; `src/patches/mp_faction_restrict.cpp` 13/0; `src/patches/net_optimizer.cpp` 11/11; `src/patches/autosave.cpp` 7/5; `include/autosave_gate.h` 7/0; `src/engine/native_ui.cpp` 6/6; `src/patches/game_state.cpp` 6/6; `src/patches/walker_cockpit_trace.cpp` 5/2; `include/bzr_options_ui.h` 5/0; `src/patches/pilot_fp_animation_trace.cpp` 4/2; the remaining 16 files carry 1-3 each (`include/patches.h` 1 = `DEFAULT_BZR_SIGNATURE_ADDR`).

In scope: `patcher.cpp`'s 32 in-code literals are all `GetStaticPointer("Name", 0x...)` defaults, i.e. a second copy of what `static_pointers` already holds (and two of them, per the mismatch finding above, are the *only* copy that runs). `trampolines.cpp`'s 7 in-code literals are `ds:[0x00945564]`, `ds:[0x008A2B08]`, `ds:[0x008A2A5C]`, `ds:[0x008A2AA0]`, `push 0x0089E8C8` inside the dead Map Filters 3/4/5 trampolines, and `mov eax,[0x0091830C]` in `Trampoline_AutoSaveLoadButtonHook` (a replay of the replaced instruction, inherently site-bound). Outside scope but in-scope-adjacent: `ui_performance_hooks.cpp:2008/2010/2012` are the three fallbacks for the undefined `Shell*` resolves. `bzr_hooks.cpp` (360 in code) is the file that most contradicts the rule and should be its own audit item.

## Dead or unused code (list with evidence)

- `Trampoline_VersionNotice` (`src/patches/trampolines.cpp:1018-1035`) and `g_RetAddr_VersionNotice` (`include/patches.h:75`): grep over `src/ include/` finds only the definition and the header; no table or patch references it.
- `Trampoline_Probe_MapFilter1`, `Trampoline_Probe_MapListFix1`, `Trampoline_Probe_MapListFix2`, `Trampoline_MapFilters1/2/3/4/5/7/8`, `Trampoline_OffensiveAttackRevealHook`, `Trampoline_TurretTankAttackRevealHook` (`trampolines.cpp:697-1010`, `:1442-1482`) and `MapFilters6Rel32` (`patcher.cpp:934`): referenced only by the `FillJmp5Payloads` table (`patcher.cpp:895-897`) under names ("Probe Refresh Path MapFilter1", "Probe MapListFix1/2", "Map Filters n/8", "Offensive Attack Reveal Hook", "TurretTank Attack Reveal Hook") that `BuildPatchList` never emits, so `p.name == x.n` can never be true. The attack-reveal pair is intentionally parked (`patches.h:229-233`); the map-filter set is the "disabled clean-room filter/sort port" that `AGENTS.md` says to keep separate. Recommend an explicit `#if OPENSHIM_MAP_FILTER_PORT` (or a comment on the table) so the dead entries are visibly deliberate rather than looking like a registration slip.
- `ResolvePointers` parameters `pF1`, `pL2`, `oa`, `tta` (`patcher.cpp:746`, call at `:1221`) are always 0 because `findAddr` looks up names absent from the list; the four `g_RetAddr_Probe_MapFilter1`, `g_RetAddr_Probe_MapListFix2`, `g_RetAddr_OffensiveAttackRevealHook`, `g_RetAddr_TurretTankAttackRevealHook` are therefore never set. `ResolveStaticReturnPointers` (`:809-817`) populates nine `g_RetAddr_MapFilters*` that only dead trampolines jump through.
- `scripts/patches.json`: 11 orphaned `globals` (listed above) and 9 `static_pointers` (`RetAddr_MapFilters*`) consumed only by dead code; `HopFix1_Fallback`/`HopFix2_Fallback` never read (name mismatch).
- `HookEngine::ParseHexPattern` (`hook_engine.cpp:27-37`, `hook_engine.h:50`): no callers anywhere in `src/ include/ tests/`. It also uses throwing `std::stoul`, unlike `ParseIdaPatternText`.
- `ResolveSoundChannelOverrideTargets(bool isSteam, ...)` (`patcher.cpp:609`): `isSteam` unused. `SoundChannelOverrideTargets::initSiteAddress` (`:171`, written `:601`) is never read.
- `g_Config.Load()` is called twice in `RunPatcher` (`:1137`, `:1181`) with no intervening write to the file.
- `include/trampolines.h` re-declares three `g_RetAddr_HopFix*` that `patches.h` already defines `inline`; `trampolines.cpp` includes both. Harmless duplicate.
- `SafeCapture_MapSorting` (`trampolines.cpp:632-656`) is unreachable in effect: `g_EnableScrollRestore` is forced `false` at `patcher.cpp:794` on every distribution before any patch is applied, so the helper returns at its first line. The comment block at `patcher.cpp:771-793` explains why; the trampoline still pays a `pushad`/call/`popad` per hit.
- Non-trampoline code living in `trampolines.cpp`: the Ogre material-collision listener and the briefing asset override mount (`:62-333`, `:1089-1133`) have nothing to do with hop-fix trampolines. Relocation candidate, not a defect. (Checked: the `OgreDataStreamPtrStub {pRep, pInfo}` layout matches Ogre 1.10's `SharedPtr`, so the by-value return is ABI-consistent; not flagged.)

## Performance notes

- `ScanForPatterns` (`hook_engine.cpp:191-196`) copies every executable region of the exe (`std::vector<uint8_t> buf(region.second)` + `ReadProcessMemory`) once **per target**: 22 targets on the first pass, then up to 10 Steam settle passes over whatever is unresolved. `ResolveNamedAddress` (`:407-411`) does the same once per name (28 names, uncached until success). Hoisting the region read outside the target loop (read once per pass, scan all patterns over the same buffer) removes ~20x redundant multi-megabyte copies at startup. Startup-only, so Low, but it is the dominant cost of the patcher thread and it delays hooks that the retry loop is racing the game to install.
- The inner matcher is the naive O(n*m) byte loop with no first-byte skip; fine given the sizes, but if the hoist above is done, a first-byte `memchr` skip is a free 5-10x.
- `LogHit` at the head of every hop-fix/lobby/ban trampoline costs one cached static read when `OPENSHIM_TRACE_HITS` is unset; acceptable. When tracing is on, note that the C logger may use SSE registers inside `pushfd/pushad`, which do not save XMM state; sites that keep a float live across the patched instruction would misbehave only in trace mode.
- `Trampoline_MapListFixSupport1` runs three tracing calls per mouse-wheel tick (`TraceMapRefreshSiteFrame`, two `TraceManualRefreshSupport`); the latter is budgeted (160), the former's budget lives in `scroll_helper.h` (outside scope).
- `SoundChannelOverrideThreadProc` is a process-lifetime thread doing two `ReadProcessMemory` calls per second; negligible, but it never exits before `g_ShutdownRequested`.
- `PatchAllowsDistribution` is O(patches x JSON entries) string compares (65 x 76); negligible.

## Positive notes (things done well that later work should keep doing)

- The REL32 call-replacement sites (`Pilot Carrier *`, `Neutral Attack Order`, `AIP Prereq *`, `AI Multi Producer *`, `Splinter Emitter`, `Sun Screen Flash`) verify `ResolveRelCallTarget(site-1) == ResolveNamedAddress(callee)` and stand down on mismatch, leaving the stock call in place. This is the right pattern; extend it to the two HoverCraft sites.
- `ResolveNamedAddress` counts every match even when the first is taken, logs `matches=`, `scan=`, `fallback=`, `used=`, `source=`, `agree=`, and echoes the mandatory `identity` note, so a mis-resolve is diagnosable from one log line. `AnchorToAddress` bounds-checks the anchor, verifies the `E8` opcode, and bounds-checks the rel32 target against the module.
- `resolve_table.cpp` is Windows-free, rejects entries individually (one bad entry does not disarm the rest), refuses an entry with no `identity`, and fails a whole pattern on one bad token rather than matching a prefix; `resolve_table_tests.cpp` pins the shipped file to the pre-migration byte arrays.
- `ParseIdaPatternText` returning empty for an unparseable pattern, with callers checking `empty()` before scanning (`patcher.cpp:576`, `hook_engine.cpp:186`), prevents the classic "empty pattern matches the first byte" failure.
- The provisional-miss logic (`missesAreProvisional`) and the stall-bounded Steam settle loop (`patcher.cpp:1204-1218`) avoid both the false `[SIGNATURE]` warnings and a fixed multi-second launch penalty.
- `[STALE-CONFIG]` vs `[SIGNATURE]` are separated by whether a JSON entry exists (`:1251-1277`), which sends readers to the right fix.
- `iat_patch.h` bounds every RVA against `SizeOfImage`, bounds both thunk walks, keeps the `__try` in a scope with no unwindable objects, and turns a loader race into a retryable `Result`; `WaitForModuleLoadToFinish` pins by full path deliberately.
- Every naked trampoline's C helper was checked for calling convention against `bzr_hooks.h`/`scroll_helper.h`: `__cdecl` helpers are cleaned with matching `add esp, N`, the `__fastcall` scroll helpers receive their single argument in `ecx`, and the `ret 4`/`ret 8` on the call-replacement trampolines match the replaced `__thiscall` callee's stack cleanup. The return-address offsets checked against known instruction encodings (HopFix1 0x0E, HopFix2 0x13, HopFix3 0x07, Map Sorting 0x07, TurretCraft 0x08, AutoSave 0x05, Joiner 0x05, Under Attack 0x34) are consistent with the replayed instructions.
- Feature gating removes patches from the list *before* scanning (`ScanForPatterns` checks `targetEligible`), so a disabled feature pays no scan cost.
