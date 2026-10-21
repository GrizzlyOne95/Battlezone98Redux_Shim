// vehicle_list_mod_fix.cpp
// BZR Open Shim - vehicle list mod fix: the asset debug-exception cache,
// the guarded vehicle list load and the ModFix 2/4 entry points that keep
// modded vehicle lists selectable, split out of bzr_hooks.cpp.
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
#include "map_folder_items.h"
#include "odf_item_hooks.h"
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
    // ---------------------------------------------------------------------
    // Global state used by hooks/trampolines
    // ---------------------------------------------------------------------
    void* g_VehicleListContext = nullptr;

    void* g_VehicleListParam   = nullptr;

    namespace Hooks
    {
        constexpr DWORD kDbgPrintExceptionAnsi = 0x40010006u;

        constexpr DWORD kDbgPrintExceptionWide = 0x4001000Au;

        constexpr DWORD kVehicleAssetRetryDelayMs = 1500u;

        constexpr size_t kVehicleAssetExceptionCacheSize = 8;

        static VehicleAssetExceptionCacheEntry g_VehicleAssetExceptionCache[kVehicleAssetExceptionCacheSize] = {};

        static int FilterVehicleAssetDebugException(
            unsigned int code,
            const char* stage,
            const BzrString* assetName)
        {
            if (code == kDbgPrintExceptionAnsi || code == kDbgPrintExceptionWide)
            {
                Log(L"[VEHICLE] Swallowed debug-print exception during %hs for asset '%hs' (code=0x%08X)\n",
                    stage ? stage : "unknown",
                    assetName ? BzrStringData(assetName) : "",
                    code);
                return EXCEPTION_EXECUTE_HANDLER;
            }

            return EXCEPTION_CONTINUE_SEARCH;
        }

        static bool CopyVehicleAssetName(
            const BzrString* assetName,
            char (&buffer)[64])
        {
            buffer[0] = '\0';
            if (!assetName)
                return false;

            const char* name = BzrStringData(assetName);
            if (!name || !name[0])
                return false;

            strncpy_s(buffer, name, _TRUNCATE);
            return buffer[0] != '\0';
        }

        static bool TickIsBefore(DWORD lhs, DWORD rhs)
        {
            return static_cast<long>(lhs - rhs) < 0;
        }

        static VehicleAssetExceptionCacheEntry* FindVehicleAssetExceptionEntry(const char* assetName)
        {
            if (!assetName || !assetName[0])
                return nullptr;

            for (auto& entry : g_VehicleAssetExceptionCache)
            {
                if (entry.assetName[0] && _stricmp(entry.assetName, assetName) == 0)
                    return &entry;
            }

            return nullptr;
        }

        static VehicleAssetExceptionCacheEntry* GetVehicleAssetExceptionSlot()
        {
            VehicleAssetExceptionCacheEntry* oldest = &g_VehicleAssetExceptionCache[0];
            for (auto& entry : g_VehicleAssetExceptionCache)
            {
                if (!entry.assetName[0])
                    return &entry;
                if (TickIsBefore(entry.suppressUntil, oldest->suppressUntil))
                    oldest = &entry;
            }
            return oldest;
        }



        static void RememberVehicleAssetDebugException(const BzrString* assetName)
        {
            char assetNameBuffer[64] = {};
            if (!CopyVehicleAssetName(assetName, assetNameBuffer))
                return;

            VehicleAssetExceptionCacheEntry* entry = FindVehicleAssetExceptionEntry(assetNameBuffer);
            if (!entry)
                entry = GetVehicleAssetExceptionSlot();
            if (!entry)
                return;

            strncpy_s(entry->assetName, assetNameBuffer, _TRUNCATE);
            entry->suppressUntil = GetTickCount() + kVehicleAssetRetryDelayMs;
            entry->lastSkipLogTick = 0;
        }

        static bool ShouldSuppressVehicleAssetLoad(const BzrString* assetName, const char* stage)
        {
            char assetNameBuffer[64] = {};
            if (!CopyVehicleAssetName(assetName, assetNameBuffer))
                return false;

            VehicleAssetExceptionCacheEntry* entry = FindVehicleAssetExceptionEntry(assetNameBuffer);
            if (!entry)
                return false;

            const DWORD now = GetTickCount();
            if (!TickIsBefore(now, entry->suppressUntil))
                return false;

            if (entry->lastSkipLogTick == 0 || !TickIsBefore(now, entry->lastSkipLogTick + 500u))
            {
                Log(L"[VEHICLE] Suppressed retry during %hs for recent-miss asset '%hs'\n",
                    stage ? stage : "unknown",
                    assetNameBuffer);
                entry->lastSkipLogTick = now;
            }

            return true;
        }

        static void CallVehicleListLoadSafely(void* mgrThis, BzrString* assetName, const char* stage)
        {
            if (!g_BzrFn_VehicleListLoad || !mgrThis || !assetName)
                return;

            if (ShouldSuppressVehicleAssetLoad(assetName, stage))
                return;

            __try
            {
                g_BzrFn_VehicleListLoad(mgrThis, assetName);
            }
            __except (FilterVehicleAssetDebugException(GetExceptionCode(), stage, assetName))
            {
                RememberVehicleAssetDebugException(assetName);
            }
        }
    }

    using namespace Hooks;

    // ---------------------------------------------------------------------
    // Map-folder gap items for the waiting room (see map_folder_items.h)
    // ---------------------------------------------------------------------
    using FnVxtIndexCheck = void*(__cdecl*)(const char* name);
    static FnVxtIndexCheck g_OrigVxtIndexCheck = nullptr;

    // Stands in for an index record. The loader only tests the result for
    // zero, but a real-looking record is safer than the value 1.
    static uint8_t g_VxtIndexStandIn[0x20] = {};

    static bool EngineIndexHas(const char* name)
    {
        if (!g_OrigVxtIndexCheck || !name)
            return true; // unknown: never claim a gap
        __try
        {
            return g_OrigVxtIndexCheck(name) != nullptr;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return true;
        }
    }

    // Replaces the loader's own `call FUN_00481F10`. Stock answers first; a
    // miss is turned into a hit only for a file the map-folder store will
    // then serve through the item detours.
    static void* __cdecl VxtIndexCheckIntercept(const char* name)
    {
        void* hit = g_OrigVxtIndexCheck ? g_OrigVxtIndexCheck(name) : nullptr;
        if (hit)
            return hit;
        if (OdfItemHooksInstalled() && MapFolderItems::CanServe(name))
            return g_VxtIndexStandIn;
        return nullptr;
    }

    static void InstallVxtIndexCheckOnce()
    {
        static bool s_tried = false;
        if (s_tried)
            return;
        s_tried = true;

        const uint32_t site = HookEngine::ResolveNamedAddress("VehicleListLoad::IndexCheckCall");
        const uint32_t loader = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_VehicleListLoad));
        if (site == 0 || loader == 0 || site < loader || site > loader + 0x80)
        {
            Log(L"[VXT] index-check call not identified (site=0x%08X loader=0x%08X); map-folder lists off\n",
                site, loader);
            return;
        }

        // Identity: the call must reach the cdecl index thunk, not merely
        // sit inside the loader.
        void* target = HookEngine::ResolveRelCallTarget(site);
        static const uint8_t kThunk[] = { 0x55, 0x8B, 0xEC, 0x51, 0x8B, 0x45, 0x08, 0x50, 0xE8 };
        uint8_t thunk[sizeof(kThunk)] = {};
        if (!target ||
            !HookEngine::ReadMemory(static_cast<uint32_t>(reinterpret_cast<uintptr_t>(target)), thunk, sizeof(thunk)) ||
            std::memcmp(thunk, kThunk, sizeof(kThunk)) != 0)
        {
            Log(L"[VXT] index-check call 0x%08X does not reach the index thunk (target=%p); map-folder lists off\n",
                site, target);
            return;
        }

        uint8_t original[5] = {};
        if (!HookEngine::ReadMemory(site, original, sizeof(original)) || original[0] != 0xE8)
            return;
        g_OrigVxtIndexCheck = reinterpret_cast<FnVxtIndexCheck>(target);

        HookEngine::PatchDef def;
        def.address = site;
        def.type = HookEngine::PatchType::REL32;
        def.name = "VehicleListLoad::IndexCheckCall";
        def.verified = true;
        def.expected_original.assign(original, original + sizeof(original));
        const int32_t rel =
            static_cast<int32_t>(reinterpret_cast<uintptr_t>(&VxtIndexCheckIntercept)) -
            static_cast<int32_t>(site + 5);
        def.payload.assign(5, 0);
        def.payload[0] = 0xE8;
        std::memcpy(def.payload.data() + 1, &rel, sizeof(rel));
        if (!HookEngine::ApplyPatch(def))
        {
            g_OrigVxtIndexCheck = nullptr;
            Log(L"[VXT] could not rewrite the index-check call 0x%08X; map-folder lists off\n", site);
            return;
        }
        MapFolderItems::SetIndexCheck(&EngineIndexHas);
        Log(L"[VXT] index-check call 0x%08X -> map-folder gap check (thunk %p)\n", site, target);
    }

    // Points the store at the selected map's own folder when the index lacks
    // its .vxt, and clears it otherwise. Folder lookups are cached per map:
    // the lobby re-selects on every data change.
    static void PrepareMapFolderItems(const std::string& base)
    {
        InstallVxtIndexCheckOnce();
        if (!g_OrigVxtIndexCheck || !OdfItemHooksInstalled() || base.empty())
        {
            MapFolderItems::SetFolder({});
            return;
        }
        if (EngineIndexHas((base + ".vxt").c_str()))
        {
            MapFolderItems::SetFolder({});
            return;
        }

        static std::unordered_map<std::string, std::filesystem::path> s_folders;
        std::string key = base;
        for (char& c : key)
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        auto it = s_folders.find(key);
        if (it == s_folders.end())
        {
            std::filesystem::path folder;
            try
            {
                const auto gameDir = Assets::ResolveAssetRuntimeEnvironment().gameDir;
                std::vector<std::filesystem::path> roots;
                roots.push_back(gameDir / "addon");
                for (auto& root : Assets::GetContentRootCandidates(gameDir))
                    roots.push_back(std::move(root));
                folder = MapFolderItems::FindMapFolder(roots, base);
            }
            catch (...)
            {
                folder.clear();
            }
            if (folder.empty())
                Log(L"[VXT] '%hs.vxt' is not indexed and no map folder holds it with '%hs.bzn'\n",
                    base.c_str(), base.c_str());
            else
                Log(L"[VXT] '%hs.vxt' is not indexed; reading it from '%ls'\n",
                    base.c_str(), folder.wstring().c_str());
            it = s_folders.emplace(key, std::move(folder)).first;
        }
        MapFolderItems::SetFolder(it->second);
    }

    static uint8_t* VehicleEntryAt(void* context, uint32_t index)
    {
        if (!context) return nullptr;
        auto table = *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(context) + 0x18);
        if (!table) return nullptr;
        uint32_t bucket = *reinterpret_cast<uint32_t*>(table + 0x0C);
        uint32_t mask = *reinterpret_cast<uint32_t*>(table + 0x08);
        if (mask == 0) return nullptr;
        mask -= 1;
        uint32_t base = *reinterpret_cast<uint32_t*>(table + 0x04);
        return *reinterpret_cast<uint8_t**>(base + ((bucket + index) & mask) * 4);
    }

    static void VehicleListModFix_Select(const BzrString* name)
    {
        if (!g_VehicleListContext || !name)
            return;

        auto ctx = reinterpret_cast<uint8_t*>(g_VehicleListContext);
        *reinterpret_cast<int*>(ctx + 0x38) = -1;

        uint8_t* match = nullptr;
        auto table = *reinterpret_cast<uint8_t**>(ctx + 0x18);
        if (table)
        {
            uint32_t count = *reinterpret_cast<uint32_t*>(table + 0x10);
            if (count)
            {
                uint32_t bucket = *reinterpret_cast<uint32_t*>(table + 0x0C);
                uint32_t mask = *reinterpret_cast<uint32_t*>(table + 0x08);
                uint32_t base = *reinterpret_cast<uint32_t*>(table + 0x04);
                if (mask)
                {
                    mask -= 1;
                    for (uint32_t i = 0; i < count; ++i)
                    {
                        auto entry = *reinterpret_cast<uint8_t**>(base + ((bucket + i) & mask) * 4);
                        if (!entry)
                            continue;
                        auto entryStr = reinterpret_cast<const BzrString*>(entry);
                        if (BzrStringEquals(entryStr, name))
                        {
                            match = entry;
                            *reinterpret_cast<uint32_t*>(ctx + 0x38) = i;
                            break;
                        }
                    }
                }
            }
        }

        BzrString title;
        BzrString subtitle;
        BzrStringInitEmpty(&title);
        BzrStringInitEmpty(&subtitle);
        if (match)
        {
            BzrStringCopy(&title, reinterpret_cast<const BzrString*>(match));
            BzrStringCopy(&subtitle, reinterpret_cast<const BzrString*>(match + 0x3C));
        }

        void* listThis = (g_BzrPtr_945478 && *g_BzrPtr_945478) ? *g_BzrPtr_945478 : nullptr;
        if (g_BzrFn_VehicleListSet && listThis)
            g_BzrFn_VehicleListSet(listThis, title, subtitle);

        // Stock (0x007A3E60) swaps the map's 4-char extension for ".vxt":
        // "bzpmap.bzn" -> "bzpmap.vxt". Appending instead asked for
        // "bzpmap.bzn.vxt", which never exists, so the load fell back to
        // netveh.odf and BZP's faction-only list became stock ships. Stock
        // also skips the load for a name too short to carry an extension.
        BzrString file;
        BzrStringInitEmpty(&file);
        const bool hasExtension = name->size >= 4;
        if (hasExtension)
        {
            BzrStringAssign(&file, BzrStringData(name), name->size - 4);
            BzrStringAppend(&file, ".vxt", 4);
        }

        void* mgrThis = (g_BzrPtr_94548C && *g_BzrPtr_94548C) ? *g_BzrPtr_94548C : nullptr;
        if (mgrThis && hasExtension)
        {
            PrepareMapFolderItems(std::string(BzrStringData(name), name->size - 4));

            // The lobby re-selects on every data change; log each new file once.
            static char s_lastLogged[64] = {};
            const char* fileName = BzrStringData(&file);
            if (std::strncmp(s_lastLogged, fileName, sizeof(s_lastLogged) - 1) != 0)
            {
                strncpy_s(s_lastLogged, fileName, _TRUNCATE);
                Log(L"[VEHICLE] Waiting-room list for '%hs' loads '%hs'\n",
                    BzrStringData(name), fileName);
            }
            CallVehicleListLoadSafely(mgrThis, &file, "VehicleListModFix_Select");
        }

        if (g_BzrFn_VehicleListRefresh1 && g_VehicleListContext)
            g_BzrFn_VehicleListRefresh1(g_VehicleListContext);
        if (g_BzrFn_VehicleListRefresh2 && g_VehicleListContext)
            g_BzrFn_VehicleListRefresh2(g_VehicleListContext);
        if (g_BzrFn_VehicleListFinalize && listThis)
            g_BzrFn_VehicleListFinalize(listThis);

        BzrStringFree(&title);
        BzrStringFree(&subtitle);
        BzrStringFree(&file);
    }

    void __fastcall VehicleListModFix2(void* thisPtr, void* /*edx*/, BzrString* name)
    {
        g_VehicleListContext = thisPtr;
        VehicleListModFix_Select(name);
    }

    void VehicleListModFix4Helper()
    {
        if (!g_BzrPtr_94555C || !*g_BzrPtr_94555C)
            return;

        auto root = reinterpret_cast<uint8_t*>(*g_BzrPtr_94555C);
        g_VehicleListContext = *reinterpret_cast<void**>(root + 0x1C8);
        if (!g_VehicleListContext)
            return;

        auto ctx = reinterpret_cast<uint8_t*>(g_VehicleListContext);
        int index = *reinterpret_cast<int*>(ctx + 0x38);
        BzrString title;
        BzrString subtitle;
        BzrStringInitEmpty(&title);
        BzrStringInitEmpty(&subtitle);

        if (index >= 0)
        {
            auto entry = VehicleEntryAt(g_VehicleListContext, static_cast<uint32_t>(index));
            if (entry)
            {
                BzrStringCopy(&title, reinterpret_cast<const BzrString*>(entry));
                BzrStringCopy(&subtitle, reinterpret_cast<const BzrString*>(entry + 0x3C));
            }
        }

        void* listThis = (g_BzrPtr_945478 && *g_BzrPtr_945478) ? *g_BzrPtr_945478 : nullptr;
        if (g_BzrFn_VehicleListSet && listThis)
            g_BzrFn_VehicleListSet(listThis, title, subtitle);

        void* mgrThis = (g_BzrPtr_94548C && *g_BzrPtr_94548C) ? *g_BzrPtr_94548C : nullptr;
        if (mgrThis && g_VehicleListParam)
        {
            MapFolderItems::SetFolder({}); // netveh is stock; no map folder applies
            CallVehicleListLoadSafely(
                mgrThis,
                reinterpret_cast<BzrString*>(g_VehicleListParam),
                "VehicleListModFix4Helper");
        }

        if (g_BzrFn_VehicleListFinalize && listThis)
            g_BzrFn_VehicleListFinalize(listThis);

        BzrStringFree(&title);
        BzrStringFree(&subtitle);
    }
}
