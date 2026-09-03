// mp_faction_restrict.cpp — restore a host-style "stock factions only" rule for
// the multiplayer starting-vehicle list.
//
// ============================================================================
// WHAT REDUX DOES, AND WHAT THIS CHANGES
// ============================================================================
//
// Redux 2.2.301 builds the multiplayer starting-vehicle list in one loader,
// FUN_00766900 (`this` = the global list singleton returned by FUN_00764780,
// stored at DAT_0094548C). The loader parses a whitespace-separated pool file
// and, for every entry, classifies it by the FIRST CHARACTER of its ODF name:
//
//     0x00766C93  call 0x766F30            ; -> char* odf name
//     0x00766C98  mov  dl, byte ptr [eax]  ; first character
//     0x00766CB3  sub  ecx, 0x61           ; -= 'a'
//     0x00766CCB  movzx eax, byte [edx + 0x766E50]   ; byte map
//     0x00766CD2  jmp   dword [eax*4 + 0x766E3C]     ; jump table
//        'a' -> 0 NSDF   's' -> 1 CCA   'b' -> 2 Black Dog
//        'c' -> 3 CRA    else -> 4 Other
//
// ...then pushes it into a PER-NATION vector at `this + nation*0x0C`:
//
//     0x00766D60  imul ecx, [ebp-0xA8], 0xC   ; nation * sizeof(vector)
//     0x00766D67  add  ecx, [ebp-0xA4]        ; + this
//     0x00766D6D  call 0x766FC0               ; push_back   <-- UNCONDITIONAL
//
// NOTE for future readers: the `cmp [ecx+0x60], nation / jne` at 0x00766D1C
// reads like a nation filter in Ghidra output. It is NOT. It guards only the
// restoration of the saved selection index; membership is never filtered.
//
// The UI then displays exactly one bucket, `buckets[this->+0x60]`, and
// cUI_Multiplayer_VehicleSelect (FUN_007A9590) ships Faction left/right arrows
// (FUN_007667C0 / FUN_00766860) that cycle `+0x60` across all five buckets,
// skipping empty ones. So every faction present in the pool is already
// selectable by every player, and there is no host control over that.
//
// This module optionally prunes the buckets the host does not want after the
// list is built, which makes the corresponding factions unreachable because the
// faction arrows skip empty buckets on their own. Nothing else is touched.
//
// ============================================================================
// WHY THIS IS A CALL-SITE PATCH AND NOT A TRAMPOLINE
// ============================================================================
//
// FUN_00766900 has exactly two callers in the whole image:
//     0x00798BE1  in cUI_Multiplayer_Create  -> loads "netveh.odf"
//     0x007A3EDF  in FUN_007A3E60            -> loads "<mission>.vxt"
// Both are `mov ecx, eax / call rel32` right after FUN_00764780 returns the
// singleton. Rewriting those two rel32 operands is the narrowest possible
// change: no byte relocation, no trampoline, and it cannot affect any path
// other than multiplayer starting-vehicle list construction.
//
// ============================================================================
// HOST AUTHORITY AND SCOPE — READ BEFORE EXTENDING
// ============================================================================
//
// * The host-provided pool stays authoritative. This code only ever SUBTRACTS
//   from what the pool already produced. It can never add a craft, expose an
//   arbitrary ODF, or reach content the pool did not list.
// * `<mission>.vxt` still wins. A map that deliberately publishes Black Dog or
//   CRA craft keeps doing so when this setting is off, which is the default.
// * This is LOCAL. It prunes the list on the machine it runs on. It is not a
//   synchronized match rule: Redux clients each build this list from their own
//   copy of the same map files, and nothing here is sent over the wire. With a
//   stock client, or an OpenShim client with the setting off, that client still
//   sees the full pool. It is therefore a reference implementation and a
//   matched-mod convenience, not enforcement. Do not describe it as enforcement.
// * Nation is list state only. `+0x60` is never written to team state, so this
//   cannot change team ownership, nation/faction assignment, ODF resolution,
//   producer/build menus, AI production, or physics.
//
// Default OFF: with [Network] StockFactionsOnly unset, the hook still installs
// but prunes nothing, so behaviour is bit-identical to stock Redux.

#include "mp_faction_restrict.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstring>
#include <cstdint>
#include <string>

namespace BZROpenShim { namespace MpFactionRestrict {

namespace {

constexpr char kComponent[] = "mp-faction";

// --- Verified layout of the list singleton (see the .md, §3.2) --------------
// +0x00..0x3B  five std::vector, 0x0C bytes each, one per nation
// +0x3C        selection index inside the active bucket
// +0x40..0x57  loaded filename (std::string)
// +0x58/+0x5C  source-file timestamp used as a reload cache key
// +0x60        current nation index
constexpr uint32_t kBucketStride   = 0x0C;
constexpr uint32_t kEntrySize      = 0x60; // proven by FUN_00766F80: (end-begin)/0x60
constexpr uint32_t kOffSelIndex    = 0x3C;
constexpr uint32_t kOffTimestampLo = 0x58;
constexpr uint32_t kOffCurNation   = 0x60;

// __thiscall void Load(this, std::string* poolName);  callee-clean, `ret 4`.
using FnLoadVehicleList = void(__fastcall*)(void* self, void* unusedEdx, void* poolName);
// __thiscall void clear(std::vector*);  _Orphan_all + _Destroy + end = begin.
using FnClearBucket     = void(__fastcall*)(void* vec, void* unusedEdx);

std::atomic<bool>  g_Installed{false};
std::atomic<bool>  g_FailureLogged{false};
FnLoadVehicleList  g_OrigLoad  = nullptr;
FnClearBucket      g_ClearBucket = nullptr;

// Remembers the mask we last applied so a mid-session config change can
// invalidate the loader's own file/timestamp cache and force a rebuild.
uint32_t g_LastAppliedMask = 0xFFFFFFFFu;

// Offset of the `call clear(bucket)` inside the loader's five-iteration
// bucket-reset loop: 0x00766A58 - 0x00766900 on exact GOG Redux 2.2.301.
constexpr uint32_t kClearCallOffsetInLoader = 0x158;

// Derive the bucket `clear` from the loader rather than pattern-scanning for
// it. Its body is a std::vector<T>::clear template instantiation that appears
// byte-identically at 16 unrelated addresses in this image once the import and
// call operands are wildcarded, so a signature scan cannot establish identity.
// Anchoring on the loader's own call site does, and the body check below then
// confirms we landed on the shape we expect.
FnClearBucket ResolveClearBucketFromLoader(uint32_t loaderAddr)
{
    void* target = HookEngine::ResolveRelCallTarget(loaderAddr + kClearCallOffsetInLoader);
    if (!target)
        return nullptr;

    // _Orphan_all through an import thunk, _Destroy(begin,end), then end = begin.
    // Operand bytes (12..15 import, 33..36 rel32) are deliberately not checked.
    static const struct { uint32_t index; uint8_t value; } kBody[] = {
        { 0,0x55},{ 1,0x8B},{ 2,0xEC},{ 3,0x51},{ 4,0x89},{ 5,0x4D},{ 6,0xFC},
        { 7,0x8B},{ 8,0x4D},{ 9,0xFC},{10,0xFF},{11,0x15},
        {16,0x8B},{17,0x45},{18,0xFC},{19,0x8B},{20,0x48},{21,0x04},{22,0x51},
        {23,0x8B},{24,0x55},{25,0xFC},{26,0x8B},{27,0x02},{28,0x50},{29,0x8B},
        {30,0x4D},{31,0xFC},{32,0xE8},
        {37,0x8B},{38,0x4D},{39,0xFC},{40,0x8B},{41,0x55},{42,0xFC},{43,0x8B},
        {44,0x02},{45,0x89},{46,0x41},{47,0x04},
    };
    uint8_t body[48] = {};
    if (!HookEngine::ReadMemory(static_cast<uint32_t>(reinterpret_cast<uintptr_t>(target)),
                                body, sizeof(body)))
        return nullptr;
    for (const auto& b : kBody)
    {
        if (body[b.index] != b.value)
            return nullptr;
    }
    return reinterpret_cast<FnClearBucket>(target);
}

bool ReadShimBool(const char* name, bool defaultValue)
{
    // openshim_env_config.h is force-included, so this reads openshim.ini first
    // and falls back to the real process environment.
    char raw[64] = {};
    const DWORD len = GetEnvironmentVariableA(name, raw, sizeof(raw));
    if (len == 0 || len >= sizeof(raw))
        return defaultValue;

    std::string value(raw, len);
    while (!value.empty() && (value.front() == ' ' || value.front() == '\t')) value.erase(value.begin());
    while (!value.empty() && (value.back()  == ' ' || value.back()  == '\t')) value.pop_back();
    for (auto& c : value) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));

    if (value == "1" || value == "true" || value == "on"  || value == "yes" || value == "enabled")  return true;
    if (value == "0" || value == "false"|| value == "off" || value == "no"  || value == "disabled") return false;
    return defaultValue;
}

uint8_t* BucketAt(void* self, int nation)
{
    return static_cast<uint8_t*>(self) + static_cast<uint32_t>(nation) * kBucketStride;
}

// Mirrors FUN_00766F80 exactly: (end - begin) / 0x60.
int BucketCount(void* self, int nation)
{
    const uint8_t* v = BucketAt(self, nation);
    uint32_t begin = 0, end = 0;
    std::memcpy(&begin, v,     sizeof(begin));
    std::memcpy(&end,   v + 4, sizeof(end));
    if (end < begin) return 0;
    const uint32_t bytes = end - begin;
    if (bytes % kEntrySize != 0) return -1; // layout mismatch -> caller stands down
    return static_cast<int>(bytes / kEntrySize);
}

} // namespace

bool IsEnabled()
{
    return ReadShimBool("OPENSHIM_STOCK_FACTIONS_ONLY", false);
}

uint32_t AllowedNationMask()
{
    // [Network] StockFactionSet is the ODF first-character set, e.g.
    //   "as"  -> NSDF + CCA          (default; the balanced stock pair)
    //   "asb" -> NSDF + CCA + BlackDog  (exactly the 1.5 `netveh.odf` pool)
    // Unrecognised or empty input falls back to the default rather than
    // producing an empty list.
    uint32_t mask = 0;
    char raw[64] = {};
    const DWORD len = GetEnvironmentVariableA("OPENSHIM_STOCK_FACTION_SET", raw, sizeof(raw));
    if (len > 0 && len < sizeof(raw))
    {
        for (DWORD i = 0; i < len; ++i)
        {
            switch (tolower(static_cast<unsigned char>(raw[i])))
            {
                case 'a': mask |= (1u << Nation_NSDF);     break;
                case 's': mask |= (1u << Nation_CCA);      break;
                case 'b': mask |= (1u << Nation_BlackDog); break;
                case 'c': mask |= (1u << Nation_CRA);      break;
                case 'o': mask |= (1u << Nation_Other);    break;
                default: break; // ignore separators and noise
            }
        }
    }
    if (mask == 0)
        mask = (1u << Nation_NSDF) | (1u << Nation_CCA);
    return mask;
}

namespace {

// Runs after the engine has fully populated the five buckets.
void PruneToAllowedNations(void* self)
{
    if (!self || !g_ClearBucket)
        return;

    const uint32_t allowed = AllowedNationMask();

    // Validate the layout before touching anything. A single bad count means we
    // are not looking at the structure we think we are, so stand down entirely.
    int counts[Nation_Count] = {};
    int allowedTotal = 0;
    for (int n = 0; n < Nation_Count; ++n)
    {
        counts[n] = BucketCount(self, n);
        if (counts[n] < 0)
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[FACTION] bucket %d has a non-multiple-of-0x60 span; layout unverified, pruning skipped", n);
            return;
        }
        if (allowed & (1u << n))
            allowedTotal += counts[n];
    }

    // Fail safe: never leave the player with an empty selector. If the pool
    // this map supplies contains nothing from the allowed set, the host's pool
    // wins and we prune nothing.
    if (allowedTotal == 0)
    {
        LogShimA(LogLevel::Info, kComponent,
                 "[FACTION] pool has no craft in the allowed set (mask=0x%02X); leaving the full pool intact",
                 allowed);
        return;
    }

    int removed = 0;
    for (int n = 0; n < Nation_Count; ++n)
    {
        if (allowed & (1u << n))
            continue;
        if (counts[n] <= 0)
            continue;
        // Use the engine's own clear (FUN_007670D0): it runs each entry's
        // destructor via _Destroy before resetting end = begin. Never reset the
        // pointers by hand here; the entries own heap strings.
        g_ClearBucket(BucketAt(self, n), nullptr);
        removed += counts[n];
    }

    // Repair the active selection if it pointed into a bucket we just emptied.
    // FUN_007667C0/FUN_00766860 already skip empty buckets, but `+0x60` may be
    // sitting on one right now (it is seeded from multi.ini `multi/faction`).
    int32_t cur = 0;
    std::memcpy(&cur, static_cast<uint8_t*>(self) + kOffCurNation, sizeof(cur));
    const bool curUsable = (cur >= 0 && cur < Nation_Count) &&
                           (allowed & (1u << cur)) != 0 &&
                           BucketCount(self, cur) > 0;
    if (!curUsable)
    {
        for (int n = 0; n < Nation_Count; ++n)
        {
            if ((allowed & (1u << n)) && BucketCount(self, n) > 0)
            {
                const int32_t next = n;
                std::memcpy(static_cast<uint8_t*>(self) + kOffCurNation, &next, sizeof(next));
                break;
            }
        }
        const int32_t zero = 0;
        std::memcpy(static_cast<uint8_t*>(self) + kOffSelIndex, &zero, sizeof(zero));
    }

    std::memcpy(&cur, static_cast<uint8_t*>(self) + kOffCurNation, sizeof(cur));
    LogShimA(LogLevel::Info, kComponent,
             "[FACTION] pruned %d craft outside mask=0x%02X (a=%d s=%d b=%d c=%d other=%d) -> nation=%d",
             removed, allowed, counts[0], counts[1], counts[2], counts[3], counts[4], cur);
}

// Replacement for the two `call FUN_00766900` sites. __fastcall places `self`
// in ecx and leaves the single stack argument to be cleaned by us, which is the
// same contract as the original __thiscall `ret 4`.
void __fastcall LoadVehicleListIntercept(void* self, void* unusedEdx, void* poolName)
{
    const bool enabled = IsEnabled();
    const uint32_t mask = enabled ? AllowedNationMask() : 0;

    // The loader early-outs when the same file with the same timestamp is
    // already loaded. After a config change that cache would hand back the
    // previously pruned (or unpruned) buckets, so invalidate it first.
    if (self && mask != g_LastAppliedMask)
    {
        const int64_t invalid = 0;
        std::memcpy(static_cast<uint8_t*>(self) + kOffTimestampLo, &invalid, sizeof(invalid));
    }

    if (g_OrigLoad)
        g_OrigLoad(self, unusedEdx, poolName);

    if (enabled)
        PruneToAllowedNations(self);

    g_LastAppliedMask = mask;
}

} // namespace

void InstallMpFactionRestrictIfPossible()
{
    if (g_Installed.load())
        return;

    // Both resolves anchor on the CALL instruction itself, not on its operand:
    // a .text reference scan otherwise lands a few bytes late and the guard
    // fails silently.
    const uint32_t netvehCall  = HookEngine::ResolveNamedAddress("MPVehicleList::LoadCallSiteNetveh");
    const uint32_t missionCall = HookEngine::ResolveNamedAddress("MPVehicleList::LoadCallSiteMission");

    if (netvehCall == 0 || missionCall == 0)
    {
        if (!g_FailureLogged.exchange(true))
            LogShimA(LogLevel::Info, kComponent,
                     "[FACTION] resolves not ready (netveh=0x%08X mission=0x%08X); deferring",
                     netvehCall, missionCall);
        return;
    }

    // Identity, not just signature: the two call sites must name one loader.
    // A unique byte signature is not function identity on its own.
    void* netvehTarget  = HookEngine::ResolveRelCallTarget(netvehCall);
    void* missionTarget = HookEngine::ResolveRelCallTarget(missionCall);
    if (!netvehTarget || netvehTarget != missionTarget)
    {
        LogShimA(LogLevel::Warn, kComponent,
                 "[FACTION] call sites disagree on the loader (netveh->%p mission->%p); hook disabled",
                 netvehTarget, missionTarget);
        return;
    }

    const uint32_t loaderAddr = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(netvehTarget));
    FnClearBucket clearFn = ResolveClearBucketFromLoader(loaderAddr);
    if (!clearFn)
    {
        LogShimA(LogLevel::Warn, kComponent,
                 "[FACTION] bucket clear not identified from loader 0x%08X; hook disabled", loaderAddr);
        return;
    }

    g_OrigLoad    = reinterpret_cast<FnLoadVehicleList>(netvehTarget);
    g_ClearBucket = clearFn;

    // Rewrite each `call rel32` to reach our interceptor, verifying the exact
    // original five bytes first so a different build fails closed.
    auto patchCallSite = [](uint32_t site) -> bool
    {
        uint8_t original[5] = {};
        if (!HookEngine::ReadMemory(site, original, sizeof(original)) || original[0] != 0xE8)
            return false;

        HookEngine::PatchDef def;
        def.address = site;
        def.type = HookEngine::PatchType::REL32;
        def.name = "MPVehicleList::LoadCallSite";
        def.verified = true;
        def.expected_original.assign(original, original + sizeof(original));

        const int32_t rel =
            static_cast<int32_t>(reinterpret_cast<uintptr_t>(&LoadVehicleListIntercept)) -
            static_cast<int32_t>(site + 5);
        def.payload.assign(5, 0);
        def.payload[0] = 0xE8;
        std::memcpy(def.payload.data() + 1, &rel, sizeof(rel));
        return HookEngine::ApplyPatch(def);
    };

    if (!patchCallSite(netvehCall) || !patchCallSite(missionCall))
    {
        LogShimA(LogLevel::Warn, kComponent,
                 "[FACTION] failed to rewrite loader call sites (netveh=0x%08X mission=0x%08X)",
                 netvehCall, missionCall);
        g_OrigLoad = nullptr;
        g_ClearBucket = nullptr;
        return;
    }

    g_Installed.store(true);
    LogShimA(LogLevel::Info, kComponent,
             "[FACTION] installed: loader=%p clear=%p sites=0x%08X/0x%08X enabled=%u mask=0x%02X",
             netvehTarget, reinterpret_cast<void*>(clearFn), netvehCall, missionCall,
             IsEnabled() ? 1u : 0u, AllowedNationMask());
}

}} // namespace BZROpenShim::MpFactionRestrict
