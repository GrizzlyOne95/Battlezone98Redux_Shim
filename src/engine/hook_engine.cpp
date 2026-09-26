#include "hook_engine.h"
#include "resolve_table.h"
#include "shim_log.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iterator>
#include <map>
#include <mutex>
#include <sstream>
#include <vector>

namespace HookEngine
{
    namespace
    {
        std::recursive_mutex g_CodePatchMutex;

        // How many times a code write waits for a thread to leave the site
        // before giving up; each wait is a millisecond.
        constexpr int kBusySiteAttempts = 20;

        bool IsExecutableProtection(DWORD protect)
        {
            return (protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)) != 0;
        }

        // The other threads of this process. They are enumerated and opened
        // before anything is suspended: the snapshot allocates, and nothing
        // may allocate, log or take a lock while another thread is held,
        // since that thread may own the heap or the logger.
        class OtherThreads
        {
        public:
            OtherThreads()
            {
                HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
                if (snapshot == INVALID_HANDLE_VALUE)
                    return;
                const DWORD processId = GetCurrentProcessId();
                const DWORD self = GetCurrentThreadId();
                THREADENTRY32 entry = {};
                entry.dwSize = sizeof(entry);
                if (Thread32First(snapshot, &entry))
                {
                    do
                    {
                        if (entry.th32OwnerProcessID != processId || entry.th32ThreadID == self)
                            continue;
                        HANDLE handle = OpenThread(THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT, FALSE, entry.th32ThreadID);
                        if (handle)
                            m_threads.push_back({ handle, entry.th32ThreadID, false, 0 });
                    } while (Thread32Next(snapshot, &entry));
                }
                CloseHandle(snapshot);
            }

            ~OtherThreads()
            {
                Resume();
                for (const Entry& thread : m_threads)
                    CloseHandle(thread.handle);
            }

            OtherThreads(const OtherThreads&) = delete;
            OtherThreads& operator=(const OtherThreads&) = delete;

            // Suspends every thread and records where each one will resume.
            // GetThreadContext does not return until the suspension has taken
            // effect, so the pointer it reports is the instruction the thread
            // is about to execute.
            void Suspend()
            {
                for (Entry& thread : m_threads)
                {
                    thread.ip = 0;
                    thread.suspended = SuspendThread(thread.handle) != static_cast<DWORD>(-1);
                    if (!thread.suspended)
                        continue;
                    CONTEXT context = {};
                    context.ContextFlags = CONTEXT_CONTROL;
                    if (!GetThreadContext(thread.handle, &context))
                        continue;
#if defined(_M_IX86)
                    thread.ip = context.Eip;
#else
                    thread.ip = static_cast<uintptr_t>(context.Rip);
#endif
                }
            }

            // After Suspend(): the id of a thread about to execute inside
            // [begin, end), or 0 when the site is clear.
            DWORD ThreadInside(uintptr_t begin, uintptr_t end) const
            {
                for (const Entry& thread : m_threads)
                {
                    if (thread.suspended && thread.ip >= begin && thread.ip < end)
                        return thread.id;
                }
                return 0;
            }

            // Suspend() plus the check for one site. A thread inside the site
            // means the write cannot land safely: everything is resumed again
            // and its id is reported.
            bool SuspendOutside(uintptr_t begin, uintptr_t end, DWORD& busyThread)
            {
                Suspend();
                const DWORD busy = ThreadInside(begin, end);
                if (busy == 0)
                    return true;
                busyThread = busy;
                Resume();
                return false;
            }

            void Resume()
            {
                for (Entry& thread : m_threads)
                {
                    if (!thread.suspended)
                        continue;
                    ResumeThread(thread.handle);
                    thread.suspended = false;
                }
            }

        private:
            struct Entry
            {
                HANDLE handle;
                DWORD id;
                bool suspended;
                uintptr_t ip;
            };
            std::vector<Entry> m_threads;
        };
    }

    namespace
    {
        // The thread snapshot is system-wide and costs tens of milliseconds
        // (measured at ~40 ms a write on the dev box, four seconds over a
        // launch), so one is shared by every write that follows within
        // kSnapshotMaxAgeMs, across lock scopes: the patcher's startup writes
        // arrive one call apart and would otherwise each take their own. It
        // is renewed once it is older than that, so a thread started in the
        // meantime is still seen, and dropped at the last unlock once stale.
        // Only the lock holder touches these, so the mutex is their guard.
        constexpr ULONGLONG kSnapshotMaxAgeMs = 250;
        int g_LockDepth = 0;
        OtherThreads* g_Threads = nullptr;
        ULONGLONG g_ThreadsStamp = 0;

        void DropThreadSnapshot()
        {
            delete g_Threads;
            g_Threads = nullptr;
        }

        // Requires the lock to be held by the calling thread.
        OtherThreads& CurrentThreads()
        {
            const ULONGLONG now = GetTickCount64();
            if (g_Threads && now - g_ThreadsStamp > kSnapshotMaxAgeMs)
                DropThreadSnapshot();
            if (!g_Threads)
            {
                g_Threads = new OtherThreads();
                g_ThreadsStamp = now;
            }
            return *g_Threads;
        }
    }

    CodePatchLock::CodePatchLock()
    {
        g_CodePatchMutex.lock();
        ++g_LockDepth;
    }

    CodePatchLock::~CodePatchLock()
    {
        if (--g_LockDepth == 0 && g_Threads && GetTickCount64() - g_ThreadsStamp > kSnapshotMaxAgeMs)
            DropThreadSnapshot();
        g_CodePatchMutex.unlock();
    }

    std::vector<uint16_t> ParseIdaPattern(const std::string& hex)
    {
        // One parser for both the "patches" and "resolves" arrays; it lives in
        // resolve_table.cpp so the host tests can reach it without <Windows.h>.
        return BZROpenShim::ParseIdaPatternText(hex);
    }

    bool ReadMemory(uint32_t address, void* buffer, size_t len)
    {
        SIZE_T read = 0;
        return ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(address), buffer, len, &read) && read == len;
    }

    bool WriteMemory(uint32_t address, const void* data, size_t len)
    {
        // Nothing to write is not a write that succeeded: ApplyPatch relies
        // on this to report a patch whose payload was never filled as a
        // [SKIP], which is what the zero-length VirtualProtect used to do.
        if (len == 0)
            return false;

        CodePatchLock lock;
        HANDLE hProc = GetCurrentProcess();
        DWORD oldProtect = 0;
        void* ptr = reinterpret_cast<void*>(address);

        if (!VirtualProtect(ptr, len, PAGE_EXECUTE_READWRITE, &oldProtect))
            return false;

        bool ok = false;
        DWORD busyThread = 0;
        if (!IsExecutableProtection(oldProtect))
        {
            // Data, not code: nothing executes it, so a plain copy is enough.
            SIZE_T written = 0;
            ok = WriteProcessMemory(hProc, ptr, data, len, &written) && written == len;
        }
        else
        {
            // Code the game may be running this instant. WriteProcessMemory
            // is a plain copy, not an atomic store, and most sites replace
            // several instructions with one jump: a thread whose instruction
            // pointer is inside the site when the bytes land executes half of
            // the old code and half of the new. So every other thread is held
            // while the bytes go in, after a check that none of them is inside
            // the site; one that is gets a moment to move on and the write is
            // tried again.
            OtherThreads& threads = CurrentThreads();
            for (int attempt = 0; attempt < kBusySiteAttempts; ++attempt)
            {
                if (attempt > 0)
                    Sleep(1);
                if (!threads.SuspendOutside(address, address + len, busyThread))
                    continue;
                SIZE_T written = 0;
                ok = WriteProcessMemory(hProc, ptr, data, len, &written) && written == len;
                FlushInstructionCache(hProc, ptr, len);
                threads.Resume();
                busyThread = 0;
                break;
            }
        }

        DWORD restoreProtect = 0;
        VirtualProtect(ptr, len, oldProtect, &restoreProtect);

        if (busyThread != 0)
        {
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Warn, "PATCH",
                "site 0x%08X (%u bytes) not written: thread %lu kept executing inside it",
                address, static_cast<unsigned>(len), static_cast<unsigned long>(busyThread));
        }
        return ok;
    }

    namespace
    {
        // The guard half of ApplyPatch: false when the site is 0, the payload
        // was never filled, the guard is shorter than the payload, or the
        // bytes at the site are not the ones the guard expects.
        bool PatchGuardPasses(const PatchDef& patch)
        {
            if (patch.address == 0 || patch.payload.empty()) return false;

            if (!patch.expected_original.empty())
            {
                // A guard shorter than the payload verifies nothing about the
                // bytes past it; refuse rather than overwrite them blind.
                if (patch.expected_original.size() < patch.payload.size())
                {
                    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Warn, "PATCH",
                        "%s: guard covers %u of %u payload bytes at 0x%08X; not applied",
                        patch.name.c_str(),
                        static_cast<unsigned>(patch.expected_original.size()),
                        static_cast<unsigned>(patch.payload.size()),
                        patch.address);
                    return false;
                }
                std::vector<uint8_t> current(patch.expected_original.size());
                if (!ReadMemory(patch.address, current.data(), current.size())) return false;
                if (memcmp(current.data(), patch.expected_original.data(), current.size()) != 0) return false;
            }
            return true;
        }
    }

    bool ApplyPatch(const PatchDef& patch)
    {
        // Held across the guard check and the write so nobody rewrites the
        // site in between.
        CodePatchLock lock;
        if (!PatchGuardPasses(patch)) return false;
        return WriteMemory(patch.address, patch.payload.data(), patch.payload.size());
    }

    std::vector<bool> ApplyPatches(const std::vector<PatchDef>& patches)
    {
        std::vector<bool> applied(patches.size(), false);
        CodePatchLock lock;

        // Guards and protections first, while every thread still runs:
        // ReadMemory, VirtualProtect and the logger are all off limits once
        // the threads are held, since a held thread may own the heap or the
        // log lock.
        struct Site
        {
            size_t index;
            void* ptr;
            size_t len;
            DWORD oldProtect;
            bool executable;
            bool pending;
            DWORD busyThread;
        };
        std::vector<Site> sites;
        sites.reserve(patches.size());
        for (size_t i = 0; i < patches.size(); ++i)
        {
            const PatchDef& patch = patches[i];
            if (!PatchGuardPasses(patch)) continue;
            Site site{ i, reinterpret_cast<void*>(patch.address), patch.payload.size(), 0, false, true, 0 };
            if (!VirtualProtect(site.ptr, site.len, PAGE_EXECUTE_READWRITE, &site.oldProtect)) continue;
            site.executable = IsExecutableProtection(site.oldProtect);
            sites.push_back(site);
        }

        HANDLE hProc = GetCurrentProcess();
        size_t codePending = 0;
        for (Site& site : sites)
        {
            if (site.executable)
            {
                ++codePending;
                continue;
            }
            // Data: nothing executes it, a plain copy is enough.
            SIZE_T written = 0;
            applied[site.index] = WriteProcessMemory(hProc, site.ptr, patches[site.index].payload.data(), site.len, &written) && written == site.len;
            site.pending = false;
        }

        if (codePending > 0)
        {
            // One suspension for every code site. A site some thread is about
            // to execute stays pending for this round; the threads get a
            // moment to move on and the round repeats for what is left.
            OtherThreads& threads = CurrentThreads();
            for (int attempt = 0; attempt < kBusySiteAttempts && codePending > 0; ++attempt)
            {
                if (attempt > 0)
                    Sleep(1);
                threads.Suspend();
                for (Site& site : sites)
                {
                    if (!site.pending) continue;
                    const uintptr_t begin = reinterpret_cast<uintptr_t>(site.ptr);
                    const DWORD busy = threads.ThreadInside(begin, begin + site.len);
                    if (busy != 0)
                    {
                        site.busyThread = busy;
                        continue;
                    }
                    SIZE_T written = 0;
                    applied[site.index] = WriteProcessMemory(hProc, site.ptr, patches[site.index].payload.data(), site.len, &written) && written == site.len;
                    FlushInstructionCache(hProc, site.ptr, site.len);
                    site.pending = false;
                    site.busyThread = 0;
                    --codePending;
                }
                threads.Resume();
            }
        }

        for (const Site& site : sites)
        {
            DWORD restoreProtect = 0;
            VirtualProtect(site.ptr, site.len, site.oldProtect, &restoreProtect);
        }
        for (const Site& site : sites)
        {
            if (!site.pending) continue;
            BZROpenShim::LogShimA(BZROpenShim::LogLevel::Warn, "PATCH",
                "%s: site 0x%08X (%u bytes) not written: thread %lu kept executing inside it",
                patches[site.index].name.c_str(), patches[site.index].address,
                static_cast<unsigned>(site.len), static_cast<unsigned long>(site.busyThread));
        }
        return applied;
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

    // The pattern scan reads the module's own executable pages in place, under
    // SEH, instead of copying every region into a buffer first. The copies were
    // the dominant cost of the scan: each region once per target per pass in
    // ScanForPatterns, and once per name in ResolveNamedAddress. A leaf with
    // raw pointers only, because __try cannot share a function with objects
    // that need unwinding (C2712). Returns true with outOffset set to the first
    // match at or after startOffset; false at the end of the region or when a
    // read faulted (outFaulted), after which the region is treated as
    // unreadable from that point, as a short ReadProcessMemory was before.
    static bool FindPatternInPlace(const uint8_t* region,
                                   size_t regionSize,
                                   const uint16_t* pattern,
                                   size_t patternSize,
                                   size_t startOffset,
                                   size_t& outOffset,
                                   bool& outFaulted) noexcept
    {
        outFaulted = false;
        if (!region || patternSize == 0 || regionSize < patternSize)
            return false;
        __try
        {
            const size_t last = regionSize - patternSize;
            for (size_t i = startOffset; i <= last; ++i)
            {
                size_t j = 0;
                while (j < patternSize &&
                       (pattern[j] >= 0x100 ||
                        region[i + j] == static_cast<uint8_t>(pattern[j])))
                {
                    ++j;
                }
                if (j == patternSize)
                {
                    outOffset = i;
                    return true;
                }
            }
            return false;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            outFaulted = true;
            return false;
        }
    }

    void ScanForPatterns(const std::string& moduleName, std::vector<PatchDef>& patches, const std::vector<ScanTarget>& targets, bool missesAreProvisional)
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
                size_t next = 0;
                size_t i = 0;
                bool faulted = false;
                while (FindPatternInPlace(region.first, region.second,
                                          idaPattern.data(), idaPattern.size(),
                                          next, i, faulted))
                {
                    ++matchCount;
                    if (matchCount == 1)
                    {
                        matchedAddress = static_cast<uint32_t>(
                            reinterpret_cast<uintptr_t>(region.first + i + target.offset));
                        // The bytes the patch verifies before it writes: still
                        // copied out (a few bytes), bounded by the region.
                        matchedExpected.clear();
                        const size_t site = i + target.offset;
                        const size_t available = site < region.second ? region.second - site : 0;
                        const size_t wanted = std::min<size_t>(target.expected_size, available);
                        if (wanted > 0)
                        {
                            matchedExpected.resize(wanted);
                            SIZE_T read = 0;
                            if (!ReadProcessMemory(hProc, region.first + site, matchedExpected.data(), wanted, &read))
                                read = 0;
                            matchedExpected.resize(read);
                        }
                    }
                    if (!target.require_unique)
                        break;
                    next = i + 1;
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
                // A provisional miss is expected bookkeeping, not a fault: the
                // caller retries once the image settles. Only a miss with no
                // retry left behind it is worth a warning.
                const bool provisionalMiss = matchCount != 1 && missesAreProvisional;
                BZROpenShim::LogShimA(
                    (matchCount == 1 || provisionalMiss)
                        ? BZROpenShim::LogLevel::Info
                        : BZROpenShim::LogLevel::Warn,
                    "patch-scan",
                    "[PATCH-SCAN] name=\"%s\" matches=%zu address=0x%08X state=%s",
                    target.name.c_str(), matchCount, matchedAddress,
                    matchCount == 1
                        ? "unique"
                        : (provisionalMiss ? "pending-image-settle" : "failed-closed"));
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
            for (const auto& region : regions)
            {
                size_t next = 0;
                size_t i = 0;
                bool faulted = false;
                while (FindPatternInPlace(region.first, region.second,
                                          pattern.data(), pattern.size(),
                                          next, i, faulted))
                {
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
                    next = i + 1;
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
