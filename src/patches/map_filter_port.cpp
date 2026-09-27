// map_filter_port.cpp
// BZR Open Shim - clean-room port of the multiplayer map list filter/sort
// (MapFilters1Rebuild, MapFilters2Filter and their BzrVector/MapEntry/
// MapRing helpers). Disabled: kept separate from the validated map
// hop/refresh hooks, which stay in bzr_hooks.cpp.
#include "bzr_hooks.h"
#include "bzr_object_layout.h"
#include "bzr_hooks_internal.h"
#include "engine_globals.h"
#include "game_state.h"
#include "openshim_ini.h"
#include "openshim_preset_migration.h"
#include "openshim_assets.h"
#include "terrain_proxy.h"
#include "terrain_tile_blend.h"
#include "bzr_options_ui.h"
#include "remembered_mesh_bounds_table.h"
#include "patches.h"
#include "patcher.h"
#include "fog_wake_feature.h"
#include "mp_vehicle_preview_fix.h"
#include "shim_log.h"
#include "x86_length.h"
#include "ogre_shader_cache.h"
#include "ogre_enhanced_light_selection.h"
#include "render_effect_intent.h"
#include "render_profile_runtime.h"
#include "native_ui.h"
#include "../engine/native_ui_validation.h"
#include "ogre_animation_profiler.h"
#include "ogre_profiler_algorithms.h"
#include "weapon_convergence.h"
#include "headlight_falloff.h"
#include "shadow_far_distance.h"
#include "sun_flash.h"
#include "chunk_batch_invalidation.h"
#include "ai_range_policy.h"
#include "lcbench_safety_policy.h"
#include "hook_engine.h"
#include "ui_performance.h"
#include "openshim_events.h"
#include "player_kill_trace.h"
#include "net_optimizer.h"
#include "pond_class_label.h"
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <array>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <intrin.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <exception>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <new>
#include <string>
#include <string_view>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    using namespace Hooks;

    namespace Hooks
    {
        struct BzrVector
        {
            BzrString* begin;
            BzrString* end;
            BzrString* cap;
        };

        struct MapFilterList
        {
            BzrVector keys;
            BzrVector labels;
        };

        struct MapEntry
        {
            BzrString name;
            int32_t field18;
            int32_t field1C;
            BzrString str20;
            char type;
            uint8_t pad39[3];
            BzrString str3C;
            BzrString str54;
            BzrString str6C;
            BzrString str84;
            BzrString str9C;
        };

        struct MapRing
        {
            void* pad0;
            void** entries;
            uint32_t capacity;
            uint32_t head;
            uint32_t count;
        };

        struct MapManager
        {
            uint8_t pad[0x1C];
            MapEntry** entries;
            uint32_t capacity;
            uint32_t head;
            uint32_t count;
        };

        static_assert(offsetof(MapEntry, field18) == 0x18, "MapEntry field18 offset mismatch");
        static_assert(offsetof(MapEntry, str20) == 0x20, "MapEntry str20 offset mismatch");
        static_assert(offsetof(MapEntry, type) == 0x38, "MapEntry type offset mismatch");
        static_assert(offsetof(MapEntry, str3C) == 0x3C, "MapEntry str3C offset mismatch");
        static_assert(offsetof(MapEntry, str54) == 0x54, "MapEntry str54 offset mismatch");
        static_assert(offsetof(MapEntry, str6C) == 0x6C, "MapEntry str6C offset mismatch");
        static_assert(offsetof(MapEntry, str84) == 0x84, "MapEntry str84 offset mismatch");
        static_assert(offsetof(MapEntry, str9C) == 0x9C, "MapEntry str9C offset mismatch");
        static_assert(sizeof(MapEntry) == 0xB4, "MapEntry size mismatch");

        static MapManager* GetMapManager()
        {
            __try
            {
                return *reinterpret_cast<MapManager**>(0x00945478);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        static bool BzrStringIsBlank(const BzrString* s)
        {
            if (!s || s->size == 0)
                return true;
            const char* data = BzrStringData(s);
            for (uint32_t i = 0; i < s->size; ++i)
            {
                if (data[i] != ' ' && data[i] != '\t' && data[i] != '\r' && data[i] != '\n')
                    return false;
            }
            return true;
        }

        static bool BzrStringEqualsCStr(const BzrString* s, const char* text)
        {
            if (!s || !text)
                return false;
            const size_t len = std::strlen(text);
            if (s->size != len)
                return false;
            const char* data = BzrStringData(s);
            return std::memcmp(data, text, len) == 0;
        }

        static bool BzrStringStartsWithI(const BzrString* s, const char* prefix)
        {
            if (!s || !prefix)
                return false;
            const size_t plen = std::strlen(prefix);
            if (s->size < plen)
                return false;
            const char* data = BzrStringData(s);
            for (size_t i = 0; i < plen; ++i)
            {
                if (std::tolower(static_cast<unsigned char>(data[i])) !=
                    std::tolower(static_cast<unsigned char>(prefix[i])))
                    return false;
            }
            return true;
        }

        static bool BzrStringContainsI(const BzrString* s, const char* needle)
        {
            if (!s || !needle || !*needle)
                return false;
            const size_t nlen = std::strlen(needle);
            if (nlen == 0 || s->size < nlen)
                return false;
            const char* data = BzrStringData(s);
            for (uint32_t i = 0; i + nlen <= s->size; ++i)
            {
                bool match = true;
                for (size_t j = 0; j < nlen; ++j)
                {
                    if (std::tolower(static_cast<unsigned char>(data[i + j])) !=
                        std::tolower(static_cast<unsigned char>(needle[j])))
                    {
                        match = false;
                        break;
                    }
                }
                if (match)
                    return true;
            }
            return false;
        }

        static void BzrVectorClear(BzrVector* v)
        {
            if (!v)
                return;
            if (v->begin && v->end)
            {
                for (BzrString* cur = v->begin; cur < v->end; ++cur)
                    BzrStringFree(cur);
            }
            if (v->begin)
                std::free(v->begin);
            v->begin = nullptr;
            v->end = nullptr;
            v->cap = nullptr;
        }

        static void BzrVectorEnsure(BzrVector* v, size_t extra)
        {
            if (!v)
                return;
            const size_t size = v->begin ? static_cast<size_t>(v->end - v->begin) : 0;
            const size_t cap = v->begin ? static_cast<size_t>(v->cap - v->begin) : 0;
            if (size + extra <= cap)
                return;

            size_t new_cap = cap ? cap * 2 : 8;
            if (new_cap < size + extra)
                new_cap = size + extra;

            BzrString* mem = static_cast<BzrString*>(std::malloc(new_cap * sizeof(BzrString)));
            if (!mem)
                return;

            if (v->begin && size)
            {
                std::memcpy(mem, v->begin, size * sizeof(BzrString));
                std::free(v->begin);
            }
            v->begin = mem;
            v->end = mem + size;
            v->cap = mem + new_cap;
        }

        static void BzrVectorPushCStr(BzrVector* v, const char* str)
        {
            if (!v)
                return;
            if (!str)
                str = "";
            BzrVectorEnsure(v, 1);
            if (!v->begin || v->end >= v->cap)
                return;
            BzrStringInitEmpty(v->end);
            BzrStringAssign(v->end, str, std::strlen(str));
            v->end += 1;
        }

        static void MapFilterListClear(MapFilterList* list)
        {
            if (!list)
                return;
            BzrVectorClear(&list->keys);
            BzrVectorClear(&list->labels);
        }

        static void MapFilterListPush(MapFilterList* list, const char* key, const char* label)
        {
            if (!list)
                return;
            BzrVectorPushCStr(&list->keys, key ? key : "");
            BzrVectorPushCStr(&list->labels, label ? label : "");
        }

        static bool MapEntryHasTag(const MapEntry* entry, const char* tag)
        {
            if (!entry || !tag || !*tag)
                return false;
            return BzrStringContainsI(&entry->str3C, tag) ||
                   BzrStringContainsI(&entry->str54, tag) ||
                   BzrStringContainsI(&entry->str6C, tag) ||
                   BzrStringContainsI(&entry->str84, tag) ||
                   BzrStringContainsI(&entry->str9C, tag) ||
                   BzrStringContainsI(&entry->name, tag)  ||
                   BzrStringContainsI(&entry->str20, tag);
        }

        static bool MapEntryIsStock(const MapEntry* entry)
        {
            if (!entry)
                return false;
            return BzrStringIsBlank(&entry->str3C);
        }

        static bool MapEntryIsTRO(const MapEntry* entry)
        {
            if (!entry)
                return false;
            return BzrStringStartsWithI(&entry->name, "evolve_");
        }

        static bool MapEntryMatchesPlayers(const MapEntry* entry, int count)
        {
            if (!entry || count <= 0)
                return false;
            int minP = entry->field1C;
            int maxP = entry->field18;
            if (minP > maxP)
                std::swap(minP, maxP);
            if (minP <= 0 || maxP <= 0)
                return false;
            return minP <= count && maxP >= count;
        }

        static void MapEntryInit(MapEntry* entry)
        {
            if (!entry)
                return;
            std::memset(entry, 0, sizeof(*entry));
            BzrStringInitEmpty(&entry->name);
            BzrStringInitEmpty(&entry->str20);
            BzrStringInitEmpty(&entry->str3C);
            BzrStringInitEmpty(&entry->str54);
            BzrStringInitEmpty(&entry->str6C);
            BzrStringInitEmpty(&entry->str84);
            BzrStringInitEmpty(&entry->str9C);
        }

        static void MapEntryCopy(MapEntry* dst, const MapEntry* src)
        {
            if (!dst || !src)
                return;
            MapEntryInit(dst);
            BzrStringCopy(&dst->name, &src->name);
            dst->field18 = src->field18;
            dst->field1C = src->field1C;
            BzrStringCopy(&dst->str20, &src->str20);
            dst->type = src->type;
            BzrStringCopy(&dst->str3C, &src->str3C);
            BzrStringCopy(&dst->str54, &src->str54);
            BzrStringCopy(&dst->str6C, &src->str6C);
            BzrStringCopy(&dst->str84, &src->str84);
            BzrStringCopy(&dst->str9C, &src->str9C);
        }

        static void MapEntryDestroy(MapEntry* entry)
        {
            if (!entry)
                return;
            BzrStringFree(&entry->name);
            BzrStringFree(&entry->str20);
            BzrStringFree(&entry->str3C);
            BzrStringFree(&entry->str54);
            BzrStringFree(&entry->str6C);
            BzrStringFree(&entry->str84);
            BzrStringFree(&entry->str9C);
            operator delete(entry);
        }

        static void MapRingClear(MapRing* ring)
        {
            if (!ring)
                return;
            if (ring->entries)
            {
                for (uint32_t i = 0; i < ring->capacity; ++i)
                {
                    if (ring->entries[i])
                    {
                        MapEntryDestroy(reinterpret_cast<MapEntry*>(ring->entries[i]));
                        ring->entries[i] = nullptr;
                    }
                }
                std::free(ring->entries);
            }
            ring->entries = nullptr;
            ring->capacity = 0;
            ring->head = 0;
            ring->count = 0;
        }

        static void MapRingEnsure(MapRing* ring, uint32_t needed)
        {
            if (!ring)
                return;
            if (ring->capacity > ring->count + needed + 1)
                return;

            uint32_t new_cap = ring->capacity ? ring->capacity : 1;
            while (new_cap == ring->capacity || new_cap < 8)
                new_cap <<= 1;
            while (new_cap <= ring->count + needed + 1)
                new_cap <<= 1;

            void** mem = static_cast<void**>(std::calloc(new_cap, sizeof(void*)));
            if (!mem)
                return;

            for (uint32_t i = 0; i < ring->count; ++i)
            {
                uint32_t idx = ring->capacity ? ((ring->head + i) & (ring->capacity - 1)) : 0;
                mem[i] = ring->entries ? ring->entries[idx] : nullptr;
            }

            if (ring->entries)
                std::free(ring->entries);

            ring->entries = mem;
            ring->capacity = new_cap;
            ring->head = 0;
        }

        static void MapRingPush(MapRing* ring, const MapEntry* entry)
        {
            if (!ring || !entry)
                return;
            MapRingEnsure(ring, 1);
            if (!ring->entries || ring->capacity == 0)
                return;
            ring->head &= (ring->capacity - 1);
            const uint32_t idx = (ring->head + ring->count) & (ring->capacity - 1);
            if (!ring->entries[idx])
            {
                ring->entries[idx] = operator new(sizeof(MapEntry));
            }
            MapEntryCopy(reinterpret_cast<MapEntry*>(ring->entries[idx]), entry);
            ring->count += 1;
        }

        static uint32_t ComputeMapFilterFlags()
        {
            MapManager* mgr = GetMapManager();
            if (!mgr || !mgr->entries || mgr->capacity == 0)
                return 0;

            uint32_t flags = 0;
            for (uint32_t i = 0; i < mgr->count; ++i)
            {
                uint32_t idx = (mgr->head + i) & (mgr->capacity - 1);
                MapEntry* entry = mgr->entries[idx];
                if (!entry)
                    continue;

                if (MapEntryHasTag(entry, "Favorites"))
                    flags |= 0x4;
                if (MapEntryHasTag(entry, "Special"))
                    flags |= 0x2;
                if (MapEntryIsStock(entry) || !MapEntryIsStock(entry))
                    flags |= 0x1;

                switch (entry->type)
                {
                    case 'M': flags |= 0x20; break;
                    case 'A': flags |= 0x40; break;
                    case 'X': flags |= 0x80; break;
                    default: break;
                }

                for (int players = 5; players <= 15; ++players)
                {
                    if (MapEntryMatchesPlayers(entry, players))
                    {
                        flags |= (0x100u << (players - 5));
                    }
                }
            }
            return flags;
        }

        static const char* LocalizeMaybe(const char* section, const char* key, const char* fallback)
        {
            if (g_BzrFn_Localize)
            {
                const char* txt = g_BzrFn_Localize(section, key);
                if (txt && *txt)
                    return txt;
            }
            return fallback;
        }
    }

    void __cdecl MapFilters1Rebuild(void* listPtr)
    {
        if (!listPtr)
            return;

        auto* list = reinterpret_cast<MapFilterList*>(listPtr);
        MapFilterListClear(list);

        const uint32_t flags = ComputeMapFilterFlags();
        if (EnvFlagEnabled("OPENSHIM_TRACE_MAP_REFRESH") ||
            EnvFlagEnabled("OPENSHIM_TRACE_STEAM_MAP_REFRESH"))
        {
            Log(L"[MAPTRACE] MapFilters1Rebuild list=0x%08X flags=0x%08X\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(listPtr)),
                flags);
        }

        if (flags & 0x4)
        {
            MapFilterListPush(list, "Favorites", "Favorites");
            MapFilterListPush(list, "", "");
        }

        MapFilterListPush(list, "All Maps",
            LocalizeMaybe("filters", "all_maps", "All Maps"));

        if (flags & 0x1)
        {
            MapFilterListPush(list, "Stock",
                LocalizeMaybe("filters", "stock", "Stock"));
        }

        MapFilterListPush(list, "Stock_BZ98", "Stock (BZ98)");
        MapFilterListPush(list, "Stock_TRO", "Stock (TRO)");

        if (flags & 0x1)
        {
            MapFilterListPush(list, "Workshop",
                LocalizeMaybe("filters", "workshop", "Workshop"));
        }

        MapFilterListPush(list, "", "");

        MapFilterListPush(list, "Strategy",
            LocalizeMaybe("filters", "strategy", "Strategy"));

        if (flags & 0x20)
            MapFilterListPush(list, "Mission MPI", "Mission MPI");

        MapFilterListPush(list, "Death Match",
            LocalizeMaybe("filters", "death_match", "Death Match"));

        if (flags & 0x40)
            MapFilterListPush(list, "Action MPI", "Action MPI");

        MapFilterListPush(list, "KOTH",
            LocalizeMaybe("filters", "koth", "KOTH"));

        if (flags & 0x2)
            MapFilterListPush(list, "Special", "Special");

        MapFilterListPush(list, "", "");
        MapFilterListPush(list, "", "");

        MapFilterListPush(list, "2 Players",
            LocalizeMaybe("filters", "2_players", "2 Players"));
        MapFilterListPush(list, "3 Players",
            LocalizeMaybe("filters", "3_players", "3 Players"));
        MapFilterListPush(list, "4 Players",
            LocalizeMaybe("filters", "4_players", "4 Players"));

        const struct { int players; uint32_t bit; } kPlayerFlags[] =
        {
            { 5, 0x100 }, { 6, 0x200 }, { 7, 0x400 }, { 8, 0x800 },
            { 9, 0x1000 }, { 10, 0x2000 }, { 11, 0x4000 }, { 12, 0x8000 },
            { 13, 0x10000 }, { 14, 0x20000 }, { 15, 0x40000 },
        };

        for (const auto& entry : kPlayerFlags)
        {
            if (flags & entry.bit)
            {
                char label[16] = {};
                std::snprintf(label, sizeof(label), "%d Players", entry.players);
                MapFilterListPush(list, label, label);
            }
        }

        if (static_cast<int32_t>(flags) < 0)
        {
            MapFilterListPush(list, "", "");
            MapFilterListPush(list, "Other", "Other");
        }
    }

    void __cdecl MapFilters2Filter(void* listPtr, BzrString* filter)
    {
        if (!listPtr || !filter)
            return;

        auto* ring = reinterpret_cast<MapRing*>(listPtr);
        MapRingClear(ring);

        const char* filterStr = BzrStringData(filter);
        const uint32_t filterLen = filter->size;
        if (!filterStr || filterLen == 0)
            return;
        if (EnvFlagEnabled("OPENSHIM_TRACE_MAP_REFRESH") ||
            EnvFlagEnabled("OPENSHIM_TRACE_STEAM_MAP_REFRESH"))
        {
            Log(L"[MAPTRACE] MapFilters2Filter list=0x%08X filter=%hs len=%u\n",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(listPtr)),
                filterStr,
                filterLen);
        }

        MapManager* mgr = GetMapManager();
        if (!mgr || !mgr->entries || mgr->capacity == 0)
            return;

        for (uint32_t i = 0; i < mgr->count; ++i)
        {
            uint32_t idx = (mgr->head + i) & (mgr->capacity - 1);
            const MapEntry* entry = mgr->entries[idx];
            if (!entry)
                continue;

            bool include = false;
            if (BzrStringEqualsCStr(filter, "All Maps"))
                include = true;
            else if (BzrStringEqualsCStr(filter, "Stock"))
                include = MapEntryIsStock(entry);
            else if (BzrStringEqualsCStr(filter, "Stock_BZ98"))
                include = MapEntryIsStock(entry) && !MapEntryIsTRO(entry);
            else if (BzrStringEqualsCStr(filter, "Stock_TRO"))
                include = MapEntryIsStock(entry) && MapEntryIsTRO(entry);
            else if (BzrStringEqualsCStr(filter, "Workshop"))
                include = !MapEntryIsStock(entry);
            else if (BzrStringEqualsCStr(filter, "Strategy"))
                include = entry->type == 'S';
            else if (BzrStringEqualsCStr(filter, "Mission MPI"))
                include = entry->type == 'M';
            else if (BzrStringEqualsCStr(filter, "Death Match"))
                include = entry->type == 'D';
            else if (BzrStringEqualsCStr(filter, "Action MPI"))
                include = entry->type == 'A';
            else if (BzrStringEqualsCStr(filter, "KOTH"))
                include = entry->type == 'K';
            else if (BzrStringEqualsCStr(filter, "Special"))
                include = MapEntryHasTag(entry, "Special");
            else if (BzrStringEqualsCStr(filter, "Favorites"))
                include = MapEntryHasTag(entry, "Favorites");
            else if (BzrStringEqualsCStr(filter, "Other"))
                include = entry->type == 'X';
            else if (filterLen >= 8 && std::strstr(filterStr, "Players"))
            {
                const int count = std::atoi(filterStr);
                include = MapEntryMatchesPlayers(entry, count);
            }
            else
            {
                include = MapEntryHasTag(entry, filterStr);
            }

            if (include)
                MapRingPush(ring, entry);
        }
    }
}
