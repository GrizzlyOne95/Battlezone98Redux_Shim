<!-- Reviewer worksheet from the 2026-09-25 repository audit. Line numbers refer to commit 17e40c0f (main before the audit branch); bzr_hooks.cpp line numbers shift by up to ~530 lines after the dead-code removal in the same PR. See Docs/CODE_AUDIT_20260925.md for the consolidated, prioritized view. -->

# bzr_hooks.cpp lines 22000-33000

Scope: `src/patches/bzr_hooks.cpp` lines 22000-33000 (read end to end in ~400-line
chunks), with `include/bzr_hooks.h`, `include/bzr_object_layout.h`, and the out-of-range
helpers each function in the range calls (`InstallInlineDetour32` 34274, `EnvFlagEnabled`
33757, `ResolveOgreProcRaw` 3229, the install call sites in `ResolveBzrHooks` 34446 /
`RetryDeferredRuntimeHooks` 36017 / the sim-tick hook ~40415, the feature-gate refreshers
at 16342-16358). Line numbers are 1-based against the current file.

## Summary

The range is a mostly well-guarded set of GOG-2.2.301 feature hooks: nearly every
installer verifies prologue bytes or the live vtable slot before writing, hooks fail closed
on mismatch, and engine reads sit behind POD-only SEH leaves. The three issues that matter
most are: (1) the opt-in MPAUTH instrumentation installs 5-byte inline detours after
verifying only 3 prologue bytes, and one site's own expected 4th byte (`0x83`) proves the
5-byte steal splits a 3-byte `sub esp,imm8` (trampoline executes garbage when tracing is
on); (2) three hot AI hooks call `GetEnvironmentVariableA` (via `EnvFlagEnabled`) on every
`DoSubTask` of every AI process every sim tick, and the jet-flame selector calls
`GetModuleHandleA` per craft per frame; (3) several functions mix `__try` with checked STL
iterators/range-for, which violates the file's own stated C2712 rule and breaks Debug
builds. There is also a shipped-but-placeholder "legacy 1.4 AI" branch that unconditionally
pins fleeing AI in state 9, a proximity-mine team-filter path that "detonates" without
spawning ordnance, and a cluster of raw engine addresses declared inline in feature code
instead of `scripts/patches.json` named resolves.

## Findings

### [High][Med] MPAUTH inline detours steal 5 bytes after verifying 3; ordinary-reader site provably splits an instruction — src/patches/bzr_hooks.cpp:26449-26455
```cpp
static const uint8_t kExpectedOrdinary[4] = { 0x55, 0x8B, 0xEC, 0x83 };
// First bytes are push ebp; mov ebp,esp; sub esp, ? — check at least 55 8B EC
if (ExpectedBytesMatchAt(kGogOrdinaryStateReaderAddr, kExpectedOrdinary, 3))
{
    if (InstallInlineDetour32(g_OrdinaryStateReaderDetour, kGogOrdinaryStateReaderAddr,
        reinterpret_cast<void*>(MpauthOrdinaryStateReaderHook), 5, kExpectedOrdinary, 3))
```
`InstallInlineDetour32` (34274) copies exactly `patchLen` bytes into the trampoline and appends
`jmp target+patchLen`; it has no length disassembler. After `55 8B EC` (3 bytes) every
`0x83 /r ib` form (`sub esp,imm8`, `and esp,imm8`, ...) is 3 bytes, so a 5-byte steal ends
one byte into it: the trampoline becomes `push ebp; mov ebp,esp; sub esp,0xE9; <rel32 as
code>` and the resume address `target+5` lands on the immediate byte. The same pattern is used
at 26338 (`kExpectedDwSim[3]`, len 5), 26356, 26374 (`GameObject::Remove`, len 5 — this one
fires for every object removal), 26392, 26430, 26470: all steal 5 bytes but verify only the
3-byte prologue, so whether the split happens depends on unverified bytes. The
`Ordnance_Receive` site (26414) is the only one whose declared length (6) is consistent with
its declared 4th byte. Opt-in (`[Diagnostics] TraceMpauth*`), which is why this is High rather
than Critical.
Fix: make every `kExpected*` array cover the full stolen length (as `InstallAttackTaskKiteHookIfPossible`,
`InstallScavengerRetargetHookIfPossible`, `InstallConstructorRemoteBuildFixIfPossible` do),
choose `patchLen` on an instruction boundary from the disassembly, and pass `expectedLen ==
patchLen`. Verifiable on Windows only (needs the executable); a Linux host test could at least
assert `expectedLen == patchLen` for every detour table entry if the tables were data.

### [Medium][High] `__try` mixed with checked STL iterators (C2712 in Debug) in four functions — src/patches/bzr_hooks.cpp:22871, 26070, 26192, 26251, 31388
```cpp
const auto tuningIt = g_AiUnitTuningOverridesByObject.find(          // 22871
...
    __try                                                              // 22911, 22931
```
```cpp
__try { ... for (auto &kv : g_MpauthSplHitCounts) ... }               // 26070
__try { auto it = g_MpauthRecentDwRemovedIds.find(dwId); ... }         // 26192, 26251
for (auto& pair : g_MultiplayerFlagRenderSets) { ... __try { ... } }   // 31388-31396
```
The file's own convention (comment at 22675: "Keep all checked STL iterators/RAII in the
caller so Debug builds do not hit C2712"; again at 23261 and 31768) is that a function
holding a `_ITERATOR_DEBUG_LEVEL` iterator (which has a destructor in Debug) must not contain
`__try`. `AttackTaskDoStateTuningHook` was written that way, then the legacy-AI D3/D4
blocks added two `__try` blocks beside `tuningIt`. CI builds only `--config Release`
(`.github/workflows/*.yml`), so this is a latent Debug-only compile break, not a runtime bug.
Fix: move each `__try` into a POD-only static leaf (e.g. `TryReadCraftDamageAfterTaskStart`,
`MpauthSenderSeen(uint16_t)`, `HideBillboardSafe(fn, billboard)`), the pattern already used
everywhere else in the range. Verifiable on Windows only (MSVC diagnostic).

### [Medium][High] Per-tick `GetEnvironmentVariableA` in the AI DoSubTask path — src/patches/bzr_hooks.cpp:24048, 24126-24130, 24206
```cpp
if (EnvFlagEnabled("OPENSHIM_TRACE_AI_RANGE"))            // ApplyRetargetPeriodAfterDoSubTask, every call
...
static bool ShouldTraceAttackReveal()
{   return EnvFlagEnabled("OPENSHIM_TRACE_ATTACK_REVEAL") || EnvFlagEnabled("BZR_TRACE_ATTACK_REVEAL"); }
...
TraceAttackRevealEvent("noop", "already_revealed", ...);  // reached on every call once revealed
```
`EnvFlagEnabled` (33757) is an uncached `GetEnvironmentVariableA`. `OffensiveProcessDoSubTaskHook`
/ `GunTowerProcessDoSubTaskHook` / `TurretTankProcessDoSubTaskHook` are installed into 12
process vtables and run for every AI unit every sim tick; each call goes through
`RevealProcessOwnerPerceivedTeam` (which always ends in a `TraceAttackRevealEvent` → two env
lookups while `AttackRevealPerceivedTeam` is active, the default) and
`ApplyRetargetPeriodAfterDoSubTask` (one env lookup unconditionally). That is ~3 CRT/Win32
environment scans per AI unit per tick in a default configuration. `CalcRangeCraftHook`
(23842) and `ShouldTraceScrapPathing` (23228, three lookups) have the same shape but run
less often.
Fix: cache once, as `ShouldTraceJetFlames` (27695) and `ShouldTraceArtilleryMask` (27855)
already do with a `static int s_cached`, or hoist into the feature's `Initialize*Config`.
Verifiable on Windows (profiling); the refactor itself is trivially reviewable.

### [Medium][High] `GetModuleHandleA` per craft per rendered frame in the jet-flame selector — src/patches/bzr_hooks.cpp:27364-27366, 27413
```cpp
HMODULE exuModule = GetModuleHandleA("exu.dll");
if (!exuModule)
    exuModule = GetModuleHandleA("ExtraUtilities.dll");
```
`SelectEngineFlameManager` (27726) is called from `EngineFlameHoverCraftEmitHook` (39322) for
every hovering craft on every frame, and it calls `ResolveTeamEngineFlameColor` →
`ResolveExuTeamEngineFlameColor` → one or two `GetModuleHandleA` calls (loader lock + module
list walk) before any cached pointer is consulted. When EXU is absent (stock or CR-less
play) it is always two calls. The same function then re-derives the ODF name a second time:
`TryGetCraftFactionChar` (27753) already produced `faction`, but `ResolveFactionEngineFlameColor`
(27764) calls `TryGetCraftOdfName` again (second SEH frame + virtual call).
Fix: resolve the EXU export once per mission/`ResolveBzrHooks` (or re-probe on a 1-2 s tick),
and switch on the already-computed `faction` instead of calling `ResolveFactionEngineFlameColor`.
Windows-only to measure.

### [Medium][Med] Legacy-1.4 AI branch ships a placeholder that pins fleeing units in state 9 — src/patches/bzr_hooks.cpp:22931-22951
```cpp
// Use placeholder: suppress always for legacy 9->10 unless stuck
suppress = true;
// TODO: refine with actual distance/IsStuck check
```
When an ODF sets `aiName=tanklegacy*` or `legacyAI=1`, `AttackTaskDoStateTuningHook` rewrites
every stock 9→10 (flee→blast) transition back to 9 unconditionally, so a legacy craft that
entered flee never leaves it via the stock timeout. The `__try` block around it reads nothing
(`taskStart` at 22935 is assigned and unused), D2 is a TODO comment, and `IsBuildingStub`
(22850) is an unreferenced stub. This is experimental logic in a default-off ODF feature, but
it is reachable from shipped content. Fix: either finish D2/D3 (distance + IsStuck read) or
gate the legacy branch behind an explicit `[Experimental]` flag and log once that it is a
partial port; delete `IsBuildingStub`. Windows-only to validate behaviour.

### [Medium][Med] Team-filtered proximity mine "detonates" by flagging removal without spawning its ordnance — src/patches/bzr_hooks.cpp:32887-32900
```cpp
// Spawn explosion ordnance, set removed flags etc.
// For simplicity and correctness, we might want to jump back into
// the original Simulate if we detect a detonation condition, ...
*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(mineObj) + 0x14) |= 0x280;
```
`RunProximityMineFilteredSimulate` replaces `ProximityMine::Simulate` entirely when an ODF
`teamFilter` is not `all`, and on trigger only sets the removed flags; the comment itself
says stock also spawns the explosion ordnance. So a filtered mine silently vanishes instead of
exploding. The magnet-mine twin (32657) has a related gap: `if (!mineClass) return;` (32679)
skips the base `Mine::Simulate` call so such a mine never expires. Fix: on detonation, call the
original `g_BzrFn_ProximityMineSimulateOriginal` with the arming timer forced to its trigger
state (or reproduce the ordnance spawn), and route the `!mineClass` case to `g_BzrFn_MineSimulate`.
Windows-only.

### [Medium][High] Raw engine addresses declared inline in feature code instead of `scripts/patches.json` — src/patches/bzr_hooks.cpp:24234-24235, 24821-24823, 32135, 32182-32187
```cpp
constexpr uint32_t kHowitzerPrimaryVtable = 0x0087AD70;   // inside SuppressUndeployedHowitzerSniperRetaliation
constexpr uintptr_t kBzrNetLoggerAddr = 0x007D6A70;       // BZRNet route observer
constexpr uintptr_t kTextEntryAppendCharAddr = 0x007CFA70; // nickname input hook, function-local
constexpr uintptr_t kMultiCreateUpdateVtblSlotAddr = 0x0089EC14; // map preview fix (+5 more)
```
Project rule (AGENTS.md): build-specific sites live in `scripts/patches.json` / named resolves,
not scattered through feature code. These four features (howitzer vtables, BZRNet logger +
two call sites, TextEntry AppendChar, multi-create update slot + 5 UI addresses) declare
their addresses at point of use, so the build-identity audit cannot see them. The
`MultiRenderCountClampHook` asm also hardcodes `cmp eax, 256` (25059) next to a comment naming
`kMultiRenderCountMax` (836), which will silently diverge if the constant changes. Fix: move
them to the constants block / `patches.json` named resolves (as `"CalcRange(Craft)"` already
is) and have the asm read the constant via a static. Linux-verifiable by the existing
patches.json schema tests if the entries are added.

### [Low][High] Chunk create hooks install without byte verification on GOG and on the unsafe-Steam path — src/patches/bzr_hooks.cpp:22506-22530
```cpp
InstallInlineDetour32(g_ChunkEffectCreateChunkDetour, kGogChunkEffectCreateChunkAddr,
                      reinterpret_cast<void*>(ChunkEffectCreateChunkHook),
                      kChunkEffectCreateChunkDetourLen, nullptr, 0);
```
`kExpectedCreateChunkBytes` / `kExpectedCreateChunkletBytes` exist (22445-22454) but are only
consulted on the Steam wait path; the actual install passes `nullptr, 0`, so on GOG (and on
Steam with `g_AllowUnsafeSteamChunkCreateHooks`) the 16-byte steal is written unverified.
Diagnostic-only (`TraceChunkRender`/`TraceChunkEffectRuntime`). Fix: pass the expected
arrays to both `InstallInlineDetour32` calls. Windows-only.

### [Low][High] Scrap-score installer dereferences the GOG call site and publishes GOG helper pointers before verifying anything — src/patches/bzr_hooks.cpp:23561-23590
```cpp
g_BzrFn_FindPlanForObject = reinterpret_cast<FnFindPlanForObject>(kGogFindPlanForObjectAddr);
...
auto* callBytes = reinterpret_cast<uint8_t*>(kGogRecycleTaskScrapDistanceCallAddr);
if (callBytes[0] == 0xE8)
```
The raw read is outside SEH and before `ExpectedBytesMatchAt`; `g_BzrFn_FindPlanForObject`,
`g_BzrFn_AiPathGetLength`, `g_BzrFn_AiPathDelete`, `g_BzrFn_GetGameTime` keep their GOG values
even when the byte check fails. Today every consumer sits behind a verified hook
(`ScrapCandidateScoreCallsiteHook`, the DoGotoScrap detour, the RTTI-checked DoSubTask vtable
hooks), so this is not a live fail-open, but the same "assign first, verify later" shape at
24428-24458 / 24509-24534 (`InstallShieldTowerTeamFilterHookIfPossible`,
`InstallMineTeamFilterHooksIfPossible`) means any future caller of those `g_BzrFn_*` outside a
verified hook would call a GOG address on a foreign build. Fix: use `RedirectCallTarget`
(24766, which reads via `ReadProcessMemory`) for the probe and assign the helper pointers only
after the byte checks pass. Windows-only.

### [Low][High] Per-frame filesystem retry when flag resource creation fails — src/patches/bzr_hooks.cpp:31124-31148
```cpp
if (renderSet.resourcesReady) return true;
...
std::filesystem::create_directories(renderSet.resourceDirectory, ec);
if (ec) return false;
```
`RenderMultiplayerFlags` calls `EnsureMultiplayerFlagResourceFiles` per eligible object per
frame; on any persistent failure (unwritable generated-flags dir, Ogre resource-group throw)
`resourcesReady` stays false and every frame re-runs `create_directories`, two `exists`
probes, five `ResolveOgreProc` lookups (each a `GetModuleHandleA` + mutex + `std::string`
allocation of a mangled name, 3229) and the Ogre calls. Fix: add a `resourcesFailedUntilTick`
backoff on `MultiplayerFlagRenderSet`, and hoist the per-frame `ResolveOgreProc` calls in
`RenderMultiplayerFlags` (31836-31841) and `HideUnusedMultiplayerFlagBillboards` (31384) into
function-local statics, as `RefreshVehicleSkinningDiagnosticsIfNeeded` (30778) already does.
Windows-only.

### [Low][Med] VDF/SDF parsers can wrap `size_t` on 32-bit with a corrupt block size — src/patches/bzr_hooks.cpp:28784, 28887
```cpp
if (blockSize < 8 || cursor + blockSize > bytes.size())   // blockSize is uint32 from the file
...
if (bytes.size() < cursor + (static_cast<size_t>(geoCount) * kVgeoRecordBytes))
```
On the 32-bit build `cursor + blockSize` and `geoCount * 100` can overflow and pass the bound,
after which `memcmp`/record reads run past the buffer (SDF loop can also cycle). Input is
`Edit/stock/*.vdf|sdf` and mod payload dirs, so corrupt or hostile mod files are the trigger.
Fix: compare `blockSize > bytes.size() - cursor` and `geoCount > (bytes.size() - cursor) /
kVgeoRecordBytes`. Linux-verifiable if the parsers are lifted into a host-testable unit (they
are pure `std::vector<uint8_t>` code).

### [Low][Med] Steam engine-flame vtable patch captures whatever is in the slot as "original" — src/patches/bzr_hooks.cpp:27284-27305
```cpp
auto** vtable = *reinterpret_cast<void***>(manager);
...
g_BzrFn_EngineFlameControl = reinterpret_cast<FnEngineFlameControl>(vtable[controlIndex]);
```
No SEH around the vtable read and no expected-original check before `WritePointerValue`; if
another hook already owns the slot, this chains blindly. Fix: compare against a resolved
expected original (or at least require the slot to lie inside the main module's .text) before
writing, matching the GOG installers' `current != expected → return` shape. Windows-only.

## Dead or unused code (list with evidence)

- `IsBuildingStub` (22850) — zero references in `src/`, `include/`, `tests/`
  (`grep -rn IsBuildingStub` returns only the definition). Delete.
- Legacy-AI D3 `__try` block (22931-22943): reads nothing; `taskStart` assigned and unused;
  the block is dead scaffolding around `suppress = true` (see finding above).
- `MpauthOrdinaryStateReaderHook` 26216-26219: empty `else if (ShouldTraceMpauthDw() && g_MpauthDwTraceBudget > 0) { }` branch.
- `RunMagnetMineFilteredSimulate` 32683-32687: empty `if (sound handle == 0) { /* could be added */ }` block.
- Every non-static hook in the range (`AttackTaskDoStateTuningHook`, `CalcRangeCraftHook`,
  `GunTowerProcessDoSubTaskHook`, `TurretTankProcessDoSubTaskHook`, the eight `Mpauth*Hook`s,
  the three `*SimulateTeamFilterHook`s, `SprayBuildingSimulateUndeadFixHook`,
  `AIUnitRemoveConstructorCleanupHook`) is referenced only from this file's installers and is
  not declared in `include/bzr_hooks.h`; they should be `static` (or moved with their
  installers) when the file is split.
- Duplicated helpers that should be shared: `IsIniBoolTrue` (29480) and `TryParseBoolValue`
  (29768) implement the same normalise-and-compare; `TryReadProducerBuildMenuEntryFromOdfFile`
  (32914-32948) re-implements `TryResolveOdfFilePath` (29874) inline; `MpauthReadDwIdentity`
  duplicates its own body for the two base candidates; the three MPAUTH "budget decrement /
  else re-increment" blocks repeat eight times.

## Performance notes

- Hot per-tick path (default config): `OffensiveProcessDoSubTaskHook` →
  `RevealProcessOwnerPerceivedTeam` → `TraceAttackRevealEvent` (2× `GetEnvironmentVariableA`)
  + `ApplyRetargetPeriodAfterDoSubTask` (1× `GetEnvironmentVariableA`, plus
  `TryGetAiTuningForObject` → `TryGetObjectOdfToken` (SEH + virtual call + tolower) + string
  map lookup when `AiOdfGameplayTuning` is on). See finding.
- `AttackTaskDoStateTuningHook`: `IsLegacyAiCraft` (22818) does the same ODF walk + map lookup
  per AI attack task per tick before the per-unit map is even consulted; consider caching the
  legacy bit on the `AiUnitTuningOverride` / a per-craft flag.
- Jet flames: `GetModuleHandleA` ×1-2 + two ODF walks per craft per frame (finding).
- MP flag renderer: per frame walks the 4096-slot arena, does a terrain raycast
  (`HasTerrainLineOfSight`) per eligible object in range, and resolves four Ogre exports
  through the string-keyed cache each frame; `TryCopyMultiplayerFlagPayload` ×15 per frame.
  Acceptable only because it is gated on `ShouldEnableMultiplayerFlagUi()`.
- `RefreshChunkObjectIdentityCacheIfNeeded` (30614): every 1 s clears and rebuilds up to 1024
  object trees with `std::vector`/`unordered_set` allocations per object; gated on chunk
  proxy/trace flags, fine as is but should stay off the default path.
- `MpauthGoRemoveHook` runs two SEH probes on every `GameObject::Remove` even when its trace
  budget is exhausted; gate on `ShouldTraceMpauthDw()` first.
- Good: `TryGetAiTuningForObject`, `TryGetTeamFilterForObject`, the chunk payload `exists`
  caches and `ResolveOgreProcRaw` all memoise; trace logging everywhere is budgeted with
  `InterlockedDecrement`.

## Positive notes (things done well that later work should keep doing)

- Fail-closed installers: `ExpectedBytesMatchAt` / vtable-slot-equals-original /
  `VtableTypeNameMatches` before every write, and `RedirectCallTarget` (24766) verifying the
  current rel32 target equals the stock callee before redirecting — the briefing-scroll,
  quake-fade, target-cam, cinematic-zoom, BZRNet-route and scrap-score sites all use it.
- Idempotent re-install: every installer recognises its own hook already in the slot and
  returns success, so `RetryDeferredRuntimeHooks` is safe to call repeatedly.
- POD-only SEH leaves (`TryReadAttackTaskEndpoints`, `TryProbeScrapPath`,
  `InitialiseMultiplayerFlagResourceGroupSafe`, `DumpMultiplayerFlagCopyFailureDiagnostics`)
  with explicit comments naming the C2712 constraint — keep this discipline (see finding 2).
- The global feature registry (22279-22367) with `revertToBaseline` / `refreshMpGate` and
  `TickMpGateReconcile` gives every SinglePlayer-tier feature a single net-id gate, and the
  comment explains why the gate does not touch .text before `SatelliteWorldIsLive()`.
- Naked stubs are minimal and documented (`ThumbnailMaterialGuardEntry`,
  `ScrapCandidateScoreCallsiteHook`, `MultiRenderCountClampHook` with stolen bytes listed).
- Calling-convention annotations in the range are consistent with how they are installed:
  `__fastcall(this, edx, ...)` for `__thiscall` entry detours and vtable slots
  (`AttackTaskDoStateTuningHook`, `EarthQuakeSimulateReplayFadeHook`,
  `TextEntryAppendCharNicknameHook`, `MultiCreateUpdateHook`, `RigProcessCleanUState2FixHook`),
  `__cdecl` for stack-argument entry detours whose prologue loads `[ebp+8]`
  (`CalcRangeCraftHook`, `ScriptCanBuildProducerHook`, `AIUnitRemoveConstructorCleanupHook`)
  and for the rel32-redirected `__cdecl` logger/predicate calls. No mismatches found.
- Object-layout offsets that matter (`perceivedTeam`, owner/target handles) are taken from
  `bzr_object_layout.h` with instruction-level provenance, and the 2026-08-17 / 09-19 defects
  are documented at the point of use (24186-24200).

## Section map (for the split)

| Start | End | Feature / hook group | ~Lines | openshim.ini keys / patch names / flags | Status |
|---|---|---|---|---|---|
| 21969 | 22094 | BZRNet nickname authoritative apply (tail; fn starts 21969) | 125 | `[Network] Nickname`, `OpenShimSetBZRNetNickname` bridge | active |
| 22096 | 22277 | BZRNet route preference / UDP port config | 180 | `[Network] RoutePreference`, `UdpPort`, `Nickname` | active |
| 22279 | 22438 | Global feature registry + `TickMpGateReconcile` | 160 | all `[Display]`/`[SinglePlayer]`/`[Fixes]` tiers | active (cross-cutting) |
| 22440 | 22620 | Chunk effect create / fragment-walk diagnostic detours | 180 | `[Diagnostics] TraceChunkRender`, `TraceChunkEffectRuntime` | diagnostic |
| 22622 | 23219 | AI attack-task kite + legacy-1.4 tuning (`AttackTaskDoStateTuningHook`) | 600 | EXU `SetAiUnitTuningFromBridge`; ODF `legacyAI`/`aiName=tanklegacy*`; env `OPENSHIM_TRACE_AI_KITE/RANGE/LEGACY_AI` | active (kite) / experimental (legacy) |
| 23221 | 23630 | Scavenger path-scored scrap selection (naked call-site thunk) | 410 | `[SinglePlayer] AiOdfGameplayTuning`, `g_SmartScavengerPathingEnabled`; ODF `scrap*AI` | active |
| 23632 | 23825 | Scavenger en-route retarget (`RecycleTask::DoGotoScrap` detour) | 195 | same | active |
| 23827 | 24036 | `CalcRangeCraftHook` — AI ODF range policy | 210 | patch name `"CalcRange(Craft)"`; `AiOdfGameplayTuning`, `BomberAiRange`; ODF `engageRangeAI`, `weaponRangeMinAI` | active |
| 24038 | 24124 | Retarget period after DoSubTask | 90 | ODF `retargetPeriodAI`; `kGlobalRetargetPeriod` | active |
| 24126 | 24217 | Attack-reveal perceived team | 90 | `[SinglePlayer] AttackRevealPerceivedTeam`; env `OPENSHIM_TRACE_ATTACK_REVEAL` | active |
| 24219 | 24361 | Howitzer undeployed-retaliation fix + Offensive/GunTower/TurretTank DoSubTask hooks | 145 | `[Fixes] HowitzerUndeployedRetaliation` | active |
| 24363 | 24613 | ShieldTower / MagnetMine / ProximityMine team-filter hook entries + installers, magnet zero-range guard | 250 | ODF `teamFilter`/`affectAllies`/`affectEnemies`; env `OPENSHIM_DISABLE_MAGNET_ZERO_RANGE_FIX` | active |
| 24615 | 24764 | ScriptUtils CanBuild/IsBusy PROD support | 150 | `g_ProducerScriptPredicateHooksEnabled` | active |
| 24766 | 24823 | `RedirectCallTarget` shared helper | 60 | (utility) | active |
| 24825 | 24994 | BZRNet peer route observer (logger call-site redirects) | 170 | `[Network]` sidebar caption | active |
| 24996 | 25027 | Briefing/archive scroll fix | 30 | env `OPENSHIM_DISABLE_BRIEFING_SCROLL_FIX` | active |
| 25029 | 25120 | draw_multi renderCount clamp (#65, naked) | 90 | `g_MultiRenderCountClampEnabled` | active |
| 25122 | 25392 | Thumbnail BMP decode guard (naked entry, C++-exception-only filter) | 270 | `g_ThumbnailBmpGuardEnabled` | active |
| 25394 | 25545 | Post-load quake replay fade (#57) | 150 | env `OPENSHIM_DISABLE_QUAKE_FADE`, `OPENSHIM_QUAKE_FADE_SECONDS` | active |
| 25547 | 25607 | Stale target-cam overlay fix (#56/#78) | 60 | env `OPENSHIM_DISABLE_TARGETCAM_FIX` | active |
| 25609 | 25698 | Cinematic-from-satellite zoom fix (#58) | 90 | env `OPENSHIM_DISABLE_CINECAM_FIX` | active |
| 25700 | 25817 | Splinter (spraybomb) undead fix (#46) | 120 | `[Fixes] SplinterUndead` | active |
| 25819 | 26484 | MPAUTH receiver-replay instrumentation (8 detours, `InstallMpauthHooksIfPossible` 26331) | 665 | `[Diagnostics] TraceMpauth`, `TraceMpauthDw`, `TraceMpauthSpl`; env `*_TRACE_MPAUTH*` | diagnostic / experimental |
| 26490 | 26542 | Tug cargo PostLoad deploy fix hook | 55 | `[Fixes] TugCargoPostLoad` | active |
| 26544 | 26727 | Constructor recycle stale-target undeploy fix (`RigProcessCleanUState2FixHook`) + installer; Tug installer (26683) | 185 | `[Fixes] ConstructorRecycleStaleTarget`, `TugCargoPostLoad` | active |
| 26729 | 26814 | APC allied-target deploy branch patch + MP gate | 85 | `[Fixes] ApcAlliedTargetDeploy` | active |
| 26816 | 26999 | `InstallAiTuningHooksIfPossible` (CalcRange detour + 12 RTTI-checked DoSubTask vtable hooks) | 185 | `"CalcRange(Craft)"` named resolve | active |
| 27001 | 27277 | Constructor remote-build death cleanup (`AI_UnitRemove` detour) | 275 | `[Fixes] ConstructorRemoteBuild`; env `OPENSHIM_TRACE_CONSTRUCTOR_REMOTE_BUILD` | active |
| 27279 | 27853 | Engine flame (jet flames) variant managers + EXU colour bridge | 575 | `[Display] JetFlames`; env `OPENSHIM_FACTION_JET_FLAMES`, `OPENSHIM_TRACE_JET_FLAMES`; EXU `EXU_GetTeamEngineFlameColor` | active |
| 27855 | 27932 | Artillery-mask trace flag + vehicle-asset debug-exception cache helpers | 80 | env `OPENSHIM_TRACE_ARTILLERY_MASK`; used by 33371+ | active |
| 27934 | 29478 | Chunk payload mesh resolution, VDF/SDF geo tables, geo manifest, reverse index, tree inference | 1545 | `g_EnableChunkMeshProxy` (35059), chunk trace flags, `kChunkGeoManifestFileName` | active when chunk assets present |
| 29480 | 29743 | Producer build-menu ini parsing (`IsIniBoolTrue`, token packing, kind classification, overrides) | 265 | `kProducerBuildMenuIniName` `[…]` `Recycler/Factory/Armory/ConstructionRig/Fallback` | active |
| 29745 | 30264 | ODF parsing helpers + AI tuning ODF reader + `TryGetAiTuningForObject` | 520 | ODF `*AI` keys, `aiName`, `weaponNameN`, `ordName`/`shotSpeed`/`lifeSpan` | active |
| 30266 | 30420 | Team-filter ODF reader | 155 | ODF `teamFilter`, `affectAllies`, `affectEnemies` | active |
| 30422 | 30651 | GameObject/obj76 link helpers + chunk object identity cache refresh | 230 | chunk proxy/trace flags | active-conditional |
| 30653 | 30972 | Vehicle skinning diagnostics (Ogre entity probe) | 320 | `g_VehicleSkinningTraceEnabled` | diagnostic |
| 30974 | 31005 | World-position helpers | 30 | (utility) | active |
| 31007 | 32070 | Multiplayer vehicle flags Ogre renderer + one-shot diagnostics + Submit vtable hook / sim-tick fallback | 1065 | `ShouldEnableMultiplayerFlagUi()`, `[Display] MultiplayerFlagShowOwnCraft`, env `OPENSHIM_MP_FLAG_SHOW_OWN` | active / still instrumented |
| 32072 | 32194 | Lobby nickname `cUI_TextEntry::AppendChar` input routing | 120 | `[Network] Nickname` UI | active |
| 32196 | 32328 | Multiplayer create-screen map-preview overflow fix | 130 | env `OPENSHIM_DISABLE_MAP_PREVIEW_FIX` | active |
| 32330 | 32912 | Shield tower / magnet mine / proximity mine filtered-simulate bodies | 580 | ODF `teamFilter` | active (proximity detonation incomplete) |
| 32914 | 33010 | Producer build-menu ODF root reader (`buildMenuRoot`) | 95 | producer ODF `[ProducerClass] buildMenuRoot` | active |
