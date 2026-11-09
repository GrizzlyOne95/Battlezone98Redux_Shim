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
#include "bool_token.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstring>
#include <cstdint>
#include <string>

namespace BZROpenShim {
bool VehicleListPoolFallsBackToNetveh(const char* name); // vehicle_list_mod_fix.cpp
}

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

// "Any Nation" OFF: restrict to the exact 1.5 netveh.odf names. See
// SetAnyNationRestrict in the header.
std::atomic<bool> g_AnyNationRestrict{false};
// The list singleton, captured from the last loader call (ecx).
std::atomic<void*> g_ListSelf{nullptr};
constexpr uint32_t kOffCachedNameString = 0x40; // std::string, size at +0x10

// The 27 entries of the 1.5 stock netveh.odf (Any Nation OFF pool):
// NSDF 13, CCA 9, Black Dog 5, CRA 0. Source:
// Battlezone_Source/BZ1/1.5/Battlezone_Install/stock/netveh.odf. Redux's own
// netveh.odf lacks avtam2 and svtamp (swapped out for bsuser/cvrckt/cvtnk/
// cvwamp), so on the shipped pool 25 of these survive; the filter only ever
// subtracts, so those two are not added back.
const char* const kStock15Names[] = {
    // NSDF (13)
    "avtump", "avltnk", "avltmp", "avlamp", "avtank", "asuser", "avtam2",
    "avfimp", "avwalk", "avwamp", "avtamp", "avhrmp", "avrckt",
    // CCA (9)
    "ssuser", "svtamp", "svtank", "svfimp", "svwamp", "svhraz", "svtump",
    "svltnk", "svrckt",
    // Black Dog (5)
    "bvtump", "bvltnk", "bvraz", "bvhraz", "bvtank",
};

// MSVC std::string as laid out in this build (FUN_00766F30 reads size at +0x10):
// char buf[16] | uint32 size | uint32 res. Returns null if it looks wrong.
const char* EntryNameChars(const uint8_t* entry)
{
    uint32_t size = 0, res = 0;
    std::memcpy(&size, entry + 0x10, sizeof(size));
    std::memcpy(&res,  entry + 0x14, sizeof(res));
    if (size > res || res > 0x1000)
        return nullptr;
    if (res >= 16)
    {
        const char* p = nullptr;
        std::memcpy(&p, entry, sizeof(p));
        return p;
    }
    return reinterpret_cast<const char*>(entry);
}

// True when the pool being loaded is (or falls back to) the global netveh.odf.
// 1.5's Any Nation only chose which netveh file to load; a map's own .vxt list
// replaced it and was never filtered, so OFF prunes netveh only.
bool IsNetvehPool(const void* poolName)
{
    const char* n = poolName ? EntryNameChars(static_cast<const uint8_t*>(poolName)) : nullptr;
    if (!n)
        return false;
    const size_t len = strnlen(n, 0x200);
    const size_t k = sizeof("netveh.odf") - 1;
    if (len >= k && _stricmp(n + len - k, "netveh.odf") == 0
        && (len == k || n[len - k - 1] == '\\' || n[len - k - 1] == '/'))
        return true;
    // A missing map .vxt is loaded as netveh.odf content, so treat it as netveh.
    return VehicleListPoolFallsBackToNetveh(n);
}

bool InStock15Set(const char* name)
{
    if (!name)
        return false;
    for (const char* n : kStock15Names)
    {
        if (_stricmp(n, name) == 0)
            return true;
    }
    return false;
}

__declspec(noinline) bool SafeCallLoad(FnLoadVehicleList fn, void* self, void* arg)
{
    __try
    {
        fn(self, nullptr, arg);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }
}

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

    bool value = defaultValue;
    return BZROpenShim::BoolToken::TryParse(raw, len, value) ? value : defaultValue;
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

// Any Nation OFF: keep only the 1.5 netveh.odf names. Compacts each bucket in
// place. A removed entry that owns heap strings (>15 chars) is leaked rather
// than destroyed: its destructor address is not identified, and every shipped
// entry is short enough to live in the inline buffer.
void PruneToStock15Names(void* self)
{
    if (!self)
        return;

    int counts[Nation_Count] = {};
    int keepTotal = 0;
    for (int n = 0; n < Nation_Count; ++n)
    {
        counts[n] = BucketCount(self, n);
        if (counts[n] < 0)
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[ANYNATION] bucket %d span is not a multiple of 0x60; name pruning skipped", n);
            return;
        }
        uint32_t begin = 0;
        std::memcpy(&begin, BucketAt(self, n), sizeof(begin));
        for (int i = 0; i < counts[n]; ++i)
        {
            if (InStock15Set(EntryNameChars(reinterpret_cast<const uint8_t*>(begin) + i * kEntrySize)))
                ++keepTotal;
        }
    }
    if (keepTotal == 0)
    {
        LogShimA(LogLevel::Info, kComponent,
                 "[ANYNATION] pool has no craft from the 1.5 netveh.odf set; leaving the full pool intact");
        return;
    }

    // Remember the selection by ODF name so it can be found again.
    char selName[40] = {};
    int32_t cur = 0, sel = 0;
    std::memcpy(&cur, static_cast<uint8_t*>(self) + kOffCurNation, sizeof(cur));
    std::memcpy(&sel, static_cast<uint8_t*>(self) + kOffSelIndex, sizeof(sel));
    if (cur >= 0 && cur < Nation_Count && sel >= 0 && sel < counts[cur])
    {
        uint32_t begin = 0;
        std::memcpy(&begin, BucketAt(self, cur), sizeof(begin));
        const char* nm = EntryNameChars(reinterpret_cast<const uint8_t*>(begin) + sel * kEntrySize);
        if (nm)
            strncpy_s(selName, sizeof(selName), nm, _TRUNCATE);
    }

    int removed = 0, leaked = 0, after[Nation_Count] = {};
    for (int n = 0; n < Nation_Count; ++n)
    {
        uint8_t* vec = BucketAt(self, n);
        uint32_t begin = 0;
        std::memcpy(&begin, vec, sizeof(begin));
        uint8_t* dst = reinterpret_cast<uint8_t*>(begin);
        for (int i = 0; i < counts[n]; ++i)
        {
            uint8_t* src = reinterpret_cast<uint8_t*>(begin) + i * kEntrySize;
            if (InStock15Set(EntryNameChars(src)))
            {
                if (dst != src)
                    std::memmove(dst, src, kEntrySize);
                dst += kEntrySize;
                ++after[n];
            }
            else
            {
                ++removed;
                for (int s = 0; s < 4; ++s)
                {
                    uint32_t res = 0;
                    std::memcpy(&res, src + s * 0x18 + 0x14, sizeof(res));
                    if (res >= 16)
                        ++leaked;
                }
            }
        }
        const uint32_t newEnd = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(dst));
        std::memcpy(vec + 4, &newEnd, sizeof(newEnd));
    }

    // Selection repair: same craft if it survived, else the first allowed one,
    // staying in the same faction when that still has craft.
    int32_t newCur = cur, newSel = 0;
    bool found = false;
    if (newCur >= 0 && newCur < Nation_Count && selName[0])
    {
        uint32_t begin = 0;
        std::memcpy(&begin, BucketAt(self, newCur), sizeof(begin));
        for (int i = 0; i < after[newCur]; ++i)
        {
            const char* nm = EntryNameChars(reinterpret_cast<const uint8_t*>(begin) + i * kEntrySize);
            if (nm && _stricmp(nm, selName) == 0) { newSel = i; found = true; break; }
        }
    }
    if (!found && !(newCur >= 0 && newCur < Nation_Count && after[newCur] > 0))
    {
        for (int n = 0; n < Nation_Count; ++n)
        {
            if (after[n] > 0) { newCur = n; break; }
        }
    }
    std::memcpy(static_cast<uint8_t*>(self) + kOffCurNation, &newCur, sizeof(newCur));
    std::memcpy(static_cast<uint8_t*>(self) + kOffSelIndex, &newSel, sizeof(newSel));
    LogShimA(LogLevel::Info, kComponent,
             "[ANYNATION] pruned %d craft to the 1.5 netveh.odf set (a=%d s=%d b=%d c=%d other=%d); selection '%s' %s -> nation=%d index=%d leakedHeapStrings=%d",
             removed, after[0], after[1], after[2], after[3], after[4], selName,
             found ? "kept" : "pruned, reset to first allowed", newCur, newSel, leaked);
}

// Replacement for the two `call FUN_00766900` sites. __fastcall places `self`
// in ecx and leaves the single stack argument to be cleaned by us, which is the
// same contract as the original __thiscall `ret 4`.
void __fastcall LoadVehicleListIntercept(void* self, void* unusedEdx, void* poolName)
{
    const bool enabled = IsEnabled();
    const bool anyOff = g_AnyNationRestrict.load() && IsNetvehPool(poolName);
    const uint32_t mask = (enabled ? AllowedNationMask() : 0) | (anyOff ? 0x100u : 0u);
    if (self)
        g_ListSelf.store(self);

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
    if (anyOff)
        PruneToStock15Names(self);

    if (self)
    {
        int c[Nation_Count] = {};
        int total = 0;
        for (int n = 0; n < Nation_Count; ++n) { c[n] = BucketCount(self, n); total += c[n] > 0 ? c[n] : 0; }
        LogShimA(LogLevel::Info, kComponent,
                 "[ANYNATION] vehicle pool after load: total=%d (a=%d s=%d b=%d c=%d other=%d) anyNationRestrict=%u",
                 total, c[0], c[1], c[2], c[3], c[4], anyOff ? 1u : 0u);
    }

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
    // original five bytes first so a different build fails closed. The stock
    // bytes are handed back so a site can be put back if the other one fails.
    auto patchCallSite = [](uint32_t site, uint8_t (&original)[5]) -> bool
    {
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

    uint8_t netvehOriginal[5] = {};
    uint8_t missionOriginal[5] = {};
    if (!patchCallSite(netvehCall, netvehOriginal))
    {
        LogShimA(LogLevel::Warn, kComponent,
                 "[FACTION] failed to rewrite the netveh loader call site 0x%08X; hook disabled",
                 netvehCall);
        g_OrigLoad = nullptr;
        g_ClearBucket = nullptr;
        return;
    }
    if (!patchCallSite(missionCall, missionOriginal))
    {
        // The netveh site already reaches the interceptor. Put its stock call
        // back so neither site is hooked: a lone hooked site whose original
        // had been cleared would return without loading, and Create Game would
        // show an empty vehicle list. Should the restore itself fail, the
        // original is kept so the interceptor still delegates.
        const bool restored = HookEngine::WriteMemory(netvehCall, netvehOriginal, sizeof(netvehOriginal));
        void* netvehNow = HookEngine::ResolveRelCallTarget(netvehCall);
        LogShimA(LogLevel::Warn, kComponent,
                 "[FACTION] failed to rewrite the mission loader call site 0x%08X; netveh site 0x%08X %s (call -> %p); hook disabled",
                 missionCall, netvehCall,
                 restored ? "restored to stock" : "could not be restored, interceptor keeps delegating",
                 netvehNow);
        if (restored)
        {
            g_OrigLoad = nullptr;
            g_ClearBucket = nullptr;
        }
        return;
    }

    g_Installed.store(true);
    LogShimA(LogLevel::Info, kComponent,
             "[FACTION] installed: loader=%p clear=%p sites=0x%08X/0x%08X enabled=%u mask=0x%02X",
             netvehTarget, reinterpret_cast<void*>(clearFn), netvehCall, missionCall,
             IsEnabled() ? 1u : 0u, AllowedNationMask());
}

bool VehicleListHookReady()
{
    return g_Installed.load() && g_OrigLoad && g_ClearBucket;
}

bool LoadVehicleListThroughHook(void* self, void* poolName)
{
    if (!VehicleListHookReady())
        return false;
    LoadVehicleListIntercept(self, nullptr, poolName);
    return true;
}

void SetAnyNationRestrict(bool restrict)
{
    g_AnyNationRestrict.store(restrict);
}

bool AnyNationRestrictActive()
{
    return g_AnyNationRestrict.load();
}

bool RebuildVehicleList(const char* why)
{
    void* self = g_ListSelf.load();
    if (!self || !VehicleListHookReady())
    {
        LogShimA(LogLevel::Info, kComponent,
                 "[ANYNATION] list rebuild (%s) skipped: no list built yet (self=%p)", why ? why : "?", self);
        return false;
    }
    // The loader re-reads the file named in its cached filename string, so the
    // cache must hold one.
    uint32_t nameSize = 0;
    std::memcpy(&nameSize, static_cast<uint8_t*>(self) + kOffCachedNameString + 0x10, sizeof(nameSize));
    if (nameSize == 0 || nameSize > 0x200)
    {
        LogShimA(LogLevel::Warn, kComponent,
                 "[ANYNATION] list rebuild (%s) skipped: cached pool name has size %u", why ? why : "?", nameSize);
        return false;
    }
    const int64_t invalid = 0;
    std::memcpy(static_cast<uint8_t*>(self) + kOffTimestampLo, &invalid, sizeof(invalid));
    g_LastAppliedMask = 0xFFFFFFFEu;
    const bool ok = SafeCallLoad(&LoadVehicleListIntercept, self,
                                 static_cast<uint8_t*>(self) + kOffCachedNameString);
    LogShimA(LogLevel::Info, kComponent, "[ANYNATION] list rebuild (%s) %s", why ? why : "?",
             ok ? "done" : "FAILED (exception)");
    return ok;
}

}} // namespace BZROpenShim::MpFactionRestrict
