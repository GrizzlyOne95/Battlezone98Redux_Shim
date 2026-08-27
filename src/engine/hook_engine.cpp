#include "hook_engine.h"
#include "resolve_table.h"
#include "shim_log.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <psapi.h>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iterator>
#include <map>
#include <mutex>
#include <sstream>

namespace HookEngine
{

    std::vector<uint16_t> ParseIdaPattern(const std::string& hex)
    {
        // One parser for both the "patches" and "resolves" arrays; it lives in
        // resolve_table.cpp so the host tests can reach it without <Windows.h>.
        return BZROpenShim::ParseIdaPatternText(hex);
    }

    std::vector<uint8_t> ParseHexPattern(const std::string& hex)
    {
        std::vector<uint8_t> bytes;
        std::stringstream ss(hex);
        std::string item;
        while (ss >> item)
        {
            bytes.push_back(static_cast<uint8_t>(std::stoul(item, nullptr, 16)));
        }
        return bytes;
    }

    bool ReadMemory(uint32_t address, void* buffer, size_t len)
    {
        SIZE_T read = 0;
        return ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(address), buffer, len, &read) && read == len;
    }

    bool WriteMemory(uint32_t address, const void* data, size_t len)
    {
        HANDLE hProc = GetCurrentProcess();
        DWORD oldProtect = 0;
        void* ptr = reinterpret_cast<void*>(address);

        if (!VirtualProtect(ptr, len, PAGE_EXECUTE_READWRITE, &oldProtect))
            return false;

        SIZE_T written = 0;
        BOOL ok = WriteProcessMemory(hProc, ptr, data, len, &written);

        VirtualProtect(ptr, len, oldProtect, &oldProtect);
        return ok && written == len;
    }

    bool ApplyPatch(const PatchDef& patch)
    {
        if (patch.address == 0) return false;

        if (!patch.expected_original.empty())
        {
            std::vector<uint8_t> current(patch.expected_original.size());
            if (!ReadMemory(patch.address, current.data(), current.size())) return false;
            if (memcmp(current.data(), patch.expected_original.data(), current.size()) != 0) return false;
        }

        return WriteMemory(patch.address, patch.payload.data(), patch.payload.size());
    }

    void* ResolveRelCallTarget(uint32_t instrAddr)
    {
        uint8_t op;
        if (!ReadMemory(instrAddr, &op, 1) || op != 0xE8) return nullptr;

        int32_t rel = 0;
        if (!ReadMemory(instrAddr + 1, &rel, 4)) return nullptr;

        return reinterpret_cast<void*>(instrAddr + 5 + rel);
    }

    std::vector<uint8_t> MakeJmp5Payload(uint32_t src, uint32_t dst, size_t total_len)
    {
        int32_t rel = static_cast<int32_t>(dst) - static_cast<int32_t>(src + 5);
        std::vector<uint8_t> buf(total_len, 0x90);
        buf[0] = 0xE9;
        memcpy(&buf[1], &rel, 4);
        return buf;
    }


    void* ResolveRelCallTargetWithRetry(uint32_t instrAddr, int maxAttempts, uint32_t delayMs)
    {
        for (int attempt = 0; attempt < maxAttempts; ++attempt)
        {
            if (void* target = ResolveRelCallTarget(instrAddr))
            {
                return target;
            }
            if (attempt + 1 < maxAttempts)
                Sleep(delayMs);
        }
        return nullptr;
    }


    namespace
    {
        // Committed, executable regions of a mapped module, clipped to the
        // image. Shared by the patch scan and the resolve scan so both agree
        // on what "the code" is.
        bool CollectExecutableRegions(const std::string& moduleName,
                                      std::vector<std::pair<uint8_t*, size_t>>& outRegions,
                                      uint8_t*& outBase,
                                      uint8_t*& outEnd)
        {
            outRegions.clear();
            outBase = nullptr;
            outEnd = nullptr;

            HMODULE hMod = GetModuleHandleA(moduleName.empty() ? nullptr : moduleName.c_str());
            if (!hMod) return false;

            MODULEINFO mi;
            if (!GetModuleInformation(GetCurrentProcess(), hMod, &mi, sizeof(mi))) return false;

            uint8_t* base = reinterpret_cast<uint8_t*>(mi.lpBaseOfDll);
            uint8_t* end = base + mi.SizeOfImage;

            MEMORY_BASIC_INFORMATION mbi = {};
            uint8_t* addr = base;
            while (addr < end && VirtualQuery(addr, &mbi, sizeof(mbi)) == sizeof(mbi))
            {
                uint8_t* rBase = reinterpret_cast<uint8_t*>(mbi.BaseAddress);
                uint8_t* rEnd = rBase + mbi.RegionSize;
                if (rEnd <= base || rBase >= end)
                {
                    addr = rEnd;
                    continue;
                }
                uint8_t* clipStart = (rBase < base) ? base : rBase;
                uint8_t* clipEnd = (rEnd > end) ? end : rEnd;
                size_t clipSize = static_cast<size_t>(clipEnd - clipStart);

                if (clipSize > 0 && mbi.State == MEM_COMMIT &&
                    (mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)))
                {
                    outRegions.push_back({ clipStart, clipSize });
                }
                addr = rEnd;
            }

            outBase = base;
            outEnd = end;
            return true;
        }
    }

    void ScanForPatterns(const std::string& moduleName, std::vector<PatchDef>& patches, const std::vector<ScanTarget>& targets)
    {
        std::vector<std::pair<uint8_t*, size_t>> regions;
        uint8_t* base = nullptr;
        uint8_t* end = nullptr;
        if (!CollectExecutableRegions(moduleName, regions, base, end)) return;

        HANDLE hProc = GetCurrentProcess();

        for (const auto& target : targets)
        {
            // Runtime filtering happens on PatchDef before this function is
            // called. Do not scan a target that no longer has an eligible
            // patch definition; this keeps storefront/feature-disabled hooks
            // from paying even the signature-scan cost on an inapplicable
            // runtime.
            const bool targetEligible = std::any_of(
                patches.begin(), patches.end(),
                [&target](const PatchDef& patch) { return patch.name == target.name; });
            if (!targetEligible)
                continue;

            auto idaPattern = ParseIdaPattern(target.ida_pattern);
            if (idaPattern.empty()) continue;

            size_t matchCount = 0;
            uint32_t matchedAddress = 0;
            std::vector<uint8_t> matchedExpected;
            for (const auto& region : regions)
            {
                std::vector<uint8_t> buf(region.second);
                SIZE_T read = 0;
                if (!ReadProcessMemory(hProc, region.first, buf.data(), region.second, &read) || read == 0)
                    continue;
                if (read < idaPattern.size())
                    continue;

                for (size_t i = 0; i <= read - idaPattern.size(); i++)
                {
                    bool match = true;
                    for (size_t j = 0; j < idaPattern.size(); j++)
                    {
                        if (idaPattern[j] < 0x100 && buf[i + j] != static_cast<uint8_t>(idaPattern[j]))
                        {
                            match = false;
                            break;
                        }
                    }

                    if (match)
                    {
                        ++matchCount;
                        if (matchCount == 1)
                        {
                            matchedAddress = static_cast<uint32_t>(
                                reinterpret_cast<uintptr_t>(region.first + i + target.offset));
                            matchedExpected.clear();
                            for (size_t j = 0; j < target.expected_size && (i + target.offset + j) < read; ++j)
                                matchedExpected.push_back(buf[i + target.offset + j]);
                        }
                        if (!target.require_unique)
                            break;
                    }
                }
                if (matchCount > 0 && !target.require_unique)
                    break;
            }

            if (matchCount == 1 || (matchCount > 0 && !target.require_unique))
            {
                for (auto& patch : patches)
                {
                    if (patch.name != target.name)
                        continue;
                    patch.address = matchedAddress;
                    patch.verified = true;
                    patch.expected_original = matchedExpected;
                    break;
                }
            }
            if (target.require_unique)
            {
                BZROpenShim::LogShimA(
                    matchCount == 1 ? BZROpenShim::LogLevel::Info : BZROpenShim::LogLevel::Warn,
                    "patch-scan",
                    "[PATCH-SCAN] name=\"%s\" matches=%zu address=0x%08X state=%s",
                    target.name.c_str(), matchCount, matchedAddress,
                    matchCount == 1 ? "unique" : "failed-closed");
            }
        }
    }

    std::string FindPatchesJsonPath()
    {
        {
            std::ifstream f("scripts/patches.json");
            if (f.is_open()) return "scripts/patches.json";
        }

        // The game may be launched with a working directory other than the
        // install root; fall back to the exe's own directory.
        char path[MAX_PATH] = {};
        if (GetModuleFileNameA(nullptr, path, MAX_PATH) != 0)
        {
            char* slash = strrchr(path, '\\');
            if (slash) *slash = '\0';
            std::string exeRelative = std::string(path) + "\\scripts\\patches.json";
            std::ifstream f(exeRelative);
            if (f.is_open()) return exeRelative;
        }

        return {};
    }

    namespace
    {
        std::mutex g_ResolveMutex;
        bool g_ResolveTableLoaded = false;
        std::vector<BZROpenShim::ResolveTarget> g_ResolveTable;
        // Only successes are cached. A failure is usually "the module is not
        // mapped yet", and callers are expected to ask again.
        std::map<std::string, uint32_t> g_ResolveCache;

        void LoadResolveTableLocked()
        {
            if (g_ResolveTableLoaded) return;
            g_ResolveTableLoaded = true;

            const std::string path = FindPatchesJsonPath();
            if (path.empty())
            {
                BZROpenShim::LogShimA(BZROpenShim::LogLevel::Warn, "resolve",
                    "[RESOLVE] scripts/patches.json not found; every resolve falls back");
                return;
            }

            std::string text;
            try
            {
                std::ifstream f(path, std::ios::binary);
                text.assign(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
            }
            catch (...)
            {
                text.clear();
            }

            std::string error;
            g_ResolveTable = BZROpenShim::ParseResolveTable(text, &error);
            if (!error.empty())
            {
                BZROpenShim::LogShimA(BZROpenShim::LogLevel::Warn, "resolve",
                    "[RESOLVE] table has rejected entries: %s", error.c_str());
            }
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "resolve",
                "[RESOLVE] loaded %zu entr%s from %s",
                g_ResolveTable.size(), g_ResolveTable.size() == 1 ? "y" : "ies", path.c_str());
        }

        // Applies offset and mode to a match, rejecting anything that would
        // land outside the module or that is not the instruction the entry
        // claims. An anchor that misses by a couple of bytes is the classic
        // way one of these silently resolves to a plausible neighbour.
        bool AnchorToAddress(const BZROpenShim::ResolveTarget& target,
                             uint8_t* match,
                             uint8_t* base,
                             uint8_t* end,
                             uint32_t& outAddress)
        {
            outAddress = 0;

            uint8_t* anchor = match + target.offset;
            if (anchor < base || anchor >= end)
                return false;

            if (target.mode == BZROpenShim::ResolveMode::Address)
            {
                outAddress = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(anchor));
                return true;
            }

            // Rel32Target: the anchor must actually be the CALL.
            if (anchor + 5 > end || anchor[0] != 0xE8)
                return false;

            int32_t rel = 0;
            std::memcpy(&rel, anchor + 1, sizeof(rel));
            uint8_t* callTarget = anchor + 5 + rel;
            if (callTarget < base || callTarget >= end)
                return false;

            outAddress = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(callTarget));
            return true;
        }
    }

    uint32_t ResolveNamedAddress(const char* name)
    {
        if (!name || !name[0]) return 0;

        std::lock_guard<std::mutex> lock(g_ResolveMutex);
        LoadResolveTableLocked();

        const std::string key(name);
        auto cached = g_ResolveCache.find(key);
        if (cached != g_ResolveCache.end())
            return cached->second;

        const BZROpenShim::ResolveTarget* target = nullptr;
        for (const auto& candidate : g_ResolveTable)
        {
            if (candidate.name == key)
            {
                target = &candidate;
                break;
            }
        }
        if (!target)
        {
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Warn, "resolve",
                "[RESOLVE] name=\"%s\" has no entry in scripts/patches.json", name);
            return 0;
        }

        std::vector<std::pair<uint8_t*, size_t>> regions;
        uint8_t* base = nullptr;
        uint8_t* end = nullptr;
        const bool moduleReady = CollectExecutableRegions("", regions, base, end);

        const auto pattern = ParseIdaPattern(target->ida_pattern);
        size_t matchCount = 0;
        uint32_t scanned = 0;

        if (moduleReady && !pattern.empty())
        {
            HANDLE hProc = GetCurrentProcess();
            for (const auto& region : regions)
            {
                std::vector<uint8_t> buf(region.second);
                SIZE_T read = 0;
                if (!ReadProcessMemory(hProc, region.first, buf.data(), region.second, &read) || read == 0)
                    continue;
                if (read < pattern.size())
                    continue;

                for (size_t i = 0; i <= read - pattern.size(); i++)
                {
                    bool match = true;
                    for (size_t j = 0; j < pattern.size(); j++)
                    {
                        if (pattern[j] < 0x100 && buf[i + j] != static_cast<uint8_t>(pattern[j]))
                        {
                            match = false;
                            break;
                        }
                    }
                    if (!match)
                        continue;

                    // Always count every hit, even when the first one will be
                    // taken: an ambiguous signature that happens to work is
                    // still worth seeing in the log before it stops working.
                    ++matchCount;
                    if (matchCount == 1)
                    {
                        uint32_t candidate = 0;
                        if (AnchorToAddress(*target, region.first + i, base, end, candidate))
                            scanned = candidate;
                        else
                            matchCount = 0; // anchor rejected; keep looking
                    }
                }
            }
        }

        if (target->require_unique && matchCount != 1)
            scanned = 0;

        const bool scanUsable = scanned != 0;
        const bool preferFallback =
            target->preference == BZROpenShim::ResolvePreference::Fallback;
        uint32_t chosen = 0;
        const char* source = "none";
        if (preferFallback && target->fallback_addr != 0)
        {
            chosen = target->fallback_addr;
            source = "fallback";
        }
        else if (scanUsable)
        {
            chosen = scanned;
            source = "scan";
        }
        else if (target->fallback_addr != 0)
        {
            chosen = target->fallback_addr;
            source = "fallback";
        }

        const bool agrees = scanUsable && target->fallback_addr != 0 &&
                            scanned == target->fallback_addr;
        const bool disagrees = scanUsable && target->fallback_addr != 0 &&
                               scanned != target->fallback_addr;

        BZROpenShim::LogShimA(
            (chosen == 0 || disagrees) ? BZROpenShim::LogLevel::Warn : BZROpenShim::LogLevel::Info,
            "resolve",
            "[RESOLVE] name=\"%s\" matches=%zu scan=0x%08X fallback=0x%08X used=0x%08X "
            "source=%s agree=%s identity=\"%s\"",
            name, matchCount, scanned, target->fallback_addr, chosen, source,
            agrees ? "yes" : (disagrees ? "NO" : "n/a"),
            target->identity.c_str());

        if (chosen != 0)
            g_ResolveCache[key] = chosen;
        return chosen;
    }

}
