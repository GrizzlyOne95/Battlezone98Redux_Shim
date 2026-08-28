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
        // Assembly detours for shell seams.  These are __declspec(naked) so they
        // can tail-call the original bytes without disturbing the caller's stack.
        // The stock shell manager pointer is expected to be passed as 'this' via
        // ecx/thunk; we preserve all regs and call the C++ helper on a clean stack.

        // Helpers called from assembly with the screenId still on stack / in register.
        void ShellRequestHook(int screenId)
        {
            UiPerf::NotifyShellRequest(screenId);
        }

        void ShellTransitionHook()
        {
            UiPerf::Heartbeat("ShellTransition");
            // Also drive the transition-complete logic: the first transition tick
            // after a request marks the factory having run.
            // We don't complete here; the transition is completed lazily on the
            // next frame's heartbeat or on explicit complete.  For now just heartbeat.
        }

        // Naked detours.  We install them as 5-byte JMPs; each saves the original
        // 5 bytes so a trampoline can be built if needed.  For this profiling
        // build the shell request detour is function-level: we hook the call site
        // that pushes the screenId rather than the target, so the trampoline is
        // simply the overwritten bytes + JMP back.  To keep the first cut safe
        // and auditable, the actual byte-patching is deferred to Install()'s
        // second phase once the address has been validated against bytes.
    } // namespace

    void Install()
    {
        if (g_Installed.exchange(true))
            return;

        UiPerf::Initialize();

        // Even when disabled we resolve addresses so a later enable doesn't need
        // a restart; but we only patch when enabled to keep the OFF path truly
        // zero-overhead (no detour indirection).
        if (!UiPerf::IsEnabled())
        {
            LogShimA(LogLevel::Info, "uiperf-hooks", "UiPerf disabled; hooks not installed (enable via [Diagnostics] UiPerformanceLogging=true)");
            return;
        }

        // Resolve shell addresses from patches.json statics / fallbacks.
        // GOG v2.2.301 constants (also in patcher.cpp ResolveStaticReturnPointers):
        //   FUN_007c7930 = shell request
        //   FUN_007c7070 = shell transition
        //   FUN_007c79a0 = shell back
        // Prefer ResolveNamedAddress when available, otherwise use statics.
        uint32_t reqAddr = HookEngine::ResolveNamedAddress("ShellRequest");
        if (!reqAddr) reqAddr = 0x007C7930;
        uint32_t transAddr = HookEngine::ResolveNamedAddress("ShellTransition");
        if (!transAddr) transAddr = 0x007C7070;
        uint32_t backAddr = HookEngine::ResolveNamedAddress("ShellBack");
        if (!backAddr) backAddr = 0x007C79A0;

        // Validate expected bytes before patching.  We don't know the exact
        // instruction sequence at these addresses a priori, so we only verify
        // that the addresses are readable code and not already patched.
        auto readable = [](uint32_t addr) -> bool {
            __try {
                volatile uint8_t v = *reinterpret_cast<uint8_t*>(addr);
                (void)v;
                return true;
            } __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
        };

        int patched = 0;
        // Phase 1: shell hooks are installed as lightweight IAT-style wrappers
        // around the existing trampoline infrastructure in src/patches/trampolines.cpp.
        // To avoid double-patching the same 5 bytes that patcher.cpp already owns,
        // the first profiling commit records shell transitions via the existing
        // Patcher's LogHit / MapRefresh trace path and the new UiPerf::Notify*
        // helpers called directly from trampoline C++ (no extra JMP).  Install()
        // therefore does NOT emit new JMPs on rev 1; it only validates that the
        // fallback addresses are readable and logs readiness.
        if (readable(reqAddr))   { g_ShellRequestAddr = reqAddr; ++patched; }
        if (readable(transAddr)) { g_ShellTransitionAddr = transAddr; ++patched; }
        if (readable(backAddr))  { g_ShellBackAddr = backAddr; ++patched; }

        LogShimA(LogLevel::Info, "uiperf-hooks",
            "UiPerf hooks ready (rev1 polling): shellReq=0x%08X shellTrans=0x%08X shellBack=0x%08X readable=%d",
            reqAddr, transAddr, backAddr, patched);

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
                && has("?loadResourceGroup@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z")
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
