// resource_walk_stat_cache.cpp
// BZR Open Shim - answer the resource-location walk's stat calls from the
// directory enumeration it just did
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Why: every mod-set change (shell <-> addon mission) runs
// buildSingleIAResource (0x0076A600), which re-registers each Modable resource
// location through FUN_006679c0 -> FUN_00667ed0, a recursive std::tr2::sys
// directory walk. The walk enumerates with FindFirstFileW/FindNextFileW and
// then asks GetFileAttributesExW/GetFileAttributesW about the very entries it
// was just handed. Sampled 2026-10-03
// (Docs/Archive/2026/OGRE_LOAD_HITCH_MEASUREMENT_20261003.md), those attribute queries were
// ~0.75 s of the ~1.4 s Modable unload->clear phase.
//
// How: a per-thread scope opened by a detour on buildSingleIAResource. Inside
// it, the executable's FindFirstFileW/FindNextFileW (IAT) remember each
// returned entry's WIN32_FIND_DATAW attributes under "<directory>\<name>", and
// GetFileAttributesExW(GetFileExInfoStandard)/GetFileAttributesW for exactly
// such a path are answered from that record. FindFirstFile and
// GetFileAttributesEx report the same object (neither follows a reparse
// point), so the answer is what the OS would give a moment later. The record
// is thrown away when the scope closes, so nothing survives into another load
// or into any other code path. Outside the scope every hook is a single
// thread-local test and a tail call.
//
// Paths are matched after lower-casing and folding '/' to '\'. A stat whose
// spelling differs from the enumeration (relative vs absolute, "..") simply
// misses and goes to the OS.
//
// Shell scopes (BeginResourceWalkStatScope) also note each Ogre script file the
// walk enumerates and, when the scope closes, hand the ones not seen before to
// one background-priority thread that opens and reads them. The first open of a
// file since boot is slow (measured 2026-11-16: 5075 script files took 11.4 s
// cold, 0.3 s warm; the bytes are only 9 MB, so it is per-open cost, likely the
// on-access scan). The game-room rebuild opens ~2100 of them on the main
// thread, so reading them early, while the player is in the menus, takes that
// cost off the hang. Read only: the files and what the engine loads are
// unchanged. Paths keep their enumerated spelling (case-sensitive filesystems
// under Proton/Wine). OPENSHIM_DISABLE_SHELL_SCRIPT_PREFETCH=1 turns it off.

#include "resource_walk_stat_cache.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "iat_patch.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cwctype>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "walk-stat-cache";
        constexpr char kDisableSwitch[] = "OPENSHIM_DISABLE_RESOURCE_WALK_STAT_CACHE";
        constexpr char kPrefetchDisableSwitch[] = "OPENSHIM_DISABLE_SHELL_SCRIPT_PREFETCH";
        constexpr char kEngineAddressName[] = "BuildSingleIAResource";
        constexpr uint8_t kExpectedPrologue[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };

        using FnBuildSingleIAResource = void(__thiscall*)(void*, void*);
        using PFN_FindFirstFileW = HANDLE(WINAPI*)(LPCWSTR, LPWIN32_FIND_DATAW);
        using PFN_FindNextFileW = BOOL(WINAPI*)(HANDLE, LPWIN32_FIND_DATAW);
        using PFN_FindClose = BOOL(WINAPI*)(HANDLE);
        using PFN_GetFileAttributesW = DWORD(WINAPI*)(LPCWSTR);
        using PFN_GetFileAttributesExW = BOOL(WINAPI*)(LPCWSTR, GET_FILEEX_INFO_LEVELS, LPVOID);

        PFN_FindFirstFileW g_RealFindFirstFileW = nullptr;
        PFN_FindNextFileW g_RealFindNextFileW = nullptr;
        PFN_FindClose g_RealFindClose = nullptr;
        PFN_GetFileAttributesW g_RealGetFileAttributesW = nullptr;
        PFN_GetFileAttributesExW g_RealGetFileAttributesExW = nullptr;

        InlineDetour32 g_BuildDetour = {};
        FnBuildSingleIAResource g_BuildOriginal = nullptr;
        bool g_ImportsPatched = false;
        bool g_Installed = false;
        bool g_FailureLogged = false;
        bool g_DisabledLogged = false;

        struct OpenEnum
        {
            std::wstring key;        // normalised directory
            std::wstring spelling;   // directory as the walk spelled it
        };

        struct Scope
        {
            int depth = 0;
            bool collectScripts = false;   // a shell scope: note script files for prefetch
            std::unordered_map<HANDLE, OpenEnum> openEnums;
            std::unordered_map<std::wstring, WIN32_FILE_ATTRIBUTE_DATA> entries;
            std::vector<std::wstring> scripts;   // enumerated script paths, walk spelling
            uint32_t hits = 0;
            uint32_t misses = 0;
            uint64_t startTick = 0;
        };
        thread_local Scope t_Scope;

        std::wstring Normalise(const wchar_t* path, size_t length)
        {
            std::wstring key;
            key.reserve(length);
            for (size_t i = 0; i < length; ++i)
            {
                wchar_t c = path[i] == L'/' ? L'\\' : path[i];
                if (c == L'\\' && !key.empty() && key.back() == L'\\')
                    continue;
                key.push_back(static_cast<wchar_t>(std::towlower(c)));
            }
            while (key.size() > 1 && key.back() == L'\\')
                key.pop_back();
            return key;
        }

        // "dir/*" or "dir\*.*" -> normalised "dir"; nothing for a bare pattern.
        bool DirectoryOfPattern(LPCWSTR pattern, OpenEnum& out)
        {
            if (!pattern)
                return false;
            const std::wstring text(pattern);
            const size_t sep = text.find_last_of(L"\\/");
            if (sep == std::wstring::npos || sep == 0)
                return false;
            out.key = Normalise(text.c_str(), sep);
            out.spelling.assign(text, 0, sep);
            return true;
        }

        // The Ogre script types the Modable rebuild parses.
        bool IsScriptName(const wchar_t* name)
        {
            static const wchar_t* const kExtensions[] = {
                L".material", L".program", L".particle", L".compositor",
                L".overlay", L".fontdef", L".os",
            };
            const wchar_t* dot = wcsrchr(name, L'.');
            if (!dot)
                return false;
            for (const wchar_t* ext : kExtensions)
                if (_wcsicmp(dot, ext) == 0)
                    return true;
            return false;
        }

        void Remember(const OpenEnum& directory, const WIN32_FIND_DATAW& data)
        {
            const wchar_t* name = data.cFileName;
            if (name[0] == L'.' && (name[1] == 0 || (name[1] == L'.' && name[2] == 0)))
                return;
            if (t_Scope.collectScripts && !(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                IsScriptName(name))
            {
                std::wstring path = directory.spelling;
                path.push_back(L'\\');
                path += name;
                t_Scope.scripts.push_back(std::move(path));
            }
            std::wstring key = directory.key;
            key.push_back(L'\\');
            key += Normalise(name, wcslen(name));
            WIN32_FILE_ATTRIBUTE_DATA attributes = {};
            attributes.dwFileAttributes = data.dwFileAttributes;
            attributes.ftCreationTime = data.ftCreationTime;
            attributes.ftLastAccessTime = data.ftLastAccessTime;
            attributes.ftLastWriteTime = data.ftLastWriteTime;
            attributes.nFileSizeHigh = data.nFileSizeHigh;
            attributes.nFileSizeLow = data.nFileSizeLow;
            t_Scope.entries[std::move(key)] = attributes;
        }

        const WIN32_FILE_ATTRIBUTE_DATA* Lookup(LPCWSTR path)
        {
            if (!path)
                return nullptr;
            auto it = t_Scope.entries.find(Normalise(path, wcslen(path)));
            if (it == t_Scope.entries.end())
            {
                ++t_Scope.misses;
                return nullptr;
            }
            ++t_Scope.hits;
            return &it->second;
        }

        HANDLE WINAPI HookFindFirstFileW(LPCWSTR pattern, LPWIN32_FIND_DATAW data)
        {
            HANDLE handle = g_RealFindFirstFileW(pattern, data);
            if (t_Scope.depth > 0 && handle != INVALID_HANDLE_VALUE && data)
            {
                OpenEnum directory;
                if (DirectoryOfPattern(pattern, directory))
                {
                    Remember(directory, *data);
                    t_Scope.openEnums[handle] = std::move(directory);
                }
            }
            return handle;
        }

        BOOL WINAPI HookFindNextFileW(HANDLE handle, LPWIN32_FIND_DATAW data)
        {
            const BOOL ok = g_RealFindNextFileW(handle, data);
            if (ok && t_Scope.depth > 0 && data)
            {
                auto it = t_Scope.openEnums.find(handle);
                if (it != t_Scope.openEnums.end())
                    Remember(it->second, *data);
            }
            return ok;
        }

        BOOL WINAPI HookFindClose(HANDLE handle)
        {
            if (t_Scope.depth > 0)
                t_Scope.openEnums.erase(handle);
            return g_RealFindClose(handle);
        }

        DWORD WINAPI HookGetFileAttributesW(LPCWSTR path)
        {
            if (t_Scope.depth > 0)
            {
                if (const auto* cached = Lookup(path))
                {
                    SetLastError(ERROR_SUCCESS);
                    return cached->dwFileAttributes;
                }
            }
            return g_RealGetFileAttributesW(path);
        }

        BOOL WINAPI HookGetFileAttributesExW(LPCWSTR path, GET_FILEEX_INFO_LEVELS level, LPVOID info)
        {
            if (t_Scope.depth > 0 && level == GetFileExInfoStandard && info)
            {
                if (const auto* cached = Lookup(path))
                {
                    *static_cast<WIN32_FILE_ATTRIBUTE_DATA*>(info) = *cached;
                    SetLastError(ERROR_SUCCESS);
                    return TRUE;
                }
            }
            return g_RealGetFileAttributesExW(path, level, info);
        }

        // ---- background prefetch of shell script files -------------------
        SRWLOCK g_PrefetchLock = SRWLOCK_INIT;
        std::vector<std::wstring> g_PrefetchQueue;          // guarded by g_PrefetchLock
        std::unordered_set<std::wstring> g_PrefetchSeen;    // normalised; guarded
        bool g_PrefetchWorkerRunning = false;               // guarded
        bool g_PrefetchDisabled = false;                    // set once at install

        DWORD WINAPI PrefetchWorker(LPVOID)
        {
            // Background mode lowers I/O priority too; Wine may refuse it.
            if (!SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_BEGIN))
                SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);
            static char buffer[64 * 1024];   // only one worker runs at a time
            uint32_t files = 0;
            uint32_t failed = 0;
            uint64_t bytes = 0;
            const uint64_t start = GetTickCount64();
            for (;;)
            {
                std::vector<std::wstring> batch;
                AcquireSRWLockExclusive(&g_PrefetchLock);
                batch.swap(g_PrefetchQueue);
                if (batch.empty())
                    g_PrefetchWorkerRunning = false;
                ReleaseSRWLockExclusive(&g_PrefetchLock);
                if (batch.empty())
                    break;
                for (const std::wstring& path : batch)
                {
                    HANDLE file = CreateFileW(path.c_str(), GENERIC_READ,
                                              FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                              nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
                    if (file == INVALID_HANDLE_VALUE)
                    {
                        ++failed;
                        continue;
                    }
                    DWORD got = 0;
                    while (ReadFile(file, buffer, sizeof(buffer), &got, nullptr) && got != 0)
                        bytes += got;
                    CloseHandle(file);
                    ++files;
                }
            }
            LogShimA(LogLevel::Info, kComponent,
                     "[PREFETCH] read %u script files (%llu KB) in %llu ms, %u could not be opened",
                     files, static_cast<unsigned long long>(bytes / 1024),
                     static_cast<unsigned long long>(GetTickCount64() - start), failed);
            return 0;
        }

        void QueuePrefetch(std::vector<std::wstring>& paths, const char* label)
        {
            if (paths.empty() || g_PrefetchDisabled)
                return;
            uint32_t added = 0;
            bool startWorker = false;
            AcquireSRWLockExclusive(&g_PrefetchLock);
            for (std::wstring& path : paths)
            {
                if (!g_PrefetchSeen.insert(Normalise(path.c_str(), path.size())).second)
                    continue;
                g_PrefetchQueue.push_back(std::move(path));
                ++added;
            }
            if (added && !g_PrefetchWorkerRunning)
                startWorker = g_PrefetchWorkerRunning = true;
            ReleaseSRWLockExclusive(&g_PrefetchLock);
            if (!added)
                return;
            LogShimA(LogLevel::Info, kComponent, "[PREFETCH] %s queued %u new script files", label, added);
            if (!startWorker)
                return;
            HANDLE worker = CreateThread(nullptr, 0, PrefetchWorker, nullptr, 0, nullptr);
            if (worker)
            {
                CloseHandle(worker);
                return;
            }
            // No thread: drop the queue; the engine reads the files itself as before.
            const DWORD error = GetLastError();
            AcquireSRWLockExclusive(&g_PrefetchLock);
            g_PrefetchQueue.clear();
            g_PrefetchWorkerRunning = false;
            ReleaseSRWLockExclusive(&g_PrefetchLock);
            LogShimA(LogLevel::Warn, kComponent, "[PREFETCH] worker thread could not start (%lu)", error);
        }

        void EnterScope()
        {
            if (t_Scope.depth++ == 0)
                t_Scope.startTick = GetTickCount64();
        }

        void LeaveScope(const char* label)
        {
            if (t_Scope.depth == 0)
                return;
            if (--t_Scope.depth != 0)
                return;
            if (t_Scope.hits || t_Scope.misses)
                LogShimA(LogLevel::Info, kComponent,
                         "[WALKSTAT] %s %llu ms: %u stat calls answered from enumeration, "
                         "%u passed to the OS, %u entries seen",
                         label,
                         static_cast<unsigned long long>(GetTickCount64() - t_Scope.startTick),
                         t_Scope.hits, t_Scope.misses,
                         static_cast<unsigned>(t_Scope.entries.size()));
            if (t_Scope.collectScripts)
                QueuePrefetch(t_Scope.scripts, label);
            t_Scope.collectScripts = false;
            t_Scope.scripts.clear();
            t_Scope.entries.clear();
            t_Scope.openEnums.clear();
            t_Scope.hits = t_Scope.misses = 0;
        }

        void __fastcall BuildSingleIAResourceHook(void* self, void* /*edx*/, void* request)
        {
            struct ScopeGuard
            {
                ScopeGuard() { EnterScope(); }
                ~ScopeGuard() { LeaveScope("build"); }
            } guard;   // closes even if the engine throws through here
            g_BuildOriginal(self, request);
        }

        bool DisabledByEnvironment(const char* name = kDisableSwitch)
        {
            char value[16] = {};
            const DWORD len = GetEnvironmentVariableA(name, value, sizeof(value));
            if (len == 0 || len >= sizeof(value))
                return false;
            return !(value[0] == '0' && value[1] == '\0');
        }

        void LogFailureOnce(const char* what)
        {
            if (g_FailureLogged)
                return;
            g_FailureLogged = true;
            LogShimA(LogLevel::Warn, kComponent, "[WALKSTAT] not installed: %s", what);
        }

        // All five or none: a partial set would record without answering or
        // answer without recording -- harmless, but pointless and confusing.
        bool PatchImports(HMODULE exe)
        {
            struct Row { const char* name; void* hook; void** original; };
            const Row rows[] = {
                {"FindFirstFileW", reinterpret_cast<void*>(&HookFindFirstFileW),
                 reinterpret_cast<void**>(&g_RealFindFirstFileW)},
                {"FindNextFileW", reinterpret_cast<void*>(&HookFindNextFileW),
                 reinterpret_cast<void**>(&g_RealFindNextFileW)},
                {"FindClose", reinterpret_cast<void*>(&HookFindClose),
                 reinterpret_cast<void**>(&g_RealFindClose)},
                {"GetFileAttributesW", reinterpret_cast<void*>(&HookGetFileAttributesW),
                 reinterpret_cast<void**>(&g_RealGetFileAttributesW)},
                {"GetFileAttributesExW", reinterpret_cast<void*>(&HookGetFileAttributesExW),
                 reinterpret_cast<void**>(&g_RealGetFileAttributesExW)},
            };
            for (const Row& row : rows)
            {
                // The originals must be valid before any slot points at a hook.
                *row.original = reinterpret_cast<void*>(
                    GetProcAddress(GetModuleHandleA("kernel32.dll"), row.name));
                if (!*row.original)
                    return false;
            }
            for (const Row& row : rows)
            {
                void* previous = nullptr;
                if (IatPatch::PatchImportFromAnyDll(exe, row.name, row.hook, &previous) !=
                    IatPatch::Result::Patched)
                {
                    LogShimA(LogLevel::Warn, kComponent, "[WALKSTAT] import %s not patched", row.name);
                    return false;
                }
                // Chain to whatever the slot held (another OpenShim hook, e.g.
                // the UiPerf file-scan counters, or kernel32 itself).
                if (previous)
                    *row.original = previous;
            }
            return true;
        }
    }

    // Needs only the import hooks; the buildSingleIAResource detour is not
    // involved. A no-op when the imports are not patched (disabled, failed).
    bool BeginResourceWalkStatScope()
    {
        if (!g_ImportsPatched)
            return false;
        // Only the outermost scope decides; a nested one changes nothing.
        if (t_Scope.depth == 0)
            t_Scope.collectScripts = !g_PrefetchDisabled;
        EnterScope();
        return true;
    }

    void EndResourceWalkStatScope(const char* label)
    {
        LeaveScope(label ? label : "scope");
    }

    void InstallResourceWalkStatCacheIfPossible()
    {
        if (g_Installed)
            return;
        if (DisabledByEnvironment())
        {
            if (!g_DisabledLogged)
            {
                g_DisabledLogged = true;
                LogShimA(LogLevel::Info, kComponent, "[WALKSTAT] disabled by %s", kDisableSwitch);
            }
            return;
        }

        uint32_t address = 0;
        const auto status = HookEngine::ResolveEngineAddress(kEngineAddressName, address);
        if (status != HookEngine::EngineAddressStatus::Bound)
        {
            // Mismatch can be SteamStub not settled yet; a later retry rechecks.
            if (status != HookEngine::EngineAddressStatus::Mismatch)
                LogFailureOnce("engine address BuildSingleIAResource did not verify");
            return;
        }
        if (!ExpectedBytesMatchAt(address, kExpectedPrologue, sizeof(kExpectedPrologue)))
        {
            LogFailureOnce("unexpected buildSingleIAResource prologue");
            return;
        }

        g_PrefetchDisabled = DisabledByEnvironment(kPrefetchDisableSwitch);
        if (g_PrefetchDisabled)
            LogShimA(LogLevel::Info, kComponent, "[PREFETCH] disabled by %s", kPrefetchDisableSwitch);

        // Imports first: until the detour opens a scope the hooks only pass through.
        if (!g_ImportsPatched)
        {
            if (!PatchImports(GetModuleHandleW(nullptr)))
            {
                LogFailureOnce("executable imports could not be patched");
                return;
            }
            g_ImportsPatched = true;
        }

        if (!InstallInlineDetour32(g_BuildDetour, address,
                                   reinterpret_cast<void*>(&BuildSingleIAResourceHook),
                                   sizeof(kExpectedPrologue), kExpectedPrologue, sizeof(kExpectedPrologue)))
        {
            LogFailureOnce("buildSingleIAResource detour failed (import hooks stay pass-through)");
            return;
        }
        g_BuildOriginal = reinterpret_cast<FnBuildSingleIAResource>(g_BuildDetour.trampoline);
        g_Installed = true;
        LogShimA(LogLevel::Info, kComponent, "[WALKSTAT] installed at 0x%08X", address);
    }
}
