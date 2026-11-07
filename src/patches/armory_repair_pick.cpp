// armory_repair_pick.cpp
// BZR Open Shim - let a guest pick an allied damaged building for RKIT repair
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// The Armory target validator (GOG 0x00472DA0) accepts a repair target when
// GetCurHealth(target) < GetMaxHealth(target) (FUN_0046FBD0 +0x204 against
// FUN_004624F0 +0x208). On a guest's remote copy of a host building +0x204
// stays at max while the health ratio +0x200 is synced, so the pick is
// rejected. Only the current-health call at 0x004730F3 is redirected; the
// stock accessor is untouched.

#include "armory_repair_pick.h"

#include "armory_repair_pick_policy.h"
#include "bzr_hooks_internal.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>

#include <cfloat>
#include <cstdint>

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "armory";

        // ecx = object; float returned in ST0 like the stock accessor.
        float __fastcall RepairPickCurrentHealth(const void* obj)
        {
            float current = 0.0f;
            float ratio = 0.0f;
            float maxHealth = 0.0f;
            __try
            {
                const uint8_t* base = static_cast<const uint8_t*>(obj);
                current = *reinterpret_cast<const volatile float*>(base + 0x204);
                ratio = *reinterpret_cast<const volatile float*>(base + 0x200);
                maxHealth = *reinterpret_cast<const volatile float*>(base + 0x208);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return FLT_MAX; // reject: never report damage we could not read
            }
            return ArmoryRepairPickHealth(current, ratio, maxHealth);
        }
    }

    void InitializeArmoryRepairPick()
    {
        const uint32_t callSite = HookEngine::ResolveNamedAddress("ArmoryRepairPick::CurHealthCall");
        const uint32_t curHealth = HookEngine::ResolveNamedAddress("ArmoryRepairPick::CurHealth");
        if (callSite == 0 || curHealth == 0)
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[ArmoryRepairPick] stands down: call 0x%08X target 0x%08X", callSite, curHealth);
            return;
        }
        if (!Hooks::RedirectCallTarget(callSite, curHealth,
                                       reinterpret_cast<uintptr_t>(&RepairPickCurrentHealth)))
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[ArmoryRepairPick] stands down: call at 0x%08X does not target 0x%08X",
                     callSite, curHealth);
            return;
        }
        LogShimA(LogLevel::Info, kComponent, "[ArmoryRepairPick] installed at 0x%08X", callSite);
    }
}
