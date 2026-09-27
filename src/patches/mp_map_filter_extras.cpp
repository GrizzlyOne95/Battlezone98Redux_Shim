// mp_map_filter_extras.cpp
// BZR Open Shim - extra filters on the multiplayer Create Game map list.
//
// Stock offers All Maps, Strategy, Death Match, King of the Hill, 2/3/4
// Players and (when any exist) Workshop. This adds "5+ Players" and "Stock
// Maps" without re-implementing the list: every container operation is the
// engine's own, so nothing the MSVC120 game allocates is ever freed by the
// v143 shim, or the other way round.
//
//   1. Filter list. The map component's constructor (0x007A3160) fills a
//      keys vector (+0x00) and a labels vector (+0x0C) with push_back
//      (0x006CF320). A detour at 0x007A35C0, the first instruction after the
//      last label, appends our key/label pairs the same way. Like stock's
//      Workshop entry, an extra filter is offered only when at least one map
//      matches it: the list's reselect path picks row 0 without a bounds
//      check, so an empty result must never be reachable.
//   2. Predicate. cMapManager::BuildFilteredMapList (0x00752A50, thiscall on
//      the filtered deque, key std::string by value, ret 0x18) appends
//      nothing for a key it does not know. For one of our keys the entry
//      detour destroys the key, passes "All Maps" instead (short enough for
//      the small-string buffer, so the engine allocates nothing), and
//      remembers which extra filter is active.
//   3. Append. The predicate's only push_back call (0x00752CD0 ->
//      0x00752DD0, the deque<MapEntry> copy-append) is redirected here, so a
//      map is appended only when it matches the active extra filter.
//
// Off by default: [General] MapFilterExtras = 1, or
// OPENSHIM_MAP_FILTER_EXTRAS=1. Every address comes from engine_addresses
// with its guard bytes; a mismatch leaves the stock list untouched.

#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "bzr_string.h"
#include "hook_engine.h"
#include "map_filter_extras.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace Hooks
    {
        namespace
        {
            using MapFilterExtras::Extra;
            using MapFilterExtras::ExtraFilterInfo;
            using MapFilterExtras::kExtraFilters;

            // __thiscall with the key by value; declared __fastcall so the
            // dummy edx lines the key up on the stack. Callee pops 0x18.
            using FnMapFilterPredicate = void(__fastcall*)(void* filteredDeque, void* edx, BzrString key);
            using FnMapDequePushBack = void(__thiscall*)(void* deque, const void* entry);
            using FnVectorStringPushBack = void(__thiscall*)(void* vector, const BzrString* value);

            // MapEntry (0xB4 bytes, confirmed from its copy constructor 0x00753550).
            constexpr uint32_t kMapEntryMinPlayers = 0x18;
            constexpr uint32_t kMapEntryMaxPlayers = 0x1C;
            constexpr uint32_t kMapEntryWorkshopId = 0x3C;
            // The map manager's full list is a deque<MapEntry> at +0x18 with
            // one element per block: +4 block map, +8 map size (a power of
            // two), +0xC first offset, +0x10 count.
            constexpr uint32_t kMapManagerDeque = 0x18;
            // Map component (constructed by 0x007A3160; `this` at [ebp-0x1C4]).
            constexpr uint32_t kComponentKeys = 0x00;
            constexpr uint32_t kComponentLabels = 0x0C;

            constexpr uint8_t kPredicatePrologue[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
            constexpr uint8_t kKeysBuiltBytes[] = { 0x8B, 0x85, 0x3C, 0xFE, 0xFF, 0xFF };

            InlineDetour32 g_PredicateDetour = {};
            InlineDetour32 g_KeysBuiltDetour = {};
            void* g_KeysBuiltTrampoline = nullptr;
            FnMapDequePushBack g_MapDequePushBack = nullptr;
            FnVectorStringPushBack g_VectorStringPushBack = nullptr;
            uint32_t g_MapManagerSlot = 0;
            bool g_MapFilterExtrasInstalled = false;
            bool g_MapFilterExtrasInstallLogged = false;

            // Set only while the predicate runs for one of our keys. The
            // filter list lives on the game's UI thread.
            Extra g_ActiveExtra = Extra::None;

            constexpr const char* kComponent = "mapfilter";

            bool ShouldEnableMapFilterExtras()
            {
                if (EnvFlagEnabled("OPENSHIM_MAP_FILTER_EXTRAS"))
                    return true;
                bool enabled = false;
                return TryGetUserConfigBool("General", "MapFilterExtras", enabled) && enabled;
            }

            // Reads the fields the extra filters use. POD-only: called from
            // inside __try.
            bool TryReadEntry(const uint8_t* entry, int& minPlayers, int& maxPlayers,
                              char* workshopId, size_t workshopIdSize)
            {
                __try
                {
                    minPlayers = *reinterpret_cast<const int*>(entry + kMapEntryMinPlayers);
                    maxPlayers = *reinterpret_cast<const int*>(entry + kMapEntryMaxPlayers);
                    const char* id = BzrStringData(
                        reinterpret_cast<const BzrString*>(entry + kMapEntryWorkshopId));
                    size_t i = 0;
                    for (; id && id[i] && i + 1 < workshopIdSize; ++i)
                        workshopId[i] = id[i];
                    workshopId[i] = '\0';
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            bool EntryMatches(const void* entry, Extra extra)
            {
                if (extra == Extra::None)
                    return true;
                int minPlayers = 0;
                int maxPlayers = 0;
                char workshopId[64] = {};
                // An unreadable entry is shown rather than hidden: the extra
                // filter narrows "All Maps", so failing open is what stock does.
                if (!entry || !TryReadEntry(static_cast<const uint8_t*>(entry), minPlayers,
                                            maxPlayers, workshopId, sizeof(workshopId)))
                {
                    return true;
                }
                return MapFilterExtras::MatchesExtra(extra, minPlayers, maxPlayers, workshopId);
            }

            // Collects up to `capacity` entry pointers from the full map list.
            // POD-only: called from inside __try.
            bool TryCollectMapEntries(const void** out, unsigned capacity, unsigned& outCount)
            {
                outCount = 0;
                __try
                {
                    const uint8_t* manager = *reinterpret_cast<const uint8_t* const*>(g_MapManagerSlot);
                    if (!manager)
                        return false;
                    const uint8_t* deque = manager + kMapManagerDeque;
                    const void* const* blocks = *reinterpret_cast<const void* const* const*>(deque + 0x4);
                    const uint32_t mapSize = *reinterpret_cast<const uint32_t*>(deque + 0x8);
                    const uint32_t first = *reinterpret_cast<const uint32_t*>(deque + 0xC);
                    const uint32_t count = *reinterpret_cast<const uint32_t*>(deque + 0x10);
                    if (!blocks || mapSize == 0 || (mapSize & (mapSize - 1)) != 0)
                        return false;
                    for (uint32_t i = 0; i < count && outCount < capacity; ++i)
                    {
                        const void* entry = blocks[(first + i) & (mapSize - 1)];
                        if (entry)
                            out[outCount++] = entry;
                    }
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    outCount = 0;
                    return false;
                }
            }

            unsigned CountMatchingMaps(Extra extra)
            {
                static const void* entries[4096];
                unsigned count = 0;
                if (!TryCollectMapEntries(entries, 4096, count))
                    return 0;
                unsigned matches = 0;
                for (unsigned i = 0; i < count; ++i)
                {
                    if (EntryMatches(entries[i], extra))
                        ++matches;
                }
                return matches;
            }

            // Appends one key/label pair through the engine's own string and
            // vector code. POD-only: called from inside __try.
            bool TryPushKeyAndLabel(uint8_t* component, const char* key, const char* label)
            {
                __try
                {
                    BzrString text;
                    g_BzrFn_BzrStringCtorFromCStr(&text, key);
                    g_VectorStringPushBack(component + kComponentKeys, &text);
                    g_BzrFn_BzrStringDtor(&text);

                    g_BzrFn_BzrStringCtorFromCStr(&text, label);
                    g_VectorStringPushBack(component + kComponentLabels, &text);
                    g_BzrFn_BzrStringDtor(&text);
                    return true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return false;
                }
            }

            void __cdecl AppendExtraFilterKeys(uint8_t* component)
            {
                if (!component || !g_VectorStringPushBack ||
                    !g_BzrFn_BzrStringCtorFromCStr || !g_BzrFn_BzrStringDtor)
                {
                    return;
                }
                for (const ExtraFilterInfo& info : kExtraFilters)
                {
                    const unsigned matches = CountMatchingMaps(info.extra);
                    if (matches == 0)
                    {
                        LogShimA(LogLevel::Info, kComponent, "[MAPFILTER] '%s' not offered: no map matches", info.label);
                        continue;
                    }
                    const bool pushed = TryPushKeyAndLabel(component, info.key, info.label);
                    LogShimA(LogLevel::Info, kComponent, "[MAPFILTER] '%s' %s (%u maps)",
                        info.label, pushed ? "offered" : "push failed", matches);
                }
            }

            __declspec(naked) void MapFilterKeysBuiltStub()
            {
                __asm
                {
                    pushad
                    pushfd
                    mov  eax, dword ptr [ebp - 0x1C4]
                    push eax
                    call AppendExtraFilterKeys
                    add  esp, 4
                    popfd
                    popad
                    jmp  dword ptr [g_KeysBuiltTrampoline]
                }
            }

            void __fastcall MapFilterPredicateHook(void* filteredDeque, void* edx, BzrString key)
            {
                const auto original = reinterpret_cast<FnMapFilterPredicate>(g_PredicateDetour.trampoline);
                const Extra extra = MapFilterExtras::ExtraFromKey(BzrStringData(&key));
                if (extra == Extra::None)
                {
                    g_ActiveExtra = Extra::None;
                    original(filteredDeque, edx, key); // takes ownership of the key
                    return;
                }

                // Run the stock predicate as "All Maps" and narrow it in the
                // append hook. The original would have destroyed the key, so
                // this frame does it instead; "All Maps" is short enough for
                // the small-string buffer, so it owns no heap memory.
                BzrString allMaps;
                g_BzrFn_BzrStringCtorFromCStr(&allMaps, "All Maps");
                g_BzrFn_BzrStringDtor(&key);
                g_ActiveExtra = extra;
                original(filteredDeque, edx, allMaps);
                g_ActiveExtra = Extra::None;
            }

            void __fastcall MapFilterAppendHook(void* filteredDeque, void* /*edx*/, const void* entry)
            {
                if (g_ActiveExtra != Extra::None && !EntryMatches(entry, g_ActiveExtra))
                    return;
                g_MapDequePushBack(filteredDeque, entry);
            }

            bool ResolveCode(const char* name, uint32_t& address)
            {
                return HookEngine::ResolveEngineAddress(name, address) == HookEngine::EngineAddressStatus::Bound;
            }
        }

        void InstallMapFilterExtrasIfEnabled()
        {
            if (g_MapFilterExtrasInstalled || !ShouldEnableMapFilterExtras())
                return;

            uint32_t predicate = 0;
            uint32_t appendCall = 0;
            uint32_t pushBack = 0;
            uint32_t keysBuilt = 0;
            uint32_t vectorPush = 0;
            const bool resolved =
                ResolveCode("MapFilterPredicate", predicate) &&
                ResolveCode("MapFilterAppendCall", appendCall) &&
                ResolveCode("MapDequePushBack", pushBack) &&
                ResolveCode("MapFilterKeysBuilt", keysBuilt) &&
                ResolveCode("VectorStringPushBack", vectorPush) &&
                HookEngine::ResolveEngineAddress("MapManagerSlot", g_MapManagerSlot) ==
                    HookEngine::EngineAddressStatus::BoundData;
            if (!resolved || !g_BzrFn_BzrStringCtorFromCStr || !g_BzrFn_BzrStringDtor)
            {
                if (!g_MapFilterExtrasInstallLogged)
                {
                    LogShimA(LogLevel::Warn, kComponent, "[MAPFILTER] extra filters stand down: an engine address did not verify");
                    g_MapFilterExtrasInstallLogged = true;
                }
                return;
            }
            g_MapDequePushBack = reinterpret_cast<FnMapDequePushBack>(pushBack);
            g_VectorStringPushBack = reinterpret_cast<FnVectorStringPushBack>(vectorPush);

            // Filtering first, then the list entries: an entry is only
            // offered once selecting it can actually narrow the list.
            if (!InstallInlineDetour32(g_PredicateDetour, predicate,
                                       reinterpret_cast<void*>(&MapFilterPredicateHook),
                                       sizeof(kPredicatePrologue), kPredicatePrologue,
                                       sizeof(kPredicatePrologue)))
            {
                LogShimA(LogLevel::Warn, kComponent, "[MAPFILTER] extra filters stand down: predicate detour refused");
                g_MapFilterExtrasInstalled = true;
                return;
            }
            if (!RedirectCallTarget(appendCall, pushBack, reinterpret_cast<uintptr_t>(&MapFilterAppendHook)))
            {
                // The predicate detour stays, but with no append hook an extra
                // key would show every map; since no extra key is offered
                // below, the detour only ever sees stock keys and forwards them.
                LogShimA(LogLevel::Warn, kComponent, "[MAPFILTER] extra filters stand down: append call site did not match");
                g_MapFilterExtrasInstalled = true;
                return;
            }
            if (!InstallInlineDetour32(g_KeysBuiltDetour, keysBuilt,
                                       reinterpret_cast<void*>(&MapFilterKeysBuiltStub),
                                       sizeof(kKeysBuiltBytes), kKeysBuiltBytes,
                                       sizeof(kKeysBuiltBytes)))
            {
                LogShimA(LogLevel::Warn, kComponent, "[MAPFILTER] extra filters stand down: filter-list detour refused");
                g_MapFilterExtrasInstalled = true;
                return;
            }
            // The detour publishes its trampoline only after the jump is
            // written. That is safe here because this runs in late init, long
            // before the Create Game screen can exist to reach the stub.
            g_KeysBuiltTrampoline = g_KeysBuiltDetour.trampoline;
            g_MapFilterExtrasInstalled = true;
            LogShimA(LogLevel::Info, kComponent, "[MAPFILTER] extra filters installed (5+ Players, Stock Maps)");
        }
    }
}
