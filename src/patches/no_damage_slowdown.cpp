// no_damage_slowdown.cpp
// BZR Open Shim - No Damage Slowdown (SinglePlayer tier): removes Redux's
// low-health performance penalty from every unit.
#include "bzr_hooks.h"
#include "hook_engine.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <cstdint>

namespace BZROpenShim
{
    namespace Hooks
    {
        // The 1.5 decompile names the function GetPerformance(float health):
        // 1.0 at >= 0.5 health, then ramping down to 0 below that. Seven
        // Simulate paths (hover, producer, SAV, torpedo, turret craft/tank,
        // walker) scale their ODF accel/velocity/turn by it. BZ 1.4 and
        // earlier appear to lack it (likely, unproven).
        //
        // Live GOG layout at 0x004E9610 (cdecl, returns in ST0):
        //   0F 2F 05 [84 25 8A 00]   comiss xmm0,[0.5]
        //   72 06                    jb   <ramp>          ; row + 0x12
        //   D9 E8                    fld1 ; ret 1.0
        // NOPing the jb sends every health ratio down the fld1 path.
        static constexpr uint32_t kGateOffset = 0x12;
        static constexpr uint8_t kGateStock[2] = { 0x72, 0x06 };
        static constexpr uint8_t kGatePatched[2] = { 0x90, 0x90 };

        static uintptr_t g_NoDmgGateAddr = 0;
        static bool g_NoDmgConfigInitialized = false;
        static bool g_NoDmgEnabled = false;      // openshim.ini / settings row
        static bool g_NoDmgPatchActive = false;  // what the bytes currently say

        static bool NoDamageSlowdownBound()
        {
            static const bool bound = [] {
                uint32_t fn = 0;
                const HookEngine::EngineRow rows[] = {
                    { "GetPerformanceHealthGate", &fn },
                };
                if (!HookEngine::BindEngineRows("No damage slowdown", rows))
                    return false;
                g_NoDmgGateAddr = fn + kGateOffset;
                // A re-resolve with the patch already in place must not read as
                // "not applied", or the network-game revert would be skipped.
                g_NoDmgPatchActive = ExpectedBytesMatchAt(g_NoDmgGateAddr, kGatePatched, sizeof(kGatePatched));
                if (!g_NoDmgPatchActive &&
                    !ExpectedBytesMatchAt(g_NoDmgGateAddr, kGateStock, sizeof(kGateStock)))
                {
                    Log(L"[NODMGSLOW] Gate bytes are neither stock nor patched; standing down\n");
                    return false;
                }
                return true;
            }();
            return bound;
        }

        // Multiplayer gate: also writes the stock bytes back in a network game,
        // since peers run the stock penalty and the sim must match.
        void RefreshNoDamageSlowdownState()
        {
            const bool wantActive = g_NoDmgEnabled && IsSinglePlayerSession();
            if (!wantActive && !g_NoDmgPatchActive)
                return;
            if (!NoDamageSlowdownBound())
                return;
            if (wantActive == g_NoDmgPatchActive)
                return;
            if (!WritePatchBytes(g_NoDmgGateAddr, wantActive ? kGatePatched : kGateStock, sizeof(kGateStock)))
                return;
            g_NoDmgPatchActive = wantActive;
            Log(L"[NODMGSLOW] Low-health slowdown %hs (%hs)\n",
                wantActive ? "removed" : "restored to stock",
                wantActive ? "single-player" : "disabled or network game");
        }

        void InitializeNoDamageSlowdownConfig()
        {
            if (g_NoDmgConfigInitialized)
                return;
            g_NoDmgConfigInitialized = true;
            bool cfg = false;
            g_NoDmgEnabled = TryGetUserConfigBool(kUserConfigSinglePlayerSection, "NoDamageSlowdown", cfg) && cfg;
            Log(L"[NODMGSLOW] No damage slowdown baseline=%hs (SP-only)\n", g_NoDmgEnabled ? "on" : "off");
            RefreshNoDamageSlowdownState();
        }

        void ReloadNoDamageSlowdownConfig()
        {
            g_NoDmgConfigInitialized = false;
            InitializeNoDamageSlowdownConfig();
        }
    }
}
