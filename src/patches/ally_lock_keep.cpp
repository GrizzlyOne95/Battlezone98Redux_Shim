// ally_lock_keep.cpp
// BZR Open Shim - keeps a Lua LockAllies(true) made in Start() alive.
#include "ally_lock_keep.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "patcher.h"
#include <Windows.h>
#include <cstring>

namespace BZROpenShim
{
    namespace Hooks
    {
        // Recovered from the GOG 2.2.301 image (2026-11-23). Lua LockAllies
        // (handler 0x00501CB0 -> setter 0x0046CE10) stores the gate dword
        // 0x0260D5EC; the Y/U handler 0x0046CD10 does nothing while it is
        // nonzero. AllyEditor::Init 0x0046CC80 writes the gate to 0, and the
        // UI rebuild 0x00681DF0 calls it (0x00681E2A) for net games; sim
        // startup 0x006185F0 reaches that rebuild after Start(), so a lock set
        // in Start() is lost. The wrapper keeps the gate across that one call.
        // The network-startup reset (0x00570170) stays stock.
        namespace
        {
            using InitFn = void(__cdecl*)();
            InitFn g_Init = nullptr;
            volatile uint32_t* g_Gate = nullptr;
            uint32_t g_LastRestored = 0;

            bool ReadGate(uint32_t& out)
            {
                __try { out = *g_Gate; return true; }
                __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
            }

            bool WriteGate(uint32_t value)
            {
                __try { *g_Gate = value; return true; }
                __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
            }

            void __cdecl AllyInitHook()
            {
                uint32_t saved = 0;
                const bool have = ReadGate(saved);
                g_Init();
                if (have && saved != 0 && WriteGate(saved) && saved != g_LastRestored)
                    Log(L"[ALLYLOCK] ally editor rebuilt; restored LockAllies gate=%u\n", saved);
                if (have) g_LastRestored = saved;
            }
        }

        bool IsAllyLockKeepPatchName(const char* name)
        {
            return name && strcmp(name, "Ally Lock Survives UI Rebuild") == 0;
        }

        uint32_t PrepareAllyLockKeepHook(const char* name, uint32_t site, void* original)
        {
            bool enabled = true;  // default on: the lost lock is a stock defect (1.5 kept it)
            TryGetUserConfigBool("Network", "AllyLockSurvivesStart", enabled);
            if (EnvFlagEnabled("OPENSHIM_DISABLE_ALLY_LOCK_SURVIVES_START") ||
                EnvFlagEnabled("BZR_DISABLE_ALLY_LOCK_SURVIVES_START"))
                enabled = false;
            if (!enabled) return 0;

            const uint32_t expected = HookEngine::ResolveNamedAddress("AllyEditor::Init");
            const uint32_t gate = HookEngine::ResolveNamedAddress("AllyLock::Gate");
            if (!original || !expected || !gate || reinterpret_cast<uintptr_t>(original) != expected)
            {
                Log(L"[ALLYLOCK] %hs identity failed site=0x%08X original=%p expected=0x%08X gate=0x%08X; stock call kept\n",
                    name, site, original, expected, gate);
                return 0;
            }
            g_Init = reinterpret_cast<InitFn>(original);
            g_Gate = reinterpret_cast<volatile uint32_t*>(static_cast<uintptr_t>(gate));
            Log(L"[ALLYLOCK] %hs redirected site=0x%08X original=%p gate=0x%08X\n", name, site, original, gate);
            return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&AllyInitHook));
        }
    }
}
