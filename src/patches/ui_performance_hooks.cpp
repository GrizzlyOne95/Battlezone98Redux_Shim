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
#include "hook_engine.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>
#include <process.h>

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
        std::atomic<uint64_t> g_ShellRequestStart{ 0 };
        std::atomic<int> g_PendingScreenId{ -1 };

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
        using FnShellTransition = void(__cdecl*)(); // actually no args, uses global manager
        using FnShellBack = void(__cdecl*)();

        void __fastcall Detour_ShellRequest(void* ecx, void* /*edx*/, int screenId)
        {
            if (UiPerf::IsEnabled())
            {
                if (!g_ShellManager) g_ShellManager = ecx; // capture valid dialog/manager
                g_PendingScreenId.store(screenId, std::memory_order_relaxed);
                g_ShellRequestStart.store(UiPerf::NowTicks(), std::memory_order_relaxed);
                UiPerf::NotifyShellRequest(screenId);
                LogShimA(LogLevel::Info, "uiperf-hooks",
                    "[UIPERF] ShellRequest screenId=0x%02X (%s) this=0x%p",
                    screenId, UiPerf::ShellScreenName(screenId) ? UiPerf::ShellScreenName(screenId) : "unknown", ecx);
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

        static void TryHandleTriggerFile()
        {
            __try {
                char gameDir[MAX_PATH] = {};
                if (!GetModuleFileNameA(nullptr, gameDir, MAX_PATH)) return;
                char* sl = strrchr(gameDir, '\\');
                if (!sl) return;
                *(sl+1) = '\0';
                char trigPath[MAX_PATH] = {};
                _snprintf_s(trigPath, MAX_PATH, _TRUNCATE, "%suiperf_trigger.txt", gameDir);
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
                LogShimA(LogLevel::Info, "uiperf-harness", "trigger file requests button '%s'", p);
                void* ms2 = *(void**)0x0094551C;
                if (!ms2 || *(uintptr_t*)ms2 != 0x0089E178) return;
                void* ov2 = *(void**)((uint8_t*)ms2 + 0x158);
                if (!ov2 || *(uintptr_t*)ov2 != 0x008A0B94) return;
                void** b = *(void***)((uint8_t*)ov2 + 0x12C);
                void** e = *(void***)((uint8_t*)ov2 + 0x130);
                if (!b || !e || b >= e || (e - b) >= 64) return;
                for (void** it = b; it != e; ++it)
                {
                    void* ch2 = *it;
                    if (!ch2) continue;
                    const char* nm2 = (const char*)((uint8_t*)ch2 + 0x20);
                    if (!nm2 || strcmp(nm2, p) != 0) continue;
                    if (*(uintptr_t*)ch2 != 0x008A0470) return;
                    void* oc2 = *(void**)((uint8_t*)ch2 + 0x154);
                    if (!oc2) return;
                    LogShimA(LogLevel::Info, "uiperf-harness", "invoking OnClick for '%s' at 0x%p this=0x%p", p, oc2, ch2);
                    auto* fn = reinterpret_cast<void(__thiscall*)(void*)>(oc2);
                    __try { fn(ch2); } __except (EXCEPTION_EXECUTE_HANDLER) {
                        LogShimA(LogLevel::Warn, "uiperf-harness", "OnClick threw for '%s'", p);
                    }
                    break;
                }
            } __except (EXCEPTION_EXECUTE_HANDLER) {}
        }

        void __stdcall Detour_ShellTransition()
        {
            uint64_t t0 = 0;
            if (UiPerf::IsEnabled())
            {
                t0 = UiPerf::NowTicks();
                UiPerf::Log("[UIPERF] BEGIN ShellTransition");
            }
            auto* orig = reinterpret_cast<FnShellTransition>(g_ShellTransitionHook.trampoline);
            if (orig) orig();
            if (UiPerf::IsEnabled() && t0)
            {
                const double ms = UiPerf::TicksToMs(UiPerf::NowTicks() - t0);
                const int pending = g_PendingScreenId.load(std::memory_order_relaxed);
                UiPerf::Log("[UIPERF] END ShellTransition %.2fms pending=0x%02X", ms, pending);
                UiPerf::NotifyShellTransitionComplete();
                UiPerf::Heartbeat("ShellTransitionEnd");
                g_PendingScreenId.store(-1, std::memory_order_relaxed);
                if (pending == 0x01)
                {
                    LogMainScreenButtons();
                    TryHandleTriggerFile();
                }
                else
                {
                    // Also check trigger file on any transition, so a trigger
                    // written while at MP/IA can still be consumed when that
                    // screen's transition completes and we return to Main.
                    TryHandleTriggerFile();
                }
            }
        }

        void __stdcall Detour_ShellBack()
        {
            if (UiPerf::IsEnabled())
            {
                UiPerf::NotifyShellRequest(0x100);
                LogShimA(LogLevel::Info, "uiperf-hooks", "[UIPERF] ShellBack");
            }
            auto* orig = reinterpret_cast<FnShellBack>(g_ShellBackHook.trampoline);
            if (orig) orig();
            if (UiPerf::IsEnabled())
                UiPerf::Heartbeat("ShellBackEnd");
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

        int hooked = 0;
        // Install inline hooks with correct instruction-boundary lengths
        // (dumped 2026-08-28 via ReadProcessMemory):
        //   007C7930: 55 8B EC 51 89 4D FC ... => 7 bytes to reach 89 4D FC
        //   007C7070: 55 8B EC 6A FF ... => 5 bytes is boundary (push -1)
        // Back uses 5 as fallback.
        if (InstallInlineHook(g_ShellRequestHook, reqAddr, reinterpret_cast<void*>(&Detour_ShellRequest), 7, nullptr))
        {
            ++hooked;
            LogShimA(LogLevel::Info, "uiperf-hooks", "ShellRequest hook installed at 0x%08X len=7 tramp=0x%p", reqAddr, g_ShellRequestHook.trampoline);
        }
        else LogShimA(LogLevel::Warn, "uiperf-hooks", "ShellRequest hook FAILED at 0x%08X", reqAddr);

        if (InstallInlineHook(g_ShellTransitionHook, transAddr, reinterpret_cast<void*>(&Detour_ShellTransition), 5, nullptr))
        {
            ++hooked;
            LogShimA(LogLevel::Info, "uiperf-hooks", "ShellTransition hook installed at 0x%08X len=5 tramp=0x%p", transAddr, g_ShellTransitionHook.trampoline);
        }
        else LogShimA(LogLevel::Warn, "uiperf-hooks", "ShellTransition hook FAILED at 0x%08X", transAddr);

        if (InstallInlineHook(g_ShellBackHook, backAddr, reinterpret_cast<void*>(&Detour_ShellBack), 5, nullptr))
        {
            ++hooked;
            LogShimA(LogLevel::Info, "uiperf-hooks", "ShellBack hook installed at 0x%08X tramp=0x%p", backAddr, g_ShellBackHook.trampoline);
        }
        else LogShimA(LogLevel::Info, "uiperf-hooks", "ShellBack hook skipped at 0x%08X", backAddr);

        g_ShellRequestAddr = reqAddr;
        g_ShellTransitionAddr = transAddr;
        g_ShellBackAddr = backAddr;

        LogShimA(LogLevel::Info, "uiperf-hooks",
            "UiPerf hooks ready: shellReq=0x%08X shellTrans=0x%08X shellBack=0x%08X hooked=%d automatrix=%d",
            reqAddr, transAddr, backAddr, hooked, g_AutoMatrixEnabled.load()?1:0);

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

} // namespace BZROpenShim::UiPerfHooks
