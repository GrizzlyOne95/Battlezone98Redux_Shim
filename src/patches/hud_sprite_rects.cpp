// hud_sprite_rects.cpp
// BZR Open Shim - HUD sprite rect table: discovery with UV-sample validation,
// per-sprite rect/visibility mutation and restore, and its bridge accessors,
// split out of bzr_hooks.cpp.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "hook_engine.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace BZROpenShim
{
    namespace Hooks
    {
        constexpr uintptr_t kHudSpriteNameCountAddr = 0x00920F00;

        constexpr uintptr_t kHudSpriteNameTableAddr = 0x00920F08;

        constexpr size_t kHudSpriteNameEntrySize = 0x20;

        // The live sprite rect records are a static exe-image array, NOT a
        // heap allocation: the registration code (0x0068B107) and the
        // renderer's per-draw accessors (width 0x0068F090, height 0x0068F0C0,
        // UV block via base-8 at 0x0068F0F0) all index
        // `0x025F8F40 + id*0x24` directly. Layout: int16 x,y,w,h at +0,
        // float u0,v0,u1,v1 at +8, flags at +0x18, texture refs at
        // +0x1C/+0x20. (An earlier revision assumed heap-resident 0x30-byte
        // runtime records and scanned process memory for them; the scan was
        // later restricted to MEM_PRIVATE regions, which can never contain
        // this MEM_IMAGE table, so discovery failed every session.)
        constexpr uintptr_t kHudSpriteRectTableAddr = 0x025F8F40;

        constexpr uint32_t kHudSpriteMaxReasonableCount = 4096;

        // Kept short so a hide request issued before the mission HUD exists
        // converges quickly once the rect records are created; the scan is
        // bounded to MEM_PRIVATE regions <= 128 MB so a retry is cheap.
        constexpr ULONGLONG kHudSpriteRectDiscoveryRetryMs = 4000;

        constexpr ULONGLONG kHudSpriteFallbackDiscoveryRetryMs = 5000;

        struct HudSpriteKnownSample
        {
            const char* name = nullptr;
            float u0 = 0.0f;
            float v0 = 0.0f;
            float u1 = 0.0f;
            float v1 = 0.0f;
            int id = 0;
        };

        constexpr ULONGLONG kHudSpriteDiscoveryBackoffCapMs = 60000;

        static int16_t ClampHudSpriteCoord(int value)
        {
            if (value < static_cast<int>(SHRT_MIN))
                return SHRT_MIN;
            if (value > static_cast<int>(SHRT_MAX))
                return SHRT_MAX;
            return static_cast<int16_t>(value);
        }

        bool IsReadableDataProtect(DWORD protect)
        {
            if ((protect & PAGE_GUARD) != 0 || (protect & PAGE_NOACCESS) != 0)
                return false;

            switch (protect & 0xFFu)
            {
            case PAGE_READONLY:
            case PAGE_READWRITE:
            case PAGE_WRITECOPY:
            case PAGE_EXECUTE_READ:
            case PAGE_EXECUTE_READWRITE:
            case PAGE_EXECUTE_WRITECOPY:
                return true;
            default:
                return false;
            }
        }

        static bool TryReadHudSpriteNameCount(uint32_t& outCount)
        {
            __try
            {
                const uint32_t count = *reinterpret_cast<const uint32_t*>(kHudSpriteNameCountAddr);
                if (count == 0 || count > kHudSpriteMaxReasonableCount)
                    return false;

                outCount = count;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            return false;
        }

        // POD-only SEH boundaries (no C++ unwinding objects). Keep these
        // separate from LookupHudSpriteId, which owns the std::string memo
        // cache: __try cannot live in a function that requires unwinding.
        // Returns false only if the scan faulted; outFound distinguishes a
        // clean "scanned but not present" from a hit.
        static bool SehScanHudSpriteTable(const char* name, uint32_t count, bool& outFound, int& outId)
        {
            outFound = false;
            outId = 0;
            __try
            {
                auto* table = reinterpret_cast<const char*>(kHudSpriteNameTableAddr);
                char entryName[kHudSpriteNameEntrySize + 1] = {};
                for (int index = static_cast<int>(count) - 1; index > 0; --index)
                {
                    const char* entry = table + (static_cast<size_t>(index) * kHudSpriteNameEntrySize);
                    std::memcpy(entryName, entry, kHudSpriteNameEntrySize);
                    entryName[kHudSpriteNameEntrySize] = '\0';
                    if (_stricmp(entryName, name) == 0)
                    {
                        outFound = true;
                        outId = index;
                        return true;
                    }
                }
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool SehCallHudSpriteLookupFn(const char* name, int& outId)
        {
            outId = 0;
            __try
            {
                outId = g_BzrFn_HudSpriteLookup(name);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static int LookupHudSpriteId(const char* name)
        {
            if (!name || !name[0])
                return 0;

            // The sprite table is static for the process lifetime and this
            // lookup runs every HUD refresh tick; memoize successful hits so
            // steady-state refreshes neither rescan the 900+ entry table nor
            // spam the log once per second.
            static std::mutex s_HudSpriteCacheMutex;
            static std::unordered_map<std::string, int> s_HudSpriteIdCache;
            {
                std::lock_guard<std::mutex> lock(s_HudSpriteCacheMutex);
                const auto it = s_HudSpriteIdCache.find(name);
                if (it != s_HudSpriteIdCache.end())
                    return it->second;
            }
            const auto rememberHit = [&](int id)
            {
                std::lock_guard<std::mutex> lock(s_HudSpriteCacheMutex);
                s_HudSpriteIdCache.emplace(name, id);
                return id;
            };

            uint32_t count = 0;
            bool lookupRaised = false;
            if (TryReadHudSpriteNameCount(count))
            {
                LogShimA(
                    LogLevel::Info,
                    "hudlookup",
                    "table search sprite=%s count=%u tableAddr=0x%08X",
                    name,
                    static_cast<unsigned>(count),
                    static_cast<unsigned>(kHudSpriteNameTableAddr));

                bool found = false;
                int index = 0;
                if (!SehScanHudSpriteTable(name, count, found, index))
                {
                    lookupRaised = true;
                    LogShimA(
                        LogLevel::Warn,
                        "hudlookup",
                        "table search sprite=%s raised exception",
                        name);
                }
                else if (found)
                {
                    LogShimA(
                        LogLevel::Info,
                        "hudlookup",
                        "table sprite=%s => id=%d (cached)",
                        name,
                        index);
                    return rememberHit(index);
                }
            }
            else
            {
                LogShimA(
                    LogLevel::Warn,
                    "hudlookup",
                    "table unavailable for sprite=%s countAddr=0x%08X tableAddr=0x%08X",
                    name,
                    static_cast<unsigned>(kHudSpriteNameCountAddr),
                    static_cast<unsigned>(kHudSpriteNameTableAddr));
            }

            // Retain the engine helper for unusual builds whose name table is
            // not exposed at the stock addresses. The direct table is safer for
            // bridge calls because it does not enter renderer-owned lookup code.
            if (g_BzrFn_HudSpriteLookup)
            {
                int id = 0;
                if (!SehCallHudSpriteLookupFn(name, id))
                {
                    lookupRaised = true;
                    LogShimA(
                        LogLevel::Warn,
                        "hudlookup",
                        "lookupFn=0x%p sprite=%s raised exception",
                        reinterpret_cast<void*>(g_BzrFn_HudSpriteLookup),
                        name);
                }
                else
                {
                    LogShimA(
                        LogLevel::Info,
                        "hudlookup",
                        "lookupFn=0x%p sprite=%s => id=%d (cached)",
                        reinterpret_cast<void*>(g_BzrFn_HudSpriteLookup),
                        name,
                        id);
                    if (id > 0)
                        return rememberHit(id);
                }
            }

            LogShimA(
                LogLevel::Warn,
                "hudlookup",
                "sprite=%s not found by any lookup path",
                name);
            // A miss against a readable table, with no lookup faulting, is as
            // final as a hit: the table is static for the process. Memoise it,
            // so the next refresh tick neither rescans the table nor logs the
            // same miss again. An unreadable table or a fault is retried.
            return (count > 0 && !lookupRaised) ? rememberHit(0) : 0;
        }

        static bool HudSpriteUvNearlyEqual(float a, float b)
        {
            return std::fabs(a - b) <= 0.0005f;
        }

        static bool ResolveHudSpriteKnownSamples(std::array<HudSpriteKnownSample, 6>& outSamples)
        {
            outSamples = {{
                {"scrap_panel", 660.0f / 1024.0f, 960.0f / 1024.0f, 840.0f / 1024.0f, 1024.0f / 1024.0f, 0},
                {"pilot_panel", 844.0f / 1024.0f, 960.0f / 1024.0f, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 0},
                {"sscrap_panel", 660.0f / 1024.0f, 960.0f / 1024.0f, 840.0f / 1024.0f, 1024.0f / 1024.0f, 0},
                {"spilot_panel", 844.0f / 1024.0f, 960.0f / 1024.0f, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 0},
                {"fscrap_panel", 660.0f / 1024.0f, 960.0f / 1024.0f, 840.0f / 1024.0f, 1024.0f / 1024.0f, 0},
                {"fpilot_panel", 844.0f / 1024.0f, 960.0f / 1024.0f, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 0},
            }};

            for (auto& sample : outSamples)
            {
                sample.id = LookupHudSpriteId(sample.name);
                if (sample.id <= 0)
                    return false;
            }

            return true;
        }

        static bool HudSpriteRecordMatches(const HudSpriteRectRecord& record, const HudSpriteKnownSample& sample)
        {
            return HudSpriteUvNearlyEqual(record.u0, sample.u0) &&
                   HudSpriteUvNearlyEqual(record.v0, sample.v0) &&
                   HudSpriteUvNearlyEqual(record.u1, sample.u1) &&
                   HudSpriteUvNearlyEqual(record.v1, sample.v1);
        }

        static bool ValidateHudSpriteRectTableBase(
            HudSpriteRectRecord* base,
            const std::array<HudSpriteKnownSample, 6>& samples)
        {
            if (!base)
                return false;

            __try
            {
                for (const auto& sample : samples)
                {
                    const HudSpriteRectRecord& record = base[sample.id];
                    if (!HudSpriteRecordMatches(record, sample))
                        return false;
                }

                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            return false;
        }

        static bool IsLikelyHudSpriteRectRegion(const MEMORY_BASIC_INFORMATION& mbi);

        static bool IsStockScrapPilotPanelName(const char* name)
        {
            if (!name || !name[0])
                return false;

            return _stricmp(name, "scrap_panel") == 0 ||
                   _stricmp(name, "pilot_panel") == 0 ||
                   _stricmp(name, "sscrap_panel") == 0 ||
                   _stricmp(name, "spilot_panel") == 0 ||
                   _stricmp(name, "fscrap_panel") == 0 ||
                   _stricmp(name, "fpilot_panel") == 0;
        }

        static bool HudSpriteRecordMatchesStockScrapOrPilotUv(const HudSpriteRectRecord& record)
        {
            const HudSpriteKnownSample scrapSample = {
                "scrap_panel",
                660.0f / 1024.0f,
                960.0f / 1024.0f,
                840.0f / 1024.0f,
                1024.0f / 1024.0f,
                0
            };
            const HudSpriteKnownSample pilotSample = {
                "pilot_panel",
                844.0f / 1024.0f,
                960.0f / 1024.0f,
                1024.0f / 1024.0f,
                1024.0f / 1024.0f,
                0
            };

            return HudSpriteRecordMatches(record, scrapSample) ||
                   HudSpriteRecordMatches(record, pilotSample);
        }

        static bool HudSpriteRecordLooksLikeLivePanelRecord(const HudSpriteRectRecord& record)
        {
            return record.w > 0 &&
                   record.h > 0 &&
                   record.w <= 4096 &&
                   record.h <= 4096 &&
                   record.x >= -64 &&
                   record.y >= -64 &&
                   record.x <= 8192 &&
                   record.y <= 8192;
        }

        static bool TryReadHudSpriteRectRecord(const HudSpriteRectRecord* candidate, HudSpriteRectRecord& record)
        {
            __try
            {
                record = *candidate;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        static bool DiscoverStockScrapPilotPanelRecordAddresses(std::vector<uintptr_t>& outAddresses)
        {
            outAddresses.clear();
            if (!g_HudSpriteCachedPanelAddresses.empty())
            {
                outAddresses = g_HudSpriteCachedPanelAddresses;
                return true;
            }

            const ULONGLONG now = GetTickCount64();
            const ULONGLONG fallbackRetryMs =
                g_HudSpriteFallbackDiscoveryBackoffMs > kHudSpriteFallbackDiscoveryRetryMs
                    ? g_HudSpriteFallbackDiscoveryBackoffMs
                    : kHudSpriteFallbackDiscoveryRetryMs;
            if (g_HudSpriteFallbackDiscoveryAttempted &&
                now - g_HudSpriteFallbackDiscoveryLastTick < fallbackRetryMs)
            {
                return false;
            }

            g_HudSpriteFallbackDiscoveryAttempted = true;
            g_HudSpriteFallbackDiscoveryLastTick = now;

            SYSTEM_INFO systemInfo = {};
            GetSystemInfo(&systemInfo);

            auto* cursor = static_cast<uint8_t*>(systemInfo.lpMinimumApplicationAddress);
            auto* maxAddress = static_cast<uint8_t*>(systemInfo.lpMaximumApplicationAddress);
            MEMORY_BASIC_INFORMATION mbi = {};
            while (cursor < maxAddress &&
                   VirtualQuery(cursor, &mbi, sizeof(mbi)) == sizeof(mbi))
            {
                auto* regionBase = static_cast<uint8_t*>(mbi.BaseAddress);
                auto* regionEnd = regionBase + mbi.RegionSize;
                cursor = regionEnd;

                if (!IsLikelyHudSpriteRectRegion(mbi))
                    continue;

                if (mbi.RegionSize < sizeof(HudSpriteRectRecord))
                    continue;

                for (size_t offset = 0; offset + sizeof(HudSpriteRectRecord) <= mbi.RegionSize; offset += sizeof(float))
                {
                    const auto* candidate = reinterpret_cast<const HudSpriteRectRecord*>(regionBase + offset);
                    HudSpriteRectRecord record = {};
                    if (!TryReadHudSpriteRectRecord(candidate, record))
                        continue;

                    if (!HudSpriteRecordLooksLikeLivePanelRecord(record))
                        continue;

                    if (!HudSpriteRecordMatchesStockScrapOrPilotUv(record))
                        continue;

                    const uintptr_t address = reinterpret_cast<uintptr_t>(candidate);
                    if (g_HudSpriteOriginalEntriesByAddress.find(address) == g_HudSpriteOriginalEntriesByAddress.end())
                        g_HudSpriteOriginalEntriesByAddress.emplace(address, record);
                    outAddresses.push_back(address);
                }
            }

            std::sort(outAddresses.begin(), outAddresses.end());
            outAddresses.erase(std::unique(outAddresses.begin(), outAddresses.end()), outAddresses.end());
            if (!outAddresses.empty())
            {
                g_HudSpriteCachedPanelAddresses = outAddresses;
                g_HudSpriteFallbackDiscoveryBackoffMs = 0;
                return true;
            }

            g_HudSpriteFallbackDiscoveryBackoffMs =
                g_HudSpriteFallbackDiscoveryBackoffMs == 0
                    ? kHudSpriteFallbackDiscoveryRetryMs * 2
                    : ((g_HudSpriteFallbackDiscoveryBackoffMs * 2 < kHudSpriteDiscoveryBackoffCapMs)
                           ? g_HudSpriteFallbackDiscoveryBackoffMs * 2
                           : kHudSpriteDiscoveryBackoffCapMs);
            return false;
        }

        static bool WriteHudSpriteRectRecordAtAddress(uintptr_t address, const HudSpriteRectRecord& record)
        {
            if (address == 0)
                return false;

            auto* entry = reinterpret_cast<void*>(address);
            DWORD oldProtect = 0;
            if (!VirtualProtect(entry, sizeof(record), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;

            *reinterpret_cast<HudSpriteRectRecord*>(entry) = record;
            FlushInstructionCache(GetCurrentProcess(), entry, sizeof(record));

            DWORD restoreProtect = 0;
            VirtualProtect(entry, sizeof(record), oldProtect, &restoreProtect);
            return true;
        }

        static bool SetStockScrapPilotPanelsVisibleByUv(bool visible)
        {
            if (!visible)
            {
                std::vector<uintptr_t> addresses;
                if (!DiscoverStockScrapPilotPanelRecordAddresses(addresses))
                {
                    LogShimA(LogLevel::Warn, "hudfallback", "no stock scrap/pilot panel records found");
                    return false;
                }

                bool anySucceeded = false;
                std::vector<uintptr_t> staleAddresses;
                for (uintptr_t address : addresses)
                {
                    auto originalIt = g_HudSpriteOriginalEntriesByAddress.find(address);
                    if (originalIt == g_HudSpriteOriginalEntriesByAddress.end())
                        continue;

                    // The engine can free and rebuild the HUD rect heap block
                    // (mission restart, resolution change). A cached address is
                    // only trustworthy while it still holds the stock panel
                    // UVs, which survive hiding because only w/h are zeroed.
                    HudSpriteRectRecord live = {};
                    if (!TryReadHudSpriteRectRecord(reinterpret_cast<const HudSpriteRectRecord*>(address), live) ||
                        !HudSpriteRecordMatchesStockScrapOrPilotUv(live))
                    {
                        staleAddresses.push_back(address);
                        continue;
                    }

                    HudSpriteRectRecord hidden = originalIt->second;
                    hidden.w = 0;
                    hidden.h = 0;
                    // The game can rebuild the HUD rect records after the
                    // initial layout application. Re-write the hidden rect on
                    // every hide request instead of treating the cached
                    // hidden set as proof that the live record is still zeroed.
                    if (WriteHudSpriteRectRecordAtAddress(address, hidden))
                    {
                        g_HudSpriteHiddenAddresses.insert(address);
                        anySucceeded = true;
                    }
                }

                if (!staleAddresses.empty())
                {
                    for (uintptr_t address : staleAddresses)
                    {
                        g_HudSpriteOriginalEntriesByAddress.erase(address);
                        g_HudSpriteHiddenAddresses.erase(address);
                    }
                    // Drop the cache so the next hide request rediscovers the
                    // rebuilt records instead of writing into freed memory.
                    g_HudSpriteCachedPanelAddresses.clear();
                    g_HudSpriteFallbackDiscoveryAttempted = false;
                    LogShimA(
                        LogLevel::Warn,
                        "hudfallback",
                        "dropped %zu stale panel record address(es); rediscovery scheduled",
                        staleAddresses.size());
                }

                LogShimA(
                    anySucceeded ? LogLevel::Info : LogLevel::Warn,
                    "hudfallback",
                    "hide stock scrap/pilot panels matches=%zu hidden=%zu",
                    addresses.size(),
                    g_HudSpriteHiddenAddresses.size());
                return anySucceeded;
            }

            if (g_HudSpriteHiddenAddresses.empty())
                return true;

            bool anySucceeded = false;
            std::vector<uintptr_t> staleRestoreAddresses;
            for (const auto& entry : g_HudSpriteOriginalEntriesByAddress)
            {
                if (g_HudSpriteHiddenAddresses.find(entry.first) == g_HudSpriteHiddenAddresses.end())
                    continue;

                // The hide path re-reads each cached address and requires the
                // stock panel UV block before it writes, because the engine can
                // free and rebuild the HUD rect heap (mission restart,
                // resolution change). The restore path must apply the same
                // evidence: after such a rebuild the cached address is freed or
                // reused, and VirtualProtect+write would then corrupt whatever
                // owns the memory now.
                HudSpriteRectRecord live = {};
                if (!TryReadHudSpriteRectRecord(
                        reinterpret_cast<const HudSpriteRectRecord*>(entry.first), live) ||
                    !HudSpriteRecordMatchesStockScrapOrPilotUv(live))
                {
                    staleRestoreAddresses.push_back(entry.first);
                    continue;
                }

                if (WriteHudSpriteRectRecordAtAddress(entry.first, entry.second))
                    anySucceeded = true;
            }

            if (!staleRestoreAddresses.empty())
            {
                for (uintptr_t address : staleRestoreAddresses)
                {
                    g_HudSpriteOriginalEntriesByAddress.erase(address);
                    g_HudSpriteHiddenAddresses.erase(address);
                }
                // Drop the cache so the next request rediscovers the rebuilt
                // records instead of writing into freed memory.
                g_HudSpriteCachedPanelAddresses.clear();
                g_HudSpriteFallbackDiscoveryAttempted = false;
                LogShimA(
                    LogLevel::Warn,
                    "hudfallback",
                    "restore dropped %zu stale panel record address(es); rediscovery scheduled",
                    staleRestoreAddresses.size());
            }

            if (anySucceeded)
                g_HudSpriteHiddenAddresses.clear();
            LogShimA(
                anySucceeded ? LogLevel::Info : LogLevel::Warn,
                "hudfallback",
                "restore stock scrap/pilot panels restored=%zu",
                anySucceeded ? g_HudSpriteOriginalEntriesByAddress.size() : 0u);
            return anySucceeded;
        }

        static void LogHudSpriteValidationSnapshot(
            const char* source,
            uintptr_t candidateBaseAddr,
            const std::array<HudSpriteKnownSample, 6>& samples)
        {
            static long s_budget = 6;
            if (InterlockedDecrement(&s_budget) < 0)
                return;

            char line[1024] = {};
            int written = _snprintf_s(
                line,
                _countof(line),
                _TRUNCATE,
                "%s base=0x%08X",
                source ? source : "candidate",
                static_cast<unsigned>(candidateBaseAddr));

            auto* base = reinterpret_cast<const HudSpriteRectRecord*>(candidateBaseAddr);
            for (const auto& sample : samples)
            {
                HudSpriteRectRecord record = {};
                bool readOk = false;
                __try
                {
                    record = base[sample.id];
                    readOk = true;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }

                // _snprintf_s returns -1 once it truncates; adding that would
                // step `written` backwards over the previous piece.
                if (written < 0)
                    break;

                int piece = 0;
                if (!readOk)
                {
                    piece = _snprintf_s(
                        line + written,
                        _countof(line) - written,
                        _TRUNCATE,
                        " | %s#%d=<fault>",
                        sample.name ? sample.name : "?",
                        sample.id);
                    written = piece < 0 ? -1 : written + piece;
                    continue;
                }

                piece = _snprintf_s(
                    line + written,
                    _countof(line) - written,
                    _TRUNCATE,
                    " | %s#%d=(%.3f,%.3f,%.3f,%.3f)",
                    sample.name ? sample.name : "?",
                    sample.id,
                    static_cast<double>(record.u0),
                    static_cast<double>(record.v0),
                    static_cast<double>(record.u1),
                    static_cast<double>(record.v1));
                written = piece < 0 ? -1 : written + piece;
            }

            LogShimA(LogLevel::Info, "huddiscover", "%s", line);
        }

        static bool IsLikelyHudSpriteRectRegion(const MEMORY_BASIC_INFORMATION& mbi)
        {
            if (mbi.State != MEM_COMMIT || !IsReadableDataProtect(mbi.Protect))
                return false;

            // The stock scrap/pilot rect records are runtime heap data
            // (MEM_PRIVATE). The previous code also returned true for MEM_MAPPED
            // and MEM_IMAGE, which forced the discovery scan to crawl every
            // mapped asset file and loaded module at 4-byte stride on the UI
            // thread -> multi-second freeze on the first legacy-layout toggle.
            // Restrict to private commits (matching the comment's original
            // intent) and skip pathologically large arenas that cannot hold the
            // small HUD rect table but would dominate the scan cost.
            if (mbi.Type != MEM_PRIVATE)
                return false;

            constexpr SIZE_T kMaxHudSpriteScanRegionBytes = 128ull * 1024ull * 1024ull;
            if (mbi.RegionSize > kMaxHudSpriteScanRegionBytes)
                return false;

            return true;
        }

        static bool DiscoverHudSpriteRectTableBase()
        {
            if (g_HudSpriteRectTableBase)
                return true;
            const ULONGLONG now = GetTickCount64();
            const ULONGLONG tableRetryMs =
                g_HudSpriteRectTableDiscoveryBackoffMs > kHudSpriteRectDiscoveryRetryMs
                    ? g_HudSpriteRectTableDiscoveryBackoffMs
                    : kHudSpriteRectDiscoveryRetryMs;
            if (g_HudSpriteRectTableDiscoveryAttempted &&
                now - g_HudSpriteRectTableDiscoveryLastTick < tableRetryMs)
                return false;

            g_HudSpriteRectTableDiscoveryAttempted = true;
            g_HudSpriteRectTableDiscoveryLastTick = now;

            std::array<HudSpriteKnownSample, 6> samples = {};
            if (!ResolveHudSpriteKnownSamples(samples))
            {
                Log(L"[HUD] Failed resolving stock HUD sprite ids needed for rect-table discovery\n");
                return false;
            }

            // The table is a static exe array (see kHudSpriteRectTableAddr):
            // no memory scan, just validate the known base by checking that
            // every panel record carries its stock atlas UVs (UVs survive our
            // hiding, which only zeroes w/h). Validation can fail briefly at
            // boot before the game registers the sprites; the retry/backoff
            // gate above keeps that cheap.
            auto* candidateBase = reinterpret_cast<HudSpriteRectRecord*>(kHudSpriteRectTableAddr);
            if (!ValidateHudSpriteRectTableBase(candidateBase, samples))
            {
                LogHudSpriteValidationSnapshot(
                    "static-fail",
                    kHudSpriteRectTableAddr,
                    samples);
                g_HudSpriteRectTableDiscoveryBackoffMs =
                    g_HudSpriteRectTableDiscoveryBackoffMs == 0
                        ? kHudSpriteRectDiscoveryRetryMs * 2
                        : ((g_HudSpriteRectTableDiscoveryBackoffMs * 2 < kHudSpriteDiscoveryBackoffCapMs)
                               ? g_HudSpriteRectTableDiscoveryBackoffMs * 2
                               : kHudSpriteDiscoveryBackoffCapMs);
                LogShimA(
                    LogLevel::Warn,
                    "huddiscover",
                    "static rect table at 0x%08X failed sample validation backoffMs=%llu",
                    static_cast<unsigned>(kHudSpriteRectTableAddr),
                    static_cast<unsigned long long>(g_HudSpriteRectTableDiscoveryBackoffMs));
                Log(L"[HUD] Static sprite rect table at 0x%08X failed validation\n",
                    static_cast<uint32_t>(kHudSpriteRectTableAddr));
                return false;
            }

            g_HudSpriteRectTableBase = candidateBase;
            g_HudSpriteOriginalEntries.clear();
            g_HudSpriteHiddenEntries.clear();
            g_HudSpriteRectTableDiscoveryBackoffMs = 0;
            Log(L"[HUD] Sprite rect table (static) base=0x%08X scrap=%d pilot=%d sscrap=%d spilot=%d fscrap=%d fpilot=%d\n",
                static_cast<uint32_t>(kHudSpriteRectTableAddr),
                samples[0].id,
                samples[1].id,
                samples[2].id,
                samples[3].id,
                samples[4].id,
                samples[5].id);
            return true;
        }

        static HudSpriteRectRecord* GetHudSpriteRectEntry(int spriteId)
        {
            if (spriteId <= 0)
                return nullptr;

            for (int attempt = 0; attempt < 2; ++attempt)
            {
                if (!g_HudSpriteRectTableBase && !DiscoverHudSpriteRectTableBase())
                    return nullptr;

                __try
                {
                    auto* entry = g_HudSpriteRectTableBase + spriteId;
                    volatile int16_t probe = entry->w;
                    (void)probe;
                    return entry;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    g_HudSpriteRectTableBase = nullptr;
                    g_HudSpriteRectTableDiscoveryAttempted = false;
                }
            }

            return nullptr;
        }

        static bool WriteHudSpriteRectEntry(int spriteId, const HudSpriteRectRecord& record)
        {
            auto* entry = GetHudSpriteRectEntry(spriteId);
            if (!entry)
                return false;

            DWORD oldProtect = 0;
            if (!VirtualProtect(entry, sizeof(record), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;

            *entry = record;
            FlushInstructionCache(GetCurrentProcess(), entry, sizeof(record));

            DWORD restoreProtect = 0;
            VirtualProtect(entry, sizeof(record), oldProtect, &restoreProtect);
            return true;
        }

        bool TryGetHudSpriteCurrentRecord(int spriteId, HudSpriteRectRecord& outRecord)
        {
            auto* entry = GetHudSpriteRectEntry(spriteId);
            if (!entry)
                return false;

            __try
            {
                outRecord = *entry;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            return false;
        }

        static bool ResolveHudSpriteForMutation(const char* name, int& outId, HudSpriteRectRecord& outCurrent)
        {
            outId = LookupHudSpriteId(name);
            if (outId <= 0)
            {
                Log(L"[HUD] Unknown sprite '%hs'\n", name ? name : "<null>");
                return false;
            }

            if (!TryGetHudSpriteCurrentRecord(outId, outCurrent))
            {
                Log(L"[HUD] Failed reading live rect entry for sprite '%hs' (id=%d)\n",
                    name ? name : "<null>",
                    outId);
                return false;
            }

            if (g_HudSpriteOriginalEntries.find(outId) == g_HudSpriteOriginalEntries.end())
                g_HudSpriteOriginalEntries.emplace(outId, outCurrent);
            return true;
        }
    }

    using namespace Hooks;

    static bool SetHudSpriteRectByTable(const char* name, int x, int y, int w, int h)
    {
        int spriteId = 0;
        HudSpriteRectRecord current = {};
        if (!ResolveHudSpriteForMutation(name, spriteId, current))
            return false;

        HudSpriteRectRecord updated = current;
        const auto hiddenIt = g_HudSpriteHiddenEntries.find(spriteId);
        if (hiddenIt != g_HudSpriteHiddenEntries.end())
            updated = hiddenIt->second;

        updated.x = ClampHudSpriteCoord(x);
        updated.y = ClampHudSpriteCoord(y);
        updated.w = ClampHudSpriteCoord(w);
        updated.h = ClampHudSpriteCoord(h);

        if (hiddenIt != g_HudSpriteHiddenEntries.end())
        {
            hiddenIt->second = updated;

            HudSpriteRectRecord hiddenRecord = updated;
            hiddenRecord.w = 0;
            hiddenRecord.h = 0;
            if (!WriteHudSpriteRectEntry(spriteId, hiddenRecord))
            {
                Log(L"[HUD] Failed updating hidden sprite '%hs' (id=%d)\n",
                    name ? name : "<null>",
                    spriteId);
                return false;
            }
        }
        else if (!WriteHudSpriteRectEntry(spriteId, updated))
        {
            Log(L"[HUD] Failed writing rect for sprite '%hs' (id=%d)\n",
                name ? name : "<null>",
                spriteId);
            return false;
        }

        Log(L"[HUD] Sprite rect %hs id=%d => (%d,%d,%d,%d)%s\n",
            name ? name : "<null>",
            spriteId,
            static_cast<int>(updated.x),
            static_cast<int>(updated.y),
            static_cast<int>(updated.w),
            static_cast<int>(updated.h),
            hiddenIt != g_HudSpriteHiddenEntries.end() ? " [hidden snapshot]" : "");
        return true;
    }

    static bool SetHudSpriteVisibleByTable(const char* name, bool visible)
    {
        const int spriteId = LookupHudSpriteId(name);
        if (spriteId <= 0)
        {
            Log(L"[HUD] Unknown sprite '%hs'\n", name ? name : "<null>");
            return false;
        }

        const auto hiddenIt = g_HudSpriteHiddenEntries.find(spriteId);
        if (!visible)
        {
            HudSpriteRectRecord current = {};
            if (!TryGetHudSpriteCurrentRecord(spriteId, current))
            {
                Log(L"[HUD] Failed reading live rect entry for sprite '%hs' (id=%d)\n",
                    name ? name : "<null>",
                    spriteId);
                return false;
            }

            const bool firstHide = hiddenIt == g_HudSpriteHiddenEntries.end();
            if (firstHide)
            {
                g_HudSpriteOriginalEntries.emplace(spriteId, current);
                g_HudSpriteHiddenEntries[spriteId] = current;
            }

            HudSpriteRectRecord hiddenRecord = g_HudSpriteHiddenEntries[spriteId];
            hiddenRecord.w = 0;
            hiddenRecord.h = 0;
            if (!WriteHudSpriteRectEntry(spriteId, hiddenRecord))
            {
                Log(L"[HUD] Failed hiding sprite '%hs' (id=%d)\n",
                    name ? name : "<null>",
                    spriteId);
                return false;
            }

            // The hide is re-enforced every HUD refresh tick; only log the
            // transition so steady state does not spam once per second.
            if (firstHide)
                Log(L"[HUD] Sprite hidden %hs id=%d\n", name ? name : "<null>", spriteId);
            return true;
        }

        if (hiddenIt != g_HudSpriteHiddenEntries.end())
        {
            if (!WriteHudSpriteRectEntry(spriteId, hiddenIt->second))
            {
                Log(L"[HUD] Failed restoring visible state for sprite '%hs' (id=%d)\n",
                    name ? name : "<null>",
                    spriteId);
                return false;
            }

            g_HudSpriteHiddenEntries.erase(spriteId);
            Log(L"[HUD] Sprite shown %hs id=%d\n", name ? name : "<null>", spriteId);
            return true;
        }

        // Recover records zeroed by an older bridge call that did not track
        // hidden state, while leaving an already-visible stock record alone.
        HudSpriteRectRecord current = {};
        const auto originalIt = g_HudSpriteOriginalEntries.find(spriteId);
        if (originalIt != g_HudSpriteOriginalEntries.end() &&
            TryGetHudSpriteCurrentRecord(spriteId, current) &&
            current.w == 0 && current.h == 0)
        {
            return WriteHudSpriteRectEntry(spriteId, originalIt->second);
        }

        Log(L"[HUD] Sprite already visible %hs id=%d\n", name ? name : "<null>", spriteId);
        return true;
    }

    static bool SetStockScrapPilotPanelsVisibleByTable(bool visible)
    {
        static constexpr const char* kPanelNames[] = {
            "scrap_panel",
            "pilot_panel",
            "sscrap_panel",
            "spilot_panel",
            "fscrap_panel",
            "fpilot_panel",
        };

        bool allSucceeded = true;
        for (const char* panelName : kPanelNames)
        {
            if (!SetHudSpriteVisibleByTable(panelName, visible))
                allSucceeded = false;
        }

        return allSucceeded;
    }

    bool SetStockScrapPilotPanelsVisible(bool visible)
    {
        // The addon intentionally calls the primary panel name once. Treat any
        // stock scrap/pilot name as a request for the complete six-entry set so
        // faction/team aliases cannot leave one of the two top HUD boxes drawn.
        if (SetStockScrapPilotPanelsVisibleByTable(visible))
            return true;

        if (SetStockScrapPilotPanelsVisibleByUv(visible))
            return true;

        // A hide/show request can arrive before the mission HUD rect records
        // exist (the Lua layout driver fires within seconds of process start).
        // Report success anyway: the addon keeps a ~1s reassert loop alive only
        // while the bridge looks supported, and its next call lands after the
        // discovery throttle elapses, converging once the HUD is built. A hard
        // "false" here made the addon latch the bridge as unsupported for the
        // whole session, leaving the stock top-centre panels drawn.
        static bool s_deferredLogged = false;
        if (!s_deferredLogged)
        {
            LogShimA(
                LogLevel::Info,
                "hudfallback",
                "stock scrap/pilot panel visible=%s deferred until records discoverable",
                visible ? "true" : "false");
            s_deferredLogged = true;
        }
        return true;
    }

    bool GetHudSpriteRectFromBridge(const char* name, int* outX, int* outY, int* outW, int* outH)
    {
        if (!outX || !outY || !outW || !outH)
        {
            Log(L"[HUD] Invalid rect output pointers for sprite '%hs'\n", name ? name : "<null>");
            return false;
        }

        const int spriteId = LookupHudSpriteId(name);
        if (spriteId <= 0)
        {
            Log(L"[HUD] Unknown sprite '%hs'\n", name ? name : "<null>");
            return false;
        }

        HudSpriteRectRecord current = {};
        if (!TryGetHudSpriteCurrentRecord(spriteId, current))
        {
            Log(L"[HUD] Failed reading live rect entry for sprite '%hs' (id=%d)\n",
                name ? name : "<null>",
                spriteId);
            return false;
        }

        *outX = static_cast<int>(current.x);
        *outY = static_cast<int>(current.y);
        *outW = static_cast<int>(current.w);
        *outH = static_cast<int>(current.h);
        return true;
    }

    bool SetHudSpriteRectFromBridge(const char* name, int x, int y, int w, int h)
    {
        if (IsStockScrapPilotPanelName(name))
        {
            g_ScrapPilotHudPanelOverrideActive = true;
            g_ScrapPilotHudPanelOverrideVisible = w != 0 || h != 0;
            return SetStockScrapPilotPanelsVisible(w != 0 || h != 0);
        }

        return SetHudSpriteRectByTable(name, x, y, w, h);
    }

    bool SetHudSpriteVisibleFromBridge(const char* name, bool visible)
    {
        if (IsStockScrapPilotPanelName(name))
        {
            g_ScrapPilotHudPanelOverrideActive = true;
            g_ScrapPilotHudPanelOverrideVisible = visible;
            return SetStockScrapPilotPanelsVisible(visible);
        }

        return SetHudSpriteVisibleByTable(name, visible);
    }

    bool RestoreHudSpriteFromBridge(const char* name)
    {
        if (IsStockScrapPilotPanelName(name))
        {
            g_ScrapPilotHudPanelOverrideActive = true;
            g_ScrapPilotHudPanelOverrideVisible = true;
            return SetStockScrapPilotPanelsVisible(true);
        }

        const int spriteId = LookupHudSpriteId(name);
        if (spriteId <= 0)
        {
            Log(L"[HUD] Unknown sprite '%hs'\n", name ? name : "<null>");
            return false;
        }

        const auto originalIt = g_HudSpriteOriginalEntries.find(spriteId);
        if (originalIt == g_HudSpriteOriginalEntries.end())
        {
            Log(L"[HUD] No cached original rect for sprite '%hs' (id=%d)\n",
                name ? name : "<null>",
                spriteId);
            return false;
        }

        if (!WriteHudSpriteRectEntry(spriteId, originalIt->second))
        {
            Log(L"[HUD] Failed restoring original rect for sprite '%hs' (id=%d)\n",
                name ? name : "<null>",
                spriteId);
            return false;
        }

        g_HudSpriteHiddenEntries.erase(spriteId);
        Log(L"[HUD] Sprite restored %hs id=%d\n", name ? name : "<null>", spriteId);
        return true;
    }

    bool RestoreAllHudSpritesFromBridge()
    {
        bool anyFailed = false;
        for (const auto& entry : g_HudSpriteOriginalEntries)
        {
            if (!WriteHudSpriteRectEntry(entry.first, entry.second))
            {
                anyFailed = true;
                Log(L"[HUD] Failed restoring cached sprite id=%d during restore-all\n", entry.first);
            }
        }

        if (!anyFailed)
        {
            g_HudSpriteHiddenEntries.clear();
            Log(L"[HUD] Restored %u cached HUD sprite rect(s)\n",
                static_cast<unsigned>(g_HudSpriteOriginalEntries.size()));
        }

        return !anyFailed;
    }
}
