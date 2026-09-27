// global_turbo.cpp
// BZR Open Shim - global and per-unit turbo (SinglePlayer tier) and its
// bridge accessors, split out of bzr_hooks.cpp. Installed and configured
// from there; shared helpers come from bzr_hooks_internal.h.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>

namespace BZROpenShim
{
    namespace Hooks
    {
        // --- Global turbo (SinglePlayer tier) ----------------------------------
        // Forces units to turbo, mirroring EXU's GlobalTurbo exactly: redirect the
        // first throttle-tolerance comparison to a 0.9 constant and NOP the second
        // turbo gate so units turbo whenever near full throttle. OpenShim owns the
        // two byte patches plus the per-unit simulation boundary hooks. EXU's
        // Lua APIs delegate here when the hook ownership export is available;
        // its original native implementation remains a standalone fallback.
        // All turbo behavior is hard-disabled in network games.
        //
        // Live GOG layout at 0x00601CA0:
        //   0F 2F 05 [04 26 8A 00]   comiss xmm0,[0x008A2604]   ; operand@0x601CA3
        //   ...
        //   76 0C                    jbe  0x601CC3              ; gate  @0x601CB5
        static constexpr uintptr_t kGlobalTurboComissOperandAddr = 0x00601CA3;
        static constexpr uintptr_t kGlobalTurboSecondGateAddr = 0x00601CB5;
        static constexpr uint8_t kGlobalTurboComissOperandExpected[4] = { 0x04, 0x26, 0x8A, 0x00 };
        static constexpr uint8_t kGlobalTurboSecondGateExpected[2] = { 0x76, 0x0C };
        static constexpr uint8_t kGlobalTurboSecondGatePatched[2] = { 0x90, 0x90 };
        static constexpr uintptr_t kUnitTurboBeginHookAddr = 0x00601C92;
        static constexpr uintptr_t kUnitTurboEndHookAddr = 0x00601CCD;
        static constexpr uint8_t kUnitTurboBeginHookExpected[6] = {
            0x8B, 0x45, 0x90, 0xD9, 0x58, 0x08
        };
        static constexpr uint8_t kUnitTurboEndHookExpected[9] = {
            0x8B, 0x55, 0x90, 0x8B, 0x85, 0x78, 0xFF, 0xFF, 0xFF
        };
        static constexpr bool kGlobalTurboEnabledDefault = false;

        // The comiss operand is redirected to this constant (EXU uses 0.9f). Must
        // live for the process lifetime — its absolute address is written into the
        // instruction, so a namespace-scope static is required.
        static float g_GlobalTurboTolerance = 0.9f;
        bool g_GlobalTurboConfigInitialized = false;
        static bool g_GlobalTurboEnabled = kGlobalTurboEnabledDefault;      // desired
        static bool g_GlobalTurboBaselineEnabled = kGlobalTurboEnabledDefault;  // openshim.ini
        static bool g_GlobalTurboBaselineCaptured = false;
        static bool g_GlobalTurboPatchActive = false;
        static bool g_UnitTurboHooksInstalled = false;
        static bool g_UnitTurboHookMismatchLogged = false;
        static std::unordered_map<uint32_t, bool> g_UnitTurboOverrides;

        using FnGameObjectGetHandle = uint32_t(__thiscall*)(void* object);
        using FnExuUpdateCullingForUnit = void(__cdecl*)(void* object);
        static FnExuUpdateCullingForUnit g_ExuFn_UpdateCullingForUnit = nullptr;
        static HMODULE g_ExuCullingCallbackModule = nullptr;

        // Writes both turbo sites for the desired state. When activating, the
        // comiss operand is rewritten to the absolute address of our tolerance
        // constant and the second gate is NOP'd; when reverting, both are restored
        // to the stock bytes.
        static bool WriteGlobalTurboPatch(bool active)
        {
            uint8_t operandBytes[sizeof(kGlobalTurboComissOperandExpected)];
            if (active)
            {
                const uint32_t tolAddr =
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&g_GlobalTurboTolerance));
                std::memcpy(operandBytes, &tolAddr, sizeof(operandBytes));
            }
            else
            {
                std::memcpy(operandBytes, kGlobalTurboComissOperandExpected, sizeof(operandBytes));
            }
            const uint8_t* gateBytes =
                active ? kGlobalTurboSecondGatePatched : kGlobalTurboSecondGateExpected;

            if (!WritePatchBytes(kGlobalTurboComissOperandAddr, operandBytes, sizeof(operandBytes)))
                return false;
            if (!WritePatchBytes(kGlobalTurboSecondGateAddr, gateBytes, sizeof(kGlobalTurboSecondGateExpected)))
                return false;
            return true;
        }

        static bool ReconcileGlobalTurboPatchState(bool wantActive, bool writeLog)
        {
            if (wantActive == g_GlobalTurboPatchActive)
                return true;

            if (wantActive)
            {
                if (!ExpectedBytesMatchAt(kGlobalTurboComissOperandAddr,
                                          kGlobalTurboComissOperandExpected,
                                          sizeof(kGlobalTurboComissOperandExpected)) ||
                    !ExpectedBytesMatchAt(kGlobalTurboSecondGateAddr,
                                          kGlobalTurboSecondGateExpected,
                                          sizeof(kGlobalTurboSecondGateExpected)))
                {
                    return false;
                }
                if (!WriteGlobalTurboPatch(true))
                    return false;

                g_GlobalTurboPatchActive = true;
                if (writeLog)
                {
                    Log(L"[TURBO] Applied global turbo (tolerance=%.3f) tol@0x%08X gate@0x%08X\n",
                        static_cast<double>(g_GlobalTurboTolerance),
                        static_cast<uint32_t>(kGlobalTurboComissOperandAddr),
                        static_cast<uint32_t>(kGlobalTurboSecondGateAddr));
                }
                return true;
            }

            // Revert only if the second gate still holds our NOPs. If it does
            // not, another owner changed the site and we leave it untouched.
            if (!ExpectedBytesMatchAt(kGlobalTurboSecondGateAddr,
                                      kGlobalTurboSecondGatePatched,
                                      sizeof(kGlobalTurboSecondGatePatched)))
            {
                g_GlobalTurboPatchActive = false;
                return false;
            }
            if (!WriteGlobalTurboPatch(false))
                return false;

            g_GlobalTurboPatchActive = false;
            if (writeLog)
                Log(L"[TURBO] Reverted global turbo\n");
            return true;
        }

        static FnExuUpdateCullingForUnit ResolveExuCullingCallback()
        {
            // Two loader lookups per unit per tick added up. The module set
            // only changes at load time, so re-probe once a second and answer
            // from the cache in between.
            static ULONGLONG s_nextProbeTick = 0;
            const ULONGLONG now = GetTickCount64();
            if (now < s_nextProbeTick)
                return g_ExuFn_UpdateCullingForUnit;
            s_nextProbeTick = now + 1000;
            HMODULE module = GetModuleHandleA("exu.dll");
            if (!module)
                module = GetModuleHandleA("ExtraUtilities.dll");
            if (module != g_ExuCullingCallbackModule)
            {
                g_ExuCullingCallbackModule = module;
                g_ExuFn_UpdateCullingForUnit = module
                    ? reinterpret_cast<FnExuUpdateCullingForUnit>(
                        GetProcAddress(module, "EXU_UpdateCullingForUnit"))
                    : nullptr;
            }
            return g_ExuFn_UpdateCullingForUnit;
        }

        static bool TryGetTurboObjectHandle(void* object, uint32_t& outHandle)
        {
            outHandle = 0;
            if (!object || g_GameObjectGetHandleAddr == 0)
                return false;
            __try
            {
                outHandle = reinterpret_cast<FnGameObjectGetHandle>(
                    g_GameObjectGetHandleAddr)(object);
                return outHandle != 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Keep SEH in a leaf with no STL/RAII locals. Debug MSVC iterators
        // require object unwinding, which cannot coexist with __try in the same
        // function (C2712).
        static void TryUpdateExuCullingForUnit(FnExuUpdateCullingForUnit updateCulling,
                                               void* object)
        {
            if (!updateCulling)
                return;
            __try
            {
                updateCulling(object);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        static void __cdecl HandleUnitTurboBoundary(void* object, int boundary)
        {
            if (boundary == 0)
                TryUpdateExuCullingForUnit(ResolveExuCullingCallback(), object);

            uint32_t handle = 0;
            if (!TryGetTurboObjectHandle(object, handle))
                return;
            const auto overrideIt = g_UnitTurboOverrides.find(handle);
            if (overrideIt == g_UnitTurboOverrides.end())
                return;

            const bool singlePlayer = ReadLocalPlayerNetIdValue() == 0;
            const bool wantActive = boundary == 0
                ? (singlePlayer && overrideIt->second)
                : (singlePlayer && g_GlobalTurboEnabled);
            ReconcileGlobalTurboPatchState(wantActive, false);
        }

        static void __declspec(naked) UnitTurboBeginHook()
        {
            __asm
            {
                pushad
                pushfd
                push 0
                mov eax, [eax + 0x10]
                push eax
                call HandleUnitTurboBoundary
                add esp, 8
                popfd
                popad
                mov eax, [ebp - 0x70]
                fstp dword ptr [eax + 0x08]
                ret
            }
        }

        static void __declspec(naked) UnitTurboEndHook()
        {
            __asm
            {
                pushad
                pushfd
                push 1
                mov eax, [edx + 0x10]
                push eax
                call HandleUnitTurboBoundary
                add esp, 8
                popfd
                popad
                mov edx, [ebp - 0x70]
                mov eax, [ebp - 0x88]
                ret
            }
        }

        static bool WriteUnitTurboCallHook(
            uintptr_t address,
            size_t length,
            const void* target)
        {
            if (length < 5 || !target)
                return false;
            std::array<uint8_t, 9> patch = {};
            patch.fill(0x90);
            patch[0] = 0xE8;
            const int32_t relative =
                static_cast<int32_t>(reinterpret_cast<uintptr_t>(target)) -
                static_cast<int32_t>(address + 5);
            std::memcpy(patch.data() + 1, &relative, sizeof(relative));
            return WritePatchBytes(address, patch.data(), length);
        }

        void InstallUnitTurboHooksIfPossible()
        {
            if (g_UnitTurboHooksInstalled)
                return;
            if (!ExpectedBytesMatchAt(
                    kUnitTurboBeginHookAddr,
                    kUnitTurboBeginHookExpected,
                    sizeof(kUnitTurboBeginHookExpected)) ||
                !ExpectedBytesMatchAt(
                    kUnitTurboEndHookAddr,
                    kUnitTurboEndHookExpected,
                    sizeof(kUnitTurboEndHookExpected)))
            {
                if (!g_UnitTurboHookMismatchLogged)
                {
                    g_UnitTurboHookMismatchLogged = true;
                    Log(L"[TURBO] Per-unit hook bytes not ready/mismatched; deferring\n");
                }
                return;
            }

            if (!WriteUnitTurboCallHook(
                    kUnitTurboBeginHookAddr,
                    sizeof(kUnitTurboBeginHookExpected),
                    reinterpret_cast<const void*>(UnitTurboBeginHook)))
            {
                return;
            }
            if (!WriteUnitTurboCallHook(
                    kUnitTurboEndHookAddr,
                    sizeof(kUnitTurboEndHookExpected),
                    reinterpret_cast<const void*>(UnitTurboEndHook)))
            {
                WritePatchBytes(
                    kUnitTurboBeginHookAddr,
                    kUnitTurboBeginHookExpected,
                    sizeof(kUnitTurboBeginHookExpected));
                return;
            }

            g_UnitTurboHooksInstalled = true;
            g_UnitTurboHookMismatchLogged = false;
            Log(L"[TURBO] Installed shim-owned per-unit hooks begin=0x%08X end=0x%08X\n",
                static_cast<uint32_t>(kUnitTurboBeginHookAddr),
                static_cast<uint32_t>(kUnitTurboEndHookAddr));
        }

        // Reconciles the live turbo bytes with the desired global state.
        void RefreshGlobalTurboPatchState()
        {
            const bool wantActive =
                g_GlobalTurboEnabled &&
                (ReadLocalPlayerNetIdValue() == 0);
            ReconcileGlobalTurboPatchState(wantActive, true);
        }

        void InitializeGlobalTurboConfig()
        {
            if (g_GlobalTurboConfigInitialized)
                return;
            g_GlobalTurboConfigInitialized = true;

            bool enabled = kGlobalTurboEnabledDefault;

            // Global user baseline (openshim.ini [SinglePlayer]).
            bool cfg = false;
            if (TryGetUserConfigBool(kUserConfigSinglePlayerSection, "Turbo", cfg))
                enabled = cfg;

            // Env overrides / kill switch (parity with the other features).
            if (EnvFlagEnabled("OPENSHIM_GLOBAL_TURBO") || EnvFlagEnabled("BZR_GLOBAL_TURBO"))
                enabled = true;
            else if (EnvFlagEnabled("OPENSHIM_DISABLE_GLOBAL_TURBO") ||
                     EnvFlagEnabled("BZR_DISABLE_GLOBAL_TURBO"))
                enabled = false;

            // Advanced: override the throttle tolerance (default 0.9 matches EXU).
            float tol = g_GlobalTurboTolerance;
            if (TryGetEnvFloat("OPENSHIM_GLOBAL_TURBO_TOLERANCE", tol))
                g_GlobalTurboTolerance = tol;

            g_GlobalTurboEnabled = enabled;
            g_GlobalTurboBaselineEnabled = enabled;
            g_GlobalTurboBaselineCaptured = true;

            InstallUnitTurboHooksIfPossible();
            Log(L"[TURBO] Global turbo baseline=%hs tolerance=%.3f (SP-only; shim-owned)\n",
                enabled ? "on" : "off",
                static_cast<double>(g_GlobalTurboTolerance));

            RefreshGlobalTurboPatchState();
        }

        void RevertGlobalTurboToBaseline()
        {
            InitializeGlobalTurboConfig();  // idempotent; ensures baseline captured
            if (!g_GlobalTurboBaselineCaptured)
                return;
            g_UnitTurboOverrides.clear();
            g_GlobalTurboEnabled = g_GlobalTurboBaselineEnabled;
            RefreshGlobalTurboPatchState();
        }
    }

    using namespace Hooks;

    bool GetGlobalTurboFromBridge()
    {
        InitializeGlobalTurboConfig();
        return g_GlobalTurboEnabled;
    }

    bool SetGlobalTurboFromBridge(bool enabled)
    {
        InitializeGlobalTurboConfig();
        InstallUnitTurboHooksIfPossible();
        g_GlobalTurboEnabled = enabled;
        RefreshGlobalTurboPatchState();
        Log(L"[MISSIONHOOK] global turbo %hs patch=%hs\n",
            enabled ? "enabled" : "disabled",
            g_GlobalTurboPatchActive ? "active" : "inactive");
        return !enabled || g_GlobalTurboPatchActive;
    }

    bool HasUnitTurboHooksFromBridge()
    {
        InstallUnitTurboHooksIfPossible();
        return g_UnitTurboHooksInstalled;
    }

    bool GetUnitTurboFromBridge(uint32_t handle)
    {
        const auto it = g_UnitTurboOverrides.find(handle);
        return it != g_UnitTurboOverrides.end() && it->second;
    }

    bool SetUnitTurboFromBridge(uint32_t handle, bool enabled)
    {
        if (handle == 0)
            return false;
        // Accept the mission override even if Steam's runtime bytes have not
        // settled yet. The deferred installer will make it effective as soon
        // as the guarded hook sites become available.
        g_UnitTurboOverrides[handle] = enabled;
        InstallUnitTurboHooksIfPossible();
        return true;
    }
}
