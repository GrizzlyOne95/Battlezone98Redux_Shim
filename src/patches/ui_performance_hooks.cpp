// ui_performance_hooks.cpp
// BZR Open Shim - UI performance hook glue
//
// Wires native shell + Ogre + file-scan sites into UiPerf.  The native shell
// factory manager is FUN_007c7ad0 (REDUX_SHELL_UI_RE_MAP.md); the pending
// transition path is FUN_007c7820 -> FUN_007c7070.  Shell request is
// FUN_007c7930, back is FUN_007c79a0.  Ogre ResourceGroupManager lives in
// OgreMain.dll and is reachable through the same resolve mechanism used by the
// shader cache and collision guard.  This file installs thin detours at
// shell and Ogre sites plus bookkeeping for scan/MP teardown phases.
//
// SPDX-License-Identifier: MIT

#include "ui_performance_hooks.h"
#include "ui_performance.h"
#include "ui_file_scan_hooks.h"
#include "hook_engine.h"
#include "patcher.h"
#include "shim_log.h"
#include "BZROpenShim.h"

#include <Windows.h>
#include <process.h>
#include <intrin.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>

namespace BZROpenShim::UiPerfHooks
{
    namespace
    {
        std::atomic<bool> g_Installed{ false };

        // Shell manager capture for auto-matrix (set on first ShellRequest).
        void* g_ShellManager = nullptr;
        std::atomic<bool> g_AutoMatrixRunning{ false };
        std::atomic<bool> g_AutoMatrixEnabled{ false };

        // Per-operation active timers (single-threaded shell path, but Ogre
        // may be called from load thread; guard with mutex).
        struct ActiveOp
        {
            uint64_t startTicks = 0;
            std::string group;
        };
        std::mutex g_ActiveMutex;
        std::unordered_map<std::string, ActiveOp> g_ActiveOps;

        // Re-entrancy guard for discovery scopes.
        thread_local int t_modDiscoveryDepth = 0;
        thread_local uint64_t t_modDiscoveryStart = 0;
        std::string g_ModDiscoveryContext;

        // Shell hook trampolines and state.
        struct ShellHook
        {
            void* trampoline = nullptr;
            uint8_t origBytes[16] = {};
            size_t origLen = 0;
            uintptr_t target = 0;
        };
        ShellHook g_ShellRequestHook;
        ShellHook g_ShellTransitionHook;
        ShellHook g_ShellBackHook;
        ShellHook g_BuildIaResourcesHook;
        ShellHook g_InstantActionCtorHook;
        ShellHook g_BuildMainResourcesHook;
        ShellHook g_BuildMpResourcesHook;
        ShellHook g_MainScreenCtorHook;
        ShellHook g_MainScreenDtorHook;
        ShellHook g_MultiplayerLobbyCtorHook;
        ShellHook g_MultiplayerLobbyDtorHook;
        std::atomic<int> g_ShellHookInstallState{ 0 }; // 0=waiting, 1=installing, 2=finished
        std::atomic<uint64_t> g_ShellRequestStart{ 0 };
        std::atomic<int> g_PendingScreenId{ -1 };
        std::atomic<bool> g_ShellTransitionInFlight{ false };

        // Trigger-file reachability: file is polled on a worker thread every
        // ~200ms (conservative, not per-frame) with SetSuppress so it never
        // appears in SCAN. Actual OnClick is dispatched on the main thread
        // via window message, so UI objects are only touched on the game thread.
        static const UINT WM_UI_TRIGGER = WM_APP + 0x42B;
        std::atomic<HWND> g_Hwnd{ nullptr };
        std::atomic<WNDPROC> g_OrigWndProc{ nullptr };
        std::atomic<bool> g_TriggerPollRunning{ false };
        std::atomic<bool> g_TriggerMessagePending{ false };
        HANDLE g_TriggerPollThread = nullptr;
        HANDLE g_TriggerStopEvent = nullptr;

        void TryHandleTriggerFileOnMainThread();
        void TryInstallDeferredSteamShellHooksOnMainThread();
        static void StopTriggerDelivery() noexcept;

        struct FindGameWindowCtx
        {
            HWND found = nullptr;
        };

        static BOOL CALLBACK EnumFindGameWindowCB(HWND h, LPARAM context)
        {
            auto* c = reinterpret_cast<FindGameWindowCtx*>(context);
            char title[256] = {};
            GetWindowTextA(h, title, sizeof(title));
            if (std::strstr(title, "Battlezone 98 Redux"))
            {
                c->found = h;
                return FALSE;
            }
            return TRUE;
        }

        static HWND FindGameWindowOnCurrentThread()
        {
            FindGameWindowCtx context;
            EnumThreadWindows(GetCurrentThreadId(), EnumFindGameWindowCB,
                              reinterpret_cast<LPARAM>(&context));
            return context.found;
        }

        LRESULT CALLBACK NewWndProc(HWND h, UINT msg, WPARAM w, LPARAM l)
        {
            if (msg == WM_UI_TRIGGER)
            {
                g_TriggerMessagePending.store(false, std::memory_order_release);
                LogShimA(LogLevel::Info, "uiperf-harness",
                    "[UIPERF][HARNESS] custom main-thread event delivered hwnd=0x%p tid=%lu",
                    h, static_cast<unsigned long>(GetCurrentThreadId()));
                TryHandleTriggerFileOnMainThread();
                return 0;
            }
            const WNDPROC original = g_OrigWndProc.load(std::memory_order_acquire);
            return original ? CallWindowProcA(original, h, msg, w, l)
                            : DefWindowProcA(h, msg, w, l);
        }

        static void EnsureGameWindowSubclassOnMainThread()
        {
            if (g_Hwnd.load(std::memory_order_acquire))
                return;

            const HWND window = FindGameWindowOnCurrentThread();
            if (!window)
                return;

            SetLastError(ERROR_SUCCESS);
            const auto previous = reinterpret_cast<WNDPROC>(
                SetWindowLongPtrA(window, GWLP_WNDPROC,
                                  reinterpret_cast<LONG_PTR>(&NewWndProc)));
            if (!previous && GetLastError() != ERROR_SUCCESS)
            {
                LogShimA(LogLevel::Warn, "uiperf-harness",
                    "[UIPERF][HARNESS] failed to subclass game window error=%lu",
                    static_cast<unsigned long>(GetLastError()));
                return;
            }

            g_OrigWndProc.store(previous, std::memory_order_release);
            g_Hwnd.store(window, std::memory_order_release);
            LogShimA(LogLevel::Info, "uiperf-harness",
                "[UIPERF][HARNESS] game window subclassed hwnd=0x%p tid=%lu original=0x%p",
                window, static_cast<unsigned long>(GetCurrentThreadId()), previous);
        }

        // PeekMessageA is imported by Redux and runs on the frontend/UI thread.
        // It is used only to install our subclass from the owning thread. Trigger
        // file polling remains on the low-frequency helper below.
        using PFN_PeekMessageA = BOOL(WINAPI*)(LPMSG, HWND, UINT, UINT, UINT);
        PFN_PeekMessageA g_RealPeekMessageA = nullptr;
        void** g_PeekMessageAIat = nullptr;
        BOOL WINAPI Hooked_PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
        {
            EnsureGameWindowSubclassOnMainThread();
            TryInstallDeferredSteamShellHooksOnMainThread();
            return g_RealPeekMessageA
                ? g_RealPeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg)
                : FALSE;
        }

        bool PatchImportIAT(HMODULE mod, const char* func, void* newFunc,
                            void** orig, void*** patchedSlot)
        {
            if (!mod || !func || !newFunc) return false;
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(mod);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE) return false;
            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<uint8_t*>(mod) + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE) return false;
            DWORD rva = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
            if (!rva) return false;
            auto* desc = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(reinterpret_cast<uint8_t*>(mod) + rva);
            for (; desc->Name; ++desc)
            {
                auto* thunk = reinterpret_cast<IMAGE_THUNK_DATA*>(reinterpret_cast<uint8_t*>(mod) + desc->FirstThunk);
                auto* origThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(reinterpret_cast<uint8_t*>(mod) + (desc->OriginalFirstThunk ? desc->OriginalFirstThunk : desc->FirstThunk));
                for (; origThunk->u1.AddressOfData; ++origThunk, ++thunk)
                {
                    if (IMAGE_SNAP_BY_ORDINAL(origThunk->u1.Ordinal)) continue;
                    auto* byName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(reinterpret_cast<uint8_t*>(mod) + origThunk->u1.AddressOfData);
                    if (strcmp((const char*)byName->Name, func) != 0) continue;
                    void** iat = reinterpret_cast<void**>(&thunk->u1.Function);
                    DWORD old = 0;
                    if (!VirtualProtect(iat, sizeof(void*), PAGE_READWRITE, &old)) return false;
                    if (orig && !*orig) *orig = *iat;
                    *iat = newFunc;
                    VirtualProtect(iat, sizeof(void*), old, &old);
                    FlushInstructionCache(GetCurrentProcess(), iat, sizeof(void*));
                    if (patchedSlot) *patchedSlot = iat;
                    return true;
                }
            }
            return false;
        }

        using FnOgreGroupOp = void(__thiscall*)(void*, const std::string&);
        FnOgreGroupOp g_RealOgreClear = nullptr;
        FnOgreGroupOp g_RealOgreInitialise = nullptr;
        void** g_OgreClearIat = nullptr;
        void** g_OgreInitialiseIat = nullptr;

        void __fastcall Hooked_OgreClear(void* self, void* /*edx*/,
                                         const std::string& group)
        {
            OnOgreClearResourceGroup_Begin(group.c_str());
            if (g_RealOgreClear) g_RealOgreClear(self, group);
            OnOgreClearResourceGroup_End(group.c_str());
        }

        void __fastcall Hooked_OgreInitialise(void* self, void* /*edx*/,
                                              const std::string& group)
        {
            // The caller is the open question: which stock site decides the
            // group must be rebuilt. Record it so each route's rebuild can be
            // attributed to a call site rather than inferred from nesting.
            if (UiPerf::IsEnabled())
                UiPerf::Log("[UIPERF][OGRE] initialiseResourceGroup group=%s caller=0x%p",
                            group.c_str(), _ReturnAddress());
            OnOgreInitialiseResourceGroup_Begin(group.c_str());
            if (g_RealOgreInitialise) g_RealOgreInitialise(self, group);
            OnOgreInitialiseResourceGroup_End(group.c_str());
        }

        static void RestoreImportSlot(void** slot, void* hook, void* original) noexcept
        {
            if (!slot || !hook || !original) return;
            DWORD oldProtect = 0;
            if (!VirtualProtect(slot, sizeof(void*), PAGE_READWRITE, &oldProtect))
                return;
            InterlockedCompareExchangePointer(
                reinterpret_cast<PVOID volatile*>(slot), original, hook);
            DWORD ignored = 0;
            VirtualProtect(slot, sizeof(void*), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), slot, sizeof(void*));
        }

        static bool BuildTriggerFilePath(char (&path)[MAX_PATH])
        {
            char gamePath[MAX_PATH] = {};
            if (!GetModuleFileNameA(nullptr, gamePath, MAX_PATH))
                return false;
            char* slash = std::strrchr(gamePath, '\\');
            if (!slash)
                return false;
            *(slash + 1) = '\0';
            return _snprintf_s(path, MAX_PATH, _TRUNCATE,
                               "%suiperf_trigger.txt", gamePath) >= 0;
        }

        static bool TriggerFileExistsSuppressed()
        {
            char triggerPath[MAX_PATH] = {};
            if (!BuildTriggerFilePath(triggerPath))
                return false;
            UiFileScan::SetSuppress(true);
            const DWORD attributes = GetFileAttributesA(triggerPath);
            UiFileScan::SetSuppress(false);
            return attributes != INVALID_FILE_ATTRIBUTES &&
                   (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
        }

        static unsigned __stdcall TriggerPollThreadProc(void*)
        {
            uint64_t samples = 0;
            double activeMs = 0.0;
            double maximumUs = 0.0;
            uint64_t posts = 0;
            LogShimA(LogLevel::Info, "uiperf-harness",
                "[UIPERF][HARNESS] trigger polling helper entered tid=%lu running=%d",
                static_cast<unsigned long>(GetCurrentThreadId()),
                g_TriggerPollRunning.load(std::memory_order_acquire) ? 1 : 0);

            while (g_TriggerPollRunning.load(std::memory_order_acquire))
            {
                if (WaitForSingleObject(g_TriggerStopEvent, 200) == WAIT_OBJECT_0)
                    break;
                if (!g_TriggerPollRunning.load(std::memory_order_acquire))
                    break;

                const uint64_t start = UiPerf::NowTicks();
                const bool exists = TriggerFileExistsSuppressed();
                const double elapsedMs = UiPerf::TicksToMs(UiPerf::NowTicks() - start);
                ++samples;
                activeMs += elapsedMs;
                maximumUs = (std::max)(maximumUs, elapsedMs * 1000.0);

                if (exists)
                {
                    const HWND window = g_Hwnd.load(std::memory_order_acquire);
                    if (window && !g_TriggerMessagePending.exchange(
                                      true, std::memory_order_acq_rel))
                    {
                        if (PostMessageA(window, WM_UI_TRIGGER, 0, 0))
                        {
                            ++posts;
                            LogShimA(LogLevel::Info, "uiperf-harness",
                                "[UIPERF][HARNESS] trigger file detected; posted main-thread event hwnd=0x%p",
                                window);
                        }
                        else
                        {
                            g_TriggerMessagePending.store(false, std::memory_order_release);
                        }
                    }
                }

                if (samples == 25 || (samples > 25 && (samples % 50) == 0))
                {
                    LogShimA(LogLevel::Info, "uiperf-harness",
                        "[UIPERF][HARNESS] poll samples=%llu active=%.3fms avg=%.3fus max=%.3fus posts=%llu",
                        static_cast<unsigned long long>(samples), activeMs,
                        samples ? activeMs * 1000.0 / static_cast<double>(samples) : 0.0,
                        maximumUs, static_cast<unsigned long long>(posts));
                }
            }
            LogShimA(LogLevel::Info, "uiperf-harness",
                "[UIPERF][HARNESS] trigger polling helper exited tid=%lu samples=%llu posts=%llu running=%d",
                static_cast<unsigned long>(GetCurrentThreadId()),
                static_cast<unsigned long long>(samples),
                static_cast<unsigned long long>(posts),
                g_TriggerPollRunning.load(std::memory_order_acquire) ? 1 : 0);
            return 0;
        }

        static bool StartTriggerDelivery()
        {
            HMODULE mainModule = GetModuleHandleW(nullptr);
            if (!PatchImportIAT(mainModule, "PeekMessageA",
                                reinterpret_cast<void*>(&Hooked_PeekMessageA),
                                reinterpret_cast<void**>(&g_RealPeekMessageA),
                                &g_PeekMessageAIat))
            {
                LogShimA(LogLevel::Warn, "uiperf-harness",
                    "[UIPERF][HARNESS] PeekMessageA UI-thread seam was not installed");
                return false;
            }

            g_TriggerStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
            if (!g_TriggerStopEvent)
            {
                LogShimA(LogLevel::Warn, "uiperf-harness",
                    "[UIPERF][HARNESS] trigger stop event creation failed error=%lu",
                    static_cast<unsigned long>(GetLastError()));
                StopTriggerDelivery();
                return false;
            }

            g_TriggerPollRunning.store(true, std::memory_order_release);
            const uintptr_t thread = _beginthreadex(
                nullptr, 0, TriggerPollThreadProc, nullptr, 0, nullptr);
            if (!thread)
            {
                g_TriggerPollRunning.store(false, std::memory_order_release);
                LogShimA(LogLevel::Warn, "uiperf-harness",
                    "[UIPERF][HARNESS] trigger polling helper could not start");
                StopTriggerDelivery();
                return false;
            }
            g_TriggerPollThread = reinterpret_cast<HANDLE>(thread);
            LogShimA(LogLevel::Info, "uiperf-harness",
                "[UIPERF][HARNESS] idle trigger delivery armed poll_interval=200ms");
            return true;
        }

        static void StopTriggerDelivery() noexcept
        {
            g_TriggerPollRunning.store(false, std::memory_order_release);
            if (g_TriggerStopEvent)
                SetEvent(g_TriggerStopEvent);
            if (g_TriggerPollThread)
            {
                WaitForSingleObject(g_TriggerPollThread, INFINITE);
                CloseHandle(g_TriggerPollThread);
                g_TriggerPollThread = nullptr;
            }

            const HWND window = g_Hwnd.exchange(nullptr, std::memory_order_acq_rel);
            const WNDPROC original = g_OrigWndProc.exchange(
                nullptr, std::memory_order_acq_rel);
            if (window && original && IsWindow(window))
            {
                const auto current = reinterpret_cast<WNDPROC>(
                    GetWindowLongPtrA(window, GWLP_WNDPROC));
                if (current == &NewWndProc)
                {
                    SetWindowLongPtrA(window, GWLP_WNDPROC,
                                      reinterpret_cast<LONG_PTR>(original));
                }
                else if (current)
                {
                    LogShimA(LogLevel::Warn, "uiperf-harness",
                        "[UIPERF][HARNESS] window procedure changed after install; preserving newer owner current=0x%p",
                        current);
                }
            }

            if (g_PeekMessageAIat && g_RealPeekMessageA)
            {
                DWORD oldProtect = 0;
                if (VirtualProtect(g_PeekMessageAIat, sizeof(void*),
                                   PAGE_READWRITE, &oldProtect))
                {
                    InterlockedCompareExchangePointer(
                        reinterpret_cast<PVOID volatile*>(g_PeekMessageAIat),
                        reinterpret_cast<void*>(g_RealPeekMessageA),
                        reinterpret_cast<void*>(&Hooked_PeekMessageA));
                    DWORD ignored = 0;
                    VirtualProtect(g_PeekMessageAIat, sizeof(void*),
                                   oldProtect, &ignored);
                    FlushInstructionCache(GetCurrentProcess(),
                                          g_PeekMessageAIat, sizeof(void*));
                }
            }
            g_PeekMessageAIat = nullptr;
            g_RealPeekMessageA = nullptr;
            g_TriggerMessagePending.store(false, std::memory_order_release);

            if (g_TriggerStopEvent)
            {
                CloseHandle(g_TriggerStopEvent);
                g_TriggerStopEvent = nullptr;
            }
        }

        bool InstallInlineHook(ShellHook& hook, uintptr_t target, void* detour, size_t minLen, const uint8_t* expectedPrefix = nullptr);

        void BeginOp(const char* key, const char* group)
        {
            if (!UiPerf::IsEnabled()) return;
            std::lock_guard<std::mutex> lock(g_ActiveMutex);
            ActiveOp& op = g_ActiveOps[key];
            op.startTicks = UiPerf::NowTicks();
            op.group = group ? group : "";
        }

        double EndOp(const char* key, const char** outGroup)
        {
            if (!UiPerf::IsEnabled()) return 0.0;
            std::lock_guard<std::mutex> lock(g_ActiveMutex);
            auto it = g_ActiveOps.find(key);
            if (it == g_ActiveOps.end() || it->second.startTicks == 0)
                return 0.0;
            const double ms = UiPerf::TicksToMs(UiPerf::NowTicks() - it->second.startTicks);
            if (outGroup)
            {
                // Return pointer to owned storage; valid until next BeginOp on same key.
                *outGroup = it->second.group.c_str();
            }
            it->second.startTicks = 0;
            return ms;
        }

        // Shell detour state.
        void* g_OrigShellRequest = nullptr;      // FUN_007c7930
        void* g_OrigShellTransition = nullptr;   // FUN_007c7070
        void* g_OrigShellBack = nullptr;         // FUN_007c79a0

        // Preserve original bytes so detour can trampoline.
        uint8_t g_ShellRequestPatch[5] = {};
        uint8_t g_ShellRequestOrig[5] = {};
        uint8_t g_ShellTransitionPatch[5] = {};
        uint8_t g_ShellTransitionOrig[5] = {};
        uintptr_t g_ShellRequestAddr = 0;
        uintptr_t g_ShellTransitionAddr = 0;
        uintptr_t g_ShellBackAddr = 0;

        // Minimal 5-byte JMP detour (relative).  Reads/writes are done with
        // VirtualProtect + FlushInstructionCache.
        bool InstallJmp5(uintptr_t target, void* detour, uint8_t* outOrig)
        {
            if (!target || !detour) return false;
            DWORD old = 0;
            if (!VirtualProtect(reinterpret_cast<void*>(target), 5, PAGE_EXECUTE_READWRITE, &old))
                return false;
            if (outOrig)
                memcpy(outOrig, reinterpret_cast<void*>(target), 5);
            const int32_t rel = static_cast<int32_t>(reinterpret_cast<uintptr_t>(detour) - (target + 5));
            uint8_t patch[5] = { 0xE9, 0,0,0,0 };
            memcpy(patch+1, &rel, 4);
            memcpy(reinterpret_cast<void*>(target), patch, 5);
            FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<void*>(target), 5);
            DWORD ign = 0;
            VirtualProtect(reinterpret_cast<void*>(target), 5, old, &ign);
            return true;
        }

        // Forward decls for detour thunks (naked trampolines delegate to C++ helpers).
        void OnShellRequestDetour(int screenId);
        void OnShellTransitionDetour();
        void OnShellBackDetour();

        // Ogre ResourceGroupManager detours via IAT-style vtable patching is
        // deferred: the startup path resolves OgreMain exports and patches the
        // import table entries that the game uses to call them.  For the initial
        // profiling cut we rely on the explicit Begin/End helpers called from
        // existing hook sites (collision guard, flag preview, shader cache) plus
        // a polling observer that samples ResourceGroupManager::isResourceGroupInUse.
        // This keeps the first commit safe while still producing [UIPERF][OGRE]
        // attribution from the paths the game actually exercises.
    } // namespace

    void OnOgreInitialiseResourceGroup_Begin(const char* group)
    {
        BeginOp("initialiseResourceGroup", group);
        if (UiPerf::IsEnabled())
        {
            UiPerf::Log("[UIPERF] BEGIN Ogre::initialiseResourceGroup group=%s", group ? group : "<none>");
            UiPerf::Heartbeat("OgreInitialise_Begin");
        }
    }

    void OnOgreInitialiseResourceGroup_End(const char* group)
    {
        const char* activeGroup = nullptr;
        const double ms = EndOp("initialiseResourceGroup", &activeGroup);
        const char* g = group ? group : (activeGroup ? activeGroup : "<none>");
        UiPerf::RecordOgreResourceOp("initialiseResourceGroup", g, ms);
        UiPerf::Heartbeat("OgreInitialise_End");
    }

    void OnOgreLoadResourceGroup_Begin(const char* group)  { BeginOp("loadResourceGroup", group); }
    void OnOgreLoadResourceGroup_End(const char* group)
    {
        const char* ag = nullptr; const double ms = EndOp("loadResourceGroup", &ag);
        UiPerf::RecordOgreResourceOp("loadResourceGroup", group ? group : (ag?ag:"<none>"), ms);
    }
    void OnOgreUnloadResourceGroup_Begin(const char* group)  { BeginOp("unloadResourceGroup", group); }
    void OnOgreUnloadResourceGroup_End(const char* group)
    {
        const char* ag = nullptr; const double ms = EndOp("unloadResourceGroup", &ag);
        UiPerf::RecordOgreResourceOp("unloadResourceGroup", group ? group : (ag?ag:"<none>"), ms);
    }
    void OnOgreClearResourceGroup_Begin(const char* group)  { BeginOp("clearResourceGroup", group); }
    void OnOgreClearResourceGroup_End(const char* group)
    {
        const char* ag = nullptr; const double ms = EndOp("clearResourceGroup", &ag);
        UiPerf::RecordOgreResourceOp("clearResourceGroup", group ? group : (ag?ag:"<none>"), ms);
    }
    void OnOgreDestroyResourceGroup_Begin(const char* group)  { BeginOp("destroyResourceGroup", group); }
    void OnOgreDestroyResourceGroup_End(const char* group)
    {
        const char* ag = nullptr; const double ms = EndOp("destroyResourceGroup", &ag);
        UiPerf::RecordOgreResourceOp("destroyResourceGroup", group ? group : (ag?ag:"<none>"), ms);
    }
    void OnOgreParseScripts_Begin(const char* group)  { BeginOp("parseResourceGroupScripts", group); }
    void OnOgreParseScripts_End(const char* group, uint32_t scriptsParsed)
    {
        const char* ag = nullptr; const double ms = EndOp("parseResourceGroupScripts", &ag);
        const char* g = group ? group : (ag?ag:"<none>");
        UiPerf::RecordOgreResourceOp("parseResourceGroupScripts", g, ms);
        if (scriptsParsed)
            UiPerf::RecordOgreScriptStats({scriptsParsed, 0, 0, ms});
    }

    void OnModDiscovery_Begin(const char* context)
    {
        if (!UiPerf::IsEnabled()) return;
        if (t_modDiscoveryDepth++ == 0)
        {
            t_modDiscoveryStart = UiPerf::NowTicks();
            g_ModDiscoveryContext = context ? context : "ModDiscovery";
            UiPerf::Log("[UIPERF] BEGIN %s", g_ModDiscoveryContext.c_str());
        }
    }

    void OnModDiscovery_End()
    {
        if (!UiPerf::IsEnabled()) return;
        if (--t_modDiscoveryDepth == 0 && t_modDiscoveryStart != 0)
        {
            const double ms = UiPerf::TicksToMs(UiPerf::NowTicks() - t_modDiscoveryStart);
            UiPerf::Log("[UIPERF] END %s %.2fms", g_ModDiscoveryContext.c_str(), ms);
            t_modDiscoveryStart = 0;
        }
        if (t_modDiscoveryDepth < 0) t_modDiscoveryDepth = 0;
    }

    void OnWorkshopScan_Begin()
    {
        if (!UiPerf::IsEnabled()) return;
        BeginOp("WorkshopScan", "workshop/content/301650");
        UiPerf::Log("[UIPERF] BEGIN WorkshopScan");
    }

    void OnWorkshopScan_End()
    {
        if (!UiPerf::IsEnabled()) return;
        const char* ag = nullptr; const double ms = EndOp("WorkshopScan", &ag);
        UiPerf::Log("[UIPERF] END WorkshopScan %.2fms", ms);
    }

    void OnShellRequest(int screenId)
    {
        UiPerf::NotifyShellRequest(screenId);
    }

    void OnShellTransitionUpdate()
    {
        // Heartbeat at each shell update tick; stall detection will flag long gaps.
        UiPerf::Heartbeat("ShellUpdate");
    }

    void OnMultiplayerShutdown_Begin(const char* phase)
    {
        BeginOp(phase ? phase : "mp_shutdown", phase);
        if (UiPerf::IsEnabled())
            UiPerf::Log("[UIPERF] BEGIN MultiplayerShutdown phase=%s", phase ? phase : "<unknown>");
    }

    void OnMultiplayerShutdown_End(const char* phase)
    {
        const char* ag = nullptr; const double ms = EndOp(phase ? phase : "mp_shutdown", &ag);
        if (UiPerf::IsEnabled())
            UiPerf::Log("[UIPERF] END MultiplayerShutdown phase=%s %.2fms", phase ? phase : "<unknown>", ms);
    }

    namespace
    {
        // ------------------------------------------------------------------
        // Shell detour helpers (thiscall).  Detours receive ECX=this, stack
        // holds screenId for request.  They log, capture manager, then
        // tail-call the original via trampoline.
        // ------------------------------------------------------------------
        using FnShellRequest = void(__thiscall*)(void*, int);
        // FUN_007C7070 is cdecl: (dialog, promoted bool mode) -> bool/int.
        // Its callers clean eight stack bytes after the call. Preserving both
        // arguments and EAX is essential; treating it as void() reconstructs a
        // bogus dialog from stack garbage and prevents the frontend settling.
        using FnShellTransition = int(__cdecl*)(int*, int);
        using FnShellBack = void(__thiscall*)(void*);
        using FnBuildIaResources = void(__thiscall*)(void*);
        using FnInstantActionCtor = void*(__thiscall*)(void*);
        using FnBuildFrontendResources = void(__thiscall*)(void*);
        using FnFrontendCtor = void*(__thiscall*)(void*);
        using FnFrontendDeletingDtor = void*(__thiscall*)(void*, unsigned int);

        // These three "build*Resources" functions are the stock Modable
        // mount-mode setters; see the mount-mode section below. Reporting the
        // mode field they guard on costs nothing and makes every skip visible.
        void ReportModableModeTransition(const char* label, int targetMode,
                                         void* self, int modeBefore);
        int ReadModableMode(void* self) noexcept;

        void __fastcall Detour_BuildMainResources(void* ecx, void* /*edx*/)
        {
            UiPerf::Heartbeat("BuildMainResources_Begin");
            const int before = ReadModableMode(ecx);
            {
                UiPerf::ScopedPhase phase("buildMainResources");
                auto* orig = reinterpret_cast<FnBuildFrontendResources>(g_BuildMainResourcesHook.trampoline);
                if (orig) orig(ecx);
            }
            ReportModableModeTransition("buildMainResources", 4, ecx, before);
            UiPerf::Heartbeat("BuildMainResources_End");
        }

        void __fastcall Detour_BuildMpResources(void* ecx, void* /*edx*/)
        {
            UiPerf::Heartbeat("BuildMpResources_Begin");
            const int before = ReadModableMode(ecx);
            {
                UiPerf::ScopedPhase phase("buildMPResources");
                auto* orig = reinterpret_cast<FnBuildFrontendResources>(g_BuildMpResourcesHook.trampoline);
                if (orig) orig(ecx);
            }
            ReportModableModeTransition("buildMPResources", 2, ecx, before);
            UiPerf::Heartbeat("BuildMpResources_End");
        }

        void* __fastcall Detour_MainScreenCtor(void* ecx, void* /*edx*/)
        {
            UiPerf::Heartbeat("MainScreenCtor_Begin");
            UiPerf::ScopedPhase phase("MainScreenCtor");
            auto* orig = reinterpret_cast<FnFrontendCtor>(g_MainScreenCtorHook.trampoline);
            void* result = orig ? orig(ecx) : nullptr;
            UiPerf::Heartbeat("MainScreenCtor_End");
            return result;
        }

        void* __fastcall Detour_MainScreenDtor(void* ecx, void* /*edx*/, unsigned int flags)
        {
            UiPerf::Heartbeat("MainScreenDtor_Begin");
            UiPerf::ScopedPhase phase("MainScreenDeletingDtor");
            auto* orig = reinterpret_cast<FnFrontendDeletingDtor>(g_MainScreenDtorHook.trampoline);
            void* result = orig ? orig(ecx, flags) : ecx;
            UiPerf::Heartbeat("MainScreenDtor_End");
            return result;
        }

        void* __fastcall Detour_MultiplayerLobbyCtor(void* ecx, void* /*edx*/)
        {
            UiPerf::Heartbeat("MultiplayerLobbyCtor_Begin");
            UiPerf::ScopedPhase phase("MultiplayerLobbyCtor");
            auto* orig = reinterpret_cast<FnFrontendCtor>(g_MultiplayerLobbyCtorHook.trampoline);
            void* result = orig ? orig(ecx) : nullptr;
            UiPerf::Heartbeat("MultiplayerLobbyCtor_End");
            return result;
        }

        void* __fastcall Detour_MultiplayerLobbyDtor(void* ecx, void* /*edx*/, unsigned int flags)
        {
            UiPerf::Heartbeat("MultiplayerLobbyDtor_Begin");
            UiPerf::ScopedPhase phase("MultiplayerLobbyDeletingDtor");
            auto* orig = reinterpret_cast<FnFrontendDeletingDtor>(g_MultiplayerLobbyDtorHook.trampoline);
            void* result = orig ? orig(ecx, flags) : ecx;
            UiPerf::Heartbeat("MultiplayerLobbyDtor_End");
            return result;
        }

        void __fastcall Detour_BuildIaResources(void* ecx, void* /*edx*/)
        {
            const uint64_t start = UiPerf::NowTicks();
            const int before = ReadModableMode(ecx);
            auto* orig = reinterpret_cast<FnBuildIaResources>(g_BuildIaResourcesHook.trampoline);
            if (orig) orig(ecx);
            LogShimA(LogLevel::Info, "uiperf-hooks",
                "[UIPERF][DRILL] buildIAResources %.2fms this=0x%p",
                UiPerf::TicksToMs(UiPerf::NowTicks() - start), ecx);
            ReportModableModeTransition("buildIAResources", 1, ecx, before);
        }

        void* __fastcall Detour_InstantActionCtor(void* ecx, void* /*edx*/)
        {
            const uint64_t start = UiPerf::NowTicks();
            auto* orig = reinterpret_cast<FnInstantActionCtor>(g_InstantActionCtorHook.trampoline);
            void* result = orig ? orig(ecx) : nullptr;
            LogShimA(LogLevel::Info, "uiperf-hooks",
                "[UIPERF][DRILL] InstantActionCtor %.2fms this=0x%p result=0x%p",
                UiPerf::TicksToMs(UiPerf::NowTicks() - start), ecx, result);
            return result;
        }

        void __fastcall Detour_ShellRequest(void* ecx, void* /*edx*/, int screenId)
        {
            if (UiPerf::IsEnabled())
            {
                if (!g_ShellManager) g_ShellManager = ecx; // capture valid dialog/manager
                g_PendingScreenId.store(screenId, std::memory_order_relaxed);
                g_ShellRequestStart.store(UiPerf::NowTicks(), std::memory_order_relaxed);
                UiFileScan::BeginTransition();
                UiPerf::NotifyShellRequest(screenId);
                LogShimA(LogLevel::Info, "uiperf-hooks",
                    "[UIPERF] ShellRequest screenId=0x%02X (%s) this=0x%p caller=0x%p",
                    screenId,
                    UiPerf::ShellScreenName(screenId)
                        ? UiPerf::ShellScreenName(screenId)
                        : "unknown",
                    ecx, _ReturnAddress());
            }
            auto* orig = reinterpret_cast<FnShellRequest>(g_ShellRequestHook.trampoline);
            if (orig) orig(ecx, screenId);
        }

        // Helper: log MainScreen buttons (POD, SEH-safe). Called only when pending==0x01.
        static void LogMainScreenButtons()
        {
            __try {
                void* ms = *(void**)0x0094551C;
                if (!ms || *(uintptr_t*)ms != 0x0089E178) return;
                void* ov = *(void**)((uint8_t*)ms + 0x158);
                if (!ov || *(uintptr_t*)ov != 0x008A0B94) return;
                void** beg = *(void***)((uint8_t*)ov + 0x12C);
                void** en = *(void***)((uint8_t*)ov + 0x130);
                if (!beg || !en || beg >= en || (en - beg) >= 64) return;
                for (void** it = beg; it != en; ++it)
                {
                    void* ch = *it;
                    if (!ch) continue;
                    const char* nm = (const char*)((uint8_t*)ch + 0x20);
                    if (!nm || !nm[0] || strlen(nm) > 64) continue;
                    uintptr_t vt = *(uintptr_t*)ch;
                    void* oc = (vt == 0x008A0470) ? *(void**)((uint8_t*)ch + 0x154) : nullptr;
                    LogShimA(LogLevel::Info, "uiperf-harness", "button name='%s' vt=0x%08X this=0x%p onClick=0x%p", nm, (unsigned)vt, ch, oc);
                }
            } __except (EXCEPTION_EXECUTE_HANDLER) {}
        }

        static void LogUiTree(void* node, int depth)
        {
            if (!node || depth > 5) return;
            __try
            {
                const char* name = reinterpret_cast<const char*>(
                    reinterpret_cast<uint8_t*>(node) + 0x20);
                const size_t nameLength = strnlen_s(name, 65);
                const uintptr_t vtable = *reinterpret_cast<uintptr_t*>(node);
                void* onClick = vtable == 0x008A0470
                    ? *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(node) + 0x154)
                    : nullptr;
                LogShimA(LogLevel::Info, "uiperf-harness",
                    "[UIPERF][HARNESS] ui depth=%d name=%s ptr=0x%p vt=0x%08X onclick=0x%p",
                    depth, (nameLength > 0 && nameLength <= 64) ? name : "<unnamed>",
                    node, static_cast<unsigned>(vtable), onClick);

                void** begin = *reinterpret_cast<void***>(
                    reinterpret_cast<uint8_t*>(node) + 0x12C);
                void** end = *reinterpret_cast<void***>(
                    reinterpret_cast<uint8_t*>(node) + 0x130);
                if (!begin || !end || begin >= end || (end - begin) > 256)
                    return;
                for (void** child = begin; child != end; ++child)
                    LogUiTree(*child, depth + 1);
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
        }

        static void* FindNamedButton(void* node, const char* wanted, int depth)
        {
            if (!node || !wanted || depth > 5) return nullptr;
            __try
            {
                const char* name = reinterpret_cast<const char*>(
                    reinterpret_cast<uint8_t*>(node) + 0x20);
                if (strnlen_s(name, 65) <= 64 && std::strcmp(name, wanted) == 0 &&
                    *reinterpret_cast<uintptr_t*>(node) == 0x008A0470)
                    return node;

                void** begin = *reinterpret_cast<void***>(
                    reinterpret_cast<uint8_t*>(node) + 0x12C);
                void** end = *reinterpret_cast<void***>(
                    reinterpret_cast<uint8_t*>(node) + 0x130);
                if (!begin || !end || begin >= end || (end - begin) > 256)
                    return nullptr;
                for (void** child = begin; child != end; ++child)
                    if (void* found = FindNamedButton(*child, wanted, depth + 1))
                        return found;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}
            return nullptr;
        }

        static void* GetActiveScreen() noexcept
        {
            __try
            {
                void* wrapper = *reinterpret_cast<void**>(0x00918320);
                return wrapper ? *reinterpret_cast<void**>(
                    reinterpret_cast<uint8_t*>(wrapper) + 0x14) : nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
        }

        void TryHandleTriggerFileOnMainThread()
        {
            BZROpenShim::UiFileScan::SetSuppress(true);
            __try {
            __try {
                char trigPath[MAX_PATH] = {};
                if (!BuildTriggerFilePath(trigPath)) return;
                DWORD attr = GetFileAttributesA(trigPath);
                if (attr == INVALID_FILE_ATTRIBUTES || (attr & FILE_ATTRIBUTE_DIRECTORY)) return;
                char want[128] = {};
                FILE* f = nullptr;
                if (fopen_s(&f, trigPath, "r") != 0 || !f) return;
                if (!fgets(want, sizeof(want), f)) { fclose(f); DeleteFileA(trigPath); return; }
                fclose(f);
                DeleteFileA(trigPath);
                // trim
                size_t n = strlen(want);
                while (n && (want[n-1]=='\r' || want[n-1]=='\n' || want[n-1]==' ' || want[n-1]=='\t')) want[--n]='\0';
                char* p = want;
                while (*p==' ' || *p=='\t') ++p;
                if (!*p) return;
                LogShimA(LogLevel::Info, "uiperf-harness",
                    "[UIPERF][HARNESS] trigger=%s detected", p);
                if (strcmp(p, "__BACK__") == 0)
                {
                    auto* backFn = reinterpret_cast<FnShellBack>(g_ShellBackHook.trampoline ? g_ShellBackHook.trampoline : reinterpret_cast<void*>(0x007C79A0));
                    void* wrapper = *reinterpret_cast<void**>(0x00918320);
                    if (backFn && wrapper)
                    {
                        LogShimA(LogLevel::Info, "uiperf-harness",
                            "[UIPERF][HARNESS] invoking ShellBack on main thread tid=%lu",
                            static_cast<unsigned long>(GetCurrentThreadId()));
                        __try { backFn(wrapper); } __except (EXCEPTION_EXECUTE_HANDLER) {
                            LogShimA(LogLevel::Warn, "uiperf-harness", "ShellBack threw");
                        }
                    }
                    return;
                }
                if (strcmp(p, "__ENUMERATE__") == 0)
                {
                    void* activeScreen = GetActiveScreen();
                    LogShimA(LogLevel::Info, "uiperf-harness",
                        "[UIPERF][HARNESS] enumerating active screen ptr=0x%p", activeScreen);
                    LogUiTree(activeScreen, 0);
                    return;
                }
                void* ms2 = *(void**)0x0094551C;
                if (!ms2 || *(uintptr_t*)ms2 != 0x0089E178)
                {
                    void* activeScreen = GetActiveScreen();
                    void* genericButton = FindNamedButton(activeScreen, p, 0);
                    if (!genericButton)
                    {
                        LogShimA(LogLevel::Warn, "uiperf-harness",
                            "[UIPERF][HARNESS] MainScreen not located and button=%s not found in active screen ptr=0x%p",
                            p, activeScreen);
                        return;
                    }
                    void* genericOnClick = *reinterpret_cast<void**>(
                        reinterpret_cast<uint8_t*>(genericButton) + 0x154);
                    LogShimA(LogLevel::Info, "uiperf-harness",
                        "[UIPERF][HARNESS] button=%s ptr=0x%p vt=0x%08X onclick=0x%p",
                        p, genericButton,
                        static_cast<unsigned>(*reinterpret_cast<uintptr_t*>(genericButton)),
                        genericOnClick);
                    LogShimA(LogLevel::Info, "uiperf-harness",
                        "[UIPERF][HARNESS] invoking OnClick on main thread tid=%lu",
                        static_cast<unsigned long>(GetCurrentThreadId()));
                    // Redux stores member thunks in the OnClick slot. Back
                    // callbacks read owner+0x138 to find the shell manager, so
                    // invoking without the live screen in ECX is not equivalent
                    // to the engine's normal UI dispatch.
                    reinterpret_cast<void(__thiscall*)(void*)>(genericOnClick)(activeScreen);
                    return;
                }
                LogShimA(LogLevel::Info, "uiperf-harness",
                    "[UIPERF][HARNESS] MainScreen ptr=0x%p vt=0x%08X",
                    ms2, static_cast<unsigned>(*(uintptr_t*)ms2));
                void* ov2 = *(void**)((uint8_t*)ms2 + 0x158);
                if (!ov2 || *(uintptr_t*)ov2 != 0x008A0B94)
                {
                    LogShimA(LogLevel::Warn, "uiperf-harness",
                        "[UIPERF][HARNESS] MainScreen_Overlay not located ptr=0x%p", ov2);
                    return;
                }
                LogShimA(LogLevel::Info, "uiperf-harness",
                    "[UIPERF][HARNESS] MainScreen_Overlay ptr=0x%p vt=0x%08X",
                    ov2, static_cast<unsigned>(*(uintptr_t*)ov2));
                void** b = *(void***)((uint8_t*)ov2 + 0x12C);
                void** e = *(void***)((uint8_t*)ov2 + 0x130);
                if (!b || !e || b >= e || (e - b) >= 64) return;
                bool found = false;
                for (void** it = b; it != e; ++it)
                {
                    void* ch2 = *it;
                    if (!ch2) continue;
                    const char* nm2 = (const char*)((uint8_t*)ch2 + 0x20);
                    if (!nm2 || strcmp(nm2, p) != 0) continue;
                    if (*(uintptr_t*)ch2 != 0x008A0470) return;
                    void* oc2 = *(void**)((uint8_t*)ch2 + 0x154);
                    if (!oc2) return;
                    found = true;
                    LogShimA(LogLevel::Info, "uiperf-harness",
                        "[UIPERF][HARNESS] button=%s ptr=0x%p vt=0x%08X onclick=0x%p",
                        p, ch2, static_cast<unsigned>(*(uintptr_t*)ch2), oc2);
                    LogShimA(LogLevel::Info, "uiperf-harness",
                        "[UIPERF][HARNESS] invoking OnClick on main thread tid=%lu",
                        static_cast<unsigned long>(GetCurrentThreadId()));
                    auto* fn = reinterpret_cast<void(__thiscall*)(void*)>(oc2);
                    __try { fn(ms2); } __except (EXCEPTION_EXECUTE_HANDLER) {
                        LogShimA(LogLevel::Warn, "uiperf-harness", "OnClick threw for '%s'", p);
                    }
                    break;
                }
                if (!found)
                {
                    LogShimA(LogLevel::Warn, "uiperf-harness",
                        "[UIPERF][HARNESS] button=%s not found", p);
                }
            } __except (EXCEPTION_EXECUTE_HANDLER) {}
            } __finally {
                BZROpenShim::UiFileScan::SetSuppress(false);
            }
        }

        int __cdecl Detour_ShellTransition(int* dialog, int mode)
        {
            const int pendingBefore = g_PendingScreenId.load(std::memory_order_relaxed);
            uint64_t callStart = 0;
            if (UiPerf::IsEnabled() && pendingBefore >= 0)
            {
                callStart = UiPerf::NowTicks();
                if (!g_ShellTransitionInFlight.exchange(true, std::memory_order_acq_rel))
                    UiPerf::Log("[UIPERF] BEGIN ShellTransition pending=0x%02X", pendingBefore);
            }
            auto* orig = reinterpret_cast<FnShellTransition>(g_ShellTransitionHook.trampoline);
            const int result = orig ? orig(dialog, mode) : 0;
            if (UiPerf::IsEnabled() && callStart)
            {
                const int pending = g_PendingScreenId.load(std::memory_order_relaxed);
                bool requestStillPending = true;
                void* activeScreen = nullptr;
                __try
                {
                    requestStillPending = !dialog ||
                        *(reinterpret_cast<uint8_t*>(dialog) + 0x27) != 0;
                    activeScreen = dialog ? reinterpret_cast<void*>(dialog[5]) : nullptr;
                }
                __except (EXCEPTION_EXECUTE_HANDLER) {}
                // Screen factories may reuse the allocation that held the
                // previous screen. Redux clears the request byte only after
                // destruction and destination construction complete, making
                // that byte the reliable completion signal.
                if (pending >= 0 && !requestStillPending && activeScreen)
                {
                    const double ms = UiPerf::TicksToMs(UiPerf::NowTicks() - callStart);
                    UiPerf::Log("[UIPERF] END ShellTransition final_call=%.2fms pending=0x%02X active=0x%p vt=0x%08X",
                        ms, pending, activeScreen,
                        static_cast<unsigned>(*reinterpret_cast<uintptr_t*>(activeScreen)));
                    // Emit filesystem diagnostics before closing the UiPerf
                    // transition so filesystem API self time participates in
                    // exclusive accounting without double-counting its
                    // inclusive enumeration lifetimes.
                    UiFileScan::EndTransition();
                    UiPerf::NotifyShellTransitionComplete();
                    UiPerf::Heartbeat("ShellTransitionEnd");
                    g_PendingScreenId.store(-1, std::memory_order_relaxed);
                    g_ShellTransitionInFlight.store(false, std::memory_order_release);
                    if (pending == 0x01)
                        LogMainScreenButtons();
                }
            }
            return result;
        }

        void __fastcall Detour_ShellBack(void* ecx, void* /*edx*/)
        {
            if (UiPerf::IsEnabled())
            {
                g_PendingScreenId.store(0x100, std::memory_order_relaxed);
                g_ShellRequestStart.store(UiPerf::NowTicks(), std::memory_order_relaxed);
                UiFileScan::BeginTransition();
                UiPerf::NotifyShellRequest(0x100);
                LogShimA(LogLevel::Info, "uiperf-hooks", "[UIPERF] ShellBack");
            }
            auto* orig = reinterpret_cast<FnShellBack>(g_ShellBackHook.trampoline);
            if (orig) orig(ecx);
        }

        bool InstallInlineHook(ShellHook& hook, uintptr_t target, void* detour, size_t minLen, const uint8_t* expectedPrefix)
        {
            if (!target || !detour || minLen < 5) return false;
            // Read original bytes.
            uint8_t orig[16] = {};
            SIZE_T r = 0;
            if (!ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(target), orig, minLen, &r) || r != minLen)
                return false;
            if (expectedPrefix)
            {
                for (size_t i = 0; i < minLen; ++i)
                    if (expectedPrefix[i] != 0xFF && orig[i] != expectedPrefix[i]) return false;
            }
            // Allocate trampoline: orig bytes + jmp back to target+minLen.
            void* tramp = VirtualAlloc(nullptr, 32, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
            if (!tramp) return false;
            memcpy(tramp, orig, minLen);
            // jmp back
            uint8_t* p = reinterpret_cast<uint8_t*>(tramp) + minLen;
            p[0] = 0xE9;
            const int32_t relBack = static_cast<int32_t>((target + minLen) - (reinterpret_cast<uintptr_t>(p) + 5));
            memcpy(p+1, &relBack, 4);
            FlushInstructionCache(GetCurrentProcess(), tramp, minLen+5);
            // Patch target to jmp detour.
            DWORD old = 0;
            if (!VirtualProtect(reinterpret_cast<void*>(target), minLen, PAGE_EXECUTE_READWRITE, &old))
            {
                VirtualFree(tramp, 0, MEM_RELEASE);
                return false;
            }
            uint8_t patch[16] = {};
            patch[0] = 0xE9;
            const int32_t relDetour = static_cast<int32_t>(reinterpret_cast<uintptr_t>(detour) - (target + 5));
            memcpy(patch+1, &relDetour, 4);
            for (size_t i = 5; i < minLen; ++i) patch[i] = 0x90; // nop pad
            memcpy(reinterpret_cast<void*>(target), patch, minLen);
            FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<void*>(target), minLen);
            DWORD ign = 0;
            VirtualProtect(reinterpret_cast<void*>(target), minLen, old, &ign);
            hook.trampoline = tramp;
            memcpy(hook.origBytes, orig, minLen);
            hook.origLen = minLen;
            hook.target = target;
            return true;
        }

        bool MemoryMatches(uintptr_t address, const uint8_t* expected, size_t length)
        {
            if (!address || !expected || !length)
                return false;
            uint8_t actual[16] = {};
            if (length > sizeof(actual))
                return false;
            SIZE_T read = 0;
            return ReadProcessMemory(GetCurrentProcess(),
                                     reinterpret_cast<const void*>(address),
                                     actual, length, &read) &&
                   read == length && std::memcmp(actual, expected, length) == 0;
        }

        bool IsLiveMainScreenReady()
        {
            __try
            {
                void* mainScreen = *reinterpret_cast<void**>(0x0094551C);
                return mainScreen &&
                       *reinterpret_cast<uintptr_t*>(mainScreen) == 0x0089E178;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool AreSteamShellFunctionsSettled()
        {
            // Validate bytes beyond each overwritten prologue. The 2026-08-28
            // full dumps showed SteamStub could expose a correct 7-byte entry
            // while the rest of ShellRequest was still ciphertext. Checking
            // only the trampoline prefix therefore cannot establish readiness.
            static constexpr uint8_t kRequestBody[] = {
                0x8D, 0x4D, 0x08, 0x51, 0x8B, 0x4D, 0xFC, 0x83, 0xC1, 0x2C, 0xE8
            };
            static constexpr uint8_t kRequestTail[] = {
                0x8B, 0xE5, 0x5D, 0xC2, 0x04, 0x00
            };
            static constexpr uint8_t kTransitionBody[] = {
                0x68, 0xE0, 0x20, 0x86, 0x00, 0x64, 0xA1, 0x00, 0x00, 0x00, 0x00
            };
            static constexpr uint8_t kBackBody[] = {
                0x8B, 0x4D, 0xFC, 0x83, 0xC1, 0x2C, 0xE8
            };
            return MemoryMatches(g_ShellRequestAddr + 0x0E,
                                 kRequestBody, sizeof(kRequestBody)) &&
                   MemoryMatches(g_ShellRequestAddr + 0x1D,
                                 kRequestTail, sizeof(kRequestTail)) &&
                   MemoryMatches(g_ShellTransitionAddr + 0x05,
                                 kTransitionBody, sizeof(kTransitionBody)) &&
                   MemoryMatches(g_ShellBackAddr + 0x07,
                                 kBackBody, sizeof(kBackBody));
        }

        bool AreFrontendDrilldownFunctionsSettled()
        {
            // These body sentinels are intentionally outside the overwritten
            // prologues. SteamStub previously exposed valid entry bytes while
            // the remainder of a function was still ciphertext, so a prologue
            // match alone is not sufficient authority to install a detour.
            static constexpr uint8_t kBuildMainBody[] = {
                0x68, 0x50, 0xD5, 0x85, 0x00, 0x64, 0xA1
            };
            static constexpr uint8_t kBuildMpBody[] = {
                0x68, 0xA0, 0xD5, 0x85, 0x00, 0x64, 0xA1
            };
            static constexpr uint8_t kMainCtorBody[] = {
                0x68, 0x54, 0xEC, 0x85, 0x00, 0x64, 0xA1
            };
            static constexpr uint8_t kMpCtorBody[] = {
                0x68, 0x50, 0xFF, 0x85, 0x00, 0x64, 0xA1
            };
            static constexpr uint8_t kMainDtorBody[] = {
                0x8B, 0x4D, 0xFC, 0xE8, 0xD1, 0x03, 0x00, 0x00
            };
            static constexpr uint8_t kMpDtorBody[] = {
                0x8B, 0x4D, 0xFC, 0xE8, 0x21, 0x00, 0x00, 0x00
            };
            return MemoryMatches(0x0076A030 + 5, kBuildMainBody, sizeof(kBuildMainBody)) &&
                   MemoryMatches(0x0076A240 + 5, kBuildMpBody, sizeof(kBuildMpBody)) &&
                   MemoryMatches(0x0078E670 + 5, kMainCtorBody, sizeof(kMainCtorBody)) &&
                   MemoryMatches(0x0079EA90 + 5, kMpCtorBody, sizeof(kMpCtorBody)) &&
                   MemoryMatches(0x0078E8C0 + 7, kMainDtorBody, sizeof(kMainDtorBody)) &&
                   MemoryMatches(0x007A0F80 + 7, kMpDtorBody, sizeof(kMpDtorBody));
        }

        void InstallFrontendDrilldownHooks()
        {
            if (!AreFrontendDrilldownFunctionsSettled())
            {
                LogShimA(LogLevel::Warn, "uiperf-hooks",
                    "Frontend drilldown hooks skipped because full-function sentinels are not settled");
                return;
            }

            static constexpr uint8_t kSehPrefix[] = {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF
            };
            static constexpr uint8_t kDeletingDtorPrefix[] = {
                0x55, 0x8B, 0xEC, 0x51, 0x89, 0x4D, 0xFC
            };
            int hooked = 0;
            hooked += InstallInlineHook(g_BuildMainResourcesHook, 0x0076A030,
                reinterpret_cast<void*>(&Detour_BuildMainResources), 5, kSehPrefix) ? 1 : 0;
            hooked += InstallInlineHook(g_BuildMpResourcesHook, 0x0076A240,
                reinterpret_cast<void*>(&Detour_BuildMpResources), 5, kSehPrefix) ? 1 : 0;
            hooked += InstallInlineHook(g_MainScreenCtorHook, 0x0078E670,
                reinterpret_cast<void*>(&Detour_MainScreenCtor), 5, kSehPrefix) ? 1 : 0;
            hooked += InstallInlineHook(g_MainScreenDtorHook, 0x0078E8C0,
                reinterpret_cast<void*>(&Detour_MainScreenDtor), 7, kDeletingDtorPrefix) ? 1 : 0;
            hooked += InstallInlineHook(g_MultiplayerLobbyCtorHook, 0x0079EA90,
                reinterpret_cast<void*>(&Detour_MultiplayerLobbyCtor), 5, kSehPrefix) ? 1 : 0;
            hooked += InstallInlineHook(g_MultiplayerLobbyDtorHook, 0x007A0F80,
                reinterpret_cast<void*>(&Detour_MultiplayerLobbyDtor), 7, kDeletingDtorPrefix) ? 1 : 0;
            LogShimA(hooked == 6 ? LogLevel::Info : LogLevel::Warn,
                "uiperf-hooks",
                "Frontend transition drilldown hooks installed=%d/6 (Main/Multiplayer build, ctor, dtor)",
                hooked);
        }

        // --- Ogre initialiseResourceGroup phase drilldown --------------------
        //
        // initialiseResourceGroup() is stock Ogre and splits into exactly two
        // phases: parseResourceGroupScripts(), which locates every script the
        // group's archives match and hands each one to a ScriptLoader, and
        // createDeclaredResources(). Both, plus the two script loaders Redux
        // actually uses, are exported by OgreMain.dll.
        //
        // The export address is an incremental-link thunk (`E9 rel32`), so the
        // thunk is followed to the real body before hooking: a relative jump
        // cannot be relocated into a trampoline. Every candidate is refused
        // unless its first five bytes are exactly the MSVC SEH prologue
        // `55 8B EC 6A FF`, which is also where the fifth byte lands on an
        // instruction boundary. A different OgreMain build therefore fails
        // closed instead of being patched mid-instruction.
        ShellHook g_OgreParseScriptsHook;
        ShellHook g_OgreCreateDeclaredHook;
        ShellHook g_OgreCompilerParseHook;
        ShellHook g_OgreMaterialParseHook;
        std::atomic<bool> g_OgrePhaseHooksInstalled{ false };

        // Only accumulated while inside parseResourceGroupScripts, so script
        // parsing driven by anything else is not folded into the phase report.
        std::atomic<int> g_OgreInParsePhase{ 0 };
        std::atomic<uint32_t> g_OgreCompilerParseCount{ 0 };
        std::atomic<uint32_t> g_OgreMaterialParseCount{ 0 };
        std::atomic<uint64_t> g_OgreScriptParseTicks{ 0 };
        std::atomic<uint64_t> g_OgreScriptParseMaxTicks{ 0 };

        // Ogre::DataStream keeps its name as the first member after the vptr,
        // and MSVC's std::string is {union{char buf[16]; char* ptr;}, size,
        // capacity}. Both are read-only probes and every field is validated,
        // so an OgreMain whose layout differs simply yields no name rather
        // than a bad pointer dereference.
        std::atomic<bool> g_OgreScriptNamesUsable{ true };

        // MSVC std::string is {union{char buf[16]; char* ptr;}, size, capacity}.
        // Every field is validated and the read is guarded, so a build with a
        // different layout yields no string rather than a bad dereference.
        bool TryReadStdString(const void* strObj, char* out, size_t outSize) noexcept
        {
            if (!strObj || !out || outSize < 2) return false;
            __try
            {
                auto* str = reinterpret_cast<const uint8_t*>(strObj);
                const uint32_t size = *reinterpret_cast<const uint32_t*>(str + 16);
                const uint32_t capacity = *reinterpret_cast<const uint32_t*>(str + 20);
                if (capacity < 15 || capacity > 65536 || size > capacity ||
                    size == 0 || size >= outSize)
                    return false;
                const char* data = (capacity >= 16)
                    ? *reinterpret_cast<char* const*>(str)
                    : reinterpret_cast<const char*>(str);
                if (!data) return false;
                for (uint32_t i = 0; i < size; ++i)
                {
                    const unsigned char c = static_cast<unsigned char>(data[i]);
                    if (c < 0x20 || c > 0x7E) return false;
                }
                memcpy(out, data, size);
                out[size] = '\0';
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        }

        // Ogre::DataStream keeps its name as the first member after the vptr.
        bool TryReadOgreDataStreamName(void* sharedPtr, char* out, size_t outSize) noexcept
        {
            if (!sharedPtr || !g_OgreScriptNamesUsable.load(std::memory_order_relaxed))
                return false;
            uint8_t* stream = nullptr;
            __try { stream = *reinterpret_cast<uint8_t**>(sharedPtr); }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_OgreScriptNamesUsable.store(false, std::memory_order_relaxed);
                return false;
            }
            if (!stream) return false;
            if (!TryReadStdString(stream + 4, out, outSize)) return false;
            return strchr(out, '.') != nullptr;
        }

        // Per-extension attribution for the parse phase.
        struct ScriptExtBucket { uint32_t count = 0; uint64_t ticks = 0; };
        std::mutex g_OgreScriptStatMutex;
        std::unordered_map<std::string, ScriptExtBucket> g_OgreScriptByExt;
        struct SlowScript { char name[128] = {}; uint64_t ticks = 0; };
        SlowScript g_OgreSlowScripts[3];

        void RecordScriptParseSample(const char* name, uint64_t ticks)
        {
            std::lock_guard<std::mutex> lock(g_OgreScriptStatMutex);
            const char* dot = name ? strrchr(name, '.') : nullptr;
            ScriptExtBucket& b = g_OgreScriptByExt[dot ? dot + 1 : "<unnamed>"];
            ++b.count;
            b.ticks += ticks;
            for (SlowScript& slot : g_OgreSlowScripts)
            {
                if (ticks > slot.ticks)
                {
                    for (size_t i = std::size(g_OgreSlowScripts) - 1; i > 0; --i)
                        g_OgreSlowScripts[i] = g_OgreSlowScripts[i - 1];
                    slot.ticks = ticks;
                    if (name)
                    {
                        strncpy_s(slot.name, name, _TRUNCATE);
                    }
                    else
                    {
                        slot.name[0] = '\0';
                    }
                    break;
                }
            }
        }

        void ResetScriptParseSamples()
        {
            std::lock_guard<std::mutex> lock(g_OgreScriptStatMutex);
            g_OgreScriptByExt.clear();
            for (SlowScript& slot : g_OgreSlowScripts) { slot.name[0] = '\0'; slot.ticks = 0; }
        }

        void LogScriptParseSamples()
        {
            std::lock_guard<std::mutex> lock(g_OgreScriptStatMutex);
            for (const auto& kv : g_OgreScriptByExt)
            {
                UiPerf::Log("[UIPERF][OGRE]     scriptParse ext=%s count=%u elapsed=%.2fms",
                            kv.first.c_str(), kv.second.count,
                            UiPerf::TicksToMs(kv.second.ticks));
            }
            for (const SlowScript& slot : g_OgreSlowScripts)
            {
                if (!slot.ticks) continue;
                UiPerf::Log("[UIPERF][OGRE]     scriptParse slowest=%s elapsed=%.2fms",
                            slot.name[0] ? slot.name : "<unnamed>",
                            UiPerf::TicksToMs(slot.ticks));
            }
        }

        using FnOgreGroupPhase = void(__fastcall*)(void*, void*, void*);
        using FnOgreParseScript = void(__fastcall*)(void*, void*, void*, void*);

        void AccumulateScriptParse(uint64_t ticks) noexcept
        {
            g_OgreScriptParseTicks.fetch_add(ticks, std::memory_order_relaxed);
            uint64_t prev = g_OgreScriptParseMaxTicks.load(std::memory_order_relaxed);
            while (ticks > prev &&
                   !g_OgreScriptParseMaxTicks.compare_exchange_weak(prev, ticks,
                       std::memory_order_relaxed, std::memory_order_relaxed))
            {
            }
        }

        void __fastcall Detour_OgreParseResourceGroupScripts(void* ecx, void* /*edx*/, void* grp)
        {
            auto* orig = reinterpret_cast<FnOgreGroupPhase>(g_OgreParseScriptsHook.trampoline);
            if (!orig) return;
            if (!UiPerf::IsEnabled())
            {
                orig(ecx, nullptr, grp);
                return;
            }
            g_OgreCompilerParseCount.store(0, std::memory_order_relaxed);
            g_OgreMaterialParseCount.store(0, std::memory_order_relaxed);
            g_OgreScriptParseTicks.store(0, std::memory_order_relaxed);
            g_OgreScriptParseMaxTicks.store(0, std::memory_order_relaxed);
            ResetScriptParseSamples();
            g_OgreInParsePhase.fetch_add(1, std::memory_order_acq_rel);
            const uint64_t start = UiPerf::NowTicks();
            orig(ecx, nullptr, grp);
            const double ms = UiPerf::TicksToMs(UiPerf::NowTicks() - start);
            g_OgreInParsePhase.fetch_sub(1, std::memory_order_acq_rel);

            const uint32_t compiled = g_OgreCompilerParseCount.load(std::memory_order_relaxed);
            const uint32_t materials = g_OgreMaterialParseCount.load(std::memory_order_relaxed);
            const double parseMs = UiPerf::TicksToMs(g_OgreScriptParseTicks.load(std::memory_order_relaxed));
            const double maxMs = UiPerf::TicksToMs(g_OgreScriptParseMaxTicks.load(std::memory_order_relaxed));
            // Residual is everything the phase did other than handing bytes to
            // a script loader: matching patterns against every archive,
            // building the file list, and opening each stream.
            UiPerf::Log("[UIPERF][OGRE]   parseResourceGroupScripts elapsed=%.2fms "
                        "scripts=%u materialSerializer=%u scriptParse=%.2fms "
                        "maxScript=%.2fms residual=%.2fms",
                        ms, compiled, materials, parseMs, maxMs, ms - parseMs);
            LogScriptParseSamples();
            UiPerf::RecordOgreScriptStats({ compiled, materials, 0, parseMs });
        }

        void __fastcall Detour_OgreCreateDeclaredResources(void* ecx, void* /*edx*/, void* grp)
        {
            auto* orig = reinterpret_cast<FnOgreGroupPhase>(g_OgreCreateDeclaredHook.trampoline);
            if (!orig) return;
            if (!UiPerf::IsEnabled())
            {
                orig(ecx, nullptr, grp);
                return;
            }
            const uint64_t start = UiPerf::NowTicks();
            orig(ecx, nullptr, grp);
            UiPerf::Log("[UIPERF][OGRE]   createDeclaredResources elapsed=%.2fms",
                        UiPerf::TicksToMs(UiPerf::NowTicks() - start));
        }

        void __fastcall Detour_OgreCompilerParseScript(void* ecx, void* /*edx*/,
                                                      void* stream, void* group)
        {
            auto* orig = reinterpret_cast<FnOgreParseScript>(g_OgreCompilerParseHook.trampoline);
            if (!orig) return;
            if (!UiPerf::IsEnabled() || g_OgreInParsePhase.load(std::memory_order_acquire) <= 0)
            {
                orig(ecx, nullptr, stream, group);
                return;
            }
            char name[128] = {};
            const bool haveName = TryReadOgreDataStreamName(stream, name, sizeof(name));
            const uint64_t start = UiPerf::NowTicks();
            orig(ecx, nullptr, stream, group);
            const uint64_t ticks = UiPerf::NowTicks() - start;
            AccumulateScriptParse(ticks);
            RecordScriptParseSample(haveName ? name : nullptr, ticks);
            g_OgreCompilerParseCount.fetch_add(1, std::memory_order_relaxed);
        }

        void __fastcall Detour_OgreMaterialParseScript(void* ecx, void* /*edx*/,
                                                      void* stream, void* group)
        {
            auto* orig = reinterpret_cast<FnOgreParseScript>(g_OgreMaterialParseHook.trampoline);
            if (!orig) return;
            if (!UiPerf::IsEnabled() || g_OgreInParsePhase.load(std::memory_order_acquire) <= 0)
            {
                orig(ecx, nullptr, stream, group);
                return;
            }
            char name[128] = {};
            const bool haveName = TryReadOgreDataStreamName(stream, name, sizeof(name));
            const uint64_t start = UiPerf::NowTicks();
            orig(ecx, nullptr, stream, group);
            const uint64_t ticks = UiPerf::NowTicks() - start;
            AccumulateScriptParse(ticks);
            RecordScriptParseSample(haveName ? name : nullptr, ticks);
            g_OgreMaterialParseCount.fetch_add(1, std::memory_order_relaxed);
        }

        // Exported name -> real body, following the incremental-link thunk.
        uintptr_t ResolveOgreExportBody(HMODULE ogre, const char* mangled)
        {
            auto* entry = reinterpret_cast<uint8_t*>(
                reinterpret_cast<void*>(GetProcAddress(ogre, mangled)));
            if (!entry) return 0;
            if (entry[0] == 0xE9)
            {
                int32_t rel = 0;
                memcpy(&rel, entry + 1, sizeof(rel));
                return reinterpret_cast<uintptr_t>(entry + 5 + rel);
            }
            return reinterpret_cast<uintptr_t>(entry);
        }

        void InstallOgrePhaseHooks()
        {
            if (!UiPerf::IsEnabled()) return;
            if (g_OgrePhaseHooksInstalled.exchange(true)) return;

            HMODULE ogre = GetModuleHandleA("OgreMain.dll");
            if (!ogre)
            {
                LogShimA(LogLevel::Info, "uiperf-hooks",
                    "Ogre phase drilldown skipped: OgreMain.dll not loaded");
                g_OgrePhaseHooksInstalled.store(false);
                return;
            }

            static constexpr uint8_t kOgreSehPrologue[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
            struct PhaseHook
            {
                const char* label;
                const char* mangled;
                ShellHook* hook;
                void* detour;
            };
            const PhaseHook hooks[] = {
                { "parseResourceGroupScripts",
                  "?parseResourceGroupScripts@ResourceGroupManager@Ogre@@IAEXPAUResourceGroup@12@@Z",
                  &g_OgreParseScriptsHook,
                  reinterpret_cast<void*>(&Detour_OgreParseResourceGroupScripts) },
                { "createDeclaredResources",
                  "?createDeclaredResources@ResourceGroupManager@Ogre@@IAEXPAUResourceGroup@12@@Z",
                  &g_OgreCreateDeclaredHook,
                  reinterpret_cast<void*>(&Detour_OgreCreateDeclaredResources) },
                { "ScriptCompilerManager::parseScript",
                  "?parseScript@ScriptCompilerManager@Ogre@@UAEXAAV?$SharedPtr@VDataStream@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
                  &g_OgreCompilerParseHook,
                  reinterpret_cast<void*>(&Detour_OgreCompilerParseScript) },
                { "MaterialSerializer::parseScript",
                  "?parseScript@MaterialSerializer@Ogre@@QAEXAAV?$SharedPtr@VDataStream@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
                  &g_OgreMaterialParseHook,
                  reinterpret_cast<void*>(&Detour_OgreMaterialParseScript) },
            };

            int installed = 0;
            for (const PhaseHook& h : hooks)
            {
                const uintptr_t body = ResolveOgreExportBody(ogre, h.mangled);
                if (!body)
                {
                    LogShimA(LogLevel::Warn, "uiperf-hooks",
                        "Ogre phase hook %s: export not found", h.label);
                    continue;
                }
                if (InstallInlineHook(*h.hook, body, h.detour, 5, kOgreSehPrologue))
                {
                    ++installed;
                    LogShimA(LogLevel::Info, "uiperf-hooks",
                        "Ogre phase hook %s installed at 0x%p tramp=0x%p",
                        h.label, reinterpret_cast<void*>(body), h.hook->trampoline);
                }
                else
                {
                    LogShimA(LogLevel::Warn, "uiperf-hooks",
                        "Ogre phase hook %s refused at 0x%p (prologue mismatch)",
                        h.label, reinterpret_cast<void*>(body));
                }
            }
            LogShimA(LogLevel::Info, "uiperf-hooks",
                "Ogre initialiseResourceGroup phase drilldown installed=%d/4", installed);
        }

        // --- Modable mount-mode instrumentation ------------------------------
        //
        // PROVEN STATIC (GOG battlezone98redux.exe, 2.2.301): the resource
        // manager object carries a mount-mode field at +0x8C, and five stock
        // setters drive it. Each one has the same shape:
        //
        //     if (g_ModableSubsystemEnabled == 0) return;   // 0x00915568
        //     if (this->mode == <target>) return;           // already there
        //     this->mode = <target>;
        //     ... mutate resource locations ...
        //     ResourceGroupManager::clearResourceGroup("Modable");
        //     ResourceGroupManager::initialiseResourceGroup("Modable");
        //
        // So a "desired state == active state" guard already exists in stock
        // code and demonstrably fires (Abort out of a stock mission returns
        // from buildMainResources in 0.09 ms). What is not guarded is the
        // alternation between two genuinely different mount sets, which is why
        // these hooks record the transitions themselves and the individual
        // resource locations each one mounts: that location list, not the
        // coarse mode, is the only candidate for an authoritative content
        // identity.
        struct ModableSetterSite
        {
            uintptr_t addr;
            int targetMode;
            const char* label;
            ShellHook hook;
        };

        // 0x0076A030 (mode 4), 0x0076A240 (mode 2) and 0x0076A430 (mode 1) are
        // the functions this file already hooks as buildMainResources,
        // buildMPResources and buildIAResources, so they are reported from
        // those detours instead of being hooked twice.
        ModableSetterSite g_ModableSetters[] = {
            { 0x0076A600, 0, "setModableNone", {} },
            { 0x0076AB20, 3, "setModableCustomCampaignList", {} },
            { 0x0076AE60, 0, "setModableCampaign", {} },
            { 0x0076B350, 0, "setModableContentB", {} },
        };

        ShellHook g_OgreAddLocationHook;
        ShellHook g_OgreRemoveLocationHook;
        std::atomic<bool> g_ModableHooksInstalled{ false };
        std::atomic<int> g_ModableSetterDepth{ 0 };
        std::atomic<uint32_t> g_ModableAdds{ 0 };
        std::atomic<uint32_t> g_ModableRemoves{ 0 };

        int ReadModableMode(void* self) noexcept
        {
            __try
            {
                if (!self) return -1;
                return *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(self) + 0x8C);
            }
            __except (EXCEPTION_EXECUTE_HANDLER) { return -1; }
        }

        // The manager's remembered content identity: a std::string at +0x90 that
        // setModableCampaign compares against the selected content object's own
        // string at +0x7C. Together with the mode at +0x8C this is the stock
        // "has the mounted content actually changed" test.
        void ReadModableIdentity(void* self, char* out, size_t outSize) noexcept
        {
            out[0] = '\0';
            if (!self) return;
            TryReadStdString(reinterpret_cast<uint8_t*>(self) + 0x90, out, outSize);
        }

        void ReportModableModeTransition(const char* label, int targetMode,
                                         void* self, int modeBefore)
        {
            if (!UiPerf::IsEnabled()) return;
            const int after = ReadModableMode(self);
            char identity[260] = {};
            ReadModableIdentity(self, identity, sizeof(identity));
            UiPerf::Log("[UIPERF][MODABLE] setter=%s target=%d this=0x%p modeBefore=%d "
                        "modeAfter=%d skipped=%d identity=%s",
                        label, targetMode, self, modeBefore, after,
                        (modeBefore == after && modeBefore == targetMode) ? 1 : 0,
                        identity[0] ? identity : "<none>");
        }

        // Argument counts are taken from each function's own epilogue: 0x0076AB20
        // ends in `ret`, the other three in `ret 4`. Getting this wrong
        // unbalances the stack, so the two shapes are kept strictly separate.
        struct ModableSetterCall
        {
            void* self;
            void* content;
            bool hasContent;
        };

        void RunModableSetterOriginal(ModableSetterSite& site, const ModableSetterCall& call)
        {
            if (call.hasContent)
            {
                auto* orig = reinterpret_cast<void(__fastcall*)(void*, void*, void*)>(site.hook.trampoline);
                orig(call.self, nullptr, call.content);
            }
            else
            {
                auto* orig = reinterpret_cast<void(__fastcall*)(void*, void*)>(site.hook.trampoline);
                orig(call.self, nullptr);
            }
        }

        void InvokeModableSetterImpl(size_t index, void* self, void* content, bool hasContent)
        {
            ModableSetterSite& site = g_ModableSetters[index];
            if (!site.hook.trampoline) return;
            const ModableSetterCall call{ self, content, hasContent };
            if (!UiPerf::IsEnabled())
            {
                RunModableSetterOriginal(site, call);
                return;
            }
            const int before = ReadModableMode(self);
            char identityBefore[260] = {};
            ReadModableIdentity(self, identityBefore, sizeof(identityBefore));
            char requested[260] = {};
            if (content)
                TryReadStdString(reinterpret_cast<uint8_t*>(content) + 0x7C, requested, sizeof(requested));
            g_ModableAdds.store(0, std::memory_order_relaxed);
            g_ModableRemoves.store(0, std::memory_order_relaxed);
            g_ModableSetterDepth.fetch_add(1, std::memory_order_acq_rel);
            const uint64_t start = UiPerf::NowTicks();
            RunModableSetterOriginal(site, call);
            const double ms = UiPerf::TicksToMs(UiPerf::NowTicks() - start);
            g_ModableSetterDepth.fetch_sub(1, std::memory_order_acq_rel);
            const int after = ReadModableMode(self);
            char identityAfter[260] = {};
            ReadModableIdentity(self, identityAfter, sizeof(identityAfter));
            UiPerf::Log("[UIPERF][MODABLE] setter=%s target=%d this=0x%p modeBefore=%d "
                        "modeAfter=%d requested=%s identityBefore=%s identityAfter=%s "
                        "added=%u removed=%u elapsed=%.2fms",
                        site.label, site.targetMode, self, before, after,
                        requested[0] ? requested : "<none>",
                        identityBefore[0] ? identityBefore : "<none>",
                        identityAfter[0] ? identityAfter : "<none>",
                        g_ModableAdds.load(std::memory_order_relaxed),
                        g_ModableRemoves.load(std::memory_order_relaxed), ms);
        }

        // 0x0076AB20 takes no argument; the other three take the selected
        // content object, whose identity string lives at +0x7C and which the
        // manager remembers at +0x90.
        void __fastcall Detour_ModableSetter0(void* ecx, void*, void* content) { InvokeModableSetterImpl(0, ecx, content, true); }
        void __fastcall Detour_ModableSetter1(void* ecx, void*) { InvokeModableSetterImpl(1, ecx, nullptr, false); }
        void __fastcall Detour_ModableSetter2(void* ecx, void*, void* content) { InvokeModableSetterImpl(2, ecx, content, true); }
        void __fastcall Detour_ModableSetter3(void* ecx, void*, void* content) { InvokeModableSetterImpl(3, ecx, content, true); }

        using FnAddResourceLocation =
            void(__fastcall*)(void*, void*, void*, void*, void*, bool, bool);
        using FnRemoveResourceLocation = void(__fastcall*)(void*, void*, void*, void*);

        void __fastcall Detour_OgreAddResourceLocation(void* ecx, void* /*edx*/,
                                                      void* name, void* locType,
                                                      void* group, bool recursive,
                                                      bool readOnly)
        {
            auto* orig = reinterpret_cast<FnAddResourceLocation>(g_OgreAddLocationHook.trampoline);
            if (!orig) return;
            if (UiPerf::IsEnabled())
            {
                char n[260] = {}, t[64] = {}, g[64] = {};
                const bool haveName = TryReadStdString(name, n, sizeof(n));
                TryReadStdString(locType, t, sizeof(t));
                TryReadStdString(group, g, sizeof(g));
                g_ModableAdds.fetch_add(1, std::memory_order_relaxed);
                UiPerf::Log("[UIPERF][MODABLE]   +location group=%s type=%s recursive=%d name=%s",
                            g[0] ? g : "?", t[0] ? t : "?", recursive ? 1 : 0,
                            haveName ? n : "?");
            }
            orig(ecx, nullptr, name, locType, group, recursive, readOnly);
        }

        void __fastcall Detour_OgreRemoveResourceLocation(void* ecx, void* /*edx*/,
                                                         void* name, void* group)
        {
            auto* orig = reinterpret_cast<FnRemoveResourceLocation>(g_OgreRemoveLocationHook.trampoline);
            if (!orig) return;
            if (UiPerf::IsEnabled())
            {
                char n[260] = {}, g[64] = {};
                const bool haveName = TryReadStdString(name, n, sizeof(n));
                TryReadStdString(group, g, sizeof(g));
                g_ModableRemoves.fetch_add(1, std::memory_order_relaxed);
                UiPerf::Log("[UIPERF][MODABLE]   -location group=%s name=%s",
                            g[0] ? g : "?", haveName ? n : "?");
            }
            orig(ecx, nullptr, name, group);
        }

        void InstallModableModeHooks()
        {
            if (!UiPerf::IsEnabled()) return;
            if (g_ModableHooksInstalled.exchange(true)) return;

            // Every one of these bodies begins with the same MSVC SEH prologue,
            // whose fifth byte is an instruction boundary. A build whose bytes
            // differ - or a Steam image that has not settled - fails the prefix
            // check and is left alone.
            static constexpr uint8_t kSehPrologue[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
            void* detours[] = {
                reinterpret_cast<void*>(&Detour_ModableSetter0),
                reinterpret_cast<void*>(&Detour_ModableSetter1),
                reinterpret_cast<void*>(&Detour_ModableSetter2),
                reinterpret_cast<void*>(&Detour_ModableSetter3),
            };
            int installed = 0;
            for (size_t i = 0; i < std::size(g_ModableSetters); ++i)
            {
                ModableSetterSite& site = g_ModableSetters[i];
                if (InstallInlineHook(site.hook, site.addr, detours[i], 5, kSehPrologue))
                {
                    ++installed;
                    LogShimA(LogLevel::Info, "uiperf-hooks",
                        "Modable setter hook %s installed at 0x%08X tramp=0x%p",
                        site.label, static_cast<unsigned>(site.addr), site.hook.trampoline);
                }
                else
                {
                    LogShimA(LogLevel::Warn, "uiperf-hooks",
                        "Modable setter hook %s refused at 0x%08X (prologue mismatch)",
                        site.label, static_cast<unsigned>(site.addr));
                }
            }

            HMODULE ogre = GetModuleHandleA("OgreMain.dll");
            if (ogre)
            {
                const uintptr_t addAddr = ResolveOgreExportBody(ogre,
                    "?addResourceLocation@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00_N1@Z");
                const uintptr_t removeAddr = ResolveOgreExportBody(ogre,
                    "?removeResourceLocation@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
                if (addAddr && InstallInlineHook(g_OgreAddLocationHook, addAddr,
                        reinterpret_cast<void*>(&Detour_OgreAddResourceLocation), 5, kSehPrologue))
                    ++installed;
                if (removeAddr && InstallInlineHook(g_OgreRemoveLocationHook, removeAddr,
                        reinterpret_cast<void*>(&Detour_OgreRemoveResourceLocation), 5, kSehPrologue))
                    ++installed;
            }
            LogShimA(LogLevel::Info, "uiperf-hooks",
                "Modable mount instrumentation installed=%d/6", installed);
        }

        void InstallResolvedShellHooks(bool installGogDrilldown)
        {
            int expectedState = 0;
            if (!g_ShellHookInstallState.compare_exchange_strong(
                    expectedState, 1, std::memory_order_acq_rel))
                return;

            static constexpr uint8_t kThiscallPrefix[] = {
                0x55, 0x8B, 0xEC, 0x51, 0x89, 0x4D, 0xFC
            };
            static constexpr uint8_t kTransitionPrefix[] = {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF
            };
            int hooked = 0;
            if (InstallInlineHook(g_ShellRequestHook, g_ShellRequestAddr,
                                  reinterpret_cast<void*>(&Detour_ShellRequest),
                                  7, kThiscallPrefix))
            {
                ++hooked;
                LogShimA(LogLevel::Info, "uiperf-hooks",
                    "ShellRequest hook installed at 0x%08X len=7 tramp=0x%p",
                    g_ShellRequestAddr, g_ShellRequestHook.trampoline);
            }
            if (InstallInlineHook(g_ShellTransitionHook, g_ShellTransitionAddr,
                                  reinterpret_cast<void*>(&Detour_ShellTransition),
                                  5, kTransitionPrefix))
            {
                ++hooked;
                LogShimA(LogLevel::Info, "uiperf-hooks",
                    "ShellTransition hook installed at 0x%08X len=5 tramp=0x%p",
                    g_ShellTransitionAddr, g_ShellTransitionHook.trampoline);
            }
            if (InstallInlineHook(g_ShellBackHook, g_ShellBackAddr,
                                  reinterpret_cast<void*>(&Detour_ShellBack),
                                  7, kThiscallPrefix))
            {
                ++hooked;
                LogShimA(LogLevel::Info, "uiperf-hooks",
                    "ShellBack hook installed at 0x%08X len=7 tramp=0x%p",
                    g_ShellBackAddr, g_ShellBackHook.trampoline);
            }

            // These addresses and prologues are GOG-only drilldown evidence;
            // they must not be written into SteamStub-managed code pages.
            if (installGogDrilldown)
            {
                if (InstallInlineHook(g_BuildIaResourcesHook, 0x0076A430,
                                      reinterpret_cast<void*>(&Detour_BuildIaResources),
                                      5, kTransitionPrefix))
                    LogShimA(LogLevel::Info, "uiperf-hooks", "buildIAResources drilldown installed");
                if (InstallInlineHook(g_InstantActionCtorHook, 0x00789C20,
                                      reinterpret_cast<void*>(&Detour_InstantActionCtor),
                                      5, kTransitionPrefix))
                    LogShimA(LogLevel::Info, "uiperf-hooks", "InstantActionCtor drilldown installed");
            }

            // These markers identify the native call chain around the two
            // transitions users report as laggiest. They only measure and are
            // installed after full-function body validation; they do not alter
            // resource or menu behavior.
            InstallFrontendDrilldownHooks();

            // Mount-mode instrumentation shares the same settle gate: on Steam
            // these bodies are only trustworthy once the image has settled.
            InstallModableModeHooks();

            g_ShellHookInstallState.store(2, std::memory_order_release);
            LogShimA(hooked == 3 ? LogLevel::Info : LogLevel::Warn,
                "uiperf-hooks",
                "UiPerf shell hooks finished: request=0x%08X transition=0x%08X back=0x%08X hooked=%d",
                g_ShellRequestAddr, g_ShellTransitionAddr, g_ShellBackAddr, hooked);
        }

        void TryInstallDeferredSteamShellHooksOnMainThread()
        {
            if (GetBzrDistribution() != BzrDistribution::Steam ||
                g_ShellHookInstallState.load(std::memory_order_acquire) != 0 ||
                !IsLiveMainScreenReady() || !AreSteamShellFunctionsSettled())
                return;

            LogShimA(LogLevel::Info, "uiperf-hooks",
                "Steam shell code settled at live MainScreen; installing profiler detours on UI thread");
            InstallResolvedShellHooks(false);
        }

        // Auto-matrix driver thread.
        unsigned __stdcall AutoMatrixThread(void*)
        {
            // Wait for UiPerf enabled and for shell manager to be captured.
            for (int i = 0; i < 600 && !g_ShellManager; ++i)
            {
                if (!UiPerf::IsEnabled() || !g_AutoMatrixEnabled.load()) return 0;
                Sleep(500);
            }
            if (!g_ShellManager) return 0;
            // Give main menu time to stabilize after boot.
            Sleep(3000);
            struct Step { int id; const char* name; };
            const Step firstPass[] = {
                { 0x0E, "Main->MP" },
                { 0x01, "MP->Main" },
                { 0x1B, "Main->IA" },
                { 0x01, "IA->Main" },
                { 0x20, "Main->Campaign" },
                { 0x01, "Campaign->Main" },
            };
            auto runPass = [&](int pass) -> bool {
                for (size_t s = 0; s < _countof(firstPass); ++s)
                {
                    if (!g_AutoMatrixEnabled.load()) return false;
                    const Step& step = firstPass[s];
                    // Skip if we're already on that screen? Just request anyway.
                    LogShimA(LogLevel::Info, "uiperf-automatrix",
                        "[UIPERF][AUTOMATRIX] pass=%d step=%zu %s request=0x%02X",
                        pass, s, step.name, step.id);
                    // Call ShellRequest on manager thread? We are on worker thread,
                    // but shell manager is single-threaded; we must marshal to main
                    // thread via APC or simply call directly if the function is
                    // thread-safe for queuing (it marks pending and history).
                    // The original request is always from main thread; calling
                    // from worker may race. So we use a suspended main-thread
                    // call via QueueUserAPC? Simpler: we patch the request to be
                    // callable from any thread as it just sets pending flag.
                    // For safety, we call via the trampoline which will run on
                    // this thread but touches manager memory; manager's pending
                    // flag is not thread-safe but the game will poll it on its
                    // own update loop, so cross-thread write is racy but likely
                    // okay for profiling (worst case missed request). We add a
                    // Sleep to let update loop pick it up.
                    auto* fn = reinterpret_cast<FnShellRequest>(g_ShellRequestHook.trampoline ? g_ShellRequestHook.trampoline : reinterpret_cast<void*>(0x007C7930));
                    if (fn && g_ShellManager)
                    {
                        __try { fn(g_ShellManager, step.id); } __except (EXCEPTION_EXECUTE_HANDLER) {
                            LogShimA(LogLevel::Warn, "uiperf-automatrix", "exception in synthetic request 0x%02X", step.id);
                        }
                    }
                    else if (!g_ShellManager)
                    {
                        LogShimA(LogLevel::Warn, "uiperf-automatrix", "no manager for request 0x%02X", step.id);
                    }
                    // Wait for transition to complete: poll for 10s max, checking
                    // that ShellTransition has fired (PendingScreenId cleared).
                    for (int w = 0; w < 100; ++w)
                    {
                        Sleep(100);
                        if (g_PendingScreenId.load() == -1) break;
                    }
                    // Extra settle for menu to become input-ready (resource
                    // loading and first viewport). 2s is enough for the
                    // 5-10s stalls to be captured as part of the transition;
                    // the settle is after END.
                    Sleep(2000);
                }
                return true;
            };
            LogShimA(LogLevel::Info, "uiperf-automatrix", "[UIPERF][AUTOMATRIX] starting pass 1 (first)");
            runPass(1);
            LogShimA(LogLevel::Info, "uiperf-automatrix", "[UIPERF][AUTOMATRIX] starting pass 2 (repeat, no content change)");
            Sleep(1000);
            runPass(2);
            LogShimA(LogLevel::Info, "uiperf-automatrix", "[UIPERF][AUTOMATRIX] matrix complete");
            return 0;
        }

    } // namespace

    void Install()
    {
        if (g_Installed.exchange(true))
            return;

        UiPerf::Initialize();

        // Check for auto-matrix opt-in (ini or env).  This is a separate
        // instrumentation aid, not an optimization, and is OFF by default.
        {
            char buf[16] = {};
            bool autoMat = false;
            // Try ini first.
            char gameDir[MAX_PATH] = {};
            if (GetModuleFileNameA(nullptr, gameDir, MAX_PATH))
            {
                char* slash = strrchr(gameDir, '\\');
                if (slash) { *(slash+1) = '\0'; std::string ini = std::string(gameDir) + "openshim.ini"; char val[16] = {}; GetPrivateProfileStringA("Diagnostics", "UiPerformanceAutoMatrix", "__unset__", val, sizeof(val), ini.c_str());
                    if (strcmp(val, "__unset__") != 0) {
                        std::string v(val); for(char&c:v) c=tolower((unsigned char)c);
                        autoMat = (v=="1"||v=="true"||v=="on"||v=="yes"||v=="enabled");
                    }
                }
            }
            if (!autoMat)
            {
                DWORD len = GetEnvironmentVariableA("OPENSHIM_UI_PERFORMANCE_AUTOMATRIX", buf, sizeof(buf));
                if (len>0 && len < sizeof(buf)) { std::string v(buf,len); for(char&c:v) c=tolower((unsigned char)c); autoMat = (v=="1"||v=="true"||v=="on"||v=="yes"); }
            }
            g_AutoMatrixEnabled.store(autoMat, std::memory_order_relaxed);
            if (autoMat) LogShimA(LogLevel::Info, "uiperf-hooks", "UiPerf auto-matrix enabled");
        }

        // Even when disabled we resolve addresses so a later enable doesn't need
        // a restart; but we only patch when enabled to keep the OFF path truly
        // zero-overhead (no detour indirection).
        if (!UiPerf::IsEnabled())
        {
            LogShimA(LogLevel::Info, "uiperf-hooks", "UiPerf disabled; hooks not installed (enable via [Diagnostics] UiPerformanceLogging=true)");
            return;
        }

        uint32_t reqAddr = HookEngine::ResolveNamedAddress("ShellRequest");
        if (!reqAddr) reqAddr = 0x007C7930;
        uint32_t transAddr = HookEngine::ResolveNamedAddress("ShellTransition");
        if (!transAddr) transAddr = 0x007C7070;
        uint32_t backAddr = HookEngine::ResolveNamedAddress("ShellBack");
        if (!backAddr) backAddr = 0x007C79A0;

        g_ShellRequestAddr = reqAddr;
        g_ShellTransitionAddr = transAddr;
        g_ShellBackAddr = backAddr;

        const BzrDistribution distribution = GetBzrDistribution();
        if (distribution == BzrDistribution::Steam)
        {
            LogShimA(LogLevel::Info, "uiperf-hooks",
                "Steam shell hooks deferred until settled live MainScreen; request=0x%08X transition=0x%08X back=0x%08X",
                reqAddr, transAddr, backAddr);
        }
        else if (distribution == BzrDistribution::GOG)
        {
            InstallResolvedShellHooks(true);
        }
        else
        {
            LogShimA(LogLevel::Warn, "uiperf-hooks",
                "Shell hooks not installed because Redux distribution is unknown");
        }

        // Hooked PeekMessageA installs the window subclass from Redux's owning
        // UI thread. The worker started here never dereferences Battlezone UI
        // objects: cross-thread UI traversal is forbidden because menu objects
        // are rebuilt during shell transitions and are not thread-safe. It only
        // tests trigger-file presence and posts WM_UI_TRIGGER; the subclass
        // performs all file consumption, overlay traversal, and OnClick work.
        StartTriggerDelivery();

        const bool clearHooked = PatchImportIAT(
            GetModuleHandleW(nullptr),
            "?clearResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
            reinterpret_cast<void*>(&Hooked_OgreClear),
            reinterpret_cast<void**>(&g_RealOgreClear), &g_OgreClearIat);
        const bool initialiseHooked = PatchImportIAT(
            GetModuleHandleW(nullptr),
            "?initialiseResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
            reinterpret_cast<void*>(&Hooked_OgreInitialise),
            reinterpret_cast<void**>(&g_RealOgreInitialise), &g_OgreInitialiseIat);
        LogShimA(LogLevel::Info, "uiperf-hooks",
            "Ogre ResourceGroup IAT timing clear=%s initialise=%s",
            clearHooked ? "active" : "missing",
            initialiseHooked ? "active" : "missing");

        InstallOgrePhaseHooks();

        if (g_AutoMatrixEnabled.load() && !g_AutoMatrixRunning.exchange(true))
        {
            uintptr_t th = _beginthreadex(nullptr, 0, &AutoMatrixThread, nullptr, 0, nullptr);
            if (th) CloseHandle(reinterpret_cast<HANDLE>(th));
        }

        // Ogre ResourceGroupManager exports - validate presence.
        HMODULE ogre = GetModuleHandleA("OgreMain.dll");
        if (ogre)
        {
            auto has = [&](const char* name)->bool { return GetProcAddress(ogre, name) != nullptr; };
            const bool haveRG = has("?getSingletonPtr@ResourceGroupManager@Ogre@@SAPAV12@XZ")
                && has("?initialiseResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z")
                && has("?initialiseAllResourceGroups@ResourceGroupManager@Ogre@@QAEXXZ")
                && has("?clearResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z")
                && has("?destroyResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z")
                && has("?loadResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N1@Z")
                && has("?unloadResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
            LogShimA(LogLevel::Info, "uiperf-hooks",
                "OgreMain.dll %s (ResourceGroupManager exports %s)",
                ogre ? "loaded" : "not loaded",
                haveRG ? "present" : "missing");
        }
        else
        {
            LogShimA(LogLevel::Info, "uiperf-hooks", "OgreMain.dll not yet loaded; Ogre timing will attach on first initialiseResourceGroup");
        }
    }

    void Shutdown() noexcept
    {
        StopTriggerDelivery();
        RestoreImportSlot(g_OgreClearIat, reinterpret_cast<void*>(&Hooked_OgreClear),
                          reinterpret_cast<void*>(g_RealOgreClear));
        RestoreImportSlot(g_OgreInitialiseIat,
                          reinterpret_cast<void*>(&Hooked_OgreInitialise),
                          reinterpret_cast<void*>(g_RealOgreInitialise));
        g_OgreClearIat = nullptr;
        g_OgreInitialiseIat = nullptr;
        g_RealOgreClear = nullptr;
        g_RealOgreInitialise = nullptr;
    }

} // namespace BZROpenShim::UiPerfHooks
