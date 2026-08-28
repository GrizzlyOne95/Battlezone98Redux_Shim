// ui_file_scan_hooks.cpp
// Win32 file-enumeration counters for UiPerf.
//
// Hooks FindFirstFileW/A, FindNextFileW/A, FindClose, GetFileAttributesW/A
// via IAT patching on the game executable + OgreMain + MSVCR120 so every
// enumeration path is counted regardless of which CRT it comes through.  The
// counters are kept thread-local and aggregated per scan root by watching the
// FindFirstFile pattern argument.  At ModDiscovery scope end a single
// RecordScan() call is emitted.
//
// When UiPerformanceLogging==false this file still compiles but Install() is
// a no-op.
//
// SPDX-License-Identifier: MIT

#include "ui_file_scan_hooks.h"
#include "ui_performance.h"
#include "ui_performance_hooks.h"
#include "shim_log.h"

#include <Windows.h>

#include <atomic>
#include <mutex>
#include <string>
#include <unordered_map>
#include <filesystem>

namespace BZROpenShim::UiFileScan
{
    namespace
    {
        std::atomic<bool> g_Installed{ false };

        // Original function pointers (filled by IAT patching).
        using PFN_FindFirstFileW = HANDLE(WINAPI*)(LPCWSTR, LPWIN32_FIND_DATAW);
        using PFN_FindFirstFileA = HANDLE(WINAPI*)(LPCSTR, LPWIN32_FIND_DATAA);
        using PFN_FindNextFileW = BOOL(WINAPI*)(HANDLE, LPWIN32_FIND_DATAW);
        using PFN_FindNextFileA = BOOL(WINAPI*)(HANDLE, LPWIN32_FIND_DATAA);
        using PFN_FindClose = BOOL(WINAPI*)(HANDLE);
        using PFN_GetFileAttributesW = DWORD(WINAPI*)(LPCWSTR);
        using PFN_GetFileAttributesA = DWORD(WINAPI*)(LPCSTR);

        PFN_FindFirstFileW g_RealFindFirstFileW = nullptr;
        PFN_FindFirstFileA g_RealFindFirstFileA = nullptr;
        PFN_FindNextFileW g_RealFindNextFileW = nullptr;
        PFN_FindNextFileA g_RealFindNextFileA = nullptr;
        PFN_FindClose g_RealFindClose = nullptr;
        PFN_GetFileAttributesW g_RealGetFileAttributesW = nullptr;
        PFN_GetFileAttributesA g_RealGetFileAttributesA = nullptr;

        // Per-thread live enumeration -> pattern.
        struct EnumRecord
        {
            std::wstring pattern;
        };
        thread_local std::unordered_map<HANDLE, EnumRecord> t_liveEnums;

        // Global scan aggregates (thread-safe via mutex; updated on FindClose).
        struct RootAggregate
        {
            uint32_t directories = 0;
            uint32_t files = 0;
            uint32_t odf = 0;
            uint32_t bzn = 0;
            uint32_t trn = 0;
            uint32_t des = 0;
            uint32_t ini = 0;
        };
        std::mutex g_AggMutex;
        std::unordered_map<std::string, RootAggregate> g_RootAgg;
        std::atomic<uint64_t> g_ScanStartTicks{ 0 };
        std::atomic<uint32_t> g_TotalFindFirst{ 0 };
        std::atomic<uint32_t> g_TotalFindNext{ 0 };
        std::atomic<uint32_t> g_TotalGetAttributes{ 0 };
        std::atomic<bool> g_ScanActive{ false };
        std::atomic<bool> g_Suppress{ false };

        std::string NarrowLower(std::string s)
        {
            for (char& c : s) c = static_cast<char>(::tolower(static_cast<unsigned char>(c)));
            return s;
        }

        std::string PatternToRoot(const std::wstring& pat)
        {
            if (pat.empty()) return "unknown";
            char buf[MAX_PATH * 2] = {};
            WideCharToMultiByte(CP_UTF8, 0, pat.c_str(), -1, buf, sizeof(buf), nullptr, nullptr);
            std::string s(buf);
            auto lower = NarrowLower(s);
            if (lower.find("workshop") != std::string::npos || lower.find("301650") != std::string::npos)
                return "workshop/content/301650";
            if (lower.find("\\addon") != std::string::npos || lower.find("/addon") != std::string::npos)
                return "addon";
            if (lower.find("\\mods") != std::string::npos || lower.find("/mods") != std::string::npos)
                return "mods";
            if (lower.find("packaged_mods") != std::string::npos)
                return "packaged_mods";
            if (lower.find("bz_assets") != std::string::npos)
                return "BZ_ASSETS";
            // Fall back to parent directory via string scan (no filesystem call to avoid re-entrancy).
            size_t sep = s.find_last_of("\\/");
            if (sep != std::string::npos && sep > 0)
            {
                size_t prev = s.find_last_of("\\/", sep - 1);
                if (prev != std::string::npos) return s.substr(0, sep);
                return s.substr(0, sep);
            }
            return s.substr(0, 64);
        }

        void CountExtension(RootAggregate& agg, const std::wstring& name)
        {
            if (name.empty()) return;
            size_t dot = name.find_last_of(L'.');
            if (dot == std::wstring::npos || dot + 1 >= name.size()) return;
            std::wstring ext = name.substr(dot);
            for (auto& c : ext) c = static_cast<wchar_t>(::towlower(c));
            if (ext == L".odf") ++agg.odf;
            else if (ext == L".bzn") ++agg.bzn;
            else if (ext == L".trn") ++agg.trn;
            else if (ext == L".des") ++agg.des;
            else if (ext == L".ini") ++agg.ini;
        }

        // IAT patch helper (same as file_io_hooks.cpp, trimmed).
        bool PatchIAT(HMODULE mod, const char* func, void* replacement, void** original)
        {
            if (!mod || !func || !replacement) return false;
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(mod);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE) return false;
            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<uint8_t*>(mod) + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE) return false;
            const DWORD rva = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
            if (!rva) return false;
            auto* desc = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(reinterpret_cast<uint8_t*>(mod) + rva);
            for (; desc->Name; ++desc)
            {
                auto* origThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(reinterpret_cast<uint8_t*>(mod) + (desc->OriginalFirstThunk ? desc->OriginalFirstThunk : desc->FirstThunk));
                auto* thunk = reinterpret_cast<IMAGE_THUNK_DATA*>(reinterpret_cast<uint8_t*>(mod) + desc->FirstThunk);
                for (; origThunk->u1.AddressOfData; ++origThunk, ++thunk)
                {
                    if (IMAGE_SNAP_BY_ORDINAL(origThunk->u1.Ordinal)) continue;
                    auto* byName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(reinterpret_cast<uint8_t*>(mod) + origThunk->u1.AddressOfData);
                    if (std::strcmp(reinterpret_cast<const char*>(byName->Name), func) != 0) continue;
                    auto** iat = reinterpret_cast<void**>(&thunk->u1.Function);
                    DWORD old = 0;
                    if (!VirtualProtect(iat, sizeof(void*), PAGE_READWRITE, &old)) return false;
                    if (original && *original == nullptr) *original = *iat;
                    *iat = replacement;
                    VirtualProtect(iat, sizeof(void*), old, &old);
                    return true;
                }
            }
            return false;
        }

        // Re-entrancy guard: hooks must not re-enter themselves via helper
        // string/filesystem calls that may themselves call FindFirst/GetAttributes.
        thread_local bool t_InHook = false;
        struct ReentryGuard
        {
            bool entered = false;
            ReentryGuard() { if (!t_InHook) { t_InHook = true; entered = true; } }
            ~ReentryGuard() { if (entered) t_InHook = false; }
            bool active() const { return entered; }
        };

        void SetSuppressImpl(bool s) noexcept { g_Suppress.store(s, std::memory_order_relaxed); }

        // Hook implementations ------------------------------------------------
        HANDLE WINAPI Hooked_FindFirstFileW(LPCWSTR pattern, LPWIN32_FIND_DATAW data)
        {
            if (!g_RealFindFirstFileW)
                return INVALID_HANDLE_VALUE;
            const HANDLE h = g_RealFindFirstFileW(pattern, data);
            if (!UiPerf::IsEnabled() || g_Suppress.load(std::memory_order_relaxed)) return h;
            if (t_InHook) return h;
            ReentryGuard guard;
            if (!guard.active()) return h;
            g_TotalFindFirst.fetch_add(1, std::memory_order_relaxed);
            if (h != INVALID_HANDLE_VALUE)
            {
                t_liveEnums[h] = EnumRecord{ pattern ? pattern : L"" };
                // Also count the first result's extension.
                if (data)
                {
                    const std::string root = PatternToRoot(pattern ? pattern : L"");
                    std::lock_guard<std::mutex> lock(g_AggMutex);
                    RootAggregate& agg = g_RootAgg[root];
                    if (data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                        ++agg.directories;
                    else
                    {
                        ++agg.files;
                        CountExtension(agg, data->cFileName);
                    }
                }
            }
            if (!g_ScanActive.load(std::memory_order_relaxed) && pattern)
            {
                g_ScanActive.store(true, std::memory_order_relaxed);
                g_ScanStartTicks.store(UiPerf::NowTicks(), std::memory_order_relaxed);
            }
            return h;
        }

        HANDLE WINAPI Hooked_FindFirstFileA(LPCSTR pattern, LPWIN32_FIND_DATAA data)
        {
            if (!g_RealFindFirstFileA)
                return INVALID_HANDLE_VALUE;
            const HANDLE h = g_RealFindFirstFileA(pattern, data);
            if (!UiPerf::IsEnabled() || g_Suppress.load(std::memory_order_relaxed)) return h;
            if (t_InHook) return h;
            ReentryGuard guard;
            if (!guard.active()) return h;
            g_TotalFindFirst.fetch_add(1, std::memory_order_relaxed);
            if (h != INVALID_HANDLE_VALUE && pattern && data)
            {
                // Convert to wide for unified handling.
                wchar_t wpat[MAX_PATH * 2] = {};
                MultiByteToWideChar(CP_ACP, 0, pattern, -1, wpat, _countof(wpat));
                wchar_t wname[MAX_PATH] = {};
                MultiByteToWideChar(CP_ACP, 0, data->cFileName, -1, wname, _countof(wname));
                t_liveEnums[h] = EnumRecord{ wpat };
                const std::string root = PatternToRoot(wpat);
                std::lock_guard<std::mutex> lock(g_AggMutex);
                RootAggregate& agg = g_RootAgg[root];
                if (data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    ++agg.directories;
                else
                {
                    ++agg.files;
                    CountExtension(agg, wname);
                }
            }
            if (!g_ScanActive.load(std::memory_order_relaxed) && pattern)
            {
                g_ScanActive.store(true, std::memory_order_relaxed);
                g_ScanStartTicks.store(UiPerf::NowTicks(), std::memory_order_relaxed);
            }
            return h;
        }

        BOOL WINAPI Hooked_FindNextFileW(HANDLE h, LPWIN32_FIND_DATAW data)
        {
            if (!g_RealFindNextFileW) return FALSE;
            const BOOL ok = g_RealFindNextFileW(h, data);
            if (!UiPerf::IsEnabled() || g_Suppress.load(std::memory_order_relaxed) || !ok || !data) return ok;
            if (t_InHook) return ok;
            ReentryGuard guard;
            if (!guard.active()) return ok;
            g_TotalFindNext.fetch_add(1, std::memory_order_relaxed);
            auto it = t_liveEnums.find(h);
            const std::wstring pat = (it != t_liveEnums.end()) ? it->second.pattern : L"";
            const std::string root = PatternToRoot(pat);
            std::lock_guard<std::mutex> lock(g_AggMutex);
            RootAggregate& agg = g_RootAgg[root];
            if (data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                ++agg.directories;
            else
            {
                ++agg.files;
                CountExtension(agg, data->cFileName);
            }
            return ok;
        }

        BOOL WINAPI Hooked_FindNextFileA(HANDLE h, LPWIN32_FIND_DATAA data)
        {
            if (!g_RealFindNextFileA) return FALSE;
            const BOOL ok = g_RealFindNextFileA(h, data);
            if (!UiPerf::IsEnabled() || g_Suppress.load(std::memory_order_relaxed) || !ok || !data) return ok;
            if (t_InHook) return ok;
            ReentryGuard guard;
            if (!guard.active()) return ok;
            g_TotalFindNext.fetch_add(1, std::memory_order_relaxed);
            auto it = t_liveEnums.find(h);
            const std::wstring pat = (it != t_liveEnums.end()) ? it->second.pattern : L"";
            const std::string root = PatternToRoot(pat);
            wchar_t wname[MAX_PATH] = {};
            MultiByteToWideChar(CP_ACP, 0, data->cFileName, -1, wname, _countof(wname));
            std::lock_guard<std::mutex> lock(g_AggMutex);
            RootAggregate& agg = g_RootAgg[root];
            if (data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                ++agg.directories;
            else
            {
                ++agg.files;
                CountExtension(agg, wname);
            }
            return ok;
        }

        BOOL WINAPI Hooked_FindClose(HANDLE h)
        {
            if (!g_RealFindClose) return FALSE;
            if (UiPerf::IsEnabled() && !t_InHook)
                t_liveEnums.erase(h);
            return g_RealFindClose(h);
        }

        DWORD WINAPI Hooked_GetFileAttributesW(LPCWSTR path)
        {
            if (!g_RealGetFileAttributesW) return INVALID_FILE_ATTRIBUTES;
            const DWORD r = g_RealGetFileAttributesW(path);
            if (!UiPerf::IsEnabled() || g_Suppress.load(std::memory_order_relaxed) || t_InHook) return r;
            g_TotalGetAttributes.fetch_add(1, std::memory_order_relaxed);
            return r;
        }

        DWORD WINAPI Hooked_GetFileAttributesA(LPCSTR path)
        {
            if (!g_RealGetFileAttributesA) return INVALID_FILE_ATTRIBUTES;
            const DWORD r = g_RealGetFileAttributesA(path);
            if (!UiPerf::IsEnabled() || g_Suppress.load(std::memory_order_relaxed) || t_InHook) return r;
            g_TotalGetAttributes.fetch_add(1, std::memory_order_relaxed);
            return r;
        }

        int PatchModule(HMODULE mod, const wchar_t* label)
        {
            int n = 0;
            n += PatchIAT(mod, "FindFirstFileW", reinterpret_cast<void*>(Hooked_FindFirstFileW), reinterpret_cast<void**>(&g_RealFindFirstFileW)) ? 1 : 0;
            n += PatchIAT(mod, "FindFirstFileA", reinterpret_cast<void*>(Hooked_FindFirstFileA), reinterpret_cast<void**>(&g_RealFindFirstFileA)) ? 1 : 0;
            n += PatchIAT(mod, "FindNextFileW", reinterpret_cast<void*>(Hooked_FindNextFileW), reinterpret_cast<void**>(&g_RealFindNextFileW)) ? 1 : 0;
            n += PatchIAT(mod, "FindNextFileA", reinterpret_cast<void*>(Hooked_FindNextFileA), reinterpret_cast<void**>(&g_RealFindNextFileA)) ? 1 : 0;
            n += PatchIAT(mod, "FindClose", reinterpret_cast<void*>(Hooked_FindClose), reinterpret_cast<void**>(&g_RealFindClose)) ? 1 : 0;
            n += PatchIAT(mod, "GetFileAttributesW", reinterpret_cast<void*>(Hooked_GetFileAttributesW), reinterpret_cast<void**>(&g_RealGetFileAttributesW)) ? 1 : 0;
            n += PatchIAT(mod, "GetFileAttributesA", reinterpret_cast<void*>(Hooked_GetFileAttributesA), reinterpret_cast<void**>(&g_RealGetFileAttributesA)) ? 1 : 0;
            LogShimA(LogLevel::Info, "uiperf-scan",
                "file scan hooks on %ls: patched=%d", label ? label : L"<unknown>", n);
            return n;
        }
    } // namespace

    void Install() noexcept
    {
        if (g_Installed.exchange(true))
            return;

        // Only install IAT hooks when UiPerf is enabled; otherwise we'd pay the
        // indirection cost on every FindFirstFile even when OFF.
        if (!UiPerf::IsEnabled())
        {
            LogShimA(LogLevel::Info, "uiperf-scan", "UiPerf file scan hooks not installed (logging OFF)");
            return;
        }

        HMODULE main = GetModuleHandleW(nullptr);
        if (main) PatchModule(main, L"battlezone98redux.exe");

        HMODULE ogre = GetModuleHandleA("OgreMain.dll");
        if (ogre)
        {
            // Ogre itself does filesystem enumeration for ResourceGroup.
            PatchModule(ogre, L"OgreMain.dll");
        }

        // Also patch the CRTs so std::filesystem enumeration is captured.
        // Do NOT patch kernel32.dll: its forwarded exports re-enter via kernelbase
        // and cause infinite recursion through the hook's own helpers.
        for (const wchar_t* dll : { L"msvcr120.dll", L"ucrtbase.dll" })
        {
            if (HMODULE m = GetModuleHandleW(dll))
                PatchModule(m, dll);
        }

        g_ScanStartTicks.store(UiPerf::NowTicks(), std::memory_order_relaxed);
        LogShimA(LogLevel::Info, "uiperf-scan", "file scan hooks installed");
    }

    void Shutdown() noexcept
    {
        if (!g_Installed.load()) return;
        if (!UiPerf::IsEnabled()) return;
        const uint64_t start = g_ScanStartTicks.load();
        const double elapsed = start ? UiPerf::TicksToMs(UiPerf::NowTicks() - start) : 0.0;
        std::lock_guard<std::mutex> lock(g_AggMutex);
        for (auto& kv : g_RootAgg)
        {
            UiPerf::ScanCounters sc;
            sc.root = kv.first.c_str();
            sc.directories = kv.second.directories;
            sc.files = kv.second.files;
            sc.filesOpened = kv.second.files; // best-effort: files == opened for enumeration path
            sc.odf = kv.second.odf;
            sc.bzn = kv.second.bzn;
            sc.trn = kv.second.trn;
            sc.des = kv.second.des;
            sc.ini = kv.second.ini;
            sc.elapsedMs = elapsed;
            UiPerf::RecordScan(sc);
        }
        LogShimA(LogLevel::Info, "uiperf-scan",
            "scan summary: FindFirst=%u FindNext=%u GetFileAttributes=%u roots=%zu elapsed=%.2fms",
            g_TotalFindFirst.load(), g_TotalFindNext.load(), g_TotalGetAttributes.load(),
            g_RootAgg.size(), elapsed);
    }

    void SetSuppress(bool suppress) noexcept { g_Suppress.store(suppress, std::memory_order_relaxed); }

} // namespace BZROpenShim::UiFileScan
